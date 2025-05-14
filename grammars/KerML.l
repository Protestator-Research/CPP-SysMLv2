%{
    #include "kerml.tab.h"
    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
%}

/* Definitionen von regulären Ausdrücken */

%%
"about" { return KEYWORD_ABOUT; }
"abstract" { return KEYWORD_ABSTRACT; }
"alias" { return KEYWORD_ALIAS; }
"all" { return KEYWORD_ALL; }
"and" { return KEYWORD_AND; }
"as" { return KEYWORD_AS; }
"assoc" { return KEYWORD_ASSOC; }
"behavior" { return KEYWORD_BEHAVIOR; }
"binding" { return KEYWORD_BINDING; }
"bool" { return KEYWORD_BOOL; }
"by" { return KEYWORD_BY; }
"chains" { return KEYWORD_CHAINS; }
"class" { return KEYWORD_CLASS; }
"classifier" { return KEYWORD_CLASSIFIER; }
"comment" { return KEYWORD_COMMENT; }
"composite" { return KEYWORD_COMPOSITE; }
"conjugate" { return KEYWORD_CONJUGATE; }
"conjugates" { return KEYWORD_CONJUGATES; }
"conjugation" { return KEYWORD_CONJUGATION; }
"connector" { return KEYWORD_CONNECTOR; }
"datatype" { return KEYWORD_DATATYPE; }
"default" { return KEYWORD_DEFAULT; }
"dependency" { return KEYWORD_DEPENDENCY; }
"derived" { return KEYWORD_DERIVED; }
"differences" { return KEYWORD_DIFFERENCES; }
"disjoining" { return KEYWORD_DISJOINING; }
"disjoint" { return KEYWORD_DISJOINT; }
"doc" { return KEYWORD_DOC; }
"else" { return KEYWORD_ELSE; }
"end" { return KEYWORD_END; }
"expr" { return KEYWORD_EXPR; }
"false" { return KEYWORD_FALSE; }
"feature" { return KEYWORD_FEATURE; }
"featured" { return KEYWORD_FEATURED; }
"featuring" { return KEYWORD_FEATURING; }
"filter" { return KEYWORD_FILTER; }
"first" { return KEYWORD_FIRST; }
"flow" { return KEYWORD_FLOW; }
"for" { return KEYWORD_FOR; }
"from" { return KEYWORD_FROM; }
"function" { return KEYWORD_FUNCTION; }
"hastype" { return KEYWORD_HASTYPE; }
"if" { return KEYWORD_IF; }
"intersects" { return KEYWORD_INTERSECTS; }
"implies" { return KEYWORD_IMPLIES; }
"import" { return KEYWORD_IMPORT; }
"in" { return KEYWORD_IN; }
"inout" { return KEYWORD_INOUT; }
"interaction" { return KEYWORD_INTERACTION; }
"inv" { return KEYWORD_INV; }
"inverse" { return KEYWORD_INVERSE; }
"inverting" { return KEYWORD_INVERTING; }
"istype" { return KEYWORD_ISTYPE; }
"language" { return KEYWORD_LANGUAGE; }
"member" { return KEYWORD_MEMBER; }
"metaclass" { return KEYWORD_METACLASS; }
"metadata" { return KEYWORD_METADATA; }
"multiplicity" { return KEYWORD_MULTIPLICITY; }
"namespace" { return KEYWORD_NAMESPACE; }
"nonunique" { return KEYWORD_NONUNIQUE; }
"not" { return KEYWORD_NOT; }
"null" { return KEYWORD_NULL; }
"of" { return KEYWORD_OF; }
"or" { return KEYWORD_OR; }
"ordered" { return KEYWORD_ORDERED; }
"out" { return KEYWORD_OUT; }
"package" { return KEYWORD_PACKAGE; }
"potion" { return KEYWORD_PORTION; }
"predicate" { return KEYWORD_PREDICATE; }
"private" { return KEYWORD_PRIVATE; }
"protected" { return KEYWORD_PROTECTED; }
"public" { return KEYWORD_PUBLIC; }
"readonly" { return KEYWORD_READONLY; }
"redefines" { return KEYWORD_REDEFINES; }
"redefinition" { return KEYWORD_REDEFINITION; }
"references" { return KEYWORD_REFERENCES; }
"rep" { return KEYWORD_REP; }
"return" { return KEYWORD_RETURN; }
"specialization" { return KEYWORD_SPECILIZATION; }
"specializes" { return KEYWORD_SPECIALIZES; }
"step" { return KEYWORD_STEP; }
"struct" { return KEYWORD_STRUCT; }
"subclassifier" { return KEYWORD_SUBCLASSIFIER; }
"subset" { return KEYWORD_SUBSET; }
"subsets" { return KEYWORD_SUBSETS; }
"subtype" { return KEYWORD_SUBTYPE; }
"succession" { return KEYWORD_SUCCSESSION; }
"then" { return KEYWORD_THEN; }
"to" { return KEYWORD_TO; }
"true" { return KEYWORD_TRUE; }
"type" { return KEYWORD_TYPE; }
"typed" { return KEYWORD_TYPED; }
"typing" { return KEYWORD_TYPING; }
"unions" { return KEYWORD_UNIONS; }
"xor" { return KEYWORD_XOR; }
"var" { return KEYWORD_VAR; }
"locale" { return KEYWORD_LOCALE; }
"standard" { return KEYWORD_STANDARD; }
"library" { return KEYWORD_LIBRARY; }
"constant" { return KEYWORD_CONSTANT; }
"meta" {return KEYWORD_META;}

