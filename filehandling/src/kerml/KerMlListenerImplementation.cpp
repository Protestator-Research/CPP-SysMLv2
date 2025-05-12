//
// Created by Moritz Herzog on 09.05.25.
//

#include "KerMlListenerImplementation.h"
#include "root/dependencies/Dependency.h"

KerMLListenerImplementation::~KerMLListenerImplementation() {

}

KerMLListenerImplementation::KerMLListenerImplementation() {

}

void KerMLListenerImplementation::enterStart(KerMLParser::StartContext *) {}
void KerMLListenerImplementation::exitStart(KerMLParser::StartContext *) {}
void KerMLListenerImplementation::enterStartRule(KerMLParser::StartRuleContext *) {}
void KerMLListenerImplementation::exitStartRule(KerMLParser::StartRuleContext *) {}
void KerMLListenerImplementation::enterElements(KerMLParser::ElementsContext *ctx) {

}

void KerMLListenerImplementation::exitElements(KerMLParser::ElementsContext *ctx) {

}

void KerMLListenerImplementation::enterIdentification(KerMLParser::IdentificationContext *ctx) {}
void KerMLListenerImplementation::exitIdentification(KerMLParser::IdentificationContext *ctx) {}

void KerMLListenerImplementation::enterRelationship_body(KerMLParser::Relationship_bodyContext *ctx) {

}

void KerMLListenerImplementation::exitRelationship_body(KerMLParser::Relationship_bodyContext *ctx) {

}

void KerMLListenerImplementation::enterRelationship_onwed_elements(KerMLParser::Relationship_onwed_elementsContext *ctx) {

}

void KerMLListenerImplementation::exitRelationship_onwed_elements(KerMLParser::Relationship_onwed_elementsContext *ctx) {

}

void KerMLListenerImplementation::enterRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *ctx) {

}

