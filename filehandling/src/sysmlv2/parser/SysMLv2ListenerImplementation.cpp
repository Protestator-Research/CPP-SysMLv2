#include <sysmlv2/parser/SysMLv2ListenerImplementation.h>
#include <sysml/SysML.h>
#include <kerml/KerML.h>
#include <iostream>
#include <algorithm>

SysMLv2ListenerImplementation::SysMLv2ListenerImplementation() = default;
SysMLv2ListenerImplementation::~SysMLv2ListenerImplementation() = default;

void SysMLv2ListenerImplementation::enterStart(SysMLv2Parser::StartContext*) {
    Elements.clear();
    while (!ParentStack.empty()) ParentStack.pop();
    pendingTypings_.clear();
    pendingSpecializations_.clear();
    aliases_.clear();
    packageImports_.clear();
    populateWithBaseDatatypes();
}

void SysMLv2ListenerImplementation::exitStart(SysMLv2Parser::StartContext*) {
    resolveReferences();
}

void SysMLv2ListenerImplementation::enterDependency(SysMLv2Parser::DependencyContext*) {
    const auto dep = std::make_shared<KerML::Entities::Dependency>();
    ParentStack.emplace(dep);
}

void SysMLv2ListenerImplementation::exitDependency(SysMLv2Parser::DependencyContext* ctx) {
    if (ParentStack.empty()) return;
    const auto dep = std::dynamic_pointer_cast<KerML::Entities::Dependency>(ParentStack.top());
    if (!dep) return;
    ParentStack.pop();

    if (ctx && ctx->dependency_declaration()) {
        auto decl = ctx->dependency_declaration();
        if (decl->identification()) {
            applyIdentification(decl->identification(), dep);
        }
        if (decl->KEYWORD_TO()) {
            size_t toIndex = decl->KEYWORD_TO()->getSymbol()->getTokenIndex();
            std::vector<std::shared_ptr<KerML::Entities::Element>> clients;
            std::vector<std::shared_ptr<KerML::Entities::Element>> suppliers;
            for (auto q : decl->qualified_name()) {
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
    }

    Elements.push_back(dep);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(dep);
    }
}

void SysMLv2ListenerImplementation::enterAnnotating_element(SysMLv2Parser::Annotating_elementContext*) {}
void SysMLv2ListenerImplementation::exitAnnotating_element(SysMLv2Parser::Annotating_elementContext*) {}

void SysMLv2ListenerImplementation::exitComment(SysMLv2Parser::CommentContext* ctx) {
    std::string identification = "";
    if (ctx->identification() != nullptr) {
        identification = ctx->identification()->getText();
    }

    std::vector<std::shared_ptr<KerML::Entities::Element>> annotatedElements;
    if (ctx->KEYWORD_ABOUT() != nullptr) {
        for (auto& about : ctx->annotation()) {
            const auto& annotatedElement = findElementWithName(about->getText());
            if (annotatedElement != nullptr)
                annotatedElements.push_back(annotatedElement);
        }
    }
    std::string locale = "";
    if (ctx->KEYWORD_LOCALE() != nullptr && ctx->STRING_VALUE() != nullptr) {
        locale = ctx->STRING_VALUE()->getText();
    }

    std::string body = ctx->REGULAR_COMMENT() ? ctx->REGULAR_COMMENT()->getText() : "";
    const auto& comment = std::make_shared<KerML::Entities::Comment>(locale, body);
    Elements.push_back(comment);

    if (!identification.empty())
        comment->setDeclaredName(identification);

    if (!annotatedElements.empty())
        comment->appendAnnotatedElements(annotatedElements);
    else if (!ParentStack.empty())
        comment->appendAnnotatedElement(ParentStack.top());

    if (!ParentStack.empty())
        ParentStack.top()->appendOwnedElement(comment);
}

void SysMLv2ListenerImplementation::exitDocumentation(SysMLv2Parser::DocumentationContext* ctx) {
    std::string identification = "";
    if (ctx->identification() != nullptr) {
        identification = ctx->identification()->getText();
    }
    std::string locale = "";
    if (ctx->KEYWORD_LOCALE() != nullptr && ctx->STRING_VALUE() != nullptr) {
        locale = ctx->STRING_VALUE()->getText();
    }
    std::string body = ctx->REGULAR_COMMENT() ? ctx->REGULAR_COMMENT()->getText() : "";
    auto parent = ParentStack.empty() ? nullptr : ParentStack.top();
    auto documentation = std::make_shared<KerML::Entities::Documentation>(parent, locale, body);
    documentation->setDeclaredName(identification);
    Elements.push_back(documentation);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(documentation);
    }
}

void SysMLv2ListenerImplementation::exitTextual_representation(SysMLv2Parser::Textual_representationContext* ctx) {
    std::string language;
    if (ctx->KEYWORD_LANGUAGE() != nullptr && ctx->STRING_VALUE() != nullptr)
        language = ctx->STRING_VALUE()->getText();

    std::string body = ctx->REGULAR_COMMENT() ? ctx->REGULAR_COMMENT()->getText() : "";
    const auto textualRepresentation = std::make_shared<KerML::Entities::TextualRepresentation>(language, body);
    Elements.push_back(textualRepresentation);
    if (!ParentStack.empty())
        ParentStack.top()->appendOwnedElement(textualRepresentation);
}

void SysMLv2ListenerImplementation::enterPackage(SysMLv2Parser::PackageContext* ctx) {
    const auto package = std::make_shared<KerML::Entities::Package>();
    if (ctx && ctx->package_declaration() && ctx->package_declaration()->identification()) {
        applyIdentification(ctx->package_declaration()->identification(), package);
    }
    ParentStack.push(package);
}

void SysMLv2ListenerImplementation::exitPackage(SysMLv2Parser::PackageContext*) {
    if (ParentStack.empty()) return;
    const auto package = std::dynamic_pointer_cast<KerML::Entities::Package>(ParentStack.top());
    ParentStack.pop();
    if (package) {
        Elements.push_back(package);
        if (!ParentStack.empty()) {
            package->setOwner(ParentStack.top());
            ParentStack.top()->appendOwnedElement(package);
        }
    }
}

void SysMLv2ListenerImplementation::enterPackage_declaration(SysMLv2Parser::Package_declarationContext*) {}
void SysMLv2ListenerImplementation::exitPackage_declaration(SysMLv2Parser::Package_declarationContext* ctx) {
    if (ParentStack.empty()) return;
    if (auto package = std::dynamic_pointer_cast<KerML::Entities::Package>(ParentStack.top())) {
        if (ctx && ctx->identification()) {
            applyIdentification(ctx->identification(), package);
        }
    }
}

