//
// Created by Moritz Herzog on 09.05.25.
//

#include <kerml/parser/KerMlListenerImplementation.h>
#include <kerml/KerML.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <sysmlv2/resolution/Retarget.h>

namespace {
    using SysMLv2::Files::ReferenceKind;
    using SysMLv2::Files::ReferenceRole;
    using ElementPtr = std::shared_ptr<KerML::Entities::Element>;

    template <class T>
    std::shared_ptr<T> newPlaceholder(ReferenceKind kind, const std::string& name) {
        return std::dynamic_pointer_cast<T>(SysMLv2::Files::makePlaceholder(kind, name));
    }

    // A reference for which no scoped resolution is attempted (the target is a member of the value of another expression, or a
    // parameter of the invoked function). It keeps its placeholder and is reported as "not attempted".
    std::shared_ptr<KerML::Entities::Feature> notAttemptedFeature(SysMLv2::Files::ReferenceRecorder& recorder, const std::string& name,
                                                                  const ElementPtr& context, antlr4::ParserRuleContext* position) {
        return recorder.reference<KerML::Entities::Feature>(name, ReferenceKind::Feature, ReferenceRole::NotAttempted, context, false, nullptr,
                                                            position, nullptr);
    }
}

// Empty callbacks below are intentional for syntax wrappers and tokens whose
// semantics are handled by their enclosing or child rule. Do not create a
// second model element in those callbacks.



KerMLListenerImplementation::KerMLListenerImplementation() { }

KerMLListenerImplementation::~KerMLListenerImplementation() { }

void KerMLListenerImplementation::enterComment(KerMLParser::CommentContext *) { }

void KerMLListenerImplementation::exitComment(KerMLParser::CommentContext *context) {
    // Found by AP4(e) fuzzing (same shape as exitDocumentation/exitTextual_representation below):
    // after error recovery `context` or its expected children (STRING_VALUE() when KEYWORD_LOCALE()
    // is present, REGULAR_COMMENT()) may be missing/null, and ParentStack may be empty.
    if (!context || context->REGULAR_COMMENT() == nullptr) return;

    std::string identification="";
    if(context->identification() != nullptr) {
        identification =  context->identification()->getText();
    }

    const bool hasAbout = context->KEYWORD_ABOUT() != nullptr && !context->annotation().empty();
    std::string locale = "";
    if(context->KEYWORD_LOCALE() != nullptr && context->STRING_VALUE() != nullptr) {
        locale = context->STRING_VALUE()->getText();
    }

    std::string body = context->REGULAR_COMMENT()->getText();

    const auto& comment = std::make_shared<KerML::Entities::Comment>(locale, body);
    Elements.push_back(comment);


    if(!identification.empty())
        comment->setDeclaredName(identification);

    if (hasAbout) {
        // Annotated elements are added once the workspace has resolved the names.
        for (auto& about : context->annotation()) {
            Recorder.reference<KerML::Entities::Element>(about->getText(), ReferenceKind::Element, ReferenceRole::Plain,
                ParentStack.empty() ? nullptr : ParentStack.top(), false, nullptr, about,
                [comment](const std::shared_ptr<KerML::Entities::Element>& target) { comment->appendAnnotatedElement(target); });
        }
    }
    else if (!ParentStack.empty())
        comment->appendAnnotatedElement(ParentStack.top());

    if (!ParentStack.empty())
        ParentStack.top()->appendOwnedElement(comment);
}

void KerMLListenerImplementation::enterStart(KerMLParser::StartContext *)
{
    const auto& rootNamespace = std::make_shared<KerML::Entities::Namespace>("Root Namespace");
    while (!ParentStack.empty()) ParentStack.pop();
    Elements.clear();
    Recorder = SysMLv2::Files::ReferenceRecorder();
    OwnershipKinds.clear();
    MemberMarks.clear();
    Recorder.data.root = rootNamespace;
    ParentStack.push(rootNamespace);
    Elements.push_back(rootNamespace);
}

void KerMLListenerImplementation::exitStart(KerMLParser::StartContext *) {
    // The abstract-syntax ownership (memberships, owners) of the whole source; the root namespace owns the top level elements.
    SysMLv2::Files::OwnershipInput input;
    input.elements = &Elements;
    input.root = Recorder.data.root;
    input.kinds = std::move(OwnershipKinds);
    input.visibility = &Recorder.data.visibility;
    SysMLv2::Files::buildOwnership(input);
    OwnershipKinds.clear();
}

void KerMLListenerImplementation::enterStartRule(KerMLParser::StartRuleContext *) { }

void KerMLListenerImplementation::exitStartRule(KerMLParser::StartRuleContext *) { }

void KerMLListenerImplementation::enterElements(KerMLParser::ElementsContext *) { }

void KerMLListenerImplementation::exitElements(KerMLParser::ElementsContext *) { }

void KerMLListenerImplementation::enterIdentification(KerMLParser::IdentificationContext *) { }

void KerMLListenerImplementation::exitIdentification(KerMLParser::IdentificationContext *) { }

void KerMLListenerImplementation::enterRelationship_body(KerMLParser::Relationship_bodyContext *) { }

void KerMLListenerImplementation::exitRelationship_body(KerMLParser::Relationship_bodyContext *) { }

void KerMLListenerImplementation::enterRelationship_owned_elements(KerMLParser::Relationship_owned_elementsContext *) { }

void KerMLListenerImplementation::exitRelationship_owned_elements(KerMLParser::Relationship_owned_elementsContext *) { }

void KerMLListenerImplementation::enterRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *) { }

void KerMLListenerImplementation::exitRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *) { }

void KerMLListenerImplementation::enterOwned_related_element(KerMLParser::Owned_related_elementContext *) { }

void KerMLListenerImplementation::exitOwned_related_element(KerMLParser::Owned_related_elementContext *) { }

void KerMLListenerImplementation::enterDependency(KerMLParser::DependencyContext *) {
    const auto dep = std::make_shared<KerML::Entities::Dependency>();
    ParentStack.emplace(dep);
}

void KerMLListenerImplementation::exitDependency(KerMLParser::DependencyContext *ctx) {
    if (ParentStack.empty()) return;
    const auto dep = std::dynamic_pointer_cast<KerML::Entities::Dependency>(ParentStack.top());
    if (!dep) return;
    ParentStack.pop();

    if (ctx && ctx->identification()) {
        dep->setDeclaredName(ctx->identification()->getText());
    }

    if (ctx && ctx->KEYWORD_TO()) {
        size_t toIndex = ctx->KEYWORD_TO()->getSymbol()->getTokenIndex();
        std::vector<std::shared_ptr<KerML::Entities::Element>> clients;
        std::vector<std::shared_ptr<KerML::Entities::Element>> suppliers;
        for (auto q : ctx->qualified_name()) {
            const bool isClient = q->getStart()->getTokenIndex() < toIndex;
            // The ends of a dependency are resolved from the namespace that owns the dependency.
            auto elem = Recorder.replacing<KerML::Entities::Element>(q->getText(), ReferenceKind::Element, ReferenceRole::Plain,
                ParentStack.empty() ? nullptr : ParentStack.top(), false, nullptr, q,
                [dep, isClient](const ElementPtr& placeholder, const ElementPtr& target) {
                    auto ends = isClient ? dep->client() : dep->supplier();
                    SysMLv2::Files::replaceInVector(ends, placeholder, target);
                    if (isClient) dep->setClient(ends);
                    else dep->setSupplier(ends);
                });
            if (isClient) {
                clients.push_back(elem);
            } else {
                suppliers.push_back(elem);
            }
        }
        dep->setClient(clients);
        dep->setSupplier(suppliers);
    }

    Elements.push_back(dep);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(dep);
    }
}

void KerMLListenerImplementation::enterAnnotation(KerMLParser::AnnotationContext *) { }

void KerMLListenerImplementation::exitAnnotation(KerMLParser::AnnotationContext *ctx) {
    if (!ctx || ParentStack.empty()) return;
    // Comments resolve their annotations in exitComment; metadata is on the stack.
    if (auto metadata = std::dynamic_pointer_cast<KerML::Entities::MetadataFeature>(ParentStack.top())) {
        Recorder.reference<KerML::Entities::Element>(ctx->getText(), ReferenceKind::Element, ReferenceRole::Plain, metadata, true, nullptr, ctx,
            [metadata](const ElementPtr& target) { metadata->appendAnnotatedElement(target); });
    }
}

void KerMLListenerImplementation::enterOwned_annotation(KerMLParser::Owned_annotationContext*) { }

void KerMLListenerImplementation::exitOwned_annotation(KerMLParser::Owned_annotationContext *) { }

void KerMLListenerImplementation::enterAnnotating_element(KerMLParser::Annotating_elementContext *) { }

void KerMLListenerImplementation::exitAnnotating_element(KerMLParser::Annotating_elementContext *) { }

void KerMLListenerImplementation::enterDocumentation(KerMLParser::DocumentationContext *) { }

void KerMLListenerImplementation::exitDocumentation(KerMLParser::DocumentationContext *context) {
    // Found by AP4(e) fuzzing (truncated/mutated KerML/DataTypes/Collections.kerml): after error
    // recovery, `context` or its expected children (in particular REGULAR_COMMENT(), and
    // STRING_VALUE() when KEYWORD_LOCALE() is present) may be missing/null, and ParentStack may be
    // empty. Bail out rather than dereferencing null / calling .top() on an empty stack.
    if (!context || ParentStack.empty()) return;
    if (context->REGULAR_COMMENT() == nullptr) return;

    std::string identification = "";
    if(context->identification()!=nullptr) {
        identification = context->identification()->getText();
    }

    std::string locale = "";
    if(context->KEYWORD_LOCALE()!=nullptr && context->STRING_VALUE()!=nullptr) {
        locale = context->STRING_VALUE()->getText();
    }

    std::string body = context->REGULAR_COMMENT()->getText();

    auto documentation = std::make_shared<KerML::Entities::Documentation>(ParentStack.top(), locale, body);
    documentation->setDeclaredName(identification);

    ParentStack.top()->appendOwnedElement(documentation);
}

void KerMLListenerImplementation::enterTextual_representation(KerMLParser::Textual_representationContext *) { }

void KerMLListenerImplementation::exitTextual_representation(KerMLParser::Textual_representationContext *ctx) {
    // Found by AP4(e) fuzzing (same shape as exitDocumentation above): after error recovery `ctx` or
    // its expected children (STRING_VALUE() when KEYWORD_LANGUAGE() is present, REGULAR_COMMENT())
    // may be missing/null.
    if (!ctx || ctx->REGULAR_COMMENT() == nullptr) return;

    std::string language;

    if (ctx->KEYWORD_LANGUAGE()!=nullptr && ctx->STRING_VALUE()!=nullptr)
        language = ctx->STRING_VALUE()->getText();

    const auto textualRepresentation = std::make_shared<KerML::Entities::TextualRepresentation>(language, ctx->REGULAR_COMMENT()->getText());
    Elements.push_back(textualRepresentation);

    if (!ParentStack.empty())
        ParentStack.top()->appendOwnedElement(textualRepresentation);
}

void KerMLListenerImplementation::enterRoot_namespace(KerMLParser::Root_namespaceContext*) { }

void KerMLListenerImplementation::exitRoot_namespace(KerMLParser::Root_namespaceContext *) { }

void KerMLListenerImplementation::enterNamespace(KerMLParser::NamespaceContext *) {
    const auto namespaceElement = std::make_shared<KerML::Entities::Namespace>();

    if(!ParentStack.empty())
        ParentStack.top()->appendOwnedElement(namespaceElement);

    ParentStack.push(namespaceElement);
}

void KerMLListenerImplementation::exitNamespace(KerMLParser::NamespaceContext *) {
    if (ParentStack.empty()) return;
    const auto namespaceElement = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top());
    ParentStack.pop();
    if (namespaceElement) {
        Elements.push_back(namespaceElement);
    }
}

void KerMLListenerImplementation::enterNamespace_declaration(KerMLParser::Namespace_declarationContext *) { }

void KerMLListenerImplementation::exitNamespace_declaration(KerMLParser::Namespace_declarationContext *ctx) {
    if (ParentStack.empty()) return;
    const auto namespaceElement = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top());
    if (namespaceElement && ctx && ctx->identification()) {
        applyIdentification(ctx->identification(), namespaceElement);
    }
}

void KerMLListenerImplementation::enterNamespace_body(KerMLParser::Namespace_bodyContext *) { }

void KerMLListenerImplementation::exitNamespace_body(KerMLParser::Namespace_bodyContext *) { }

void KerMLListenerImplementation::enterNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *) { }

void KerMLListenerImplementation::exitNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *) { }

void KerMLListenerImplementation::enterNamespace_body_element(KerMLParser::Namespace_body_elementContext *) { }

void KerMLListenerImplementation::exitNamespace_body_element(KerMLParser::Namespace_body_elementContext *) { }

void KerMLListenerImplementation::enterMember_prefix(KerMLParser::Member_prefixContext *) { }

void KerMLListenerImplementation::exitMember_prefix(KerMLParser::Member_prefixContext *) { }

void KerMLListenerImplementation::enterVisibility_indicator(KerMLParser::Visibility_indicatorContext *) { }
void KerMLListenerImplementation::exitVisibility_indicator(KerMLParser::Visibility_indicatorContext * ctx) {
    if (ParentStack.empty()) return;
    if (auto import = std::dynamic_pointer_cast<KerML::Entities::Import>(ParentStack.top())) {
        if (ctx->KEYWORD_PRIVATE() != nullptr)
            import->setVisibility(KerML::Entities::PRIVATE);
        else if (ctx->KEYWORD_PROTECTED() != nullptr)
            import->setVisibility(KerML::Entities::PROTECTED);
        else if (ctx->KEYWORD_PUBLIC() != nullptr)
            import->setVisibility(KerML::Entities::PUBLIC);
    }
}

void KerMLListenerImplementation::enterNamespace_member(KerMLParser::Namespace_memberContext *) { }

void KerMLListenerImplementation::exitNamespace_member(KerMLParser::Namespace_memberContext *) { }

void KerMLListenerImplementation::enterNon_feature_member(KerMLParser::Non_feature_memberContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OwningMembership>());
}

void KerMLListenerImplementation::exitNon_feature_member(KerMLParser::Non_feature_memberContext *ctx) {
    finishMembership(ctx ? ctx->member_prefix() : nullptr);
}

void KerMLListenerImplementation::enterNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OwningMembership>());
}

void KerMLListenerImplementation::exitNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *ctx) {
    finishMembership(ctx ? ctx->member_prefix() : nullptr);
}

void KerMLListenerImplementation::enterAlias_member(KerMLParser::Alias_memberContext *) { }

void KerMLListenerImplementation::exitAlias_member(KerMLParser::Alias_memberContext* ctx) {
    if (!ctx || !ctx->qualified_name()) return;
    const std::string targetName = ctx->qualified_name()->getText();
    const auto names = ctx->NAME();
    std::string aliasName;
    std::string shortName;
    if (ctx->SYMBOL_SMALLER() != nullptr) {
        if (!names.empty()) shortName = names[0]->getText();
        if (names.size() > 1) aliasName = names[1]->getText();
    }
    else if (!names.empty()) {
        aliasName = names[0]->getText();
    }
    if (aliasName.empty() && shortName.empty()) return;

    // An alias is a non-owning membership of the target in the namespace that declares it.
    auto membership = std::make_shared<KerML::Entities::Membership>();
    if (!aliasName.empty()) membership->setMemberName(aliasName);
    if (!shortName.empty()) membership->setMemberShortName(shortName);
    KerML::Entities::VisibilityKind visibility = KerML::Entities::PUBLIC;
    if (ctx->member_prefix() && ctx->member_prefix()->visibility_indicator()) {
        visibility = importVisibility(ctx->member_prefix()->visibility_indicator());
    }
    membership->setVisibility(visibility);
    const auto owner = ParentStack.empty() ? nullptr : ParentStack.top();
    if (owner) {
        membership->setMembershipOwningNamespace(std::dynamic_pointer_cast<KerML::Entities::Namespace>(owner));
        membership->setOwner(owner);
        owner->appendOwnedElement(membership);
    }
    Elements.push_back(membership);

    auto record = std::make_shared<SysMLv2::Files::AliasRecord>();
    record->owner = owner;
    record->membership = membership;
    record->name = aliasName;
    record->shortName = shortName;
    record->target = targetName;
    record->visibility = visibility;
    if (ctx->getStart() != nullptr) {
        record->line = static_cast<int>(ctx->getStart()->getLine());
        record->column = static_cast<int>(ctx->getStart()->getCharPositionInLine());
    }
    Recorder.data.aliases.push_back(record);

    // The alias name is also recorded on the target as an alternative identifier.
    const std::string aliasId = names.back()->getText();
    Recorder.reference<KerML::Entities::Element>(targetName, ReferenceKind::Element, ReferenceRole::Alias, owner, false, nullptr,
        ctx->qualified_name(), [record, membership, aliasId](const ElementPtr& target) {
            record->resolvedTarget = target;
            membership->setMemberElement(target);
            target->appendAliasId(aliasId);
        });
}

void KerMLListenerImplementation::enterQualified_name(KerMLParser::Qualified_nameContext *) { }

void KerMLListenerImplementation::exitQualified_name(KerMLParser::Qualified_nameContext *) { }

