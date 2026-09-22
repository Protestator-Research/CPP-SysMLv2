
    #include <sysmlv2/sysmlv2file_global.h>


// Generated from ./KerML.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include <kerml/parser/KerMLVisitor.h>


    /**
 * This class provides an empty implementation of KerMLVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class SYSMLV2FILE_EXPORT KerMLBaseVisitor : public KerMLVisitor {
public:

  virtual std::any visitStart(KerMLParser::StartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStartRule(KerMLParser::StartRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElements(KerMLParser::ElementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentification(KerMLParser::IdentificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationship_body(KerMLParser::Relationship_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationship_owned_elements(KerMLParser::Relationship_owned_elementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_related_element(KerMLParser::Owned_related_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDependency(KerMLParser::DependencyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotation(KerMLParser::AnnotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_annotation(KerMLParser::Owned_annotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotating_element(KerMLParser::Annotating_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComment(KerMLParser::CommentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDocumentation(KerMLParser::DocumentationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTextual_representation(KerMLParser::Textual_representationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRoot_namespace(KerMLParser::Root_namespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace(KerMLParser::NamespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_declaration(KerMLParser::Namespace_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_body(KerMLParser::Namespace_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_body_element(KerMLParser::Namespace_body_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMember_prefix(KerMLParser::Member_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVisibility_indicator(KerMLParser::Visibility_indicatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_member(KerMLParser::Namespace_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_member(KerMLParser::Non_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAlias_member(KerMLParser::Alias_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualified_name(KerMLParser::Qualified_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespace_import(KerMLParser::Namespace_importContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImport_declaration(KerMLParser::Import_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMembership_import(KerMLParser::Membership_importContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilter_package(KerMLParser::Filter_packageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilter_package_member(KerMLParser::Filter_package_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement(KerMLParser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_element(KerMLParser::Non_feature_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_element(KerMLParser::Feature_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditional_options(KerMLParser::Additional_optionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(KerMLParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_prefix(KerMLParser::Type_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_declaration(KerMLParser::Type_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecialization_part(KerMLParser::Specialization_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConjugation_part(KerMLParser::Conjugation_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_relationship_part(KerMLParser::Type_relationship_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDisjoining_part(KerMLParser::Disjoining_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnioning_part(KerMLParser::Unioning_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntersecting_part(KerMLParser::Intersecting_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDifferencing_part(KerMLParser::Differencing_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_body(KerMLParser::Type_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_body_elements(KerMLParser::Type_body_elementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_body_element(KerMLParser::Type_body_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecialization(KerMLParser::SpecializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_specialization(KerMLParser::Owned_specializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecific_type(KerMLParser::Specific_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGeneral_type(KerMLParser::General_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConjunction(KerMLParser::ConjunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_conjugation(KerMLParser::Owned_conjugationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDisjoining(KerMLParser::DisjoiningContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_disjoining(KerMLParser::Owned_disjoiningContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnioning(KerMLParser::UnioningContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntersecting(KerMLParser::IntersectingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDifferencing(KerMLParser::DifferencingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_member(KerMLParser::Feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_feature_member(KerMLParser::Type_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_member(KerMLParser::Owned_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassifier(KerMLParser::ClassifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassifier_declaration(KerMLParser::Classifier_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuperclassing_part(KerMLParser::Superclassing_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubclassification(KerMLParser::SubclassificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_subclassification(KerMLParser::Owned_subclassificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature(KerMLParser::FeatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_prefix(KerMLParser::Feature_prefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_direction(KerMLParser::Feature_directionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_declaration(KerMLParser::Feature_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_identification(KerMLParser::Feature_identificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_relationship_part(KerMLParser::Feature_relationship_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChaining_part(KerMLParser::Chaining_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInverting_part(KerMLParser::Inverting_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_featuring_part(KerMLParser::Type_featuring_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_specialization_part(KerMLParser::Feature_specialization_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_part(KerMLParser::Multiplicity_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_specialization(KerMLParser::Feature_specializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypings(KerMLParser::TypingsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTyped_by(KerMLParser::Typed_byContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubsettings(KerMLParser::SubsettingsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubsets(KerMLParser::SubsetsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReferences(KerMLParser::ReferencesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRedefinitions(KerMLParser::RedefinitionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRedefines(KerMLParser::RedefinesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_typing(KerMLParser::Feature_typingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_typing(KerMLParser::Owned_feature_typingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubsetting(KerMLParser::SubsettingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_subsetting(KerMLParser::Owned_subsettingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRedefinition(KerMLParser::RedefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_redefinition(KerMLParser::Owned_redefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_chain(KerMLParser::Owned_feature_chainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_chain(KerMLParser::Feature_chainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_inverting(KerMLParser::Feature_invertingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_featuring(KerMLParser::Type_featuringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_type_featuring(KerMLParser::Owned_type_featuringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitData_type(KerMLParser::Data_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClass(KerMLParser::ClassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructure(KerMLParser::StructureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssociation(KerMLParser::AssociationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssociation_structure(KerMLParser::Association_structureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnector(KerMLParser::ConnectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnector_declaration(KerMLParser::Connector_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnector_end_member(KerMLParser::Connector_end_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConnector_end(KerMLParser::Connector_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinding_connector(KerMLParser::Binding_connectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuccession(KerMLParser::SuccessionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuccession_declaration(KerMLParser::Succession_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBehavior(KerMLParser::BehaviorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStep(KerMLParser::StepContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction(KerMLParser::FunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_body(KerMLParser::Function_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_body_part(KerMLParser::Function_body_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturn_feature_member(KerMLParser::Return_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitResult_expression_member(KerMLParser::Result_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(KerMLParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPredicate(KerMLParser::PredicateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolean_expression(KerMLParser::Boolean_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvariant(KerMLParser::InvariantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expression_reference_member(KerMLParser::Owned_expression_reference_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expression_member(KerMLParser::Owned_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expressions(KerMLParser::Owned_expressionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_expression(KerMLParser::Owned_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEased_owned_expression(KerMLParser::Eased_owned_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditional_expression(KerMLParser::Conditional_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditional_binary_operator_expression(KerMLParser::Conditional_binary_operator_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinary_operator_expression(KerMLParser::Binary_operator_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinary_operator(KerMLParser::Binary_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_operator_expression(KerMLParser::Unary_operator_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_operator(KerMLParser::Unary_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassification_expression(KerMLParser::Classification_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassification(KerMLParser::ClassificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassification_test_operator(KerMLParser::Classification_test_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCast_operator(KerMLParser::Cast_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetaclassification_expression(KerMLParser::Metaclassification_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_member(KerMLParser::Argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(KerMLParser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_value(KerMLParser::Argument_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_expression_member(KerMLParser::Argument_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_expression(KerMLParser::Argument_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_expression_value(KerMLParser::Argument_expression_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_argument_member(KerMLParser::Metadata_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_argument(KerMLParser::Metadata_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_value(KerMLParser::Metadata_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_reference(KerMLParser::Metadata_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadataclassification_test_operator(KerMLParser::Metadataclassification_test_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMeta_cast_operator(KerMLParser::Meta_cast_operatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExtend_expression(KerMLParser::Extend_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_reference_member(KerMLParser::Type_reference_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_result_member(KerMLParser::Type_result_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_reference(KerMLParser::Type_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReference_typing(KerMLParser::Reference_typingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_expressions(KerMLParser::Primary_expressionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_expression(KerMLParser::Primary_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_argument_value(KerMLParser::Primary_argument_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_argument(KerMLParser::Primary_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary_argument_member(KerMLParser::Primary_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_chain_primary_expression(KerMLParser::Non_feature_chain_primary_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_chain_primary_argument_value(KerMLParser::Non_feature_chain_primary_argument_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_chain_primary_argument(KerMLParser::Non_feature_chain_primary_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNon_feature_chain_primary_argument_member(KerMLParser::Non_feature_chain_primary_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBracket_expression(KerMLParser::Bracket_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndex_expression(KerMLParser::Index_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSequence_expression(KerMLParser::Sequence_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSequence_expression_list(KerMLParser::Sequence_expression_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSequence_expression_list_member(KerMLParser::Sequence_expression_list_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_chain_expression(KerMLParser::Feature_chain_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollect_expression(KerMLParser::Collect_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelect_expression(KerMLParser::Select_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_operation_expression(KerMLParser::Function_operation_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_argument_member(KerMLParser::Body_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_argument(KerMLParser::Body_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_argument_value(KerMLParser::Body_argument_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_expression_member(KerMLParser::Body_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_argument_member(KerMLParser::Function_reference_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_argument(KerMLParser::Function_reference_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_arugment_value(KerMLParser::Function_reference_arugment_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_expression(KerMLParser::Function_reference_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference_member(KerMLParser::Function_reference_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_reference(KerMLParser::Function_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_chain_member(KerMLParser::Feature_chain_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBase_expression(KerMLParser::Base_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNull_expression(KerMLParser::Null_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_reference_member(KerMLParser::Feature_reference_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_reference(KerMLParser::Feature_referenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvocation_expression(KerMLParser::Invocation_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInternal_invocation_expression(KerMLParser::Internal_invocation_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument_list(KerMLParser::Argument_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPositional_argument_list(KerMLParser::Positional_argument_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_argument_list(KerMLParser::Named_argument_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_argument_member(KerMLParser::Named_argument_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_argument(KerMLParser::Named_argumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter_redefinition(KerMLParser::Parameter_redefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBody_expression(KerMLParser::Body_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression_body_member(KerMLParser::Expression_body_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression_body(KerMLParser::Expression_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_expression(KerMLParser::Literal_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_boolean(KerMLParser::Literal_booleanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolean_value(KerMLParser::Boolean_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_string(KerMLParser::Literal_stringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_integer(KerMLParser::Literal_integerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_real(KerMLParser::Literal_realContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReal_value(KerMLParser::Real_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral_infinity(KerMLParser::Literal_infinityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInteraction(KerMLParser::InteractionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow(KerMLParser::Item_flowContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuccession_item_flow(KerMLParser::Succession_item_flowContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_declaration(KerMLParser::Item_flow_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_feature_member(KerMLParser::Item_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_feature(KerMLParser::Item_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_feature_specialization_part(KerMLParser::Item_feature_specialization_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_end(KerMLParser::Item_flow_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_feature(KerMLParser::Item_flow_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue_part(KerMLParser::Value_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_value(KerMLParser::Feature_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeature_assignment(KerMLParser::Feature_assignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity(KerMLParser::MultiplicityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_range(KerMLParser::Multiplicity_rangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_multiplicity(KerMLParser::Owned_multiplicityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicity_expression_member(KerMLParser::Multiplicity_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInternal_multiplicity_expression_member(KerMLParser::Internal_multiplicity_expression_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetaclass(KerMLParser::MetaclassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_feature(KerMLParser::Metadata_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body(KerMLParser::Metadata_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body_element(KerMLParser::Metadata_body_elementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMetadata_body_feature(KerMLParser::Metadata_body_featureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackage(KerMLParser::PackageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLibrary_package(KerMLParser::Library_packageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackage_declaration(KerMLParser::Package_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackage_body(KerMLParser::Package_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement_filter_member(KerMLParser::Element_filter_memberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMeta_assignment(KerMLParser::Meta_assignmentContext *ctx) override {
    return visitChildren(ctx);
  }


};

