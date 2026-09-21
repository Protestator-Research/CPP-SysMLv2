//
// Created by Moritz Herzog on 09.05.25.
//

#include <kerml/parser/KerMlListenerImplementation.h>
#include <kerml/KerML.h>
#include <string>
#include <iostream>
#include <algorithm>



KerMLListenerImplementation::KerMLListenerImplementation() { }

KerMLListenerImplementation::~KerMLListenerImplementation() { }

void KerMLListenerImplementation::enterComment(KerMLParser::CommentContext *) { }

void KerMLListenerImplementation::exitComment(KerMLParser::CommentContext *context) {
    std::string identification="";
    if(context->identification() != nullptr) {
        identification =  context->identification()->getText();
    }

    std::vector<std::shared_ptr<KerML::Entities::Element>> annotatedElements;
    if(context->KEYWORD_ABOUT() != nullptr) {
        for(auto& about : context->annotation()) {
            std::cout << "\t" << about->getText() << std::endl;
            const auto& annotatedElement = findElementWithName(about->getText());

            if(annotatedElement != nullptr)
                annotatedElements.push_back(annotatedElement);
        }
    }
    std::string locale = "";
    if(context->KEYWORD_LOCALE() != nullptr) {
        locale = context->STRING_VALUE()->getText();
    }

    std::string body = context->REGULAR_COMMENT()->getText();

    const auto& comment = std::make_shared<KerML::Entities::Comment>(locale, body);
    Elements.push_back(comment);


    if(!identification.empty())
        comment->setDeclaredName(identification);

    if(!annotatedElements.empty())
        comment->appendAnnotatedElements(annotatedElements);
    else
        comment->appendAnnotatedElement(ParentStack.top());

    ParentStack.top()->appendOwnedElement(comment);
}

void KerMLListenerImplementation::enterStart(KerMLParser::StartContext *)
{
    const auto& rootNamespace = std::make_shared<KerML::Entities::Namespace>("Root Namespace");
    ParentStack.push(rootNamespace);
    Elements.push_back(rootNamespace);
    populateWithBaseDatatypes();
}

void KerMLListenerImplementation::exitStart(KerMLParser::StartContext *) { }

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
            auto elem = findElementWithName(q->getText());
            if (!elem) {
                elem = std::make_shared<KerML::Entities::Element>();
                elem->setDeclaredName(q->getText());
            }
            if (q->getStart()->getTokenIndex() < toIndex) {
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

void KerMLListenerImplementation::exitAnnotation(KerMLParser::AnnotationContext *) { }

void KerMLListenerImplementation::enterOwned_annotation(KerMLParser::Owned_annotationContext*) { }

void KerMLListenerImplementation::exitOwned_annotation(KerMLParser::Owned_annotationContext *) { }

void KerMLListenerImplementation::enterAnnotating_element(KerMLParser::Annotating_elementContext *) { }

void KerMLListenerImplementation::exitAnnotating_element(KerMLParser::Annotating_elementContext *) { }

void KerMLListenerImplementation::enterDocumentation(KerMLParser::DocumentationContext *) { }

void KerMLListenerImplementation::exitDocumentation(KerMLParser::DocumentationContext *context) {

    std::string identification = "";
    if(context->identification()!=nullptr) {
        identification = context->identification()->getText();
    }

    std::string locale = "";
    if(context->KEYWORD_LOCALE()!=nullptr) {
        locale = context->STRING_VALUE()->getText();
    }

    std::string body = context->REGULAR_COMMENT()->getText();

    auto documentation = std::make_shared<KerML::Entities::Documentation>(ParentStack.top(), locale, body);
    documentation->setDeclaredName(identification);

    ParentStack.top()->appendOwnedElement(documentation);
}

void KerMLListenerImplementation::enterTextual_representation(KerMLParser::Textual_representationContext *) { }

void KerMLListenerImplementation::exitTextual_representation(KerMLParser::Textual_representationContext *ctx) {
    std::string language;
    
    if (ctx->KEYWORD_LANGUAGE()!=nullptr)
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

void KerMLListenerImplementation::enterNon_feature_member(KerMLParser::Non_feature_memberContext *) { }

void KerMLListenerImplementation::exitNon_feature_member(KerMLParser::Non_feature_memberContext *) { }

void KerMLListenerImplementation::enterNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *) { }

void KerMLListenerImplementation::exitNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *) { }

void KerMLListenerImplementation::enterAlias_member(KerMLParser::Alias_memberContext *) { }

void KerMLListenerImplementation::exitAlias_member(KerMLParser::Alias_memberContext* ctx) {
    const auto element = findElementWithName(ctx->qualified_name()->getText());

    if ((ctx->SYMBOL_GREATER() != nullptr) && (ctx->SYMBOL_GREATER() != nullptr))
    {
        element->appendAliasId(ctx->NAME().front()->getText());

        if (ctx->NAME().size() > 1)
            element->appendAliasId(ctx->NAME().back()->getText());
    }
    else
    {
        if (!ctx->NAME().empty())
            element->appendAliasId(ctx->NAME().front()->getText());
    }
}

void KerMLListenerImplementation::enterQualified_name(KerMLParser::Qualified_nameContext *) { }

void KerMLListenerImplementation::exitQualified_name(KerMLParser::Qualified_nameContext *) { }

void KerMLListenerImplementation::enterNamespace_import(KerMLParser::Namespace_importContext *) {
    const auto namespaceImport = std::make_shared<KerML::Entities::NamespaceImport>();
    ParentStack.emplace(namespaceImport);
}

