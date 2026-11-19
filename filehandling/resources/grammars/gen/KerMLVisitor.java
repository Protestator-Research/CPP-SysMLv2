// Generated from /home/herzog/Dokumente/Projekte/CPP-SysMLv2/filehandling/resources/grammars/KerML.g4 by ANTLR 4.13.2

    #include <sysmlv2/sysmlv2file_global.h>

import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link KerMLParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface KerMLVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link KerMLParser#start}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStart(KerMLParser.StartContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#startRule}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStartRule(KerMLParser.StartRuleContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#elements}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitElements(KerMLParser.ElementsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#identification}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdentification(KerMLParser.IdentificationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#relationship_body}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelationship_body(KerMLParser.Relationship_bodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#relationship_owned_elements}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelationship_owned_elements(KerMLParser.Relationship_owned_elementsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#relationship_owned_element}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelationship_owned_element(KerMLParser.Relationship_owned_elementContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_related_element}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_related_element(KerMLParser.Owned_related_elementContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#dependency}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDependency(KerMLParser.DependencyContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#annotation}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAnnotation(KerMLParser.AnnotationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_annotation}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_annotation(KerMLParser.Owned_annotationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#annotating_element}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAnnotating_element(KerMLParser.Annotating_elementContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#comment}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitComment(KerMLParser.CommentContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#documentation}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDocumentation(KerMLParser.DocumentationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#textual_representation}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTextual_representation(KerMLParser.Textual_representationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#root_namespace}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRoot_namespace(KerMLParser.Root_namespaceContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#namespace}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace(KerMLParser.NamespaceContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#namespace_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_declaration(KerMLParser.Namespace_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#namespace_body}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_body(KerMLParser.Namespace_bodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#namespace_body_elements}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_body_elements(KerMLParser.Namespace_body_elementsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#namespace_body_element}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_body_element(KerMLParser.Namespace_body_elementContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#member_prefix}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMember_prefix(KerMLParser.Member_prefixContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#visibility_indicator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVisibility_indicator(KerMLParser.Visibility_indicatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#namespace_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_member(KerMLParser.Namespace_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#non_feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNon_feature_member(KerMLParser.Non_feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#namespace_feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_feature_member(KerMLParser.Namespace_feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#alias_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAlias_member(KerMLParser.Alias_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#qualified_name}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitQualified_name(KerMLParser.Qualified_nameContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#namespace_import}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespace_import(KerMLParser.Namespace_importContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#import_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitImport_declaration(KerMLParser.Import_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#membership_import}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMembership_import(KerMLParser.Membership_importContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#filter_package}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFilter_package(KerMLParser.Filter_packageContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#filter_package_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFilter_package_member(KerMLParser.Filter_package_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#element}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitElement(KerMLParser.ElementContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#non_feature_element}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNon_feature_element(KerMLParser.Non_feature_elementContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_element}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_element(KerMLParser.Feature_elementContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#additional_options}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAdditional_options(KerMLParser.Additional_optionsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType(KerMLParser.TypeContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_prefix}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_prefix(KerMLParser.Type_prefixContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_declaration(KerMLParser.Type_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#specialization_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSpecialization_part(KerMLParser.Specialization_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#conjugation_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConjugation_part(KerMLParser.Conjugation_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_relationship_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_relationship_part(KerMLParser.Type_relationship_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#disjoining_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDisjoining_part(KerMLParser.Disjoining_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#unioning_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUnioning_part(KerMLParser.Unioning_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#intersecting_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIntersecting_part(KerMLParser.Intersecting_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#differencing_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDifferencing_part(KerMLParser.Differencing_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_body}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_body(KerMLParser.Type_bodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_body_elements}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_body_elements(KerMLParser.Type_body_elementsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_body_element}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_body_element(KerMLParser.Type_body_elementContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#specialization}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSpecialization(KerMLParser.SpecializationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_specialization}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_specialization(KerMLParser.Owned_specializationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#specific_type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSpecific_type(KerMLParser.Specific_typeContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#general_type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitGeneral_type(KerMLParser.General_typeContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#conjunction}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConjunction(KerMLParser.ConjunctionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_conjugation}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_conjugation(KerMLParser.Owned_conjugationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#disjoining}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDisjoining(KerMLParser.DisjoiningContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_disjoining}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_disjoining(KerMLParser.Owned_disjoiningContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#unioning}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUnioning(KerMLParser.UnioningContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#intersecting}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIntersecting(KerMLParser.IntersectingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#differencing}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDifferencing(KerMLParser.DifferencingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_member(KerMLParser.Feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_feature_member(KerMLParser.Type_feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_feature_member(KerMLParser.Owned_feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#classifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitClassifier(KerMLParser.ClassifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#classifier_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitClassifier_declaration(KerMLParser.Classifier_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#superclassing_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSuperclassing_part(KerMLParser.Superclassing_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#subclassification}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSubclassification(KerMLParser.SubclassificationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_subclassification}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_subclassification(KerMLParser.Owned_subclassificationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature(KerMLParser.FeatureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#anonymous_feature}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAnonymous_feature(KerMLParser.Anonymous_featureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_prefix}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_prefix(KerMLParser.Feature_prefixContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#end_feature_prefix}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEnd_feature_prefix(KerMLParser.End_feature_prefixContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#basic_feature_prefix}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBasic_feature_prefix(KerMLParser.Basic_feature_prefixContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_cross_feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_cross_feature_member(KerMLParser.Owned_cross_feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_cross_feature}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_cross_feature(KerMLParser.Owned_cross_featureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_direction}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_direction(KerMLParser.Feature_directionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_declaration(KerMLParser.Feature_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_identification}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_identification(KerMLParser.Feature_identificationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_relationship_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_relationship_part(KerMLParser.Feature_relationship_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#chaining_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitChaining_part(KerMLParser.Chaining_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#inverting_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInverting_part(KerMLParser.Inverting_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_featuring_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_featuring_part(KerMLParser.Type_featuring_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_specialization_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_specialization_part(KerMLParser.Feature_specialization_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#multiplicity_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiplicity_part(KerMLParser.Multiplicity_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#multiplicity_modifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiplicity_modifier(KerMLParser.Multiplicity_modifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_specialization}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_specialization(KerMLParser.Feature_specializationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#typings}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTypings(KerMLParser.TypingsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#typed_by}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTyped_by(KerMLParser.Typed_byContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#subsettings}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSubsettings(KerMLParser.SubsettingsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#subsets}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSubsets(KerMLParser.SubsetsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#references}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReferences(KerMLParser.ReferencesContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#crosses}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCrosses(KerMLParser.CrossesContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#redefinitions}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRedefinitions(KerMLParser.RedefinitionsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#redefines}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRedefines(KerMLParser.RedefinesContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_typing}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_typing(KerMLParser.Feature_typingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_feature_typing}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_feature_typing(KerMLParser.Owned_feature_typingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#subsetting}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSubsetting(KerMLParser.SubsettingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_subsetting}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_subsetting(KerMLParser.Owned_subsettingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_reference_subsetting}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_reference_subsetting(KerMLParser.Owned_reference_subsettingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_cross_subsetting}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_cross_subsetting(KerMLParser.Owned_cross_subsettingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#redefinition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRedefinition(KerMLParser.RedefinitionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_redefinition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_redefinition(KerMLParser.Owned_redefinitionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_feature_chain}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_feature_chain(KerMLParser.Owned_feature_chainContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_chain}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_chain(KerMLParser.Feature_chainContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_feature_chaining}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_feature_chaining(KerMLParser.Owned_feature_chainingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_inverting}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_inverting(KerMLParser.Feature_invertingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_feature_inverting}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_feature_inverting(KerMLParser.Owned_feature_invertingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_featuring}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_featuring(KerMLParser.Type_featuringContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_type_featuring}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_type_featuring(KerMLParser.Owned_type_featuringContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#data_type}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitData_type(KerMLParser.Data_typeContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#class}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitClass(KerMLParser.ClassContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#structure}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStructure(KerMLParser.StructureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#association}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssociation(KerMLParser.AssociationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#association_structure}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssociation_structure(KerMLParser.Association_structureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#connector}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConnector(KerMLParser.ConnectorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#connector_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConnector_declaration(KerMLParser.Connector_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#binary_connector_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBinary_connector_declaration(KerMLParser.Binary_connector_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#nary_connector_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNary_connector_declaration(KerMLParser.Nary_connector_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#connector_end_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConnector_end_member(KerMLParser.Connector_end_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#connector_end}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConnector_end(KerMLParser.Connector_endContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_cross_multiplicity_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_cross_multiplicity_member(KerMLParser.Owned_cross_multiplicity_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_cross_multiplicity}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_cross_multiplicity(KerMLParser.Owned_cross_multiplicityContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#binding_connector}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBinding_connector(KerMLParser.Binding_connectorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#binding_connector_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBinding_connector_declaration(KerMLParser.Binding_connector_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#succession}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSuccession(KerMLParser.SuccessionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#succession_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSuccession_declaration(KerMLParser.Succession_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#behavior}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBehavior(KerMLParser.BehaviorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#step}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStep(KerMLParser.StepContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#function}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction(KerMLParser.FunctionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#function_body}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction_body(KerMLParser.Function_bodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#function_body_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction_body_part(KerMLParser.Function_body_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#return_feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReturn_feature_member(KerMLParser.Return_feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#result_expression_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitResult_expression_member(KerMLParser.Result_expression_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression(KerMLParser.ExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#predicate}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPredicate(KerMLParser.PredicateContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#boolean_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBoolean_expression(KerMLParser.Boolean_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#invariant}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInvariant(KerMLParser.InvariantContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_expression_reference_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_expression_reference_member(KerMLParser.Owned_expression_reference_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_expression_reference}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_expression_reference(KerMLParser.Owned_expression_referenceContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_expression_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_expression_member(KerMLParser.Owned_expression_memberContext ctx);
	/**
	 * Visit a parse tree produced by the {@code SelectExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSelectExpr(KerMLParser.SelectExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code CollectExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCollectExpr(KerMLParser.CollectExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code BinaryExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBinaryExpr(KerMLParser.BinaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ExtentExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExtentExpr(KerMLParser.ExtentExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ConditionalExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConditionalExpr(KerMLParser.ConditionalExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code UnaryExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUnaryExpr(KerMLParser.UnaryExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code IndexExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIndexExpr(KerMLParser.IndexExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code BaseExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBaseExpr(KerMLParser.BaseExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code FeatureChainExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeatureChainExpr(KerMLParser.FeatureChainExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code BracketExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBracketExpr(KerMLParser.BracketExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code MetaclassificationExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetaclassificationExpr(KerMLParser.MetaclassificationExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ClassificationExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitClassificationExpr(KerMLParser.ClassificationExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code SequenceExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSequenceExpr(KerMLParser.SequenceExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code FunctionOperationExpr}
	 * labeled alternative in {@link KerMLParser#owned_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionOperationExpr(KerMLParser.FunctionOperationExprContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#function_operation_arguments}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction_operation_arguments(KerMLParser.Function_operation_argumentsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_reference_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_reference_member(KerMLParser.Type_reference_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_result_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_result_member(KerMLParser.Type_result_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#type_reference}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitType_reference(KerMLParser.Type_referenceContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#reference_typing}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReference_typing(KerMLParser.Reference_typingContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#sequence_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSequence_expression(KerMLParser.Sequence_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#sequence_expression_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSequence_expression_list(KerMLParser.Sequence_expression_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#sequence_operator_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSequence_operator_expression(KerMLParser.Sequence_operator_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#sequence_expression_list_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSequence_expression_list_member(KerMLParser.Sequence_expression_list_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#function_reference}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunction_reference(KerMLParser.Function_referenceContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_chain_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_chain_member(KerMLParser.Feature_chain_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_feature_chain_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_feature_chain_member(KerMLParser.Owned_feature_chain_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#base_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBase_expression(KerMLParser.Base_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#null_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNull_expression(KerMLParser.Null_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_reference_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_reference_expression(KerMLParser.Feature_reference_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_reference_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_reference_member(KerMLParser.Feature_reference_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_reference}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_reference(KerMLParser.Feature_referenceContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#metadata_access_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetadata_access_expression(KerMLParser.Metadata_access_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#invocation_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInvocation_expression(KerMLParser.Invocation_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#internal_invocation_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInternal_invocation_expression(KerMLParser.Internal_invocation_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#constructor_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConstructor_expression(KerMLParser.Constructor_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#argument_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgument_list(KerMLParser.Argument_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#positional_argument_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPositional_argument_list(KerMLParser.Positional_argument_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#named_argument_list}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamed_argument_list(KerMLParser.Named_argument_listContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#named_argument_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamed_argument_member(KerMLParser.Named_argument_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#named_argument}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamed_argument(KerMLParser.Named_argumentContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#parameter_redefinition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParameter_redefinition(KerMLParser.Parameter_redefinitionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#body_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBody_expression(KerMLParser.Body_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#expression_body_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression_body_member(KerMLParser.Expression_body_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#expression_body}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression_body(KerMLParser.Expression_bodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#literal_expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteral_expression(KerMLParser.Literal_expressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#literal_boolean}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteral_boolean(KerMLParser.Literal_booleanContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#boolean_value}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBoolean_value(KerMLParser.Boolean_valueContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#literal_string}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteral_string(KerMLParser.Literal_stringContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#literal_integer}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteral_integer(KerMLParser.Literal_integerContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#literal_real}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteral_real(KerMLParser.Literal_realContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#real_value}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReal_value(KerMLParser.Real_valueContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#literal_infinity}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteral_infinity(KerMLParser.Literal_infinityContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#interaction}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInteraction(KerMLParser.InteractionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_flow}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_flow(KerMLParser.Item_flowContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#succession_item_flow}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSuccession_item_flow(KerMLParser.Succession_item_flowContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_flow_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_flow_declaration(KerMLParser.Item_flow_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_feature_member(KerMLParser.Item_feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_feature}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_feature(KerMLParser.Item_featureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_feature_specialization_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_feature_specialization_part(KerMLParser.Item_feature_specialization_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_flow_end_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_flow_end_member(KerMLParser.Item_flow_end_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_flow_end}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_flow_end(KerMLParser.Item_flow_endContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_flow_feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_flow_feature_member(KerMLParser.Item_flow_feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_flow_feature}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_flow_feature(KerMLParser.Item_flow_featureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#item_flow_redefinition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem_flow_redefinition(KerMLParser.Item_flow_redefinitionContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#value_part}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitValue_part(KerMLParser.Value_partContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_value}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_value(KerMLParser.Feature_valueContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#feature_assignment}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFeature_assignment(KerMLParser.Feature_assignmentContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#multiplicity}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiplicity(KerMLParser.MultiplicityContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#multiplicity_subset}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiplicity_subset(KerMLParser.Multiplicity_subsetContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#multiplicity_range}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiplicity_range(KerMLParser.Multiplicity_rangeContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_multiplicity}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_multiplicity(KerMLParser.Owned_multiplicityContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#owned_multiplicity_range}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitOwned_multiplicity_range(KerMLParser.Owned_multiplicity_rangeContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#multiplicity_bounds}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiplicity_bounds(KerMLParser.Multiplicity_boundsContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#multiplicity_expression_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiplicity_expression_member(KerMLParser.Multiplicity_expression_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#internal_multiplicity_expression_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitInternal_multiplicity_expression_member(KerMLParser.Internal_multiplicity_expression_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#metaclass}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetaclass(KerMLParser.MetaclassContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#prefix_metadata_annotation}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrefix_metadata_annotation(KerMLParser.Prefix_metadata_annotationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#prefix_metadata_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrefix_metadata_member(KerMLParser.Prefix_metadata_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#prefix_metadata_feature}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPrefix_metadata_feature(KerMLParser.Prefix_metadata_featureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#metadata_feature}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetadata_feature(KerMLParser.Metadata_featureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#metadata_feature_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetadata_feature_declaration(KerMLParser.Metadata_feature_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#metadata_body}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetadata_body(KerMLParser.Metadata_bodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#metadata_body_element}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetadata_body_element(KerMLParser.Metadata_body_elementContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#metadata_body_feature_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetadata_body_feature_member(KerMLParser.Metadata_body_feature_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#metadata_body_feature}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMetadata_body_feature(KerMLParser.Metadata_body_featureContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#package}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPackage(KerMLParser.PackageContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#library_package}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLibrary_package(KerMLParser.Library_packageContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#package_declaration}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPackage_declaration(KerMLParser.Package_declarationContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#package_body}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPackage_body(KerMLParser.Package_bodyContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#element_filter_member}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitElement_filter_member(KerMLParser.Element_filter_memberContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#meta_assignment}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMeta_assignment(KerMLParser.Meta_assignmentContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#typed_by_operator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTyped_by_operator(KerMLParser.Typed_by_operatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#specializes_operator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSpecializes_operator(KerMLParser.Specializes_operatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#subsets_operator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSubsets_operator(KerMLParser.Subsets_operatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#references_operator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitReferences_operator(KerMLParser.References_operatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#redefines_operator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRedefines_operator(KerMLParser.Redefines_operatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#conjugates_operator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConjugates_operator(KerMLParser.Conjugates_operatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link KerMLParser#crosses_operator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCrosses_operator(KerMLParser.Crosses_operatorContext ctx);
}