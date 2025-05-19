%option nodefault
%option noinput
%option noyywrap
%option c++
%option yyclass="KerMLFlexScanner"
%{
    #include "KerMLBisonParser.h"
    #include <string>
    #include <cstdlib>
    #include "KerMLFlexScanner.h"

    #ifndef YY_DECL
        #define YY_DECL KerML::Parser::parser::symbol_type KerMLFlexScanner::yylex()
    #endif
%}

/* Definitionen von regulären Ausdrücken */

%%
"about" { return KerML::Parser::parser::token::make_KEYWORD_ABOUT(); }
"abstract" { return KerML::Parser::parser::token::make_KEYWORD_ABSTRACT(); }
"alias" { return KerML::Parser::parser::token::make_KEYWORD_ALIAS(); }
"all" { return KerML::Parser::parser::token::make_KEYWORD_ALL(); }
"and" { return KerML::Parser::parser::token::make_KEYWORD_AND(); }
"as" { return KerML::Parser::parser::token::make_KEYWORD_AS(); }
"assoc" { return KerML::Parser::parser::token::make_KEYWORD_ASSOC(); }
"behavior" { return KerML::Parser::parser::token::make_KEYWORD_BEHAVIOR(); }
"binding" { return KerML::Parser::parser::token::make_KEYWORD_BINDING(); }
"bool" { return KerML::Parser::parser::token::make_KEYWORD_BOOL(); }
"by" { return KerML::Parser::parser::token::make_KEYWORD_BY(); }
"chains" { return KerML::Parser::parser::token::make_KEYWORD_CHAINS(); }
"class" { return KerML::Parser::parser::token::make_KEYWORD_CLASS(); }
"classifier" { return KerML::Parser::parser::token::make_KEYWORD_CLASSIFIER(); }
"comment" { return KerML::Parser::parser::token::make_KEYWORD_COMMENT(); }
"composite" { return KerML::Parser::parser::token::make_KEYWORD_COMPOSITE(); }
"conjugate" { return KerML::Parser::parser::token::make_KEYWORD_CONJUGATE(); }
"conjugates" { return KerML::Parser::parser::token::make_KEYWORD_CONJUGATES(); }
"conjugation" { return KerML::Parser::parser::token::make_KEYWORD_CONJUGATION(); }
"connector" { return KerML::Parser::parser::token::make_KEYWORD_CONNECTOR(); }
"datatype" { return KerML::Parser::parser::token::make_KEYWORD_DATATYPE(); }
"default" { return KerML::Parser::parser::token::make_KEYWORD_DEFAULT(); }
"dependency" { return KerML::Parser::parser::token::make_KEYWORD_DEPENDENCY(); }
"derived" { return KerML::Parser::parser::token::make_KEYWORD_DERIVED(); }
"differences" { return KerML::Parser::parser::token::make_KEYWORD_DIFFERENCES(); }
"disjoining" { return KerML::Parser::parser::token::make_KEYWORD_DISJOINING(); }
"disjoint" { return KerML::Parser::parser::token::make_KEYWORD_DISJOINT(); }
"doc" { return KerML::Parser::parser::token::make_KEYWORD_DOC(); }
"else" { return KerML::Parser::parser::token::make_KEYWORD_ELSE(); }
"end" { return KerML::Parser::parser::token::make_KEYWORD_END(); }
"expr" { return KerML::Parser::parser::token::make_KEYWORD_EXPR(); }
"false" { return KerML::Parser::parser::token::make_KEYWORD_FALSE(); }
"feature" { return KerML::Parser::parser::token::make_KEYWORD_FEATURE(); }
"featured" { return KerML::Parser::parser::token::make_KEYWORD_FEATURED(); }
"featuring" { return KerML::Parser::parser::token::make_KEYWORD_FEATURING(); }
"filter" { return KerML::Parser::parser::token::make_KEYWORD_FILTER(); }
"first" { return KerML::Parser::parser::token::make_KEYWORD_FIRST(); }
"flow" { return KerML::Parser::parser::token::make_KEYWORD_FLOW(); }
"for" { return KerML::Parser::parser::token::make_KEYWORD_FOR(); }
"from" { return KerML::Parser::parser::token::make_KEYWORD_FROM(); }
"function" { return KerML::Parser::parser::token::make_KEYWORD_FUNCTION(); }
"hastype" { return KerML::Parser::parser::token::make_KEYWORD_HASTYPE(); }
"if" { return KerML::Parser::parser::token::make_KEYWORD_IF(); }
"intersects" { return KerML::Parser::parser::token::make_KEYWORD_INTERSECTS(); }
"implies" { return KerML::Parser::parser::token::make_KEYWORD_IMPLIES(); }
"import" { return KerML::Parser::parser::token::make_KEYWORD_IMPORT(); }
"in" { return KerML::Parser::parser::token::make_KEYWORD_IN(); }
"inout" { return KerML::Parser::parser::token::make_KEYWORD_INOUT(); }
"interaction" { return KerML::Parser::parser::token::make_KEYWORD_INTERACTION(); }
"inv" { return KerML::Parser::parser::token::make_KEYWORD_INV(); }
"inverse" { return KerML::Parser::parser::token::make_KEYWORD_INVERSE(); }
"inverting" { return KerML::Parser::parser::token::make_KEYWORD_INVERTING(); }
"istype" { return KerML::Parser::parser::token::make_KEYWORD_ISTYPE(); }
"language" { return KerML::Parser::parser::token::make_KEYWORD_LANGUAGE(); }
"member" { return KerML::Parser::parser::token::make_KEYWORD_MEMBER(); }
"metaclass" { return KerML::Parser::parser::token::make_KEYWORD_METACLASS(); }
"metadata" { return KerML::Parser::parser::token::make_KEYWORD_METADATA(); }
"multiplicity" { return KerML::Parser::parser::token::make_KEYWORD_MULTIPLICITY(); }
"namespace" { return KerML::Parser::parser::token::make_KEYWORD_NAMESPACE(); }
"nonunique" { return KerML::Parser::parser::token::make_KEYWORD_NONUNIQUE(); }
"not" { return KerML::Parser::parser::token::make_KEYWORD_NOT(); }
"null" { return KerML::Parser::parser::token::make_KEYWORD_NULL(); }
"of" { return KerML::Parser::parser::token::make_KEYWORD_OF(); }
"or" { return KerML::Parser::parser::token::make_KEYWORD_OR(); }
"ordered" { return KerML::Parser::parser::token::make_KEYWORD_ORDERED(); }
"out" { return KerML::Parser::parser::token::make_KEYWORD_OUT(); }
"package" { return KerML::Parser::parser::token::make_KEYWORD_PACKAGE(); }
"potion" { return KerML::Parser::parser::token::make_KEYWORD_PORTION(); }
"predicate" { return KerML::Parser::parser::token::make_KEYWORD_PREDICATE(); }
"private" { return KerML::Parser::parser::token::make_KEYWORD_PRIVATE(); }
"protected" { return KerML::Parser::parser::token::make_KEYWORD_PROTECTED(); }
"public" { return KerML::Parser::parser::token::make_KEYWORD_PUBLIC(); }
"readonly" { return KerML::Parser::parser::token::make_KEYWORD_READONLY(); }
"redefines" { return KerML::Parser::parser::token::make_KEYWORD_REDEFINES(); }
"redefinition" { return KerML::Parser::parser::token::make_KEYWORD_REDEFINITION(); }
"references" { return KerML::Parser::parser::token::make_KEYWORD_REFERENCES(); }
"rep" { return KerML::Parser::parser::token::make_KEYWORD_REP(); }
"return" { return KerML::Parser::parser::token::make_KEYWORD_RETURN(); }
"specialization" { return KerML::Parser::parser::token::make_KEYWORD_SPECILIZATION(); }
"specializes" { return KerML::Parser::parser::token::make_KEYWORD_SPECIALIZES(); }
"step" { return KerML::Parser::parser::token::make_KEYWORD_STEP(); }
"struct" { return KerML::Parser::parser::token::make_KEYWORD_STRUCT(); }
"subclassifier" { return KerML::Parser::parser::token::make_KEYWORD_SUBCLASSIFIER(); }
"subset" { return KerML::Parser::parser::token::make_KEYWORD_SUBSET(); }
"subsets" { return KerML::Parser::parser::token::make_KEYWORD_SUBSETS(); }
"subtype" { return KerML::Parser::parser::token::make_KEYWORD_SUBTYPE(); }
"succession" { return KerML::Parser::parser::token::make_KEYWORD_SUCCSESSION(); }
"then" { return KerML::Parser::parser::token::make_KEYWORD_THEN(); }
"to" { return KerML::Parser::parser::token::make_KEYWORD_TO(); }
"true" { return KerML::Parser::parser::token::make_KEYWORD_TRUE(); }
"type" { return KerML::Parser::parser::token::make_KEYWORD_TYPE(); }
"typed" { return KerML::Parser::parser::token::make_KEYWORD_TYPED(); }
"typing" { return KerML::Parser::parser::token::make_KEYWORD_TYPING(); }
"unions" { return KerML::Parser::parser::token::make_KEYWORD_UNIONS(); }
"xor" { return KerML::Parser::parser::token::make_KEYWORD_XOR(); }
"var" { return KerML::Parser::parser::token::make_KEYWORD_VAR(); }
"locale" { return KerML::Parser::parser::token::make_KEYWORD_LOCALE(); }
"standard" { return KerML::Parser::parser::token::make_KEYWORD_STANDARD(); }
"library" { return KerML::Parser::parser::token::make_KEYWORD_LIBRARY(); }
"constant" { return KerML::Parser::parser::token::make_KEYWORD_CONSTANT(); }
"meta" {return KerML::Parser::parser::token::make_KEYWORD_META();}