void KerMLListenerImplementation::exitNamespace_import(KerMLParser::Namespace_importContext *ctx) {
    const auto namespaceImport = std::dynamic_pointer_cast<KerML::Entities::NamespaceImport>(ParentStack.top());
    if(!namespaceImport) {
        std::cout << "Type on Parent Stack: " << ParentStack.top()->getType() << std::endl;
        std::cout<<"Wrong Parent Stack"<<std::endl;
        return;
    }
    ParentStack.pop();
    bool isAll = ctx->KEYWORD_ALL() != nullptr;

    if(ctx->KEYWORD_ALL())
        std::cout<<"\timport All from Namespace activated"<<std::endl;

    bool isRecursive = false;
    if(ctx->import_declaration()->membership_import())
        isRecursive = ctx->import_declaration()->membership_import()->SYMBOL_DOUBLE_STAR() != nullptr;

    if(ctx->relationship_body()->SYMBOL_STATEMENT_DELIMITER()== nullptr){
        std::cout<<"\t NammespaceNotClosed"<<std::endl;
    }
    const auto namespace_elem = std::make_shared<KerML::Entities::Namespace>(ctx->import_declaration()->getText(), true);
    namespaceImport->setIsRecursive(isRecursive);
    namespaceImport->setIsImportAll(isAll);
    if (!ParentStack.empty()) {
        namespaceImport->setImportOwningNamespace(std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top()));
    }
    namespaceImport->setImportedNamespace(namespace_elem);

    Elements.push_back(namespaceImport);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(namespaceImport);
    }

    if (ctx->import_declaration() && ctx->import_declaration()->membership_import() &&
        ctx->import_declaration()->membership_import()->SYMBOL_STAR() == nullptr &&
        ctx->import_declaration()->membership_import()->SYMBOL_DOUBLE_STAR() == nullptr) {
        const auto memImport = std::make_shared<KerML::Entities::MembershipImport>();
        memImport->setIsRecursive(false);
        memImport->setIsImportAll(isAll);
        if (!ParentStack.empty()) {
            if (auto owningNs = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top())) {
                memImport->setImportOwningNamespace(owningNs);
                owningNs->appendOwnedElement(memImport);
            }
        }
        if (ctx->import_declaration()->membership_import()->qualified_name()) {
            const auto mem = std::make_shared<KerML::Entities::Membership>();
            mem->setMemberName(ctx->import_declaration()->membership_import()->qualified_name()->getText());
            memImport->setImportedMembership(mem);
        }
        Elements.push_back(memImport);
    }
}

void KerMLListenerImplementation::enterImport_declaration(KerMLParser::Import_declarationContext *) { }

void KerMLListenerImplementation::exitImport_declaration(KerMLParser::Import_declarationContext *) { }

void KerMLListenerImplementation::enterMembership_import(KerMLParser::Membership_importContext *) { }

void KerMLListenerImplementation::exitMembership_import(KerMLParser::Membership_importContext *ctx) {
    if (!ctx) return;
    if (ctx->SYMBOL_STAR() == nullptr && ctx->SYMBOL_DOUBLE_STAR() == nullptr && ctx->qualified_name()) {
        const auto memImport = std::make_shared<KerML::Entities::MembershipImport>();
        const auto mem = std::make_shared<KerML::Entities::Membership>();
        mem->setMemberName(ctx->qualified_name()->getText());
        memImport->setImportedMembership(mem);
        if (!ParentStack.empty()) {
            if (auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top())) {
                memImport->setImportOwningNamespace(ns);
                ns->appendOwnedElement(memImport);
            }
        }
        Elements.push_back(memImport);
    }
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

void KerMLListenerImplementation::exitType_prefix(KerMLParser::Type_prefixContext *) { }

void KerMLListenerImplementation::enterType_declaration(KerMLParser::Type_declarationContext *) { }

void KerMLListenerImplementation::exitType_declaration(KerMLParser::Type_declarationContext *ctx) {
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type)
    {
        std::cout << "Error wrong type in Parentstack" << std::endl;
        return;
    }
    
    type->setDeclaredName(ctx->identification()->getText());
    if (ctx->KEYWORD_ALL() != nullptr)
    {
    }
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
        const auto generalType = findOrCreateType(ctx->owned_specialization()[i]->general_type()->getText());
        const auto specialization = std::make_shared<KerML::Entities::Specialization>(generalType, type);
    	type->appendOwnedSpecialization(specialization);
        type->appendOwnedElement(specialization);
        Elements.push_back(specialization);
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
        const auto origType = findOrCreateType(ctx->owned_conjugation()->qualified_name()->getText());
        const auto conjugation = std::make_shared<KerML::Entities::Conjugation>(origType, type);
        type->setConjugation(conjugation);
        type->appendOwnedElement(conjugation);
        Elements.push_back(conjugation);
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
            const auto disjoiningType = findOrCreateType(elem->qualified_name()->getText());
            const auto disjoining = std::make_shared<KerML::Entities::Disjoining>(type, disjoiningType);
            type->appendOwnedDisjoining(disjoining);
            type->appendOwnedElement(disjoining);
            Elements.push_back(disjoining);
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
            const auto uType = findOrCreateType(elem->qualified_name()->getText());
            const auto unioning = std::make_shared<KerML::Entities::Unioning>(type, uType);
            type->appendOwnedUnioning(unioning);
            type->appendOwnedElement(unioning);
            Elements.push_back(unioning);
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
            const auto iType = findOrCreateType(elem->qualified_name()->getText());
            const auto intersecting = std::make_shared<KerML::Entities::Intersecting>(type, iType);
            type->appendOwnedIntersecting(intersecting);
            type->appendOwnedElement(intersecting);
            Elements.push_back(intersecting);
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
            const auto dType = findOrCreateType(elem->qualified_name()->getText());
            const auto differencing = std::make_shared<KerML::Entities::Differencing>(type, dType);
            type->appendOwnedDifferencing(differencing);
            type->appendOwnedElement(differencing);
            Elements.push_back(differencing);
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
    const auto generalType = std::dynamic_pointer_cast<KerML::Entities::Type>(findElementWithName(ctx->general_type()->getText()));
    const auto specializedType = std::dynamic_pointer_cast<KerML::Entities::Type>(findElementWithName(ctx->specific_type()->getText()));
    const auto specialization = std::make_shared<KerML::Entities::Specialization>(generalType, specializedType);

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
    const auto orig = findOrCreateType(ctx->qualified_name(0)->getText());
    const auto conj = findOrCreateType(ctx->qualified_name(1)->getText());
    const auto conjugation = std::make_shared<KerML::Entities::Conjugation>(orig, conj);
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
    const auto t1 = findOrCreateType(ctx->qualified_name(0)->getText());
    const auto t2 = findOrCreateType(ctx->qualified_name(1)->getText());
    const auto disjoining = std::make_shared<KerML::Entities::Disjoining>(t1, t2);
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

}

