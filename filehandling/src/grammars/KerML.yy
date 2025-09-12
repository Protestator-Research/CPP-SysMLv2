%require "3.2"
%language "c++"
%define api.token.constructor
%define api.value.type variant
%define parse.error verbose
%define parse.assert
%define api.namespace {KerML::Parser}  // Kein Namespace
%parse-param { KerMLFlexScanner* lexer }
%lex-param   { KerMLFlexScanner* lexer }
%{
    #include <string>
    #include <vector>
    #include <iostream>
    #include <root/namespaces/Namespace.h>
    #include <root/elements/Element.h>
%}

%code requires {
    class KerMLFlexScanner;
}

%code {
    #include "KerMLFlexScanner.h"
}

%token <std::string> BASIC_NAME SINGLE_LINE_COMMENT UNRESTRICTED_NAME BLOCK_COMMENT
%token <double> DECIMAL_VALUE
%token <double> EXPONENTIAL_VALUE
%token <int> NUMBER
%token SYMBOL_DOT_QUESTION SYMBOL_DQUESTION SYMBOL_QUESTION SYMBOL_GREATER_EQUALS SYMBOL_GREATER SYMBOL_IFF_NOT_EQUALS SYMBOL_NOT_EQUALS SYMBOL_IFF_EQUALS SYMBOL_EQUALS SYMBOL_DEF_ASSIGN SYMBOL_ASSIGN SYMBOL_SMALLER_EQUAL SYMBOL_SMALLER SYMBOL_DDOT SYMBOL_DOT SYMBOL_ARROOW SYMBOL_SLASH SYMBOL_MINUS SYMBOL_PLUS SYMBOL_DOUBLE_STAR SYMBOL_VERTICAL_LINE SYMBOL_UPPER SYMBOL_AND SYMBOL_MOD SYMBOL_HASHTAG SYMBOL_AT SYMBOL_COMMA SYMBOL_SQUARE_BRACKET_CLOSE SYMBOL_SQUARE_BRACKET_OPEN SYMBOL_CURLY_BRACKET_CLOSE SYMBOL_CURLY_BRACKET_OPEN SYMBOL_ROUND_BRACKET_CLOSE SYMBOL_ROUND_BRACKET_OPEN SYMBOL_CONJUNGATES SYMBOL_REDEFINES SYMBOL_REFERENCES SYMBOL_SPECIALIZES SYMBOL_TYPED_BY SYMBOL_NAMESPACE_SUBSET SYMBOL_STAR SYMBOL_STATEMENT_DELIMITER
%token <std::string> STRING
%token KEYWORD_CONJUGATION KEYWORD_META KEYWORD_CONSTANT KEYWORD_LIBRARY KEYWORD_STANDARD KEYWORD_LOCALE KEYWORD_VAR KEYWORD_XOR KEYWORD_UNIONS KEYWORD_TYPING KEYWORD_TYPED KEYWORD_TYPE KEYWORD_TRUE KEYWORD_TO KEYWORD_THEN KEYWORD_SUCCSESSION KEYWORD_SUBTYPE KEYWORD_SUBSETS KEYWORD_SUBSET KEYWORD_SUBCLASSIFIER KEYWORD_STRUCT KEYWORD_STEP KEYWORD_SPECIALIZES KEYWORD_SPECILIZATION KEYWORD_RETURN KEYWORD_REP KEYWORD_REFERENCES KEYWORD_REDEFINITION KEYWORD_REDEFINES KEYWORD_READONLY KEYWORD_PUBLIC KEYWORD_PROTECTED KEYWORD_PRIVATE KEYWORD_PREDICATE KEYWORD_PORTION KEYWORD_PACKAGE KEYWORD_OUT KEYWORD_ORDERED KEYWORD_OR KEYWORD_OF KEYWORD_NULL KEYWORD_NOT KEYWORD_NONUNIQUE KEYWORD_NAMESPACE KEYWORD_MULTIPLICITY KEYWORD_METADATA KEYWORD_METACLASS KEYWORD_MEMBER KEYWORD_LANGUAGE KEYWORD_ISTYPE KEYWORD_INVERTING KEYWORD_INVERSE KEYWORD_INV KEYWORD_INTERACTION KEYWORD_INOUT KEYWORD_IN KEYWORD_IMPORT KEYWORD_IMPLIES KEYWORD_INTERSECTS KEYWORD_IF KEYWORD_HASTYPE KEYWORD_FUNCTION KEYWORD_FROM KEYWORD_FOR KEYWORD_FLOW KEYWORD_FIRST KEYWORD_FILTER KEYWORD_FEATURING KEYWORD_FEATURED KEYWORD_FEATURE KEYWORD_FALSE KEYWORD_EXPR KEYWORD_END KEYWORD_ELSE KEYWORD_DOC KEYWORD_DISJOINT KEYWORD_DISJOINING KEYWORD_DIFFERENCES KEYWORD_DERIVED KEYWORD_DEPENDENCY KEYWORD_DEFAULT KEYWORD_DATATYPE KEYWORD_CONNECTOR KEYWORD_CONJUGATES KEYWORD_CONJUGATE KEYWORD_COMPOSITE KEYWORD_COMMENT KEYWORD_CLASSIFIER KEYWORD_CLASS KEYWORD_CHAINS KEYWORD_BY KEYWORD_BOOL KEYWORD_BINDING KEYWORD_BEHAVIOR KEYWORD_ASSOC KEYWORD_AS KEYWORD_AND KEYWORD_ALL KEYWORD_ALIAS KEYWORD_ABSTRACT KEYWORD_ABOUT

