
    #include <sysmlv2/sysmlv2file_global.h>


    #include <sysmlv2/sysmlv2file_global.h>


// Generated from ./SysMLv2.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "../../../resources/grammars/SysMLv2Visitor.h"


    /**
 * This class provides an empty implementation of SysMLv2Visitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class SYSMLV2FILE_EXPORT SysMLv2BaseVisitor : public SysMLv2Visitor {
public:

  virtual std::any visitStart(SysMLv2Parser::StartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStart_element(SysMLv2Parser::Start_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStartRule(SysMLv2Parser::StartRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationship_body(SysMLv2Parser::Relationship_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDependency(SysMLv2Parser::DependencyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDependency_declaration(SysMLv2Parser::Dependency_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotation(SysMLv2Parser::AnnotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_annotation(SysMLv2Parser::Owned_annotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotating_member(SysMLv2Parser::Annotating_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotating_element(SysMLv2Parser::Annotating_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComment(SysMLv2Parser::CommentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDocumentation(SysMLv2Parser::DocumentationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTextual_representation(SysMLv2Parser::Textual_representationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRoot_namespace(SysMLv2Parser::Root_namespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackage(SysMLv2Parser::PackageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackage_body(SysMLv2Parser::Package_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackage_body_element(SysMLv2Parser::Package_body_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackage_member(SysMLv2Parser::Package_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAlias_member(SysMLv2Parser::Alias_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefinition_element(SysMLv2Parser::Definition_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsage_element(SysMLv2Parser::Usage_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasic_definition_prefix(SysMLv2Parser::Basic_definition_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefinition_extension_keyword(SysMLv2Parser::Definition_extension_keywordContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefinition_prefix(SysMLv2Parser::Definition_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefinition(SysMLv2Parser::DefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefinition_declaration(SysMLv2Parser::Definition_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefinition_body(SysMLv2Parser::Definition_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefinition_body_item(SysMLv2Parser::Definition_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefinition_member(SysMLv2Parser::Definition_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_occurrence_usage_member(SysMLv2Parser::Non_occurrence_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOccurrence_usage_member(SysMLv2Parser::Occurrence_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructure_usage_member(SysMLv2Parser::Structure_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBehavior_usage_member(SysMLv2Parser::Behavior_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_direction(SysMLv2Parser::Feature_directionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRef_prefix(SysMLv2Parser::Ref_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasic_usage_prefix(SysMLv2Parser::Basic_usage_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnd_usage_prefix(SysMLv2Parser::End_usage_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_cross_feature_member(SysMLv2Parser::Owned_cross_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_cross_feature(SysMLv2Parser::Owned_cross_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsage_extention_keyword(SysMLv2Parser::Usage_extention_keywordContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnextended_usage_prefix(SysMLv2Parser::Unextended_usage_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsage_prefix(SysMLv2Parser::Usage_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsage(SysMLv2Parser::UsageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsage_declaration(SysMLv2Parser::Usage_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsage_completion(SysMLv2Parser::Usage_completionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsage_body(SysMLv2Parser::Usage_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefault_reference_usage(SysMLv2Parser::Default_reference_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReference_usage(SysMLv2Parser::Reference_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariant_reference(SysMLv2Parser::Variant_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_occurrence_usage_element(SysMLv2Parser::Non_occurrence_usage_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOccurrence_usage_element(SysMLv2Parser::Occurrence_usage_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructure_usage_element(SysMLv2Parser::Structure_usage_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBehavior_usage_element(SysMLv2Parser::Behavior_usage_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariant_usage_element(SysMLv2Parser::Variant_usage_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubsclassification_part(SysMLv2Parser::Subsclassification_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCrosses(SysMLv2Parser::CrossesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_cross_subsetting(SysMLv2Parser::Owned_cross_subsettingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_part(SysMLv2Parser::Multiplicity_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_multiplicity(SysMLv2Parser::Owned_multiplicityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_range(SysMLv2Parser::Multiplicity_rangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute_definition(SysMLv2Parser::Attribute_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute_usage(SysMLv2Parser::Attribute_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumeration_definition(SysMLv2Parser::Enumeration_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumeration_body(SysMLv2Parser::Enumeration_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumeration_usage_member(SysMLv2Parser::Enumeration_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumerated_value(SysMLv2Parser::Enumerated_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumeration_usage(SysMLv2Parser::Enumeration_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOccurrence_definition_prefix(SysMLv2Parser::Occurrence_definition_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOccurrence_definition(SysMLv2Parser::Occurrence_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndividual_definition(SysMLv2Parser::Individual_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOccurrence_usage_prefix(SysMLv2Parser::Occurrence_usage_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOccurrence_usage(SysMLv2Parser::Occurrence_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndividual_usage(SysMLv2Parser::Individual_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPortion_usage(SysMLv2Parser::Portion_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPortion_kind(SysMLv2Parser::Portion_kindContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSource_succession_member(SysMLv2Parser::Source_succession_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSource_succession(SysMLv2Parser::Source_successionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSource_end_member(SysMLv2Parser::Source_end_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSource_end(SysMLv2Parser::Source_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_definition(SysMLv2Parser::Item_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_usage(SysMLv2Parser::Item_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPart_definition(SysMLv2Parser::Part_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPart_usage(SysMLv2Parser::Part_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPort_definition(SysMLv2Parser::Port_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPort_usage(SysMLv2Parser::Port_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConjungated_port_typing(SysMLv2Parser::Conjungated_port_typingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnection_definition(SysMLv2Parser::Connection_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnection_usage(SysMLv2Parser::Connection_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnector_part(SysMLv2Parser::Connector_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinary_connector_part(SysMLv2Parser::Binary_connector_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNary_connector_part(SysMLv2Parser::Nary_connector_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnector_end_member(SysMLv2Parser::Connector_end_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnecotr_end(SysMLv2Parser::Connecotr_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_cross_multiplicity_member(SysMLv2Parser::Owned_cross_multiplicity_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_cross_multiplicity(SysMLv2Parser::Owned_cross_multiplicityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinding_end_usage_member(SysMLv2Parser::Binding_end_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_definition(SysMLv2Parser::Interface_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_body(SysMLv2Parser::Interface_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_body_item(SysMLv2Parser::Interface_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_non_occurrence_usage_member(SysMLv2Parser::Interface_non_occurrence_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_non_occurrence_usage_element(SysMLv2Parser::Interface_non_occurrence_usage_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_occurrence_usage_member(SysMLv2Parser::Interface_occurrence_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_occurrence_usage_element(SysMLv2Parser::Interface_occurrence_usage_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefault_interface_end(SysMLv2Parser::Default_interface_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_usage(SysMLv2Parser::Interface_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_usage_declaration(SysMLv2Parser::Interface_usage_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_part(SysMLv2Parser::Interface_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinary_interface_part(SysMLv2Parser::Binary_interface_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNary_interface_part(SysMLv2Parser::Nary_interface_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_end_member(SysMLv2Parser::Interface_end_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterface_end(SysMLv2Parser::Interface_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAllocation_definition(SysMLv2Parser::Allocation_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAllocation_usage(SysMLv2Parser::Allocation_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAllocation_usage_declaration(SysMLv2Parser::Allocation_usage_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_definition(SysMLv2Parser::Flow_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMessage(SysMLv2Parser::MessageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMessage_declaration(SysMLv2Parser::Message_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMessage_event_member(SysMLv2Parser::Message_event_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMessage_event(SysMLv2Parser::Message_eventContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_usage(SysMLv2Parser::Flow_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuccession_flow_usage(SysMLv2Parser::Succession_flow_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_declaration(SysMLv2Parser::Flow_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_payload_feature_member(SysMLv2Parser::Flow_payload_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_payload_feature(SysMLv2Parser::Flow_payload_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPayload_feature(SysMLv2Parser::Payload_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPayload_feature_specialization_part(SysMLv2Parser::Payload_feature_specialization_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_end_member(SysMLv2Parser::Flow_end_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_end(SysMLv2Parser::Flow_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_end_subsetting(SysMLv2Parser::Flow_end_subsettingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_chain_prefix(SysMLv2Parser::Feature_chain_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_feature_member(SysMLv2Parser::Flow_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_feature(SysMLv2Parser::Flow_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlow_feature_redefinition(SysMLv2Parser::Flow_feature_redefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_definition(SysMLv2Parser::Action_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_body(SysMLv2Parser::Action_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_body_item(SysMLv2Parser::Action_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_behavior_body_item(SysMLv2Parser::Non_behavior_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_behavior_member(SysMLv2Parser::Action_behavior_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitial_node_member(SysMLv2Parser::Initial_node_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_node_member(SysMLv2Parser::Action_node_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_target_succession_member(SysMLv2Parser::Action_target_succession_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGuarded_succession_member(SysMLv2Parser::Guarded_succession_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_usage(SysMLv2Parser::Action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_usage_declaration(SysMLv2Parser::Action_usage_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPerform_action_usage(SysMLv2Parser::Perform_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_node(SysMLv2Parser::Action_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_node_usage_declaration(SysMLv2Parser::Action_node_usage_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_node_prefix(SysMLv2Parser::Action_node_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitControl_node(SysMLv2Parser::Control_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitControl_node_prefix(SysMLv2Parser::Control_node_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMerge_node(SysMLv2Parser::Merge_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecision_node(SysMLv2Parser::Decision_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJoin_node(SysMLv2Parser::Join_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFork_node(SysMLv2Parser::Fork_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAccept_node(SysMLv2Parser::Accept_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAccept_node_declaration(SysMLv2Parser::Accept_node_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAccept_parameter_part(SysMLv2Parser::Accept_parameter_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPayload_parameter_member(SysMLv2Parser::Payload_parameter_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPayload_parameter(SysMLv2Parser::Payload_parameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrigger_value_part(SysMLv2Parser::Trigger_value_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrigger_expression(SysMLv2Parser::Trigger_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSend_node(SysMLv2Parser::Send_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSend_node_declaration(SysMLv2Parser::Send_node_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSender_receiver_part(SysMLv2Parser::Sender_receiver_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNode_parameter_member(SysMLv2Parser::Node_parameter_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNode_parameter(SysMLv2Parser::Node_parameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_binding(SysMLv2Parser::Feature_bindingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment_node(SysMLv2Parser::Assignment_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment_node_declaration(SysMLv2Parser::Assignment_node_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment_target_member(SysMLv2Parser::Assignment_target_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment_target_parameter(SysMLv2Parser::Assignment_target_parameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment_target_binding(SysMLv2Parser::Assignment_target_bindingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_chain_member(SysMLv2Parser::Feature_chain_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_chain_member(SysMLv2Parser::Owned_feature_chain_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTerminate_node(SysMLv2Parser::Terminate_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_node(SysMLv2Parser::If_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression_parameter_member(SysMLv2Parser::Expression_parameter_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_body_parameter_member(SysMLv2Parser::Action_body_parameter_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_body_parameter(SysMLv2Parser::Action_body_parameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_node_parameter_member(SysMLv2Parser::If_node_parameter_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhile_loop_node(SysMLv2Parser::While_loop_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_loop_node(SysMLv2Parser::For_loop_nodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_variable_declaration_member(SysMLv2Parser::For_variable_declaration_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_variable_declaration(SysMLv2Parser::For_variable_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAction_target_succession(SysMLv2Parser::Action_target_successionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTarget_succession(SysMLv2Parser::Target_successionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGuarded_target_succession(SysMLv2Parser::Guarded_target_successionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefault_target_succession(SysMLv2Parser::Default_target_successionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGuarded_succession(SysMLv2Parser::Guarded_successionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_definition(SysMLv2Parser::State_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_def_body(SysMLv2Parser::State_def_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_body_item(SysMLv2Parser::State_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEntry_action_member(SysMLv2Parser::Entry_action_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDo_action_member(SysMLv2Parser::Do_action_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExit_action_member(SysMLv2Parser::Exit_action_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEntry_transition_member(SysMLv2Parser::Entry_transition_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_action_usage(SysMLv2Parser::State_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmpty_action_usage(SysMLv2Parser::Empty_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_perform_action_uage(SysMLv2Parser::State_perform_action_uageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_accept_action_usage(SysMLv2Parser::State_accept_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_send_action_usage(SysMLv2Parser::State_send_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_assignment_action_usage(SysMLv2Parser::State_assignment_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransition_usage_member(SysMLv2Parser::Transition_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTarget_transition_usage_member(SysMLv2Parser::Target_transition_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_usage(SysMLv2Parser::State_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitState_usage_body(SysMLv2Parser::State_usage_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExhibit_state_usage(SysMLv2Parser::Exhibit_state_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransition_usage(SysMLv2Parser::Transition_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTarget_transition_usage(SysMLv2Parser::Target_transition_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrigger_action_member(SysMLv2Parser::Trigger_action_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrigger_action(SysMLv2Parser::Trigger_actionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGuard_expression_member(SysMLv2Parser::Guard_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEffect_behavior_member(SysMLv2Parser::Effect_behavior_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEffect_behavior_usage(SysMLv2Parser::Effect_behavior_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransition_perform_action_usage(SysMLv2Parser::Transition_perform_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransition_accept_action_usage(SysMLv2Parser::Transition_accept_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransition_send_action_usage(SysMLv2Parser::Transition_send_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransition_assignment_action_usage(SysMLv2Parser::Transition_assignment_action_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransition_succession_member(SysMLv2Parser::Transition_succession_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransition_succession(SysMLv2Parser::Transition_successionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCalculation_definition(SysMLv2Parser::Calculation_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCalculation_usage(SysMLv2Parser::Calculation_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCalculation_body(SysMLv2Parser::Calculation_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCalculation_body_part(SysMLv2Parser::Calculation_body_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCalculation_body_item(SysMLv2Parser::Calculation_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturn_parameter_member(SysMLv2Parser::Return_parameter_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitResult_expression_member(SysMLv2Parser::Result_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstraint_definition(SysMLv2Parser::Constraint_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstraint_usage(SysMLv2Parser::Constraint_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssert_constriant_usage(SysMLv2Parser::Assert_constriant_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstraint_usage_declaration(SysMLv2Parser::Constraint_usage_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequirement_definition(SysMLv2Parser::Requirement_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequirement_body(SysMLv2Parser::Requirement_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequirement_body_item(SysMLv2Parser::Requirement_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubject_member(SysMLv2Parser::Subject_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubject_usage(SysMLv2Parser::Subject_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequirement_constraint_member(SysMLv2Parser::Requirement_constraint_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequriement_kind(SysMLv2Parser::Requriement_kindContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequirement_constraint_usage(SysMLv2Parser::Requirement_constraint_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFramed_concern_member(SysMLv2Parser::Framed_concern_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFramed_concern_usage(SysMLv2Parser::Framed_concern_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitActor_member(SysMLv2Parser::Actor_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitActor_usage(SysMLv2Parser::Actor_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStakeholder_member(SysMLv2Parser::Stakeholder_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStakeholder_usage(SysMLv2Parser::Stakeholder_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequirement_usage(SysMLv2Parser::Requirement_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSatisfy_requirement_usage(SysMLv2Parser::Satisfy_requirement_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSatisfaction_subject_member(SysMLv2Parser::Satisfaction_subject_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSatisfaction_parameter(SysMLv2Parser::Satisfaction_parameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSatisfaction_feature_value(SysMLv2Parser::Satisfaction_feature_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSatisfaction_reference_expression(SysMLv2Parser::Satisfaction_reference_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConcern_definition(SysMLv2Parser::Concern_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConcern_usage(SysMLv2Parser::Concern_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCase_definition(SysMLv2Parser::Case_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCase_usage(SysMLv2Parser::Case_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCase_body(SysMLv2Parser::Case_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCase_body_item(SysMLv2Parser::Case_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjective_member(SysMLv2Parser::Objective_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjective_requirement_usage(SysMLv2Parser::Objective_requirement_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnalysis_case_definition(SysMLv2Parser::Analysis_case_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnalysis_case_usage(SysMLv2Parser::Analysis_case_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVerification_case_definition(SysMLv2Parser::Verification_case_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVerification_case_usage(SysMLv2Parser::Verification_case_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequirement_verification_member(SysMLv2Parser::Requirement_verification_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRequirement_verification_usage(SysMLv2Parser::Requirement_verification_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUse_case_definition(SysMLv2Parser::Use_case_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUse_case_usage(SysMLv2Parser::Use_case_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInclude_use_case_usage(SysMLv2Parser::Include_use_case_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_definition(SysMLv2Parser::View_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_definition_body(SysMLv2Parser::View_definition_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_definition_body_item(SysMLv2Parser::View_definition_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_rendering_member(SysMLv2Parser::View_rendering_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_rendering_usage(SysMLv2Parser::View_rendering_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_usage(SysMLv2Parser::View_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_body(SysMLv2Parser::View_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_body_item(SysMLv2Parser::View_body_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpose(SysMLv2Parser::ExposeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMembership_expose(SysMLv2Parser::Membership_exposeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_expose(SysMLv2Parser::Namespace_exposeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitViewpoint_definition(SysMLv2Parser::Viewpoint_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitViewpoint_usage(SysMLv2Parser::Viewpoint_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRendering_definition(SysMLv2Parser::Rendering_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRendering_usage(SysMLv2Parser::Rendering_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_definition(SysMLv2Parser::Metadata_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefix_metadata_annotation(SysMLv2Parser::Prefix_metadata_annotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefix_metadata_member(SysMLv2Parser::Prefix_metadata_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefix_metadata_usage(SysMLv2Parser::Prefix_metadata_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_usage(SysMLv2Parser::Metadata_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_usage_declaration(SysMLv2Parser::Metadata_usage_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body(SysMLv2Parser::Metadata_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body_usage_member(SysMLv2Parser::Metadata_body_usage_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body_usage(SysMLv2Parser::Metadata_body_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExtended_definition(SysMLv2Parser::Extended_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExtended_usage(SysMLv2Parser::Extended_usageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefined_by(SysMLv2Parser::Defined_byContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElements(SysMLv2Parser::ElementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentification(SysMLv2Parser::IdentificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationship_owned_elements(SysMLv2Parser::Relationship_owned_elementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationship_owned_element(SysMLv2Parser::Relationship_owned_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_related_element(SysMLv2Parser::Owned_related_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace(SysMLv2Parser::NamespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_declaration(SysMLv2Parser::Namespace_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_body(SysMLv2Parser::Namespace_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_body_elements(SysMLv2Parser::Namespace_body_elementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_body_element(SysMLv2Parser::Namespace_body_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMember_prefix(SysMLv2Parser::Member_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVisibility_indicator(SysMLv2Parser::Visibility_indicatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_member(SysMLv2Parser::Namespace_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_member(SysMLv2Parser::Non_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_feature_member(SysMLv2Parser::Namespace_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualified_name(SysMLv2Parser::Qualified_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_import(SysMLv2Parser::Namespace_importContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImport_declaration(SysMLv2Parser::Import_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMembership_import(SysMLv2Parser::Membership_importContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilter_package(SysMLv2Parser::Filter_packageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilter_package_member(SysMLv2Parser::Filter_package_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement(SysMLv2Parser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_element(SysMLv2Parser::Non_feature_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_element(SysMLv2Parser::Feature_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditional_options(SysMLv2Parser::Additional_optionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(SysMLv2Parser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_prefix(SysMLv2Parser::Type_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_declaration(SysMLv2Parser::Type_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecialization_part(SysMLv2Parser::Specialization_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConjugation_part(SysMLv2Parser::Conjugation_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_relationship_part(SysMLv2Parser::Type_relationship_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDisjoining_part(SysMLv2Parser::Disjoining_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnioning_part(SysMLv2Parser::Unioning_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntersecting_part(SysMLv2Parser::Intersecting_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDifferencing_part(SysMLv2Parser::Differencing_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_body(SysMLv2Parser::Type_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_body_elements(SysMLv2Parser::Type_body_elementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_body_element(SysMLv2Parser::Type_body_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecialization(SysMLv2Parser::SpecializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_specialization(SysMLv2Parser::Owned_specializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecific_type(SysMLv2Parser::Specific_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGeneral_type(SysMLv2Parser::General_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConjunction(SysMLv2Parser::ConjunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_conjugation(SysMLv2Parser::Owned_conjugationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDisjoining(SysMLv2Parser::DisjoiningContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_disjoining(SysMLv2Parser::Owned_disjoiningContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnioning(SysMLv2Parser::UnioningContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntersecting(SysMLv2Parser::IntersectingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDifferencing(SysMLv2Parser::DifferencingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_member(SysMLv2Parser::Feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_feature_member(SysMLv2Parser::Type_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_member(SysMLv2Parser::Owned_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassifier(SysMLv2Parser::ClassifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassifier_declaration(SysMLv2Parser::Classifier_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuperclassing_part(SysMLv2Parser::Superclassing_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubclassification(SysMLv2Parser::SubclassificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_subclassification(SysMLv2Parser::Owned_subclassificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature(SysMLv2Parser::FeatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_prefix(SysMLv2Parser::Feature_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_declaration(SysMLv2Parser::Feature_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_identification(SysMLv2Parser::Feature_identificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_relationship_part(SysMLv2Parser::Feature_relationship_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChaining_part(SysMLv2Parser::Chaining_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInverting_part(SysMLv2Parser::Inverting_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_featuring_part(SysMLv2Parser::Type_featuring_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_specialization_part(SysMLv2Parser::Feature_specialization_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_specialization(SysMLv2Parser::Feature_specializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypings(SysMLv2Parser::TypingsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTyped_by(SysMLv2Parser::Typed_byContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubsettings(SysMLv2Parser::SubsettingsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubsets(SysMLv2Parser::SubsetsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReferences(SysMLv2Parser::ReferencesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRedefinitions(SysMLv2Parser::RedefinitionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRedefines(SysMLv2Parser::RedefinesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_typing(SysMLv2Parser::Feature_typingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_typing(SysMLv2Parser::Owned_feature_typingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubsetting(SysMLv2Parser::SubsettingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_subsetting(SysMLv2Parser::Owned_subsettingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_reference_subsetting(SysMLv2Parser::Owned_reference_subsettingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRedefinition(SysMLv2Parser::RedefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_redefinition(SysMLv2Parser::Owned_redefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_chain(SysMLv2Parser::Owned_feature_chainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_chain(SysMLv2Parser::Feature_chainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_chaining(SysMLv2Parser::Owned_feature_chainingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_inverting(SysMLv2Parser::Feature_invertingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_inverting(SysMLv2Parser::Owned_feature_invertingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_featuring(SysMLv2Parser::Type_featuringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_type_featuring(SysMLv2Parser::Owned_type_featuringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitData_type(SysMLv2Parser::Data_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClass(SysMLv2Parser::ClassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructure(SysMLv2Parser::StructureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssociation(SysMLv2Parser::AssociationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssociation_structure(SysMLv2Parser::Association_structureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnector(SysMLv2Parser::ConnectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnector_declaration(SysMLv2Parser::Connector_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinary_connector_declaration(SysMLv2Parser::Binary_connector_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNary_connector_declaration(SysMLv2Parser::Nary_connector_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnector_end(SysMLv2Parser::Connector_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinding_connector(SysMLv2Parser::Binding_connectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinding_connector_declaration(SysMLv2Parser::Binding_connector_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuccession(SysMLv2Parser::SuccessionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuccession_declaration(SysMLv2Parser::Succession_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBehavior(SysMLv2Parser::BehaviorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStep(SysMLv2Parser::StepContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction(SysMLv2Parser::FunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_body(SysMLv2Parser::Function_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_body_part(SysMLv2Parser::Function_body_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturn_feature_member(SysMLv2Parser::Return_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(SysMLv2Parser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPredicate(SysMLv2Parser::PredicateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolean_expression(SysMLv2Parser::Boolean_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvariant(SysMLv2Parser::InvariantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expression_reference_member(SysMLv2Parser::Owned_expression_reference_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expression_reference(SysMLv2Parser::Owned_expression_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expression_member(SysMLv2Parser::Owned_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expressions(SysMLv2Parser::Owned_expressionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expression(SysMLv2Parser::Owned_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEased_owned_expression(SysMLv2Parser::Eased_owned_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditional_expression(SysMLv2Parser::Conditional_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditional_binary_operator_expression(SysMLv2Parser::Conditional_binary_operator_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditional_binary_operator(SysMLv2Parser::Conditional_binary_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinary_operator_expression(SysMLv2Parser::Binary_operator_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinary_operator(SysMLv2Parser::Binary_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_operator_expression(SysMLv2Parser::Unary_operator_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_operator(SysMLv2Parser::Unary_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassification_expression(SysMLv2Parser::Classification_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassification(SysMLv2Parser::ClassificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassification_test_operator(SysMLv2Parser::Classification_test_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCast_operator(SysMLv2Parser::Cast_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetaclassification_expression(SysMLv2Parser::Metaclassification_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_member(SysMLv2Parser::Argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(SysMLv2Parser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_value(SysMLv2Parser::Argument_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_expression_member(SysMLv2Parser::Argument_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_expression(SysMLv2Parser::Argument_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_expression_value(SysMLv2Parser::Argument_expression_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_argument_member(SysMLv2Parser::Metadata_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_argument(SysMLv2Parser::Metadata_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_value(SysMLv2Parser::Metadata_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_reference(SysMLv2Parser::Metadata_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadataclassification_test_operator(SysMLv2Parser::Metadataclassification_test_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMeta_cast_operator(SysMLv2Parser::Meta_cast_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExtend_expression(SysMLv2Parser::Extend_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_reference_member(SysMLv2Parser::Type_reference_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_result_member(SysMLv2Parser::Type_result_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_reference(SysMLv2Parser::Type_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReference_typing(SysMLv2Parser::Reference_typingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_expressions(SysMLv2Parser::Primary_expressionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_expression(SysMLv2Parser::Primary_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_argument_value(SysMLv2Parser::Primary_argument_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_argument(SysMLv2Parser::Primary_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_argument_member(SysMLv2Parser::Primary_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_chain_primary_expression(SysMLv2Parser::Non_feature_chain_primary_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_chain_primary_argument_value(SysMLv2Parser::Non_feature_chain_primary_argument_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_chain_primary_argument(SysMLv2Parser::Non_feature_chain_primary_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_chain_primary_argument_member(SysMLv2Parser::Non_feature_chain_primary_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBracket_expression(SysMLv2Parser::Bracket_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndex_expression(SysMLv2Parser::Index_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSequence_expression(SysMLv2Parser::Sequence_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSequence_expression_list(SysMLv2Parser::Sequence_expression_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSequence_operator_expression(SysMLv2Parser::Sequence_operator_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSequence_expression_list_member(SysMLv2Parser::Sequence_expression_list_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_chain_expression(SysMLv2Parser::Feature_chain_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollect_expression(SysMLv2Parser::Collect_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelect_expression(SysMLv2Parser::Select_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_operation_expression(SysMLv2Parser::Function_operation_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_argument_member(SysMLv2Parser::Body_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_argument(SysMLv2Parser::Body_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_argument_value(SysMLv2Parser::Body_argument_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_expression_member(SysMLv2Parser::Body_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_argument_member(SysMLv2Parser::Function_reference_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_argument(SysMLv2Parser::Function_reference_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_arugment_value(SysMLv2Parser::Function_reference_arugment_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_expression(SysMLv2Parser::Function_reference_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_member(SysMLv2Parser::Function_reference_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference(SysMLv2Parser::Function_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBase_expression(SysMLv2Parser::Base_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNull_expression(SysMLv2Parser::Null_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_reference_expression(SysMLv2Parser::Feature_reference_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_reference_member(SysMLv2Parser::Feature_reference_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_reference(SysMLv2Parser::Feature_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_access_expression(SysMLv2Parser::Metadata_access_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvocation_expression(SysMLv2Parser::Invocation_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInternal_invocation_expression(SysMLv2Parser::Internal_invocation_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_list(SysMLv2Parser::Argument_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPositional_argument_list(SysMLv2Parser::Positional_argument_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_argument_list(SysMLv2Parser::Named_argument_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_argument_member(SysMLv2Parser::Named_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_argument(SysMLv2Parser::Named_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter_redefinition(SysMLv2Parser::Parameter_redefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_expression(SysMLv2Parser::Body_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression_body_member(SysMLv2Parser::Expression_body_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression_body(SysMLv2Parser::Expression_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_expression(SysMLv2Parser::Literal_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_boolean(SysMLv2Parser::Literal_booleanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolean_value(SysMLv2Parser::Boolean_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_string(SysMLv2Parser::Literal_stringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_integer(SysMLv2Parser::Literal_integerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_real(SysMLv2Parser::Literal_realContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReal_value(SysMLv2Parser::Real_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_infinity(SysMLv2Parser::Literal_infinityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInteraction(SysMLv2Parser::InteractionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow(SysMLv2Parser::Item_flowContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_declaration(SysMLv2Parser::Item_flow_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_feature_member(SysMLv2Parser::Item_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_feature(SysMLv2Parser::Item_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_feature_specialization_part(SysMLv2Parser::Item_feature_specialization_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_end_member(SysMLv2Parser::Item_flow_end_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_end(SysMLv2Parser::Item_flow_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_feature_member(SysMLv2Parser::Item_flow_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_feature(SysMLv2Parser::Item_flow_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_redefinition(SysMLv2Parser::Item_flow_redefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue_part(SysMLv2Parser::Value_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_value(SysMLv2Parser::Feature_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_assignment(SysMLv2Parser::Feature_assignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity(SysMLv2Parser::MultiplicityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_subset(SysMLv2Parser::Multiplicity_subsetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_multiplicity_range(SysMLv2Parser::Owned_multiplicity_rangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_expression_member(SysMLv2Parser::Multiplicity_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInternal_multiplicity_expression_member(SysMLv2Parser::Internal_multiplicity_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetaclass(SysMLv2Parser::MetaclassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefix_metadata_feature(SysMLv2Parser::Prefix_metadata_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_feature(SysMLv2Parser::Metadata_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_feature_declaration(SysMLv2Parser::Metadata_feature_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body_element(SysMLv2Parser::Metadata_body_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body_feature_member(SysMLv2Parser::Metadata_body_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body_feature(SysMLv2Parser::Metadata_body_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLibrary_package(SysMLv2Parser::Library_packageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackage_declaration(SysMLv2Parser::Package_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement_filter_member(SysMLv2Parser::Element_filter_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMeta_assignment(SysMLv2Parser::Meta_assignmentContext *ctx) override {
    return visitChildren(ctx);
  }


};

