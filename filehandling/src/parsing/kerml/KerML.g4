/**
 * Implementation of the KerML Beta 2 Standard for ANTLR 4 Parsing.
 * @author Moritz Herzog
 * The internal assignments of the values is not done in the ANTLR4 grammar. This needs to be done later on in the code.
 **/

grammar KerML;

start: elements EOF;

startRule: start;

elements: element*;

identification: ('<' NAME '>')? | (NAME)?;
relationship_body: SYMBOL_STATEMENT_DELIMITER | (SYMBOL_CURLY_BRACKET_OPEN relationship_onwed_elements SYMBOL_CURLY_BRACKET_CLOSE);
relationship_onwed_elements: elements;
relationship_owned_element: owned_related_element | owned_annotation;
owned_related_element: non_feature_element | feature_element;
dependency: (prefix_metadata_annotation)* KEYWORD_DEPENDENCY (identification KEYWORD_FROM)? qualified_name (SYMBOL_COMMA qualified_name)* KEYWORD_TO qualified_name (SYMBOL_COMMA qualified_name)* relationship_body;

annotation: qualified_name;
owned_annotation: annotating_element;
annotating_element: comment | documentation | textual_representation | metadata_feature;
comment: (KEYWORD_COMMENT identification (KEYWORD_ABOUT annotation (SYMBOL_COMMA  annotation)*)?)? ('locale' STRING_VALUE)? REGULAR_COMMENT;
documentation: KEYWORD_DOC identification ('locale' STRING_VALUE)? REGULAR_COMMENT;
textual_representation: (KEYWORD_REP identification)? KEYWORD_LANGUAGE STRING_VALUE REGULAR_COMMENT;

root_namespace: namespace_body_elements;
namespace: (prefix_metadata_member)* namespace_declaration namespace_body;
namespace_declaration: KEYWORD_NAMESPACE identification;
namespace_body: SYMBOL_STATEMENT_DELIMITER | (SYMBOL_CURLY_BRACKET_OPEN namespace_body_element SYMBOL_CURLY_BRACKET_CLOSE);
namespace_body_elements: elements;
namespace_body_element: namespace_member | alias_member | namespace_import;
member_prefix: (visibility_indicator)?;
visibility_indicator: KEYWORD_PUBLIC | KEYWORD_PRIVATE | KEYWORD_PROTECTED;
namespace_member: non_feature_member | namespace_feature_member;
non_feature_member: member_prefix non_feature_element;
namespace_feature_member: member_prefix feature_element;
alias_member: member_prefix KEYWORD_ALIAS (SYMBOL_SMALLER NAME SYMBOL_GREATER)? (NAME)? KEYWORD_FOR qualified_name relationship_body;
qualified_name: (NAME SYMBOL_NAMESPACE_SUBSET)* NAME;

namespace_import: visibility_indicator? KEYWORD_IMPORT KEYWORD_ALL? import_declaration relationship_body?;
import_declaration: membership_import | namespace_import;
membership_import: qualified_name (SYMBOL_NAMESPACE_SUBSET? (SYMBOL_DOUBLE_STAR|SYMBOL_STAR)?);
filter_package: import_declaration filter_package_member;
filter_package_member: SYMBOL_SQUARE_BRACKET_OPEN owned_expression SYMBOL_SQUARE_BRACKET_CLOSE;

element: annotating_element | non_feature_element | feature_element | additional_options;

non_feature_element: dependency |
                    type |
                    classifier |
                    data_type |
                    namespace |
                    class |
                    structure |
                    metaclass |
                    association |
                    association_structure |
                    interaction |
                    behavior |
                    function |
                    predicate |
                    multiplicity |
                    package |
                    library_package |
                    specialization |
                    conjunction |
                    subclassification |
                    disjoining |
                    feature_inverting |
                    feature_typing |
                    subsetting |
                    redefinition |
                    type_featuring |
                    namespace_import;

feature_element: feature |
                 step |
                 expression |
                 boolean_expression |
                 invariant |
                 connector |
                 binding_connector |
                 succession |
                 item_flow |
                 succession_item_flow;

additional_options: meta_assignment;