void KerMLListenerImplementation::exitType_feature_member(KerMLParser::Type_feature_memberContext *) {

}

void KerMLListenerImplementation::enterOwned_feature_member(KerMLParser::Owned_feature_memberContext *) {

}

void KerMLListenerImplementation::exitOwned_feature_member(KerMLParser::Owned_feature_memberContext *) {

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
            const auto superClassifier = findOrCreateClassifier(superName);
            const auto subclassification = std::make_shared<KerML::Entities::Subclassification>(superClassifier, classifier);
            classifier->appendOwnedSubclassification(subclassification);
            classifier->appendOwnedSpecialization(subclassification);
            classifier->appendOwnedElement(subclassification);
            Elements.push_back(subclassification);
        }
        return;
    }
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (type) {
        for (const auto& elem : ctx->owned_subclassification()) {
            std::string superName = elem->qualified_name() ? elem->qualified_name()->getText() : elem->getText();
            const auto generalType = findOrCreateType(superName);
            const auto specialization = std::make_shared<KerML::Entities::Specialization>(generalType, type);
            type->appendOwnedSpecialization(specialization);
            type->appendOwnedElement(specialization);
            Elements.push_back(specialization);
        }
    }
}

void KerMLListenerImplementation::enterSubclassification(KerMLParser::SubclassificationContext *) { }

void KerMLListenerImplementation::exitSubclassification(KerMLParser::SubclassificationContext *ctx) {
    if (!ctx || ctx->qualified_name().size() < 2) return;

    const std::string subName = ctx->qualified_name(0)->getText();
    const std::string superName = ctx->qualified_name(1)->getText();

    const auto subClassifier = findOrCreateClassifier(subName);
    const auto superClassifier = findOrCreateClassifier(superName);

    const auto subclassification = std::make_shared<KerML::Entities::Subclassification>(superClassifier, subClassifier);

    if (ctx->identification() != nullptr) {
        subclassification->setDeclaredName(ctx->identification()->getText());
    }

    subClassifier->appendOwnedSubclassification(subclassification);
    subClassifier->appendOwnedSpecialization(subclassification);
    subClassifier->appendOwnedElement(subclassification);

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

void KerMLListenerImplementation::enterFeature_prefix(KerMLParser::Feature_prefixContext *) { }

void KerMLListenerImplementation::exitFeature_prefix(KerMLParser::Feature_prefixContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) {
        return;
    }
    feature->setAbstract(ctx->KEYWORD_ABSTRACT() != nullptr);
    feature->setIsVariable(ctx->KEYWORD_VAR() != nullptr);
    feature->setIsComposite(ctx->KEYWORD_COMPOSITE() != nullptr);
    feature->setIsPortion(ctx->KEYWORD_PORTION() != nullptr);
    feature->setIsEnd(ctx->KEYWORD_END() != nullptr);
    feature->setIsDerived(ctx->KEYWORD_DERIVED() != nullptr);
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
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) {
        return;
    }
    feature->setIsUnique(ctx->KEYWORD_ALL() != nullptr);
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

void KerMLListenerImplementation::exitMultiplicity_part(KerMLParser::Multiplicity_partContext *) {

}

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
    const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(findElementWithName(ctx->general_type()->qualified_name()->getText()));
    feature_typing->setType(type);
}

void KerMLListenerImplementation::enterOwned_feature_typing(KerMLParser::Owned_feature_typingContext *) { }

void KerMLListenerImplementation::exitOwned_feature_typing(KerMLParser::Owned_feature_typingContext *ctx) {
    if (ParentStack.empty()) return;
    if (const auto instExpr = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
        if (ctx && ctx->general_type()) {
            std::string typeName = ctx->general_type()->getText();
            const auto type = findOrCreateType(typeName);
            instExpr->setInstantiatedType(type);
        }
        return;
    }
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature || !ctx || !ctx->general_type()) return;

    std::string typeName = ctx->general_type()->getText();
    const auto type = findOrCreateType(typeName);
    const auto featureTyping = std::make_shared<KerML::Entities::FeatureTyping>(type, feature);
    feature->appendOwnedTyping(featureTyping);
    feature->appendType(type);
    feature->appendOwnedElement(featureTyping);
    Elements.push_back(featureTyping);
}

