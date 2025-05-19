%{
    #include "KerMLBisonParser.h"
    #include <string>
    #include <cstdlib>
    #include "KerMLFlexScanner.h"
%}


%option nodefault
%option noyywrap
%option c++
%option nounput noinput batch debug
%option yyclass="KerMLFlexScanner"



/* Definitionen von regulären Ausdrücken */

%%
"about" { return KerML::Parser::parser::token::KEYWORD_ABOUT; }
"abstract" { return KerML::Parser::parser::token::KEYWORD_ABSTRACT; }
"alias" { return KerML::Parser::parser::token::KEYWORD_ALIAS; }
"all" { return KerML::Parser::parser::token::KEYWORD_ALL; }
"and" { return KerML::Parser::parser::token::KEYWORD_AND; }
"as" { return KerML::Parser::parser::token::KEYWORD_AS; }
"assoc" { return KerML::Parser::parser::token::KEYWORD_ASSOC; }
"behavior" { return KerML::Parser::parser::token::KEYWORD_BEHAVIOR; }
"binding" { return KerML::Parser::parser::token::KEYWORD_BINDING; }
"bool" { return KerML::Parser::parser::token::KEYWORD_BOOL; }
"by" { return KerML::Parser::parser::token::KEYWORD_BY; }
"chains" { return KerML::Parser::parser::token::KEYWORD_CHAINS; }
"class" { return KerML::Parser::parser::token::KEYWORD_CLASS; }
"classifier" { return KerML::Parser::parser::token::KEYWORD_CLASSIFIER; }
"comment" { return KerML::Parser::parser::token::KEYWORD_COMMENT; }
"composite" { return KerML::Parser::parser::token::KEYWORD_COMPOSITE; }
"conjugate" { return KerML::Parser::parser::token::KEYWORD_CONJUGATE; }
"conjugates" { return KerML::Parser::parser::token::KEYWORD_CONJUGATES; }
"conjugation" { return KerML::Parser::parser::token::KEYWORD_CONJUGATION; }
"connector" { return KerML::Parser::parser::token::KEYWORD_CONNECTOR; }
"datatype" { return KerML::Parser::parser::token::KEYWORD_DATATYPE; }
"default" { return KerML::Parser::parser::token::KEYWORD_DEFAULT; }
"dependency" { return KerML::Parser::parser::token::KEYWORD_DEPENDENCY; }
"derived" { return KerML::Parser::parser::token::KEYWORD_DERIVED; }
"differences" { return KerML::Parser::parser::token::KEYWORD_DIFFERENCES; }
"disjoining" { return KerML::Parser::parser::token::KEYWORD_DISJOINING; }
"disjoint" { return KerML::Parser::parser::token::KEYWORD_DISJOINT; }
"doc" { return KerML::Parser::parser::token::KEYWORD_DOC; }
"else" { return KerML::Parser::parser::token::KEYWORD_ELSE; }
"end" { return KerML::Parser::parser::token::KEYWORD_END; }
"expr" { return KerML::Parser::parser::token::KEYWORD_EXPR; }
"false" { return KerML::Parser::parser::token::KEYWORD_FALSE; }
"feature" { return KerML::Parser::parser::token::KEYWORD_FEATURE; }
"featured" { return KerML::Parser::parser::token::KEYWORD_FEATURED; }
"featuring" { return KerML::Parser::parser::token::KEYWORD_FEATURING; }
"filter" { return KerML::Parser::parser::token::KEYWORD_FILTER; }
"first" { return KerML::Parser::parser::token::KEYWORD_FIRST; }
"flow" { return KerML::Parser::parser::token::KEYWORD_FLOW; }
"for" { return KerML::Parser::parser::token::KEYWORD_FOR; }
"from" { return KerML::Parser::parser::token::KEYWORD_FROM; }
"function" { return KerML::Parser::parser::token::KEYWORD_FUNCTION; }
"hastype" { return KerML::Parser::parser::token::KEYWORD_HASTYPE; }
"if" { return KerML::Parser::parser::token::KEYWORD_IF; }
"intersects" { return KerML::Parser::parser::token::KEYWORD_INTERSECTS; }
"implies" { return KerML::Parser::parser::token::KEYWORD_IMPLIES; }
"import" { return KerML::Parser::parser::token::KEYWORD_IMPORT; }
"in" { return KerML::Parser::parser::token::KEYWORD_IN; }
"inout" { return KerML::Parser::parser::token::KEYWORD_INOUT; }
"interaction" { return KerML::Parser::parser::token::KEYWORD_INTERACTION; }
"inv" { return KerML::Parser::parser::token::KEYWORD_INV; }
"inverse" { return KerML::Parser::parser::token::KEYWORD_INVERSE; }
"inverting" { return KerML::Parser::parser::token::KEYWORD_INVERTING; }
"istype" { return KerML::Parser::parser::token::KEYWORD_ISTYPE; }
"language" { return KerML::Parser::parser::token::KEYWORD_LANGUAGE; }
"member" { return KerML::Parser::parser::token::KEYWORD_MEMBER; }
"metaclass" { return KerML::Parser::parser::token::KEYWORD_METACLASS; }
"metadata" { return KerML::Parser::parser::token::KEYWORD_METADATA; }
"multiplicity" { return KerML::Parser::parser::token::KEYWORD_MULTIPLICITY; }
"namespace" { return KerML::Parser::parser::token::KEYWORD_NAMESPACE; }
"nonunique" { return KerML::Parser::parser::token::KEYWORD_NONUNIQUE; }
"not" { return KerML::Parser::parser::token::KEYWORD_NOT; }
"null" { return KerML::Parser::parser::token::KEYWORD_NULL; }
"of" { return KerML::Parser::parser::token::KEYWORD_OF; }
"or" { return KerML::Parser::parser::token::KEYWORD_OR; }
"ordered" { return KerML::Parser::parser::token::KEYWORD_ORDERED; }
"out" { return KerML::Parser::parser::token::KEYWORD_OUT; }
"package" { return KerML::Parser::parser::token::KEYWORD_PACKAGE; }
"potion" { return KerML::Parser::parser::token::KEYWORD_PORTION; }
"predicate" { return KerML::Parser::parser::token::KEYWORD_PREDICATE; }
"private" { return KerML::Parser::parser::token::KEYWORD_PRIVATE; }
"protected" { return KerML::Parser::parser::token::KEYWORD_PROTECTED; }
"public" { return KerML::Parser::parser::token::KEYWORD_PUBLIC; }
"readonly" { return KerML::Parser::parser::token::KEYWORD_READONLY; }
"redefines" { return KerML::Parser::parser::token::KEYWORD_REDEFINES; }
"redefinition" { return KerML::Parser::parser::token::KEYWORD_REDEFINITION; }
"references" { return KerML::Parser::parser::token::KEYWORD_REFERENCES; }
"rep" { return KerML::Parser::parser::token::KEYWORD_REP; }
"return" { return KerML::Parser::parser::token::KEYWORD_RETURN; }
"specialization" { return KerML::Parser::parser::token::KEYWORD_SPECILIZATION; }
"specializes" { return KerML::Parser::parser::token::KEYWORD_SPECIALIZES; }
"step" { return KerML::Parser::parser::token::KEYWORD_STEP; }
"struct" { return KerML::Parser::parser::token::KEYWORD_STRUCT; }
"subclassifier" { return KerML::Parser::parser::token::KEYWORD_SUBCLASSIFIER; }
"subset" { return KerML::Parser::parser::token::KEYWORD_SUBSET; }
"subsets" { return KerML::Parser::parser::token::KEYWORD_SUBSETS; }
"subtype" { return KerML::Parser::parser::token::KEYWORD_SUBTYPE; }
"succession" { return KerML::Parser::parser::token::KEYWORD_SUCCSESSION; }
"then" { return KerML::Parser::parser::token::KEYWORD_THEN; }
"to" { return KerML::Parser::parser::token::KEYWORD_TO; }
"true" { return KerML::Parser::parser::token::KEYWORD_TRUE; }
"type" { return KerML::Parser::parser::token::KEYWORD_TYPE; }
"typed" { return KerML::Parser::parser::token::KEYWORD_TYPED; }
"typing" { return KerML::Parser::parser::token::KEYWORD_TYPING; }
"unions" { return KerML::Parser::parser::token::KEYWORD_UNIONS; }
"xor" { return KerML::Parser::parser::token::KEYWORD_XOR; }
"var" { return KerML::Parser::parser::token::KEYWORD_VAR; }
"locale" { return KerML::Parser::parser::token::KEYWORD_LOCALE; }
"standard" { return KerML::Parser::parser::token::KEYWORD_STANDARD; }
"library" { return KerML::Parser::parser::token::KEYWORD_LIBRARY; }
"constant" { return KerML::Parser::parser::token::KEYWORD_CONSTANT; }
"meta" {return KerML::Parser::parser::token::KEYWORD_META;}