void SysMLv2ListenerImplementation::enterAlias_member(SysMLv2Parser::Alias_memberContext*) {}
void SysMLv2ListenerImplementation::exitAlias_member(SysMLv2Parser::Alias_memberContext* ctx) {
    if (!ctx || !ctx->qualified_name()) return;
    std::string targetName = ctx->qualified_name()->getText();
    std::string aliasName;
    if (!ctx->NAME().empty()) {
        aliasName = ctx->NAME().back()->getText();
    }
    if (!aliasName.empty()) {
        aliases_[aliasName] = targetName;
        auto elem = findElementWithName(targetName);
        if (elem) {
            elem->appendAliasId(aliasName);
        }
    }
}

void SysMLv2ListenerImplementation::enterDefinition_declaration(SysMLv2Parser::Definition_declarationContext*) {}
void SysMLv2ListenerImplementation::exitDefinition_declaration(SysMLv2Parser::Definition_declarationContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    auto topElem = ParentStack.top();
    if (ctx->identification()) {
        applyIdentification(ctx->identification(), topElem);
    }
}

void SysMLv2ListenerImplementation::exitSubsclassification_part(SysMLv2Parser::Subsclassification_partContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    auto classifier = std::dynamic_pointer_cast<KerML::Entities::Classifier>(ParentStack.top());
    if (!classifier) return;
    for (auto subCtx : ctx->owned_subclassification()) {
        std::string superName = subCtx->getText();
        pendingSpecializations_.push_back({classifier, superName});
    }
}

void SysMLv2ListenerImplementation::enterVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext*) {
    auto vm = std::make_shared<SysMLv2::Entities::VariantMembership>();
    ParentStack.push(vm);
}

void SysMLv2ListenerImplementation::exitVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext*) {
    if (ParentStack.empty()) return;
    auto vm = std::dynamic_pointer_cast<SysMLv2::Entities::VariantMembership>(ParentStack.top());
    if (!vm) return;
    ParentStack.pop();

    if (!vm->ownedElements().empty()) {
        for (const auto& child : vm->ownedElements()) {
            if (auto usage = std::dynamic_pointer_cast<SysMLv2::Entities::Usage>(child)) {
                vm->setOwnedVariantUsage(usage);
                vm->setMemberElement(usage);
                vm->setOwnedMemberElement(usage);
                break;
            }
        }
    }

    Elements.push_back(vm);
    if (!ParentStack.empty()) {
        vm->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(vm);
        if (auto def = std::dynamic_pointer_cast<SysMLv2::Entities::Definition>(ParentStack.top())) {
            def->appendOwnedMembership(vm);
        }
    }
}

void SysMLv2ListenerImplementation::enterSubject_member(SysMLv2Parser::Subject_memberContext*) {
    auto sm = std::make_shared<SysMLv2::Entities::SubjectMembership>();
    ParentStack.push(sm);
}

void SysMLv2ListenerImplementation::exitSubject_member(SysMLv2Parser::Subject_memberContext*) {
    if (ParentStack.empty()) return;
    auto sm = std::dynamic_pointer_cast<SysMLv2::Entities::SubjectMembership>(ParentStack.top());
    if (!sm) return;
    ParentStack.pop();

    if (!sm->ownedElements().empty()) {
        for (const auto& child : sm->ownedElements()) {
            if (auto usage = std::dynamic_pointer_cast<SysMLv2::Entities::Usage>(child)) {
                sm->setOwnedSubjectParameter(usage);
                sm->setMemberElement(usage);
                sm->setOwnedMemberElement(usage);
                break;
            }
        }
    }

    Elements.push_back(sm);
    if (!ParentStack.empty()) {
        sm->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(sm);
        if (auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top())) {
            ns->appendOwnedMembership(sm);
        }
    }
}

void SysMLv2ListenerImplementation::enterSubject_usage(SysMLv2Parser::Subject_usageContext*) {
    auto u = std::make_shared<SysMLv2::Entities::Usage>();
    ParentStack.push(u);
}

void SysMLv2ListenerImplementation::exitSubject_usage(SysMLv2Parser::Subject_usageContext*) {
    if (ParentStack.empty()) return;
    auto u = std::dynamic_pointer_cast<SysMLv2::Entities::Usage>(ParentStack.top());
    if (!u) return;
    ParentStack.pop();

    Elements.push_back(u);
    if (!ParentStack.empty()) {
        u->setOwner(ParentStack.top());
        ParentStack.top()->appendOwnedElement(u);
    }
}

void SysMLv2ListenerImplementation::enterUsage_declaration(SysMLv2Parser::Usage_declarationContext*) {}
void SysMLv2ListenerImplementation::exitUsage_declaration(SysMLv2Parser::Usage_declarationContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    auto topElem = ParentStack.top();
    if (ctx->identification()) {
        applyIdentification(ctx->identification(), topElem);
    }
    if (ctx->feature_specialization_part()) {
        if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(topElem)) {
            applyFeatureSpecializationPart(ctx->feature_specialization_part(), feat);
        }
    }
}

void SysMLv2ListenerImplementation::applyUsagePrefix(SysMLv2Parser::Usage_prefixContext* prefix, const std::shared_ptr<KerML::Entities::Feature>& feature) {
    if (!prefix || !feature) return;
    std::string text = prefix->getText();
    if (text.find("inout") != std::string::npos) feature->setDirection(KerML::Entities::IN_OUT);
    else if (text.find("in") != std::string::npos) feature->setDirection(KerML::Entities::IN);
    else if (text.find("out") != std::string::npos) feature->setDirection(KerML::Entities::OUT);
}

void SysMLv2ListenerImplementation::applyOccurrenceUsagePrefix(SysMLv2Parser::Occurrence_usage_prefixContext* prefix, const std::shared_ptr<KerML::Entities::Feature>& feature) {
    if (!prefix || !feature) return;
    std::string text = prefix->getText();
    if (text.find("inout") != std::string::npos) feature->setDirection(KerML::Entities::IN_OUT);
    else if (text.find("in") != std::string::npos) feature->setDirection(KerML::Entities::IN);
    else if (text.find("out") != std::string::npos) feature->setDirection(KerML::Entities::OUT);
}

void SysMLv2ListenerImplementation::applyFeatureSpecializationPart(SysMLv2Parser::Feature_specialization_partContext* part, const std::shared_ptr<KerML::Entities::Feature>& feature) {
    if (!part || !feature) return;
    for (auto spec : part->feature_specialization()) {
        if (spec->typings()) {
            for (auto typingCtx : spec->typings()->owned_feature_typing()) {
                std::string typeName = typingCtx->getText();
                pendingTypings_.push_back({feature, typeName});
            }
            if (spec->typings()->typed_by() && spec->typings()->typed_by()->owned_feature_typing()) {
                std::string typeName = spec->typings()->typed_by()->owned_feature_typing()->getText();
                pendingTypings_.push_back({feature, typeName});
            }
        }
    }
}