void KerMLListenerImplementation::enterSubsetting(KerMLParser::SubsettingContext *) { }

void KerMLListenerImplementation::exitSubsetting(KerMLParser::SubsettingContext *) { }

void KerMLListenerImplementation::enterOwned_subsetting(KerMLParser::Owned_subsettingContext *) { }

void KerMLListenerImplementation::exitOwned_subsetting(KerMLParser::Owned_subsettingContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature || !ctx || !ctx->general_type()) return;

    std::string subsettedName = ctx->general_type()->getText();
    const auto subsetted = findOrCreateFeature(subsettedName);
    const auto subsetting = std::make_shared<KerML::Entities::Subsetting>(subsetted, feature);
    feature->appendOwnedSubsetting(subsetting);
    feature->appendOwnedElement(subsetting);
    Elements.push_back(subsetting);
}

void KerMLListenerImplementation::enterOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *) { }

void KerMLListenerImplementation::exitOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature || !ctx || !ctx->general_type()) return;

    std::string refName = ctx->general_type()->getText();
    const auto referenced = findOrCreateFeature(refName);
    const auto refSubsetting = std::make_shared<KerML::Entities::ReferenceSubsetting>(referenced, feature);
    feature->setOwnedReferenceSubsetting(refSubsetting);
    feature->appendOwnedElement(refSubsetting);
    Elements.push_back(refSubsetting);
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
        const auto redefined = findOrCreateFeature(redefName);
        const auto redefinition = std::make_shared<KerML::Entities::Redefinition>(redefined, feature);
        feature->appendOwnedRedefinition(redefinition);
        feature->appendOwnedElement(redefinition);
        Elements.push_back(redefinition);
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
    const auto redefined = findOrCreateFeature(redefName);
    const auto redefinition = std::make_shared<KerML::Entities::Redefinition>(redefined, feature);
    feature->appendOwnedRedefinition(redefinition);
    feature->appendOwnedElement(redefinition);
    Elements.push_back(redefinition);
}

void KerMLListenerImplementation::enterOwned_feature_chain(KerMLParser::Owned_feature_chainContext *) {

}

void KerMLListenerImplementation::exitOwned_feature_chain(KerMLParser::Owned_feature_chainContext *) {

}

void KerMLListenerImplementation::enterFeature_chain(KerMLParser::Feature_chainContext *) {

}

void KerMLListenerImplementation::exitFeature_chain(KerMLParser::Feature_chainContext *) {

}

void KerMLListenerImplementation::enterOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *) { }

void KerMLListenerImplementation::exitOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *ctx) {
    if (ParentStack.empty()) return;
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) {
        std::cout << "Wrong Type in parent stack." << std::endl;
        return;
    }
    if (ctx && ctx->qualified_name()) {
        const auto name = ctx->qualified_name()->getText();
        feature->appendChainingFeature(std::dynamic_pointer_cast<KerML::Entities::Feature>(findElementWithName(name)));
    }
}

void KerMLListenerImplementation::enterFeature_inverting(KerMLParser::Feature_invertingContext *) {

}

void KerMLListenerImplementation::exitFeature_inverting(KerMLParser::Feature_invertingContext *) {

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
        const auto invertedFeature = findElementWithName(ctx->qualified_name()->getText());
        const auto featureInverting = std::make_shared<KerML::Entities::FeatureInverting>(std::dynamic_pointer_cast<KerML::Entities::Feature>(invertedFeature),feature);
        feature->appendOwnedElement(featureInverting);
        feature->appendOwnedFeatureInverting(featureInverting);
        Elements.push_back(featureInverting);
    }
}

void KerMLListenerImplementation::enterType_featuring(KerMLParser::Type_featuringContext *) {

}

void KerMLListenerImplementation::exitType_featuring(KerMLParser::Type_featuringContext *) {

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
        const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(findElementWithName(ctx->qualified_name()->getText()));

        const auto featureTyping = std::make_shared<KerML::Entities::TypeFeaturing>(type, feature);
        feature->appendOwnedTypeFeaturing(featureTyping);
        Elements.push_back(featureTyping);
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

    if (ctx && ctx->type_prefix() && ctx->type_prefix()->KEYWORD_ABSTRACT() != nullptr) {
        conn->setAbstract(true);
    }
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

void
KerMLListenerImplementation::exitBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *) {

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
            conn->appendOwnedFeature(endFeature);
            const auto efm = std::make_shared<KerML::Entities::EndFeatureMembership>(endFeature, conn, std::vector<std::shared_ptr<KerML::Entities::Type>>{});
            efm->setMembershipOwningNamespace(conn);
            conn->appendOwnedFeatureMembership(efm);
            conn->appendFeatureMemberships(efm);
            conn->appendOwnedElement(efm);
            Elements.push_back(efm);
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

void KerMLListenerImplementation::exitSuccession_declaration(KerMLParser::Succession_declarationContext *) {

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

void KerMLListenerImplementation::enterOwned_expressions(KerMLParser::Owned_expressionsContext *) {

}

void KerMLListenerImplementation::exitOwned_expressions(KerMLParser::Owned_expressionsContext *) {

}

void KerMLListenerImplementation::enterOwned_expression(KerMLParser::Owned_expressionContext *) {

}

void KerMLListenerImplementation::exitOwned_expression(KerMLParser::Owned_expressionContext *) {

}

void KerMLListenerImplementation::enterEased_owned_expression(KerMLParser::Eased_owned_expressionContext *) {

}

void KerMLListenerImplementation::exitEased_owned_expression(KerMLParser::Eased_owned_expressionContext *) {

}

void KerMLListenerImplementation::enterConditional_expression(KerMLParser::Conditional_expressionContext *) {

}

void KerMLListenerImplementation::exitConditional_expression(KerMLParser::Conditional_expressionContext *) {

}

void KerMLListenerImplementation::enterConditional_binary_operator_expression(
        KerMLParser::Conditional_binary_operator_expressionContext *) {

}

void KerMLListenerImplementation::exitConditional_binary_operator_expression(
        KerMLParser::Conditional_binary_operator_expressionContext *) {

}

void
KerMLListenerImplementation::enterConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext *) {

}

void
KerMLListenerImplementation::exitConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext *) {

}