type: type_prefix KEYWORD_TYPE type_declaration type_body;
type_prefix: KEYWORD_ABSTRACT? prefix_metadata_member*;
type_declaration: KEYWORD_ALL? identification owned_multiplicity? (specialization_part | conjugation_part)+ type_relationship_part*;
specialization_part: SPECIALIZES owned_specialization (SYMBOL_COMMA owned_specialization)*;
conjugation_part: CONJUNGATES owned_conjugation;
type_relationship_part: disjoining_part | unioning_part | intersecting_part | differencing_part;
disjoining_part: KEYWORD_DISJOINT KEYWORD_FROM owned_disjoining (SYMBOL_COMMA owned_disjoining)*;
unioning_part: KEYWORD_UNIONS unioning (SYMBOL_COMMA unioning)*;
intersecting_part: KEYWORD_INTERSECTS intersecting (SYMBOL_COMMA intersecting)*;
differencing_part: KEYWORD_DIFFERENCES differencing (SYMBOL_COMMA differencing)*;
type_body: SYMBOL_STATEMENT_DELIMITER | (SYMBOL_CURLY_BRACKET_OPEN type_body_elements SYMBOL_CURLY_BRACKET_CLOSE);
type_body_elements: elements;
type_body_element: non_feature_element | feature_element | alias_member | namespace_import;

specialization: (KEYWORD_SPECILIZATION identification)? KEYWORD_SUBTYPE specific_type SPECIALIZES general_type relationship_body;
owned_specialization: general_type;
specific_type: qualified_name | owned_feature_chain;
general_type: qualified_name | owned_feature_chain;

conjunction: (KEYWORD_CONJUGATION identification)? KEYWORD_CONJUGATE (qualified_name | feature_chain) CONJUNGATES (qualified_name | feature_chain) relationship_body;
owned_conjugation: qualified_name | feature_chain;

disjoining: (KEYWORD_DISJOINING identification)? KEYWORD_DISJOINT (qualified_name | feature_chain) KEYWORD_FROM (qualified_name | feature_chain) relationship_body;
owned_disjoining: qualified_name | feature_chain;

unioning: qualified_name | owned_feature_chain;
intersecting: qualified_name | owned_feature_chain;
differencing: qualified_name | owned_feature_chain;

feature_member: type_feature_member | owned_feature_member;
type_feature_member: member_prefix KEYWORD_MEMBER feature_element;
owned_feature_member: member_prefix feature_element;

classifier: type_prefix KEYWORD_CLASSIFIER classifier_declaration type_body;
classifier_declaration: KEYWORD_ALL? identification owned_multiplicity? (superclassing_part | conjugation_part)? type_relationship_part*;
superclassing_part: SPECIALIZES owned_subclassification (SYMBOL_COMMA owned_subclassification)*;
subclassification: (KEYWORD_SPECILIZATION identification)? KEYWORD_SUBCLASSIFIER qualified_name SPECIALIZES qualified_name relationship_body;
owned_subclassification: qualified_name;

feature: feature_prefix ((KEYWORD_FEATURE feature_declaration) | KEYWORD_FEATURE | prefix_metadata_member);
feature_prefix: (feature_direction)? KEYWORD_ABSTRACT? (KEYWORD_COMPOSITE | KEYWORD_PORTION)? KEYWORD_READONLY? KEYWORD_DERIVED? KEYWORD_END? prefix_metadata_member*;
feature_direction: (KEYWORD_IN | KEYWORD_OUT | KEYWORD_INOUT);
feature_declaration: KEYWORD_ALL? (feature_identification (feature_specialization_part | conjugation_part)? | feature_specialization_part | conjugation_part) feature_relationship_part*;
feature_identification: SYMBOL_SMALLER NAME SYMBOL_GREATER (NAME)? | NAME;
feature_relationship_part: type_relationship_part | chaining_part | inverting_part | type_featuring_part;
chaining_part: KEYWORD_CHAINS owned_feature_chaining | feature_chain;
inverting_part: KEYWORD_INVERSE KEYWORD_OF owned_feature_inverting;
type_featuring_part: KEYWORD_FEATURED KEYWORD_BY owned_type_featuring (SYMBOL_COMMA owned_type_featuring)*;
feature_specialization_part: feature_specilization+ multiplicity_part feature_specilization* | multiplicity_part feature_specilization+;
multiplicity_part: owned_multiplicity | owned_multiplicity? ((KEYWORD_ORDERED KEYWORD_NONUNIQUE?)?|(KEYWORD_NONUNIQUE? KEYWORD_ORDERED)?);
feature_specilization: typings | subsettings | references | redefinitions;
typings: typed_by (SYMBOL_COMMA owned_feature_typing)*;
typed_by: TYPED_BY owned_feature_typing;
subsettings: subsets (SYMBOL_COMMA owned_subsetting)*;
subsets: SUBSETS owned_subsetting;
references: REFERENCES owned_reference_subsetting;
redefinitions: redefines (SYMBOL_COMMA owned_redefinition);
redefines: REDEFINES owned_redefinition;

