grammar SysMLv2;

import KerML;

start: start_element* EOF;

start_element: element | definition_element | usage_element;

startRule: start;

relationship_body: SYMBOL_STATEMENT_DELIMITER | (SYMBOL_CURLY_BRACKET_OPEN owned_annotation SYMBOL_CURLY_BRACKET_CLOSE);
dependency: prefix_metadata_annotation* KEYWORD_DEPENDENCY dependency_declaration relationship_body;
dependency_declaration: (identification KEYWORD_FROM)? qualified_name (SYMBOL_COMMA qualified_name)* KEYWORD_TO qualified_name (SYMBOL_COMMA qualified_name)*;

annotation: qualified_name;
owned_annotation: annotating_element;
annotating_member: annotating_element;
annotating_element: comment | documentation | textual_representation | metadata_feature;

comment: (KEYWORD_COMMENT identification (KEYWORD_ABOUT annotation (SYMBOL_COMMA annotation)*)?)?(KEYWORD_LOCALE STRING_VALUE)? REGULAR_COMMENT;
documentation: KEYWORD_DOC identification (KEYWORD_LOCALE STRING_VALUE)? REGULAR_COMMENT;
textual_representation: (KEYWORD_REP identification)? KEYWORD_LANGUAGE STRING_VALUE REGULAR_COMMENT;

root_namespace: package_body_element*;
package: prefix_metadata_member* package_declaration package_body;
package_body: SYMBOL_STATEMENT_DELIMITER | (SYMBOL_CURLY_BRACKET_OPEN package_body_element* SYMBOL_CURLY_BRACKET_CLOSE);
package_body_element: package_member |
                      element_filter_member |
                      alias_member |
                      namespace_import;

package_member: definition_element | usage_element;
alias_member: member_prefix KEYWORD_ALIAS ('<'NAME'>')? NAME? KEYWORD_FOR qualified_name relationship_body;

definition_element: package |
                    library_package |
                    annotating_element |
                    dependency |
                    attribute_definition |
                    enumeration_definition |
                    occurrence_definition |
                    individual_definition |
                    item_definition |
                    part_definition |
                    connection_definition |
                    flow_definition |
                    interface_definition |
                    port_definition |
                    action_definition |
                    calculation_definition |
                    state_definition |
                    constraint_definition |
                    requirement_definition |
                    calculation_definition |
                    state_definition |
                    requirement_definition |
                    concern_definition |
                    case_definition |
                    analysis_case_definition |
                    verification_case_definition |
                    view_definition |
                    viewpoint_definition |
                    rendering_definition |
                    metadata_definition |
                    extended_definition;

usage_element: non_occurrence_usage_element | occurrence_usage_element;

basic_definition_prefix: KEYWORD_ABSTRACT | KEYWORD_VARIATION;
definition_extension_keyword: prefix_metadata_member;
definition_prefix: basic_definition_prefix? definition_extension_keyword*;
definition: definition_declaration definition_body;
definition_declaration: identification subsclassification_part?;
definition_body: SYMBOL_STATEMENT_DELIMITER | (SYMBOL_CURLY_BRACKET_OPEN definition_body_item* SYMBOL_CURLY_BRACKET_CLOSE);
definition_body_item: definition_member |
                      variant_usage_member |
                      non_occurrence_usage_member |
                      source_succession_member? occurrence_usage_member |
                      alias_member |
                      namespace_import;
definition_member: member_prefix definition_element;
variant_usage_member: member_prefix KEYWORD_VARIANT variant_usage_element;
non_occurrence_usage_member: member_prefix non_occurrence_usage_element;
occurrence_usage_member: member_prefix occurrence_usage_element;
structure_usage_member: member_prefix structure_usage_element;
behavior_usage_member: member_prefix behavior_usage_element;

feature_direction: KEYWORD_IN | KEYWORD_OUT | KEYWORD_INOUT;
ref_prefix: feature_direction? KEYWORD_DERIVED? (KEYWORD_VARIATION | KEYWORD_CONSTANT | KEYWORD_ABSTRACT KEYWORD_CONSTANT?)?;
basic_usage_prefix: ref_prefix KEYWORD_REF?;
end_usage_prefix: KEYWORD_END? owned_cross_feature_member?;
owned_cross_feature_member: owned_cross_feature;
owned_cross_feature: basic_usage_prefix usage_declaration;
usage_extention_keyword: prefix_metadata_member;
unextended_usage_prefix: end_usage_prefix | basic_usage_prefix;
usage_prefix: unextended_usage_prefix usage_extention_keyword*;
usage: usage_declaration usage_completion;
usage_declaration: identification feature_specialization_part?;
usage_completion: value_part? usage_body;
usage_body: definition_body;