void KerMLListenerImplementation::enterBinary_operator_expression(KerMLParser::Binary_operator_expressionContext *) {
    const auto opExpr = std::make_shared<KerML::Entities::OperatorExpression>();
    ParentStack.push(opExpr);
}

void KerMLListenerImplementation::exitBinary_operator_expression(KerMLParser::Binary_operator_expressionContext *ctx) {
    if (ParentStack.empty()) return;
    const auto opExpr = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(ParentStack.top());
    if (!opExpr) return;
    ParentStack.pop();

    if (ctx && ctx->binary_operator()) {
        opExpr->setOperatorName(ctx->binary_operator()->getText());
    }
    Elements.push_back(opExpr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(opExpr);
        if (auto parentInst = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
            parentInst->appendArgument(opExpr);
        }
    }
}

void KerMLListenerImplementation::enterBinary_operator(KerMLParser::Binary_operatorContext *) {

}

void KerMLListenerImplementation::exitBinary_operator(KerMLParser::Binary_operatorContext *) {

}

void KerMLListenerImplementation::enterUnary_operator_expression(KerMLParser::Unary_operator_expressionContext *) {
    const auto opExpr = std::make_shared<KerML::Entities::OperatorExpression>();
    ParentStack.push(opExpr);
}

void KerMLListenerImplementation::exitUnary_operator_expression(KerMLParser::Unary_operator_expressionContext *ctx) {
    if (ParentStack.empty()) return;
    const auto opExpr = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(ParentStack.top());
    if (!opExpr) return;
    ParentStack.pop();

    if (ctx && ctx->unary_operator()) {
        opExpr->setOperatorName(ctx->unary_operator()->getText());
    }
    Elements.push_back(opExpr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(opExpr);
        if (auto parentInst = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
            parentInst->appendArgument(opExpr);
        }
    }
}

void KerMLListenerImplementation::enterUnary_operator(KerMLParser::Unary_operatorContext *) {

}

void KerMLListenerImplementation::exitUnary_operator(KerMLParser::Unary_operatorContext *) {

}

void KerMLListenerImplementation::enterClassification_expression(KerMLParser::Classification_expressionContext *) {

}

void KerMLListenerImplementation::exitClassification_expression(KerMLParser::Classification_expressionContext *) {

}

void KerMLListenerImplementation::enterClassification(KerMLParser::ClassificationContext *) {

}

void KerMLListenerImplementation::exitClassification(KerMLParser::ClassificationContext *) {

}

void
KerMLListenerImplementation::enterClassification_test_operator(KerMLParser::Classification_test_operatorContext *) {

}

void
KerMLListenerImplementation::exitClassification_test_operator(KerMLParser::Classification_test_operatorContext *) {

}

void KerMLListenerImplementation::enterCast_operator(KerMLParser::Cast_operatorContext *) {

}

void KerMLListenerImplementation::exitCast_operator(KerMLParser::Cast_operatorContext *) {

}

void KerMLListenerImplementation::enterMetaclassification_expression(
        KerMLParser::Metaclassification_expressionContext *) {

}

void
KerMLListenerImplementation::exitMetaclassification_expression(KerMLParser::Metaclassification_expressionContext *) {

}

void KerMLListenerImplementation::enterArgument_member(KerMLParser::Argument_memberContext *) {

}

void KerMLListenerImplementation::exitArgument_member(KerMLParser::Argument_memberContext *) {

}

void KerMLListenerImplementation::enterArgument(KerMLParser::ArgumentContext *) {

}

void KerMLListenerImplementation::exitArgument(KerMLParser::ArgumentContext *) {

}

void KerMLListenerImplementation::enterArgument_value(KerMLParser::Argument_valueContext *) {

}

void KerMLListenerImplementation::exitArgument_value(KerMLParser::Argument_valueContext *) {

}

void KerMLListenerImplementation::enterArgument_expression_member(KerMLParser::Argument_expression_memberContext *) {

}

void KerMLListenerImplementation::exitArgument_expression_member(KerMLParser::Argument_expression_memberContext *) {

}

void KerMLListenerImplementation::enterArgument_expression(KerMLParser::Argument_expressionContext *) {

}

void KerMLListenerImplementation::exitArgument_expression(KerMLParser::Argument_expressionContext *) {

}

void KerMLListenerImplementation::enterArgument_expression_value(KerMLParser::Argument_expression_valueContext *) {

}

void KerMLListenerImplementation::exitArgument_expression_value(KerMLParser::Argument_expression_valueContext *) {

}

void KerMLListenerImplementation::enterMetadata_argument_member(KerMLParser::Metadata_argument_memberContext *) {

}

void KerMLListenerImplementation::exitMetadata_argument_member(KerMLParser::Metadata_argument_memberContext *) {

}