";" { return KerML::Parser::parser::token::make_SYMBOL_STATEMENT_DELIMITER(); }
"*" { return KerML::Parser::parser::token::make_SYMBOL_STAR(); }
"::" { return KerML::Parser::parser::token::make_SYMBOL_NAMESPACE_SUBSET(); }
":" { return KerML::Parser::parser::token::make_SYMBOL_TYPED_BY(); }
":>" { return KerML::Parser::parser::token::make_SYMBOL_SPECIALIZES(); }
"::>" { return KerML::Parser::parser::token::make_SYMBOL_REFERENCES(); }
":>>" { return KerML::Parser::parser::token::make_SYMBOL_REDEFINES(); }
"~" { return KerML::Parser::parser::token::make_SYMBOL_CONJUNGATES(); }
"(" { return KerML::Parser::parser::token::make_SYMBOL_ROUND_BRACKET_OPEN(); }
")" { return KerML::Parser::parser::token::make_SYMBOL_ROUND_BRACKET_CLOSE(); }
"\{" { return KerML::Parser::parser::token::make_SYMBOL_CURLY_BRACKET_OPEN(); }
"\}" { return KerML::Parser::parser::token::make_SYMBOL_CURLY_BRACKET_CLOSE(); }
"[" { return KerML::Parser::parser::token::make_SYMBOL_SQUARE_BRACKET_OPEN(); }
"]" { return KerML::Parser::parser::token::make_SYMBOL_SQUARE_BRACKET_CLOSE(); }
"," { return KerML::Parser::parser::token::make_SYMBOL_COMMA(); }
"@" { return KerML::Parser::parser::token::make_SYMBOL_AT(); }
"#" { return KerML::Parser::parser::token::make_SYMBOL_HASHTAG(); }
"%" { return KerML::Parser::parser::token::make_SYMBOL_MOD(); }
"&" { return KerML::Parser::parser::token::make_SYMBOL_AND(); }
"^" { return KerML::Parser::parser::token::make_SYMBOL_UPPER(); }
"|" { return KerML::Parser::parser::token::make_SYMBOL_VERTICAL_LINE(); }
"**" { return KerML::Parser::parser::token::make_SYMBOL_DOUBLE_STAR(); }
"+" { return KerML::Parser::parser::token::make_SYMBOL_PLUS(); }
"-" { return KerML::Parser::parser::token::make_SYMBOL_MINUS(); }
"/" { return KerML::Parser::parser::token::make_SYMBOL_SLASH(); }
"->" { return KerML::Parser::parser::token::make_SYMBOL_ARROOW(); }
"." { return KerML::Parser::parser::token::make_SYMBOL_DOT(); }
".." { return KerML::Parser::parser::token::make_SYMBOL_DDOT(); }
"<" { return KerML::Parser::parser::token::make_SYMBOL_SMALLER(); }
"<=" { return KerML::Parser::parser::token::make_SYMBOL_SMALLER_EQUAL(); }
"=" { return KerML::Parser::parser::token::make_SYMBOL_ASSIGN(); }
":=" { return KerML::Parser::parser::token::make_SYMBOL_DEF_ASSIGN(); }
"==" { return KerML::Parser::parser::token::make_SYMBOL_EQUALS(); }
"===" { return KerML::Parser::parser::token::make_SYMBOL_IFF_EQUALS(); }
"!=" { return KerML::Parser::parser::token::make_SYMBOL_NOT_EQUALS(); }
"!==" { return KerML::Parser::parser::token::make_SYMBOL_IFF_NOT_EQUALS(); }
">" { return KerML::Parser::parser::token::make_SYMBOL_GREATER(); }
">=" { return KerML::Parser::parser::token::make_SYMBOL_GREATER_EQUALS(); }
"?" { return KerML::Parser::parser::token::make_SYMBOL_QUESTION(); }
"??" { return KerML::Parser::parser::token::make_SYMBOL_DQUESTION(); }
".?" { return KerML::Parser::parser::token::make_SYMBOL_DOT_QUESTION(); }