default_reference_usage: ref_prefix usage;
reference_usage: (end_usage_prefix | ref_prefix) KEYWORD_REF usage;
variant_reference: owned_reference_subsetting feature_specilization* usage_body;

non_occurrence_usage_element: default_reference_usage |
                              reference_usage |
                              attribute_usage |
                              enumeration_usage |
                              binding_connector_as_usage |
                              succession_as_usage |
                              extended_usage;
occurrence_usage_element: structure_usage_element | behavior_usage_element;
structure_usage_element: occurrence_usage |
                         individual_usage |
                         portion_usage |
                         event_occurrence_usage |
                         item_usage |
                         part_usage |
                         view_usage |
                         rendering_usage |
                         port_usage |
                         connection_usage |
                         interface_usage |
                         allocation_usage |
                         message |
                         flow_usage |
                         succession_flow_usage;
behavior_usage_element: action_usage |
                        calculation_usage |
                        state_usage |
                        constraint_usage |
                        requirement_usage |
                        concern_usage |
                        case_usage |
                        analysis_case_usage |
                        verification_case_usage |
                        use_case_usage |
                        viewpoint_usage |
                        perform_action_usage |
                        exhibit_state_usage |
                        include_use_case_usage |
                        assert_constriant_usage |
                        satisfy_requirement_usage;
variant_usage_element: variant_reference |
                       reference_usage |
                       attribute_usage |
                       binding_connector_as_usage |
                       succession_as_usage |
                       occurrence_usage |
                       individual_usage |
                       portion_usage |
                       event_occurrence_usage |
                       item_usage |
                       part_usage |
                       view_usage |
                       rendering_usage |
                       port_usage |
                       connection_usage |
                       interface_usage |
                       allocation_usage |
                       message |
                       flow_usage |
                       succession_flow_usage |
                       behavior_usage_element;

subsclassification_part: SPECIALIZES owned_subclassification (SYMBOL_COMMA owned_subclassification)*;

crosses: CROSSES owned_cross_subsetting;
owned_cross_subsetting: qualified_name | owned_feature_chain;
multiplicity_part: owned_multiplicity (KEYWORD_ORDERED? KEYWORD_NONUNIQUE? | KEYWORD_NONUNIQUE KEYWORD_ORDERED?);
owned_multiplicity: multiplicity_range;
multiplicity_range: SYMBOL_SQUARE_BRACKET_OPEN (multiplicity_expression_member SYMBOL_DDOT)? multiplicity_expression_member SYMBOL_SQUARE_BRACKET_CLOSE;

attribute_definition: definition_prefix KEYWORD_ATTRIBUTE KEYWORD_DEF definition;
attribute_usage: usage_prefix KEYWORD_ATTRIBUTE usage;

enumeration_definition: definition_extension_keyword* KEYWORD_ENUM KEYWORD_DEF definition_declaration enumeration_body;
enumeration_body: SYMBOL_STATEMENT_DELIMITER | (SYMBOL_CURLY_BRACKET_OPEN (annotating_member|enumeration_usage_member)* SYMBOL_CURLY_BRACKET_CLOSE);
enumeration_usage_member: member_prefix enumerated_value;
enumerated_value: KEYWORD_ENUM? usage;
enumeration_usage: usage_prefix KEYWORD_ENUM usage;

occurrence_definition_prefix: basic_definition_prefix? KEYWORD_INDIVIDIAL? definition_extension_keyword*;
occurrence_definition: occurrence_definition_prefix KEYWORD_OCCURRENCE KEYWORD_DEF definition;
individual_definition: basic_definition_prefix? KEYWORD_INDIVIDIAL KEYWORD_DEF definition;

occurrence_usage_prefix: basic_usage_prefix KEYWORD_INDIVIDIAL? portion_kind? usage_extention_keyword*;
occurrence_usage: occurrence_usage_prefix KEYWORD_OCCURRENCE usage;
individual_usage: basic_usage_prefix KEYWORD_INDIVIDIAL portion_kind? usage_extention_keyword* usage;
portion_usage: basic_usage_prefix KEYWORD_INDIVIDIAL? portion_kind usage_extention_keyword* usage;
portion_kind: KEYWORD_SNAPSHOT | KEYWORD_TIMESLICE;
event_occurrence_usage: occurrence_usage_prefix KEYWORD_EVENT ((owned_reference_subsetting feature_specialization_part?)|(KEYWORD_OCCURRENCE usage_declaration)) usage_completion;

source_succession_member: KEYWORD_THEN souce_succession;
souce_succession: source_end_member;
source_end_member: source_end;
source_end: owned_multiplicity?;

