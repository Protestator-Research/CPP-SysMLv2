
    #include <sysmlv2/sysmlv2file_global.h>


// Generated from ./KerML.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include <kerml/parser/KerMLParser.h>



    /**
 * This class defines an abstract visitor for a parse tree
 * produced by KerMLParser.
 */
class SYSMLV2FILE_EXPORT KerMLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by KerMLParser.
   */
    virtual std::any visitStart(KerMLParser::StartContext *context) = 0;

    virtual std::any visitStartRule(KerMLParser::StartRuleContext *context) = 0;

    virtual std::any visitElements(KerMLParser::ElementsContext *context) = 0;

    virtual std::any visitIdentification(KerMLParser::IdentificationContext *context) = 0;

    virtual std::any visitRelationship_body(KerMLParser::Relationship_bodyContext *context) = 0;

    virtual std::any visitRelationship_owned_elements(KerMLParser::Relationship_owned_elementsContext *context) = 0;

    virtual std::any visitRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *context) = 0;

    virtual std::any visitOwned_related_element(KerMLParser::Owned_related_elementContext *context) = 0;

    virtual std::any visitDependency(KerMLParser::DependencyContext *context) = 0;

    virtual std::any visitAnnotation(KerMLParser::AnnotationContext *context) = 0;

    virtual std::any visitOwned_annotation(KerMLParser::Owned_annotationContext *context) = 0;

    virtual std::any visitAnnotating_element(KerMLParser::Annotating_elementContext *context) = 0;

    virtual std::any visitComment(KerMLParser::CommentContext *context) = 0;

    virtual std::any visitDocumentation(KerMLParser::DocumentationContext *context) = 0;

    virtual std::any visitTextual_representation(KerMLParser::Textual_representationContext *context) = 0;

    virtual std::any visitRoot_namespace(KerMLParser::Root_namespaceContext *context) = 0;

    virtual std::any visitNamespace(KerMLParser::NamespaceContext *context) = 0;

    virtual std::any visitNamespace_declaration(KerMLParser::Namespace_declarationContext *context) = 0;

    virtual std::any visitNamespace_body(KerMLParser::Namespace_bodyContext *context) = 0;

    virtual std::any visitNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *context) = 0;

    virtual std::any visitNamespace_body_element(KerMLParser::Namespace_body_elementContext *context) = 0;

    virtual std::any visitMember_prefix(KerMLParser::Member_prefixContext *context) = 0;

    virtual std::any visitVisibility_indicator(KerMLParser::Visibility_indicatorContext *context) = 0;

    virtual std::any visitNamespace_member(KerMLParser::Namespace_memberContext *context) = 0;

    virtual std::any visitNon_feature_member(KerMLParser::Non_feature_memberContext *context) = 0;

    virtual std::any visitNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *context) = 0;

    virtual std::any visitAlias_member(KerMLParser::Alias_memberContext *context) = 0;

    virtual std::any visitQualified_name(KerMLParser::Qualified_nameContext *context) = 0;

    virtual std::any visitNamespace_import(KerMLParser::Namespace_importContext *context) = 0;

    virtual std::any visitImport_declaration(KerMLParser::Import_declarationContext *context) = 0;

    virtual std::any visitMembership_import(KerMLParser::Membership_importContext *context) = 0;

    virtual std::any visitFilter_package(KerMLParser::Filter_packageContext *context) = 0;

    virtual std::any visitFilter_package_member(KerMLParser::Filter_package_memberContext *context) = 0;

    virtual std::any visitElement(KerMLParser::ElementContext *context) = 0;

    virtual std::any visitNon_feature_element(KerMLParser::Non_feature_elementContext *context) = 0;

    virtual std::any visitFeature_element(KerMLParser::Feature_elementContext *context) = 0;

    virtual std::any visitAdditional_options(KerMLParser::Additional_optionsContext *context) = 0;

    virtual std::any visitType(KerMLParser::TypeContext *context) = 0;

    virtual std::any visitType_prefix(KerMLParser::Type_prefixContext *context) = 0;

    virtual std::any visitType_declaration(KerMLParser::Type_declarationContext *context) = 0;

    virtual std::any visitSpecialization_part(KerMLParser::Specialization_partContext *context) = 0;

    virtual std::any visitConjugation_part(KerMLParser::Conjugation_partContext *context) = 0;

    virtual std::any visitType_relationship_part(KerMLParser::Type_relationship_partContext *context) = 0;

    virtual std::any visitDisjoining_part(KerMLParser::Disjoining_partContext *context) = 0;

    virtual std::any visitUnioning_part(KerMLParser::Unioning_partContext *context) = 0;

    virtual std::any visitIntersecting_part(KerMLParser::Intersecting_partContext *context) = 0;

    virtual std::any visitDifferencing_part(KerMLParser::Differencing_partContext *context) = 0;

    virtual std::any visitType_body(KerMLParser::Type_bodyContext *context) = 0;

    virtual std::any visitType_body_elements(KerMLParser::Type_body_elementsContext *context) = 0;

    virtual std::any visitType_body_element(KerMLParser::Type_body_elementContext *context) = 0;

    virtual std::any visitSpecialization(KerMLParser::SpecializationContext *context) = 0;

    virtual std::any visitOwned_specialization(KerMLParser::Owned_specializationContext *context) = 0;

    virtual std::any visitSpecific_type(KerMLParser::Specific_typeContext *context) = 0;

    virtual std::any visitGeneral_type(KerMLParser::General_typeContext *context) = 0;

    virtual std::any visitConjunction(KerMLParser::ConjunctionContext *context) = 0;

    virtual std::any visitOwned_conjugation(KerMLParser::Owned_conjugationContext *context) = 0;

    virtual std::any visitDisjoining(KerMLParser::DisjoiningContext *context) = 0;

    virtual std::any visitOwned_disjoining(KerMLParser::Owned_disjoiningContext *context) = 0;

    virtual std::any visitUnioning(KerMLParser::UnioningContext *context) = 0;

    virtual std::any visitIntersecting(KerMLParser::IntersectingContext *context) = 0;

    virtual std::any visitDifferencing(KerMLParser::DifferencingContext *context) = 0;

    virtual std::any visitFeature_member(KerMLParser::Feature_memberContext *context) = 0;

    virtual std::any visitType_feature_member(KerMLParser::Type_feature_memberContext *context) = 0;

    virtual std::any visitOwned_feature_member(KerMLParser::Owned_feature_memberContext *context) = 0;

    virtual std::any visitClassifier(KerMLParser::ClassifierContext *context) = 0;

    virtual std::any visitClassifier_declaration(KerMLParser::Classifier_declarationContext *context) = 0;

    virtual std::any visitSuperclassing_part(KerMLParser::Superclassing_partContext *context) = 0;

    virtual std::any visitSubclassification(KerMLParser::SubclassificationContext *context) = 0;

    virtual std::any visitOwned_subclassification(KerMLParser::Owned_subclassificationContext *context) = 0;

    virtual std::any visitFeature(KerMLParser::FeatureContext *context) = 0;

    virtual std::any visitFeature_prefix(KerMLParser::Feature_prefixContext *context) = 0;

    virtual std::any visitFeature_direction(KerMLParser::Feature_directionContext *context) = 0;

    virtual std::any visitFeature_declaration(KerMLParser::Feature_declarationContext *context) = 0;

    virtual std::any visitFeature_identification(KerMLParser::Feature_identificationContext *context) = 0;

    virtual std::any visitFeature_relationship_part(KerMLParser::Feature_relationship_partContext *context) = 0;

    virtual std::any visitChaining_part(KerMLParser::Chaining_partContext *context) = 0;

    virtual std::any visitInverting_part(KerMLParser::Inverting_partContext *context) = 0;

    virtual std::any visitType_featuring_part(KerMLParser::Type_featuring_partContext *context) = 0;

    virtual std::any visitFeature_specialization_part(KerMLParser::Feature_specialization_partContext *context) = 0;

    virtual std::any visitMultiplicity_part(KerMLParser::Multiplicity_partContext *context) = 0;

    virtual std::any visitFeature_specialization(KerMLParser::Feature_specializationContext *context) = 0;

    virtual std::any visitTypings(KerMLParser::TypingsContext *context) = 0;

    virtual std::any visitTyped_by(KerMLParser::Typed_byContext *context) = 0;

    virtual std::any visitSubsettings(KerMLParser::SubsettingsContext *context) = 0;

    virtual std::any visitSubsets(KerMLParser::SubsetsContext *context) = 0;

    virtual std::any visitReferences(KerMLParser::ReferencesContext *context) = 0;

    virtual std::any visitRedefinitions(KerMLParser::RedefinitionsContext *context) = 0;

    virtual std::any visitRedefines(KerMLParser::RedefinesContext *context) = 0;

    virtual std::any visitFeature_typing(KerMLParser::Feature_typingContext *context) = 0;

    virtual std::any visitOwned_feature_typing(KerMLParser::Owned_feature_typingContext *context) = 0;

    virtual std::any visitSubsetting(KerMLParser::SubsettingContext *context) = 0;

    virtual std::any visitOwned_subsetting(KerMLParser::Owned_subsettingContext *context) = 0;

    virtual std::any visitOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *context) = 0;

    virtual std::any visitRedefinition(KerMLParser::RedefinitionContext *context) = 0;

    virtual std::any visitOwned_redefinition(KerMLParser::Owned_redefinitionContext *context) = 0;

    virtual std::any visitOwned_feature_chain(KerMLParser::Owned_feature_chainContext *context) = 0;

    virtual std::any visitFeature_chain(KerMLParser::Feature_chainContext *context) = 0;

    virtual std::any visitOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *context) = 0;

    virtual std::any visitFeature_inverting(KerMLParser::Feature_invertingContext *context) = 0;

    virtual std::any visitOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *context) = 0;

    virtual std::any visitType_featuring(KerMLParser::Type_featuringContext *context) = 0;

    virtual std::any visitOwned_type_featuring(KerMLParser::Owned_type_featuringContext *context) = 0;

    virtual std::any visitData_type(KerMLParser::Data_typeContext *context) = 0;

    virtual std::any visitClass(KerMLParser::ClassContext *context) = 0;

    virtual std::any visitStructure(KerMLParser::StructureContext *context) = 0;

    virtual std::any visitAssociation(KerMLParser::AssociationContext *context) = 0;

    virtual std::any visitAssociation_structure(KerMLParser::Association_structureContext *context) = 0;

    virtual std::any visitConnector(KerMLParser::ConnectorContext *context) = 0;

    virtual std::any visitConnector_declaration(KerMLParser::Connector_declarationContext *context) = 0;

    virtual std::any visitBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *context) = 0;

    virtual std::any visitNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *context) = 0;

    virtual std::any visitConnector_end_member(KerMLParser::Connector_end_memberContext *context) = 0;

    virtual std::any visitConnector_end(KerMLParser::Connector_endContext *context) = 0;

    virtual std::any visitBinding_connector(KerMLParser::Binding_connectorContext *context) = 0;

    virtual std::any visitBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext *context) = 0;

    virtual std::any visitSuccession(KerMLParser::SuccessionContext *context) = 0;

    virtual std::any visitSuccession_declaration(KerMLParser::Succession_declarationContext *context) = 0;

    virtual std::any visitBehavior(KerMLParser::BehaviorContext *context) = 0;

    virtual std::any visitStep(KerMLParser::StepContext *context) = 0;

    virtual std::any visitFunction(KerMLParser::FunctionContext *context) = 0;

    virtual std::any visitFunction_body(KerMLParser::Function_bodyContext *context) = 0;

    virtual std::any visitFunction_body_part(KerMLParser::Function_body_partContext *context) = 0;

    virtual std::any visitReturn_feature_member(KerMLParser::Return_feature_memberContext *context) = 0;

    virtual std::any visitResult_expression_member(KerMLParser::Result_expression_memberContext *context) = 0;

    virtual std::any visitExpression(KerMLParser::ExpressionContext *context) = 0;

    virtual std::any visitPredicate(KerMLParser::PredicateContext *context) = 0;

    virtual std::any visitBoolean_expression(KerMLParser::Boolean_expressionContext *context) = 0;

    virtual std::any visitInvariant(KerMLParser::InvariantContext *context) = 0;

    virtual std::any visitOwned_expression_reference_member(KerMLParser::Owned_expression_reference_memberContext *context) = 0;

    virtual std::any visitOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *context) = 0;

    virtual std::any visitOwned_expression_member(KerMLParser::Owned_expression_memberContext *context) = 0;

    virtual std::any visitOwned_expressions(KerMLParser::Owned_expressionsContext *context) = 0;

    virtual std::any visitOwned_expression(KerMLParser::Owned_expressionContext *context) = 0;

    virtual std::any visitEased_owned_expression(KerMLParser::Eased_owned_expressionContext *context) = 0;

    virtual std::any visitConditional_expression(KerMLParser::Conditional_expressionContext *context) = 0;

    virtual std::any visitConditional_binary_operator_expression(KerMLParser::Conditional_binary_operator_expressionContext *context) = 0;

    virtual std::any visitConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext *context) = 0;

    virtual std::any visitBinary_operator_expression(KerMLParser::Binary_operator_expressionContext *context) = 0;

    virtual std::any visitBinary_operator(KerMLParser::Binary_operatorContext *context) = 0;

    virtual std::any visitUnary_operator_expression(KerMLParser::Unary_operator_expressionContext *context) = 0;

    virtual std::any visitUnary_operator(KerMLParser::Unary_operatorContext *context) = 0;

    virtual std::any visitClassification_expression(KerMLParser::Classification_expressionContext *context) = 0;

    virtual std::any visitClassification(KerMLParser::ClassificationContext *context) = 0;

    virtual std::any visitClassification_test_operator(KerMLParser::Classification_test_operatorContext *context) = 0;

    virtual std::any visitCast_operator(KerMLParser::Cast_operatorContext *context) = 0;

    virtual std::any visitMetaclassification_expression(KerMLParser::Metaclassification_expressionContext *context) = 0;

    virtual std::any visitArgument_member(KerMLParser::Argument_memberContext *context) = 0;

    virtual std::any visitArgument(KerMLParser::ArgumentContext *context) = 0;

    virtual std::any visitArgument_value(KerMLParser::Argument_valueContext *context) = 0;

    virtual std::any visitArgument_expression_member(KerMLParser::Argument_expression_memberContext *context) = 0;

    virtual std::any visitArgument_expression(KerMLParser::Argument_expressionContext *context) = 0;

    virtual std::any visitArgument_expression_value(KerMLParser::Argument_expression_valueContext *context) = 0;

    virtual std::any visitMetadata_argument_member(KerMLParser::Metadata_argument_memberContext *context) = 0;

    virtual std::any visitMetadata_argument(KerMLParser::Metadata_argumentContext *context) = 0;

    virtual std::any visitMetadata_value(KerMLParser::Metadata_valueContext *context) = 0;

    virtual std::any visitMetadata_reference(KerMLParser::Metadata_referenceContext *context) = 0;

    virtual std::any visitMetadataclassification_test_operator(KerMLParser::Metadataclassification_test_operatorContext *context) = 0;

    virtual std::any visitMeta_cast_operator(KerMLParser::Meta_cast_operatorContext *context) = 0;

    virtual std::any visitExtend_expression(KerMLParser::Extend_expressionContext *context) = 0;

    virtual std::any visitType_reference_member(KerMLParser::Type_reference_memberContext *context) = 0;

    virtual std::any visitType_result_member(KerMLParser::Type_result_memberContext *context) = 0;

    virtual std::any visitType_reference(KerMLParser::Type_referenceContext *context) = 0;

    virtual std::any visitReference_typing(KerMLParser::Reference_typingContext *context) = 0;

    virtual std::any visitPrimary_expressions(KerMLParser::Primary_expressionsContext *context) = 0;

    virtual std::any visitPrimary_expression(KerMLParser::Primary_expressionContext *context) = 0;

    virtual std::any visitPrimary_argument_value(KerMLParser::Primary_argument_valueContext *context) = 0;

    virtual std::any visitPrimary_argument(KerMLParser::Primary_argumentContext *context) = 0;

    virtual std::any visitPrimary_argument_member(KerMLParser::Primary_argument_memberContext *context) = 0;

    virtual std::any visitNon_feature_chain_primary_expression(KerMLParser::Non_feature_chain_primary_expressionContext *context) = 0;

    virtual std::any visitNon_feature_chain_primary_argument_value(KerMLParser::Non_feature_chain_primary_argument_valueContext *context) = 0;

    virtual std::any visitNon_feature_chain_primary_argument(KerMLParser::Non_feature_chain_primary_argumentContext *context) = 0;

    virtual std::any visitNon_feature_chain_primary_argument_member(KerMLParser::Non_feature_chain_primary_argument_memberContext *context) = 0;

    virtual std::any visitBracket_expression(KerMLParser::Bracket_expressionContext *context) = 0;

    virtual std::any visitIndex_expression(KerMLParser::Index_expressionContext *context) = 0;

    virtual std::any visitSequence_expression(KerMLParser::Sequence_expressionContext *context) = 0;

    virtual std::any visitSequence_expression_list(KerMLParser::Sequence_expression_listContext *context) = 0;

    virtual std::any visitSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *context) = 0;

    virtual std::any visitSequence_expression_list_member(KerMLParser::Sequence_expression_list_memberContext *context) = 0;

    virtual std::any visitFeature_chain_expression(KerMLParser::Feature_chain_expressionContext *context) = 0;

    virtual std::any visitCollect_expression(KerMLParser::Collect_expressionContext *context) = 0;

    virtual std::any visitSelect_expression(KerMLParser::Select_expressionContext *context) = 0;

    virtual std::any visitFunction_operation_expression(KerMLParser::Function_operation_expressionContext *context) = 0;

    virtual std::any visitBody_argument_member(KerMLParser::Body_argument_memberContext *context) = 0;

    virtual std::any visitBody_argument(KerMLParser::Body_argumentContext *context) = 0;

    virtual std::any visitBody_argument_value(KerMLParser::Body_argument_valueContext *context) = 0;

    virtual std::any visitBody_expression_member(KerMLParser::Body_expression_memberContext *context) = 0;

    virtual std::any visitFunction_reference_argument_member(KerMLParser::Function_reference_argument_memberContext *context) = 0;

    virtual std::any visitFunction_reference_argument(KerMLParser::Function_reference_argumentContext *context) = 0;

    virtual std::any visitFunction_reference_arugment_value(KerMLParser::Function_reference_arugment_valueContext *context) = 0;

    virtual std::any visitFunction_reference_expression(KerMLParser::Function_reference_expressionContext *context) = 0;

    virtual std::any visitFunction_reference_member(KerMLParser::Function_reference_memberContext *context) = 0;

    virtual std::any visitFunction_reference(KerMLParser::Function_referenceContext *context) = 0;

    virtual std::any visitFeature_chain_member(KerMLParser::Feature_chain_memberContext *context) = 0;

    virtual std::any visitOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *context) = 0;

    virtual std::any visitBase_expression(KerMLParser::Base_expressionContext *context) = 0;

    virtual std::any visitNull_expression(KerMLParser::Null_expressionContext *context) = 0;

    virtual std::any visitFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *context) = 0;

    virtual std::any visitFeature_reference_member(KerMLParser::Feature_reference_memberContext *context) = 0;

    virtual std::any visitFeature_reference(KerMLParser::Feature_referenceContext *context) = 0;

    virtual std::any visitMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *context) = 0;

    virtual std::any visitInvocation_expression(KerMLParser::Invocation_expressionContext *context) = 0;

    virtual std::any visitInternal_invocation_expression(KerMLParser::Internal_invocation_expressionContext *context) = 0;

    virtual std::any visitArgument_list(KerMLParser::Argument_listContext *context) = 0;

    virtual std::any visitPositional_argument_list(KerMLParser::Positional_argument_listContext *context) = 0;

    virtual std::any visitNamed_argument_list(KerMLParser::Named_argument_listContext *context) = 0;

    virtual std::any visitNamed_argument_member(KerMLParser::Named_argument_memberContext *context) = 0;

    virtual std::any visitNamed_argument(KerMLParser::Named_argumentContext *context) = 0;

    virtual std::any visitParameter_redefinition(KerMLParser::Parameter_redefinitionContext *context) = 0;

    virtual std::any visitBody_expression(KerMLParser::Body_expressionContext *context) = 0;

    virtual std::any visitExpression_body_member(KerMLParser::Expression_body_memberContext *context) = 0;

    virtual std::any visitExpression_body(KerMLParser::Expression_bodyContext *context) = 0;

    virtual std::any visitLiteral_expression(KerMLParser::Literal_expressionContext *context) = 0;

    virtual std::any visitLiteral_boolean(KerMLParser::Literal_booleanContext *context) = 0;

    virtual std::any visitBoolean_value(KerMLParser::Boolean_valueContext *context) = 0;

    virtual std::any visitLiteral_string(KerMLParser::Literal_stringContext *context) = 0;

    virtual std::any visitLiteral_integer(KerMLParser::Literal_integerContext *context) = 0;

    virtual std::any visitLiteral_real(KerMLParser::Literal_realContext *context) = 0;

    virtual std::any visitReal_value(KerMLParser::Real_valueContext *context) = 0;

    virtual std::any visitLiteral_infinity(KerMLParser::Literal_infinityContext *context) = 0;

    virtual std::any visitInteraction(KerMLParser::InteractionContext *context) = 0;

    virtual std::any visitItem_flow(KerMLParser::Item_flowContext *context) = 0;

    virtual std::any visitSuccession_item_flow(KerMLParser::Succession_item_flowContext *context) = 0;

    virtual std::any visitItem_flow_declaration(KerMLParser::Item_flow_declarationContext *context) = 0;

    virtual std::any visitItem_feature_member(KerMLParser::Item_feature_memberContext *context) = 0;

    virtual std::any visitItem_feature(KerMLParser::Item_featureContext *context) = 0;

    virtual std::any visitItem_feature_specialization_part(KerMLParser::Item_feature_specialization_partContext *context) = 0;

    virtual std::any visitItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *context) = 0;

    virtual std::any visitItem_flow_end(KerMLParser::Item_flow_endContext *context) = 0;

    virtual std::any visitItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *context) = 0;

    virtual std::any visitItem_flow_feature(KerMLParser::Item_flow_featureContext *context) = 0;

    virtual std::any visitItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *context) = 0;

    virtual std::any visitValue_part(KerMLParser::Value_partContext *context) = 0;

    virtual std::any visitFeature_value(KerMLParser::Feature_valueContext *context) = 0;

    virtual std::any visitFeature_assignment(KerMLParser::Feature_assignmentContext *context) = 0;

    virtual std::any visitMultiplicity(KerMLParser::MultiplicityContext *context) = 0;

    virtual std::any visitMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *context) = 0;

    virtual std::any visitMultiplicity_range(KerMLParser::Multiplicity_rangeContext *context) = 0;

    virtual std::any visitOwned_multiplicity(KerMLParser::Owned_multiplicityContext *context) = 0;

    virtual std::any visitOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *context) = 0;

    virtual std::any visitMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext *context) = 0;

    virtual std::any visitMultiplicity_expression_member(KerMLParser::Multiplicity_expression_memberContext *context) = 0;

    virtual std::any visitInternal_multiplicity_expression_member(KerMLParser::Internal_multiplicity_expression_memberContext *context) = 0;

    virtual std::any visitMetaclass(KerMLParser::MetaclassContext *context) = 0;

    virtual std::any visitPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *context) = 0;

    virtual std::any visitPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *context) = 0;

    virtual std::any visitPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *context) = 0;

    virtual std::any visitMetadata_feature(KerMLParser::Metadata_featureContext *context) = 0;

    virtual std::any visitMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *context) = 0;

    virtual std::any visitMetadata_body(KerMLParser::Metadata_bodyContext *context) = 0;

    virtual std::any visitMetadata_body_element(KerMLParser::Metadata_body_elementContext *context) = 0;

    virtual std::any visitMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *context) = 0;

    virtual std::any visitMetadata_body_feature(KerMLParser::Metadata_body_featureContext *context) = 0;

    virtual std::any visitPackage(KerMLParser::PackageContext *context) = 0;

    virtual std::any visitLibrary_package(KerMLParser::Library_packageContext *context) = 0;

    virtual std::any visitPackage_declaration(KerMLParser::Package_declarationContext *context) = 0;

    virtual std::any visitPackage_body(KerMLParser::Package_bodyContext *context) = 0;

    virtual std::any visitElement_filter_member(KerMLParser::Element_filter_memberContext *context) = 0;

    virtual std::any visitMeta_assignment(KerMLParser::Meta_assignmentContext *context) = 0;


};

