
    #include <sysmlv2/sysmlv2file_global.h>


// Generated from ./KerML.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class SYSMLV2FILE_EXPORT KerMLParser : public antlr4::Parser {
public:
  enum {
    KEYWORD_ABOUT = 1, KEYWORD_ABSTRACT = 2, KEYWORD_ALIAS = 3, KEYWORD_ALL = 4, 
    KEYWORD_AND = 5, KEYWORD_AS = 6, KEYWORD_ASSOC = 7, KEYWORD_BEHAVIOR = 8, 
    KEYWORD_BINDING = 9, KEYWORD_BOOL = 10, KEYWORD_BY = 11, KEYWORD_CHAINS = 12, 
    KEYWORD_CLASS = 13, KEYWORD_CLASSIFIER = 14, KEYWORD_COMMENT = 15, KEYWORD_COMPOSITE = 16, 
    KEYWORD_CONJUGATE = 17, KEYWORD_CONJUGATES = 18, KEYWORD_CONJUGATION = 19, 
    KEYWORD_CONNECTOR = 20, KEYWORD_DATATYPE = 21, KEYWORD_DEFAULT = 22, 
    KEYWORD_DEPENDENCY = 23, KEYWORD_DERIVED = 24, KEYWORD_DIFFERENCES = 25, 
    KEYWORD_DISJOINING = 26, KEYWORD_DISJOINT = 27, KEYWORD_DOC = 28, KEYWORD_ELSE = 29, 
    KEYWORD_END = 30, KEYWORD_EXPR = 31, KEYWORD_FALSE = 32, KEYWORD_FEATURE = 33, 
    KEYWORD_FEATURED = 34, KEYWORD_FEATURING = 35, KEYWORD_FILTER = 36, 
    KEYWORD_FIRST = 37, KEYWORD_FLOW = 38, KEYWORD_FOR = 39, KEYWORD_FROM = 40, 
    KEYWORD_FUNCTION = 41, KEYWORD_HASTYPE = 42, KEYWORD_IF = 43, KEYWORD_INTERSECTS = 44, 
    KEYWORD_IMPLIES = 45, KEYWORD_IMPORT = 46, KEYWORD_IN = 47, KEYWORD_INOUT = 48, 
    KEYWORD_INTERACTION = 49, KEYWORD_INV = 50, KEYWORD_INVERSE = 51, KEYWORD_INVERTING = 52, 
    KEYWORD_ISTYPE = 53, KEYWORD_LANGUAGE = 54, KEYWORD_MEMBER = 55, KEYWORD_METACLASS = 56, 
    KEYWORD_METADATA = 57, KEYWORD_MULTIPLICITY = 58, KEYWORD_NAMESPACE = 59, 
    KEYWORD_NONUNIQUE = 60, KEYWORD_NOT = 61, KEYWORD_NULL = 62, KEYWORD_OF = 63, 
    KEYWORD_OR = 64, KEYWORD_ORDERED = 65, KEYWORD_OUT = 66, KEYWORD_PACKAGE = 67, 
    KEYWORD_PORTION = 68, KEYWORD_PREDICATE = 69, KEYWORD_PRIVATE = 70, 
    KEYWORD_PROTECTED = 71, KEYWORD_PUBLIC = 72, KEYWORD_READONLY = 73, 
    KEYWORD_REDEFINES = 74, KEYWORD_REDEFINITION = 75, KEYWORD_REFERENCES = 76, 
    KEYWORD_REP = 77, KEYWORD_RETURN = 78, KEYWORD_SPECIALIZATION = 79, 
    KEYWORD_SPECIALIZES = 80, KEYWORD_STEP = 81, KEYWORD_STRUCT = 82, KEYWORD_SUBCLASSIFIER = 83, 
    KEYWORD_SUBSET = 84, KEYWORD_SUBSETS = 85, KEYWORD_SUBTYPE = 86, KEYWORD_SUCCESSION = 87, 
    KEYWORD_THEN = 88, KEYWORD_TO = 89, KEYWORD_TRUE = 90, KEYWORD_TYPE = 91, 
    KEYWORD_TYPED = 92, KEYWORD_TYPING = 93, KEYWORD_UNIONS = 94, KEYWORD_XOR = 95, 
    KEYWORD_VAR = 96, KEYWORD_LOCALE = 97, KEYWORD_STANDARD = 98, KEYWORD_LIBRARY = 99, 
    KEYWORD_CONSTANT = 100, KEYWORD_CROSSES = 101, KEYWORD_META = 102, KEYWORD_NEW = 103, 
    SINGLE_LINE_NOTE = 104, MULTI_LINE_NOTE = 105, REGULAR_COMMENT = 106, 
    SYMBOL_COMMENT_BLOCK_START = 107, SYMBOL_NOTE_BLOCK_START = 108, SYMBOL_COMMENT_BLOCK_END = 109, 
    SYMBOL_STATEMENT_DELIMITER = 110, SYMBOL_STAR = 111, SYMBOL_NAMESPACE_SUBSET = 112, 
    SYMBOL_TYPED_BY = 113, SYMBOL_SPECIALIZES = 114, SYMBOL_REFERENCES = 115, 
    SYMBOL_REDEFINES = 116, SYMBOL_CONJUGATES = 117, SYMBOL_CROSSES = 118, 
    SYMBOL_ROUND_BRACKET_OPEN = 119, SYMBOL_ROUND_BRACKET_CLOSE = 120, SYMBOL_CURLY_BRACKET_OPEN = 121, 
    SYMBOL_CURLY_BRACKET_CLOSE = 122, SYMBOL_SQUARE_BRACKET_OPEN = 123, 
    SYMBOL_SQUARE_BRACKET_CLOSE = 124, SYMBOL_COMMA = 125, SYMBOL_AT = 126, 
    SYMBOL_HASHTAG = 127, SYMBOL_MOD = 128, SYMBOL_AND = 129, SYMBOL_UPPER = 130, 
    SYMBOL_VERTICAL_LINE = 131, SYMBOL_DOUBLE_STAR = 132, SYMBOL_PLUS = 133, 
    SYMBOL_MINUS = 134, SYMBOL_SLASH = 135, SYMBOL_ARROW = 136, SYMBOL_DOT = 137, 
    SYMBOL_DDOT = 138, SYMBOL_SMALLER = 139, SYMBOL_SMALLER_EQUAL = 140, 
    SYMBOL_ASSIGN = 141, SYMBOL_DEF_ASSIGN = 142, SYMBOL_EQUALS = 143, SYMBOL_IFF_EQUALS = 144, 
    SYMBOL_NOT_EQUALS = 145, SYMBOL_IFF_NOT_EQUALS = 146, SYMBOL_GREATER = 147, 
    SYMBOL_GREATER_EQUALS = 148, SYMBOL_QUESTION = 149, SYMBOL_DQUESTION = 150, 
    SYMBOL_DOT_QUESTION = 151, SYMBOL_ATAT = 152, NAME = 153, BASIC_NAME = 154, 
    UNRESTRICTED_NAME = 155, DECIMAL_VALUE = 156, EXPONENTIAL_VALUE = 157, 
    STRING_VALUE = 158, WS = 159
  };

  enum {
    RuleStart = 0, RuleStartRule = 1, RuleElements = 2, RuleIdentification = 3, 
    RuleRelationship_body = 4, RuleRelationship_owned_elements = 5, RuleRelationship_owned_element = 6, 
    RuleOwned_related_element = 7, RuleDependency = 8, RuleAnnotation = 9, 
    RuleOwned_annotation = 10, RuleAnnotating_element = 11, RuleComment = 12, 
    RuleDocumentation = 13, RuleTextual_representation = 14, RuleRoot_namespace = 15, 
    RuleNamespace = 16, RuleNamespace_declaration = 17, RuleNamespace_body = 18, 
    RuleNamespace_body_elements = 19, RuleNamespace_body_element = 20, RuleMember_prefix = 21, 
    RuleVisibility_indicator = 22, RuleNamespace_member = 23, RuleNon_feature_member = 24, 
    RuleNamespace_feature_member = 25, RuleAlias_member = 26, RuleQualified_name = 27, 
    RuleNamespace_import = 28, RuleImport_declaration = 29, RuleMembership_import = 30, 
    RuleFilter_package = 31, RuleFilter_package_member = 32, RuleElement = 33, 
    RuleNon_feature_element = 34, RuleFeature_element = 35, RuleAdditional_options = 36, 
    RuleType = 37, RuleType_prefix = 38, RuleType_declaration = 39, RuleSpecialization_part = 40, 
    RuleConjugation_part = 41, RuleType_relationship_part = 42, RuleDisjoining_part = 43, 
    RuleUnioning_part = 44, RuleIntersecting_part = 45, RuleDifferencing_part = 46, 
    RuleType_body = 47, RuleType_body_elements = 48, RuleType_body_element = 49, 
    RuleSpecialization = 50, RuleOwned_specialization = 51, RuleSpecific_type = 52, 
    RuleGeneral_type = 53, RuleConjunction = 54, RuleOwned_conjugation = 55, 
    RuleDisjoining = 56, RuleOwned_disjoining = 57, RuleUnioning = 58, RuleIntersecting = 59, 
    RuleDifferencing = 60, RuleFeature_member = 61, RuleType_feature_member = 62, 
    RuleOwned_feature_member = 63, RuleClassifier = 64, RuleClassifier_declaration = 65, 
    RuleSuperclassing_part = 66, RuleSubclassification = 67, RuleOwned_subclassification = 68, 
    RuleFeature = 69, RuleAnonymous_feature = 70, RuleFeature_prefix = 71, 
    RuleEnd_feature_prefix = 72, RuleBasic_feature_prefix = 73, RuleOwned_cross_feature_member = 74, 
    RuleOwned_cross_feature = 75, RuleFeature_direction = 76, RuleFeature_declaration = 77, 
    RuleFeature_identification = 78, RuleFeature_relationship_part = 79, 
    RuleChaining_part = 80, RuleInverting_part = 81, RuleType_featuring_part = 82, 
    RuleFeature_specialization_part = 83, RuleMultiplicity_part = 84, RuleMultiplicity_modifier = 85, 
    RuleFeature_specialization = 86, RuleTypings = 87, RuleTyped_by = 88, 
    RuleSubsettings = 89, RuleSubsets = 90, RuleReferences = 91, RuleCrosses = 92, 
    RuleRedefinitions = 93, RuleRedefines = 94, RuleFeature_typing = 95, 
    RuleOwned_feature_typing = 96, RuleSubsetting = 97, RuleOwned_subsetting = 98, 
    RuleOwned_reference_subsetting = 99, RuleOwned_cross_subsetting = 100, 
    RuleRedefinition = 101, RuleOwned_redefinition = 102, RuleOwned_feature_chain = 103, 
    RuleFeature_chain = 104, RuleOwned_feature_chaining = 105, RuleFeature_inverting = 106, 
    RuleOwned_feature_inverting = 107, RuleType_featuring = 108, RuleOwned_type_featuring = 109, 
    RuleData_type = 110, RuleClass = 111, RuleStructure = 112, RuleAssociation = 113, 
    RuleAssociation_structure = 114, RuleConnector = 115, RuleConnector_declaration = 116, 
    RuleBinary_connector_declaration = 117, RuleNary_connector_declaration = 118, 
    RuleConnector_end_member = 119, RuleConnector_end = 120, RuleOwned_cross_multiplicity_member = 121, 
    RuleOwned_cross_multiplicity = 122, RuleBinding_connector = 123, RuleBinding_connector_declaration = 124, 
    RuleSuccession = 125, RuleSuccession_declaration = 126, RuleBehavior = 127, 
    RuleStep = 128, RuleFunction = 129, RuleFunction_body = 130, RuleFunction_body_part = 131, 
    RuleReturn_feature_member = 132, RuleResult_expression_member = 133, 
    RuleExpression = 134, RulePredicate = 135, RuleBoolean_expression = 136, 
    RuleInvariant = 137, RuleOwned_expression_reference_member = 138, RuleOwned_expression_reference = 139, 
    RuleOwned_expression_member = 140, RuleOwned_expression = 141, RuleFunction_operation_arguments = 142, 
    RuleType_reference_member = 143, RuleType_result_member = 144, RuleType_reference = 145, 
    RuleReference_typing = 146, RuleSequence_expression = 147, RuleSequence_expression_list = 148, 
    RuleSequence_operator_expression = 149, RuleSequence_expression_list_member = 150, 
    RuleFunction_reference = 151, RuleFeature_chain_member = 152, RuleOwned_feature_chain_member = 153, 
    RuleBase_expression = 154, RuleNull_expression = 155, RuleFeature_reference_expression = 156, 
    RuleFeature_reference_member = 157, RuleFeature_reference = 158, RuleMetadata_access_expression = 159, 
    RuleInvocation_expression = 160, RuleInternal_invocation_expression = 161, 
    RuleConstructor_expression = 162, RuleArgument_list = 163, RulePositional_argument_list = 164, 
    RuleNamed_argument_list = 165, RuleNamed_argument_member = 166, RuleNamed_argument = 167, 
    RuleParameter_redefinition = 168, RuleBody_expression = 169, RuleExpression_body_member = 170, 
    RuleExpression_body = 171, RuleLiteral_expression = 172, RuleLiteral_boolean = 173, 
    RuleBoolean_value = 174, RuleLiteral_string = 175, RuleLiteral_integer = 176, 
    RuleLiteral_real = 177, RuleReal_value = 178, RuleLiteral_infinity = 179, 
    RuleInteraction = 180, RuleItem_flow = 181, RuleSuccession_item_flow = 182, 
    RuleItem_flow_declaration = 183, RuleItem_feature_member = 184, RuleItem_feature = 185, 
    RuleItem_feature_specialization_part = 186, RuleItem_flow_end_member = 187, 
    RuleItem_flow_end = 188, RuleItem_flow_feature_member = 189, RuleItem_flow_feature = 190, 
    RuleItem_flow_redefinition = 191, RuleValue_part = 192, RuleFeature_value = 193, 
    RuleFeature_assignment = 194, RuleMultiplicity = 195, RuleMultiplicity_subset = 196, 
    RuleMultiplicity_range = 197, RuleOwned_multiplicity = 198, RuleOwned_multiplicity_range = 199, 
    RuleMultiplicity_bounds = 200, RuleMultiplicity_expression_member = 201, 
    RuleInternal_multiplicity_expression_member = 202, RuleMetaclass = 203, 
    RulePrefix_metadata_annotation = 204, RulePrefix_metadata_member = 205, 
    RulePrefix_metadata_feature = 206, RuleMetadata_feature = 207, RuleMetadata_feature_declaration = 208, 
    RuleMetadata_body = 209, RuleMetadata_body_element = 210, RuleMetadata_body_feature_member = 211, 
    RuleMetadata_body_feature = 212, RulePackage = 213, RuleLibrary_package = 214, 
    RulePackage_declaration = 215, RulePackage_body = 216, RuleElement_filter_member = 217, 
    RuleMeta_assignment = 218, RuleTyped_by_operator = 219, RuleSpecializes_operator = 220, 
    RuleSubsets_operator = 221, RuleReferences_operator = 222, RuleRedefines_operator = 223, 
    RuleConjugates_operator = 224, RuleCrosses_operator = 225
  };

  explicit KerMLParser(antlr4::TokenStream *input);

  KerMLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~KerMLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class StartContext;
  class StartRuleContext;
  class ElementsContext;
  class IdentificationContext;
  class Relationship_bodyContext;
  class Relationship_owned_elementsContext;
  class Relationship_owned_elementContext;
  class Owned_related_elementContext;
  class DependencyContext;
  class AnnotationContext;
  class Owned_annotationContext;
  class Annotating_elementContext;
  class CommentContext;
  class DocumentationContext;
  class Textual_representationContext;
  class Root_namespaceContext;
  class NamespaceContext;
  class Namespace_declarationContext;
  class Namespace_bodyContext;
  class Namespace_body_elementsContext;
  class Namespace_body_elementContext;
  class Member_prefixContext;
  class Visibility_indicatorContext;
  class Namespace_memberContext;
  class Non_feature_memberContext;
  class Namespace_feature_memberContext;
  class Alias_memberContext;
  class Qualified_nameContext;
  class Namespace_importContext;
  class Import_declarationContext;
  class Membership_importContext;
  class Filter_packageContext;
  class Filter_package_memberContext;
  class ElementContext;
  class Non_feature_elementContext;
  class Feature_elementContext;
  class Additional_optionsContext;
  class TypeContext;
  class Type_prefixContext;
  class Type_declarationContext;
  class Specialization_partContext;
  class Conjugation_partContext;
  class Type_relationship_partContext;
  class Disjoining_partContext;
  class Unioning_partContext;
  class Intersecting_partContext;
  class Differencing_partContext;
  class Type_bodyContext;
  class Type_body_elementsContext;
  class Type_body_elementContext;
  class SpecializationContext;
  class Owned_specializationContext;
  class Specific_typeContext;
  class General_typeContext;
  class ConjunctionContext;
  class Owned_conjugationContext;
  class DisjoiningContext;
  class Owned_disjoiningContext;
  class UnioningContext;
  class IntersectingContext;
  class DifferencingContext;
  class Feature_memberContext;
  class Type_feature_memberContext;
  class Owned_feature_memberContext;
  class ClassifierContext;
  class Classifier_declarationContext;
  class Superclassing_partContext;
  class SubclassificationContext;
  class Owned_subclassificationContext;
  class FeatureContext;
  class Anonymous_featureContext;
  class Feature_prefixContext;
  class End_feature_prefixContext;
  class Basic_feature_prefixContext;
  class Owned_cross_feature_memberContext;
  class Owned_cross_featureContext;
  class Feature_directionContext;
  class Feature_declarationContext;
  class Feature_identificationContext;
  class Feature_relationship_partContext;
  class Chaining_partContext;
  class Inverting_partContext;
  class Type_featuring_partContext;
  class Feature_specialization_partContext;
  class Multiplicity_partContext;
  class Multiplicity_modifierContext;
  class Feature_specializationContext;
  class TypingsContext;
  class Typed_byContext;
  class SubsettingsContext;
  class SubsetsContext;
  class ReferencesContext;
  class CrossesContext;
  class RedefinitionsContext;
  class RedefinesContext;
  class Feature_typingContext;
  class Owned_feature_typingContext;
  class SubsettingContext;
  class Owned_subsettingContext;
  class Owned_reference_subsettingContext;
  class Owned_cross_subsettingContext;
  class RedefinitionContext;
  class Owned_redefinitionContext;
  class Owned_feature_chainContext;
  class Feature_chainContext;
  class Owned_feature_chainingContext;
  class Feature_invertingContext;
  class Owned_feature_invertingContext;
  class Type_featuringContext;
  class Owned_type_featuringContext;
  class Data_typeContext;
  class ClassContext;
  class StructureContext;
  class AssociationContext;
  class Association_structureContext;
  class ConnectorContext;
  class Connector_declarationContext;
  class Binary_connector_declarationContext;
  class Nary_connector_declarationContext;
  class Connector_end_memberContext;
  class Connector_endContext;
  class Owned_cross_multiplicity_memberContext;
  class Owned_cross_multiplicityContext;
  class Binding_connectorContext;
  class Binding_connector_declarationContext;
  class SuccessionContext;
  class Succession_declarationContext;
  class BehaviorContext;
  class StepContext;
  class FunctionContext;
  class Function_bodyContext;
  class Function_body_partContext;
  class Return_feature_memberContext;
  class Result_expression_memberContext;
  class ExpressionContext;
  class PredicateContext;
  class Boolean_expressionContext;
  class InvariantContext;
  class Owned_expression_reference_memberContext;
  class Owned_expression_referenceContext;
  class Owned_expression_memberContext;
  class Owned_expressionContext;
  class Function_operation_argumentsContext;
  class Type_reference_memberContext;
  class Type_result_memberContext;
  class Type_referenceContext;
  class Reference_typingContext;
  class Sequence_expressionContext;
  class Sequence_expression_listContext;
  class Sequence_operator_expressionContext;
  class Sequence_expression_list_memberContext;
  class Function_referenceContext;
  class Feature_chain_memberContext;
  class Owned_feature_chain_memberContext;
  class Base_expressionContext;
  class Null_expressionContext;
  class Feature_reference_expressionContext;
  class Feature_reference_memberContext;
  class Feature_referenceContext;
  class Metadata_access_expressionContext;
  class Invocation_expressionContext;
  class Internal_invocation_expressionContext;
  class Constructor_expressionContext;
  class Argument_listContext;
  class Positional_argument_listContext;
  class Named_argument_listContext;
  class Named_argument_memberContext;
  class Named_argumentContext;
  class Parameter_redefinitionContext;
  class Body_expressionContext;
  class Expression_body_memberContext;
  class Expression_bodyContext;
  class Literal_expressionContext;
  class Literal_booleanContext;
  class Boolean_valueContext;
  class Literal_stringContext;
  class Literal_integerContext;
  class Literal_realContext;
  class Real_valueContext;
  class Literal_infinityContext;
  class InteractionContext;
  class Item_flowContext;
  class Succession_item_flowContext;
  class Item_flow_declarationContext;
  class Item_feature_memberContext;
  class Item_featureContext;
  class Item_feature_specialization_partContext;
  class Item_flow_end_memberContext;
  class Item_flow_endContext;
  class Item_flow_feature_memberContext;
  class Item_flow_featureContext;
  class Item_flow_redefinitionContext;
  class Value_partContext;
  class Feature_valueContext;
  class Feature_assignmentContext;
  class MultiplicityContext;
  class Multiplicity_subsetContext;
  class Multiplicity_rangeContext;
  class Owned_multiplicityContext;
  class Owned_multiplicity_rangeContext;
  class Multiplicity_boundsContext;
  class Multiplicity_expression_memberContext;
  class Internal_multiplicity_expression_memberContext;
  class MetaclassContext;
  class Prefix_metadata_annotationContext;
  class Prefix_metadata_memberContext;
  class Prefix_metadata_featureContext;
  class Metadata_featureContext;
  class Metadata_feature_declarationContext;
  class Metadata_bodyContext;
  class Metadata_body_elementContext;
  class Metadata_body_feature_memberContext;
  class Metadata_body_featureContext;
  class PackageContext;
  class Library_packageContext;
  class Package_declarationContext;
  class Package_bodyContext;
  class Element_filter_memberContext;
  class Meta_assignmentContext;
  class Typed_by_operatorContext;
  class Specializes_operatorContext;
  class Subsets_operatorContext;
  class References_operatorContext;
  class Redefines_operatorContext;
  class Conjugates_operatorContext;
  class Crosses_operatorContext; 

  class SYSMLV2FILE_EXPORT StartContext : public antlr4::ParserRuleContext {
  public:
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementsContext *elements();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StartContext* start();

  class SYSMLV2FILE_EXPORT StartRuleContext : public antlr4::ParserRuleContext {
  public:
    StartRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StartContext *start();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StartRuleContext* startRule();

  class SYSMLV2FILE_EXPORT ElementsContext : public antlr4::ParserRuleContext {
  public:
    ElementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Member_prefixContext *> member_prefix();
    Member_prefixContext* member_prefix(size_t i);
    std::vector<ElementContext *> element();
    ElementContext* element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementsContext* elements();

  class SYSMLV2FILE_EXPORT IdentificationContext : public antlr4::ParserRuleContext {
  public:
    IdentificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_SMALLER();
    antlr4::tree::TerminalNode *SYMBOL_GREATER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentificationContext* identification();

  class SYSMLV2FILE_EXPORT Relationship_bodyContext : public antlr4::ParserRuleContext {
  public:
    Relationship_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Relationship_owned_elementsContext *relationship_owned_elements();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Relationship_bodyContext* relationship_body();

  class SYSMLV2FILE_EXPORT Relationship_owned_elementsContext : public antlr4::ParserRuleContext {
  public:
    Relationship_owned_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Relationship_owned_elementContext *> relationship_owned_element();
    Relationship_owned_elementContext* relationship_owned_element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Relationship_owned_elementsContext* relationship_owned_elements();

  class SYSMLV2FILE_EXPORT Relationship_owned_elementContext : public antlr4::ParserRuleContext {
  public:
    Relationship_owned_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_related_elementContext *owned_related_element();
    Owned_annotationContext *owned_annotation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Relationship_owned_elementContext* relationship_owned_element();

  class SYSMLV2FILE_EXPORT Owned_related_elementContext : public antlr4::ParserRuleContext {
  public:
    Owned_related_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_elementContext *non_feature_element();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_related_elementContext* owned_related_element();

  class SYSMLV2FILE_EXPORT DependencyContext : public antlr4::ParserRuleContext {
  public:
    DependencyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_DEPENDENCY();
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();
    Relationship_bodyContext *relationship_body();
    std::vector<Prefix_metadata_annotationContext *> prefix_metadata_annotation();
    Prefix_metadata_annotationContext* prefix_metadata_annotation(size_t i);
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DependencyContext* dependency();

  class SYSMLV2FILE_EXPORT AnnotationContext : public antlr4::ParserRuleContext {
  public:
    AnnotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationContext* annotation();

  class SYSMLV2FILE_EXPORT Owned_annotationContext : public antlr4::ParserRuleContext {
  public:
    Owned_annotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotating_elementContext *annotating_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_annotationContext* owned_annotation();

  class SYSMLV2FILE_EXPORT Annotating_elementContext : public antlr4::ParserRuleContext {
  public:
    Annotating_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CommentContext *comment();
    DocumentationContext *documentation();
    Textual_representationContext *textual_representation();
    Metadata_featureContext *metadata_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Annotating_elementContext* annotating_element();

  class SYSMLV2FILE_EXPORT CommentContext : public antlr4::ParserRuleContext {
  public:
    CommentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REGULAR_COMMENT();
    antlr4::tree::TerminalNode *KEYWORD_COMMENT();
    antlr4::tree::TerminalNode *KEYWORD_LOCALE();
    antlr4::tree::TerminalNode *STRING_VALUE();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_ABOUT();
    std::vector<AnnotationContext *> annotation();
    AnnotationContext* annotation(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CommentContext* comment();

  class SYSMLV2FILE_EXPORT DocumentationContext : public antlr4::ParserRuleContext {
  public:
    DocumentationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_DOC();
    antlr4::tree::TerminalNode *REGULAR_COMMENT();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_LOCALE();
    antlr4::tree::TerminalNode *STRING_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DocumentationContext* documentation();

  class SYSMLV2FILE_EXPORT Textual_representationContext : public antlr4::ParserRuleContext {
  public:
    Textual_representationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_LANGUAGE();
    antlr4::tree::TerminalNode *STRING_VALUE();
    antlr4::tree::TerminalNode *REGULAR_COMMENT();
    antlr4::tree::TerminalNode *KEYWORD_REP();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Textual_representationContext* textual_representation();

  class SYSMLV2FILE_EXPORT Root_namespaceContext : public antlr4::ParserRuleContext {
  public:
    Root_namespaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Namespace_body_elementsContext *namespace_body_elements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Root_namespaceContext* root_namespace();

  class SYSMLV2FILE_EXPORT NamespaceContext : public antlr4::ParserRuleContext {
  public:
    NamespaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Namespace_declarationContext *namespace_declaration();
    Namespace_bodyContext *namespace_body();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamespaceContext* namespace_();

  class SYSMLV2FILE_EXPORT Namespace_declarationContext : public antlr4::ParserRuleContext {
  public:
    Namespace_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_NAMESPACE();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Namespace_declarationContext* namespace_declaration();

  class SYSMLV2FILE_EXPORT Namespace_bodyContext : public antlr4::ParserRuleContext {
  public:
    Namespace_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Namespace_body_elementContext *namespace_body_element();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Namespace_bodyContext* namespace_body();

  class SYSMLV2FILE_EXPORT Namespace_body_elementsContext : public antlr4::ParserRuleContext {
  public:
    Namespace_body_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementsContext *elements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Namespace_body_elementsContext* namespace_body_elements();

  class SYSMLV2FILE_EXPORT Namespace_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Namespace_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Namespace_memberContext *namespace_member();
    Alias_memberContext *alias_member();
    Namespace_importContext *namespace_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Namespace_body_elementContext* namespace_body_element();

  class SYSMLV2FILE_EXPORT Member_prefixContext : public antlr4::ParserRuleContext {
  public:
    Member_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Visibility_indicatorContext *visibility_indicator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Member_prefixContext* member_prefix();

  class SYSMLV2FILE_EXPORT Visibility_indicatorContext : public antlr4::ParserRuleContext {
  public:
    Visibility_indicatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_PUBLIC();
    antlr4::tree::TerminalNode *KEYWORD_PRIVATE();
    antlr4::tree::TerminalNode *KEYWORD_PROTECTED();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Visibility_indicatorContext* visibility_indicator();

  class SYSMLV2FILE_EXPORT Namespace_memberContext : public antlr4::ParserRuleContext {
  public:
    Namespace_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_memberContext *non_feature_member();
    Namespace_feature_memberContext *namespace_feature_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Namespace_memberContext* namespace_member();

  class SYSMLV2FILE_EXPORT Non_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Non_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Non_feature_elementContext *non_feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Non_feature_memberContext* non_feature_member();

  class SYSMLV2FILE_EXPORT Namespace_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Namespace_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Namespace_feature_memberContext* namespace_feature_member();

  class SYSMLV2FILE_EXPORT Alias_memberContext : public antlr4::ParserRuleContext {
  public:
    Alias_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ALIAS();
    antlr4::tree::TerminalNode *KEYWORD_FOR();
    Qualified_nameContext *qualified_name();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *SYMBOL_SMALLER();
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_GREATER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Alias_memberContext* alias_member();

  class SYSMLV2FILE_EXPORT Qualified_nameContext : public antlr4::ParserRuleContext {
  public:
    Qualified_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_NAMESPACE_SUBSET();
    antlr4::tree::TerminalNode* SYMBOL_NAMESPACE_SUBSET(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Qualified_nameContext* qualified_name();

  class SYSMLV2FILE_EXPORT Namespace_importContext : public antlr4::ParserRuleContext {
  public:
    Namespace_importContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_IMPORT();
    Import_declarationContext *import_declaration();
    Relationship_bodyContext *relationship_body();
    Visibility_indicatorContext *visibility_indicator();
    antlr4::tree::TerminalNode *KEYWORD_ALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Namespace_importContext* namespace_import();

  class SYSMLV2FILE_EXPORT Import_declarationContext : public antlr4::ParserRuleContext {
  public:
    Import_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Membership_importContext *membership_import();
    Filter_packageContext *filter_package();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Import_declarationContext* import_declaration();

  class SYSMLV2FILE_EXPORT Membership_importContext : public antlr4::ParserRuleContext {
  public:
    Membership_importContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    antlr4::tree::TerminalNode *SYMBOL_NAMESPACE_SUBSET();
    antlr4::tree::TerminalNode *SYMBOL_DOUBLE_STAR();
    antlr4::tree::TerminalNode *SYMBOL_STAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Membership_importContext* membership_import();

  class SYSMLV2FILE_EXPORT Filter_packageContext : public antlr4::ParserRuleContext {
  public:
    Filter_packageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Membership_importContext *membership_import();
    Filter_package_memberContext *filter_package_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Filter_packageContext* filter_package();

  class SYSMLV2FILE_EXPORT Filter_package_memberContext : public antlr4::ParserRuleContext {
  public:
    Filter_package_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_OPEN();
    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Filter_package_memberContext* filter_package_member();

  class SYSMLV2FILE_EXPORT ElementContext : public antlr4::ParserRuleContext {
  public:
    ElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Additional_optionsContext *additional_options();
    Annotating_elementContext *annotating_element();
    Non_feature_elementContext *non_feature_element();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementContext* element();

  class SYSMLV2FILE_EXPORT Non_feature_elementContext : public antlr4::ParserRuleContext {
  public:
    Non_feature_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DependencyContext *dependency();
    TypeContext *type();
    ClassifierContext *classifier();
    Data_typeContext *data_type();
    NamespaceContext *namespace_();
    ClassContext *class_();
    StructureContext *structure();
    MetaclassContext *metaclass();
    AssociationContext *association();
    Association_structureContext *association_structure();
    InteractionContext *interaction();
    BehaviorContext *behavior();
    FunctionContext *function();
    PredicateContext *predicate();
    MultiplicityContext *multiplicity();
    PackageContext *package();
    Library_packageContext *library_package();
    SpecializationContext *specialization();
    ConjunctionContext *conjunction();
    SubclassificationContext *subclassification();
    DisjoiningContext *disjoining();
    Feature_invertingContext *feature_inverting();
    Feature_typingContext *feature_typing();
    SubsettingContext *subsetting();
    RedefinitionContext *redefinition();
    Type_featuringContext *type_featuring();
    Namespace_importContext *namespace_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Non_feature_elementContext* non_feature_element();

  class SYSMLV2FILE_EXPORT Feature_elementContext : public antlr4::ParserRuleContext {
  public:
    Feature_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FeatureContext *feature();
    StepContext *step();
    ExpressionContext *expression();
    Boolean_expressionContext *boolean_expression();
    InvariantContext *invariant();
    ConnectorContext *connector();
    Binding_connectorContext *binding_connector();
    SuccessionContext *succession();
    Item_flowContext *item_flow();
    Succession_item_flowContext *succession_item_flow();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_elementContext* feature_element();

  class SYSMLV2FILE_EXPORT Additional_optionsContext : public antlr4::ParserRuleContext {
  public:
    Additional_optionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Meta_assignmentContext *meta_assignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Additional_optionsContext* additional_options();

  class SYSMLV2FILE_EXPORT TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_TYPE();
    Type_declarationContext *type_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class SYSMLV2FILE_EXPORT Type_prefixContext : public antlr4::ParserRuleContext {
  public:
    Type_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ABSTRACT();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_prefixContext* type_prefix();

  class SYSMLV2FILE_EXPORT Type_declarationContext : public antlr4::ParserRuleContext {
  public:
    Type_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_ALL();
    Multiplicity_boundsContext *multiplicity_bounds();
    std::vector<Specialization_partContext *> specialization_part();
    Specialization_partContext* specialization_part(size_t i);
    std::vector<Conjugation_partContext *> conjugation_part();
    Conjugation_partContext* conjugation_part(size_t i);
    std::vector<Type_relationship_partContext *> type_relationship_part();
    Type_relationship_partContext* type_relationship_part(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_declarationContext* type_declaration();

  class SYSMLV2FILE_EXPORT Specialization_partContext : public antlr4::ParserRuleContext {
  public:
    Specialization_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Specializes_operatorContext *specializes_operator();
    std::vector<Owned_specializationContext *> owned_specialization();
    Owned_specializationContext* owned_specialization(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Specialization_partContext* specialization_part();

  class SYSMLV2FILE_EXPORT Conjugation_partContext : public antlr4::ParserRuleContext {
  public:
    Conjugation_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Conjugates_operatorContext *conjugates_operator();
    Owned_conjugationContext *owned_conjugation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Conjugation_partContext* conjugation_part();

  class SYSMLV2FILE_EXPORT Type_relationship_partContext : public antlr4::ParserRuleContext {
  public:
    Type_relationship_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Disjoining_partContext *disjoining_part();
    Unioning_partContext *unioning_part();
    Intersecting_partContext *intersecting_part();
    Differencing_partContext *differencing_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_relationship_partContext* type_relationship_part();

  class SYSMLV2FILE_EXPORT Disjoining_partContext : public antlr4::ParserRuleContext {
  public:
    Disjoining_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_DISJOINT();
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    std::vector<Owned_disjoiningContext *> owned_disjoining();
    Owned_disjoiningContext* owned_disjoining(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Disjoining_partContext* disjoining_part();

  class SYSMLV2FILE_EXPORT Unioning_partContext : public antlr4::ParserRuleContext {
  public:
    Unioning_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_UNIONS();
    std::vector<UnioningContext *> unioning();
    UnioningContext* unioning(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Unioning_partContext* unioning_part();

  class SYSMLV2FILE_EXPORT Intersecting_partContext : public antlr4::ParserRuleContext {
  public:
    Intersecting_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_INTERSECTS();
    std::vector<IntersectingContext *> intersecting();
    IntersectingContext* intersecting(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Intersecting_partContext* intersecting_part();

  class SYSMLV2FILE_EXPORT Differencing_partContext : public antlr4::ParserRuleContext {
  public:
    Differencing_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_DIFFERENCES();
    std::vector<DifferencingContext *> differencing();
    DifferencingContext* differencing(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Differencing_partContext* differencing_part();

  class SYSMLV2FILE_EXPORT Type_bodyContext : public antlr4::ParserRuleContext {
  public:
    Type_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Type_body_elementsContext *type_body_elements();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_bodyContext* type_body();

  class SYSMLV2FILE_EXPORT Type_body_elementsContext : public antlr4::ParserRuleContext {
  public:
    Type_body_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Type_body_elementContext *> type_body_element();
    Type_body_elementContext* type_body_element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_body_elementsContext* type_body_elements();

  class SYSMLV2FILE_EXPORT Type_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Type_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_feature_memberContext *type_feature_member();
    Member_prefixContext *member_prefix();
    ElementContext *element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_body_elementContext* type_body_element();

  class SYSMLV2FILE_EXPORT SpecializationContext : public antlr4::ParserRuleContext {
  public:
    SpecializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_SUBTYPE();
    Specific_typeContext *specific_type();
    Specializes_operatorContext *specializes_operator();
    General_typeContext *general_type();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *KEYWORD_SPECIALIZATION();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecializationContext* specialization();

  class SYSMLV2FILE_EXPORT Owned_specializationContext : public antlr4::ParserRuleContext {
  public:
    Owned_specializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_specializationContext* owned_specialization();

  class SYSMLV2FILE_EXPORT Specific_typeContext : public antlr4::ParserRuleContext {
  public:
    Specific_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Specific_typeContext* specific_type();

  class SYSMLV2FILE_EXPORT General_typeContext : public antlr4::ParserRuleContext {
  public:
    General_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  General_typeContext* general_type();

  class SYSMLV2FILE_EXPORT ConjunctionContext : public antlr4::ParserRuleContext {
  public:
    ConjunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_CONJUGATE();
    Conjugates_operatorContext *conjugates_operator();
    Relationship_bodyContext *relationship_body();
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    std::vector<Feature_chainContext *> feature_chain();
    Feature_chainContext* feature_chain(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_CONJUGATION();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConjunctionContext* conjunction();

  class SYSMLV2FILE_EXPORT Owned_conjugationContext : public antlr4::ParserRuleContext {
  public:
    Owned_conjugationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_conjugationContext* owned_conjugation();

  class SYSMLV2FILE_EXPORT DisjoiningContext : public antlr4::ParserRuleContext {
  public:
    DisjoiningContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_DISJOINT();
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    Relationship_bodyContext *relationship_body();
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    std::vector<Feature_chainContext *> feature_chain();
    Feature_chainContext* feature_chain(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_DISJOINING();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DisjoiningContext* disjoining();

  class SYSMLV2FILE_EXPORT Owned_disjoiningContext : public antlr4::ParserRuleContext {
  public:
    Owned_disjoiningContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_disjoiningContext* owned_disjoining();

  class SYSMLV2FILE_EXPORT UnioningContext : public antlr4::ParserRuleContext {
  public:
    UnioningContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnioningContext* unioning();

  class SYSMLV2FILE_EXPORT IntersectingContext : public antlr4::ParserRuleContext {
  public:
    IntersectingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntersectingContext* intersecting();

  class SYSMLV2FILE_EXPORT DifferencingContext : public antlr4::ParserRuleContext {
  public:
    DifferencingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DifferencingContext* differencing();

  class SYSMLV2FILE_EXPORT Feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_feature_memberContext *type_feature_member();
    Owned_feature_memberContext *owned_feature_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_memberContext* feature_member();

  class SYSMLV2FILE_EXPORT Type_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Type_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_MEMBER();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_feature_memberContext* type_feature_member();

  class SYSMLV2FILE_EXPORT Owned_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_feature_memberContext* owned_feature_member();

  class SYSMLV2FILE_EXPORT ClassifierContext : public antlr4::ParserRuleContext {
  public:
    ClassifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_CLASSIFIER();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();
    Type_prefixContext *type_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassifierContext* classifier();

  class SYSMLV2FILE_EXPORT Classifier_declarationContext : public antlr4::ParserRuleContext {
  public:
    Classifier_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_ALL();
    Multiplicity_boundsContext *multiplicity_bounds();
    Superclassing_partContext *superclassing_part();
    Conjugation_partContext *conjugation_part();
    std::vector<Type_relationship_partContext *> type_relationship_part();
    Type_relationship_partContext* type_relationship_part(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Classifier_declarationContext* classifier_declaration();

  class SYSMLV2FILE_EXPORT Superclassing_partContext : public antlr4::ParserRuleContext {
  public:
    Superclassing_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Specializes_operatorContext *specializes_operator();
    std::vector<Owned_subclassificationContext *> owned_subclassification();
    Owned_subclassificationContext* owned_subclassification(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Superclassing_partContext* superclassing_part();

  class SYSMLV2FILE_EXPORT SubclassificationContext : public antlr4::ParserRuleContext {
  public:
    SubclassificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_SUBCLASSIFIER();
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    Specializes_operatorContext *specializes_operator();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *KEYWORD_SPECIALIZATION();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubclassificationContext* subclassification();

  class SYSMLV2FILE_EXPORT Owned_subclassificationContext : public antlr4::ParserRuleContext {
  public:
    Owned_subclassificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_subclassificationContext* owned_subclassification();

  class SYSMLV2FILE_EXPORT FeatureContext : public antlr4::ParserRuleContext {
  public:
    FeatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    Type_bodyContext *type_body();
    antlr4::tree::TerminalNode *KEYWORD_FEATURE();
    Prefix_metadata_memberContext *prefix_metadata_member();
    Feature_declarationContext *feature_declaration();
    Value_partContext *value_part();
    Anonymous_featureContext *anonymous_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FeatureContext* feature();

  class SYSMLV2FILE_EXPORT Anonymous_featureContext : public antlr4::ParserRuleContext {
  public:
    Anonymous_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_declarationContext *feature_declaration();
    Type_bodyContext *type_body();
    End_feature_prefixContext *end_feature_prefix();
    Basic_feature_prefixContext *basic_feature_prefix();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Anonymous_featureContext* anonymous_feature();

  class SYSMLV2FILE_EXPORT Feature_prefixContext : public antlr4::ParserRuleContext {
  public:
    Feature_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    End_feature_prefixContext *end_feature_prefix();
    Basic_feature_prefixContext *basic_feature_prefix();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);
    Owned_cross_feature_memberContext *owned_cross_feature_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_prefixContext* feature_prefix();

  class SYSMLV2FILE_EXPORT End_feature_prefixContext : public antlr4::ParserRuleContext {
  public:
    End_feature_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_END();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  End_feature_prefixContext* end_feature_prefix();

  class SYSMLV2FILE_EXPORT Basic_feature_prefixContext : public antlr4::ParserRuleContext {
  public:
    Basic_feature_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_directionContext *feature_direction();
    antlr4::tree::TerminalNode *KEYWORD_DERIVED();
    antlr4::tree::TerminalNode *KEYWORD_ABSTRACT();
    antlr4::tree::TerminalNode *KEYWORD_VAR();
    antlr4::tree::TerminalNode *KEYWORD_READONLY();
    antlr4::tree::TerminalNode *KEYWORD_COMPOSITE();
    antlr4::tree::TerminalNode *KEYWORD_PORTION();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Basic_feature_prefixContext* basic_feature_prefix();

  class SYSMLV2FILE_EXPORT Owned_cross_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_cross_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_cross_featureContext *owned_cross_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_cross_feature_memberContext* owned_cross_feature_member();

  class SYSMLV2FILE_EXPORT Owned_cross_featureContext : public antlr4::ParserRuleContext {
  public:
    Owned_cross_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Basic_feature_prefixContext *basic_feature_prefix();
    Feature_declarationContext *feature_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_cross_featureContext* owned_cross_feature();

  class SYSMLV2FILE_EXPORT Feature_directionContext : public antlr4::ParserRuleContext {
  public:
    Feature_directionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_IN();
    antlr4::tree::TerminalNode *KEYWORD_OUT();
    antlr4::tree::TerminalNode *KEYWORD_INOUT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_directionContext* feature_direction();

  class SYSMLV2FILE_EXPORT Feature_declarationContext : public antlr4::ParserRuleContext {
  public:
    Feature_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_identificationContext *feature_identification();
    Feature_specialization_partContext *feature_specialization_part();
    Conjugation_partContext *conjugation_part();
    antlr4::tree::TerminalNode *KEYWORD_ALL();
    std::vector<Feature_relationship_partContext *> feature_relationship_part();
    Feature_relationship_partContext* feature_relationship_part(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_declarationContext* feature_declaration();

  class SYSMLV2FILE_EXPORT Feature_identificationContext : public antlr4::ParserRuleContext {
  public:
    Feature_identificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SMALLER();
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_GREATER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_identificationContext* feature_identification();

  class SYSMLV2FILE_EXPORT Feature_relationship_partContext : public antlr4::ParserRuleContext {
  public:
    Feature_relationship_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_relationship_partContext *type_relationship_part();
    Chaining_partContext *chaining_part();
    Inverting_partContext *inverting_part();
    Type_featuring_partContext *type_featuring_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_relationship_partContext* feature_relationship_part();

  class SYSMLV2FILE_EXPORT Chaining_partContext : public antlr4::ParserRuleContext {
  public:
    Chaining_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_CHAINS();
    Owned_feature_chainingContext *owned_feature_chaining();
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Chaining_partContext* chaining_part();

  class SYSMLV2FILE_EXPORT Inverting_partContext : public antlr4::ParserRuleContext {
  public:
    Inverting_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_INVERSE();
    antlr4::tree::TerminalNode *KEYWORD_OF();
    Owned_feature_invertingContext *owned_feature_inverting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Inverting_partContext* inverting_part();

  class SYSMLV2FILE_EXPORT Type_featuring_partContext : public antlr4::ParserRuleContext {
  public:
    Type_featuring_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_FEATURED();
    antlr4::tree::TerminalNode *KEYWORD_BY();
    std::vector<Owned_type_featuringContext *> owned_type_featuring();
    Owned_type_featuringContext* owned_type_featuring(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_featuring_partContext* type_featuring_part();

  class SYSMLV2FILE_EXPORT Feature_specialization_partContext : public antlr4::ParserRuleContext {
  public:
    Feature_specialization_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Feature_specializationContext *> feature_specialization();
    Feature_specializationContext* feature_specialization(size_t i);
    Multiplicity_partContext *multiplicity_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_specialization_partContext* feature_specialization_part();

  class SYSMLV2FILE_EXPORT Multiplicity_partContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_boundsContext *multiplicity_bounds();
    antlr4::tree::TerminalNode *KEYWORD_ORDERED();
    antlr4::tree::TerminalNode *KEYWORD_NONUNIQUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Multiplicity_partContext* multiplicity_part();

  class SYSMLV2FILE_EXPORT Multiplicity_modifierContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_modifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ORDERED();
    antlr4::tree::TerminalNode *KEYWORD_NONUNIQUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Multiplicity_modifierContext* multiplicity_modifier();

  class SYSMLV2FILE_EXPORT Feature_specializationContext : public antlr4::ParserRuleContext {
  public:
    Feature_specializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypingsContext *typings();
    SubsettingsContext *subsettings();
    ReferencesContext *references();
    CrossesContext *crosses();
    RedefinitionsContext *redefinitions();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_specializationContext* feature_specialization();

  class SYSMLV2FILE_EXPORT TypingsContext : public antlr4::ParserRuleContext {
  public:
    TypingsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Typed_byContext *typed_by();
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);
    std::vector<Owned_feature_typingContext *> owned_feature_typing();
    Owned_feature_typingContext* owned_feature_typing(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypingsContext* typings();

  class SYSMLV2FILE_EXPORT Typed_byContext : public antlr4::ParserRuleContext {
  public:
    Typed_byContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Typed_by_operatorContext *typed_by_operator();
    Owned_feature_typingContext *owned_feature_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Typed_byContext* typed_by();

  class SYSMLV2FILE_EXPORT SubsettingsContext : public antlr4::ParserRuleContext {
  public:
    SubsettingsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SubsetsContext *subsets();
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);
    std::vector<Owned_subsettingContext *> owned_subsetting();
    Owned_subsettingContext* owned_subsetting(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubsettingsContext* subsettings();

  class SYSMLV2FILE_EXPORT SubsetsContext : public antlr4::ParserRuleContext {
  public:
    SubsetsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Subsets_operatorContext *subsets_operator();
    Owned_subsettingContext *owned_subsetting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubsetsContext* subsets();

  class SYSMLV2FILE_EXPORT ReferencesContext : public antlr4::ParserRuleContext {
  public:
    ReferencesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    References_operatorContext *references_operator();
    Owned_reference_subsettingContext *owned_reference_subsetting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReferencesContext* references();

  class SYSMLV2FILE_EXPORT CrossesContext : public antlr4::ParserRuleContext {
  public:
    CrossesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Crosses_operatorContext *crosses_operator();
    Owned_cross_subsettingContext *owned_cross_subsetting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CrossesContext* crosses();

  class SYSMLV2FILE_EXPORT RedefinitionsContext : public antlr4::ParserRuleContext {
  public:
    RedefinitionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RedefinesContext *redefines();
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);
    std::vector<Owned_redefinitionContext *> owned_redefinition();
    Owned_redefinitionContext* owned_redefinition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RedefinitionsContext* redefinitions();

  class SYSMLV2FILE_EXPORT RedefinesContext : public antlr4::ParserRuleContext {
  public:
    RedefinesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Redefines_operatorContext *redefines_operator();
    Owned_redefinitionContext *owned_redefinition();
    Feature_directionContext *feature_direction();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RedefinesContext* redefines();

  class SYSMLV2FILE_EXPORT Feature_typingContext : public antlr4::ParserRuleContext {
  public:
    Feature_typingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_TYPING();
    Qualified_nameContext *qualified_name();
    Typed_by_operatorContext *typed_by_operator();
    General_typeContext *general_type();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *KEYWORD_SPECIALIZATION();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_typingContext* feature_typing();

  class SYSMLV2FILE_EXPORT Owned_feature_typingContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_typingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_feature_typingContext* owned_feature_typing();

  class SYSMLV2FILE_EXPORT SubsettingContext : public antlr4::ParserRuleContext {
  public:
    SubsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Specific_typeContext *specific_type();
    Subsets_operatorContext *subsets_operator();
    General_typeContext *general_type();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *KEYWORD_SPECIALIZATION();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_SUBSET();
    Multiplicity_partContext *multiplicity_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubsettingContext* subsetting();

  class SYSMLV2FILE_EXPORT Owned_subsettingContext : public antlr4::ParserRuleContext {
  public:
    Owned_subsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_subsettingContext* owned_subsetting();

  class SYSMLV2FILE_EXPORT Owned_reference_subsettingContext : public antlr4::ParserRuleContext {
  public:
    Owned_reference_subsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_reference_subsettingContext* owned_reference_subsetting();

  class SYSMLV2FILE_EXPORT Owned_cross_subsettingContext : public antlr4::ParserRuleContext {
  public:
    Owned_cross_subsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_cross_subsettingContext* owned_cross_subsetting();

  class SYSMLV2FILE_EXPORT RedefinitionContext : public antlr4::ParserRuleContext {
  public:
    RedefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Redefines_operatorContext *redefines_operator();
    Qualified_nameContext *qualified_name();
    Relationship_bodyContext *relationship_body();
    Feature_directionContext *feature_direction();
    antlr4::tree::TerminalNode *KEYWORD_SPECIALIZATION();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_REDEFINITION();
    Specific_typeContext *specific_type();
    Typed_byContext *typed_by();
    Multiplicity_partContext *multiplicity_part();
    SubsetsContext *subsets();
    Feature_assignmentContext *feature_assignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RedefinitionContext* redefinition();

  class SYSMLV2FILE_EXPORT Owned_redefinitionContext : public antlr4::ParserRuleContext {
  public:
    Owned_redefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_redefinitionContext* owned_redefinition();

  class SYSMLV2FILE_EXPORT Owned_feature_chainContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_feature_chainContext* owned_feature_chain();

  class SYSMLV2FILE_EXPORT Feature_chainContext : public antlr4::ParserRuleContext {
  public:
    Feature_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Owned_feature_chainingContext *> owned_feature_chaining();
    Owned_feature_chainingContext* owned_feature_chaining(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_DOT();
    antlr4::tree::TerminalNode* SYMBOL_DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_chainContext* feature_chain();

  class SYSMLV2FILE_EXPORT Owned_feature_chainingContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_chainingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_feature_chainingContext* owned_feature_chaining();

  class SYSMLV2FILE_EXPORT Feature_invertingContext : public antlr4::ParserRuleContext {
  public:
    Feature_invertingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_INVERSE();
    antlr4::tree::TerminalNode *KEYWORD_OF();
    Relationship_bodyContext *relationship_body();
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    std::vector<Owned_feature_chainContext *> owned_feature_chain();
    Owned_feature_chainContext* owned_feature_chain(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_INVERTING();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_invertingContext* feature_inverting();

  class SYSMLV2FILE_EXPORT Owned_feature_invertingContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_invertingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_feature_invertingContext* owned_feature_inverting();

  class SYSMLV2FILE_EXPORT Type_featuringContext : public antlr4::ParserRuleContext {
  public:
    Type_featuringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_FEATURING();
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_BY();
    Relationship_bodyContext *relationship_body();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_OF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_featuringContext* type_featuring();

  class SYSMLV2FILE_EXPORT Owned_type_featuringContext : public antlr4::ParserRuleContext {
  public:
    Owned_type_featuringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_type_featuringContext* owned_type_featuring();

  class SYSMLV2FILE_EXPORT Data_typeContext : public antlr4::ParserRuleContext {
  public:
    Data_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_DATATYPE();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Data_typeContext* data_type();

  class SYSMLV2FILE_EXPORT ClassContext : public antlr4::ParserRuleContext {
  public:
    ClassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CLASS();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassContext* class_();

  class SYSMLV2FILE_EXPORT StructureContext : public antlr4::ParserRuleContext {
  public:
    StructureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_STRUCT();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();
    Type_prefixContext *type_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructureContext* structure();

  class SYSMLV2FILE_EXPORT AssociationContext : public antlr4::ParserRuleContext {
  public:
    AssociationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ASSOC();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssociationContext* association();

  class SYSMLV2FILE_EXPORT Association_structureContext : public antlr4::ParserRuleContext {
  public:
    Association_structureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ASSOC();
    antlr4::tree::TerminalNode *KEYWORD_STRUCT();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Association_structureContext* association_structure();

  class SYSMLV2FILE_EXPORT ConnectorContext : public antlr4::ParserRuleContext {
  public:
    ConnectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CONNECTOR();
    Type_bodyContext *type_body();
    Connector_declarationContext *connector_declaration();
    Feature_declarationContext *feature_declaration();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConnectorContext* connector();

  class SYSMLV2FILE_EXPORT Connector_declarationContext : public antlr4::ParserRuleContext {
  public:
    Connector_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Binary_connector_declarationContext *binary_connector_declaration();
    Nary_connector_declarationContext *nary_connector_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Connector_declarationContext* connector_declaration();

  class SYSMLV2FILE_EXPORT Binary_connector_declarationContext : public antlr4::ParserRuleContext {
  public:
    Binary_connector_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    antlr4::tree::TerminalNode *KEYWORD_ALL();
    Feature_declarationContext *feature_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Binary_connector_declarationContext* binary_connector_declaration();

  class SYSMLV2FILE_EXPORT Nary_connector_declarationContext : public antlr4::ParserRuleContext {
  public:
    Nary_connector_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();
    Feature_declarationContext *feature_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Nary_connector_declarationContext* nary_connector_declaration();

  class SYSMLV2FILE_EXPORT Connector_end_memberContext : public antlr4::ParserRuleContext {
  public:
    Connector_end_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Connector_endContext *connector_end();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Connector_end_memberContext* connector_end_member();

  class SYSMLV2FILE_EXPORT Connector_endContext : public antlr4::ParserRuleContext {
  public:
    Connector_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    Owned_cross_multiplicity_memberContext *owned_cross_multiplicity_member();
    antlr4::tree::TerminalNode *NAME();
    References_operatorContext *references_operator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Connector_endContext* connector_end();

  class SYSMLV2FILE_EXPORT Owned_cross_multiplicity_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_cross_multiplicity_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_cross_multiplicityContext *owned_cross_multiplicity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_cross_multiplicity_memberContext* owned_cross_multiplicity_member();

  class SYSMLV2FILE_EXPORT Owned_cross_multiplicityContext : public antlr4::ParserRuleContext {
  public:
    Owned_cross_multiplicityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_multiplicityContext *owned_multiplicity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_cross_multiplicityContext* owned_cross_multiplicity();

  class SYSMLV2FILE_EXPORT Binding_connectorContext : public antlr4::ParserRuleContext {
  public:
    Binding_connectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_BINDING();
    Binding_connector_declarationContext *binding_connector_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Binding_connectorContext* binding_connector();

  class SYSMLV2FILE_EXPORT Binding_connector_declarationContext : public antlr4::ParserRuleContext {
  public:
    Binding_connector_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_declarationContext *feature_declaration();
    antlr4::tree::TerminalNode *KEYWORD_OF();
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_ASSIGN();
    antlr4::tree::TerminalNode *KEYWORD_ALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Binding_connector_declarationContext* binding_connector_declaration();

  class SYSMLV2FILE_EXPORT SuccessionContext : public antlr4::ParserRuleContext {
  public:
    SuccessionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_SUCCESSION();
    Succession_declarationContext *succession_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SuccessionContext* succession();

  class SYSMLV2FILE_EXPORT Succession_declarationContext : public antlr4::ParserRuleContext {
  public:
    Succession_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_declarationContext *feature_declaration();
    antlr4::tree::TerminalNode *KEYWORD_FIRST();
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_THEN();
    antlr4::tree::TerminalNode *KEYWORD_ALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Succession_declarationContext* succession_declaration();

  class SYSMLV2FILE_EXPORT BehaviorContext : public antlr4::ParserRuleContext {
  public:
    BehaviorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_BEHAVIOR();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BehaviorContext* behavior();

  class SYSMLV2FILE_EXPORT StepContext : public antlr4::ParserRuleContext {
  public:
    StepContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_STEP();
    Feature_declarationContext *feature_declaration();
    Type_bodyContext *type_body();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StepContext* step();

  class SYSMLV2FILE_EXPORT FunctionContext : public antlr4::ParserRuleContext {
  public:
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FUNCTION();
    Classifier_declarationContext *classifier_declaration();
    Function_bodyContext *function_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionContext* function();

  class SYSMLV2FILE_EXPORT Function_bodyContext : public antlr4::ParserRuleContext {
  public:
    Function_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Function_body_partContext *function_body_part();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_bodyContext* function_body();

  class SYSMLV2FILE_EXPORT Function_body_partContext : public antlr4::ParserRuleContext {
  public:
    Function_body_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Type_body_elementContext *> type_body_element();
    Type_body_elementContext* type_body_element(size_t i);
    std::vector<Return_feature_memberContext *> return_feature_member();
    Return_feature_memberContext* return_feature_member(size_t i);
    Result_expression_memberContext *result_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_body_partContext* function_body_part();

  class SYSMLV2FILE_EXPORT Return_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Return_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_RETURN();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Return_feature_memberContext* return_feature_member();

  class SYSMLV2FILE_EXPORT Result_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Result_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Owned_expressionContext *owned_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Result_expression_memberContext* result_expression_member();

  class SYSMLV2FILE_EXPORT ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_EXPR();
    Feature_declarationContext *feature_declaration();
    Function_bodyContext *function_body();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class SYSMLV2FILE_EXPORT PredicateContext : public antlr4::ParserRuleContext {
  public:
    PredicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_PREDICATE();
    Classifier_declarationContext *classifier_declaration();
    Function_bodyContext *function_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PredicateContext* predicate();

  class SYSMLV2FILE_EXPORT Boolean_expressionContext : public antlr4::ParserRuleContext {
  public:
    Boolean_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_BOOL();
    Feature_declarationContext *feature_declaration();
    Function_bodyContext *function_body();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Boolean_expressionContext* boolean_expression();

  class SYSMLV2FILE_EXPORT InvariantContext : public antlr4::ParserRuleContext {
  public:
    InvariantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INV();
    Function_bodyContext *function_body();
    Feature_declarationContext *feature_declaration();
    Value_partContext *value_part();
    antlr4::tree::TerminalNode *KEYWORD_TRUE();
    antlr4::tree::TerminalNode *KEYWORD_FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InvariantContext* invariant();

  class SYSMLV2FILE_EXPORT Owned_expression_reference_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_expression_reference_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expression_referenceContext *owned_expression_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_expression_reference_memberContext* owned_expression_reference_member();

  class SYSMLV2FILE_EXPORT Owned_expression_referenceContext : public antlr4::ParserRuleContext {
  public:
    Owned_expression_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expression_memberContext *owned_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_expression_referenceContext* owned_expression_reference();

  class SYSMLV2FILE_EXPORT Owned_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expressionContext *owned_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_expression_memberContext* owned_expression_member();

  class SYSMLV2FILE_EXPORT Owned_expressionContext : public antlr4::ParserRuleContext {
  public:
    Owned_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Owned_expressionContext() = default;
    void copyFrom(Owned_expressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class SYSMLV2FILE_EXPORT SelectExprContext : public Owned_expressionContext {
  public:
    SelectExprContext(Owned_expressionContext *ctx);

    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_DOT_QUESTION();
    Body_expressionContext *body_expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT CollectExprContext : public Owned_expressionContext {
  public:
    CollectExprContext(Owned_expressionContext *ctx);

    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    Body_expressionContext *body_expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT BinaryExprContext : public Owned_expressionContext {
  public:
    BinaryExprContext(Owned_expressionContext *ctx);

    antlr4::Token *op = nullptr;
    std::vector<Owned_expressionContext *> owned_expression();
    Owned_expressionContext* owned_expression(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_DOUBLE_STAR();
    antlr4::tree::TerminalNode *SYMBOL_UPPER();
    antlr4::tree::TerminalNode *SYMBOL_STAR();
    antlr4::tree::TerminalNode *SYMBOL_SLASH();
    antlr4::tree::TerminalNode *SYMBOL_MOD();
    antlr4::tree::TerminalNode *SYMBOL_PLUS();
    antlr4::tree::TerminalNode *SYMBOL_MINUS();
    antlr4::tree::TerminalNode *SYMBOL_DDOT();
    antlr4::tree::TerminalNode *SYMBOL_GREATER();
    antlr4::tree::TerminalNode *SYMBOL_SMALLER();
    antlr4::tree::TerminalNode *SYMBOL_GREATER_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_SMALLER_EQUAL();
    antlr4::tree::TerminalNode *SYMBOL_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_NOT_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_IFF_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_IFF_NOT_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_AND();
    antlr4::tree::TerminalNode *KEYWORD_AND();
    antlr4::tree::TerminalNode *KEYWORD_XOR();
    antlr4::tree::TerminalNode *SYMBOL_VERTICAL_LINE();
    antlr4::tree::TerminalNode *KEYWORD_OR();
    antlr4::tree::TerminalNode *KEYWORD_IMPLIES();
    antlr4::tree::TerminalNode *SYMBOL_DQUESTION();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT ExtentExprContext : public Owned_expressionContext {
  public:
    ExtentExprContext(Owned_expressionContext *ctx);

    antlr4::tree::TerminalNode *KEYWORD_ALL();
    Type_reference_memberContext *type_reference_member();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT ConditionalExprContext : public Owned_expressionContext {
  public:
    ConditionalExprContext(Owned_expressionContext *ctx);

    antlr4::tree::TerminalNode *KEYWORD_IF();
    std::vector<Owned_expressionContext *> owned_expression();
    Owned_expressionContext* owned_expression(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_QUESTION();
    antlr4::tree::TerminalNode *KEYWORD_ELSE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT UnaryExprContext : public Owned_expressionContext {
  public:
    UnaryExprContext(Owned_expressionContext *ctx);

    antlr4::Token *op = nullptr;
    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_PLUS();
    antlr4::tree::TerminalNode *SYMBOL_MINUS();
    antlr4::tree::TerminalNode *SYMBOL_CONJUGATES();
    antlr4::tree::TerminalNode *KEYWORD_NOT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT IndexExprContext : public Owned_expressionContext {
  public:
    IndexExprContext(Owned_expressionContext *ctx);

    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_HASHTAG();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    Sequence_expression_list_memberContext *sequence_expression_list_member();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT BaseExprContext : public Owned_expressionContext {
  public:
    BaseExprContext(Owned_expressionContext *ctx);

    Base_expressionContext *base_expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT FeatureChainExprContext : public Owned_expressionContext {
  public:
    FeatureChainExprContext(Owned_expressionContext *ctx);

    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    Feature_reference_memberContext *feature_reference_member();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT BracketExprContext : public Owned_expressionContext {
  public:
    BracketExprContext(Owned_expressionContext *ctx);

    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_OPEN();
    Sequence_expression_list_memberContext *sequence_expression_list_member();
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_CLOSE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT MetaclassificationExprContext : public Owned_expressionContext {
  public:
    MetaclassificationExprContext(Owned_expressionContext *ctx);

    antlr4::Token *op = nullptr;
    Owned_expressionContext *owned_expression();
    Type_reference_memberContext *type_reference_member();
    antlr4::tree::TerminalNode *SYMBOL_ATAT();
    Type_result_memberContext *type_result_member();
    antlr4::tree::TerminalNode *KEYWORD_META();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT ClassificationExprContext : public Owned_expressionContext {
  public:
    ClassificationExprContext(Owned_expressionContext *ctx);

    antlr4::Token *op = nullptr;
    Type_reference_memberContext *type_reference_member();
    antlr4::tree::TerminalNode *KEYWORD_ISTYPE();
    antlr4::tree::TerminalNode *KEYWORD_HASTYPE();
    antlr4::tree::TerminalNode *SYMBOL_AT();
    antlr4::tree::TerminalNode *KEYWORD_AS();
    Owned_expressionContext *owned_expression();
    Type_result_memberContext *type_result_member();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT SequenceExprContext : public Owned_expressionContext {
  public:
    SequenceExprContext(Owned_expressionContext *ctx);

    Sequence_expressionContext *sequence_expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class SYSMLV2FILE_EXPORT FunctionOperationExprContext : public Owned_expressionContext {
  public:
    FunctionOperationExprContext(Owned_expressionContext *ctx);

    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_ARROW();
    Reference_typingContext *reference_typing();
    Function_operation_argumentsContext *function_operation_arguments();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Owned_expressionContext* owned_expression();
  Owned_expressionContext* owned_expression(int precedence);
  class SYSMLV2FILE_EXPORT Function_operation_argumentsContext : public antlr4::ParserRuleContext {
  public:
    Function_operation_argumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_expressionContext *body_expression();
    Function_referenceContext *function_reference();
    Argument_listContext *argument_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_operation_argumentsContext* function_operation_arguments();

  class SYSMLV2FILE_EXPORT Type_reference_memberContext : public antlr4::ParserRuleContext {
  public:
    Type_reference_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_referenceContext *type_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_reference_memberContext* type_reference_member();

  class SYSMLV2FILE_EXPORT Type_result_memberContext : public antlr4::ParserRuleContext {
  public:
    Type_result_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_referenceContext *type_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_result_memberContext* type_result_member();

  class SYSMLV2FILE_EXPORT Type_referenceContext : public antlr4::ParserRuleContext {
  public:
    Type_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reference_typingContext *reference_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_referenceContext* type_reference();

  class SYSMLV2FILE_EXPORT Reference_typingContext : public antlr4::ParserRuleContext {
  public:
    Reference_typingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Reference_typingContext* reference_typing();

  class SYSMLV2FILE_EXPORT Sequence_expressionContext : public antlr4::ParserRuleContext {
  public:
    Sequence_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    Sequence_expression_listContext *sequence_expression_list();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sequence_expressionContext* sequence_expression();

  class SYSMLV2FILE_EXPORT Sequence_expression_listContext : public antlr4::ParserRuleContext {
  public:
    Sequence_expression_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Sequence_operator_expressionContext *sequence_operator_expression();
    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_COMMA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sequence_expression_listContext* sequence_expression_list();

  class SYSMLV2FILE_EXPORT Sequence_operator_expressionContext : public antlr4::ParserRuleContext {
  public:
    Sequence_operator_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expression_memberContext *owned_expression_member();
    antlr4::tree::TerminalNode *SYMBOL_COMMA();
    Sequence_expression_list_memberContext *sequence_expression_list_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sequence_operator_expressionContext* sequence_operator_expression();

  class SYSMLV2FILE_EXPORT Sequence_expression_list_memberContext : public antlr4::ParserRuleContext {
  public:
    Sequence_expression_list_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Sequence_expression_listContext *sequence_expression_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sequence_expression_list_memberContext* sequence_expression_list_member();

  class SYSMLV2FILE_EXPORT Function_referenceContext : public antlr4::ParserRuleContext {
  public:
    Function_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reference_typingContext *reference_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_referenceContext* function_reference();

  class SYSMLV2FILE_EXPORT Feature_chain_memberContext : public antlr4::ParserRuleContext {
  public:
    Feature_chain_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_reference_memberContext *feature_reference_member();
    Owned_feature_chain_memberContext *owned_feature_chain_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_chain_memberContext* feature_chain_member();

  class SYSMLV2FILE_EXPORT Owned_feature_chain_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_chain_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_feature_chain_memberContext* owned_feature_chain_member();

  class SYSMLV2FILE_EXPORT Base_expressionContext : public antlr4::ParserRuleContext {
  public:
    Base_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Invocation_expressionContext *invocation_expression();
    Constructor_expressionContext *constructor_expression();
    Null_expressionContext *null_expression();
    Literal_expressionContext *literal_expression();
    Metadata_access_expressionContext *metadata_access_expression();
    Feature_reference_expressionContext *feature_reference_expression();
    Body_expressionContext *body_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Base_expressionContext* base_expression();

  class SYSMLV2FILE_EXPORT Null_expressionContext : public antlr4::ParserRuleContext {
  public:
    Null_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_NULL();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Null_expressionContext* null_expression();

  class SYSMLV2FILE_EXPORT Feature_reference_expressionContext : public antlr4::ParserRuleContext {
  public:
    Feature_reference_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_reference_memberContext *feature_reference_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_reference_expressionContext* feature_reference_expression();

  class SYSMLV2FILE_EXPORT Feature_reference_memberContext : public antlr4::ParserRuleContext {
  public:
    Feature_reference_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_referenceContext *feature_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_reference_memberContext* feature_reference_member();

  class SYSMLV2FILE_EXPORT Feature_referenceContext : public antlr4::ParserRuleContext {
  public:
    Feature_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_referenceContext* feature_reference();

  class SYSMLV2FILE_EXPORT Metadata_access_expressionContext : public antlr4::ParserRuleContext {
  public:
    Metadata_access_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    antlr4::tree::TerminalNode *KEYWORD_METADATA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_access_expressionContext* metadata_access_expression();

  class SYSMLV2FILE_EXPORT Invocation_expressionContext : public antlr4::ParserRuleContext {
  public:
    Invocation_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Internal_invocation_expressionContext *internal_invocation_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Invocation_expressionContext* invocation_expression();

  class SYSMLV2FILE_EXPORT Internal_invocation_expressionContext : public antlr4::ParserRuleContext {
  public:
    Internal_invocation_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_feature_typingContext *owned_feature_typing();
    Argument_listContext *argument_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Internal_invocation_expressionContext* internal_invocation_expression();

  class SYSMLV2FILE_EXPORT Constructor_expressionContext : public antlr4::ParserRuleContext {
  public:
    Constructor_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_NEW();
    Owned_feature_typingContext *owned_feature_typing();
    Argument_listContext *argument_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Constructor_expressionContext* constructor_expression();

  class SYSMLV2FILE_EXPORT Argument_listContext : public antlr4::ParserRuleContext {
  public:
    Argument_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();
    Named_argument_listContext *named_argument_list();
    Positional_argument_listContext *positional_argument_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Argument_listContext* argument_list();

  class SYSMLV2FILE_EXPORT Positional_argument_listContext : public antlr4::ParserRuleContext {
  public:
    Positional_argument_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Owned_expressionContext *> owned_expression();
    Owned_expressionContext* owned_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Positional_argument_listContext* positional_argument_list();

  class SYSMLV2FILE_EXPORT Named_argument_listContext : public antlr4::ParserRuleContext {
  public:
    Named_argument_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Named_argument_memberContext *> named_argument_member();
    Named_argument_memberContext* named_argument_member(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Named_argument_listContext* named_argument_list();

  class SYSMLV2FILE_EXPORT Named_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Named_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Named_argumentContext *named_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Named_argument_memberContext* named_argument_member();

  class SYSMLV2FILE_EXPORT Named_argumentContext : public antlr4::ParserRuleContext {
  public:
    Named_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Parameter_redefinitionContext *parameter_redefinition();
    antlr4::tree::TerminalNode *SYMBOL_ASSIGN();
    Owned_expressionContext *owned_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Named_argumentContext* named_argument();

  class SYSMLV2FILE_EXPORT Parameter_redefinitionContext : public antlr4::ParserRuleContext {
  public:
    Parameter_redefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Parameter_redefinitionContext* parameter_redefinition();

  class SYSMLV2FILE_EXPORT Body_expressionContext : public antlr4::ParserRuleContext {
  public:
    Body_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expression_body_memberContext *expression_body_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Body_expressionContext* body_expression();

  class SYSMLV2FILE_EXPORT Expression_body_memberContext : public antlr4::ParserRuleContext {
  public:
    Expression_body_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expression_bodyContext *expression_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expression_body_memberContext* expression_body_member();

  class SYSMLV2FILE_EXPORT Expression_bodyContext : public antlr4::ParserRuleContext {
  public:
    Expression_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Function_body_partContext *function_body_part();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expression_bodyContext* expression_body();

  class SYSMLV2FILE_EXPORT Literal_expressionContext : public antlr4::ParserRuleContext {
  public:
    Literal_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_TRUE();
    antlr4::tree::TerminalNode *KEYWORD_FALSE();
    Literal_stringContext *literal_string();
    Literal_integerContext *literal_integer();
    Literal_realContext *literal_real();
    Literal_infinityContext *literal_infinity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Literal_expressionContext* literal_expression();

  class SYSMLV2FILE_EXPORT Literal_booleanContext : public antlr4::ParserRuleContext {
  public:
    Literal_booleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Boolean_valueContext *boolean_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Literal_booleanContext* literal_boolean();

  class SYSMLV2FILE_EXPORT Boolean_valueContext : public antlr4::ParserRuleContext {
  public:
    Boolean_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_TRUE();
    antlr4::tree::TerminalNode *KEYWORD_FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Boolean_valueContext* boolean_value();

  class SYSMLV2FILE_EXPORT Literal_stringContext : public antlr4::ParserRuleContext {
  public:
    Literal_stringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Literal_stringContext* literal_string();

  class SYSMLV2FILE_EXPORT Literal_integerContext : public antlr4::ParserRuleContext {
  public:
    Literal_integerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DECIMAL_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Literal_integerContext* literal_integer();

  class SYSMLV2FILE_EXPORT Literal_realContext : public antlr4::ParserRuleContext {
  public:
    Literal_realContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Real_valueContext *real_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Literal_realContext* literal_real();

  class SYSMLV2FILE_EXPORT Real_valueContext : public antlr4::ParserRuleContext {
  public:
    Real_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    std::vector<antlr4::tree::TerminalNode *> DECIMAL_VALUE();
    antlr4::tree::TerminalNode* DECIMAL_VALUE(size_t i);
    antlr4::tree::TerminalNode *EXPONENTIAL_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Real_valueContext* real_value();

  class SYSMLV2FILE_EXPORT Literal_infinityContext : public antlr4::ParserRuleContext {
  public:
    Literal_infinityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Literal_infinityContext* literal_infinity();

  class SYSMLV2FILE_EXPORT InteractionContext : public antlr4::ParserRuleContext {
  public:
    InteractionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INTERACTION();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InteractionContext* interaction();

  class SYSMLV2FILE_EXPORT Item_flowContext : public antlr4::ParserRuleContext {
  public:
    Item_flowContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FLOW();
    Item_flow_declarationContext *item_flow_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_flowContext* item_flow();

  class SYSMLV2FILE_EXPORT Succession_item_flowContext : public antlr4::ParserRuleContext {
  public:
    Succession_item_flowContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_SUCCESSION();
    antlr4::tree::TerminalNode *KEYWORD_FLOW();
    Item_flow_declarationContext *item_flow_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Succession_item_flowContext* succession_item_flow();

  class SYSMLV2FILE_EXPORT Item_flow_declarationContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_declarationContext *feature_declaration();
    std::vector<Item_flow_end_memberContext *> item_flow_end_member();
    Item_flow_end_memberContext* item_flow_end_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();
    Value_partContext *value_part();
    antlr4::tree::TerminalNode *KEYWORD_OF();
    Item_feature_memberContext *item_feature_member();
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    antlr4::tree::TerminalNode *KEYWORD_ALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_flow_declarationContext* item_flow_declaration();

  class SYSMLV2FILE_EXPORT Item_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Item_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_featureContext *item_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_feature_memberContext* item_feature_member();

  class SYSMLV2FILE_EXPORT Item_featureContext : public antlr4::ParserRuleContext {
  public:
    Item_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentificationContext *identification();
    Item_feature_specialization_partContext *item_feature_specialization_part();
    Value_partContext *value_part();
    Owned_feature_typingContext *owned_feature_typing();
    Multiplicity_boundsContext *multiplicity_bounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_featureContext* item_feature();

  class SYSMLV2FILE_EXPORT Item_feature_specialization_partContext : public antlr4::ParserRuleContext {
  public:
    Item_feature_specialization_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_partContext *multiplicity_part();
    std::vector<Feature_specializationContext *> feature_specialization();
    Feature_specializationContext* feature_specialization(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_feature_specialization_partContext* item_feature_specialization_part();

  class SYSMLV2FILE_EXPORT Item_flow_end_memberContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_end_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_flow_endContext *item_flow_end();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_flow_end_memberContext* item_flow_end_member();

  class SYSMLV2FILE_EXPORT Item_flow_endContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_flow_feature_memberContext *item_flow_feature_member();
    Owned_reference_subsettingContext *owned_reference_subsetting();
    antlr4::tree::TerminalNode *SYMBOL_DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_flow_endContext* item_flow_end();

  class SYSMLV2FILE_EXPORT Item_flow_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_flow_featureContext *item_flow_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_flow_feature_memberContext* item_flow_feature_member();

  class SYSMLV2FILE_EXPORT Item_flow_featureContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_flow_redefinitionContext *item_flow_redefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_flow_featureContext* item_flow_feature();

  class SYSMLV2FILE_EXPORT Item_flow_redefinitionContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_redefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_flow_redefinitionContext* item_flow_redefinition();

  class SYSMLV2FILE_EXPORT Value_partContext : public antlr4::ParserRuleContext {
  public:
    Value_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_valueContext *feature_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Value_partContext* value_part();

  class SYSMLV2FILE_EXPORT Feature_valueContext : public antlr4::ParserRuleContext {
  public:
    Feature_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_ASSIGN();
    antlr4::tree::TerminalNode *SYMBOL_DEF_ASSIGN();
    antlr4::tree::TerminalNode *KEYWORD_DEFAULT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_valueContext* feature_value();

  class SYSMLV2FILE_EXPORT Feature_assignmentContext : public antlr4::ParserRuleContext {
  public:
    Feature_assignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ASSIGN();
    Owned_expressionContext *owned_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_assignmentContext* feature_assignment();

  class SYSMLV2FILE_EXPORT MultiplicityContext : public antlr4::ParserRuleContext {
  public:
    MultiplicityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_subsetContext *multiplicity_subset();
    Multiplicity_rangeContext *multiplicity_range();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicityContext* multiplicity();

  class SYSMLV2FILE_EXPORT Multiplicity_subsetContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_subsetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_MULTIPLICITY();
    IdentificationContext *identification();
    SubsetsContext *subsets();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Multiplicity_subsetContext* multiplicity_subset();

  class SYSMLV2FILE_EXPORT Multiplicity_rangeContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_rangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_MULTIPLICITY();
    IdentificationContext *identification();
    Multiplicity_boundsContext *multiplicity_bounds();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Multiplicity_rangeContext* multiplicity_range();

  class SYSMLV2FILE_EXPORT Owned_multiplicityContext : public antlr4::ParserRuleContext {
  public:
    Owned_multiplicityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_boundsContext *multiplicity_bounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_multiplicityContext* owned_multiplicity();

  class SYSMLV2FILE_EXPORT Owned_multiplicity_rangeContext : public antlr4::ParserRuleContext {
  public:
    Owned_multiplicity_rangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_boundsContext *multiplicity_bounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_multiplicity_rangeContext* owned_multiplicity_range();

  class SYSMLV2FILE_EXPORT Multiplicity_boundsContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_boundsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_OPEN();
    std::vector<Multiplicity_expression_memberContext *> multiplicity_expression_member();
    Multiplicity_expression_memberContext* multiplicity_expression_member(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_CLOSE();
    antlr4::tree::TerminalNode *SYMBOL_DDOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Multiplicity_boundsContext* multiplicity_bounds();

  class SYSMLV2FILE_EXPORT Multiplicity_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Internal_multiplicity_expression_memberContext *internal_multiplicity_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Multiplicity_expression_memberContext* multiplicity_expression_member();

  class SYSMLV2FILE_EXPORT Internal_multiplicity_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Internal_multiplicity_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Literal_expressionContext *literal_expression();
    Feature_reference_expressionContext *feature_reference_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Internal_multiplicity_expression_memberContext* internal_multiplicity_expression_member();

  class SYSMLV2FILE_EXPORT MetaclassContext : public antlr4::ParserRuleContext {
  public:
    MetaclassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_METACLASS();
    Type_bodyContext *type_body();
    IdentificationContext *identification();
    Classifier_declarationContext *classifier_declaration();
    Type_prefixContext *type_prefix();
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);
    Specializes_operatorContext *specializes_operator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MetaclassContext* metaclass();

  class SYSMLV2FILE_EXPORT Prefix_metadata_annotationContext : public antlr4::ParserRuleContext {
  public:
    Prefix_metadata_annotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_HASHTAG();
    Prefix_metadata_featureContext *prefix_metadata_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Prefix_metadata_annotationContext* prefix_metadata_annotation();

  class SYSMLV2FILE_EXPORT Prefix_metadata_memberContext : public antlr4::ParserRuleContext {
  public:
    Prefix_metadata_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_HASHTAG();
    Prefix_metadata_featureContext *prefix_metadata_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Prefix_metadata_memberContext* prefix_metadata_member();

  class SYSMLV2FILE_EXPORT Prefix_metadata_featureContext : public antlr4::ParserRuleContext {
  public:
    Prefix_metadata_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_feature_typingContext *owned_feature_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Prefix_metadata_featureContext* prefix_metadata_feature();

  class SYSMLV2FILE_EXPORT Metadata_featureContext : public antlr4::ParserRuleContext {
  public:
    Metadata_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_feature_declarationContext *metadata_feature_declaration();
    antlr4::tree::TerminalNode *SYMBOL_AT();
    antlr4::tree::TerminalNode *KEYWORD_METADATA();
    antlr4::tree::TerminalNode *KEYWORD_ABOUT();
    std::vector<AnnotationContext *> annotation();
    AnnotationContext* annotation(size_t i);
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_COMMA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_featureContext* metadata_feature();

  class SYSMLV2FILE_EXPORT Metadata_feature_declarationContext : public antlr4::ParserRuleContext {
  public:
    Metadata_feature_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_feature_typingContext *owned_feature_typing();
    IdentificationContext *identification();
    Typed_by_operatorContext *typed_by_operator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_feature_declarationContext* metadata_feature_declaration();

  class SYSMLV2FILE_EXPORT Metadata_bodyContext : public antlr4::ParserRuleContext {
  public:
    Metadata_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Metadata_body_elementContext *> metadata_body_element();
    Metadata_body_elementContext* metadata_body_element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_bodyContext* metadata_body();

  class SYSMLV2FILE_EXPORT Metadata_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Metadata_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_memberContext *non_feature_member();
    Metadata_body_feature_memberContext *metadata_body_feature_member();
    Alias_memberContext *alias_member();
    Import_declarationContext *import_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_body_elementContext* metadata_body_element();

  class SYSMLV2FILE_EXPORT Metadata_body_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Metadata_body_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_body_featureContext *metadata_body_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_body_feature_memberContext* metadata_body_feature_member();

  class SYSMLV2FILE_EXPORT Metadata_body_featureContext : public antlr4::ParserRuleContext {
  public:
    Metadata_body_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_redefinitionContext *owned_redefinition();
    Metadata_bodyContext *metadata_body();
    antlr4::tree::TerminalNode *KEYWORD_FEATURE();
    Redefines_operatorContext *redefines_operator();
    Feature_specialization_partContext *feature_specialization_part();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_body_featureContext* metadata_body_feature();

  class SYSMLV2FILE_EXPORT PackageContext : public antlr4::ParserRuleContext {
  public:
    PackageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Package_declarationContext *package_declaration();
    Package_bodyContext *package_body();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PackageContext* package();

  class SYSMLV2FILE_EXPORT Library_packageContext : public antlr4::ParserRuleContext {
  public:
    Library_packageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_LIBRARY();
    Package_declarationContext *package_declaration();
    Package_bodyContext *package_body();
    antlr4::tree::TerminalNode *KEYWORD_STANDARD();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Library_packageContext* library_package();

  class SYSMLV2FILE_EXPORT Package_declarationContext : public antlr4::ParserRuleContext {
  public:
    Package_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_PACKAGE();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Package_declarationContext* package_declaration();

  class SYSMLV2FILE_EXPORT Package_bodyContext : public antlr4::ParserRuleContext {
  public:
    Package_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Namespace_body_elementContext *> namespace_body_element();
    Namespace_body_elementContext* namespace_body_element(size_t i);
    std::vector<Element_filter_memberContext *> element_filter_member();
    Element_filter_memberContext* element_filter_member(size_t i);
    std::vector<ElementContext *> element();
    ElementContext* element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Package_bodyContext* package_body();

  class SYSMLV2FILE_EXPORT Element_filter_memberContext : public antlr4::ParserRuleContext {
  public:
    Element_filter_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FILTER();
    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Element_filter_memberContext* element_filter_member();

  class SYSMLV2FILE_EXPORT Meta_assignmentContext : public antlr4::ParserRuleContext {
  public:
    Meta_assignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_ASSIGN();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_META();
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Meta_assignmentContext* meta_assignment();

  class SYSMLV2FILE_EXPORT Typed_by_operatorContext : public antlr4::ParserRuleContext {
  public:
    Typed_by_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_TYPED_BY();
    antlr4::tree::TerminalNode *KEYWORD_TYPED();
    antlr4::tree::TerminalNode *KEYWORD_BY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Typed_by_operatorContext* typed_by_operator();

  class SYSMLV2FILE_EXPORT Specializes_operatorContext : public antlr4::ParserRuleContext {
  public:
    Specializes_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SPECIALIZES();
    antlr4::tree::TerminalNode *KEYWORD_SPECIALIZES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Specializes_operatorContext* specializes_operator();

  class SYSMLV2FILE_EXPORT Subsets_operatorContext : public antlr4::ParserRuleContext {
  public:
    Subsets_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SPECIALIZES();
    antlr4::tree::TerminalNode *KEYWORD_SUBSETS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Subsets_operatorContext* subsets_operator();

  class SYSMLV2FILE_EXPORT References_operatorContext : public antlr4::ParserRuleContext {
  public:
    References_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_REFERENCES();
    antlr4::tree::TerminalNode *KEYWORD_REFERENCES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  References_operatorContext* references_operator();

  class SYSMLV2FILE_EXPORT Redefines_operatorContext : public antlr4::ParserRuleContext {
  public:
    Redefines_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_REDEFINES();
    antlr4::tree::TerminalNode *KEYWORD_REDEFINES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Redefines_operatorContext* redefines_operator();

  class SYSMLV2FILE_EXPORT Conjugates_operatorContext : public antlr4::ParserRuleContext {
  public:
    Conjugates_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_CONJUGATES();
    antlr4::tree::TerminalNode *KEYWORD_CONJUGATES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Conjugates_operatorContext* conjugates_operator();

  class SYSMLV2FILE_EXPORT Crosses_operatorContext : public antlr4::ParserRuleContext {
  public:
    Crosses_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_CROSSES();
    antlr4::tree::TerminalNode *KEYWORD_CROSSES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Crosses_operatorContext* crosses_operator();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool owned_expressionSempred(Owned_expressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