item_definition: occurrence_definition_prefix KEYWORD_ITEM KEYWORD_DEF definition;
item_usage: occurrence_usage_prefix KEYWORD_ITEM usage;

part_definition: occurrence_definition_prefix KEYWORD_PART KEYWORD_DEF definition;
part_usage: occurrence_usage_prefix KEYWORD_PART usage;

port_definition: definition_prefix KEYWORD_PORT KEYWORD_DEF definition;
port_usage: occurrence_usage_prefix KEYWORD_PORT usage;
conjungated_port_typing: SYMBOL_CONJUNGATES qualified_name;

connection_definition: occurrence_definition_prefix KEYWORD_CONNECTION KEYWORD_DEF definition;
connection_usage: occurrence_usage_prefix ((KEYWORD_CONNECTION usage_declaration value_part? (KEYWORD_CONNECT connector_part)?)| (KEYWORD_CONNECT connector_part)) usage_body;
connector_part: binary_connector_part | nary_connector_part;
binary_connector_part: connector_end_member KEYWORD_TO connector_end_member;
nary_connector_part: SYMBOL_ROUND_BRACKET_OPEN connector_end_member (SYMBOL_COMMA connector_end_member)+ SYMBOL_ROUND_BRACKET_CLOSE;
connector_end_member: connector_end;
connecotr_end: owned_cross_multiplicity_member? (declared_name = NAME REFERENCES)? owned_reference_subsetting;
owned_cross_multiplicity_member: owned_cross_multiplicity;
owned_cross_multiplicity: owned_multiplicity;

binding_connector_as_usage: usage_prefix (KEYWORD_BINDING usage_declaration)? KEYWORD_BIND connector_end_member SYMBOL_ASSIGN connector_end_member usage_body;
succession_as_usage: usage_prefix (KEYWORD_SUCCSESSION usage_declaration)? KEYWORD_FIRST connector_end_member KEYWORD_THEN connector_end_member usage_body;

interface_definition: occurrence_definition_prefix KEYWORD_INTERFACE KEYWORD_DEF definition_declaration interface_body;
interface_body: SYMBOL_STATEMENT_DELIMITER | (SYMBOL_CURLY_BRACKET_OPEN interface_body_item* SYMBOL_CURLY_BRACKET_CLOSE);
interface_body_item: definition_member |
                     variant_usage_member |
                     interface_non_occurrence_usage_member source_succession_member? |
                     interface_occurrence_usage_member |
                     alias_member |
                     namespace_import;
interface_non_occurrence_usage_member: member_prefix interface_non_occurrence_usage_element;
interface_non_occurrence_usage_element: reference_usage |
                                        attribute_usage |
                                        enumeration_usage |
                                        binding_connector_as_usage |
                                        succession_as_usage;
interface_occurrence_usage_member: member_prefix interface_occurrence_usage_element;
interface_occurrence_usage_element: default_interface_end | structure_usage_element | behavior_usage_element;
default_interface_end: KEYWORD_END usage;

interface_usage: occurrence_usage_prefix KEYWORD_INTERFACE interface_usage_declaration interface_body;
interface_usage_declaration: usage_declaration value_part? (KEYWORD_CONNECT interface_part)? | interface_part;
interface_part: binary_interface_part | nary_interface_part;
binary_interface_part: interface_end_member KEYWORD_TO interface_end_member;
nary_interface_part: SYMBOL_ROUND_BRACKET_OPEN interface_end_member (SYMBOL_COMMA interface_end_member)+ SYMBOL_ROUND_BRACKET_CLOSE;
interface_end_member: interface_end;
interface_end: owned_cross_multiplicity_member? (declared_name=NAME REFERENCES)? owned_reference_subsetting;

allocation_definition: occurrence_definition_prefix KEYWORD_ALLOCATION KEYWORD_DEF definition;
allocation_usage: occurrence_usage_prefix allocation_usage_declaration usage_body;
allocation_usage_declaration: KEYWORD_ALLOCATION usage_declaration (KEYWORD_ALLOCATION connector_part)? | KEYWORD_ALLOCATE connector_part;

