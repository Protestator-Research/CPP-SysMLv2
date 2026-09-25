#pragma once

#include <sysmlv2/sysmlv2file_global.h>
#include "antlr4-runtime.h"
#include <sysmlv2/parser/SysMLv2BaseListener.h>
#include <kerml/root/elements/Element.h>
#include <memory>
#include <stack>
#include <string>
#include <vector>
#include <map>

namespace KerML::Entities {
    class Type;
    class Classifier;
    class Feature;
    class Expression;
    class Namespace;
}

/**
 * Implementation of SysMLv2Listener.
 */
class SYSMLV2FILE_EXPORT SysMLv2ListenerImplementation : public SysMLv2BaseListener {
public:
    SysMLv2ListenerImplementation();
    ~SysMLv2ListenerImplementation() override;

    virtual void enterStart(SysMLv2Parser::StartContext* ctx) override;
    virtual void exitStart(SysMLv2Parser::StartContext* ctx) override;

    virtual void enterStart_element(SysMLv2Parser::Start_elementContext* /*ctx*/) override {}
    virtual void exitStart_element(SysMLv2Parser::Start_elementContext* /*ctx*/) override {}

    virtual void enterStartRule(SysMLv2Parser::StartRuleContext* /*ctx*/) override {}
    virtual void exitStartRule(SysMLv2Parser::StartRuleContext* /*ctx*/) override {}

    virtual void enterRelationship_body(SysMLv2Parser::Relationship_bodyContext* /*ctx*/) override {}
    virtual void exitRelationship_body(SysMLv2Parser::Relationship_bodyContext* /*ctx*/) override {}

    virtual void enterDependency(SysMLv2Parser::DependencyContext* ctx) override;
    virtual void exitDependency(SysMLv2Parser::DependencyContext* ctx) override;

    virtual void enterDependency_declaration(SysMLv2Parser::Dependency_declarationContext* /*ctx*/) override {}
    virtual void exitDependency_declaration(SysMLv2Parser::Dependency_declarationContext* /*ctx*/) override {}

    virtual void enterAnnotation(SysMLv2Parser::AnnotationContext* /*ctx*/) override {}
    virtual void exitAnnotation(SysMLv2Parser::AnnotationContext* /*ctx*/) override {}

    virtual void enterOwned_annotation(SysMLv2Parser::Owned_annotationContext* /*ctx*/) override {}
    virtual void exitOwned_annotation(SysMLv2Parser::Owned_annotationContext* /*ctx*/) override {}

    virtual void enterAnnotating_member(SysMLv2Parser::Annotating_memberContext* /*ctx*/) override {}
    virtual void exitAnnotating_member(SysMLv2Parser::Annotating_memberContext* /*ctx*/) override {}

    virtual void enterAnnotating_element(SysMLv2Parser::Annotating_elementContext* ctx) override;
    virtual void exitAnnotating_element(SysMLv2Parser::Annotating_elementContext* ctx) override;

    virtual void enterComment(SysMLv2Parser::CommentContext* /*ctx*/) override {}
    virtual void exitComment(SysMLv2Parser::CommentContext* ctx) override;

    virtual void enterDocumentation(SysMLv2Parser::DocumentationContext* /*ctx*/) override {}
    virtual void exitDocumentation(SysMLv2Parser::DocumentationContext* ctx) override;

    virtual void enterTextual_representation(SysMLv2Parser::Textual_representationContext* /*ctx*/) override {}
    virtual void exitTextual_representation(SysMLv2Parser::Textual_representationContext* ctx) override;

    virtual void enterRoot_namespace(SysMLv2Parser::Root_namespaceContext* /*ctx*/) override {}
    virtual void exitRoot_namespace(SysMLv2Parser::Root_namespaceContext* /*ctx*/) override {}

    virtual void enterPackage(SysMLv2Parser::PackageContext* ctx) override;
    virtual void exitPackage(SysMLv2Parser::PackageContext* ctx) override;

    virtual void enterPackage_body(SysMLv2Parser::Package_bodyContext* /*ctx*/) override {}
    virtual void exitPackage_body(SysMLv2Parser::Package_bodyContext* /*ctx*/) override {}

    virtual void enterPackage_body_element(SysMLv2Parser::Package_body_elementContext* /*ctx*/) override {}
    virtual void exitPackage_body_element(SysMLv2Parser::Package_body_elementContext* /*ctx*/) override {}

    virtual void enterPackage_member(SysMLv2Parser::Package_memberContext* /*ctx*/) override {}
    virtual void exitPackage_member(SysMLv2Parser::Package_memberContext* /*ctx*/) override {}

    virtual void enterAlias_member(SysMLv2Parser::Alias_memberContext* ctx) override;
    virtual void exitAlias_member(SysMLv2Parser::Alias_memberContext* ctx) override;

    virtual void enterDefinition_element(SysMLv2Parser::Definition_elementContext* /*ctx*/) override {}
    virtual void exitDefinition_element(SysMLv2Parser::Definition_elementContext* /*ctx*/) override {}

    virtual void enterUsage_element(SysMLv2Parser::Usage_elementContext* /*ctx*/) override {}
    virtual void exitUsage_element(SysMLv2Parser::Usage_elementContext* /*ctx*/) override {}

    virtual void enterBasic_definition_prefix(SysMLv2Parser::Basic_definition_prefixContext* /*ctx*/) override {}
    virtual void exitBasic_definition_prefix(SysMLv2Parser::Basic_definition_prefixContext* /*ctx*/) override {}

    virtual void enterDefinition_extension_keyword(SysMLv2Parser::Definition_extension_keywordContext* /*ctx*/) override {}
    virtual void exitDefinition_extension_keyword(SysMLv2Parser::Definition_extension_keywordContext* /*ctx*/) override {}

    virtual void enterDefinition_prefix(SysMLv2Parser::Definition_prefixContext* /*ctx*/) override {}
    virtual void exitDefinition_prefix(SysMLv2Parser::Definition_prefixContext* ctx) override;

    virtual void enterDefinition(SysMLv2Parser::DefinitionContext* /*ctx*/) override {}
    virtual void exitDefinition(SysMLv2Parser::DefinitionContext* /*ctx*/) override {}

    virtual void enterDefinition_declaration(SysMLv2Parser::Definition_declarationContext* ctx) override;
    virtual void exitDefinition_declaration(SysMLv2Parser::Definition_declarationContext* ctx) override;

    virtual void enterDefinition_body(SysMLv2Parser::Definition_bodyContext* /*ctx*/) override {}
    virtual void exitDefinition_body(SysMLv2Parser::Definition_bodyContext* /*ctx*/) override {}

    virtual void enterDefinition_body_item(SysMLv2Parser::Definition_body_itemContext* /*ctx*/) override {}
    virtual void exitDefinition_body_item(SysMLv2Parser::Definition_body_itemContext* /*ctx*/) override {}

    virtual void enterDefinition_member(SysMLv2Parser::Definition_memberContext* /*ctx*/) override {}
    virtual void exitDefinition_member(SysMLv2Parser::Definition_memberContext* /*ctx*/) override {}

