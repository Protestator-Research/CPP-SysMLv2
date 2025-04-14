
// Generated from SysMLv2.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "../../sysmlv2file_global.h"


class SYSMLV2FILE_EXPORT SysMLv2Parser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, DEPENDENCY = 12, REPRESENTATION = 13, 
    LANGUAGE_DESCRIPTOR = 14, DOCUMENTATION = 15, COMMENT = 16, ABOUT = 17, 
    PART = 18, BLOCK_COMMENT = 19, LINE_COMMENT = 20, TO = 21, FROM = 22, 
    FOR = 23, DELIMITER = 24, PORT = 25, ITEM = 26, PACKAGE = 27, DEFINITION = 28, 
    ATTRIBUTE = 29, MEASURABLE = 30, CONTROLLABLE = 31, ASSERT = 32, ACTION = 33, 
    ALIAS = 34, PRIVATE = 35, PROTECTED = 36, PUBLIC = 37, IMPORT = 38, 
    ABSTRACT = 39, VARIATION = 40, VARIANT = 41, STAR = 42, CALC = 43, IN = 44, 
    OUT = 45, RETURN = 46, HASHTAG = 47, COMMAND = 48, VARIABLE = 49, CONNECT_TO = 50, 
    INSTANCE = 51, INDIVIDUAL = 52, SUPERCLASS = 53, NUMBER = 54, NAME = 55, 
    INT = 56, WS = 57
  };

  enum {
    RuleStart = 0, RuleStartRule = 1, RuleElements = 2, RuleDependency = 3, 
    RuleTextual_representaion = 4, RuleComment = 5, RulePart = 6, RulePort = 7, 
    RuleAttribute = 8, RuleItem = 9, RulePackage = 10, RuleAssertion = 11, 
    RuleActions = 12, RuleAlias = 13, RuleVisibility = 14, RuleImport_rule = 15, 
    RuleAbstraction = 16, RuleVariation = 17, RuleVariant = 18, RuleFunction = 19, 
    RuleInput = 20, RuleOutput = 21, RuleReturn = 22, RuleCommand_definition = 23, 
    RuleConnectTo = 24, RuleType_definition = 25, RuleSuper_class_definition = 26, 
    RuleAbout = 27, RuleSpecilization = 28, RuleDecriptor = 29, RuleNamelist = 30, 
    RuleName = 31, RuleAddress = 32, RuleBracketed_content = 33, RuleFuction_arguments = 34, 
    RuleArgument = 35, RuleDelimiter_rule = 36, RuleMultiplicity = 37, RuleUnit = 38, 
    RuleDefinition_rule = 39
  };

  explicit SysMLv2Parser(antlr4::TokenStream *input);

  SysMLv2Parser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~SysMLv2Parser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class StartContext;
  class StartRuleContext;
  class ElementsContext;
  class DependencyContext;
  class Textual_representaionContext;
  class CommentContext;
  class PartContext;
  class PortContext;
  class AttributeContext;
  class ItemContext;
  class PackageContext;
  class AssertionContext;
  class ActionsContext;
  class AliasContext;
  class VisibilityContext;
  class Import_ruleContext;
  class AbstractionContext;
  class VariationContext;
  class VariantContext;
  class FunctionContext;
  class InputContext;
  class OutputContext;
  class ReturnContext;
  class Command_definitionContext;
  class ConnectToContext;
  class Type_definitionContext;
  class Super_class_definitionContext;
  class AboutContext;
  class SpecilizationContext;
  class DecriptorContext;
  class NamelistContext;
  class NameContext;
  class AddressContext;
  class Bracketed_contentContext;
  class Fuction_argumentsContext;
  class ArgumentContext;
  class Delimiter_ruleContext;
  class MultiplicityContext;
  class UnitContext;
  class Definition_ruleContext; 

  class  StartContext : public antlr4::ParserRuleContext {
  public:
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ElementsContext *> elements();
    ElementsContext* elements(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartContext* start();

  class  StartRuleContext : public antlr4::ParserRuleContext {
  public:
    StartRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StartContext *start();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartRuleContext* startRule();

  class  ElementsContext : public antlr4::ParserRuleContext {
  public:
    ElementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DependencyContext *dependency();
    CommentContext *comment();
    PartContext *part();
    PortContext *port();
    ItemContext *item();
    PackageContext *package();
    AttributeContext *attribute();
    AssertionContext *assertion();
    ActionsContext *actions();
    AliasContext *alias();
    VisibilityContext *visibility();
    Import_ruleContext *import_rule();
    AbstractionContext *abstraction();
    VariationContext *variation();
    VariantContext *variant();
    FunctionContext *function();
    InputContext *input();
    OutputContext *output();
    ReturnContext *return_();
    Command_definitionContext *command_definition();
    Textual_representaionContext *textual_representaion();
    ConnectToContext *connectTo();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementsContext* elements();

  class  DependencyContext : public antlr4::ParserRuleContext {
  public:
    DependencyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEPENDENCY();
    std::vector<NamelistContext *> namelist();
    NamelistContext* namelist(size_t i);
    antlr4::tree::TerminalNode *TO();
    antlr4::tree::TerminalNode *DELIMITER();
    antlr4::tree::TerminalNode *FROM();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DependencyContext* dependency();

  class  Textual_representaionContext : public antlr4::ParserRuleContext {
  public:
    Textual_representaionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DecriptorContext *decriptor();
    antlr4::tree::TerminalNode *BLOCK_COMMENT();
    antlr4::tree::TerminalNode *REPRESENTATION();
    antlr4::tree::TerminalNode *NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Textual_representaionContext* textual_representaion();

  class  CommentContext : public antlr4::ParserRuleContext {
  public:
    CommentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BLOCK_COMMENT();
    antlr4::tree::TerminalNode *COMMENT();
    antlr4::tree::TerminalNode *NAME();
    AboutContext *about();
    antlr4::tree::TerminalNode *DOCUMENTATION();
    antlr4::tree::TerminalNode *LINE_COMMENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CommentContext* comment();

  class  PartContext : public antlr4::ParserRuleContext {
  public:
    PartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PART();
    antlr4::tree::TerminalNode *NAME();
    Delimiter_ruleContext *delimiter_rule();
    antlr4::tree::TerminalNode *DEFINITION();
    SpecilizationContext *specilization();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PartContext* part();

  class  PortContext : public antlr4::ParserRuleContext {
  public:
    PortContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PORT();
    antlr4::tree::TerminalNode *NAME();
    Delimiter_ruleContext *delimiter_rule();
    antlr4::tree::TerminalNode *DEFINITION();
    SpecilizationContext *specilization();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PortContext* port();

  class  AttributeContext : public antlr4::ParserRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME();
    Delimiter_ruleContext *delimiter_rule();
    antlr4::tree::TerminalNode *ATTRIBUTE();
    antlr4::tree::TerminalNode *MEASURABLE();
    antlr4::tree::TerminalNode *CONTROLLABLE();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *DEFINITION();
    MultiplicityContext *multiplicity();
    Type_definitionContext *type_definition();
    UnitContext *unit();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeContext* attribute();

  class  ItemContext : public antlr4::ParserRuleContext {
  public:
    ItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ITEM();
    antlr4::tree::TerminalNode *NAME();
    Delimiter_ruleContext *delimiter_rule();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ItemContext* item();

  class  PackageContext : public antlr4::ParserRuleContext {
  public:
    PackageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PACKAGE();
    antlr4::tree::TerminalNode *NAME();
    Delimiter_ruleContext *delimiter_rule();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PackageContext* package();

  class  AssertionContext : public antlr4::ParserRuleContext {
  public:
    AssertionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSERT();
    antlr4::tree::TerminalNode *NAME();
    Delimiter_ruleContext *delimiter_rule();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssertionContext* assertion();

  class  ActionsContext : public antlr4::ParserRuleContext {
  public:
    ActionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ACTION();
    Fuction_argumentsContext *fuction_arguments();
    Bracketed_contentContext *bracketed_content();
    antlr4::tree::TerminalNode *DEFINITION();
    antlr4::tree::TerminalNode *NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ActionsContext* actions();

  class  AliasContext : public antlr4::ParserRuleContext {
  public:
    AliasContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ALIAS();
    std::vector<AddressContext *> address();
    AddressContext* address(size_t i);
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AliasContext* alias();

  class  VisibilityContext : public antlr4::ParserRuleContext {
  public:
    VisibilityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PRIVATE();
    StartContext *start();
    antlr4::tree::TerminalNode *PUBLIC();
    antlr4::tree::TerminalNode *PROTECTED();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VisibilityContext* visibility();

  class  Import_ruleContext : public antlr4::ParserRuleContext {
  public:
    Import_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    AddressContext *address();
    antlr4::tree::TerminalNode *DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Import_ruleContext* import_rule();

  class  AbstractionContext : public antlr4::ParserRuleContext {
  public:
    AbstractionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ABSTRACT();
    StartContext *start();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AbstractionContext* abstraction();

  class  VariationContext : public antlr4::ParserRuleContext {
  public:
    VariationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIATION();
    StartContext *start();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariationContext* variation();

  class  VariantContext : public antlr4::ParserRuleContext {
  public:
    VariantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIANT();
    PartContext *part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariantContext* variant();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CALC();
    Definition_ruleContext *definition_rule();
    Bracketed_contentContext *bracketed_content();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionContext* function();

  class  InputContext : public antlr4::ParserRuleContext {
  public:
    InputContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *NAME();
    Type_definitionContext *type_definition();
    antlr4::tree::TerminalNode *DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InputContext* input();

  class  OutputContext : public antlr4::ParserRuleContext {
  public:
    OutputContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OUT();
    antlr4::tree::TerminalNode *NAME();
    Type_definitionContext *type_definition();
    antlr4::tree::TerminalNode *DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OutputContext* output();

  class  ReturnContext : public antlr4::ParserRuleContext {
  public:
    ReturnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    Type_definitionContext *type_definition();
    antlr4::tree::TerminalNode *DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReturnContext* return_();

  class  Command_definitionContext : public antlr4::ParserRuleContext {
  public:
    Command_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HASHTAG();
    antlr4::tree::TerminalNode *COMMAND();
    antlr4::tree::TerminalNode *NAME();
    antlr4::tree::TerminalNode *ATTRIBUTE();
    antlr4::tree::TerminalNode *DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Command_definitionContext* command_definition();

  class  ConnectToContext : public antlr4::ParserRuleContext {
  public:
    ConnectToContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AddressContext *> address();
    AddressContext* address(size_t i);
    antlr4::tree::TerminalNode *CONNECT_TO();
    antlr4::tree::TerminalNode *DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConnectToContext* connectTo();

  class  Type_definitionContext : public antlr4::ParserRuleContext {
  public:
    Type_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddressContext *address();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_definitionContext* type_definition();

  class  Super_class_definitionContext : public antlr4::ParserRuleContext {
  public:
    Super_class_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUPERCLASS();
    AddressContext *address();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Super_class_definitionContext* super_class_definition();

  class  AboutContext : public antlr4::ParserRuleContext {
  public:
    AboutContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ABOUT();
    std::vector<AddressContext *> address();
    AddressContext* address(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AboutContext* about();

  class  SpecilizationContext : public antlr4::ParserRuleContext {
  public:
    SpecilizationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddressContext *address();
    antlr4::tree::TerminalNode *SUPERCLASS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SpecilizationContext* specilization();

  class  DecriptorContext : public antlr4::ParserRuleContext {
  public:
    DecriptorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LANGUAGE_DESCRIPTOR();
    antlr4::tree::TerminalNode *NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DecriptorContext* decriptor();

  class  NamelistContext : public antlr4::ParserRuleContext {
  public:
    NamelistContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NameContext *> name();
    NameContext* name(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamelistContext* namelist();

  class  NameContext : public antlr4::ParserRuleContext {
  public:
    NameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NameContext* name();

  class  AddressContext : public antlr4::ParserRuleContext {
  public:
    AddressContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STAR();
    antlr4::tree::TerminalNode* STAR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AddressContext* address();

  class  Bracketed_contentContext : public antlr4::ParserRuleContext {
  public:
    Bracketed_contentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementsContext *> elements();
    ElementsContext* elements(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Bracketed_contentContext* bracketed_content();

  class  Fuction_argumentsContext : public antlr4::ParserRuleContext {
  public:
    Fuction_argumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentContext *> argument();
    ArgumentContext* argument(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Fuction_argumentsContext* fuction_arguments();

  class  ArgumentContext : public antlr4::ParserRuleContext {
  public:
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME();
    Type_definitionContext *type_definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArgumentContext* argument();

  class  Delimiter_ruleContext : public antlr4::ParserRuleContext {
  public:
    Delimiter_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Bracketed_contentContext *bracketed_content();
    antlr4::tree::TerminalNode *DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Delimiter_ruleContext* delimiter_rule();

  class  MultiplicityContext : public antlr4::ParserRuleContext {
  public:
    MultiplicityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MultiplicityContext* multiplicity();

  class  UnitContext : public antlr4::ParserRuleContext {
  public:
    UnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnitContext* unit();

  class  Definition_ruleContext : public antlr4::ParserRuleContext {
  public:
    Definition_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEFINITION();
    antlr4::tree::TerminalNode *NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Definition_ruleContext* definition_rule();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

