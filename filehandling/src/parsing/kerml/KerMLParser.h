
// Generated from ./KerML.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "../../sysmlv2file_global.h"



class SYSMLV2FILE_EXPORT KerMLParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, TYPED_BY = 5, SPECIALIZES = 6, 
    SUBSETS = 7, REFERENCES = 8, REDEFINES = 9, CONJUNGATES = 10, KEYWORD_ABOUT = 11, 
    KEYWORD_ABSTRACT = 12, KEYWORD_ALIAS = 13, KEYWORD_ALL = 14, KEYWORD_AND = 15, 
    KEYWORD_AS = 16, KEYWORD_ASSOC = 17, KEYWORD_BEHAVIOR = 18, KEYWORD_BINDING = 19, 
    KEYWORD_BOOL = 20, KEYWORD_BY = 21, KEYWORD_CHAINS = 22, KEYWORD_CLASS = 23, 
    KEYWORD_CLASSIFIER = 24, KEYWORD_COMMENT = 25, KEYWORD_COMPOSITE = 26, 
    KEYWORD_CONJUGATE = 27, KEYWORD_CONJUGATES = 28, KEYWORD_CONJUGATION = 29, 
    KEYWORD_CONNECTOR = 30, KEYWORD_DATATYPE = 31, KEYWORD_DEFAULT = 32, 
    KEYWORD_DEPENDENCY = 33, KEYWORD_DERIVED = 34, KEYWORD_DIFFERENCES = 35, 
    KEYWORD_DISJOINING = 36, KEYWORD_DISJOINT = 37, KEYWORD_DOC = 38, KEYWORD_ELSE = 39, 
    KEYWORD_END = 40, KEYWORD_EXPR = 41, KEYWORD_FALSE = 42, KEYWORD_FEATURE = 43, 
    KEYWORD_FEATURED = 44, KEYWORD_FEATURING = 45, KEYWORD_FILTER = 46, 
    KEYWORD_FIRST = 47, KEYWORD_FLOW = 48, KEYWORD_FOR = 49, KEYWORD_FROM = 50, 
    KEYWORD_FUNCTION = 51, KEYWORD_HASTYPE = 52, KEYWORD_IF = 53, KEYWORD_INTERSECTS = 54, 
    KEYWORD_IMPLIES = 55, KEYWORD_IMPORT = 56, KEYWORD_IN = 57, KEYWORD_INOUT = 58, 
    KEYWORD_INTERACTION = 59, KEYWORD_INV = 60, KEYWORD_INVERSE = 61, KEYWORD_INVERTING = 62, 
    KEYWORD_ISTYPE = 63, KEYWORD_LANGUAGE = 64, KEYWORD_MEMBER = 65, KEYWORD_METACLASS = 66, 
    KEYWORD_METADATA = 67, KEYWORD_MULTIPLICITY = 68, KEYWORD_NAMESPACE = 69, 
    KEYWORD_NONUNIQUE = 70, KEYWORD_NOT = 71, KEYWORD_NULL = 72, KEYWORD_OF = 73, 
    KEYWORD_OR = 74, KEYWORD_ORDERED = 75, KEYWORD_OUT = 76, KEYWORD_PACKAGE = 77, 
    KEYWORD_PORTION = 78, KEYWORD_PREDICATE = 79, KEYWORD_PRIVATE = 80, 
    KEYWORD_PROTECTED = 81, KEYWORD_PUBLIC = 82, KEYWORD_READONLY = 83, 
    KEYWORD_REDEFINES = 84, KEYWORD_REDEFINITION = 85, KEYWORD_REFERENCES = 86, 
    KEYWORD_REP = 87, KEYWORD_RETURN = 88, KEYWORD_SPECILIZATION = 89, KEYWORD_SPECIALIZES = 90, 
    KEYWORD_STEP = 91, KEYWORD_STRUCT = 92, KEYWORD_SUBCLASSIFIER = 93, 
    KEYWORD_SUBSET = 94, KEYWORD_SUBSETS = 95, KEYWORD_SUBTYPE = 96, KEYWORD_SUCCSESSION = 97, 
    KEYWORD_THEN = 98, KEYWORD_TO = 99, KEYWORD_TRUE = 100, KEYWORD_TYPE = 101, 
    KEYWORD_TYPED = 102, KEYWORD_TYPING = 103, KEYWORD_UNIONS = 104, KEYWORD_XOR = 105, 
    SINGLE_LINE_NOTE = 106, MULTI_LINE_NOTE = 107, REGULAR_COMMENT = 108, 
    SYMBOL_COMMENT_BLOCK_START = 109, SYMBOL_NOTE_BLOCK_START = 110, SYMBOL_COMMENT_BLOCK_END = 111, 
    SYMBOL_STATEMENT_DELIMITER = 112, SYMBOL_STAR = 113, SYMBOL_NAMESPACE_SUBSET = 114, 
    SYMBOL_TYPED_BY = 115, SYMBOL_SPECIALIZES = 116, SYMBOL_REFERENCES = 117, 
    SYMBOL_REDEFINES = 118, SYMBOL_CONJUNGATES = 119, SYMBOL_ROUND_BRACKET_OPEN = 120, 
    SYMBOL_ROUND_BRACKET_CLOSE = 121, SYMBOL_CURLY_BRACKET_OPEN = 122, SYMBOL_CURLY_BRACKET_CLOSE = 123, 
    SYMBOL_SQUARE_BRACKET_OPEN = 124, SYMBOL_SQUARE_BRACKET_CLOSE = 125, 
    SYMBOL_COMMA = 126, SYMBOL_AT = 127, SYMBOL_HASHTAG = 128, SYMBOL_MOD = 129, 
    SYMBOL_AND = 130, SYMBOL_UPPER = 131, SYMBOL_VERTICAL_LINE = 132, SYMBOL_DOUBLE_STAR = 133, 
    SYMBOL_PLUS = 134, SYMBOL_MINUS = 135, SYMBOL_SLASH = 136, SYMBOL_ARROOW = 137, 
    SYMBOL_DOT = 138, SYMBOL_DDOT = 139, SYMBOL_SMALLER = 140, SYMBOL_SMALLER_EQUAL = 141, 
    SYMBOL_ASSIGN = 142, SYMBOL_DEF_ASSIGN = 143, SYMBOL_EQUALS = 144, SYMBOL_IFF_EQUALS = 145, 
    SYMBOL_NOT_EQUALS = 146, SYMBOL_IFF_NOT_EQUALS = 147, SYMBOL_GREATER = 148, 
    SYMBOL_GREATER_EQUALS = 149, SYMBOL_QUESTION = 150, SYMBOL_DQUESTION = 151, 
    SYMBOL_DOT_QUESTION = 152, NAME = 153, BASIC_NAME = 154, UNRESTRICTED_NAME = 155, 
    DECIMAL_VALUE = 156, EXPONENTIAL_VALUE = 157, STRING_VALUE = 158, WS = 159
  };

  enum {
    RuleStart = 0, RuleStartRule = 1, RuleElements = 2, RuleIdentification = 3, 
    RuleRelationship_body = 4, RuleRelationship_onwed_elements = 5, RuleRelationship_owned_element = 6, 
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
    RuleFeature = 69, RuleFeature_prefix = 70, RuleFeature_direction = 71, 
    RuleFeature_declaration = 72, RuleFeature_identification = 73, RuleFeature_relationship_part = 74, 
    RuleChaining_part = 75, RuleInverting_part = 76, RuleType_featuring_part = 77, 
    RuleFeature_specialization_part = 78, RuleMultiplicity_part = 79, RuleFeature_specilization = 80, 
    RuleTypings = 81, RuleTyped_by = 82, RuleSubsettings = 83, RuleSubsets = 84, 
    RuleReferences = 85, RuleRedefinitions = 86, RuleRedefines = 87, RuleFeature_typing = 88, 
    RuleOwned_feature_typing = 89, RuleSubsetting = 90, RuleOwned_subsetting = 91, 
    RuleOwned_reference_subsetting = 92, RuleRedefinition = 93, RuleOwned_redefinition = 94, 
    RuleOwned_feature_chain = 95, RuleFeature_chain = 96, RuleOwned_feature_chaining = 97, 
    RuleFeature_inverting = 98, RuleOwned_feature_inverting = 99, RuleType_featuring = 100, 
    RuleOwned_type_featuring = 101, RuleData_type = 102, RuleClass = 103, 
    RuleStructure = 104, RuleAssociation = 105, RuleAssociation_structure = 106, 
    RuleConnector = 107, RuleConnector_declaration = 108, RuleBinary_connector_declaration = 109, 
    RuleNary_connector_declaration = 110, RuleConnector_end_member = 111, 
    RuleConnector_end = 112, RuleBinding_connector = 113, RuleBinding_connector_declaration = 114, 
    RuleSuccession = 115, RuleSuccession_declaration = 116, RuleBehavior = 117, 
    RuleStep = 118, RuleFunction = 119, RuleFunction_body = 120, RuleFunction_body_part = 121, 
    RuleReturn_feature_member = 122, RuleResult_expression_member = 123, 
    RuleExpression = 124, RulePredicate = 125, RuleBoolean_expression = 126, 
    RuleInvariant = 127, RuleOwned_expression_reference_member = 128, RuleOwned_expression_reference = 129, 
    RuleOwned_expression_member = 130, RuleOwned_expressions = 131, RuleOwned_expression = 132, 
    RuleConditional_expression = 133, RuleConditional_binary_operator_expression = 134, 
    RuleConditional_binary_operator = 135, RuleBinary_operator_expression = 136, 
    RuleBinary_operator = 137, RuleUnary_operator_expression = 138, RuleUnary_operator = 139, 
    RuleClassification_expression = 140, RuleClassification = 141, RuleClassification_test_operator = 142, 
    RuleCast_operator = 143, RuleMetaclassification_expression = 144, RuleArgument_expression_member = 145, 
    RuleArgument_expression = 146, RuleArgument_expression_value = 147, 
    RuleMetadata_argument_member = 148, RuleMetadata_argument = 149, RuleMetadata_value = 150, 
    RuleMetadata_reference = 151, RuleMetadataclassification_test_operator = 152, 
    RuleMeta_cast_operator = 153, RuleExtend_expression = 154, RuleType_reference_member = 155, 
    RuleType_result_member = 156, RuleType_reference = 157, RuleReference_typing = 158, 
    RulePrimary_expressions = 159, RulePrimary_expression = 160, RuleNon_feature_chain_primary_expression = 161, 
    RuleNon_feature_chain_primary_argument_value = 162, RuleBracket_expression = 163, 
    RuleIndex_expression = 164, RuleSequence_expression = 165, RuleSequence_expression_list = 166, 
    RuleSequence_operator_expression = 167, RuleSequence_expression_list_member = 168, 
    RuleFeature_chain_expression = 169, RuleCollect_expression = 170, RuleSelect_expression = 171, 
    RuleFunction_operation_expression = 172, RuleBody_argument_member = 173, 
    RuleBody_argument = 174, RuleBody_argument_value = 175, RuleBody_expression_member = 176, 
    RuleFunction_reference_argument_member = 177, RuleFunction_reference_argument = 178, 
    RuleFunction_reference_arugment_value = 179, RuleFunction_reference_expression = 180, 
    RuleFunction_reference_member = 181, RuleFunction_reference = 182, RuleFeature_chain_member = 183, 
    RuleOwned_feature_chain_member = 184, RuleBase_expression = 185, RuleNull_expression = 186, 
    RuleFeature_reference_expression = 187, RuleFeature_reference_member = 188, 
    RuleFeature_reference = 189, RuleMetadata_access_expression = 190, RuleInvocation_expression = 191, 
    RuleInternal_invocation_expression = 192, RuleArgument_list = 193, RulePositional_argument_list = 194, 
    RuleNamed_argument_list = 195, RuleNamed_argument_member = 196, RuleNamed_argument = 197, 
    RuleParamenter_redefinition = 198, RuleBody_expression = 199, RuleExpression_body_member = 200, 
    RuleExpression_body = 201, RuleLiteral_expression = 202, RuleLiteral_boolean = 203, 
    RuleBoolean_value = 204, RuleLiteral_string = 205, RuleLiteral_integer = 206, 
    RuleLiteral_real = 207, RuleReal_value = 208, RuleLiteral_infinity = 209, 
    RuleInteraction = 210, RuleItem_flow = 211, RuleSuccession_item_flow = 212, 
    RuleItem_flow_declaration = 213, RuleItem_feature_member = 214, RuleItem_feature = 215, 
    RuleItem_feature_specilization_part = 216, RuleItem_flow_end_member = 217, 
    RuleItem_flow_end = 218, RuleItem_flow_feature_member = 219, RuleItem_flow_feature = 220, 
    RuleItem_flow_redefinition = 221, RuleValue_part = 222, RuleFeature_value = 223, 
    RuleMultiplicity = 224, RuleMultiplicity_subset = 225, RuleMultiplicity_range = 226, 
    RuleOwned_multiplicity = 227, RuleOwned_multiplicity_range = 228, RuleMultiplicity_bounds = 229, 
    RuleMultiplicity_expression_member = 230, RuleInternal_multiplicity_expression_member = 231, 
    RuleMetaclass = 232, RulePrefix_metadata_annotation = 233, RulePrefix_metadata_member = 234, 
    RulePrefix_metadata_feature = 235, RuleMetadata_feature = 236, RuleMetadata_feature_declaration = 237, 
    RuleMetadata_body = 238, RuleMetadata_body_element = 239, RuleMetadata_body_feature_member = 240, 
    RuleMetadata_body_feature = 241, RulePackage = 242, RuleLibrary_package = 243, 
    RulePackage_declaration = 244, RulePackage_body = 245, RuleElement_filter_member = 246, 
    RuleMeta_assignment = 247
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
  class Relationship_onwed_elementsContext;
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
  class Feature_prefixContext;
  class Feature_directionContext;
  class Feature_declarationContext;
  class Feature_identificationContext;
  class Feature_relationship_partContext;
  class Chaining_partContext;
  class Inverting_partContext;
  class Type_featuring_partContext;
  class Feature_specialization_partContext;
  class Multiplicity_partContext;
  class Feature_specilizationContext;
  class TypingsContext;
  class Typed_byContext;
  class SubsettingsContext;
  class SubsetsContext;
  class ReferencesContext;
  class RedefinitionsContext;
  class RedefinesContext;
  class Feature_typingContext;
  class Owned_feature_typingContext;
  class SubsettingContext;
  class Owned_subsettingContext;
  class Owned_reference_subsettingContext;
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
  class Owned_expressionsContext;
  class Owned_expressionContext;
  class Conditional_expressionContext;
  class Conditional_binary_operator_expressionContext;
  class Conditional_binary_operatorContext;
  class Binary_operator_expressionContext;
  class Binary_operatorContext;
  class Unary_operator_expressionContext;
  class Unary_operatorContext;
  class Classification_expressionContext;
  class ClassificationContext;
  class Classification_test_operatorContext;
  class Cast_operatorContext;
  class Metaclassification_expressionContext;
  class Argument_expression_memberContext;
  class Argument_expressionContext;
  class Argument_expression_valueContext;
  class Metadata_argument_memberContext;
  class Metadata_argumentContext;
  class Metadata_valueContext;
  class Metadata_referenceContext;
  class Metadataclassification_test_operatorContext;
  class Meta_cast_operatorContext;
  class Extend_expressionContext;
  class Type_reference_memberContext;
  class Type_result_memberContext;
  class Type_referenceContext;
  class Reference_typingContext;
  class Primary_expressionsContext;
  class Primary_expressionContext;
  class Non_feature_chain_primary_expressionContext;
  class Non_feature_chain_primary_argument_valueContext;
  class Bracket_expressionContext;
  class Index_expressionContext;
  class Sequence_expressionContext;
  class Sequence_expression_listContext;
  class Sequence_operator_expressionContext;
  class Sequence_expression_list_memberContext;
  class Feature_chain_expressionContext;
  class Collect_expressionContext;
  class Select_expressionContext;
  class Function_operation_expressionContext;
  class Body_argument_memberContext;
  class Body_argumentContext;
  class Body_argument_valueContext;
  class Body_expression_memberContext;
  class Function_reference_argument_memberContext;
  class Function_reference_argumentContext;
  class Function_reference_arugment_valueContext;
  class Function_reference_expressionContext;
  class Function_reference_memberContext;
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
  class Argument_listContext;
  class Positional_argument_listContext;
  class Named_argument_listContext;
  class Named_argument_memberContext;
  class Named_argumentContext;
  class Paramenter_redefinitionContext;
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
  class Item_feature_specilization_partContext;
  class Item_flow_end_memberContext;
  class Item_flow_endContext;
  class Item_flow_feature_memberContext;
  class Item_flow_featureContext;
  class Item_flow_redefinitionContext;
  class Value_partContext;
  class Feature_valueContext;
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

  class  StartContext : public antlr4::ParserRuleContext {
  public:
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementsContext *elements();
    antlr4::tree::TerminalNode *EOF();

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
    std::vector<ElementContext *> element();
    ElementContext* element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementsContext* elements();

  class  IdentificationContext : public antlr4::ParserRuleContext {
  public:
    IdentificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SMALLER();
    antlr4::tree::TerminalNode *NAME();
    antlr4::tree::TerminalNode *SYMBOL_GREATER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdentificationContext* identification();

  class  Relationship_bodyContext : public antlr4::ParserRuleContext {
  public:
    Relationship_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Relationship_onwed_elementsContext *relationship_onwed_elements();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Relationship_bodyContext* relationship_body();

  class  Relationship_onwed_elementsContext : public antlr4::ParserRuleContext {
  public:
    Relationship_onwed_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementsContext *elements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Relationship_onwed_elementsContext* relationship_onwed_elements();

  class  Relationship_owned_elementContext : public antlr4::ParserRuleContext {
  public:
    Relationship_owned_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_related_elementContext *owned_related_element();
    Owned_annotationContext *owned_annotation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Relationship_owned_elementContext* relationship_owned_element();

  class  Owned_related_elementContext : public antlr4::ParserRuleContext {
  public:
    Owned_related_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_elementContext *non_feature_element();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_related_elementContext* owned_related_element();

  class  DependencyContext : public antlr4::ParserRuleContext {
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
   
  };

  DependencyContext* dependency();

  class  AnnotationContext : public antlr4::ParserRuleContext {
  public:
    AnnotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AnnotationContext* annotation();

  class  Owned_annotationContext : public antlr4::ParserRuleContext {
  public:
    Owned_annotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotating_elementContext *annotating_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_annotationContext* owned_annotation();

  class  Annotating_elementContext : public antlr4::ParserRuleContext {
  public:
    Annotating_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CommentContext *comment();
    DocumentationContext *documentation();
    Textual_representationContext *textual_representation();
    Metadata_featureContext *metadata_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotating_elementContext* annotating_element();

  class  CommentContext : public antlr4::ParserRuleContext {
  public:
    CommentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REGULAR_COMMENT();
    antlr4::tree::TerminalNode *KEYWORD_COMMENT();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *STRING_VALUE();
    antlr4::tree::TerminalNode *KEYWORD_ABOUT();
    std::vector<AnnotationContext *> annotation();
    AnnotationContext* annotation(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CommentContext* comment();

  class  DocumentationContext : public antlr4::ParserRuleContext {
  public:
    DocumentationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_DOC();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *REGULAR_COMMENT();
    antlr4::tree::TerminalNode *STRING_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DocumentationContext* documentation();

  class  Textual_representationContext : public antlr4::ParserRuleContext {
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
   
  };

  Textual_representationContext* textual_representation();

  class  Root_namespaceContext : public antlr4::ParserRuleContext {
  public:
    Root_namespaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Namespace_body_elementsContext *namespace_body_elements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Root_namespaceContext* root_namespace();

  class  NamespaceContext : public antlr4::ParserRuleContext {
  public:
    NamespaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Namespace_declarationContext *namespace_declaration();
    Namespace_bodyContext *namespace_body();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceContext* namespace_();

  class  Namespace_declarationContext : public antlr4::ParserRuleContext {
  public:
    Namespace_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_NAMESPACE();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_declarationContext* namespace_declaration();

  class  Namespace_bodyContext : public antlr4::ParserRuleContext {
  public:
    Namespace_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Namespace_body_elementContext *namespace_body_element();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_bodyContext* namespace_body();

  class  Namespace_body_elementsContext : public antlr4::ParserRuleContext {
  public:
    Namespace_body_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementsContext *elements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_body_elementsContext* namespace_body_elements();

  class  Namespace_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Namespace_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Namespace_memberContext *namespace_member();
    Alias_memberContext *alias_member();
    Namespace_importContext *namespace_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_body_elementContext* namespace_body_element();

  class  Member_prefixContext : public antlr4::ParserRuleContext {
  public:
    Member_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Visibility_indicatorContext *visibility_indicator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Member_prefixContext* member_prefix();

  class  Visibility_indicatorContext : public antlr4::ParserRuleContext {
  public:
    Visibility_indicatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_PUBLIC();
    antlr4::tree::TerminalNode *KEYWORD_PRIVATE();
    antlr4::tree::TerminalNode *KEYWORD_PROTECTED();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Visibility_indicatorContext* visibility_indicator();

  class  Namespace_memberContext : public antlr4::ParserRuleContext {
  public:
    Namespace_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_memberContext *non_feature_member();
    Namespace_feature_memberContext *namespace_feature_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_memberContext* namespace_member();

  class  Non_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Non_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Non_feature_elementContext *non_feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Non_feature_memberContext* non_feature_member();

  class  Namespace_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Namespace_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_feature_memberContext* namespace_feature_member();

  class  Alias_memberContext : public antlr4::ParserRuleContext {
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
   
  };

  Alias_memberContext* alias_member();

  class  Qualified_nameContext : public antlr4::ParserRuleContext {
  public:
    Qualified_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_NAMESPACE_SUBSET();
    antlr4::tree::TerminalNode* SYMBOL_NAMESPACE_SUBSET(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Qualified_nameContext* qualified_name();

  class  Namespace_importContext : public antlr4::ParserRuleContext {
  public:
    Namespace_importContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_IMPORT();
    Import_declarationContext *import_declaration();
    Visibility_indicatorContext *visibility_indicator();
    antlr4::tree::TerminalNode *KEYWORD_ALL();
    Relationship_bodyContext *relationship_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Namespace_importContext* namespace_import();

  class  Import_declarationContext : public antlr4::ParserRuleContext {
  public:
    Import_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Membership_importContext *membership_import();
    Namespace_importContext *namespace_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Import_declarationContext* import_declaration();

  class  Membership_importContext : public antlr4::ParserRuleContext {
  public:
    Membership_importContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    antlr4::tree::TerminalNode *SYMBOL_NAMESPACE_SUBSET();
    antlr4::tree::TerminalNode *SYMBOL_DOUBLE_STAR();
    antlr4::tree::TerminalNode *SYMBOL_STAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Membership_importContext* membership_import();

  class  Filter_packageContext : public antlr4::ParserRuleContext {
  public:
    Filter_packageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Import_declarationContext *import_declaration();
    Filter_package_memberContext *filter_package_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Filter_packageContext* filter_package();

  class  Filter_package_memberContext : public antlr4::ParserRuleContext {
  public:
    Filter_package_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_OPEN();
    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Filter_package_memberContext* filter_package_member();

  class  ElementContext : public antlr4::ParserRuleContext {
  public:
    ElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotating_elementContext *annotating_element();
    Non_feature_elementContext *non_feature_element();
    Feature_elementContext *feature_element();
    Additional_optionsContext *additional_options();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementContext* element();

  class  Non_feature_elementContext : public antlr4::ParserRuleContext {
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
   
  };

  Non_feature_elementContext* non_feature_element();

  class  Feature_elementContext : public antlr4::ParserRuleContext {
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
   
  };

  Feature_elementContext* feature_element();

  class  Additional_optionsContext : public antlr4::ParserRuleContext {
  public:
    Additional_optionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Meta_assignmentContext *meta_assignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Additional_optionsContext* additional_options();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_TYPE();
    Type_declarationContext *type_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeContext* type();

  class  Type_prefixContext : public antlr4::ParserRuleContext {
  public:
    Type_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ABSTRACT();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_prefixContext* type_prefix();

  class  Type_declarationContext : public antlr4::ParserRuleContext {
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
   
  };

  Type_declarationContext* type_declaration();

  class  Specialization_partContext : public antlr4::ParserRuleContext {
  public:
    Specialization_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SPECIALIZES();
    std::vector<Owned_specializationContext *> owned_specialization();
    Owned_specializationContext* owned_specialization(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Specialization_partContext* specialization_part();

  class  Conjugation_partContext : public antlr4::ParserRuleContext {
  public:
    Conjugation_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONJUNGATES();
    Owned_conjugationContext *owned_conjugation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Conjugation_partContext* conjugation_part();

  class  Type_relationship_partContext : public antlr4::ParserRuleContext {
  public:
    Type_relationship_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Disjoining_partContext *disjoining_part();
    Unioning_partContext *unioning_part();
    Intersecting_partContext *intersecting_part();
    Differencing_partContext *differencing_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_relationship_partContext* type_relationship_part();

  class  Disjoining_partContext : public antlr4::ParserRuleContext {
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
   
  };

  Disjoining_partContext* disjoining_part();

  class  Unioning_partContext : public antlr4::ParserRuleContext {
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
   
  };

  Unioning_partContext* unioning_part();

  class  Intersecting_partContext : public antlr4::ParserRuleContext {
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
   
  };

  Intersecting_partContext* intersecting_part();

  class  Differencing_partContext : public antlr4::ParserRuleContext {
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
   
  };

  Differencing_partContext* differencing_part();

  class  Type_bodyContext : public antlr4::ParserRuleContext {
  public:
    Type_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Type_body_elementsContext *type_body_elements();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_bodyContext* type_body();

  class  Type_body_elementsContext : public antlr4::ParserRuleContext {
  public:
    Type_body_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Type_body_elementContext *> type_body_element();
    Type_body_elementContext* type_body_element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_body_elementsContext* type_body_elements();

  class  Type_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Type_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_elementContext *non_feature_element();
    Feature_elementContext *feature_element();
    Alias_memberContext *alias_member();
    Namespace_importContext *namespace_import();
    Additional_optionsContext *additional_options();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_body_elementContext* type_body_element();

  class  SpecializationContext : public antlr4::ParserRuleContext {
  public:
    SpecializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_SUBTYPE();
    Specific_typeContext *specific_type();
    antlr4::tree::TerminalNode *SPECIALIZES();
    General_typeContext *general_type();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *KEYWORD_SPECILIZATION();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SpecializationContext* specialization();

  class  Owned_specializationContext : public antlr4::ParserRuleContext {
  public:
    Owned_specializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_specializationContext* owned_specialization();

  class  Specific_typeContext : public antlr4::ParserRuleContext {
  public:
    Specific_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Specific_typeContext* specific_type();

  class  General_typeContext : public antlr4::ParserRuleContext {
  public:
    General_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  General_typeContext* general_type();

  class  ConjunctionContext : public antlr4::ParserRuleContext {
  public:
    ConjunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_CONJUGATE();
    antlr4::tree::TerminalNode *CONJUNGATES();
    Relationship_bodyContext *relationship_body();
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    std::vector<Feature_chainContext *> feature_chain();
    Feature_chainContext* feature_chain(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_CONJUGATION();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConjunctionContext* conjunction();

  class  Owned_conjugationContext : public antlr4::ParserRuleContext {
  public:
    Owned_conjugationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_conjugationContext* owned_conjugation();

  class  DisjoiningContext : public antlr4::ParserRuleContext {
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
   
  };

  DisjoiningContext* disjoining();

  class  Owned_disjoiningContext : public antlr4::ParserRuleContext {
  public:
    Owned_disjoiningContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_disjoiningContext* owned_disjoining();

  class  UnioningContext : public antlr4::ParserRuleContext {
  public:
    UnioningContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnioningContext* unioning();

  class  IntersectingContext : public antlr4::ParserRuleContext {
  public:
    IntersectingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntersectingContext* intersecting();

  class  DifferencingContext : public antlr4::ParserRuleContext {
  public:
    DifferencingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DifferencingContext* differencing();

  class  Feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_feature_memberContext *type_feature_member();
    Owned_feature_memberContext *owned_feature_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_memberContext* feature_member();

  class  Type_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Type_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_MEMBER();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_feature_memberContext* type_feature_member();

  class  Owned_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_feature_memberContext* owned_feature_member();

  class  ClassifierContext : public antlr4::ParserRuleContext {
  public:
    ClassifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_CLASSIFIER();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();
    Type_prefixContext *type_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassifierContext* classifier();

  class  Classifier_declarationContext : public antlr4::ParserRuleContext {
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
   
  };

  Classifier_declarationContext* classifier_declaration();

  class  Superclassing_partContext : public antlr4::ParserRuleContext {
  public:
    Superclassing_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SPECIALIZES();
    std::vector<Owned_subclassificationContext *> owned_subclassification();
    Owned_subclassificationContext* owned_subclassification(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Superclassing_partContext* superclassing_part();

  class  SubclassificationContext : public antlr4::ParserRuleContext {
  public:
    SubclassificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_SUBCLASSIFIER();
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    antlr4::tree::TerminalNode *SPECIALIZES();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *KEYWORD_SPECILIZATION();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SubclassificationContext* subclassification();

  class  Owned_subclassificationContext : public antlr4::ParserRuleContext {
  public:
    Owned_subclassificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_subclassificationContext* owned_subclassification();

  class  FeatureContext : public antlr4::ParserRuleContext {
  public:
    FeatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FEATURE();
    Prefix_metadata_memberContext *prefix_metadata_member();
    Feature_declarationContext *feature_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FeatureContext* feature();

  class  Feature_prefixContext : public antlr4::ParserRuleContext {
  public:
    Feature_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_directionContext *feature_direction();
    antlr4::tree::TerminalNode *KEYWORD_ABSTRACT();
    antlr4::tree::TerminalNode *KEYWORD_READONLY();
    antlr4::tree::TerminalNode *KEYWORD_DERIVED();
    antlr4::tree::TerminalNode *KEYWORD_END();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_COMPOSITE();
    antlr4::tree::TerminalNode *KEYWORD_PORTION();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_prefixContext* feature_prefix();

  class  Feature_directionContext : public antlr4::ParserRuleContext {
  public:
    Feature_directionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_IN();
    antlr4::tree::TerminalNode *KEYWORD_OUT();
    antlr4::tree::TerminalNode *KEYWORD_INOUT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_directionContext* feature_direction();

  class  Feature_declarationContext : public antlr4::ParserRuleContext {
  public:
    Feature_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_identificationContext *feature_identification();
    Feature_specialization_partContext *feature_specialization_part();
    Conjugation_partContext *conjugation_part();
    antlr4::tree::TerminalNode *KEYWORD_ALL();
    std::vector<Feature_relationship_partContext *> feature_relationship_part();
    Feature_relationship_partContext* feature_relationship_part(size_t i);
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_declarationContext* feature_declaration();

  class  Feature_identificationContext : public antlr4::ParserRuleContext {
  public:
    Feature_identificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SMALLER();
    std::vector<antlr4::tree::TerminalNode *> NAME();
    antlr4::tree::TerminalNode* NAME(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_GREATER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_identificationContext* feature_identification();

  class  Feature_relationship_partContext : public antlr4::ParserRuleContext {
  public:
    Feature_relationship_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_relationship_partContext *type_relationship_part();
    Chaining_partContext *chaining_part();
    Inverting_partContext *inverting_part();
    Type_featuring_partContext *type_featuring_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_relationship_partContext* feature_relationship_part();

  class  Chaining_partContext : public antlr4::ParserRuleContext {
  public:
    Chaining_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_CHAINS();
    Owned_feature_chainingContext *owned_feature_chaining();
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Chaining_partContext* chaining_part();

  class  Inverting_partContext : public antlr4::ParserRuleContext {
  public:
    Inverting_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_INVERSE();
    antlr4::tree::TerminalNode *KEYWORD_OF();
    Owned_feature_invertingContext *owned_feature_inverting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Inverting_partContext* inverting_part();

  class  Type_featuring_partContext : public antlr4::ParserRuleContext {
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
   
  };

  Type_featuring_partContext* type_featuring_part();

  class  Feature_specialization_partContext : public antlr4::ParserRuleContext {
  public:
    Feature_specialization_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Feature_specilizationContext *> feature_specilization();
    Feature_specilizationContext* feature_specilization(size_t i);
    Multiplicity_partContext *multiplicity_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_specialization_partContext* feature_specialization_part();

  class  Multiplicity_partContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_boundsContext *multiplicity_bounds();
    antlr4::tree::TerminalNode *KEYWORD_ORDERED();
    antlr4::tree::TerminalNode *KEYWORD_NONUNIQUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Multiplicity_partContext* multiplicity_part();

  class  Feature_specilizationContext : public antlr4::ParserRuleContext {
  public:
    Feature_specilizationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypingsContext *typings();
    SubsettingsContext *subsettings();
    ReferencesContext *references();
    RedefinitionsContext *redefinitions();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_specilizationContext* feature_specilization();

  class  TypingsContext : public antlr4::ParserRuleContext {
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
   
  };

  TypingsContext* typings();

  class  Typed_byContext : public antlr4::ParserRuleContext {
  public:
    Typed_byContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPED_BY();
    Owned_feature_typingContext *owned_feature_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Typed_byContext* typed_by();

  class  SubsettingsContext : public antlr4::ParserRuleContext {
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
   
  };

  SubsettingsContext* subsettings();

  class  SubsetsContext : public antlr4::ParserRuleContext {
  public:
    SubsetsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUBSETS();
    Owned_subsettingContext *owned_subsetting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SubsetsContext* subsets();

  class  ReferencesContext : public antlr4::ParserRuleContext {
  public:
    ReferencesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REFERENCES();
    Owned_reference_subsettingContext *owned_reference_subsetting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReferencesContext* references();

  class  RedefinitionsContext : public antlr4::ParserRuleContext {
  public:
    RedefinitionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RedefinesContext *redefines();
    antlr4::tree::TerminalNode *SYMBOL_COMMA();
    Owned_redefinitionContext *owned_redefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RedefinitionsContext* redefinitions();

  class  RedefinesContext : public antlr4::ParserRuleContext {
  public:
    RedefinesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REDEFINES();
    Owned_redefinitionContext *owned_redefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RedefinesContext* redefines();

  class  Feature_typingContext : public antlr4::ParserRuleContext {
  public:
    Feature_typingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    antlr4::tree::TerminalNode *TYPED_BY();
    General_typeContext *general_type();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *KEYWORD_SPECILIZATION();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_TYPING();
    Multiplicity_partContext *multiplicity_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_typingContext* feature_typing();

  class  Owned_feature_typingContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_typingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_feature_typingContext* owned_feature_typing();

  class  SubsettingContext : public antlr4::ParserRuleContext {
  public:
    SubsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Specific_typeContext *specific_type();
    antlr4::tree::TerminalNode *SUBSETS();
    General_typeContext *general_type();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *KEYWORD_SPECILIZATION();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_SUBSET();
    Multiplicity_partContext *multiplicity_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SubsettingContext* subsetting();

  class  Owned_subsettingContext : public antlr4::ParserRuleContext {
  public:
    Owned_subsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_subsettingContext* owned_subsetting();

  class  Owned_reference_subsettingContext : public antlr4::ParserRuleContext {
  public:
    Owned_reference_subsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_reference_subsettingContext* owned_reference_subsetting();

  class  RedefinitionContext : public antlr4::ParserRuleContext {
  public:
    RedefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_REDEFINITION();
    Specific_typeContext *specific_type();
    antlr4::tree::TerminalNode *REDEFINES();
    General_typeContext *general_type();
    Relationship_bodyContext *relationship_body();
    antlr4::tree::TerminalNode *KEYWORD_SPECILIZATION();
    IdentificationContext *identification();
    Multiplicity_partContext *multiplicity_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RedefinitionContext* redefinition();

  class  Owned_redefinitionContext : public antlr4::ParserRuleContext {
  public:
    Owned_redefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    General_typeContext *general_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_redefinitionContext* owned_redefinition();

  class  Owned_feature_chainContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_feature_chainContext* owned_feature_chain();

  class  Feature_chainContext : public antlr4::ParserRuleContext {
  public:
    Feature_chainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Owned_feature_chainingContext *> owned_feature_chaining();
    Owned_feature_chainingContext* owned_feature_chaining(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_chainContext* feature_chain();

  class  Owned_feature_chainingContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_chainingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_feature_chainingContext* owned_feature_chaining();

  class  Feature_invertingContext : public antlr4::ParserRuleContext {
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
   
  };

  Feature_invertingContext* feature_inverting();

  class  Owned_feature_invertingContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_invertingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_feature_invertingContext* owned_feature_inverting();

  class  Type_featuringContext : public antlr4::ParserRuleContext {
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
   
  };

  Type_featuringContext* type_featuring();

  class  Owned_type_featuringContext : public antlr4::ParserRuleContext {
  public:
    Owned_type_featuringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_type_featuringContext* owned_type_featuring();

  class  Data_typeContext : public antlr4::ParserRuleContext {
  public:
    Data_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_DATATYPE();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Data_typeContext* data_type();

  class  ClassContext : public antlr4::ParserRuleContext {
  public:
    ClassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CLASS();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassContext* class_();

  class  StructureContext : public antlr4::ParserRuleContext {
  public:
    StructureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_STRUCT();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StructureContext* structure();

  class  AssociationContext : public antlr4::ParserRuleContext {
  public:
    AssociationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ASSOC();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssociationContext* association();

  class  Association_structureContext : public antlr4::ParserRuleContext {
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
   
  };

  Association_structureContext* association_structure();

  class  ConnectorContext : public antlr4::ParserRuleContext {
  public:
    ConnectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_CONNECTOR();
    Connector_declarationContext *connector_declaration();
    Type_bodyContext *type_body();
    Type_prefixContext *type_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConnectorContext* connector();

  class  Connector_declarationContext : public antlr4::ParserRuleContext {
  public:
    Connector_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_declarationContext *feature_declaration();
    Binary_connector_declarationContext *binary_connector_declaration();
    Nary_connector_declarationContext *nary_connector_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Connector_declarationContext* connector_declaration();

  class  Binary_connector_declarationContext : public antlr4::ParserRuleContext {
  public:
    Binary_connector_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();
    antlr4::tree::TerminalNode *KEYWORD_ALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Binary_connector_declarationContext* binary_connector_declaration();

  class  Nary_connector_declarationContext : public antlr4::ParserRuleContext {
  public:
    Nary_connector_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Nary_connector_declarationContext* nary_connector_declaration();

  class  Connector_end_memberContext : public antlr4::ParserRuleContext {
  public:
    Connector_end_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Connector_endContext *connector_end();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Connector_end_memberContext* connector_end_member();

  class  Connector_endContext : public antlr4::ParserRuleContext {
  public:
    Connector_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    antlr4::tree::TerminalNode *NAME();
    antlr4::tree::TerminalNode *REFERENCES();
    Multiplicity_boundsContext *multiplicity_bounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Connector_endContext* connector_end();

  class  Binding_connectorContext : public antlr4::ParserRuleContext {
  public:
    Binding_connectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_BINDING();
    Binding_connector_declarationContext *binding_connector_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Binding_connectorContext* binding_connector();

  class  Binding_connector_declarationContext : public antlr4::ParserRuleContext {
  public:
    Binding_connector_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_declarationContext *feature_declaration();
    antlr4::tree::TerminalNode *KEYWORD_OF();
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_EQUALS();
    antlr4::tree::TerminalNode *KEYWORD_ALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Binding_connector_declarationContext* binding_connector_declaration();

  class  SuccessionContext : public antlr4::ParserRuleContext {
  public:
    SuccessionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_SUCCSESSION();
    Succession_declarationContext *succession_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SuccessionContext* succession();

  class  Succession_declarationContext : public antlr4::ParserRuleContext {
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
   
  };

  Succession_declarationContext* succession_declaration();

  class  BehaviorContext : public antlr4::ParserRuleContext {
  public:
    BehaviorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_BEHAVIOR();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BehaviorContext* behavior();

  class  StepContext : public antlr4::ParserRuleContext {
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
   
  };

  StepContext* step();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FUNCTION();
    Classifier_declarationContext *classifier_declaration();
    Function_bodyContext *function_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionContext* function();

  class  Function_bodyContext : public antlr4::ParserRuleContext {
  public:
    Function_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Function_body_partContext *function_body_part();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Function_bodyContext* function_body();

  class  Function_body_partContext : public antlr4::ParserRuleContext {
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
   
  };

  Function_body_partContext* function_body_part();

  class  Return_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Return_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_RETURN();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Return_feature_memberContext* return_feature_member();

  class  Result_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Result_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Owned_expressionContext *owned_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Result_expression_memberContext* result_expression_member();

  class  ExpressionContext : public antlr4::ParserRuleContext {
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
   
  };

  ExpressionContext* expression();

  class  PredicateContext : public antlr4::ParserRuleContext {
  public:
    PredicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_PREDICATE();
    Classifier_declarationContext *classifier_declaration();
    Function_bodyContext *function_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PredicateContext* predicate();

  class  Boolean_expressionContext : public antlr4::ParserRuleContext {
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
   
  };

  Boolean_expressionContext* boolean_expression();

  class  InvariantContext : public antlr4::ParserRuleContext {
  public:
    InvariantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INV();
    Feature_declarationContext *feature_declaration();
    Function_bodyContext *function_body();
    Value_partContext *value_part();
    antlr4::tree::TerminalNode *KEYWORD_TRUE();
    antlr4::tree::TerminalNode *KEYWORD_FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InvariantContext* invariant();

  class  Owned_expression_reference_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_expression_reference_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expression_referenceContext *owned_expression_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_expression_reference_memberContext* owned_expression_reference_member();

  class  Owned_expression_referenceContext : public antlr4::ParserRuleContext {
  public:
    Owned_expression_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expression_memberContext *owned_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_expression_referenceContext* owned_expression_reference();

  class  Owned_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expressionsContext *owned_expressions();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_expression_memberContext* owned_expression_member();

  class  Owned_expressionsContext : public antlr4::ParserRuleContext {
  public:
    Owned_expressionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Owned_expressionContext *> owned_expression();
    Owned_expressionContext* owned_expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_expressionsContext* owned_expressions();

  class  Owned_expressionContext : public antlr4::ParserRuleContext {
  public:
    Owned_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Conditional_expressionContext *conditional_expression();
    Conditional_binary_operator_expressionContext *conditional_binary_operator_expression();
    Binary_operator_expressionContext *binary_operator_expression();
    Unary_operator_expressionContext *unary_operator_expression();
    Classification_expressionContext *classification_expression();
    Metaclassification_expressionContext *metaclassification_expression();
    Extend_expressionContext *extend_expression();
    Primary_expressionContext *primary_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_expressionContext* owned_expression();

  class  Conditional_expressionContext : public antlr4::ParserRuleContext {
  public:
    Conditional_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_IF();
    antlr4::tree::TerminalNode *SYMBOL_QUESTION();
    std::vector<Argument_expression_memberContext *> argument_expression_member();
    Argument_expression_memberContext* argument_expression_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_ELSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Conditional_expressionContext* conditional_expression();

  class  Conditional_binary_operator_expressionContext : public antlr4::ParserRuleContext {
  public:
    Conditional_binary_operator_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Conditional_binary_operatorContext *conditional_binary_operator();
    Argument_expression_memberContext *argument_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Conditional_binary_operator_expressionContext* conditional_binary_operator_expression();

  class  Conditional_binary_operatorContext : public antlr4::ParserRuleContext {
  public:
    Conditional_binary_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DQUESTION();
    antlr4::tree::TerminalNode *KEYWORD_OR();
    antlr4::tree::TerminalNode *KEYWORD_AND();
    antlr4::tree::TerminalNode *KEYWORD_IMPLIES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Conditional_binary_operatorContext* conditional_binary_operator();

  class  Binary_operator_expressionContext : public antlr4::ParserRuleContext {
  public:
    Binary_operator_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Binary_operatorContext *binary_operator();
    Owned_expressionsContext *owned_expressions();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Binary_operator_expressionContext* binary_operator_expression();

  class  Binary_operatorContext : public antlr4::ParserRuleContext {
  public:
    Binary_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_VERTICAL_LINE();
    antlr4::tree::TerminalNode *SYMBOL_AND();
    antlr4::tree::TerminalNode *KEYWORD_XOR();
    antlr4::tree::TerminalNode *SYMBOL_DDOT();
    antlr4::tree::TerminalNode *SYMBOL_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_NOT_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_IFF_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_IFF_NOT_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_GREATER();
    antlr4::tree::TerminalNode *SYMBOL_SMALLER();
    antlr4::tree::TerminalNode *SYMBOL_GREATER_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_SMALLER_EQUAL();
    antlr4::tree::TerminalNode *SYMBOL_PLUS();
    antlr4::tree::TerminalNode *SYMBOL_MINUS();
    antlr4::tree::TerminalNode *SYMBOL_STAR();
    antlr4::tree::TerminalNode *SYMBOL_SLASH();
    antlr4::tree::TerminalNode *SYMBOL_MOD();
    antlr4::tree::TerminalNode *SYMBOL_UPPER();
    antlr4::tree::TerminalNode *SYMBOL_DOUBLE_STAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Binary_operatorContext* binary_operator();

  class  Unary_operator_expressionContext : public antlr4::ParserRuleContext {
  public:
    Unary_operator_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unary_operatorContext *unary_operator();
    Owned_expressionsContext *owned_expressions();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Unary_operator_expressionContext* unary_operator_expression();

  class  Unary_operatorContext : public antlr4::ParserRuleContext {
  public:
    Unary_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_PLUS();
    antlr4::tree::TerminalNode *SYMBOL_MINUS();
    antlr4::tree::TerminalNode *SYMBOL_CONJUNGATES();
    antlr4::tree::TerminalNode *KEYWORD_NOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Unary_operatorContext* unary_operator();

  class  Classification_expressionContext : public antlr4::ParserRuleContext {
  public:
    Classification_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classification_test_operatorContext *classification_test_operator();
    Type_reference_memberContext *type_reference_member();
    Cast_operatorContext *cast_operator();
    Type_result_memberContext *type_result_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Classification_expressionContext* classification_expression();

  class  ClassificationContext : public antlr4::ParserRuleContext {
  public:
    ClassificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classification_test_operatorContext *classification_test_operator();
    Type_reference_memberContext *type_reference_member();
    Cast_operatorContext *cast_operator();
    Type_result_memberContext *type_result_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassificationContext* classification();

  class  Classification_test_operatorContext : public antlr4::ParserRuleContext {
  public:
    Classification_test_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ISTYPE();
    antlr4::tree::TerminalNode *KEYWORD_HASTYPE();
    antlr4::tree::TerminalNode *SYMBOL_AT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Classification_test_operatorContext* classification_test_operator();

  class  Cast_operatorContext : public antlr4::ParserRuleContext {
  public:
    Cast_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_AS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Cast_operatorContext* cast_operator();

  class  Metaclassification_expressionContext : public antlr4::ParserRuleContext {
  public:
    Metaclassification_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_argument_memberContext *metadata_argument_member();
    Metadataclassification_test_operatorContext *metadataclassification_test_operator();
    Type_reference_memberContext *type_reference_member();
    Meta_cast_operatorContext *meta_cast_operator();
    Type_result_memberContext *type_result_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metaclassification_expressionContext* metaclassification_expression();

  class  Argument_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Argument_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_expressionContext *argument_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Argument_expression_memberContext* argument_expression_member();

  class  Argument_expressionContext : public antlr4::ParserRuleContext {
  public:
    Argument_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_expression_valueContext *argument_expression_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Argument_expressionContext* argument_expression();

  class  Argument_expression_valueContext : public antlr4::ParserRuleContext {
  public:
    Argument_expression_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expression_referenceContext *owned_expression_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Argument_expression_valueContext* argument_expression_value();

  class  Metadata_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Metadata_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_argumentContext *metadata_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadata_argument_memberContext* metadata_argument_member();

  class  Metadata_argumentContext : public antlr4::ParserRuleContext {
  public:
    Metadata_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_valueContext *metadata_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadata_argumentContext* metadata_argument();

  class  Metadata_valueContext : public antlr4::ParserRuleContext {
  public:
    Metadata_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_referenceContext *metadata_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadata_valueContext* metadata_value();

  class  Metadata_referenceContext : public antlr4::ParserRuleContext {
  public:
    Metadata_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadata_referenceContext* metadata_reference();

  class  Metadataclassification_test_operatorContext : public antlr4::ParserRuleContext {
  public:
    Metadataclassification_test_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadataclassification_test_operatorContext* metadataclassification_test_operator();

  class  Meta_cast_operatorContext : public antlr4::ParserRuleContext {
  public:
    Meta_cast_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Meta_cast_operatorContext* meta_cast_operator();

  class  Extend_expressionContext : public antlr4::ParserRuleContext {
  public:
    Extend_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ALL();
    Type_reference_memberContext *type_reference_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Extend_expressionContext* extend_expression();

  class  Type_reference_memberContext : public antlr4::ParserRuleContext {
  public:
    Type_reference_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_referenceContext *type_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_reference_memberContext* type_reference_member();

  class  Type_result_memberContext : public antlr4::ParserRuleContext {
  public:
    Type_result_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_referenceContext *type_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_result_memberContext* type_result_member();

  class  Type_referenceContext : public antlr4::ParserRuleContext {
  public:
    Type_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reference_typingContext *reference_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Type_referenceContext* type_reference();

  class  Reference_typingContext : public antlr4::ParserRuleContext {
  public:
    Reference_typingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Reference_typingContext* reference_typing();

  class  Primary_expressionsContext : public antlr4::ParserRuleContext {
  public:
    Primary_expressionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Primary_expressionContext *> primary_expression();
    Primary_expressionContext* primary_expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Primary_expressionsContext* primary_expressions();

  class  Primary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Primary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_chain_expressionContext *feature_chain_expression();
    Non_feature_chain_primary_expressionContext *non_feature_chain_primary_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Primary_expressionContext* primary_expression();

  class  Non_feature_chain_primary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Non_feature_chain_primary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Bracket_expressionContext *bracket_expression();
    Index_expressionContext *index_expression();
    Sequence_expressionContext *sequence_expression();
    Select_expressionContext *select_expression();
    Collect_expressionContext *collect_expression();
    Function_operation_expressionContext *function_operation_expression();
    Base_expressionContext *base_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Non_feature_chain_primary_expressionContext* non_feature_chain_primary_expression();

  class  Non_feature_chain_primary_argument_valueContext : public antlr4::ParserRuleContext {
  public:
    Non_feature_chain_primary_argument_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_chain_primary_expressionContext *non_feature_chain_primary_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Non_feature_chain_primary_argument_valueContext* non_feature_chain_primary_argument_value();

  class  Bracket_expressionContext : public antlr4::ParserRuleContext {
  public:
    Bracket_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_OPEN();
    Sequence_expression_list_memberContext *sequence_expression_list_member();
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Bracket_expressionContext* bracket_expression();

  class  Index_expressionContext : public antlr4::ParserRuleContext {
  public:
    Index_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_HASHTAG();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    Sequence_expression_list_memberContext *sequence_expression_list_member();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Index_expressionContext* index_expression();

  class  Sequence_expressionContext : public antlr4::ParserRuleContext {
  public:
    Sequence_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    Sequence_expression_listContext *sequence_expression_list();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Sequence_expressionContext* sequence_expression();

  class  Sequence_expression_listContext : public antlr4::ParserRuleContext {
  public:
    Sequence_expression_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expressionsContext *owned_expressions();
    antlr4::tree::TerminalNode *SYMBOL_COMMA();
    Sequence_operator_expressionContext *sequence_operator_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Sequence_expression_listContext* sequence_expression_list();

  class  Sequence_operator_expressionContext : public antlr4::ParserRuleContext {
  public:
    Sequence_operator_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expression_memberContext *owned_expression_member();
    antlr4::tree::TerminalNode *SYMBOL_COMMA();
    Sequence_expression_list_memberContext *sequence_expression_list_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Sequence_operator_expressionContext* sequence_operator_expression();

  class  Sequence_expression_list_memberContext : public antlr4::ParserRuleContext {
  public:
    Sequence_expression_list_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Sequence_expression_listContext *sequence_expression_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Sequence_expression_list_memberContext* sequence_expression_list_member();

  class  Feature_chain_expressionContext : public antlr4::ParserRuleContext {
  public:
    Feature_chain_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    Feature_chain_memberContext *feature_chain_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_chain_expressionContext* feature_chain_expression();

  class  Collect_expressionContext : public antlr4::ParserRuleContext {
  public:
    Collect_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    Body_expression_memberContext *body_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Collect_expressionContext* collect_expression();

  class  Select_expressionContext : public antlr4::ParserRuleContext {
  public:
    Select_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT_QUESTION();
    Body_expression_memberContext *body_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Select_expressionContext* select_expression();

  class  Function_operation_expressionContext : public antlr4::ParserRuleContext {
  public:
    Function_operation_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ARROOW();
    Reference_typingContext *reference_typing();
    Body_argument_memberContext *body_argument_member();
    Function_reference_argument_memberContext *function_reference_argument_member();
    Argument_expressionContext *argument_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Function_operation_expressionContext* function_operation_expression();

  class  Body_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Body_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_argumentContext *body_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Body_argument_memberContext* body_argument_member();

  class  Body_argumentContext : public antlr4::ParserRuleContext {
  public:
    Body_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_argument_valueContext *body_argument_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Body_argumentContext* body_argument();

  class  Body_argument_valueContext : public antlr4::ParserRuleContext {
  public:
    Body_argument_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_expressionContext *body_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Body_argument_valueContext* body_argument_value();

  class  Body_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Body_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_expressionContext *body_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Body_expression_memberContext* body_expression_member();

  class  Function_reference_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_reference_argumentContext *function_reference_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Function_reference_argument_memberContext* function_reference_argument_member();

  class  Function_reference_argumentContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_reference_memberContext *function_reference_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Function_reference_argumentContext* function_reference_argument();

  class  Function_reference_arugment_valueContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_arugment_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_reference_expressionContext *function_reference_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Function_reference_arugment_valueContext* function_reference_arugment_value();

  class  Function_reference_expressionContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reference_typingContext *reference_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Function_reference_expressionContext* function_reference_expression();

  class  Function_reference_memberContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_referenceContext *function_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Function_reference_memberContext* function_reference_member();

  class  Function_referenceContext : public antlr4::ParserRuleContext {
  public:
    Function_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reference_typingContext *reference_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Function_referenceContext* function_reference();

  class  Feature_chain_memberContext : public antlr4::ParserRuleContext {
  public:
    Feature_chain_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_reference_memberContext *feature_reference_member();
    Owned_feature_chain_memberContext *owned_feature_chain_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_chain_memberContext* feature_chain_member();

  class  Owned_feature_chain_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_chain_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_chainContext *feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_feature_chain_memberContext* owned_feature_chain_member();

  class  Base_expressionContext : public antlr4::ParserRuleContext {
  public:
    Base_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Null_expressionContext *null_expression();
    Literal_expressionContext *literal_expression();
    Feature_reference_expressionContext *feature_reference_expression();
    Metadata_access_expressionContext *metadata_access_expression();
    Invocation_expressionContext *invocation_expression();
    Body_expressionContext *body_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Base_expressionContext* base_expression();

  class  Null_expressionContext : public antlr4::ParserRuleContext {
  public:
    Null_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_NULL();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Null_expressionContext* null_expression();

  class  Feature_reference_expressionContext : public antlr4::ParserRuleContext {
  public:
    Feature_reference_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_reference_memberContext *feature_reference_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_reference_expressionContext* feature_reference_expression();

  class  Feature_reference_memberContext : public antlr4::ParserRuleContext {
  public:
    Feature_reference_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_referenceContext *feature_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_reference_memberContext* feature_reference_member();

  class  Feature_referenceContext : public antlr4::ParserRuleContext {
  public:
    Feature_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_referenceContext* feature_reference();

  class  Metadata_access_expressionContext : public antlr4::ParserRuleContext {
  public:
    Metadata_access_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    antlr4::tree::TerminalNode *KEYWORD_METADATA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadata_access_expressionContext* metadata_access_expression();

  class  Invocation_expressionContext : public antlr4::ParserRuleContext {
  public:
    Invocation_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Internal_invocation_expressionContext *internal_invocation_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Invocation_expressionContext* invocation_expression();

  class  Internal_invocation_expressionContext : public antlr4::ParserRuleContext {
  public:
    Internal_invocation_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_listContext *argument_list();
    Owned_feature_typingContext *owned_feature_typing();
    Named_argument_listContext *named_argument_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Internal_invocation_expressionContext* internal_invocation_expression();

  class  Argument_listContext : public antlr4::ParserRuleContext {
  public:
    Argument_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();
    Owned_expressionsContext *owned_expressions();
    Positional_argument_listContext *positional_argument_list();
    Named_argument_listContext *named_argument_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Argument_listContext* argument_list();

  class  Positional_argument_listContext : public antlr4::ParserRuleContext {
  public:
    Positional_argument_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);
    std::vector<Owned_expressionsContext *> owned_expressions();
    Owned_expressionsContext* owned_expressions(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Positional_argument_listContext* positional_argument_list();

  class  Named_argument_listContext : public antlr4::ParserRuleContext {
  public:
    Named_argument_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Named_argument_memberContext *> named_argument_member();
    Named_argument_memberContext* named_argument_member(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Named_argument_listContext* named_argument_list();

  class  Named_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Named_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Named_argumentContext *named_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Named_argument_memberContext* named_argument_member();

  class  Named_argumentContext : public antlr4::ParserRuleContext {
  public:
    Named_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Paramenter_redefinitionContext *paramenter_redefinition();
    antlr4::tree::TerminalNode *SYMBOL_EQUALS();
    Owned_expressionsContext *owned_expressions();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Named_argumentContext* named_argument();

  class  Paramenter_redefinitionContext : public antlr4::ParserRuleContext {
  public:
    Paramenter_redefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Paramenter_redefinitionContext* paramenter_redefinition();

  class  Body_expressionContext : public antlr4::ParserRuleContext {
  public:
    Body_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expression_body_memberContext *expression_body_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Body_expressionContext* body_expression();

  class  Expression_body_memberContext : public antlr4::ParserRuleContext {
  public:
    Expression_body_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expression_bodyContext *expression_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expression_body_memberContext* expression_body_member();

  class  Expression_bodyContext : public antlr4::ParserRuleContext {
  public:
    Expression_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    Function_body_partContext *function_body_part();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expression_bodyContext* expression_body();

  class  Literal_expressionContext : public antlr4::ParserRuleContext {
  public:
    Literal_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Literal_booleanContext *literal_boolean();
    Literal_stringContext *literal_string();
    Literal_integerContext *literal_integer();
    Literal_realContext *literal_real();
    Literal_infinityContext *literal_infinity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Literal_expressionContext* literal_expression();

  class  Literal_booleanContext : public antlr4::ParserRuleContext {
  public:
    Literal_booleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Boolean_valueContext *boolean_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Literal_booleanContext* literal_boolean();

  class  Boolean_valueContext : public antlr4::ParserRuleContext {
  public:
    Boolean_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_TRUE();
    antlr4::tree::TerminalNode *KEYWORD_FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Boolean_valueContext* boolean_value();

  class  Literal_stringContext : public antlr4::ParserRuleContext {
  public:
    Literal_stringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Literal_stringContext* literal_string();

  class  Literal_integerContext : public antlr4::ParserRuleContext {
  public:
    Literal_integerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DECIMAL_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Literal_integerContext* literal_integer();

  class  Literal_realContext : public antlr4::ParserRuleContext {
  public:
    Literal_realContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Real_valueContext *real_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Literal_realContext* literal_real();

  class  Real_valueContext : public antlr4::ParserRuleContext {
  public:
    Real_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    std::vector<antlr4::tree::TerminalNode *> DECIMAL_VALUE();
    antlr4::tree::TerminalNode* DECIMAL_VALUE(size_t i);
    antlr4::tree::TerminalNode *EXPONENTIAL_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Real_valueContext* real_value();

  class  Literal_infinityContext : public antlr4::ParserRuleContext {
  public:
    Literal_infinityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Literal_infinityContext* literal_infinity();

  class  InteractionContext : public antlr4::ParserRuleContext {
  public:
    InteractionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_prefixContext *type_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INTERACTION();
    Classifier_declarationContext *classifier_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InteractionContext* interaction();

  class  Item_flowContext : public antlr4::ParserRuleContext {
  public:
    Item_flowContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FLOW();
    Item_flow_declarationContext *item_flow_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_flowContext* item_flow();

  class  Succession_item_flowContext : public antlr4::ParserRuleContext {
  public:
    Succession_item_flowContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_prefixContext *feature_prefix();
    antlr4::tree::TerminalNode *KEYWORD_SUCCSESSION();
    antlr4::tree::TerminalNode *KEYWORD_FLOW();
    Item_flow_declarationContext *item_flow_declaration();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Succession_item_flowContext* succession_item_flow();

  class  Item_flow_declarationContext : public antlr4::ParserRuleContext {
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
   
  };

  Item_flow_declarationContext* item_flow_declaration();

  class  Item_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Item_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_featureContext *item_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_feature_memberContext* item_feature_member();

  class  Item_featureContext : public antlr4::ParserRuleContext {
  public:
    Item_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentificationContext *identification();
    Item_feature_specilization_partContext *item_feature_specilization_part();
    Value_partContext *value_part();
    Owned_feature_typingContext *owned_feature_typing();
    Multiplicity_boundsContext *multiplicity_bounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_featureContext* item_feature();

  class  Item_feature_specilization_partContext : public antlr4::ParserRuleContext {
  public:
    Item_feature_specilization_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_partContext *multiplicity_part();
    std::vector<Feature_specilizationContext *> feature_specilization();
    Feature_specilizationContext* feature_specilization(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_feature_specilization_partContext* item_feature_specilization_part();

  class  Item_flow_end_memberContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_end_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_flow_endContext *item_flow_end();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_flow_end_memberContext* item_flow_end_member();

  class  Item_flow_endContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_flow_feature_memberContext *item_flow_feature_member();
    Owned_reference_subsettingContext *owned_reference_subsetting();
    antlr4::tree::TerminalNode *SYMBOL_DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_flow_endContext* item_flow_end();

  class  Item_flow_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_flow_featureContext *item_flow_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_flow_feature_memberContext* item_flow_feature_member();

  class  Item_flow_featureContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Item_flow_redefinitionContext *item_flow_redefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_flow_featureContext* item_flow_feature();

  class  Item_flow_redefinitionContext : public antlr4::ParserRuleContext {
  public:
    Item_flow_redefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Item_flow_redefinitionContext* item_flow_redefinition();

  class  Value_partContext : public antlr4::ParserRuleContext {
  public:
    Value_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_valueContext *feature_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Value_partContext* value_part();

  class  Feature_valueContext : public antlr4::ParserRuleContext {
  public:
    Feature_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_EQUALS();
    antlr4::tree::TerminalNode *SYMBOL_DEF_ASSIGN();
    antlr4::tree::TerminalNode *KEYWORD_DEFAULT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Feature_valueContext* feature_value();

  class  MultiplicityContext : public antlr4::ParserRuleContext {
  public:
    MultiplicityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_subsetContext *multiplicity_subset();
    Multiplicity_rangeContext *multiplicity_range();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MultiplicityContext* multiplicity();

  class  Multiplicity_subsetContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_subsetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_MULTIPLICITY();
    IdentificationContext *identification();
    SubsetsContext *subsets();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Multiplicity_subsetContext* multiplicity_subset();

  class  Multiplicity_rangeContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_rangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_MULTIPLICITY();
    IdentificationContext *identification();
    Multiplicity_boundsContext *multiplicity_bounds();
    Type_bodyContext *type_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Multiplicity_rangeContext* multiplicity_range();

  class  Owned_multiplicityContext : public antlr4::ParserRuleContext {
  public:
    Owned_multiplicityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_boundsContext *multiplicity_bounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_multiplicityContext* owned_multiplicity();

  class  Owned_multiplicity_rangeContext : public antlr4::ParserRuleContext {
  public:
    Owned_multiplicity_rangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_boundsContext *multiplicity_bounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Owned_multiplicity_rangeContext* owned_multiplicity_range();

  class  Multiplicity_boundsContext : public antlr4::ParserRuleContext {
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
   
  };

  Multiplicity_boundsContext* multiplicity_bounds();

  class  Multiplicity_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Internal_multiplicity_expression_memberContext *internal_multiplicity_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Multiplicity_expression_memberContext* multiplicity_expression_member();

  class  Internal_multiplicity_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Internal_multiplicity_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Literal_expressionContext *literal_expression();
    Feature_reference_expressionContext *feature_reference_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Internal_multiplicity_expression_memberContext* internal_multiplicity_expression_member();

  class  MetaclassContext : public antlr4::ParserRuleContext {
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
    antlr4::tree::TerminalNode *SPECIALIZES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MetaclassContext* metaclass();

  class  Prefix_metadata_annotationContext : public antlr4::ParserRuleContext {
  public:
    Prefix_metadata_annotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_HASHTAG();
    Prefix_metadata_featureContext *prefix_metadata_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prefix_metadata_annotationContext* prefix_metadata_annotation();

  class  Prefix_metadata_memberContext : public antlr4::ParserRuleContext {
  public:
    Prefix_metadata_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_HASHTAG();
    Prefix_metadata_featureContext *prefix_metadata_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prefix_metadata_memberContext* prefix_metadata_member();

  class  Prefix_metadata_featureContext : public antlr4::ParserRuleContext {
  public:
    Prefix_metadata_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_feature_typingContext *owned_feature_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Prefix_metadata_featureContext* prefix_metadata_feature();

  class  Metadata_featureContext : public antlr4::ParserRuleContext {
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
   
  };

  Metadata_featureContext* metadata_feature();

  class  Metadata_feature_declarationContext : public antlr4::ParserRuleContext {
  public:
    Metadata_feature_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_feature_typingContext *owned_feature_typing();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *SYMBOL_TYPED_BY();
    antlr4::tree::TerminalNode *KEYWORD_TYPED();
    antlr4::tree::TerminalNode *KEYWORD_BY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadata_feature_declarationContext* metadata_feature_declaration();

  class  Metadata_bodyContext : public antlr4::ParserRuleContext {
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
   
  };

  Metadata_bodyContext* metadata_body();

  class  Metadata_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Metadata_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_memberContext *non_feature_member();
    Metadata_body_feature_memberContext *metadata_body_feature_member();
    Alias_memberContext *alias_member();
    Import_declarationContext *import_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadata_body_elementContext* metadata_body_element();

  class  Metadata_body_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Metadata_body_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_body_featureContext *metadata_body_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadata_body_feature_memberContext* metadata_body_feature_member();

  class  Metadata_body_featureContext : public antlr4::ParserRuleContext {
  public:
    Metadata_body_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_redefinitionContext *owned_redefinition();
    Metadata_bodyContext *metadata_body();
    antlr4::tree::TerminalNode *KEYWORD_FEATURE();
    Feature_specialization_partContext *feature_specialization_part();
    Value_partContext *value_part();
    antlr4::tree::TerminalNode *SYMBOL_REDEFINES();
    antlr4::tree::TerminalNode *KEYWORD_REDEFINES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Metadata_body_featureContext* metadata_body_feature();

  class  PackageContext : public antlr4::ParserRuleContext {
  public:
    PackageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Package_declarationContext *package_declaration();
    Package_bodyContext *package_body();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PackageContext* package();

  class  Library_packageContext : public antlr4::ParserRuleContext {
  public:
    Library_packageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Package_declarationContext *package_declaration();
    Package_bodyContext *package_body();
    std::vector<Prefix_metadata_memberContext *> prefix_metadata_member();
    Prefix_metadata_memberContext* prefix_metadata_member(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Library_packageContext* library_package();

  class  Package_declarationContext : public antlr4::ParserRuleContext {
  public:
    Package_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_PACKAGE();
    IdentificationContext *identification();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Package_declarationContext* package_declaration();

  class  Package_bodyContext : public antlr4::ParserRuleContext {
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
   
  };

  Package_bodyContext* package_body();

  class  Element_filter_memberContext : public antlr4::ParserRuleContext {
  public:
    Element_filter_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FILTER();
    Owned_expressionContext *owned_expression();
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Element_filter_memberContext* element_filter_member();

  class  Meta_assignmentContext : public antlr4::ParserRuleContext {
  public:
    Meta_assignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_ASSIGN();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Meta_assignmentContext* meta_assignment();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

