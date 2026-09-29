//
// Implicit generalizations of the KerML and SysML v2 model elements. See ImplicitGenerals.h.
//
#include "ImplicitGenerals.h"

#include <kerml/KerML.h>
#include <sysml/SysML.h>

#include <unordered_set>

namespace SysMLv2::Files::Detail {

    namespace {
        using KerML::Entities::Element;

        template <class T>
        bool is(const Element* element) {
            return dynamic_cast<const T*>(element) != nullptr;
        }

        struct Rule {
            bool (*matches)(const Element*);
            std::vector<const char*> names;
        };

        namespace K = KerML::Entities;
        namespace S = SysMLv2::Entities;

        // Most specific first; the first matching rule of the definitions/classifiers and the first one of the usages/features
        // apply. The generalizations of the library elements named here are followed by the resolver.
        const std::vector<Rule>& classifierRules() {
            static const std::vector<Rule> rules = {
                {is<S::ConcernDefinition>, {"Requirements::ConcernCheck"}},
                {is<S::ViewpointDefinition>, {"Views::ViewpointCheck"}},
                {is<S::RequirementDefinition>, {"Requirements::RequirementCheck"}},
                {is<S::ConstraintDefinition>, {"Constraints::ConstraintCheck"}},
                {is<S::UseCaseDefinition>, {"UseCases::UseCase"}},
                {is<S::AnalysisCaseDefinition>, {"AnalysisCases::AnalysisCase"}},
                {is<S::VerificationCaseDefinition>, {"VerificationCases::VerificationCase"}},
                {is<S::CaseDefinition>, {"Cases::Case"}},
                {is<S::CalculationDefinition>, {"Calculations::Calculation"}},
                {is<S::StateDefinition>, {"States::StateAction"}},
                {is<S::FlowDefinition>, {"Flows::Message"}},
                {is<S::ActionDefinition>, {"Actions::Action"}},
                {is<S::InterfaceDefinition>, {"Interfaces::Interface"}},
                {is<S::AllocationDefinition>, {"Allocations::Allocation"}},
                {is<S::ConnectionDefinition>, {"Connections::Connection"}},
                {is<S::PortDefinition>, {"Ports::Port"}},
                {is<S::ViewDefinition>, {"Views::View"}},
                {is<S::RenderingDefinition>, {"Views::Rendering"}},
                {is<S::PartDefinition>, {"Parts::Part"}},
                {is<S::MetadataDefinition>, {"Metadata::MetadataItem", "Metaobjects::Metaobject"}},
                {is<S::ItemDefinition>, {"Items::Item"}},
                {is<S::EnumerationDefinition>, {"Attributes::AttributeValue"}},
                {is<S::AttributeDefinition>, {"Attributes::AttributeValue"}},
                {is<S::OccurrenceDefinition>, {"Occurrences::Occurrence"}},
                {is<K::Metaclass>, {"Metaobjects::Metaobject"}},
                {is<K::AssociationStructure>, {"Objects::LinkObject"}},
                {is<K::Interaction>, {"Transfers::Transfer"}},
                {is<K::Association>, {"Links::Link"}},
                {is<K::Structure>, {"Objects::Object"}},
                {is<K::Predicate>, {"Performances::BooleanEvaluation"}},
                {is<K::Function>, {"Performances::Evaluation"}},
                {is<K::Behavior>, {"Performances::Performance"}},
                {is<K::Class>, {"Occurrences::Occurrence"}},
                {is<K::DataType>, {"Base::DataValue"}},
            };
            return rules;
        }

