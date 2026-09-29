//
// Created by Moritz Herzog on 09.05.25.
//

#pragma once

#include <sysmlv2/sysmlv2file_global.h>
#include <kerml/parser/KerMLListener.h>
#include <sysmlv2/resolution/ResolutionData.h>
#include <sysmlv2/ownership/Ownership.h>
#include <memory>
#include <stack>
#include <functional>

namespace KerML::Entities {
    class Element;
    class Type;
    class Classifier;
    class Feature;
    class Expression;
}

/**
 * Implementation of the KerMLListener interface.
 *
 * @author Moritz Herzog
 * @date 09.05.25
 * @version Beta 3
 */
class SYSMLV2FILE_EXPORT KerMLListenerImplementation : public KerMLListener{
public:
    KerMLListenerImplementation();
    ~KerMLListenerImplementation();

    void visitTerminal(antlr4::tree::TerminalNode *node) override;

    void visitErrorNode(antlr4::tree::ErrorNode *node) override;

    void enterEveryRule(antlr4::ParserRuleContext *ctx) override;

    void exitEveryRule(antlr4::ParserRuleContext *ctx) override;

    void enterConstructor_expression(KerMLParser::Constructor_expressionContext *ctx) override;

    void exitConstructor_expression(KerMLParser::Constructor_expressionContext *ctx) override;

    void enterFunction_operation_arguments(KerMLParser::Function_operation_argumentsContext *ctx) override;

    void exitFunction_operation_arguments(KerMLParser::Function_operation_argumentsContext *ctx) override;

    void enterConditionalExpr(KerMLParser::ConditionalExprContext *ctx) override;

    void exitConditionalExpr(KerMLParser::ConditionalExprContext *ctx) override;

    void enterBinaryExpr(KerMLParser::BinaryExprContext *ctx) override;

    void exitBinaryExpr(KerMLParser::BinaryExprContext *ctx) override;

    void enterUnaryExpr(KerMLParser::UnaryExprContext *ctx) override;

    void exitUnaryExpr(KerMLParser::UnaryExprContext *ctx) override;

    void enterClassificationExpr(KerMLParser::ClassificationExprContext *ctx) override;

    void exitClassificationExpr(KerMLParser::ClassificationExprContext *ctx) override;

    void enterMetaclassificationExpr(KerMLParser::MetaclassificationExprContext *ctx) override;

    void exitMetaclassificationExpr(KerMLParser::MetaclassificationExprContext *ctx) override;

    void enterExtentExpr(KerMLParser::ExtentExprContext *ctx) override;

    void exitExtentExpr(KerMLParser::ExtentExprContext *ctx) override;

    void enterIndexExpr(KerMLParser::IndexExprContext *ctx) override;

    void exitIndexExpr(KerMLParser::IndexExprContext *ctx) override;

    void enterBracketExpr(KerMLParser::BracketExprContext *ctx) override;

    void exitBracketExpr(KerMLParser::BracketExprContext *ctx) override;

    void enterFeatureChainExpr(KerMLParser::FeatureChainExprContext *ctx) override;

    void exitFeatureChainExpr(KerMLParser::FeatureChainExprContext *ctx) override;

    void enterCollectExpr(KerMLParser::CollectExprContext *ctx) override;

    void exitCollectExpr(KerMLParser::CollectExprContext *ctx) override;

    void enterSelectExpr(KerMLParser::SelectExprContext *ctx) override;

    void exitSelectExpr(KerMLParser::SelectExprContext *ctx) override;

    void enterFunctionOperationExpr(KerMLParser::FunctionOperationExprContext *ctx) override;

    void exitFunctionOperationExpr(KerMLParser::FunctionOperationExprContext *ctx) override;

    void enterSequenceExpr(KerMLParser::SequenceExprContext *ctx) override;

    void exitSequenceExpr(KerMLParser::SequenceExprContext *ctx) override;

    void enterBaseExpr(KerMLParser::BaseExprContext *ctx) override;

    void exitBaseExpr(KerMLParser::BaseExprContext *ctx) override;

    void enterStart(KerMLParser::StartContext *ctx) override;

    void exitStart(KerMLParser::StartContext *ctx) override;

    void enterStartRule(KerMLParser::StartRuleContext *ctx) override;

    void exitStartRule(KerMLParser::StartRuleContext *ctx) override;

    void enterElements(KerMLParser::ElementsContext *ctx) override;

    void exitElements(KerMLParser::ElementsContext *ctx) override;

    void enterIdentification(KerMLParser::IdentificationContext *ctx) override;

    void exitIdentification(KerMLParser::IdentificationContext *ctx) override;

    void enterRelationship_body(KerMLParser::Relationship_bodyContext *ctx) override;

    void exitRelationship_body(KerMLParser::Relationship_bodyContext *ctx) override;

    void enterRelationship_owned_elements(KerMLParser::Relationship_owned_elementsContext *ctx) override;

    void exitRelationship_owned_elements(KerMLParser::Relationship_owned_elementsContext *ctx) override;