void KerMLListenerImplementation::enterMetadata_argument(KerMLParser::Metadata_argumentContext *) {

}

void KerMLListenerImplementation::exitMetadata_argument(KerMLParser::Metadata_argumentContext *) {

}

void KerMLListenerImplementation::enterMetadata_value(KerMLParser::Metadata_valueContext *) {

}

void KerMLListenerImplementation::exitMetadata_value(KerMLParser::Metadata_valueContext *) {

}

void KerMLListenerImplementation::enterMetadata_reference(KerMLParser::Metadata_referenceContext *) {

}

void KerMLListenerImplementation::exitMetadata_reference(KerMLParser::Metadata_referenceContext *) {

}

void KerMLListenerImplementation::enterMetadataclassification_test_operator(
        KerMLParser::Metadataclassification_test_operatorContext *) {

}

void KerMLListenerImplementation::exitMetadataclassification_test_operator(
        KerMLParser::Metadataclassification_test_operatorContext *) {

}

void KerMLListenerImplementation::enterMeta_cast_operator(KerMLParser::Meta_cast_operatorContext *) {

}

void KerMLListenerImplementation::exitMeta_cast_operator(KerMLParser::Meta_cast_operatorContext *) {

}

void KerMLListenerImplementation::enterExtend_expression(KerMLParser::Extend_expressionContext *) {

}

void KerMLListenerImplementation::exitExtend_expression(KerMLParser::Extend_expressionContext *) {

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

void KerMLListenerImplementation::exitType_reference(KerMLParser::Type_referenceContext *) {

}

void KerMLListenerImplementation::enterReference_typing(KerMLParser::Reference_typingContext *) {

}

void KerMLListenerImplementation::exitReference_typing(KerMLParser::Reference_typingContext *) {

}

void KerMLListenerImplementation::enterPrimary_expressions(KerMLParser::Primary_expressionsContext *) {

}

void KerMLListenerImplementation::exitPrimary_expressions(KerMLParser::Primary_expressionsContext *) {

}

void KerMLListenerImplementation::enterPrimary_expression(KerMLParser::Primary_expressionContext *) {

}

void KerMLListenerImplementation::exitPrimary_expression(KerMLParser::Primary_expressionContext *) {

}

void KerMLListenerImplementation::enterPrimary_argument_value(KerMLParser::Primary_argument_valueContext *) {

}

void KerMLListenerImplementation::exitPrimary_argument_value(KerMLParser::Primary_argument_valueContext *) {

}

void KerMLListenerImplementation::enterPrimary_argument(KerMLParser::Primary_argumentContext *) {

}

void KerMLListenerImplementation::exitPrimary_argument(KerMLParser::Primary_argumentContext *) {

}

void KerMLListenerImplementation::enterPrimary_argument_member(KerMLParser::Primary_argument_memberContext *) {

}

void KerMLListenerImplementation::exitPrimary_argument_member(KerMLParser::Primary_argument_memberContext *) {

}

void KerMLListenerImplementation::enterNon_feature_chain_primary_expression(
        KerMLParser::Non_feature_chain_primary_expressionContext *) {

}

void KerMLListenerImplementation::exitNon_feature_chain_primary_expression(
        KerMLParser::Non_feature_chain_primary_expressionContext *) {

}

void KerMLListenerImplementation::enterNon_feature_chain_primary_argument_value(
        KerMLParser::Non_feature_chain_primary_argument_valueContext *) {

}

void KerMLListenerImplementation::exitNon_feature_chain_primary_argument_value(
        KerMLParser::Non_feature_chain_primary_argument_valueContext *) {

}

void KerMLListenerImplementation::enterNon_feature_chain_primary_argument(
        KerMLParser::Non_feature_chain_primary_argumentContext *) {

}

void KerMLListenerImplementation::exitNon_feature_chain_primary_argument(
        KerMLParser::Non_feature_chain_primary_argumentContext *) {

}

void KerMLListenerImplementation::enterNon_feature_chain_primary_argument_member(
        KerMLParser::Non_feature_chain_primary_argument_memberContext *) {

}

void KerMLListenerImplementation::exitNon_feature_chain_primary_argument_member(
        KerMLParser::Non_feature_chain_primary_argument_memberContext *) {

}

void KerMLListenerImplementation::enterBracket_expression(KerMLParser::Bracket_expressionContext *) {

}

void KerMLListenerImplementation::exitBracket_expression(KerMLParser::Bracket_expressionContext *) {

}

void KerMLListenerImplementation::enterIndex_expression(KerMLParser::Index_expressionContext *) {
    const auto expr = std::make_shared<KerML::Entities::IndexExpression>();
    ParentStack.push(expr);
}

void KerMLListenerImplementation::exitIndex_expression(KerMLParser::Index_expressionContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::IndexExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();

    expr->setOperatorName("#");
    Elements.push_back(expr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(expr);
        if (auto parentInst = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
            parentInst->appendArgument(expr);
        }
    }
}

void KerMLListenerImplementation::enterSequence_expression(KerMLParser::Sequence_expressionContext *) {

}

void KerMLListenerImplementation::exitSequence_expression(KerMLParser::Sequence_expressionContext *) {

}

void KerMLListenerImplementation::enterSequence_expression_list(KerMLParser::Sequence_expression_listContext *) {

}

void KerMLListenerImplementation::exitSequence_expression_list(KerMLParser::Sequence_expression_listContext *) {

}

void
KerMLListenerImplementation::enterSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *) {

}