void SysMLv2ListenerImplementation::exitMultiplicity_part(SysMLv2Parser::Multiplicity_partContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!feature) return;
    std::string text = ctx->getText();
    if (text.find("nonunique") != std::string::npos) feature->setIsUnique(false);
    if (text.find("ordered") != std::string::npos) feature->setIsOrdered(true);
    else feature->setIsOrdered(false);
}

void SysMLv2ListenerImplementation::enterMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext*) {}
void SysMLv2ListenerImplementation::exitOccurrence_definition_prefix(SysMLv2Parser::Occurrence_definition_prefixContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
        std::string text = ctx->getText();
        if (text.find("abstract") != std::string::npos) type->setAbstract(true);
        if (text.find("variation") != std::string::npos) {
            if (auto def = std::dynamic_pointer_cast<SysMLv2::Entities::Definition>(type)) {
                def->setIsVariation(true);
            }
        }
    }
}

void SysMLv2ListenerImplementation::exitDefinition_prefix(SysMLv2Parser::Definition_prefixContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
        std::string text = ctx->getText();
        if (text.find("abstract") != std::string::npos) type->setAbstract(true);
        if (text.find("variation") != std::string::npos) {
            if (auto def = std::dynamic_pointer_cast<SysMLv2::Entities::Definition>(type)) {
                def->setIsVariation(true);
            }
        }
    }
}

void SysMLv2ListenerImplementation::exitUsage_prefix(SysMLv2Parser::Usage_prefixContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
        applyUsagePrefix(ctx, feat);
    }
}

void SysMLv2ListenerImplementation::exitOccurrence_usage_prefix(SysMLv2Parser::Occurrence_usage_prefixContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
        applyOccurrenceUsagePrefix(ctx, feat);
    }
}

template<typename T>
static void handleUsageEnter(std::stack<std::shared_ptr<KerML::Entities::Element>>& parentStack) {
    auto usage = std::make_shared<T>();
    parentStack.push(usage);
}

template<typename T>
static void handleUsageExit(std::stack<std::shared_ptr<KerML::Entities::Element>>& parentStack, std::vector<std::shared_ptr<KerML::Entities::Element>>& elements) {
    if (parentStack.empty()) return;
    auto usage = std::dynamic_pointer_cast<T>(parentStack.top());
    if (!usage) return;
    parentStack.pop();

    elements.push_back(usage);
    if (!parentStack.empty()) {
        usage->setOwner(parentStack.top());
        parentStack.top()->appendOwnedElement(usage);
        if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(parentStack.top())) {
            if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(usage)) {
                type->appendOwnedFeature(feat);
                feat->setOwningType(type);
            }
        }
    }
}

void SysMLv2ListenerImplementation::enterEnumerated_value(SysMLv2Parser::Enumerated_valueContext*) {
    handleUsageEnter<SysMLv2::Entities::EnumerationUsage>(ParentStack);
}

void SysMLv2ListenerImplementation::exitEnumerated_value(SysMLv2Parser::Enumerated_valueContext*) {
    handleUsageExit<SysMLv2::Entities::EnumerationUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::exitMultiplicity_range(SysMLv2Parser::Multiplicity_rangeContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type || ctx->multiplicity_expression_member().empty()) return;

    std::shared_ptr<KerML::Entities::Multiplicity> multiplicity;
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
    if (multiplicity) {
        type->setMultiplicity(multiplicity);
        type->appendOwnedElement(multiplicity);
        Elements.push_back(multiplicity);
    }
}

void SysMLv2ListenerImplementation::enterConnector_end(SysMLv2Parser::Connector_endContext*) {
    auto endFeature = std::make_shared<KerML::Entities::Feature>();
    endFeature->setIsEnd(true);
    ParentStack.push(endFeature);
}

void SysMLv2ListenerImplementation::exitConnector_end(SysMLv2Parser::Connector_endContext* ctx) {
    if (ParentStack.empty()) return;
    auto endFeature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!endFeature) return;
    ParentStack.pop();

    if (ctx && ctx->owned_reference_subsetting() && ctx->owned_reference_subsetting()->general_type()) {
        std::string targetName = ctx->owned_reference_subsetting()->general_type()->getText();
        auto targetFeature = findOrCreateFeature(targetName);
        auto refSub = std::make_shared<KerML::Entities::ReferenceSubsetting>(targetFeature, endFeature);
        endFeature->setOwnedReferenceSubsetting(refSub);
        endFeature->appendOwnedElement(refSub);
        Elements.push_back(refSub);
    }

    Elements.push_back(endFeature);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(endFeature);
        if (auto conn = std::dynamic_pointer_cast<KerML::Entities::Connector>(ParentStack.top())) {
            conn->appendConnectorEnd(endFeature);
            conn->appendOwnedFeature(endFeature);
        }
    }
}

void SysMLv2ListenerImplementation::exitMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext* ctx) {
    if (ParentStack.empty() || !ctx) return;
    auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    if (!type || ctx->multiplicity_expression_member().empty()) return;

    std::shared_ptr<KerML::Entities::Multiplicity> multiplicity;
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
    if (multiplicity) {
        type->setMultiplicity(multiplicity);
        type->appendOwnedElement(multiplicity);
        Elements.push_back(multiplicity);
    }
}

// Definition-Family Implementierungen
template<typename T>
static void handleDefEnter(std::stack<std::shared_ptr<KerML::Entities::Element>>& parentStack, antlr4::ParserRuleContext*) {
    auto def = std::make_shared<T>();
    parentStack.push(def);
}

template<typename T>
static void handleDefExit(std::stack<std::shared_ptr<KerML::Entities::Element>>& parentStack, std::vector<std::shared_ptr<KerML::Entities::Element>>& elements, antlr4::ParserRuleContext* ctx = nullptr) {
    if (parentStack.empty()) return;
    auto def = std::dynamic_pointer_cast<T>(parentStack.top());
    if (!def) return;
    parentStack.pop();

    if (ctx) {
        std::string text = ctx->getText();
        if (text.find("abstract") != std::string::npos) def->setAbstract(true);
        if (text.find("variation") != std::string::npos) def->setIsVariation(true);
    }

    elements.push_back(def);
    if (!parentStack.empty()) {
        def->setOwner(parentStack.top());
        parentStack.top()->appendOwnedElement(def);
    }
}

#define DEFINE_DEF_METHODS(Name, Type) \
void SysMLv2ListenerImplementation::enter##Name(SysMLv2Parser::Name##Context* ctx) { \
    handleDefEnter<Type>(ParentStack, ctx); \
} \
void SysMLv2ListenerImplementation::exit##Name(SysMLv2Parser::Name##Context* ctx) { \
    handleDefExit<Type>(ParentStack, Elements, ctx); \
}

