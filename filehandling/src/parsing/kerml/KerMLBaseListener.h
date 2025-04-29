
// Generated from KerML.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "KerMLListener.h"
#include "../../sysmlv2file_global.h"

/**
 * This class provides an empty implementation of KerMLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class SYSMLV2FILE_EXPORT KerMLBaseListener : public KerMLListener {
public:

  virtual void enterStart(KerMLParser::StartContext * /*ctx*/) override { }
  virtual void exitStart(KerMLParser::StartContext * /*ctx*/) override { }

  virtual void enterStartRule(KerMLParser::StartRuleContext * /*ctx*/) override { }
  virtual void exitStartRule(KerMLParser::StartRuleContext * /*ctx*/) override { }

  virtual void enterElements(KerMLParser::ElementsContext * /*ctx*/) override { }
  virtual void exitElements(KerMLParser::ElementsContext * /*ctx*/) override { }

  virtual void enterIdentification(KerMLParser::IdentificationContext * /*ctx*/) override { }
  virtual void exitIdentification(KerMLParser::IdentificationContext * /*ctx*/) override { }

  virtual void enterRelationship_body(KerMLParser::Relationship_bodyContext * /*ctx*/) override { }
  virtual void exitRelationship_body(KerMLParser::Relationship_bodyContext * /*ctx*/) override { }

  virtual void enterRelationship_onwed_elements(KerMLParser::Relationship_onwed_elementsContext * /*ctx*/) override { }
  virtual void exitRelationship_onwed_elements(KerMLParser::Relationship_onwed_elementsContext * /*ctx*/) override { }

  virtual void enterRelationship_owned_element(KerMLParser::Relationship_owned_elementContext * /*ctx*/) override { }
  virtual void exitRelationship_owned_element(KerMLParser::Relationship_owned_elementContext * /*ctx*/) override { }

  virtual void enterOwned_related_element(KerMLParser::Owned_related_elementContext * /*ctx*/) override { }
  virtual void exitOwned_related_element(KerMLParser::Owned_related_elementContext * /*ctx*/) override { }

  virtual void enterDependency(KerMLParser::DependencyContext * /*ctx*/) override { }
  virtual void exitDependency(KerMLParser::DependencyContext * /*ctx*/) override { }

  virtual void enterAnnotation(KerMLParser::AnnotationContext * /*ctx*/) override { }
  virtual void exitAnnotation(KerMLParser::AnnotationContext * /*ctx*/) override { }

  virtual void enterOwned_annotation(KerMLParser::Owned_annotationContext * /*ctx*/) override { }
  virtual void exitOwned_annotation(KerMLParser::Owned_annotationContext * /*ctx*/) override { }

  virtual void enterAnnotating_element(KerMLParser::Annotating_elementContext * /*ctx*/) override { }
  virtual void exitAnnotating_element(KerMLParser::Annotating_elementContext * /*ctx*/) override { }

  virtual void enterComment(KerMLParser::CommentContext * /*ctx*/) override { }
  virtual void exitComment(KerMLParser::CommentContext * /*ctx*/) override { }

  virtual void enterDocumentation(KerMLParser::DocumentationContext * /*ctx*/) override { }
  virtual void exitDocumentation(KerMLParser::DocumentationContext * /*ctx*/) override { }

  virtual void enterTextual_representation(KerMLParser::Textual_representationContext * /*ctx*/) override { }
  virtual void exitTextual_representation(KerMLParser::Textual_representationContext * /*ctx*/) override { }

  virtual void enterRoot_namespace(KerMLParser::Root_namespaceContext * /*ctx*/) override { }
  virtual void exitRoot_namespace(KerMLParser::Root_namespaceContext * /*ctx*/) override { }

  virtual void enterNamespace(KerMLParser::NamespaceContext * /*ctx*/) override { }
  virtual void exitNamespace(KerMLParser::NamespaceContext * /*ctx*/) override { }

  virtual void enterNamespace_declaration(KerMLParser::Namespace_declarationContext * /*ctx*/) override { }
  virtual void exitNamespace_declaration(KerMLParser::Namespace_declarationContext * /*ctx*/) override { }

  virtual void enterNamespace_body(KerMLParser::Namespace_bodyContext * /*ctx*/) override { }
  virtual void exitNamespace_body(KerMLParser::Namespace_bodyContext * /*ctx*/) override { }

  virtual void enterNamespace_body_elements(KerMLParser::Namespace_body_elementsContext * /*ctx*/) override { }
  virtual void exitNamespace_body_elements(KerMLParser::Namespace_body_elementsContext * /*ctx*/) override { }

  virtual void enterNamespace_body_element(KerMLParser::Namespace_body_elementContext * /*ctx*/) override { }
  virtual void exitNamespace_body_element(KerMLParser::Namespace_body_elementContext * /*ctx*/) override { }

  virtual void enterMember_prefix(KerMLParser::Member_prefixContext * /*ctx*/) override { }
  virtual void exitMember_prefix(KerMLParser::Member_prefixContext * /*ctx*/) override { }

  virtual void enterVisibility_indicator(KerMLParser::Visibility_indicatorContext * /*ctx*/) override { }
  virtual void exitVisibility_indicator(KerMLParser::Visibility_indicatorContext * /*ctx*/) override { }

  virtual void enterNamespace_member(KerMLParser::Namespace_memberContext * /*ctx*/) override { }
  virtual void exitNamespace_member(KerMLParser::Namespace_memberContext * /*ctx*/) override { }

  virtual void enterNon_feature_member(KerMLParser::Non_feature_memberContext * /*ctx*/) override { }
  virtual void exitNon_feature_member(KerMLParser::Non_feature_memberContext * /*ctx*/) override { }

  virtual void enterNamespace_feature_member(KerMLParser::Namespace_feature_memberContext * /*ctx*/) override { }
  virtual void exitNamespace_feature_member(KerMLParser::Namespace_feature_memberContext * /*ctx*/) override { }

  virtual void enterAlias_member(KerMLParser::Alias_memberContext * /*ctx*/) override { }
  virtual void exitAlias_member(KerMLParser::Alias_memberContext * /*ctx*/) override { }

  virtual void enterQualified_name(KerMLParser::Qualified_nameContext * /*ctx*/) override { }
  virtual void exitQualified_name(KerMLParser::Qualified_nameContext * /*ctx*/) override { }

  virtual void enterNamespace_import(KerMLParser::Namespace_importContext * /*ctx*/) override { }
  virtual void exitNamespace_import(KerMLParser::Namespace_importContext * /*ctx*/) override { }

  virtual void enterImport_declaration(KerMLParser::Import_declarationContext * /*ctx*/) override { }
  virtual void exitImport_declaration(KerMLParser::Import_declarationContext * /*ctx*/) override { }

  virtual void enterMembership_import(KerMLParser::Membership_importContext * /*ctx*/) override { }
  virtual void exitMembership_import(KerMLParser::Membership_importContext * /*ctx*/) override { }

  virtual void enterFilter_package(KerMLParser::Filter_packageContext * /*ctx*/) override { }
  virtual void exitFilter_package(KerMLParser::Filter_packageContext * /*ctx*/) override { }

  virtual void enterFilter_package_member(KerMLParser::Filter_package_memberContext * /*ctx*/) override { }
  virtual void exitFilter_package_member(KerMLParser::Filter_package_memberContext * /*ctx*/) override { }

  virtual void enterElement(KerMLParser::ElementContext * /*ctx*/) override { }
  virtual void exitElement(KerMLParser::ElementContext * /*ctx*/) override { }

  virtual void enterNon_feature_element(KerMLParser::Non_feature_elementContext * /*ctx*/) override { }
  virtual void exitNon_feature_element(KerMLParser::Non_feature_elementContext * /*ctx*/) override { }

  virtual void enterFeature_element(KerMLParser::Feature_elementContext * /*ctx*/) override { }
  virtual void exitFeature_element(KerMLParser::Feature_elementContext * /*ctx*/) override { }

  virtual void enterAdditional_options(KerMLParser::Additional_optionsContext * /*ctx*/) override { }
  virtual void exitAdditional_options(KerMLParser::Additional_optionsContext * /*ctx*/) override { }

  virtual void enterType(KerMLParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(KerMLParser::TypeContext * /*ctx*/) override { }

  virtual void enterType_prefix(KerMLParser::Type_prefixContext * /*ctx*/) override { }
  virtual void exitType_prefix(KerMLParser::Type_prefixContext * /*ctx*/) override { }

  virtual void enterType_declaration(KerMLParser::Type_declarationContext * /*ctx*/) override { }
  virtual void exitType_declaration(KerMLParser::Type_declarationContext * /*ctx*/) override { }

  virtual void enterSpecialization_part(KerMLParser::Specialization_partContext * /*ctx*/) override { }
  virtual void exitSpecialization_part(KerMLParser::Specialization_partContext * /*ctx*/) override { }

  virtual void enterConjugation_part(KerMLParser::Conjugation_partContext * /*ctx*/) override { }
  virtual void exitConjugation_part(KerMLParser::Conjugation_partContext * /*ctx*/) override { }

  virtual void enterType_relationship_part(KerMLParser::Type_relationship_partContext * /*ctx*/) override { }
  virtual void exitType_relationship_part(KerMLParser::Type_relationship_partContext * /*ctx*/) override { }

  virtual void enterDisjoining_part(KerMLParser::Disjoining_partContext * /*ctx*/) override { }
  virtual void exitDisjoining_part(KerMLParser::Disjoining_partContext * /*ctx*/) override { }

  virtual void enterUnioning_part(KerMLParser::Unioning_partContext * /*ctx*/) override { }
  virtual void exitUnioning_part(KerMLParser::Unioning_partContext * /*ctx*/) override { }

  virtual void enterIntersecting_part(KerMLParser::Intersecting_partContext * /*ctx*/) override { }
  virtual void exitIntersecting_part(KerMLParser::Intersecting_partContext * /*ctx*/) override { }

  virtual void enterDifferencing_part(KerMLParser::Differencing_partContext * /*ctx*/) override { }
  virtual void exitDifferencing_part(KerMLParser::Differencing_partContext * /*ctx*/) override { }

  virtual void enterType_body(KerMLParser::Type_bodyContext * /*ctx*/) override { }
  virtual void exitType_body(KerMLParser::Type_bodyContext * /*ctx*/) override { }

  virtual void enterType_body_elements(KerMLParser::Type_body_elementsContext * /*ctx*/) override { }
  virtual void exitType_body_elements(KerMLParser::Type_body_elementsContext * /*ctx*/) override { }

  virtual void enterType_body_element(KerMLParser::Type_body_elementContext * /*ctx*/) override { }
  virtual void exitType_body_element(KerMLParser::Type_body_elementContext * /*ctx*/) override { }

  virtual void enterSpecialization(KerMLParser::SpecializationContext * /*ctx*/) override { }
  virtual void exitSpecialization(KerMLParser::SpecializationContext * /*ctx*/) override { }

  virtual void enterOwned_specialization(KerMLParser::Owned_specializationContext * /*ctx*/) override { }
  virtual void exitOwned_specialization(KerMLParser::Owned_specializationContext * /*ctx*/) override { }

  virtual void enterSpecific_type(KerMLParser::Specific_typeContext * /*ctx*/) override { }
  virtual void exitSpecific_type(KerMLParser::Specific_typeContext * /*ctx*/) override { }

  virtual void enterGeneral_type(KerMLParser::General_typeContext * /*ctx*/) override { }
  virtual void exitGeneral_type(KerMLParser::General_typeContext * /*ctx*/) override { }

  virtual void enterConjunction(KerMLParser::ConjunctionContext * /*ctx*/) override { }
  virtual void exitConjunction(KerMLParser::ConjunctionContext * /*ctx*/) override { }

  virtual void enterOwned_conjugation(KerMLParser::Owned_conjugationContext * /*ctx*/) override { }
  virtual void exitOwned_conjugation(KerMLParser::Owned_conjugationContext * /*ctx*/) override { }

  virtual void enterDisjoining(KerMLParser::DisjoiningContext * /*ctx*/) override { }
  virtual void exitDisjoining(KerMLParser::DisjoiningContext * /*ctx*/) override { }

  virtual void enterOwned_disjoining(KerMLParser::Owned_disjoiningContext * /*ctx*/) override { }
  virtual void exitOwned_disjoining(KerMLParser::Owned_disjoiningContext * /*ctx*/) override { }

  virtual void enterUnioning(KerMLParser::UnioningContext * /*ctx*/) override { }
  virtual void exitUnioning(KerMLParser::UnioningContext * /*ctx*/) override { }

  virtual void enterIntersecting(KerMLParser::IntersectingContext * /*ctx*/) override { }
  virtual void exitIntersecting(KerMLParser::IntersectingContext * /*ctx*/) override { }

  virtual void enterDifferencing(KerMLParser::DifferencingContext * /*ctx*/) override { }
  virtual void exitDifferencing(KerMLParser::DifferencingContext * /*ctx*/) override { }

  virtual void enterFeature_member(KerMLParser::Feature_memberContext * /*ctx*/) override { }
  virtual void exitFeature_member(KerMLParser::Feature_memberContext * /*ctx*/) override { }

  virtual void enterType_feature_member(KerMLParser::Type_feature_memberContext * /*ctx*/) override { }
  virtual void exitType_feature_member(KerMLParser::Type_feature_memberContext * /*ctx*/) override { }

  virtual void enterOwned_feature_member(KerMLParser::Owned_feature_memberContext * /*ctx*/) override { }
  virtual void exitOwned_feature_member(KerMLParser::Owned_feature_memberContext * /*ctx*/) override { }

  virtual void enterClassifier(KerMLParser::ClassifierContext * /*ctx*/) override { }
  virtual void exitClassifier(KerMLParser::ClassifierContext * /*ctx*/) override { }

  virtual void enterClassifier_declaration(KerMLParser::Classifier_declarationContext * /*ctx*/) override { }
  virtual void exitClassifier_declaration(KerMLParser::Classifier_declarationContext * /*ctx*/) override { }

  virtual void enterSuperclassing_part(KerMLParser::Superclassing_partContext * /*ctx*/) override { }
  virtual void exitSuperclassing_part(KerMLParser::Superclassing_partContext * /*ctx*/) override { }

  virtual void enterSubclassification(KerMLParser::SubclassificationContext * /*ctx*/) override { }
  virtual void exitSubclassification(KerMLParser::SubclassificationContext * /*ctx*/) override { }

  virtual void enterOwned_subclassification(KerMLParser::Owned_subclassificationContext * /*ctx*/) override { }
  virtual void exitOwned_subclassification(KerMLParser::Owned_subclassificationContext * /*ctx*/) override { }

  virtual void enterFeature(KerMLParser::FeatureContext * /*ctx*/) override { }
  virtual void exitFeature(KerMLParser::FeatureContext * /*ctx*/) override { }

  virtual void enterFeature_prefix(KerMLParser::Feature_prefixContext * /*ctx*/) override { }
  virtual void exitFeature_prefix(KerMLParser::Feature_prefixContext * /*ctx*/) override { }

  virtual void enterFeature_direction(KerMLParser::Feature_directionContext * /*ctx*/) override { }
  virtual void exitFeature_direction(KerMLParser::Feature_directionContext * /*ctx*/) override { }

  virtual void enterFeature_declaration(KerMLParser::Feature_declarationContext * /*ctx*/) override { }
  virtual void exitFeature_declaration(KerMLParser::Feature_declarationContext * /*ctx*/) override { }

  virtual void enterFeature_identification(KerMLParser::Feature_identificationContext * /*ctx*/) override { }
  virtual void exitFeature_identification(KerMLParser::Feature_identificationContext * /*ctx*/) override { }

  virtual void enterFeature_relationship_part(KerMLParser::Feature_relationship_partContext * /*ctx*/) override { }
  virtual void exitFeature_relationship_part(KerMLParser::Feature_relationship_partContext * /*ctx*/) override { }

  virtual void enterChaining_part(KerMLParser::Chaining_partContext * /*ctx*/) override { }
  virtual void exitChaining_part(KerMLParser::Chaining_partContext * /*ctx*/) override { }

  virtual void enterInverting_part(KerMLParser::Inverting_partContext * /*ctx*/) override { }
  virtual void exitInverting_part(KerMLParser::Inverting_partContext * /*ctx*/) override { }

  virtual void enterType_featuring_part(KerMLParser::Type_featuring_partContext * /*ctx*/) override { }
  virtual void exitType_featuring_part(KerMLParser::Type_featuring_partContext * /*ctx*/) override { }

  virtual void enterFeature_specialization_part(KerMLParser::Feature_specialization_partContext * /*ctx*/) override { }
  virtual void exitFeature_specialization_part(KerMLParser::Feature_specialization_partContext * /*ctx*/) override { }

  virtual void enterMultiplicity_part(KerMLParser::Multiplicity_partContext * /*ctx*/) override { }
  virtual void exitMultiplicity_part(KerMLParser::Multiplicity_partContext * /*ctx*/) override { }

  virtual void enterFeature_specilization(KerMLParser::Feature_specilizationContext * /*ctx*/) override { }
  virtual void exitFeature_specilization(KerMLParser::Feature_specilizationContext * /*ctx*/) override { }

  virtual void enterTypings(KerMLParser::TypingsContext * /*ctx*/) override { }
  virtual void exitTypings(KerMLParser::TypingsContext * /*ctx*/) override { }

  virtual void enterTyped_by(KerMLParser::Typed_byContext * /*ctx*/) override { }
  virtual void exitTyped_by(KerMLParser::Typed_byContext * /*ctx*/) override { }

  virtual void enterSubsettings(KerMLParser::SubsettingsContext * /*ctx*/) override { }
  virtual void exitSubsettings(KerMLParser::SubsettingsContext * /*ctx*/) override { }

  virtual void enterSubsets(KerMLParser::SubsetsContext * /*ctx*/) override { }
  virtual void exitSubsets(KerMLParser::SubsetsContext * /*ctx*/) override { }

  virtual void enterReferences(KerMLParser::ReferencesContext * /*ctx*/) override { }
  virtual void exitReferences(KerMLParser::ReferencesContext * /*ctx*/) override { }

  virtual void enterRedefinitions(KerMLParser::RedefinitionsContext * /*ctx*/) override { }
  virtual void exitRedefinitions(KerMLParser::RedefinitionsContext * /*ctx*/) override { }

  virtual void enterRedefines(KerMLParser::RedefinesContext * /*ctx*/) override { }
  virtual void exitRedefines(KerMLParser::RedefinesContext * /*ctx*/) override { }

  virtual void enterFeature_typing(KerMLParser::Feature_typingContext * /*ctx*/) override { }
  virtual void exitFeature_typing(KerMLParser::Feature_typingContext * /*ctx*/) override { }

  virtual void enterOwned_feature_typing(KerMLParser::Owned_feature_typingContext * /*ctx*/) override { }
  virtual void exitOwned_feature_typing(KerMLParser::Owned_feature_typingContext * /*ctx*/) override { }

  virtual void enterSubsetting(KerMLParser::SubsettingContext * /*ctx*/) override { }
  virtual void exitSubsetting(KerMLParser::SubsettingContext * /*ctx*/) override { }

  virtual void enterOwned_subsetting(KerMLParser::Owned_subsettingContext * /*ctx*/) override { }
  virtual void exitOwned_subsetting(KerMLParser::Owned_subsettingContext * /*ctx*/) override { }

  virtual void enterOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext * /*ctx*/) override { }
  virtual void exitOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext * /*ctx*/) override { }

  virtual void enterRedefinition(KerMLParser::RedefinitionContext * /*ctx*/) override { }
  virtual void exitRedefinition(KerMLParser::RedefinitionContext * /*ctx*/) override { }

  virtual void enterOwned_redefinition(KerMLParser::Owned_redefinitionContext * /*ctx*/) override { }
  virtual void exitOwned_redefinition(KerMLParser::Owned_redefinitionContext * /*ctx*/) override { }

  virtual void enterOwned_feature_chain(KerMLParser::Owned_feature_chainContext * /*ctx*/) override { }
  virtual void exitOwned_feature_chain(KerMLParser::Owned_feature_chainContext * /*ctx*/) override { }

  virtual void enterFeature_chain(KerMLParser::Feature_chainContext * /*ctx*/) override { }
  virtual void exitFeature_chain(KerMLParser::Feature_chainContext * /*ctx*/) override { }

  virtual void enterOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext * /*ctx*/) override { }
  virtual void exitOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext * /*ctx*/) override { }

  virtual void enterFeature_inverting(KerMLParser::Feature_invertingContext * /*ctx*/) override { }
  virtual void exitFeature_inverting(KerMLParser::Feature_invertingContext * /*ctx*/) override { }

  virtual void enterOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext * /*ctx*/) override { }
  virtual void exitOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext * /*ctx*/) override { }

  virtual void enterType_featuring(KerMLParser::Type_featuringContext * /*ctx*/) override { }
  virtual void exitType_featuring(KerMLParser::Type_featuringContext * /*ctx*/) override { }

  virtual void enterOwned_type_featuring(KerMLParser::Owned_type_featuringContext * /*ctx*/) override { }
  virtual void exitOwned_type_featuring(KerMLParser::Owned_type_featuringContext * /*ctx*/) override { }

  virtual void enterData_type(KerMLParser::Data_typeContext * /*ctx*/) override { }
  virtual void exitData_type(KerMLParser::Data_typeContext * /*ctx*/) override { }

  virtual void enterClass(KerMLParser::ClassContext * /*ctx*/) override { }
  virtual void exitClass(KerMLParser::ClassContext * /*ctx*/) override { }

  virtual void enterStructure(KerMLParser::StructureContext * /*ctx*/) override { }
  virtual void exitStructure(KerMLParser::StructureContext * /*ctx*/) override { }

  virtual void enterAssociation(KerMLParser::AssociationContext * /*ctx*/) override { }
  virtual void exitAssociation(KerMLParser::AssociationContext * /*ctx*/) override { }

  virtual void enterAssociation_structure(KerMLParser::Association_structureContext * /*ctx*/) override { }
  virtual void exitAssociation_structure(KerMLParser::Association_structureContext * /*ctx*/) override { }

  virtual void enterConnector(KerMLParser::ConnectorContext * /*ctx*/) override { }
  virtual void exitConnector(KerMLParser::ConnectorContext * /*ctx*/) override { }

  virtual void enterConnector_declaration(KerMLParser::Connector_declarationContext * /*ctx*/) override { }
  virtual void exitConnector_declaration(KerMLParser::Connector_declarationContext * /*ctx*/) override { }

  virtual void enterBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext * /*ctx*/) override { }
  virtual void exitBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext * /*ctx*/) override { }

  virtual void enterNary_connector_declaration(KerMLParser::Nary_connector_declarationContext * /*ctx*/) override { }
  virtual void exitNary_connector_declaration(KerMLParser::Nary_connector_declarationContext * /*ctx*/) override { }

  virtual void enterConnector_end_member(KerMLParser::Connector_end_memberContext * /*ctx*/) override { }
  virtual void exitConnector_end_member(KerMLParser::Connector_end_memberContext * /*ctx*/) override { }

  virtual void enterConnector_end(KerMLParser::Connector_endContext * /*ctx*/) override { }
  virtual void exitConnector_end(KerMLParser::Connector_endContext * /*ctx*/) override { }

  virtual void enterBinding_connector(KerMLParser::Binding_connectorContext * /*ctx*/) override { }
  virtual void exitBinding_connector(KerMLParser::Binding_connectorContext * /*ctx*/) override { }

  virtual void enterBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext * /*ctx*/) override { }
  virtual void exitBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext * /*ctx*/) override { }

  virtual void enterSuccession(KerMLParser::SuccessionContext * /*ctx*/) override { }
  virtual void exitSuccession(KerMLParser::SuccessionContext * /*ctx*/) override { }

  virtual void enterSuccession_declaration(KerMLParser::Succession_declarationContext * /*ctx*/) override { }
  virtual void exitSuccession_declaration(KerMLParser::Succession_declarationContext * /*ctx*/) override { }

  virtual void enterBehavior(KerMLParser::BehaviorContext * /*ctx*/) override { }
  virtual void exitBehavior(KerMLParser::BehaviorContext * /*ctx*/) override { }

  virtual void enterStep(KerMLParser::StepContext * /*ctx*/) override { }
  virtual void exitStep(KerMLParser::StepContext * /*ctx*/) override { }

  virtual void enterFunction(KerMLParser::FunctionContext * /*ctx*/) override { }
  virtual void exitFunction(KerMLParser::FunctionContext * /*ctx*/) override { }

  virtual void enterFunction_body(KerMLParser::Function_bodyContext * /*ctx*/) override { }
  virtual void exitFunction_body(KerMLParser::Function_bodyContext * /*ctx*/) override { }

  virtual void enterFunction_body_part(KerMLParser::Function_body_partContext * /*ctx*/) override { }
  virtual void exitFunction_body_part(KerMLParser::Function_body_partContext * /*ctx*/) override { }

  virtual void enterReturn_feature_member(KerMLParser::Return_feature_memberContext * /*ctx*/) override { }
  virtual void exitReturn_feature_member(KerMLParser::Return_feature_memberContext * /*ctx*/) override { }

  virtual void enterResult_expression_member(KerMLParser::Result_expression_memberContext * /*ctx*/) override { }
  virtual void exitResult_expression_member(KerMLParser::Result_expression_memberContext * /*ctx*/) override { }

  virtual void enterExpression(KerMLParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(KerMLParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterPredicate(KerMLParser::PredicateContext * /*ctx*/) override { }
  virtual void exitPredicate(KerMLParser::PredicateContext * /*ctx*/) override { }

  virtual void enterBoolean_expression(KerMLParser::Boolean_expressionContext * /*ctx*/) override { }
  virtual void exitBoolean_expression(KerMLParser::Boolean_expressionContext * /*ctx*/) override { }

  virtual void enterInvariant(KerMLParser::InvariantContext * /*ctx*/) override { }
  virtual void exitInvariant(KerMLParser::InvariantContext * /*ctx*/) override { }

  virtual void enterOwned_expression_reference_member(KerMLParser::Owned_expression_reference_memberContext * /*ctx*/) override { }
  virtual void exitOwned_expression_reference_member(KerMLParser::Owned_expression_reference_memberContext * /*ctx*/) override { }

  virtual void enterOwned_expression_reference(KerMLParser::Owned_expression_referenceContext * /*ctx*/) override { }
  virtual void exitOwned_expression_reference(KerMLParser::Owned_expression_referenceContext * /*ctx*/) override { }

  virtual void enterOwned_expression_member(KerMLParser::Owned_expression_memberContext * /*ctx*/) override { }
  virtual void exitOwned_expression_member(KerMLParser::Owned_expression_memberContext * /*ctx*/) override { }

  virtual void enterOwned_expressions(KerMLParser::Owned_expressionsContext * /*ctx*/) override { }
  virtual void exitOwned_expressions(KerMLParser::Owned_expressionsContext * /*ctx*/) override { }

  virtual void enterOwned_expression(KerMLParser::Owned_expressionContext * /*ctx*/) override { }
  virtual void exitOwned_expression(KerMLParser::Owned_expressionContext * /*ctx*/) override { }

  virtual void enterConditional_expression(KerMLParser::Conditional_expressionContext * /*ctx*/) override { }
  virtual void exitConditional_expression(KerMLParser::Conditional_expressionContext * /*ctx*/) override { }

  virtual void enterConditional_binary_operator_expression(KerMLParser::Conditional_binary_operator_expressionContext * /*ctx*/) override { }
  virtual void exitConditional_binary_operator_expression(KerMLParser::Conditional_binary_operator_expressionContext * /*ctx*/) override { }

  virtual void enterConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext * /*ctx*/) override { }
  virtual void exitConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext * /*ctx*/) override { }

  virtual void enterBinary_operator_expression(KerMLParser::Binary_operator_expressionContext * /*ctx*/) override { }
  virtual void exitBinary_operator_expression(KerMLParser::Binary_operator_expressionContext * /*ctx*/) override { }

  virtual void enterBinary_operator(KerMLParser::Binary_operatorContext * /*ctx*/) override { }
  virtual void exitBinary_operator(KerMLParser::Binary_operatorContext * /*ctx*/) override { }

  virtual void enterUnary_operator_expression(KerMLParser::Unary_operator_expressionContext * /*ctx*/) override { }
  virtual void exitUnary_operator_expression(KerMLParser::Unary_operator_expressionContext * /*ctx*/) override { }

  virtual void enterUnary_operator(KerMLParser::Unary_operatorContext * /*ctx*/) override { }
  virtual void exitUnary_operator(KerMLParser::Unary_operatorContext * /*ctx*/) override { }

  virtual void enterClassification_expression(KerMLParser::Classification_expressionContext * /*ctx*/) override { }
  virtual void exitClassification_expression(KerMLParser::Classification_expressionContext * /*ctx*/) override { }

  virtual void enterClassification(KerMLParser::ClassificationContext * /*ctx*/) override { }
  virtual void exitClassification(KerMLParser::ClassificationContext * /*ctx*/) override { }

  virtual void enterClassification_test_operator(KerMLParser::Classification_test_operatorContext * /*ctx*/) override { }
  virtual void exitClassification_test_operator(KerMLParser::Classification_test_operatorContext * /*ctx*/) override { }

  virtual void enterCast_operator(KerMLParser::Cast_operatorContext * /*ctx*/) override { }
  virtual void exitCast_operator(KerMLParser::Cast_operatorContext * /*ctx*/) override { }

  virtual void enterMetaclassification_expression(KerMLParser::Metaclassification_expressionContext * /*ctx*/) override { }
  virtual void exitMetaclassification_expression(KerMLParser::Metaclassification_expressionContext * /*ctx*/) override { }

  virtual void enterArgument_expression_member(KerMLParser::Argument_expression_memberContext * /*ctx*/) override { }
  virtual void exitArgument_expression_member(KerMLParser::Argument_expression_memberContext * /*ctx*/) override { }

  virtual void enterArgument_expression(KerMLParser::Argument_expressionContext * /*ctx*/) override { }
  virtual void exitArgument_expression(KerMLParser::Argument_expressionContext * /*ctx*/) override { }

  virtual void enterArgument_expression_value(KerMLParser::Argument_expression_valueContext * /*ctx*/) override { }
  virtual void exitArgument_expression_value(KerMLParser::Argument_expression_valueContext * /*ctx*/) override { }

  virtual void enterMetadata_argument_member(KerMLParser::Metadata_argument_memberContext * /*ctx*/) override { }
  virtual void exitMetadata_argument_member(KerMLParser::Metadata_argument_memberContext * /*ctx*/) override { }

  virtual void enterMetadata_argument(KerMLParser::Metadata_argumentContext * /*ctx*/) override { }
  virtual void exitMetadata_argument(KerMLParser::Metadata_argumentContext * /*ctx*/) override { }

  virtual void enterMetadata_value(KerMLParser::Metadata_valueContext * /*ctx*/) override { }
  virtual void exitMetadata_value(KerMLParser::Metadata_valueContext * /*ctx*/) override { }

  virtual void enterMetadata_reference(KerMLParser::Metadata_referenceContext * /*ctx*/) override { }
  virtual void exitMetadata_reference(KerMLParser::Metadata_referenceContext * /*ctx*/) override { }

  virtual void enterMetadataclassification_test_operator(KerMLParser::Metadataclassification_test_operatorContext * /*ctx*/) override { }
  virtual void exitMetadataclassification_test_operator(KerMLParser::Metadataclassification_test_operatorContext * /*ctx*/) override { }

  virtual void enterMeta_cast_operator(KerMLParser::Meta_cast_operatorContext * /*ctx*/) override { }
  virtual void exitMeta_cast_operator(KerMLParser::Meta_cast_operatorContext * /*ctx*/) override { }

  virtual void enterExtend_expression(KerMLParser::Extend_expressionContext * /*ctx*/) override { }
  virtual void exitExtend_expression(KerMLParser::Extend_expressionContext * /*ctx*/) override { }

  virtual void enterType_reference_member(KerMLParser::Type_reference_memberContext * /*ctx*/) override { }
  virtual void exitType_reference_member(KerMLParser::Type_reference_memberContext * /*ctx*/) override { }

  virtual void enterType_result_member(KerMLParser::Type_result_memberContext * /*ctx*/) override { }
  virtual void exitType_result_member(KerMLParser::Type_result_memberContext * /*ctx*/) override { }

  virtual void enterType_reference(KerMLParser::Type_referenceContext * /*ctx*/) override { }
  virtual void exitType_reference(KerMLParser::Type_referenceContext * /*ctx*/) override { }

  virtual void enterReference_typing(KerMLParser::Reference_typingContext * /*ctx*/) override { }
  virtual void exitReference_typing(KerMLParser::Reference_typingContext * /*ctx*/) override { }

  virtual void enterPrimary_expressions(KerMLParser::Primary_expressionsContext * /*ctx*/) override { }
  virtual void exitPrimary_expressions(KerMLParser::Primary_expressionsContext * /*ctx*/) override { }

  virtual void enterPrimary_expression(KerMLParser::Primary_expressionContext * /*ctx*/) override { }
  virtual void exitPrimary_expression(KerMLParser::Primary_expressionContext * /*ctx*/) override { }

  virtual void enterNon_feature_chain_primary_expression(KerMLParser::Non_feature_chain_primary_expressionContext * /*ctx*/) override { }
  virtual void exitNon_feature_chain_primary_expression(KerMLParser::Non_feature_chain_primary_expressionContext * /*ctx*/) override { }

  virtual void enterNon_feature_chain_primary_argument_value(KerMLParser::Non_feature_chain_primary_argument_valueContext * /*ctx*/) override { }
  virtual void exitNon_feature_chain_primary_argument_value(KerMLParser::Non_feature_chain_primary_argument_valueContext * /*ctx*/) override { }

  virtual void enterBracket_expression(KerMLParser::Bracket_expressionContext * /*ctx*/) override { }
  virtual void exitBracket_expression(KerMLParser::Bracket_expressionContext * /*ctx*/) override { }

  virtual void enterIndex_expression(KerMLParser::Index_expressionContext * /*ctx*/) override { }
  virtual void exitIndex_expression(KerMLParser::Index_expressionContext * /*ctx*/) override { }

  virtual void enterSequence_expression(KerMLParser::Sequence_expressionContext * /*ctx*/) override { }
  virtual void exitSequence_expression(KerMLParser::Sequence_expressionContext * /*ctx*/) override { }

  virtual void enterSequence_expression_list(KerMLParser::Sequence_expression_listContext * /*ctx*/) override { }
  virtual void exitSequence_expression_list(KerMLParser::Sequence_expression_listContext * /*ctx*/) override { }

  virtual void enterSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext * /*ctx*/) override { }
  virtual void exitSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext * /*ctx*/) override { }

  virtual void enterSequence_expression_list_member(KerMLParser::Sequence_expression_list_memberContext * /*ctx*/) override { }
  virtual void exitSequence_expression_list_member(KerMLParser::Sequence_expression_list_memberContext * /*ctx*/) override { }

  virtual void enterFeature_chain_expression(KerMLParser::Feature_chain_expressionContext * /*ctx*/) override { }
  virtual void exitFeature_chain_expression(KerMLParser::Feature_chain_expressionContext * /*ctx*/) override { }

  virtual void enterCollect_expression(KerMLParser::Collect_expressionContext * /*ctx*/) override { }
  virtual void exitCollect_expression(KerMLParser::Collect_expressionContext * /*ctx*/) override { }

  virtual void enterSelect_expression(KerMLParser::Select_expressionContext * /*ctx*/) override { }
  virtual void exitSelect_expression(KerMLParser::Select_expressionContext * /*ctx*/) override { }

  virtual void enterFunction_operation_expression(KerMLParser::Function_operation_expressionContext * /*ctx*/) override { }
  virtual void exitFunction_operation_expression(KerMLParser::Function_operation_expressionContext * /*ctx*/) override { }

  virtual void enterBody_argument_member(KerMLParser::Body_argument_memberContext * /*ctx*/) override { }
  virtual void exitBody_argument_member(KerMLParser::Body_argument_memberContext * /*ctx*/) override { }

  virtual void enterBody_argument(KerMLParser::Body_argumentContext * /*ctx*/) override { }
  virtual void exitBody_argument(KerMLParser::Body_argumentContext * /*ctx*/) override { }

  virtual void enterBody_argument_value(KerMLParser::Body_argument_valueContext * /*ctx*/) override { }
  virtual void exitBody_argument_value(KerMLParser::Body_argument_valueContext * /*ctx*/) override { }

  virtual void enterBody_expression_member(KerMLParser::Body_expression_memberContext * /*ctx*/) override { }
  virtual void exitBody_expression_member(KerMLParser::Body_expression_memberContext * /*ctx*/) override { }

  virtual void enterFunction_reference_argument_member(KerMLParser::Function_reference_argument_memberContext * /*ctx*/) override { }
  virtual void exitFunction_reference_argument_member(KerMLParser::Function_reference_argument_memberContext * /*ctx*/) override { }

  virtual void enterFunction_reference_argument(KerMLParser::Function_reference_argumentContext * /*ctx*/) override { }
  virtual void exitFunction_reference_argument(KerMLParser::Function_reference_argumentContext * /*ctx*/) override { }

  virtual void enterFunction_reference_arugment_value(KerMLParser::Function_reference_arugment_valueContext * /*ctx*/) override { }
  virtual void exitFunction_reference_arugment_value(KerMLParser::Function_reference_arugment_valueContext * /*ctx*/) override { }

  virtual void enterFunction_reference_expression(KerMLParser::Function_reference_expressionContext * /*ctx*/) override { }
  virtual void exitFunction_reference_expression(KerMLParser::Function_reference_expressionContext * /*ctx*/) override { }

  virtual void enterFunction_reference_member(KerMLParser::Function_reference_memberContext * /*ctx*/) override { }
  virtual void exitFunction_reference_member(KerMLParser::Function_reference_memberContext * /*ctx*/) override { }

  virtual void enterFunction_reference(KerMLParser::Function_referenceContext * /*ctx*/) override { }
  virtual void exitFunction_reference(KerMLParser::Function_referenceContext * /*ctx*/) override { }

  virtual void enterFeature_chain_member(KerMLParser::Feature_chain_memberContext * /*ctx*/) override { }
  virtual void exitFeature_chain_member(KerMLParser::Feature_chain_memberContext * /*ctx*/) override { }

  virtual void enterOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext * /*ctx*/) override { }
  virtual void exitOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext * /*ctx*/) override { }

  virtual void enterBase_expression(KerMLParser::Base_expressionContext * /*ctx*/) override { }
  virtual void exitBase_expression(KerMLParser::Base_expressionContext * /*ctx*/) override { }

  virtual void enterNull_expression(KerMLParser::Null_expressionContext * /*ctx*/) override { }
  virtual void exitNull_expression(KerMLParser::Null_expressionContext * /*ctx*/) override { }

  virtual void enterFeature_reference_expression(KerMLParser::Feature_reference_expressionContext * /*ctx*/) override { }
  virtual void exitFeature_reference_expression(KerMLParser::Feature_reference_expressionContext * /*ctx*/) override { }

  virtual void enterFeature_reference_member(KerMLParser::Feature_reference_memberContext * /*ctx*/) override { }
  virtual void exitFeature_reference_member(KerMLParser::Feature_reference_memberContext * /*ctx*/) override { }

  virtual void enterFeature_reference(KerMLParser::Feature_referenceContext * /*ctx*/) override { }
  virtual void exitFeature_reference(KerMLParser::Feature_referenceContext * /*ctx*/) override { }

  virtual void enterMetadata_access_expression(KerMLParser::Metadata_access_expressionContext * /*ctx*/) override { }
  virtual void exitMetadata_access_expression(KerMLParser::Metadata_access_expressionContext * /*ctx*/) override { }

  virtual void enterInvocation_expression(KerMLParser::Invocation_expressionContext * /*ctx*/) override { }
  virtual void exitInvocation_expression(KerMLParser::Invocation_expressionContext * /*ctx*/) override { }

  virtual void enterInternal_invocation_expression(KerMLParser::Internal_invocation_expressionContext * /*ctx*/) override { }
  virtual void exitInternal_invocation_expression(KerMLParser::Internal_invocation_expressionContext * /*ctx*/) override { }

  virtual void enterArgument_list(KerMLParser::Argument_listContext * /*ctx*/) override { }
  virtual void exitArgument_list(KerMLParser::Argument_listContext * /*ctx*/) override { }

  virtual void enterPositional_argument_list(KerMLParser::Positional_argument_listContext * /*ctx*/) override { }
  virtual void exitPositional_argument_list(KerMLParser::Positional_argument_listContext * /*ctx*/) override { }

  virtual void enterNamed_argument_list(KerMLParser::Named_argument_listContext * /*ctx*/) override { }
  virtual void exitNamed_argument_list(KerMLParser::Named_argument_listContext * /*ctx*/) override { }

  virtual void enterNamed_argument_member(KerMLParser::Named_argument_memberContext * /*ctx*/) override { }
  virtual void exitNamed_argument_member(KerMLParser::Named_argument_memberContext * /*ctx*/) override { }

  virtual void enterNamed_argument(KerMLParser::Named_argumentContext * /*ctx*/) override { }
  virtual void exitNamed_argument(KerMLParser::Named_argumentContext * /*ctx*/) override { }

  virtual void enterParamenter_redefinition(KerMLParser::Paramenter_redefinitionContext * /*ctx*/) override { }
  virtual void exitParamenter_redefinition(KerMLParser::Paramenter_redefinitionContext * /*ctx*/) override { }

  virtual void enterBody_expression(KerMLParser::Body_expressionContext * /*ctx*/) override { }
  virtual void exitBody_expression(KerMLParser::Body_expressionContext * /*ctx*/) override { }

  virtual void enterExpression_body_member(KerMLParser::Expression_body_memberContext * /*ctx*/) override { }
  virtual void exitExpression_body_member(KerMLParser::Expression_body_memberContext * /*ctx*/) override { }

  virtual void enterExpression_body(KerMLParser::Expression_bodyContext * /*ctx*/) override { }
  virtual void exitExpression_body(KerMLParser::Expression_bodyContext * /*ctx*/) override { }

  virtual void enterLiteral_expression(KerMLParser::Literal_expressionContext * /*ctx*/) override { }
  virtual void exitLiteral_expression(KerMLParser::Literal_expressionContext * /*ctx*/) override { }

  virtual void enterLiteral_boolean(KerMLParser::Literal_booleanContext * /*ctx*/) override { }
  virtual void exitLiteral_boolean(KerMLParser::Literal_booleanContext * /*ctx*/) override { }

  virtual void enterBoolean_value(KerMLParser::Boolean_valueContext * /*ctx*/) override { }
  virtual void exitBoolean_value(KerMLParser::Boolean_valueContext * /*ctx*/) override { }

  virtual void enterLiteral_string(KerMLParser::Literal_stringContext * /*ctx*/) override { }
  virtual void exitLiteral_string(KerMLParser::Literal_stringContext * /*ctx*/) override { }

  virtual void enterLiteral_integer(KerMLParser::Literal_integerContext * /*ctx*/) override { }
  virtual void exitLiteral_integer(KerMLParser::Literal_integerContext * /*ctx*/) override { }

  virtual void enterLiteral_real(KerMLParser::Literal_realContext * /*ctx*/) override { }
  virtual void exitLiteral_real(KerMLParser::Literal_realContext * /*ctx*/) override { }

  virtual void enterReal_value(KerMLParser::Real_valueContext * /*ctx*/) override { }
  virtual void exitReal_value(KerMLParser::Real_valueContext * /*ctx*/) override { }

  virtual void enterLiteral_infinity(KerMLParser::Literal_infinityContext * /*ctx*/) override { }
  virtual void exitLiteral_infinity(KerMLParser::Literal_infinityContext * /*ctx*/) override { }

  virtual void enterInteraction(KerMLParser::InteractionContext * /*ctx*/) override { }
  virtual void exitInteraction(KerMLParser::InteractionContext * /*ctx*/) override { }

  virtual void enterItem_flow(KerMLParser::Item_flowContext * /*ctx*/) override { }
  virtual void exitItem_flow(KerMLParser::Item_flowContext * /*ctx*/) override { }

  virtual void enterSuccession_item_flow(KerMLParser::Succession_item_flowContext * /*ctx*/) override { }
  virtual void exitSuccession_item_flow(KerMLParser::Succession_item_flowContext * /*ctx*/) override { }

  virtual void enterItem_flow_declaration(KerMLParser::Item_flow_declarationContext * /*ctx*/) override { }
  virtual void exitItem_flow_declaration(KerMLParser::Item_flow_declarationContext * /*ctx*/) override { }

  virtual void enterItem_feature_member(KerMLParser::Item_feature_memberContext * /*ctx*/) override { }
  virtual void exitItem_feature_member(KerMLParser::Item_feature_memberContext * /*ctx*/) override { }

  virtual void enterItem_feature(KerMLParser::Item_featureContext * /*ctx*/) override { }
  virtual void exitItem_feature(KerMLParser::Item_featureContext * /*ctx*/) override { }

  virtual void enterItem_feature_specilization_part(KerMLParser::Item_feature_specilization_partContext * /*ctx*/) override { }
  virtual void exitItem_feature_specilization_part(KerMLParser::Item_feature_specilization_partContext * /*ctx*/) override { }

  virtual void enterItem_flow_end_member(KerMLParser::Item_flow_end_memberContext * /*ctx*/) override { }
  virtual void exitItem_flow_end_member(KerMLParser::Item_flow_end_memberContext * /*ctx*/) override { }

  virtual void enterItem_flow_end(KerMLParser::Item_flow_endContext * /*ctx*/) override { }
  virtual void exitItem_flow_end(KerMLParser::Item_flow_endContext * /*ctx*/) override { }

  virtual void enterItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext * /*ctx*/) override { }
  virtual void exitItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext * /*ctx*/) override { }

  virtual void enterItem_flow_feature(KerMLParser::Item_flow_featureContext * /*ctx*/) override { }
  virtual void exitItem_flow_feature(KerMLParser::Item_flow_featureContext * /*ctx*/) override { }

  virtual void enterItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext * /*ctx*/) override { }
  virtual void exitItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext * /*ctx*/) override { }

  virtual void enterValue_part(KerMLParser::Value_partContext * /*ctx*/) override { }
  virtual void exitValue_part(KerMLParser::Value_partContext * /*ctx*/) override { }

  virtual void enterFeature_value(KerMLParser::Feature_valueContext * /*ctx*/) override { }
  virtual void exitFeature_value(KerMLParser::Feature_valueContext * /*ctx*/) override { }

  virtual void enterMultiplicity(KerMLParser::MultiplicityContext * /*ctx*/) override { }
  virtual void exitMultiplicity(KerMLParser::MultiplicityContext * /*ctx*/) override { }

  virtual void enterMultiplicity_subset(KerMLParser::Multiplicity_subsetContext * /*ctx*/) override { }
  virtual void exitMultiplicity_subset(KerMLParser::Multiplicity_subsetContext * /*ctx*/) override { }

  virtual void enterMultiplicity_range(KerMLParser::Multiplicity_rangeContext * /*ctx*/) override { }
  virtual void exitMultiplicity_range(KerMLParser::Multiplicity_rangeContext * /*ctx*/) override { }

  virtual void enterOwned_multiplicity(KerMLParser::Owned_multiplicityContext * /*ctx*/) override { }
  virtual void exitOwned_multiplicity(KerMLParser::Owned_multiplicityContext * /*ctx*/) override { }

  virtual void enterOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext * /*ctx*/) override { }
  virtual void exitOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext * /*ctx*/) override { }

  virtual void enterMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext * /*ctx*/) override { }
  virtual void exitMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext * /*ctx*/) override { }

  virtual void enterMultiplicity_expression_member(KerMLParser::Multiplicity_expression_memberContext * /*ctx*/) override { }
  virtual void exitMultiplicity_expression_member(KerMLParser::Multiplicity_expression_memberContext * /*ctx*/) override { }

  virtual void enterInternal_multiplicity_expression_member(KerMLParser::Internal_multiplicity_expression_memberContext * /*ctx*/) override { }
  virtual void exitInternal_multiplicity_expression_member(KerMLParser::Internal_multiplicity_expression_memberContext * /*ctx*/) override { }

  virtual void enterMetaclass(KerMLParser::MetaclassContext * /*ctx*/) override { }
  virtual void exitMetaclass(KerMLParser::MetaclassContext * /*ctx*/) override { }

  virtual void enterPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext * /*ctx*/) override { }
  virtual void exitPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext * /*ctx*/) override { }

  virtual void enterPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext * /*ctx*/) override { }
  virtual void exitPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext * /*ctx*/) override { }

  virtual void enterPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext * /*ctx*/) override { }
  virtual void exitPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext * /*ctx*/) override { }

  virtual void enterMetadata_feature(KerMLParser::Metadata_featureContext * /*ctx*/) override { }
  virtual void exitMetadata_feature(KerMLParser::Metadata_featureContext * /*ctx*/) override { }

  virtual void enterMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext * /*ctx*/) override { }
  virtual void exitMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext * /*ctx*/) override { }

  virtual void enterMetadata_body(KerMLParser::Metadata_bodyContext * /*ctx*/) override { }
  virtual void exitMetadata_body(KerMLParser::Metadata_bodyContext * /*ctx*/) override { }

  virtual void enterMetadata_body_element(KerMLParser::Metadata_body_elementContext * /*ctx*/) override { }
  virtual void exitMetadata_body_element(KerMLParser::Metadata_body_elementContext * /*ctx*/) override { }

  virtual void enterMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext * /*ctx*/) override { }
  virtual void exitMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext * /*ctx*/) override { }

  virtual void enterMetadata_body_feature(KerMLParser::Metadata_body_featureContext * /*ctx*/) override { }
  virtual void exitMetadata_body_feature(KerMLParser::Metadata_body_featureContext * /*ctx*/) override { }

  virtual void enterPackage(KerMLParser::PackageContext * /*ctx*/) override { }
  virtual void exitPackage(KerMLParser::PackageContext * /*ctx*/) override { }

  virtual void enterLibrary_package(KerMLParser::Library_packageContext * /*ctx*/) override { }
  virtual void exitLibrary_package(KerMLParser::Library_packageContext * /*ctx*/) override { }

  virtual void enterPackage_declaration(KerMLParser::Package_declarationContext * /*ctx*/) override { }
  virtual void exitPackage_declaration(KerMLParser::Package_declarationContext * /*ctx*/) override { }

  virtual void enterPackage_body(KerMLParser::Package_bodyContext * /*ctx*/) override { }
  virtual void exitPackage_body(KerMLParser::Package_bodyContext * /*ctx*/) override { }

  virtual void enterElement_filter_member(KerMLParser::Element_filter_memberContext * /*ctx*/) override { }
  virtual void exitElement_filter_member(KerMLParser::Element_filter_memberContext * /*ctx*/) override { }

  virtual void enterMeta_assignment(KerMLParser::Meta_assignmentContext * /*ctx*/) override { }
  virtual void exitMeta_assignment(KerMLParser::Meta_assignmentContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