feature_typing: (KEYWORD_SPECILIZATION identification)? KEYWORD_TYPING? qualified_name TYPED_BY general_type multiplicity_part? relationship_body;
owned_feature_typing: general_type;

subsetting: (KEYWORD_SPECILIZATION identification)? KEYWORD_SUBSET? specific_type SUBSETS general_type multiplicity_part? relationship_body;
owned_subsetting: general_type;
owned_reference_subsetting: general_type;

redefinition: (KEYWORD_SPECILIZATION identification)? KEYWORD_REDEFINITION? specific_type REDEFINES general_type multiplicity_part? relationship_body;
owned_redefinition: general_type;

owned_feature_chain: feature_chain;
feature_chain: owned_feature_chaining (SYMBOL_DOT owned_feature_chaining);
owned_feature_chaining: qualified_name;

feature_inverting: (KEYWORD_INVERTING identification)? KEYWORD_INVERSE (qualified_name | owned_feature_chain) KEYWORD_OF (qualified_name | owned_feature_chain) relationship_body;
owned_feature_inverting: qualified_name | owned_feature_chain;

type_featuring: KEYWORD_FEATURING (identification KEYWORD_OF)? qualified_name KEYWORD_BY qualified_name relationship_body;
owned_type_featuring: qualified_name;

data_type: type_prefix KEYWORD_DATATYPE classifier_declaration type_body;

class: type_prefix KEYWORD_CLASS classifier_declaration type_body;

structure: type_prefix KEYWORD_STRUCT classifier_declaration type_body;

association: type_prefix KEYWORD_ASSOC classifier_declaration type_body;
association_structure: type_prefix KEYWORD_ASSOC KEYWORD_STRUCT classifier_declaration type_body;

connector: feature_prefix KEYWORD_CONNECTOR (feature_declaration? value_part? | connector_declaration) type_body;
connector_declaration: binary_connector_declaration | nary_connector_declaration;
binary_connector_declaration: (feature_declaration? KEYWORD_FROM | KEYWORD_ALL KEYWORD_FROM?)? connector_end_member KEYWORD_TO connector_end_member;
nary_connector_declaration: feature_declaration? SYMBOL_ROUND_BRACKET_OPEN connector_end_member SYMBOL_COMMA connector_end_member (SYMBOL_COMMA connector_end_member)* SYMBOL_ROUND_BRACKET_CLOSE;
connector_end_member: connector_end;
connector_end: (NAME REFERENCES)? owned_reference_subsetting owned_multiplicity?;

binding_connector: feature_prefix KEYWORD_BINDING binding_connector_declaration type_body;
binding_connector_declaration: feature_declaration (KEYWORD_OF connector_end_member SYMBOL_EQUALS connector_end_member)? | (KEYWORD_ALL? (KEYWORD_OF? connector_end_member SYMBOL_EQUALS connector_end_member)?);

succession: feature_prefix KEYWORD_SUCCSESSION succession_declaration type_body;
succession_declaration: feature_declaration (KEYWORD_FIRST connector_end_member KEYWORD_THEN connector_end_member)? | ((KEYWORD_ALL)? (KEYWORD_FIRST? connector_end_member KEYWORD_THEN connector_end_member)?);

