
// Generated from SysMLv2.g4 by ANTLR 4.13.2

#pragma once


#include <antlr4-runtime.h>
#include <sysmlv2/parser/SysMLv2Parser.h>


/**
 * This interface defines an abstract listener for a parse tree produced by SysMLv2Parser.
 */
class  SysMLv2Listener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStart(SysMLv2Parser::StartContext *ctx) = 0;
  virtual void exitStart(SysMLv2Parser::StartContext *ctx) = 0;

  virtual void enterStart_element(SysMLv2Parser::Start_elementContext *ctx) = 0;
  virtual void exitStart_element(SysMLv2Parser::Start_elementContext *ctx) = 0;

  virtual void enterStartRule(SysMLv2Parser::StartRuleContext *ctx) = 0;
  virtual void exitStartRule(SysMLv2Parser::StartRuleContext *ctx) = 0;

  virtual void enterRelationship_body(SysMLv2Parser::Relationship_bodyContext *ctx) = 0;
  virtual void exitRelationship_body(SysMLv2Parser::Relationship_bodyContext *ctx) = 0;

  virtual void enterDependency(SysMLv2Parser::DependencyContext *ctx) = 0;
  virtual void exitDependency(SysMLv2Parser::DependencyContext *ctx) = 0;

  virtual void enterDependency_declaration(SysMLv2Parser::Dependency_declarationContext *ctx) = 0;
  virtual void exitDependency_declaration(SysMLv2Parser::Dependency_declarationContext *ctx) = 0;

  virtual void enterAnnotation(SysMLv2Parser::AnnotationContext *ctx) = 0;
  virtual void exitAnnotation(SysMLv2Parser::AnnotationContext *ctx) = 0;

  virtual void enterOwned_annotation(SysMLv2Parser::Owned_annotationContext *ctx) = 0;
  virtual void exitOwned_annotation(SysMLv2Parser::Owned_annotationContext *ctx) = 0;

  virtual void enterAnnotating_member(SysMLv2Parser::Annotating_memberContext *ctx) = 0;
  virtual void exitAnnotating_member(SysMLv2Parser::Annotating_memberContext *ctx) = 0;

  virtual void enterAnnotating_element(SysMLv2Parser::Annotating_elementContext *ctx) = 0;
  virtual void exitAnnotating_element(SysMLv2Parser::Annotating_elementContext *ctx) = 0;

  virtual void enterComment(SysMLv2Parser::CommentContext *ctx) = 0;
  virtual void exitComment(SysMLv2Parser::CommentContext *ctx) = 0;

  virtual void enterDocumentation(SysMLv2Parser::DocumentationContext *ctx) = 0;
  virtual void exitDocumentation(SysMLv2Parser::DocumentationContext *ctx) = 0;

  virtual void enterTextual_representation(SysMLv2Parser::Textual_representationContext *ctx) = 0;
  virtual void exitTextual_representation(SysMLv2Parser::Textual_representationContext *ctx) = 0;

  virtual void enterRoot_namespace(SysMLv2Parser::Root_namespaceContext *ctx) = 0;
  virtual void exitRoot_namespace(SysMLv2Parser::Root_namespaceContext *ctx) = 0;

  virtual void enterPackage(SysMLv2Parser::PackageContext *ctx) = 0;
  virtual void exitPackage(SysMLv2Parser::PackageContext *ctx) = 0;

  virtual void enterPackage_body(SysMLv2Parser::Package_bodyContext *ctx) = 0;
  virtual void exitPackage_body(SysMLv2Parser::Package_bodyContext *ctx) = 0;

  virtual void enterPackage_body_element(SysMLv2Parser::Package_body_elementContext *ctx) = 0;
  virtual void exitPackage_body_element(SysMLv2Parser::Package_body_elementContext *ctx) = 0;

  virtual void enterPackage_member(SysMLv2Parser::Package_memberContext *ctx) = 0;
  virtual void exitPackage_member(SysMLv2Parser::Package_memberContext *ctx) = 0;

  virtual void enterAlias_member(SysMLv2Parser::Alias_memberContext *ctx) = 0;
  virtual void exitAlias_member(SysMLv2Parser::Alias_memberContext *ctx) = 0;

  virtual void enterDefinition_element(SysMLv2Parser::Definition_elementContext *ctx) = 0;
  virtual void exitDefinition_element(SysMLv2Parser::Definition_elementContext *ctx) = 0;

  virtual void enterUsage_element(SysMLv2Parser::Usage_elementContext *ctx) = 0;
  virtual void exitUsage_element(SysMLv2Parser::Usage_elementContext *ctx) = 0;

  virtual void enterBasic_definition_prefix(SysMLv2Parser::Basic_definition_prefixContext *ctx) = 0;
  virtual void exitBasic_definition_prefix(SysMLv2Parser::Basic_definition_prefixContext *ctx) = 0;

  virtual void enterDefinition_extension_keyword(SysMLv2Parser::Definition_extension_keywordContext *ctx) = 0;
  virtual void exitDefinition_extension_keyword(SysMLv2Parser::Definition_extension_keywordContext *ctx) = 0;

  virtual void enterDefinition_prefix(SysMLv2Parser::Definition_prefixContext *ctx) = 0;
  virtual void exitDefinition_prefix(SysMLv2Parser::Definition_prefixContext *ctx) = 0;

  virtual void enterDefinition(SysMLv2Parser::DefinitionContext *ctx) = 0;
  virtual void exitDefinition(SysMLv2Parser::DefinitionContext *ctx) = 0;

  virtual void enterDefinition_declaration(SysMLv2Parser::Definition_declarationContext *ctx) = 0;
  virtual void exitDefinition_declaration(SysMLv2Parser::Definition_declarationContext *ctx) = 0;

  virtual void enterDefinition_body(SysMLv2Parser::Definition_bodyContext *ctx) = 0;
  virtual void exitDefinition_body(SysMLv2Parser::Definition_bodyContext *ctx) = 0;

  virtual void enterDefinition_body_item(SysMLv2Parser::Definition_body_itemContext *ctx) = 0;
  virtual void exitDefinition_body_item(SysMLv2Parser::Definition_body_itemContext *ctx) = 0;

  virtual void enterDefinition_member(SysMLv2Parser::Definition_memberContext *ctx) = 0;
  virtual void exitDefinition_member(SysMLv2Parser::Definition_memberContext *ctx) = 0;

  virtual void enterVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext *ctx) = 0;
  virtual void exitVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext *ctx) = 0;

  virtual void enterNon_occurrence_usage_member(SysMLv2Parser::Non_occurrence_usage_memberContext *ctx) = 0;
  virtual void exitNon_occurrence_usage_member(SysMLv2Parser::Non_occurrence_usage_memberContext *ctx) = 0;

  virtual void enterOccurrence_usage_member(SysMLv2Parser::Occurrence_usage_memberContext *ctx) = 0;
  virtual void exitOccurrence_usage_member(SysMLv2Parser::Occurrence_usage_memberContext *ctx) = 0;

  virtual void enterStructure_usage_member(SysMLv2Parser::Structure_usage_memberContext *ctx) = 0;
  virtual void exitStructure_usage_member(SysMLv2Parser::Structure_usage_memberContext *ctx) = 0;

  virtual void enterBehavior_usage_member(SysMLv2Parser::Behavior_usage_memberContext *ctx) = 0;
  virtual void exitBehavior_usage_member(SysMLv2Parser::Behavior_usage_memberContext *ctx) = 0;

  virtual void enterFeature_direction(SysMLv2Parser::Feature_directionContext *ctx) = 0;
  virtual void exitFeature_direction(SysMLv2Parser::Feature_directionContext *ctx) = 0;

  virtual void enterRef_prefix(SysMLv2Parser::Ref_prefixContext *ctx) = 0;
  virtual void exitRef_prefix(SysMLv2Parser::Ref_prefixContext *ctx) = 0;

  virtual void enterBasic_usage_prefix(SysMLv2Parser::Basic_usage_prefixContext *ctx) = 0;
  virtual void exitBasic_usage_prefix(SysMLv2Parser::Basic_usage_prefixContext *ctx) = 0;

  virtual void enterEnd_usage_prefix(SysMLv2Parser::End_usage_prefixContext *ctx) = 0;
  virtual void exitEnd_usage_prefix(SysMLv2Parser::End_usage_prefixContext *ctx) = 0;

  virtual void enterOwned_cross_feature_member(SysMLv2Parser::Owned_cross_feature_memberContext *ctx) = 0;
  virtual void exitOwned_cross_feature_member(SysMLv2Parser::Owned_cross_feature_memberContext *ctx) = 0;

  virtual void enterOwned_cross_feature(SysMLv2Parser::Owned_cross_featureContext *ctx) = 0;
  virtual void exitOwned_cross_feature(SysMLv2Parser::Owned_cross_featureContext *ctx) = 0;

  virtual void enterUsage_extention_keyword(SysMLv2Parser::Usage_extention_keywordContext *ctx) = 0;
  virtual void exitUsage_extention_keyword(SysMLv2Parser::Usage_extention_keywordContext *ctx) = 0;

  virtual void enterUnextended_usage_prefix(SysMLv2Parser::Unextended_usage_prefixContext *ctx) = 0;
  virtual void exitUnextended_usage_prefix(SysMLv2Parser::Unextended_usage_prefixContext *ctx) = 0;

  virtual void enterUsage_prefix(SysMLv2Parser::Usage_prefixContext *ctx) = 0;
  virtual void exitUsage_prefix(SysMLv2Parser::Usage_prefixContext *ctx) = 0;

  virtual void enterUsage(SysMLv2Parser::UsageContext *ctx) = 0;
  virtual void exitUsage(SysMLv2Parser::UsageContext *ctx) = 0;

  virtual void enterUsage_declaration(SysMLv2Parser::Usage_declarationContext *ctx) = 0;
  virtual void exitUsage_declaration(SysMLv2Parser::Usage_declarationContext *ctx) = 0;

  virtual void enterUsage_completion(SysMLv2Parser::Usage_completionContext *ctx) = 0;
  virtual void exitUsage_completion(SysMLv2Parser::Usage_completionContext *ctx) = 0;

  virtual void enterUsage_body(SysMLv2Parser::Usage_bodyContext *ctx) = 0;
  virtual void exitUsage_body(SysMLv2Parser::Usage_bodyContext *ctx) = 0;

  virtual void enterDefault_reference_usage(SysMLv2Parser::Default_reference_usageContext *ctx) = 0;
  virtual void exitDefault_reference_usage(SysMLv2Parser::Default_reference_usageContext *ctx) = 0;

  virtual void enterReference_usage(SysMLv2Parser::Reference_usageContext *ctx) = 0;
  virtual void exitReference_usage(SysMLv2Parser::Reference_usageContext *ctx) = 0;

  virtual void enterVariant_reference(SysMLv2Parser::Variant_referenceContext *ctx) = 0;
  virtual void exitVariant_reference(SysMLv2Parser::Variant_referenceContext *ctx) = 0;

  virtual void enterNon_occurrence_usage_element(SysMLv2Parser::Non_occurrence_usage_elementContext *ctx) = 0;
  virtual void exitNon_occurrence_usage_element(SysMLv2Parser::Non_occurrence_usage_elementContext *ctx) = 0;

  virtual void enterOccurrence_usage_element(SysMLv2Parser::Occurrence_usage_elementContext *ctx) = 0;
  virtual void exitOccurrence_usage_element(SysMLv2Parser::Occurrence_usage_elementContext *ctx) = 0;

  virtual void enterStructure_usage_element(SysMLv2Parser::Structure_usage_elementContext *ctx) = 0;
  virtual void exitStructure_usage_element(SysMLv2Parser::Structure_usage_elementContext *ctx) = 0;

  virtual void enterBehavior_usage_element(SysMLv2Parser::Behavior_usage_elementContext *ctx) = 0;
  virtual void exitBehavior_usage_element(SysMLv2Parser::Behavior_usage_elementContext *ctx) = 0;

  virtual void enterVariant_usage_element(SysMLv2Parser::Variant_usage_elementContext *ctx) = 0;
  virtual void exitVariant_usage_element(SysMLv2Parser::Variant_usage_elementContext *ctx) = 0;

  virtual void enterSubsclassification_part(SysMLv2Parser::Subsclassification_partContext *ctx) = 0;
  virtual void exitSubsclassification_part(SysMLv2Parser::Subsclassification_partContext *ctx) = 0;

  virtual void enterCrosses(SysMLv2Parser::CrossesContext *ctx) = 0;
  virtual void exitCrosses(SysMLv2Parser::CrossesContext *ctx) = 0;

  virtual void enterOwned_cross_subsetting(SysMLv2Parser::Owned_cross_subsettingContext *ctx) = 0;
  virtual void exitOwned_cross_subsetting(SysMLv2Parser::Owned_cross_subsettingContext *ctx) = 0;

  virtual void enterMultiplicity_part(SysMLv2Parser::Multiplicity_partContext *ctx) = 0;
  virtual void exitMultiplicity_part(SysMLv2Parser::Multiplicity_partContext *ctx) = 0;

  virtual void enterOwned_multiplicity(SysMLv2Parser::Owned_multiplicityContext *ctx) = 0;
  virtual void exitOwned_multiplicity(SysMLv2Parser::Owned_multiplicityContext *ctx) = 0;

  virtual void enterMultiplicity_range(SysMLv2Parser::Multiplicity_rangeContext *ctx) = 0;
  virtual void exitMultiplicity_range(SysMLv2Parser::Multiplicity_rangeContext *ctx) = 0;

  virtual void enterAttribute_definition(SysMLv2Parser::Attribute_definitionContext *ctx) = 0;
  virtual void exitAttribute_definition(SysMLv2Parser::Attribute_definitionContext *ctx) = 0;

  virtual void enterAttribute_usage(SysMLv2Parser::Attribute_usageContext *ctx) = 0;
  virtual void exitAttribute_usage(SysMLv2Parser::Attribute_usageContext *ctx) = 0;

  virtual void enterEnumeration_definition(SysMLv2Parser::Enumeration_definitionContext *ctx) = 0;
  virtual void exitEnumeration_definition(SysMLv2Parser::Enumeration_definitionContext *ctx) = 0;

  virtual void enterEnumeration_body(SysMLv2Parser::Enumeration_bodyContext *ctx) = 0;
  virtual void exitEnumeration_body(SysMLv2Parser::Enumeration_bodyContext *ctx) = 0;

  virtual void enterEnumeration_usage_member(SysMLv2Parser::Enumeration_usage_memberContext *ctx) = 0;
  virtual void exitEnumeration_usage_member(SysMLv2Parser::Enumeration_usage_memberContext *ctx) = 0;

  virtual void enterEnumerated_value(SysMLv2Parser::Enumerated_valueContext *ctx) = 0;
  virtual void exitEnumerated_value(SysMLv2Parser::Enumerated_valueContext *ctx) = 0;

  virtual void enterEnumeration_usage(SysMLv2Parser::Enumeration_usageContext *ctx) = 0;
  virtual void exitEnumeration_usage(SysMLv2Parser::Enumeration_usageContext *ctx) = 0;

  virtual void enterOccurrence_definition_prefix(SysMLv2Parser::Occurrence_definition_prefixContext *ctx) = 0;
  virtual void exitOccurrence_definition_prefix(SysMLv2Parser::Occurrence_definition_prefixContext *ctx) = 0;

  virtual void enterOccurrence_definition(SysMLv2Parser::Occurrence_definitionContext *ctx) = 0;
  virtual void exitOccurrence_definition(SysMLv2Parser::Occurrence_definitionContext *ctx) = 0;

  virtual void enterIndividual_definition(SysMLv2Parser::Individual_definitionContext *ctx) = 0;
  virtual void exitIndividual_definition(SysMLv2Parser::Individual_definitionContext *ctx) = 0;

  virtual void enterOccurrence_usage_prefix(SysMLv2Parser::Occurrence_usage_prefixContext *ctx) = 0;
  virtual void exitOccurrence_usage_prefix(SysMLv2Parser::Occurrence_usage_prefixContext *ctx) = 0;

  virtual void enterOccurrence_usage(SysMLv2Parser::Occurrence_usageContext *ctx) = 0;
  virtual void exitOccurrence_usage(SysMLv2Parser::Occurrence_usageContext *ctx) = 0;

  virtual void enterIndividual_usage(SysMLv2Parser::Individual_usageContext *ctx) = 0;
  virtual void exitIndividual_usage(SysMLv2Parser::Individual_usageContext *ctx) = 0;

  virtual void enterPortion_usage(SysMLv2Parser::Portion_usageContext *ctx) = 0;
  virtual void exitPortion_usage(SysMLv2Parser::Portion_usageContext *ctx) = 0;

  virtual void enterPortion_kind(SysMLv2Parser::Portion_kindContext *ctx) = 0;
  virtual void exitPortion_kind(SysMLv2Parser::Portion_kindContext *ctx) = 0;

  virtual void enterEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext *ctx) = 0;
  virtual void exitEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext *ctx) = 0;

  virtual void enterSource_succession_member(SysMLv2Parser::Source_succession_memberContext *ctx) = 0;
  virtual void exitSource_succession_member(SysMLv2Parser::Source_succession_memberContext *ctx) = 0;

  virtual void enterSouce_succession(SysMLv2Parser::Souce_successionContext *ctx) = 0;
  virtual void exitSouce_succession(SysMLv2Parser::Souce_successionContext *ctx) = 0;

  virtual void enterSource_end_member(SysMLv2Parser::Source_end_memberContext *ctx) = 0;
  virtual void exitSource_end_member(SysMLv2Parser::Source_end_memberContext *ctx) = 0;

  virtual void enterSource_end(SysMLv2Parser::Source_endContext *ctx) = 0;
  virtual void exitSource_end(SysMLv2Parser::Source_endContext *ctx) = 0;

  virtual void enterItem_definition(SysMLv2Parser::Item_definitionContext *ctx) = 0;
  virtual void exitItem_definition(SysMLv2Parser::Item_definitionContext *ctx) = 0;

  virtual void enterItem_usage(SysMLv2Parser::Item_usageContext *ctx) = 0;
  virtual void exitItem_usage(SysMLv2Parser::Item_usageContext *ctx) = 0;

  virtual void enterPart_definition(SysMLv2Parser::Part_definitionContext *ctx) = 0;
  virtual void exitPart_definition(SysMLv2Parser::Part_definitionContext *ctx) = 0;

  virtual void enterPart_usage(SysMLv2Parser::Part_usageContext *ctx) = 0;
  virtual void exitPart_usage(SysMLv2Parser::Part_usageContext *ctx) = 0;

  virtual void enterPort_definition(SysMLv2Parser::Port_definitionContext *ctx) = 0;
  virtual void exitPort_definition(SysMLv2Parser::Port_definitionContext *ctx) = 0;

  virtual void enterPort_usage(SysMLv2Parser::Port_usageContext *ctx) = 0;
  virtual void exitPort_usage(SysMLv2Parser::Port_usageContext *ctx) = 0;

  virtual void enterConjungated_port_typing(SysMLv2Parser::Conjungated_port_typingContext *ctx) = 0;
  virtual void exitConjungated_port_typing(SysMLv2Parser::Conjungated_port_typingContext *ctx) = 0;

  virtual void enterConnection_definition(SysMLv2Parser::Connection_definitionContext *ctx) = 0;
  virtual void exitConnection_definition(SysMLv2Parser::Connection_definitionContext *ctx) = 0;

  virtual void enterConnection_usage(SysMLv2Parser::Connection_usageContext *ctx) = 0;
  virtual void exitConnection_usage(SysMLv2Parser::Connection_usageContext *ctx) = 0;

  virtual void enterConnector_part(SysMLv2Parser::Connector_partContext *ctx) = 0;
  virtual void exitConnector_part(SysMLv2Parser::Connector_partContext *ctx) = 0;

  virtual void enterBinary_connector_part(SysMLv2Parser::Binary_connector_partContext *ctx) = 0;
  virtual void exitBinary_connector_part(SysMLv2Parser::Binary_connector_partContext *ctx) = 0;

  virtual void enterNary_connector_part(SysMLv2Parser::Nary_connector_partContext *ctx) = 0;
  virtual void exitNary_connector_part(SysMLv2Parser::Nary_connector_partContext *ctx) = 0;

  virtual void enterConnector_end_member(SysMLv2Parser::Connector_end_memberContext *ctx) = 0;
  virtual void exitConnector_end_member(SysMLv2Parser::Connector_end_memberContext *ctx) = 0;

  virtual void enterConnecotr_end(SysMLv2Parser::Connecotr_endContext *ctx) = 0;
  virtual void exitConnecotr_end(SysMLv2Parser::Connecotr_endContext *ctx) = 0;

  virtual void enterOwned_cross_multiplicity_member(SysMLv2Parser::Owned_cross_multiplicity_memberContext *ctx) = 0;
  virtual void exitOwned_cross_multiplicity_member(SysMLv2Parser::Owned_cross_multiplicity_memberContext *ctx) = 0;

  virtual void enterOwned_cross_multiplicity(SysMLv2Parser::Owned_cross_multiplicityContext *ctx) = 0;
  virtual void exitOwned_cross_multiplicity(SysMLv2Parser::Owned_cross_multiplicityContext *ctx) = 0;

  virtual void enterBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext *ctx) = 0;
  virtual void exitBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext *ctx) = 0;

  virtual void enterSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext *ctx) = 0;
  virtual void exitSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext *ctx) = 0;

  virtual void enterInterface_definition(SysMLv2Parser::Interface_definitionContext *ctx) = 0;
  virtual void exitInterface_definition(SysMLv2Parser::Interface_definitionContext *ctx) = 0;

  virtual void enterInterface_body(SysMLv2Parser::Interface_bodyContext *ctx) = 0;
  virtual void exitInterface_body(SysMLv2Parser::Interface_bodyContext *ctx) = 0;

  virtual void enterInterface_body_item(SysMLv2Parser::Interface_body_itemContext *ctx) = 0;
  virtual void exitInterface_body_item(SysMLv2Parser::Interface_body_itemContext *ctx) = 0;

  virtual void enterInterface_non_occurrence_usage_member(SysMLv2Parser::Interface_non_occurrence_usage_memberContext *ctx) = 0;
  virtual void exitInterface_non_occurrence_usage_member(SysMLv2Parser::Interface_non_occurrence_usage_memberContext *ctx) = 0;

  virtual void enterInterface_non_occurrence_usage_element(SysMLv2Parser::Interface_non_occurrence_usage_elementContext *ctx) = 0;
  virtual void exitInterface_non_occurrence_usage_element(SysMLv2Parser::Interface_non_occurrence_usage_elementContext *ctx) = 0;

  virtual void enterInterface_occurrence_usage_member(SysMLv2Parser::Interface_occurrence_usage_memberContext *ctx) = 0;
  virtual void exitInterface_occurrence_usage_member(SysMLv2Parser::Interface_occurrence_usage_memberContext *ctx) = 0;

  virtual void enterInterface_occurrence_usage_element(SysMLv2Parser::Interface_occurrence_usage_elementContext *ctx) = 0;
  virtual void exitInterface_occurrence_usage_element(SysMLv2Parser::Interface_occurrence_usage_elementContext *ctx) = 0;

  virtual void enterDefault_interface_end(SysMLv2Parser::Default_interface_endContext *ctx) = 0;
  virtual void exitDefault_interface_end(SysMLv2Parser::Default_interface_endContext *ctx) = 0;

  virtual void enterInterface_usage(SysMLv2Parser::Interface_usageContext *ctx) = 0;
  virtual void exitInterface_usage(SysMLv2Parser::Interface_usageContext *ctx) = 0;

  virtual void enterInterface_usage_declaration(SysMLv2Parser::Interface_usage_declarationContext *ctx) = 0;
  virtual void exitInterface_usage_declaration(SysMLv2Parser::Interface_usage_declarationContext *ctx) = 0;

  virtual void enterInterface_part(SysMLv2Parser::Interface_partContext *ctx) = 0;
  virtual void exitInterface_part(SysMLv2Parser::Interface_partContext *ctx) = 0;

  virtual void enterBinary_interface_part(SysMLv2Parser::Binary_interface_partContext *ctx) = 0;
  virtual void exitBinary_interface_part(SysMLv2Parser::Binary_interface_partContext *ctx) = 0;

  virtual void enterNary_interface_part(SysMLv2Parser::Nary_interface_partContext *ctx) = 0;
  virtual void exitNary_interface_part(SysMLv2Parser::Nary_interface_partContext *ctx) = 0;

  virtual void enterInterface_end_member(SysMLv2Parser::Interface_end_memberContext *ctx) = 0;
  virtual void exitInterface_end_member(SysMLv2Parser::Interface_end_memberContext *ctx) = 0;

  virtual void enterInterface_end(SysMLv2Parser::Interface_endContext *ctx) = 0;
  virtual void exitInterface_end(SysMLv2Parser::Interface_endContext *ctx) = 0;

  virtual void enterAllocation_definition(SysMLv2Parser::Allocation_definitionContext *ctx) = 0;
  virtual void exitAllocation_definition(SysMLv2Parser::Allocation_definitionContext *ctx) = 0;

  virtual void enterAllocation_usage(SysMLv2Parser::Allocation_usageContext *ctx) = 0;
  virtual void exitAllocation_usage(SysMLv2Parser::Allocation_usageContext *ctx) = 0;

  virtual void enterAllocation_usage_declaration(SysMLv2Parser::Allocation_usage_declarationContext *ctx) = 0;
  virtual void exitAllocation_usage_declaration(SysMLv2Parser::Allocation_usage_declarationContext *ctx) = 0;

  virtual void enterFlow_definition(SysMLv2Parser::Flow_definitionContext *ctx) = 0;
  virtual void exitFlow_definition(SysMLv2Parser::Flow_definitionContext *ctx) = 0;

  virtual void enterMessage(SysMLv2Parser::MessageContext *ctx) = 0;
  virtual void exitMessage(SysMLv2Parser::MessageContext *ctx) = 0;

  virtual void enterMessage_declaration(SysMLv2Parser::Message_declarationContext *ctx) = 0;
  virtual void exitMessage_declaration(SysMLv2Parser::Message_declarationContext *ctx) = 0;

  virtual void enterMessage_event_member(SysMLv2Parser::Message_event_memberContext *ctx) = 0;
  virtual void exitMessage_event_member(SysMLv2Parser::Message_event_memberContext *ctx) = 0;

  virtual void enterMessage_event(SysMLv2Parser::Message_eventContext *ctx) = 0;
  virtual void exitMessage_event(SysMLv2Parser::Message_eventContext *ctx) = 0;

  virtual void enterFlow_usage(SysMLv2Parser::Flow_usageContext *ctx) = 0;
  virtual void exitFlow_usage(SysMLv2Parser::Flow_usageContext *ctx) = 0;

  virtual void enterSuccession_flow_usage(SysMLv2Parser::Succession_flow_usageContext *ctx) = 0;
  virtual void exitSuccession_flow_usage(SysMLv2Parser::Succession_flow_usageContext *ctx) = 0;

  virtual void enterFlow_declaration(SysMLv2Parser::Flow_declarationContext *ctx) = 0;
  virtual void exitFlow_declaration(SysMLv2Parser::Flow_declarationContext *ctx) = 0;

  virtual void enterFlow_payload_feature_member(SysMLv2Parser::Flow_payload_feature_memberContext *ctx) = 0;
  virtual void exitFlow_payload_feature_member(SysMLv2Parser::Flow_payload_feature_memberContext *ctx) = 0;

  virtual void enterFlow_payload_feature(SysMLv2Parser::Flow_payload_featureContext *ctx) = 0;
  virtual void exitFlow_payload_feature(SysMLv2Parser::Flow_payload_featureContext *ctx) = 0;

  virtual void enterPayload_feature(SysMLv2Parser::Payload_featureContext *ctx) = 0;
  virtual void exitPayload_feature(SysMLv2Parser::Payload_featureContext *ctx) = 0;

  virtual void enterPayload_feature_specialization_part(SysMLv2Parser::Payload_feature_specialization_partContext *ctx) = 0;
  virtual void exitPayload_feature_specialization_part(SysMLv2Parser::Payload_feature_specialization_partContext *ctx) = 0;

  virtual void enterFlow_end_member(SysMLv2Parser::Flow_end_memberContext *ctx) = 0;
  virtual void exitFlow_end_member(SysMLv2Parser::Flow_end_memberContext *ctx) = 0;

  virtual void enterFlow_end(SysMLv2Parser::Flow_endContext *ctx) = 0;
  virtual void exitFlow_end(SysMLv2Parser::Flow_endContext *ctx) = 0;

  virtual void enterFlow_end_subsetting(SysMLv2Parser::Flow_end_subsettingContext *ctx) = 0;
  virtual void exitFlow_end_subsetting(SysMLv2Parser::Flow_end_subsettingContext *ctx) = 0;

  virtual void enterFeature_chain_prefix(SysMLv2Parser::Feature_chain_prefixContext *ctx) = 0;
  virtual void exitFeature_chain_prefix(SysMLv2Parser::Feature_chain_prefixContext *ctx) = 0;

  virtual void enterFlow_feature_member(SysMLv2Parser::Flow_feature_memberContext *ctx) = 0;
  virtual void exitFlow_feature_member(SysMLv2Parser::Flow_feature_memberContext *ctx) = 0;

  virtual void enterFlow_feature(SysMLv2Parser::Flow_featureContext *ctx) = 0;
  virtual void exitFlow_feature(SysMLv2Parser::Flow_featureContext *ctx) = 0;

  virtual void enterFlow_feature_redefinition(SysMLv2Parser::Flow_feature_redefinitionContext *ctx) = 0;
  virtual void exitFlow_feature_redefinition(SysMLv2Parser::Flow_feature_redefinitionContext *ctx) = 0;

  virtual void enterAction_definition(SysMLv2Parser::Action_definitionContext *ctx) = 0;
  virtual void exitAction_definition(SysMLv2Parser::Action_definitionContext *ctx) = 0;

  virtual void enterAction_body(SysMLv2Parser::Action_bodyContext *ctx) = 0;
  virtual void exitAction_body(SysMLv2Parser::Action_bodyContext *ctx) = 0;

  virtual void enterAction_body_item(SysMLv2Parser::Action_body_itemContext *ctx) = 0;
  virtual void exitAction_body_item(SysMLv2Parser::Action_body_itemContext *ctx) = 0;

  virtual void enterNon_behavior_body_item(SysMLv2Parser::Non_behavior_body_itemContext *ctx) = 0;
  virtual void exitNon_behavior_body_item(SysMLv2Parser::Non_behavior_body_itemContext *ctx) = 0;

  virtual void enterAction_behavior_member(SysMLv2Parser::Action_behavior_memberContext *ctx) = 0;
  virtual void exitAction_behavior_member(SysMLv2Parser::Action_behavior_memberContext *ctx) = 0;

  virtual void enterInitial_node_member(SysMLv2Parser::Initial_node_memberContext *ctx) = 0;
  virtual void exitInitial_node_member(SysMLv2Parser::Initial_node_memberContext *ctx) = 0;

  virtual void enterAction_node_member(SysMLv2Parser::Action_node_memberContext *ctx) = 0;
  virtual void exitAction_node_member(SysMLv2Parser::Action_node_memberContext *ctx) = 0;

  virtual void enterAction_target_succession_member(SysMLv2Parser::Action_target_succession_memberContext *ctx) = 0;
  virtual void exitAction_target_succession_member(SysMLv2Parser::Action_target_succession_memberContext *ctx) = 0;

  virtual void enterGuarded_succession_member(SysMLv2Parser::Guarded_succession_memberContext *ctx) = 0;
  virtual void exitGuarded_succession_member(SysMLv2Parser::Guarded_succession_memberContext *ctx) = 0;

  virtual void enterAction_usage(SysMLv2Parser::Action_usageContext *ctx) = 0;
  virtual void exitAction_usage(SysMLv2Parser::Action_usageContext *ctx) = 0;

  virtual void enterAction_usage_declaration(SysMLv2Parser::Action_usage_declarationContext *ctx) = 0;
  virtual void exitAction_usage_declaration(SysMLv2Parser::Action_usage_declarationContext *ctx) = 0;

  virtual void enterPerform_action_usage(SysMLv2Parser::Perform_action_usageContext *ctx) = 0;
  virtual void exitPerform_action_usage(SysMLv2Parser::Perform_action_usageContext *ctx) = 0;

  virtual void enterPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext *ctx) = 0;
  virtual void exitPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext *ctx) = 0;

  virtual void enterAction_node(SysMLv2Parser::Action_nodeContext *ctx) = 0;
  virtual void exitAction_node(SysMLv2Parser::Action_nodeContext *ctx) = 0;

  virtual void enterAction_node_usage_declaration(SysMLv2Parser::Action_node_usage_declarationContext *ctx) = 0;
  virtual void exitAction_node_usage_declaration(SysMLv2Parser::Action_node_usage_declarationContext *ctx) = 0;

  virtual void enterAction_node_prefix(SysMLv2Parser::Action_node_prefixContext *ctx) = 0;
  virtual void exitAction_node_prefix(SysMLv2Parser::Action_node_prefixContext *ctx) = 0;

  virtual void enterControl_node(SysMLv2Parser::Control_nodeContext *ctx) = 0;
  virtual void exitControl_node(SysMLv2Parser::Control_nodeContext *ctx) = 0;

  virtual void enterControl_node_prefix(SysMLv2Parser::Control_node_prefixContext *ctx) = 0;
  virtual void exitControl_node_prefix(SysMLv2Parser::Control_node_prefixContext *ctx) = 0;

  virtual void enterMerge_node(SysMLv2Parser::Merge_nodeContext *ctx) = 0;
  virtual void exitMerge_node(SysMLv2Parser::Merge_nodeContext *ctx) = 0;

  virtual void enterDecision_node(SysMLv2Parser::Decision_nodeContext *ctx) = 0;
  virtual void exitDecision_node(SysMLv2Parser::Decision_nodeContext *ctx) = 0;

  virtual void enterJoin_node(SysMLv2Parser::Join_nodeContext *ctx) = 0;
  virtual void exitJoin_node(SysMLv2Parser::Join_nodeContext *ctx) = 0;

  virtual void enterFork_node(SysMLv2Parser::Fork_nodeContext *ctx) = 0;
  virtual void exitFork_node(SysMLv2Parser::Fork_nodeContext *ctx) = 0;

  virtual void enterAccept_node(SysMLv2Parser::Accept_nodeContext *ctx) = 0;
  virtual void exitAccept_node(SysMLv2Parser::Accept_nodeContext *ctx) = 0;

  virtual void enterAccept_node_declaration(SysMLv2Parser::Accept_node_declarationContext *ctx) = 0;
  virtual void exitAccept_node_declaration(SysMLv2Parser::Accept_node_declarationContext *ctx) = 0;

  virtual void enterAccept_parameter_part(SysMLv2Parser::Accept_parameter_partContext *ctx) = 0;
  virtual void exitAccept_parameter_part(SysMLv2Parser::Accept_parameter_partContext *ctx) = 0;

  virtual void enterPayload_parameter_member(SysMLv2Parser::Payload_parameter_memberContext *ctx) = 0;
  virtual void exitPayload_parameter_member(SysMLv2Parser::Payload_parameter_memberContext *ctx) = 0;

  virtual void enterPayload_parameter(SysMLv2Parser::Payload_parameterContext *ctx) = 0;
  virtual void exitPayload_parameter(SysMLv2Parser::Payload_parameterContext *ctx) = 0;

  virtual void enterTrigger_value_part(SysMLv2Parser::Trigger_value_partContext *ctx) = 0;
  virtual void exitTrigger_value_part(SysMLv2Parser::Trigger_value_partContext *ctx) = 0;

  virtual void enterTrigger_expression(SysMLv2Parser::Trigger_expressionContext *ctx) = 0;
  virtual void exitTrigger_expression(SysMLv2Parser::Trigger_expressionContext *ctx) = 0;

  virtual void enterSend_node(SysMLv2Parser::Send_nodeContext *ctx) = 0;
  virtual void exitSend_node(SysMLv2Parser::Send_nodeContext *ctx) = 0;

  virtual void enterSend_node_declaration(SysMLv2Parser::Send_node_declarationContext *ctx) = 0;
  virtual void exitSend_node_declaration(SysMLv2Parser::Send_node_declarationContext *ctx) = 0;

  virtual void enterSender_receiver_part(SysMLv2Parser::Sender_receiver_partContext *ctx) = 0;
  virtual void exitSender_receiver_part(SysMLv2Parser::Sender_receiver_partContext *ctx) = 0;

  virtual void enterNode_parameter_member(SysMLv2Parser::Node_parameter_memberContext *ctx) = 0;
  virtual void exitNode_parameter_member(SysMLv2Parser::Node_parameter_memberContext *ctx) = 0;

  virtual void enterNode_parameter(SysMLv2Parser::Node_parameterContext *ctx) = 0;
  virtual void exitNode_parameter(SysMLv2Parser::Node_parameterContext *ctx) = 0;

  virtual void enterFeature_binding(SysMLv2Parser::Feature_bindingContext *ctx) = 0;
  virtual void exitFeature_binding(SysMLv2Parser::Feature_bindingContext *ctx) = 0;

  virtual void enterAssignment_node(SysMLv2Parser::Assignment_nodeContext *ctx) = 0;
  virtual void exitAssignment_node(SysMLv2Parser::Assignment_nodeContext *ctx) = 0;

  virtual void enterAssignment_node_declaration(SysMLv2Parser::Assignment_node_declarationContext *ctx) = 0;
  virtual void exitAssignment_node_declaration(SysMLv2Parser::Assignment_node_declarationContext *ctx) = 0;

  virtual void enterAssignment_target_member(SysMLv2Parser::Assignment_target_memberContext *ctx) = 0;
  virtual void exitAssignment_target_member(SysMLv2Parser::Assignment_target_memberContext *ctx) = 0;

  virtual void enterAssignment_target_parameter(SysMLv2Parser::Assignment_target_parameterContext *ctx) = 0;
  virtual void exitAssignment_target_parameter(SysMLv2Parser::Assignment_target_parameterContext *ctx) = 0;

  virtual void enterAssignment_target_binding(SysMLv2Parser::Assignment_target_bindingContext *ctx) = 0;
  virtual void exitAssignment_target_binding(SysMLv2Parser::Assignment_target_bindingContext *ctx) = 0;

  virtual void enterFeature_chain_member(SysMLv2Parser::Feature_chain_memberContext *ctx) = 0;
  virtual void exitFeature_chain_member(SysMLv2Parser::Feature_chain_memberContext *ctx) = 0;

  virtual void enterOwned_feature_chain_member(SysMLv2Parser::Owned_feature_chain_memberContext *ctx) = 0;
  virtual void exitOwned_feature_chain_member(SysMLv2Parser::Owned_feature_chain_memberContext *ctx) = 0;

  virtual void enterTerminate_node(SysMLv2Parser::Terminate_nodeContext *ctx) = 0;
  virtual void exitTerminate_node(SysMLv2Parser::Terminate_nodeContext *ctx) = 0;

  virtual void enterIf_node(SysMLv2Parser::If_nodeContext *ctx) = 0;
  virtual void exitIf_node(SysMLv2Parser::If_nodeContext *ctx) = 0;

  virtual void enterExpression_parameter_member(SysMLv2Parser::Expression_parameter_memberContext *ctx) = 0;
  virtual void exitExpression_parameter_member(SysMLv2Parser::Expression_parameter_memberContext *ctx) = 0;

  virtual void enterAction_body_parameter_member(SysMLv2Parser::Action_body_parameter_memberContext *ctx) = 0;
  virtual void exitAction_body_parameter_member(SysMLv2Parser::Action_body_parameter_memberContext *ctx) = 0;

  virtual void enterAction_body_parameter(SysMLv2Parser::Action_body_parameterContext *ctx) = 0;
  virtual void exitAction_body_parameter(SysMLv2Parser::Action_body_parameterContext *ctx) = 0;

  virtual void enterIf_node_parameter_member(SysMLv2Parser::If_node_parameter_memberContext *ctx) = 0;
  virtual void exitIf_node_parameter_member(SysMLv2Parser::If_node_parameter_memberContext *ctx) = 0;

  virtual void enterWhile_loop_node(SysMLv2Parser::While_loop_nodeContext *ctx) = 0;
  virtual void exitWhile_loop_node(SysMLv2Parser::While_loop_nodeContext *ctx) = 0;

  virtual void enterFor_loop_node(SysMLv2Parser::For_loop_nodeContext *ctx) = 0;
  virtual void exitFor_loop_node(SysMLv2Parser::For_loop_nodeContext *ctx) = 0;

  virtual void enterFor_variable_declaration_member(SysMLv2Parser::For_variable_declaration_memberContext *ctx) = 0;
  virtual void exitFor_variable_declaration_member(SysMLv2Parser::For_variable_declaration_memberContext *ctx) = 0;

  virtual void enterFor_variable_declaration(SysMLv2Parser::For_variable_declarationContext *ctx) = 0;
  virtual void exitFor_variable_declaration(SysMLv2Parser::For_variable_declarationContext *ctx) = 0;

  virtual void enterAction_target_succession(SysMLv2Parser::Action_target_successionContext *ctx) = 0;
  virtual void exitAction_target_succession(SysMLv2Parser::Action_target_successionContext *ctx) = 0;

  virtual void enterTarget_succession(SysMLv2Parser::Target_successionContext *ctx) = 0;
  virtual void exitTarget_succession(SysMLv2Parser::Target_successionContext *ctx) = 0;

  virtual void enterGuarded_target_succession(SysMLv2Parser::Guarded_target_successionContext *ctx) = 0;
  virtual void exitGuarded_target_succession(SysMLv2Parser::Guarded_target_successionContext *ctx) = 0;

  virtual void enterDefault_target_succession(SysMLv2Parser::Default_target_successionContext *ctx) = 0;
  virtual void exitDefault_target_succession(SysMLv2Parser::Default_target_successionContext *ctx) = 0;

  virtual void enterGuarded_succession(SysMLv2Parser::Guarded_successionContext *ctx) = 0;
  virtual void exitGuarded_succession(SysMLv2Parser::Guarded_successionContext *ctx) = 0;

  virtual void enterState_definition(SysMLv2Parser::State_definitionContext *ctx) = 0;
  virtual void exitState_definition(SysMLv2Parser::State_definitionContext *ctx) = 0;

  virtual void enterState_def_body(SysMLv2Parser::State_def_bodyContext *ctx) = 0;
  virtual void exitState_def_body(SysMLv2Parser::State_def_bodyContext *ctx) = 0;

  virtual void enterState_body_item(SysMLv2Parser::State_body_itemContext *ctx) = 0;
  virtual void exitState_body_item(SysMLv2Parser::State_body_itemContext *ctx) = 0;

  virtual void enterEntry_action_member(SysMLv2Parser::Entry_action_memberContext *ctx) = 0;
  virtual void exitEntry_action_member(SysMLv2Parser::Entry_action_memberContext *ctx) = 0;

  virtual void enterDo_action_member(SysMLv2Parser::Do_action_memberContext *ctx) = 0;
  virtual void exitDo_action_member(SysMLv2Parser::Do_action_memberContext *ctx) = 0;

  virtual void enterExit_action_member(SysMLv2Parser::Exit_action_memberContext *ctx) = 0;
  virtual void exitExit_action_member(SysMLv2Parser::Exit_action_memberContext *ctx) = 0;

  virtual void enterEntry_transition_member(SysMLv2Parser::Entry_transition_memberContext *ctx) = 0;
  virtual void exitEntry_transition_member(SysMLv2Parser::Entry_transition_memberContext *ctx) = 0;

  virtual void enterState_action_usage(SysMLv2Parser::State_action_usageContext *ctx) = 0;
  virtual void exitState_action_usage(SysMLv2Parser::State_action_usageContext *ctx) = 0;

  virtual void enterEmpty_action_usage(SysMLv2Parser::Empty_action_usageContext *ctx) = 0;
  virtual void exitEmpty_action_usage(SysMLv2Parser::Empty_action_usageContext *ctx) = 0;

  virtual void enterState_perform_action_uage(SysMLv2Parser::State_perform_action_uageContext *ctx) = 0;
  virtual void exitState_perform_action_uage(SysMLv2Parser::State_perform_action_uageContext *ctx) = 0;

  virtual void enterState_accept_action_usage(SysMLv2Parser::State_accept_action_usageContext *ctx) = 0;
  virtual void exitState_accept_action_usage(SysMLv2Parser::State_accept_action_usageContext *ctx) = 0;

  virtual void enterState_send_action_usage(SysMLv2Parser::State_send_action_usageContext *ctx) = 0;
  virtual void exitState_send_action_usage(SysMLv2Parser::State_send_action_usageContext *ctx) = 0;

  virtual void enterState_assignment_action_usage(SysMLv2Parser::State_assignment_action_usageContext *ctx) = 0;
  virtual void exitState_assignment_action_usage(SysMLv2Parser::State_assignment_action_usageContext *ctx) = 0;

  virtual void enterTransition_usage_member(SysMLv2Parser::Transition_usage_memberContext *ctx) = 0;
  virtual void exitTransition_usage_member(SysMLv2Parser::Transition_usage_memberContext *ctx) = 0;

  virtual void enterTarget_transition_usage_member(SysMLv2Parser::Target_transition_usage_memberContext *ctx) = 0;
  virtual void exitTarget_transition_usage_member(SysMLv2Parser::Target_transition_usage_memberContext *ctx) = 0;

  virtual void enterState_usage(SysMLv2Parser::State_usageContext *ctx) = 0;
  virtual void exitState_usage(SysMLv2Parser::State_usageContext *ctx) = 0;

  virtual void enterState_usage_body(SysMLv2Parser::State_usage_bodyContext *ctx) = 0;
  virtual void exitState_usage_body(SysMLv2Parser::State_usage_bodyContext *ctx) = 0;

  virtual void enterExhibit_state_usage(SysMLv2Parser::Exhibit_state_usageContext *ctx) = 0;
  virtual void exitExhibit_state_usage(SysMLv2Parser::Exhibit_state_usageContext *ctx) = 0;

  virtual void enterTransition_usage(SysMLv2Parser::Transition_usageContext *ctx) = 0;
  virtual void exitTransition_usage(SysMLv2Parser::Transition_usageContext *ctx) = 0;

  virtual void enterTarget_transition_usage(SysMLv2Parser::Target_transition_usageContext *ctx) = 0;
  virtual void exitTarget_transition_usage(SysMLv2Parser::Target_transition_usageContext *ctx) = 0;

  virtual void enterTrigger_action_member(SysMLv2Parser::Trigger_action_memberContext *ctx) = 0;
  virtual void exitTrigger_action_member(SysMLv2Parser::Trigger_action_memberContext *ctx) = 0;

  virtual void enterTrigger_action(SysMLv2Parser::Trigger_actionContext *ctx) = 0;
  virtual void exitTrigger_action(SysMLv2Parser::Trigger_actionContext *ctx) = 0;

  virtual void enterGuard_expression_member(SysMLv2Parser::Guard_expression_memberContext *ctx) = 0;
  virtual void exitGuard_expression_member(SysMLv2Parser::Guard_expression_memberContext *ctx) = 0;

  virtual void enterEffect_behavior_member(SysMLv2Parser::Effect_behavior_memberContext *ctx) = 0;
  virtual void exitEffect_behavior_member(SysMLv2Parser::Effect_behavior_memberContext *ctx) = 0;

  virtual void enterEffect_behavior_usage(SysMLv2Parser::Effect_behavior_usageContext *ctx) = 0;
  virtual void exitEffect_behavior_usage(SysMLv2Parser::Effect_behavior_usageContext *ctx) = 0;

  virtual void enterTransition_perform_action_usage(SysMLv2Parser::Transition_perform_action_usageContext *ctx) = 0;
  virtual void exitTransition_perform_action_usage(SysMLv2Parser::Transition_perform_action_usageContext *ctx) = 0;

  virtual void enterTransition_accept_action_usage(SysMLv2Parser::Transition_accept_action_usageContext *ctx) = 0;
  virtual void exitTransition_accept_action_usage(SysMLv2Parser::Transition_accept_action_usageContext *ctx) = 0;

  virtual void enterTransition_send_action_usage(SysMLv2Parser::Transition_send_action_usageContext *ctx) = 0;
  virtual void exitTransition_send_action_usage(SysMLv2Parser::Transition_send_action_usageContext *ctx) = 0;

  virtual void enterTransition_assignment_action_usage(SysMLv2Parser::Transition_assignment_action_usageContext *ctx) = 0;
  virtual void exitTransition_assignment_action_usage(SysMLv2Parser::Transition_assignment_action_usageContext *ctx) = 0;

  virtual void enterTransition_succession_member(SysMLv2Parser::Transition_succession_memberContext *ctx) = 0;
  virtual void exitTransition_succession_member(SysMLv2Parser::Transition_succession_memberContext *ctx) = 0;

  virtual void enterTransition_succession(SysMLv2Parser::Transition_successionContext *ctx) = 0;
  virtual void exitTransition_succession(SysMLv2Parser::Transition_successionContext *ctx) = 0;

  virtual void enterCalculation_definition(SysMLv2Parser::Calculation_definitionContext *ctx) = 0;
  virtual void exitCalculation_definition(SysMLv2Parser::Calculation_definitionContext *ctx) = 0;

  virtual void enterCalculation_usage(SysMLv2Parser::Calculation_usageContext *ctx) = 0;
  virtual void exitCalculation_usage(SysMLv2Parser::Calculation_usageContext *ctx) = 0;

  virtual void enterCalculation_body(SysMLv2Parser::Calculation_bodyContext *ctx) = 0;
  virtual void exitCalculation_body(SysMLv2Parser::Calculation_bodyContext *ctx) = 0;

  virtual void enterCalculation_body_part(SysMLv2Parser::Calculation_body_partContext *ctx) = 0;
  virtual void exitCalculation_body_part(SysMLv2Parser::Calculation_body_partContext *ctx) = 0;

  virtual void enterCalculation_body_item(SysMLv2Parser::Calculation_body_itemContext *ctx) = 0;
  virtual void exitCalculation_body_item(SysMLv2Parser::Calculation_body_itemContext *ctx) = 0;

  virtual void enterReturn_parameter_member(SysMLv2Parser::Return_parameter_memberContext *ctx) = 0;
  virtual void exitReturn_parameter_member(SysMLv2Parser::Return_parameter_memberContext *ctx) = 0;

  virtual void enterResult_expression_member(SysMLv2Parser::Result_expression_memberContext *ctx) = 0;
  virtual void exitResult_expression_member(SysMLv2Parser::Result_expression_memberContext *ctx) = 0;

  virtual void enterConstraint_definition(SysMLv2Parser::Constraint_definitionContext *ctx) = 0;
  virtual void exitConstraint_definition(SysMLv2Parser::Constraint_definitionContext *ctx) = 0;

  virtual void enterConstraint_usage(SysMLv2Parser::Constraint_usageContext *ctx) = 0;
  virtual void exitConstraint_usage(SysMLv2Parser::Constraint_usageContext *ctx) = 0;

  virtual void enterAssert_constriant_usage(SysMLv2Parser::Assert_constriant_usageContext *ctx) = 0;
  virtual void exitAssert_constriant_usage(SysMLv2Parser::Assert_constriant_usageContext *ctx) = 0;

  virtual void enterConstraint_usage_declaration(SysMLv2Parser::Constraint_usage_declarationContext *ctx) = 0;
  virtual void exitConstraint_usage_declaration(SysMLv2Parser::Constraint_usage_declarationContext *ctx) = 0;

  virtual void enterRequirement_definition(SysMLv2Parser::Requirement_definitionContext *ctx) = 0;
  virtual void exitRequirement_definition(SysMLv2Parser::Requirement_definitionContext *ctx) = 0;

  virtual void enterRequirement_body(SysMLv2Parser::Requirement_bodyContext *ctx) = 0;
  virtual void exitRequirement_body(SysMLv2Parser::Requirement_bodyContext *ctx) = 0;

  virtual void enterRequirement_body_item(SysMLv2Parser::Requirement_body_itemContext *ctx) = 0;
  virtual void exitRequirement_body_item(SysMLv2Parser::Requirement_body_itemContext *ctx) = 0;

  virtual void enterSubject_member(SysMLv2Parser::Subject_memberContext *ctx) = 0;
  virtual void exitSubject_member(SysMLv2Parser::Subject_memberContext *ctx) = 0;

  virtual void enterSubject_usage(SysMLv2Parser::Subject_usageContext *ctx) = 0;
  virtual void exitSubject_usage(SysMLv2Parser::Subject_usageContext *ctx) = 0;

  virtual void enterRequirement_constraint_member(SysMLv2Parser::Requirement_constraint_memberContext *ctx) = 0;
  virtual void exitRequirement_constraint_member(SysMLv2Parser::Requirement_constraint_memberContext *ctx) = 0;

  virtual void enterRequriement_kind(SysMLv2Parser::Requriement_kindContext *ctx) = 0;
  virtual void exitRequriement_kind(SysMLv2Parser::Requriement_kindContext *ctx) = 0;

  virtual void enterRequirement_constraint_usage(SysMLv2Parser::Requirement_constraint_usageContext *ctx) = 0;
  virtual void exitRequirement_constraint_usage(SysMLv2Parser::Requirement_constraint_usageContext *ctx) = 0;

  virtual void enterFramed_concern_member(SysMLv2Parser::Framed_concern_memberContext *ctx) = 0;
  virtual void exitFramed_concern_member(SysMLv2Parser::Framed_concern_memberContext *ctx) = 0;

  virtual void enterFramed_concern_usage(SysMLv2Parser::Framed_concern_usageContext *ctx) = 0;
  virtual void exitFramed_concern_usage(SysMLv2Parser::Framed_concern_usageContext *ctx) = 0;

  virtual void enterActor_member(SysMLv2Parser::Actor_memberContext *ctx) = 0;
  virtual void exitActor_member(SysMLv2Parser::Actor_memberContext *ctx) = 0;

  virtual void enterActor_usage(SysMLv2Parser::Actor_usageContext *ctx) = 0;
  virtual void exitActor_usage(SysMLv2Parser::Actor_usageContext *ctx) = 0;

  virtual void enterStakeholder_member(SysMLv2Parser::Stakeholder_memberContext *ctx) = 0;
  virtual void exitStakeholder_member(SysMLv2Parser::Stakeholder_memberContext *ctx) = 0;

  virtual void enterStakeholder_usage(SysMLv2Parser::Stakeholder_usageContext *ctx) = 0;
  virtual void exitStakeholder_usage(SysMLv2Parser::Stakeholder_usageContext *ctx) = 0;

  virtual void enterRequirement_usage(SysMLv2Parser::Requirement_usageContext *ctx) = 0;
  virtual void exitRequirement_usage(SysMLv2Parser::Requirement_usageContext *ctx) = 0;

  virtual void enterSatisfy_requirement_usage(SysMLv2Parser::Satisfy_requirement_usageContext *ctx) = 0;
  virtual void exitSatisfy_requirement_usage(SysMLv2Parser::Satisfy_requirement_usageContext *ctx) = 0;

  virtual void enterSatisfaction_subject_member(SysMLv2Parser::Satisfaction_subject_memberContext *ctx) = 0;
  virtual void exitSatisfaction_subject_member(SysMLv2Parser::Satisfaction_subject_memberContext *ctx) = 0;

  virtual void enterSatisfaction_parameter(SysMLv2Parser::Satisfaction_parameterContext *ctx) = 0;
  virtual void exitSatisfaction_parameter(SysMLv2Parser::Satisfaction_parameterContext *ctx) = 0;

  virtual void enterSatisfaction_feature_value(SysMLv2Parser::Satisfaction_feature_valueContext *ctx) = 0;
  virtual void exitSatisfaction_feature_value(SysMLv2Parser::Satisfaction_feature_valueContext *ctx) = 0;

  virtual void enterSatisfaction_reference_expression(SysMLv2Parser::Satisfaction_reference_expressionContext *ctx) = 0;
  virtual void exitSatisfaction_reference_expression(SysMLv2Parser::Satisfaction_reference_expressionContext *ctx) = 0;

  virtual void enterConcern_definition(SysMLv2Parser::Concern_definitionContext *ctx) = 0;
  virtual void exitConcern_definition(SysMLv2Parser::Concern_definitionContext *ctx) = 0;

  virtual void enterConcern_usage(SysMLv2Parser::Concern_usageContext *ctx) = 0;
  virtual void exitConcern_usage(SysMLv2Parser::Concern_usageContext *ctx) = 0;

  virtual void enterCase_definition(SysMLv2Parser::Case_definitionContext *ctx) = 0;
  virtual void exitCase_definition(SysMLv2Parser::Case_definitionContext *ctx) = 0;

  virtual void enterCase_usage(SysMLv2Parser::Case_usageContext *ctx) = 0;
  virtual void exitCase_usage(SysMLv2Parser::Case_usageContext *ctx) = 0;

  virtual void enterCase_body(SysMLv2Parser::Case_bodyContext *ctx) = 0;
  virtual void exitCase_body(SysMLv2Parser::Case_bodyContext *ctx) = 0;

  virtual void enterCase_body_item(SysMLv2Parser::Case_body_itemContext *ctx) = 0;
  virtual void exitCase_body_item(SysMLv2Parser::Case_body_itemContext *ctx) = 0;

  virtual void enterObjective_member(SysMLv2Parser::Objective_memberContext *ctx) = 0;
  virtual void exitObjective_member(SysMLv2Parser::Objective_memberContext *ctx) = 0;

  virtual void enterObjective_requirement_usage(SysMLv2Parser::Objective_requirement_usageContext *ctx) = 0;
  virtual void exitObjective_requirement_usage(SysMLv2Parser::Objective_requirement_usageContext *ctx) = 0;

  virtual void enterAnalysis_case_definition(SysMLv2Parser::Analysis_case_definitionContext *ctx) = 0;
  virtual void exitAnalysis_case_definition(SysMLv2Parser::Analysis_case_definitionContext *ctx) = 0;

  virtual void enterAnalysis_case_usage(SysMLv2Parser::Analysis_case_usageContext *ctx) = 0;
  virtual void exitAnalysis_case_usage(SysMLv2Parser::Analysis_case_usageContext *ctx) = 0;

  virtual void enterVerification_case_definition(SysMLv2Parser::Verification_case_definitionContext *ctx) = 0;
  virtual void exitVerification_case_definition(SysMLv2Parser::Verification_case_definitionContext *ctx) = 0;

  virtual void enterVerification_case_usage(SysMLv2Parser::Verification_case_usageContext *ctx) = 0;
  virtual void exitVerification_case_usage(SysMLv2Parser::Verification_case_usageContext *ctx) = 0;

  virtual void enterRequirement_verification_member(SysMLv2Parser::Requirement_verification_memberContext *ctx) = 0;
  virtual void exitRequirement_verification_member(SysMLv2Parser::Requirement_verification_memberContext *ctx) = 0;

  virtual void enterRequirement_verification_usage(SysMLv2Parser::Requirement_verification_usageContext *ctx) = 0;
  virtual void exitRequirement_verification_usage(SysMLv2Parser::Requirement_verification_usageContext *ctx) = 0;

  virtual void enterUse_case_definition(SysMLv2Parser::Use_case_definitionContext *ctx) = 0;
  virtual void exitUse_case_definition(SysMLv2Parser::Use_case_definitionContext *ctx) = 0;

  virtual void enterUse_case_usage(SysMLv2Parser::Use_case_usageContext *ctx) = 0;
  virtual void exitUse_case_usage(SysMLv2Parser::Use_case_usageContext *ctx) = 0;

  virtual void enterInclude_use_case_usage(SysMLv2Parser::Include_use_case_usageContext *ctx) = 0;
  virtual void exitInclude_use_case_usage(SysMLv2Parser::Include_use_case_usageContext *ctx) = 0;

  virtual void enterView_definition(SysMLv2Parser::View_definitionContext *ctx) = 0;
  virtual void exitView_definition(SysMLv2Parser::View_definitionContext *ctx) = 0;

  virtual void enterView_definition_body(SysMLv2Parser::View_definition_bodyContext *ctx) = 0;
  virtual void exitView_definition_body(SysMLv2Parser::View_definition_bodyContext *ctx) = 0;

  virtual void enterView_definition_body_item(SysMLv2Parser::View_definition_body_itemContext *ctx) = 0;
  virtual void exitView_definition_body_item(SysMLv2Parser::View_definition_body_itemContext *ctx) = 0;

  virtual void enterView_rendering_member(SysMLv2Parser::View_rendering_memberContext *ctx) = 0;
  virtual void exitView_rendering_member(SysMLv2Parser::View_rendering_memberContext *ctx) = 0;

  virtual void enterView_rendering_usage(SysMLv2Parser::View_rendering_usageContext *ctx) = 0;
  virtual void exitView_rendering_usage(SysMLv2Parser::View_rendering_usageContext *ctx) = 0;

  virtual void enterView_usage(SysMLv2Parser::View_usageContext *ctx) = 0;
  virtual void exitView_usage(SysMLv2Parser::View_usageContext *ctx) = 0;

  virtual void enterView_body(SysMLv2Parser::View_bodyContext *ctx) = 0;
  virtual void exitView_body(SysMLv2Parser::View_bodyContext *ctx) = 0;

  virtual void enterView_body_item(SysMLv2Parser::View_body_itemContext *ctx) = 0;
  virtual void exitView_body_item(SysMLv2Parser::View_body_itemContext *ctx) = 0;

  virtual void enterExpose(SysMLv2Parser::ExposeContext *ctx) = 0;
  virtual void exitExpose(SysMLv2Parser::ExposeContext *ctx) = 0;

  virtual void enterMembership_expose(SysMLv2Parser::Membership_exposeContext *ctx) = 0;
  virtual void exitMembership_expose(SysMLv2Parser::Membership_exposeContext *ctx) = 0;

  virtual void enterNamespace_expose(SysMLv2Parser::Namespace_exposeContext *ctx) = 0;
  virtual void exitNamespace_expose(SysMLv2Parser::Namespace_exposeContext *ctx) = 0;

  virtual void enterViewpoint_definition(SysMLv2Parser::Viewpoint_definitionContext *ctx) = 0;
  virtual void exitViewpoint_definition(SysMLv2Parser::Viewpoint_definitionContext *ctx) = 0;

  virtual void enterViewpoint_usage(SysMLv2Parser::Viewpoint_usageContext *ctx) = 0;
  virtual void exitViewpoint_usage(SysMLv2Parser::Viewpoint_usageContext *ctx) = 0;

  virtual void enterRendering_definition(SysMLv2Parser::Rendering_definitionContext *ctx) = 0;
  virtual void exitRendering_definition(SysMLv2Parser::Rendering_definitionContext *ctx) = 0;

  virtual void enterRendering_usage(SysMLv2Parser::Rendering_usageContext *ctx) = 0;
  virtual void exitRendering_usage(SysMLv2Parser::Rendering_usageContext *ctx) = 0;

  virtual void enterMetadata_definition(SysMLv2Parser::Metadata_definitionContext *ctx) = 0;
  virtual void exitMetadata_definition(SysMLv2Parser::Metadata_definitionContext *ctx) = 0;

  virtual void enterPrefix_metadata_annotation(SysMLv2Parser::Prefix_metadata_annotationContext *ctx) = 0;
  virtual void exitPrefix_metadata_annotation(SysMLv2Parser::Prefix_metadata_annotationContext *ctx) = 0;

  virtual void enterPrefix_metadata_member(SysMLv2Parser::Prefix_metadata_memberContext *ctx) = 0;
  virtual void exitPrefix_metadata_member(SysMLv2Parser::Prefix_metadata_memberContext *ctx) = 0;

  virtual void enterPrefix_metadata_usage(SysMLv2Parser::Prefix_metadata_usageContext *ctx) = 0;
  virtual void exitPrefix_metadata_usage(SysMLv2Parser::Prefix_metadata_usageContext *ctx) = 0;

  virtual void enterMetadata_usage(SysMLv2Parser::Metadata_usageContext *ctx) = 0;
  virtual void exitMetadata_usage(SysMLv2Parser::Metadata_usageContext *ctx) = 0;

  virtual void enterMetadata_usage_declaration(SysMLv2Parser::Metadata_usage_declarationContext *ctx) = 0;
  virtual void exitMetadata_usage_declaration(SysMLv2Parser::Metadata_usage_declarationContext *ctx) = 0;

  virtual void enterMetadata_body(SysMLv2Parser::Metadata_bodyContext *ctx) = 0;
  virtual void exitMetadata_body(SysMLv2Parser::Metadata_bodyContext *ctx) = 0;

  virtual void enterMetadata_body_usage_member(SysMLv2Parser::Metadata_body_usage_memberContext *ctx) = 0;
  virtual void exitMetadata_body_usage_member(SysMLv2Parser::Metadata_body_usage_memberContext *ctx) = 0;

  virtual void enterMetadata_body_usage(SysMLv2Parser::Metadata_body_usageContext *ctx) = 0;
  virtual void exitMetadata_body_usage(SysMLv2Parser::Metadata_body_usageContext *ctx) = 0;

  virtual void enterExtended_definition(SysMLv2Parser::Extended_definitionContext *ctx) = 0;
  virtual void exitExtended_definition(SysMLv2Parser::Extended_definitionContext *ctx) = 0;

  virtual void enterExtended_usage(SysMLv2Parser::Extended_usageContext *ctx) = 0;
  virtual void exitExtended_usage(SysMLv2Parser::Extended_usageContext *ctx) = 0;

  virtual void enterElements(SysMLv2Parser::ElementsContext *ctx) = 0;
  virtual void exitElements(SysMLv2Parser::ElementsContext *ctx) = 0;

  virtual void enterIdentification(SysMLv2Parser::IdentificationContext *ctx) = 0;
  virtual void exitIdentification(SysMLv2Parser::IdentificationContext *ctx) = 0;

  virtual void enterRelationship_onwed_elements(SysMLv2Parser::Relationship_onwed_elementsContext *ctx) = 0;
  virtual void exitRelationship_onwed_elements(SysMLv2Parser::Relationship_onwed_elementsContext *ctx) = 0;

  virtual void enterRelationship_owned_element(SysMLv2Parser::Relationship_owned_elementContext *ctx) = 0;
  virtual void exitRelationship_owned_element(SysMLv2Parser::Relationship_owned_elementContext *ctx) = 0;

  virtual void enterOwned_related_element(SysMLv2Parser::Owned_related_elementContext *ctx) = 0;
  virtual void exitOwned_related_element(SysMLv2Parser::Owned_related_elementContext *ctx) = 0;

  virtual void enterNamespace(SysMLv2Parser::NamespaceContext *ctx) = 0;
  virtual void exitNamespace(SysMLv2Parser::NamespaceContext *ctx) = 0;

  virtual void enterNamespace_declaration(SysMLv2Parser::Namespace_declarationContext *ctx) = 0;
  virtual void exitNamespace_declaration(SysMLv2Parser::Namespace_declarationContext *ctx) = 0;

  virtual void enterNamespace_body(SysMLv2Parser::Namespace_bodyContext *ctx) = 0;
  virtual void exitNamespace_body(SysMLv2Parser::Namespace_bodyContext *ctx) = 0;

  virtual void enterNamespace_body_elements(SysMLv2Parser::Namespace_body_elementsContext *ctx) = 0;
  virtual void exitNamespace_body_elements(SysMLv2Parser::Namespace_body_elementsContext *ctx) = 0;

  virtual void enterNamespace_body_element(SysMLv2Parser::Namespace_body_elementContext *ctx) = 0;
  virtual void exitNamespace_body_element(SysMLv2Parser::Namespace_body_elementContext *ctx) = 0;

  virtual void enterMember_prefix(SysMLv2Parser::Member_prefixContext *ctx) = 0;
  virtual void exitMember_prefix(SysMLv2Parser::Member_prefixContext *ctx) = 0;

  virtual void enterVisibility_indicator(SysMLv2Parser::Visibility_indicatorContext *ctx) = 0;
  virtual void exitVisibility_indicator(SysMLv2Parser::Visibility_indicatorContext *ctx) = 0;

  virtual void enterNamespace_member(SysMLv2Parser::Namespace_memberContext *ctx) = 0;
  virtual void exitNamespace_member(SysMLv2Parser::Namespace_memberContext *ctx) = 0;

  virtual void enterNon_feature_member(SysMLv2Parser::Non_feature_memberContext *ctx) = 0;
  virtual void exitNon_feature_member(SysMLv2Parser::Non_feature_memberContext *ctx) = 0;

  virtual void enterNamespace_feature_member(SysMLv2Parser::Namespace_feature_memberContext *ctx) = 0;
  virtual void exitNamespace_feature_member(SysMLv2Parser::Namespace_feature_memberContext *ctx) = 0;

  virtual void enterQualified_name(SysMLv2Parser::Qualified_nameContext *ctx) = 0;
  virtual void exitQualified_name(SysMLv2Parser::Qualified_nameContext *ctx) = 0;

  virtual void enterNamespace_import(SysMLv2Parser::Namespace_importContext *ctx) = 0;
  virtual void exitNamespace_import(SysMLv2Parser::Namespace_importContext *ctx) = 0;

  virtual void enterImport_declaration(SysMLv2Parser::Import_declarationContext *ctx) = 0;
  virtual void exitImport_declaration(SysMLv2Parser::Import_declarationContext *ctx) = 0;

  virtual void enterMembership_import(SysMLv2Parser::Membership_importContext *ctx) = 0;
  virtual void exitMembership_import(SysMLv2Parser::Membership_importContext *ctx) = 0;

  virtual void enterFilter_package(SysMLv2Parser::Filter_packageContext *ctx) = 0;
  virtual void exitFilter_package(SysMLv2Parser::Filter_packageContext *ctx) = 0;

  virtual void enterFilter_package_member(SysMLv2Parser::Filter_package_memberContext *ctx) = 0;
  virtual void exitFilter_package_member(SysMLv2Parser::Filter_package_memberContext *ctx) = 0;

  virtual void enterElement(SysMLv2Parser::ElementContext *ctx) = 0;
  virtual void exitElement(SysMLv2Parser::ElementContext *ctx) = 0;

  virtual void enterNon_feature_element(SysMLv2Parser::Non_feature_elementContext *ctx) = 0;
  virtual void exitNon_feature_element(SysMLv2Parser::Non_feature_elementContext *ctx) = 0;

  virtual void enterFeature_element(SysMLv2Parser::Feature_elementContext *ctx) = 0;
  virtual void exitFeature_element(SysMLv2Parser::Feature_elementContext *ctx) = 0;

  virtual void enterAdditional_options(SysMLv2Parser::Additional_optionsContext *ctx) = 0;
  virtual void exitAdditional_options(SysMLv2Parser::Additional_optionsContext *ctx) = 0;

  virtual void enterType(SysMLv2Parser::TypeContext *ctx) = 0;
  virtual void exitType(SysMLv2Parser::TypeContext *ctx) = 0;

  virtual void enterType_prefix(SysMLv2Parser::Type_prefixContext *ctx) = 0;
  virtual void exitType_prefix(SysMLv2Parser::Type_prefixContext *ctx) = 0;

  virtual void enterType_declaration(SysMLv2Parser::Type_declarationContext *ctx) = 0;
  virtual void exitType_declaration(SysMLv2Parser::Type_declarationContext *ctx) = 0;

  virtual void enterSpecialization_part(SysMLv2Parser::Specialization_partContext *ctx) = 0;
  virtual void exitSpecialization_part(SysMLv2Parser::Specialization_partContext *ctx) = 0;

  virtual void enterConjugation_part(SysMLv2Parser::Conjugation_partContext *ctx) = 0;
  virtual void exitConjugation_part(SysMLv2Parser::Conjugation_partContext *ctx) = 0;

  virtual void enterType_relationship_part(SysMLv2Parser::Type_relationship_partContext *ctx) = 0;
  virtual void exitType_relationship_part(SysMLv2Parser::Type_relationship_partContext *ctx) = 0;

  virtual void enterDisjoining_part(SysMLv2Parser::Disjoining_partContext *ctx) = 0;
  virtual void exitDisjoining_part(SysMLv2Parser::Disjoining_partContext *ctx) = 0;

  virtual void enterUnioning_part(SysMLv2Parser::Unioning_partContext *ctx) = 0;
  virtual void exitUnioning_part(SysMLv2Parser::Unioning_partContext *ctx) = 0;

  virtual void enterIntersecting_part(SysMLv2Parser::Intersecting_partContext *ctx) = 0;
  virtual void exitIntersecting_part(SysMLv2Parser::Intersecting_partContext *ctx) = 0;

  virtual void enterDifferencing_part(SysMLv2Parser::Differencing_partContext *ctx) = 0;
  virtual void exitDifferencing_part(SysMLv2Parser::Differencing_partContext *ctx) = 0;

  virtual void enterType_body(SysMLv2Parser::Type_bodyContext *ctx) = 0;
  virtual void exitType_body(SysMLv2Parser::Type_bodyContext *ctx) = 0;

  virtual void enterType_body_elements(SysMLv2Parser::Type_body_elementsContext *ctx) = 0;
  virtual void exitType_body_elements(SysMLv2Parser::Type_body_elementsContext *ctx) = 0;

  virtual void enterType_body_element(SysMLv2Parser::Type_body_elementContext *ctx) = 0;
  virtual void exitType_body_element(SysMLv2Parser::Type_body_elementContext *ctx) = 0;

  virtual void enterSpecialization(SysMLv2Parser::SpecializationContext *ctx) = 0;
  virtual void exitSpecialization(SysMLv2Parser::SpecializationContext *ctx) = 0;

  virtual void enterOwned_specialization(SysMLv2Parser::Owned_specializationContext *ctx) = 0;
  virtual void exitOwned_specialization(SysMLv2Parser::Owned_specializationContext *ctx) = 0;

  virtual void enterSpecific_type(SysMLv2Parser::Specific_typeContext *ctx) = 0;
  virtual void exitSpecific_type(SysMLv2Parser::Specific_typeContext *ctx) = 0;

  virtual void enterGeneral_type(SysMLv2Parser::General_typeContext *ctx) = 0;
  virtual void exitGeneral_type(SysMLv2Parser::General_typeContext *ctx) = 0;

  virtual void enterConjunction(SysMLv2Parser::ConjunctionContext *ctx) = 0;
  virtual void exitConjunction(SysMLv2Parser::ConjunctionContext *ctx) = 0;

  virtual void enterOwned_conjugation(SysMLv2Parser::Owned_conjugationContext *ctx) = 0;
  virtual void exitOwned_conjugation(SysMLv2Parser::Owned_conjugationContext *ctx) = 0;

  virtual void enterDisjoining(SysMLv2Parser::DisjoiningContext *ctx) = 0;
  virtual void exitDisjoining(SysMLv2Parser::DisjoiningContext *ctx) = 0;

  virtual void enterOwned_disjoining(SysMLv2Parser::Owned_disjoiningContext *ctx) = 0;
  virtual void exitOwned_disjoining(SysMLv2Parser::Owned_disjoiningContext *ctx) = 0;

  virtual void enterUnioning(SysMLv2Parser::UnioningContext *ctx) = 0;
  virtual void exitUnioning(SysMLv2Parser::UnioningContext *ctx) = 0;

  virtual void enterIntersecting(SysMLv2Parser::IntersectingContext *ctx) = 0;
  virtual void exitIntersecting(SysMLv2Parser::IntersectingContext *ctx) = 0;

  virtual void enterDifferencing(SysMLv2Parser::DifferencingContext *ctx) = 0;
  virtual void exitDifferencing(SysMLv2Parser::DifferencingContext *ctx) = 0;

  virtual void enterFeature_member(SysMLv2Parser::Feature_memberContext *ctx) = 0;
  virtual void exitFeature_member(SysMLv2Parser::Feature_memberContext *ctx) = 0;

  virtual void enterType_feature_member(SysMLv2Parser::Type_feature_memberContext *ctx) = 0;
  virtual void exitType_feature_member(SysMLv2Parser::Type_feature_memberContext *ctx) = 0;

  virtual void enterOwned_feature_member(SysMLv2Parser::Owned_feature_memberContext *ctx) = 0;
  virtual void exitOwned_feature_member(SysMLv2Parser::Owned_feature_memberContext *ctx) = 0;

  virtual void enterClassifier(SysMLv2Parser::ClassifierContext *ctx) = 0;
  virtual void exitClassifier(SysMLv2Parser::ClassifierContext *ctx) = 0;

  virtual void enterClassifier_declaration(SysMLv2Parser::Classifier_declarationContext *ctx) = 0;
  virtual void exitClassifier_declaration(SysMLv2Parser::Classifier_declarationContext *ctx) = 0;

  virtual void enterSuperclassing_part(SysMLv2Parser::Superclassing_partContext *ctx) = 0;
  virtual void exitSuperclassing_part(SysMLv2Parser::Superclassing_partContext *ctx) = 0;

  virtual void enterSubclassification(SysMLv2Parser::SubclassificationContext *ctx) = 0;
  virtual void exitSubclassification(SysMLv2Parser::SubclassificationContext *ctx) = 0;

  virtual void enterOwned_subclassification(SysMLv2Parser::Owned_subclassificationContext *ctx) = 0;
  virtual void exitOwned_subclassification(SysMLv2Parser::Owned_subclassificationContext *ctx) = 0;

  virtual void enterFeature(SysMLv2Parser::FeatureContext *ctx) = 0;
  virtual void exitFeature(SysMLv2Parser::FeatureContext *ctx) = 0;

  virtual void enterFeature_prefix(SysMLv2Parser::Feature_prefixContext *ctx) = 0;
  virtual void exitFeature_prefix(SysMLv2Parser::Feature_prefixContext *ctx) = 0;

  virtual void enterFeature_declaration(SysMLv2Parser::Feature_declarationContext *ctx) = 0;
  virtual void exitFeature_declaration(SysMLv2Parser::Feature_declarationContext *ctx) = 0;

  virtual void enterFeature_identification(SysMLv2Parser::Feature_identificationContext *ctx) = 0;
  virtual void exitFeature_identification(SysMLv2Parser::Feature_identificationContext *ctx) = 0;

  virtual void enterFeature_relationship_part(SysMLv2Parser::Feature_relationship_partContext *ctx) = 0;
  virtual void exitFeature_relationship_part(SysMLv2Parser::Feature_relationship_partContext *ctx) = 0;

  virtual void enterChaining_part(SysMLv2Parser::Chaining_partContext *ctx) = 0;
  virtual void exitChaining_part(SysMLv2Parser::Chaining_partContext *ctx) = 0;

  virtual void enterInverting_part(SysMLv2Parser::Inverting_partContext *ctx) = 0;
  virtual void exitInverting_part(SysMLv2Parser::Inverting_partContext *ctx) = 0;

  virtual void enterType_featuring_part(SysMLv2Parser::Type_featuring_partContext *ctx) = 0;
  virtual void exitType_featuring_part(SysMLv2Parser::Type_featuring_partContext *ctx) = 0;

  virtual void enterFeature_specialization_part(SysMLv2Parser::Feature_specialization_partContext *ctx) = 0;
  virtual void exitFeature_specialization_part(SysMLv2Parser::Feature_specialization_partContext *ctx) = 0;

  virtual void enterFeature_specilization(SysMLv2Parser::Feature_specilizationContext *ctx) = 0;
  virtual void exitFeature_specilization(SysMLv2Parser::Feature_specilizationContext *ctx) = 0;

  virtual void enterTypings(SysMLv2Parser::TypingsContext *ctx) = 0;
  virtual void exitTypings(SysMLv2Parser::TypingsContext *ctx) = 0;

  virtual void enterTyped_by(SysMLv2Parser::Typed_byContext *ctx) = 0;
  virtual void exitTyped_by(SysMLv2Parser::Typed_byContext *ctx) = 0;

  virtual void enterSubsettings(SysMLv2Parser::SubsettingsContext *ctx) = 0;
  virtual void exitSubsettings(SysMLv2Parser::SubsettingsContext *ctx) = 0;

  virtual void enterSubsets(SysMLv2Parser::SubsetsContext *ctx) = 0;
  virtual void exitSubsets(SysMLv2Parser::SubsetsContext *ctx) = 0;

  virtual void enterReferences(SysMLv2Parser::ReferencesContext *ctx) = 0;
  virtual void exitReferences(SysMLv2Parser::ReferencesContext *ctx) = 0;

  virtual void enterRedefinitions(SysMLv2Parser::RedefinitionsContext *ctx) = 0;
  virtual void exitRedefinitions(SysMLv2Parser::RedefinitionsContext *ctx) = 0;

  virtual void enterRedefines(SysMLv2Parser::RedefinesContext *ctx) = 0;
  virtual void exitRedefines(SysMLv2Parser::RedefinesContext *ctx) = 0;

  virtual void enterFeature_typing(SysMLv2Parser::Feature_typingContext *ctx) = 0;
  virtual void exitFeature_typing(SysMLv2Parser::Feature_typingContext *ctx) = 0;

  virtual void enterOwned_feature_typing(SysMLv2Parser::Owned_feature_typingContext *ctx) = 0;
  virtual void exitOwned_feature_typing(SysMLv2Parser::Owned_feature_typingContext *ctx) = 0;

  virtual void enterSubsetting(SysMLv2Parser::SubsettingContext *ctx) = 0;
  virtual void exitSubsetting(SysMLv2Parser::SubsettingContext *ctx) = 0;

  virtual void enterOwned_subsetting(SysMLv2Parser::Owned_subsettingContext *ctx) = 0;
  virtual void exitOwned_subsetting(SysMLv2Parser::Owned_subsettingContext *ctx) = 0;

  virtual void enterOwned_reference_subsetting(SysMLv2Parser::Owned_reference_subsettingContext *ctx) = 0;
  virtual void exitOwned_reference_subsetting(SysMLv2Parser::Owned_reference_subsettingContext *ctx) = 0;

  virtual void enterRedefinition(SysMLv2Parser::RedefinitionContext *ctx) = 0;
  virtual void exitRedefinition(SysMLv2Parser::RedefinitionContext *ctx) = 0;

  virtual void enterOwned_redefinition(SysMLv2Parser::Owned_redefinitionContext *ctx) = 0;
  virtual void exitOwned_redefinition(SysMLv2Parser::Owned_redefinitionContext *ctx) = 0;

  virtual void enterOwned_feature_chain(SysMLv2Parser::Owned_feature_chainContext *ctx) = 0;
  virtual void exitOwned_feature_chain(SysMLv2Parser::Owned_feature_chainContext *ctx) = 0;

  virtual void enterFeature_chain(SysMLv2Parser::Feature_chainContext *ctx) = 0;
  virtual void exitFeature_chain(SysMLv2Parser::Feature_chainContext *ctx) = 0;

  virtual void enterOwned_feature_chaining(SysMLv2Parser::Owned_feature_chainingContext *ctx) = 0;
  virtual void exitOwned_feature_chaining(SysMLv2Parser::Owned_feature_chainingContext *ctx) = 0;

  virtual void enterFeature_inverting(SysMLv2Parser::Feature_invertingContext *ctx) = 0;
  virtual void exitFeature_inverting(SysMLv2Parser::Feature_invertingContext *ctx) = 0;

  virtual void enterOwned_feature_inverting(SysMLv2Parser::Owned_feature_invertingContext *ctx) = 0;
  virtual void exitOwned_feature_inverting(SysMLv2Parser::Owned_feature_invertingContext *ctx) = 0;

  virtual void enterType_featuring(SysMLv2Parser::Type_featuringContext *ctx) = 0;
  virtual void exitType_featuring(SysMLv2Parser::Type_featuringContext *ctx) = 0;

  virtual void enterOwned_type_featuring(SysMLv2Parser::Owned_type_featuringContext *ctx) = 0;
  virtual void exitOwned_type_featuring(SysMLv2Parser::Owned_type_featuringContext *ctx) = 0;

  virtual void enterData_type(SysMLv2Parser::Data_typeContext *ctx) = 0;
  virtual void exitData_type(SysMLv2Parser::Data_typeContext *ctx) = 0;

  virtual void enterClass(SysMLv2Parser::ClassContext *ctx) = 0;
  virtual void exitClass(SysMLv2Parser::ClassContext *ctx) = 0;

  virtual void enterStructure(SysMLv2Parser::StructureContext *ctx) = 0;
  virtual void exitStructure(SysMLv2Parser::StructureContext *ctx) = 0;

  virtual void enterAssociation(SysMLv2Parser::AssociationContext *ctx) = 0;
  virtual void exitAssociation(SysMLv2Parser::AssociationContext *ctx) = 0;

  virtual void enterAssociation_structure(SysMLv2Parser::Association_structureContext *ctx) = 0;
  virtual void exitAssociation_structure(SysMLv2Parser::Association_structureContext *ctx) = 0;

  virtual void enterConnector(SysMLv2Parser::ConnectorContext *ctx) = 0;
  virtual void exitConnector(SysMLv2Parser::ConnectorContext *ctx) = 0;

  virtual void enterConnector_declaration(SysMLv2Parser::Connector_declarationContext *ctx) = 0;
  virtual void exitConnector_declaration(SysMLv2Parser::Connector_declarationContext *ctx) = 0;

  virtual void enterBinary_connector_declaration(SysMLv2Parser::Binary_connector_declarationContext *ctx) = 0;
  virtual void exitBinary_connector_declaration(SysMLv2Parser::Binary_connector_declarationContext *ctx) = 0;

  virtual void enterNary_connector_declaration(SysMLv2Parser::Nary_connector_declarationContext *ctx) = 0;
  virtual void exitNary_connector_declaration(SysMLv2Parser::Nary_connector_declarationContext *ctx) = 0;

  virtual void enterConnector_end(SysMLv2Parser::Connector_endContext *ctx) = 0;
  virtual void exitConnector_end(SysMLv2Parser::Connector_endContext *ctx) = 0;

  virtual void enterBinding_connector(SysMLv2Parser::Binding_connectorContext *ctx) = 0;
  virtual void exitBinding_connector(SysMLv2Parser::Binding_connectorContext *ctx) = 0;

  virtual void enterBinding_connector_declaration(SysMLv2Parser::Binding_connector_declarationContext *ctx) = 0;
  virtual void exitBinding_connector_declaration(SysMLv2Parser::Binding_connector_declarationContext *ctx) = 0;

  virtual void enterSuccession(SysMLv2Parser::SuccessionContext *ctx) = 0;
  virtual void exitSuccession(SysMLv2Parser::SuccessionContext *ctx) = 0;

  virtual void enterSuccession_declaration(SysMLv2Parser::Succession_declarationContext *ctx) = 0;
  virtual void exitSuccession_declaration(SysMLv2Parser::Succession_declarationContext *ctx) = 0;

  virtual void enterBehavior(SysMLv2Parser::BehaviorContext *ctx) = 0;
  virtual void exitBehavior(SysMLv2Parser::BehaviorContext *ctx) = 0;

  virtual void enterStep(SysMLv2Parser::StepContext *ctx) = 0;
  virtual void exitStep(SysMLv2Parser::StepContext *ctx) = 0;

  virtual void enterFunction(SysMLv2Parser::FunctionContext *ctx) = 0;
  virtual void exitFunction(SysMLv2Parser::FunctionContext *ctx) = 0;

  virtual void enterFunction_body(SysMLv2Parser::Function_bodyContext *ctx) = 0;
  virtual void exitFunction_body(SysMLv2Parser::Function_bodyContext *ctx) = 0;

  virtual void enterFunction_body_part(SysMLv2Parser::Function_body_partContext *ctx) = 0;
  virtual void exitFunction_body_part(SysMLv2Parser::Function_body_partContext *ctx) = 0;

  virtual void enterReturn_feature_member(SysMLv2Parser::Return_feature_memberContext *ctx) = 0;
  virtual void exitReturn_feature_member(SysMLv2Parser::Return_feature_memberContext *ctx) = 0;

  virtual void enterExpression(SysMLv2Parser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(SysMLv2Parser::ExpressionContext *ctx) = 0;

  virtual void enterPredicate(SysMLv2Parser::PredicateContext *ctx) = 0;
  virtual void exitPredicate(SysMLv2Parser::PredicateContext *ctx) = 0;

  virtual void enterBoolean_expression(SysMLv2Parser::Boolean_expressionContext *ctx) = 0;
  virtual void exitBoolean_expression(SysMLv2Parser::Boolean_expressionContext *ctx) = 0;

  virtual void enterInvariant(SysMLv2Parser::InvariantContext *ctx) = 0;
  virtual void exitInvariant(SysMLv2Parser::InvariantContext *ctx) = 0;

  virtual void enterOwned_expression_reference_member(SysMLv2Parser::Owned_expression_reference_memberContext *ctx) = 0;
  virtual void exitOwned_expression_reference_member(SysMLv2Parser::Owned_expression_reference_memberContext *ctx) = 0;

  virtual void enterOwned_expression_reference(SysMLv2Parser::Owned_expression_referenceContext *ctx) = 0;
  virtual void exitOwned_expression_reference(SysMLv2Parser::Owned_expression_referenceContext *ctx) = 0;

  virtual void enterOwned_expression_member(SysMLv2Parser::Owned_expression_memberContext *ctx) = 0;
  virtual void exitOwned_expression_member(SysMLv2Parser::Owned_expression_memberContext *ctx) = 0;

  virtual void enterOwned_expressions(SysMLv2Parser::Owned_expressionsContext *ctx) = 0;
  virtual void exitOwned_expressions(SysMLv2Parser::Owned_expressionsContext *ctx) = 0;

  virtual void enterOwned_expression(SysMLv2Parser::Owned_expressionContext *ctx) = 0;
  virtual void exitOwned_expression(SysMLv2Parser::Owned_expressionContext *ctx) = 0;

  virtual void enterEased_owned_expression(SysMLv2Parser::Eased_owned_expressionContext *ctx) = 0;
  virtual void exitEased_owned_expression(SysMLv2Parser::Eased_owned_expressionContext *ctx) = 0;

  virtual void enterConditional_expression(SysMLv2Parser::Conditional_expressionContext *ctx) = 0;
  virtual void exitConditional_expression(SysMLv2Parser::Conditional_expressionContext *ctx) = 0;

  virtual void enterConditional_binary_operator_expression(SysMLv2Parser::Conditional_binary_operator_expressionContext *ctx) = 0;
  virtual void exitConditional_binary_operator_expression(SysMLv2Parser::Conditional_binary_operator_expressionContext *ctx) = 0;

  virtual void enterConditional_binary_operator(SysMLv2Parser::Conditional_binary_operatorContext *ctx) = 0;
  virtual void exitConditional_binary_operator(SysMLv2Parser::Conditional_binary_operatorContext *ctx) = 0;

  virtual void enterBinary_operator_expression(SysMLv2Parser::Binary_operator_expressionContext *ctx) = 0;
  virtual void exitBinary_operator_expression(SysMLv2Parser::Binary_operator_expressionContext *ctx) = 0;

  virtual void enterBinary_operator(SysMLv2Parser::Binary_operatorContext *ctx) = 0;
  virtual void exitBinary_operator(SysMLv2Parser::Binary_operatorContext *ctx) = 0;

  virtual void enterUnary_operator_expression(SysMLv2Parser::Unary_operator_expressionContext *ctx) = 0;
  virtual void exitUnary_operator_expression(SysMLv2Parser::Unary_operator_expressionContext *ctx) = 0;

  virtual void enterUnary_operator(SysMLv2Parser::Unary_operatorContext *ctx) = 0;
  virtual void exitUnary_operator(SysMLv2Parser::Unary_operatorContext *ctx) = 0;

  virtual void enterClassification_expression(SysMLv2Parser::Classification_expressionContext *ctx) = 0;
  virtual void exitClassification_expression(SysMLv2Parser::Classification_expressionContext *ctx) = 0;

  virtual void enterClassification(SysMLv2Parser::ClassificationContext *ctx) = 0;
  virtual void exitClassification(SysMLv2Parser::ClassificationContext *ctx) = 0;

  virtual void enterClassification_test_operator(SysMLv2Parser::Classification_test_operatorContext *ctx) = 0;
  virtual void exitClassification_test_operator(SysMLv2Parser::Classification_test_operatorContext *ctx) = 0;

  virtual void enterCast_operator(SysMLv2Parser::Cast_operatorContext *ctx) = 0;
  virtual void exitCast_operator(SysMLv2Parser::Cast_operatorContext *ctx) = 0;

  virtual void enterMetaclassification_expression(SysMLv2Parser::Metaclassification_expressionContext *ctx) = 0;
  virtual void exitMetaclassification_expression(SysMLv2Parser::Metaclassification_expressionContext *ctx) = 0;

  virtual void enterArgument_member(SysMLv2Parser::Argument_memberContext *ctx) = 0;
  virtual void exitArgument_member(SysMLv2Parser::Argument_memberContext *ctx) = 0;

  virtual void enterArgument(SysMLv2Parser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(SysMLv2Parser::ArgumentContext *ctx) = 0;

  virtual void enterArgument_value(SysMLv2Parser::Argument_valueContext *ctx) = 0;
  virtual void exitArgument_value(SysMLv2Parser::Argument_valueContext *ctx) = 0;

  virtual void enterArgument_expression_member(SysMLv2Parser::Argument_expression_memberContext *ctx) = 0;
  virtual void exitArgument_expression_member(SysMLv2Parser::Argument_expression_memberContext *ctx) = 0;

  virtual void enterArgument_expression(SysMLv2Parser::Argument_expressionContext *ctx) = 0;
  virtual void exitArgument_expression(SysMLv2Parser::Argument_expressionContext *ctx) = 0;

  virtual void enterArgument_expression_value(SysMLv2Parser::Argument_expression_valueContext *ctx) = 0;
  virtual void exitArgument_expression_value(SysMLv2Parser::Argument_expression_valueContext *ctx) = 0;

  virtual void enterMetadata_argument_member(SysMLv2Parser::Metadata_argument_memberContext *ctx) = 0;
  virtual void exitMetadata_argument_member(SysMLv2Parser::Metadata_argument_memberContext *ctx) = 0;

  virtual void enterMetadata_argument(SysMLv2Parser::Metadata_argumentContext *ctx) = 0;
  virtual void exitMetadata_argument(SysMLv2Parser::Metadata_argumentContext *ctx) = 0;

  virtual void enterMetadata_value(SysMLv2Parser::Metadata_valueContext *ctx) = 0;
  virtual void exitMetadata_value(SysMLv2Parser::Metadata_valueContext *ctx) = 0;

  virtual void enterMetadata_reference(SysMLv2Parser::Metadata_referenceContext *ctx) = 0;
  virtual void exitMetadata_reference(SysMLv2Parser::Metadata_referenceContext *ctx) = 0;

  virtual void enterMetadataclassification_test_operator(SysMLv2Parser::Metadataclassification_test_operatorContext *ctx) = 0;
  virtual void exitMetadataclassification_test_operator(SysMLv2Parser::Metadataclassification_test_operatorContext *ctx) = 0;

  virtual void enterMeta_cast_operator(SysMLv2Parser::Meta_cast_operatorContext *ctx) = 0;
  virtual void exitMeta_cast_operator(SysMLv2Parser::Meta_cast_operatorContext *ctx) = 0;

  virtual void enterExtend_expression(SysMLv2Parser::Extend_expressionContext *ctx) = 0;
  virtual void exitExtend_expression(SysMLv2Parser::Extend_expressionContext *ctx) = 0;

  virtual void enterType_reference_member(SysMLv2Parser::Type_reference_memberContext *ctx) = 0;
  virtual void exitType_reference_member(SysMLv2Parser::Type_reference_memberContext *ctx) = 0;

  virtual void enterType_result_member(SysMLv2Parser::Type_result_memberContext *ctx) = 0;
  virtual void exitType_result_member(SysMLv2Parser::Type_result_memberContext *ctx) = 0;

  virtual void enterType_reference(SysMLv2Parser::Type_referenceContext *ctx) = 0;
  virtual void exitType_reference(SysMLv2Parser::Type_referenceContext *ctx) = 0;

  virtual void enterReference_typing(SysMLv2Parser::Reference_typingContext *ctx) = 0;
  virtual void exitReference_typing(SysMLv2Parser::Reference_typingContext *ctx) = 0;

  virtual void enterPrimary_expressions(SysMLv2Parser::Primary_expressionsContext *ctx) = 0;
  virtual void exitPrimary_expressions(SysMLv2Parser::Primary_expressionsContext *ctx) = 0;

  virtual void enterPrimary_expression(SysMLv2Parser::Primary_expressionContext *ctx) = 0;
  virtual void exitPrimary_expression(SysMLv2Parser::Primary_expressionContext *ctx) = 0;

  virtual void enterPrimary_argument_value(SysMLv2Parser::Primary_argument_valueContext *ctx) = 0;
  virtual void exitPrimary_argument_value(SysMLv2Parser::Primary_argument_valueContext *ctx) = 0;

  virtual void enterPrimary_argument(SysMLv2Parser::Primary_argumentContext *ctx) = 0;
  virtual void exitPrimary_argument(SysMLv2Parser::Primary_argumentContext *ctx) = 0;

  virtual void enterPrimary_argument_member(SysMLv2Parser::Primary_argument_memberContext *ctx) = 0;
  virtual void exitPrimary_argument_member(SysMLv2Parser::Primary_argument_memberContext *ctx) = 0;

  virtual void enterNon_feature_chain_primary_expression(SysMLv2Parser::Non_feature_chain_primary_expressionContext *ctx) = 0;
  virtual void exitNon_feature_chain_primary_expression(SysMLv2Parser::Non_feature_chain_primary_expressionContext *ctx) = 0;

  virtual void enterNon_feature_chain_primary_argument_value(SysMLv2Parser::Non_feature_chain_primary_argument_valueContext *ctx) = 0;
  virtual void exitNon_feature_chain_primary_argument_value(SysMLv2Parser::Non_feature_chain_primary_argument_valueContext *ctx) = 0;

  virtual void enterNon_feature_chain_primary_argument(SysMLv2Parser::Non_feature_chain_primary_argumentContext *ctx) = 0;
  virtual void exitNon_feature_chain_primary_argument(SysMLv2Parser::Non_feature_chain_primary_argumentContext *ctx) = 0;

  virtual void enterNon_feature_chain_primary_argument_member(SysMLv2Parser::Non_feature_chain_primary_argument_memberContext *ctx) = 0;
  virtual void exitNon_feature_chain_primary_argument_member(SysMLv2Parser::Non_feature_chain_primary_argument_memberContext *ctx) = 0;

  virtual void enterBracket_expression(SysMLv2Parser::Bracket_expressionContext *ctx) = 0;
  virtual void exitBracket_expression(SysMLv2Parser::Bracket_expressionContext *ctx) = 0;

  virtual void enterIndex_expression(SysMLv2Parser::Index_expressionContext *ctx) = 0;
  virtual void exitIndex_expression(SysMLv2Parser::Index_expressionContext *ctx) = 0;

  virtual void enterSequence_expression(SysMLv2Parser::Sequence_expressionContext *ctx) = 0;
  virtual void exitSequence_expression(SysMLv2Parser::Sequence_expressionContext *ctx) = 0;

  virtual void enterSequence_expression_list(SysMLv2Parser::Sequence_expression_listContext *ctx) = 0;
  virtual void exitSequence_expression_list(SysMLv2Parser::Sequence_expression_listContext *ctx) = 0;

  virtual void enterSequence_operator_expression(SysMLv2Parser::Sequence_operator_expressionContext *ctx) = 0;
  virtual void exitSequence_operator_expression(SysMLv2Parser::Sequence_operator_expressionContext *ctx) = 0;

  virtual void enterSequence_expression_list_member(SysMLv2Parser::Sequence_expression_list_memberContext *ctx) = 0;
  virtual void exitSequence_expression_list_member(SysMLv2Parser::Sequence_expression_list_memberContext *ctx) = 0;

  virtual void enterFeature_chain_expression(SysMLv2Parser::Feature_chain_expressionContext *ctx) = 0;
  virtual void exitFeature_chain_expression(SysMLv2Parser::Feature_chain_expressionContext *ctx) = 0;

  virtual void enterCollect_expression(SysMLv2Parser::Collect_expressionContext *ctx) = 0;
  virtual void exitCollect_expression(SysMLv2Parser::Collect_expressionContext *ctx) = 0;

  virtual void enterSelect_expression(SysMLv2Parser::Select_expressionContext *ctx) = 0;
  virtual void exitSelect_expression(SysMLv2Parser::Select_expressionContext *ctx) = 0;

  virtual void enterFunction_operation_expression(SysMLv2Parser::Function_operation_expressionContext *ctx) = 0;
  virtual void exitFunction_operation_expression(SysMLv2Parser::Function_operation_expressionContext *ctx) = 0;

  virtual void enterBody_argument_member(SysMLv2Parser::Body_argument_memberContext *ctx) = 0;
  virtual void exitBody_argument_member(SysMLv2Parser::Body_argument_memberContext *ctx) = 0;

  virtual void enterBody_argument(SysMLv2Parser::Body_argumentContext *ctx) = 0;
  virtual void exitBody_argument(SysMLv2Parser::Body_argumentContext *ctx) = 0;

  virtual void enterBody_argument_value(SysMLv2Parser::Body_argument_valueContext *ctx) = 0;
  virtual void exitBody_argument_value(SysMLv2Parser::Body_argument_valueContext *ctx) = 0;

  virtual void enterBody_expression_member(SysMLv2Parser::Body_expression_memberContext *ctx) = 0;
  virtual void exitBody_expression_member(SysMLv2Parser::Body_expression_memberContext *ctx) = 0;

  virtual void enterFunction_reference_argument_member(SysMLv2Parser::Function_reference_argument_memberContext *ctx) = 0;
  virtual void exitFunction_reference_argument_member(SysMLv2Parser::Function_reference_argument_memberContext *ctx) = 0;

  virtual void enterFunction_reference_argument(SysMLv2Parser::Function_reference_argumentContext *ctx) = 0;
  virtual void exitFunction_reference_argument(SysMLv2Parser::Function_reference_argumentContext *ctx) = 0;

  virtual void enterFunction_reference_arugment_value(SysMLv2Parser::Function_reference_arugment_valueContext *ctx) = 0;
  virtual void exitFunction_reference_arugment_value(SysMLv2Parser::Function_reference_arugment_valueContext *ctx) = 0;

  virtual void enterFunction_reference_expression(SysMLv2Parser::Function_reference_expressionContext *ctx) = 0;
  virtual void exitFunction_reference_expression(SysMLv2Parser::Function_reference_expressionContext *ctx) = 0;

  virtual void enterFunction_reference_member(SysMLv2Parser::Function_reference_memberContext *ctx) = 0;
  virtual void exitFunction_reference_member(SysMLv2Parser::Function_reference_memberContext *ctx) = 0;

  virtual void enterFunction_reference(SysMLv2Parser::Function_referenceContext *ctx) = 0;
  virtual void exitFunction_reference(SysMLv2Parser::Function_referenceContext *ctx) = 0;

  virtual void enterBase_expression(SysMLv2Parser::Base_expressionContext *ctx) = 0;
  virtual void exitBase_expression(SysMLv2Parser::Base_expressionContext *ctx) = 0;

  virtual void enterNull_expression(SysMLv2Parser::Null_expressionContext *ctx) = 0;
  virtual void exitNull_expression(SysMLv2Parser::Null_expressionContext *ctx) = 0;

  virtual void enterFeature_reference_expression(SysMLv2Parser::Feature_reference_expressionContext *ctx) = 0;
  virtual void exitFeature_reference_expression(SysMLv2Parser::Feature_reference_expressionContext *ctx) = 0;

  virtual void enterFeature_reference_member(SysMLv2Parser::Feature_reference_memberContext *ctx) = 0;
  virtual void exitFeature_reference_member(SysMLv2Parser::Feature_reference_memberContext *ctx) = 0;

  virtual void enterFeature_reference(SysMLv2Parser::Feature_referenceContext *ctx) = 0;
  virtual void exitFeature_reference(SysMLv2Parser::Feature_referenceContext *ctx) = 0;

  virtual void enterMetadata_access_expression(SysMLv2Parser::Metadata_access_expressionContext *ctx) = 0;
  virtual void exitMetadata_access_expression(SysMLv2Parser::Metadata_access_expressionContext *ctx) = 0;

  virtual void enterInvocation_expression(SysMLv2Parser::Invocation_expressionContext *ctx) = 0;
  virtual void exitInvocation_expression(SysMLv2Parser::Invocation_expressionContext *ctx) = 0;

  virtual void enterInternal_invocation_expression(SysMLv2Parser::Internal_invocation_expressionContext *ctx) = 0;
  virtual void exitInternal_invocation_expression(SysMLv2Parser::Internal_invocation_expressionContext *ctx) = 0;

  virtual void enterArgument_list(SysMLv2Parser::Argument_listContext *ctx) = 0;
  virtual void exitArgument_list(SysMLv2Parser::Argument_listContext *ctx) = 0;

  virtual void enterPositional_argument_list(SysMLv2Parser::Positional_argument_listContext *ctx) = 0;
  virtual void exitPositional_argument_list(SysMLv2Parser::Positional_argument_listContext *ctx) = 0;

  virtual void enterNamed_argument_list(SysMLv2Parser::Named_argument_listContext *ctx) = 0;
  virtual void exitNamed_argument_list(SysMLv2Parser::Named_argument_listContext *ctx) = 0;

  virtual void enterNamed_argument_member(SysMLv2Parser::Named_argument_memberContext *ctx) = 0;
  virtual void exitNamed_argument_member(SysMLv2Parser::Named_argument_memberContext *ctx) = 0;

  virtual void enterNamed_argument(SysMLv2Parser::Named_argumentContext *ctx) = 0;
  virtual void exitNamed_argument(SysMLv2Parser::Named_argumentContext *ctx) = 0;

  virtual void enterParamenter_redefinition(SysMLv2Parser::Paramenter_redefinitionContext *ctx) = 0;
  virtual void exitParamenter_redefinition(SysMLv2Parser::Paramenter_redefinitionContext *ctx) = 0;

  virtual void enterBody_expression(SysMLv2Parser::Body_expressionContext *ctx) = 0;
  virtual void exitBody_expression(SysMLv2Parser::Body_expressionContext *ctx) = 0;

  virtual void enterExpression_body_member(SysMLv2Parser::Expression_body_memberContext *ctx) = 0;
  virtual void exitExpression_body_member(SysMLv2Parser::Expression_body_memberContext *ctx) = 0;

  virtual void enterExpression_body(SysMLv2Parser::Expression_bodyContext *ctx) = 0;
  virtual void exitExpression_body(SysMLv2Parser::Expression_bodyContext *ctx) = 0;

  virtual void enterLiteral_expression(SysMLv2Parser::Literal_expressionContext *ctx) = 0;
  virtual void exitLiteral_expression(SysMLv2Parser::Literal_expressionContext *ctx) = 0;

  virtual void enterLiteral_boolean(SysMLv2Parser::Literal_booleanContext *ctx) = 0;
  virtual void exitLiteral_boolean(SysMLv2Parser::Literal_booleanContext *ctx) = 0;

  virtual void enterBoolean_value(SysMLv2Parser::Boolean_valueContext *ctx) = 0;
  virtual void exitBoolean_value(SysMLv2Parser::Boolean_valueContext *ctx) = 0;

  virtual void enterLiteral_string(SysMLv2Parser::Literal_stringContext *ctx) = 0;
  virtual void exitLiteral_string(SysMLv2Parser::Literal_stringContext *ctx) = 0;

  virtual void enterLiteral_integer(SysMLv2Parser::Literal_integerContext *ctx) = 0;
  virtual void exitLiteral_integer(SysMLv2Parser::Literal_integerContext *ctx) = 0;

  virtual void enterLiteral_real(SysMLv2Parser::Literal_realContext *ctx) = 0;
  virtual void exitLiteral_real(SysMLv2Parser::Literal_realContext *ctx) = 0;

  virtual void enterReal_value(SysMLv2Parser::Real_valueContext *ctx) = 0;
  virtual void exitReal_value(SysMLv2Parser::Real_valueContext *ctx) = 0;

  virtual void enterLiteral_infinity(SysMLv2Parser::Literal_infinityContext *ctx) = 0;
  virtual void exitLiteral_infinity(SysMLv2Parser::Literal_infinityContext *ctx) = 0;

  virtual void enterInteraction(SysMLv2Parser::InteractionContext *ctx) = 0;
  virtual void exitInteraction(SysMLv2Parser::InteractionContext *ctx) = 0;

  virtual void enterItem_flow(SysMLv2Parser::Item_flowContext *ctx) = 0;
  virtual void exitItem_flow(SysMLv2Parser::Item_flowContext *ctx) = 0;

  virtual void enterSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext *ctx) = 0;
  virtual void exitSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext *ctx) = 0;

  virtual void enterItem_flow_declaration(SysMLv2Parser::Item_flow_declarationContext *ctx) = 0;
  virtual void exitItem_flow_declaration(SysMLv2Parser::Item_flow_declarationContext *ctx) = 0;

  virtual void enterItem_feature_member(SysMLv2Parser::Item_feature_memberContext *ctx) = 0;
  virtual void exitItem_feature_member(SysMLv2Parser::Item_feature_memberContext *ctx) = 0;

  virtual void enterItem_feature(SysMLv2Parser::Item_featureContext *ctx) = 0;
  virtual void exitItem_feature(SysMLv2Parser::Item_featureContext *ctx) = 0;

  virtual void enterItem_feature_specilization_part(SysMLv2Parser::Item_feature_specilization_partContext *ctx) = 0;
  virtual void exitItem_feature_specilization_part(SysMLv2Parser::Item_feature_specilization_partContext *ctx) = 0;

  virtual void enterItem_flow_end_member(SysMLv2Parser::Item_flow_end_memberContext *ctx) = 0;
  virtual void exitItem_flow_end_member(SysMLv2Parser::Item_flow_end_memberContext *ctx) = 0;

  virtual void enterItem_flow_end(SysMLv2Parser::Item_flow_endContext *ctx) = 0;
  virtual void exitItem_flow_end(SysMLv2Parser::Item_flow_endContext *ctx) = 0;

  virtual void enterItem_flow_feature_member(SysMLv2Parser::Item_flow_feature_memberContext *ctx) = 0;
  virtual void exitItem_flow_feature_member(SysMLv2Parser::Item_flow_feature_memberContext *ctx) = 0;

  virtual void enterItem_flow_feature(SysMLv2Parser::Item_flow_featureContext *ctx) = 0;
  virtual void exitItem_flow_feature(SysMLv2Parser::Item_flow_featureContext *ctx) = 0;

  virtual void enterItem_flow_redefinition(SysMLv2Parser::Item_flow_redefinitionContext *ctx) = 0;
  virtual void exitItem_flow_redefinition(SysMLv2Parser::Item_flow_redefinitionContext *ctx) = 0;

  virtual void enterValue_part(SysMLv2Parser::Value_partContext *ctx) = 0;
  virtual void exitValue_part(SysMLv2Parser::Value_partContext *ctx) = 0;

  virtual void enterFeature_value(SysMLv2Parser::Feature_valueContext *ctx) = 0;
  virtual void exitFeature_value(SysMLv2Parser::Feature_valueContext *ctx) = 0;

  virtual void enterFeature_assignment(SysMLv2Parser::Feature_assignmentContext *ctx) = 0;
  virtual void exitFeature_assignment(SysMLv2Parser::Feature_assignmentContext *ctx) = 0;

  virtual void enterMultiplicity(SysMLv2Parser::MultiplicityContext *ctx) = 0;
  virtual void exitMultiplicity(SysMLv2Parser::MultiplicityContext *ctx) = 0;

  virtual void enterMultiplicity_subset(SysMLv2Parser::Multiplicity_subsetContext *ctx) = 0;
  virtual void exitMultiplicity_subset(SysMLv2Parser::Multiplicity_subsetContext *ctx) = 0;

  virtual void enterOwned_multiplicity_range(SysMLv2Parser::Owned_multiplicity_rangeContext *ctx) = 0;
  virtual void exitOwned_multiplicity_range(SysMLv2Parser::Owned_multiplicity_rangeContext *ctx) = 0;

  virtual void enterMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext *ctx) = 0;
  virtual void exitMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext *ctx) = 0;

  virtual void enterMultiplicity_expression_member(SysMLv2Parser::Multiplicity_expression_memberContext *ctx) = 0;
  virtual void exitMultiplicity_expression_member(SysMLv2Parser::Multiplicity_expression_memberContext *ctx) = 0;

  virtual void enterInternal_multiplicity_expression_member(SysMLv2Parser::Internal_multiplicity_expression_memberContext *ctx) = 0;
  virtual void exitInternal_multiplicity_expression_member(SysMLv2Parser::Internal_multiplicity_expression_memberContext *ctx) = 0;

  virtual void enterMetaclass(SysMLv2Parser::MetaclassContext *ctx) = 0;
  virtual void exitMetaclass(SysMLv2Parser::MetaclassContext *ctx) = 0;

  virtual void enterPrefix_metadata_feature(SysMLv2Parser::Prefix_metadata_featureContext *ctx) = 0;
  virtual void exitPrefix_metadata_feature(SysMLv2Parser::Prefix_metadata_featureContext *ctx) = 0;

  virtual void enterMetadata_feature(SysMLv2Parser::Metadata_featureContext *ctx) = 0;
  virtual void exitMetadata_feature(SysMLv2Parser::Metadata_featureContext *ctx) = 0;

  virtual void enterMetadata_feature_declaration(SysMLv2Parser::Metadata_feature_declarationContext *ctx) = 0;
  virtual void exitMetadata_feature_declaration(SysMLv2Parser::Metadata_feature_declarationContext *ctx) = 0;

  virtual void enterMetadata_body_element(SysMLv2Parser::Metadata_body_elementContext *ctx) = 0;
  virtual void exitMetadata_body_element(SysMLv2Parser::Metadata_body_elementContext *ctx) = 0;

  virtual void enterMetadata_body_feature_member(SysMLv2Parser::Metadata_body_feature_memberContext *ctx) = 0;
  virtual void exitMetadata_body_feature_member(SysMLv2Parser::Metadata_body_feature_memberContext *ctx) = 0;

  virtual void enterMetadata_body_feature(SysMLv2Parser::Metadata_body_featureContext *ctx) = 0;
  virtual void exitMetadata_body_feature(SysMLv2Parser::Metadata_body_featureContext *ctx) = 0;

  virtual void enterLibrary_package(SysMLv2Parser::Library_packageContext *ctx) = 0;
  virtual void exitLibrary_package(SysMLv2Parser::Library_packageContext *ctx) = 0;

  virtual void enterPackage_declaration(SysMLv2Parser::Package_declarationContext *ctx) = 0;
  virtual void exitPackage_declaration(SysMLv2Parser::Package_declarationContext *ctx) = 0;

  virtual void enterElement_filter_member(SysMLv2Parser::Element_filter_memberContext *ctx) = 0;
  virtual void exitElement_filter_member(SysMLv2Parser::Element_filter_memberContext *ctx) = 0;

  virtual void enterMeta_assignment(SysMLv2Parser::Meta_assignmentContext *ctx) = 0;
  virtual void exitMeta_assignment(SysMLv2Parser::Meta_assignmentContext *ctx) = 0;


};

