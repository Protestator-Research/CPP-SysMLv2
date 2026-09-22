
    #include <sysmlv2/sysmlv2file_global.h>


    #include <sysmlv2/sysmlv2file_global.h>


// Generated from ./SysMLv2.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include <sysmlv2/parser/SysMLv2Parser.h>



    /**
 * This class defines an abstract visitor for a parse tree
 * produced by SysMLv2Parser.
 */
class SYSMLV2FILE_EXPORT SysMLv2Visitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SysMLv2Parser.
   */
    virtual std::any visitStart(SysMLv2Parser::StartContext *context) = 0;

    virtual std::any visitStart_element(SysMLv2Parser::Start_elementContext *context) = 0;

    virtual std::any visitStartRule(SysMLv2Parser::StartRuleContext *context) = 0;

    virtual std::any visitRelationship_body(SysMLv2Parser::Relationship_bodyContext *context) = 0;

    virtual std::any visitDependency(SysMLv2Parser::DependencyContext *context) = 0;

    virtual std::any visitDependency_declaration(SysMLv2Parser::Dependency_declarationContext *context) = 0;

    virtual std::any visitAnnotation(SysMLv2Parser::AnnotationContext *context) = 0;

    virtual std::any visitOwned_annotation(SysMLv2Parser::Owned_annotationContext *context) = 0;

    virtual std::any visitAnnotating_member(SysMLv2Parser::Annotating_memberContext *context) = 0;

    virtual std::any visitAnnotating_element(SysMLv2Parser::Annotating_elementContext *context) = 0;

    virtual std::any visitComment(SysMLv2Parser::CommentContext *context) = 0;

    virtual std::any visitDocumentation(SysMLv2Parser::DocumentationContext *context) = 0;

    virtual std::any visitTextual_representation(SysMLv2Parser::Textual_representationContext *context) = 0;

    virtual std::any visitRoot_namespace(SysMLv2Parser::Root_namespaceContext *context) = 0;

    virtual std::any visitPackage(SysMLv2Parser::PackageContext *context) = 0;

    virtual std::any visitPackage_body(SysMLv2Parser::Package_bodyContext *context) = 0;

    virtual std::any visitPackage_body_element(SysMLv2Parser::Package_body_elementContext *context) = 0;

    virtual std::any visitPackage_member(SysMLv2Parser::Package_memberContext *context) = 0;

    virtual std::any visitAlias_member(SysMLv2Parser::Alias_memberContext *context) = 0;

    virtual std::any visitDefinition_element(SysMLv2Parser::Definition_elementContext *context) = 0;

    virtual std::any visitUsage_element(SysMLv2Parser::Usage_elementContext *context) = 0;

    virtual std::any visitBasic_definition_prefix(SysMLv2Parser::Basic_definition_prefixContext *context) = 0;

    virtual std::any visitDefinition_extension_keyword(SysMLv2Parser::Definition_extension_keywordContext *context) = 0;

    virtual std::any visitDefinition_prefix(SysMLv2Parser::Definition_prefixContext *context) = 0;

    virtual std::any visitDefinition(SysMLv2Parser::DefinitionContext *context) = 0;

    virtual std::any visitDefinition_declaration(SysMLv2Parser::Definition_declarationContext *context) = 0;

    virtual std::any visitDefinition_body(SysMLv2Parser::Definition_bodyContext *context) = 0;

    virtual std::any visitDefinition_body_item(SysMLv2Parser::Definition_body_itemContext *context) = 0;

    virtual std::any visitDefinition_member(SysMLv2Parser::Definition_memberContext *context) = 0;

    virtual std::any visitVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext *context) = 0;

    virtual std::any visitNon_occurrence_usage_member(SysMLv2Parser::Non_occurrence_usage_memberContext *context) = 0;

    virtual std::any visitOccurrence_usage_member(SysMLv2Parser::Occurrence_usage_memberContext *context) = 0;

    virtual std::any visitStructure_usage_member(SysMLv2Parser::Structure_usage_memberContext *context) = 0;

    virtual std::any visitBehavior_usage_member(SysMLv2Parser::Behavior_usage_memberContext *context) = 0;

    virtual std::any visitFeature_direction(SysMLv2Parser::Feature_directionContext *context) = 0;

    virtual std::any visitRef_prefix(SysMLv2Parser::Ref_prefixContext *context) = 0;

    virtual std::any visitBasic_usage_prefix(SysMLv2Parser::Basic_usage_prefixContext *context) = 0;

    virtual std::any visitEnd_usage_prefix(SysMLv2Parser::End_usage_prefixContext *context) = 0;

    virtual std::any visitOwned_cross_feature_member(SysMLv2Parser::Owned_cross_feature_memberContext *context) = 0;

    virtual std::any visitOwned_cross_feature(SysMLv2Parser::Owned_cross_featureContext *context) = 0;

    virtual std::any visitUsage_extention_keyword(SysMLv2Parser::Usage_extention_keywordContext *context) = 0;

    virtual std::any visitUnextended_usage_prefix(SysMLv2Parser::Unextended_usage_prefixContext *context) = 0;

    virtual std::any visitUsage_prefix(SysMLv2Parser::Usage_prefixContext *context) = 0;

    virtual std::any visitUsage(SysMLv2Parser::UsageContext *context) = 0;

    virtual std::any visitUsage_declaration(SysMLv2Parser::Usage_declarationContext *context) = 0;

    virtual std::any visitUsage_completion(SysMLv2Parser::Usage_completionContext *context) = 0;

    virtual std::any visitUsage_body(SysMLv2Parser::Usage_bodyContext *context) = 0;

    virtual std::any visitDefault_reference_usage(SysMLv2Parser::Default_reference_usageContext *context) = 0;

    virtual std::any visitReference_usage(SysMLv2Parser::Reference_usageContext *context) = 0;

    virtual std::any visitVariant_reference(SysMLv2Parser::Variant_referenceContext *context) = 0;

    virtual std::any visitNon_occurrence_usage_element(SysMLv2Parser::Non_occurrence_usage_elementContext *context) = 0;

    virtual std::any visitOccurrence_usage_element(SysMLv2Parser::Occurrence_usage_elementContext *context) = 0;

    virtual std::any visitStructure_usage_element(SysMLv2Parser::Structure_usage_elementContext *context) = 0;

    virtual std::any visitBehavior_usage_element(SysMLv2Parser::Behavior_usage_elementContext *context) = 0;

    virtual std::any visitVariant_usage_element(SysMLv2Parser::Variant_usage_elementContext *context) = 0;

    virtual std::any visitSubsclassification_part(SysMLv2Parser::Subsclassification_partContext *context) = 0;

    virtual std::any visitCrosses(SysMLv2Parser::CrossesContext *context) = 0;

    virtual std::any visitOwned_cross_subsetting(SysMLv2Parser::Owned_cross_subsettingContext *context) = 0;

    virtual std::any visitMultiplicity_part(SysMLv2Parser::Multiplicity_partContext *context) = 0;

    virtual std::any visitOwned_multiplicity(SysMLv2Parser::Owned_multiplicityContext *context) = 0;

    virtual std::any visitMultiplicity_range(SysMLv2Parser::Multiplicity_rangeContext *context) = 0;

    virtual std::any visitAttribute_definition(SysMLv2Parser::Attribute_definitionContext *context) = 0;

    virtual std::any visitAttribute_usage(SysMLv2Parser::Attribute_usageContext *context) = 0;

    virtual std::any visitEnumeration_definition(SysMLv2Parser::Enumeration_definitionContext *context) = 0;

    virtual std::any visitEnumeration_body(SysMLv2Parser::Enumeration_bodyContext *context) = 0;

    virtual std::any visitEnumeration_usage_member(SysMLv2Parser::Enumeration_usage_memberContext *context) = 0;

    virtual std::any visitEnumerated_value(SysMLv2Parser::Enumerated_valueContext *context) = 0;

    virtual std::any visitEnumeration_usage(SysMLv2Parser::Enumeration_usageContext *context) = 0;

    virtual std::any visitOccurrence_definition_prefix(SysMLv2Parser::Occurrence_definition_prefixContext *context) = 0;

    virtual std::any visitOccurrence_definition(SysMLv2Parser::Occurrence_definitionContext *context) = 0;

    virtual std::any visitIndividual_definition(SysMLv2Parser::Individual_definitionContext *context) = 0;

    virtual std::any visitOccurrence_usage_prefix(SysMLv2Parser::Occurrence_usage_prefixContext *context) = 0;

    virtual std::any visitOccurrence_usage(SysMLv2Parser::Occurrence_usageContext *context) = 0;

    virtual std::any visitIndividual_usage(SysMLv2Parser::Individual_usageContext *context) = 0;

    virtual std::any visitPortion_usage(SysMLv2Parser::Portion_usageContext *context) = 0;

    virtual std::any visitPortion_kind(SysMLv2Parser::Portion_kindContext *context) = 0;

    virtual std::any visitEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext *context) = 0;

    virtual std::any visitSource_succession_member(SysMLv2Parser::Source_succession_memberContext *context) = 0;

    virtual std::any visitSource_succession(SysMLv2Parser::Source_successionContext *context) = 0;

    virtual std::any visitSource_end_member(SysMLv2Parser::Source_end_memberContext *context) = 0;

    virtual std::any visitSource_end(SysMLv2Parser::Source_endContext *context) = 0;

    virtual std::any visitItem_definition(SysMLv2Parser::Item_definitionContext *context) = 0;

    virtual std::any visitItem_usage(SysMLv2Parser::Item_usageContext *context) = 0;

    virtual std::any visitPart_definition(SysMLv2Parser::Part_definitionContext *context) = 0;

    virtual std::any visitPart_usage(SysMLv2Parser::Part_usageContext *context) = 0;

    virtual std::any visitPort_definition(SysMLv2Parser::Port_definitionContext *context) = 0;

    virtual std::any visitPort_usage(SysMLv2Parser::Port_usageContext *context) = 0;

    virtual std::any visitConjungated_port_typing(SysMLv2Parser::Conjungated_port_typingContext *context) = 0;

    virtual std::any visitConnection_definition(SysMLv2Parser::Connection_definitionContext *context) = 0;

    virtual std::any visitConnection_usage(SysMLv2Parser::Connection_usageContext *context) = 0;

    virtual std::any visitConnector_part(SysMLv2Parser::Connector_partContext *context) = 0;

    virtual std::any visitBinary_connector_part(SysMLv2Parser::Binary_connector_partContext *context) = 0;

    virtual std::any visitNary_connector_part(SysMLv2Parser::Nary_connector_partContext *context) = 0;

    virtual std::any visitConnector_end_member(SysMLv2Parser::Connector_end_memberContext *context) = 0;

    virtual std::any visitConnecotr_end(SysMLv2Parser::Connecotr_endContext *context) = 0;

    virtual std::any visitOwned_cross_multiplicity_member(SysMLv2Parser::Owned_cross_multiplicity_memberContext *context) = 0;

    virtual std::any visitOwned_cross_multiplicity(SysMLv2Parser::Owned_cross_multiplicityContext *context) = 0;

    virtual std::any visitBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext *context) = 0;

    virtual std::any visitBinding_end_usage_member(SysMLv2Parser::Binding_end_usage_memberContext *context) = 0;

    virtual std::any visitSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext *context) = 0;

    virtual std::any visitInterface_definition(SysMLv2Parser::Interface_definitionContext *context) = 0;

    virtual std::any visitInterface_body(SysMLv2Parser::Interface_bodyContext *context) = 0;

    virtual std::any visitInterface_body_item(SysMLv2Parser::Interface_body_itemContext *context) = 0;

    virtual std::any visitInterface_non_occurrence_usage_member(SysMLv2Parser::Interface_non_occurrence_usage_memberContext *context) = 0;

    virtual std::any visitInterface_non_occurrence_usage_element(SysMLv2Parser::Interface_non_occurrence_usage_elementContext *context) = 0;

    virtual std::any visitInterface_occurrence_usage_member(SysMLv2Parser::Interface_occurrence_usage_memberContext *context) = 0;

    virtual std::any visitInterface_occurrence_usage_element(SysMLv2Parser::Interface_occurrence_usage_elementContext *context) = 0;

    virtual std::any visitDefault_interface_end(SysMLv2Parser::Default_interface_endContext *context) = 0;

    virtual std::any visitInterface_usage(SysMLv2Parser::Interface_usageContext *context) = 0;

    virtual std::any visitInterface_usage_declaration(SysMLv2Parser::Interface_usage_declarationContext *context) = 0;

    virtual std::any visitInterface_part(SysMLv2Parser::Interface_partContext *context) = 0;

    virtual std::any visitBinary_interface_part(SysMLv2Parser::Binary_interface_partContext *context) = 0;

    virtual std::any visitNary_interface_part(SysMLv2Parser::Nary_interface_partContext *context) = 0;

    virtual std::any visitInterface_end_member(SysMLv2Parser::Interface_end_memberContext *context) = 0;

    virtual std::any visitInterface_end(SysMLv2Parser::Interface_endContext *context) = 0;

    virtual std::any visitAllocation_definition(SysMLv2Parser::Allocation_definitionContext *context) = 0;

    virtual std::any visitAllocation_usage(SysMLv2Parser::Allocation_usageContext *context) = 0;

    virtual std::any visitAllocation_usage_declaration(SysMLv2Parser::Allocation_usage_declarationContext *context) = 0;

    virtual std::any visitFlow_definition(SysMLv2Parser::Flow_definitionContext *context) = 0;

    virtual std::any visitMessage(SysMLv2Parser::MessageContext *context) = 0;

    virtual std::any visitMessage_declaration(SysMLv2Parser::Message_declarationContext *context) = 0;

    virtual std::any visitMessage_event_member(SysMLv2Parser::Message_event_memberContext *context) = 0;

    virtual std::any visitMessage_event(SysMLv2Parser::Message_eventContext *context) = 0;

    virtual std::any visitFlow_usage(SysMLv2Parser::Flow_usageContext *context) = 0;

    virtual std::any visitSuccession_flow_usage(SysMLv2Parser::Succession_flow_usageContext *context) = 0;

    virtual std::any visitFlow_declaration(SysMLv2Parser::Flow_declarationContext *context) = 0;

    virtual std::any visitFlow_payload_feature_member(SysMLv2Parser::Flow_payload_feature_memberContext *context) = 0;

    virtual std::any visitFlow_payload_feature(SysMLv2Parser::Flow_payload_featureContext *context) = 0;

    virtual std::any visitPayload_feature(SysMLv2Parser::Payload_featureContext *context) = 0;

    virtual std::any visitPayload_feature_specialization_part(SysMLv2Parser::Payload_feature_specialization_partContext *context) = 0;

    virtual std::any visitFlow_end_member(SysMLv2Parser::Flow_end_memberContext *context) = 0;

    virtual std::any visitFlow_end(SysMLv2Parser::Flow_endContext *context) = 0;

    virtual std::any visitFlow_end_subsetting(SysMLv2Parser::Flow_end_subsettingContext *context) = 0;

    virtual std::any visitFeature_chain_prefix(SysMLv2Parser::Feature_chain_prefixContext *context) = 0;

    virtual std::any visitFlow_feature_member(SysMLv2Parser::Flow_feature_memberContext *context) = 0;

    virtual std::any visitFlow_feature(SysMLv2Parser::Flow_featureContext *context) = 0;

    virtual std::any visitFlow_feature_redefinition(SysMLv2Parser::Flow_feature_redefinitionContext *context) = 0;

    virtual std::any visitAction_definition(SysMLv2Parser::Action_definitionContext *context) = 0;

    virtual std::any visitAction_body(SysMLv2Parser::Action_bodyContext *context) = 0;

    virtual std::any visitAction_body_item(SysMLv2Parser::Action_body_itemContext *context) = 0;

    virtual std::any visitNon_behavior_body_item(SysMLv2Parser::Non_behavior_body_itemContext *context) = 0;

    virtual std::any visitAction_behavior_member(SysMLv2Parser::Action_behavior_memberContext *context) = 0;

    virtual std::any visitInitial_node_member(SysMLv2Parser::Initial_node_memberContext *context) = 0;

    virtual std::any visitAction_node_member(SysMLv2Parser::Action_node_memberContext *context) = 0;

    virtual std::any visitAction_target_succession_member(SysMLv2Parser::Action_target_succession_memberContext *context) = 0;

    virtual std::any visitGuarded_succession_member(SysMLv2Parser::Guarded_succession_memberContext *context) = 0;

    virtual std::any visitAction_usage(SysMLv2Parser::Action_usageContext *context) = 0;

    virtual std::any visitAction_usage_declaration(SysMLv2Parser::Action_usage_declarationContext *context) = 0;

    virtual std::any visitPerform_action_usage(SysMLv2Parser::Perform_action_usageContext *context) = 0;

    virtual std::any visitPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext *context) = 0;

    virtual std::any visitAction_node(SysMLv2Parser::Action_nodeContext *context) = 0;

    virtual std::any visitAction_node_usage_declaration(SysMLv2Parser::Action_node_usage_declarationContext *context) = 0;

    virtual std::any visitAction_node_prefix(SysMLv2Parser::Action_node_prefixContext *context) = 0;

    virtual std::any visitControl_node(SysMLv2Parser::Control_nodeContext *context) = 0;

    virtual std::any visitControl_node_prefix(SysMLv2Parser::Control_node_prefixContext *context) = 0;

    virtual std::any visitMerge_node(SysMLv2Parser::Merge_nodeContext *context) = 0;

    virtual std::any visitDecision_node(SysMLv2Parser::Decision_nodeContext *context) = 0;

    virtual std::any visitJoin_node(SysMLv2Parser::Join_nodeContext *context) = 0;

    virtual std::any visitFork_node(SysMLv2Parser::Fork_nodeContext *context) = 0;

    virtual std::any visitAccept_node(SysMLv2Parser::Accept_nodeContext *context) = 0;

    virtual std::any visitAccept_node_declaration(SysMLv2Parser::Accept_node_declarationContext *context) = 0;

    virtual std::any visitAccept_parameter_part(SysMLv2Parser::Accept_parameter_partContext *context) = 0;

    virtual std::any visitPayload_parameter_member(SysMLv2Parser::Payload_parameter_memberContext *context) = 0;

    virtual std::any visitPayload_parameter(SysMLv2Parser::Payload_parameterContext *context) = 0;

    virtual std::any visitTrigger_value_part(SysMLv2Parser::Trigger_value_partContext *context) = 0;

    virtual std::any visitTrigger_expression(SysMLv2Parser::Trigger_expressionContext *context) = 0;

    virtual std::any visitSend_node(SysMLv2Parser::Send_nodeContext *context) = 0;

    virtual std::any visitSend_node_declaration(SysMLv2Parser::Send_node_declarationContext *context) = 0;

    virtual std::any visitSender_receiver_part(SysMLv2Parser::Sender_receiver_partContext *context) = 0;

    virtual std::any visitNode_parameter_member(SysMLv2Parser::Node_parameter_memberContext *context) = 0;

    virtual std::any visitNode_parameter(SysMLv2Parser::Node_parameterContext *context) = 0;

    virtual std::any visitFeature_binding(SysMLv2Parser::Feature_bindingContext *context) = 0;

    virtual std::any visitAssignment_node(SysMLv2Parser::Assignment_nodeContext *context) = 0;

    virtual std::any visitAssignment_node_declaration(SysMLv2Parser::Assignment_node_declarationContext *context) = 0;

    virtual std::any visitAssignment_target_member(SysMLv2Parser::Assignment_target_memberContext *context) = 0;

    virtual std::any visitAssignment_target_parameter(SysMLv2Parser::Assignment_target_parameterContext *context) = 0;

    virtual std::any visitAssignment_target_binding(SysMLv2Parser::Assignment_target_bindingContext *context) = 0;

    virtual std::any visitFeature_chain_member(SysMLv2Parser::Feature_chain_memberContext *context) = 0;

    virtual std::any visitOwned_feature_chain_member(SysMLv2Parser::Owned_feature_chain_memberContext *context) = 0;

    virtual std::any visitTerminate_node(SysMLv2Parser::Terminate_nodeContext *context) = 0;

    virtual std::any visitIf_node(SysMLv2Parser::If_nodeContext *context) = 0;

    virtual std::any visitExpression_parameter_member(SysMLv2Parser::Expression_parameter_memberContext *context) = 0;

    virtual std::any visitAction_body_parameter_member(SysMLv2Parser::Action_body_parameter_memberContext *context) = 0;

    virtual std::any visitAction_body_parameter(SysMLv2Parser::Action_body_parameterContext *context) = 0;

    virtual std::any visitIf_node_parameter_member(SysMLv2Parser::If_node_parameter_memberContext *context) = 0;

    virtual std::any visitWhile_loop_node(SysMLv2Parser::While_loop_nodeContext *context) = 0;

    virtual std::any visitFor_loop_node(SysMLv2Parser::For_loop_nodeContext *context) = 0;

    virtual std::any visitFor_variable_declaration_member(SysMLv2Parser::For_variable_declaration_memberContext *context) = 0;

    virtual std::any visitFor_variable_declaration(SysMLv2Parser::For_variable_declarationContext *context) = 0;

    virtual std::any visitAction_target_succession(SysMLv2Parser::Action_target_successionContext *context) = 0;

    virtual std::any visitTarget_succession(SysMLv2Parser::Target_successionContext *context) = 0;

    virtual std::any visitGuarded_target_succession(SysMLv2Parser::Guarded_target_successionContext *context) = 0;

    virtual std::any visitDefault_target_succession(SysMLv2Parser::Default_target_successionContext *context) = 0;

    virtual std::any visitGuarded_succession(SysMLv2Parser::Guarded_successionContext *context) = 0;

    virtual std::any visitState_definition(SysMLv2Parser::State_definitionContext *context) = 0;

    virtual std::any visitState_def_body(SysMLv2Parser::State_def_bodyContext *context) = 0;

    virtual std::any visitState_body_item(SysMLv2Parser::State_body_itemContext *context) = 0;

    virtual std::any visitEntry_action_member(SysMLv2Parser::Entry_action_memberContext *context) = 0;

    virtual std::any visitDo_action_member(SysMLv2Parser::Do_action_memberContext *context) = 0;

    virtual std::any visitExit_action_member(SysMLv2Parser::Exit_action_memberContext *context) = 0;

    virtual std::any visitEntry_transition_member(SysMLv2Parser::Entry_transition_memberContext *context) = 0;

    virtual std::any visitState_action_usage(SysMLv2Parser::State_action_usageContext *context) = 0;

    virtual std::any visitEmpty_action_usage(SysMLv2Parser::Empty_action_usageContext *context) = 0;

    virtual std::any visitState_perform_action_uage(SysMLv2Parser::State_perform_action_uageContext *context) = 0;

    virtual std::any visitState_accept_action_usage(SysMLv2Parser::State_accept_action_usageContext *context) = 0;

    virtual std::any visitState_send_action_usage(SysMLv2Parser::State_send_action_usageContext *context) = 0;

    virtual std::any visitState_assignment_action_usage(SysMLv2Parser::State_assignment_action_usageContext *context) = 0;

    virtual std::any visitTransition_usage_member(SysMLv2Parser::Transition_usage_memberContext *context) = 0;

    virtual std::any visitTarget_transition_usage_member(SysMLv2Parser::Target_transition_usage_memberContext *context) = 0;

    virtual std::any visitState_usage(SysMLv2Parser::State_usageContext *context) = 0;

    virtual std::any visitState_usage_body(SysMLv2Parser::State_usage_bodyContext *context) = 0;

    virtual std::any visitExhibit_state_usage(SysMLv2Parser::Exhibit_state_usageContext *context) = 0;

    virtual std::any visitTransition_usage(SysMLv2Parser::Transition_usageContext *context) = 0;

    virtual std::any visitTarget_transition_usage(SysMLv2Parser::Target_transition_usageContext *context) = 0;

    virtual std::any visitTrigger_action_member(SysMLv2Parser::Trigger_action_memberContext *context) = 0;

    virtual std::any visitTrigger_action(SysMLv2Parser::Trigger_actionContext *context) = 0;

    virtual std::any visitGuard_expression_member(SysMLv2Parser::Guard_expression_memberContext *context) = 0;

    virtual std::any visitEffect_behavior_member(SysMLv2Parser::Effect_behavior_memberContext *context) = 0;

    virtual std::any visitEffect_behavior_usage(SysMLv2Parser::Effect_behavior_usageContext *context) = 0;

    virtual std::any visitTransition_perform_action_usage(SysMLv2Parser::Transition_perform_action_usageContext *context) = 0;

    virtual std::any visitTransition_accept_action_usage(SysMLv2Parser::Transition_accept_action_usageContext *context) = 0;

    virtual std::any visitTransition_send_action_usage(SysMLv2Parser::Transition_send_action_usageContext *context) = 0;

    virtual std::any visitTransition_assignment_action_usage(SysMLv2Parser::Transition_assignment_action_usageContext *context) = 0;

    virtual std::any visitTransition_succession_member(SysMLv2Parser::Transition_succession_memberContext *context) = 0;

    virtual std::any visitTransition_succession(SysMLv2Parser::Transition_successionContext *context) = 0;

    virtual std::any visitCalculation_definition(SysMLv2Parser::Calculation_definitionContext *context) = 0;

    virtual std::any visitCalculation_usage(SysMLv2Parser::Calculation_usageContext *context) = 0;

    virtual std::any visitCalculation_body(SysMLv2Parser::Calculation_bodyContext *context) = 0;

    virtual std::any visitCalculation_body_part(SysMLv2Parser::Calculation_body_partContext *context) = 0;

    virtual std::any visitCalculation_body_item(SysMLv2Parser::Calculation_body_itemContext *context) = 0;

    virtual std::any visitReturn_parameter_member(SysMLv2Parser::Return_parameter_memberContext *context) = 0;

    virtual std::any visitResult_expression_member(SysMLv2Parser::Result_expression_memberContext *context) = 0;

    virtual std::any visitConstraint_definition(SysMLv2Parser::Constraint_definitionContext *context) = 0;

    virtual std::any visitConstraint_usage(SysMLv2Parser::Constraint_usageContext *context) = 0;

    virtual std::any visitAssert_constriant_usage(SysMLv2Parser::Assert_constriant_usageContext *context) = 0;

    virtual std::any visitConstraint_usage_declaration(SysMLv2Parser::Constraint_usage_declarationContext *context) = 0;

    virtual std::any visitRequirement_definition(SysMLv2Parser::Requirement_definitionContext *context) = 0;

    virtual std::any visitRequirement_body(SysMLv2Parser::Requirement_bodyContext *context) = 0;

    virtual std::any visitRequirement_body_item(SysMLv2Parser::Requirement_body_itemContext *context) = 0;

    virtual std::any visitSubject_member(SysMLv2Parser::Subject_memberContext *context) = 0;

    virtual std::any visitSubject_usage(SysMLv2Parser::Subject_usageContext *context) = 0;

    virtual std::any visitRequirement_constraint_member(SysMLv2Parser::Requirement_constraint_memberContext *context) = 0;

    virtual std::any visitRequriement_kind(SysMLv2Parser::Requriement_kindContext *context) = 0;

    virtual std::any visitRequirement_constraint_usage(SysMLv2Parser::Requirement_constraint_usageContext *context) = 0;

    virtual std::any visitFramed_concern_member(SysMLv2Parser::Framed_concern_memberContext *context) = 0;

    virtual std::any visitFramed_concern_usage(SysMLv2Parser::Framed_concern_usageContext *context) = 0;

    virtual std::any visitActor_member(SysMLv2Parser::Actor_memberContext *context) = 0;

    virtual std::any visitActor_usage(SysMLv2Parser::Actor_usageContext *context) = 0;

    virtual std::any visitStakeholder_member(SysMLv2Parser::Stakeholder_memberContext *context) = 0;

    virtual std::any visitStakeholder_usage(SysMLv2Parser::Stakeholder_usageContext *context) = 0;

    virtual std::any visitRequirement_usage(SysMLv2Parser::Requirement_usageContext *context) = 0;

    virtual std::any visitSatisfy_requirement_usage(SysMLv2Parser::Satisfy_requirement_usageContext *context) = 0;

    virtual std::any visitSatisfaction_subject_member(SysMLv2Parser::Satisfaction_subject_memberContext *context) = 0;

    virtual std::any visitSatisfaction_parameter(SysMLv2Parser::Satisfaction_parameterContext *context) = 0;

    virtual std::any visitSatisfaction_feature_value(SysMLv2Parser::Satisfaction_feature_valueContext *context) = 0;

    virtual std::any visitSatisfaction_reference_expression(SysMLv2Parser::Satisfaction_reference_expressionContext *context) = 0;

    virtual std::any visitConcern_definition(SysMLv2Parser::Concern_definitionContext *context) = 0;

    virtual std::any visitConcern_usage(SysMLv2Parser::Concern_usageContext *context) = 0;

    virtual std::any visitCase_definition(SysMLv2Parser::Case_definitionContext *context) = 0;

    virtual std::any visitCase_usage(SysMLv2Parser::Case_usageContext *context) = 0;

    virtual std::any visitCase_body(SysMLv2Parser::Case_bodyContext *context) = 0;

    virtual std::any visitCase_body_item(SysMLv2Parser::Case_body_itemContext *context) = 0;

    virtual std::any visitObjective_member(SysMLv2Parser::Objective_memberContext *context) = 0;

    virtual std::any visitObjective_requirement_usage(SysMLv2Parser::Objective_requirement_usageContext *context) = 0;

    virtual std::any visitAnalysis_case_definition(SysMLv2Parser::Analysis_case_definitionContext *context) = 0;

    virtual std::any visitAnalysis_case_usage(SysMLv2Parser::Analysis_case_usageContext *context) = 0;

    virtual std::any visitVerification_case_definition(SysMLv2Parser::Verification_case_definitionContext *context) = 0;

    virtual std::any visitVerification_case_usage(SysMLv2Parser::Verification_case_usageContext *context) = 0;

    virtual std::any visitRequirement_verification_member(SysMLv2Parser::Requirement_verification_memberContext *context) = 0;

    virtual std::any visitRequirement_verification_usage(SysMLv2Parser::Requirement_verification_usageContext *context) = 0;

    virtual std::any visitUse_case_definition(SysMLv2Parser::Use_case_definitionContext *context) = 0;

    virtual std::any visitUse_case_usage(SysMLv2Parser::Use_case_usageContext *context) = 0;

    virtual std::any visitInclude_use_case_usage(SysMLv2Parser::Include_use_case_usageContext *context) = 0;

    virtual std::any visitView_definition(SysMLv2Parser::View_definitionContext *context) = 0;

    virtual std::any visitView_definition_body(SysMLv2Parser::View_definition_bodyContext *context) = 0;

    virtual std::any visitView_definition_body_item(SysMLv2Parser::View_definition_body_itemContext *context) = 0;

    virtual std::any visitView_rendering_member(SysMLv2Parser::View_rendering_memberContext *context) = 0;

    virtual std::any visitView_rendering_usage(SysMLv2Parser::View_rendering_usageContext *context) = 0;

    virtual std::any visitView_usage(SysMLv2Parser::View_usageContext *context) = 0;

    virtual std::any visitView_body(SysMLv2Parser::View_bodyContext *context) = 0;

    virtual std::any visitView_body_item(SysMLv2Parser::View_body_itemContext *context) = 0;

    virtual std::any visitExpose(SysMLv2Parser::ExposeContext *context) = 0;

    virtual std::any visitMembership_expose(SysMLv2Parser::Membership_exposeContext *context) = 0;

    virtual std::any visitNamespace_expose(SysMLv2Parser::Namespace_exposeContext *context) = 0;

    virtual std::any visitViewpoint_definition(SysMLv2Parser::Viewpoint_definitionContext *context) = 0;

    virtual std::any visitViewpoint_usage(SysMLv2Parser::Viewpoint_usageContext *context) = 0;

    virtual std::any visitRendering_definition(SysMLv2Parser::Rendering_definitionContext *context) = 0;

    virtual std::any visitRendering_usage(SysMLv2Parser::Rendering_usageContext *context) = 0;

    virtual std::any visitMetadata_definition(SysMLv2Parser::Metadata_definitionContext *context) = 0;

    virtual std::any visitPrefix_metadata_annotation(SysMLv2Parser::Prefix_metadata_annotationContext *context) = 0;

    virtual std::any visitPrefix_metadata_member(SysMLv2Parser::Prefix_metadata_memberContext *context) = 0;

    virtual std::any visitPrefix_metadata_usage(SysMLv2Parser::Prefix_metadata_usageContext *context) = 0;

    virtual std::any visitMetadata_usage(SysMLv2Parser::Metadata_usageContext *context) = 0;

    virtual std::any visitMetadata_usage_declaration(SysMLv2Parser::Metadata_usage_declarationContext *context) = 0;

    virtual std::any visitMetadata_body(SysMLv2Parser::Metadata_bodyContext *context) = 0;

    virtual std::any visitMetadata_body_usage_member(SysMLv2Parser::Metadata_body_usage_memberContext *context) = 0;

    virtual std::any visitMetadata_body_usage(SysMLv2Parser::Metadata_body_usageContext *context) = 0;

    virtual std::any visitExtended_definition(SysMLv2Parser::Extended_definitionContext *context) = 0;

    virtual std::any visitExtended_usage(SysMLv2Parser::Extended_usageContext *context) = 0;

    virtual std::any visitDefined_by(SysMLv2Parser::Defined_byContext *context) = 0;

    virtual std::any visitElements(SysMLv2Parser::ElementsContext *context) = 0;

    virtual std::any visitIdentification(SysMLv2Parser::IdentificationContext *context) = 0;

    virtual std::any visitRelationship_owned_elements(SysMLv2Parser::Relationship_owned_elementsContext *context) = 0;

    virtual std::any visitRelationship_owned_element(SysMLv2Parser::Relationship_owned_elementContext *context) = 0;

    virtual std::any visitOwned_related_element(SysMLv2Parser::Owned_related_elementContext *context) = 0;

    virtual std::any visitNamespace(SysMLv2Parser::NamespaceContext *context) = 0;

    virtual std::any visitNamespace_declaration(SysMLv2Parser::Namespace_declarationContext *context) = 0;

    virtual std::any visitNamespace_body(SysMLv2Parser::Namespace_bodyContext *context) = 0;

    virtual std::any visitNamespace_body_elements(SysMLv2Parser::Namespace_body_elementsContext *context) = 0;

    virtual std::any visitNamespace_body_element(SysMLv2Parser::Namespace_body_elementContext *context) = 0;

    virtual std::any visitMember_prefix(SysMLv2Parser::Member_prefixContext *context) = 0;

    virtual std::any visitVisibility_indicator(SysMLv2Parser::Visibility_indicatorContext *context) = 0;

    virtual std::any visitNamespace_member(SysMLv2Parser::Namespace_memberContext *context) = 0;

    virtual std::any visitNon_feature_member(SysMLv2Parser::Non_feature_memberContext *context) = 0;

    virtual std::any visitNamespace_feature_member(SysMLv2Parser::Namespace_feature_memberContext *context) = 0;

    virtual std::any visitQualified_name(SysMLv2Parser::Qualified_nameContext *context) = 0;

    virtual std::any visitNamespace_import(SysMLv2Parser::Namespace_importContext *context) = 0;

    virtual std::any visitImport_declaration(SysMLv2Parser::Import_declarationContext *context) = 0;

    virtual std::any visitMembership_import(SysMLv2Parser::Membership_importContext *context) = 0;

    virtual std::any visitFilter_package(SysMLv2Parser::Filter_packageContext *context) = 0;

    virtual std::any visitFilter_package_member(SysMLv2Parser::Filter_package_memberContext *context) = 0;

    virtual std::any visitElement(SysMLv2Parser::ElementContext *context) = 0;

    virtual std::any visitNon_feature_element(SysMLv2Parser::Non_feature_elementContext *context) = 0;

    virtual std::any visitFeature_element(SysMLv2Parser::Feature_elementContext *context) = 0;

    virtual std::any visitAdditional_options(SysMLv2Parser::Additional_optionsContext *context) = 0;

    virtual std::any visitType(SysMLv2Parser::TypeContext *context) = 0;

    virtual std::any visitType_prefix(SysMLv2Parser::Type_prefixContext *context) = 0;

    virtual std::any visitType_declaration(SysMLv2Parser::Type_declarationContext *context) = 0;

    virtual std::any visitSpecialization_part(SysMLv2Parser::Specialization_partContext *context) = 0;

    virtual std::any visitConjugation_part(SysMLv2Parser::Conjugation_partContext *context) = 0;

    virtual std::any visitType_relationship_part(SysMLv2Parser::Type_relationship_partContext *context) = 0;

    virtual std::any visitDisjoining_part(SysMLv2Parser::Disjoining_partContext *context) = 0;

    virtual std::any visitUnioning_part(SysMLv2Parser::Unioning_partContext *context) = 0;

    virtual std::any visitIntersecting_part(SysMLv2Parser::Intersecting_partContext *context) = 0;

    virtual std::any visitDifferencing_part(SysMLv2Parser::Differencing_partContext *context) = 0;

    virtual std::any visitType_body(SysMLv2Parser::Type_bodyContext *context) = 0;

    virtual std::any visitType_body_elements(SysMLv2Parser::Type_body_elementsContext *context) = 0;

    virtual std::any visitType_body_element(SysMLv2Parser::Type_body_elementContext *context) = 0;

    virtual std::any visitSpecialization(SysMLv2Parser::SpecializationContext *context) = 0;

    virtual std::any visitOwned_specialization(SysMLv2Parser::Owned_specializationContext *context) = 0;

    virtual std::any visitSpecific_type(SysMLv2Parser::Specific_typeContext *context) = 0;

    virtual std::any visitGeneral_type(SysMLv2Parser::General_typeContext *context) = 0;

    virtual std::any visitConjunction(SysMLv2Parser::ConjunctionContext *context) = 0;

    virtual std::any visitOwned_conjugation(SysMLv2Parser::Owned_conjugationContext *context) = 0;

    virtual std::any visitDisjoining(SysMLv2Parser::DisjoiningContext *context) = 0;

    virtual std::any visitOwned_disjoining(SysMLv2Parser::Owned_disjoiningContext *context) = 0;

    virtual std::any visitUnioning(SysMLv2Parser::UnioningContext *context) = 0;

    virtual std::any visitIntersecting(SysMLv2Parser::IntersectingContext *context) = 0;

    virtual std::any visitDifferencing(SysMLv2Parser::DifferencingContext *context) = 0;

    virtual std::any visitFeature_member(SysMLv2Parser::Feature_memberContext *context) = 0;

    virtual std::any visitType_feature_member(SysMLv2Parser::Type_feature_memberContext *context) = 0;

    virtual std::any visitOwned_feature_member(SysMLv2Parser::Owned_feature_memberContext *context) = 0;

    virtual std::any visitClassifier(SysMLv2Parser::ClassifierContext *context) = 0;

    virtual std::any visitClassifier_declaration(SysMLv2Parser::Classifier_declarationContext *context) = 0;

    virtual std::any visitSuperclassing_part(SysMLv2Parser::Superclassing_partContext *context) = 0;

    virtual std::any visitSubclassification(SysMLv2Parser::SubclassificationContext *context) = 0;

    virtual std::any visitOwned_subclassification(SysMLv2Parser::Owned_subclassificationContext *context) = 0;

    virtual std::any visitFeature(SysMLv2Parser::FeatureContext *context) = 0;

    virtual std::any visitFeature_prefix(SysMLv2Parser::Feature_prefixContext *context) = 0;

    virtual std::any visitFeature_declaration(SysMLv2Parser::Feature_declarationContext *context) = 0;

    virtual std::any visitFeature_identification(SysMLv2Parser::Feature_identificationContext *context) = 0;

    virtual std::any visitFeature_relationship_part(SysMLv2Parser::Feature_relationship_partContext *context) = 0;

    virtual std::any visitChaining_part(SysMLv2Parser::Chaining_partContext *context) = 0;

    virtual std::any visitInverting_part(SysMLv2Parser::Inverting_partContext *context) = 0;

    virtual std::any visitType_featuring_part(SysMLv2Parser::Type_featuring_partContext *context) = 0;

    virtual std::any visitFeature_specialization_part(SysMLv2Parser::Feature_specialization_partContext *context) = 0;

    virtual std::any visitFeature_specialization(SysMLv2Parser::Feature_specializationContext *context) = 0;

    virtual std::any visitTypings(SysMLv2Parser::TypingsContext *context) = 0;

    virtual std::any visitTyped_by(SysMLv2Parser::Typed_byContext *context) = 0;

    virtual std::any visitSubsettings(SysMLv2Parser::SubsettingsContext *context) = 0;

    virtual std::any visitSubsets(SysMLv2Parser::SubsetsContext *context) = 0;

    virtual std::any visitReferences(SysMLv2Parser::ReferencesContext *context) = 0;

    virtual std::any visitRedefinitions(SysMLv2Parser::RedefinitionsContext *context) = 0;

    virtual std::any visitRedefines(SysMLv2Parser::RedefinesContext *context) = 0;

    virtual std::any visitFeature_typing(SysMLv2Parser::Feature_typingContext *context) = 0;

    virtual std::any visitOwned_feature_typing(SysMLv2Parser::Owned_feature_typingContext *context) = 0;

    virtual std::any visitSubsetting(SysMLv2Parser::SubsettingContext *context) = 0;

    virtual std::any visitOwned_subsetting(SysMLv2Parser::Owned_subsettingContext *context) = 0;

    virtual std::any visitOwned_reference_subsetting(SysMLv2Parser::Owned_reference_subsettingContext *context) = 0;

    virtual std::any visitRedefinition(SysMLv2Parser::RedefinitionContext *context) = 0;

    virtual std::any visitOwned_redefinition(SysMLv2Parser::Owned_redefinitionContext *context) = 0;

    virtual std::any visitOwned_feature_chain(SysMLv2Parser::Owned_feature_chainContext *context) = 0;

    virtual std::any visitFeature_chain(SysMLv2Parser::Feature_chainContext *context) = 0;

    virtual std::any visitOwned_feature_chaining(SysMLv2Parser::Owned_feature_chainingContext *context) = 0;

    virtual std::any visitFeature_inverting(SysMLv2Parser::Feature_invertingContext *context) = 0;

    virtual std::any visitOwned_feature_inverting(SysMLv2Parser::Owned_feature_invertingContext *context) = 0;

    virtual std::any visitType_featuring(SysMLv2Parser::Type_featuringContext *context) = 0;

    virtual std::any visitOwned_type_featuring(SysMLv2Parser::Owned_type_featuringContext *context) = 0;

    virtual std::any visitData_type(SysMLv2Parser::Data_typeContext *context) = 0;

    virtual std::any visitClass(SysMLv2Parser::ClassContext *context) = 0;

    virtual std::any visitStructure(SysMLv2Parser::StructureContext *context) = 0;

    virtual std::any visitAssociation(SysMLv2Parser::AssociationContext *context) = 0;

    virtual std::any visitAssociation_structure(SysMLv2Parser::Association_structureContext *context) = 0;

    virtual std::any visitConnector(SysMLv2Parser::ConnectorContext *context) = 0;

    virtual std::any visitConnector_declaration(SysMLv2Parser::Connector_declarationContext *context) = 0;

    virtual std::any visitBinary_connector_declaration(SysMLv2Parser::Binary_connector_declarationContext *context) = 0;

    virtual std::any visitNary_connector_declaration(SysMLv2Parser::Nary_connector_declarationContext *context) = 0;

    virtual std::any visitConnector_end(SysMLv2Parser::Connector_endContext *context) = 0;

    virtual std::any visitBinding_connector(SysMLv2Parser::Binding_connectorContext *context) = 0;

    virtual std::any visitBinding_connector_declaration(SysMLv2Parser::Binding_connector_declarationContext *context) = 0;

    virtual std::any visitSuccession(SysMLv2Parser::SuccessionContext *context) = 0;

    virtual std::any visitSuccession_declaration(SysMLv2Parser::Succession_declarationContext *context) = 0;

    virtual std::any visitBehavior(SysMLv2Parser::BehaviorContext *context) = 0;

    virtual std::any visitStep(SysMLv2Parser::StepContext *context) = 0;

    virtual std::any visitFunction(SysMLv2Parser::FunctionContext *context) = 0;

    virtual std::any visitFunction_body(SysMLv2Parser::Function_bodyContext *context) = 0;

    virtual std::any visitFunction_body_part(SysMLv2Parser::Function_body_partContext *context) = 0;

    virtual std::any visitReturn_feature_member(SysMLv2Parser::Return_feature_memberContext *context) = 0;

    virtual std::any visitExpression(SysMLv2Parser::ExpressionContext *context) = 0;

    virtual std::any visitPredicate(SysMLv2Parser::PredicateContext *context) = 0;

    virtual std::any visitBoolean_expression(SysMLv2Parser::Boolean_expressionContext *context) = 0;

    virtual std::any visitInvariant(SysMLv2Parser::InvariantContext *context) = 0;

    virtual std::any visitOwned_expression_reference_member(SysMLv2Parser::Owned_expression_reference_memberContext *context) = 0;

    virtual std::any visitOwned_expression_reference(SysMLv2Parser::Owned_expression_referenceContext *context) = 0;

    virtual std::any visitOwned_expression_member(SysMLv2Parser::Owned_expression_memberContext *context) = 0;

    virtual std::any visitOwned_expressions(SysMLv2Parser::Owned_expressionsContext *context) = 0;

    virtual std::any visitOwned_expression(SysMLv2Parser::Owned_expressionContext *context) = 0;

    virtual std::any visitEased_owned_expression(SysMLv2Parser::Eased_owned_expressionContext *context) = 0;

    virtual std::any visitConditional_expression(SysMLv2Parser::Conditional_expressionContext *context) = 0;

    virtual std::any visitConditional_binary_operator_expression(SysMLv2Parser::Conditional_binary_operator_expressionContext *context) = 0;

    virtual std::any visitConditional_binary_operator(SysMLv2Parser::Conditional_binary_operatorContext *context) = 0;

    virtual std::any visitBinary_operator_expression(SysMLv2Parser::Binary_operator_expressionContext *context) = 0;

    virtual std::any visitBinary_operator(SysMLv2Parser::Binary_operatorContext *context) = 0;

    virtual std::any visitUnary_operator_expression(SysMLv2Parser::Unary_operator_expressionContext *context) = 0;

    virtual std::any visitUnary_operator(SysMLv2Parser::Unary_operatorContext *context) = 0;

    virtual std::any visitClassification_expression(SysMLv2Parser::Classification_expressionContext *context) = 0;

    virtual std::any visitClassification(SysMLv2Parser::ClassificationContext *context) = 0;

    virtual std::any visitClassification_test_operator(SysMLv2Parser::Classification_test_operatorContext *context) = 0;

    virtual std::any visitCast_operator(SysMLv2Parser::Cast_operatorContext *context) = 0;

    virtual std::any visitMetaclassification_expression(SysMLv2Parser::Metaclassification_expressionContext *context) = 0;

    virtual std::any visitArgument_member(SysMLv2Parser::Argument_memberContext *context) = 0;

    virtual std::any visitArgument(SysMLv2Parser::ArgumentContext *context) = 0;

    virtual std::any visitArgument_value(SysMLv2Parser::Argument_valueContext *context) = 0;

    virtual std::any visitArgument_expression_member(SysMLv2Parser::Argument_expression_memberContext *context) = 0;

    virtual std::any visitArgument_expression(SysMLv2Parser::Argument_expressionContext *context) = 0;

    virtual std::any visitArgument_expression_value(SysMLv2Parser::Argument_expression_valueContext *context) = 0;

    virtual std::any visitMetadata_argument_member(SysMLv2Parser::Metadata_argument_memberContext *context) = 0;

    virtual std::any visitMetadata_argument(SysMLv2Parser::Metadata_argumentContext *context) = 0;

    virtual std::any visitMetadata_value(SysMLv2Parser::Metadata_valueContext *context) = 0;

    virtual std::any visitMetadata_reference(SysMLv2Parser::Metadata_referenceContext *context) = 0;

    virtual std::any visitMetadataclassification_test_operator(SysMLv2Parser::Metadataclassification_test_operatorContext *context) = 0;

    virtual std::any visitMeta_cast_operator(SysMLv2Parser::Meta_cast_operatorContext *context) = 0;

    virtual std::any visitExtend_expression(SysMLv2Parser::Extend_expressionContext *context) = 0;

    virtual std::any visitType_reference_member(SysMLv2Parser::Type_reference_memberContext *context) = 0;

    virtual std::any visitType_result_member(SysMLv2Parser::Type_result_memberContext *context) = 0;

    virtual std::any visitType_reference(SysMLv2Parser::Type_referenceContext *context) = 0;

    virtual std::any visitReference_typing(SysMLv2Parser::Reference_typingContext *context) = 0;

    virtual std::any visitPrimary_expressions(SysMLv2Parser::Primary_expressionsContext *context) = 0;

    virtual std::any visitPrimary_expression(SysMLv2Parser::Primary_expressionContext *context) = 0;

    virtual std::any visitPrimary_argument_value(SysMLv2Parser::Primary_argument_valueContext *context) = 0;

    virtual std::any visitPrimary_argument(SysMLv2Parser::Primary_argumentContext *context) = 0;

    virtual std::any visitPrimary_argument_member(SysMLv2Parser::Primary_argument_memberContext *context) = 0;

    virtual std::any visitNon_feature_chain_primary_expression(SysMLv2Parser::Non_feature_chain_primary_expressionContext *context) = 0;

    virtual std::any visitNon_feature_chain_primary_argument_value(SysMLv2Parser::Non_feature_chain_primary_argument_valueContext *context) = 0;

    virtual std::any visitNon_feature_chain_primary_argument(SysMLv2Parser::Non_feature_chain_primary_argumentContext *context) = 0;

    virtual std::any visitNon_feature_chain_primary_argument_member(SysMLv2Parser::Non_feature_chain_primary_argument_memberContext *context) = 0;

    virtual std::any visitBracket_expression(SysMLv2Parser::Bracket_expressionContext *context) = 0;

    virtual std::any visitIndex_expression(SysMLv2Parser::Index_expressionContext *context) = 0;

    virtual std::any visitSequence_expression(SysMLv2Parser::Sequence_expressionContext *context) = 0;

    virtual std::any visitSequence_expression_list(SysMLv2Parser::Sequence_expression_listContext *context) = 0;

    virtual std::any visitSequence_operator_expression(SysMLv2Parser::Sequence_operator_expressionContext *context) = 0;

    virtual std::any visitSequence_expression_list_member(SysMLv2Parser::Sequence_expression_list_memberContext *context) = 0;

    virtual std::any visitFeature_chain_expression(SysMLv2Parser::Feature_chain_expressionContext *context) = 0;

    virtual std::any visitCollect_expression(SysMLv2Parser::Collect_expressionContext *context) = 0;

    virtual std::any visitSelect_expression(SysMLv2Parser::Select_expressionContext *context) = 0;

    virtual std::any visitFunction_operation_expression(SysMLv2Parser::Function_operation_expressionContext *context) = 0;

    virtual std::any visitBody_argument_member(SysMLv2Parser::Body_argument_memberContext *context) = 0;

    virtual std::any visitBody_argument(SysMLv2Parser::Body_argumentContext *context) = 0;

    virtual std::any visitBody_argument_value(SysMLv2Parser::Body_argument_valueContext *context) = 0;

    virtual std::any visitBody_expression_member(SysMLv2Parser::Body_expression_memberContext *context) = 0;

    virtual std::any visitFunction_reference_argument_member(SysMLv2Parser::Function_reference_argument_memberContext *context) = 0;

    virtual std::any visitFunction_reference_argument(SysMLv2Parser::Function_reference_argumentContext *context) = 0;

    virtual std::any visitFunction_reference_arugment_value(SysMLv2Parser::Function_reference_arugment_valueContext *context) = 0;

    virtual std::any visitFunction_reference_expression(SysMLv2Parser::Function_reference_expressionContext *context) = 0;

    virtual std::any visitFunction_reference_member(SysMLv2Parser::Function_reference_memberContext *context) = 0;

    virtual std::any visitFunction_reference(SysMLv2Parser::Function_referenceContext *context) = 0;

    virtual std::any visitBase_expression(SysMLv2Parser::Base_expressionContext *context) = 0;

    virtual std::any visitNull_expression(SysMLv2Parser::Null_expressionContext *context) = 0;

    virtual std::any visitFeature_reference_expression(SysMLv2Parser::Feature_reference_expressionContext *context) = 0;

    virtual std::any visitFeature_reference_member(SysMLv2Parser::Feature_reference_memberContext *context) = 0;

    virtual std::any visitFeature_reference(SysMLv2Parser::Feature_referenceContext *context) = 0;

    virtual std::any visitMetadata_access_expression(SysMLv2Parser::Metadata_access_expressionContext *context) = 0;

    virtual std::any visitInvocation_expression(SysMLv2Parser::Invocation_expressionContext *context) = 0;

    virtual std::any visitInternal_invocation_expression(SysMLv2Parser::Internal_invocation_expressionContext *context) = 0;

    virtual std::any visitArgument_list(SysMLv2Parser::Argument_listContext *context) = 0;

    virtual std::any visitPositional_argument_list(SysMLv2Parser::Positional_argument_listContext *context) = 0;

    virtual std::any visitNamed_argument_list(SysMLv2Parser::Named_argument_listContext *context) = 0;

    virtual std::any visitNamed_argument_member(SysMLv2Parser::Named_argument_memberContext *context) = 0;

    virtual std::any visitNamed_argument(SysMLv2Parser::Named_argumentContext *context) = 0;

    virtual std::any visitParameter_redefinition(SysMLv2Parser::Parameter_redefinitionContext *context) = 0;

    virtual std::any visitBody_expression(SysMLv2Parser::Body_expressionContext *context) = 0;

    virtual std::any visitExpression_body_member(SysMLv2Parser::Expression_body_memberContext *context) = 0;

    virtual std::any visitExpression_body(SysMLv2Parser::Expression_bodyContext *context) = 0;

    virtual std::any visitLiteral_expression(SysMLv2Parser::Literal_expressionContext *context) = 0;

    virtual std::any visitLiteral_boolean(SysMLv2Parser::Literal_booleanContext *context) = 0;

    virtual std::any visitBoolean_value(SysMLv2Parser::Boolean_valueContext *context) = 0;

    virtual std::any visitLiteral_string(SysMLv2Parser::Literal_stringContext *context) = 0;

    virtual std::any visitLiteral_integer(SysMLv2Parser::Literal_integerContext *context) = 0;

    virtual std::any visitLiteral_real(SysMLv2Parser::Literal_realContext *context) = 0;

    virtual std::any visitReal_value(SysMLv2Parser::Real_valueContext *context) = 0;

    virtual std::any visitLiteral_infinity(SysMLv2Parser::Literal_infinityContext *context) = 0;

    virtual std::any visitInteraction(SysMLv2Parser::InteractionContext *context) = 0;

    virtual std::any visitItem_flow(SysMLv2Parser::Item_flowContext *context) = 0;

    virtual std::any visitSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext *context) = 0;

    virtual std::any visitItem_flow_declaration(SysMLv2Parser::Item_flow_declarationContext *context) = 0;

    virtual std::any visitItem_feature_member(SysMLv2Parser::Item_feature_memberContext *context) = 0;

    virtual std::any visitItem_feature(SysMLv2Parser::Item_featureContext *context) = 0;

    virtual std::any visitItem_feature_specialization_part(SysMLv2Parser::Item_feature_specialization_partContext *context) = 0;

    virtual std::any visitItem_flow_end_member(SysMLv2Parser::Item_flow_end_memberContext *context) = 0;

    virtual std::any visitItem_flow_end(SysMLv2Parser::Item_flow_endContext *context) = 0;

    virtual std::any visitItem_flow_feature_member(SysMLv2Parser::Item_flow_feature_memberContext *context) = 0;

    virtual std::any visitItem_flow_feature(SysMLv2Parser::Item_flow_featureContext *context) = 0;

    virtual std::any visitItem_flow_redefinition(SysMLv2Parser::Item_flow_redefinitionContext *context) = 0;

    virtual std::any visitValue_part(SysMLv2Parser::Value_partContext *context) = 0;

    virtual std::any visitFeature_value(SysMLv2Parser::Feature_valueContext *context) = 0;

    virtual std::any visitFeature_assignment(SysMLv2Parser::Feature_assignmentContext *context) = 0;

    virtual std::any visitMultiplicity(SysMLv2Parser::MultiplicityContext *context) = 0;

    virtual std::any visitMultiplicity_subset(SysMLv2Parser::Multiplicity_subsetContext *context) = 0;

    virtual std::any visitOwned_multiplicity_range(SysMLv2Parser::Owned_multiplicity_rangeContext *context) = 0;

    virtual std::any visitMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext *context) = 0;

    virtual std::any visitMultiplicity_expression_member(SysMLv2Parser::Multiplicity_expression_memberContext *context) = 0;

    virtual std::any visitInternal_multiplicity_expression_member(SysMLv2Parser::Internal_multiplicity_expression_memberContext *context) = 0;

    virtual std::any visitMetaclass(SysMLv2Parser::MetaclassContext *context) = 0;

    virtual std::any visitPrefix_metadata_feature(SysMLv2Parser::Prefix_metadata_featureContext *context) = 0;

    virtual std::any visitMetadata_feature(SysMLv2Parser::Metadata_featureContext *context) = 0;

    virtual std::any visitMetadata_feature_declaration(SysMLv2Parser::Metadata_feature_declarationContext *context) = 0;

    virtual std::any visitMetadata_body_element(SysMLv2Parser::Metadata_body_elementContext *context) = 0;

    virtual std::any visitMetadata_body_feature_member(SysMLv2Parser::Metadata_body_feature_memberContext *context) = 0;

    virtual std::any visitMetadata_body_feature(SysMLv2Parser::Metadata_body_featureContext *context) = 0;

    virtual std::any visitLibrary_package(SysMLv2Parser::Library_packageContext *context) = 0;

    virtual std::any visitPackage_declaration(SysMLv2Parser::Package_declarationContext *context) = 0;

    virtual std::any visitElement_filter_member(SysMLv2Parser::Element_filter_memberContext *context) = 0;

    virtual std::any visitMeta_assignment(SysMLv2Parser::Meta_assignmentContext *context) = 0;


};