behavior: type_prefix KEYWORD_BEHAVIOR classifier_declaration type_body;

step: feature_prefix KEYWORD_STEP feature_declaration value_part? type_body;

function: type_prefix KEYWORD_FUNCTION classifier_declaration function_body;
function_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN function_body_part SYMBOL_CURLY_BRACKET_CLOSE;
function_body_part: (type_body_element | return_feature_member)+ (result_expression_member)?;
return_feature_member: member_prefix KEYWORD_RETURN feature_element;
result_expression_member: member_prefix owned_expression;

expression: feature_prefix KEYWORD_EXPR feature_declaration value_part? function_body;

predicate: type_prefix KEYWORD_PREDICATE classifier_declaration function_body;

boolean_expression: feature_prefix KEYWORD_BOOL feature_declaration value_part? function_body;
invariant: feature_prefix KEYWORD_INV (KEYWORD_TRUE | KEYWORD_FALSE)? feature_declaration value_part? function_body;

owned_expression_reference_member: owned_expression_reference;
owned_expression_reference: owned_expression_member;
owned_expression_member: owned_expressions;
owned_expressions: owned_expression+;
owned_expression: conditional_expression |
                  conditional_binary_operator_expression |
                  binary_operator_expression |
                  unary_operator_expression |
                  classification_expression |
                  metaclassification_expression |
                  extend_expression |
                  primary_expression;
conditional_expression: KEYWORD_IF /*argument_member*/ SYMBOL_QUESTION argument_expression_member KEYWORD_ELSE argument_expression_member;
conditional_binary_operator_expression: /*argument_member*/ conditional_binary_operator argument_expression_member;
conditional_binary_operator: SYMBOL_DQUESTION | KEYWORD_OR | KEYWORD_AND | KEYWORD_IMPLIES;
binary_operator_expression:  /*argument_member*/ binary_operator owned_expressions;
binary_operator: SYMBOL_VERTICAL_LINE | SYMBOL_AND | KEYWORD_XOR | SYMBOL_DDOT | SYMBOL_EQUALS | SYMBOL_NOT_EQUALS | SYMBOL_IFF_EQUALS | SYMBOL_IFF_NOT_EQUALS | SYMBOL_GREATER | SYMBOL_SMALLER | SYMBOL_GREATER_EQUALS | SYMBOL_SMALLER_EQUAL | SYMBOL_PLUS | SYMBOL_MINUS | SYMBOL_STAR | SYMBOL_SLASH | SYMBOL_MOD | SYMBOL_UPPER | SYMBOL_DOUBLE_STAR;
unary_operator_expression: unary_operator owned_expressions;
unary_operator: SYMBOL_PLUS | SYMBOL_MINUS | SYMBOL_CONJUNGATES | KEYWORD_NOT;
classification_expression: /*argument_member?*/((classification_test_operator type_reference_member)|(cast_operator type_result_member));
classification: /*argument_member?*/ (classification_test_operator type_reference_member)|(cast_operator type_result_member);
classification_test_operator: KEYWORD_ISTYPE | KEYWORD_HASTYPE | SYMBOL_AT;
cast_operator: KEYWORD_AS;
metaclassification_expression: metadata_argument_member (metadataclassification_test_operator type_reference_member) | (meta_cast_operator type_result_member);
//argument_member: argument;
//argument: argument_value;
//argument_value: owned_expression;
argument_expression_member: argument_expression;
argument_expression: argument_expression_value;
argument_expression_value: owned_expression_reference;
metadata_argument_member: metadata_argument;
metadata_argument: metadata_value;
metadata_value: metadata_reference;
metadata_reference: qualified_name;
metadataclassification_test_operator: SYMBOL_DOT;
meta_cast_operator: 'meta';
extend_expression: KEYWORD_ALL type_reference_member;
type_reference_member: type_reference;
type_result_member: type_reference;
type_reference: reference_typing;
reference_typing: qualified_name;