    virtual void enterVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext* ctx) override;
    virtual void exitVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext* ctx) override;

    virtual void enterNon_occurrence_usage_member(SysMLv2Parser::Non_occurrence_usage_memberContext* /*ctx*/) override {}
    virtual void exitNon_occurrence_usage_member(SysMLv2Parser::Non_occurrence_usage_memberContext* /*ctx*/) override {}

    virtual void enterOccurrence_usage_member(SysMLv2Parser::Occurrence_usage_memberContext* /*ctx*/) override {}
    virtual void exitOccurrence_usage_member(SysMLv2Parser::Occurrence_usage_memberContext* /*ctx*/) override {}

    virtual void enterStructure_usage_member(SysMLv2Parser::Structure_usage_memberContext* /*ctx*/) override {}
    virtual void exitStructure_usage_member(SysMLv2Parser::Structure_usage_memberContext* /*ctx*/) override {}

    virtual void enterBehavior_usage_member(SysMLv2Parser::Behavior_usage_memberContext* /*ctx*/) override {}
    virtual void exitBehavior_usage_member(SysMLv2Parser::Behavior_usage_memberContext* /*ctx*/) override {}

    virtual void enterFeature_direction(SysMLv2Parser::Feature_directionContext* /*ctx*/) override {}
    virtual void exitFeature_direction(SysMLv2Parser::Feature_directionContext* /*ctx*/) override {}

    virtual void enterRef_prefix(SysMLv2Parser::Ref_prefixContext* /*ctx*/) override {}
    virtual void exitRef_prefix(SysMLv2Parser::Ref_prefixContext* /*ctx*/) override {}

    virtual void enterBasic_usage_prefix(SysMLv2Parser::Basic_usage_prefixContext* /*ctx*/) override {}
    virtual void exitBasic_usage_prefix(SysMLv2Parser::Basic_usage_prefixContext* /*ctx*/) override {}

    virtual void enterEnd_usage_prefix(SysMLv2Parser::End_usage_prefixContext* /*ctx*/) override {}
    virtual void exitEnd_usage_prefix(SysMLv2Parser::End_usage_prefixContext* /*ctx*/) override {}

    virtual void enterOwned_cross_feature_member(SysMLv2Parser::Owned_cross_feature_memberContext* /*ctx*/) override {}
    virtual void exitOwned_cross_feature_member(SysMLv2Parser::Owned_cross_feature_memberContext* /*ctx*/) override {}

    virtual void enterOwned_cross_feature(SysMLv2Parser::Owned_cross_featureContext* /*ctx*/) override {}
    virtual void exitOwned_cross_feature(SysMLv2Parser::Owned_cross_featureContext* /*ctx*/) override {}

    virtual void enterUsage_extention_keyword(SysMLv2Parser::Usage_extention_keywordContext* /*ctx*/) override {}
    virtual void exitUsage_extention_keyword(SysMLv2Parser::Usage_extention_keywordContext* /*ctx*/) override {}

    virtual void enterUnextended_usage_prefix(SysMLv2Parser::Unextended_usage_prefixContext* /*ctx*/) override {}
    virtual void exitUnextended_usage_prefix(SysMLv2Parser::Unextended_usage_prefixContext* /*ctx*/) override {}

    virtual void enterUsage_prefix(SysMLv2Parser::Usage_prefixContext* /*ctx*/) override {}
    virtual void exitUsage_prefix(SysMLv2Parser::Usage_prefixContext* ctx) override;

    virtual void enterUsage(SysMLv2Parser::UsageContext* /*ctx*/) override {}
    virtual void exitUsage(SysMLv2Parser::UsageContext* /*ctx*/) override {}

    virtual void enterUsage_declaration(SysMLv2Parser::Usage_declarationContext* ctx) override;
    virtual void exitUsage_declaration(SysMLv2Parser::Usage_declarationContext* ctx) override;

    virtual void enterUsage_completion(SysMLv2Parser::Usage_completionContext* /*ctx*/) override {}
    virtual void exitUsage_completion(SysMLv2Parser::Usage_completionContext* /*ctx*/) override {}

    virtual void enterUsage_body(SysMLv2Parser::Usage_bodyContext* /*ctx*/) override {}
    virtual void exitUsage_body(SysMLv2Parser::Usage_bodyContext* /*ctx*/) override {}

    virtual void enterDefault_reference_usage(SysMLv2Parser::Default_reference_usageContext* ctx) override;
    virtual void exitDefault_reference_usage(SysMLv2Parser::Default_reference_usageContext* ctx) override;

    virtual void enterReference_usage(SysMLv2Parser::Reference_usageContext* ctx) override;
    virtual void exitReference_usage(SysMLv2Parser::Reference_usageContext* ctx) override;

    virtual void enterVariant_reference(SysMLv2Parser::Variant_referenceContext* ctx) override;
    virtual void exitVariant_reference(SysMLv2Parser::Variant_referenceContext* ctx) override;

    virtual void enterRedefinition_usage_element(SysMLv2Parser::Redefinition_usage_elementContext* ctx) override;
    virtual void exitRedefinition_usage_element(SysMLv2Parser::Redefinition_usage_elementContext* ctx) override;

    virtual void enterRedefinition_usage(SysMLv2Parser::Redefinition_usageContext* ctx) override;
    virtual void exitRedefinition_usage(SysMLv2Parser::Redefinition_usageContext* ctx) override;

    virtual void enterNon_occurrence_usage_element(SysMLv2Parser::Non_occurrence_usage_elementContext* /*ctx*/) override {}
    virtual void exitNon_occurrence_usage_element(SysMLv2Parser::Non_occurrence_usage_elementContext* /*ctx*/) override {}

    virtual void enterOccurrence_usage_element(SysMLv2Parser::Occurrence_usage_elementContext* /*ctx*/) override {}
    virtual void exitOccurrence_usage_element(SysMLv2Parser::Occurrence_usage_elementContext* /*ctx*/) override {}

    virtual void enterStructure_usage_element(SysMLv2Parser::Structure_usage_elementContext* /*ctx*/) override {}
    virtual void exitStructure_usage_element(SysMLv2Parser::Structure_usage_elementContext* /*ctx*/) override {}

    virtual void enterBehavior_usage_element(SysMLv2Parser::Behavior_usage_elementContext* /*ctx*/) override {}
    virtual void exitBehavior_usage_element(SysMLv2Parser::Behavior_usage_elementContext* /*ctx*/) override {}

    virtual void enterVariant_usage_element(SysMLv2Parser::Variant_usage_elementContext* /*ctx*/) override {}
    virtual void exitVariant_usage_element(SysMLv2Parser::Variant_usage_elementContext* /*ctx*/) override {}

    virtual void enterSubsclassification_part(SysMLv2Parser::Subsclassification_partContext* /*ctx*/) override {}
    virtual void exitSubsclassification_part(SysMLv2Parser::Subsclassification_partContext* ctx) override;

    virtual void enterCrosses(SysMLv2Parser::CrossesContext* /*ctx*/) override {}
    virtual void exitCrosses(SysMLv2Parser::CrossesContext* /*ctx*/) override {}

    virtual void enterOwned_cross_subsetting(SysMLv2Parser::Owned_cross_subsettingContext* /*ctx*/) override {}
    virtual void exitOwned_cross_subsetting(SysMLv2Parser::Owned_cross_subsettingContext* /*ctx*/) override {}

    virtual void enterMultiplicity_part(SysMLv2Parser::Multiplicity_partContext* /*ctx*/) override {}
    virtual void exitMultiplicity_part(SysMLv2Parser::Multiplicity_partContext* ctx) override;

    virtual void enterOwned_multiplicity(SysMLv2Parser::Owned_multiplicityContext* /*ctx*/) override {}
    virtual void exitOwned_multiplicity(SysMLv2Parser::Owned_multiplicityContext* /*ctx*/) override {}

    virtual void enterMultiplicity_range(SysMLv2Parser::Multiplicity_rangeContext* /*ctx*/) override {}
    virtual void exitMultiplicity_range(SysMLv2Parser::Multiplicity_rangeContext* ctx) override;

    virtual void enterAttribute_definition(SysMLv2Parser::Attribute_definitionContext* ctx) override;
    virtual void exitAttribute_definition(SysMLv2Parser::Attribute_definitionContext* ctx) override;

    virtual void enterAttribute_usage(SysMLv2Parser::Attribute_usageContext* ctx) override;
    virtual void exitAttribute_usage(SysMLv2Parser::Attribute_usageContext* ctx) override;

    virtual void enterEnumeration_definition(SysMLv2Parser::Enumeration_definitionContext* ctx) override;
    virtual void exitEnumeration_definition(SysMLv2Parser::Enumeration_definitionContext* ctx) override;

    virtual void enterEnumeration_body(SysMLv2Parser::Enumeration_bodyContext* /*ctx*/) override {}
    virtual void exitEnumeration_body(SysMLv2Parser::Enumeration_bodyContext* /*ctx*/) override {}

    virtual void enterEnumeration_usage_member(SysMLv2Parser::Enumeration_usage_memberContext* /*ctx*/) override {}
    virtual void exitEnumeration_usage_member(SysMLv2Parser::Enumeration_usage_memberContext* /*ctx*/) override {}

    virtual void enterEnumerated_value(SysMLv2Parser::Enumerated_valueContext* ctx) override;
    virtual void exitEnumerated_value(SysMLv2Parser::Enumerated_valueContext* ctx) override;

    virtual void enterEnumeration_usage(SysMLv2Parser::Enumeration_usageContext* ctx) override;
    virtual void exitEnumeration_usage(SysMLv2Parser::Enumeration_usageContext* ctx) override;

    virtual void enterOccurrence_definition_prefix(SysMLv2Parser::Occurrence_definition_prefixContext* /*ctx*/) override {}
    virtual void exitOccurrence_definition_prefix(SysMLv2Parser::Occurrence_definition_prefixContext* ctx) override;

    virtual void enterOccurrence_definition(SysMLv2Parser::Occurrence_definitionContext* ctx) override;
    virtual void exitOccurrence_definition(SysMLv2Parser::Occurrence_definitionContext* ctx) override;

    virtual void enterIndividual_definition(SysMLv2Parser::Individual_definitionContext* ctx) override;
    virtual void exitIndividual_definition(SysMLv2Parser::Individual_definitionContext* ctx) override;

    virtual void enterOccurrence_usage_prefix(SysMLv2Parser::Occurrence_usage_prefixContext* /*ctx*/) override {}
    virtual void exitOccurrence_usage_prefix(SysMLv2Parser::Occurrence_usage_prefixContext* ctx) override;

    virtual void enterOccurrence_usage(SysMLv2Parser::Occurrence_usageContext* ctx) override;
    virtual void exitOccurrence_usage(SysMLv2Parser::Occurrence_usageContext* ctx) override;

    virtual void enterIndividual_usage(SysMLv2Parser::Individual_usageContext* ctx) override;
    virtual void exitIndividual_usage(SysMLv2Parser::Individual_usageContext* ctx) override;

    virtual void enterPortion_usage(SysMLv2Parser::Portion_usageContext* ctx) override;
    virtual void exitPortion_usage(SysMLv2Parser::Portion_usageContext* ctx) override;

    virtual void enterPortion_kind(SysMLv2Parser::Portion_kindContext* /*ctx*/) override {}
    virtual void exitPortion_kind(SysMLv2Parser::Portion_kindContext* /*ctx*/) override {}

    virtual void enterEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext* ctx) override;
    virtual void exitEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext* ctx) override;

    virtual void enterSource_succession_member(SysMLv2Parser::Source_succession_memberContext* /*ctx*/) override {}
    virtual void exitSource_succession_member(SysMLv2Parser::Source_succession_memberContext* /*ctx*/) override {}

    virtual void enterSource_succession(SysMLv2Parser::Source_successionContext* /*ctx*/) override {}
    virtual void exitSource_succession(SysMLv2Parser::Source_successionContext* /*ctx*/) override {}

    virtual void enterSource_end_member(SysMLv2Parser::Source_end_memberContext* /*ctx*/) override {}
    virtual void exitSource_end_member(SysMLv2Parser::Source_end_memberContext* /*ctx*/) override {}

    virtual void enterSource_end(SysMLv2Parser::Source_endContext* /*ctx*/) override {}
    virtual void exitSource_end(SysMLv2Parser::Source_endContext* /*ctx*/) override {}

    virtual void enterItem_definition(SysMLv2Parser::Item_definitionContext* ctx) override;
    virtual void exitItem_definition(SysMLv2Parser::Item_definitionContext* ctx) override;

    virtual void enterItem_usage(SysMLv2Parser::Item_usageContext* ctx) override;
    virtual void exitItem_usage(SysMLv2Parser::Item_usageContext* ctx) override;

    virtual void enterPart_definition(SysMLv2Parser::Part_definitionContext* ctx) override;
    virtual void exitPart_definition(SysMLv2Parser::Part_definitionContext* ctx) override;

    virtual void enterPart_usage(SysMLv2Parser::Part_usageContext* ctx) override;
    virtual void exitPart_usage(SysMLv2Parser::Part_usageContext* ctx) override;

    virtual void enterPort_definition(SysMLv2Parser::Port_definitionContext* ctx) override;
    virtual void exitPort_definition(SysMLv2Parser::Port_definitionContext* ctx) override;

    virtual void enterPort_usage(SysMLv2Parser::Port_usageContext* ctx) override;
    virtual void exitPort_usage(SysMLv2Parser::Port_usageContext* ctx) override;

    virtual void enterConjungated_port_typing(SysMLv2Parser::Conjungated_port_typingContext* /*ctx*/) override {}
    virtual void exitConjungated_port_typing(SysMLv2Parser::Conjungated_port_typingContext* /*ctx*/) override {}

    virtual void enterConnection_definition(SysMLv2Parser::Connection_definitionContext* ctx) override;
    virtual void exitConnection_definition(SysMLv2Parser::Connection_definitionContext* ctx) override;

    virtual void enterConnection_usage(SysMLv2Parser::Connection_usageContext* ctx) override;
    virtual void exitConnection_usage(SysMLv2Parser::Connection_usageContext* ctx) override;

    virtual void enterConnector_part(SysMLv2Parser::Connector_partContext* /*ctx*/) override {}
    virtual void exitConnector_part(SysMLv2Parser::Connector_partContext* /*ctx*/) override {}

    virtual void enterBinary_connector_part(SysMLv2Parser::Binary_connector_partContext* /*ctx*/) override {}
    virtual void exitBinary_connector_part(SysMLv2Parser::Binary_connector_partContext* /*ctx*/) override {}

    virtual void enterNary_connector_part(SysMLv2Parser::Nary_connector_partContext* /*ctx*/) override {}
    virtual void exitNary_connector_part(SysMLv2Parser::Nary_connector_partContext* /*ctx*/) override {}

    virtual void enterConnector_end_member(SysMLv2Parser::Connector_end_memberContext* /*ctx*/) override {}
    virtual void exitConnector_end_member(SysMLv2Parser::Connector_end_memberContext* /*ctx*/) override {}

    virtual void enterConnecotr_end(SysMLv2Parser::Connecotr_endContext* ctx) override;
    virtual void exitConnecotr_end(SysMLv2Parser::Connecotr_endContext* ctx) override;

    virtual void enterConnector_end(SysMLv2Parser::Connector_endContext* ctx) override;
    virtual void exitConnector_end(SysMLv2Parser::Connector_endContext* ctx) override;

    virtual void enterOwned_cross_multiplicity_member(SysMLv2Parser::Owned_cross_multiplicity_memberContext* /*ctx*/) override {}
    virtual void exitOwned_cross_multiplicity_member(SysMLv2Parser::Owned_cross_multiplicity_memberContext* /*ctx*/) override {}

    virtual void enterOwned_cross_multiplicity(SysMLv2Parser::Owned_cross_multiplicityContext* /*ctx*/) override {}
    virtual void exitOwned_cross_multiplicity(SysMLv2Parser::Owned_cross_multiplicityContext* /*ctx*/) override {}

    virtual void enterBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext* ctx) override;
    virtual void exitBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext* ctx) override;

    virtual void enterBinding_end_usage_member(SysMLv2Parser::Binding_end_usage_memberContext* /*ctx*/) override {}
    virtual void exitBinding_end_usage_member(SysMLv2Parser::Binding_end_usage_memberContext* /*ctx*/) override {}

    virtual void enterSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext* ctx) override;
    virtual void exitSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext* ctx) override;

    virtual void enterInterface_definition(SysMLv2Parser::Interface_definitionContext* ctx) override;
    virtual void exitInterface_definition(SysMLv2Parser::Interface_definitionContext* ctx) override;

    virtual void enterInterface_body(SysMLv2Parser::Interface_bodyContext* /*ctx*/) override {}
    virtual void exitInterface_body(SysMLv2Parser::Interface_bodyContext* /*ctx*/) override {}

    virtual void enterInterface_body_item(SysMLv2Parser::Interface_body_itemContext* /*ctx*/) override {}
    virtual void exitInterface_body_item(SysMLv2Parser::Interface_body_itemContext* /*ctx*/) override {}

    virtual void enterInterface_non_occurrence_usage_member(SysMLv2Parser::Interface_non_occurrence_usage_memberContext* /*ctx*/) override {}
    virtual void exitInterface_non_occurrence_usage_member(SysMLv2Parser::Interface_non_occurrence_usage_memberContext* /*ctx*/) override {}

    virtual void enterInterface_non_occurrence_usage_element(SysMLv2Parser::Interface_non_occurrence_usage_elementContext* /*ctx*/) override {}
    virtual void exitInterface_non_occurrence_usage_element(SysMLv2Parser::Interface_non_occurrence_usage_elementContext* /*ctx*/) override {}

    virtual void enterInterface_occurrence_usage_member(SysMLv2Parser::Interface_occurrence_usage_memberContext* /*ctx*/) override {}
    virtual void exitInterface_occurrence_usage_member(SysMLv2Parser::Interface_occurrence_usage_memberContext* /*ctx*/) override {}

    virtual void enterInterface_occurrence_usage_element(SysMLv2Parser::Interface_occurrence_usage_elementContext* /*ctx*/) override {}
    virtual void exitInterface_occurrence_usage_element(SysMLv2Parser::Interface_occurrence_usage_elementContext* /*ctx*/) override {}

    virtual void enterDefault_interface_end(SysMLv2Parser::Default_interface_endContext* /*ctx*/) override {}
    virtual void exitDefault_interface_end(SysMLv2Parser::Default_interface_endContext* /*ctx*/) override {}

    virtual void enterInterface_usage(SysMLv2Parser::Interface_usageContext* ctx) override;
    virtual void exitInterface_usage(SysMLv2Parser::Interface_usageContext* ctx) override;

    virtual void enterInterface_usage_declaration(SysMLv2Parser::Interface_usage_declarationContext* /*ctx*/) override {}
    virtual void exitInterface_usage_declaration(SysMLv2Parser::Interface_usage_declarationContext* /*ctx*/) override {}

    virtual void enterInterface_part(SysMLv2Parser::Interface_partContext* /*ctx*/) override {}
    virtual void exitInterface_part(SysMLv2Parser::Interface_partContext* /*ctx*/) override {}

    virtual void enterBinary_interface_part(SysMLv2Parser::Binary_interface_partContext* /*ctx*/) override {}
    virtual void exitBinary_interface_part(SysMLv2Parser::Binary_interface_partContext* /*ctx*/) override {}

    virtual void enterNary_interface_part(SysMLv2Parser::Nary_interface_partContext* /*ctx*/) override {}
    virtual void exitNary_interface_part(SysMLv2Parser::Nary_interface_partContext* /*ctx*/) override {}

    virtual void enterInterface_end_member(SysMLv2Parser::Interface_end_memberContext* /*ctx*/) override {}
    virtual void exitInterface_end_member(SysMLv2Parser::Interface_end_memberContext* /*ctx*/) override {}

    virtual void enterInterface_end(SysMLv2Parser::Interface_endContext* /*ctx*/) override {}
    virtual void exitInterface_end(SysMLv2Parser::Interface_endContext* /*ctx*/) override {}

    virtual void enterAllocation_definition(SysMLv2Parser::Allocation_definitionContext* ctx) override;
    virtual void exitAllocation_definition(SysMLv2Parser::Allocation_definitionContext* ctx) override;

    virtual void enterAllocation_usage(SysMLv2Parser::Allocation_usageContext* ctx) override;
    virtual void exitAllocation_usage(SysMLv2Parser::Allocation_usageContext* ctx) override;

    virtual void enterAllocation_usage_declaration(SysMLv2Parser::Allocation_usage_declarationContext* /*ctx*/) override {}
    virtual void exitAllocation_usage_declaration(SysMLv2Parser::Allocation_usage_declarationContext* /*ctx*/) override {}

    virtual void enterFlow_definition(SysMLv2Parser::Flow_definitionContext* ctx) override;
    virtual void exitFlow_definition(SysMLv2Parser::Flow_definitionContext* ctx) override;

    virtual void enterMessage(SysMLv2Parser::MessageContext* ctx) override;
    virtual void exitMessage(SysMLv2Parser::MessageContext* ctx) override;

    virtual void enterMessage_declaration(SysMLv2Parser::Message_declarationContext* /*ctx*/) override {}
    virtual void exitMessage_declaration(SysMLv2Parser::Message_declarationContext* /*ctx*/) override {}

    virtual void enterMessage_event_member(SysMLv2Parser::Message_event_memberContext* /*ctx*/) override {}
    virtual void exitMessage_event_member(SysMLv2Parser::Message_event_memberContext* /*ctx*/) override {}

    virtual void enterMessage_event(SysMLv2Parser::Message_eventContext* /*ctx*/) override {}
    virtual void exitMessage_event(SysMLv2Parser::Message_eventContext* /*ctx*/) override {}

    virtual void enterFlow_usage(SysMLv2Parser::Flow_usageContext* ctx) override;
    virtual void exitFlow_usage(SysMLv2Parser::Flow_usageContext* ctx) override;

    virtual void enterSuccession_flow_usage(SysMLv2Parser::Succession_flow_usageContext* ctx) override;
    virtual void exitSuccession_flow_usage(SysMLv2Parser::Succession_flow_usageContext* ctx) override;

    virtual void enterFlow_declaration(SysMLv2Parser::Flow_declarationContext* /*ctx*/) override {}
    virtual void exitFlow_declaration(SysMLv2Parser::Flow_declarationContext* /*ctx*/) override {}

    virtual void enterFlow_payload_feature_member(SysMLv2Parser::Flow_payload_feature_memberContext* /*ctx*/) override {}
    virtual void exitFlow_payload_feature_member(SysMLv2Parser::Flow_payload_feature_memberContext* /*ctx*/) override {}

    virtual void enterFlow_payload_feature(SysMLv2Parser::Flow_payload_featureContext* /*ctx*/) override {}
    virtual void exitFlow_payload_feature(SysMLv2Parser::Flow_payload_featureContext* /*ctx*/) override {}

    virtual void enterPayload_feature(SysMLv2Parser::Payload_featureContext* /*ctx*/) override {}
    virtual void exitPayload_feature(SysMLv2Parser::Payload_featureContext* /*ctx*/) override {}

    virtual void enterPayload_feature_specialization_part(SysMLv2Parser::Payload_feature_specialization_partContext* /*ctx*/) override {}
    virtual void exitPayload_feature_specialization_part(SysMLv2Parser::Payload_feature_specialization_partContext* /*ctx*/) override {}

    virtual void enterFlow_end_member(SysMLv2Parser::Flow_end_memberContext* /*ctx*/) override {}
    virtual void exitFlow_end_member(SysMLv2Parser::Flow_end_memberContext* /*ctx*/) override {}

    virtual void enterFlow_end(SysMLv2Parser::Flow_endContext* /*ctx*/) override {}
    virtual void exitFlow_end(SysMLv2Parser::Flow_endContext* /*ctx*/) override {}

    virtual void enterFlow_end_subsetting(SysMLv2Parser::Flow_end_subsettingContext* /*ctx*/) override {}
    virtual void exitFlow_end_subsetting(SysMLv2Parser::Flow_end_subsettingContext* /*ctx*/) override {}

    virtual void enterFeature_chain_prefix(SysMLv2Parser::Feature_chain_prefixContext* /*ctx*/) override {}
    virtual void exitFeature_chain_prefix(SysMLv2Parser::Feature_chain_prefixContext* /*ctx*/) override {}

    virtual void enterFlow_feature_member(SysMLv2Parser::Flow_feature_memberContext* /*ctx*/) override {}
    virtual void exitFlow_feature_member(SysMLv2Parser::Flow_feature_memberContext* /*ctx*/) override {}

    virtual void enterFlow_feature(SysMLv2Parser::Flow_featureContext* /*ctx*/) override {}
    virtual void exitFlow_feature(SysMLv2Parser::Flow_featureContext* /*ctx*/) override {}

    virtual void enterFlow_feature_redefinition(SysMLv2Parser::Flow_feature_redefinitionContext* /*ctx*/) override {}
    virtual void exitFlow_feature_redefinition(SysMLv2Parser::Flow_feature_redefinitionContext* /*ctx*/) override {}

    virtual void enterAction_definition(SysMLv2Parser::Action_definitionContext* ctx) override;
    virtual void exitAction_definition(SysMLv2Parser::Action_definitionContext* ctx) override;

    virtual void enterAction_body(SysMLv2Parser::Action_bodyContext* /*ctx*/) override {}
    virtual void exitAction_body(SysMLv2Parser::Action_bodyContext* /*ctx*/) override {}

    virtual void enterAction_body_item(SysMLv2Parser::Action_body_itemContext* /*ctx*/) override {}
    virtual void exitAction_body_item(SysMLv2Parser::Action_body_itemContext* /*ctx*/) override {}

    virtual void enterNon_behavior_body_item(SysMLv2Parser::Non_behavior_body_itemContext* /*ctx*/) override {}
    virtual void exitNon_behavior_body_item(SysMLv2Parser::Non_behavior_body_itemContext* /*ctx*/) override {}

    virtual void enterAction_behavior_member(SysMLv2Parser::Action_behavior_memberContext* /*ctx*/) override {}
    virtual void exitAction_behavior_member(SysMLv2Parser::Action_behavior_memberContext* /*ctx*/) override {}

    virtual void enterInitial_node_member(SysMLv2Parser::Initial_node_memberContext* /*ctx*/) override {}
    virtual void exitInitial_node_member(SysMLv2Parser::Initial_node_memberContext* /*ctx*/) override {}

    virtual void enterAction_node_member(SysMLv2Parser::Action_node_memberContext* /*ctx*/) override {}
    virtual void exitAction_node_member(SysMLv2Parser::Action_node_memberContext* /*ctx*/) override {}

    virtual void enterAction_target_succession_member(SysMLv2Parser::Action_target_succession_memberContext* /*ctx*/) override {}
    virtual void exitAction_target_succession_member(SysMLv2Parser::Action_target_succession_memberContext* /*ctx*/) override {}

    virtual void enterGuarded_succession_member(SysMLv2Parser::Guarded_succession_memberContext* /*ctx*/) override {}
    virtual void exitGuarded_succession_member(SysMLv2Parser::Guarded_succession_memberContext* /*ctx*/) override {}

    virtual void enterAction_usage(SysMLv2Parser::Action_usageContext* ctx) override;
    virtual void exitAction_usage(SysMLv2Parser::Action_usageContext* ctx) override;

    virtual void enterAction_usage_declaration(SysMLv2Parser::Action_usage_declarationContext* /*ctx*/) override {}
    virtual void exitAction_usage_declaration(SysMLv2Parser::Action_usage_declarationContext* /*ctx*/) override {}

    virtual void enterPerform_action_usage(SysMLv2Parser::Perform_action_usageContext* ctx) override;
    virtual void exitPerform_action_usage(SysMLv2Parser::Perform_action_usageContext* ctx) override;

    virtual void enterPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext* ctx) override;
    virtual void exitPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext* ctx) override;

    virtual void enterAction_node(SysMLv2Parser::Action_nodeContext* /*ctx*/) override {}
    virtual void exitAction_node(SysMLv2Parser::Action_nodeContext* /*ctx*/) override {}

    virtual void enterAction_node_usage_declaration(SysMLv2Parser::Action_node_usage_declarationContext* /*ctx*/) override {}
    virtual void exitAction_node_usage_declaration(SysMLv2Parser::Action_node_usage_declarationContext* /*ctx*/) override {}

    virtual void enterAction_node_prefix(SysMLv2Parser::Action_node_prefixContext* /*ctx*/) override {}
    virtual void exitAction_node_prefix(SysMLv2Parser::Action_node_prefixContext* /*ctx*/) override {}

    virtual void enterControl_node(SysMLv2Parser::Control_nodeContext* /*ctx*/) override {}
    virtual void exitControl_node(SysMLv2Parser::Control_nodeContext* /*ctx*/) override {}

    virtual void enterControl_node_prefix(SysMLv2Parser::Control_node_prefixContext* /*ctx*/) override {}
    virtual void exitControl_node_prefix(SysMLv2Parser::Control_node_prefixContext* /*ctx*/) override {}

    virtual void enterMerge_node(SysMLv2Parser::Merge_nodeContext* /*ctx*/) override {}
    virtual void exitMerge_node(SysMLv2Parser::Merge_nodeContext* /*ctx*/) override {}

    virtual void enterDecision_node(SysMLv2Parser::Decision_nodeContext* /*ctx*/) override {}
    virtual void exitDecision_node(SysMLv2Parser::Decision_nodeContext* /*ctx*/) override {}

    virtual void enterJoin_node(SysMLv2Parser::Join_nodeContext* /*ctx*/) override {}
    virtual void exitJoin_node(SysMLv2Parser::Join_nodeContext* /*ctx*/) override {}

    virtual void enterFork_node(SysMLv2Parser::Fork_nodeContext* /*ctx*/) override {}
    virtual void exitFork_node(SysMLv2Parser::Fork_nodeContext* /*ctx*/) override {}

    virtual void enterAccept_node(SysMLv2Parser::Accept_nodeContext* /*ctx*/) override {}
    virtual void exitAccept_node(SysMLv2Parser::Accept_nodeContext* /*ctx*/) override {}

    virtual void enterAccept_node_declaration(SysMLv2Parser::Accept_node_declarationContext* /*ctx*/) override {}
    virtual void exitAccept_node_declaration(SysMLv2Parser::Accept_node_declarationContext* /*ctx*/) override {}

    virtual void enterAccept_parameter_part(SysMLv2Parser::Accept_parameter_partContext* /*ctx*/) override {}
    virtual void exitAccept_parameter_part(SysMLv2Parser::Accept_parameter_partContext* /*ctx*/) override {}

    virtual void enterPayload_parameter_member(SysMLv2Parser::Payload_parameter_memberContext* /*ctx*/) override {}
    virtual void exitPayload_parameter_member(SysMLv2Parser::Payload_parameter_memberContext* /*ctx*/) override {}

    virtual void enterPayload_parameter(SysMLv2Parser::Payload_parameterContext* /*ctx*/) override {}
    virtual void exitPayload_parameter(SysMLv2Parser::Payload_parameterContext* /*ctx*/) override {}

    virtual void enterTrigger_value_part(SysMLv2Parser::Trigger_value_partContext* /*ctx*/) override {}
    virtual void exitTrigger_value_part(SysMLv2Parser::Trigger_value_partContext* /*ctx*/) override {}

    virtual void enterTrigger_expression(SysMLv2Parser::Trigger_expressionContext* /*ctx*/) override {}
    virtual void exitTrigger_expression(SysMLv2Parser::Trigger_expressionContext* /*ctx*/) override {}

    virtual void enterSend_node(SysMLv2Parser::Send_nodeContext* /*ctx*/) override {}
    virtual void exitSend_node(SysMLv2Parser::Send_nodeContext* /*ctx*/) override {}

    virtual void enterSend_node_declaration(SysMLv2Parser::Send_node_declarationContext* /*ctx*/) override {}
    virtual void exitSend_node_declaration(SysMLv2Parser::Send_node_declarationContext* /*ctx*/) override {}

    virtual void enterSender_receiver_part(SysMLv2Parser::Sender_receiver_partContext* /*ctx*/) override {}
    virtual void exitSender_receiver_part(SysMLv2Parser::Sender_receiver_partContext* /*ctx*/) override {}

    virtual void enterNode_parameter_member(SysMLv2Parser::Node_parameter_memberContext* /*ctx*/) override {}
    virtual void exitNode_parameter_member(SysMLv2Parser::Node_parameter_memberContext* /*ctx*/) override {}

    virtual void enterNode_parameter(SysMLv2Parser::Node_parameterContext* /*ctx*/) override {}
    virtual void exitNode_parameter(SysMLv2Parser::Node_parameterContext* /*ctx*/) override {}

    virtual void enterFeature_binding(SysMLv2Parser::Feature_bindingContext* /*ctx*/) override {}
    virtual void exitFeature_binding(SysMLv2Parser::Feature_bindingContext* /*ctx*/) override {}

    virtual void enterAssignment_node(SysMLv2Parser::Assignment_nodeContext* /*ctx*/) override {}
    virtual void exitAssignment_node(SysMLv2Parser::Assignment_nodeContext* /*ctx*/) override {}

    virtual void enterAssignment_node_declaration(SysMLv2Parser::Assignment_node_declarationContext* /*ctx*/) override {}
    virtual void exitAssignment_node_declaration(SysMLv2Parser::Assignment_node_declarationContext* /*ctx*/) override {}

    virtual void enterAssignment_target_member(SysMLv2Parser::Assignment_target_memberContext* /*ctx*/) override {}
    virtual void exitAssignment_target_member(SysMLv2Parser::Assignment_target_memberContext* /*ctx*/) override {}

    virtual void enterAssignment_target_parameter(SysMLv2Parser::Assignment_target_parameterContext* /*ctx*/) override {}
    virtual void exitAssignment_target_parameter(SysMLv2Parser::Assignment_target_parameterContext* /*ctx*/) override {}

    virtual void enterAssignment_target_binding(SysMLv2Parser::Assignment_target_bindingContext* /*ctx*/) override {}
    virtual void exitAssignment_target_binding(SysMLv2Parser::Assignment_target_bindingContext* /*ctx*/) override {}

    virtual void enterFeature_chain_member(SysMLv2Parser::Feature_chain_memberContext* /*ctx*/) override {}
    virtual void exitFeature_chain_member(SysMLv2Parser::Feature_chain_memberContext* /*ctx*/) override {}

    virtual void enterOwned_feature_chain_member(SysMLv2Parser::Owned_feature_chain_memberContext* /*ctx*/) override {}
    virtual void exitOwned_feature_chain_member(SysMLv2Parser::Owned_feature_chain_memberContext* /*ctx*/) override {}

    virtual void enterTerminate_node(SysMLv2Parser::Terminate_nodeContext* /*ctx*/) override {}
    virtual void exitTerminate_node(SysMLv2Parser::Terminate_nodeContext* /*ctx*/) override {}

    virtual void enterIf_node(SysMLv2Parser::If_nodeContext* /*ctx*/) override {}
    virtual void exitIf_node(SysMLv2Parser::If_nodeContext* /*ctx*/) override {}

    virtual void enterExpression_parameter_member(SysMLv2Parser::Expression_parameter_memberContext* /*ctx*/) override {}
    virtual void exitExpression_parameter_member(SysMLv2Parser::Expression_parameter_memberContext* /*ctx*/) override {}

    virtual void enterAction_body_parameter_member(SysMLv2Parser::Action_body_parameter_memberContext* /*ctx*/) override {}
    virtual void exitAction_body_parameter_member(SysMLv2Parser::Action_body_parameter_memberContext* /*ctx*/) override {}

    virtual void enterAction_body_parameter(SysMLv2Parser::Action_body_parameterContext* /*ctx*/) override {}
    virtual void exitAction_body_parameter(SysMLv2Parser::Action_body_parameterContext* /*ctx*/) override {}

    virtual void enterIf_node_parameter_member(SysMLv2Parser::If_node_parameter_memberContext* /*ctx*/) override {}
    virtual void exitIf_node_parameter_member(SysMLv2Parser::If_node_parameter_memberContext* /*ctx*/) override {}

    virtual void enterWhile_loop_node(SysMLv2Parser::While_loop_nodeContext* /*ctx*/) override {}
    virtual void exitWhile_loop_node(SysMLv2Parser::While_loop_nodeContext* /*ctx*/) override {}

    virtual void enterFor_loop_node(SysMLv2Parser::For_loop_nodeContext* /*ctx*/) override {}
    virtual void exitFor_loop_node(SysMLv2Parser::For_loop_nodeContext* /*ctx*/) override {}

    virtual void enterFor_variable_declaration_member(SysMLv2Parser::For_variable_declaration_memberContext* /*ctx*/) override {}
    virtual void exitFor_variable_declaration_member(SysMLv2Parser::For_variable_declaration_memberContext* /*ctx*/) override {}

    virtual void enterFor_variable_declaration(SysMLv2Parser::For_variable_declarationContext* /*ctx*/) override {}
    virtual void exitFor_variable_declaration(SysMLv2Parser::For_variable_declarationContext* /*ctx*/) override {}

    virtual void enterAction_target_succession(SysMLv2Parser::Action_target_successionContext* /*ctx*/) override {}
    virtual void exitAction_target_succession(SysMLv2Parser::Action_target_successionContext* /*ctx*/) override {}

    virtual void enterTarget_succession(SysMLv2Parser::Target_successionContext* /*ctx*/) override {}
    virtual void exitTarget_succession(SysMLv2Parser::Target_successionContext* /*ctx*/) override {}

    virtual void enterGuarded_target_succession(SysMLv2Parser::Guarded_target_successionContext* /*ctx*/) override {}
    virtual void exitGuarded_target_succession(SysMLv2Parser::Guarded_target_successionContext* /*ctx*/) override {}

    virtual void enterDefault_target_succession(SysMLv2Parser::Default_target_successionContext* /*ctx*/) override {}
    virtual void exitDefault_target_succession(SysMLv2Parser::Default_target_successionContext* /*ctx*/) override {}

    virtual void enterGuarded_succession(SysMLv2Parser::Guarded_successionContext* /*ctx*/) override {}
    virtual void exitGuarded_succession(SysMLv2Parser::Guarded_successionContext* /*ctx*/) override {}

    virtual void enterState_definition(SysMLv2Parser::State_definitionContext* ctx) override;
    virtual void exitState_definition(SysMLv2Parser::State_definitionContext* ctx) override;

    virtual void enterState_def_body(SysMLv2Parser::State_def_bodyContext* /*ctx*/) override {}
    virtual void exitState_def_body(SysMLv2Parser::State_def_bodyContext* /*ctx*/) override {}

    virtual void enterState_body_item(SysMLv2Parser::State_body_itemContext* /*ctx*/) override {}
    virtual void exitState_body_item(SysMLv2Parser::State_body_itemContext* /*ctx*/) override {}

    virtual void enterEntry_action_member(SysMLv2Parser::Entry_action_memberContext* /*ctx*/) override {}
    virtual void exitEntry_action_member(SysMLv2Parser::Entry_action_memberContext* /*ctx*/) override {}

    virtual void enterDo_action_member(SysMLv2Parser::Do_action_memberContext* /*ctx*/) override {}
    virtual void exitDo_action_member(SysMLv2Parser::Do_action_memberContext* /*ctx*/) override {}

    virtual void enterExit_action_member(SysMLv2Parser::Exit_action_memberContext* /*ctx*/) override {}
    virtual void exitExit_action_member(SysMLv2Parser::Exit_action_memberContext* /*ctx*/) override {}

    virtual void enterEntry_transition_member(SysMLv2Parser::Entry_transition_memberContext* /*ctx*/) override {}
    virtual void exitEntry_transition_member(SysMLv2Parser::Entry_transition_memberContext* /*ctx*/) override {}

    virtual void enterState_action_usage(SysMLv2Parser::State_action_usageContext* /*ctx*/) override {}
    virtual void exitState_action_usage(SysMLv2Parser::State_action_usageContext* /*ctx*/) override {}

    virtual void enterEmpty_action_usage(SysMLv2Parser::Empty_action_usageContext* /*ctx*/) override {}
    virtual void exitEmpty_action_usage(SysMLv2Parser::Empty_action_usageContext* /*ctx*/) override {}

    virtual void enterState_perform_action_uage(SysMLv2Parser::State_perform_action_uageContext* /*ctx*/) override {}
    virtual void exitState_perform_action_uage(SysMLv2Parser::State_perform_action_uageContext* /*ctx*/) override {}

    virtual void enterState_accept_action_usage(SysMLv2Parser::State_accept_action_usageContext* /*ctx*/) override {}
    virtual void exitState_accept_action_usage(SysMLv2Parser::State_accept_action_usageContext* /*ctx*/) override {}

    virtual void enterState_send_action_usage(SysMLv2Parser::State_send_action_usageContext* /*ctx*/) override {}
    virtual void exitState_send_action_usage(SysMLv2Parser::State_send_action_usageContext* /*ctx*/) override {}

    virtual void enterState_assignment_action_usage(SysMLv2Parser::State_assignment_action_usageContext* /*ctx*/) override {}
    virtual void exitState_assignment_action_usage(SysMLv2Parser::State_assignment_action_usageContext* /*ctx*/) override {}

    virtual void enterTransition_usage_member(SysMLv2Parser::Transition_usage_memberContext* /*ctx*/) override {}
    virtual void exitTransition_usage_member(SysMLv2Parser::Transition_usage_memberContext* /*ctx*/) override {}

    virtual void enterTarget_transition_usage_member(SysMLv2Parser::Target_transition_usage_memberContext* /*ctx*/) override {}
    virtual void exitTarget_transition_usage_member(SysMLv2Parser::Target_transition_usage_memberContext* /*ctx*/) override {}

    virtual void enterState_usage(SysMLv2Parser::State_usageContext* ctx) override;
    virtual void exitState_usage(SysMLv2Parser::State_usageContext* ctx) override;

    virtual void enterState_usage_body(SysMLv2Parser::State_usage_bodyContext* /*ctx*/) override {}
    virtual void exitState_usage_body(SysMLv2Parser::State_usage_bodyContext* /*ctx*/) override {}

    virtual void enterExhibit_state_usage(SysMLv2Parser::Exhibit_state_usageContext* ctx) override;
    virtual void exitExhibit_state_usage(SysMLv2Parser::Exhibit_state_usageContext* ctx) override;

    virtual void enterTransition_usage(SysMLv2Parser::Transition_usageContext* /*ctx*/) override {}
    virtual void exitTransition_usage(SysMLv2Parser::Transition_usageContext* /*ctx*/) override {}

    virtual void enterTarget_transition_usage(SysMLv2Parser::Target_transition_usageContext* /*ctx*/) override {}
    virtual void exitTarget_transition_usage(SysMLv2Parser::Target_transition_usageContext* /*ctx*/) override {}

    virtual void enterTrigger_action_member(SysMLv2Parser::Trigger_action_memberContext* /*ctx*/) override {}
    virtual void exitTrigger_action_member(SysMLv2Parser::Trigger_action_memberContext* /*ctx*/) override {}

    virtual void enterTrigger_action(SysMLv2Parser::Trigger_actionContext* /*ctx*/) override {}
    virtual void exitTrigger_action(SysMLv2Parser::Trigger_actionContext* /*ctx*/) override {}

    virtual void enterGuard_expression_member(SysMLv2Parser::Guard_expression_memberContext* /*ctx*/) override {}
    virtual void exitGuard_expression_member(SysMLv2Parser::Guard_expression_memberContext* /*ctx*/) override {}

    virtual void enterEffect_behavior_member(SysMLv2Parser::Effect_behavior_memberContext* /*ctx*/) override {}
    virtual void exitEffect_behavior_member(SysMLv2Parser::Effect_behavior_memberContext* /*ctx*/) override {}

    virtual void enterTransition_succession_member(SysMLv2Parser::Transition_succession_memberContext* /*ctx*/) override {}
    virtual void exitTransition_succession_member(SysMLv2Parser::Transition_succession_memberContext* /*ctx*/) override {}

    virtual void enterTransition_succession(SysMLv2Parser::Transition_successionContext* /*ctx*/) override {}
    virtual void exitTransition_succession(SysMLv2Parser::Transition_successionContext* /*ctx*/) override {}

    virtual void enterCalculation_definition(SysMLv2Parser::Calculation_definitionContext* ctx) override;
    virtual void exitCalculation_definition(SysMLv2Parser::Calculation_definitionContext* ctx) override;

    virtual void enterCalculation_body(SysMLv2Parser::Calculation_bodyContext* /*ctx*/) override {}
    virtual void exitCalculation_body(SysMLv2Parser::Calculation_bodyContext* /*ctx*/) override {}

    virtual void enterCalculation_body_item(SysMLv2Parser::Calculation_body_itemContext* /*ctx*/) override {}
    virtual void exitCalculation_body_item(SysMLv2Parser::Calculation_body_itemContext* /*ctx*/) override {}

    virtual void enterCalculation_usage(SysMLv2Parser::Calculation_usageContext* ctx) override;
    virtual void exitCalculation_usage(SysMLv2Parser::Calculation_usageContext* ctx) override;

    virtual void enterConstraint_definition(SysMLv2Parser::Constraint_definitionContext* ctx) override;
    virtual void exitConstraint_definition(SysMLv2Parser::Constraint_definitionContext* ctx) override;

    virtual void enterConstraint_usage(SysMLv2Parser::Constraint_usageContext* ctx) override;
    virtual void exitConstraint_usage(SysMLv2Parser::Constraint_usageContext* ctx) override;

    virtual void enterConstraint_usage_declaration(SysMLv2Parser::Constraint_usage_declarationContext* /*ctx*/) override {}
    virtual void exitConstraint_usage_declaration(SysMLv2Parser::Constraint_usage_declarationContext* /*ctx*/) override {}

    virtual void enterAssert_constriant_usage(SysMLv2Parser::Assert_constriant_usageContext* ctx) override;
    virtual void exitAssert_constriant_usage(SysMLv2Parser::Assert_constriant_usageContext* ctx) override;

    virtual void enterRequirement_definition(SysMLv2Parser::Requirement_definitionContext* ctx) override;
    virtual void exitRequirement_definition(SysMLv2Parser::Requirement_definitionContext* ctx) override;

    virtual void enterRequirement_body(SysMLv2Parser::Requirement_bodyContext* /*ctx*/) override {}
    virtual void exitRequirement_body(SysMLv2Parser::Requirement_bodyContext* /*ctx*/) override {}

    virtual void enterRequirement_body_item(SysMLv2Parser::Requirement_body_itemContext* /*ctx*/) override {}
    virtual void exitRequirement_body_item(SysMLv2Parser::Requirement_body_itemContext* /*ctx*/) override {}

    virtual void enterRequirement_usage(SysMLv2Parser::Requirement_usageContext* ctx) override;
    virtual void exitRequirement_usage(SysMLv2Parser::Requirement_usageContext* ctx) override;

    virtual void enterRequirement_constraint_member(SysMLv2Parser::Requirement_constraint_memberContext* /*ctx*/) override {}
    virtual void exitRequirement_constraint_member(SysMLv2Parser::Requirement_constraint_memberContext* /*ctx*/) override {}

    virtual void enterRequirement_constraint_usage(SysMLv2Parser::Requirement_constraint_usageContext* /*ctx*/) override {}
    virtual void exitRequirement_constraint_usage(SysMLv2Parser::Requirement_constraint_usageContext* /*ctx*/) override {}

    virtual void enterFramed_concern_member(SysMLv2Parser::Framed_concern_memberContext* /*ctx*/) override {}
    virtual void exitFramed_concern_member(SysMLv2Parser::Framed_concern_memberContext* /*ctx*/) override {}

    virtual void enterFramed_concern_usage(SysMLv2Parser::Framed_concern_usageContext* /*ctx*/) override {}
    virtual void exitFramed_concern_usage(SysMLv2Parser::Framed_concern_usageContext* /*ctx*/) override {}

    virtual void enterActor_member(SysMLv2Parser::Actor_memberContext* /*ctx*/) override {}
    virtual void exitActor_member(SysMLv2Parser::Actor_memberContext* /*ctx*/) override {}

    virtual void enterActor_usage(SysMLv2Parser::Actor_usageContext* /*ctx*/) override {}
    virtual void exitActor_usage(SysMLv2Parser::Actor_usageContext* /*ctx*/) override {}

    virtual void enterStakeholder_member(SysMLv2Parser::Stakeholder_memberContext* /*ctx*/) override {}
    virtual void exitStakeholder_member(SysMLv2Parser::Stakeholder_memberContext* /*ctx*/) override {}

    virtual void enterStakeholder_usage(SysMLv2Parser::Stakeholder_usageContext* /*ctx*/) override {}
    virtual void exitStakeholder_usage(SysMLv2Parser::Stakeholder_usageContext* /*ctx*/) override {}

    virtual void enterSubject_member(SysMLv2Parser::Subject_memberContext* ctx) override;
    virtual void exitSubject_member(SysMLv2Parser::Subject_memberContext* ctx) override;

    virtual void enterSubject_usage(SysMLv2Parser::Subject_usageContext* ctx) override;
    virtual void exitSubject_usage(SysMLv2Parser::Subject_usageContext* ctx) override;

    virtual void enterSatisfy_requirement_usage(SysMLv2Parser::Satisfy_requirement_usageContext* ctx) override;
    virtual void exitSatisfy_requirement_usage(SysMLv2Parser::Satisfy_requirement_usageContext* ctx) override;

    virtual void enterSatisfaction_subject_member(SysMLv2Parser::Satisfaction_subject_memberContext* /*ctx*/) override {}
    virtual void exitSatisfaction_subject_member(SysMLv2Parser::Satisfaction_subject_memberContext* /*ctx*/) override {}

    virtual void enterSatisfaction_parameter(SysMLv2Parser::Satisfaction_parameterContext* /*ctx*/) override {}
    virtual void exitSatisfaction_parameter(SysMLv2Parser::Satisfaction_parameterContext* /*ctx*/) override {}

    virtual void enterSatisfaction_feature_value(SysMLv2Parser::Satisfaction_feature_valueContext* /*ctx*/) override {}
    virtual void exitSatisfaction_feature_value(SysMLv2Parser::Satisfaction_feature_valueContext* /*ctx*/) override {}

    virtual void enterSatisfaction_reference_expression(SysMLv2Parser::Satisfaction_reference_expressionContext* /*ctx*/) override {}
    virtual void exitSatisfaction_reference_expression(SysMLv2Parser::Satisfaction_reference_expressionContext* /*ctx*/) override {}

    virtual void enterConcern_definition(SysMLv2Parser::Concern_definitionContext* ctx) override;
    virtual void exitConcern_definition(SysMLv2Parser::Concern_definitionContext* ctx) override;

    virtual void enterConcern_usage(SysMLv2Parser::Concern_usageContext* ctx) override;
    virtual void exitConcern_usage(SysMLv2Parser::Concern_usageContext* ctx) override;

    virtual void enterCase_definition(SysMLv2Parser::Case_definitionContext* ctx) override;
    virtual void exitCase_definition(SysMLv2Parser::Case_definitionContext* ctx) override;

    virtual void enterCase_body(SysMLv2Parser::Case_bodyContext* /*ctx*/) override {}
    virtual void exitCase_body(SysMLv2Parser::Case_bodyContext* /*ctx*/) override {}

    virtual void enterCase_body_item(SysMLv2Parser::Case_body_itemContext* /*ctx*/) override {}
    virtual void exitCase_body_item(SysMLv2Parser::Case_body_itemContext* /*ctx*/) override {}

    virtual void enterCase_usage(SysMLv2Parser::Case_usageContext* ctx) override;
    virtual void exitCase_usage(SysMLv2Parser::Case_usageContext* ctx) override;

    virtual void enterAnalysis_case_definition(SysMLv2Parser::Analysis_case_definitionContext* ctx) override;
    virtual void exitAnalysis_case_definition(SysMLv2Parser::Analysis_case_definitionContext* ctx) override;

    virtual void enterAnalysis_case_usage(SysMLv2Parser::Analysis_case_usageContext* ctx) override;
    virtual void exitAnalysis_case_usage(SysMLv2Parser::Analysis_case_usageContext* ctx) override;

    virtual void enterVerification_case_definition(SysMLv2Parser::Verification_case_definitionContext* ctx) override;
    virtual void exitVerification_case_definition(SysMLv2Parser::Verification_case_definitionContext* ctx) override;

    virtual void enterVerification_case_usage(SysMLv2Parser::Verification_case_usageContext* ctx) override;
    virtual void exitVerification_case_usage(SysMLv2Parser::Verification_case_usageContext* ctx) override;

    virtual void enterObjective_member(SysMLv2Parser::Objective_memberContext* /*ctx*/) override {}
    virtual void exitObjective_member(SysMLv2Parser::Objective_memberContext* /*ctx*/) override {}

    virtual void enterObjective_requirement_usage(SysMLv2Parser::Objective_requirement_usageContext* /*ctx*/) override {}
    virtual void exitObjective_requirement_usage(SysMLv2Parser::Objective_requirement_usageContext* /*ctx*/) override {}

    virtual void enterUse_case_definition(SysMLv2Parser::Use_case_definitionContext* /*ctx*/) override {}
    virtual void exitUse_case_definition(SysMLv2Parser::Use_case_definitionContext* /*ctx*/) override {}

    virtual void enterUse_case_usage(SysMLv2Parser::Use_case_usageContext* ctx) override;
    virtual void exitUse_case_usage(SysMLv2Parser::Use_case_usageContext* ctx) override;

    virtual void enterInclude_use_case_usage(SysMLv2Parser::Include_use_case_usageContext* ctx) override;
    virtual void exitInclude_use_case_usage(SysMLv2Parser::Include_use_case_usageContext* ctx) override;

    virtual void enterView_definition(SysMLv2Parser::View_definitionContext* ctx) override;
    virtual void exitView_definition(SysMLv2Parser::View_definitionContext* ctx) override;

    virtual void enterView_definition_body(SysMLv2Parser::View_definition_bodyContext* /*ctx*/) override {}
    virtual void exitView_definition_body(SysMLv2Parser::View_definition_bodyContext* /*ctx*/) override {}

    virtual void enterView_definition_body_item(SysMLv2Parser::View_definition_body_itemContext* /*ctx*/) override {}
    virtual void exitView_definition_body_item(SysMLv2Parser::View_definition_body_itemContext* /*ctx*/) override {}

    virtual void enterView_rendering_usage(SysMLv2Parser::View_rendering_usageContext* /*ctx*/) override {}
    virtual void exitView_rendering_usage(SysMLv2Parser::View_rendering_usageContext* /*ctx*/) override {}

    virtual void enterView_usage(SysMLv2Parser::View_usageContext* ctx) override;
    virtual void exitView_usage(SysMLv2Parser::View_usageContext* ctx) override;

    virtual void enterView_body(SysMLv2Parser::View_bodyContext* /*ctx*/) override {}
    virtual void exitView_body(SysMLv2Parser::View_bodyContext* /*ctx*/) override {}

    virtual void enterView_body_item(SysMLv2Parser::View_body_itemContext* /*ctx*/) override {}
    virtual void exitView_body_item(SysMLv2Parser::View_body_itemContext* /*ctx*/) override {}

    virtual void enterViewpoint_definition(SysMLv2Parser::Viewpoint_definitionContext* ctx) override;
    virtual void exitViewpoint_definition(SysMLv2Parser::Viewpoint_definitionContext* ctx) override;

    virtual void enterViewpoint_usage(SysMLv2Parser::Viewpoint_usageContext* ctx) override;
    virtual void exitViewpoint_usage(SysMLv2Parser::Viewpoint_usageContext* ctx) override;

    virtual void enterRendering_definition(SysMLv2Parser::Rendering_definitionContext* ctx) override;
    virtual void exitRendering_definition(SysMLv2Parser::Rendering_definitionContext* ctx) override;

    virtual void enterRendering_usage(SysMLv2Parser::Rendering_usageContext* ctx) override;
    virtual void exitRendering_usage(SysMLv2Parser::Rendering_usageContext* ctx) override;

    virtual void enterMetadata_definition(SysMLv2Parser::Metadata_definitionContext* ctx) override;
    virtual void exitMetadata_definition(SysMLv2Parser::Metadata_definitionContext* ctx) override;

    virtual void enterMetadata_body(SysMLv2Parser::Metadata_bodyContext* /*ctx*/) override {}
    virtual void exitMetadata_body(SysMLv2Parser::Metadata_bodyContext* /*ctx*/) override {}

    virtual void enterMetadata_body_usage(SysMLv2Parser::Metadata_body_usageContext* /*ctx*/) override {}
    virtual void exitMetadata_body_usage(SysMLv2Parser::Metadata_body_usageContext* /*ctx*/) override {}

    virtual void enterMetadata_usage(SysMLv2Parser::Metadata_usageContext* ctx) override;
    virtual void exitMetadata_usage(SysMLv2Parser::Metadata_usageContext* ctx) override;

    virtual void enterExtended_definition(SysMLv2Parser::Extended_definitionContext* ctx) override;
    virtual void exitExtended_definition(SysMLv2Parser::Extended_definitionContext* ctx) override;

    virtual void enterExtended_usage(SysMLv2Parser::Extended_usageContext* ctx) override;
    virtual void exitExtended_usage(SysMLv2Parser::Extended_usageContext* ctx) override;

    virtual void enterNamespace(SysMLv2Parser::NamespaceContext* ctx) override;
    virtual void exitNamespace(SysMLv2Parser::NamespaceContext* ctx) override;

    virtual void enterNamespace_import(SysMLv2Parser::Namespace_importContext* ctx) override;
    virtual void exitNamespace_import(SysMLv2Parser::Namespace_importContext* ctx) override;

    virtual void enterType(SysMLv2Parser::TypeContext* ctx) override;
    virtual void exitType(SysMLv2Parser::TypeContext* ctx) override;

    virtual void enterSpecialization(SysMLv2Parser::SpecializationContext* ctx) override;
    virtual void exitSpecialization(SysMLv2Parser::SpecializationContext* ctx) override;

    virtual void enterConjunction(SysMLv2Parser::ConjunctionContext* ctx) override;
    virtual void exitConjunction(SysMLv2Parser::ConjunctionContext* ctx) override;

    virtual void enterDisjoining(SysMLv2Parser::DisjoiningContext* ctx) override;
    virtual void exitDisjoining(SysMLv2Parser::DisjoiningContext* ctx) override;

    virtual void enterClassifier(SysMLv2Parser::ClassifierContext* ctx) override;
    virtual void exitClassifier(SysMLv2Parser::ClassifierContext* ctx) override;

    virtual void enterSubclassification(SysMLv2Parser::SubclassificationContext* ctx) override;
    virtual void exitSubclassification(SysMLv2Parser::SubclassificationContext* ctx) override;

    virtual void enterFeature(SysMLv2Parser::FeatureContext* ctx) override;
    virtual void exitFeature(SysMLv2Parser::FeatureContext* ctx) override;

    virtual void enterFeature_typing(SysMLv2Parser::Feature_typingContext* ctx) override;
    virtual void exitFeature_typing(SysMLv2Parser::Feature_typingContext* ctx) override;

    virtual void enterSubsetting(SysMLv2Parser::SubsettingContext* ctx) override;
    virtual void exitSubsetting(SysMLv2Parser::SubsettingContext* ctx) override;

    virtual void enterRedefinition(SysMLv2Parser::RedefinitionContext* ctx) override;
    virtual void exitRedefinition(SysMLv2Parser::RedefinitionContext* ctx) override;

    virtual void enterFeature_inverting(SysMLv2Parser::Feature_invertingContext* ctx) override;
    virtual void exitFeature_inverting(SysMLv2Parser::Feature_invertingContext* ctx) override;

    virtual void enterType_featuring(SysMLv2Parser::Type_featuringContext* ctx) override;
    virtual void exitType_featuring(SysMLv2Parser::Type_featuringContext* ctx) override;

    virtual void enterData_type(SysMLv2Parser::Data_typeContext* ctx) override;
    virtual void exitData_type(SysMLv2Parser::Data_typeContext* ctx) override;

    virtual void enterClass(SysMLv2Parser::ClassContext* ctx) override;
    virtual void exitClass(SysMLv2Parser::ClassContext* ctx) override;

    virtual void enterStructure(SysMLv2Parser::StructureContext* ctx) override;
    virtual void exitStructure(SysMLv2Parser::StructureContext* ctx) override;

    virtual void enterAssociation(SysMLv2Parser::AssociationContext* ctx) override;
    virtual void exitAssociation(SysMLv2Parser::AssociationContext* ctx) override;

    virtual void enterAssociation_structure(SysMLv2Parser::Association_structureContext* ctx) override;
    virtual void exitAssociation_structure(SysMLv2Parser::Association_structureContext* ctx) override;

    virtual void enterConnector(SysMLv2Parser::ConnectorContext* ctx) override;
    virtual void exitConnector(SysMLv2Parser::ConnectorContext* ctx) override;

    virtual void enterBinding_connector(SysMLv2Parser::Binding_connectorContext* ctx) override;
    virtual void exitBinding_connector(SysMLv2Parser::Binding_connectorContext* ctx) override;

    virtual void enterSuccession(SysMLv2Parser::SuccessionContext* ctx) override;
    virtual void exitSuccession(SysMLv2Parser::SuccessionContext* ctx) override;

    virtual void enterBehavior(SysMLv2Parser::BehaviorContext* ctx) override;
    virtual void exitBehavior(SysMLv2Parser::BehaviorContext* ctx) override;

    virtual void enterStep(SysMLv2Parser::StepContext* ctx) override;
    virtual void exitStep(SysMLv2Parser::StepContext* ctx) override;

    virtual void enterFunction(SysMLv2Parser::FunctionContext* ctx) override;
    virtual void exitFunction(SysMLv2Parser::FunctionContext* ctx) override;

    virtual void enterPredicate(SysMLv2Parser::PredicateContext* ctx) override;
    virtual void exitPredicate(SysMLv2Parser::PredicateContext* ctx) override;

    virtual void enterBoolean_expression(SysMLv2Parser::Boolean_expressionContext* ctx) override;
    virtual void exitBoolean_expression(SysMLv2Parser::Boolean_expressionContext* ctx) override;

    virtual void enterInvariant(SysMLv2Parser::InvariantContext* ctx) override;
    virtual void exitInvariant(SysMLv2Parser::InvariantContext* ctx) override;

    virtual void enterClassification(SysMLv2Parser::ClassificationContext* ctx) override;
    virtual void exitClassification(SysMLv2Parser::ClassificationContext* ctx) override;

    virtual void enterConditional_expression(SysMLv2Parser::Conditional_expressionContext* ctx) override;
    virtual void exitConditional_expression(SysMLv2Parser::Conditional_expressionContext* ctx) override;

    virtual void enterConditional_binary_operator_expression(SysMLv2Parser::Conditional_binary_operator_expressionContext* ctx) override;
    virtual void exitConditional_binary_operator_expression(SysMLv2Parser::Conditional_binary_operator_expressionContext* ctx) override;

    virtual void enterBinary_operator_expression(SysMLv2Parser::Binary_operator_expressionContext* ctx) override;
    virtual void exitBinary_operator_expression(SysMLv2Parser::Binary_operator_expressionContext* ctx) override;

    virtual void enterUnary_operator_expression(SysMLv2Parser::Unary_operator_expressionContext* ctx) override;
    virtual void exitUnary_operator_expression(SysMLv2Parser::Unary_operator_expressionContext* ctx) override;

    virtual void enterLiteral_expression(SysMLv2Parser::Literal_expressionContext* ctx) override;
    virtual void exitLiteral_expression(SysMLv2Parser::Literal_expressionContext* ctx) override;

    virtual void enterLiteral_boolean(SysMLv2Parser::Literal_booleanContext* ctx) override;
    virtual void exitLiteral_boolean(SysMLv2Parser::Literal_booleanContext* ctx) override;

    virtual void enterLiteral_string(SysMLv2Parser::Literal_stringContext* ctx) override;
    virtual void exitLiteral_string(SysMLv2Parser::Literal_stringContext* ctx) override;

    virtual void enterLiteral_integer(SysMLv2Parser::Literal_integerContext* ctx) override;
    virtual void exitLiteral_integer(SysMLv2Parser::Literal_integerContext* ctx) override;

    virtual void enterLiteral_real(SysMLv2Parser::Literal_realContext* ctx) override;
    virtual void exitLiteral_real(SysMLv2Parser::Literal_realContext* ctx) override;

    virtual void enterLiteral_infinity(SysMLv2Parser::Literal_infinityContext* ctx) override;
    virtual void exitLiteral_infinity(SysMLv2Parser::Literal_infinityContext* ctx) override;

    virtual void enterInteraction(SysMLv2Parser::InteractionContext* ctx) override;
    virtual void exitInteraction(SysMLv2Parser::InteractionContext* ctx) override;

    virtual void enterItem_flow(SysMLv2Parser::Item_flowContext* ctx) override;
    virtual void exitItem_flow(SysMLv2Parser::Item_flowContext* ctx) override;

    virtual void enterSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext* ctx) override;
    virtual void exitSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext* ctx) override;

    virtual void enterFeature_value(SysMLv2Parser::Feature_valueContext* ctx) override;
    virtual void exitFeature_value(SysMLv2Parser::Feature_valueContext* ctx) override;

    virtual void enterFeature_assignment(SysMLv2Parser::Feature_assignmentContext* ctx) override;
    virtual void exitFeature_assignment(SysMLv2Parser::Feature_assignmentContext* ctx) override;

    virtual void enterMultiplicity(SysMLv2Parser::MultiplicityContext* ctx) override;
    virtual void exitMultiplicity(SysMLv2Parser::MultiplicityContext* ctx) override;

    virtual void enterMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext* ctx) override;
    virtual void exitMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext* ctx) override;

    virtual void enterMetaclass(SysMLv2Parser::MetaclassContext* ctx) override;
    virtual void exitMetaclass(SysMLv2Parser::MetaclassContext* ctx) override;

    virtual void enterPrefix_metadata_feature(SysMLv2Parser::Prefix_metadata_featureContext* /*ctx*/) override {}
    virtual void exitPrefix_metadata_feature(SysMLv2Parser::Prefix_metadata_featureContext* /*ctx*/) override {}

    virtual void enterMetadata_feature(SysMLv2Parser::Metadata_featureContext* ctx) override;
    virtual void exitMetadata_feature(SysMLv2Parser::Metadata_featureContext* ctx) override;

    virtual void enterMetadata_feature_declaration(SysMLv2Parser::Metadata_feature_declarationContext* /*ctx*/) override {}
    virtual void exitMetadata_feature_declaration(SysMLv2Parser::Metadata_feature_declarationContext* /*ctx*/) override {}

    virtual void enterMetadata_body_element(SysMLv2Parser::Metadata_body_elementContext* /*ctx*/) override {}
    virtual void exitMetadata_body_element(SysMLv2Parser::Metadata_body_elementContext* /*ctx*/) override {}

    virtual void enterMetadata_body_feature_member(SysMLv2Parser::Metadata_body_feature_memberContext* /*ctx*/) override {}
    virtual void exitMetadata_body_feature_member(SysMLv2Parser::Metadata_body_feature_memberContext* /*ctx*/) override {}

    virtual void enterMetadata_body_feature(SysMLv2Parser::Metadata_body_featureContext* /*ctx*/) override {}
    virtual void exitMetadata_body_feature(SysMLv2Parser::Metadata_body_featureContext* /*ctx*/) override {}

    virtual void enterLibrary_package(SysMLv2Parser::Library_packageContext* ctx) override;
    virtual void exitLibrary_package(SysMLv2Parser::Library_packageContext* ctx) override;

    virtual void enterPackage_declaration(SysMLv2Parser::Package_declarationContext* ctx) override;
    virtual void exitPackage_declaration(SysMLv2Parser::Package_declarationContext* ctx) override;

    virtual void enterElement_filter_member(SysMLv2Parser::Element_filter_memberContext* /*ctx*/) override {}
    virtual void exitElement_filter_member(SysMLv2Parser::Element_filter_memberContext* /*ctx*/) override {}

    virtual void enterMeta_assignment(SysMLv2Parser::Meta_assignmentContext* ctx) override;
    virtual void exitMeta_assignment(SysMLv2Parser::Meta_assignmentContext* ctx) override;

    virtual void enterEveryRule(antlr4::ParserRuleContext* /*ctx*/) override {}
    virtual void exitEveryRule(antlr4::ParserRuleContext* /*ctx*/) override {}
    virtual void visitTerminal(antlr4::tree::TerminalNode* /*node*/) override {}
    virtual void visitErrorNode(antlr4::tree::ErrorNode* /*node*/) override {}

    std::vector<std::shared_ptr<KerML::Entities::Element>> getElements() const;