void KerMLListenerImplementation::enterNamespace_import(KerMLParser::Namespace_importContext *) {
    const auto namespaceImport = std::make_shared<KerML::Entities::NamespaceImport>();
    ParentStack.emplace(namespaceImport);
}

void KerMLListenerImplementation::exitNamespace_import(KerMLParser::Namespace_importContext *ctx) {
    if (ParentStack.empty()) return;
    const auto namespaceImport = std::dynamic_pointer_cast<KerML::Entities::NamespaceImport>(ParentStack.top());
    if(!namespaceImport) {
        return;
    }
    ParentStack.pop();
    if (!ctx || !ctx->import_declaration()) {
        // Incomplete context after error recovery; nothing more to attach.
        return;
    }
    const bool isAll = ctx->KEYWORD_ALL() != nullptr;

    KerMLParser::Membership_importContext* importedName = ctx->import_declaration()->membership_import();
    if (importedName == nullptr && ctx->import_declaration()->filter_package() != nullptr)
        importedName = ctx->import_declaration()->filter_package()->membership_import();
    const bool star = importedName != nullptr && importedName->SYMBOL_STAR() != nullptr;
    const bool recursive = importedName != nullptr && importedName->SYMBOL_DOUBLE_STAR() != nullptr;
    const bool hasName = importedName != nullptr && importedName->qualified_name() != nullptr;
    const auto visibility = ctx->visibility_indicator() ? importVisibility(ctx->visibility_indicator()) : KerML::Entities::PRIVATE;

    // One import element per import: `import A::B;` is a MembershipImport (of the membership of B), `import A::*;` and `import A::**;` are
    // NamespaceImports. The element pushed by enterNamespace_import is the NamespaceImport; a membership import replaces it.
    std::shared_ptr<KerML::Entities::Import> import = namespaceImport;
    std::shared_ptr<KerML::Entities::Membership> importedMembership;
    if (hasName && !star && !recursive) {
        const auto membershipImport = std::make_shared<KerML::Entities::MembershipImport>();
        importedMembership = std::make_shared<KerML::Entities::Membership>();
        importedMembership->setMemberName(importedName->qualified_name()->getText());
        membershipImport->setImportedMembership(importedMembership);
        import = membershipImport;
    } else {
        // The model keeps the imported namespace by name until the reference is resolved (see recordImport).
        namespaceImport->setImportedNamespace(std::make_shared<KerML::Entities::Namespace>(ctx->import_declaration()->getText(), true));
    }
    import->setIsRecursive(recursive);
    import->setIsImportAll(isAll);
    import->setVisibility(visibility);
    if (!ParentStack.empty()) {
        import->setImportOwningNamespace(std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top()));
    }

    Elements.push_back(import);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(import);
    }

    // The imported name is resolved by the workspace: `A::*`, `A::**` import the members of the namespace A, `A::b` the member b.
    if (hasName) {
        recordImport(import, ctx, importedName->qualified_name()->getText(), star, recursive, isAll, visibility, importedMembership);
    }
}

void KerMLListenerImplementation::enterImport_declaration(KerMLParser::Import_declarationContext *) { }

void KerMLListenerImplementation::exitImport_declaration(KerMLParser::Import_declarationContext *) { }

void KerMLListenerImplementation::enterMembership_import(KerMLParser::Membership_importContext *) { }

void KerMLListenerImplementation::exitMembership_import(KerMLParser::Membership_importContext *) {
    // The import element is created by exitNamespace_import (there is exactly one per import).
}

void KerMLListenerImplementation::enterFilter_package(KerMLParser::Filter_packageContext *) { }

void KerMLListenerImplementation::exitFilter_package(KerMLParser::Filter_packageContext *) { }

void KerMLListenerImplementation::enterFilter_package_member(KerMLParser::Filter_package_memberContext *) {
    const auto filter = std::make_shared<KerML::Entities::ElementFilterMembership>();
    ParentStack.emplace(filter);
}

void KerMLListenerImplementation::exitFilter_package_member(KerMLParser::Filter_package_memberContext *) {
    if (ParentStack.empty()) return;
    const auto filter = std::dynamic_pointer_cast<KerML::Entities::ElementFilterMembership>(ParentStack.top());
    if (!filter) return;
    ParentStack.pop();

    if (!filter->ownedRelatedElement().empty()) {
        for (const auto& elem : filter->ownedRelatedElement()) {
            if (auto expr = std::dynamic_pointer_cast<KerML::Entities::Expression>(elem)) {
                filter->setCondition(expr);
                break;
            }
        }
    }
    if (!ParentStack.empty()) {
        if (auto pkg = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top())) {
            pkg->appendOwnedMembership(filter);
            filter->setMembershipOwningNamespace(pkg);
        }
        ParentStack.top()->appendOwnedElement(filter);
    }
    Elements.push_back(filter);
}

void KerMLListenerImplementation::enterElement(KerMLParser::ElementContext *) { }

void KerMLListenerImplementation::exitElement(KerMLParser::ElementContext *) { }

void KerMLListenerImplementation::enterNon_feature_element(KerMLParser::Non_feature_elementContext *) { }

void KerMLListenerImplementation::exitNon_feature_element(KerMLParser::Non_feature_elementContext *) { }

void KerMLListenerImplementation::enterFeature_element(KerMLParser::Feature_elementContext *) { }

void KerMLListenerImplementation::exitFeature_element(KerMLParser::Feature_elementContext *) { }

void KerMLListenerImplementation::enterAdditional_options(KerMLParser::Additional_optionsContext *) { }

void KerMLListenerImplementation::exitAdditional_options(KerMLParser::Additional_optionsContext *) { }

void KerMLListenerImplementation::enterType(KerMLParser::TypeContext *) {
    const auto type = std::make_shared<KerML::Entities::Type>();
    ParentStack.emplace(type);
}

void KerMLListenerImplementation::exitType(KerMLParser::TypeContext *ctx) {
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if(!type)
    {
        std::cout << "Error wrong type in Parentstack" << std::endl;
        return;
    }
    
    type->setAbstract(ctx->type_prefix()->KEYWORD_ABSTRACT()!=nullptr);

	ParentStack.pop();
    type->setOwner(ParentStack.top());
    ParentStack.top()->appendOwnedElement(type);
    Elements.push_back(type);
}

void KerMLListenerImplementation::enterType_prefix(KerMLParser::Type_prefixContext *) { }

void KerMLListenerImplementation::exitType_prefix(KerMLParser::Type_prefixContext *ctx) {
    if (!ctx || ParentStack.empty()) return;
    if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
        type->setAbstract(ctx->KEYWORD_ABSTRACT() != nullptr);
    }
}

void KerMLListenerImplementation::enterType_declaration(KerMLParser::Type_declarationContext *) { }

void KerMLListenerImplementation::exitType_declaration(KerMLParser::Type_declarationContext *ctx) {
    if (!ctx || ParentStack.empty()) return;
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type) return;
    applyIdentification(ctx->identification(), type);
    type->setIsSufficient(ctx->KEYWORD_ALL() != nullptr);
}

void KerMLListenerImplementation::enterSpecialization_part(KerMLParser::Specialization_partContext *) {
}

void KerMLListenerImplementation::exitSpecialization_part(KerMLParser::Specialization_partContext *ctx) {
    if (ParentStack.empty()) return;
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type) {
        return;
    }
    
    for (size_t i = 0; i < ctx->owned_specialization().size(); i++)
    {
        const auto generalName = ctx->owned_specialization()[i]->general_type()->getText();
        const auto generalType = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, generalName);
        const auto specialization = std::make_shared<KerML::Entities::Specialization>(generalType, type);
    	type->appendOwnedSpecialization(specialization);
        type->appendOwnedElement(specialization);
        Elements.push_back(specialization);
        Recorder.record(generalType, generalName, ReferenceKind::Type, ReferenceRole::Generalization, type, true, type,
            ctx->owned_specialization()[i]->general_type(), [specialization](const ElementPtr& element) {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) specialization->setGeneral(target);
            });
    }
}

void KerMLListenerImplementation::enterConjugation_part(KerMLParser::Conjugation_partContext *) {

}

void KerMLListenerImplementation::exitConjugation_part(KerMLParser::Conjugation_partContext *ctx) {
    if (ParentStack.empty()) return;
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type) {
        return;
    }
    
    if (ctx->owned_conjugation() && ctx->owned_conjugation()->qualified_name() != nullptr)
    {
        type->setIsConjugated(true);
        const auto origName = ctx->owned_conjugation()->qualified_name()->getText();
        const auto origType = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, origName);
        const auto conjugation = std::make_shared<KerML::Entities::Conjugation>(origType, type);
        type->setConjugation(conjugation);
        type->appendOwnedElement(conjugation);
        Elements.push_back(conjugation);
        Recorder.record(origType, origName, ReferenceKind::Type, ReferenceRole::Plain, type, true, nullptr,
            ctx->owned_conjugation()->qualified_name(), [conjugation](const ElementPtr& element) {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) conjugation->setOrginalType(target);
            });
    }
}

void KerMLListenerImplementation::enterType_relationship_part(KerMLParser::Type_relationship_partContext *) {

}

void KerMLListenerImplementation::exitType_relationship_part(KerMLParser::Type_relationship_partContext *) {

}

void KerMLListenerImplementation::enterDisjoining_part(KerMLParser::Disjoining_partContext *) {

}

void KerMLListenerImplementation::exitDisjoining_part(KerMLParser::Disjoining_partContext *ctx) {
    if (ParentStack.empty()) return;
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type) return;

    for (const auto& elem : ctx->owned_disjoining()) {
        if (elem->qualified_name()) {
            const auto disjoiningType = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, elem->qualified_name()->getText());
            const auto disjoining = std::make_shared<KerML::Entities::Disjoining>(type, disjoiningType);
            type->appendOwnedDisjoining(disjoining);
            type->appendOwnedElement(disjoining);
            Elements.push_back(disjoining);
            Recorder.record(disjoiningType, elem->qualified_name()->getText(), ReferenceKind::Type, ReferenceRole::Plain, type, true, nullptr,
                elem->qualified_name(), [disjoining](const ElementPtr& element) {
                    if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) disjoining->setDisjoiningType(target);
                });
        }
    }
}

void KerMLListenerImplementation::enterUnioning_part(KerMLParser::Unioning_partContext *) {

}

void KerMLListenerImplementation::exitUnioning_part(KerMLParser::Unioning_partContext *ctx) {
    if (ParentStack.empty()) return;
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type) return;

    for (const auto& elem : ctx->unioning()) {
        if (elem->qualified_name()) {
            const auto uType = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, elem->qualified_name()->getText());
            const auto unioning = std::make_shared<KerML::Entities::Unioning>(type, uType);
            type->appendOwnedUnioning(unioning);
            type->appendOwnedElement(unioning);
            Elements.push_back(unioning);
            Recorder.record(uType, elem->qualified_name()->getText(), ReferenceKind::Type, ReferenceRole::Plain, type, true, nullptr,
                elem->qualified_name(), [unioning](const ElementPtr& element) {
                    if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) unioning->setUnioningType(target);
                });
        }
    }
}

void KerMLListenerImplementation::enterIntersecting_part(KerMLParser::Intersecting_partContext *) {

}

void KerMLListenerImplementation::exitIntersecting_part(KerMLParser::Intersecting_partContext *ctx) {
    if (ParentStack.empty()) return;
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type) return;

    for (const auto& elem : ctx->intersecting()) {
        if (elem->qualified_name()) {
            const auto iType = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, elem->qualified_name()->getText());
            const auto intersecting = std::make_shared<KerML::Entities::Intersecting>(type, iType);
            type->appendOwnedIntersecting(intersecting);
            type->appendOwnedElement(intersecting);
            Elements.push_back(intersecting);
            Recorder.record(iType, elem->qualified_name()->getText(), ReferenceKind::Type, ReferenceRole::Plain, type, true, nullptr,
                elem->qualified_name(), [intersecting](const ElementPtr& element) {
                    if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) intersecting->setIntersectingType(target);
                });
        }
    }
}

void KerMLListenerImplementation::enterDifferencing_part(KerMLParser::Differencing_partContext *) {

}

void KerMLListenerImplementation::exitDifferencing_part(KerMLParser::Differencing_partContext *ctx) {
    if (ParentStack.empty()) return;
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type) return;

    for (const auto& elem : ctx->differencing()) {
        if (elem->qualified_name()) {
            const auto dType = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, elem->qualified_name()->getText());
            const auto differencing = std::make_shared<KerML::Entities::Differencing>(type, dType);
            type->appendOwnedDifferencing(differencing);
            type->appendOwnedElement(differencing);
            Elements.push_back(differencing);
            Recorder.record(dType, elem->qualified_name()->getText(), ReferenceKind::Type, ReferenceRole::Plain, type, true, nullptr,
                elem->qualified_name(), [differencing](const ElementPtr& element) {
                    if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) differencing->setDifferencingType(target);
                });
        }
    }
}

void KerMLListenerImplementation::enterType_body(KerMLParser::Type_bodyContext *) { }

void KerMLListenerImplementation::exitType_body(KerMLParser::Type_bodyContext *) { }

void KerMLListenerImplementation::enterType_body_elements(KerMLParser::Type_body_elementsContext *) { }

void KerMLListenerImplementation::exitType_body_elements(KerMLParser::Type_body_elementsContext *) { }

void KerMLListenerImplementation::enterType_body_element(KerMLParser::Type_body_elementContext *) { }

void KerMLListenerImplementation::exitType_body_element(KerMLParser::Type_body_elementContext *) { }

void KerMLListenerImplementation::enterSpecialization(KerMLParser::SpecializationContext *) { }

void KerMLListenerImplementation::exitSpecialization(KerMLParser::SpecializationContext *ctx) {
    if (!ctx || !ctx->general_type() || !ctx->specific_type()) return;
    const auto generalName = ctx->general_type()->getText();
    const auto specificName = ctx->specific_type()->getText();
    const auto generalType = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, generalName);
    const auto specializedType = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, specificName);
    const auto specialization = std::make_shared<KerML::Entities::Specialization>(generalType, specializedType);
    const auto specializationOwner = ParentStack.empty() ? nullptr : ParentStack.top();
    // Both types are named in the body of the namespace that owns the specialization.
    Recorder.record(generalType, generalName, ReferenceKind::Type, ReferenceRole::Generalization, specializationOwner, false, specializedType,
        ctx->general_type(), [specialization](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) specialization->setGeneral(target);
        });
    Recorder.record(specializedType, specificName, ReferenceKind::Type, ReferenceRole::Plain, specializationOwner, false, nullptr,
        ctx->specific_type(), [specialization](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) specialization->setSpecific(target);
        });

	if (ctx->KEYWORD_SPECIALIZATION() != nullptr)
        specialization->setDeclaredName(ctx->identification()->getText());

    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(specialization);
    }
    Elements.push_back(specialization);
}

void KerMLListenerImplementation::enterOwned_specialization(KerMLParser::Owned_specializationContext *) { }

void KerMLListenerImplementation::exitOwned_specialization(KerMLParser::Owned_specializationContext *) { }

void KerMLListenerImplementation::enterSpecific_type(KerMLParser::Specific_typeContext *) { }

void KerMLListenerImplementation::exitSpecific_type(KerMLParser::Specific_typeContext *) { }

void KerMLListenerImplementation::enterGeneral_type(KerMLParser::General_typeContext *) { }

void KerMLListenerImplementation::exitGeneral_type(KerMLParser::General_typeContext *) { }

void KerMLListenerImplementation::enterConjunction(KerMLParser::ConjunctionContext *) { }

void KerMLListenerImplementation::exitConjunction(KerMLParser::ConjunctionContext *ctx) {
    if (!ctx || ctx->qualified_name().size() < 2) return;
    const auto orig = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, ctx->qualified_name(0)->getText());
    const auto conj = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, ctx->qualified_name(1)->getText());
    const auto conjugation = std::make_shared<KerML::Entities::Conjugation>(orig, conj);
    const auto conjugationOwner = ParentStack.empty() ? nullptr : ParentStack.top();
    Recorder.record(orig, ctx->qualified_name(0)->getText(), ReferenceKind::Type, ReferenceRole::Plain, conjugationOwner, false, nullptr,
        ctx->qualified_name(0), [conjugation](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) conjugation->setOrginalType(target);
        });
    Recorder.record(conj, ctx->qualified_name(1)->getText(), ReferenceKind::Type, ReferenceRole::Plain, conjugationOwner, false, nullptr,
        ctx->qualified_name(1), [conjugation](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) conjugation->setConjungatedType(target);
        });
    if (ctx->identification()) {
        conjugation->setDeclaredName(ctx->identification()->getText());
    }
    if (!ParentStack.empty()) {
        conjugation->setOwningType(std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top()));
        ParentStack.top()->appendOwnedElement(conjugation);
    }
    Elements.push_back(conjugation);
}

void KerMLListenerImplementation::enterOwned_conjugation(KerMLParser::Owned_conjugationContext *) { }

void KerMLListenerImplementation::exitOwned_conjugation(KerMLParser::Owned_conjugationContext *) { }

void KerMLListenerImplementation::enterDisjoining(KerMLParser::DisjoiningContext *) { }