";" { return KerML::Parser::parser::token::SYMBOL_STATEMENT_DELIMITER; }
"*" { return KerML::Parser::parser::token::SYMBOL_STAR; }
"::" { return KerML::Parser::parser::token::SYMBOL_NAMESPACE_SUBSET; }
":" { return KerML::Parser::parser::token::SYMBOL_TYPED_BY; }
":>" { return KerML::Parser::parser::token::SYMBOL_SPECIALIZES; }
"::>" { return KerML::Parser::parser::token::SYMBOL_REFERENCES; }
":>>" { return KerML::Parser::parser::token::SYMBOL_REDEFINES; }
"~" { return KerML::Parser::parser::token::SYMBOL_CONJUNGATES; }
"(" { return KerML::Parser::parser::token::SYMBOL_ROUND_BRACKET_OPEN; }
")" { return KerML::Parser::parser::token::SYMBOL_ROUND_BRACKET_CLOSE; }
"\{" { return KerML::Parser::parser::token::SYMBOL_CURLY_BRACKET_OPEN; }
"\}" { return KerML::Parser::parser::token::SYMBOL_CURLY_BRACKET_CLOSE; }
"[" { return KerML::Parser::parser::token::SYMBOL_SQUARE_BRACKET_OPEN; }
"]" { return KerML::Parser::parser::token::SYMBOL_SQUARE_BRACKET_CLOSE; }
"," { return KerML::Parser::parser::token::SYMBOL_COMMA; }
"@" { return KerML::Parser::parser::token::SYMBOL_AT; }
"#" { return KerML::Parser::parser::token::SYMBOL_HASHTAG; }
"%" { return KerML::Parser::parser::token::SYMBOL_MOD; }
"&" { return KerML::Parser::parser::token::SYMBOL_AND; }
"^" { return KerML::Parser::parser::token::SYMBOL_UPPER; }
"|" { return KerML::Parser::parser::token::SYMBOL_VERTICAL_LINE; }
"**" { return KerML::Parser::parser::token::SYMBOL_DOUBLE_STAR; }
"+" { return KerML::Parser::parser::token::SYMBOL_PLUS; }
"-" { return KerML::Parser::parser::token::SYMBOL_MINUS; }
"/" { return KerML::Parser::parser::token::SYMBOL_SLASH; }
"->" { return KerML::Parser::parser::token::SYMBOL_ARROOW; }
"." { return KerML::Parser::parser::token::SYMBOL_DOT; }
".." { return KerML::Parser::parser::token::SYMBOL_DDOT; }
"<" { return KerML::Parser::parser::token::SYMBOL_SMALLER; }
"<=" { return KerML::Parser::parser::token::SYMBOL_SMALLER_EQUAL; }
"=" { return KerML::Parser::parser::token::SYMBOL_ASSIGN; }
":=" { return KerML::Parser::parser::token::SYMBOL_DEF_ASSIGN; }
"==" { return KerML::Parser::parser::token::SYMBOL_EQUALS; }
"===" { return KerML::Parser::parser::token::SYMBOL_IFF_EQUALS; }
"!=" { return KerML::Parser::parser::token::SYMBOL_NOT_EQUALS; }
"!==" { return KerML::Parser::parser::token::SYMBOL_IFF_NOT_EQUALS; }
">" { return KerML::Parser::parser::token::SYMBOL_GREATER; }
">=" { return KerML::Parser::parser::token::SYMBOL_GREATER_EQUALS; }
"?" { return KerML::Parser::parser::token::SYMBOL_QUESTION; }
"??" { return KerML::Parser::parser::token::SYMBOL_DQUESTION; }
".?" { return KerML::Parser::parser::token::SYMBOL_DOT_QUESTION; }