primary_expressions: primary_expression+;
primary_expression: feature_chain_expression | non_feature_chain_primary_expression;
//primary_argument_value: primary_expression;
//primary_argument: primary_argument_value;
//primary_argument_member: primary_argument;
non_feature_chain_primary_expression: bracket_expression |
                                index_expression |
                                sequence_expression |
                                select_expression |
                                collect_expression |
                                function_operation_expression |
                                base_expression;
non_feature_chain_primary_argument_value: non_feature_chain_primary_expression;
//non_feature_chain_primary_argument: primary_argument;
//non_feature_chain_primary_argument_member: primary_argument;
bracket_expression: SYMBOL_SQUARE_BRACKET_OPEN sequence_expression_list_member SYMBOL_SQUARE_BRACKET_CLOSE;
index_expression: SYMBOL_HASHTAG SYMBOL_ROUND_BRACKET_OPEN sequence_expression_list_member SYMBOL_ROUND_BRACKET_CLOSE;
sequence_expression: SYMBOL_ROUND_BRACKET_OPEN sequence_expression_list SYMBOL_ROUND_BRACKET_CLOSE;
sequence_expression_list: owned_expressions SYMBOL_COMMA? | sequence_operator_expression;
sequence_operator_expression: owned_expression_member SYMBOL_COMMA sequence_expression_list_member;
sequence_expression_list_member: sequence_expression_list;
feature_chain_expression: SYMBOL_DOT feature_chain_member;
collect_expression: SYMBOL_DOT body_expression_member;
select_expression: SYMBOL_DOT_QUESTION body_expression_member;
function_operation_expression: '->' reference_typing (body_argument_member |function_reference_argument_member | argument_expression);
body_argument_member: body_argument;
body_argument: body_argument_value;
body_argument_value: body_expression;
body_expression_member: body_expression;
function_reference_argument_member: function_reference_argument;
function_reference_argument: function_reference_member;
function_reference_arugment_value: function_reference_expression;
function_reference_expression: reference_typing;
function_reference_member: function_reference;
function_reference:  reference_typing;
feature_chain_member: feature_reference_member | owned_feature_chain_member;
owned_feature_chain_member: feature_chain;

base_expression: null_expression |
                 literal_expression |
                 feature_reference_expression |
                 metadata_access_expression |
                 invocation_expression |
                 body_expression;
null_expression: KEYWORD_NULL | SYMBOL_ROUND_BRACKET_OPEN SYMBOL_ROUND_BRACKET_CLOSE;
feature_reference_expression: feature_reference_member;
feature_reference_member: feature_reference;
feature_reference: qualified_name;

metadata_access_expression: qualified_name SYMBOL_DOT KEYWORD_METADATA;
invocation_expression: internal_invocation_expression;
internal_invocation_expression: (owned_feature_typing | named_argument_list) argument_list;
argument_list: SYMBOL_ROUND_BRACKET_OPEN (owned_expressions positional_argument_list | named_argument_list)? SYMBOL_ROUND_BRACKET_CLOSE;
positional_argument_list: /*argument_member*/ (SYMBOL_COMMA owned_expressions)*;
named_argument_list: named_argument_member (SYMBOL_COMMA named_argument_member)*;
named_argument_member: named_argument;
named_argument: paramenter_redefinition SYMBOL_EQUALS owned_expressions;
paramenter_redefinition: qualified_name;
body_expression: expression_body_member;
expression_body_member: expression_body;
expression_body: SYMBOL_ROUND_BRACKET_OPEN function_body_part SYMBOL_ROUND_BRACKET_CLOSE;

literal_expression: literal_boolean |
                    literal_string |
                    literal_integer |
                    literal_real |
                    literal_integer |
                    literal_infinity;
literal_boolean: boolean_value;
boolean_value:  (KEYWORD_TRUE | KEYWORD_FALSE);
literal_string: STRING_VALUE;
literal_integer: DECIMAL_VALUE;
literal_real: real_value;
real_value: (DECIMAL_VALUE? SYMBOL_DOT (DECIMAL_VALUE | EXPONENTIAL_VALUE)) | EXPONENTIAL_VALUE;
literal_infinity: SYMBOL_STAR;

interaction: type_prefix KEYWORD_INTERACTION classifier_declaration type_body;