    void enterRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *ctx) override;

    void exitRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *ctx) override;

    void enterOwned_related_element(KerMLParser::Owned_related_elementContext *ctx) override;

    void exitOwned_related_element(KerMLParser::Owned_related_elementContext *ctx) override;

    void enterDependency(KerMLParser::DependencyContext *ctx) override;

    void exitDependency(KerMLParser::DependencyContext *ctx) override;

    void enterAnnotation(KerMLParser::AnnotationContext *ctx) override;

    void exitAnnotation(KerMLParser::AnnotationContext *ctx) override;

    void enterOwned_annotation(KerMLParser::Owned_annotationContext *ctx) override;

    void exitOwned_annotation(KerMLParser::Owned_annotationContext *ctx) override;

    void enterAnnotating_element(KerMLParser::Annotating_elementContext *ctx) override;

    void exitAnnotating_element(KerMLParser::Annotating_elementContext *ctx) override;

    void enterDocumentation(KerMLParser::DocumentationContext *ctx) override;

    void exitDocumentation(KerMLParser::DocumentationContext *ctx) override;

    void enterTextual_representation(KerMLParser::Textual_representationContext *ctx) override;

    void exitTextual_representation(KerMLParser::Textual_representationContext *ctx) override;

    void enterRoot_namespace(KerMLParser::Root_namespaceContext *ctx) override;

    void exitRoot_namespace(KerMLParser::Root_namespaceContext *ctx) override;

    void enterNamespace(KerMLParser::NamespaceContext *ctx) override;

    void exitNamespace(KerMLParser::NamespaceContext *ctx) override;

    void enterNamespace_declaration(KerMLParser::Namespace_declarationContext *ctx) override;

    void exitNamespace_declaration(KerMLParser::Namespace_declarationContext *ctx) override;

    void enterNamespace_body(KerMLParser::Namespace_bodyContext *ctx) override;

    void exitNamespace_body(KerMLParser::Namespace_bodyContext *ctx) override;

    void enterNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *ctx) override;

    void exitNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *ctx) override;

    void enterNamespace_body_element(KerMLParser::Namespace_body_elementContext *ctx) override;

    void exitNamespace_body_element(KerMLParser::Namespace_body_elementContext *ctx) override;

    void enterMember_prefix(KerMLParser::Member_prefixContext *ctx) override;

    void exitMember_prefix(KerMLParser::Member_prefixContext *ctx) override;

    void enterVisibility_indicator(KerMLParser::Visibility_indicatorContext *ctx) override;

    void exitVisibility_indicator(KerMLParser::Visibility_indicatorContext *ctx) override;

    void enterNamespace_member(KerMLParser::Namespace_memberContext *ctx) override;

    void exitNamespace_member(KerMLParser::Namespace_memberContext *ctx) override;

    void enterNon_feature_member(KerMLParser::Non_feature_memberContext *ctx) override;

    void exitNon_feature_member(KerMLParser::Non_feature_memberContext *ctx) override;

    void enterNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *ctx) override;

    void exitNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *ctx) override;

    void enterAlias_member(KerMLParser::Alias_memberContext *ctx) override;

    void exitAlias_member(KerMLParser::Alias_memberContext *ctx) override;

    void enterQualified_name(KerMLParser::Qualified_nameContext *ctx) override;

    void exitQualified_name(KerMLParser::Qualified_nameContext *ctx) override;

    void enterNamespace_import(KerMLParser::Namespace_importContext *ctx) override;

    void exitNamespace_import(KerMLParser::Namespace_importContext *ctx) override;

    void enterImport_declaration(KerMLParser::Import_declarationContext *ctx) override;

    void exitImport_declaration(KerMLParser::Import_declarationContext *ctx) override;

    void enterMembership_import(KerMLParser::Membership_importContext *ctx) override;

    void exitMembership_import(KerMLParser::Membership_importContext *ctx) override;

    void enterFilter_package(KerMLParser::Filter_packageContext *ctx) override;

    void exitFilter_package(KerMLParser::Filter_packageContext *ctx) override;

    void enterFilter_package_member(KerMLParser::Filter_package_memberContext *ctx) override;

    void exitFilter_package_member(KerMLParser::Filter_package_memberContext *ctx) override;

    void enterElement(KerMLParser::ElementContext *ctx) override;

    void exitElement(KerMLParser::ElementContext *ctx) override;

    void enterNon_feature_element(KerMLParser::Non_feature_elementContext *ctx) override;

    void exitNon_feature_element(KerMLParser::Non_feature_elementContext *ctx) override;

    void enterFeature_element(KerMLParser::Feature_elementContext *ctx) override;

    void exitFeature_element(KerMLParser::Feature_elementContext *ctx) override;

    void enterAdditional_options(KerMLParser::Additional_optionsContext *ctx) override;

    void exitAdditional_options(KerMLParser::Additional_optionsContext *ctx) override;

    void enterType(KerMLParser::TypeContext *ctx) override;

    void exitType(KerMLParser::TypeContext *ctx) override;

    void enterType_prefix(KerMLParser::Type_prefixContext *ctx) override;

    void exitType_prefix(KerMLParser::Type_prefixContext *ctx) override;

    void enterType_declaration(KerMLParser::Type_declarationContext *ctx) override;

    void exitType_declaration(KerMLParser::Type_declarationContext *ctx) override;

    void enterSpecialization_part(KerMLParser::Specialization_partContext *ctx) override;

    void exitSpecialization_part(KerMLParser::Specialization_partContext *ctx) override;

    void enterConjugation_part(KerMLParser::Conjugation_partContext *ctx) override;

    void exitConjugation_part(KerMLParser::Conjugation_partContext *ctx) override;

    void enterType_relationship_part(KerMLParser::Type_relationship_partContext *ctx) override;

    void exitType_relationship_part(KerMLParser::Type_relationship_partContext *ctx) override;

    void enterDisjoining_part(KerMLParser::Disjoining_partContext *ctx) override;

    void exitDisjoining_part(KerMLParser::Disjoining_partContext *ctx) override;

    void enterUnioning_part(KerMLParser::Unioning_partContext *ctx) override;

    void exitUnioning_part(KerMLParser::Unioning_partContext *ctx) override;

    void enterIntersecting_part(KerMLParser::Intersecting_partContext *ctx) override;

    void exitIntersecting_part(KerMLParser::Intersecting_partContext *ctx) override;

    void enterDifferencing_part(KerMLParser::Differencing_partContext *ctx) override;

    void exitDifferencing_part(KerMLParser::Differencing_partContext *ctx) override;

    void enterType_body(KerMLParser::Type_bodyContext *ctx) override;

    void exitType_body(KerMLParser::Type_bodyContext *ctx) override;

    void enterType_body_elements(KerMLParser::Type_body_elementsContext *ctx) override;

    void exitType_body_elements(KerMLParser::Type_body_elementsContext *ctx) override;

    void enterType_body_element(KerMLParser::Type_body_elementContext *ctx) override;

    void exitType_body_element(KerMLParser::Type_body_elementContext *ctx) override;

    void enterSpecialization(KerMLParser::SpecializationContext *ctx) override;

    void exitSpecialization(KerMLParser::SpecializationContext *ctx) override;

    void enterOwned_specialization(KerMLParser::Owned_specializationContext *ctx) override;

    void exitOwned_specialization(KerMLParser::Owned_specializationContext *ctx) override;

    void enterSpecific_type(KerMLParser::Specific_typeContext *ctx) override;

    void exitSpecific_type(KerMLParser::Specific_typeContext *ctx) override;

    void enterGeneral_type(KerMLParser::General_typeContext *ctx) override;

    void exitGeneral_type(KerMLParser::General_typeContext *ctx) override;

    void enterConjunction(KerMLParser::ConjunctionContext *ctx) override;

    void exitConjunction(KerMLParser::ConjunctionContext *ctx) override;

    void enterOwned_conjugation(KerMLParser::Owned_conjugationContext *ctx) override;

    void exitOwned_conjugation(KerMLParser::Owned_conjugationContext *ctx) override;

    void enterDisjoining(KerMLParser::DisjoiningContext *ctx) override;

    void exitDisjoining(KerMLParser::DisjoiningContext *ctx) override;

    void enterOwned_disjoining(KerMLParser::Owned_disjoiningContext *ctx) override;

    void exitOwned_disjoining(KerMLParser::Owned_disjoiningContext *ctx) override;

    void enterUnioning(KerMLParser::UnioningContext *ctx) override;

    void exitUnioning(KerMLParser::UnioningContext *ctx) override;

    void enterIntersecting(KerMLParser::IntersectingContext *ctx) override;

    void exitIntersecting(KerMLParser::IntersectingContext *ctx) override;

    void enterDifferencing(KerMLParser::DifferencingContext *ctx) override;

    void exitDifferencing(KerMLParser::DifferencingContext *ctx) override;

    void enterFeature_member(KerMLParser::Feature_memberContext *ctx) override;

    void exitFeature_member(KerMLParser::Feature_memberContext *ctx) override;

    void enterType_feature_member(KerMLParser::Type_feature_memberContext *ctx) override;

    void exitType_feature_member(KerMLParser::Type_feature_memberContext *ctx) override;

    void enterOwned_feature_member(KerMLParser::Owned_feature_memberContext *ctx) override;

    void exitOwned_feature_member(KerMLParser::Owned_feature_memberContext *ctx) override;

    void enterClassifier(KerMLParser::ClassifierContext *ctx) override;

    void exitClassifier(KerMLParser::ClassifierContext *ctx) override;

    void enterClassifier_declaration(KerMLParser::Classifier_declarationContext *ctx) override;

    void exitClassifier_declaration(KerMLParser::Classifier_declarationContext *ctx) override;

    void enterSuperclassing_part(KerMLParser::Superclassing_partContext *ctx) override;

    void exitSuperclassing_part(KerMLParser::Superclassing_partContext *ctx) override;

    void enterSubclassification(KerMLParser::SubclassificationContext *ctx) override;

    void exitSubclassification(KerMLParser::SubclassificationContext *ctx) override;

    void enterOwned_subclassification(KerMLParser::Owned_subclassificationContext *ctx) override;

    void exitOwned_subclassification(KerMLParser::Owned_subclassificationContext *ctx) override;

    void enterFeature(KerMLParser::FeatureContext *ctx) override;

    void exitFeature(KerMLParser::FeatureContext *ctx) override;

    void enterAnonymous_feature(KerMLParser::Anonymous_featureContext *ctx) override;

    void exitAnonymous_feature(KerMLParser::Anonymous_featureContext *ctx) override;

    void enterFeature_prefix(KerMLParser::Feature_prefixContext *ctx) override;

    void exitFeature_prefix(KerMLParser::Feature_prefixContext *ctx) override;

    void enterEnd_feature_prefix(KerMLParser::End_feature_prefixContext *ctx) override;

    void exitEnd_feature_prefix(KerMLParser::End_feature_prefixContext *ctx) override;

    void enterBasic_feature_prefix(KerMLParser::Basic_feature_prefixContext *ctx) override;

    void exitBasic_feature_prefix(KerMLParser::Basic_feature_prefixContext *ctx) override;

    void enterOwned_cross_feature_member(KerMLParser::Owned_cross_feature_memberContext *ctx) override;

    void exitOwned_cross_feature_member(KerMLParser::Owned_cross_feature_memberContext *ctx) override;

    void enterOwned_cross_feature(KerMLParser::Owned_cross_featureContext *ctx) override;

    void exitOwned_cross_feature(KerMLParser::Owned_cross_featureContext *ctx) override;

    void enterOwned_cross_multiplicity_member(KerMLParser::Owned_cross_multiplicity_memberContext *ctx) override;

    void exitOwned_cross_multiplicity_member(KerMLParser::Owned_cross_multiplicity_memberContext *ctx) override;

    void enterOwned_cross_multiplicity(KerMLParser::Owned_cross_multiplicityContext *ctx) override;

    void exitOwned_cross_multiplicity(KerMLParser::Owned_cross_multiplicityContext *ctx) override;

    void enterCrosses(KerMLParser::CrossesContext *ctx) override;

    void exitCrosses(KerMLParser::CrossesContext *ctx) override;

    void enterOwned_cross_subsetting(KerMLParser::Owned_cross_subsettingContext *ctx) override;

    void exitOwned_cross_subsetting(KerMLParser::Owned_cross_subsettingContext *ctx) override;

    void enterFeature_direction(KerMLParser::Feature_directionContext *ctx) override;

    void exitFeature_direction(KerMLParser::Feature_directionContext *ctx) override;

    void enterFeature_declaration(KerMLParser::Feature_declarationContext *ctx) override;

    void exitFeature_declaration(KerMLParser::Feature_declarationContext *ctx) override;

    void enterFeature_identification(KerMLParser::Feature_identificationContext *ctx) override;

    void exitFeature_identification(KerMLParser::Feature_identificationContext *ctx) override;

    void enterFeature_relationship_part(KerMLParser::Feature_relationship_partContext *ctx) override;

    void exitFeature_relationship_part(KerMLParser::Feature_relationship_partContext *ctx) override;

    void enterChaining_part(KerMLParser::Chaining_partContext *ctx) override;

    void exitChaining_part(KerMLParser::Chaining_partContext *ctx) override;

    void enterInverting_part(KerMLParser::Inverting_partContext *ctx) override;

    void exitInverting_part(KerMLParser::Inverting_partContext *ctx) override;

    void enterType_featuring_part(KerMLParser::Type_featuring_partContext *ctx) override;

    void exitType_featuring_part(KerMLParser::Type_featuring_partContext *ctx) override;

    void enterFeature_specialization_part(KerMLParser::Feature_specialization_partContext *ctx) override;

    void exitFeature_specialization_part(KerMLParser::Feature_specialization_partContext *ctx) override;

    void enterMultiplicity_part(KerMLParser::Multiplicity_partContext *ctx) override;

    void exitMultiplicity_part(KerMLParser::Multiplicity_partContext *ctx) override;

    void enterMultiplicity_modifier(KerMLParser::Multiplicity_modifierContext *ctx) override;

    void exitMultiplicity_modifier(KerMLParser::Multiplicity_modifierContext *ctx) override;

    void enterTyped_by_operator(KerMLParser::Typed_by_operatorContext *ctx) override;

    void exitTyped_by_operator(KerMLParser::Typed_by_operatorContext *ctx) override;

    void enterSpecializes_operator(KerMLParser::Specializes_operatorContext *ctx) override;

    void exitSpecializes_operator(KerMLParser::Specializes_operatorContext *ctx) override;

    void enterSubsets_operator(KerMLParser::Subsets_operatorContext *ctx) override;

    void exitSubsets_operator(KerMLParser::Subsets_operatorContext *ctx) override;

    void enterReferences_operator(KerMLParser::References_operatorContext *ctx) override;

    void exitReferences_operator(KerMLParser::References_operatorContext *ctx) override;

    void enterRedefines_operator(KerMLParser::Redefines_operatorContext *ctx) override;

    void exitRedefines_operator(KerMLParser::Redefines_operatorContext *ctx) override;

    void enterConjugates_operator(KerMLParser::Conjugates_operatorContext *ctx) override;

    void exitConjugates_operator(KerMLParser::Conjugates_operatorContext *ctx) override;

    void enterCrosses_operator(KerMLParser::Crosses_operatorContext *ctx) override;

    void exitCrosses_operator(KerMLParser::Crosses_operatorContext *ctx) override;

    void enterFeature_specialization(KerMLParser::Feature_specializationContext *ctx) override;

    void exitFeature_specialization(KerMLParser::Feature_specializationContext *ctx) override;

    void enterTypings(KerMLParser::TypingsContext *ctx) override;

    void exitTypings(KerMLParser::TypingsContext *ctx) override;

    void enterTyped_by(KerMLParser::Typed_byContext *ctx) override;

    void exitTyped_by(KerMLParser::Typed_byContext *ctx) override;

    void enterSubsettings(KerMLParser::SubsettingsContext *ctx) override;

    void exitSubsettings(KerMLParser::SubsettingsContext *ctx) override;

    void enterSubsets(KerMLParser::SubsetsContext *ctx) override;

    void exitSubsets(KerMLParser::SubsetsContext *ctx) override;

    void enterReferences(KerMLParser::ReferencesContext *ctx) override;

    void exitReferences(KerMLParser::ReferencesContext *ctx) override;

    void enterRedefinitions(KerMLParser::RedefinitionsContext *ctx) override;

    void exitRedefinitions(KerMLParser::RedefinitionsContext *ctx) override;

    void enterRedefines(KerMLParser::RedefinesContext *ctx) override;

    void exitRedefines(KerMLParser::RedefinesContext *ctx) override;

    void enterFeature_typing(KerMLParser::Feature_typingContext *ctx) override;

    void exitFeature_typing(KerMLParser::Feature_typingContext *ctx) override;

    void enterOwned_feature_typing(KerMLParser::Owned_feature_typingContext *ctx) override;

    void exitOwned_feature_typing(KerMLParser::Owned_feature_typingContext *ctx) override;

    void enterSubsetting(KerMLParser::SubsettingContext *ctx) override;

    void exitSubsetting(KerMLParser::SubsettingContext *ctx) override;

    void enterOwned_subsetting(KerMLParser::Owned_subsettingContext *ctx) override;

    void exitOwned_subsetting(KerMLParser::Owned_subsettingContext *ctx) override;

    void enterOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *ctx) override;

    void exitOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *ctx) override;

    void enterRedefinition(KerMLParser::RedefinitionContext *ctx) override;

    void exitRedefinition(KerMLParser::RedefinitionContext *ctx) override;

    void enterOwned_redefinition(KerMLParser::Owned_redefinitionContext *ctx) override;

    void exitOwned_redefinition(KerMLParser::Owned_redefinitionContext *ctx) override;

    void enterOwned_feature_chain(KerMLParser::Owned_feature_chainContext *ctx) override;

    void exitOwned_feature_chain(KerMLParser::Owned_feature_chainContext *ctx) override;

    void enterFeature_chain(KerMLParser::Feature_chainContext *ctx) override;

    void exitFeature_chain(KerMLParser::Feature_chainContext *ctx) override;

    void enterOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *ctx) override;

    void exitOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *ctx) override;

    void enterFeature_inverting(KerMLParser::Feature_invertingContext *ctx) override;

    void exitFeature_inverting(KerMLParser::Feature_invertingContext *ctx) override;

    void enterOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *ctx) override;

    void exitOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *ctx) override;

    void enterType_featuring(KerMLParser::Type_featuringContext *ctx) override;

    void exitType_featuring(KerMLParser::Type_featuringContext *ctx) override;

    void enterOwned_type_featuring(KerMLParser::Owned_type_featuringContext *ctx) override;

    void exitOwned_type_featuring(KerMLParser::Owned_type_featuringContext *ctx) override;

    void enterData_type(KerMLParser::Data_typeContext *ctx) override;

    void exitData_type(KerMLParser::Data_typeContext *ctx) override;

    void enterClass(KerMLParser::ClassContext *ctx) override;

    void exitClass(KerMLParser::ClassContext *ctx) override;

    void enterStructure(KerMLParser::StructureContext *ctx) override;

    void exitStructure(KerMLParser::StructureContext *ctx) override;

    void enterAssociation(KerMLParser::AssociationContext *ctx) override;

    void exitAssociation(KerMLParser::AssociationContext *ctx) override;

    void enterAssociation_structure(KerMLParser::Association_structureContext *ctx) override;

    void exitAssociation_structure(KerMLParser::Association_structureContext *ctx) override;

    void enterConnector(KerMLParser::ConnectorContext *ctx) override;

    void exitConnector(KerMLParser::ConnectorContext *ctx) override;

    void enterConnector_declaration(KerMLParser::Connector_declarationContext *ctx) override;

    void exitConnector_declaration(KerMLParser::Connector_declarationContext *ctx) override;

    void enterBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *ctx) override;

    void exitBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *ctx) override;

    void enterNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *ctx) override;

    void exitNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *ctx) override;

    void enterConnector_end_member(KerMLParser::Connector_end_memberContext *ctx) override;

    void exitConnector_end_member(KerMLParser::Connector_end_memberContext *ctx) override;

    void enterConnector_end(KerMLParser::Connector_endContext *ctx) override;

    void exitConnector_end(KerMLParser::Connector_endContext *ctx) override;

    void enterBinding_connector(KerMLParser::Binding_connectorContext *ctx) override;

    void exitBinding_connector(KerMLParser::Binding_connectorContext *ctx) override;

    void enterBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext *ctx) override;

    void exitBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext *ctx) override;

    void enterSuccession(KerMLParser::SuccessionContext *ctx) override;

    void exitSuccession(KerMLParser::SuccessionContext *ctx) override;

    void enterSuccession_declaration(KerMLParser::Succession_declarationContext *ctx) override;

    void exitSuccession_declaration(KerMLParser::Succession_declarationContext *ctx) override;

    void enterBehavior(KerMLParser::BehaviorContext *ctx) override;

    void exitBehavior(KerMLParser::BehaviorContext *ctx) override;

    void enterStep(KerMLParser::StepContext *ctx) override;

    void exitStep(KerMLParser::StepContext *ctx) override;

    void enterFunction(KerMLParser::FunctionContext *ctx) override;

    void exitFunction(KerMLParser::FunctionContext *ctx) override;

    void enterFunction_body(KerMLParser::Function_bodyContext *ctx) override;

    void exitFunction_body(KerMLParser::Function_bodyContext *ctx) override;

    void enterFunction_body_part(KerMLParser::Function_body_partContext *ctx) override;

    void exitFunction_body_part(KerMLParser::Function_body_partContext *ctx) override;

    void enterReturn_feature_member(KerMLParser::Return_feature_memberContext *ctx) override;

    void exitReturn_feature_member(KerMLParser::Return_feature_memberContext *ctx) override;

    void enterResult_expression_member(KerMLParser::Result_expression_memberContext *ctx) override;

    void exitResult_expression_member(KerMLParser::Result_expression_memberContext *ctx) override;

    void enterExpression(KerMLParser::ExpressionContext *ctx) override;

    void exitExpression(KerMLParser::ExpressionContext *ctx) override;

    void enterPredicate(KerMLParser::PredicateContext *ctx) override;

    void exitPredicate(KerMLParser::PredicateContext *ctx) override;

    void enterBoolean_expression(KerMLParser::Boolean_expressionContext *ctx) override;

    void exitBoolean_expression(KerMLParser::Boolean_expressionContext *ctx) override;

    void enterInvariant(KerMLParser::InvariantContext *ctx) override;

    void exitInvariant(KerMLParser::InvariantContext *ctx) override;

    void enterOwned_expression_reference_member(KerMLParser::Owned_expression_reference_memberContext *ctx) override;

    void exitOwned_expression_reference_member(KerMLParser::Owned_expression_reference_memberContext *ctx) override;

    void enterOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *ctx) override;

    void exitOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *ctx) override;

    void enterOwned_expression_member(KerMLParser::Owned_expression_memberContext *ctx) override;

    void exitOwned_expression_member(KerMLParser::Owned_expression_memberContext *ctx) override;

    void enterType_reference_member(KerMLParser::Type_reference_memberContext *ctx) override;

    void exitType_reference_member(KerMLParser::Type_reference_memberContext *ctx) override;

    void enterType_result_member(KerMLParser::Type_result_memberContext *ctx) override;

    void exitType_result_member(KerMLParser::Type_result_memberContext *ctx) override;

    void enterType_reference(KerMLParser::Type_referenceContext *ctx) override;

    void exitType_reference(KerMLParser::Type_referenceContext *ctx) override;

    void enterReference_typing(KerMLParser::Reference_typingContext *ctx) override;

    void exitReference_typing(KerMLParser::Reference_typingContext *ctx) override;

    void enterSequence_expression(KerMLParser::Sequence_expressionContext *ctx) override;

    void exitSequence_expression(KerMLParser::Sequence_expressionContext *ctx) override;

    void enterSequence_expression_list(KerMLParser::Sequence_expression_listContext *ctx) override;

    void exitSequence_expression_list(KerMLParser::Sequence_expression_listContext *ctx) override;

    void enterSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *ctx) override;

    void exitSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *ctx) override;

    void enterSequence_expression_list_member(KerMLParser::Sequence_expression_list_memberContext *ctx) override;

    void exitSequence_expression_list_member(KerMLParser::Sequence_expression_list_memberContext *ctx) override;

    void enterFunction_reference(KerMLParser::Function_referenceContext *ctx) override;

    void exitFunction_reference(KerMLParser::Function_referenceContext *ctx) override;

    void enterFeature_chain_member(KerMLParser::Feature_chain_memberContext *ctx) override;

    void exitFeature_chain_member(KerMLParser::Feature_chain_memberContext *ctx) override;

    void enterOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *ctx) override;

    void exitOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *ctx) override;

    void enterBase_expression(KerMLParser::Base_expressionContext *ctx) override;

    void exitBase_expression(KerMLParser::Base_expressionContext *ctx) override;

    void enterNull_expression(KerMLParser::Null_expressionContext *ctx) override;

    void exitNull_expression(KerMLParser::Null_expressionContext *ctx) override;

    void enterFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *ctx) override;

    void exitFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *ctx) override;

    void enterFeature_reference_member(KerMLParser::Feature_reference_memberContext *ctx) override;

    void exitFeature_reference_member(KerMLParser::Feature_reference_memberContext *ctx) override;

    void enterFeature_reference(KerMLParser::Feature_referenceContext *ctx) override;

    void exitFeature_reference(KerMLParser::Feature_referenceContext *ctx) override;

    void enterMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *ctx) override;

    void exitMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *ctx) override;

    void enterInvocation_expression(KerMLParser::Invocation_expressionContext *ctx) override;

    void exitInvocation_expression(KerMLParser::Invocation_expressionContext *ctx) override;

    void enterInternal_invocation_expression(KerMLParser::Internal_invocation_expressionContext *ctx) override;

    void exitInternal_invocation_expression(KerMLParser::Internal_invocation_expressionContext *ctx) override;

    void enterArgument_list(KerMLParser::Argument_listContext *ctx) override;

    void exitArgument_list(KerMLParser::Argument_listContext *ctx) override;

    void enterPositional_argument_list(KerMLParser::Positional_argument_listContext *ctx) override;

    void exitPositional_argument_list(KerMLParser::Positional_argument_listContext *ctx) override;

    void enterNamed_argument_list(KerMLParser::Named_argument_listContext *ctx) override;

    void exitNamed_argument_list(KerMLParser::Named_argument_listContext *ctx) override;

    void enterNamed_argument_member(KerMLParser::Named_argument_memberContext *ctx) override;

    void exitNamed_argument_member(KerMLParser::Named_argument_memberContext *ctx) override;

    void enterNamed_argument(KerMLParser::Named_argumentContext *ctx) override;

    void exitNamed_argument(KerMLParser::Named_argumentContext *ctx) override;

    void enterParameter_redefinition(KerMLParser::Parameter_redefinitionContext *ctx) override;

    void exitParameter_redefinition(KerMLParser::Parameter_redefinitionContext *ctx) override;

    void enterBody_expression(KerMLParser::Body_expressionContext *ctx) override;

    void exitBody_expression(KerMLParser::Body_expressionContext *ctx) override;

    void enterExpression_body_member(KerMLParser::Expression_body_memberContext *ctx) override;

    void exitExpression_body_member(KerMLParser::Expression_body_memberContext *ctx) override;

    void enterExpression_body(KerMLParser::Expression_bodyContext *ctx) override;

    void exitExpression_body(KerMLParser::Expression_bodyContext *ctx) override;

    void enterLiteral_expression(KerMLParser::Literal_expressionContext *ctx) override;

    void exitLiteral_expression(KerMLParser::Literal_expressionContext *ctx) override;

    void enterLiteral_boolean(KerMLParser::Literal_booleanContext *ctx) override;

    void exitLiteral_boolean(KerMLParser::Literal_booleanContext *ctx) override;

    void enterBoolean_value(KerMLParser::Boolean_valueContext *ctx) override;

    void exitBoolean_value(KerMLParser::Boolean_valueContext *ctx) override;

    void enterLiteral_string(KerMLParser::Literal_stringContext *ctx) override;

    void exitLiteral_string(KerMLParser::Literal_stringContext *ctx) override;

    void enterLiteral_integer(KerMLParser::Literal_integerContext *ctx) override;

    void exitLiteral_integer(KerMLParser::Literal_integerContext *ctx) override;

    void enterLiteral_real(KerMLParser::Literal_realContext *ctx) override;

    void exitLiteral_real(KerMLParser::Literal_realContext *ctx) override;

    void enterReal_value(KerMLParser::Real_valueContext *ctx) override;

    void exitReal_value(KerMLParser::Real_valueContext *ctx) override;

    void enterLiteral_infinity(KerMLParser::Literal_infinityContext *ctx) override;

    void exitLiteral_infinity(KerMLParser::Literal_infinityContext *ctx) override;

    void enterInteraction(KerMLParser::InteractionContext *ctx) override;

    void exitInteraction(KerMLParser::InteractionContext *ctx) override;

    void enterItem_flow(KerMLParser::Item_flowContext *ctx) override;

    void exitItem_flow(KerMLParser::Item_flowContext *ctx) override;

    void enterSuccession_item_flow(KerMLParser::Succession_item_flowContext *ctx) override;

    void exitSuccession_item_flow(KerMLParser::Succession_item_flowContext *ctx) override;

    void enterItem_flow_declaration(KerMLParser::Item_flow_declarationContext *ctx) override;

    void exitItem_flow_declaration(KerMLParser::Item_flow_declarationContext *ctx) override;

    void enterItem_feature_member(KerMLParser::Item_feature_memberContext *ctx) override;

    void exitItem_feature_member(KerMLParser::Item_feature_memberContext *ctx) override;

    void enterItem_feature(KerMLParser::Item_featureContext *ctx) override;

    void exitItem_feature(KerMLParser::Item_featureContext *ctx) override;

    void enterItem_feature_specialization_part(KerMLParser::Item_feature_specialization_partContext *ctx) override;

    void exitItem_feature_specialization_part(KerMLParser::Item_feature_specialization_partContext *ctx) override;

    void enterItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *ctx) override;

    void exitItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *ctx) override;

    void enterItem_flow_end(KerMLParser::Item_flow_endContext *ctx) override;

    void exitItem_flow_end(KerMLParser::Item_flow_endContext *ctx) override;

    void enterItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *ctx) override;

    void exitItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *ctx) override;

    void enterItem_flow_feature(KerMLParser::Item_flow_featureContext *ctx) override;

    void exitItem_flow_feature(KerMLParser::Item_flow_featureContext *ctx) override;

    void enterItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *ctx) override;

    void exitItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *ctx) override;

    void enterValue_part(KerMLParser::Value_partContext *ctx) override;

    void exitValue_part(KerMLParser::Value_partContext *ctx) override;

    void enterFeature_value(KerMLParser::Feature_valueContext *ctx) override;

    void exitFeature_value(KerMLParser::Feature_valueContext *ctx) override;

    void enterFeature_assignment(KerMLParser::Feature_assignmentContext *ctx) override;

    void exitFeature_assignment(KerMLParser::Feature_assignmentContext *ctx) override;

    void enterMultiplicity(KerMLParser::MultiplicityContext *ctx) override;

    void exitMultiplicity(KerMLParser::MultiplicityContext *ctx) override;

    void enterMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *ctx) override;

    void exitMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *ctx) override;

    void enterMultiplicity_range(KerMLParser::Multiplicity_rangeContext *ctx) override;

    void exitMultiplicity_range(KerMLParser::Multiplicity_rangeContext *ctx) override;

    void enterOwned_multiplicity(KerMLParser::Owned_multiplicityContext *ctx) override;

    void exitOwned_multiplicity(KerMLParser::Owned_multiplicityContext *ctx) override;

    void enterOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *ctx) override;

    void exitOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *ctx) override;

    void enterMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext *ctx) override;

    void exitMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext *ctx) override;

    void enterMultiplicity_expression_member(KerMLParser::Multiplicity_expression_memberContext *ctx) override;

    void exitMultiplicity_expression_member(KerMLParser::Multiplicity_expression_memberContext *ctx) override;

    void enterInternal_multiplicity_expression_member(
            KerMLParser::Internal_multiplicity_expression_memberContext *ctx) override;

    void exitInternal_multiplicity_expression_member(
            KerMLParser::Internal_multiplicity_expression_memberContext *ctx) override;

    void enterMetaclass(KerMLParser::MetaclassContext *ctx) override;

    void exitMetaclass(KerMLParser::MetaclassContext *ctx) override;

    void enterPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *ctx) override;

    void exitPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *ctx) override;

    void enterPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *ctx) override;

    void exitPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *ctx) override;

    void enterPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *ctx) override;

    void exitPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *ctx) override;

    void enterMetadata_feature(KerMLParser::Metadata_featureContext *ctx) override;

    void exitMetadata_feature(KerMLParser::Metadata_featureContext *ctx) override;

    void enterMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *ctx) override;

    void exitMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *ctx) override;

    void enterMetadata_body(KerMLParser::Metadata_bodyContext *ctx) override;

    void exitMetadata_body(KerMLParser::Metadata_bodyContext *ctx) override;

    void enterMetadata_body_element(KerMLParser::Metadata_body_elementContext *ctx) override;

    void exitMetadata_body_element(KerMLParser::Metadata_body_elementContext *ctx) override;

    void enterMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *ctx) override;

    void exitMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *ctx) override;

    void enterMetadata_body_feature(KerMLParser::Metadata_body_featureContext *ctx) override;

    void exitMetadata_body_feature(KerMLParser::Metadata_body_featureContext *ctx) override;

    void enterPackage(KerMLParser::PackageContext *ctx) override;

    void exitPackage(KerMLParser::PackageContext *ctx) override;

    void enterLibrary_package(KerMLParser::Library_packageContext *ctx) override;

    void exitLibrary_package(KerMLParser::Library_packageContext *ctx) override;

    void enterPackage_declaration(KerMLParser::Package_declarationContext *ctx) override;

    void exitPackage_declaration(KerMLParser::Package_declarationContext *ctx) override;

    void enterPackage_body(KerMLParser::Package_bodyContext *ctx) override;

    void exitPackage_body(KerMLParser::Package_bodyContext *ctx) override;

    void enterElement_filter_member(KerMLParser::Element_filter_memberContext *ctx) override;

    void exitElement_filter_member(KerMLParser::Element_filter_memberContext *ctx) override;

    void enterMeta_assignment(KerMLParser::Meta_assignmentContext *ctx) override;

    void exitMeta_assignment(KerMLParser::Meta_assignmentContext *ctx) override;

    void enterComment(KerMLParser::CommentContext *ctx) override;

    void exitComment(KerMLParser::CommentContext *ctx) override;

    std::vector<std::shared_ptr<KerML::Entities::Element>> getElements();

    /// Moves out everything recorded for name resolution (pending references, imports, aliases, visibilities).
    /// Names are not resolved by the listener; a SysMLv2::Files::Workspace resolves them.
    SysMLv2::Files::ResolutionData takeResolutionData();