void
KerMLListenerImplementation::exitSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *) {

}

void KerMLListenerImplementation::enterSequence_expression_list_member(
        KerMLParser::Sequence_expression_list_memberContext *) {

}

void KerMLListenerImplementation::exitSequence_expression_list_member(
        KerMLParser::Sequence_expression_list_memberContext *) {

}

void KerMLListenerImplementation::enterFeature_chain_expression(KerMLParser::Feature_chain_expressionContext *) {
    const auto expr = std::make_shared<KerML::Entities::FeatureChainExpression>();
    ParentStack.push(expr);
}

void KerMLListenerImplementation::exitFeature_chain_expression(KerMLParser::Feature_chain_expressionContext *ctx) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::FeatureChainExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();

    expr->setOperatorName(".");
    if (ctx && ctx->feature_chain_member()) {
        std::string name = ctx->feature_chain_member()->getText();
        auto feat = findOrCreateFeature(name);
        expr->setTargetFeature(feat);
    }
    Elements.push_back(expr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(expr);
        if (auto parentInst = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
            parentInst->appendArgument(expr);
        }
    }
}

void KerMLListenerImplementation::enterCollect_expression(KerMLParser::Collect_expressionContext *) {
    const auto expr = std::make_shared<KerML::Entities::CollectExpression>();
    ParentStack.push(expr);
}

void KerMLListenerImplementation::exitCollect_expression(KerMLParser::Collect_expressionContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::CollectExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();

    expr->setOperatorName(".");
    Elements.push_back(expr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(expr);
        if (auto parentInst = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
            parentInst->appendArgument(expr);
        }
    }
}

void KerMLListenerImplementation::enterSelect_expression(KerMLParser::Select_expressionContext *) {
    const auto expr = std::make_shared<KerML::Entities::SelectExpression>();
    ParentStack.push(expr);
}

void KerMLListenerImplementation::exitSelect_expression(KerMLParser::Select_expressionContext *) {
    if (ParentStack.empty()) return;
    const auto expr = std::dynamic_pointer_cast<KerML::Entities::SelectExpression>(ParentStack.top());
    if (!expr) return;
    ParentStack.pop();

    expr->setOperatorName(".?");
    Elements.push_back(expr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(expr);
        if (auto parentInst = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
            parentInst->appendArgument(expr);
        }
    }
}

void KerMLListenerImplementation::enterFunction_operation_expression(
        KerMLParser::Function_operation_expressionContext *) {

}

void
KerMLListenerImplementation::exitFunction_operation_expression(KerMLParser::Function_operation_expressionContext *) {

}

void KerMLListenerImplementation::enterBody_argument_member(KerMLParser::Body_argument_memberContext *) {

}

void KerMLListenerImplementation::exitBody_argument_member(KerMLParser::Body_argument_memberContext *) {

}

void KerMLListenerImplementation::enterBody_argument(KerMLParser::Body_argumentContext *) {

}

void KerMLListenerImplementation::exitBody_argument(KerMLParser::Body_argumentContext *) {

}

void KerMLListenerImplementation::enterBody_argument_value(KerMLParser::Body_argument_valueContext *) {

}

void KerMLListenerImplementation::exitBody_argument_value(KerMLParser::Body_argument_valueContext *) {

}

void KerMLListenerImplementation::enterBody_expression_member(KerMLParser::Body_expression_memberContext *) {

}

void KerMLListenerImplementation::exitBody_expression_member(KerMLParser::Body_expression_memberContext *) {

}

void KerMLListenerImplementation::enterFunction_reference_argument_member(
        KerMLParser::Function_reference_argument_memberContext *) {

}

void KerMLListenerImplementation::exitFunction_reference_argument_member(
        KerMLParser::Function_reference_argument_memberContext *) {

}

void
KerMLListenerImplementation::enterFunction_reference_argument(KerMLParser::Function_reference_argumentContext *) {

}

void
KerMLListenerImplementation::exitFunction_reference_argument(KerMLParser::Function_reference_argumentContext *) {

}

void KerMLListenerImplementation::enterFunction_reference_arugment_value(
        KerMLParser::Function_reference_arugment_valueContext *) {

}

void KerMLListenerImplementation::exitFunction_reference_arugment_value(
        KerMLParser::Function_reference_arugment_valueContext *) {

}

void KerMLListenerImplementation::enterFunction_reference_expression(
        KerMLParser::Function_reference_expressionContext *) {

}

void
KerMLListenerImplementation::exitFunction_reference_expression(KerMLParser::Function_reference_expressionContext *) {

}

void KerMLListenerImplementation::enterFunction_reference_member(KerMLParser::Function_reference_memberContext *) {

}

void KerMLListenerImplementation::exitFunction_reference_member(KerMLParser::Function_reference_memberContext *) {

}

void KerMLListenerImplementation::enterFunction_reference(KerMLParser::Function_referenceContext *) {

}

void KerMLListenerImplementation::exitFunction_reference(KerMLParser::Function_referenceContext *) {

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

    Elements.push_back(expr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(expr);
    }
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
        auto feat = findOrCreateFeature(refName);
        expr->setReferent(feat);
    }
    Elements.push_back(expr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(expr);
        if (auto parentInst = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
            parentInst->appendArgument(expr);
        }
    }
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
        auto elem = findElementWithName(refName);
        expr->setReferencedElement(elem);
    }
    Elements.push_back(expr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(expr);
        if (auto parentInst = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
            parentInst->appendArgument(expr);
        }
    }
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

    Elements.push_back(expr);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(expr);
        if (auto parentInst = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
            parentInst->appendArgument(expr);
        }
    }
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

}