%left TPLUS TMINUS
%left TMUL TDIV

%type <std::string> relationship_body comment_option from_option prefix_metadata_annotation type_prefix qualified_name qualified_name_tail identification mutliplicity_bounds specialization_option conjugation_option type_body;
%type <bool> abstract_modifier all_modifier;
%type <std::string> specific_type general_type;


%start model

%%
    model:
    elements;
    
    elements:
    elements element
    | /*empty*/ ;
    
    element: annotating_element |
    non_feature_element |
    feature_element |
    additional_options;
    
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
    import;
    
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


    
    type_prefix: abstract_modifier prefix_metadata_annotation {
        if($1) std::cout<<"isAbstract: true \n"<<std::endl;
        if(!$2.empty()) std::cout<<"metadata_member: "<<$2<<std::endl;
    }
    | abstract_modifier {
        if($1) std::cout<<"isAbstract: true"<<std::endl;
    }
    | /* empty */ {}
    
    prefix_metadata_annotation: SYMBOL_HASHTAG qualified_name {
        $$ = $2;
    }
    | /*empty*/ {$$ = "";};
    
    abstract_modifier:
    KEYWORD_ABSTRACT {$$ = true;} |
    /* empty */ {$$ = false;};
    
    //TODO: Basic Name muss mit unrestricted name unterschieden werden.
    qualified_name:
    BASIC_NAME qualified_name_tail
    {
        if (!$2.empty()) {
            $$ = $1.append($2);
        } else {
            $$ = $1;
        }
    }
    | UNRESTRICTED_NAME qualified_name_tail {
        if (!$2.empty()) {
            $$ = $1.append($2);
        } else {
            $$ = $1;
        }
    }
    |/*empty*/ {
        $$="";
    }

    ;
    
    qualified_name_tail:
    SYMBOL_DDOT BASIC_NAME qualified_name_tail
    {
        std::string full;
        if (!$3.empty()) {
            full = $2.append($3);
        } else {
            full = $2;
        }
        $$ = full;
    }
    | SYMBOL_DDOT UNRESTRICTED_NAME qualified_name_tail {
        std::string full;
        if (!$3.empty()) {
            full = $2.append($3);
        } else {
            full = $2;
        }
        $$ = full;
    }
    | /* empty */
    {
        $$ = "";
    }
    ;
    
    all_modifier:
    KEYWORD_ALL {$$ = true;} |
    /* empty */ {$$ = false;};
    
    
    identification: SYMBOL_SMALLER BASIC_NAME SYMBOL_GREATER {
        $$ = $2;
    }
    | BASIC_NAME {
        $$ = $1;
    };
    
    mutliplicity_bounds: SYMBOL_SQUARE_BRACKET_OPEN NUMBER SYMBOL_DDOT NUMBER SYMBOL_SQUARE_BRACKET_OPEN {
        std::cout<<"lower bound: "<< $2 <<std::endl;
        std::cout<<"upper bound: "<< $2 <<std::endl;
    }
    | SYMBOL_SQUARE_BRACKET_OPEN NUMBER SYMBOL_SQUARE_BRACKET_OPEN {
        std::cout<<"multiplicity: "<< $2 <<std::endl;
    }
    | /* empty */ {$$="";};
    
    specialization_option: KEYWORD_SPECIALIZES identification {
        std::cout<<"specialization: "<< $2 <<std::endl;
        $$ = $2;
    }
    | SYMBOL_SPECIALIZES identification {
        std::cout<<"specialization: "<< $2 <<std::endl;
        $$ = $2;
    };
    
    conjugation_option: KEYWORD_CONJUGATES qualified_name {
         std::cout<< "conjugation: "<< $2 <<std::endl;
        $$ = $2;
    }
    | SYMBOL_CONJUNGATES qualified_name {
        std::cout<< "conjugation: "<< $2 <<std::endl;
        $$ = $2;
    };
    
    type_body: SYMBOL_STATEMENT_DELIMITER {$$ = "";}
    | SYMBOL_CURLY_BRACKET_OPEN type_body_elements SYMBOL_CURLY_BRACKET_CLOSE {
        $$ = "$2";
    };
    
    type_body_elements:
    type_body_elements type_body_element
    | /*empty*/ ;
    
    type_body_element: non_feature_member
                     | feature_member
                     | alias_member
                     | import;

    type:
    type_prefix KEYWORD_TYPE all_modifier identification mutliplicity_bounds conjugation_option type_body type_relationship_part_option;
    
    type_relationship_part_option: type_relationship_part | /*empty*/;
    
    type_relationship_part: disjoining_part |
    unioning_part |
    intersecting_part |
    differencing_part;
    
    disjoining_part: KEYWORD_DISJOINT KEYWORD_FROM owned_disjoining disjoining_part_multiplicity;
    disjoining_part_multiplicity: disjoining_part_multiplicity SYMBOL_COMMA owned_disjoining | /*empty*/;
    unioning_part: KEYWORD_UNIONS unioning unioning_part_multiplicity;
    unioning_part_multiplicity: unioning_part_multiplicity SYMBOL_COMMA unioning | /*empty*/;
    intersecting_part: KEYWORD_INTERSECTS intersecting intersecting_part_multiplicity;
    intersecting_part_multiplicity: intersecting_part_multiplicity SYMBOL_COMMA intersecting | /*empty*/;
    differencing_part: KEYWORD_DIFFERENCES differencing differencing_part_multiplicity;
    differencing_part_multiplicity: differencing_part_multiplicity SYMBOL_COMMA differencing | /*empty*/;
    
    relationship_body: SYMBOL_STATEMENT_DELIMITER {$$ = "";}
    |  SYMBOL_CURLY_BRACKET_OPEN relationship_body_elements SYMBOL_CURLY_BRACKET_CLOSE {
        $$="";
    };
    
    relationship_body_elements: relationship_body_elements relationship_body_element | /*empty*/;
    relationship_body_element: owned_related_element | owned_annotation;
    owned_related_element: non_feature_element | feature_element;
    
    from_option: KEYWORD_FROM qualified_name {
        $$ = $2;
    } | /*empty*/ {$$ = "";};
    
    dependency: prefix_metadata_annotation KEYWORD_DEPENDENCY identification from_option KEYWORD_TO qualified_name relationship_body;
    
    owned_annotation: annotating_element;
    about_option: KEYWORD_ABOUT qualified_name
    locale_option: KEYWORD_LOCALE STRING
    | /*empty*/;
    annotating_element: comment | documentation | textual_representation | metadata_feature;
    comment_option: SINGLE_LINE_COMMENT {
        $$=$1;
    } |
    BLOCK_COMMENT {
        $$=$1;
    };
    comment: KEYWORD_COMMENT qualified_name about_option locale_option comment_option
    | locale_option comment_option;
    documentation: KEYWORD_DOC identification locale_option comment_option;
    textual_representation: KEYWORD_REP identification KEYWORD_LANGUAGE STRING comment_option
    | KEYWORD_LANGUAGE STRING comment_option;
    namespace: prefix_metadata_annotation KEYWORD_NAMESPACE identification namespace_body;
    namespace_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN namesapce_body_elements SYMBOL_CURLY_BRACKET_CLOSE;
    namesapce_body_elements: namesapce_body_elements element | /*empty*/;
    member_prefix: visiblity_indicator | /*empty*/;
    visiblity_indicator: KEYWORD_PUBLIC | KEYWORD_PROTECTED | KEYWORD_PRIVATE;
    import: member_prefix KEYWORD_IMPORT all_modifier import_declaration;
    import_declaration: qualified_name complete_namespace_import
    complete_namespace_import: SYMBOL_NAMESPACE_SUBSET SYMBOL_STAR | SYMBOL_NAMESPACE_SUBSET SYMBOL_DOUBLE_STAR | /*empty*/;
    root_namespace: namespace_body_elements;
    namespace_member: non_feature_member | namespace_feature_member;
    non_feature_member: member_prefix non_feature_element;
    namespace_feature_member: member_prefix feature_element;
    alias_member: member_prefix KEYWORD_ALIAS identification name_option KEYWORD_FOR qualified_name relationship_body;
    namespace_body_elements: elements;
    namespace_body_element: namespace_member | alias_member | import;

    specializes: KEYWORD_SPECIALIZES | SYMBOL_SPECIALIZES;
    specialization: KEYWORD_SPECILIZATION identification KEYWORD_SUBTYPE specific_type specializes general_type relationship_body
    | KEYWORD_SUBTYPE specific_type specializes general_type relationship_body;
    specific_type: general_type {
        $$ = $<std::string>0;
    };
    general_type: qualified_name {
        $$ = $<std::string>0;
    } | owned_feature_chain {
        $$="";
    };
    
    conjunction: KEYWORD_CONJUGATION identification KEYWORD_CONJUGATE owned_conjungation KEYWORD_CONJUGATES owned_conjungation relationship_body
    | KEYWORD_CONJUGATE owned_conjungation KEYWORD_CONJUGATES owned_conjungation relationship_body;
    owned_conjungation: qualified_name | feature_chain;
    conjugation_part: SYMBOL_CONJUNGATES owned_conjungation
    | KEYWORD_CONJUGATES owned_conjungation;
    disjoining: KEYWORD_DISJOINING identification KEYWORD_DISJOINT owned_disjoining KEYWORD_FROM owned_disjoining relationship_body
    | KEYWORD_DISJOINT owned_disjoining KEYWORD_FROM owned_disjoining relationship_body;
    owned_disjoining: qualified_name | feature_chain;
    
    unioning: general_type;
    intersecting: general_type;
    differencing: general_type;
    
    feature_member: type_feature_member | owned_feature_member;
    type_feature_member: member_prefix KEYWORD_MEMBER feature_element;
    owned_feature_member: member_prefix feature_element;
    
    classifier: KEYWORD_CLASSIFIER classifier_declaration type_body
    | type_prefix KEYWORD_CLASSIFIER classifier_declaration type_body;
    superclassing_conjunction_option: superclassing_part | conjugation_part | /*empty*/;
    classifier_declaration: all_modifier identification mutliplicity_bounds superclassing_conjunction_option type_relationship_part_option;
    subclassification: specialization_option KEYWORD_SUBCLASSIFIER qualified_name SYMBOL_SPECIALIZES qualified_name relationship_body
    |specialization_option KEYWORD_SUBCLASSIFIER qualified_name KEYWORD_SPECIALIZES qualified_name relationship_body;
    superclassing_part: SYMBOL_SPECIALIZES owned_subclassification multible_superclasses_option;
    multible_superclasses_option: SYMBOL_COMMA owned_subclassification multible_superclasses_option | /*empty*/;
    owned_subclassification: qualified_name;

    feature: feature_prefix feature_descriptor subsettings_option feature_assignment_option feature_value_option type_body;
    feature_prefix: feature_direction_option abstract_option feature_type_option readonly_option derived_option end_option prefix_metadata_annotation;
    abstract_option: KEYWORD_ABSTRACT | /*empty*/;
    readonly_option: KEYWORD_READONLY | /*empty*/;
    derived_option: KEYWORD_DERIVED | /*empty*/;
    end_option: KEYWORD_END | /*empty*/;
    feature_type_option: KEYWORD_VAR | KEYWORD_COMPOSITE | KEYWORD_PORTION | /*emtpy*/;
    feature_descriptor: KEYWORD_FEATURE feature_declaration
    | KEYWORD_FEATURE
    | prefix_metadata_member;
    subsettings_option: subsettings | /*empty*/;
    feature_assignment_option: feature_assignment | /*empty*/;
    feature_value_option: feature_value | /*empty*/;
    feature_direction_option: KEYWORD_IN | KEYWORD_OUT | KEYWORD_INOUT | /*empty*/;
    feature_declaration: all_modifier feature_identification feature_specialization_conjungation_option feature_relationship_part_option
    | all_modifier feature_specialization_part feature_relationship_part_option
    | all_modifier conjugation_part feature_relationship_part_option;
    
    feature_identification: SYMBOL_SMALLER BASIC_NAME SYMBOL_GREATER | SYMBOL_SMALLER BASIC_NAME SYMBOL_GREATER BASIC_NAME | BASIC_NAME;
    feature_specialization_conjungation_option: feature_specialization_part | conjugation_part | /* empty */;
    feature_relationship_part_option: feature_relationship_part | /* empty */;
    feature_relationship_part: type_relationship_part | chaining_part | inverting_part | type_featuring_part;
    chaining_part: KEYWORD_CHAINS owned_feature_chain
    | KEYWORD_CHAINS feature_chain;
    inverting_part: KEYWORD_INVERSE KEYWORD_OF owned_feature_chain;
    type_featuring_part: KEYWORD_FEATURED KEYWORD_BY owned_type_featuring type_featuting_part_multiplicity;
    type_featuting_part_multiplicity: type_featuting_part_multiplicity SYMBOL_COMMA owned_type_featuring | /* empty */;
    feature_specialization_part: feature_specialization_option multiplicity_part  feature_specialization_option;
    feature_specialization_option: feature_specialization_option typings | feature_specialization_option subsettings |  feature_specialization_option references | feature_specialization_option redefinitions | /*empty*/;
    typings: typed_by typed_by_mutliplicity;
    typed_by: SYMBOL_TYPED_BY owned_feature_typing;
    typed_by_mutliplicity: SYMBOL_COMMA owned_feature_typing typed_by_mutliplicity | /* empty */;
    subsettings: subsets owned_subsetting_option subsetting_multiplictiy;
    subsets: SYMBOL_SPECIALIZES owned_subsetting | KEYWORD_SUBSETS owned_subsetting;
    subsetting_multiplictiy: SYMBOL_COMMA owned_subsetting owned_subsetting_option| /* empty */
    multiplicity_part: mutliplicity_bounds
    | mutliplicity_bounds KEYWORD_ORDERED
    | mutliplicity_bounds KEYWORD_ORDERED KEYWORD_NONUNIQUE
    | mutliplicity_bounds KEYWORD_NONUNIQUE KEYWORD_ORDERED
    | /*empty*/ ;
    references: SYMBOL_REFERENCES owned_reference_subsettings
    | KEYWORD_REFERENCES owned_reference_subsettings;
    redefinitions: redefines owned_redefinition redefinitions_mutliplicity_option;
    redefinitions_mutliplicity_option: SYMBOL_COMMA owned_redefinition redefinitions_mutliplicity_option;
    redefines: feature_direction_option SYMBOL_REDEFINES owned_redefinition
    | feature_direction_option KEYWORD_REDEFINES owned_redefinition;
    
    
    feature_typing: specialization_option typing_option qualified_name SYMBOL_TYPED_BY general_type multiplicity_part relationship_body
    | specialization_option typing_option qualified_name KEYWORD_TYPED KEYWORD_BY general_type multiplicity_part relationship_body;
    typing_option: KEYWORD_TYPING | /*empty*/;
    owned_feature_typing: general_type;
    
    subsetting: specialization_option subset_option specific_type SYMBOL_SPECIALIZES general_type multiplicity_part relationship_body
    | specialization_option subset_option specific_type KEYWORD_SUBSETS  general_type multiplicity_part relationship_body;
    subset_option: KEYWORD_SUBSET | /*empty*/;
    typed_by_option: typed_by | /*empty*/;
    owned_subsetting_option: owned_subsetting | /*empty*/;
    owned_subsetting: general_type;
    owned_reference_subsettings: general_type;
    
    redefinition: feature_direction_option specialization_option redefinition_option SYMBOL_REDEFINES qualified_name typed_by_option multiplicity_part subsets_option feature_assignment_option relationship_body;
    redefinition_option: KEYWORD_REDEFINITION specific_type | /*empty*/;
    subsets_option: subsets | /*empty*/;
    owned_redefinition: general_type;
    
    owned_feature_chain: feature_chain;
    feature_chain: qualified_name feature_chain_part;
    feature_chain_part: SYMBOL_DOT qualified_name feature_chain_part | /*empty*/;
    owned_feature_chaining: qualified_name;
    
    feature_inverting: inverting_option KEYWORD_INVERSE general_type KEYWORD_OF general_type relationship_body;
    inverting_option: KEYWORD_INVERTING identification | /*empty*/;
    owned_feature_invering: qualified_name | owned_feature_chain;
    
    type_featuring: KEYWORD_FEATURING identification of_option KEYWORD_BY qualified_name relationship_body;
    of_option: KEYWORD_OF qualified_name | /*empty*/;
    owned_type_featuring: qualified_name;
    
    data_type: type_prefix KEYWORD_DATATYPE classifier_declaration type_body;
    
    class: type_prefix KEYWORD_CLASS classifier_declaration type_body;
    
    structure: type_prefix_option KEYWORD_STRUCT classifier_declaration type_body;
    
    association: type_prefix KEYWORD_ASSOC classifier_declaration type_body;
    association_structure: type_prefix KEYWORD_ASSOC KEYWORD_STRUCT classifier_declaration type_body;
    type_prefix_option: type_prefix | /* empty */;
    
    connector: type_prefix_option KEYWORD_CONNECTOR connector_declaration type_body;
    connector_declaration: feature_declaration binary_connector_declaration
    | feature_declaration nary_connector_declaration;
    binary_connector_declaration: all_modifier KEYWORD_FROM connector_end_member KEYWORD_TO connector_end_member;
    nary_connector_declaration: SYMBOL_ROUND_BRACKET_OPEN connector_end_member nary_connector_declaration_additional_member SYMBOL_ROUND_BRACKET_CLOSE;
    nary_connector_declaration_additional_member: SYMBOL_COMMA connector_end_member nary_connector_declaration_additional_member | /*empty*/;
    connector_end_member: connector_end;
    connector_end: name_reference_option mutliplicity_bounds owned_reference_subsettings;
    name_reference_option: BASIC_NAME SYMBOL_REFERENCES
    | BASIC_NAME KEYWORD_REFERENCES
    | /*empty*/;
    
    binding_connector: feature_prefix KEYWORD_BINDING binding_connector_declaration type_body;
    binding_connector_declaration: feature_declaration all_modifier connector_end_member_of_option;
    connector_end_member_of_option: KEYWORD_OF connector_end_member SYMBOL_EQUALS connector_end_member | /*empty*/;
    
    succession: feature_prefix KEYWORD_SUCCSESSION succession_declaration type_body;
    succession_declaration: feature_declaration all_modifier connector_end_member_first_option;
    connector_end_member_first_option: KEYWORD_FIRST connector_end_member KEYWORD_THEN connector_end_member | /*empty*/;
    
    behavior: type_prefix KEYWORD_BEHAVIOR classifier_declaration type_body;
    
    step: feature_prefix KEYWORD_STEP feature_declaration value_part_option type_body;
    
    function: type_prefix KEYWORD_FUNCTION classifier_declaration function_body;
    function_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN function_body_part SYMBOL_CURLY_BRACKET_CLOSE;
    function_body_part_multiplicity: type_body_elements function_body_part_multiplicity
    | return_feature_element function_body_part_multiplicity
    | /*empty*/;
    function_body_part: function_body_part_multiplicity result_expression_member;
    return_feature_element: member_prefix KEYWORD_RETURN owned_expression;
    result_expression_member: member_prefix owned_expression
    | /*empty*/;
    
    expression: feature_prefix KEYWORD_EXPR feature_declaration value_part_option function_body;
    value_part_option: value_part | /*empty*/;
    
    predicate: type_prefix KEYWORD_PREDICATE classifier_declaration function_body;
    
    boolean_expression: feature_prefix KEYWORD_BOOL feature_declaration value_part_option function_body;
    invariant: feature_prefix KEYWORD_INV invariant_option feature_declaration value_part_option function_body;
    invariant_option: KEYWORD_TRUE | KEYWORD_FALSE | /* empty */;
    
    owned_expression_reference_member: owned_expression_reference;
    owned_expression_reference: owned_expression_member;
    owned_expression_member: owned_expressions;
    owned_expressions: owned_expression owned_expressions | /*empty*/;
    owned_expression: conditional_expression
    | conditional_binary_operator_expression
    | binary_operator_expression
    | unary_operator_expression
    | classification_expression
    | metaclassification_expression
    | extend_expression
    | primary_expression;
    conditional_expression: KEYWORD_IF argument_member SYMBOL_QUESTION argument_expression_member KEYWORD_ELSE argument_expression_member;
    conditional_binary_operator_expression: argument_member conditional_binary_operator argument_expression_member;
    conditional_binary_operator: SYMBOL_DQUESTION | KEYWORD_OR | KEYWORD_AND | KEYWORD_IMPLIES;
    binary_operator_expression:  argument_member binary_operator owned_expressions;
    binary_operator: SYMBOL_VERTICAL_LINE | SYMBOL_AND | KEYWORD_XOR | SYMBOL_DDOT | SYMBOL_EQUALS | SYMBOL_NOT_EQUALS | SYMBOL_IFF_EQUALS | SYMBOL_IFF_NOT_EQUALS | SYMBOL_GREATER | SYMBOL_SMALLER | SYMBOL_GREATER_EQUALS | SYMBOL_SMALLER_EQUAL | SYMBOL_PLUS | SYMBOL_MINUS | SYMBOL_STAR | SYMBOL_SLASH | SYMBOL_MOD | SYMBOL_UPPER | SYMBOL_DOUBLE_STAR;
    unary_operator_expression: unary_operator owned_expressions
    unary_operator: SYMBOL_PLUS | SYMBOL_MINUS | SYMBOL_CONJUNGATES | KEYWORD_NOT;
    classification_expression: argument_member classification_test_operator type_reference_member
    | argument_member KEYWORD_AS type_result_member;
    classification: argument_member classification_test_operator type_reference_member
    | argument_member KEYWORD_AS type_result_member;
    classification_test_operator: KEYWORD_ISTYPE | KEYWORD_HASTYPE | SYMBOL_AT;
    metaclassification_expression: metadata_argument_member metadataclassification_test_operator type_reference_member
    | metadata_argument_member KEYWORD_META type_result_member;
    argument_member: argument | /*empty*/;
    argument: argument_value;
    argument_value: owned_expression;
    argument_expression_member: argument_expression;
    argument_expression: argument_expression_value;
    argument_expression_value: owned_expression_reference;
    metadata_argument_member: metadata_argument;
    metadata_argument: metadata_value;
    metadata_value: metadata_reference;
    metadata_reference: qualified_name;
    metadataclassification_test_operator: SYMBOL_DOT;
    extend_expression: KEYWORD_ALL type_reference_member;
    type_reference_member: type_reference;
    type_result_member: type_reference;
    type_reference: reference_typing;
    reference_typing: qualified_name;
    
    primary_expressions: primary_expression primary_expressions | /*empty*/;
    primary_expression: feature_chain_expression | non_feature_chain_primary_expression;
    primary_argument_value: primary_expression;
    primary_argument: primary_argument_value;
    primary_argument_member: primary_argument;
    non_feature_chain_primary_expression: bracket_expression |
    index_expression |
    sequence_expression |
    select_expression |
    collect_expression |
    function_operation_expression |
    base_expression;
    non_feature_chain_primary_argument_value: non_feature_chain_primary_expression;
    non_feature_chain_primary_argument: primary_argument;
    non_feature_chain_primary_argument_member: primary_argument;
    bracket_expression: SYMBOL_SQUARE_BRACKET_OPEN sequence_expression_list_member SYMBOL_SQUARE_BRACKET_CLOSE;
    index_expression: SYMBOL_HASHTAG SYMBOL_ROUND_BRACKET_OPEN sequence_expression_list_member SYMBOL_ROUND_BRACKET_CLOSE;
    sequence_expression: SYMBOL_ROUND_BRACKET_OPEN sequence_expression_list SYMBOL_ROUND_BRACKET_CLOSE;
    sequence_expression_list: owned_expressions SYMBOL_COMMA sequence_expression_list
    | sequence_operator_expression
    | /*empty*/;
    sequence_operator_expression: owned_expression_member SYMBOL_COMMA sequence_expression_list_member;
    sequence_expression_list_member: sequence_expression_list;
    feature_chain_expression: SYMBOL_DOT feature_chain_member;
    collect_expression: SYMBOL_DOT body_expression_member;
    select_expression: SYMBOL_DOT_QUESTION body_expression_member;
    function_operation_expression: SYMBOL_ARROOW reference_typing body_argument_member
    | SYMBOL_ARROOW reference_typing function_reference_argument_member
    | SYMBOL_ARROOW reference_typing argument_expression;
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
    
    base_expression: null_expression
    | literal_expression
    | feature_reference_expression
    | metadata_access_expression
    | invocation_expression
    | body_expression;
    null_expression: KEYWORD_NULL | SYMBOL_ROUND_BRACKET_OPEN SYMBOL_ROUND_BRACKET_CLOSE;
    feature_reference_expression: feature_reference_member;
    feature_reference_member: feature_reference;
    feature_reference: qualified_name;
    
    metadata_access_expression: qualified_name SYMBOL_DOT KEYWORD_METADATA;
    invocation_expression: internal_invocation_expression;
    internal_invocation_expression: owned_feature_typing argument_list
    | named_argument_list_option argument_list;
    argument_list: SYMBOL_ROUND_BRACKET_OPEN owned_expressions positional_argument_list SYMBOL_ROUND_BRACKET_CLOSE
    | SYMBOL_ROUND_BRACKET_OPEN named_argument_list_option SYMBOL_ROUND_BRACKET_CLOSE
    | SYMBOL_ROUND_BRACKET_OPEN SYMBOL_ROUND_BRACKET_CLOSE;
    named_argument_list_option: named_argument_member named_argument_list_mutliplicity;
    named_argument_list_mutliplicity: SYMBOL_COMMA named_argument_member named_argument_list_mutliplicity | /*empty*/;
    positional_argument_list: argument_member positional_argument_list_multible;
    positional_argument_list_multible: positional_argument_list_multible SYMBOL_COMMA owned_expressions | /*empty*/;
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
    boolean_value: KEYWORD_TRUE | KEYWORD_FALSE;
    literal_string: STRING;
    literal_integer: DECIMAL_VALUE;
    literal_real: real_value;
    real_value: DECIMAL_VALUE | EXPONENTIAL_VALUE;
    literal_infinity: SYMBOL_STAR;
    
    interaction: type_prefix KEYWORD_INTERACTION classifier_declaration type_body;
    
    item_flow: feature_prefix KEYWORD_FLOW item_flow_declaration type_body;
    succession_item_flow: feature_prefix KEYWORD_SUCCSESSION KEYWORD_FLOW item_flow_declaration type_body;
    item_flow_declaration: feature_declaration value_part_option item_flow_of_option item_flow_from_to_option
    | all_modifier item_flow_end_member KEYWORD_TO item_flow_end_member;
    item_flow_of_option: KEYWORD_OF item_feature_member | /*empty*/;
    item_flow_from_to_option: KEYWORD_FROM item_flow_end_member KEYWORD_TO item_flow_end_member | /*empty*/;
    item_feature_member: item_feature;
    item_feature: identification item_feature_specilization_part value_part_option
    | owned_feature_typing mutliplicity_bounds
    | mutliplicity_bounds owned_feature_typing_option;
    owned_feature_typing_option: owned_feature_typing | /*empty*/;
    item_feature_specilization_part: feature_specialization_option multiplicity_part feature_specialization_option;
    item_flow_end_member: item_flow_end;
    item_flow_end: item_flow_feature_member
    | general_type SYMBOL_DOT item_flow_feature_member;
    item_flow_feature_member: item_flow_feature;
    item_flow_feature: item_flow_redefinition;
    item_flow_redefinition: qualified_name;
    
    value_part: feature_value;
    feature_value: SYMBOL_EQUALS owned_expression
    | SYMBOL_DEF_ASSIGN owned_expression
    | KEYWORD_DEFAULT euqals_assign_option owned_expression;
    euqals_assign_option: SYMBOL_EQUALS | SYMBOL_DEF_ASSIGN | /*empty*/;
    feature_assignment: SYMBOL_ASSIGN owned_expression;
    
    multiplicity: multiplicity_subset | multiplicity_range;
    multiplicity_subset: KEYWORD_MULTIPLICITY identification subsets type_body;
    multiplicity_range: KEYWORD_MULTIPLICITY identification multiplicity_bounds type_body;
    owned_multiplicity: multiplicity_bounds;
    owned_multiplicity_range: multiplicity_bounds;
    multiplicity_bounds: SYMBOL_SQUARE_BRACKET_OPEN multiplicity_expression_member SYMBOL_SQUARE_BRACKET_CLOSE
    | SYMBOL_SQUARE_BRACKET_OPEN multiplicity_expression_member SYMBOL_DDOT multiplicity_expression_member SYMBOL_SQUARE_BRACKET_CLOSE;
    multiplicity_expression_member: internal_multiplicity_expression_member;
    internal_multiplicity_expression_member: literal_expression | feature_reference_expression;
    
    metaclass: type_prefix_option KEYWORD_METACLASS identification name_option meta_specialization_option type_body
    | type_prefix_option KEYWORD_METACLASS classifier_declaration name_option meta_specialization_option type_body;
    name_option: BASIC_NAME | /*empty*/;
    meta_specialization_option: KEYWORD_SPECIALIZES BASIC_NAME | SYMBOL_SPECIALIZES BASIC_NAME | /*empty*/;
    //prefix_metadata_annotation: SYMBOL_HASHTAG prefix_metadata_feature;
    prefix_metadata_member: SYMBOL_HASHTAG prefix_metadata_feature;
    prefix_metadata_feature: owned_feature_typing;
    metadata_feature: prefix_metadata_member_multiplicity KEYWORD_METADATA metadata_feature_declaration about_annotation
    | prefix_metadata_member_multiplicity SYMBOL_AT metadata_feature_declaration about_annotation;
    prefix_metadata_member_multiplicity: prefix_metadata_member_multiplicity prefix_metadata_member | /*empty*/;
    about_annotation: KEYWORD_ABOUT qualified_name about_annotation_mutliplicity;
    about_annotation_mutliplicity: SYMBOL_COMMA qualified_name about_annotation_mutliplicity | /*empty*/;
    metadata_feature_declaration: identification_annotation owned_feature_typing;
    identification_annotation: identification SYMBOL_TYPED_BY | identification KEYWORD_TYPED KEYWORD_BY | /*empty*/
    metadata_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN metadata_body_elements SYMBOL_CURLY_BRACKET_CLOSE;
    metadata_body_elements: metadata_body_element metadata_body_elements | /*empty*/;
    metadata_body_element: non_feature_member |
                           metadata_body_feature_member |
                           alias_member |
                           import_declaration;
    metadata_body_feature_member: metadata_body_feature;
    metadata_body_feature: feature_option defines_redefines_optin owned_redefinition feature_specialization_part_option value_part_option metadata_body;
    feature_option: KEYWORD_FEATURE | /*empty*/;
    defines_redefines_optin: SYMBOL_REDEFINES | KEYWORD_REDEFINES |/*emtpy*/;
    feature_specialization_part_option: feature_specialization_part |/*empty*/;
    
    package:prefix_metadata_member_multiplicity package_declaration package_body;
    library_package: standard_option KEYWORD_LIBRARY prefix_metadata_member_multiplicity package_declaration package_body;
    standard_option: KEYWORD_STANDARD | /*empty*/;
    package_declaration: KEYWORD_PACKAGE identification;
    package_body: SYMBOL_STATEMENT_DELIMITER |
    | SYMBOL_CURLY_BRACKET_OPEN element_filter_members SYMBOL_CURLY_BRACKET_CLOSE
    | SYMBOL_CURLY_BRACKET_OPEN elements SYMBOL_CURLY_BRACKET_CLOSE;
    element_filter_members: element_filter_members element_filter_member | /*empty*/;
    element_filter_member: member_prefix KEYWORD_FILTER owned_expression SYMBOL_STATEMENT_DELIMITER;

    meta_assignment: qualified_name SYMBOL_ASSIGN identification KEYWORD_META qualified_name SYMBOL_STATEMENT_DELIMITER;
%%

void KerML::Parser::parser::error(const std::string& msg) {
        std::cerr << "Parser-Fehler: " << msg << std::endl;
    }