private:
    void attachExpression(const std::shared_ptr<KerML::Entities::Expression>& expression);
    void finishOperatorExpression(const std::string& operatorName);
    void finishMembership(KerMLParser::Member_prefixContext *prefix, bool owningOnly = false);
    void applyIdentification(KerMLParser::IdentificationContext *idCtx, const std::shared_ptr<KerML::Entities::Element>& elem);
    void recordImport(const std::shared_ptr<KerML::Entities::Element>& importElement, antlr4::ParserRuleContext *importCtx,
                      const std::string& target, bool star, bool recursive, bool importAll, KerML::Entities::VisibilityKind visibility,
                      const std::shared_ptr<KerML::Entities::Membership>& importedMembership = nullptr);
    KerML::Entities::VisibilityKind importVisibility(KerMLParser::Visibility_indicatorContext *indicator) const;
    std::shared_ptr<KerML::Entities::Type> typeReference(const std::string& name, const std::shared_ptr<KerML::Entities::Element>& context,
                                                         bool relativeToOwner, antlr4::ParserRuleContext *position,
                                                         std::function<void(const std::shared_ptr<KerML::Entities::Type>&)> patch);
    std::shared_ptr<KerML::Entities::Feature> featureReference(const std::string& name, const std::shared_ptr<KerML::Entities::Element>& context,
                                                               bool relativeToOwner, antlr4::ParserRuleContext *position,
                                                               std::function<void(const std::shared_ptr<KerML::Entities::Feature>&)> patch);
    /// Records a general type / feature of @p specific (role Generalization or Redefinition) whose relationship is patched by @p patch.
    void generalReference(const std::shared_ptr<KerML::Entities::Element>& placeholder, const std::string& name, SysMLv2::Files::ReferenceKind kind,
                          SysMLv2::Files::ReferenceRole role, const std::shared_ptr<KerML::Entities::Element>& specific,
                          antlr4::ParserRuleContext *position, std::function<void(const std::shared_ptr<KerML::Entities::Element>&)> patch);
    SysMLv2::Files::ReferenceRecorder Recorder;
    /// The memberships that member rules stand for (see SysMLv2::Files::buildOwnership) and the member rules that are being walked.
    SysMLv2::Files::MembershipKinds OwnershipKinds;
    std::vector<SysMLv2::Files::MemberMark> MemberMarks;
    std::vector<std::shared_ptr<KerML::Entities::Element>> Elements;
    std::stack<std::shared_ptr<KerML::Entities::Element>> ParentStack;
};