item_flow: feature_prefix KEYWORD_FLOW item_flow_declaration type_body;
succession_item_flow: feature_prefix KEYWORD_SUCCSESSION KEYWORD_FLOW item_flow_declaration type_body;
item_flow_declaration: (feature_declaration value_part? (KEYWORD_OF item_feature_member)? (KEYWORD_FROM item_flow_end_member KEYWORD_TO item_flow_end_member)? | KEYWORD_ALL? item_flow_end_member KEYWORD_TO item_flow_end_member);
item_feature_member: item_feature;
item_feature: (identification item_feature_specilization_part value_part?) | (owned_feature_typing owned_multiplicity?) | (owned_multiplicity owned_feature_typing?);
item_feature_specilization_part: feature_specilization* (multiplicity_part feature_specilization?);
item_flow_end_member: item_flow_end;
item_flow_end: (owned_reference_subsetting SYMBOL_DOT)? item_flow_feature_member;
item_flow_feature_member: item_flow_feature;
item_flow_feature: item_flow_redefinition;
item_flow_redefinition: qualified_name;

value_part: feature_value;
feature_value:(SYMBOL_EQUALS | SYMBOL_DEF_ASSIGN | KEYWORD_DEFAULT (SYMBOL_EQUALS | SYMBOL_DEF_ASSIGN)?) owned_expression;

multiplicity: multiplicity_subset | multiplicity_range;
multiplicity_subset: KEYWORD_MULTIPLICITY identification subsets type_body;
multiplicity_range: KEYWORD_MULTIPLICITY identification multiplicity_bounds type_body;
owned_multiplicity: owned_multiplicity_range;
owned_multiplicity_range: multiplicity_bounds;
multiplicity_bounds: SYMBOL_SQUARE_BRACKET_OPEN (multiplicity_expression_member SYMBOL_DDOT)? multiplicity_expression_member SYMBOL_SQUARE_BRACKET_CLOSE;
multiplicity_expression_member: internal_multiplicity_expression_member;
internal_multiplicity_expression_member: (literal_expression | feature_reference_expression);

metaclass: type_prefix KEYWORD_METACLASS classifier_declaration NAME? SPECIALIZES? NAME? type_body;
prefix_metadata_annotation: SYMBOL_HASHTAG prefix_metadata_feature;
prefix_metadata_member: SYMBOL_HASHTAG prefix_metadata_feature;
prefix_metadata_feature: owned_feature_typing;
metadata_feature: (prefix_metadata_member)* (SYMBOL_AT | KEYWORD_METADATA) metadata_feature_declaration (KEYWORD_ABOUT annotation (SYMBOL_COMMA annotation));
metadata_feature_declaration: (identification (SYMBOL_TYPED_BY | KEYWORD_TYPED KEYWORD_BY))? owned_feature_typing;
metadata_body: ';' | (SYMBOL_CURLY_BRACKET_OPEN (metadata_body_element)* SYMBOL_CURLY_BRACKET_CLOSE);
metadata_body_element: non_feature_member |
                       metadata_body_feature_member |
                       alias_member |
                       import_declaration;
metadata_body_feature_member: metadata_body_feature;
metadata_body_feature: KEYWORD_FEATURE? (SYMBOL_REDEFINES | KEYWORD_REDEFINES)? owned_redefinition feature_specialization_part? value_part? metadata_body;

package:(prefix_metadata_member)* package_declaration package_body;
library_package: ('standard')? 'library' (prefix_metadata_member)* package_declaration package_body;
package_declaration: KEYWORD_PACKAGE identification;
package_body: ';' | (SYMBOL_CURLY_BRACKET_OPEN (namespace_body_element | element_filter_member | element)+ SYMBOL_CURLY_BRACKET_CLOSE);
element_filter_member: member_prefix KEYWORD_FILTER owned_expression ';';

meta_assignment: qualified_name SYMBOL_ASSIGN 'meta' qualified_name ';';