void KerMLListenerImplementation::exitDisjoining(KerMLParser::DisjoiningContext *ctx) {
    if (!ctx || ctx->qualified_name().size() < 2) return;
    const auto t1 = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, ctx->qualified_name(0)->getText());
    const auto t2 = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, ctx->qualified_name(1)->getText());
    const auto disjoining = std::make_shared<KerML::Entities::Disjoining>(t1, t2);
    const auto disjoiningOwner = ParentStack.empty() ? nullptr : ParentStack.top();
    Recorder.record(t1, ctx->qualified_name(0)->getText(), ReferenceKind::Type, ReferenceRole::Plain, disjoiningOwner, false, nullptr,
        ctx->qualified_name(0), [disjoining](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) disjoining->setTypeDisjoined(target);
        });
    Recorder.record(t2, ctx->qualified_name(1)->getText(), ReferenceKind::Type, ReferenceRole::Plain, disjoiningOwner, false, nullptr,
        ctx->qualified_name(1), [disjoining](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) disjoining->setDisjoiningType(target);
        });
    if (ctx->identification()) {
        disjoining->setDeclaredName(ctx->identification()->getText());
    }
    if (!ParentStack.empty()) {
        disjoining->setOwningType(std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top()));
        ParentStack.top()->appendOwnedElement(disjoining);
    }
    Elements.push_back(disjoining);
}

void KerMLListenerImplementation::enterOwned_disjoining(KerMLParser::Owned_disjoiningContext *) {

}

void KerMLListenerImplementation::exitOwned_disjoining(KerMLParser::Owned_disjoiningContext *) {

}

void KerMLListenerImplementation::enterUnioning(KerMLParser::UnioningContext *) {

}

void KerMLListenerImplementation::exitUnioning(KerMLParser::UnioningContext *) {

}

void KerMLListenerImplementation::enterIntersecting(KerMLParser::IntersectingContext *) {

}

void KerMLListenerImplementation::exitIntersecting(KerMLParser::IntersectingContext *) {

}

void KerMLListenerImplementation::enterDifferencing(KerMLParser::DifferencingContext *) {

}

void KerMLListenerImplementation::exitDifferencing(KerMLParser::DifferencingContext *) {

}

void KerMLListenerImplementation::enterFeature_member(KerMLParser::Feature_memberContext *) {

}

void KerMLListenerImplementation::exitFeature_member(KerMLParser::Feature_memberContext *) {

}

void KerMLListenerImplementation::enterType_feature_member(KerMLParser::Type_feature_memberContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OwningMembership>());
}

void KerMLListenerImplementation::exitType_feature_member(KerMLParser::Type_feature_memberContext *ctx) {
    // `member feature x;` is a member that is not a feature of the type: it is owned through a plain OwningMembership.
    finishMembership(ctx ? ctx->member_prefix() : nullptr, true);
}

void KerMLListenerImplementation::enterOwned_feature_member(KerMLParser::Owned_feature_memberContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OwningMembership>());
}

void KerMLListenerImplementation::exitOwned_feature_member(KerMLParser::Owned_feature_memberContext *ctx) {
    finishMembership(ctx ? ctx->member_prefix() : nullptr);
}

void KerMLListenerImplementation::enterClassifier(KerMLParser::ClassifierContext *) {
    const auto classifier = std::make_shared<KerML::Entities::Classifier>();
    ParentStack.emplace(classifier);
}

void KerMLListenerImplementation::exitClassifier(KerMLParser::ClassifierContext *ctx) {
    if (ParentStack.empty()) return;
    const auto classifier = std::dynamic_pointer_cast<KerML::Entities::Classifier>(ParentStack.top());
    if (!classifier) return;
    ParentStack.pop();
    
    if (ctx->type_prefix() && ctx->type_prefix()->KEYWORD_ABSTRACT() != nullptr) {
        classifier->setAbstract(true);
    }

    Elements.push_back(classifier);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(classifier);
    }
}

void KerMLListenerImplementation::enterClassifier_declaration(KerMLParser::Classifier_declarationContext *) { }

void KerMLListenerImplementation::exitClassifier_declaration(KerMLParser::Classifier_declarationContext *ctx) {
    if (ParentStack.empty()) return;
    const auto classifier = std::dynamic_pointer_cast<KerML::Entities::Classifier>(ParentStack.top());
    if (!classifier) {
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            if (ctx->identification() != nullptr) {
                applyIdentification(ctx->identification(), type);
            }
            if (ctx->KEYWORD_ALL() != nullptr) {
                type->setIsSufficient(true);
            }
        }
        return;
    }
    if (ctx->identification() != nullptr) {
        applyIdentification(ctx->identification(), classifier);
    }
    if (ctx->KEYWORD_ALL() != nullptr) {
        classifier->setIsSufficient(true);
    }
}

void KerMLListenerImplementation::enterSuperclassing_part(KerMLParser::Superclassing_partContext *) {
    
}

void KerMLListenerImplementation::exitSuperclassing_part(KerMLParser::Superclassing_partContext *ctx) {
    if (ParentStack.empty()) return;
    const auto classifier = std::dynamic_pointer_cast<KerML::Entities::Classifier>(ParentStack.top());
    if (classifier) {
        for (const auto& elem : ctx->owned_subclassification()) {
            std::string superName = elem->qualified_name() ? elem->qualified_name()->getText() : elem->getText();
            const auto superClassifier = newPlaceholder<KerML::Entities::Classifier>(ReferenceKind::Classifier, superName);
            const auto subclassification = std::make_shared<KerML::Entities::Subclassification>(superClassifier, classifier);
            classifier->appendOwnedSubclassification(subclassification);
            classifier->appendOwnedSpecialization(subclassification);
            classifier->appendOwnedElement(subclassification);
            Elements.push_back(subclassification);
            Recorder.record(superClassifier, superName, ReferenceKind::Classifier, ReferenceRole::Generalization, classifier, true, classifier,
                elem, [subclassification](const ElementPtr& element) {
                    if (auto target = std::dynamic_pointer_cast<KerML::Entities::Classifier>(element))
                        SysMLv2::Files::Retarget::subclassification(*subclassification, target);
                });
        }
        return;
    }
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (type) {
        for (const auto& elem : ctx->owned_subclassification()) {
            std::string superName = elem->qualified_name() ? elem->qualified_name()->getText() : elem->getText();
            const auto generalType = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, superName);
            const auto specialization = std::make_shared<KerML::Entities::Specialization>(generalType, type);
            type->appendOwnedSpecialization(specialization);
            type->appendOwnedElement(specialization);
            Elements.push_back(specialization);
            Recorder.record(generalType, superName, ReferenceKind::Type, ReferenceRole::Generalization, type, true, type, elem,
                [specialization](const ElementPtr& element) {
                    if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) specialization->setGeneral(target);
                });
        }
    }
}

void KerMLListenerImplementation::enterSubclassification(KerMLParser::SubclassificationContext *) { }

void KerMLListenerImplementation::exitSubclassification(KerMLParser::SubclassificationContext *ctx) {
    if (!ctx || ctx->qualified_name().size() < 2) return;

    const std::string subName = ctx->qualified_name(0)->getText();
    const std::string superName = ctx->qualified_name(1)->getText();

    const auto subClassifier = newPlaceholder<KerML::Entities::Classifier>(ReferenceKind::Classifier, subName);
    const auto superClassifier = newPlaceholder<KerML::Entities::Classifier>(ReferenceKind::Classifier, superName);

    const auto subclassification = std::make_shared<KerML::Entities::Subclassification>(superClassifier, subClassifier);
    const auto subclassificationOwner = ParentStack.empty() ? nullptr : ParentStack.top();
    // Both classifiers are named in the body of the namespace that owns the subclassification. The subclassification is attached to
    // the sub classifier once that is known.
    Recorder.record(subClassifier, subName, ReferenceKind::Classifier, ReferenceRole::Plain, subclassificationOwner, false, nullptr,
        ctx->qualified_name(0), [subclassification](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Classifier>(element)) {
                subclassification->setSubclassifier(target);
                subclassification->setSpecific(target);
                target->appendOwnedSubclassification(subclassification);
                target->appendOwnedSpecialization(subclassification);
                target->appendOwnedElement(subclassification);
            }
        });
    Recorder.record(superClassifier, superName, ReferenceKind::Classifier, ReferenceRole::Generalization, subclassificationOwner, false,
        subClassifier, ctx->qualified_name(1), [subclassification](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Classifier>(element))
                SysMLv2::Files::Retarget::subclassification(*subclassification, target);
        });

    if (ctx->identification() != nullptr) {
        subclassification->setDeclaredName(ctx->identification()->getText());
    }

    if (!ParentStack.empty()) {
        subclassification->setOwner(ParentStack.top());
        if (auto parentClassifier = std::dynamic_pointer_cast<KerML::Entities::Classifier>(ParentStack.top())) {
            subclassification->setOwningClassifier(parentClassifier);
            subclassification->setOwningType(parentClassifier);
        } else if (auto parentType = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            subclassification->setOwningType(parentType);
        }
        ParentStack.top()->appendOwnedElement(subclassification);
    }

    Elements.push_back(subclassification);
}

void KerMLListenerImplementation::enterOwned_subclassification(KerMLParser::Owned_subclassificationContext *) { }

void KerMLListenerImplementation::exitOwned_subclassification(KerMLParser::Owned_subclassificationContext *) { }

void KerMLListenerImplementation::enterFeature(KerMLParser::FeatureContext *) {
    const auto feature = std::make_shared<KerML::Entities::Feature>();
    ParentStack.emplace(feature);
}

void KerMLListenerImplementation::exitFeature(KerMLParser::FeatureContext *) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) {
        return;
    }
    ParentStack.pop();
    Elements.push_back(feature);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(feature);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(feature);
            const auto fm = std::make_shared<KerML::Entities::FeatureMembership>();
            fm->setOwnedMemberFeature(feature);
            fm->setMemberElement(feature);
            fm->setOwningType(type);
            fm->setMembershipOwningNamespace(type);
            type->appendOwnedFeatureMembership(fm);
            type->appendFeatureMemberships(fm);
            type->appendOwnedElement(fm);
            Elements.push_back(fm);
        }
    }
}

void KerMLListenerImplementation::enterAnonymous_feature(KerMLParser::Anonymous_featureContext *) {
    // anonymous_feature is an ALTERNATIVE INSIDE the `feature` rule (feature: ... | anonymous_feature),
    // not a separate outer parse-tree node: ANTLR still invokes enter/exitFeature for the very same
    // `feature` context, so the Feature has already been pushed by enterFeature by the time this runs.
    // This must therefore be a true no-op - building another Feature here pushed a second, empty
    // Feature per anonymous declaration (caught in review; see TestKerMLParser).
}

void KerMLListenerImplementation::exitAnonymous_feature(KerMLParser::Anonymous_featureContext *) {
    // See enterAnonymous_feature: no-op. exitFeature (invoked for the same `feature` node) already
    // finishes, pops and attaches the Feature that enterFeature pushed.
}

void KerMLListenerImplementation::enterFeature_prefix(KerMLParser::Feature_prefixContext *) { }

// The modifiers of a FeaturePrefix are applied by exitEnd_feature_prefix / exitBasic_feature_prefix, because the
// prefix of an owned cross feature (see enterOwned_cross_feature) is a BasicFeaturePrefix of its own.
void KerMLListenerImplementation::exitFeature_prefix(KerMLParser::Feature_prefixContext *) { }

void KerMLListenerImplementation::enterEnd_feature_prefix(KerMLParser::End_feature_prefixContext *) { }

void KerMLListenerImplementation::exitEnd_feature_prefix(KerMLParser::End_feature_prefixContext *) {
    if (ParentStack.empty()) return;
    if (const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
        feature->setIsEnd(true);
    }
}

void KerMLListenerImplementation::enterBasic_feature_prefix(KerMLParser::Basic_feature_prefixContext *) { }

void KerMLListenerImplementation::exitBasic_feature_prefix(KerMLParser::Basic_feature_prefixContext *ctx) {
    if (!ctx || ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) {
        return;
    }
    feature->setAbstract(ctx->KEYWORD_ABSTRACT() != nullptr);
    feature->setIsVariable(ctx->KEYWORD_VAR() != nullptr);
    feature->setIsComposite(ctx->KEYWORD_COMPOSITE() != nullptr);
    feature->setIsPortion(ctx->KEYWORD_PORTION() != nullptr);
    feature->setIsDerived(ctx->KEYWORD_DERIVED() != nullptr);
}

void KerMLListenerImplementation::enterOwned_cross_feature_member(KerMLParser::Owned_cross_feature_memberContext *) { }

void KerMLListenerImplementation::exitOwned_cross_feature_member(KerMLParser::Owned_cross_feature_memberContext *) { }

// OwnedCrossFeature (KerML 8.2.4.3.1): the cross feature declared between 'end' and the kind keyword of an end
// feature. It is a Feature of its own, owned by the end feature (not one of its featured members).
void KerMLListenerImplementation::enterOwned_cross_feature(KerMLParser::Owned_cross_featureContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::Feature>());
}

void KerMLListenerImplementation::exitOwned_cross_feature(KerMLParser::Owned_cross_featureContext *) {
    if (ParentStack.empty()) return;
    const auto cross = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!cross) return;
    ParentStack.pop();
    Elements.push_back(cross);
    if (ParentStack.empty()) return;
    cross->setOwner(ParentStack.top());
    // The cross feature is owned through an OwnedCrossFeatureMember (an OwningMembership), not as a feature of the end feature.
    OwnershipKinds[cross.get()] = SysMLv2::Files::MembershipKind::Owning;
    ParentStack.top()->appendOwnedElement(cross);
    if (const auto endFeature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
        endFeature->setCrossFeature(cross);
    }
}

void KerMLListenerImplementation::enterOwned_cross_multiplicity_member(KerMLParser::Owned_cross_multiplicity_memberContext *) { }

void KerMLListenerImplementation::exitOwned_cross_multiplicity_member(KerMLParser::Owned_cross_multiplicity_memberContext *) { }

void KerMLListenerImplementation::enterOwned_cross_multiplicity(KerMLParser::Owned_cross_multiplicityContext *) { }

void KerMLListenerImplementation::exitOwned_cross_multiplicity(KerMLParser::Owned_cross_multiplicityContext *) { }

void KerMLListenerImplementation::enterCrosses(KerMLParser::CrossesContext *) { }

void KerMLListenerImplementation::exitCrosses(KerMLParser::CrossesContext *) { }

void KerMLListenerImplementation::enterOwned_cross_subsetting(KerMLParser::Owned_cross_subsettingContext *) { }

// Crosses = CROSSES OwnedCrossSubsetting: the feature being declared cross-subsets the given (possibly chained) feature.
void KerMLListenerImplementation::exitOwned_cross_subsetting(KerMLParser::Owned_cross_subsettingContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature || !ctx || !ctx->general_type()) return;

    const auto crossedName = ctx->general_type()->getText();
    const auto crossed = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, crossedName);
    const auto crossSubsetting = std::make_shared<KerML::Entities::CrossSubsetting>(crossed, feature);
    feature->setOwnedCrossSubsetting(crossSubsetting);
    feature->appendOwnedElement(crossSubsetting);
    Elements.push_back(crossSubsetting);
    Recorder.record(crossed, crossedName, ReferenceKind::Feature, ReferenceRole::Generalization, feature, true, feature, ctx->general_type(),
        [crossSubsetting](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element))
                SysMLv2::Files::Retarget::crossSubsetting(*crossSubsetting, target);
        });
}

void KerMLListenerImplementation::enterFeature_direction(KerMLParser::Feature_directionContext *) { }

void KerMLListenerImplementation::exitFeature_direction(KerMLParser::Feature_directionContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) {
        return;
    }
    if (ctx->KEYWORD_IN() != nullptr)
        feature->setDirection(KerML::Entities::FeatureDirectionKind::IN);
    if (ctx->KEYWORD_OUT() != nullptr)
        feature->setDirection(KerML::Entities::FeatureDirectionKind::OUT);
    if (ctx->KEYWORD_INOUT() != nullptr)
        feature->setDirection(KerML::Entities::FeatureDirectionKind::IN_OUT);
}

void KerMLListenerImplementation::enterFeature_declaration(KerMLParser::Feature_declarationContext *) { }

void KerMLListenerImplementation::exitFeature_declaration(KerMLParser::Feature_declarationContext *ctx) {
    // KEYWORD_ALL here is FeatureDeclaration's "isSufficient" marker (spec: "( isSufficient ?= 'all' )?
    // FeatureIdentification ..."); it has nothing to do with uniqueness. Uniqueness is set from
    // 'nonunique' in exitMultiplicity_part (defaulting to true, i.e. unique, when absent). Setting
    // isUnique from KEYWORD_ALL here was a bug: it forced isUnique() to false on every feature that
    // does not use the (rare) 'all' marker, overriding whatever exitMultiplicity_part had set.
    (void)ctx;
}

void KerMLListenerImplementation::enterFeature_identification(KerMLParser::Feature_identificationContext *) { }

void KerMLListenerImplementation::exitFeature_identification(KerMLParser::Feature_identificationContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) {
        return;
    }

    if (ctx->SYMBOL_SMALLER() != nullptr && ctx->SYMBOL_GREATER() != nullptr && ctx->NAME().size() >= 2) {
        feature->setDeclaredShortName(ctx->NAME().front()->getText());
        feature->setDeclaredName(ctx->NAME().back()->getText());
    } else if (!ctx->NAME().empty()) {
        feature->setDeclaredName(ctx->NAME().front()->getText());
    }
}

