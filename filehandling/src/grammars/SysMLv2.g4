grammar SysMLv2;

import KerML;

start: EOF;

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


DEFINED_BY: SYMBOL_DEFINED_BY | (KEYWORD_DEFINED KEYWORD_BY);
CROSSES: SYMBOL_CROSSES | KEYWORD_CROSSES;

//Keywords
KEYWORD_ABOUT: 'about';
KEYWORD_ABSTRACT: 'abstract';
KEYWORD_ACCEPT: 'accept';
KEYWORD_ACTION: 'action';
KEYWORD_ACTOR: 'actor';
KEYWORD_AFTER: 'after';
KEYWORD_ALIAS: 'alias';
KEYWORD_ALL: 'all';
KEYWORD_ALLOCATE: 'allocate';
KEYWORD_ALLOCATION: 'allocation';
KEYWORD_ANALYSIS: 'analysis';
KEYWORD_AND: 'and';
KEYWORD_AS: 'as';
KEYWORD_ASSIGN: 'assign';
KEYWORD_ASSERT: 'assert';
KEYWORD_ASSOC: 'assoc';
KEYWORD_ASSUME: 'assume';
KEYWORD_AT: 'at';
KEYWORD_ATTRIBUTE: 'attribute';
KEYWORD_BIND: 'bind';
KEYWORD_BINDING: 'binding';
KEYWORD_BLOCK: 'block';
KEYWORD_BY: 'by';
KEYWORD_CALC: 'calc';
KEYWORD_CASE: 'case';
KEYWORD_COMMENT: 'comment';
KEYWORD_CONCERN: 'concern';
KEYWORD_CONNECT: 'connect';
KEYWORD_CONNECTION: 'connection';
KEYWORD_CONSTRAINT: 'constraint';
KEYWORD_CROSSES: 'crosses';
KEYWORD_DECIDE: 'decide';
KEYWORD_DEF: 'def';
KEYWORD_DEFAULT: 'default';
KEYWORD_DEFINED: 'defined';
KEYWORD_DEPENDENCY: 'dependency';
KEYWORD_DERIVED: 'derived';
KEYWORD_DO: 'do';
KEYWORD_DOC: 'doc';
KEYWORD_ELSE: 'else';
KEYWORD_END:'end';
KEYWORD_ENTRY: 'entry';
KEYWORD_ENUM: 'enum';
KEYWORD_EVENT: 'event';
KEYWORD_EXHIBIT: 'exhibit';
KEYWORD_EXIT: 'exit';
KEYWORD_EXPOSE: 'expose';
KEYWORD_FILTER: 'filter';
KEYWORD_FIRST: 'first';
KEYWORD_FLOW: 'flow';
KEYWORD_FOR: 'for';
KEYWORD_FORK: 'fork';
KEYWORD_FRAME: 'frame';
KEYWORD_FROM: 'from';
KEYWORD_HASTYPE: 'hastype';
KEYWORD_IF: 'if';
KEYWORD_IMPLIES: 'implies';
KEYWORD_IMPORT: 'import';
KEYWORD_IN:'in';
KEYWORD_INCLUDE: 'include';
KEYWORD_INDIVIDIAL: 'individual';
KEYWORD_INOUT: 'inout';
KEYWORD_INTERFACE:'interface';
KEYWORD_ISTYPE: 'istype';
KEYWORD_ITEM: 'item';
KEYWORD_JOIN: 'join';
KEYWORD_LANGUAGE: 'language';
KEYWORD_LOOP: 'loop';
KEYWORD_MERGE: 'merge';
KEYWORD_MESSAGE: 'message';
KEYWORD_METADADA: 'metadata';
KEYWORD_NONUNIQUE: 'nonunique';
KEYWORD_NOT: 'not';
KEYWORD_OBJECTIVE: 'objective';
KEYWORD_OCCURRENCE: 'occurrence';
KEYWORD_OF: 'of';
KEYWORD_OR: 'or';
KEYWORD_ORDERED: 'ordered';
KEYWORD_OUT: 'out';
KEYWORD_PACKAGE:'package';
KEYWORD_PARALLEL: 'parallel';
KEYWORD_PART:'part';
KEYWORD_PERFORM:'perform';
KEYWORD_PORT: 'port';
KEYWORD_PRIVATE: 'private';
KEYWORD_PROTECTED: 'protected';
KEYWORD_PUBLIC:'public';
KEYWORD_READONLY:'readonly';
KEYWORD_REFINES:'redefines';
KEYWORD_REF: 'ref';
KEYWORD_REFERENCES: 'references';
KEYWORD_REDER: 'render';
KEYWORD_RENDERING:'rendering';
KEYWORD_REP:'rep';
KEYWORD_REQUIRE: 'require';
KEYWORD_REQUIREMENT: 'requirement';
KEYWORD_RETURN:'return';
KEYWORD_SATISFY: 'satisfy';
KEYWORD_SEND: 'send';
KEYWORD_SNAPSHOT: 'snapshot';
KEYWORD_SPECIALIZES: 'specializes';
KEYWORD_STAKEHOLDER: 'stakeholder';
KEYWORD_STATE: 'state';
KEYWORD_SUBJECT: 'subject';
KEYWORD_SUBSETS: 'subsets';
KEYWORD_SUCCESSION: 'succession';
KEYWORD_TERMINATE: 'terminate';
KEYWORD_THEN: 'then';
KEYWORD_TIMESLICE: 'timeslice';
KEYWORD_TO: 'to';
KEYWORD_TRANSISTION: 'transition';
KEYOWRD_UNTIL: 'until';
KEYWORD_USE: 'use';
KEYWORD_VARIANT: 'variant';
KEYWORD_VARIATION: 'variation';
KEYWORD_VERIFICATION: 'verification';
KEYWORD_VERIFY: 'verify';
KEYWORD_VIA: 'via';
KEYWORD_VIEW: 'view';
KEYWORD_VIEWPOINT: 'viewpoint';
KEYWORD_WHEN: 'when';
KEYOWRD_WHILE: 'while';
KEYWORD_XOR: 'xor';

//Symbols
SYMBOL_DEFINED_BY: ':';
SYMBOL_CROSSES: '=>';