void KerMLListenerImplementation::exitRelationship_owned_element(KerMLParser::Relationship_owned_elementContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_related_element(KerMLParser::Owned_related_elementContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_related_element(KerMLParser::Owned_related_elementContext *ctx) {

}

void KerMLListenerImplementation::enterDependency(KerMLParser::DependencyContext *ctx) {
    auto& dependency = new KerML::Entities::Dependency();
}

void KerMLListenerImplementation::exitDependency(KerMLParser::DependencyContext *ctx) {

}

void KerMLListenerImplementation::enterAnnotation(KerMLParser::AnnotationContext *ctx) {

}

void KerMLListenerImplementation::exitAnnotation(KerMLParser::AnnotationContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_annotation(KerMLParser::Owned_annotationContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_annotation(KerMLParser::Owned_annotationContext *ctx) {

}

void KerMLListenerImplementation::enterAnnotating_element(KerMLParser::Annotating_elementContext *ctx) {

}

void KerMLListenerImplementation::exitAnnotating_element(KerMLParser::Annotating_elementContext *ctx) {

}

void KerMLListenerImplementation::enterComment(KerMLParser::CommentContext *ctx) {

}

void KerMLListenerImplementation::exitComment(KerMLParser::CommentContext *ctx) {

}

void KerMLListenerImplementation::enterDocumentation(KerMLParser::DocumentationContext *ctx) {

}

void KerMLListenerImplementation::exitDocumentation(KerMLParser::DocumentationContext *ctx) {

}

void KerMLListenerImplementation::enterTextual_representation(KerMLParser::Textual_representationContext *ctx) {

}

void KerMLListenerImplementation::exitTextual_representation(KerMLParser::Textual_representationContext *ctx) {

}

void KerMLListenerImplementation::enterRoot_namespace(KerMLParser::Root_namespaceContext *ctx) {

}

void KerMLListenerImplementation::exitRoot_namespace(KerMLParser::Root_namespaceContext *ctx) {

}

void KerMLListenerImplementation::enterNamespace(KerMLParser::NamespaceContext *ctx) {

}

void KerMLListenerImplementation::exitNamespace(KerMLParser::NamespaceContext *ctx) {

}

void KerMLListenerImplementation::enterNamespace_declaration(KerMLParser::Namespace_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitNamespace_declaration(KerMLParser::Namespace_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterNamespace_body(KerMLParser::Namespace_bodyContext *ctx) {

}

void KerMLListenerImplementation::exitNamespace_body(KerMLParser::Namespace_bodyContext *ctx) {

}

void KerMLListenerImplementation::enterNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *ctx) {

}

void KerMLListenerImplementation::exitNamespace_body_elements(KerMLParser::Namespace_body_elementsContext *ctx) {

}

void KerMLListenerImplementation::enterNamespace_body_element(KerMLParser::Namespace_body_elementContext *ctx) {

}

void KerMLListenerImplementation::exitNamespace_body_element(KerMLParser::Namespace_body_elementContext *ctx) {

}

void KerMLListenerImplementation::enterMember_prefix(KerMLParser::Member_prefixContext *ctx) {

}

void KerMLListenerImplementation::exitMember_prefix(KerMLParser::Member_prefixContext *ctx) {

}

void KerMLListenerImplementation::enterVisibility_indicator(KerMLParser::Visibility_indicatorContext *ctx) {

}

void KerMLListenerImplementation::exitVisibility_indicator(KerMLParser::Visibility_indicatorContext *ctx) {

}

void KerMLListenerImplementation::enterNamespace_member(KerMLParser::Namespace_memberContext *ctx) {

}

void KerMLListenerImplementation::exitNamespace_member(KerMLParser::Namespace_memberContext *ctx) {

}

void KerMLListenerImplementation::enterNon_feature_member(KerMLParser::Non_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::exitNon_feature_member(KerMLParser::Non_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::enterNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::exitNamespace_feature_member(KerMLParser::Namespace_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::enterAlias_member(KerMLParser::Alias_memberContext *ctx) {

}

void KerMLListenerImplementation::exitAlias_member(KerMLParser::Alias_memberContext *ctx) {

}

void KerMLListenerImplementation::enterQualified_name(KerMLParser::Qualified_nameContext *ctx) {

}

void KerMLListenerImplementation::exitQualified_name(KerMLParser::Qualified_nameContext *ctx) {

}

void KerMLListenerImplementation::enterNamespace_import(KerMLParser::Namespace_importContext *ctx) {

}

void KerMLListenerImplementation::exitNamespace_import(KerMLParser::Namespace_importContext *ctx) {

}

void KerMLListenerImplementation::enterImport_declaration(KerMLParser::Import_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitImport_declaration(KerMLParser::Import_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterMembership_import(KerMLParser::Membership_importContext *ctx) {

}

void KerMLListenerImplementation::exitMembership_import(KerMLParser::Membership_importContext *ctx) {

}

void KerMLListenerImplementation::enterFilter_package(KerMLParser::Filter_packageContext *ctx) {

}

void KerMLListenerImplementation::exitFilter_package(KerMLParser::Filter_packageContext *ctx) {

}

void KerMLListenerImplementation::enterFilter_package_member(KerMLParser::Filter_package_memberContext *ctx) {

}

void KerMLListenerImplementation::exitFilter_package_member(KerMLParser::Filter_package_memberContext *ctx) {

}

void KerMLListenerImplementation::enterElement(KerMLParser::ElementContext *ctx) {

}

void KerMLListenerImplementation::exitElement(KerMLParser::ElementContext *ctx) {

}

void KerMLListenerImplementation::enterNon_feature_element(KerMLParser::Non_feature_elementContext *ctx) {

}

void KerMLListenerImplementation::exitNon_feature_element(KerMLParser::Non_feature_elementContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_element(KerMLParser::Feature_elementContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_element(KerMLParser::Feature_elementContext *ctx) {

}

void KerMLListenerImplementation::enterAdditional_options(KerMLParser::Additional_optionsContext *ctx) {

}

void KerMLListenerImplementation::exitAdditional_options(KerMLParser::Additional_optionsContext *ctx) {

}

void KerMLListenerImplementation::enterType(KerMLParser::TypeContext *ctx) {

}

void KerMLListenerImplementation::exitType(KerMLParser::TypeContext *ctx) {

}

void KerMLListenerImplementation::enterType_prefix(KerMLParser::Type_prefixContext *ctx) {

}

void KerMLListenerImplementation::exitType_prefix(KerMLParser::Type_prefixContext *ctx) {

}

void KerMLListenerImplementation::enterType_declaration(KerMLParser::Type_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitType_declaration(KerMLParser::Type_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterSpecialization_part(KerMLParser::Specialization_partContext *ctx) {

}

void KerMLListenerImplementation::exitSpecialization_part(KerMLParser::Specialization_partContext *ctx) {

}

void KerMLListenerImplementation::enterConjugation_part(KerMLParser::Conjugation_partContext *ctx) {

}

void KerMLListenerImplementation::exitConjugation_part(KerMLParser::Conjugation_partContext *ctx) {

}

void KerMLListenerImplementation::enterType_relationship_part(KerMLParser::Type_relationship_partContext *ctx) {

}

void KerMLListenerImplementation::exitType_relationship_part(KerMLParser::Type_relationship_partContext *ctx) {

}

void KerMLListenerImplementation::enterDisjoining_part(KerMLParser::Disjoining_partContext *ctx) {

}

void KerMLListenerImplementation::exitDisjoining_part(KerMLParser::Disjoining_partContext *ctx) {

}

void KerMLListenerImplementation::enterUnioning_part(KerMLParser::Unioning_partContext *ctx) {

}

void KerMLListenerImplementation::exitUnioning_part(KerMLParser::Unioning_partContext *ctx) {

}

void KerMLListenerImplementation::enterIntersecting_part(KerMLParser::Intersecting_partContext *ctx) {

}

void KerMLListenerImplementation::exitIntersecting_part(KerMLParser::Intersecting_partContext *ctx) {

}

void KerMLListenerImplementation::enterDifferencing_part(KerMLParser::Differencing_partContext *ctx) {

}

void KerMLListenerImplementation::exitDifferencing_part(KerMLParser::Differencing_partContext *ctx) {

}

void KerMLListenerImplementation::enterType_body(KerMLParser::Type_bodyContext *ctx) {

}

void KerMLListenerImplementation::exitType_body(KerMLParser::Type_bodyContext *ctx) {

}

void KerMLListenerImplementation::enterType_body_elements(KerMLParser::Type_body_elementsContext *ctx) {

}

void KerMLListenerImplementation::exitType_body_elements(KerMLParser::Type_body_elementsContext *ctx) {

}

void KerMLListenerImplementation::enterType_body_element(KerMLParser::Type_body_elementContext *ctx) {

}

void KerMLListenerImplementation::exitType_body_element(KerMLParser::Type_body_elementContext *ctx) {

}

void KerMLListenerImplementation::enterSpecialization(KerMLParser::SpecializationContext *ctx) {

}

void KerMLListenerImplementation::exitSpecialization(KerMLParser::SpecializationContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_specialization(KerMLParser::Owned_specializationContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_specialization(KerMLParser::Owned_specializationContext *ctx) {

}

void KerMLListenerImplementation::enterSpecific_type(KerMLParser::Specific_typeContext *ctx) {

}

void KerMLListenerImplementation::exitSpecific_type(KerMLParser::Specific_typeContext *ctx) {

}

void KerMLListenerImplementation::enterGeneral_type(KerMLParser::General_typeContext *ctx) {

}

void KerMLListenerImplementation::exitGeneral_type(KerMLParser::General_typeContext *ctx) {

}

void KerMLListenerImplementation::enterConjunction(KerMLParser::ConjunctionContext *ctx) {

}

void KerMLListenerImplementation::exitConjunction(KerMLParser::ConjunctionContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_conjugation(KerMLParser::Owned_conjugationContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_conjugation(KerMLParser::Owned_conjugationContext *ctx) {

}

void KerMLListenerImplementation::enterDisjoining(KerMLParser::DisjoiningContext *ctx) {

}

void KerMLListenerImplementation::exitDisjoining(KerMLParser::DisjoiningContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_disjoining(KerMLParser::Owned_disjoiningContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_disjoining(KerMLParser::Owned_disjoiningContext *ctx) {

}

void KerMLListenerImplementation::enterUnioning(KerMLParser::UnioningContext *ctx) {

}

void KerMLListenerImplementation::exitUnioning(KerMLParser::UnioningContext *ctx) {

}

void KerMLListenerImplementation::enterIntersecting(KerMLParser::IntersectingContext *ctx) {

}

void KerMLListenerImplementation::exitIntersecting(KerMLParser::IntersectingContext *ctx) {

}

void KerMLListenerImplementation::enterDifferencing(KerMLParser::DifferencingContext *ctx) {

}

void KerMLListenerImplementation::exitDifferencing(KerMLParser::DifferencingContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_member(KerMLParser::Feature_memberContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_member(KerMLParser::Feature_memberContext *ctx) {

}

void KerMLListenerImplementation::enterType_feature_member(KerMLParser::Type_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::exitType_feature_member(KerMLParser::Type_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_feature_member(KerMLParser::Owned_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_feature_member(KerMLParser::Owned_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::enterClassifier(KerMLParser::ClassifierContext *ctx) {

}

void KerMLListenerImplementation::exitClassifier(KerMLParser::ClassifierContext *ctx) {

}

void KerMLListenerImplementation::enterClassifier_declaration(KerMLParser::Classifier_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitClassifier_declaration(KerMLParser::Classifier_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterSuperclassing_part(KerMLParser::Superclassing_partContext *ctx) {

}

void KerMLListenerImplementation::exitSuperclassing_part(KerMLParser::Superclassing_partContext *ctx) {

}

void KerMLListenerImplementation::enterSubclassification(KerMLParser::SubclassificationContext *ctx) {

}

void KerMLListenerImplementation::exitSubclassification(KerMLParser::SubclassificationContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_subclassification(KerMLParser::Owned_subclassificationContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_subclassification(KerMLParser::Owned_subclassificationContext *ctx) {

}

void KerMLListenerImplementation::enterFeature(KerMLParser::FeatureContext *ctx) {

}

void KerMLListenerImplementation::exitFeature(KerMLParser::FeatureContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_prefix(KerMLParser::Feature_prefixContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_prefix(KerMLParser::Feature_prefixContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_direction(KerMLParser::Feature_directionContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_direction(KerMLParser::Feature_directionContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_declaration(KerMLParser::Feature_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_declaration(KerMLParser::Feature_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_identification(KerMLParser::Feature_identificationContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_identification(KerMLParser::Feature_identificationContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_relationship_part(KerMLParser::Feature_relationship_partContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_relationship_part(KerMLParser::Feature_relationship_partContext *ctx) {

}

void KerMLListenerImplementation::enterChaining_part(KerMLParser::Chaining_partContext *ctx) {

}

void KerMLListenerImplementation::exitChaining_part(KerMLParser::Chaining_partContext *ctx) {

}

void KerMLListenerImplementation::enterInverting_part(KerMLParser::Inverting_partContext *ctx) {

}

void KerMLListenerImplementation::exitInverting_part(KerMLParser::Inverting_partContext *ctx) {

}

void KerMLListenerImplementation::enterType_featuring_part(KerMLParser::Type_featuring_partContext *ctx) {

}

void KerMLListenerImplementation::exitType_featuring_part(KerMLParser::Type_featuring_partContext *ctx) {

}

void
KerMLListenerImplementation::enterFeature_specialization_part(KerMLParser::Feature_specialization_partContext *ctx) {

}

void
KerMLListenerImplementation::exitFeature_specialization_part(KerMLParser::Feature_specialization_partContext *ctx) {

}

void KerMLListenerImplementation::enterMultiplicity_part(KerMLParser::Multiplicity_partContext *ctx) {

}

void KerMLListenerImplementation::exitMultiplicity_part(KerMLParser::Multiplicity_partContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_specilization(KerMLParser::Feature_specilizationContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_specilization(KerMLParser::Feature_specilizationContext *ctx) {

}

void KerMLListenerImplementation::enterTypings(KerMLParser::TypingsContext *ctx) {

}

void KerMLListenerImplementation::exitTypings(KerMLParser::TypingsContext *ctx) {

}

void KerMLListenerImplementation::enterTyped_by(KerMLParser::Typed_byContext *ctx) {

}

void KerMLListenerImplementation::exitTyped_by(KerMLParser::Typed_byContext *ctx) {

}

void KerMLListenerImplementation::enterSubsettings(KerMLParser::SubsettingsContext *ctx) {

}

void KerMLListenerImplementation::exitSubsettings(KerMLParser::SubsettingsContext *ctx) {

}

void KerMLListenerImplementation::enterSubsets(KerMLParser::SubsetsContext *ctx) {

}

void KerMLListenerImplementation::exitSubsets(KerMLParser::SubsetsContext *ctx) {

}

void KerMLListenerImplementation::enterReferences(KerMLParser::ReferencesContext *ctx) {

}

void KerMLListenerImplementation::exitReferences(KerMLParser::ReferencesContext *ctx) {

}

void KerMLListenerImplementation::enterRedefinitions(KerMLParser::RedefinitionsContext *ctx) {

}

void KerMLListenerImplementation::exitRedefinitions(KerMLParser::RedefinitionsContext *ctx) {

}

void KerMLListenerImplementation::enterRedefines(KerMLParser::RedefinesContext *ctx) {

}

void KerMLListenerImplementation::exitRedefines(KerMLParser::RedefinesContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_typing(KerMLParser::Feature_typingContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_typing(KerMLParser::Feature_typingContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_feature_typing(KerMLParser::Owned_feature_typingContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_feature_typing(KerMLParser::Owned_feature_typingContext *ctx) {

}

void KerMLListenerImplementation::enterSubsetting(KerMLParser::SubsettingContext *ctx) {

}

void KerMLListenerImplementation::exitSubsetting(KerMLParser::SubsettingContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_subsetting(KerMLParser::Owned_subsettingContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_subsetting(KerMLParser::Owned_subsettingContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_reference_subsetting(KerMLParser::Owned_reference_subsettingContext *ctx) {

}

void KerMLListenerImplementation::enterRedefinition(KerMLParser::RedefinitionContext *ctx) {

}

void KerMLListenerImplementation::exitRedefinition(KerMLParser::RedefinitionContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_redefinition(KerMLParser::Owned_redefinitionContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_redefinition(KerMLParser::Owned_redefinitionContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_feature_chain(KerMLParser::Owned_feature_chainContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_feature_chain(KerMLParser::Owned_feature_chainContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_chain(KerMLParser::Feature_chainContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_chain(KerMLParser::Feature_chainContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_feature_chaining(KerMLParser::Owned_feature_chainingContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_inverting(KerMLParser::Feature_invertingContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_inverting(KerMLParser::Feature_invertingContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_feature_inverting(KerMLParser::Owned_feature_invertingContext *ctx) {

}

void KerMLListenerImplementation::enterType_featuring(KerMLParser::Type_featuringContext *ctx) {

}

void KerMLListenerImplementation::exitType_featuring(KerMLParser::Type_featuringContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_type_featuring(KerMLParser::Owned_type_featuringContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_type_featuring(KerMLParser::Owned_type_featuringContext *ctx) {

}

void KerMLListenerImplementation::enterData_type(KerMLParser::Data_typeContext *ctx) {

}

void KerMLListenerImplementation::exitData_type(KerMLParser::Data_typeContext *ctx) {

}

void KerMLListenerImplementation::enterClass(KerMLParser::ClassContext *ctx) {

}

void KerMLListenerImplementation::exitClass(KerMLParser::ClassContext *ctx) {

}

void KerMLListenerImplementation::enterStructure(KerMLParser::StructureContext *ctx) {

}

void KerMLListenerImplementation::exitStructure(KerMLParser::StructureContext *ctx) {

}

void KerMLListenerImplementation::enterAssociation(KerMLParser::AssociationContext *ctx) {

}

void KerMLListenerImplementation::exitAssociation(KerMLParser::AssociationContext *ctx) {

}

void KerMLListenerImplementation::enterAssociation_structure(KerMLParser::Association_structureContext *ctx) {

}

void KerMLListenerImplementation::exitAssociation_structure(KerMLParser::Association_structureContext *ctx) {

}

void KerMLListenerImplementation::enterConnector(KerMLParser::ConnectorContext *ctx) {

}

void KerMLListenerImplementation::exitConnector(KerMLParser::ConnectorContext *ctx) {

}

void KerMLListenerImplementation::enterConnector_declaration(KerMLParser::Connector_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitConnector_declaration(KerMLParser::Connector_declarationContext *ctx) {

}

void
KerMLListenerImplementation::enterBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *ctx) {

}

void
KerMLListenerImplementation::exitBinary_connector_declaration(KerMLParser::Binary_connector_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitNary_connector_declaration(KerMLParser::Nary_connector_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterConnector_end_member(KerMLParser::Connector_end_memberContext *ctx) {

}

void KerMLListenerImplementation::exitConnector_end_member(KerMLParser::Connector_end_memberContext *ctx) {

}

void KerMLListenerImplementation::enterConnector_end(KerMLParser::Connector_endContext *ctx) {

}

void KerMLListenerImplementation::exitConnector_end(KerMLParser::Connector_endContext *ctx) {

}

void KerMLListenerImplementation::enterBinding_connector(KerMLParser::Binding_connectorContext *ctx) {

}

void KerMLListenerImplementation::exitBinding_connector(KerMLParser::Binding_connectorContext *ctx) {

}

void KerMLListenerImplementation::enterBinding_connector_declaration(
        KerMLParser::Binding_connector_declarationContext *ctx) {

}

void
KerMLListenerImplementation::exitBinding_connector_declaration(KerMLParser::Binding_connector_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterSuccession(KerMLParser::SuccessionContext *ctx) {

}

void KerMLListenerImplementation::exitSuccession(KerMLParser::SuccessionContext *ctx) {

}

void KerMLListenerImplementation::enterSuccession_declaration(KerMLParser::Succession_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitSuccession_declaration(KerMLParser::Succession_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterBehavior(KerMLParser::BehaviorContext *ctx) {

}

void KerMLListenerImplementation::exitBehavior(KerMLParser::BehaviorContext *ctx) {

}

void KerMLListenerImplementation::enterStep(KerMLParser::StepContext *ctx) {

}

void KerMLListenerImplementation::exitStep(KerMLParser::StepContext *ctx) {

}

void KerMLListenerImplementation::enterFunction(KerMLParser::FunctionContext *ctx) {

}

void KerMLListenerImplementation::exitFunction(KerMLParser::FunctionContext *ctx) {

}

void KerMLListenerImplementation::enterFunction_body(KerMLParser::Function_bodyContext *ctx) {

}

void KerMLListenerImplementation::exitFunction_body(KerMLParser::Function_bodyContext *ctx) {

}

void KerMLListenerImplementation::enterFunction_body_part(KerMLParser::Function_body_partContext *ctx) {

}

void KerMLListenerImplementation::exitFunction_body_part(KerMLParser::Function_body_partContext *ctx) {

}

void KerMLListenerImplementation::enterReturn_feature_member(KerMLParser::Return_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::exitReturn_feature_member(KerMLParser::Return_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::enterResult_expression_member(KerMLParser::Result_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::exitResult_expression_member(KerMLParser::Result_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::enterExpression(KerMLParser::ExpressionContext *ctx) {

}

void KerMLListenerImplementation::exitExpression(KerMLParser::ExpressionContext *ctx) {

}

void KerMLListenerImplementation::enterPredicate(KerMLParser::PredicateContext *ctx) {

}

void KerMLListenerImplementation::exitPredicate(KerMLParser::PredicateContext *ctx) {

}

void KerMLListenerImplementation::enterBoolean_expression(KerMLParser::Boolean_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitBoolean_expression(KerMLParser::Boolean_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterInvariant(KerMLParser::InvariantContext *ctx) {

}

void KerMLListenerImplementation::exitInvariant(KerMLParser::InvariantContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_expression_reference_member(
        KerMLParser::Owned_expression_reference_memberContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_expression_reference_member(
        KerMLParser::Owned_expression_reference_memberContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_expression_reference(KerMLParser::Owned_expression_referenceContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_expression_member(KerMLParser::Owned_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_expression_member(KerMLParser::Owned_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_expressions(KerMLParser::Owned_expressionsContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_expressions(KerMLParser::Owned_expressionsContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_expression(KerMLParser::Owned_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_expression(KerMLParser::Owned_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterEased_owned_expression(KerMLParser::Eased_owned_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitEased_owned_expression(KerMLParser::Eased_owned_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterConditional_expression(KerMLParser::Conditional_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitConditional_expression(KerMLParser::Conditional_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterConditional_binary_operator_expression(
        KerMLParser::Conditional_binary_operator_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitConditional_binary_operator_expression(
        KerMLParser::Conditional_binary_operator_expressionContext *ctx) {

}

void
KerMLListenerImplementation::enterConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext *ctx) {

}

void
KerMLListenerImplementation::exitConditional_binary_operator(KerMLParser::Conditional_binary_operatorContext *ctx) {

}

void KerMLListenerImplementation::enterBinary_operator_expression(KerMLParser::Binary_operator_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitBinary_operator_expression(KerMLParser::Binary_operator_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterBinary_operator(KerMLParser::Binary_operatorContext *ctx) {

}

void KerMLListenerImplementation::exitBinary_operator(KerMLParser::Binary_operatorContext *ctx) {

}

void KerMLListenerImplementation::enterUnary_operator_expression(KerMLParser::Unary_operator_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitUnary_operator_expression(KerMLParser::Unary_operator_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterUnary_operator(KerMLParser::Unary_operatorContext *ctx) {

}

void KerMLListenerImplementation::exitUnary_operator(KerMLParser::Unary_operatorContext *ctx) {

}

void KerMLListenerImplementation::enterClassification_expression(KerMLParser::Classification_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitClassification_expression(KerMLParser::Classification_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterClassification(KerMLParser::ClassificationContext *ctx) {

}

void KerMLListenerImplementation::exitClassification(KerMLParser::ClassificationContext *ctx) {

}

void
KerMLListenerImplementation::enterClassification_test_operator(KerMLParser::Classification_test_operatorContext *ctx) {

}

void
KerMLListenerImplementation::exitClassification_test_operator(KerMLParser::Classification_test_operatorContext *ctx) {

}

void KerMLListenerImplementation::enterCast_operator(KerMLParser::Cast_operatorContext *ctx) {

}

void KerMLListenerImplementation::exitCast_operator(KerMLParser::Cast_operatorContext *ctx) {

}

void KerMLListenerImplementation::enterMetaclassification_expression(
        KerMLParser::Metaclassification_expressionContext *ctx) {

}

void
KerMLListenerImplementation::exitMetaclassification_expression(KerMLParser::Metaclassification_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterArgument_member(KerMLParser::Argument_memberContext *ctx) {

}

void KerMLListenerImplementation::exitArgument_member(KerMLParser::Argument_memberContext *ctx) {

}

void KerMLListenerImplementation::enterArgument(KerMLParser::ArgumentContext *ctx) {

}

void KerMLListenerImplementation::exitArgument(KerMLParser::ArgumentContext *ctx) {

}

void KerMLListenerImplementation::enterArgument_value(KerMLParser::Argument_valueContext *ctx) {

}

void KerMLListenerImplementation::exitArgument_value(KerMLParser::Argument_valueContext *ctx) {

}

void KerMLListenerImplementation::enterArgument_expression_member(KerMLParser::Argument_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::exitArgument_expression_member(KerMLParser::Argument_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::enterArgument_expression(KerMLParser::Argument_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitArgument_expression(KerMLParser::Argument_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterArgument_expression_value(KerMLParser::Argument_expression_valueContext *ctx) {

}

void KerMLListenerImplementation::exitArgument_expression_value(KerMLParser::Argument_expression_valueContext *ctx) {

}

void KerMLListenerImplementation::enterMetadata_argument_member(KerMLParser::Metadata_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::exitMetadata_argument_member(KerMLParser::Metadata_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::enterMetadata_argument(KerMLParser::Metadata_argumentContext *ctx) {

}

void KerMLListenerImplementation::exitMetadata_argument(KerMLParser::Metadata_argumentContext *ctx) {

}

void KerMLListenerImplementation::enterMetadata_value(KerMLParser::Metadata_valueContext *ctx) {

}

void KerMLListenerImplementation::exitMetadata_value(KerMLParser::Metadata_valueContext *ctx) {

}

void KerMLListenerImplementation::enterMetadata_reference(KerMLParser::Metadata_referenceContext *ctx) {

}

void KerMLListenerImplementation::exitMetadata_reference(KerMLParser::Metadata_referenceContext *ctx) {

}

void KerMLListenerImplementation::enterMetadataclassification_test_operator(
        KerMLParser::Metadataclassification_test_operatorContext *ctx) {

}

void KerMLListenerImplementation::exitMetadataclassification_test_operator(
        KerMLParser::Metadataclassification_test_operatorContext *ctx) {

}

void KerMLListenerImplementation::enterMeta_cast_operator(KerMLParser::Meta_cast_operatorContext *ctx) {

}

void KerMLListenerImplementation::exitMeta_cast_operator(KerMLParser::Meta_cast_operatorContext *ctx) {

}

void KerMLListenerImplementation::enterExtend_expression(KerMLParser::Extend_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitExtend_expression(KerMLParser::Extend_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterType_reference_member(KerMLParser::Type_reference_memberContext *ctx) {

}

void KerMLListenerImplementation::exitType_reference_member(KerMLParser::Type_reference_memberContext *ctx) {

}

void KerMLListenerImplementation::enterType_result_member(KerMLParser::Type_result_memberContext *ctx) {

}

void KerMLListenerImplementation::exitType_result_member(KerMLParser::Type_result_memberContext *ctx) {

}

void KerMLListenerImplementation::enterType_reference(KerMLParser::Type_referenceContext *ctx) {

}

void KerMLListenerImplementation::exitType_reference(KerMLParser::Type_referenceContext *ctx) {

}

void KerMLListenerImplementation::enterReference_typing(KerMLParser::Reference_typingContext *ctx) {

}

void KerMLListenerImplementation::exitReference_typing(KerMLParser::Reference_typingContext *ctx) {

}

void KerMLListenerImplementation::enterPrimary_expressions(KerMLParser::Primary_expressionsContext *ctx) {

}

void KerMLListenerImplementation::exitPrimary_expressions(KerMLParser::Primary_expressionsContext *ctx) {

}

void KerMLListenerImplementation::enterPrimary_expression(KerMLParser::Primary_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitPrimary_expression(KerMLParser::Primary_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterPrimary_argument_value(KerMLParser::Primary_argument_valueContext *ctx) {

}

void KerMLListenerImplementation::exitPrimary_argument_value(KerMLParser::Primary_argument_valueContext *ctx) {

}

void KerMLListenerImplementation::enterPrimary_argument(KerMLParser::Primary_argumentContext *ctx) {

}

void KerMLListenerImplementation::exitPrimary_argument(KerMLParser::Primary_argumentContext *ctx) {

}

void KerMLListenerImplementation::enterPrimary_argument_member(KerMLParser::Primary_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::exitPrimary_argument_member(KerMLParser::Primary_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::enterNon_feature_chain_primary_expression(
        KerMLParser::Non_feature_chain_primary_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitNon_feature_chain_primary_expression(
        KerMLParser::Non_feature_chain_primary_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterNon_feature_chain_primary_argument_value(
        KerMLParser::Non_feature_chain_primary_argument_valueContext *ctx) {

}

void KerMLListenerImplementation::exitNon_feature_chain_primary_argument_value(
        KerMLParser::Non_feature_chain_primary_argument_valueContext *ctx) {

}

void KerMLListenerImplementation::enterNon_feature_chain_primary_argument(
        KerMLParser::Non_feature_chain_primary_argumentContext *ctx) {

}

void KerMLListenerImplementation::exitNon_feature_chain_primary_argument(
        KerMLParser::Non_feature_chain_primary_argumentContext *ctx) {

}

void KerMLListenerImplementation::enterNon_feature_chain_primary_argument_member(
        KerMLParser::Non_feature_chain_primary_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::exitNon_feature_chain_primary_argument_member(
        KerMLParser::Non_feature_chain_primary_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::enterBracket_expression(KerMLParser::Bracket_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitBracket_expression(KerMLParser::Bracket_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterIndex_expression(KerMLParser::Index_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitIndex_expression(KerMLParser::Index_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterSequence_expression(KerMLParser::Sequence_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitSequence_expression(KerMLParser::Sequence_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterSequence_expression_list(KerMLParser::Sequence_expression_listContext *ctx) {

}

void KerMLListenerImplementation::exitSequence_expression_list(KerMLParser::Sequence_expression_listContext *ctx) {

}

void
KerMLListenerImplementation::enterSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *ctx) {

}

void
KerMLListenerImplementation::exitSequence_operator_expression(KerMLParser::Sequence_operator_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterSequence_expression_list_member(
        KerMLParser::Sequence_expression_list_memberContext *ctx) {

}

void KerMLListenerImplementation::exitSequence_expression_list_member(
        KerMLParser::Sequence_expression_list_memberContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_chain_expression(KerMLParser::Feature_chain_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_chain_expression(KerMLParser::Feature_chain_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterCollect_expression(KerMLParser::Collect_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitCollect_expression(KerMLParser::Collect_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterSelect_expression(KerMLParser::Select_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitSelect_expression(KerMLParser::Select_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterFunction_operation_expression(
        KerMLParser::Function_operation_expressionContext *ctx) {

}

void
KerMLListenerImplementation::exitFunction_operation_expression(KerMLParser::Function_operation_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterBody_argument_member(KerMLParser::Body_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::exitBody_argument_member(KerMLParser::Body_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::enterBody_argument(KerMLParser::Body_argumentContext *ctx) {

}

void KerMLListenerImplementation::exitBody_argument(KerMLParser::Body_argumentContext *ctx) {

}

void KerMLListenerImplementation::enterBody_argument_value(KerMLParser::Body_argument_valueContext *ctx) {

}

void KerMLListenerImplementation::exitBody_argument_value(KerMLParser::Body_argument_valueContext *ctx) {

}

void KerMLListenerImplementation::enterBody_expression_member(KerMLParser::Body_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::exitBody_expression_member(KerMLParser::Body_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::enterFunction_reference_argument_member(
        KerMLParser::Function_reference_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::exitFunction_reference_argument_member(
        KerMLParser::Function_reference_argument_memberContext *ctx) {

}

void
KerMLListenerImplementation::enterFunction_reference_argument(KerMLParser::Function_reference_argumentContext *ctx) {

}

void
KerMLListenerImplementation::exitFunction_reference_argument(KerMLParser::Function_reference_argumentContext *ctx) {

}

void KerMLListenerImplementation::enterFunction_reference_arugment_value(
        KerMLParser::Function_reference_arugment_valueContext *ctx) {

}

void KerMLListenerImplementation::exitFunction_reference_arugment_value(
        KerMLParser::Function_reference_arugment_valueContext *ctx) {

}

void KerMLListenerImplementation::enterFunction_reference_expression(
        KerMLParser::Function_reference_expressionContext *ctx) {

}

void
KerMLListenerImplementation::exitFunction_reference_expression(KerMLParser::Function_reference_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterFunction_reference_member(KerMLParser::Function_reference_memberContext *ctx) {

}

void KerMLListenerImplementation::exitFunction_reference_member(KerMLParser::Function_reference_memberContext *ctx) {

}

void KerMLListenerImplementation::enterFunction_reference(KerMLParser::Function_referenceContext *ctx) {

}

void KerMLListenerImplementation::exitFunction_reference(KerMLParser::Function_referenceContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_chain_member(KerMLParser::Feature_chain_memberContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_chain_member(KerMLParser::Feature_chain_memberContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_feature_chain_member(KerMLParser::Owned_feature_chain_memberContext *ctx) {

}

void KerMLListenerImplementation::enterBase_expression(KerMLParser::Base_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitBase_expression(KerMLParser::Base_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterNull_expression(KerMLParser::Null_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitNull_expression(KerMLParser::Null_expressionContext *ctx) {

}

void
KerMLListenerImplementation::enterFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *ctx) {

}

void
KerMLListenerImplementation::exitFeature_reference_expression(KerMLParser::Feature_reference_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_reference_member(KerMLParser::Feature_reference_memberContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_reference_member(KerMLParser::Feature_reference_memberContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_reference(KerMLParser::Feature_referenceContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_reference(KerMLParser::Feature_referenceContext *ctx) {

}

void KerMLListenerImplementation::enterMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitMetadata_access_expression(KerMLParser::Metadata_access_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterInvocation_expression(KerMLParser::Invocation_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitInvocation_expression(KerMLParser::Invocation_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterInternal_invocation_expression(
        KerMLParser::Internal_invocation_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitInternal_invocation_expression(
        KerMLParser::Internal_invocation_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterArgument_list(KerMLParser::Argument_listContext *ctx) {

}

void KerMLListenerImplementation::exitArgument_list(KerMLParser::Argument_listContext *ctx) {

}

void KerMLListenerImplementation::enterPositional_argument_list(KerMLParser::Positional_argument_listContext *ctx) {

}

void KerMLListenerImplementation::exitPositional_argument_list(KerMLParser::Positional_argument_listContext *ctx) {

}

void KerMLListenerImplementation::enterNamed_argument_list(KerMLParser::Named_argument_listContext *ctx) {

}

void KerMLListenerImplementation::exitNamed_argument_list(KerMLParser::Named_argument_listContext *ctx) {

}

void KerMLListenerImplementation::enterNamed_argument_member(KerMLParser::Named_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::exitNamed_argument_member(KerMLParser::Named_argument_memberContext *ctx) {

}

void KerMLListenerImplementation::enterNamed_argument(KerMLParser::Named_argumentContext *ctx) {

}

void KerMLListenerImplementation::exitNamed_argument(KerMLParser::Named_argumentContext *ctx) {

}

void KerMLListenerImplementation::enterParamenter_redefinition(KerMLParser::Paramenter_redefinitionContext *ctx) {

}

void KerMLListenerImplementation::exitParamenter_redefinition(KerMLParser::Paramenter_redefinitionContext *ctx) {

}

void KerMLListenerImplementation::enterBody_expression(KerMLParser::Body_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitBody_expression(KerMLParser::Body_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterExpression_body_member(KerMLParser::Expression_body_memberContext *ctx) {

}

void KerMLListenerImplementation::exitExpression_body_member(KerMLParser::Expression_body_memberContext *ctx) {

}

void KerMLListenerImplementation::enterExpression_body(KerMLParser::Expression_bodyContext *ctx) {

}

void KerMLListenerImplementation::exitExpression_body(KerMLParser::Expression_bodyContext *ctx) {

}

void KerMLListenerImplementation::enterLiteral_expression(KerMLParser::Literal_expressionContext *ctx) {

}

void KerMLListenerImplementation::exitLiteral_expression(KerMLParser::Literal_expressionContext *ctx) {

}

void KerMLListenerImplementation::enterLiteral_boolean(KerMLParser::Literal_booleanContext *ctx) {

}

void KerMLListenerImplementation::exitLiteral_boolean(KerMLParser::Literal_booleanContext *ctx) {

}

void KerMLListenerImplementation::enterBoolean_value(KerMLParser::Boolean_valueContext *ctx) {

}

void KerMLListenerImplementation::exitBoolean_value(KerMLParser::Boolean_valueContext *ctx) {

}

void KerMLListenerImplementation::enterLiteral_string(KerMLParser::Literal_stringContext *ctx) {

}

void KerMLListenerImplementation::exitLiteral_string(KerMLParser::Literal_stringContext *ctx) {

}

void KerMLListenerImplementation::enterLiteral_integer(KerMLParser::Literal_integerContext *ctx) {

}

void KerMLListenerImplementation::exitLiteral_integer(KerMLParser::Literal_integerContext *ctx) {

}

void KerMLListenerImplementation::enterLiteral_real(KerMLParser::Literal_realContext *ctx) {

}

void KerMLListenerImplementation::exitLiteral_real(KerMLParser::Literal_realContext *ctx) {

}

void KerMLListenerImplementation::enterReal_value(KerMLParser::Real_valueContext *ctx) {

}

void KerMLListenerImplementation::exitReal_value(KerMLParser::Real_valueContext *ctx) {

}

void KerMLListenerImplementation::enterLiteral_infinity(KerMLParser::Literal_infinityContext *ctx) {

}

void KerMLListenerImplementation::exitLiteral_infinity(KerMLParser::Literal_infinityContext *ctx) {

}

void KerMLListenerImplementation::enterInteraction(KerMLParser::InteractionContext *ctx) {

}

void KerMLListenerImplementation::exitInteraction(KerMLParser::InteractionContext *ctx) {

}

void KerMLListenerImplementation::enterItem_flow(KerMLParser::Item_flowContext *ctx) {

}

void KerMLListenerImplementation::exitItem_flow(KerMLParser::Item_flowContext *ctx) {

}

void KerMLListenerImplementation::enterSuccession_item_flow(KerMLParser::Succession_item_flowContext *ctx) {

}

void KerMLListenerImplementation::exitSuccession_item_flow(KerMLParser::Succession_item_flowContext *ctx) {

}

void KerMLListenerImplementation::enterItem_flow_declaration(KerMLParser::Item_flow_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitItem_flow_declaration(KerMLParser::Item_flow_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterItem_feature_member(KerMLParser::Item_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::exitItem_feature_member(KerMLParser::Item_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::enterItem_feature(KerMLParser::Item_featureContext *ctx) {

}

void KerMLListenerImplementation::exitItem_feature(KerMLParser::Item_featureContext *ctx) {

}

void KerMLListenerImplementation::enterItem_feature_specilization_part(
        KerMLParser::Item_feature_specilization_partContext *ctx) {

}

void KerMLListenerImplementation::exitItem_feature_specilization_part(
        KerMLParser::Item_feature_specilization_partContext *ctx) {

}

void KerMLListenerImplementation::enterItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *ctx) {

}

void KerMLListenerImplementation::exitItem_flow_end_member(KerMLParser::Item_flow_end_memberContext *ctx) {

}

void KerMLListenerImplementation::enterItem_flow_end(KerMLParser::Item_flow_endContext *ctx) {

}

void KerMLListenerImplementation::exitItem_flow_end(KerMLParser::Item_flow_endContext *ctx) {

}

void KerMLListenerImplementation::enterItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::exitItem_flow_feature_member(KerMLParser::Item_flow_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::enterItem_flow_feature(KerMLParser::Item_flow_featureContext *ctx) {

}

void KerMLListenerImplementation::exitItem_flow_feature(KerMLParser::Item_flow_featureContext *ctx) {

}

void KerMLListenerImplementation::enterItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *ctx) {

}

void KerMLListenerImplementation::exitItem_flow_redefinition(KerMLParser::Item_flow_redefinitionContext *ctx) {

}

void KerMLListenerImplementation::enterValue_part(KerMLParser::Value_partContext *ctx) {

}

void KerMLListenerImplementation::exitValue_part(KerMLParser::Value_partContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_value(KerMLParser::Feature_valueContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_value(KerMLParser::Feature_valueContext *ctx) {

}

void KerMLListenerImplementation::enterFeature_assignment(KerMLParser::Feature_assignmentContext *ctx) {

}

void KerMLListenerImplementation::exitFeature_assignment(KerMLParser::Feature_assignmentContext *ctx) {

}

void KerMLListenerImplementation::enterMultiplicity(KerMLParser::MultiplicityContext *ctx) {

}

void KerMLListenerImplementation::exitMultiplicity(KerMLParser::MultiplicityContext *ctx) {

}

void KerMLListenerImplementation::enterMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *ctx) {

}

void KerMLListenerImplementation::exitMultiplicity_subset(KerMLParser::Multiplicity_subsetContext *ctx) {

}

void KerMLListenerImplementation::enterMultiplicity_range(KerMLParser::Multiplicity_rangeContext *ctx) {

}

void KerMLListenerImplementation::exitMultiplicity_range(KerMLParser::Multiplicity_rangeContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_multiplicity(KerMLParser::Owned_multiplicityContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_multiplicity(KerMLParser::Owned_multiplicityContext *ctx) {

}

void KerMLListenerImplementation::enterOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *ctx) {

}

void KerMLListenerImplementation::exitOwned_multiplicity_range(KerMLParser::Owned_multiplicity_rangeContext *ctx) {

}

void KerMLListenerImplementation::enterMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext *ctx) {

}

void KerMLListenerImplementation::exitMultiplicity_bounds(KerMLParser::Multiplicity_boundsContext *ctx) {

}

void KerMLListenerImplementation::enterMultiplicity_expression_member(
        KerMLParser::Multiplicity_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::exitMultiplicity_expression_member(
        KerMLParser::Multiplicity_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::enterInternal_multiplicity_expression_member(
        KerMLParser::Internal_multiplicity_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::exitInternal_multiplicity_expression_member(
        KerMLParser::Internal_multiplicity_expression_memberContext *ctx) {

}

void KerMLListenerImplementation::enterMetaclass(KerMLParser::MetaclassContext *ctx) {

}

void KerMLListenerImplementation::exitMetaclass(KerMLParser::MetaclassContext *ctx) {

}

void KerMLListenerImplementation::enterPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *ctx) {

}

void KerMLListenerImplementation::exitPrefix_metadata_annotation(KerMLParser::Prefix_metadata_annotationContext *ctx) {

}

void KerMLListenerImplementation::enterPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *ctx) {

}

void KerMLListenerImplementation::exitPrefix_metadata_member(KerMLParser::Prefix_metadata_memberContext *ctx) {

}

void KerMLListenerImplementation::enterPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *ctx) {

}

void KerMLListenerImplementation::exitPrefix_metadata_feature(KerMLParser::Prefix_metadata_featureContext *ctx) {

}

void KerMLListenerImplementation::enterMetadata_feature(KerMLParser::Metadata_featureContext *ctx) {

}

void KerMLListenerImplementation::exitMetadata_feature(KerMLParser::Metadata_featureContext *ctx) {

}

void
KerMLListenerImplementation::enterMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *ctx) {

}

void
KerMLListenerImplementation::exitMetadata_feature_declaration(KerMLParser::Metadata_feature_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterMetadata_body(KerMLParser::Metadata_bodyContext *ctx) {

}

void KerMLListenerImplementation::exitMetadata_body(KerMLParser::Metadata_bodyContext *ctx) {

}

void KerMLListenerImplementation::enterMetadata_body_element(KerMLParser::Metadata_body_elementContext *ctx) {

}

void KerMLListenerImplementation::exitMetadata_body_element(KerMLParser::Metadata_body_elementContext *ctx) {

}

void
KerMLListenerImplementation::enterMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *ctx) {

}

void
KerMLListenerImplementation::exitMetadata_body_feature_member(KerMLParser::Metadata_body_feature_memberContext *ctx) {

}

void KerMLListenerImplementation::enterMetadata_body_feature(KerMLParser::Metadata_body_featureContext *ctx) {

}

void KerMLListenerImplementation::exitMetadata_body_feature(KerMLParser::Metadata_body_featureContext *ctx) {

}

void KerMLListenerImplementation::enterPackage(KerMLParser::PackageContext *ctx) {

}

void KerMLListenerImplementation::exitPackage(KerMLParser::PackageContext *ctx) {

}

void KerMLListenerImplementation::enterLibrary_package(KerMLParser::Library_packageContext *ctx) {

}

void KerMLListenerImplementation::exitLibrary_package(KerMLParser::Library_packageContext *ctx) {

}

void KerMLListenerImplementation::enterPackage_declaration(KerMLParser::Package_declarationContext *ctx) {

}

void KerMLListenerImplementation::exitPackage_declaration(KerMLParser::Package_declarationContext *ctx) {

}

void KerMLListenerImplementation::enterPackage_body(KerMLParser::Package_bodyContext *ctx) {

}

void KerMLListenerImplementation::exitPackage_body(KerMLParser::Package_bodyContext *ctx) {

}

void KerMLListenerImplementation::enterElement_filter_member(KerMLParser::Element_filter_memberContext *ctx) {

}

void KerMLListenerImplementation::exitElement_filter_member(KerMLParser::Element_filter_memberContext *ctx) {

}

void KerMLListenerImplementation::enterMeta_assignment(KerMLParser::Meta_assignmentContext *ctx) {

}

void KerMLListenerImplementation::exitMeta_assignment(KerMLParser::Meta_assignmentContext *ctx) {

}