void KerMLListenerImplementation::enterFeature_relationship_part(KerMLParser::Feature_relationship_partContext *) { }

void KerMLListenerImplementation::exitFeature_relationship_part(KerMLParser::Feature_relationship_partContext *) { }

void KerMLListenerImplementation::enterChaining_part(KerMLParser::Chaining_partContext *) { }

void KerMLListenerImplementation::exitChaining_part(KerMLParser::Chaining_partContext *) { }

void KerMLListenerImplementation::enterInverting_part(KerMLParser::Inverting_partContext *) { }

void KerMLListenerImplementation::exitInverting_part(KerMLParser::Inverting_partContext *) { }

void KerMLListenerImplementation::enterType_featuring_part(KerMLParser::Type_featuring_partContext *) { }

void KerMLListenerImplementation::exitType_featuring_part(KerMLParser::Type_featuring_partContext *) { }

void KerMLListenerImplementation::enterFeature_specialization_part(KerMLParser::Feature_specialization_partContext *) {

}

void KerMLListenerImplementation::exitFeature_specialization_part(KerMLParser::Feature_specialization_partContext *) {

}

void KerMLListenerImplementation::enterMultiplicity_part(KerMLParser::Multiplicity_partContext *) {

}

void KerMLListenerImplementation::exitMultiplicity_part(KerMLParser::Multiplicity_partContext *ctx) {
    if (!ctx || ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) return;
    if (ctx->KEYWORD_ORDERED() != nullptr) feature->setIsOrdered(true);
    if (ctx->KEYWORD_NONUNIQUE() != nullptr) feature->setIsUnique(false);
}

void KerMLListenerImplementation::enterMultiplicity_modifier(KerMLParser::Multiplicity_modifierContext *) { }

void KerMLListenerImplementation::exitMultiplicity_modifier(KerMLParser::Multiplicity_modifierContext *) { }

void KerMLListenerImplementation::enterTyped_by_operator(KerMLParser::Typed_by_operatorContext *) { }

void KerMLListenerImplementation::exitTyped_by_operator(KerMLParser::Typed_by_operatorContext *) { }

void KerMLListenerImplementation::enterSpecializes_operator(KerMLParser::Specializes_operatorContext *) { }

void KerMLListenerImplementation::exitSpecializes_operator(KerMLParser::Specializes_operatorContext *) { }

void KerMLListenerImplementation::enterSubsets_operator(KerMLParser::Subsets_operatorContext *) { }

void KerMLListenerImplementation::exitSubsets_operator(KerMLParser::Subsets_operatorContext *) { }

void KerMLListenerImplementation::enterReferences_operator(KerMLParser::References_operatorContext *) { }

void KerMLListenerImplementation::exitReferences_operator(KerMLParser::References_operatorContext *) { }

void KerMLListenerImplementation::enterRedefines_operator(KerMLParser::Redefines_operatorContext *) { }

void KerMLListenerImplementation::exitRedefines_operator(KerMLParser::Redefines_operatorContext *) { }

void KerMLListenerImplementation::enterConjugates_operator(KerMLParser::Conjugates_operatorContext *) { }

void KerMLListenerImplementation::exitConjugates_operator(KerMLParser::Conjugates_operatorContext *) { }

void KerMLListenerImplementation::enterCrosses_operator(KerMLParser::Crosses_operatorContext *) { }

void KerMLListenerImplementation::exitCrosses_operator(KerMLParser::Crosses_operatorContext *) { }

void KerMLListenerImplementation::enterFeature_specialization(KerMLParser::Feature_specializationContext *) {

}

void KerMLListenerImplementation::exitFeature_specialization(KerMLParser::Feature_specializationContext *) {

}

void KerMLListenerImplementation::enterTypings(KerMLParser::TypingsContext *) {

}

void KerMLListenerImplementation::exitTypings(KerMLParser::TypingsContext *) {

}

void KerMLListenerImplementation::enterTyped_by(KerMLParser::Typed_byContext *) {

}

void KerMLListenerImplementation::exitTyped_by(KerMLParser::Typed_byContext *) {

}

void KerMLListenerImplementation::enterSubsettings(KerMLParser::SubsettingsContext *) {

}

void KerMLListenerImplementation::exitSubsettings(KerMLParser::SubsettingsContext *) {

}

void KerMLListenerImplementation::enterSubsets(KerMLParser::SubsetsContext *) {

}

void KerMLListenerImplementation::exitSubsets(KerMLParser::SubsetsContext *) {

}

void KerMLListenerImplementation::enterReferences(KerMLParser::ReferencesContext *) {

}

void KerMLListenerImplementation::exitReferences(KerMLParser::ReferencesContext *) {

}

void KerMLListenerImplementation::enterRedefinitions(KerMLParser::RedefinitionsContext *) {

}

void KerMLListenerImplementation::exitRedefinitions(KerMLParser::RedefinitionsContext *) {

}

void KerMLListenerImplementation::enterRedefines(KerMLParser::RedefinesContext *) {

}

void KerMLListenerImplementation::exitRedefines(KerMLParser::RedefinesContext *) {

}

void KerMLListenerImplementation::enterFeature_typing(KerMLParser::Feature_typingContext *) {
    const auto feature_typing = std::make_shared<KerML::Entities::FeatureTyping>();
    ParentStack.emplace(feature_typing);
}

void KerMLListenerImplementation::exitFeature_typing(KerMLParser::Feature_typingContext *ctx) {
    const auto feature_typing = std::dynamic_pointer_cast<KerML::Entities::FeatureTyping>(ParentStack.top());
	if (!feature_typing)
        throw std::runtime_error("Wrong type on parent stack");
    ParentStack.pop();

    feature_typing->setDeclaredName(ctx->qualified_name()->getText());
    const auto typeName = ctx->general_type()->qualified_name()->getText();
    const auto type = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, typeName);
    feature_typing->setType(type);
    Recorder.record(type, typeName, ReferenceKind::Type, ReferenceRole::Plain, ParentStack.empty() ? nullptr : ParentStack.top(), false, nullptr,
        ctx->general_type(), [feature_typing](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) feature_typing->setType(target);
        });
}

void KerMLListenerImplementation::enterOwned_feature_typing(KerMLParser::Owned_feature_typingContext *) { }

void KerMLListenerImplementation::exitOwned_feature_typing(KerMLParser::Owned_feature_typingContext *ctx) {
    if (ParentStack.empty()) return;
    if (const auto instExpr = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
        if (ctx && ctx->general_type()) {
            std::string typeName = ctx->general_type()->getText();
            const auto type = typeReference(typeName, instExpr, false, ctx->general_type(),
                [instExpr](const std::shared_ptr<KerML::Entities::Type>& target) { instExpr->setInstantiatedType(target); });
            instExpr->setInstantiatedType(type);
        }
        return;
    }
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature || !ctx || !ctx->general_type()) return;

    std::string typeName = ctx->general_type()->getText();
    const auto type = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, typeName);
    const auto featureTyping = std::make_shared<KerML::Entities::FeatureTyping>(type, feature);
    feature->appendOwnedTyping(featureTyping);
    feature->appendType(type);
    feature->appendOwnedElement(featureTyping);
    Elements.push_back(featureTyping);
    Recorder.record(type, typeName, ReferenceKind::Type, ReferenceRole::Generalization, feature, true, feature, ctx->general_type(),
        [feature, featureTyping, type](const ElementPtr& element) {
            auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element);
            if (!target) return;
            SysMLv2::Files::Retarget::featureTyping(*featureTyping, target);
            auto types = feature->type();
            SysMLv2::Files::replaceInVector(types, type, target);
            feature->setType(types);
        });
}

void KerMLListenerImplementation::enterSubsetting(KerMLParser::SubsettingContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::Subsetting>(
        std::make_shared<KerML::Entities::Feature>(), std::make_shared<KerML::Entities::Feature>()));
}

void KerMLListenerImplementation::exitSubsetting(KerMLParser::SubsettingContext *ctx) {
    if (ParentStack.empty()) return;
    const auto relationship = std::dynamic_pointer_cast<KerML::Entities::Subsetting>(ParentStack.top());
    if (!relationship) return;
    ParentStack.pop();
    if (!ctx || !ctx->specific_type() || !ctx->general_type()) return;
    const auto specificName = ctx->specific_type()->getText();
    const auto generalName = ctx->general_type()->getText();
    const auto specific = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, specificName);
    const auto general = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, generalName);
    const auto subsettingOwner = ParentStack.empty() ? nullptr : ParentStack.top();
    Recorder.record(specific, specificName, ReferenceKind::Feature, ReferenceRole::Plain, subsettingOwner, false, nullptr, ctx->specific_type(),
        [relationship](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) {
                relationship->setSubsettingFeature(target);
                relationship->setSpecific(target);
            }
        });
    Recorder.record(general, generalName, ReferenceKind::Feature, ReferenceRole::Generalization, subsettingOwner, false, specific, ctx->general_type(),
        [relationship](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) SysMLv2::Files::Retarget::subsetting(*relationship, target);
        });
    relationship->setSubsettedFeature(general);
    relationship->setSubsettingFeature(specific);
    relationship->setGeneral(general);
    relationship->setSpecific(specific);
    applyIdentification(ctx->identification(), relationship);
    if (!ParentStack.empty()) {
        relationship->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(relationship);
    }
    Elements.push_back(relationship);
}

void KerMLListenerImplementation::enterOwned_subsetting(KerMLParser::Owned_subsettingContext *) { }

void KerMLListenerImplementation::exitOwned_subsetting(KerMLParser::Owned_subsettingContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature || !ctx || !ctx->general_type()) return;

    std::string subsettedName = ctx->general_type()->getText();
    const auto subsetted = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, subsettedName);
    const auto subsetting = std::make_shared<KerML::Entities::Subsetting>(subsetted, feature);
    feature->appendOwnedSubsetting(subsetting);
    feature->appendOwnedElement(subsetting);
    Elements.push_back(subsetting);
    Recorder.record(subsetted, subsettedName, ReferenceKind::Feature, ReferenceRole::Generalization, feature, true, feature, ctx->general_type(),
        [subsetting](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) SysMLv2::Files::Retarget::subsetting(*subsetting, target);
        });
}

void KerMLListenerImplementation::enterOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *) { }

void KerMLListenerImplementation::exitOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature || !ctx || !ctx->general_type()) return;

    std::string refName = ctx->general_type()->getText();
    const auto referenced = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, refName);
    const auto refSubsetting = std::make_shared<KerML::Entities::ReferenceSubsetting>(referenced, feature);
    feature->setOwnedReferenceSubsetting(refSubsetting);
    feature->appendOwnedElement(refSubsetting);
    Elements.push_back(refSubsetting);
    Recorder.record(referenced, refName, ReferenceKind::Feature, ReferenceRole::Generalization, feature, true, feature, ctx->general_type(),
        [refSubsetting](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element))
                SysMLv2::Files::Retarget::referenceSubsetting(*refSubsetting, target);
        });
}

void KerMLListenerImplementation::enterRedefinition(KerMLParser::RedefinitionContext *ctx) {
    const auto feature = std::make_shared<KerML::Entities::Feature>();
    if (ctx && ctx->qualified_name()) {
        feature->setDeclaredName(ctx->qualified_name()->getText());
    }
    ParentStack.push(feature);
}

void KerMLListenerImplementation::exitRedefinition(KerMLParser::RedefinitionContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) return;
    ParentStack.pop();

    if (ctx && ctx->qualified_name()) {
        std::string redefName = ctx->qualified_name()->getText();
        const auto redefined = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, redefName);
        const auto redefinition = std::make_shared<KerML::Entities::Redefinition>(redefined, feature);
        feature->appendOwnedRedefinition(redefinition);
        feature->appendOwnedElement(redefinition);
        Elements.push_back(redefinition);
        Recorder.record(redefined, redefName, ReferenceKind::Feature, ReferenceRole::Redefinition, feature, true, feature, ctx->qualified_name(),
            [redefinition](const ElementPtr& element) {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element))
                    SysMLv2::Files::Retarget::redefinition(*redefinition, target);
            });
    }

    Elements.push_back(feature);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(feature);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(feature);
        }
    }
}

void KerMLListenerImplementation::enterOwned_redefinition(KerMLParser::Owned_redefinitionContext *) { }

void KerMLListenerImplementation::exitOwned_redefinition(KerMLParser::Owned_redefinitionContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature || !ctx || !ctx->general_type()) return;

    std::string redefName = ctx->general_type()->getText();
    const auto redefined = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, redefName);
    const auto redefinition = std::make_shared<KerML::Entities::Redefinition>(redefined, feature);
    feature->appendOwnedRedefinition(redefinition);
    feature->appendOwnedElement(redefinition);
    Elements.push_back(redefinition);
    Recorder.record(redefined, redefName, ReferenceKind::Feature, ReferenceRole::Redefinition, feature, true, feature, ctx->general_type(),
        [redefinition](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element))
                SysMLv2::Files::Retarget::redefinition(*redefinition, target);
        });
}

void KerMLListenerImplementation::enterOwned_feature_chain(KerMLParser::Owned_feature_chainContext *) {

}

void KerMLListenerImplementation::exitOwned_feature_chain(KerMLParser::Owned_feature_chainContext *) {

}

void KerMLListenerImplementation::enterFeature_chain(KerMLParser::Feature_chainContext *ctx) {
    // A chain used as a reference has its own Feature; a chains clause populates
    // the feature being declared directly.
    if (ctx && dynamic_cast<KerMLParser::Chaining_partContext*>(ctx->parent)) return;
    ParentStack.push(std::make_shared<KerML::Entities::Feature>());
}

void KerMLListenerImplementation::exitFeature_chain(KerMLParser::Feature_chainContext *ctx) {
    if (!ctx || dynamic_cast<KerMLParser::Chaining_partContext*>(ctx->parent) || ParentStack.empty()) return;
    const auto chain = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!chain) return;
    chain->setDeclaredName(ctx->getText());
    ParentStack.pop();
    Elements.push_back(chain);
    if (!ParentStack.empty()) {
        chain->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(chain);
    }
}

void KerMLListenerImplementation::enterOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *) { }

void KerMLListenerImplementation::exitOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *ctx) {
    if (!ctx || !ctx->qualified_name() || ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) return;
    const auto chainingName = ctx->qualified_name()->getText();
    const auto chaining = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, chainingName);
    const auto relationship = std::make_shared<KerML::Entities::FeatureChaining>(chaining, feature);
    feature->appendChainingFeature(chaining);
    feature->appendOwnedFeatureChaining(relationship);
    feature->appendOwnedElement(relationship);
    Elements.push_back(relationship);
    // The first feature of a chain is looked up like any name; a following one among the features of the previous ones, which
    // is expressed as the chain written so far (`a.b.c`).
    std::string chainText;
    if (auto* chainCtx = dynamic_cast<antlr4::ParserRuleContext*>(ctx->parent)) {
        for (auto* child : chainCtx->children) {
            if (auto* link = dynamic_cast<KerMLParser::Owned_feature_chainingContext*>(child)) {
                if (link->qualified_name() == nullptr) continue;
                if (!chainText.empty()) chainText += ".";
                chainText += link->qualified_name()->getText();
                if (link == ctx) break;
            }
        }
    }
    if (chainText.empty()) chainText = chainingName;
    Recorder.record(chaining, chainText, ReferenceKind::Feature, ReferenceRole::Plain, feature, true,
        nullptr, ctx->qualified_name(), [feature, relationship, chaining](const ElementPtr& element) {
            auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element);
            if (!target) return;
            relationship->setChainingFeature(target);
            auto chain = feature->chainingFeature();
            SysMLv2::Files::replaceInVector(chain, chaining, target);
            feature->setChainingFeature(chain);
        });
}

void KerMLListenerImplementation::enterFeature_inverting(KerMLParser::Feature_invertingContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::FeatureInverting>(
        std::make_shared<KerML::Entities::Feature>(), std::make_shared<KerML::Entities::Feature>()));
}

void KerMLListenerImplementation::exitFeature_inverting(KerMLParser::Feature_invertingContext *ctx) {
    if (ParentStack.empty()) return;
    const auto relationship = std::dynamic_pointer_cast<KerML::Entities::FeatureInverting>(ParentStack.top());
    if (!relationship) return;
    ParentStack.pop();
    if (!ctx) return;
    std::vector<std::string> names;
    for (auto child : ctx->children) {
        if (dynamic_cast<KerMLParser::Qualified_nameContext*>(child) ||
            dynamic_cast<KerMLParser::Owned_feature_chainContext*>(child)) names.push_back(child->getText());
    }
    if (names.size() != 2) return;
    const auto inverting = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, names[0]);
    const auto inverted = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, names[1]);
    relationship->setInvertingFeature(inverting);
    relationship->setFeatureInverted(inverted);
    const auto invertingOwner = ParentStack.empty() ? nullptr : ParentStack.top();
    Recorder.record(inverting, names[0], ReferenceKind::Feature, ReferenceRole::Plain, invertingOwner, false, nullptr, ctx,
        [relationship](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) relationship->setInvertingFeature(target);
        });
    Recorder.record(inverted, names[1], ReferenceKind::Feature, ReferenceRole::Plain, invertingOwner, false, nullptr, ctx,
        [relationship](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) relationship->setFeatureInverted(target);
        });
    applyIdentification(ctx->identification(), relationship);
    if (!ParentStack.empty()) {
        relationship->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(relationship);
    }
    Elements.push_back(relationship);
}