TYPED_BY: SYMBOL_TYPED_BY | KEYWORD_TYPED KEYWORD_BY;
SPECIALIZES: SYMBOL_SPECIALIZES | KEYWORD_SPECIALIZES;
SUBSETS:  SYMBOL_SPECIALIZES | KEYWORD_SUBSETS;
REFERENCES: SYMBOL_REFERENCES | KEYWORD_REFERENCES;
REDEFINES: SYMBOL_REDEFINES | KEYWORD_REDEFINES;
CONJUNGATES: SYMBOL_CONJUNGATES | KEYWORD_CONJUGATES;


// Keywords
KEYWORD_ABOUT: 'about';
KEYWORD_ABSTRACT: 'abstract';
KEYWORD_ALIAS: 'alias';
KEYWORD_ALL: 'all';
KEYWORD_AND: 'and';
KEYWORD_AS: 'as';
KEYWORD_ASSOC: 'assoc';
KEYWORD_BEHAVIOR: 'behavior';
KEYWORD_BINDING: 'binding';
KEYWORD_BOOL: 'bool';
KEYWORD_BY: 'by';
KEYWORD_CHAINS: 'chains';
KEYWORD_CLASS: 'class';
KEYWORD_CLASSIFIER: 'classifier';
KEYWORD_COMMENT: 'comment';
KEYWORD_COMPOSITE: 'composite';
KEYWORD_CONJUGATE: 'conjugate';
KEYWORD_CONJUGATES: 'conjugates';
KEYWORD_CONJUGATION: 'conjugation';
KEYWORD_CONNECTOR: 'connector';
KEYWORD_DATATYPE: 'datatype';
KEYWORD_DEFAULT: 'default';
KEYWORD_DEPENDENCY: 'dependency';
KEYWORD_DERIVED: 'derived';
KEYWORD_DIFFERENCES: 'differences';
KEYWORD_DISJOINING: 'disjoining';
KEYWORD_DISJOINT: 'disjoint';
KEYWORD_DOC: 'doc';
KEYWORD_ELSE: 'else';
KEYWORD_END: 'end';
KEYWORD_EXPR: 'expr';
KEYWORD_FALSE: 'false';
KEYWORD_FEATURE: 'feature';
KEYWORD_FEATURED: 'featured';
KEYWORD_FEATURING: 'featuring';
KEYWORD_FILTER: 'filter';
KEYWORD_FIRST: 'first';
KEYWORD_FLOW: 'flow';
KEYWORD_FOR: 'for';
KEYWORD_FROM: 'from';
KEYWORD_FUNCTION: 'function';
KEYWORD_HASTYPE: 'hastype';
KEYWORD_IF: 'if';
KEYWORD_INTERSECTS:'intersects';
KEYWORD_IMPLIES: 'implies';
KEYWORD_IMPORT: 'import';
KEYWORD_IN: 'in';
KEYWORD_INOUT: 'inout';
KEYWORD_INTERACTION: 'interaction';
KEYWORD_INV: 'inv';
KEYWORD_INVERSE: 'inverse';
KEYWORD_INVERTING: 'inverting';
KEYWORD_ISTYPE: 'istype';
KEYWORD_LANGUAGE: 'language';
KEYWORD_MEMBER: 'member';
KEYWORD_METACLASS: 'metaclass';
KEYWORD_METADATA: 'metadata';
KEYWORD_MULTIPLICITY: 'multiplicity';
KEYWORD_NAMESPACE: 'namespace';
KEYWORD_NONUNIQUE: 'nonunique';
KEYWORD_NOT: 'not';
KEYWORD_NULL: 'null';
KEYWORD_OF: 'of';
KEYWORD_OR: 'or';
KEYWORD_ORDERED: 'ordered';
KEYWORD_OUT: 'out';
KEYWORD_PACKAGE: 'package';
KEYWORD_PORTION: 'potion';
KEYWORD_PREDICATE: 'predicate';
KEYWORD_PRIVATE: 'private';
KEYWORD_PROTECTED: 'protected';
KEYWORD_PUBLIC: 'public';
KEYWORD_READONLY: 'readonly';
KEYWORD_REDEFINES: 'redefines';
KEYWORD_REDEFINITION: 'redefinition';
KEYWORD_REFERENCES: 'references';
KEYWORD_REP: 'rep';
KEYWORD_RETURN: 'return';
KEYWORD_SPECILIZATION: 'specialization';
KEYWORD_SPECIALIZES: 'specializes';
KEYWORD_STEP: 'step';
KEYWORD_STRUCT: 'struct';
KEYWORD_SUBCLASSIFIER: 'subsclassifier';
KEYWORD_SUBSET: 'subset';
KEYWORD_SUBSETS: 'subsets';
KEYWORD_SUBTYPE: 'subtype';
KEYWORD_SUCCSESSION: 'succession';
KEYWORD_THEN: 'then';
KEYWORD_TO: 'to';
KEYWORD_TRUE: 'true';
KEYWORD_TYPE: 'type';
KEYWORD_TYPED: 'typed';
KEYWORD_TYPING: 'typing';
KEYWORD_UNIONS: 'unions';
KEYWORD_XOR: 'xor';