";" { return SYMBOL_STATEMENT_DELIMITER; }
"*" { return SYMBOL_STAR; }
"::" { return SYMBOL_NAMESPACE_SUBSET; }
":" { return SYMBOL_TYPED_BY; }
":>" { return SYMBOL_SPECIALIZES; }
"::>" { return SYMBOL_REFERENCES; }
":>>" { return SYMBOL_REDEFINES; }
"~" { return SYMBOL_CONJUNGATES; }
"(" { return SYMBOL_ROUND_BRACKET_OPEN; }
")" { return SYMBOL_ROUND_BRACKET_CLOSE; }
"\{" { return SYMBOL_CURLY_BRACKET_OPEN; }
"\}" { return SYMBOL_CURLY_BRACKET_CLOSE; }
"[" { return SYMBOL_SQUARE_BRACKET_OPEN; }
"]" { return SYMBOL_SQUARE_BRACKET_CLOSE; }
"," { return SYMBOL_COMMA; }
"@" { return SYMBOL_AT; }
"#" { return SYMBOL_HASHTAG; }
"%" { return SYMBOL_MOD; }
"&" { return SYMBOL_AND; }
"^" { return SYMBOL_UPPER; }
"|" { return SYMBOL_VERTICAL_LINE; }
"**" { return SYMBOL_DOUBLE_STAR; }
"+" { return SYMBOL_PLUS; }
"-" { return SYMBOL_MINUS; }
"/" { return SYMBOL_SLASH; }
"->" { return SYMBOL_ARROOW; }
"." { return SYMBOL_DOT; }
".." { return SYMBOL_DDOT; }
"<" { return SYMBOL_SMALLER; }
"<=" { return SYMBOL_SMALLER_EQUAL; }
"=" { return SYMBOL_ASSIGN; }
":=" { return SYMBOL_DEF_ASSIGN; }
"==" { return SYMBOL_EQUALS; }
"===" { return SYMBOL_IFF_EQUALS; }
"!=" { return SYMBOL_NOT_EQUALS; }
"!==" { return SYMBOL_IFF_NOT_EQUALS; }
">" { return SYMBOL_GREATER; }
">=" { return SYMBOL_GREATER_EQUALS; }
"?" { return SYMBOL_QUESTION; }
"??" { return SYMBOL_DQUESTION; }
".?" { return SYMBOL_DOT_QUESTION; }

[a-zA-Z_][a-zA-Z0-9_]*   { yylval.str = strdup(yytext); return BASIC_NAME; }
[0-9]+                  { yylval.num = atoi(yytext); return NUMBER; }
"\'"[a-zA-Z_][a-zA-Z0-9_.-]* "\'" { yylval.str = strdup(yytext);  return UNRESTRICTED_NAME; }
[-+]?[0-9]+"."[0-9]+      { yylval.doubleValue = stod(yytext); return DECIMAL_VALUE; }
[-+]?[0-9]+(\.[0-9]+)?[eE][-+]?[0-9]+ {yylval.doubleValue = stod(yytext); return EXPONENTIAL_VALUE;}

[ \t\r\n]+         { }

"//".*   {yylval.str = strdup(yytext); return SINGLE_LINE_COMMENT;}
"/*"([^*]|\*+[^*/])*\*+"\\"   {yylval.str = strdup(yytext); return BLOCK_COMMENT;}
"\""([^\"\\]|\\.)*"\"" {
    yylval.str = strdup(yytext); // Übergabe des Strings an Bison
    return STRING;
}

%%