void KerMLListenerImplementation::enterOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *) {

}

void KerMLListenerImplementation::exitOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) {
        std::cout << "Wrong Type in parent stack." << std::endl;
        return;
    }

    if (ctx && ctx->qualified_name()) {
        // The referenced feature may be a forward reference that is only found when the workspace resolves the names; a placeholder
        // stands in for it until then (the FeatureInverting constructor rejects a null feature).
        const auto invertedName = ctx->qualified_name()->getText();
        const auto invertedFeature = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, invertedName);
        const auto featureInverting = std::make_shared<KerML::Entities::FeatureInverting>(invertedFeature, feature);
        feature->appendOwnedElement(featureInverting);
        feature->appendOwnedFeatureInverting(featureInverting);
        Elements.push_back(featureInverting);
        Recorder.record(invertedFeature, invertedName, ReferenceKind::Feature, ReferenceRole::Plain, feature, true, nullptr, ctx->qualified_name(),
            [featureInverting](const ElementPtr& element) {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) featureInverting->setFeatureInverted(target);
            });
    }
}

void KerMLListenerImplementation::enterType_featuring(KerMLParser::Type_featuringContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::TypeFeaturing>(
        std::make_shared<KerML::Entities::Feature>(), std::make_shared<KerML::Entities::Feature>()));
}

void KerMLListenerImplementation::exitType_featuring(KerMLParser::Type_featuringContext *ctx) {
    if (ParentStack.empty()) return;
    const auto relationship = std::dynamic_pointer_cast<KerML::Entities::TypeFeaturing>(ParentStack.top());
    if (!relationship) return;
    ParentStack.pop();
    if (!ctx || ctx->qualified_name().size() != 2) return;
    const auto feature = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, ctx->qualified_name(0)->getText());
    const auto type = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, ctx->qualified_name(1)->getText());
    relationship->setFeatureOfType(feature);
    relationship->setFeaturingType(type);
    feature->appendTypeFeaturing(relationship);
    feature->appendFeaturingType(type);
    const auto featuringOwner = ParentStack.empty() ? nullptr : ParentStack.top();
    Recorder.record(feature, ctx->qualified_name(0)->getText(), ReferenceKind::Feature, ReferenceRole::Plain, featuringOwner, false, nullptr,
        ctx->qualified_name(0), [relationship](const ElementPtr& element) {
            auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element);
            if (!target) return;
            relationship->setFeatureOfType(target);
            target->appendTypeFeaturing(relationship);
            target->appendFeaturingType(relationship->featuringType());
        });
    Recorder.record(type, ctx->qualified_name(1)->getText(), ReferenceKind::Type, ReferenceRole::Plain, featuringOwner, false, nullptr,
        ctx->qualified_name(1), [relationship, type](const ElementPtr& element) {
            auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element);
            if (!target) return;
            relationship->setFeaturingType(target);
            if (auto featured = relationship->featureOfType()) {
                auto types = featured->featuringType();
                SysMLv2::Files::replaceInVector(types, type, target);
                featured->setFeaturingType(types);
            }
        });
    applyIdentification(ctx->identification(), relationship);
    if (!ParentStack.empty()) {
        relationship->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(relationship);
    }
    Elements.push_back(relationship);
}

void KerMLListenerImplementation::enterOwned_type_featuring(KerMLParser::Owned_type_featuringContext *) { }

void KerMLListenerImplementation::exitOwned_type_featuring(KerMLParser::Owned_type_featuringContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature)
    {
        std::cout << "Wrong Type in parent stack." << std::endl;
        return;
    }

    if (ctx && ctx->qualified_name()) {
        const auto typeName = ctx->qualified_name()->getText();
        const auto type = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, typeName);

        const auto featureTyping = std::make_shared<KerML::Entities::TypeFeaturing>(type, feature);
        feature->appendOwnedTypeFeaturing(featureTyping);
        Elements.push_back(featureTyping);
        Recorder.record(type, typeName, ReferenceKind::Type, ReferenceRole::Plain, feature, true, nullptr, ctx->qualified_name(),
            [featureTyping](const ElementPtr& element) {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element)) featureTyping->setFeaturingType(target);
            });
    }
}

void KerMLListenerImplementation::enterData_type(KerMLParser::Data_typeContext *) {
    const auto dt = std::make_shared<KerML::Entities::DataType>();
    ParentStack.push(dt);
}

void KerMLListenerImplementation::exitData_type(KerMLParser::Data_typeContext *ctx) {
    if (ParentStack.empty()) return;
    const auto dt = std::dynamic_pointer_cast<KerML::Entities::DataType>(ParentStack.top());
    if (!dt) return;
    ParentStack.pop();

    if (ctx && ctx->type_prefix() && ctx->type_prefix()->KEYWORD_ABSTRACT() != nullptr) {
        dt->setAbstract(true);
    }
    Elements.push_back(dt);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(dt);
    }
}

void KerMLListenerImplementation::enterClass(KerMLParser::ClassContext *) {
    const auto _class = std::make_shared<KerML::Entities::Class>();
    ParentStack.push(_class);
}

void KerMLListenerImplementation::exitClass(KerMLParser::ClassContext *ctx) {
    if (ParentStack.empty()) return;
    const auto _class = std::dynamic_pointer_cast<KerML::Entities::Class>(ParentStack.top());
    if (!_class) return;
    ParentStack.pop();

    if (ctx && ctx->type_prefix() && ctx->type_prefix()->KEYWORD_ABSTRACT() != nullptr) {
        _class->setAbstract(true);
    }
    Elements.push_back(_class);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(_class);
    }
}

void KerMLListenerImplementation::enterStructure(KerMLParser::StructureContext *) {
    const auto str = std::make_shared<KerML::Entities::Structure>();
    ParentStack.push(str);
}

void KerMLListenerImplementation::exitStructure(KerMLParser::StructureContext *ctx) {
    if (ParentStack.empty()) return;
    const auto str = std::dynamic_pointer_cast<KerML::Entities::Structure>(ParentStack.top());
    if (!str) return;
    ParentStack.pop();

    if (ctx && ctx->type_prefix() && ctx->type_prefix()->KEYWORD_ABSTRACT() != nullptr) {
        str->setAbstract(true);
    }
    Elements.push_back(str);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(str);
    }
}

void KerMLListenerImplementation::enterAssociation(KerMLParser::AssociationContext *) {
    const auto assoc = std::make_shared<KerML::Entities::Association>();
    ParentStack.push(assoc);
}

void KerMLListenerImplementation::exitAssociation(KerMLParser::AssociationContext *ctx) {
    if (ParentStack.empty()) return;
    const auto assoc = std::dynamic_pointer_cast<KerML::Entities::Association>(ParentStack.top());
    if (!assoc) return;
    ParentStack.pop();

    if (ctx && ctx->type_prefix() && ctx->type_prefix()->KEYWORD_ABSTRACT() != nullptr) {
        assoc->setAbstract(true);
    }
    Elements.push_back(assoc);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(assoc);
    }
}

void KerMLListenerImplementation::enterAssociation_structure(KerMLParser::Association_structureContext *) {
    const auto assocStruct = std::make_shared<KerML::Entities::AssociationStructure>();
    ParentStack.push(assocStruct);
}

void KerMLListenerImplementation::exitAssociation_structure(KerMLParser::Association_structureContext *) {
    if (ParentStack.empty()) return;
    const auto assocStruct = std::dynamic_pointer_cast<KerML::Entities::AssociationStructure>(ParentStack.top());
    if (!assocStruct) return;
    ParentStack.pop();

    Elements.push_back(assocStruct);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(assocStruct);
    }
}

void KerMLListenerImplementation::enterConnector(KerMLParser::ConnectorContext *) {
    const auto conn = std::make_shared<KerML::Entities::Connector>();
    ParentStack.push(conn);
}

void KerMLListenerImplementation::exitConnector(KerMLParser::ConnectorContext *ctx) {
    if (ParentStack.empty()) return;
    const auto conn = std::dynamic_pointer_cast<KerML::Entities::Connector>(ParentStack.top());
    if (!conn) return;
    ParentStack.pop();

    // 'abstract' (and the other feature modifiers) are applied by exitBasic_feature_prefix.
    (void)ctx;
    Elements.push_back(conn);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(conn);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(conn);
        }
    }
}

void KerMLListenerImplementation::enterConnector_declaration(KerMLParser::Connector_declarationContext *) {

}

void KerMLListenerImplementation::exitConnector_declaration(KerMLParser::Connector_declarationContext *) {

}

void
KerMLListenerImplementation::enterBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *) {

}

void KerMLListenerImplementation::exitBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *ctx) {
    if (!ctx || ParentStack.empty()) return;
    if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
        if (ctx->KEYWORD_ALL()) type->setIsSufficient(true);
    }
}

void KerMLListenerImplementation::enterNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *) {

}

void KerMLListenerImplementation::exitNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *) {

}

void KerMLListenerImplementation::enterConnector_end_member(KerMLParser::Connector_end_memberContext *) {

}

void KerMLListenerImplementation::exitConnector_end_member(KerMLParser::Connector_end_memberContext *) {

}

void KerMLListenerImplementation::enterConnector_end(KerMLParser::Connector_endContext *) {
    const auto endFeature = std::make_shared<KerML::Entities::Feature>();
    endFeature->setIsEnd(true);
    ParentStack.push(endFeature);
}

void KerMLListenerImplementation::exitConnector_end(KerMLParser::Connector_endContext *ctx) {
    if (ParentStack.empty()) return;
    const auto endFeature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!endFeature) return;
    ParentStack.pop();

    if (ctx && ctx->NAME()) {
        endFeature->setDeclaredName(ctx->NAME()->getText());
    }
    Elements.push_back(endFeature);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(endFeature);
        if (auto conn = std::dynamic_pointer_cast<KerML::Entities::Connector>(ParentStack.top())) {
            conn->appendConnectorEnd(endFeature);
        }
    }
}

void KerMLListenerImplementation::enterBinding_connector(KerMLParser::Binding_connectorContext *) {
    const auto bc = std::make_shared<KerML::Entities::BindingConnector>();
    ParentStack.push(bc);
}

void KerMLListenerImplementation::exitBinding_connector(KerMLParser::Binding_connectorContext *) {
    if (ParentStack.empty()) return;
    const auto bc = std::dynamic_pointer_cast<KerML::Entities::BindingConnector>(ParentStack.top());
    if (!bc) return;
    ParentStack.pop();

    Elements.push_back(bc);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(bc);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(bc);
        }
    }
}

void KerMLListenerImplementation::enterBinding_connector_declaration(
        KerMLParser::Binding_connector_declarationContext *) {

}

void
KerMLListenerImplementation::exitBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext *) {

}

void KerMLListenerImplementation::enterSuccession(KerMLParser::SuccessionContext *) {
    const auto succ = std::make_shared<KerML::Entities::Succession>();
    ParentStack.push(succ);
}

void KerMLListenerImplementation::exitSuccession(KerMLParser::SuccessionContext *) {
    if (ParentStack.empty()) return;
    const auto succ = std::dynamic_pointer_cast<KerML::Entities::Succession>(ParentStack.top());
    if (!succ) return;
    ParentStack.pop();

    Elements.push_back(succ);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(succ);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(succ);
        }
    }
}

void KerMLListenerImplementation::enterSuccession_declaration(KerMLParser::Succession_declarationContext *) {

}

void KerMLListenerImplementation::exitSuccession_declaration(KerMLParser::Succession_declarationContext *ctx) {
    if (!ctx || ParentStack.empty()) return;
    if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
        if (ctx->KEYWORD_ALL()) type->setIsSufficient(true);
    }
}

void KerMLListenerImplementation::enterBehavior(KerMLParser::BehaviorContext *) {
    const auto beh = std::make_shared<KerML::Entities::Behavior>();
    ParentStack.push(beh);
}

void KerMLListenerImplementation::exitBehavior(KerMLParser::BehaviorContext *ctx) {
    if (ParentStack.empty()) return;
    const auto beh = std::dynamic_pointer_cast<KerML::Entities::Behavior>(ParentStack.top());
    if (!beh) return;
    ParentStack.pop();

    if (ctx && ctx->type_prefix() && ctx->type_prefix()->KEYWORD_ABSTRACT() != nullptr) {
        beh->setAbstract(true);
    }
    Elements.push_back(beh);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(beh);
    }
}

void KerMLListenerImplementation::enterStep(KerMLParser::StepContext *) {
    const auto step = std::make_shared<KerML::Entities::Step>();
    ParentStack.push(step);
}

void KerMLListenerImplementation::exitStep(KerMLParser::StepContext *) {
    if (ParentStack.empty()) return;
    const auto step = std::dynamic_pointer_cast<KerML::Entities::Step>(ParentStack.top());
    if (!step) return;
    ParentStack.pop();

    Elements.push_back(step);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(step);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(step);
        }
    }
}

void KerMLListenerImplementation::enterFunction(KerMLParser::FunctionContext *) {
    const auto func = std::make_shared<KerML::Entities::Function>();
    ParentStack.push(func);
}

void KerMLListenerImplementation::exitFunction(KerMLParser::FunctionContext *ctx) {
    if (ParentStack.empty()) return;
    const auto func = std::dynamic_pointer_cast<KerML::Entities::Function>(ParentStack.top());
    if (!func) return;
    ParentStack.pop();

    if (ctx && ctx->type_prefix() && ctx->type_prefix()->KEYWORD_ABSTRACT() != nullptr) {
        func->setAbstract(true);
    }
    Elements.push_back(func);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(func);
    }
}

void KerMLListenerImplementation::enterFunction_body(KerMLParser::Function_bodyContext *) {

}

void KerMLListenerImplementation::exitFunction_body(KerMLParser::Function_bodyContext *) {

}

void KerMLListenerImplementation::enterFunction_body_part(KerMLParser::Function_body_partContext *) {

}

void KerMLListenerImplementation::exitFunction_body_part(KerMLParser::Function_body_partContext *) {

}

void KerMLListenerImplementation::enterReturn_feature_member(KerMLParser::Return_feature_memberContext *) {
    const auto ret = std::make_shared<KerML::Entities::ReturnParameterMembership>();
    ParentStack.emplace(ret);
}

void KerMLListenerImplementation::exitReturn_feature_member(KerMLParser::Return_feature_memberContext *) {
    if (ParentStack.empty()) return;
    const auto ret = std::dynamic_pointer_cast<KerML::Entities::ReturnParameterMembership>(ParentStack.top());
    if (!ret) return;
    ParentStack.pop();

    std::shared_ptr<KerML::Entities::Feature> returnFeature = nullptr;
    if (!ret->ownedRelatedElement().empty()) {
        for (const auto& elem : ret->ownedRelatedElement()) {
            if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(elem)) {
                returnFeature = feat;
                ret->setOwnedMemberParameter(feat);
                ret->setOwnedMemberFeature(feat);
                ret->setMemberElement(feat);
                break;
            }
        }
    }
    if (!ParentStack.empty()) {
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            ret->setOwningType(type);
            ret->setMembershipOwningNamespace(type);
            type->appendOwnedFeatureMembership(ret);
            type->appendFeatureMemberships(ret);
        }
        if (auto fn = std::dynamic_pointer_cast<KerML::Entities::Function>(ParentStack.top())) {
            if (returnFeature) {
                fn->setResult(returnFeature);
            }
        }
        ParentStack.top()->appendOwnedElement(ret);
    }
    Elements.push_back(ret);
}

void KerMLListenerImplementation::enterResult_expression_member(KerMLParser::Result_expression_memberContext *) {
    const auto res = std::make_shared<KerML::Entities::ResultExpressionMembership>();
    ParentStack.emplace(res);
}

void KerMLListenerImplementation::exitResult_expression_member(KerMLParser::Result_expression_memberContext *) {
    if (ParentStack.empty()) return;
    const auto res = std::dynamic_pointer_cast<KerML::Entities::ResultExpressionMembership>(ParentStack.top());
    if (!res) return;
    ParentStack.pop();

    if (!res->ownedRelatedElement().empty()) {
        for (const auto& elem : res->ownedRelatedElement()) {
            if (auto expr = std::dynamic_pointer_cast<KerML::Entities::Expression>(elem)) {
                res->setOwnedResultExpression(expr);
                break;
            }
        }
    }
    if (!ParentStack.empty()) {
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            res->setOwningType(type);
            res->setMembershipOwningNamespace(type);
            type->appendOwnedFeatureMembership(res);
            type->appendFeatureMemberships(res);
        }
        ParentStack.top()->appendOwnedElement(res);
    }
    Elements.push_back(res);
}

void KerMLListenerImplementation::enterExpression(KerMLParser::ExpressionContext *) {
    const auto expr = std::make_shared<KerML::Entities::Expression>();
    ParentStack.push(expr);
}

void KerMLListenerImplementation::exitExpression(KerMLParser::ExpressionContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::Expression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();

    Elements.push_back(expr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(expr);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(expr);
        }
    }
}

void KerMLListenerImplementation::enterPredicate(KerMLParser::PredicateContext *) {
    const auto pred = std::make_shared<KerML::Entities::Predicate>();
    ParentStack.push(pred);
}