flow_definition: occurrence_definition_prefix KEYWORD_FLOW KEYWORD_DEF definition;
message: occurrence_usage_prefix KEYWORD_MESSAGE message_declaration definition_body;
message_declaration: usage_declaration value_part? (KEYWORD_OF flow_payload_feature_member)? (KEYWORD_FROM message_event_member KEYWORD_TO message_event_member)? | message_event_member KEYWORD_TO message_event_member;
message_event_member: message_event;
message_event: owned_reference_subsetting;
flow_usage: occurrence_usage_prefix KEYWORD_FLOW flow_declaration definition_body;
succession_flow_usage: occurrence_usage_prefix KEYWORD_SUCCSESSION KEYWORD_FLOW flow_declaration definition_body;
flow_declaration: usage_declaration value_part? (KEYWORD_OF flow_payload_feature_member)? (KEYWORD_OF flow_end_member KEYWORD_TO flow_end_member)? | flow_end_member KEYWORD_TO flow_end_member;
flow_payload_feature_member: flow_payload_feature;
flow_payload_feature: payload_feature;
payload_feature: identification payload_feature_specialization_part value_part | owned_feature_typing | owned_multiplicity owned_feature_typing;
payload_feature_specialization_part: feature_specilization+ multiplicity_part? feature_specilization* | multiplicity_part feature_specilization+;
flow_end_member: flow_end;
flow_end: flow_end_subsetting? flow_feature_member;
flow_end_subsetting: qualified_name | feature_chain_prefix;
feature_chain_prefix: owned_feature_chaining SYMBOL_DOT (owned_feature_chaining SYMBOL_DOT)+;
flow_feature_member: flow_feature;
flow_feature: flow_feature_redefinition;
flow_feature_redefinition: qualified_name;

action_definition: occurrence_definition_prefix KEYWORD_ACTION KEYWORD_DEF definition_declaration action_body;
action_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN action_body_item* SYMBOL_CURLY_BRACKET_CLOSE;
action_body_item: non_behavior_body_item |
                  initial_node_member action_target_succession_member*|
                  source_succession_member? action_behavior_member action_target_succession_member?|
                  guarded_succession_member;
non_behavior_body_item: namespace_import |
                        alias_member |
                        definition_member |
                        variant_usage_member |
                        source_succession_member? structure_usage_member;
action_behavior_member: behavior_usage_member | action_node_member;
initial_node_member: member_prefix KEYWORD_FIRST qualified_name relationship_body;
action_node_member: member_prefix action_node;
action_target_succession_member: member_prefix action_target_succession;
guarded_succession_member: member_prefix guarded_succession;

action_usage: occurrence_usage_prefix KEYWORD_ACTION action_usage_declaration action_body;
action_usage_declaration: usage_declaration value_part?;
perform_action_usage: occurrence_usage_prefix KEYWORD_PERFORM perform_action_usage_declaration action_body;
perform_action_usage_declaration: owned_reference_subsetting feature_specialization_part? | KEYWORD_ACTION usage_declaration value_part?;
action_node: control_node |
             send_node |
             accept_node |
             assignment_node |
             terminate_node |
             if_node |
             while_loop_node |
             for_loop_node;
action_node_usage_declaration: KEYWORD_ACTION usage_declaration?;
action_node_prefix: occurrence_usage_prefix action_node_usage_declaration?;

control_node: merge_node | decision_node | join_node | fork_node;
control_node_prefix: ref_prefix KEYWORD_INDIVIDIAL? portion_kind? usage_extention_keyword?;
merge_node: control_node_prefix KEYWORD_MERGE? usage_declaration action_body;
decision_node: control_node_prefix KEYWORD_DECIDE? usage_declaration action_body;
join_node: control_node_prefix KEYWORD_DECIDE? usage_declaration action_body;
fork_node: control_node_prefix KEYWORD_FORK? usage_declaration action_body;

accept_node: occurrence_usage_prefix accept_node_declaration action_body;
accept_node_declaration: action_node_usage_declaration? KEYWORD_ACCEPT accept_parameter_part;
accept_parameter_part: payload_parameter_member (KEYWORD_VIA node_parameter_member)?;
payload_parameter_member: payload_parameter;
payload_parameter: payload_feature | identification payload_feature_specialization_part? trigger_value_part;
trigger_value_part: trigger_expression;
trigger_expression: kind=(KEYWORD_AT | KEYWORD_AFTER) argument_member | kind=KEYWORD_WHEN argument_expression_member;
send_node: occurrence_usage_prefix action_usage_declaration? KEYWORD_SEND (node_parameter_member sender_receiver_part? | sender_receiver_part)? action_body;
send_node_declaration: action_node_usage_declaration? KEYWORD_SEND  node_parameter_member sender_receiver_part?;
sender_receiver_part: KEYWORD_VIA node_parameter_member (KEYWORD_TO node_parameter_member)? | KEYWORD_TO node_parameter_member;
node_parameter_member: node_parameter;
node_parameter: feature_binding;
feature_binding: owned_expression;
assignment_node: occurrence_usage_prefix assignment_node_declaration action_body;
assignment_node_declaration: action_node_usage_declaration? KEYWORD_ASSIGN assignment_target_member feature_chain_member SYMBOL_DEF_ASSIGN node_parameter_member;
assignment_target_member: assignment_target_parameter;
assignment_target_parameter: (assignment_target_binding SYMBOL_DOT)?;
assignment_target_binding: non_feature_chain_primary_expression;
feature_chain_member: memberElement = qualified_name | owned_feature_chain;
owned_feature_chain_member: owned_feature_chain;

