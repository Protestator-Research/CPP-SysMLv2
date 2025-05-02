
// Generated from SysMLv2.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "SysMLv2Parser.h"
#include "../sysmlv2file_global.h"

/**
 * This interface defines an abstract listener for a parse tree produced by SysMLv2Parser.
 */
class SYSMLV2FILE_EXPORT SysMLv2Listener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStart(SysMLv2Parser::StartContext *ctx) = 0;
  virtual void exitStart(SysMLv2Parser::StartContext *ctx) = 0;

  virtual void enterStartRule(SysMLv2Parser::StartRuleContext *ctx) = 0;
  virtual void exitStartRule(SysMLv2Parser::StartRuleContext *ctx) = 0;

  virtual void enterElements(SysMLv2Parser::ElementsContext *ctx) = 0;
  virtual void exitElements(SysMLv2Parser::ElementsContext *ctx) = 0;

  virtual void enterDependency(SysMLv2Parser::DependencyContext *ctx) = 0;
  virtual void exitDependency(SysMLv2Parser::DependencyContext *ctx) = 0;

  virtual void enterTextual_representaion(SysMLv2Parser::Textual_representaionContext *ctx) = 0;
  virtual void exitTextual_representaion(SysMLv2Parser::Textual_representaionContext *ctx) = 0;

  virtual void enterComment(SysMLv2Parser::CommentContext *ctx) = 0;
  virtual void exitComment(SysMLv2Parser::CommentContext *ctx) = 0;

  virtual void enterPart(SysMLv2Parser::PartContext *ctx) = 0;
  virtual void exitPart(SysMLv2Parser::PartContext *ctx) = 0;

  virtual void enterPort(SysMLv2Parser::PortContext *ctx) = 0;
  virtual void exitPort(SysMLv2Parser::PortContext *ctx) = 0;

  virtual void enterAttribute(SysMLv2Parser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(SysMLv2Parser::AttributeContext *ctx) = 0;

  virtual void enterItem(SysMLv2Parser::ItemContext *ctx) = 0;
  virtual void exitItem(SysMLv2Parser::ItemContext *ctx) = 0;

  virtual void enterPackage(SysMLv2Parser::PackageContext *ctx) = 0;
  virtual void exitPackage(SysMLv2Parser::PackageContext *ctx) = 0;

  virtual void enterAssertion(SysMLv2Parser::AssertionContext *ctx) = 0;
  virtual void exitAssertion(SysMLv2Parser::AssertionContext *ctx) = 0;

  virtual void enterActions(SysMLv2Parser::ActionsContext *ctx) = 0;
  virtual void exitActions(SysMLv2Parser::ActionsContext *ctx) = 0;

  virtual void enterAlias(SysMLv2Parser::AliasContext *ctx) = 0;
  virtual void exitAlias(SysMLv2Parser::AliasContext *ctx) = 0;

  virtual void enterVisibility(SysMLv2Parser::VisibilityContext *ctx) = 0;
  virtual void exitVisibility(SysMLv2Parser::VisibilityContext *ctx) = 0;

  virtual void enterImport_rule(SysMLv2Parser::Import_ruleContext *ctx) = 0;
  virtual void exitImport_rule(SysMLv2Parser::Import_ruleContext *ctx) = 0;

  virtual void enterAbstraction(SysMLv2Parser::AbstractionContext *ctx) = 0;
  virtual void exitAbstraction(SysMLv2Parser::AbstractionContext *ctx) = 0;

  virtual void enterVariation(SysMLv2Parser::VariationContext *ctx) = 0;
  virtual void exitVariation(SysMLv2Parser::VariationContext *ctx) = 0;

  virtual void enterVariant(SysMLv2Parser::VariantContext *ctx) = 0;
  virtual void exitVariant(SysMLv2Parser::VariantContext *ctx) = 0;

  virtual void enterFunction(SysMLv2Parser::FunctionContext *ctx) = 0;
  virtual void exitFunction(SysMLv2Parser::FunctionContext *ctx) = 0;

  virtual void enterInput(SysMLv2Parser::InputContext *ctx) = 0;
  virtual void exitInput(SysMLv2Parser::InputContext *ctx) = 0;

  virtual void enterOutput(SysMLv2Parser::OutputContext *ctx) = 0;
  virtual void exitOutput(SysMLv2Parser::OutputContext *ctx) = 0;

  virtual void enterReturn(SysMLv2Parser::ReturnContext *ctx) = 0;
  virtual void exitReturn(SysMLv2Parser::ReturnContext *ctx) = 0;

  virtual void enterCommand_definition(SysMLv2Parser::Command_definitionContext *ctx) = 0;
  virtual void exitCommand_definition(SysMLv2Parser::Command_definitionContext *ctx) = 0;

  virtual void enterConnectTo(SysMLv2Parser::ConnectToContext *ctx) = 0;
  virtual void exitConnectTo(SysMLv2Parser::ConnectToContext *ctx) = 0;

  virtual void enterType_definition(SysMLv2Parser::Type_definitionContext *ctx) = 0;
  virtual void exitType_definition(SysMLv2Parser::Type_definitionContext *ctx) = 0;

  virtual void enterSuper_class_definition(SysMLv2Parser::Super_class_definitionContext *ctx) = 0;
  virtual void exitSuper_class_definition(SysMLv2Parser::Super_class_definitionContext *ctx) = 0;

  virtual void enterAbout(SysMLv2Parser::AboutContext *ctx) = 0;
  virtual void exitAbout(SysMLv2Parser::AboutContext *ctx) = 0;

  virtual void enterSpecilization(SysMLv2Parser::SpecilizationContext *ctx) = 0;
  virtual void exitSpecilization(SysMLv2Parser::SpecilizationContext *ctx) = 0;

  virtual void enterDecriptor(SysMLv2Parser::DecriptorContext *ctx) = 0;
  virtual void exitDecriptor(SysMLv2Parser::DecriptorContext *ctx) = 0;

  virtual void enterNamelist(SysMLv2Parser::NamelistContext *ctx) = 0;
  virtual void exitNamelist(SysMLv2Parser::NamelistContext *ctx) = 0;

  virtual void enterName(SysMLv2Parser::NameContext *ctx) = 0;
  virtual void exitName(SysMLv2Parser::NameContext *ctx) = 0;

  virtual void enterAddress(SysMLv2Parser::AddressContext *ctx) = 0;
  virtual void exitAddress(SysMLv2Parser::AddressContext *ctx) = 0;

  virtual void enterBracketed_content(SysMLv2Parser::Bracketed_contentContext *ctx) = 0;
  virtual void exitBracketed_content(SysMLv2Parser::Bracketed_contentContext *ctx) = 0;

  virtual void enterFuction_arguments(SysMLv2Parser::Fuction_argumentsContext *ctx) = 0;
  virtual void exitFuction_arguments(SysMLv2Parser::Fuction_argumentsContext *ctx) = 0;

  virtual void enterArgument(SysMLv2Parser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(SysMLv2Parser::ArgumentContext *ctx) = 0;

  virtual void enterDelimiter_rule(SysMLv2Parser::Delimiter_ruleContext *ctx) = 0;
  virtual void exitDelimiter_rule(SysMLv2Parser::Delimiter_ruleContext *ctx) = 0;

  virtual void enterMultiplicity(SysMLv2Parser::MultiplicityContext *ctx) = 0;
  virtual void exitMultiplicity(SysMLv2Parser::MultiplicityContext *ctx) = 0;

  virtual void enterUnit(SysMLv2Parser::UnitContext *ctx) = 0;
  virtual void exitUnit(SysMLv2Parser::UnitContext *ctx) = 0;

  virtual void enterDefinition_rule(SysMLv2Parser::Definition_ruleContext *ctx) = 0;
  virtual void exitDefinition_rule(SysMLv2Parser::Definition_ruleContext *ctx) = 0;


};

