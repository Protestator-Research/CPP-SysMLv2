% {
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(const char* s);
    int yylex(void);
% }

% union {
    int num;
    double doubleValue;
    char* str;
}

%token <str> BASIC_NAME
%token <str> UNRESTRICTED_NAME
%token <doubleValue> DECIMAL_VALUE
%token <doubleValue> EXPONENTIAL_VALUE
%token <num> NUMBER
%token SYMBOL_DOT_QUESTION SYMBOL_DQUESTION SYMBOL_QUESTION SYMBOL_GREATER_EQUALS SYMBOL_GREATER SYMBOL_IFF_NOT_EQUALS SYMBOL_NOT_EQUALS SYMBOL_IFF_EQUALS SYMBOL_EQUALS SYMBOL_DEF_ASSIGN SYMBOL_ASSIGN SYMBOL_SMALLER_EQUAL SYMBOL_SMALLER SYMBOL_DDOT SYMBOL_DOT SYMBOL_ARROOW SYMBOL_SLASH SYMBOL_MINUS SYMBOL_PLUS SYMBOL_DOUBLE_STAR SYMBOL_VERTICAL_LINE SYMBOL_UPPER SYMBOL_AND SYMBOL_MOD SYMBOL_HASHTAG SYMBOL_AT SYMBOL_COMMA SYMBOL_SQUARE_BRACKET_CLOSE SYMBOL_SQUARE_BRACKET_OPEN SYMBOL_CURLY_BRACKET_CLOSE SYMBOL_CURLY_BRACKET_OPEN SYMBOL_ROUND_BRACKET_CLOSE SYMBOL_ROUND_BRACKET_OPEN SYMBOL_CONJUNGATES SYMBOL_REDEFINES SYMBOL_REFERENCES SYMBOL_SPECIALIZES SYMBOL_TYPED_BY SYMBOL_NAMESPACE_SUBSET SYMBOL_STAR SYMBOL_STATEMENT_DELIMITER
%token <str> STRING
%token KEYWORD_CONSTANT KEYWORD_LIBRARY KEYWORD_STANDARD KEYWORD_LOCALE KEYWORD_VAR KEYWORD_XOR KEYWORD_UNIONS KEYWORD_TYPING KEYWORD_TYPED KEYWORD_TYPE KEYWORD_TRUE KEYWORD_TO KEYWORD_THEN KEYWORD_SUCCSESSION KEYWORD_SUBTYPE KEYWORD_SUBSETS KEYWORD_SUBSET KEYWORD_SUBCLASSIFIER KEYWORD_STRUCT KEYWORD_STEP KEYWORD_SPECIALIZES KEYWORD_SPECILIZATION KEYWORD_RETURN KEYWORD_REP KEYWORD_REFERENCES KEYWORD_REDEFINITION KEYWORD_REDEFINES KEYWORD_READONLY KEYWORD_PUBLIC KEYWORD_PROTECTED KEYWORD_PRIVATE KEYWORD_PREDICATE KEYWORD_PORTION KEYWORD_PACKAGE KEYWORD_OUT KEYWORD_ORDERED KEYWORD_OR KEYWORD_OF KEYWORD_NULL KEYWORD_NOT KEYWORD_NONUNIQUE KEYWORD_NAMESPACE KEYWORD_MULTIPLICITY KEYWORD_METADATA KEYWORD_METACLASS KEYWORD_MEMBER KEYWORD_LANGUAGE KEYWORD_ISTYPE KEYWORD_INVERTING KEYWORD_INVERSE KEYWORD_INV KEYWORD_INTERACTION KEYWORD_INOUT KEYWORD_IN KEYWORD_IMPORT KEYWORD_IMPLIES KEYWORD_INTERSECTS KEYWORD_IF KEYWORD_HASTYPE KEYWORD_FUNCTION KEYWORD_FROM KEYWORD_FOR KEYWORD_FLOW KEYWORD_FIRST KEYWORD_FILTER KEYWORD_FEATURING KEYWORD_FEATURED KEYWORD_FEATURE KEYWORD_FALSE KEYWORD_EXPR KEYWORD_END KEYWORD_ELSE KEYWORD_DOC KEYWORD_DISJOINT KEYWORD_DISJOINING KEYWORD_DIFFERENCES KEYWORD_DERIVED KEYWORD_DEPENDENCY KEYWORD_DEFAULT KEYWORD_DATATYPE KEYWORD_CONNECTOR KEYWORD_CONJUGATES KEYWORD_CONJUGATE KEYWORD_COMPOSITE KEYWORD_COMMENT KEYWORD_CLASSIFIER KEYWORD_CLASS KEYWORD_CHAINS KEYWORD_BY KEYWORD_BOOL KEYWORD_BINDING KEYWORD_BEHAVIOR KEYWORD_ASSOC KEYWORD_AS KEYWORD_AND KEYWORD_ALL KEYWORD_ALIAS KEYWORD_ABSTRACT KEYWORD_ABOUT

%type <str> expression term factor comparison logical_expr

%%
model:
    elements;

elements:
    element*;

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

%%

void yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
}