terminate_node: occurrence_usage_prefix action_node_usage_declaration? KEYWORD_TERMINATE node_parameter_member? action_body;

if_node: action_node_prefix KEYWORD_IF expression_parameter_member action_body_parameter_member (KEYWORD_ELSE (action_body_parameter_member | if_node_parameter_member));
expression_parameter_member: owned_expression;
action_body_parameter_member: action_body_parameter;
action_body_parameter: (KEYWORD_ACTION usage_declaration?)? SYMBOL_CURLY_BRACKET_OPEN action_body_item* SYMBOL_CURLY_BRACKET_CLOSE;
if_node_parameter_member: if_node;
while_loop_node: action_node_prefix (KEYWORD_WHILE expression_parameter_member | KEYWORD_LOOP ) action_body_parameter_member (KEYWORD_UNTIL expression_parameter_member SYMBOL_STATEMENT_DELIMITER);
for_loop_node: action_node_prefix KEYWORD_FOR for_variable_declaration_member KEYWORD_IN node_parameter_member action_body_parameter_member;
for_variable_declaration_member: usage_declaration;
for_variable_declaration: usage_declaration;

action_target_succession: (target_succession | guarded_target_succession | default_target_succession) usage_body;
target_succession: source_end_member KEYWORD_THEN connector_end_member;
guarded_target_succession: guard_expression_member KEYWORD_THEN transition_succession_member;
default_target_succession: KEYWORD_ELSE transition_succession_member;
guarded_succession: (KEYWORD_SUCCSESSION usage_declaration)? KEYWORD_FIRST feature_chain_member guard_expression_member KEYWORD_THEN transition_succession_member usage_body;

state_definition: occurrence_definition_prefix KEYWORD_STATE KEYWORD_DEF definition_declaration state_def_body;
state_def_body: SYMBOL_STATEMENT_DELIMITER | KEYWORD_PARALLEL? SYMBOL_CURLY_BRACKET_OPEN state_body_item SYMBOL_CURLY_BRACKET_CLOSE;
state_body_item: non_behavior_body_item |
                 source_succession_member? behavior_usage_member target_transition_usage_member* |
                 transition_usage_member |
                 entry_action_member entry_transition_member* |
                 do_action_member |
                 exit_action_member;
entry_action_member: member_prefix kind = KEYWORD_ENTRY state_action_usage;
do_action_member: member_prefix kind = KEYWORD_DO state_action_usage;
exit_action_member: member_prefix kind = KEYWORD_EXIT state_action_usage;
entry_transition_member: member_prefix (guarded_target_succession | KEYWORD_THEN target_succession) SYMBOL_STATEMENT_DELIMITER;
state_action_usage: empty_action_usage SYMBOL_STATEMENT_DELIMITER |
                    state_perform_action_uage |
                    state_accept_action_usage |
                    state_send_action_usage |
                    state_assignment_action_usage;
empty_action_usage: {};
state_perform_action_uage: perform_action_usage_declaration action_body;
state_accept_action_usage: accept_node_declaration action_body;
state_send_action_usage: send_node_declaration action_body;
state_assignment_action_usage:assignment_node_declaration action_body;
transition_usage_member: member_prefix transition_usage;
target_transition_usage_member: member_prefix target_transition_usage;

state_usage: occurrence_usage_prefix KEYWORD_STATE action_usage_declaration state_usage_body;
state_usage_body: SYMBOL_STATEMENT_DELIMITER | KEYWORD_PARALLEL? SYMBOL_CURLY_BRACKET_OPEN state_body_item* SYMBOL_CURLY_BRACKET_CLOSE; 
exhibit_state_usage: occurrence_usage_prefix KEYWORD_EXHIBIT (owned_reference_subsetting feature_specialization_part? | KEYWORD_STATE usage_declaration) value_part? state_usage_body;
               