[a-zA-Z_][a-zA-Z0-9_]*   { 
    std::string ident(yytext, yyleng);  // yytext → std::string
    return KerML::Parser::parser::make_BASIC_NAME(ident);
}
[0-9]+ { 
    int value = std::stoi(std::string(yytext, yyleng));
    return KerML::Parser::parser::make_NUMBER(value);
}
"\'"[a-zA-Z_][a-zA-Z0-9_.-]* "\'" { 
    std::string ident(yytext, yyleng);  // yytext → std::string
    return KerML::Parser::parser::make_UNRESTRICTED_NAME(ident);
}
[-+]?[0-9]+"."[0-9]+      { 
    double value = std::stod(std::string(yytext, yyleng));
    return KerML::Parser::parser::make_DECIMAL_VALUE(value);
}
[-+]?[0-9]+(\.[0-9]+)?[eE][-+]?[0-9]+ {
    double value = std::stod(std::string(yytext, yyleng));
    return KerML::Parser::parser::make_EXPONENTIAL_VALUE(value);
}

[ \t\r\n]+         { }

"//".*   {
    std::string ident(yytext, yyleng);  // yytext → std::string
    return KerML::Parser::parser::make_SINGLE_LINE_COMMENT(ident);
}
"/*"([^*]|\*+[^*/])*\*+"\\"   {
    std::string ident(yytext, yyleng);  // yytext → std::string
    return KerML::Parser::parser::make_BLOCK_COMMENT(ident);
}
"\""([^\"\\]|\\.)*"\"" {
    std::string ident(yytext, yyleng);  // yytext → std::string
    return KerML::Parser::parser::make_STRING(ident);
}

%%