        const std::vector<Rule>& featureRules() {
            static const std::vector<Rule> rules = {
                {is<S::IncludeUseCaseUsage>, {"UseCases::useCases", "Actions::actions"}},
                {is<S::ConcernUsage>, {"Requirements::concernChecks"}},
                {is<S::SatisfyRequirementUsage>, {"Requirements::requirementChecks"}},
                {is<S::ViewpointUsage>, {"Views::viewpointChecks"}},
                {is<S::RequirementUsage>, {"Requirements::requirementChecks"}},
                {is<S::AssertConstraintUsage>, {"Constraints::constraintChecks"}},
                {is<S::ConstraintUsage>, {"Constraints::constraintChecks"}},
                {is<S::UseCaseUsage>, {"UseCases::useCases"}},
                {is<S::AnalysisCaseUsage>, {"AnalysisCases::analysisCases"}},
                {is<S::VerificationCaseUsage>, {"VerificationCases::verificationCases"}},
                {is<S::CaseUsage>, {"Cases::cases"}},
                {is<S::CalculationUsage>, {"Calculations::calculations"}},
                {is<S::ExhibitStateUsage>, {"States::stateActions"}},
                {is<S::StateUsage>, {"States::stateActions"}},
                {is<S::TransitionUsage>, {"Actions::transitionActions"}},
                {is<S::PerformActionUsage>, {"Actions::actions"}},
                {is<S::SendActionUsage>, {"Actions::sendActions"}},
                {is<S::AcceptActionUsage>, {"Actions::acceptActions"}},
                {is<S::AssignmentActionUsage>, {"Actions::assignmentActions"}},
                {is<S::TerminateActionUsage>, {"Actions::terminateActions"}},
                {is<S::IfActionUsage>, {"Actions::ifThenActions"}},
                {is<S::ForLoopActionUsage>, {"Actions::forLoopActions"}},
                {is<S::WhileLoopActionUsage>, {"Actions::whileLoopActions"}},
                {is<S::LoopActionUsage>, {"Actions::loopActions"}},
                {is<S::MergeNode>, {"Actions::MergeAction"}},
                {is<S::DecisionNode>, {"Actions::DecisionAction"}},
                {is<S::ForkNode>, {"Actions::ForkAction"}},
                {is<S::JoinNode>, {"Actions::JoinAction"}},
                {is<S::SuccessionFlowUsage>, {"Flows::successionFlows"}},
                {is<S::FlowUsage>, {"Flows::messages", "Flows::flows"}},
                {is<S::ActionUsage>, {"Actions::actions"}},
                {is<S::InterfaceUsage>, {"Interfaces::interfaces"}},
                {is<S::AllocationUsage>, {"Allocations::allocations"}},
                {is<S::ConnectionUsage>, {"Connections::connections"}},
                {is<S::BindingConnectorAsUsage>, {"Links::selfLinks"}},
                {is<S::SuccessionAsUsage>, {"Occurrences::happensBeforeLinks"}},
                {is<S::ConnectorAsUsage>, {"Connections::connections"}},
                {is<S::PortUsage>, {"Ports::ports"}},
                {is<S::ViewUsage>, {"Views::views"}},
                {is<S::RenderingUsage>, {"Views::renderings"}},
                {is<S::PartUsage>, {"Parts::parts"}},
                {is<S::MetadataUsage>, {"Metadata::metadataItems", "Metaobjects::metaobjects"}},
                {is<S::ItemUsage>, {"Items::items"}},
                {is<S::EnumerationUsage>, {"Attributes::attributeValues"}},
                {is<S::AttributeUsage>, {"Attributes::attributeValues"}},
                {is<S::EventOccurrenceUsage>, {"Occurrences::occurrences"}},
                {is<S::OccurrenceUsage>, {"Occurrences::occurrences"}},
                {is<K::MetadataFeature>, {"Metaobjects::metaobjects"}},
                {is<K::Invariant>, {"Performances::trueEvaluations"}},
                {is<K::BooleanExpression>, {"Performances::booleanEvaluations"}},
                {is<K::Expression>, {"Performances::evaluations"}},
                {is<K::SuccessionFlow>, {"Transfers::transfersBefore"}},
                {is<K::Flow>, {"Transfers::transfers"}},
                {is<K::Succession>, {"Occurrences::happensBeforeLinks"}},
                {is<K::BindingConnector>, {"Links::selfLinks"}},
                {is<K::Connector>, {"Links::links"}},
                {is<K::Step>, {"Performances::performances"}},
            };
            return rules;
        }
    }

    namespace {
        // The number of end features declared by a type (directly or through the membership that owns them). A feature that is listed
        // both as an owned element of the type and through its membership is counted once.
        size_t countEnds(const Element* type) {
            std::unordered_set<const K::Feature*> counted;
            auto consider = [&counted](const std::shared_ptr<Element>& candidate) {
                if (auto feature = std::dynamic_pointer_cast<K::Feature>(candidate)) {
                    if (feature->isEnd()) counted.insert(feature.get());
                }
            };
            for (const auto& child : const_cast<Element*>(type)->ownedElements()) {
                if (dynamic_cast<const K::Feature*>(child.get()) != nullptr) {
                    consider(child);
                } else if (dynamic_cast<const K::Type*>(child.get()) == nullptr) {
                    for (const auto& grandChild : child->ownedElements()) consider(grandChild);
                }
            }
            return counted.size();
        }
    }

    std::vector<const char*> implicitGenerals(const Element* element) {
        std::vector<const char*> result;
        if (element == nullptr) return result;
        const bool feature = dynamic_cast<const K::Feature*>(element) != nullptr;
        const bool type = feature || dynamic_cast<const K::Type*>(element) != nullptr;
        if (!type) return result;
        // An association, connection or interface with exactly two ends is binary (KerML 9.2.4, SysML 8.x).
        const bool linkLike = is<K::Association>(element) || is<S::ConnectionDefinition>(element) || is<S::InterfaceDefinition>(element) ||
                              is<K::Connector>(element) || is<S::ConnectionUsage>(element) || is<S::InterfaceUsage>(element);
        if (linkLike && countEnds(element) == 2) {
            if (is<S::InterfaceDefinition>(element)) result.push_back("Interfaces::BinaryInterface");
            else if (is<S::InterfaceUsage>(element)) result.push_back("Interfaces::binaryInterfaces");
            else if (is<S::ConnectionDefinition>(element)) result.push_back("Connections::BinaryConnection");
            else if (is<S::ConnectionUsage>(element)) result.push_back("Connections::binaryConnections");
            else if (is<K::AssociationStructure>(element)) result.push_back("Objects::BinaryLinkObject");
            else if (is<K::Association>(element)) result.push_back("Links::BinaryLink");
            else result.push_back("Links::binaryLinks");
        }
        // A type (and a feature) that is itself a classifier - an association or a connector - is looked at as both.
        if (dynamic_cast<const K::Classifier*>(element) != nullptr) {
            for (const auto& rule : classifierRules()) {
                if (rule.matches(element) && !rule.names.empty()) {
                    result.insert(result.end(), rule.names.begin(), rule.names.end());
                    break;
                }
            }
        }
        if (feature) {
            for (const auto& rule : featureRules()) {
                if (rule.matches(element)) {
                    result.insert(result.end(), rule.names.begin(), rule.names.end());
                    break;
                }
            }
            result.push_back("Base::things");
        }
        result.push_back("Base::Anything");
        return result;
    }
}
