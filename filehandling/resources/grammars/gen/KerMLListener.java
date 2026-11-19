// Generated from /home/herzog/Dokumente/Projekte/CPP-SysMLv2/filehandling/resources/grammars/KerML.g4 by ANTLR 4.13.2

    #include <sysmlv2/sysmlv2file_global.h>

import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link KerMLParser}.
 */
public interface KerMLListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link KerMLParser#start}.
	 * @param ctx the parse tree
	 */
	void enterStart(KerMLParser.StartContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#start}.
	 * @param ctx the parse tree
	 */
	void exitStart(KerMLParser.StartContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#startRule}.
	 * @param ctx the parse tree
	 */
	void enterStartRule(KerMLParser.StartRuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#startRule}.
	 * @param ctx the parse tree
	 */
	void exitStartRule(KerMLParser.StartRuleContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#elements}.
	 * @param ctx the parse tree
	 */
	void enterElements(KerMLParser.ElementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#elements}.
	 * @param ctx the parse tree
	 */
	void exitElements(KerMLParser.ElementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#identification}.
	 * @param ctx the parse tree
	 */
	void enterIdentification(KerMLParser.IdentificationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#identification}.
	 * @param ctx the parse tree
	 */
	void exitIdentification(KerMLParser.IdentificationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#relationship_body}.
	 * @param ctx the parse tree
	 */
	void enterRelationship_body(KerMLParser.Relationship_bodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#relationship_body}.
	 * @param ctx the parse tree
	 */
	void exitRelationship_body(KerMLParser.Relationship_bodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#relationship_owned_elements}.
	 * @param ctx the parse tree
	 */
	void enterRelationship_owned_elements(KerMLParser.Relationship_owned_elementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#relationship_owned_elements}.
	 * @param ctx the parse tree
	 */
	void exitRelationship_owned_elements(KerMLParser.Relationship_owned_elementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#relationship_owned_element}.
	 * @param ctx the parse tree
	 */
	void enterRelationship_owned_element(KerMLParser.Relationship_owned_elementContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#relationship_owned_element}.
	 * @param ctx the parse tree
	 */
	void exitRelationship_owned_element(KerMLParser.Relationship_owned_elementContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_related_element}.
	 * @param ctx the parse tree
	 */
	void enterOwned_related_element(KerMLParser.Owned_related_elementContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_related_element}.
	 * @param ctx the parse tree
	 */
	void exitOwned_related_element(KerMLParser.Owned_related_elementContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#dependency}.
	 * @param ctx the parse tree
	 */
	void enterDependency(KerMLParser.DependencyContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#dependency}.
	 * @param ctx the parse tree
	 */
	void exitDependency(KerMLParser.DependencyContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#annotation}.
	 * @param ctx the parse tree
	 */
	void enterAnnotation(KerMLParser.AnnotationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#annotation}.
	 * @param ctx the parse tree
	 */
	void exitAnnotation(KerMLParser.AnnotationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_annotation}.
	 * @param ctx the parse tree
	 */
	void enterOwned_annotation(KerMLParser.Owned_annotationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_annotation}.
	 * @param ctx the parse tree
	 */
	void exitOwned_annotation(KerMLParser.Owned_annotationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#annotating_element}.
	 * @param ctx the parse tree
	 */
	void enterAnnotating_element(KerMLParser.Annotating_elementContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#annotating_element}.
	 * @param ctx the parse tree
	 */
	void exitAnnotating_element(KerMLParser.Annotating_elementContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#comment}.
	 * @param ctx the parse tree
	 */
	void enterComment(KerMLParser.CommentContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#comment}.
	 * @param ctx the parse tree
	 */
	void exitComment(KerMLParser.CommentContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#documentation}.
	 * @param ctx the parse tree
	 */
	void enterDocumentation(KerMLParser.DocumentationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#documentation}.
	 * @param ctx the parse tree
	 */
	void exitDocumentation(KerMLParser.DocumentationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#textual_representation}.
	 * @param ctx the parse tree
	 */
	void enterTextual_representation(KerMLParser.Textual_representationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#textual_representation}.
	 * @param ctx the parse tree
	 */
	void exitTextual_representation(KerMLParser.Textual_representationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#root_namespace}.
	 * @param ctx the parse tree
	 */
	void enterRoot_namespace(KerMLParser.Root_namespaceContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#root_namespace}.
	 * @param ctx the parse tree
	 */
	void exitRoot_namespace(KerMLParser.Root_namespaceContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#namespace}.
	 * @param ctx the parse tree
	 */
	void enterNamespace(KerMLParser.NamespaceContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#namespace}.
	 * @param ctx the parse tree
	 */
	void exitNamespace(KerMLParser.NamespaceContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#namespace_declaration}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_declaration(KerMLParser.Namespace_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#namespace_declaration}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_declaration(KerMLParser.Namespace_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#namespace_body}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_body(KerMLParser.Namespace_bodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#namespace_body}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_body(KerMLParser.Namespace_bodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#namespace_body_elements}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_body_elements(KerMLParser.Namespace_body_elementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#namespace_body_elements}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_body_elements(KerMLParser.Namespace_body_elementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#namespace_body_element}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_body_element(KerMLParser.Namespace_body_elementContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#namespace_body_element}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_body_element(KerMLParser.Namespace_body_elementContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#member_prefix}.
	 * @param ctx the parse tree
	 */
	void enterMember_prefix(KerMLParser.Member_prefixContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#member_prefix}.
	 * @param ctx the parse tree
	 */
	void exitMember_prefix(KerMLParser.Member_prefixContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#visibility_indicator}.
	 * @param ctx the parse tree
	 */
	void enterVisibility_indicator(KerMLParser.Visibility_indicatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#visibility_indicator}.
	 * @param ctx the parse tree
	 */
	void exitVisibility_indicator(KerMLParser.Visibility_indicatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#namespace_member}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_member(KerMLParser.Namespace_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#namespace_member}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_member(KerMLParser.Namespace_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#non_feature_member}.
	 * @param ctx the parse tree
	 */
	void enterNon_feature_member(KerMLParser.Non_feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#non_feature_member}.
	 * @param ctx the parse tree
	 */
	void exitNon_feature_member(KerMLParser.Non_feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#namespace_feature_member}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_feature_member(KerMLParser.Namespace_feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#namespace_feature_member}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_feature_member(KerMLParser.Namespace_feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#alias_member}.
	 * @param ctx the parse tree
	 */
	void enterAlias_member(KerMLParser.Alias_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#alias_member}.
	 * @param ctx the parse tree
	 */
	void exitAlias_member(KerMLParser.Alias_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#qualified_name}.
	 * @param ctx the parse tree
	 */
	void enterQualified_name(KerMLParser.Qualified_nameContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#qualified_name}.
	 * @param ctx the parse tree
	 */
	void exitQualified_name(KerMLParser.Qualified_nameContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#namespace_import}.
	 * @param ctx the parse tree
	 */
	void enterNamespace_import(KerMLParser.Namespace_importContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#namespace_import}.
	 * @param ctx the parse tree
	 */
	void exitNamespace_import(KerMLParser.Namespace_importContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#import_declaration}.
	 * @param ctx the parse tree
	 */
	void enterImport_declaration(KerMLParser.Import_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#import_declaration}.
	 * @param ctx the parse tree
	 */
	void exitImport_declaration(KerMLParser.Import_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#membership_import}.
	 * @param ctx the parse tree
	 */
	void enterMembership_import(KerMLParser.Membership_importContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#membership_import}.
	 * @param ctx the parse tree
	 */
	void exitMembership_import(KerMLParser.Membership_importContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#filter_package}.
	 * @param ctx the parse tree
	 */
	void enterFilter_package(KerMLParser.Filter_packageContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#filter_package}.
	 * @param ctx the parse tree
	 */
	void exitFilter_package(KerMLParser.Filter_packageContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#filter_package_member}.
	 * @param ctx the parse tree
	 */
	void enterFilter_package_member(KerMLParser.Filter_package_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#filter_package_member}.
	 * @param ctx the parse tree
	 */
	void exitFilter_package_member(KerMLParser.Filter_package_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#element}.
	 * @param ctx the parse tree
	 */
	void enterElement(KerMLParser.ElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#element}.
	 * @param ctx the parse tree
	 */
	void exitElement(KerMLParser.ElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#non_feature_element}.
	 * @param ctx the parse tree
	 */
	void enterNon_feature_element(KerMLParser.Non_feature_elementContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#non_feature_element}.
	 * @param ctx the parse tree
	 */
	void exitNon_feature_element(KerMLParser.Non_feature_elementContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_element}.
	 * @param ctx the parse tree
	 */
	void enterFeature_element(KerMLParser.Feature_elementContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_element}.
	 * @param ctx the parse tree
	 */
	void exitFeature_element(KerMLParser.Feature_elementContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#additional_options}.
	 * @param ctx the parse tree
	 */
	void enterAdditional_options(KerMLParser.Additional_optionsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#additional_options}.
	 * @param ctx the parse tree
	 */
	void exitAdditional_options(KerMLParser.Additional_optionsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(KerMLParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(KerMLParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_prefix}.
	 * @param ctx the parse tree
	 */
	void enterType_prefix(KerMLParser.Type_prefixContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_prefix}.
	 * @param ctx the parse tree
	 */
	void exitType_prefix(KerMLParser.Type_prefixContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_declaration}.
	 * @param ctx the parse tree
	 */
	void enterType_declaration(KerMLParser.Type_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_declaration}.
	 * @param ctx the parse tree
	 */
	void exitType_declaration(KerMLParser.Type_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#specialization_part}.
	 * @param ctx the parse tree
	 */
	void enterSpecialization_part(KerMLParser.Specialization_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#specialization_part}.
	 * @param ctx the parse tree
	 */
	void exitSpecialization_part(KerMLParser.Specialization_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#conjugation_part}.
	 * @param ctx the parse tree
	 */
	void enterConjugation_part(KerMLParser.Conjugation_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#conjugation_part}.
	 * @param ctx the parse tree
	 */
	void exitConjugation_part(KerMLParser.Conjugation_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_relationship_part}.
	 * @param ctx the parse tree
	 */
	void enterType_relationship_part(KerMLParser.Type_relationship_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_relationship_part}.
	 * @param ctx the parse tree
	 */
	void exitType_relationship_part(KerMLParser.Type_relationship_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#disjoining_part}.
	 * @param ctx the parse tree
	 */
	void enterDisjoining_part(KerMLParser.Disjoining_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#disjoining_part}.
	 * @param ctx the parse tree
	 */
	void exitDisjoining_part(KerMLParser.Disjoining_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#unioning_part}.
	 * @param ctx the parse tree
	 */
	void enterUnioning_part(KerMLParser.Unioning_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#unioning_part}.
	 * @param ctx the parse tree
	 */
	void exitUnioning_part(KerMLParser.Unioning_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#intersecting_part}.
	 * @param ctx the parse tree
	 */
	void enterIntersecting_part(KerMLParser.Intersecting_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#intersecting_part}.
	 * @param ctx the parse tree
	 */
	void exitIntersecting_part(KerMLParser.Intersecting_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#differencing_part}.
	 * @param ctx the parse tree
	 */
	void enterDifferencing_part(KerMLParser.Differencing_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#differencing_part}.
	 * @param ctx the parse tree
	 */
	void exitDifferencing_part(KerMLParser.Differencing_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_body}.
	 * @param ctx the parse tree
	 */
	void enterType_body(KerMLParser.Type_bodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_body}.
	 * @param ctx the parse tree
	 */
	void exitType_body(KerMLParser.Type_bodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_body_elements}.
	 * @param ctx the parse tree
	 */
	void enterType_body_elements(KerMLParser.Type_body_elementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_body_elements}.
	 * @param ctx the parse tree
	 */
	void exitType_body_elements(KerMLParser.Type_body_elementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_body_element}.
	 * @param ctx the parse tree
	 */
	void enterType_body_element(KerMLParser.Type_body_elementContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_body_element}.
	 * @param ctx the parse tree
	 */
	void exitType_body_element(KerMLParser.Type_body_elementContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#specialization}.
	 * @param ctx the parse tree
	 */
	void enterSpecialization(KerMLParser.SpecializationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#specialization}.
	 * @param ctx the parse tree
	 */
	void exitSpecialization(KerMLParser.SpecializationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_specialization}.
	 * @param ctx the parse tree
	 */
	void enterOwned_specialization(KerMLParser.Owned_specializationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_specialization}.
	 * @param ctx the parse tree
	 */
	void exitOwned_specialization(KerMLParser.Owned_specializationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#specific_type}.
	 * @param ctx the parse tree
	 */
	void enterSpecific_type(KerMLParser.Specific_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#specific_type}.
	 * @param ctx the parse tree
	 */
	void exitSpecific_type(KerMLParser.Specific_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#general_type}.
	 * @param ctx the parse tree
	 */
	void enterGeneral_type(KerMLParser.General_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#general_type}.
	 * @param ctx the parse tree
	 */
	void exitGeneral_type(KerMLParser.General_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#conjunction}.
	 * @param ctx the parse tree
	 */
	void enterConjunction(KerMLParser.ConjunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#conjunction}.
	 * @param ctx the parse tree
	 */
	void exitConjunction(KerMLParser.ConjunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_conjugation}.
	 * @param ctx the parse tree
	 */
	void enterOwned_conjugation(KerMLParser.Owned_conjugationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_conjugation}.
	 * @param ctx the parse tree
	 */
	void exitOwned_conjugation(KerMLParser.Owned_conjugationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#disjoining}.
	 * @param ctx the parse tree
	 */
	void enterDisjoining(KerMLParser.DisjoiningContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#disjoining}.
	 * @param ctx the parse tree
	 */
	void exitDisjoining(KerMLParser.DisjoiningContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_disjoining}.
	 * @param ctx the parse tree
	 */
	void enterOwned_disjoining(KerMLParser.Owned_disjoiningContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_disjoining}.
	 * @param ctx the parse tree
	 */
	void exitOwned_disjoining(KerMLParser.Owned_disjoiningContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#unioning}.
	 * @param ctx the parse tree
	 */
	void enterUnioning(KerMLParser.UnioningContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#unioning}.
	 * @param ctx the parse tree
	 */
	void exitUnioning(KerMLParser.UnioningContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#intersecting}.
	 * @param ctx the parse tree
	 */
	void enterIntersecting(KerMLParser.IntersectingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#intersecting}.
	 * @param ctx the parse tree
	 */
	void exitIntersecting(KerMLParser.IntersectingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#differencing}.
	 * @param ctx the parse tree
	 */
	void enterDifferencing(KerMLParser.DifferencingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#differencing}.
	 * @param ctx the parse tree
	 */
	void exitDifferencing(KerMLParser.DifferencingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_member}.
	 * @param ctx the parse tree
	 */
	void enterFeature_member(KerMLParser.Feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_member}.
	 * @param ctx the parse tree
	 */
	void exitFeature_member(KerMLParser.Feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_feature_member}.
	 * @param ctx the parse tree
	 */
	void enterType_feature_member(KerMLParser.Type_feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_feature_member}.
	 * @param ctx the parse tree
	 */
	void exitType_feature_member(KerMLParser.Type_feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_feature_member}.
	 * @param ctx the parse tree
	 */
	void enterOwned_feature_member(KerMLParser.Owned_feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_feature_member}.
	 * @param ctx the parse tree
	 */
	void exitOwned_feature_member(KerMLParser.Owned_feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#classifier}.
	 * @param ctx the parse tree
	 */
	void enterClassifier(KerMLParser.ClassifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#classifier}.
	 * @param ctx the parse tree
	 */
	void exitClassifier(KerMLParser.ClassifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#classifier_declaration}.
	 * @param ctx the parse tree
	 */
	void enterClassifier_declaration(KerMLParser.Classifier_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#classifier_declaration}.
	 * @param ctx the parse tree
	 */
	void exitClassifier_declaration(KerMLParser.Classifier_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#superclassing_part}.
	 * @param ctx the parse tree
	 */
	void enterSuperclassing_part(KerMLParser.Superclassing_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#superclassing_part}.
	 * @param ctx the parse tree
	 */
	void exitSuperclassing_part(KerMLParser.Superclassing_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#subclassification}.
	 * @param ctx the parse tree
	 */
	void enterSubclassification(KerMLParser.SubclassificationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#subclassification}.
	 * @param ctx the parse tree
	 */
	void exitSubclassification(KerMLParser.SubclassificationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_subclassification}.
	 * @param ctx the parse tree
	 */
	void enterOwned_subclassification(KerMLParser.Owned_subclassificationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_subclassification}.
	 * @param ctx the parse tree
	 */
	void exitOwned_subclassification(KerMLParser.Owned_subclassificationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature}.
	 * @param ctx the parse tree
	 */
	void enterFeature(KerMLParser.FeatureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature}.
	 * @param ctx the parse tree
	 */
	void exitFeature(KerMLParser.FeatureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#anonymous_feature}.
	 * @param ctx the parse tree
	 */
	void enterAnonymous_feature(KerMLParser.Anonymous_featureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#anonymous_feature}.
	 * @param ctx the parse tree
	 */
	void exitAnonymous_feature(KerMLParser.Anonymous_featureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_prefix}.
	 * @param ctx the parse tree
	 */
	void enterFeature_prefix(KerMLParser.Feature_prefixContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_prefix}.
	 * @param ctx the parse tree
	 */
	void exitFeature_prefix(KerMLParser.Feature_prefixContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#end_feature_prefix}.
	 * @param ctx the parse tree
	 */
	void enterEnd_feature_prefix(KerMLParser.End_feature_prefixContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#end_feature_prefix}.
	 * @param ctx the parse tree
	 */
	void exitEnd_feature_prefix(KerMLParser.End_feature_prefixContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#basic_feature_prefix}.
	 * @param ctx the parse tree
	 */
	void enterBasic_feature_prefix(KerMLParser.Basic_feature_prefixContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#basic_feature_prefix}.
	 * @param ctx the parse tree
	 */
	void exitBasic_feature_prefix(KerMLParser.Basic_feature_prefixContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_cross_feature_member}.
	 * @param ctx the parse tree
	 */
	void enterOwned_cross_feature_member(KerMLParser.Owned_cross_feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_cross_feature_member}.
	 * @param ctx the parse tree
	 */
	void exitOwned_cross_feature_member(KerMLParser.Owned_cross_feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_cross_feature}.
	 * @param ctx the parse tree
	 */
	void enterOwned_cross_feature(KerMLParser.Owned_cross_featureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_cross_feature}.
	 * @param ctx the parse tree
	 */
	void exitOwned_cross_feature(KerMLParser.Owned_cross_featureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_direction}.
	 * @param ctx the parse tree
	 */
	void enterFeature_direction(KerMLParser.Feature_directionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_direction}.
	 * @param ctx the parse tree
	 */
	void exitFeature_direction(KerMLParser.Feature_directionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_declaration}.
	 * @param ctx the parse tree
	 */
	void enterFeature_declaration(KerMLParser.Feature_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_declaration}.
	 * @param ctx the parse tree
	 */
	void exitFeature_declaration(KerMLParser.Feature_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_identification}.
	 * @param ctx the parse tree
	 */
	void enterFeature_identification(KerMLParser.Feature_identificationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_identification}.
	 * @param ctx the parse tree
	 */
	void exitFeature_identification(KerMLParser.Feature_identificationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_relationship_part}.
	 * @param ctx the parse tree
	 */
	void enterFeature_relationship_part(KerMLParser.Feature_relationship_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_relationship_part}.
	 * @param ctx the parse tree
	 */
	void exitFeature_relationship_part(KerMLParser.Feature_relationship_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#chaining_part}.
	 * @param ctx the parse tree
	 */
	void enterChaining_part(KerMLParser.Chaining_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#chaining_part}.
	 * @param ctx the parse tree
	 */
	void exitChaining_part(KerMLParser.Chaining_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#inverting_part}.
	 * @param ctx the parse tree
	 */
	void enterInverting_part(KerMLParser.Inverting_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#inverting_part}.
	 * @param ctx the parse tree
	 */
	void exitInverting_part(KerMLParser.Inverting_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_featuring_part}.
	 * @param ctx the parse tree
	 */
	void enterType_featuring_part(KerMLParser.Type_featuring_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_featuring_part}.
	 * @param ctx the parse tree
	 */
	void exitType_featuring_part(KerMLParser.Type_featuring_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_specialization_part}.
	 * @param ctx the parse tree
	 */
	void enterFeature_specialization_part(KerMLParser.Feature_specialization_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_specialization_part}.
	 * @param ctx the parse tree
	 */
	void exitFeature_specialization_part(KerMLParser.Feature_specialization_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#multiplicity_part}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicity_part(KerMLParser.Multiplicity_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#multiplicity_part}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicity_part(KerMLParser.Multiplicity_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#multiplicity_modifier}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicity_modifier(KerMLParser.Multiplicity_modifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#multiplicity_modifier}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicity_modifier(KerMLParser.Multiplicity_modifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_specialization}.
	 * @param ctx the parse tree
	 */
	void enterFeature_specialization(KerMLParser.Feature_specializationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_specialization}.
	 * @param ctx the parse tree
	 */
	void exitFeature_specialization(KerMLParser.Feature_specializationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#typings}.
	 * @param ctx the parse tree
	 */
	void enterTypings(KerMLParser.TypingsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#typings}.
	 * @param ctx the parse tree
	 */
	void exitTypings(KerMLParser.TypingsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#typed_by}.
	 * @param ctx the parse tree
	 */
	void enterTyped_by(KerMLParser.Typed_byContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#typed_by}.
	 * @param ctx the parse tree
	 */
	void exitTyped_by(KerMLParser.Typed_byContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#subsettings}.
	 * @param ctx the parse tree
	 */
	void enterSubsettings(KerMLParser.SubsettingsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#subsettings}.
	 * @param ctx the parse tree
	 */
	void exitSubsettings(KerMLParser.SubsettingsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#subsets}.
	 * @param ctx the parse tree
	 */
	void enterSubsets(KerMLParser.SubsetsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#subsets}.
	 * @param ctx the parse tree
	 */
	void exitSubsets(KerMLParser.SubsetsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#references}.
	 * @param ctx the parse tree
	 */
	void enterReferences(KerMLParser.ReferencesContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#references}.
	 * @param ctx the parse tree
	 */
	void exitReferences(KerMLParser.ReferencesContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#crosses}.
	 * @param ctx the parse tree
	 */
	void enterCrosses(KerMLParser.CrossesContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#crosses}.
	 * @param ctx the parse tree
	 */
	void exitCrosses(KerMLParser.CrossesContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#redefinitions}.
	 * @param ctx the parse tree
	 */
	void enterRedefinitions(KerMLParser.RedefinitionsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#redefinitions}.
	 * @param ctx the parse tree
	 */
	void exitRedefinitions(KerMLParser.RedefinitionsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#redefines}.
	 * @param ctx the parse tree
	 */
	void enterRedefines(KerMLParser.RedefinesContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#redefines}.
	 * @param ctx the parse tree
	 */
	void exitRedefines(KerMLParser.RedefinesContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_typing}.
	 * @param ctx the parse tree
	 */
	void enterFeature_typing(KerMLParser.Feature_typingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_typing}.
	 * @param ctx the parse tree
	 */
	void exitFeature_typing(KerMLParser.Feature_typingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_feature_typing}.
	 * @param ctx the parse tree
	 */
	void enterOwned_feature_typing(KerMLParser.Owned_feature_typingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_feature_typing}.
	 * @param ctx the parse tree
	 */
	void exitOwned_feature_typing(KerMLParser.Owned_feature_typingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#subsetting}.
	 * @param ctx the parse tree
	 */
	void enterSubsetting(KerMLParser.SubsettingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#subsetting}.
	 * @param ctx the parse tree
	 */
	void exitSubsetting(KerMLParser.SubsettingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_subsetting}.
	 * @param ctx the parse tree
	 */
	void enterOwned_subsetting(KerMLParser.Owned_subsettingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_subsetting}.
	 * @param ctx the parse tree
	 */
	void exitOwned_subsetting(KerMLParser.Owned_subsettingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_reference_subsetting}.
	 * @param ctx the parse tree
	 */
	void enterOwned_reference_subsetting(KerMLParser.Owned_reference_subsettingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_reference_subsetting}.
	 * @param ctx the parse tree
	 */
	void exitOwned_reference_subsetting(KerMLParser.Owned_reference_subsettingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_cross_subsetting}.
	 * @param ctx the parse tree
	 */
	void enterOwned_cross_subsetting(KerMLParser.Owned_cross_subsettingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_cross_subsetting}.
	 * @param ctx the parse tree
	 */
	void exitOwned_cross_subsetting(KerMLParser.Owned_cross_subsettingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#redefinition}.
	 * @param ctx the parse tree
	 */
	void enterRedefinition(KerMLParser.RedefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#redefinition}.
	 * @param ctx the parse tree
	 */
	void exitRedefinition(KerMLParser.RedefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_redefinition}.
	 * @param ctx the parse tree
	 */
	void enterOwned_redefinition(KerMLParser.Owned_redefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_redefinition}.
	 * @param ctx the parse tree
	 */
	void exitOwned_redefinition(KerMLParser.Owned_redefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_feature_chain}.
	 * @param ctx the parse tree
	 */
	void enterOwned_feature_chain(KerMLParser.Owned_feature_chainContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_feature_chain}.
	 * @param ctx the parse tree
	 */
	void exitOwned_feature_chain(KerMLParser.Owned_feature_chainContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_chain}.
	 * @param ctx the parse tree
	 */
	void enterFeature_chain(KerMLParser.Feature_chainContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_chain}.
	 * @param ctx the parse tree
	 */
	void exitFeature_chain(KerMLParser.Feature_chainContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_feature_chaining}.
	 * @param ctx the parse tree
	 */
	void enterOwned_feature_chaining(KerMLParser.Owned_feature_chainingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_feature_chaining}.
	 * @param ctx the parse tree
	 */
	void exitOwned_feature_chaining(KerMLParser.Owned_feature_chainingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_inverting}.
	 * @param ctx the parse tree
	 */
	void enterFeature_inverting(KerMLParser.Feature_invertingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_inverting}.
	 * @param ctx the parse tree
	 */
	void exitFeature_inverting(KerMLParser.Feature_invertingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_feature_inverting}.
	 * @param ctx the parse tree
	 */
	void enterOwned_feature_inverting(KerMLParser.Owned_feature_invertingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_feature_inverting}.
	 * @param ctx the parse tree
	 */
	void exitOwned_feature_inverting(KerMLParser.Owned_feature_invertingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_featuring}.
	 * @param ctx the parse tree
	 */
	void enterType_featuring(KerMLParser.Type_featuringContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_featuring}.
	 * @param ctx the parse tree
	 */
	void exitType_featuring(KerMLParser.Type_featuringContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_type_featuring}.
	 * @param ctx the parse tree
	 */
	void enterOwned_type_featuring(KerMLParser.Owned_type_featuringContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_type_featuring}.
	 * @param ctx the parse tree
	 */
	void exitOwned_type_featuring(KerMLParser.Owned_type_featuringContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#data_type}.
	 * @param ctx the parse tree
	 */
	void enterData_type(KerMLParser.Data_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#data_type}.
	 * @param ctx the parse tree
	 */
	void exitData_type(KerMLParser.Data_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#class}.
	 * @param ctx the parse tree
	 */
	void enterClass(KerMLParser.ClassContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#class}.
	 * @param ctx the parse tree
	 */
	void exitClass(KerMLParser.ClassContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#structure}.
	 * @param ctx the parse tree
	 */
	void enterStructure(KerMLParser.StructureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#structure}.
	 * @param ctx the parse tree
	 */
	void exitStructure(KerMLParser.StructureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#association}.
	 * @param ctx the parse tree
	 */
	void enterAssociation(KerMLParser.AssociationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#association}.
	 * @param ctx the parse tree
	 */
	void exitAssociation(KerMLParser.AssociationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#association_structure}.
	 * @param ctx the parse tree
	 */
	void enterAssociation_structure(KerMLParser.Association_structureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#association_structure}.
	 * @param ctx the parse tree
	 */
	void exitAssociation_structure(KerMLParser.Association_structureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#connector}.
	 * @param ctx the parse tree
	 */
	void enterConnector(KerMLParser.ConnectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#connector}.
	 * @param ctx the parse tree
	 */
	void exitConnector(KerMLParser.ConnectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#connector_declaration}.
	 * @param ctx the parse tree
	 */
	void enterConnector_declaration(KerMLParser.Connector_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#connector_declaration}.
	 * @param ctx the parse tree
	 */
	void exitConnector_declaration(KerMLParser.Connector_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#binary_connector_declaration}.
	 * @param ctx the parse tree
	 */
	void enterBinary_connector_declaration(KerMLParser.Binary_connector_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#binary_connector_declaration}.
	 * @param ctx the parse tree
	 */
	void exitBinary_connector_declaration(KerMLParser.Binary_connector_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#nary_connector_declaration}.
	 * @param ctx the parse tree
	 */
	void enterNary_connector_declaration(KerMLParser.Nary_connector_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#nary_connector_declaration}.
	 * @param ctx the parse tree
	 */
	void exitNary_connector_declaration(KerMLParser.Nary_connector_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#connector_end_member}.
	 * @param ctx the parse tree
	 */
	void enterConnector_end_member(KerMLParser.Connector_end_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#connector_end_member}.
	 * @param ctx the parse tree
	 */
	void exitConnector_end_member(KerMLParser.Connector_end_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#connector_end}.
	 * @param ctx the parse tree
	 */
	void enterConnector_end(KerMLParser.Connector_endContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#connector_end}.
	 * @param ctx the parse tree
	 */
	void exitConnector_end(KerMLParser.Connector_endContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_cross_multiplicity_member}.
	 * @param ctx the parse tree
	 */
	void enterOwned_cross_multiplicity_member(KerMLParser.Owned_cross_multiplicity_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_cross_multiplicity_member}.
	 * @param ctx the parse tree
	 */
	void exitOwned_cross_multiplicity_member(KerMLParser.Owned_cross_multiplicity_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_cross_multiplicity}.
	 * @param ctx the parse tree
	 */
	void enterOwned_cross_multiplicity(KerMLParser.Owned_cross_multiplicityContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_cross_multiplicity}.
	 * @param ctx the parse tree
	 */
	void exitOwned_cross_multiplicity(KerMLParser.Owned_cross_multiplicityContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#binding_connector}.
	 * @param ctx the parse tree
	 */
	void enterBinding_connector(KerMLParser.Binding_connectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#binding_connector}.
	 * @param ctx the parse tree
	 */
	void exitBinding_connector(KerMLParser.Binding_connectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#binding_connector_declaration}.
	 * @param ctx the parse tree
	 */
	void enterBinding_connector_declaration(KerMLParser.Binding_connector_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#binding_connector_declaration}.
	 * @param ctx the parse tree
	 */
	void exitBinding_connector_declaration(KerMLParser.Binding_connector_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#succession}.
	 * @param ctx the parse tree
	 */
	void enterSuccession(KerMLParser.SuccessionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#succession}.
	 * @param ctx the parse tree
	 */
	void exitSuccession(KerMLParser.SuccessionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#succession_declaration}.
	 * @param ctx the parse tree
	 */
	void enterSuccession_declaration(KerMLParser.Succession_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#succession_declaration}.
	 * @param ctx the parse tree
	 */
	void exitSuccession_declaration(KerMLParser.Succession_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#behavior}.
	 * @param ctx the parse tree
	 */
	void enterBehavior(KerMLParser.BehaviorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#behavior}.
	 * @param ctx the parse tree
	 */
	void exitBehavior(KerMLParser.BehaviorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#step}.
	 * @param ctx the parse tree
	 */
	void enterStep(KerMLParser.StepContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#step}.
	 * @param ctx the parse tree
	 */
	void exitStep(KerMLParser.StepContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#function}.
	 * @param ctx the parse tree
	 */
	void enterFunction(KerMLParser.FunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#function}.
	 * @param ctx the parse tree
	 */
	void exitFunction(KerMLParser.FunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#function_body}.
	 * @param ctx the parse tree
	 */
	void enterFunction_body(KerMLParser.Function_bodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#function_body}.
	 * @param ctx the parse tree
	 */
	void exitFunction_body(KerMLParser.Function_bodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#function_body_part}.
	 * @param ctx the parse tree
	 */
	void enterFunction_body_part(KerMLParser.Function_body_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#function_body_part}.
	 * @param ctx the parse tree
	 */
	void exitFunction_body_part(KerMLParser.Function_body_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#return_feature_member}.
	 * @param ctx the parse tree
	 */
	void enterReturn_feature_member(KerMLParser.Return_feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#return_feature_member}.
	 * @param ctx the parse tree
	 */
	void exitReturn_feature_member(KerMLParser.Return_feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#result_expression_member}.
	 * @param ctx the parse tree
	 */
	void enterResult_expression_member(KerMLParser.Result_expression_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#result_expression_member}.
	 * @param ctx the parse tree
	 */
	void exitResult_expression_member(KerMLParser.Result_expression_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(KerMLParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(KerMLParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#predicate}.
	 * @param ctx the parse tree
	 */
	void enterPredicate(KerMLParser.PredicateContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#predicate}.
	 * @param ctx the parse tree
	 */
	void exitPredicate(KerMLParser.PredicateContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#boolean_expression}.
	 * @param ctx the parse tree
	 */
	void enterBoolean_expression(KerMLParser.Boolean_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#boolean_expression}.
	 * @param ctx the parse tree
	 */
	void exitBoolean_expression(KerMLParser.Boolean_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#invariant}.
	 * @param ctx the parse tree
	 */
	void enterInvariant(KerMLParser.InvariantContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#invariant}.
	 * @param ctx the parse tree
	 */
	void exitInvariant(KerMLParser.InvariantContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_expression_reference_member}.
	 * @param ctx the parse tree
	 */
	void enterOwned_expression_reference_member(KerMLParser.Owned_expression_reference_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_expression_reference_member}.
	 * @param ctx the parse tree
	 */
	void exitOwned_expression_reference_member(KerMLParser.Owned_expression_reference_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_expression_reference}.
	 * @param ctx the parse tree
	 */
	void enterOwned_expression_reference(KerMLParser.Owned_expression_referenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_expression_reference}.
	 * @param ctx the parse tree
	 */
	void exitOwned_expression_reference(KerMLParser.Owned_expression_referenceContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_expression_member}.
	 * @param ctx the parse tree
	 */
	void enterOwned_expression_member(KerMLParser.Owned_expression_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_expression_member}.
	 * @param ctx the parse tree
	 */
	void exitOwned_expression_member(KerMLParser.Owned_expression_memberContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SelectExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterSelectExpr(KerMLParser.SelectExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SelectExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitSelectExpr(KerMLParser.SelectExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code CollectExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterCollectExpr(KerMLParser.CollectExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code CollectExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitCollectExpr(KerMLParser.CollectExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BinaryExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterBinaryExpr(KerMLParser.BinaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BinaryExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitBinaryExpr(KerMLParser.BinaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ExtentExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterExtentExpr(KerMLParser.ExtentExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ExtentExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitExtentExpr(KerMLParser.ExtentExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ConditionalExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterConditionalExpr(KerMLParser.ConditionalExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ConditionalExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitConditionalExpr(KerMLParser.ConditionalExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnaryExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryExpr(KerMLParser.UnaryExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnaryExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryExpr(KerMLParser.UnaryExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code IndexExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterIndexExpr(KerMLParser.IndexExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code IndexExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitIndexExpr(KerMLParser.IndexExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BaseExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterBaseExpr(KerMLParser.BaseExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BaseExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitBaseExpr(KerMLParser.BaseExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FeatureChainExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterFeatureChainExpr(KerMLParser.FeatureChainExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FeatureChainExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitFeatureChainExpr(KerMLParser.FeatureChainExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BracketExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterBracketExpr(KerMLParser.BracketExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BracketExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitBracketExpr(KerMLParser.BracketExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code MetaclassificationExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterMetaclassificationExpr(KerMLParser.MetaclassificationExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code MetaclassificationExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitMetaclassificationExpr(KerMLParser.MetaclassificationExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ClassificationExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterClassificationExpr(KerMLParser.ClassificationExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ClassificationExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitClassificationExpr(KerMLParser.ClassificationExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SequenceExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterSequenceExpr(KerMLParser.SequenceExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SequenceExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitSequenceExpr(KerMLParser.SequenceExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FunctionOperationExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void enterFunctionOperationExpr(KerMLParser.FunctionOperationExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FunctionOperationExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 */
	void exitFunctionOperationExpr(KerMLParser.FunctionOperationExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#function_operation_arguments}.
	 * @param ctx the parse tree
	 */
	void enterFunction_operation_arguments(KerMLParser.Function_operation_argumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#function_operation_arguments}.
	 * @param ctx the parse tree
	 */
	void exitFunction_operation_arguments(KerMLParser.Function_operation_argumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_reference_member}.
	 * @param ctx the parse tree
	 */
	void enterType_reference_member(KerMLParser.Type_reference_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_reference_member}.
	 * @param ctx the parse tree
	 */
	void exitType_reference_member(KerMLParser.Type_reference_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_result_member}.
	 * @param ctx the parse tree
	 */
	void enterType_result_member(KerMLParser.Type_result_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_result_member}.
	 * @param ctx the parse tree
	 */
	void exitType_result_member(KerMLParser.Type_result_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#type_reference}.
	 * @param ctx the parse tree
	 */
	void enterType_reference(KerMLParser.Type_referenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#type_reference}.
	 * @param ctx the parse tree
	 */
	void exitType_reference(KerMLParser.Type_referenceContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#reference_typing}.
	 * @param ctx the parse tree
	 */
	void enterReference_typing(KerMLParser.Reference_typingContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#reference_typing}.
	 * @param ctx the parse tree
	 */
	void exitReference_typing(KerMLParser.Reference_typingContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#sequence_expression}.
	 * @param ctx the parse tree
	 */
	void enterSequence_expression(KerMLParser.Sequence_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#sequence_expression}.
	 * @param ctx the parse tree
	 */
	void exitSequence_expression(KerMLParser.Sequence_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#sequence_expression_list}.
	 * @param ctx the parse tree
	 */
	void enterSequence_expression_list(KerMLParser.Sequence_expression_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#sequence_expression_list}.
	 * @param ctx the parse tree
	 */
	void exitSequence_expression_list(KerMLParser.Sequence_expression_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#sequence_operator_expression}.
	 * @param ctx the parse tree
	 */
	void enterSequence_operator_expression(KerMLParser.Sequence_operator_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#sequence_operator_expression}.
	 * @param ctx the parse tree
	 */
	void exitSequence_operator_expression(KerMLParser.Sequence_operator_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#sequence_expression_list_member}.
	 * @param ctx the parse tree
	 */
	void enterSequence_expression_list_member(KerMLParser.Sequence_expression_list_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#sequence_expression_list_member}.
	 * @param ctx the parse tree
	 */
	void exitSequence_expression_list_member(KerMLParser.Sequence_expression_list_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#function_reference}.
	 * @param ctx the parse tree
	 */
	void enterFunction_reference(KerMLParser.Function_referenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#function_reference}.
	 * @param ctx the parse tree
	 */
	void exitFunction_reference(KerMLParser.Function_referenceContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_chain_member}.
	 * @param ctx the parse tree
	 */
	void enterFeature_chain_member(KerMLParser.Feature_chain_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_chain_member}.
	 * @param ctx the parse tree
	 */
	void exitFeature_chain_member(KerMLParser.Feature_chain_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_feature_chain_member}.
	 * @param ctx the parse tree
	 */
	void enterOwned_feature_chain_member(KerMLParser.Owned_feature_chain_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_feature_chain_member}.
	 * @param ctx the parse tree
	 */
	void exitOwned_feature_chain_member(KerMLParser.Owned_feature_chain_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#base_expression}.
	 * @param ctx the parse tree
	 */
	void enterBase_expression(KerMLParser.Base_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#base_expression}.
	 * @param ctx the parse tree
	 */
	void exitBase_expression(KerMLParser.Base_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#null_expression}.
	 * @param ctx the parse tree
	 */
	void enterNull_expression(KerMLParser.Null_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#null_expression}.
	 * @param ctx the parse tree
	 */
	void exitNull_expression(KerMLParser.Null_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_reference_expression}.
	 * @param ctx the parse tree
	 */
	void enterFeature_reference_expression(KerMLParser.Feature_reference_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_reference_expression}.
	 * @param ctx the parse tree
	 */
	void exitFeature_reference_expression(KerMLParser.Feature_reference_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_reference_member}.
	 * @param ctx the parse tree
	 */
	void enterFeature_reference_member(KerMLParser.Feature_reference_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_reference_member}.
	 * @param ctx the parse tree
	 */
	void exitFeature_reference_member(KerMLParser.Feature_reference_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_reference}.
	 * @param ctx the parse tree
	 */
	void enterFeature_reference(KerMLParser.Feature_referenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_reference}.
	 * @param ctx the parse tree
	 */
	void exitFeature_reference(KerMLParser.Feature_referenceContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#metadata_access_expression}.
	 * @param ctx the parse tree
	 */
	void enterMetadata_access_expression(KerMLParser.Metadata_access_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#metadata_access_expression}.
	 * @param ctx the parse tree
	 */
	void exitMetadata_access_expression(KerMLParser.Metadata_access_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#invocation_expression}.
	 * @param ctx the parse tree
	 */
	void enterInvocation_expression(KerMLParser.Invocation_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#invocation_expression}.
	 * @param ctx the parse tree
	 */
	void exitInvocation_expression(KerMLParser.Invocation_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#internal_invocation_expression}.
	 * @param ctx the parse tree
	 */
	void enterInternal_invocation_expression(KerMLParser.Internal_invocation_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#internal_invocation_expression}.
	 * @param ctx the parse tree
	 */
	void exitInternal_invocation_expression(KerMLParser.Internal_invocation_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#constructor_expression}.
	 * @param ctx the parse tree
	 */
	void enterConstructor_expression(KerMLParser.Constructor_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#constructor_expression}.
	 * @param ctx the parse tree
	 */
	void exitConstructor_expression(KerMLParser.Constructor_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#argument_list}.
	 * @param ctx the parse tree
	 */
	void enterArgument_list(KerMLParser.Argument_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#argument_list}.
	 * @param ctx the parse tree
	 */
	void exitArgument_list(KerMLParser.Argument_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#positional_argument_list}.
	 * @param ctx the parse tree
	 */
	void enterPositional_argument_list(KerMLParser.Positional_argument_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#positional_argument_list}.
	 * @param ctx the parse tree
	 */
	void exitPositional_argument_list(KerMLParser.Positional_argument_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#named_argument_list}.
	 * @param ctx the parse tree
	 */
	void enterNamed_argument_list(KerMLParser.Named_argument_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#named_argument_list}.
	 * @param ctx the parse tree
	 */
	void exitNamed_argument_list(KerMLParser.Named_argument_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#named_argument_member}.
	 * @param ctx the parse tree
	 */
	void enterNamed_argument_member(KerMLParser.Named_argument_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#named_argument_member}.
	 * @param ctx the parse tree
	 */
	void exitNamed_argument_member(KerMLParser.Named_argument_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#named_argument}.
	 * @param ctx the parse tree
	 */
	void enterNamed_argument(KerMLParser.Named_argumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#named_argument}.
	 * @param ctx the parse tree
	 */
	void exitNamed_argument(KerMLParser.Named_argumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#parameter_redefinition}.
	 * @param ctx the parse tree
	 */
	void enterParameter_redefinition(KerMLParser.Parameter_redefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#parameter_redefinition}.
	 * @param ctx the parse tree
	 */
	void exitParameter_redefinition(KerMLParser.Parameter_redefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#body_expression}.
	 * @param ctx the parse tree
	 */
	void enterBody_expression(KerMLParser.Body_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#body_expression}.
	 * @param ctx the parse tree
	 */
	void exitBody_expression(KerMLParser.Body_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#expression_body_member}.
	 * @param ctx the parse tree
	 */
	void enterExpression_body_member(KerMLParser.Expression_body_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#expression_body_member}.
	 * @param ctx the parse tree
	 */
	void exitExpression_body_member(KerMLParser.Expression_body_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#expression_body}.
	 * @param ctx the parse tree
	 */
	void enterExpression_body(KerMLParser.Expression_bodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#expression_body}.
	 * @param ctx the parse tree
	 */
	void exitExpression_body(KerMLParser.Expression_bodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#literal_expression}.
	 * @param ctx the parse tree
	 */
	void enterLiteral_expression(KerMLParser.Literal_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#literal_expression}.
	 * @param ctx the parse tree
	 */
	void exitLiteral_expression(KerMLParser.Literal_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#literal_boolean}.
	 * @param ctx the parse tree
	 */
	void enterLiteral_boolean(KerMLParser.Literal_booleanContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#literal_boolean}.
	 * @param ctx the parse tree
	 */
	void exitLiteral_boolean(KerMLParser.Literal_booleanContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#boolean_value}.
	 * @param ctx the parse tree
	 */
	void enterBoolean_value(KerMLParser.Boolean_valueContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#boolean_value}.
	 * @param ctx the parse tree
	 */
	void exitBoolean_value(KerMLParser.Boolean_valueContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#literal_string}.
	 * @param ctx the parse tree
	 */
	void enterLiteral_string(KerMLParser.Literal_stringContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#literal_string}.
	 * @param ctx the parse tree
	 */
	void exitLiteral_string(KerMLParser.Literal_stringContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#literal_integer}.
	 * @param ctx the parse tree
	 */
	void enterLiteral_integer(KerMLParser.Literal_integerContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#literal_integer}.
	 * @param ctx the parse tree
	 */
	void exitLiteral_integer(KerMLParser.Literal_integerContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#literal_real}.
	 * @param ctx the parse tree
	 */
	void enterLiteral_real(KerMLParser.Literal_realContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#literal_real}.
	 * @param ctx the parse tree
	 */
	void exitLiteral_real(KerMLParser.Literal_realContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#real_value}.
	 * @param ctx the parse tree
	 */
	void enterReal_value(KerMLParser.Real_valueContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#real_value}.
	 * @param ctx the parse tree
	 */
	void exitReal_value(KerMLParser.Real_valueContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#literal_infinity}.
	 * @param ctx the parse tree
	 */
	void enterLiteral_infinity(KerMLParser.Literal_infinityContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#literal_infinity}.
	 * @param ctx the parse tree
	 */
	void exitLiteral_infinity(KerMLParser.Literal_infinityContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#interaction}.
	 * @param ctx the parse tree
	 */
	void enterInteraction(KerMLParser.InteractionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#interaction}.
	 * @param ctx the parse tree
	 */
	void exitInteraction(KerMLParser.InteractionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_flow}.
	 * @param ctx the parse tree
	 */
	void enterItem_flow(KerMLParser.Item_flowContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_flow}.
	 * @param ctx the parse tree
	 */
	void exitItem_flow(KerMLParser.Item_flowContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#succession_item_flow}.
	 * @param ctx the parse tree
	 */
	void enterSuccession_item_flow(KerMLParser.Succession_item_flowContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#succession_item_flow}.
	 * @param ctx the parse tree
	 */
	void exitSuccession_item_flow(KerMLParser.Succession_item_flowContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_flow_declaration}.
	 * @param ctx the parse tree
	 */
	void enterItem_flow_declaration(KerMLParser.Item_flow_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_flow_declaration}.
	 * @param ctx the parse tree
	 */
	void exitItem_flow_declaration(KerMLParser.Item_flow_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_feature_member}.
	 * @param ctx the parse tree
	 */
	void enterItem_feature_member(KerMLParser.Item_feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_feature_member}.
	 * @param ctx the parse tree
	 */
	void exitItem_feature_member(KerMLParser.Item_feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_feature}.
	 * @param ctx the parse tree
	 */
	void enterItem_feature(KerMLParser.Item_featureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_feature}.
	 * @param ctx the parse tree
	 */
	void exitItem_feature(KerMLParser.Item_featureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_feature_specialization_part}.
	 * @param ctx the parse tree
	 */
	void enterItem_feature_specialization_part(KerMLParser.Item_feature_specialization_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_feature_specialization_part}.
	 * @param ctx the parse tree
	 */
	void exitItem_feature_specialization_part(KerMLParser.Item_feature_specialization_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_flow_end_member}.
	 * @param ctx the parse tree
	 */
	void enterItem_flow_end_member(KerMLParser.Item_flow_end_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_flow_end_member}.
	 * @param ctx the parse tree
	 */
	void exitItem_flow_end_member(KerMLParser.Item_flow_end_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_flow_end}.
	 * @param ctx the parse tree
	 */
	void enterItem_flow_end(KerMLParser.Item_flow_endContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_flow_end}.
	 * @param ctx the parse tree
	 */
	void exitItem_flow_end(KerMLParser.Item_flow_endContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_flow_feature_member}.
	 * @param ctx the parse tree
	 */
	void enterItem_flow_feature_member(KerMLParser.Item_flow_feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_flow_feature_member}.
	 * @param ctx the parse tree
	 */
	void exitItem_flow_feature_member(KerMLParser.Item_flow_feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_flow_feature}.
	 * @param ctx the parse tree
	 */
	void enterItem_flow_feature(KerMLParser.Item_flow_featureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_flow_feature}.
	 * @param ctx the parse tree
	 */
	void exitItem_flow_feature(KerMLParser.Item_flow_featureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#item_flow_redefinition}.
	 * @param ctx the parse tree
	 */
	void enterItem_flow_redefinition(KerMLParser.Item_flow_redefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#item_flow_redefinition}.
	 * @param ctx the parse tree
	 */
	void exitItem_flow_redefinition(KerMLParser.Item_flow_redefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#value_part}.
	 * @param ctx the parse tree
	 */
	void enterValue_part(KerMLParser.Value_partContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#value_part}.
	 * @param ctx the parse tree
	 */
	void exitValue_part(KerMLParser.Value_partContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_value}.
	 * @param ctx the parse tree
	 */
	void enterFeature_value(KerMLParser.Feature_valueContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_value}.
	 * @param ctx the parse tree
	 */
	void exitFeature_value(KerMLParser.Feature_valueContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#feature_assignment}.
	 * @param ctx the parse tree
	 */
	void enterFeature_assignment(KerMLParser.Feature_assignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#feature_assignment}.
	 * @param ctx the parse tree
	 */
	void exitFeature_assignment(KerMLParser.Feature_assignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#multiplicity}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicity(KerMLParser.MultiplicityContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#multiplicity}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicity(KerMLParser.MultiplicityContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#multiplicity_subset}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicity_subset(KerMLParser.Multiplicity_subsetContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#multiplicity_subset}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicity_subset(KerMLParser.Multiplicity_subsetContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#multiplicity_range}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicity_range(KerMLParser.Multiplicity_rangeContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#multiplicity_range}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicity_range(KerMLParser.Multiplicity_rangeContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_multiplicity}.
	 * @param ctx the parse tree
	 */
	void enterOwned_multiplicity(KerMLParser.Owned_multiplicityContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_multiplicity}.
	 * @param ctx the parse tree
	 */
	void exitOwned_multiplicity(KerMLParser.Owned_multiplicityContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#owned_multiplicity_range}.
	 * @param ctx the parse tree
	 */
	void enterOwned_multiplicity_range(KerMLParser.Owned_multiplicity_rangeContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#owned_multiplicity_range}.
	 * @param ctx the parse tree
	 */
	void exitOwned_multiplicity_range(KerMLParser.Owned_multiplicity_rangeContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#multiplicity_bounds}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicity_bounds(KerMLParser.Multiplicity_boundsContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#multiplicity_bounds}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicity_bounds(KerMLParser.Multiplicity_boundsContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#multiplicity_expression_member}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicity_expression_member(KerMLParser.Multiplicity_expression_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#multiplicity_expression_member}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicity_expression_member(KerMLParser.Multiplicity_expression_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#internal_multiplicity_expression_member}.
	 * @param ctx the parse tree
	 */
	void enterInternal_multiplicity_expression_member(KerMLParser.Internal_multiplicity_expression_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#internal_multiplicity_expression_member}.
	 * @param ctx the parse tree
	 */
	void exitInternal_multiplicity_expression_member(KerMLParser.Internal_multiplicity_expression_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#metaclass}.
	 * @param ctx the parse tree
	 */
	void enterMetaclass(KerMLParser.MetaclassContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#metaclass}.
	 * @param ctx the parse tree
	 */
	void exitMetaclass(KerMLParser.MetaclassContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#prefix_metadata_annotation}.
	 * @param ctx the parse tree
	 */
	void enterPrefix_metadata_annotation(KerMLParser.Prefix_metadata_annotationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#prefix_metadata_annotation}.
	 * @param ctx the parse tree
	 */
	void exitPrefix_metadata_annotation(KerMLParser.Prefix_metadata_annotationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#prefix_metadata_member}.
	 * @param ctx the parse tree
	 */
	void enterPrefix_metadata_member(KerMLParser.Prefix_metadata_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#prefix_metadata_member}.
	 * @param ctx the parse tree
	 */
	void exitPrefix_metadata_member(KerMLParser.Prefix_metadata_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#prefix_metadata_feature}.
	 * @param ctx the parse tree
	 */
	void enterPrefix_metadata_feature(KerMLParser.Prefix_metadata_featureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#prefix_metadata_feature}.
	 * @param ctx the parse tree
	 */
	void exitPrefix_metadata_feature(KerMLParser.Prefix_metadata_featureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#metadata_feature}.
	 * @param ctx the parse tree
	 */
	void enterMetadata_feature(KerMLParser.Metadata_featureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#metadata_feature}.
	 * @param ctx the parse tree
	 */
	void exitMetadata_feature(KerMLParser.Metadata_featureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#metadata_feature_declaration}.
	 * @param ctx the parse tree
	 */
	void enterMetadata_feature_declaration(KerMLParser.Metadata_feature_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#metadata_feature_declaration}.
	 * @param ctx the parse tree
	 */
	void exitMetadata_feature_declaration(KerMLParser.Metadata_feature_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#metadata_body}.
	 * @param ctx the parse tree
	 */
	void enterMetadata_body(KerMLParser.Metadata_bodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#metadata_body}.
	 * @param ctx the parse tree
	 */
	void exitMetadata_body(KerMLParser.Metadata_bodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#metadata_body_element}.
	 * @param ctx the parse tree
	 */
	void enterMetadata_body_element(KerMLParser.Metadata_body_elementContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#metadata_body_element}.
	 * @param ctx the parse tree
	 */
	void exitMetadata_body_element(KerMLParser.Metadata_body_elementContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#metadata_body_feature_member}.
	 * @param ctx the parse tree
	 */
	void enterMetadata_body_feature_member(KerMLParser.Metadata_body_feature_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#metadata_body_feature_member}.
	 * @param ctx the parse tree
	 */
	void exitMetadata_body_feature_member(KerMLParser.Metadata_body_feature_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#metadata_body_feature}.
	 * @param ctx the parse tree
	 */
	void enterMetadata_body_feature(KerMLParser.Metadata_body_featureContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#metadata_body_feature}.
	 * @param ctx the parse tree
	 */
	void exitMetadata_body_feature(KerMLParser.Metadata_body_featureContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#package}.
	 * @param ctx the parse tree
	 */
	void enterPackage(KerMLParser.PackageContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#package}.
	 * @param ctx the parse tree
	 */
	void exitPackage(KerMLParser.PackageContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#library_package}.
	 * @param ctx the parse tree
	 */
	void enterLibrary_package(KerMLParser.Library_packageContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#library_package}.
	 * @param ctx the parse tree
	 */
	void exitLibrary_package(KerMLParser.Library_packageContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#package_declaration}.
	 * @param ctx the parse tree
	 */
	void enterPackage_declaration(KerMLParser.Package_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#package_declaration}.
	 * @param ctx the parse tree
	 */
	void exitPackage_declaration(KerMLParser.Package_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#package_body}.
	 * @param ctx the parse tree
	 */
	void enterPackage_body(KerMLParser.Package_bodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#package_body}.
	 * @param ctx the parse tree
	 */
	void exitPackage_body(KerMLParser.Package_bodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#element_filter_member}.
	 * @param ctx the parse tree
	 */
	void enterElement_filter_member(KerMLParser.Element_filter_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#element_filter_member}.
	 * @param ctx the parse tree
	 */
	void exitElement_filter_member(KerMLParser.Element_filter_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#meta_assignment}.
	 * @param ctx the parse tree
	 */
	void enterMeta_assignment(KerMLParser.Meta_assignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#meta_assignment}.
	 * @param ctx the parse tree
	 */
	void exitMeta_assignment(KerMLParser.Meta_assignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#typed_by_operator}.
	 * @param ctx the parse tree
	 */
	void enterTyped_by_operator(KerMLParser.Typed_by_operatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#typed_by_operator}.
	 * @param ctx the parse tree
	 */
	void exitTyped_by_operator(KerMLParser.Typed_by_operatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#specializes_operator}.
	 * @param ctx the parse tree
	 */
	void enterSpecializes_operator(KerMLParser.Specializes_operatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#specializes_operator}.
	 * @param ctx the parse tree
	 */
	void exitSpecializes_operator(KerMLParser.Specializes_operatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#subsets_operator}.
	 * @param ctx the parse tree
	 */
	void enterSubsets_operator(KerMLParser.Subsets_operatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#subsets_operator}.
	 * @param ctx the parse tree
	 */
	void exitSubsets_operator(KerMLParser.Subsets_operatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#references_operator}.
	 * @param ctx the parse tree
	 */
	void enterReferences_operator(KerMLParser.References_operatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#references_operator}.
	 * @param ctx the parse tree
	 */
	void exitReferences_operator(KerMLParser.References_operatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#redefines_operator}.
	 * @param ctx the parse tree
	 */
	void enterRedefines_operator(KerMLParser.Redefines_operatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#redefines_operator}.
	 * @param ctx the parse tree
	 */
	void exitRedefines_operator(KerMLParser.Redefines_operatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#conjugates_operator}.
	 * @param ctx the parse tree
	 */
	void enterConjugates_operator(KerMLParser.Conjugates_operatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#conjugates_operator}.
	 * @param ctx the parse tree
	 */
	void exitConjugates_operator(KerMLParser.Conjugates_operatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link KerMLParser#crosses_operator}.
	 * @param ctx the parse tree
	 */
	void enterCrosses_operator(KerMLParser.Crosses_operatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link KerMLParser#crosses_operator}.
	 * @param ctx the parse tree
	 */
	void exitCrosses_operator(KerMLParser.Crosses_operatorContext ctx);
}