[a-zA-Z_][a-zA-Z0-9_]*   return KerMLFlexScanner::make_BASIC_NAME(yytext);

[0-9]+ { 
    int value = std::stoi(std::string(yytext, yyleng));
    return make_NUMBER(value);
}
"\'"[a-zA-Z_][a-zA-Z0-9_.-]* "\'" { 
    std::string ident(yytext, yyleng);  // yytext → std::string
    return make_UNRESTRICTED_NAME(ident);
}
[-+]?[0-9]+"."[0-9]+      { 
    double value = std::stod(std::string(yytext, yyleng));
    return make_DECIMAL_VALUE(value);
}
[-+]?[0-9]+(\.[0-9]+)?[eE][-+]?[0-9]+ {
    double value = std::stod(std::string(yytext, yyleng));
    return make_EXPONENTIAL_VALUE(value);
}

[ \t\r\n]+         { }

"//".*   {
    std::string ident(yytext, yyleng);  // yytext → std::string
    return make_SINGLE_LINE_COMMENT(ident);
}
"/*"([^*]|\*+[^*/])*\*+"\\"   {
    std::string ident(yytext, yyleng);  // yytext → std::string
    return make_BLOCK_COMMENT(ident);
}
"\""([^\"\\]|\\.)*"\"" {
    std::string ident(yytext, yyleng);  // yytext → std::string
    return make_STRING(ident);
}

%%