void KerMLListenerImplementation::exitPredicate(KerMLParser::PredicateContext *ctx) {
    if (ParentStack.empty()) return;
    const auto pred = std::dynamic_pointer_cast<KerML::Entities::Predicate>(ParentStack.top());
    if (!pred) return;
    ParentStack.pop();

    if (ctx && ctx->type_prefix() && ctx->type_prefix()->KEYWORD_ABSTRACT() != nullptr) {
        pred->setAbstract(true);
    }
    Elements.push_back(pred);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(pred);
    }
}

void KerMLListenerImplementation::enterBoolean_expression(KerMLParser::Boolean_expressionContext *) {
    const auto boolExpr = std::make_shared<KerML::Entities::BooleanExpression>();
    ParentStack.push(boolExpr);
}

void KerMLListenerImplementation::exitBoolean_expression(KerMLParser::Boolean_expressionContext *) {
    if (ParentStack.empty()) return;
    const auto boolExpr = std::dynamic_pointer_cast<KerML::Entities::BooleanExpression>(ParentStack.top());
    if (!boolExpr) return;
    ParentStack.pop();

    Elements.push_back(boolExpr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(boolExpr);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(boolExpr);
        }
    }
}

void KerMLListenerImplementation::enterInvariant(KerMLParser::InvariantContext *) {
    const auto inv = std::make_shared<KerML::Entities::Invariant>();
    ParentStack.push(inv);
}

void KerMLListenerImplementation::exitInvariant(KerMLParser::InvariantContext *ctx) {
    if (ParentStack.empty()) return;
    const auto inv = std::dynamic_pointer_cast<KerML::Entities::Invariant>(ParentStack.top());
    if (!inv) return;
    ParentStack.pop();

    if (ctx && ctx->KEYWORD_FALSE() != nullptr) {
        inv->setIsNegated(true);
    }

    Elements.push_back(inv);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(inv);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(inv);
        }
    }
}

void KerMLListenerImplementation::enterOwned_expression_reference_member(
        KerMLParser::Owned_expression_reference_memberContext *) {

}

void KerMLListenerImplementation::exitOwned_expression_reference_member(
        KerMLParser::Owned_expression_reference_memberContext *) {

}

void KerMLListenerImplementation::enterOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *) {

}

void KerMLListenerImplementation::exitOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *) {

}

void KerMLListenerImplementation::enterOwned_expression_member(KerMLParser::Owned_expression_memberContext *) {

}

void KerMLListenerImplementation::exitOwned_expression_member(KerMLParser::Owned_expression_memberContext *) {

}

void KerMLListenerImplementation::enterType_reference_member(KerMLParser::Type_reference_memberContext *) {

}

void KerMLListenerImplementation::exitType_reference_member(KerMLParser::Type_reference_memberContext *) {

}

void KerMLListenerImplementation::enterType_result_member(KerMLParser::Type_result_memberContext *) {

}

void KerMLListenerImplementation::exitType_result_member(KerMLParser::Type_result_memberContext *) {

}

void KerMLListenerImplementation::enterType_reference(KerMLParser::Type_referenceContext *) {

}

void KerMLListenerImplementation::exitType_reference(KerMLParser::Type_referenceContext *ctx) {
    if (!ctx || !ctx->reference_typing()) return;
    auto expression = std::make_shared<KerML::Entities::InstantiationExpression>();
    expression->setInstantiatedType(typeReference(ctx->reference_typing()->getText(), ParentStack.empty() ? nullptr : ParentStack.top(), false,
        ctx->reference_typing(), [expression](const std::shared_ptr<KerML::Entities::Type>& target) { expression->setInstantiatedType(target); }));
    attachExpression(expression);
}

void KerMLListenerImplementation::enterReference_typing(KerMLParser::Reference_typingContext *) {

}

void KerMLListenerImplementation::exitReference_typing(KerMLParser::Reference_typingContext *) {

}

void KerMLListenerImplementation::enterSequence_expression(KerMLParser::Sequence_expressionContext *) {

}

void KerMLListenerImplementation::exitSequence_expression(KerMLParser::Sequence_expressionContext *) {

}

void KerMLListenerImplementation::enterSequence_expression_list(KerMLParser::Sequence_expression_listContext *) {

}

void KerMLListenerImplementation::exitSequence_expression_list(KerMLParser::Sequence_expression_listContext *) {

}

void KerMLListenerImplementation::enterSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void KerMLListenerImplementation::exitSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *) {
    finishOperatorExpression(",");
}

void KerMLListenerImplementation::enterSequence_expression_list_member(
        KerMLParser::Sequence_expression_list_memberContext *) {

}

void KerMLListenerImplementation::exitSequence_expression_list_member(
        KerMLParser::Sequence_expression_list_memberContext *) {

}

void KerMLListenerImplementation::enterFunction_reference(KerMLParser::Function_referenceContext *) {

}

void KerMLListenerImplementation::exitFunction_reference(KerMLParser::Function_referenceContext *ctx) {
    if (!ctx || !ctx->reference_typing()) return;
    auto expression = std::make_shared<KerML::Entities::InstantiationExpression>();
    expression->setInstantiatedType(typeReference(ctx->reference_typing()->getText(), ParentStack.empty() ? nullptr : ParentStack.top(), false,
        ctx->reference_typing(), [expression](const std::shared_ptr<KerML::Entities::Type>& target) { expression->setInstantiatedType(target); }));
    attachExpression(expression);
}

void KerMLListenerImplementation::enterFeature_chain_member(KerMLParser::Feature_chain_memberContext *) {

}

void KerMLListenerImplementation::exitFeature_chain_member(KerMLParser::Feature_chain_memberContext *) {

}

void KerMLListenerImplementation::enterOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *) {

}

void KerMLListenerImplementation::exitOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *) {

}

void KerMLListenerImplementation::enterBase_expression(KerMLParser::Base_expressionContext *) {

}

void KerMLListenerImplementation::exitBase_expression(KerMLParser::Base_expressionContext *) {

}

void KerMLListenerImplementation::enterNull_expression(KerMLParser::Null_expressionContext *) {
    const auto expr = std::make_shared<KerML::Entities::NullExpression>();
    ParentStack.push(expr);
}

void KerMLListenerImplementation::exitNull_expression(KerMLParser::Null_expressionContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::NullExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();

    attachExpression(expr);
}

void
KerMLListenerImplementation::enterFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *) {
    const auto expr = std::make_shared<KerML::Entities::FeatureReferenceExpression>();
    ParentStack.push(expr);
}

void
KerMLListenerImplementation::exitFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *ctx) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();

    if (ctx) {
        std::string refName = ctx->getText();
        auto feat = featureReference(refName, ParentStack.empty() ? nullptr : ParentStack.top(), false, ctx,
            [expr](const std::shared_ptr<KerML::Entities::Feature>& target) { expr->setReferent(target); });
        expr->setReferent(feat);
    }
    attachExpression(expr);
}

void KerMLListenerImplementation::enterFeature_reference_member(KerMLParser::Feature_reference_memberContext *) { }

void KerMLListenerImplementation::exitFeature_reference_member(KerMLParser::Feature_reference_memberContext *) { }

void KerMLListenerImplementation::enterFeature_reference(KerMLParser::Feature_referenceContext *) { }

void KerMLListenerImplementation::exitFeature_reference(KerMLParser::Feature_referenceContext *) { }

void KerMLListenerImplementation::enterMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *) {
    const auto expr = std::make_shared<KerML::Entities::MetadataAccessExpression>();
    ParentStack.push(expr);
}

void KerMLListenerImplementation::exitMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *ctx) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::MetadataAccessExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();

    if (ctx && ctx->qualified_name()) {
        std::string refName = ctx->qualified_name()->getText();
        auto elem = Recorder.reference<KerML::Entities::Element>(refName, ReferenceKind::Element, ReferenceRole::Plain,
            ParentStack.empty() ? nullptr : ParentStack.top(), false, nullptr, ctx->qualified_name(),
            [expr](const ElementPtr& target) { expr->setReferencedElement(target); });
        expr->setReferencedElement(elem);
    }
    attachExpression(expr);
}

void KerMLListenerImplementation::enterInvocation_expression(KerMLParser::Invocation_expressionContext *) {
    const auto expr = std::make_shared<KerML::Entities::InvocationExpression>();
    ParentStack.push(expr);
}

void KerMLListenerImplementation::exitInvocation_expression(KerMLParser::Invocation_expressionContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::InvocationExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();

    attachExpression(expr);
}

void KerMLListenerImplementation::enterInternal_invocation_expression(
        KerMLParser::Internal_invocation_expressionContext *) {

}

void KerMLListenerImplementation::exitInternal_invocation_expression(
        KerMLParser::Internal_invocation_expressionContext *) {

}

void KerMLListenerImplementation::enterArgument_list(KerMLParser::Argument_listContext *) {

}

void KerMLListenerImplementation::exitArgument_list(KerMLParser::Argument_listContext *) {

}

void KerMLListenerImplementation::enterPositional_argument_list(KerMLParser::Positional_argument_listContext *) {

}

void KerMLListenerImplementation::exitPositional_argument_list(KerMLParser::Positional_argument_listContext *) {

}

void KerMLListenerImplementation::enterNamed_argument_list(KerMLParser::Named_argument_listContext *) {

}

void KerMLListenerImplementation::exitNamed_argument_list(KerMLParser::Named_argument_listContext *) {

}

void KerMLListenerImplementation::enterNamed_argument_member(KerMLParser::Named_argument_memberContext *) {

}

void KerMLListenerImplementation::exitNamed_argument_member(KerMLParser::Named_argument_memberContext *) {

}

void KerMLListenerImplementation::enterNamed_argument(KerMLParser::Named_argumentContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::Expression>());
}

void KerMLListenerImplementation::exitNamed_argument(KerMLParser::Named_argumentContext *) {
    if (ParentStack.empty()) return;
    const auto argument = std::dynamic_pointer_cast<KerML::Entities::Expression>(ParentStack.top());
    if (!argument) return;
    ParentStack.pop();
    attachExpression(argument);
}

void KerMLListenerImplementation::enterParameter_redefinition(KerMLParser::Parameter_redefinitionContext *) {

}

void KerMLListenerImplementation::exitParameter_redefinition(KerMLParser::Parameter_redefinitionContext *ctx) {
    if (!ctx || !ctx->qualified_name() || ParentStack.empty()) return;
    const auto argument = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!argument) return;
    // The parameter of the invoked function is not resolved (no scoped lookup is attempted); it keeps its placeholder.
    const auto parameter = notAttemptedFeature(Recorder, ctx->qualified_name()->getText(), argument, ctx->qualified_name());
    argument->setDeclaredName(ctx->qualified_name()->getText());
    const auto redefinition = std::make_shared<KerML::Entities::Redefinition>(parameter, argument);
    argument->appendOwnedRedefinition(redefinition);
    argument->appendOwnedElement(redefinition);
    Elements.push_back(redefinition);
}

void KerMLListenerImplementation::enterBody_expression(KerMLParser::Body_expressionContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::Expression>());
}

void KerMLListenerImplementation::exitBody_expression(KerMLParser::Body_expressionContext *) {
    if (ParentStack.empty()) return;
    const auto expression = std::dynamic_pointer_cast<KerML::Entities::Expression>(ParentStack.top());
    if (!expression) return;
    ParentStack.pop();
    attachExpression(expression);
}

void KerMLListenerImplementation::enterExpression_body_member(KerMLParser::Expression_body_memberContext *) {

}

void KerMLListenerImplementation::exitExpression_body_member(KerMLParser::Expression_body_memberContext *) {

}

void KerMLListenerImplementation::enterExpression_body(KerMLParser::Expression_bodyContext *) {

}

void KerMLListenerImplementation::exitExpression_body(KerMLParser::Expression_bodyContext *) {

}

void KerMLListenerImplementation::enterLiteral_expression(KerMLParser::Literal_expressionContext *) {

}

void KerMLListenerImplementation::exitLiteral_expression(KerMLParser::Literal_expressionContext *ctx) {
    if (!ctx) return;
    std::shared_ptr<KerML::Entities::LiteralExpression> literal;
    if (ctx->KEYWORD_TRUE() != nullptr) {
        auto b = std::make_shared<KerML::Entities::LiteralBoolean>();
        b->setValue(true);
        literal = b;
    } else if (ctx->KEYWORD_FALSE() != nullptr) {
        auto b = std::make_shared<KerML::Entities::LiteralBoolean>();
        b->setValue(false);
        literal = b;
    } else if (ctx->literal_string() != nullptr) {
        auto s = std::make_shared<KerML::Entities::LiteralString>();
        std::string text = ctx->literal_string()->getText();
        if (text.size() >= 2 && text.front() == '"' && text.back() == '"') {
            text = text.substr(1, text.size() - 2);
        }
        s->setValue(text);
        literal = s;
    } else if (ctx->literal_integer() != nullptr) {
        auto i = std::make_shared<KerML::Entities::LiteralInteger>();
        try {
            i->setValue(std::stoll(ctx->literal_integer()->getText()));
        } catch (...) {
            i->setValue(0);
        }
        literal = i;
    } else if (ctx->literal_real() != nullptr) {
        auto r = std::make_shared<KerML::Entities::LiteralRational>();
        try {
            r->setValue(std::stod(ctx->literal_real()->getText()));
        } catch (...) {
            r->setValue(0.0);
        }
        literal = r;
    } else if (ctx->literal_infinity() != nullptr) {
        literal = std::make_shared<KerML::Entities::LiteralInfinity>();
    }

    if (literal) {
        attachExpression(literal);
    }
}

void KerMLListenerImplementation::enterLiteral_boolean(KerMLParser::Literal_booleanContext *) {

}

void KerMLListenerImplementation::exitLiteral_boolean(KerMLParser::Literal_booleanContext *ctx) {
    if (!ctx || !ctx->boolean_value()) return;
    auto b = std::make_shared<KerML::Entities::LiteralBoolean>();
    b->setValue(ctx->boolean_value()->KEYWORD_TRUE() != nullptr);
    Elements.push_back(b);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(b);
        if (auto fv = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top())) {
            fv->setValue(b);
        }
    }
}

void KerMLListenerImplementation::enterBoolean_value(KerMLParser::Boolean_valueContext *) {

}

void KerMLListenerImplementation::exitBoolean_value(KerMLParser::Boolean_valueContext *) {

}

void KerMLListenerImplementation::enterLiteral_string(KerMLParser::Literal_stringContext *) {

}

void KerMLListenerImplementation::exitLiteral_string(KerMLParser::Literal_stringContext *) {

}

void KerMLListenerImplementation::enterLiteral_integer(KerMLParser::Literal_integerContext *) {

}

void KerMLListenerImplementation::exitLiteral_integer(KerMLParser::Literal_integerContext *) {

}

void KerMLListenerImplementation::enterLiteral_real(KerMLParser::Literal_realContext *) {

}

void KerMLListenerImplementation::exitLiteral_real(KerMLParser::Literal_realContext *) {

}

void KerMLListenerImplementation::enterReal_value(KerMLParser::Real_valueContext *) {

}

void KerMLListenerImplementation::exitReal_value(KerMLParser::Real_valueContext *) {

}

void KerMLListenerImplementation::enterLiteral_infinity(KerMLParser::Literal_infinityContext *) {

}

void KerMLListenerImplementation::exitLiteral_infinity(KerMLParser::Literal_infinityContext *) {

}

void KerMLListenerImplementation::enterInteraction(KerMLParser::InteractionContext *) {
    const auto interaction = std::make_shared<KerML::Entities::Interaction>();
    ParentStack.push(interaction);
}

void KerMLListenerImplementation::exitInteraction(KerMLParser::InteractionContext *) {
    if (ParentStack.empty()) return;
    const auto interaction = std::dynamic_pointer_cast<KerML::Entities::Interaction>(ParentStack.top());
    if (!interaction) return;
    ParentStack.pop();

    Elements.push_back(interaction);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(interaction);
    }
}

void KerMLListenerImplementation::enterItem_flow(KerMLParser::Item_flowContext *) {
    const auto flow = std::make_shared<KerML::Entities::Flow>();
    ParentStack.push(flow);
}

void KerMLListenerImplementation::exitItem_flow(KerMLParser::Item_flowContext *) {
    if (ParentStack.empty()) return;
    const auto flow = std::dynamic_pointer_cast<KerML::Entities::Flow>(ParentStack.top());
    if (!flow) return;
    ParentStack.pop();

    Elements.push_back(flow);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(flow);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(flow);
        }
    }
}

void KerMLListenerImplementation::enterSuccession_item_flow(KerMLParser::Succession_item_flowContext *) {
    const auto succFlow = std::make_shared<KerML::Entities::SuccessionFlow>();
    ParentStack.push(succFlow);
}

void KerMLListenerImplementation::exitSuccession_item_flow(KerMLParser::Succession_item_flowContext *) {
    if (ParentStack.empty()) return;
    const auto succFlow = std::dynamic_pointer_cast<KerML::Entities::SuccessionFlow>(ParentStack.top());
    if (!succFlow) return;
    ParentStack.pop();

    Elements.push_back(succFlow);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(succFlow);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(succFlow);
        }
    }
}

void KerMLListenerImplementation::enterItem_flow_declaration(KerMLParser::Item_flow_declarationContext *) {

}