DEFINE_DEF_METHODS(Part_definition, SysMLv2::Entities::PartDefinition)
DEFINE_DEF_METHODS(Attribute_definition, SysMLv2::Entities::AttributeDefinition)
DEFINE_DEF_METHODS(Item_definition, SysMLv2::Entities::ItemDefinition)
DEFINE_DEF_METHODS(Port_definition, SysMLv2::Entities::PortDefinition)
DEFINE_DEF_METHODS(Connection_definition, SysMLv2::Entities::ConnectionDefinition)
DEFINE_DEF_METHODS(Interface_definition, SysMLv2::Entities::InterfaceDefinition)
DEFINE_DEF_METHODS(Allocation_definition, SysMLv2::Entities::AllocationDefinition)
DEFINE_DEF_METHODS(Action_definition, SysMLv2::Entities::ActionDefinition)
DEFINE_DEF_METHODS(Calculation_definition, SysMLv2::Entities::CalculationDefinition)
DEFINE_DEF_METHODS(Requirement_definition, SysMLv2::Entities::RequirementDefinition)
DEFINE_DEF_METHODS(Concern_definition, SysMLv2::Entities::ConcernDefinition)
DEFINE_DEF_METHODS(Case_definition, SysMLv2::Entities::CaseDefinition)
DEFINE_DEF_METHODS(Analysis_case_definition, SysMLv2::Entities::AnalysisCaseDefinition)
DEFINE_DEF_METHODS(Verification_case_definition, SysMLv2::Entities::VerificationCaseDefinition)
DEFINE_DEF_METHODS(View_definition, SysMLv2::Entities::ViewDefinition)
DEFINE_DEF_METHODS(Viewpoint_definition, SysMLv2::Entities::ViewpointDefinition)
DEFINE_DEF_METHODS(Rendering_definition, SysMLv2::Entities::RenderingDefinition)
DEFINE_DEF_METHODS(Metadata_definition, SysMLv2::Entities::MetadataDefinition)
DEFINE_DEF_METHODS(Enumeration_definition, SysMLv2::Entities::EnumerationDefinition)
DEFINE_DEF_METHODS(State_definition, SysMLv2::Entities::StateDefinition)
DEFINE_DEF_METHODS(Constraint_definition, SysMLv2::Entities::ConstraintDefinition)
DEFINE_DEF_METHODS(Extended_definition, SysMLv2::Entities::Definition)
DEFINE_DEF_METHODS(Occurrence_definition, SysMLv2::Entities::OccurrenceDefinition)
DEFINE_DEF_METHODS(Flow_definition, SysMLv2::Entities::FlowDefinition)

void SysMLv2ListenerImplementation::enterIndividual_definition(SysMLv2Parser::Individual_definitionContext* ctx) {
    auto def = std::make_shared<SysMLv2::Entities::OccurrenceDefinition>();
    def->setIsIndividual(true);
    ParentStack.push(def);
}
void SysMLv2ListenerImplementation::exitIndividual_definition(SysMLv2Parser::Individual_definitionContext* ctx) {
    handleDefExit<SysMLv2::Entities::OccurrenceDefinition>(ParentStack, Elements);
}

// Usage-Family Implementierungen

#define DEFINE_USAGE_METHODS(Name, Type) \
void SysMLv2ListenerImplementation::enter##Name(SysMLv2Parser::Name##Context*) { \
    handleUsageEnter<Type>(ParentStack); \
} \
void SysMLv2ListenerImplementation::exit##Name(SysMLv2Parser::Name##Context*) { \
    handleUsageExit<Type>(ParentStack, Elements); \
}

DEFINE_USAGE_METHODS(Part_usage, SysMLv2::Entities::PartUsage)
DEFINE_USAGE_METHODS(Attribute_usage, SysMLv2::Entities::AttributeUsage)
DEFINE_USAGE_METHODS(Item_usage, SysMLv2::Entities::ItemUsage)
DEFINE_USAGE_METHODS(Port_usage, SysMLv2::Entities::PortUsage)
DEFINE_USAGE_METHODS(Interface_usage, SysMLv2::Entities::InterfaceUsage)
DEFINE_USAGE_METHODS(Allocation_usage, SysMLv2::Entities::AllocationUsage)
DEFINE_USAGE_METHODS(Action_usage, SysMLv2::Entities::ActionUsage)
DEFINE_USAGE_METHODS(Calculation_usage, SysMLv2::Entities::CalculationUsage)
DEFINE_USAGE_METHODS(Requirement_usage, SysMLv2::Entities::RequirementUsage)
DEFINE_USAGE_METHODS(Concern_usage, SysMLv2::Entities::ConcernUsage)
DEFINE_USAGE_METHODS(Case_usage, SysMLv2::Entities::CaseUsage)
DEFINE_USAGE_METHODS(Analysis_case_usage, SysMLv2::Entities::AnalysisCaseUsage)
DEFINE_USAGE_METHODS(Verification_case_usage, SysMLv2::Entities::VerificationCaseUsage)
DEFINE_USAGE_METHODS(View_usage, SysMLv2::Entities::ViewUsage)
DEFINE_USAGE_METHODS(Viewpoint_usage, SysMLv2::Entities::ViewpointUsage)
DEFINE_USAGE_METHODS(Rendering_usage, SysMLv2::Entities::RenderingUsage)
DEFINE_USAGE_METHODS(Metadata_usage, SysMLv2::Entities::MetadataUsage)
DEFINE_USAGE_METHODS(Occurrence_usage, SysMLv2::Entities::OccurrenceUsage)
DEFINE_USAGE_METHODS(Enumeration_usage, SysMLv2::Entities::EnumerationUsage)
DEFINE_USAGE_METHODS(State_usage, SysMLv2::Entities::StateUsage)
DEFINE_USAGE_METHODS(Constraint_usage, SysMLv2::Entities::ConstraintUsage)
DEFINE_USAGE_METHODS(Extended_usage, SysMLv2::Entities::Usage)
DEFINE_USAGE_METHODS(Perform_action_usage, SysMLv2::Entities::PerformActionUsage)
DEFINE_USAGE_METHODS(Exhibit_state_usage, SysMLv2::Entities::ExhibitStateUsage)
DEFINE_USAGE_METHODS(Default_reference_usage, SysMLv2::Entities::ReferenceUsage)
DEFINE_USAGE_METHODS(Reference_usage, SysMLv2::Entities::ReferenceUsage)
DEFINE_USAGE_METHODS(Variant_reference, SysMLv2::Entities::ReferenceUsage)
DEFINE_USAGE_METHODS(Assert_constriant_usage, SysMLv2::Entities::AssertConstraintUsage)
DEFINE_USAGE_METHODS(Satisfy_requirement_usage, SysMLv2::Entities::SatisfyRequirementUsage)
DEFINE_USAGE_METHODS(Use_case_usage, SysMLv2::Entities::UseCaseUsage)
DEFINE_USAGE_METHODS(Include_use_case_usage, SysMLv2::Entities::IncludeUseCaseUsage)
DEFINE_USAGE_METHODS(Flow_usage, SysMLv2::Entities::FlowUsage)
DEFINE_USAGE_METHODS(Succession_flow_usage, SysMLv2::Entities::SuccessionFlowUsage)
DEFINE_USAGE_METHODS(Message, SysMLv2::Entities::FlowUsage)