transition_usage: KEYWORD_TRANSISTION (usage_declaration KEYWORD_FROM)? feature_chain_member trigger_action_member? guard_expression_member? effect_behavior_member? KEYWORD_THEN transition_succession_member action_body;
target_transition_usage: (KEYWORD_TRANSISTION trigger_action_member? guard_expression_member? effect_behavior_member? | trigger_action_member guard_expression_member? effect_behavior_member? | guard_expression_member effect_behavior_member?)? KEYWORD_THEN transition_succession_member action_body;
trigger_action_member: KEYWORD_ACCEPT {kind=KEYWORD_TRIGGER} trigger_action;
trigger_action: accept_parameter_part;
guard_expression_member: KEYWORD_IF {kind=KEYWORD_GUARD} owned_expression;
effect_behavior_member: KEYWORD_DO {kind=KEYWORD_TRIGGER} effect_behavior_usage;
effect_behavior_usage: empty_action_usage |
                       transition_perform_action_usage |
                       transition_accept_action_usage |
                       transition_send_action_usage |
                       transition_assignment_action_usage;
transition_perform_action_usage: perform_action_usage_declaration (SYMBOL_CURLY_BRACKET_OPEN action_body_item* SYMBOL_CURLY_BRACKET_CLOSE)?;
transition_accept_action_usage: accept_node_declaration (SYMBOL_CURLY_BRACKET_OPEN action_body_item* SYMBOL_CURLY_BRACKET_CLOSE)?;
transition_send_action_usage: send_node_declaration (SYMBOL_CURLY_BRACKET_OPEN action_body_item* SYMBOL_CURLY_BRACKET_CLOSE)?;
transition_assignment_action_usage: assignment_node_declaration (SYMBOL_CURLY_BRACKET_OPEN action_body_item* SYMBOL_CURLY_BRACKET_CLOSE)?;
transition_succession_member: transition_succession;
transition_succession: connector_end_member;

calculation_definition: occurrence_definition_prefix KEYWORD_CALC KEYWORD_DEF definition_declaration calculation_body;
calculation_usage: occurrence_usage_prefix KEYWORD_CALC action_usage_declaration calculation_body;
calculation_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN calculation_body_part SYMBOL_CURLY_BRACKET_CLOSE;
calculation_body_part: calculation_body_item* result_expression_member?;
calculation_body_item: action_body_item | return_parameter_member;
return_parameter_member: member_prefix? KEYWORD_RETURN usage_element;
result_expression_member: member_prefix? owned_expression;

constraint_definition: occurrence_definition_prefix? definition_declaration calculation_body;
constraint_usage: occurrence_usage_prefix? KEYWORD_CONSTRAINT constraint_usage_declaration calculation_body;
assert_constriant_usage: occurrence_usage_prefix KEYWORD_ASSERT KEYWORD_NOT? (owned_reference_subsetting feature_specialization_part? | KEYWORD_CONSTRAINT constraint_usage_declaration) calculation_body;
constraint_usage_declaration: usage_declaration value_part?;

requirement_definition: occurrence_definition_prefix KEYWORD_REQUIREMENT KEYWORD_DEF definition_declaration requirement_body;
requirement_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN requirement_body_item* SYMBOL_CURLY_BRACKET_CLOSE;
requirement_body_item: definition_body_item |
                       subject_member |
                       requirement_constraint_member |
                       framed_concern_member |
                       requirement_verification_member |
                       actor_member |
                       stakeholder_member;
subject_member: member_prefix subject_usage;
subject_usage: KEYWORD_SUBJECT usage_extention_keyword* usage;
requirement_constraint_member: member_prefix? requriement_kind requirement_constraint_usage;
requriement_kind: KEYWORD_ASSUME {kind = 'assumption'} | KEYWORD_REQUIRE {kind = 'requirement'}; 
requirement_constraint_usage: owned_reference_subsetting feature_specialization_part? requirement_body | (usage_extention_keyword* KEYWORD_CONSTRAINT | usage_extention_keyword+) constraint_usage_declaration calculation_body;
framed_concern_member: member_prefix? KEYWORD_FRAME framed_concern_usage;
framed_concern_usage: owned_reference_subsetting feature_specialization_part? calculation_body | (usage_extention_keyword* KEYWORD_CONSTRAINT | usage_extention_keyword+) constraint_usage_declaration calculation_body;
actor_member: member_prefix actor_usage;
actor_usage: KEYWORD_ACTOR usage_extention_keyword* usage;
stakeholder_member: member_prefix stakeholder_usage;
stakeholder_usage: KEYWORD_STAKEHOLDER usage_extention_keyword;

requirement_usage: occurrence_usage_prefix KEYWORD_REQUIREMENT constraint_usage_declaration requirement_body;
satisfy_requirement_usage: occurrence_usage_prefix KEYWORD_ASSERT KEYWORD_NOT? KEYWORD_SATISFY (owned_reference_subsetting feature_specialization_part? | KEYWORD_REQUIREMENT usage_declaration ) value_part? (KEYWORD_BY satisfaction_subject_member)? requirement_body;
satisfaction_subject_member: satisfaction_parameter;
satisfaction_parameter: satisfaction_feature_value;
satisfaction_feature_value: satisfaction_reference_expression;
satisfaction_reference_expression: feature_chain_member;