void KerMLListenerImplementation::exitNamed_argument(KerMLParser::Named_argumentContext *) {

}

void KerMLListenerImplementation::enterParameter_redefinition(KerMLParser::Parameter_redefinitionContext *) {

}

void KerMLListenerImplementation::exitParameter_redefinition(KerMLParser::Parameter_redefinitionContext *) {

}

void KerMLListenerImplementation::enterBody_expression(KerMLParser::Body_expressionContext *) {

}

void KerMLListenerImplementation::exitBody_expression(KerMLParser::Body_expressionContext *) {

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
        Elements.push_back(literal);
        if (!ParentStack.empty()) {
            ParentStack.top()->appendOwnedElement(literal);
            if (auto fv = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top())) {
                fv->setValue(literal);
            }
        }
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

void KerMLListenerImplementation::exitItem_flow_declaration(KerMLParser::Item_flow_declarationContext *) {

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

void KerMLListenerImplementation::exitItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *) {

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

}

void KerMLListenerImplementation::exitMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *) {

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
        if (ctx->SPECIALIZES() != nullptr && !ctx->NAME().empty()) {
            std::string superName = ctx->NAME().back()->getText();
            auto superClassifier = findOrCreateClassifier(superName);
            auto subclassification = std::make_shared<KerML::Entities::Subclassification>(superClassifier, metaclass);
            metaclass->appendOwnedSubclassification(subclassification);
            metaclass->appendOwnedSpecialization(subclassification);
            metaclass->appendOwnedElement(subclassification);
            Elements.push_back(subclassification);
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

}

void KerMLListenerImplementation::exitMetadata_body_feature(KerMLParser::Metadata_body_featureContext *) {

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

}

void KerMLListenerImplementation::exitElement_filter_member(KerMLParser::Element_filter_memberContext *) {

}

void KerMLListenerImplementation::enterMeta_assignment(KerMLParser::Meta_assignmentContext *) {

}

void KerMLListenerImplementation::exitMeta_assignment(KerMLParser::Meta_assignmentContext *) {

}

void KerMLListenerImplementation::visitTerminal(antlr4::tree::TerminalNode *) {

}

void KerMLListenerImplementation::visitErrorNode(antlr4::tree::ErrorNode *) {

}

void KerMLListenerImplementation::enterEveryRule(antlr4::ParserRuleContext *) {

}

void KerMLListenerImplementation::exitEveryRule(antlr4::ParserRuleContext *) {

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

std::shared_ptr<KerML::Entities::Element> KerMLListenerImplementation::findElementWithName(std::string identification) {
    for (const auto &element: Elements) {
        if (element && element->declaredName() == identification)
            return element;
    }
    auto lastColon = identification.rfind("::");
    if (lastColon != std::string::npos) {
        std::string simpleName = identification.substr(lastColon + 2);
        for (const auto &element: Elements) {
            if (element && element->declaredName() == simpleName)
                return element;
        }
    }
    return nullptr;
}

std::shared_ptr<KerML::Entities::Type> KerMLListenerImplementation::findOrCreateType(const std::string& name) {
    auto elem = findElementWithName(name);
    if (elem) {
        if (auto t = std::dynamic_pointer_cast<KerML::Entities::Type>(elem)) {
            return t;
        }
    }
    auto placeholder = std::make_shared<KerML::Entities::Type>();
    auto lastColon = name.rfind("::");
    std::string declName = (lastColon != std::string::npos) ? name.substr(lastColon + 2) : name;
    placeholder->setDeclaredName(declName);
    Elements.push_back(placeholder);
    return placeholder;
}

std::shared_ptr<KerML::Entities::Classifier> KerMLListenerImplementation::findOrCreateClassifier(const std::string& name) {
    auto elem = findElementWithName(name);
    if (elem) {
        if (auto c = std::dynamic_pointer_cast<KerML::Entities::Classifier>(elem)) {
            return c;
        }
    }
    auto placeholder = std::make_shared<KerML::Entities::Classifier>();
    auto lastColon = name.rfind("::");
    std::string declName = (lastColon != std::string::npos) ? name.substr(lastColon + 2) : name;
    placeholder->setDeclaredName(declName);
    Elements.push_back(placeholder);
    return placeholder;
}

std::shared_ptr<KerML::Entities::Feature> KerMLListenerImplementation::findOrCreateFeature(const std::string& name) {
    auto elem = findElementWithName(name);
    if (elem) {
        if (auto f = std::dynamic_pointer_cast<KerML::Entities::Feature>(elem)) {
            return f;
        }
    }
    auto placeholder = std::make_shared<KerML::Entities::Feature>();
    auto lastColon = name.rfind("::");
    std::string declName = (lastColon != std::string::npos) ? name.substr(lastColon + 2) : name;
    placeholder->setDeclaredName(declName);
    Elements.push_back(placeholder);
    return placeholder;
}

void KerMLListenerImplementation::populateWithBaseDatatypes()
{
    const std::vector<std::string> baseTypes = {
        "String", "Boolean", "Integer", "Real", "Natural", "UnlimitedNatural", "Positive", "Object", "Anything"
    };
    for (const auto& name : baseTypes) {
        if (!findElementWithName(name)) {
            const auto dt = std::make_shared<KerML::Entities::DataType>();
            dt->setDeclaredName(name);
            Elements.push_back(dt);
            if (!ParentStack.empty()) {
                ParentStack.top()->appendOwnedElement(dt);
            }
        }
    }
}