void KerMLListenerImplementation::exitItem_flow_declaration(KerMLParser::Item_flow_declarationContext *ctx) {
    if (!ctx || ParentStack.empty()) return;
    if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
        if (ctx->KEYWORD_ALL()) type->setIsSufficient(true);
    }
}

void KerMLListenerImplementation::enterItem_feature_member(KerMLParser::Item_feature_memberContext *) {

}

void KerMLListenerImplementation::exitItem_feature_member(KerMLParser::Item_feature_memberContext *) {

}

void KerMLListenerImplementation::enterItem_feature(KerMLParser::Item_featureContext *) {
    const auto payload = std::make_shared<KerML::Entities::PayloadFeature>();
    ParentStack.push(payload);
}

void KerMLListenerImplementation::exitItem_feature(KerMLParser::Item_featureContext *ctx) {
    if (ParentStack.empty()) return;
    const auto payload = std::dynamic_pointer_cast<KerML::Entities::PayloadFeature>(ParentStack.top());
    if (!payload) return;
    ParentStack.pop();

    if (ctx && ctx->identification()) {
        applyIdentification(ctx->identification(), payload);
    }
    Elements.push_back(payload);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(payload);
        if (auto flow = std::dynamic_pointer_cast<KerML::Entities::Flow>(ParentStack.top())) {
            flow->appendOwnedFeature(payload);
        }
    }
}

void KerMLListenerImplementation::enterItem_feature_specialization_part(
        KerMLParser::Item_feature_specialization_partContext *) {

}

void KerMLListenerImplementation::exitItem_feature_specialization_part(
        KerMLParser::Item_feature_specialization_partContext *) {

}

void KerMLListenerImplementation::enterItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *) {

}

void KerMLListenerImplementation::exitItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *) {

}

void KerMLListenerImplementation::enterItem_flow_end(KerMLParser::Item_flow_endContext *) {
    const auto flowEnd = std::make_shared<KerML::Entities::FlowEnd>();
    ParentStack.push(flowEnd);
}

void KerMLListenerImplementation::exitItem_flow_end(KerMLParser::Item_flow_endContext *ctx) {
    if (ParentStack.empty()) return;
    const auto flowEnd = std::dynamic_pointer_cast<KerML::Entities::FlowEnd>(ParentStack.top());
    if (!flowEnd) return;
    ParentStack.pop();

    if (ctx && ctx->item_flow_feature_member()) {
        flowEnd->setDeclaredName(ctx->item_flow_feature_member()->getText());
    }
    Elements.push_back(flowEnd);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(flowEnd);
        if (auto flow = std::dynamic_pointer_cast<KerML::Entities::Flow>(ParentStack.top())) {
            flow->appendOwnedFeature(flowEnd);
            flow->appendConnectorEnd(flowEnd);
        }
    }
}

void KerMLListenerImplementation::enterItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *) {

}

void KerMLListenerImplementation::exitItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *) {

}

void KerMLListenerImplementation::enterItem_flow_feature(KerMLParser::Item_flow_featureContext *) {

}

void KerMLListenerImplementation::exitItem_flow_feature(KerMLParser::Item_flow_featureContext *) {

}

void KerMLListenerImplementation::enterItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *) {

}

void KerMLListenerImplementation::exitItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *ctx) {
    if (!ctx || !ctx->qualified_name() || ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) return;
    const auto redefinedName = ctx->qualified_name()->getText();
    const auto redefined = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, redefinedName);
    const auto relationship = std::make_shared<KerML::Entities::Redefinition>(redefined, feature);
    feature->appendOwnedRedefinition(relationship);
    feature->appendOwnedElement(relationship);
    Elements.push_back(relationship);
    Recorder.record(redefined, redefinedName, ReferenceKind::Feature, ReferenceRole::Redefinition, feature, true, feature, ctx->qualified_name(),
        [relationship](const ElementPtr& element) {
            if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element))
                SysMLv2::Files::Retarget::redefinition(*relationship, target);
        });
}

void KerMLListenerImplementation::enterValue_part(KerMLParser::Value_partContext *) {

}

void KerMLListenerImplementation::exitValue_part(KerMLParser::Value_partContext *) {

}

void KerMLListenerImplementation::enterFeature_value(KerMLParser::Feature_valueContext *ctx) {
    const auto fv = std::make_shared<KerML::Entities::FeatureValue>();
    if (ctx && ctx->KEYWORD_DEFAULT() != nullptr) {
        fv->setIsDefault(true);
    }
    ParentStack.push(fv);
}

void KerMLListenerImplementation::exitFeature_value(KerMLParser::Feature_valueContext *) {
    if (ParentStack.empty()) return;
    const auto fv = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top());
    if (!fv) return;
    ParentStack.pop();

    Elements.push_back(fv);
    if (!ParentStack.empty()) {
        if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
            fv->setFeatureWithValue(feat);
        }
        ParentStack.top()->appendOwnedElement(fv);
    }
}

void KerMLListenerImplementation::enterFeature_assignment(KerMLParser::Feature_assignmentContext *) {
    const auto fv = std::make_shared<KerML::Entities::FeatureValue>();
    ParentStack.push(fv);
}

void KerMLListenerImplementation::exitFeature_assignment(KerMLParser::Feature_assignmentContext *) {
    if (ParentStack.empty()) return;
    const auto fv = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top());
    if (!fv) return;
    ParentStack.pop();

    Elements.push_back(fv);
    if (!ParentStack.empty()) {
        if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
            fv->setFeatureWithValue(feat);
        }
        ParentStack.top()->appendOwnedElement(fv);
    }
}

void KerMLListenerImplementation::enterMultiplicity(KerMLParser::MultiplicityContext *) {

}

void KerMLListenerImplementation::exitMultiplicity(KerMLParser::MultiplicityContext *) {

}

void KerMLListenerImplementation::enterMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::Multiplicity>(1));
}

void KerMLListenerImplementation::exitMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *ctx) {
    if (ParentStack.empty()) return;
    const auto multiplicity = std::dynamic_pointer_cast<KerML::Entities::Multiplicity>(ParentStack.top());
    if (!multiplicity) return;
    if (ctx) applyIdentification(ctx->identification(), multiplicity);
    ParentStack.pop();
    Elements.push_back(multiplicity);
    if (!ParentStack.empty()) {
        multiplicity->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(multiplicity);
    }
}

void KerMLListenerImplementation::enterMultiplicity_range(KerMLParser::Multiplicity_rangeContext *) {
    const auto multRange = std::make_shared<KerML::Entities::MultiplicityRange>();
    ParentStack.push(multRange);
}

void KerMLListenerImplementation::exitMultiplicity_range(KerMLParser::Multiplicity_rangeContext *ctx) {
    if (ParentStack.empty()) return;
    const auto multRange = std::dynamic_pointer_cast<KerML::Entities::MultiplicityRange>(ParentStack.top());
    if (!multRange) return;
    ParentStack.pop();

    if (ctx && ctx->identification()) {
        applyIdentification(ctx->identification(), multRange);
    }
    Elements.push_back(multRange);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(multRange);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->setMultiplicity(multRange);
        }
    }
}

void KerMLListenerImplementation::enterOwned_multiplicity(KerMLParser::Owned_multiplicityContext *) {

}

void KerMLListenerImplementation::exitOwned_multiplicity(KerMLParser::Owned_multiplicityContext *) {

}

void KerMLListenerImplementation::enterOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *) {

}

void KerMLListenerImplementation::exitOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *) {

}

void KerMLListenerImplementation::enterMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext*) { }

void KerMLListenerImplementation::exitMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext *ctx) {
    if (ParentStack.empty()) return;
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type || !ctx || ctx->multiplicity_expression_member().empty()) {
        return;
    }
    std::shared_ptr<KerML::Entities::Multiplicity> multiplicity;
    try {
        if (ctx->multiplicity_expression_member().size() > 1) {
            unsigned minimum = std::stoul(ctx->multiplicity_expression_member().front()->getText());
            if (ctx->multiplicity_expression_member().back()->getText() == "*") {
                multiplicity = std::make_shared<KerML::Entities::Multiplicity>(minimum, true);
            } else {
                unsigned maximum = std::stoul(ctx->multiplicity_expression_member().back()->getText());
                multiplicity = std::make_shared<KerML::Entities::Multiplicity>(minimum, maximum);
            }
        } else {
            if (ctx->multiplicity_expression_member().front()->getText() == "*") {
                multiplicity = std::make_shared<KerML::Entities::Multiplicity>(0, true);
            } else {
                unsigned minimum = std::stoul(ctx->multiplicity_expression_member().front()->getText());
                multiplicity = std::make_shared<KerML::Entities::Multiplicity>(minimum);
            }
        }
    } catch (...) {
        multiplicity = std::make_shared<KerML::Entities::Multiplicity>(1);
    }
    if (multiplicity) {
        type->setMultiplicity(multiplicity);
        type->appendOwnedElement(multiplicity);
        Elements.push_back(multiplicity);
    }
}

void KerMLListenerImplementation::enterMultiplicity_expression_member(
        KerMLParser::Multiplicity_expression_memberContext *) {

}

void KerMLListenerImplementation::exitMultiplicity_expression_member(
        KerMLParser::Multiplicity_expression_memberContext *) {

}

void KerMLListenerImplementation::enterInternal_multiplicity_expression_member(
        KerMLParser::Internal_multiplicity_expression_memberContext *) {

}

void KerMLListenerImplementation::exitInternal_multiplicity_expression_member(
        KerMLParser::Internal_multiplicity_expression_memberContext *) {

}

void KerMLListenerImplementation::enterMetaclass(KerMLParser::MetaclassContext *) {
    const auto metaclass = std::make_shared<KerML::Entities::Metaclass>();
    ParentStack.push(metaclass);
}

void KerMLListenerImplementation::exitMetaclass(KerMLParser::MetaclassContext *ctx) {
    if (ParentStack.empty()) return;
    const auto metaclass = std::dynamic_pointer_cast<KerML::Entities::Metaclass>(ParentStack.top());
    if (!metaclass) return;
    ParentStack.pop();

    if (ctx) {
        if (ctx->identification() != nullptr) {
            applyIdentification(ctx->identification(), metaclass);
        }
        if (ctx->specializes_operator() != nullptr && !ctx->NAME().empty()) {
            std::string superName = ctx->NAME().back()->getText();
            auto superClassifier = newPlaceholder<KerML::Entities::Classifier>(ReferenceKind::Classifier, superName);
            auto subclassification = std::make_shared<KerML::Entities::Subclassification>(superClassifier, metaclass);
            metaclass->appendOwnedSubclassification(subclassification);
            metaclass->appendOwnedSpecialization(subclassification);
            metaclass->appendOwnedElement(subclassification);
            Elements.push_back(subclassification);
            Recorder.record(superClassifier, superName, ReferenceKind::Classifier, ReferenceRole::Generalization, metaclass, true, metaclass,
                ctx,
                [subclassification](const ElementPtr& element) {
                    if (auto target = std::dynamic_pointer_cast<KerML::Entities::Classifier>(element))
                        SysMLv2::Files::Retarget::subclassification(*subclassification, target);
                });
        }
    }
    Elements.push_back(metaclass);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(metaclass);
    }
}

void KerMLListenerImplementation::enterPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *) {

}

void KerMLListenerImplementation::exitPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *) {

}

void KerMLListenerImplementation::enterPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *) {

}

void KerMLListenerImplementation::exitPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *) {

}

void KerMLListenerImplementation::enterPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *) {
    const auto metaFeature = std::make_shared<KerML::Entities::MetadataFeature>();
    ParentStack.push(metaFeature);
}

void KerMLListenerImplementation::exitPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *) {
    if (ParentStack.empty()) return;
    const auto metaFeature = std::dynamic_pointer_cast<KerML::Entities::MetadataFeature>(ParentStack.top());
    if (!metaFeature) return;
    ParentStack.pop();

    Elements.push_back(metaFeature);
    if (!ParentStack.empty()) {
        metaFeature->appendAnnotatedElement(ParentStack.top());
        ParentStack.top()->appendOwnedElement(metaFeature);
    }
}

void KerMLListenerImplementation::enterMetadata_feature(KerMLParser::Metadata_featureContext *) {
    const auto metaFeature = std::make_shared<KerML::Entities::MetadataFeature>();
    ParentStack.push(metaFeature);
}

void KerMLListenerImplementation::exitMetadata_feature(KerMLParser::Metadata_featureContext *) {
    if (ParentStack.empty()) return;
    const auto metaFeature = std::dynamic_pointer_cast<KerML::Entities::MetadataFeature>(ParentStack.top());
    if (!metaFeature) return;
    ParentStack.pop();

    Elements.push_back(metaFeature);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(metaFeature);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(metaFeature);
        }
    }
}

void
KerMLListenerImplementation::enterMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *) {

}

void
KerMLListenerImplementation::exitMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *ctx) {
    if (ParentStack.empty()) return;
    const auto metaFeature = std::dynamic_pointer_cast<KerML::Entities::MetadataFeature>(ParentStack.top());
    if (metaFeature && ctx && ctx->identification()) {
        applyIdentification(ctx->identification(), metaFeature);
    }
}

void KerMLListenerImplementation::enterMetadata_body(KerMLParser::Metadata_bodyContext *) {

}

void KerMLListenerImplementation::exitMetadata_body(KerMLParser::Metadata_bodyContext *) {

}

void KerMLListenerImplementation::enterMetadata_body_element(KerMLParser::Metadata_body_elementContext *) {

}

void KerMLListenerImplementation::exitMetadata_body_element(KerMLParser::Metadata_body_elementContext *) {

}

void
KerMLListenerImplementation::enterMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *) {

}

void
KerMLListenerImplementation::exitMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *) {

}

void KerMLListenerImplementation::enterMetadata_body_feature(KerMLParser::Metadata_body_featureContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::Feature>());
}

void KerMLListenerImplementation::exitMetadata_body_feature(KerMLParser::Metadata_body_featureContext *) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) return;
    ParentStack.pop();
    Elements.push_back(feature);
    if (!ParentStack.empty()) {
        feature->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(feature);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
            type->appendOwnedFeature(feature);
        }
    }
}

void KerMLListenerImplementation::enterPackage(KerMLParser::PackageContext *) {
    const auto package = std::make_shared<KerML::Entities::Package>();
    ParentStack.push(package);
}

void KerMLListenerImplementation::exitPackage(KerMLParser::PackageContext *) {
    if (ParentStack.empty()) return;
    const auto package = std::dynamic_pointer_cast<KerML::Entities::Package>(ParentStack.top());
    ParentStack.pop();
    if (package) {
        Elements.push_back(package);
        if (!ParentStack.empty()) {
            ParentStack.top()->appendOwnedElement(package);
        }
    }
}

void KerMLListenerImplementation::enterLibrary_package(KerMLParser::Library_packageContext *ctx) {
    const auto libPackage = std::make_shared<KerML::Entities::LibraryPackage>();
    if (ctx && ctx->KEYWORD_STANDARD() != nullptr) {
        libPackage->setIsStandard(true);
    }
    ParentStack.push(libPackage);
}

void KerMLListenerImplementation::exitLibrary_package(KerMLParser::Library_packageContext *) {
    if (ParentStack.empty()) return;
    const auto libPackage = std::dynamic_pointer_cast<KerML::Entities::LibraryPackage>(ParentStack.top());
    ParentStack.pop();
    if (libPackage) {
        Elements.push_back(libPackage);
        if (!ParentStack.empty()) {
            ParentStack.top()->appendOwnedElement(libPackage);
        }
    }
}

void KerMLListenerImplementation::enterPackage_declaration(KerMLParser::Package_declarationContext *) {

}

void KerMLListenerImplementation::exitPackage_declaration(KerMLParser::Package_declarationContext *ctx) {
    if (ParentStack.empty()) return;
    const auto package = std::dynamic_pointer_cast<KerML::Entities::Package>(ParentStack.top());
    if (package && ctx && ctx->identification()) {
        applyIdentification(ctx->identification(), package);
    }
}

void KerMLListenerImplementation::enterPackage_body(KerMLParser::Package_bodyContext *) {

}

void KerMLListenerImplementation::exitPackage_body(KerMLParser::Package_bodyContext *) {

}

void KerMLListenerImplementation::enterElement_filter_member(KerMLParser::Element_filter_memberContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::ElementFilterMembership>());
}

void KerMLListenerImplementation::exitElement_filter_member(KerMLParser::Element_filter_memberContext *ctx) {
    if (ParentStack.empty()) return;
    const auto filter = std::dynamic_pointer_cast<KerML::Entities::ElementFilterMembership>(ParentStack.top());
    if (!filter) return;
    ParentStack.pop();
    for (const auto& child : filter->ownedElements()) {
        if (auto condition = std::dynamic_pointer_cast<KerML::Entities::Expression>(child)) {
            filter->setCondition(condition);
            break;
        }
    }
    if (ctx && ctx->member_prefix() && ctx->member_prefix()->visibility_indicator()) {
        const auto visibility = ctx->member_prefix()->visibility_indicator();
        filter->setVisibility(visibility->KEYWORD_PRIVATE() ? KerML::Entities::PRIVATE :
                              visibility->KEYWORD_PROTECTED() ? KerML::Entities::PROTECTED : KerML::Entities::PUBLIC);
    }
    if (!ParentStack.empty()) {
        filter->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(filter);
        if (auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top())) {
            filter->setMembershipOwningNamespace(ns);
            ns->appendOwnedMembership(filter);
        }
    }
    Elements.push_back(filter);
}