private:
    void attachExpression(const std::shared_ptr<KerML::Entities::Expression>& expression);
    void finishOperatorExpression(const std::string& operatorName);
    void applyIdentification(SysMLv2Parser::IdentificationContext *idCtx, const std::shared_ptr<KerML::Entities::Element>& elem);
    std::shared_ptr<KerML::Entities::Element> findElementWithName(std::string identification);
    std::shared_ptr<KerML::Entities::Type> findOrCreateType(const std::string& name);
    std::shared_ptr<KerML::Entities::Classifier> findOrCreateClassifier(const std::string& name);
    std::shared_ptr<KerML::Entities::Feature> findOrCreateFeature(const std::string& name);
    std::shared_ptr<KerML::Entities::Element> resolveElement(const std::string& name, const std::shared_ptr<KerML::Entities::Element>& context);
    void populateWithBaseDatatypes();
    void resolveReferences();

    void applyUsagePrefix(SysMLv2Parser::Usage_prefixContext* prefix, const std::shared_ptr<KerML::Entities::Feature>& feature);
    void applyOccurrenceUsagePrefix(SysMLv2Parser::Occurrence_usage_prefixContext* prefix, const std::shared_ptr<KerML::Entities::Feature>& feature);
    void applyFeatureSpecializationPart(SysMLv2Parser::Feature_specialization_partContext* part, const std::shared_ptr<KerML::Entities::Feature>& feature);

    std::vector<std::shared_ptr<KerML::Entities::Element>> Elements;
    std::stack<std::shared_ptr<KerML::Entities::Element>> ParentStack;

    struct PendingTyping {
        std::shared_ptr<KerML::Entities::Feature> feature;
        std::string typeName;
    };
    std::vector<PendingTyping> pendingTypings_;

    struct PendingSpecialization {
        std::shared_ptr<KerML::Entities::Classifier> classifier;
        std::string superName;
    };
    std::vector<PendingSpecialization> pendingSpecializations_;

    struct PendingRedefinition {
        std::shared_ptr<KerML::Entities::Feature> feature;
        std::string redefinedName;
    };
    std::vector<PendingRedefinition> pendingRedefinitions_;

    std::map<std::string, std::string> aliases_;
    std::map<std::string, std::vector<std::string>> packageImports_;
};