void SysMLv2ListenerImplementation::enterIndividual_usage(SysMLv2Parser::Individual_usageContext* ctx) {
    auto u = std::make_shared<SysMLv2::Entities::OccurrenceUsage>();
    u->setIsIndividual(true);
    ParentStack.push(u);
}
void SysMLv2ListenerImplementation::exitIndividual_usage(SysMLv2Parser::Individual_usageContext* ctx) {
    handleUsageExit<SysMLv2::Entities::OccurrenceUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterPortion_usage(SysMLv2Parser::Portion_usageContext* ctx) {
    auto u = std::make_shared<SysMLv2::Entities::OccurrenceUsage>();
    ParentStack.push(u);
}
void SysMLv2ListenerImplementation::exitPortion_usage(SysMLv2Parser::Portion_usageContext* ctx) {
    handleUsageExit<SysMLv2::Entities::OccurrenceUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext* ctx) {
    auto u = std::make_shared<SysMLv2::Entities::EventOccurrenceUsage>();
    ParentStack.push(u);
}
void SysMLv2ListenerImplementation::exitEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext* ctx) {
    handleUsageExit<SysMLv2::Entities::EventOccurrenceUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterConnection_usage(SysMLv2Parser::Connection_usageContext* ctx) {
    auto conn = std::make_shared<SysMLv2::Entities::ConnectionUsage>();
    ParentStack.push(conn);
}
void SysMLv2ListenerImplementation::exitConnection_usage(SysMLv2Parser::Connection_usageContext* ctx) {
    handleUsageExit<SysMLv2::Entities::ConnectionUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterConnecotr_end(SysMLv2Parser::Connecotr_endContext*) {
    auto endFeature = std::make_shared<KerML::Entities::Feature>();
    endFeature->setIsEnd(true);
    ParentStack.push(endFeature);
}

void SysMLv2ListenerImplementation::exitConnecotr_end(SysMLv2Parser::Connecotr_endContext* ctx) {
    if (ParentStack.empty()) return;
    auto endFeature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    if (!endFeature) return;
    ParentStack.pop();

    if (ctx && ctx->owned_reference_subsetting() && ctx->owned_reference_subsetting()->general_type()) {
        std::string targetName = ctx->owned_reference_subsetting()->general_type()->getText();
        auto targetFeature = findOrCreateFeature(targetName);
        auto refSub = std::make_shared<KerML::Entities::ReferenceSubsetting>(targetFeature, endFeature);
        endFeature->setOwnedReferenceSubsetting(refSub);
        endFeature->appendOwnedElement(refSub);
        Elements.push_back(refSub);
    }

    Elements.push_back(endFeature);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(endFeature);
        if (auto conn = std::dynamic_pointer_cast<KerML::Entities::Connector>(ParentStack.top())) {
            conn->appendConnectorEnd(endFeature);
            conn->appendOwnedFeature(endFeature);
        }
    }
}

void SysMLv2ListenerImplementation::enterPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext*) {}
void SysMLv2ListenerImplementation::exitPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext*) {}

void SysMLv2ListenerImplementation::enterBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext* ctx) {
    auto bc = std::make_shared<SysMLv2::Entities::BindingConnectorAsUsage>();
    ParentStack.push(bc);
}
void SysMLv2ListenerImplementation::exitBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext* ctx) {
    handleUsageExit<SysMLv2::Entities::BindingConnectorAsUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext* ctx) {
    auto sc = std::make_shared<SysMLv2::Entities::SuccessionAsUsage>();
    ParentStack.push(sc);
}
void SysMLv2ListenerImplementation::exitSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext* ctx) {
    handleUsageExit<SysMLv2::Entities::SuccessionAsUsage>(ParentStack, Elements);
}

// Ausdrücke und Literale
void SysMLv2ListenerImplementation::enterConditional_expression(SysMLv2Parser::Conditional_expressionContext*) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitConditional_expression(SysMLv2Parser::Conditional_expressionContext*) {
    finishOperatorExpression("if");
}

void SysMLv2ListenerImplementation::enterConditional_binary_operator_expression(SysMLv2Parser::Conditional_binary_operator_expressionContext*) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitConditional_binary_operator_expression(SysMLv2Parser::Conditional_binary_operator_expressionContext* ctx) {
    finishOperatorExpression(ctx && ctx->conditional_binary_operator() ? ctx->conditional_binary_operator()->getText() : "");
}

void SysMLv2ListenerImplementation::enterBinary_operator_expression(SysMLv2Parser::Binary_operator_expressionContext*) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitBinary_operator_expression(SysMLv2Parser::Binary_operator_expressionContext* ctx) {
    if (ParentStack.empty()) return;
    auto opExpr = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(ParentStack.top());
    if (!opExpr) return;
    ParentStack.pop();
    if (ctx && ctx->binary_operator()) {
        opExpr->setOperatorName(ctx->binary_operator()->getText());
    }
    attachExpression(opExpr);
}