//Notes and Comments
SINGLE_LINE_NOTE: '//'  ~( '\r' | '\n' )*;
MULTI_LINE_NOTE: SYMBOL_NOTE_BLOCK_START .*? SYMBOL_COMMENT_BLOCK_END;
REGULAR_COMMENT: SYMBOL_COMMENT_BLOCK_START .*? SYMBOL_COMMENT_BLOCK_END;

//Symbols
SYMBOL_COMMENT_BLOCK_START: '/*';
SYMBOL_NOTE_BLOCK_START: '//*';
SYMBOL_COMMENT_BLOCK_END: '*/';
SYMBOL_STATEMENT_DELIMITER: ';';
SYMBOL_STAR:'*';
SYMBOL_NAMESPACE_SUBSET: '::';
SYMBOL_TYPED_BY: ':';
SYMBOL_SPECIALIZES: ':>';
SYMBOL_REFERENCES: '::>';
SYMBOL_REDEFINES: ':>>';
SYMBOL_CONJUNGATES: '~';
SYMBOL_ROUND_BRACKET_OPEN: '(';
SYMBOL_ROUND_BRACKET_CLOSE: ')';
SYMBOL_CURLY_BRACKET_OPEN: '{';
SYMBOL_CURLY_BRACKET_CLOSE: '}';
SYMBOL_SQUARE_BRACKET_OPEN: '[';
SYMBOL_SQUARE_BRACKET_CLOSE: ']';
SYMBOL_COMMA: ',';
SYMBOL_AT: '@';
SYMBOL_HASHTAG: '#';
SYMBOL_MOD: '%';
SYMBOL_AND: '&';
SYMBOL_UPPER: '^';
SYMBOL_VERTICAL_LINE: '|';
SYMBOL_DOUBLE_STAR: '**';
SYMBOL_PLUS: '+';
SYMBOL_MINUS: '-';
SYMBOL_SLASH: '/';
SYMBOL_ARROOW: '->';
SYMBOL_DOT: '.';
SYMBOL_DDOT: '..';
SYMBOL_SMALLER: '<';
SYMBOL_SMALLER_EQUAL: '<=';
SYMBOL_ASSIGN: '=';
SYMBOL_DEF_ASSIGN: ':=';
SYMBOL_EQUALS: '==';
SYMBOL_IFF_EQUALS: '===';
SYMBOL_NOT_EQUALS: '!=';
SYMBOL_IFF_NOT_EQUALS: '!==';
SYMBOL_GREATER: '>';
SYMBOL_GREATER_EQUALS: '>=';
SYMBOL_QUESTION: '?';
SYMBOL_DQUESTION: '??';
SYMBOL_DOT_QUESTION: '.?';

NAME: BASIC_NAME | UNRESTRICTED_NAME;
BASIC_NAME: ('_'|[a-z]|[A-Z]|[0-9])+ ;
UNRESTRICTED_NAME: '\'' .*? '\'';

//Values:
DECIMAL_VALUE: [0-9]+ ;
EXPONENTIAL_VALUE: DECIMAL_VALUE ('e' | 'E') ('+'|'-') DECIMAL_VALUE;
STRING_VALUE: '"' .*? '"';

WS: [ \t\r\n]+ -> skip ;