void KerMLListenerImplementation::enterMeta_assignment(KerMLParser::Meta_assignmentContext *) {

}

void KerMLListenerImplementation::exitMeta_assignment(KerMLParser::Meta_assignmentContext *ctx) {
    if (!ctx || !ctx->identification() || ctx->qualified_name().size() != 2 || ParentStack.empty()) return;
    const auto scope = ParentStack.top();
    const auto value = std::make_shared<KerML::Entities::FeatureValue>();
    const auto feature = featureReference(ctx->qualified_name(0)->getText(), scope, false, ctx->qualified_name(0),
        [value](const std::shared_ptr<KerML::Entities::Feature>& target) { value->setFeatureWithValue(target); });
    value->setFeatureWithValue(feature);
    const auto expression = std::make_shared<KerML::Entities::MetadataAccessExpression>();
    const auto names = ctx->identification()->NAME();
    if (!names.empty()) {
        expression->setReferencedElement(Recorder.reference<KerML::Entities::Element>(names.back()->getText(), ReferenceKind::Element,
            ReferenceRole::Plain, scope, false, nullptr, ctx->identification(),
            [expression](const ElementPtr& target) { expression->setReferencedElement(target); }));
    }
    const auto typeName = ctx->qualified_name(1)->getText();
    const auto type = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, typeName);
    const auto typing = std::make_shared<KerML::Entities::FeatureTyping>(type, expression);
    Recorder.record(type, typeName, ReferenceKind::Type, ReferenceRole::Generalization, scope, false, expression, ctx->qualified_name(1),
        [expression, typing, type](const ElementPtr& element) {
            auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element);
            if (!target) return;
            SysMLv2::Files::Retarget::featureTyping(*typing, target);
            auto types = expression->type();
            SysMLv2::Files::replaceInVector(types, type, target);
            expression->setType(types);
        });
    expression->appendOwnedTyping(typing);
    expression->appendType(type);
    expression->appendOwnedElement(typing);
    value->setValue(expression);
    value->appendOwnedElement(expression);
    feature->appendOwnedElement(value);
    Elements.push_back(typing);
    Elements.push_back(expression);
    Elements.push_back(value);
}

void KerMLListenerImplementation::enterConditionalExpr(KerMLParser::ConditionalExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void KerMLListenerImplementation::exitConditionalExpr(KerMLParser::ConditionalExprContext *) {
    finishOperatorExpression("if");
}

void KerMLListenerImplementation::enterBinaryExpr(KerMLParser::BinaryExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void KerMLListenerImplementation::exitBinaryExpr(KerMLParser::BinaryExprContext *ctx) {
    finishOperatorExpression(ctx && ctx->op ? ctx->op->getText() : std::string());
}

void KerMLListenerImplementation::enterUnaryExpr(KerMLParser::UnaryExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void KerMLListenerImplementation::exitUnaryExpr(KerMLParser::UnaryExprContext *ctx) {
    finishOperatorExpression(ctx && ctx->op ? ctx->op->getText() : std::string());
}

void KerMLListenerImplementation::enterClassificationExpr(KerMLParser::ClassificationExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void KerMLListenerImplementation::exitClassificationExpr(KerMLParser::ClassificationExprContext *ctx) {
    finishOperatorExpression(ctx && ctx->op ? ctx->op->getText() : std::string("as"));
}

void KerMLListenerImplementation::enterMetaclassificationExpr(KerMLParser::MetaclassificationExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void KerMLListenerImplementation::exitMetaclassificationExpr(KerMLParser::MetaclassificationExprContext *ctx) {
    finishOperatorExpression(ctx && ctx->op ? ctx->op->getText() : std::string("meta"));
}

void KerMLListenerImplementation::enterExtentExpr(KerMLParser::ExtentExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void KerMLListenerImplementation::exitExtentExpr(KerMLParser::ExtentExprContext *) {
    finishOperatorExpression("all");
}

void KerMLListenerImplementation::enterBracketExpr(KerMLParser::BracketExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void KerMLListenerImplementation::exitBracketExpr(KerMLParser::BracketExprContext *) {
    finishOperatorExpression("[");
}

void KerMLListenerImplementation::enterIndexExpr(KerMLParser::IndexExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::IndexExpression>());
}

void KerMLListenerImplementation::exitIndexExpr(KerMLParser::IndexExprContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::IndexExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();
    expr->setOperatorName("#");
    attachExpression(expr);
}

void KerMLListenerImplementation::enterFeatureChainExpr(KerMLParser::FeatureChainExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::FeatureChainExpression>());
}

void KerMLListenerImplementation::exitFeatureChainExpr(KerMLParser::FeatureChainExprContext *ctx) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::FeatureChainExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();
    expr->setOperatorName(".");
    if (ctx && ctx->feature_reference_member()) {
        const auto scope = ParentStack.empty() ? nullptr : ParentStack.top();
        const std::string left = ctx->owned_expression() ? ctx->owned_expression()->getText() : std::string();
        const std::string target = ctx->feature_reference_member()->getText();
        if (SysMLv2::Files::isPlainNameChain(left)) {
            // `a.b`: the target is a feature of the value of `a`; the feature chain a.b is resolved as a whole.
            auto placeholder = Recorder.reference<KerML::Entities::Feature>(left + "." + target, ReferenceKind::Feature, ReferenceRole::Plain,
                scope, false, nullptr, ctx->feature_reference_member(),
                [expr](const std::shared_ptr<KerML::Entities::Feature>& feature) { expr->setTargetFeature(feature); });
            placeholder->setDeclaredName(target);
            expr->setTargetFeature(placeholder);
        } else {
            // The left operand is a computed value: no scoped lookup is attempted for the target.
            expr->setTargetFeature(notAttemptedFeature(Recorder, target, scope, ctx->feature_reference_member()));
        }
    }
    attachExpression(expr);
}

void KerMLListenerImplementation::enterCollectExpr(KerMLParser::CollectExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::CollectExpression>());
}

void KerMLListenerImplementation::exitCollectExpr(KerMLParser::CollectExprContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::CollectExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();
    attachExpression(expr);
}

void KerMLListenerImplementation::enterSelectExpr(KerMLParser::SelectExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::SelectExpression>());
}

void KerMLListenerImplementation::exitSelectExpr(KerMLParser::SelectExprContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::SelectExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();
    attachExpression(expr);
}

void KerMLListenerImplementation::enterFunctionOperationExpr(KerMLParser::FunctionOperationExprContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void KerMLListenerImplementation::exitFunctionOperationExpr(KerMLParser::FunctionOperationExprContext *ctx) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();
    expr->setOperatorName("->");
    if (ctx && ctx->reference_typing()) {
        expr->setInstantiatedType(typeReference(ctx->reference_typing()->getText(), ParentStack.empty() ? nullptr : ParentStack.top(), false,
            ctx->reference_typing(), [expr](const std::shared_ptr<KerML::Entities::Type>& target) { expr->setInstantiatedType(target); }));
    }
    attachExpression(expr);
}

void KerMLListenerImplementation::enterSequenceExpr(KerMLParser::SequenceExprContext *) {}

void KerMLListenerImplementation::exitSequenceExpr(KerMLParser::SequenceExprContext *) {}

void KerMLListenerImplementation::enterBaseExpr(KerMLParser::BaseExprContext *) {}

void KerMLListenerImplementation::exitBaseExpr(KerMLParser::BaseExprContext *) {}

void KerMLListenerImplementation::enterFunction_operation_arguments(KerMLParser::Function_operation_argumentsContext *) {}

void KerMLListenerImplementation::exitFunction_operation_arguments(KerMLParser::Function_operation_argumentsContext *) {}

void KerMLListenerImplementation::enterConstructor_expression(KerMLParser::Constructor_expressionContext *) {
    ParentStack.push(std::make_shared<KerML::Entities::ConstructorExpression>());
}

void KerMLListenerImplementation::exitConstructor_expression(KerMLParser::Constructor_expressionContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::ConstructorExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();
    attachExpression(expr);
}

void KerMLListenerImplementation::visitTerminal(antlr4::tree::TerminalNode *) {

}

void KerMLListenerImplementation::visitErrorNode(antlr4::tree::ErrorNode *) {

}

void KerMLListenerImplementation::enterEveryRule(antlr4::ParserRuleContext *ctx) {
    if (ParentStack.empty() || ctx == nullptr) return;
    // The connector ends written in a connector declaration are end features owned through an EndFeatureMembership.
    if (dynamic_cast<KerMLParser::Connector_end_memberContext *>(ctx) != nullptr)
        SysMLv2::Files::beginMember(MemberMarks, ctx, SysMLv2::Files::MembershipKind::EndFeature, ParentStack.top());
    // The element that follows a member prefix (`private feature x;`) is owned with the visibility of the prefix.
    if (auto *parent = dynamic_cast<antlr4::ParserRuleContext *>(ctx->parent)) {
        for (size_t i = 0; i < parent->children.size() && parent->children[i] != ctx; ++i) {
            auto *prefix = dynamic_cast<KerMLParser::Member_prefixContext *>(parent->children[i]);
            if (prefix == nullptr || prefix->visibility_indicator() == nullptr) continue;
            // (only the keyword and the element itself may follow the prefix: `member`, `return`, `filter`, ...)
            bool adjacent = true;
            for (size_t j = i + 1; j < parent->children.size() && parent->children[j] != ctx; ++j) {
                if (dynamic_cast<antlr4::tree::TerminalNode *>(parent->children[j]) == nullptr) adjacent = false;
            }
            if (adjacent) SysMLv2::Files::beginMemberWithVisibility(MemberMarks, ctx, importVisibility(prefix->visibility_indicator()), ParentStack.top());
        }
    }
}

void KerMLListenerImplementation::exitEveryRule(antlr4::ParserRuleContext *ctx) {
    if (MemberMarks.empty() || ctx == nullptr) return;
    SysMLv2::Files::endMember(MemberMarks, ctx, ParentStack.empty() ? nullptr : ParentStack.top(), OwnershipKinds, &Recorder.data.visibility);
}

std::vector<std::shared_ptr<KerML::Entities::Element>> KerMLListenerImplementation::getElements() {
    return Elements;
}

void KerMLListenerImplementation::applyIdentification(KerMLParser::IdentificationContext *idCtx, const std::shared_ptr<KerML::Entities::Element>& elem) {
    if (!idCtx || !elem) return;
    auto names = idCtx->NAME();
    if (names.empty()) return;
    if (idCtx->SYMBOL_SMALLER() != nullptr && names.size() >= 2) {
        elem->setDeclaredShortName(names[0]->getText());
        elem->setDeclaredName(names[1]->getText());
    } else if (idCtx->SYMBOL_SMALLER() != nullptr && names.size() == 1) {
        elem->setDeclaredShortName(names[0]->getText());
    } else {
        elem->setDeclaredName(names[0]->getText());
    }
}

std::shared_ptr<KerML::Entities::Type> KerMLListenerImplementation::typeReference(const std::string& name,
    const std::shared_ptr<KerML::Entities::Element>& context, bool relativeToOwner, antlr4::ParserRuleContext *position,
    std::function<void(const std::shared_ptr<KerML::Entities::Type>&)> patch) {
    return Recorder.reference<KerML::Entities::Type>(name, ReferenceKind::Type, ReferenceRole::Plain, context, relativeToOwner, nullptr,
                                                      position, std::move(patch));
}

std::shared_ptr<KerML::Entities::Feature> KerMLListenerImplementation::featureReference(const std::string& name,
    const std::shared_ptr<KerML::Entities::Element>& context, bool relativeToOwner, antlr4::ParserRuleContext *position,
    std::function<void(const std::shared_ptr<KerML::Entities::Feature>&)> patch) {
    return Recorder.reference<KerML::Entities::Feature>(name, ReferenceKind::Feature, ReferenceRole::Plain, context, relativeToOwner, nullptr,
                                                         position, std::move(patch));
}

KerML::Entities::VisibilityKind KerMLListenerImplementation::importVisibility(KerMLParser::Visibility_indicatorContext *indicator) const {
    if (indicator == nullptr) return KerML::Entities::PUBLIC;
    if (indicator->KEYWORD_PRIVATE() != nullptr) return KerML::Entities::PRIVATE;
    if (indicator->KEYWORD_PROTECTED() != nullptr) return KerML::Entities::PROTECTED;
    return KerML::Entities::PUBLIC;
}

void KerMLListenerImplementation::recordImport(const std::shared_ptr<KerML::Entities::Element>& importElement,
    antlr4::ParserRuleContext *importCtx, const std::string& target, bool star, bool recursive, bool importAll,
    KerML::Entities::VisibilityKind visibility, const std::shared_ptr<KerML::Entities::Membership>& importedMembership) {
    auto record = std::make_shared<SysMLv2::Files::ImportRecord>();
    record->owner = ParentStack.empty() ? nullptr : ParentStack.top();
    record->element = importElement;
    record->isImportAll = importAll;
    record->visibility = visibility;
    record->target = target;
    record->isRecursive = recursive;
    record->isMembershipImport = !star && !recursive;
    if (importCtx != nullptr && importCtx->getStart() != nullptr) {
        record->line = static_cast<int>(importCtx->getStart()->getLine());
        record->column = static_cast<int>(importCtx->getStart()->getCharPositionInLine());
    }
    Recorder.data.imports.push_back(record);

    const auto kind = record->isMembershipImport ? ReferenceKind::Element : ReferenceKind::Namespace;
    Recorder.record(newPlaceholder<KerML::Entities::Element>(ReferenceKind::Element, target), target, kind, ReferenceRole::Import,
        record->owner, false, nullptr, importCtx, [record, importedMembership](const ElementPtr& element) {
            record->resolvedTarget = element;
            if (auto namespaceImport = std::dynamic_pointer_cast<KerML::Entities::NamespaceImport>(record->element)) {
                if (auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(element)) namespaceImport->setImportedNamespace(ns);
            }
            if (importedMembership) importedMembership->setMemberElement(element);
        });
}

SysMLv2::Files::ResolutionData KerMLListenerImplementation::takeResolutionData() {
    return std::move(Recorder.data);
}


void KerMLListenerImplementation::attachExpression(const std::shared_ptr<KerML::Entities::Expression>& expression) {
    if (!expression) return;
    Elements.push_back(expression);
    if (ParentStack.empty()) return;
    expression->setOwner(ParentStack.top());
    ParentStack.top()->appendOwnedElement(expression);
    if (auto invocation = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
        invocation->appendArgument(expression);
    }
    if (auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top())) {
        value->setValue(expression);
    }
}

void KerMLListenerImplementation::finishOperatorExpression(const std::string& operatorName) {
    if (ParentStack.empty()) return;
    const auto expression = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(ParentStack.top());
    if (!expression) return;
    ParentStack.pop();
    expression->setOperatorName(operatorName);
    attachExpression(expression);
}


void KerMLListenerImplementation::finishMembership(KerMLParser::Member_prefixContext *prefix, bool owningOnly) {
    if (ParentStack.empty()) return;
    auto membership = std::dynamic_pointer_cast<KerML::Entities::OwningMembership>(ParentStack.top());
    if (!membership) return;
    ParentStack.pop();
    const auto children = membership->ownedElements();
    if (children.empty() || ParentStack.empty()) return;
    const auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top());
    if (!ns) return;
    const auto member = children.back();
    // A feature of a type is owned through a FeatureMembership, every other member through an OwningMembership.
    if (!owningOnly && std::dynamic_pointer_cast<KerML::Entities::Feature>(member) && std::dynamic_pointer_cast<KerML::Entities::Type>(ns))
        membership = std::make_shared<KerML::Entities::FeatureMembership>();
    membership->setOwnedMemberElement(member);
    membership->setMemberElement(member);
    if (member->declaredName()) membership->setMemberName(*member->declaredName());
    if (member->declaredShortName()) membership->setMemberShortName(*member->declaredShortName());
    membership->setMembershipOwningNamespace(ns);
    membership->setOwner(ns);
    membership->setVisibility(KerML::Entities::PUBLIC);
    if (prefix && prefix->visibility_indicator()) {
        auto visibility = prefix->visibility_indicator();
        membership->setVisibility(visibility->KEYWORD_PRIVATE() ? KerML::Entities::PRIVATE :
                                  visibility->KEYWORD_PROTECTED() ? KerML::Entities::PROTECTED : KerML::Entities::PUBLIC);
        if (membership->visibility() != KerML::Entities::PUBLIC) Recorder.data.visibility[member.get()] = membership->visibility();
        // The visibility keyword of an import is written in the prefix of the member that contains it.
        if (std::dynamic_pointer_cast<KerML::Entities::Import>(member) != nullptr) {
            for (auto it = Recorder.data.imports.rbegin(); it != Recorder.data.imports.rend(); ++it) {
                if ((*it)->element == member) {
                    (*it)->visibility = membership->visibility();
                    break;
                }
            }
        }
    }
    member->setOwner(ns);
    // The collections of the namespace (ownedMembership, ownedMember, ownedFeature, ...) are filled by buildOwnership.
    ns->appendOwnedElement(member);
    ns->appendOwnedElement(membership);
    Elements.push_back(membership);
}
