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
                    convern_definition |
                    state_definitin |
                    constraint_definition |
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
definition_declaration: identification subclassification_part?;
definition_body: SYMBOL_STATEMENT_DELIMITER | (SYMBOL_CURLY_BRACKET_OPEN definition_body_item* SYMBOL_CURLY_BRACKET_CLOSE);
definition_body_item: definition_member |
                      variant_usage_member |
                      non_occurrence_usage_member |
                      source_succession_member? occurrence_usage_member |
                      alias_member |
                      namespace_import;
definition_member: member_prefix definition_element;
variant_usage_member: member_prefix KEYWORD_VARIANT variant_membership;
non_occurrence_usage_member: member_prefix non_occurrence_usage_element;
occurrence_usage_member: member_prefix occurrence_usage_element;
structure_usage_member: member_prefix structure_usage_element;
behavior_usage_member: member_prefix behavior_usage_element;

feature_direction: KEYWORD_IN | KEYWORD_OUT | KEYWORD_INOUT;
ref_prefix: feature_direction? KEYWORD_DERIVED? (KEYWORD_VARIATION | KEYWORD_CONSTANT | KEYWORD_ABSTRACT KEYWORD_CONSTANT?)?;
basic_usage_prefix: ref_prefix KEYWORD_REF?;
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
                        stage_usage |
                        constraint_usage |
                        requirement_usage |
                        concern_usage |
                        case_usage |
                        analysis_case_usage |
                        verification_case_usage |
                        use_case_usage |
                        view_point_usage |
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
potion_kind: KEYWORD_SNAPSHOT | KEYWORD_TIMESLICE;
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
binary_interface_part: interface_end_member: KEYWORD_TO interface_end_member;
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
flow_declaration: usage_declaration value_part? (KEYWORD_OF flow_payload_feature_member)? (KEYWORD_OF flow_end_member KEYWORD_TO flow_end_member)? | flow_end_member KEYWORD_TO flow_end_member;
flow_payload_feature_member: flow_payload_feature;
flow_payload_feature: payload_feature;

DEFINED_BY: SYMBOL_DEFINED_BY | (KEYWORD_DEFINED KEYWORD_BY);
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
KEYWORD_REDER: 'render';
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
SYMBOL_DEFINED_BY: ':';
SYMBOL_CROSSES: '=>';
