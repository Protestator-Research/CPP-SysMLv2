
// Generated from KerML.g4 by ANTLR 4.13.2

#pragma once


#include <antlr4-runtime.h>
#include <kerml/parser/KerMLParser.h>


/**
 * This interface defines an abstract listener for a parse tree produced by KerMLParser.
 */
class  KerMLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStart(KerMLParser::StartContext *ctx) = 0;
  virtual void exitStart(KerMLParser::StartContext *ctx) = 0;

  virtual void enterStartRule(KerMLParser::StartRuleContext *ctx) = 0;
  virtual void exitStartRule(KerMLParser::StartRuleContext *ctx) = 0;

  virtual void enterElements(KerMLParser::ElementsContext *ctx) = 0;
  virtual void exitElements(KerMLParser::ElementsContext *ctx) = 0;

  virtual void enterIdentification(KerMLParser::IdentificationContext *ctx) = 0;
  virtual void exitIdentification(KerMLParser::IdentificationContext *ctx) = 0;

  virtual void enterRelationship_body(KerMLParser::Relationship_bodyContext *ctx) = 0;
  virtual void exitRelationship_body(KerMLParser::Relationship_bodyContext *ctx) = 0;

  virtual void enterRelationship_onwed_elements(KerMLParser::Relationship_onwed_elementsContext *ctx) = 0;
  virtual void exitRelationship_onwed_elements(KerMLParser::Relationship_onwed_elementsContext *ctx) = 0;

  virtual void enterRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *ctx) = 0;
  virtual void exitRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *ctx) = 0;

  virtual void enterOwned_related_element(KerMLParser::Owned_related_elementContext *ctx) = 0;
  virtual void exitOwned_related_element(KerMLParser::Owned_related_elementContext *ctx) = 0;

  virtual void enterDependency(KerMLParser::DependencyContext *ctx) = 0;
  virtual void exitDependency(KerMLParser::DependencyContext *ctx) = 0;

  virtual void enterAnnotation(KerMLParser::AnnotationContext *ctx) = 0;
  virtual void exitAnnotation(KerMLParser::AnnotationContext *ctx) = 0;

  virtual void enterOwned_annotation(KerMLParser::Owned_annotationContext *ctx) = 0;
  virtual void exitOwned_annotation(KerMLParser::Owned_annotationContext *ctx) = 0;

  virtual void enterAnnotating_element(KerMLParser::Annotating_elementContext *ctx) = 0;
  virtual void exitAnnotating_element(KerMLParser::Annotating_elementContext *ctx) = 0;

  virtual void enterComment(KerMLParser::CommentContext *ctx) = 0;
  virtual void exitComment(KerMLParser::CommentContext *ctx) = 0;

  virtual void enterDocumentation(KerMLParser::DocumentationContext *ctx) = 0;
  virtual void exitDocumentation(KerMLParser::DocumentationContext *ctx) = 0;

  virtual void enterTextual_representation(KerMLParser::Textual_representationContext *ctx) = 0;
  virtual void exitTextual_representation(KerMLParser::Textual_representationContext *ctx) = 0;

  virtual void enterRoot_namespace(KerMLParser::Root_namespaceContext *ctx) = 0;
  virtual void exitRoot_namespace(KerMLParser::Root_namespaceContext *ctx) = 0;

  virtual void enterNamespace(KerMLParser::NamespaceContext *ctx) = 0;
  virtual void exitNamespace(KerMLParser::NamespaceContext *ctx) = 0;

  virtual void enterNamespace_declaration(KerMLParser::Namespace_declarationContext *ctx) = 0;
  virtual void exitNamespace_declaration(KerMLParser::Namespace_declarationContext *ctx) = 0;

  virtual void enterNamespace_body(KerMLParser::Namespace_bodyContext *ctx) = 0;
  virtual void exitNamespace_body(KerMLParser::Namespace_bodyContext *ctx) = 0;

  virtual void enterNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *ctx) = 0;
  virtual void exitNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *ctx) = 0;

  virtual void enterNamespace_body_element(KerMLParser::Namespace_body_elementContext *ctx) = 0;
  virtual void exitNamespace_body_element(KerMLParser::Namespace_body_elementContext *ctx) = 0;

  virtual void enterMember_prefix(KerMLParser::Member_prefixContext *ctx) = 0;
  virtual void exitMember_prefix(KerMLParser::Member_prefixContext *ctx) = 0;

  virtual void enterVisibility_indicator(KerMLParser::Visibility_indicatorContext *ctx) = 0;
  virtual void exitVisibility_indicator(KerMLParser::Visibility_indicatorContext *ctx) = 0;

  virtual void enterNamespace_member(KerMLParser::Namespace_memberContext *ctx) = 0;
  virtual void exitNamespace_member(KerMLParser::Namespace_memberContext *ctx) = 0;

  virtual void enterNon_feature_member(KerMLParser::Non_feature_memberContext *ctx) = 0;
  virtual void exitNon_feature_member(KerMLParser::Non_feature_memberContext *ctx) = 0;

  virtual void enterNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *ctx) = 0;
  virtual void exitNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *ctx) = 0;

  virtual void enterAlias_member(KerMLParser::Alias_memberContext *ctx) = 0;
  virtual void exitAlias_member(KerMLParser::Alias_memberContext *ctx) = 0;

  virtual void enterQualified_name(KerMLParser::Qualified_nameContext *ctx) = 0;
  virtual void exitQualified_name(KerMLParser::Qualified_nameContext *ctx) = 0;

  virtual void enterNamespace_import(KerMLParser::Namespace_importContext *ctx) = 0;
  virtual void exitNamespace_import(KerMLParser::Namespace_importContext *ctx) = 0;

  virtual void enterImport_declaration(KerMLParser::Import_declarationContext *ctx) = 0;
  virtual void exitImport_declaration(KerMLParser::Import_declarationContext *ctx) = 0;

  virtual void enterMembership_import(KerMLParser::Membership_importContext *ctx) = 0;
  virtual void exitMembership_import(KerMLParser::Membership_importContext *ctx) = 0;

  virtual void enterFilter_package(KerMLParser::Filter_packageContext *ctx) = 0;
  virtual void exitFilter_package(KerMLParser::Filter_packageContext *ctx) = 0;

  virtual void enterFilter_package_member(KerMLParser::Filter_package_memberContext *ctx) = 0;
  virtual void exitFilter_package_member(KerMLParser::Filter_package_memberContext *ctx) = 0;

  virtual void enterElement(KerMLParser::ElementContext *ctx) = 0;
  virtual void exitElement(KerMLParser::ElementContext *ctx) = 0;

  virtual void enterNon_feature_element(KerMLParser::Non_feature_elementContext *ctx) = 0;
  virtual void exitNon_feature_element(KerMLParser::Non_feature_elementContext *ctx) = 0;

  virtual void enterFeature_element(KerMLParser::Feature_elementContext *ctx) = 0;
  virtual void exitFeature_element(KerMLParser::Feature_elementContext *ctx) = 0;

  virtual void enterAdditional_options(KerMLParser::Additional_optionsContext *ctx) = 0;
  virtual void exitAdditional_options(KerMLParser::Additional_optionsContext *ctx) = 0;

  virtual void enterType(KerMLParser::TypeContext *ctx) = 0;
  virtual void exitType(KerMLParser::TypeContext *ctx) = 0;

  virtual void enterType_prefix(KerMLParser::Type_prefixContext *ctx) = 0;
  virtual void exitType_prefix(KerMLParser::Type_prefixContext *ctx) = 0;

  virtual void enterType_declaration(KerMLParser::Type_declarationContext *ctx) = 0;
  virtual void exitType_declaration(KerMLParser::Type_declarationContext *ctx) = 0;

  virtual void enterSpecialization_part(KerMLParser::Specialization_partContext *ctx) = 0;
  virtual void exitSpecialization_part(KerMLParser::Specialization_partContext *ctx) = 0;

  virtual void enterConjugation_part(KerMLParser::Conjugation_partContext *ctx) = 0;
  virtual void exitConjugation_part(KerMLParser::Conjugation_partContext *ctx) = 0;

  virtual void enterType_relationship_part(KerMLParser::Type_relationship_partContext *ctx) = 0;
  virtual void exitType_relationship_part(KerMLParser::Type_relationship_partContext *ctx) = 0;

  virtual void enterDisjoining_part(KerMLParser::Disjoining_partContext *ctx) = 0;
  virtual void exitDisjoining_part(KerMLParser::Disjoining_partContext *ctx) = 0;

  virtual void enterUnioning_part(KerMLParser::Unioning_partContext *ctx) = 0;
  virtual void exitUnioning_part(KerMLParser::Unioning_partContext *ctx) = 0;

  virtual void enterIntersecting_part(KerMLParser::Intersecting_partContext *ctx) = 0;
  virtual void exitIntersecting_part(KerMLParser::Intersecting_partContext *ctx) = 0;

  virtual void enterDifferencing_part(KerMLParser::Differencing_partContext *ctx) = 0;
  virtual void exitDifferencing_part(KerMLParser::Differencing_partContext *ctx) = 0;

  virtual void enterType_body(KerMLParser::Type_bodyContext *ctx) = 0;
  virtual void exitType_body(KerMLParser::Type_bodyContext *ctx) = 0;

  virtual void enterType_body_elements(KerMLParser::Type_body_elementsContext *ctx) = 0;
  virtual void exitType_body_elements(KerMLParser::Type_body_elementsContext *ctx) = 0;

  virtual void enterType_body_element(KerMLParser::Type_body_elementContext *ctx) = 0;
  virtual void exitType_body_element(KerMLParser::Type_body_elementContext *ctx) = 0;

  virtual void enterSpecialization(KerMLParser::SpecializationContext *ctx) = 0;
  virtual void exitSpecialization(KerMLParser::SpecializationContext *ctx) = 0;

  virtual void enterOwned_specialization(KerMLParser::Owned_specializationContext *ctx) = 0;
  virtual void exitOwned_specialization(KerMLParser::Owned_specializationContext *ctx) = 0;

  virtual void enterSpecific_type(KerMLParser::Specific_typeContext *ctx) = 0;
  virtual void exitSpecific_type(KerMLParser::Specific_typeContext *ctx) = 0;

  virtual void enterGeneral_type(KerMLParser::General_typeContext *ctx) = 0;
  virtual void exitGeneral_type(KerMLParser::General_typeContext *ctx) = 0;

  virtual void enterConjunction(KerMLParser::ConjunctionContext *ctx) = 0;
  virtual void exitConjunction(KerMLParser::ConjunctionContext *ctx) = 0;

  virtual void enterOwned_conjugation(KerMLParser::Owned_conjugationContext *ctx) = 0;
  virtual void exitOwned_conjugation(KerMLParser::Owned_conjugationContext *ctx) = 0;

  virtual void enterDisjoining(KerMLParser::DisjoiningContext *ctx) = 0;
  virtual void exitDisjoining(KerMLParser::DisjoiningContext *ctx) = 0;

  virtual void enterOwned_disjoining(KerMLParser::Owned_disjoiningContext *ctx) = 0;
  virtual void exitOwned_disjoining(KerMLParser::Owned_disjoiningContext *ctx) = 0;

  virtual void enterUnioning(KerMLParser::UnioningContext *ctx) = 0;
  virtual void exitUnioning(KerMLParser::UnioningContext *ctx) = 0;

  virtual void enterIntersecting(KerMLParser::IntersectingContext *ctx) = 0;
  virtual void exitIntersecting(KerMLParser::IntersectingContext *ctx) = 0;

  virtual void enterDifferencing(KerMLParser::DifferencingContext *ctx) = 0;
  virtual void exitDifferencing(KerMLParser::DifferencingContext *ctx) = 0;

  virtual void enterFeature_member(KerMLParser::Feature_memberContext *ctx) = 0;
  virtual void exitFeature_member(KerMLParser::Feature_memberContext *ctx) = 0;

  virtual void enterType_feature_member(KerMLParser::Type_feature_memberContext *ctx) = 0;
  virtual void exitType_feature_member(KerMLParser::Type_feature_memberContext *ctx) = 0;

  virtual void enterOwned_feature_member(KerMLParser::Owned_feature_memberContext *ctx) = 0;
  virtual void exitOwned_feature_member(KerMLParser::Owned_feature_memberContext *ctx) = 0;

  virtual void enterClassifier(KerMLParser::ClassifierContext *ctx) = 0;
  virtual void exitClassifier(KerMLParser::ClassifierContext *ctx) = 0;

  virtual void enterClassifier_declaration(KerMLParser::Classifier_declarationContext *ctx) = 0;
  virtual void exitClassifier_declaration(KerMLParser::Classifier_declarationContext *ctx) = 0;

  virtual void enterSuperclassing_part(KerMLParser::Superclassing_partContext *ctx) = 0;
  virtual void exitSuperclassing_part(KerMLParser::Superclassing_partContext *ctx) = 0;

  virtual void enterSubclassification(KerMLParser::SubclassificationContext *ctx) = 0;
  virtual void exitSubclassification(KerMLParser::SubclassificationContext *ctx) = 0;

  virtual void enterOwned_subclassification(KerMLParser::Owned_subclassificationContext *ctx) = 0;
  virtual void exitOwned_subclassification(KerMLParser::Owned_subclassificationContext *ctx) = 0;

  virtual void enterFeature(KerMLParser::FeatureContext *ctx) = 0;
  virtual void exitFeature(KerMLParser::FeatureContext *ctx) = 0;

  virtual void enterFeature_prefix(KerMLParser::Feature_prefixContext *ctx) = 0;
  virtual void exitFeature_prefix(KerMLParser::Feature_prefixContext *ctx) = 0;

  virtual void enterFeature_direction(KerMLParser::Feature_directionContext *ctx) = 0;
  virtual void exitFeature_direction(KerMLParser::Feature_directionContext *ctx) = 0;

  virtual void enterFeature_declaration(KerMLParser::Feature_declarationContext *ctx) = 0;
  virtual void exitFeature_declaration(KerMLParser::Feature_declarationContext *ctx) = 0;

  virtual void enterFeature_identification(KerMLParser::Feature_identificationContext *ctx) = 0;
  virtual void exitFeature_identification(KerMLParser::Feature_identificationContext *ctx) = 0;

  virtual void enterFeature_relationship_part(KerMLParser::Feature_relationship_partContext *ctx) = 0;
  virtual void exitFeature_relationship_part(KerMLParser::Feature_relationship_partContext *ctx) = 0;

  virtual void enterChaining_part(KerMLParser::Chaining_partContext *ctx) = 0;
  virtual void exitChaining_part(KerMLParser::Chaining_partContext *ctx) = 0;

  virtual void enterInverting_part(KerMLParser::Inverting_partContext *ctx) = 0;
  virtual void exitInverting_part(KerMLParser::Inverting_partContext *ctx) = 0;

  virtual void enterType_featuring_part(KerMLParser::Type_featuring_partContext *ctx) = 0;
  virtual void exitType_featuring_part(KerMLParser::Type_featuring_partContext *ctx) = 0;

  virtual void enterFeature_specialization_part(KerMLParser::Feature_specialization_partContext *ctx) = 0;
  virtual void exitFeature_specialization_part(KerMLParser::Feature_specialization_partContext *ctx) = 0;

  virtual void enterMultiplicity_part(KerMLParser::Multiplicity_partContext *ctx) = 0;
  virtual void exitMultiplicity_part(KerMLParser::Multiplicity_partContext *ctx) = 0;

  virtual void enterFeature_specilization(KerMLParser::Feature_specilizationContext *ctx) = 0;
  virtual void exitFeature_specilization(KerMLParser::Feature_specilizationContext *ctx) = 0;

  virtual void enterTypings(KerMLParser::TypingsContext *ctx) = 0;
  virtual void exitTypings(KerMLParser::TypingsContext *ctx) = 0;

  virtual void enterTyped_by(KerMLParser::Typed_byContext *ctx) = 0;
  virtual void exitTyped_by(KerMLParser::Typed_byContext *ctx) = 0;

  virtual void enterSubsettings(KerMLParser::SubsettingsContext *ctx) = 0;
  virtual void exitSubsettings(KerMLParser::SubsettingsContext *ctx) = 0;

  virtual void enterSubsets(KerMLParser::SubsetsContext *ctx) = 0;
  virtual void exitSubsets(KerMLParser::SubsetsContext *ctx) = 0;

  virtual void enterReferences(KerMLParser::ReferencesContext *ctx) = 0;
  virtual void exitReferences(KerMLParser::ReferencesContext *ctx) = 0;

  virtual void enterRedefinitions(KerMLParser::RedefinitionsContext *ctx) = 0;
  virtual void exitRedefinitions(KerMLParser::RedefinitionsContext *ctx) = 0;

  virtual void enterRedefines(KerMLParser::RedefinesContext *ctx) = 0;
  virtual void exitRedefines(KerMLParser::RedefinesContext *ctx) = 0;

  virtual void enterFeature_typing(KerMLParser::Feature_typingContext *ctx) = 0;
  virtual void exitFeature_typing(KerMLParser::Feature_typingContext *ctx) = 0;

  virtual void enterOwned_feature_typing(KerMLParser::Owned_feature_typingContext *ctx) = 0;
  virtual void exitOwned_feature_typing(KerMLParser::Owned_feature_typingContext *ctx) = 0;

  virtual void enterSubsetting(KerMLParser::SubsettingContext *ctx) = 0;
  virtual void exitSubsetting(KerMLParser::SubsettingContext *ctx) = 0;

  virtual void enterOwned_subsetting(KerMLParser::Owned_subsettingContext *ctx) = 0;
  virtual void exitOwned_subsetting(KerMLParser::Owned_subsettingContext *ctx) = 0;

  virtual void enterOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *ctx) = 0;
  virtual void exitOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *ctx) = 0;

  virtual void enterRedefinition(KerMLParser::RedefinitionContext *ctx) = 0;
  virtual void exitRedefinition(KerMLParser::RedefinitionContext *ctx) = 0;

  virtual void enterOwned_redefinition(KerMLParser::Owned_redefinitionContext *ctx) = 0;
  virtual void exitOwned_redefinition(KerMLParser::Owned_redefinitionContext *ctx) = 0;

  virtual void enterOwned_feature_chain(KerMLParser::Owned_feature_chainContext *ctx) = 0;
  virtual void exitOwned_feature_chain(KerMLParser::Owned_feature_chainContext *ctx) = 0;

  virtual void enterFeature_chain(KerMLParser::Feature_chainContext *ctx) = 0;
  virtual void exitFeature_chain(KerMLParser::Feature_chainContext *ctx) = 0;

  virtual void enterOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *ctx) = 0;
  virtual void exitOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *ctx) = 0;

  virtual void enterFeature_inverting(KerMLParser::Feature_invertingContext *ctx) = 0;
  virtual void exitFeature_inverting(KerMLParser::Feature_invertingContext *ctx) = 0;

  virtual void enterOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *ctx) = 0;
  virtual void exitOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *ctx) = 0;

  virtual void enterType_featuring(KerMLParser::Type_featuringContext *ctx) = 0;
  virtual void exitType_featuring(KerMLParser::Type_featuringContext *ctx) = 0;

  virtual void enterOwned_type_featuring(KerMLParser::Owned_type_featuringContext *ctx) = 0;
  virtual void exitOwned_type_featuring(KerMLParser::Owned_type_featuringContext *ctx) = 0;

  virtual void enterData_type(KerMLParser::Data_typeContext *ctx) = 0;
  virtual void exitData_type(KerMLParser::Data_typeContext *ctx) = 0;

  virtual void enterClass(KerMLParser::ClassContext *ctx) = 0;
  virtual void exitClass(KerMLParser::ClassContext *ctx) = 0;

  virtual void enterStructure(KerMLParser::StructureContext *ctx) = 0;
  virtual void exitStructure(KerMLParser::StructureContext *ctx) = 0;

  virtual void enterAssociation(KerMLParser::AssociationContext *ctx) = 0;
  virtual void exitAssociation(KerMLParser::AssociationContext *ctx) = 0;

  virtual void enterAssociation_structure(KerMLParser::Association_structureContext *ctx) = 0;
  virtual void exitAssociation_structure(KerMLParser::Association_structureContext *ctx) = 0;

  virtual void enterConnector(KerMLParser::ConnectorContext *ctx) = 0;
  virtual void exitConnector(KerMLParser::ConnectorContext *ctx) = 0;

  virtual void enterConnector_declaration(KerMLParser::Connector_declarationContext *ctx) = 0;
  virtual void exitConnector_declaration(KerMLParser::Connector_declarationContext *ctx) = 0;

  virtual void enterBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *ctx) = 0;
  virtual void exitBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *ctx) = 0;

  virtual void enterNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *ctx) = 0;
  virtual void exitNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *ctx) = 0;

  virtual void enterConnector_end_member(KerMLParser::Connector_end_memberContext *ctx) = 0;
  virtual void exitConnector_end_member(KerMLParser::Connector_end_memberContext *ctx) = 0;

  virtual void enterConnector_end(KerMLParser::Connector_endContext *ctx) = 0;
  virtual void exitConnector_end(KerMLParser::Connector_endContext *ctx) = 0;

  virtual void enterBinding_connector(KerMLParser::Binding_connectorContext *ctx) = 0;
  virtual void exitBinding_connector(KerMLParser::Binding_connectorContext *ctx) = 0;

  virtual void enterBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext *ctx) = 0;
  virtual void exitBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext *ctx) = 0;

  virtual void enterSuccession(KerMLParser::SuccessionContext *ctx) = 0;
  virtual void exitSuccession(KerMLParser::SuccessionContext *ctx) = 0;

  virtual void enterSuccession_declaration(KerMLParser::Succession_declarationContext *ctx) = 0;
  virtual void exitSuccession_declaration(KerMLParser::Succession_declarationContext *ctx) = 0;

  virtual void enterBehavior(KerMLParser::BehaviorContext *ctx) = 0;
  virtual void exitBehavior(KerMLParser::BehaviorContext *ctx) = 0;

  virtual void enterStep(KerMLParser::StepContext *ctx) = 0;
  virtual void exitStep(KerMLParser::StepContext *ctx) = 0;

  virtual void enterFunction(KerMLParser::FunctionContext *ctx) = 0;
  virtual void exitFunction(KerMLParser::FunctionContext *ctx) = 0;

  virtual void enterFunction_body(KerMLParser::Function_bodyContext *ctx) = 0;
  virtual void exitFunction_body(KerMLParser::Function_bodyContext *ctx) = 0;

  virtual void enterFunction_body_part(KerMLParser::Function_body_partContext *ctx) = 0;
  virtual void exitFunction_body_part(KerMLParser::Function_body_partContext *ctx) = 0;

  virtual void enterReturn_feature_member(KerMLParser::Return_feature_memberContext *ctx) = 0;
  virtual void exitReturn_feature_member(KerMLParser::Return_feature_memberContext *ctx) = 0;

  virtual void enterResult_expression_member(KerMLParser::Result_expression_memberContext *ctx) = 0;
  virtual void exitResult_expression_member(KerMLParser::Result_expression_memberContext *ctx) = 0;

  virtual void enterExpression(KerMLParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(KerMLParser::ExpressionContext *ctx) = 0;

  virtual void enterPredicate(KerMLParser::PredicateContext *ctx) = 0;
  virtual void exitPredicate(KerMLParser::PredicateContext *ctx) = 0;

  virtual void enterBoolean_expression(KerMLParser::Boolean_expressionContext *ctx) = 0;
  virtual void exitBoolean_expression(KerMLParser::Boolean_expressionContext *ctx) = 0;

  virtual void enterInvariant(KerMLParser::InvariantContext *ctx) = 0;
  virtual void exitInvariant(KerMLParser::InvariantContext *ctx) = 0;

  virtual void enterOwned_expression_reference_member(KerMLParser::Owned_expression_reference_memberContext *ctx) = 0;
  virtual void exitOwned_expression_reference_member(KerMLParser::Owned_expression_reference_memberContext *ctx) = 0;

  virtual void enterOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *ctx) = 0;
  virtual void exitOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *ctx) = 0;

  virtual void enterOwned_expression_member(KerMLParser::Owned_expression_memberContext *ctx) = 0;
  virtual void exitOwned_expression_member(KerMLParser::Owned_expression_memberContext *ctx) = 0;

  virtual void enterOwned_expressions(KerMLParser::Owned_expressionsContext *ctx) = 0;
  virtual void exitOwned_expressions(KerMLParser::Owned_expressionsContext *ctx) = 0;

  virtual void enterOwned_expression(KerMLParser::Owned_expressionContext *ctx) = 0;
  virtual void exitOwned_expression(KerMLParser::Owned_expressionContext *ctx) = 0;

  virtual void enterEased_owned_expression(KerMLParser::Eased_owned_expressionContext *ctx) = 0;
  virtual void exitEased_owned_expression(KerMLParser::Eased_owned_expressionContext *ctx) = 0;

  virtual void enterConditional_expression(KerMLParser::Conditional_expressionContext *ctx) = 0;
  virtual void exitConditional_expression(KerMLParser::Conditional_expressionContext *ctx) = 0;

  virtual void enterConditional_binary_operator_expression(KerMLParser::Conditional_binary_operator_expressionContext *ctx) = 0;
  virtual void exitConditional_binary_operator_expression(KerMLParser::Conditional_binary_operator_expressionContext *ctx) = 0;

  virtual void enterConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext *ctx) = 0;
  virtual void exitConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext *ctx) = 0;

  virtual void enterBinary_operator_expression(KerMLParser::Binary_operator_expressionContext *ctx) = 0;
  virtual void exitBinary_operator_expression(KerMLParser::Binary_operator_expressionContext *ctx) = 0;

  virtual void enterBinary_operator(KerMLParser::Binary_operatorContext *ctx) = 0;
  virtual void exitBinary_operator(KerMLParser::Binary_operatorContext *ctx) = 0;

  virtual void enterUnary_operator_expression(KerMLParser::Unary_operator_expressionContext *ctx) = 0;
  virtual void exitUnary_operator_expression(KerMLParser::Unary_operator_expressionContext *ctx) = 0;

  virtual void enterUnary_operator(KerMLParser::Unary_operatorContext *ctx) = 0;
  virtual void exitUnary_operator(KerMLParser::Unary_operatorContext *ctx) = 0;

  virtual void enterClassification_expression(KerMLParser::Classification_expressionContext *ctx) = 0;
  virtual void exitClassification_expression(KerMLParser::Classification_expressionContext *ctx) = 0;

  virtual void enterClassification(KerMLParser::ClassificationContext *ctx) = 0;
  virtual void exitClassification(KerMLParser::ClassificationContext *ctx) = 0;

  virtual void enterClassification_test_operator(KerMLParser::Classification_test_operatorContext *ctx) = 0;
  virtual void exitClassification_test_operator(KerMLParser::Classification_test_operatorContext *ctx) = 0;

  virtual void enterCast_operator(KerMLParser::Cast_operatorContext *ctx) = 0;
  virtual void exitCast_operator(KerMLParser::Cast_operatorContext *ctx) = 0;

  virtual void enterMetaclassification_expression(KerMLParser::Metaclassification_expressionContext *ctx) = 0;
  virtual void exitMetaclassification_expression(KerMLParser::Metaclassification_expressionContext *ctx) = 0;

  virtual void enterArgument_member(KerMLParser::Argument_memberContext *ctx) = 0;
  virtual void exitArgument_member(KerMLParser::Argument_memberContext *ctx) = 0;

  virtual void enterArgument(KerMLParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(KerMLParser::ArgumentContext *ctx) = 0;

  virtual void enterArgument_value(KerMLParser::Argument_valueContext *ctx) = 0;
  virtual void exitArgument_value(KerMLParser::Argument_valueContext *ctx) = 0;

  virtual void enterArgument_expression_member(KerMLParser::Argument_expression_memberContext *ctx) = 0;
  virtual void exitArgument_expression_member(KerMLParser::Argument_expression_memberContext *ctx) = 0;

  virtual void enterArgument_expression(KerMLParser::Argument_expressionContext *ctx) = 0;
  virtual void exitArgument_expression(KerMLParser::Argument_expressionContext *ctx) = 0;

  virtual void enterArgument_expression_value(KerMLParser::Argument_expression_valueContext *ctx) = 0;
  virtual void exitArgument_expression_value(KerMLParser::Argument_expression_valueContext *ctx) = 0;

  virtual void enterMetadata_argument_member(KerMLParser::Metadata_argument_memberContext *ctx) = 0;
  virtual void exitMetadata_argument_member(KerMLParser::Metadata_argument_memberContext *ctx) = 0;

  virtual void enterMetadata_argument(KerMLParser::Metadata_argumentContext *ctx) = 0;
  virtual void exitMetadata_argument(KerMLParser::Metadata_argumentContext *ctx) = 0;

  virtual void enterMetadata_value(KerMLParser::Metadata_valueContext *ctx) = 0;
  virtual void exitMetadata_value(KerMLParser::Metadata_valueContext *ctx) = 0;

  virtual void enterMetadata_reference(KerMLParser::Metadata_referenceContext *ctx) = 0;
  virtual void exitMetadata_reference(KerMLParser::Metadata_referenceContext *ctx) = 0;

  virtual void enterMetadataclassification_test_operator(KerMLParser::Metadataclassification_test_operatorContext *ctx) = 0;
  virtual void exitMetadataclassification_test_operator(KerMLParser::Metadataclassification_test_operatorContext *ctx) = 0;

  virtual void enterMeta_cast_operator(KerMLParser::Meta_cast_operatorContext *ctx) = 0;
  virtual void exitMeta_cast_operator(KerMLParser::Meta_cast_operatorContext *ctx) = 0;

  virtual void enterExtend_expression(KerMLParser::Extend_expressionContext *ctx) = 0;
  virtual void exitExtend_expression(KerMLParser::Extend_expressionContext *ctx) = 0;

  virtual void enterType_reference_member(KerMLParser::Type_reference_memberContext *ctx) = 0;
  virtual void exitType_reference_member(KerMLParser::Type_reference_memberContext *ctx) = 0;

  virtual void enterType_result_member(KerMLParser::Type_result_memberContext *ctx) = 0;
  virtual void exitType_result_member(KerMLParser::Type_result_memberContext *ctx) = 0;

  virtual void enterType_reference(KerMLParser::Type_referenceContext *ctx) = 0;
  virtual void exitType_reference(KerMLParser::Type_referenceContext *ctx) = 0;

  virtual void enterReference_typing(KerMLParser::Reference_typingContext *ctx) = 0;
  virtual void exitReference_typing(KerMLParser::Reference_typingContext *ctx) = 0;

  virtual void enterPrimary_expressions(KerMLParser::Primary_expressionsContext *ctx) = 0;
  virtual void exitPrimary_expressions(KerMLParser::Primary_expressionsContext *ctx) = 0;

  virtual void enterPrimary_expression(KerMLParser::Primary_expressionContext *ctx) = 0;
  virtual void exitPrimary_expression(KerMLParser::Primary_expressionContext *ctx) = 0;

  virtual void enterPrimary_argument_value(KerMLParser::Primary_argument_valueContext *ctx) = 0;
  virtual void exitPrimary_argument_value(KerMLParser::Primary_argument_valueContext *ctx) = 0;

  virtual void enterPrimary_argument(KerMLParser::Primary_argumentContext *ctx) = 0;
  virtual void exitPrimary_argument(KerMLParser::Primary_argumentContext *ctx) = 0;

  virtual void enterPrimary_argument_member(KerMLParser::Primary_argument_memberContext *ctx) = 0;
  virtual void exitPrimary_argument_member(KerMLParser::Primary_argument_memberContext *ctx) = 0;

  virtual void enterNon_feature_chain_primary_expression(KerMLParser::Non_feature_chain_primary_expressionContext *ctx) = 0;
  virtual void exitNon_feature_chain_primary_expression(KerMLParser::Non_feature_chain_primary_expressionContext *ctx) = 0;

  virtual void enterNon_feature_chain_primary_argument_value(KerMLParser::Non_feature_chain_primary_argument_valueContext *ctx) = 0;
  virtual void exitNon_feature_chain_primary_argument_value(KerMLParser::Non_feature_chain_primary_argument_valueContext *ctx) = 0;

  virtual void enterNon_feature_chain_primary_argument(KerMLParser::Non_feature_chain_primary_argumentContext *ctx) = 0;
  virtual void exitNon_feature_chain_primary_argument(KerMLParser::Non_feature_chain_primary_argumentContext *ctx) = 0;

  virtual void enterNon_feature_chain_primary_argument_member(KerMLParser::Non_feature_chain_primary_argument_memberContext *ctx) = 0;
  virtual void exitNon_feature_chain_primary_argument_member(KerMLParser::Non_feature_chain_primary_argument_memberContext *ctx) = 0;

  virtual void enterBracket_expression(KerMLParser::Bracket_expressionContext *ctx) = 0;
  virtual void exitBracket_expression(KerMLParser::Bracket_expressionContext *ctx) = 0;

  virtual void enterIndex_expression(KerMLParser::Index_expressionContext *ctx) = 0;
  virtual void exitIndex_expression(KerMLParser::Index_expressionContext *ctx) = 0;

  virtual void enterSequence_expression(KerMLParser::Sequence_expressionContext *ctx) = 0;
  virtual void exitSequence_expression(KerMLParser::Sequence_expressionContext *ctx) = 0;

  virtual void enterSequence_expression_list(KerMLParser::Sequence_expression_listContext *ctx) = 0;
  virtual void exitSequence_expression_list(KerMLParser::Sequence_expression_listContext *ctx) = 0;

  virtual void enterSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *ctx) = 0;
  virtual void exitSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *ctx) = 0;

  virtual void enterSequence_expression_list_member(KerMLParser::Sequence_expression_list_memberContext *ctx) = 0;
  virtual void exitSequence_expression_list_member(KerMLParser::Sequence_expression_list_memberContext *ctx) = 0;

  virtual void enterFeature_chain_expression(KerMLParser::Feature_chain_expressionContext *ctx) = 0;
  virtual void exitFeature_chain_expression(KerMLParser::Feature_chain_expressionContext *ctx) = 0;

  virtual void enterCollect_expression(KerMLParser::Collect_expressionContext *ctx) = 0;
  virtual void exitCollect_expression(KerMLParser::Collect_expressionContext *ctx) = 0;

  virtual void enterSelect_expression(KerMLParser::Select_expressionContext *ctx) = 0;
  virtual void exitSelect_expression(KerMLParser::Select_expressionContext *ctx) = 0;

  virtual void enterFunction_operation_expression(KerMLParser::Function_operation_expressionContext *ctx) = 0;
  virtual void exitFunction_operation_expression(KerMLParser::Function_operation_expressionContext *ctx) = 0;

  virtual void enterBody_argument_member(KerMLParser::Body_argument_memberContext *ctx) = 0;
  virtual void exitBody_argument_member(KerMLParser::Body_argument_memberContext *ctx) = 0;

  virtual void enterBody_argument(KerMLParser::Body_argumentContext *ctx) = 0;
  virtual void exitBody_argument(KerMLParser::Body_argumentContext *ctx) = 0;

  virtual void enterBody_argument_value(KerMLParser::Body_argument_valueContext *ctx) = 0;
  virtual void exitBody_argument_value(KerMLParser::Body_argument_valueContext *ctx) = 0;

  virtual void enterBody_expression_member(KerMLParser::Body_expression_memberContext *ctx) = 0;
  virtual void exitBody_expression_member(KerMLParser::Body_expression_memberContext *ctx) = 0;

  virtual void enterFunction_reference_argument_member(KerMLParser::Function_reference_argument_memberContext *ctx) = 0;
  virtual void exitFunction_reference_argument_member(KerMLParser::Function_reference_argument_memberContext *ctx) = 0;

  virtual void enterFunction_reference_argument(KerMLParser::Function_reference_argumentContext *ctx) = 0;
  virtual void exitFunction_reference_argument(KerMLParser::Function_reference_argumentContext *ctx) = 0;

  virtual void enterFunction_reference_arugment_value(KerMLParser::Function_reference_arugment_valueContext *ctx) = 0;
  virtual void exitFunction_reference_arugment_value(KerMLParser::Function_reference_arugment_valueContext *ctx) = 0;

  virtual void enterFunction_reference_expression(KerMLParser::Function_reference_expressionContext *ctx) = 0;
  virtual void exitFunction_reference_expression(KerMLParser::Function_reference_expressionContext *ctx) = 0;

  virtual void enterFunction_reference_member(KerMLParser::Function_reference_memberContext *ctx) = 0;
  virtual void exitFunction_reference_member(KerMLParser::Function_reference_memberContext *ctx) = 0;

  virtual void enterFunction_reference(KerMLParser::Function_referenceContext *ctx) = 0;
  virtual void exitFunction_reference(KerMLParser::Function_referenceContext *ctx) = 0;

  virtual void enterFeature_chain_member(KerMLParser::Feature_chain_memberContext *ctx) = 0;
  virtual void exitFeature_chain_member(KerMLParser::Feature_chain_memberContext *ctx) = 0;

  virtual void enterOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *ctx) = 0;
  virtual void exitOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *ctx) = 0;

  virtual void enterBase_expression(KerMLParser::Base_expressionContext *ctx) = 0;
  virtual void exitBase_expression(KerMLParser::Base_expressionContext *ctx) = 0;

  virtual void enterNull_expression(KerMLParser::Null_expressionContext *ctx) = 0;
  virtual void exitNull_expression(KerMLParser::Null_expressionContext *ctx) = 0;

  virtual void enterFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *ctx) = 0;
  virtual void exitFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *ctx) = 0;

  virtual void enterFeature_reference_member(KerMLParser::Feature_reference_memberContext *ctx) = 0;
  virtual void exitFeature_reference_member(KerMLParser::Feature_reference_memberContext *ctx) = 0;

  virtual void enterFeature_reference(KerMLParser::Feature_referenceContext *ctx) = 0;
  virtual void exitFeature_reference(KerMLParser::Feature_referenceContext *ctx) = 0;

  virtual void enterMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *ctx) = 0;
  virtual void exitMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *ctx) = 0;

  virtual void enterInvocation_expression(KerMLParser::Invocation_expressionContext *ctx) = 0;
  virtual void exitInvocation_expression(KerMLParser::Invocation_expressionContext *ctx) = 0;

  virtual void enterInternal_invocation_expression(KerMLParser::Internal_invocation_expressionContext *ctx) = 0;
  virtual void exitInternal_invocation_expression(KerMLParser::Internal_invocation_expressionContext *ctx) = 0;

  virtual void enterArgument_list(KerMLParser::Argument_listContext *ctx) = 0;
  virtual void exitArgument_list(KerMLParser::Argument_listContext *ctx) = 0;

  virtual void enterPositional_argument_list(KerMLParser::Positional_argument_listContext *ctx) = 0;
  virtual void exitPositional_argument_list(KerMLParser::Positional_argument_listContext *ctx) = 0;

  virtual void enterNamed_argument_list(KerMLParser::Named_argument_listContext *ctx) = 0;
  virtual void exitNamed_argument_list(KerMLParser::Named_argument_listContext *ctx) = 0;

  virtual void enterNamed_argument_member(KerMLParser::Named_argument_memberContext *ctx) = 0;
  virtual void exitNamed_argument_member(KerMLParser::Named_argument_memberContext *ctx) = 0;

  virtual void enterNamed_argument(KerMLParser::Named_argumentContext *ctx) = 0;
  virtual void exitNamed_argument(KerMLParser::Named_argumentContext *ctx) = 0;

  virtual void enterParamenter_redefinition(KerMLParser::Paramenter_redefinitionContext *ctx) = 0;
  virtual void exitParamenter_redefinition(KerMLParser::Paramenter_redefinitionContext *ctx) = 0;

  virtual void enterBody_expression(KerMLParser::Body_expressionContext *ctx) = 0;
  virtual void exitBody_expression(KerMLParser::Body_expressionContext *ctx) = 0;

  virtual void enterExpression_body_member(KerMLParser::Expression_body_memberContext *ctx) = 0;
  virtual void exitExpression_body_member(KerMLParser::Expression_body_memberContext *ctx) = 0;

  virtual void enterExpression_body(KerMLParser::Expression_bodyContext *ctx) = 0;
  virtual void exitExpression_body(KerMLParser::Expression_bodyContext *ctx) = 0;

  virtual void enterLiteral_expression(KerMLParser::Literal_expressionContext *ctx) = 0;
  virtual void exitLiteral_expression(KerMLParser::Literal_expressionContext *ctx) = 0;

  virtual void enterLiteral_boolean(KerMLParser::Literal_booleanContext *ctx) = 0;
  virtual void exitLiteral_boolean(KerMLParser::Literal_booleanContext *ctx) = 0;

  virtual void enterBoolean_value(KerMLParser::Boolean_valueContext *ctx) = 0;
  virtual void exitBoolean_value(KerMLParser::Boolean_valueContext *ctx) = 0;

  virtual void enterLiteral_string(KerMLParser::Literal_stringContext *ctx) = 0;
  virtual void exitLiteral_string(KerMLParser::Literal_stringContext *ctx) = 0;

  virtual void enterLiteral_integer(KerMLParser::Literal_integerContext *ctx) = 0;
  virtual void exitLiteral_integer(KerMLParser::Literal_integerContext *ctx) = 0;

  virtual void enterLiteral_real(KerMLParser::Literal_realContext *ctx) = 0;
  virtual void exitLiteral_real(KerMLParser::Literal_realContext *ctx) = 0;

  virtual void enterReal_value(KerMLParser::Real_valueContext *ctx) = 0;
  virtual void exitReal_value(KerMLParser::Real_valueContext *ctx) = 0;

  virtual void enterLiteral_infinity(KerMLParser::Literal_infinityContext *ctx) = 0;
  virtual void exitLiteral_infinity(KerMLParser::Literal_infinityContext *ctx) = 0;

  virtual void enterInteraction(KerMLParser::InteractionContext *ctx) = 0;
  virtual void exitInteraction(KerMLParser::InteractionContext *ctx) = 0;

  virtual void enterItem_flow(KerMLParser::Item_flowContext *ctx) = 0;
  virtual void exitItem_flow(KerMLParser::Item_flowContext *ctx) = 0;

  virtual void enterSuccession_item_flow(KerMLParser::Succession_item_flowContext *ctx) = 0;
  virtual void exitSuccession_item_flow(KerMLParser::Succession_item_flowContext *ctx) = 0;

  virtual void enterItem_flow_declaration(KerMLParser::Item_flow_declarationContext *ctx) = 0;
  virtual void exitItem_flow_declaration(KerMLParser::Item_flow_declarationContext *ctx) = 0;

  virtual void enterItem_feature_member(KerMLParser::Item_feature_memberContext *ctx) = 0;
  virtual void exitItem_feature_member(KerMLParser::Item_feature_memberContext *ctx) = 0;

  virtual void enterItem_feature(KerMLParser::Item_featureContext *ctx) = 0;
  virtual void exitItem_feature(KerMLParser::Item_featureContext *ctx) = 0;

  virtual void enterItem_feature_specilization_part(KerMLParser::Item_feature_specilization_partContext *ctx) = 0;
  virtual void exitItem_feature_specilization_part(KerMLParser::Item_feature_specilization_partContext *ctx) = 0;

  virtual void enterItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *ctx) = 0;
  virtual void exitItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *ctx) = 0;

  virtual void enterItem_flow_end(KerMLParser::Item_flow_endContext *ctx) = 0;
  virtual void exitItem_flow_end(KerMLParser::Item_flow_endContext *ctx) = 0;

  virtual void enterItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *ctx) = 0;
  virtual void exitItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *ctx) = 0;

  virtual void enterItem_flow_feature(KerMLParser::Item_flow_featureContext *ctx) = 0;
  virtual void exitItem_flow_feature(KerMLParser::Item_flow_featureContext *ctx) = 0;

  virtual void enterItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *ctx) = 0;
  virtual void exitItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *ctx) = 0;

  virtual void enterValue_part(KerMLParser::Value_partContext *ctx) = 0;
  virtual void exitValue_part(KerMLParser::Value_partContext *ctx) = 0;

  virtual void enterFeature_value(KerMLParser::Feature_valueContext *ctx) = 0;
  virtual void exitFeature_value(KerMLParser::Feature_valueContext *ctx) = 0;

  virtual void enterFeature_assignment(KerMLParser::Feature_assignmentContext *ctx) = 0;
  virtual void exitFeature_assignment(KerMLParser::Feature_assignmentContext *ctx) = 0;

  virtual void enterMultiplicity(KerMLParser::MultiplicityContext *ctx) = 0;
  virtual void exitMultiplicity(KerMLParser::MultiplicityContext *ctx) = 0;

  virtual void enterMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *ctx) = 0;
  virtual void exitMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *ctx) = 0;

  virtual void enterMultiplicity_range(KerMLParser::Multiplicity_rangeContext *ctx) = 0;
  virtual void exitMultiplicity_range(KerMLParser::Multiplicity_rangeContext *ctx) = 0;

  virtual void enterOwned_multiplicity(KerMLParser::Owned_multiplicityContext *ctx) = 0;
  virtual void exitOwned_multiplicity(KerMLParser::Owned_multiplicityContext *ctx) = 0;

  virtual void enterOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *ctx) = 0;
  virtual void exitOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *ctx) = 0;

  virtual void enterMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext *ctx) = 0;
  virtual void exitMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext *ctx) = 0;

  virtual void enterMultiplicity_expression_member(KerMLParser::Multiplicity_expression_memberContext *ctx) = 0;
  virtual void exitMultiplicity_expression_member(KerMLParser::Multiplicity_expression_memberContext *ctx) = 0;

  virtual void enterInternal_multiplicity_expression_member(KerMLParser::Internal_multiplicity_expression_memberContext *ctx) = 0;
  virtual void exitInternal_multiplicity_expression_member(KerMLParser::Internal_multiplicity_expression_memberContext *ctx) = 0;

  virtual void enterMetaclass(KerMLParser::MetaclassContext *ctx) = 0;
  virtual void exitMetaclass(KerMLParser::MetaclassContext *ctx) = 0;

  virtual void enterPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *ctx) = 0;
  virtual void exitPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *ctx) = 0;

  virtual void enterPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *ctx) = 0;
  virtual void exitPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *ctx) = 0;

  virtual void enterPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *ctx) = 0;
  virtual void exitPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *ctx) = 0;

  virtual void enterMetadata_feature(KerMLParser::Metadata_featureContext *ctx) = 0;
  virtual void exitMetadata_feature(KerMLParser::Metadata_featureContext *ctx) = 0;

  virtual void enterMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *ctx) = 0;
  virtual void exitMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *ctx) = 0;

  virtual void enterMetadata_body(KerMLParser::Metadata_bodyContext *ctx) = 0;
  virtual void exitMetadata_body(KerMLParser::Metadata_bodyContext *ctx) = 0;

  virtual void enterMetadata_body_element(KerMLParser::Metadata_body_elementContext *ctx) = 0;
  virtual void exitMetadata_body_element(KerMLParser::Metadata_body_elementContext *ctx) = 0;

  virtual void enterMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *ctx) = 0;
  virtual void exitMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *ctx) = 0;

  virtual void enterMetadata_body_feature(KerMLParser::Metadata_body_featureContext *ctx) = 0;
  virtual void exitMetadata_body_feature(KerMLParser::Metadata_body_featureContext *ctx) = 0;

  virtual void enterPackage(KerMLParser::PackageContext *ctx) = 0;
  virtual void exitPackage(KerMLParser::PackageContext *ctx) = 0;

  virtual void enterLibrary_package(KerMLParser::Library_packageContext *ctx) = 0;
  virtual void exitLibrary_package(KerMLParser::Library_packageContext *ctx) = 0;

  virtual void enterPackage_declaration(KerMLParser::Package_declarationContext *ctx) = 0;
  virtual void exitPackage_declaration(KerMLParser::Package_declarationContext *ctx) = 0;

  virtual void enterPackage_body(KerMLParser::Package_bodyContext *ctx) = 0;
  virtual void exitPackage_body(KerMLParser::Package_bodyContext *ctx) = 0;

  virtual void enterElement_filter_member(KerMLParser::Element_filter_memberContext *ctx) = 0;
  virtual void exitElement_filter_member(KerMLParser::Element_filter_memberContext *ctx) = 0;

  virtual void enterMeta_assignment(KerMLParser::Meta_assignmentContext *ctx) = 0;
  virtual void exitMeta_assignment(KerMLParser::Meta_assignmentContext *ctx) = 0;


};

