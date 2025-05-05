grammar SysMLv2_old;

start: elements* EOF;

startRule: start;

elements :  dependency |
       comment |
       part |
       port |
       item |
       package |
       attribute |
       assertion |
       actions |
       alias |
       visibility |
       import_rule |
       abstraction |
       variation |
       variant |
       function |
       input |
       output |
       return |
       command_definition |
       textual_representaion |
       connectTo;


dependency: DEPENDENCY namelist (FROM namelist)? TO namelist DELIMITER;
textual_representaion: REPRESENTATION? NAME? decriptor BLOCK_COMMENT;
comment: BLOCK_COMMENT | COMMENT NAME? about? BLOCK_COMMENT | DOCUMENTATION NAME? BLOCK_COMMENT | LINE_COMMENT;
part: PART DEFINITION? NAME specilization? delimiter_rule;
port: PORT DEFINITION? NAME specilization? delimiter_rule;
attribute: (ATTRIBUTE|MEASURABLE|CONTROLLABLE|VARIABLE) DEFINITION? NAME multiplicity? type_definition? unit? delimiter_rule;
item: ITEM NAME delimiter_rule;
package: PACKAGE NAME delimiter_rule;
assertion: ASSERT NAME delimiter_rule;
actions: ACTION DEFINITION? NAME? fuction_arguments bracketed_content;
alias: ALIAS address FOR address DELIMITER;
visibility: PRIVATE start | PUBLIC start | PROTECTED start;
import_rule: IMPORT address DELIMITER;
abstraction: ABSTRACT start;
variation: VARIATION start;
variant: VARIANT part;
function: CALC definition_rule bracketed_content;
input: IN NAME type_definition DELIMITER;
output: OUT NAME type_definition DELIMITER;
return: RETURN type_definition DELIMITER;
command_definition: HASHTAG COMMAND NAME ATTRIBUTE DELIMITER;
connectTo: address CONNECT_TO address DELIMITER;

type_definition: ':' address;
super_class_definition: SUPERCLASS address;
about: ABOUT address(','address)*;
specilization: (SUPERCLASS | ':') address;
decriptor: LANGUAGE_DESCRIPTOR '"'NAME'"';
namelist: name(',' name)*;
name: NAME | '\''NAME+'\'';
address: NAME('::'(NAME | STAR STAR?))*;
bracketed_content: '{' elements* '}';
fuction_arguments: '(' argument?(',' argument*) ')';
argument: NAME type_definition;
delimiter_rule: (bracketed_content|DELIMITER);
multiplicity: '[' (STAR | NUMBER) ']';
unit: '[' NAME ']';
definition_rule: DEFINITION NAME;


DEPENDENCY: 'dependency';
REPRESENTATION: 'rep';
LANGUAGE_DESCRIPTOR: 'language';
DOCUMENTATION: 'doc';
COMMENT: 'comment';
ABOUT: 'about';
PART: 'part';
BLOCK_COMMENT: '/*' .*? '*/';
LINE_COMMENT: '//'  ~( '\r' | '\n' )*;
TO:'to';
FROM: 'from';
FOR: 'for';
DELIMITER: ';';
PORT: 'port';
ITEM: 'item';
PACKAGE: 'package';
DEFINITION: 'def';
ATTRIBUTE: 'attribute';
MEASURABLE: 'measurable';
CONTROLLABLE: 'controllable';
ASSERT: 'assert';
ACTION: 'action';
ALIAS: 'alias';
PRIVATE: 'private';
PROTECTED: 'protected';
PUBLIC: 'public';
IMPORT: 'import';
ABSTRACT: 'abstract';
VARIATION: 'variation';
VARIANT: 'variant';
STAR: '*';
CALC: 'calc';
IN: 'in';
OUT: 'out';
RETURN: 'return';
HASHTAG: '#';
COMMAND: 'command';
VARIABLE: 'variable';
CONNECT_TO: 'connectTo';
INSTANCE: 'instance';
INDIVIDUAL: 'individual';
SUPERCLASS: ':>';


NUMBER: [0-9]+;
NAME: ('_'|[a-z]|[A-Z]|[0-9])+ ;
INT     : [0-9]+ ;
WS : [ \t\r\n]+ -> skip ;