concern_definition: occurrence_definition_prefix KEYWORD_CONCERN KEYWORD_DEF definition_declaration requirement_body;
concern_usage: occurrence_usage_prefix KEYWORD_CONCERN constraint_usage_declaration requirement_body;

case_definition: occurrence_definition_prefix KEYWORD_CASE KEYWORD_DEF definition_declaration case_body;
case_usage: occurrence_usage_prefix KEYWORD_CASE constraint_usage_declaration case_body;
case_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN case_body_item* result_expression_member? SYMBOL_CURLY_BRACKET_CLOSE;
case_body_item: action_body_item |
                subject_member |
                actor_member |
                objective_member;
objective_member: member_prefix KEYWORD_OBJECTIVE objective_requirement_usage;
objective_requirement_usage: usage_extention_keyword* constraint_usage_declaration requirement_body;

analysis_case_definition: occurrence_definition_prefix KEYWORD_ANALYSIS KEYWORD_DEF definition_declaration case_body;
analysis_case_usage: occurrence_usage_prefix KEYWORD_ANALYSIS constraint_usage_declaration case_body;

verification_case_definition: occurrence_definition_prefix KEYWORD_VERIFICATION KEYWORD_DEF definition_declaration case_body;
verification_case_usage: occurrence_usage_prefix KEYWORD_VERIFICATION constraint_usage_declaration case_body;

requirement_verification_member: member_prefix KEYWORD_VERIFY {kind = 'requirement'} requirement_verification_usage;
requirement_verification_usage: owned_reference_subsetting feature_specilization* requirement_body | (usage_extention_keyword* KEYWORD_REQUIREMENT | usage_extention_keyword+) constraint_usage_declaration requirement_body;

use_case_definition: occurrence_definition_prefix KEYWORD_USE KEYWORD_CASE KEYWORD_DEF definition_declaration case_body;
use_case_usage: occurrence_usage_prefix KEYWORD_USE KEYWORD_CASE constraint_usage_declaration case_body;
include_use_case_usage: occurrence_usage_prefix KEYWORD_INCLUDE (owned_reference_subsetting feature_specialization_part? | KEYWORD_USE KEYWORD_CASE usage_declaration ) value_part? case_body;

view_definition: occurrence_definition_prefix KEYWORD_VIEW KEYWORD_DEF definition_declaration view_definition_body;
view_definition_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN view_definition_body_item* SYMBOL_CURLY_BRACKET_OPEN;
view_definition_body_item: definition_body_item |
                           element_filter_member |
                           view_rendering_member;
view_rendering_member: member_prefix KEYWORD_RENDER view_rendering_usage;
view_rendering_usage: owned_reference_subsetting feature_specialization_part? usage_body | (usage_extention_keyword* KEYWORD_RENDERING | usage_extention_keyword+) usage;

view_usage: occurrence_usage_prefix KEYWORD_VIEW usage_declaration? value_part? view_body;
view_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN view_body_item* SYMBOL_CURLY_BRACKET_CLOSE;
view_body_item: definition_body_item |
                element_filter_member |
                view_rendering_member |
                expose;
expose: KEYWORD_EXPOSE (membership_expose | namespace_expose) relationship_body;
membership_expose: membership_import;
namespace_expose: namespace_import;

viewpoint_definition: occurrence_definition_prefix KEYWORD_VIEWPOINT KEYWORD_DEF definition_declaration requirement_body;
viewpoint_usage: occurrence_usage_prefix KEYWORD_VIEWPOINT constraint_usage_declaration requirement_body;

rendering_definition: occurrence_definition_prefix KEYWORD_RENDERING KEYWORD_DEF definition;
rendering_usage: occurrence_usage_prefix KEYWORD_RENDERING usage;

metadata_definition: KEYWORD_ABSTRACT? definition_extension_keyword* KEYWORD_METADATA KEYWORD_DEF definition;
prefix_metadata_annotation: SYMBOL_HASHTAG prefix_metadata_usage annotating_element;
prefix_metadata_member: SYMBOL_HASHTAG prefix_metadata_usage;
prefix_metadata_usage: owned_feature_typing;
metadata_usage: usage_extention_keyword* (SYMBOL_AT | KEYWORD_METADATA) metadata_usage_declaration (KEYWORD_ABOUT annotation (SYMBOL_COMMA annotation)*)? metadata_body;
metadata_usage_declaration: (identification (SYMBOL_TYPED_BY | KEYWORD_TYPED KEYWORD_BY))? owned_feature_typing;
metadata_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN (definition_member | metadata_body_usage_member | alias_member | namespace_import) SYMBOL_CURLY_BRACKET_CLOSE;
metadata_body_usage_member: metadata_body_usage;
metadata_body_usage: KEYWORD_REF? REDEFINES? owned_redefinition feature_specialization_part? value_part? metadata_body;
extended_definition: basic_definition_prefix? definition_extension_keyword+ KEYWORD_DEF definition;
extended_usage: unextended_usage_prefix usage_extention_keyword+ usage;