void SysMLv2ListenerImplementation::enterUnary_operator_expression(SysMLv2Parser::Unary_operator_expressionContext*) {
    ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitUnary_operator_expression(SysMLv2Parser::Unary_operator_expressionContext* ctx) {
    if (ParentStack.empty()) return;
    auto opExpr = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(ParentStack.top());
    if (!opExpr) return;
    ParentStack.pop();
    if (ctx && ctx->unary_operator()) {
        opExpr->setOperatorName(ctx->unary_operator()->getText());
    }
    attachExpression(opExpr);
}

void SysMLv2ListenerImplementation::enterFeature_value(SysMLv2Parser::Feature_valueContext* ctx) {
    auto fv = std::make_shared<KerML::Entities::FeatureValue>();
    if (ctx && ctx->KEYWORD_DEFAULT()) fv->setIsDefault(true);
    ParentStack.push(fv);
}

void SysMLv2ListenerImplementation::exitFeature_value(SysMLv2Parser::Feature_valueContext*) {
    if (ParentStack.empty()) return;
    auto fv = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top());
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

void SysMLv2ListenerImplementation::enterFeature_assignment(SysMLv2Parser::Feature_assignmentContext*) {
    auto fv = std::make_shared<KerML::Entities::FeatureValue>();
    ParentStack.push(fv);
}

void SysMLv2ListenerImplementation::exitFeature_assignment(SysMLv2Parser::Feature_assignmentContext*) {
    if (ParentStack.empty()) return;
    auto fv = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top());
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

void SysMLv2ListenerImplementation::enterLiteral_expression(SysMLv2Parser::Literal_expressionContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_expression(SysMLv2Parser::Literal_expressionContext* ctx) {
    if (!ctx) return;
    std::shared_ptr<KerML::Entities::LiteralExpression> literal;
    if (ctx->KEYWORD_TRUE()) {
        auto b = std::make_shared<KerML::Entities::LiteralBoolean>();
        b->setValue(true);
        literal = b;
    } else if (ctx->KEYWORD_FALSE()) {
        auto b = std::make_shared<KerML::Entities::LiteralBoolean>();
        b->setValue(false);
        literal = b;
    } else if (ctx->literal_string()) {
        auto s = std::make_shared<KerML::Entities::LiteralString>();
        std::string t = ctx->literal_string()->getText();
        if (t.size() >= 2 && t.front() == '"' && t.back() == '"') t = t.substr(1, t.size() - 2);
        s->setValue(t);
        literal = s;
    } else if (ctx->literal_integer()) {
        auto i = std::make_shared<KerML::Entities::LiteralInteger>();
        i->setValue(std::stoll(ctx->literal_integer()->getText()));
        literal = i;
    } else if (ctx->literal_real()) {
        auto r = std::make_shared<KerML::Entities::LiteralRational>();
        r->setValue(std::stod(ctx->literal_real()->getText()));
        literal = r;
    } else if (ctx->literal_infinity()) {
        literal = std::make_shared<KerML::Entities::LiteralInfinity>();
    }
    if (literal) attachExpression(literal);
}

void SysMLv2ListenerImplementation::enterLiteral_boolean(SysMLv2Parser::Literal_booleanContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_boolean(SysMLv2Parser::Literal_booleanContext*) {}

void SysMLv2ListenerImplementation::enterLiteral_string(SysMLv2Parser::Literal_stringContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_string(SysMLv2Parser::Literal_stringContext*) {}

void SysMLv2ListenerImplementation::enterLiteral_integer(SysMLv2Parser::Literal_integerContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_integer(SysMLv2Parser::Literal_integerContext*) {}

void SysMLv2ListenerImplementation::enterLiteral_real(SysMLv2Parser::Literal_realContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_real(SysMLv2Parser::Literal_realContext*) {}

void SysMLv2ListenerImplementation::enterLiteral_infinity(SysMLv2Parser::Literal_infinityContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_infinity(SysMLv2Parser::Literal_infinityContext*) {}

void SysMLv2ListenerImplementation::enterMultiplicity(SysMLv2Parser::MultiplicityContext*) {}
void SysMLv2ListenerImplementation::exitMultiplicity(SysMLv2Parser::MultiplicityContext*) {}

// KerML-Stubs & Namespaces
void SysMLv2ListenerImplementation::enterNamespace(SysMLv2Parser::NamespaceContext*) {
    auto ns = std::make_shared<KerML::Entities::Namespace>();
    ParentStack.push(ns);
}
void SysMLv2ListenerImplementation::exitNamespace(SysMLv2Parser::NamespaceContext*) {
    if (ParentStack.empty()) return;
    auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top());
    ParentStack.pop();
    if (ns) {
        Elements.push_back(ns);
        if (!ParentStack.empty()) {
            ns->setOwner(ParentStack.top());
            ParentStack.top()->appendOwnedElement(ns);
        }
    }
}

void SysMLv2ListenerImplementation::enterNamespace_import(SysMLv2Parser::Namespace_importContext*) {
    auto ni = std::make_shared<KerML::Entities::NamespaceImport>();
    ParentStack.push(ni);
}
void SysMLv2ListenerImplementation::exitNamespace_import(SysMLv2Parser::Namespace_importContext* ctx) {
    if (ParentStack.empty()) return;
    auto ni = std::dynamic_pointer_cast<KerML::Entities::NamespaceImport>(ParentStack.top());
    if (!ni) return;
    ParentStack.pop();

    if (ctx && ctx->import_declaration()) {
        std::string text = ctx->import_declaration()->getText();
        bool isAll = ctx->KEYWORD_ALL() != nullptr;
        bool isRecursive = false;
        std::string importedNsName = text;
        auto starPos = importedNsName.find("::*");
        if (starPos != std::string::npos) {
            importedNsName = importedNsName.substr(0, starPos);
            isAll = true;
        }
        auto doubleStarPos = importedNsName.find("::**");
        if (doubleStarPos != std::string::npos) {
            importedNsName = importedNsName.substr(0, doubleStarPos);
            isRecursive = true;
            isAll = true;
        }
        ni->setIsImportAll(isAll);
        ni->setIsRecursive(isRecursive);
        auto importedNs = std::make_shared<KerML::Entities::Namespace>(importedNsName, true);
        ni->setImportedNamespace(importedNs);

        if (!ParentStack.empty()) {
            if (auto owner = ParentStack.top()) {
                if (owner->declaredName().has_value()) {
                    packageImports_[*owner->declaredName()].push_back(importedNsName);
                }
            }
        }
    }

    Elements.push_back(ni);
    if (!ParentStack.empty()) {
        ParentStack.top()->appendOwnedElement(ni);
    }
}

void SysMLv2ListenerImplementation::enterType(SysMLv2Parser::TypeContext*) {
    auto t = std::make_shared<KerML::Entities::Type>();
    ParentStack.push(t);
}
void SysMLv2ListenerImplementation::exitType(SysMLv2Parser::TypeContext*) {
    if (ParentStack.empty()) return;
    auto t = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
    ParentStack.pop();
    if (t) {
        Elements.push_back(t);
        if (!ParentStack.empty()) ParentStack.top()->appendOwnedElement(t);
    }
}

void SysMLv2ListenerImplementation::enterSpecialization(SysMLv2Parser::SpecializationContext*) {}
void SysMLv2ListenerImplementation::exitSpecialization(SysMLv2Parser::SpecializationContext* ctx) {
    if (!ctx) return;
    auto gen = findOrCreateType(ctx->general_type()->getText());
    auto spec = findOrCreateType(ctx->specific_type()->getText());
    auto s = std::make_shared<KerML::Entities::Specialization>(gen, spec);
    Elements.push_back(s);
    if (!ParentStack.empty()) ParentStack.top()->appendOwnedElement(s);
}

void SysMLv2ListenerImplementation::enterConjunction(SysMLv2Parser::ConjunctionContext*) {}
void SysMLv2ListenerImplementation::exitConjunction(SysMLv2Parser::ConjunctionContext*) {}
void SysMLv2ListenerImplementation::enterDisjoining(SysMLv2Parser::DisjoiningContext*) {}
void SysMLv2ListenerImplementation::exitDisjoining(SysMLv2Parser::DisjoiningContext*) {}

void SysMLv2ListenerImplementation::enterClassifier(SysMLv2Parser::ClassifierContext*) {
    auto c = std::make_shared<KerML::Entities::Classifier>();
    ParentStack.push(c);
}
void SysMLv2ListenerImplementation::exitClassifier(SysMLv2Parser::ClassifierContext*) {
    if (ParentStack.empty()) return;
    auto c = std::dynamic_pointer_cast<KerML::Entities::Classifier>(ParentStack.top());
    ParentStack.pop();
    if (c) {
        Elements.push_back(c);
        if (!ParentStack.empty()) ParentStack.top()->appendOwnedElement(c);
    }
}

void SysMLv2ListenerImplementation::enterSubclassification(SysMLv2Parser::SubclassificationContext*) {}
void SysMLv2ListenerImplementation::exitSubclassification(SysMLv2Parser::SubclassificationContext*) {}

void SysMLv2ListenerImplementation::enterFeature(SysMLv2Parser::FeatureContext*) {
    auto f = std::make_shared<KerML::Entities::Feature>();
    ParentStack.push(f);
}
void SysMLv2ListenerImplementation::exitFeature(SysMLv2Parser::FeatureContext*) {
    if (ParentStack.empty()) return;
    auto f = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
    ParentStack.pop();
    if (f) {
        Elements.push_back(f);
        if (!ParentStack.empty()) ParentStack.top()->appendOwnedElement(f);
    }
}

void SysMLv2ListenerImplementation::enterFeature_typing(SysMLv2Parser::Feature_typingContext*) {}
void SysMLv2ListenerImplementation::exitFeature_typing(SysMLv2Parser::Feature_typingContext*) {}
void SysMLv2ListenerImplementation::enterSubsetting(SysMLv2Parser::SubsettingContext*) {}
void SysMLv2ListenerImplementation::exitSubsetting(SysMLv2Parser::SubsettingContext*) {}
void SysMLv2ListenerImplementation::enterRedefinition(SysMLv2Parser::RedefinitionContext*) {}
void SysMLv2ListenerImplementation::exitRedefinition(SysMLv2Parser::RedefinitionContext*) {}
void SysMLv2ListenerImplementation::enterFeature_inverting(SysMLv2Parser::Feature_invertingContext*) {}
void SysMLv2ListenerImplementation::exitFeature_inverting(SysMLv2Parser::Feature_invertingContext*) {}
void SysMLv2ListenerImplementation::enterType_featuring(SysMLv2Parser::Type_featuringContext*) {}
void SysMLv2ListenerImplementation::exitType_featuring(SysMLv2Parser::Type_featuringContext*) {}

void SysMLv2ListenerImplementation::enterData_type(SysMLv2Parser::Data_typeContext*) {
    auto dt = std::make_shared<KerML::Entities::DataType>();
    ParentStack.push(dt);
}
void SysMLv2ListenerImplementation::exitData_type(SysMLv2Parser::Data_typeContext*) {
    handleUsageExit<KerML::Entities::DataType>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterClass(SysMLv2Parser::ClassContext*) {
    auto cl = std::make_shared<KerML::Entities::Class>();
    ParentStack.push(cl);
}
void SysMLv2ListenerImplementation::exitClass(SysMLv2Parser::ClassContext*) {
    handleUsageExit<KerML::Entities::Class>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterStructure(SysMLv2Parser::StructureContext*) {
    auto st = std::make_shared<KerML::Entities::Structure>();
    ParentStack.push(st);
}
void SysMLv2ListenerImplementation::exitStructure(SysMLv2Parser::StructureContext*) {
    handleUsageExit<KerML::Entities::Structure>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterAssociation(SysMLv2Parser::AssociationContext*) {
    auto a = std::make_shared<KerML::Entities::Association>();
    ParentStack.push(a);
}
void SysMLv2ListenerImplementation::exitAssociation(SysMLv2Parser::AssociationContext*) {
    handleUsageExit<KerML::Entities::Association>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterAssociation_structure(SysMLv2Parser::Association_structureContext*) {
    auto as = std::make_shared<KerML::Entities::AssociationStructure>();
    ParentStack.push(as);
}
void SysMLv2ListenerImplementation::exitAssociation_structure(SysMLv2Parser::Association_structureContext*) {
    handleUsageExit<KerML::Entities::AssociationStructure>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterConnector(SysMLv2Parser::ConnectorContext*) {
    auto c = std::make_shared<KerML::Entities::Connector>();
    ParentStack.push(c);
}
void SysMLv2ListenerImplementation::exitConnector(SysMLv2Parser::ConnectorContext*) {
    handleUsageExit<KerML::Entities::Connector>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterBinding_connector(SysMLv2Parser::Binding_connectorContext*) {
    auto bc = std::make_shared<KerML::Entities::BindingConnector>();
    ParentStack.push(bc);
}
void SysMLv2ListenerImplementation::exitBinding_connector(SysMLv2Parser::Binding_connectorContext*) {
    handleUsageExit<KerML::Entities::BindingConnector>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterSuccession(SysMLv2Parser::SuccessionContext*) {
    auto s = std::make_shared<KerML::Entities::Succession>();
    ParentStack.push(s);
}
void SysMLv2ListenerImplementation::exitSuccession(SysMLv2Parser::SuccessionContext*) {
    handleUsageExit<KerML::Entities::Succession>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterBehavior(SysMLv2Parser::BehaviorContext*) {
    auto b = std::make_shared<KerML::Entities::Behavior>();
    ParentStack.push(b);
}
void SysMLv2ListenerImplementation::exitBehavior(SysMLv2Parser::BehaviorContext*) {
    handleUsageExit<KerML::Entities::Behavior>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterStep(SysMLv2Parser::StepContext*) {
    auto s = std::make_shared<KerML::Entities::Step>();
    ParentStack.push(s);
}
void SysMLv2ListenerImplementation::exitStep(SysMLv2Parser::StepContext*) {
    handleUsageExit<KerML::Entities::Step>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterFunction(SysMLv2Parser::FunctionContext*) {
    auto f = std::make_shared<KerML::Entities::Function>();
    ParentStack.push(f);
}
void SysMLv2ListenerImplementation::exitFunction(SysMLv2Parser::FunctionContext*) {
    handleUsageExit<KerML::Entities::Function>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterPredicate(SysMLv2Parser::PredicateContext*) {
    auto p = std::make_shared<KerML::Entities::Predicate>();
    ParentStack.push(p);
}
void SysMLv2ListenerImplementation::exitPredicate(SysMLv2Parser::PredicateContext*) {
    handleUsageExit<KerML::Entities::Predicate>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterBoolean_expression(SysMLv2Parser::Boolean_expressionContext*) {
    auto be = std::make_shared<KerML::Entities::BooleanExpression>();
    ParentStack.push(be);
}
void SysMLv2ListenerImplementation::exitBoolean_expression(SysMLv2Parser::Boolean_expressionContext*) {
    handleUsageExit<KerML::Entities::BooleanExpression>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterInvariant(SysMLv2Parser::InvariantContext*) {
    auto inv = std::make_shared<KerML::Entities::Invariant>();
    ParentStack.push(inv);
}
void SysMLv2ListenerImplementation::exitInvariant(SysMLv2Parser::InvariantContext*) {
    handleUsageExit<KerML::Entities::Invariant>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterClassification(SysMLv2Parser::ClassificationContext*) {}
void SysMLv2ListenerImplementation::exitClassification(SysMLv2Parser::ClassificationContext*) {}
void SysMLv2ListenerImplementation::enterInteraction(SysMLv2Parser::InteractionContext*) {}
void SysMLv2ListenerImplementation::exitInteraction(SysMLv2Parser::InteractionContext*) {}
void SysMLv2ListenerImplementation::enterItem_flow(SysMLv2Parser::Item_flowContext*) {}
void SysMLv2ListenerImplementation::exitItem_flow(SysMLv2Parser::Item_flowContext*) {}
void SysMLv2ListenerImplementation::enterSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext*) {}
void SysMLv2ListenerImplementation::exitSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext*) {}

void SysMLv2ListenerImplementation::enterMetaclass(SysMLv2Parser::MetaclassContext*) {
    auto mc = std::make_shared<KerML::Entities::Metaclass>();
    ParentStack.push(mc);
}
void SysMLv2ListenerImplementation::exitMetaclass(SysMLv2Parser::MetaclassContext*) {
    handleUsageExit<KerML::Entities::Metaclass>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterMetadata_feature(SysMLv2Parser::Metadata_featureContext*) {
    auto mf = std::make_shared<KerML::Entities::MetadataFeature>();
    ParentStack.push(mf);
}
void SysMLv2ListenerImplementation::exitMetadata_feature(SysMLv2Parser::Metadata_featureContext*) {
    handleUsageExit<KerML::Entities::MetadataFeature>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterLibrary_package(SysMLv2Parser::Library_packageContext* ctx) {
    auto lp = std::make_shared<KerML::Entities::LibraryPackage>();
    if (ctx && ctx->KEYWORD_STANDARD()) lp->setIsStandard(true);
    ParentStack.push(lp);
}
void SysMLv2ListenerImplementation::exitLibrary_package(SysMLv2Parser::Library_packageContext*) {
    handleUsageExit<KerML::Entities::LibraryPackage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterMeta_assignment(SysMLv2Parser::Meta_assignmentContext*) {}
void SysMLv2ListenerImplementation::exitMeta_assignment(SysMLv2Parser::Meta_assignmentContext*) {}

std::vector<std::shared_ptr<KerML::Entities::Element>> SysMLv2ListenerImplementation::getElements() const {
    return Elements;
}

// Hilfsmethoden
void SysMLv2ListenerImplementation::attachExpression(const std::shared_ptr<KerML::Entities::Expression>& expression) {
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

void SysMLv2ListenerImplementation::finishOperatorExpression(const std::string& operatorName) {
    if (ParentStack.empty()) return;
    auto expression = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(ParentStack.top());
    if (!expression) return;
    ParentStack.pop();
    expression->setOperatorName(operatorName);
    attachExpression(expression);
}

void SysMLv2ListenerImplementation::applyIdentification(SysMLv2Parser::IdentificationContext *idCtx, const std::shared_ptr<KerML::Entities::Element>& elem) {
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

std::shared_ptr<KerML::Entities::Element> SysMLv2ListenerImplementation::findElementWithName(std::string identification) {
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

std::shared_ptr<KerML::Entities::Element> SysMLv2ListenerImplementation::resolveElement(const std::string& name, const std::shared_ptr<KerML::Entities::Element>& context) {
    std::string targetName = name;
    auto itAlias = aliases_.find(name);
    if (itAlias != aliases_.end()) {
        targetName = itAlias->second;
    }

    auto colonPos = targetName.find("::");
    if (colonPos != std::string::npos) {
        std::string pkgName = targetName.substr(0, colonPos);
        std::string simpleName = targetName.substr(colonPos + 2);
        for (const auto& elem : Elements) {
            if (elem && elem->declaredName() == simpleName) {
                if (elem->owner() && elem->owner()->declaredName() == pkgName) {
                    return elem;
                }
            }
        }
    }

    if (context) {
        std::string currentPkgName;
        auto cur = context->owner();
        while (cur) {
            if (std::dynamic_pointer_cast<KerML::Entities::Namespace>(cur) && cur->declaredName().has_value()) {
                currentPkgName = *cur->declaredName();
                break;
            }
            cur = cur->owner();
        }

        if (!currentPkgName.empty()) {
            auto itImp = packageImports_.find(currentPkgName);
            if (itImp != packageImports_.end()) {
                for (const auto& impPkg : itImp->second) {
                    for (const auto& elem : Elements) {
                        if (elem && elem->declaredName() == targetName) {
                            if (elem->owner() && elem->owner()->declaredName() == impPkg) {
                                return elem;
                            }
                        }
                    }
                }
            }
        }
    }

    return findElementWithName(targetName);
}

std::shared_ptr<KerML::Entities::Type> SysMLv2ListenerImplementation::findOrCreateType(const std::string& name) {
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

std::shared_ptr<KerML::Entities::Classifier> SysMLv2ListenerImplementation::findOrCreateClassifier(const std::string& name) {
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

std::shared_ptr<KerML::Entities::Feature> SysMLv2ListenerImplementation::findOrCreateFeature(const std::string& name) {
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

void SysMLv2ListenerImplementation::populateWithBaseDatatypes() {
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

void SysMLv2ListenerImplementation::resolveReferences() {
    for (const auto& pending : pendingTypings_) {
        if (!pending.feature) continue;
        auto target = resolveElement(pending.typeName, pending.feature);
        auto typeTarget = std::dynamic_pointer_cast<KerML::Entities::Type>(target);
        if (!typeTarget) {
            typeTarget = findOrCreateType(pending.typeName);
        }
        if (typeTarget) {
            pending.feature->appendType(typeTarget);
            auto typing = std::make_shared<KerML::Entities::FeatureTyping>(typeTarget, pending.feature);
            pending.feature->appendOwnedTyping(typing);
            pending.feature->appendOwnedElement(typing);
            Elements.push_back(typing);
        }
    }
    pendingTypings_.clear();

    for (const auto& pending : pendingSpecializations_) {
        if (!pending.classifier) continue;
        auto target = resolveElement(pending.superName, pending.classifier);
        auto generalClassifier = std::dynamic_pointer_cast<KerML::Entities::Classifier>(target);
        if (!generalClassifier) {
            generalClassifier = findOrCreateClassifier(pending.superName);
        }
        if (generalClassifier) {
            auto sub = std::make_shared<KerML::Entities::Subclassification>(generalClassifier, pending.classifier);
            pending.classifier->appendOwnedSubclassification(sub);
            pending.classifier->appendOwnedSpecialization(sub);
            pending.classifier->appendOwnedElement(sub);
            Elements.push_back(sub);
        }
    }
    pendingSpecializations_.clear();
}