DEFINED_BY: SYMBOL_TYPED_BY | KEYWORD_DEFINED KEYWORD_BY;
CROSSES: SYMBOL_CROSSES | KEYWORD_CROSSES;

//Keywords
KEYWORD_ACCEPT: 'accept';
KEYWORD_ACTION: 'action';
KEYWORD_ACTOR: 'actor';
KEYWORD_AFTER: 'after';
KEYWORD_ALIAS: 'alias';
KEYWORD_ALLOCATE: 'allocate';
KEYWORD_ALLOCATION: 'allocation';
KEYWORD_ANALYSIS: 'analysis';
KEYWORD_ASSIGN: 'assign';
KEYWORD_ASSERT: 'assert';
KEYWORD_ASSUME: 'assume';
KEYWORD_AT: 'at';
KEYWORD_ATTRIBUTE: 'attribute';
KEYWORD_BIND: 'bind';
KEYWORD_BLOCK: 'block';
KEYWORD_CALC: 'calc';
KEYWORD_CASE: 'case';
KEYWORD_CONCERN: 'concern';
KEYWORD_CONNECT: 'connect';
KEYWORD_CONNECTION: 'connection';
KEYWORD_CONSTRAINT: 'constraint';
KEYWORD_CROSSES: 'crosses';
KEYWORD_DECIDE: 'decide';
KEYWORD_DEF: 'def';
KEYWORD_DEFINED: 'defined';
KEYWORD_DERIVED: 'derived';
KEYWORD_DO: 'do';
KEYWORD_ENTRY: 'entry';
KEYWORD_ENUM: 'enum';
KEYWORD_EVENT: 'event';
KEYWORD_EXHIBIT: 'exhibit';
KEYWORD_EXIT: 'exit';
KEYWORD_EXPOSE: 'expose';
KEYWORD_FORK: 'fork';
KEYWORD_FRAME: 'frame';
KEYWORD_GUARD: 'guard';
KEYWORD_INCLUDE: 'include';
KEYWORD_INDIVIDIAL: 'individual';
KEYWORD_INTERFACE:'interface';
KEYWORD_ITEM: 'item';
KEYWORD_JOIN: 'join';
KEYWORD_LOOP: 'loop';
KEYWORD_MERGE: 'merge';
KEYWORD_MESSAGE: 'message';
KEYWORD_NONUNIQUE: 'nonunique';
KEYWORD_OBJECTIVE: 'objective';
KEYWORD_OCCURRENCE: 'occurrence';
KEYWORD_PARALLEL: 'parallel';
KEYWORD_PART:'part';
KEYWORD_PERFORM:'perform';
KEYWORD_PORT: 'port';
KEYWORD_REF: 'ref';
KEYWORD_REFERENCES: 'references';
KEYWORD_RENDER: 'render';
KEYWORD_RENDERING:'rendering';
KEYWORD_REQUIRE: 'require';
KEYWORD_REQUIREMENT: 'requirement';
KEYWORD_SATISFY: 'satisfy';
KEYWORD_SEND: 'send';
KEYWORD_SNAPSHOT: 'snapshot';
KEYWORD_STAKEHOLDER: 'stakeholder';
KEYWORD_STATE: 'state';
KEYWORD_SUBJECT: 'subject';
KEYWORD_TERMINATE: 'terminate';
KEYWORD_TIMESLICE: 'timeslice';
KEYWORD_TRANSISTION: 'transition';
KEYWORD_TRIGGER: 'trigger';
KEYWORD_UNTIL: 'until';
KEYWORD_USE: 'use';
KEYWORD_VARIANT: 'variant';
KEYWORD_VARIATION: 'variation';
KEYWORD_VERIFICATION: 'verification';
KEYWORD_VERIFY: 'verify';
KEYWORD_VIA: 'via';
KEYWORD_VIEW: 'view';
KEYWORD_VIEWPOINT: 'viewpoint';
KEYWORD_WHEN: 'when';
KEYWORD_WHILE: 'while';

//Symbols
SYMBOL_CROSSES: '=>';
