
    #include <sysmlv2/sysmlv2file_global.h>


    #include <sysmlv2/sysmlv2file_global.h>


// Generated from ./SysMLv2.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class SYSMLV2FILE_EXPORT SysMLv2Parser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, CROSSES = 2, KEYWORD_ACCEPT = 3, KEYWORD_ACTION = 4, KEYWORD_ACTOR = 5, 
    KEYWORD_AFTER = 6, KEYWORD_ALIAS = 7, KEYWORD_ALLOCATE = 8, KEYWORD_ALLOCATION = 9, 
    KEYWORD_ANALYSIS = 10, KEYWORD_ASSIGN = 11, KEYWORD_ASSERT = 12, KEYWORD_ASSUME = 13, 
    KEYWORD_AT = 14, KEYWORD_ATTRIBUTE = 15, KEYWORD_BIND = 16, KEYWORD_BLOCK = 17, 
    KEYWORD_CALC = 18, KEYWORD_CASE = 19, KEYWORD_CONCERN = 20, KEYWORD_CONNECT = 21, 
    KEYWORD_CONNECTION = 22, KEYWORD_CONSTRAINT = 23, KEYWORD_CROSSES = 24, 
    KEYWORD_DECIDE = 25, KEYWORD_DEF = 26, KEYWORD_DEFINED = 27, KEYWORD_DERIVED = 28, 
    KEYWORD_DO = 29, KEYWORD_ENTRY = 30, KEYWORD_ENUM = 31, KEYWORD_EVENT = 32, 
    KEYWORD_EXHIBIT = 33, KEYWORD_EXIT = 34, KEYWORD_EXPOSE = 35, KEYWORD_FORK = 36, 
    KEYWORD_FRAME = 37, KEYWORD_GUARD = 38, KEYWORD_INCLUDE = 39, KEYWORD_INDIVIDUAL = 40, 
    KEYWORD_INTERFACE = 41, KEYWORD_ITEM = 42, KEYWORD_JOIN = 43, KEYWORD_LOOP = 44, 
    KEYWORD_MERGE = 45, KEYWORD_MESSAGE = 46, KEYWORD_NONUNIQUE = 47, KEYWORD_OBJECTIVE = 48, 
    KEYWORD_OCCURRENCE = 49, KEYWORD_PARALLEL = 50, KEYWORD_PART = 51, KEYWORD_PERFORM = 52, 
    KEYWORD_PORT = 53, KEYWORD_REF = 54, KEYWORD_REFERENCES = 55, KEYWORD_RENDER = 56, 
    KEYWORD_RENDERING = 57, KEYWORD_REQUIRE = 58, KEYWORD_REQUIREMENT = 59, 
    KEYWORD_SATISFY = 60, KEYWORD_SEND = 61, KEYWORD_SNAPSHOT = 62, KEYWORD_STAKEHOLDER = 63, 
    KEYWORD_STATE = 64, KEYWORD_SUBJECT = 65, KEYWORD_TERMINATE = 66, KEYWORD_TIMESLICE = 67, 
    KEYWORD_TRANSITION = 68, KEYWORD_TRIGGER = 69, KEYWORD_UNTIL = 70, KEYWORD_USE = 71, 
    KEYWORD_VARIANT = 72, KEYWORD_VARIATION = 73, KEYWORD_VERIFICATION = 74, 
    KEYWORD_VERIFY = 75, KEYWORD_VIA = 76, KEYWORD_VIEW = 77, KEYWORD_VIEWPOINT = 78, 
    KEYWORD_WHEN = 79, KEYWORD_WHILE = 80, SYMBOL_CROSSES = 81, MULTIPLICITY_PART_ELEMENTS = 82, 
    TYPED_BY = 83, SPECIALIZES = 84, SUBSETS = 85, REFERENCES = 86, REDEFINES = 87, 
    CONJUGATES = 88, KEYWORD_ABOUT = 89, KEYWORD_ABSTRACT = 90, KEYWORD_ALL = 91, 
    KEYWORD_AND = 92, KEYWORD_AS = 93, KEYWORD_ASSOC = 94, KEYWORD_BEHAVIOR = 95, 
    KEYWORD_BINDING = 96, KEYWORD_BOOL = 97, KEYWORD_BY = 98, KEYWORD_CHAINS = 99, 
    KEYWORD_CLASS = 100, KEYWORD_CLASSIFIER = 101, KEYWORD_COMMENT = 102, 
    KEYWORD_COMPOSITE = 103, KEYWORD_CONJUGATE = 104, KEYWORD_CONJUGATES = 105, 
    KEYWORD_CONJUGATION = 106, KEYWORD_CONNECTOR = 107, KEYWORD_DATATYPE = 108, 
    KEYWORD_DEFAULT = 109, KEYWORD_DEPENDENCY = 110, KEYWORD_DIFFERENCES = 111, 
    KEYWORD_DISJOINING = 112, KEYWORD_DISJOINT = 113, KEYWORD_DOC = 114, 
    KEYWORD_ELSE = 115, KEYWORD_END = 116, KEYWORD_EXPR = 117, KEYWORD_FALSE = 118, 
    KEYWORD_FEATURE = 119, KEYWORD_FEATURED = 120, KEYWORD_FEATURING = 121, 
    KEYWORD_FILTER = 122, KEYWORD_FIRST = 123, KEYWORD_FLOW = 124, KEYWORD_FOR = 125, 
    KEYWORD_FROM = 126, KEYWORD_FUNCTION = 127, KEYWORD_HASTYPE = 128, KEYWORD_IF = 129, 
    KEYWORD_INTERSECTS = 130, KEYWORD_IMPLIES = 131, KEYWORD_IMPORT = 132, 
    KEYWORD_IN = 133, KEYWORD_INOUT = 134, KEYWORD_INTERACTION = 135, KEYWORD_INV = 136, 
    KEYWORD_INVERSE = 137, KEYWORD_INVERTING = 138, KEYWORD_ISTYPE = 139, 
    KEYWORD_LANGUAGE = 140, KEYWORD_MEMBER = 141, KEYWORD_METACLASS = 142, 
    KEYWORD_METADATA = 143, KEYWORD_MULTIPLICITY = 144, KEYWORD_NAMESPACE = 145, 
    KEYWORD_NOT = 146, KEYWORD_NULL = 147, KEYWORD_OF = 148, KEYWORD_OR = 149, 
    KEYWORD_ORDERED = 150, KEYWORD_OUT = 151, KEYWORD_PACKAGE = 152, KEYWORD_PORTION = 153, 
    KEYWORD_PREDICATE = 154, KEYWORD_PRIVATE = 155, KEYWORD_PROTECTED = 156, 
    KEYWORD_PUBLIC = 157, KEYWORD_READONLY = 158, KEYWORD_REDEFINES = 159, 
    KEYWORD_REDEFINITION = 160, KEYWORD_REP = 161, KEYWORD_RETURN = 162, 
    KEYWORD_SPECIALIZATION = 163, KEYWORD_SPECIALIZES = 164, KEYWORD_STEP = 165, 
    KEYWORD_STRUCT = 166, KEYWORD_SUBCLASSIFIER = 167, KEYWORD_SUBSET = 168, 
    KEYWORD_SUBSETS = 169, KEYWORD_SUBTYPE = 170, KEYWORD_SUCCESSION = 171, 
    KEYWORD_THEN = 172, KEYWORD_TO = 173, KEYWORD_TRUE = 174, KEYWORD_TYPE = 175, 
    KEYWORD_TYPED = 176, KEYWORD_TYPING = 177, KEYWORD_UNIONS = 178, KEYWORD_XOR = 179, 
    KEYWORD_VAR = 180, KEYWORD_LOCALE = 181, KEYWORD_STANDARD = 182, KEYWORD_LIBRARY = 183, 
    KEYWORD_CONSTANT = 184, SINGLE_LINE_NOTE = 185, MULTI_LINE_NOTE = 186, 
    REGULAR_COMMENT = 187, SYMBOL_COMMENT_BLOCK_START = 188, SYMBOL_NOTE_BLOCK_START = 189, 
    SYMBOL_COMMENT_BLOCK_END = 190, SYMBOL_STATEMENT_DELIMITER = 191, SYMBOL_STAR = 192, 
    SYMBOL_NAMESPACE_SUBSET = 193, SYMBOL_TYPED_BY = 194, SYMBOL_SPECIALIZES = 195, 
    SYMBOL_REFERENCES = 196, SYMBOL_REDEFINES = 197, SYMBOL_CONJUGATES = 198, 
    SYMBOL_ROUND_BRACKET_OPEN = 199, SYMBOL_ROUND_BRACKET_CLOSE = 200, SYMBOL_CURLY_BRACKET_OPEN = 201, 
    SYMBOL_CURLY_BRACKET_CLOSE = 202, SYMBOL_SQUARE_BRACKET_OPEN = 203, 
    SYMBOL_SQUARE_BRACKET_CLOSE = 204, SYMBOL_COMMA = 205, SYMBOL_AT = 206, 
    SYMBOL_HASHTAG = 207, SYMBOL_MOD = 208, SYMBOL_AND = 209, SYMBOL_UPPER = 210, 
    SYMBOL_VERTICAL_LINE = 211, SYMBOL_DOUBLE_STAR = 212, SYMBOL_PLUS = 213, 
    SYMBOL_MINUS = 214, SYMBOL_SLASH = 215, SYMBOL_ARROW = 216, SYMBOL_DOT = 217, 
    SYMBOL_DDOT = 218, SYMBOL_SMALLER = 219, SYMBOL_SMALLER_EQUAL = 220, 
    SYMBOL_ASSIGN = 221, SYMBOL_DEF_ASSIGN = 222, SYMBOL_EQUALS = 223, SYMBOL_IFF_EQUALS = 224, 
    SYMBOL_NOT_EQUALS = 225, SYMBOL_IFF_NOT_EQUALS = 226, SYMBOL_GREATER = 227, 
    SYMBOL_GREATER_EQUALS = 228, SYMBOL_QUESTION = 229, SYMBOL_DQUESTION = 230, 
    SYMBOL_DOT_QUESTION = 231, NAME = 232, BASIC_NAME = 233, UNRESTRICTED_NAME = 234, 
    DECIMAL_VALUE = 235, EXPONENTIAL_VALUE = 236, STRING_VALUE = 237, WS = 238, 
    SYMBOL_CONJUNGATES = 239, KEYWORD_SUCCSESSION = 240, KEYWORD_INDIVIDIAL = 241, 
    KEYWORD_TRANSISTION = 242
  };

  enum {
    RuleStart = 0, RuleStart_element = 1, RuleStartRule = 2, RuleRelationship_body = 3, 
    RuleDependency = 4, RuleDependency_declaration = 5, RuleAnnotation = 6, 
    RuleOwned_annotation = 7, RuleAnnotating_member = 8, RuleAnnotating_element = 9, 
    RuleComment = 10, RuleDocumentation = 11, RuleTextual_representation = 12, 
    RuleRoot_namespace = 13, RulePackage = 14, RulePackage_body = 15, RulePackage_body_element = 16, 
    RulePackage_member = 17, RuleAlias_member = 18, RuleDefinition_element = 19, 
    RuleUsage_element = 20, RuleBasic_definition_prefix = 21, RuleDefinition_extension_keyword = 22, 
    RuleDefinition_prefix = 23, RuleDefinition = 24, RuleDefinition_declaration = 25, 
    RuleDefinition_body = 26, RuleDefinition_body_item = 27, RuleDefinition_member = 28, 
    RuleVariant_usage_member = 29, RuleNon_occurrence_usage_member = 30, 
    RuleOccurrence_usage_member = 31, RuleStructure_usage_member = 32, RuleBehavior_usage_member = 33, 
    RuleFeature_direction = 34, RuleRef_prefix = 35, RuleBasic_usage_prefix = 36, 
    RuleEnd_usage_prefix = 37, RuleOwned_cross_feature_member = 38, RuleOwned_cross_feature = 39, 
    RuleUsage_extention_keyword = 40, RuleUnextended_usage_prefix = 41, 
    RuleUsage_prefix = 42, RuleUsage = 43, RuleUsage_declaration = 44, RuleUsage_completion = 45, 
    RuleUsage_body = 46, RuleDefault_reference_usage = 47, RuleReference_usage = 48, 
    RuleVariant_reference = 49, RuleNon_occurrence_usage_element = 50, RuleOccurrence_usage_element = 51, 
    RuleStructure_usage_element = 52, RuleBehavior_usage_element = 53, RuleVariant_usage_element = 54, 
    RuleSubsclassification_part = 55, RuleCrosses = 56, RuleOwned_cross_subsetting = 57, 
    RuleMultiplicity_part = 58, RuleOwned_multiplicity = 59, RuleMultiplicity_range = 60, 
    RuleAttribute_definition = 61, RuleAttribute_usage = 62, RuleEnumeration_definition = 63, 
    RuleEnumeration_body = 64, RuleEnumeration_usage_member = 65, RuleEnumerated_value = 66, 
    RuleEnumeration_usage = 67, RuleOccurrence_definition_prefix = 68, RuleOccurrence_definition = 69, 
    RuleIndividual_definition = 70, RuleOccurrence_usage_prefix = 71, RuleOccurrence_usage = 72, 
    RuleIndividual_usage = 73, RulePortion_usage = 74, RulePortion_kind = 75, 
    RuleEvent_occurrence_usage = 76, RuleSource_succession_member = 77, 
    RuleSource_succession = 78, RuleSource_end_member = 79, RuleSource_end = 80, 
    RuleItem_definition = 81, RuleItem_usage = 82, RulePart_definition = 83, 
    RulePart_usage = 84, RulePort_definition = 85, RulePort_usage = 86, 
    RuleConjungated_port_typing = 87, RuleConnection_definition = 88, RuleConnection_usage = 89, 
    RuleConnector_part = 90, RuleBinary_connector_part = 91, RuleNary_connector_part = 92, 
    RuleConnector_end_member = 93, RuleConnecotr_end = 94, RuleOwned_cross_multiplicity_member = 95, 
    RuleOwned_cross_multiplicity = 96, RuleBinding_connector_as_usage = 97, 
    RuleBinding_end_usage_member = 98, RuleSuccession_as_usage = 99, RuleInterface_definition = 100, 
    RuleInterface_body = 101, RuleInterface_body_item = 102, RuleInterface_non_occurrence_usage_member = 103, 
    RuleInterface_non_occurrence_usage_element = 104, RuleInterface_occurrence_usage_member = 105, 
    RuleInterface_occurrence_usage_element = 106, RuleDefault_interface_end = 107, 
    RuleInterface_usage = 108, RuleInterface_usage_declaration = 109, RuleInterface_part = 110, 
    RuleBinary_interface_part = 111, RuleNary_interface_part = 112, RuleInterface_end_member = 113, 
    RuleInterface_end = 114, RuleAllocation_definition = 115, RuleAllocation_usage = 116, 
    RuleAllocation_usage_declaration = 117, RuleFlow_definition = 118, RuleMessage = 119, 
    RuleMessage_declaration = 120, RuleMessage_event_member = 121, RuleMessage_event = 122, 
    RuleFlow_usage = 123, RuleSuccession_flow_usage = 124, RuleFlow_declaration = 125, 
    RuleFlow_payload_feature_member = 126, RuleFlow_payload_feature = 127, 
    RulePayload_feature = 128, RulePayload_feature_specialization_part = 129, 
    RuleFlow_end_member = 130, RuleFlow_end = 131, RuleFlow_end_subsetting = 132, 
    RuleFeature_chain_prefix = 133, RuleFlow_feature_member = 134, RuleFlow_feature = 135, 
    RuleFlow_feature_redefinition = 136, RuleAction_definition = 137, RuleAction_body = 138, 
    RuleAction_body_item = 139, RuleNon_behavior_body_item = 140, RuleAction_behavior_member = 141, 
    RuleInitial_node_member = 142, RuleAction_node_member = 143, RuleAction_target_succession_member = 144, 
    RuleGuarded_succession_member = 145, RuleAction_usage = 146, RuleAction_usage_declaration = 147, 
    RulePerform_action_usage = 148, RulePerform_action_usage_declaration = 149, 
    RuleAction_node = 150, RuleAction_node_usage_declaration = 151, RuleAction_node_prefix = 152, 
    RuleControl_node = 153, RuleControl_node_prefix = 154, RuleMerge_node = 155, 
    RuleDecision_node = 156, RuleJoin_node = 157, RuleFork_node = 158, RuleAccept_node = 159, 
    RuleAccept_node_declaration = 160, RuleAccept_parameter_part = 161, 
    RulePayload_parameter_member = 162, RulePayload_parameter = 163, RuleTrigger_value_part = 164, 
    RuleTrigger_expression = 165, RuleSend_node = 166, RuleSend_node_declaration = 167, 
    RuleSender_receiver_part = 168, RuleNode_parameter_member = 169, RuleNode_parameter = 170, 
    RuleFeature_binding = 171, RuleAssignment_node = 172, RuleAssignment_node_declaration = 173, 
    RuleAssignment_target_member = 174, RuleAssignment_target_parameter = 175, 
    RuleAssignment_target_binding = 176, RuleFeature_chain_member = 177, 
    RuleOwned_feature_chain_member = 178, RuleTerminate_node = 179, RuleIf_node = 180, 
    RuleExpression_parameter_member = 181, RuleAction_body_parameter_member = 182, 
    RuleAction_body_parameter = 183, RuleIf_node_parameter_member = 184, 
    RuleWhile_loop_node = 185, RuleFor_loop_node = 186, RuleFor_variable_declaration_member = 187, 
    RuleFor_variable_declaration = 188, RuleAction_target_succession = 189, 
    RuleTarget_succession = 190, RuleGuarded_target_succession = 191, RuleDefault_target_succession = 192, 
    RuleGuarded_succession = 193, RuleState_definition = 194, RuleState_def_body = 195, 
    RuleState_body_item = 196, RuleEntry_action_member = 197, RuleDo_action_member = 198, 
    RuleExit_action_member = 199, RuleEntry_transition_member = 200, RuleState_action_usage = 201, 
    RuleEmpty_action_usage = 202, RuleState_perform_action_uage = 203, RuleState_accept_action_usage = 204, 
    RuleState_send_action_usage = 205, RuleState_assignment_action_usage = 206, 
    RuleTransition_usage_member = 207, RuleTarget_transition_usage_member = 208, 
    RuleState_usage = 209, RuleState_usage_body = 210, RuleExhibit_state_usage = 211, 
    RuleTransition_usage = 212, RuleTarget_transition_usage = 213, RuleTrigger_action_member = 214, 
    RuleTrigger_action = 215, RuleGuard_expression_member = 216, RuleEffect_behavior_member = 217, 
    RuleEffect_behavior_usage = 218, RuleTransition_perform_action_usage = 219, 
    RuleTransition_accept_action_usage = 220, RuleTransition_send_action_usage = 221, 
    RuleTransition_assignment_action_usage = 222, RuleTransition_succession_member = 223, 
    RuleTransition_succession = 224, RuleCalculation_definition = 225, RuleCalculation_usage = 226, 
    RuleCalculation_body = 227, RuleCalculation_body_part = 228, RuleCalculation_body_item = 229, 
    RuleReturn_parameter_member = 230, RuleResult_expression_member = 231, 
    RuleConstraint_definition = 232, RuleConstraint_usage = 233, RuleAssert_constriant_usage = 234, 
    RuleConstraint_usage_declaration = 235, RuleRequirement_definition = 236, 
    RuleRequirement_body = 237, RuleRequirement_body_item = 238, RuleSubject_member = 239, 
    RuleSubject_usage = 240, RuleRequirement_constraint_member = 241, RuleRequriement_kind = 242, 
    RuleRequirement_constraint_usage = 243, RuleFramed_concern_member = 244, 
    RuleFramed_concern_usage = 245, RuleActor_member = 246, RuleActor_usage = 247, 
    RuleStakeholder_member = 248, RuleStakeholder_usage = 249, RuleRequirement_usage = 250, 
    RuleSatisfy_requirement_usage = 251, RuleSatisfaction_subject_member = 252, 
    RuleSatisfaction_parameter = 253, RuleSatisfaction_feature_value = 254, 
    RuleSatisfaction_reference_expression = 255, RuleConcern_definition = 256, 
    RuleConcern_usage = 257, RuleCase_definition = 258, RuleCase_usage = 259, 
    RuleCase_body = 260, RuleCase_body_item = 261, RuleObjective_member = 262, 
    RuleObjective_requirement_usage = 263, RuleAnalysis_case_definition = 264, 
    RuleAnalysis_case_usage = 265, RuleVerification_case_definition = 266, 
    RuleVerification_case_usage = 267, RuleRequirement_verification_member = 268, 
    RuleRequirement_verification_usage = 269, RuleUse_case_definition = 270, 
    RuleUse_case_usage = 271, RuleInclude_use_case_usage = 272, RuleView_definition = 273, 
    RuleView_definition_body = 274, RuleView_definition_body_item = 275, 
    RuleView_rendering_member = 276, RuleView_rendering_usage = 277, RuleView_usage = 278, 
    RuleView_body = 279, RuleView_body_item = 280, RuleExpose = 281, RuleMembership_expose = 282, 
    RuleNamespace_expose = 283, RuleViewpoint_definition = 284, RuleViewpoint_usage = 285, 
    RuleRendering_definition = 286, RuleRendering_usage = 287, RuleMetadata_definition = 288, 
    RulePrefix_metadata_annotation = 289, RulePrefix_metadata_member = 290, 
    RulePrefix_metadata_usage = 291, RuleMetadata_usage = 292, RuleMetadata_usage_declaration = 293, 
    RuleMetadata_body = 294, RuleMetadata_body_usage_member = 295, RuleMetadata_body_usage = 296, 
    RuleExtended_definition = 297, RuleExtended_usage = 298, RuleDefined_by = 299, 
    RuleElements = 300, RuleIdentification = 301, RuleRelationship_owned_elements = 302, 
    RuleRelationship_owned_element = 303, RuleOwned_related_element = 304, 
    RuleNamespace = 305, RuleNamespace_declaration = 306, RuleNamespace_body = 307, 
    RuleNamespace_body_elements = 308, RuleNamespace_body_element = 309, 
    RuleMember_prefix = 310, RuleVisibility_indicator = 311, RuleNamespace_member = 312, 
    RuleNon_feature_member = 313, RuleNamespace_feature_member = 314, RuleQualified_name = 315, 
    RuleNamespace_import = 316, RuleImport_declaration = 317, RuleMembership_import = 318, 
    RuleFilter_package = 319, RuleFilter_package_member = 320, RuleElement = 321, 
    RuleNon_feature_element = 322, RuleFeature_element = 323, RuleAdditional_options = 324, 
    RuleType = 325, RuleType_prefix = 326, RuleType_declaration = 327, RuleSpecialization_part = 328, 
    RuleConjugation_part = 329, RuleType_relationship_part = 330, RuleDisjoining_part = 331, 
    RuleUnioning_part = 332, RuleIntersecting_part = 333, RuleDifferencing_part = 334, 
    RuleType_body = 335, RuleType_body_elements = 336, RuleType_body_element = 337, 
    RuleSpecialization = 338, RuleOwned_specialization = 339, RuleSpecific_type = 340, 
    RuleGeneral_type = 341, RuleConjunction = 342, RuleOwned_conjugation = 343, 
    RuleDisjoining = 344, RuleOwned_disjoining = 345, RuleUnioning = 346, 
    RuleIntersecting = 347, RuleDifferencing = 348, RuleFeature_member = 349, 
    RuleType_feature_member = 350, RuleOwned_feature_member = 351, RuleClassifier = 352, 
    RuleClassifier_declaration = 353, RuleSuperclassing_part = 354, RuleSubclassification = 355, 
    RuleOwned_subclassification = 356, RuleFeature = 357, RuleFeature_prefix = 358, 
    RuleFeature_declaration = 359, RuleFeature_identification = 360, RuleFeature_relationship_part = 361, 
    RuleChaining_part = 362, RuleInverting_part = 363, RuleType_featuring_part = 364, 
    RuleFeature_specialization_part = 365, RuleFeature_specialization = 366, 
    RuleTypings = 367, RuleTyped_by = 368, RuleSubsettings = 369, RuleSubsets = 370, 
    RuleReferences = 371, RuleRedefinitions = 372, RuleRedefines = 373, 
    RuleFeature_typing = 374, RuleOwned_feature_typing = 375, RuleSubsetting = 376, 
    RuleOwned_subsetting = 377, RuleOwned_reference_subsetting = 378, RuleRedefinition = 379, 
    RuleOwned_redefinition = 380, RuleOwned_feature_chain = 381, RuleFeature_chain = 382, 
    RuleOwned_feature_chaining = 383, RuleFeature_inverting = 384, RuleOwned_feature_inverting = 385, 
    RuleType_featuring = 386, RuleOwned_type_featuring = 387, RuleData_type = 388, 
    RuleClass = 389, RuleStructure = 390, RuleAssociation = 391, RuleAssociation_structure = 392, 
    RuleConnector = 393, RuleConnector_declaration = 394, RuleBinary_connector_declaration = 395, 
    RuleNary_connector_declaration = 396, RuleConnector_end = 397, RuleBinding_connector = 398, 
    RuleBinding_connector_declaration = 399, RuleSuccession = 400, RuleSuccession_declaration = 401, 
    RuleBehavior = 402, RuleStep = 403, RuleFunction = 404, RuleFunction_body = 405, 
    RuleFunction_body_part = 406, RuleReturn_feature_member = 407, RuleExpression = 408, 
    RulePredicate = 409, RuleBoolean_expression = 410, RuleInvariant = 411, 
    RuleOwned_expression_reference_member = 412, RuleOwned_expression_reference = 413, 
    RuleOwned_expression_member = 414, RuleOwned_expressions = 415, RuleOwned_expression = 416, 
    RuleEased_owned_expression = 417, RuleConditional_expression = 418, 
    RuleConditional_binary_operator_expression = 419, RuleConditional_binary_operator = 420, 
    RuleBinary_operator_expression = 421, RuleBinary_operator = 422, RuleUnary_operator_expression = 423, 
    RuleUnary_operator = 424, RuleClassification_expression = 425, RuleClassification = 426, 
    RuleClassification_test_operator = 427, RuleCast_operator = 428, RuleMetaclassification_expression = 429, 
    RuleArgument_member = 430, RuleArgument = 431, RuleArgument_value = 432, 
    RuleArgument_expression_member = 433, RuleArgument_expression = 434, 
    RuleArgument_expression_value = 435, RuleMetadata_argument_member = 436, 
    RuleMetadata_argument = 437, RuleMetadata_value = 438, RuleMetadata_reference = 439, 
    RuleMetadataclassification_test_operator = 440, RuleMeta_cast_operator = 441, 
    RuleExtend_expression = 442, RuleType_reference_member = 443, RuleType_result_member = 444, 
    RuleType_reference = 445, RuleReference_typing = 446, RulePrimary_expressions = 447, 
    RulePrimary_expression = 448, RulePrimary_argument_value = 449, RulePrimary_argument = 450, 
    RulePrimary_argument_member = 451, RuleNon_feature_chain_primary_expression = 452, 
    RuleNon_feature_chain_primary_argument_value = 453, RuleNon_feature_chain_primary_argument = 454, 
    RuleNon_feature_chain_primary_argument_member = 455, RuleBracket_expression = 456, 
    RuleIndex_expression = 457, RuleSequence_expression = 458, RuleSequence_expression_list = 459, 
    RuleSequence_operator_expression = 460, RuleSequence_expression_list_member = 461, 
    RuleFeature_chain_expression = 462, RuleCollect_expression = 463, RuleSelect_expression = 464, 
    RuleFunction_operation_expression = 465, RuleBody_argument_member = 466, 
    RuleBody_argument = 467, RuleBody_argument_value = 468, RuleBody_expression_member = 469, 
    RuleFunction_reference_argument_member = 470, RuleFunction_reference_argument = 471, 
    RuleFunction_reference_arugment_value = 472, RuleFunction_reference_expression = 473, 
    RuleFunction_reference_member = 474, RuleFunction_reference = 475, RuleBase_expression = 476, 
    RuleNull_expression = 477, RuleFeature_reference_expression = 478, RuleFeature_reference_member = 479, 
    RuleFeature_reference = 480, RuleMetadata_access_expression = 481, RuleInvocation_expression = 482, 
    RuleInternal_invocation_expression = 483, RuleArgument_list = 484, RulePositional_argument_list = 485, 
    RuleNamed_argument_list = 486, RuleNamed_argument_member = 487, RuleNamed_argument = 488, 
    RuleParameter_redefinition = 489, RuleBody_expression = 490, RuleExpression_body_member = 491, 
    RuleExpression_body = 492, RuleLiteral_expression = 493, RuleLiteral_boolean = 494, 
    RuleBoolean_value = 495, RuleLiteral_string = 496, RuleLiteral_integer = 497, 
    RuleLiteral_real = 498, RuleReal_value = 499, RuleLiteral_infinity = 500, 
    RuleInteraction = 501, RuleItem_flow = 502, RuleSuccession_item_flow = 503, 
    RuleItem_flow_declaration = 504, RuleItem_feature_member = 505, RuleItem_feature = 506, 
    RuleItem_feature_specialization_part = 507, RuleItem_flow_end_member = 508, 
    RuleItem_flow_end = 509, RuleItem_flow_feature_member = 510, RuleItem_flow_feature = 511, 
    RuleItem_flow_redefinition = 512, RuleValue_part = 513, RuleFeature_value = 514, 
    RuleFeature_assignment = 515, RuleMultiplicity = 516, RuleMultiplicity_subset = 517, 
    RuleOwned_multiplicity_range = 518, RuleMultiplicity_bounds = 519, RuleMultiplicity_expression_member = 520, 
    RuleInternal_multiplicity_expression_member = 521, RuleMetaclass = 522, 
    RulePrefix_metadata_feature = 523, RuleMetadata_feature = 524, RuleMetadata_feature_declaration = 525, 
    RuleMetadata_body_element = 526, RuleMetadata_body_feature_member = 527, 
    RuleMetadata_body_feature = 528, RuleLibrary_package = 529, RulePackage_declaration = 530, 
    RuleElement_filter_member = 531, RuleMeta_assignment = 532
  };

  explicit SysMLv2Parser(antlr4::TokenStream *input);

  SysMLv2Parser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~SysMLv2Parser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class StartContext;
  class Start_elementContext;
  class StartRuleContext;
  class Relationship_bodyContext;
  class DependencyContext;
  class Dependency_declarationContext;
  class AnnotationContext;
  class Owned_annotationContext;
  class Annotating_memberContext;
  class Annotating_elementContext;
  class CommentContext;
  class DocumentationContext;
  class Textual_representationContext;
  class Root_namespaceContext;
  class PackageContext;
  class Package_bodyContext;
  class Package_body_elementContext;
  class Package_memberContext;
  class Alias_memberContext;
  class Definition_elementContext;
  class Usage_elementContext;
  class Basic_definition_prefixContext;
  class Definition_extension_keywordContext;
  class Definition_prefixContext;
  class DefinitionContext;
  class Definition_declarationContext;
  class Definition_bodyContext;
  class Definition_body_itemContext;
  class Definition_memberContext;
  class Variant_usage_memberContext;
  class Non_occurrence_usage_memberContext;
  class Occurrence_usage_memberContext;
  class Structure_usage_memberContext;
  class Behavior_usage_memberContext;
  class Feature_directionContext;
  class Ref_prefixContext;
  class Basic_usage_prefixContext;
  class End_usage_prefixContext;
  class Owned_cross_feature_memberContext;
  class Owned_cross_featureContext;
  class Usage_extention_keywordContext;
  class Unextended_usage_prefixContext;
  class Usage_prefixContext;
  class UsageContext;
  class Usage_declarationContext;
  class Usage_completionContext;
  class Usage_bodyContext;
  class Default_reference_usageContext;
  class Reference_usageContext;
  class Variant_referenceContext;
  class Non_occurrence_usage_elementContext;
  class Occurrence_usage_elementContext;
  class Structure_usage_elementContext;
  class Behavior_usage_elementContext;
  class Variant_usage_elementContext;
  class Subsclassification_partContext;
  class CrossesContext;
  class Owned_cross_subsettingContext;
  class Multiplicity_partContext;
  class Owned_multiplicityContext;
  class Multiplicity_rangeContext;
  class Attribute_definitionContext;
  class Attribute_usageContext;
  class Enumeration_definitionContext;
  class Enumeration_bodyContext;
  class Enumeration_usage_memberContext;
  class Enumerated_valueContext;
  class Enumeration_usageContext;
  class Occurrence_definition_prefixContext;
  class Occurrence_definitionContext;
  class Individual_definitionContext;
  class Occurrence_usage_prefixContext;
  class Occurrence_usageContext;
  class Individual_usageContext;
  class Portion_usageContext;
  class Portion_kindContext;
  class Event_occurrence_usageContext;
  class Source_succession_memberContext;
  class Source_successionContext;
  class Source_end_memberContext;
  class Source_endContext;
  class Item_definitionContext;
  class Item_usageContext;
  class Part_definitionContext;
  class Part_usageContext;
  class Port_definitionContext;
  class Port_usageContext;
  class Conjungated_port_typingContext;
  class Connection_definitionContext;
  class Connection_usageContext;
  class Connector_partContext;
  class Binary_connector_partContext;
  class Nary_connector_partContext;
  class Connector_end_memberContext;
  class Connecotr_endContext;
  class Owned_cross_multiplicity_memberContext;
  class Owned_cross_multiplicityContext;
  class Binding_connector_as_usageContext;
  class Binding_end_usage_memberContext;
  class Succession_as_usageContext;
  class Interface_definitionContext;
  class Interface_bodyContext;
  class Interface_body_itemContext;
  class Interface_non_occurrence_usage_memberContext;
  class Interface_non_occurrence_usage_elementContext;
  class Interface_occurrence_usage_memberContext;
  class Interface_occurrence_usage_elementContext;
  class Default_interface_endContext;
  class Interface_usageContext;
  class Interface_usage_declarationContext;
  class Interface_partContext;
  class Binary_interface_partContext;
  class Nary_interface_partContext;
  class Interface_end_memberContext;
  class Interface_endContext;
  class Allocation_definitionContext;
  class Allocation_usageContext;
  class Allocation_usage_declarationContext;
  class Flow_definitionContext;
  class MessageContext;
  class Message_declarationContext;
  class Message_event_memberContext;
  class Message_eventContext;
  class Flow_usageContext;
  class Succession_flow_usageContext;
  class Flow_declarationContext;
  class Flow_payload_feature_memberContext;
  class Flow_payload_featureContext;
  class Payload_featureContext;
  class Payload_feature_specialization_partContext;
  class Flow_end_memberContext;
  class Flow_endContext;
  class Flow_end_subsettingContext;
  class Feature_chain_prefixContext;
  class Flow_feature_memberContext;
  class Flow_featureContext;
  class Flow_feature_redefinitionContext;
  class Action_definitionContext;
  class Action_bodyContext;
  class Action_body_itemContext;
  class Non_behavior_body_itemContext;
  class Action_behavior_memberContext;
  class Initial_node_memberContext;
  class Action_node_memberContext;
  class Action_target_succession_memberContext;
  class Guarded_succession_memberContext;
  class Action_usageContext;
  class Action_usage_declarationContext;
  class Perform_action_usageContext;
  class Perform_action_usage_declarationContext;
  class Action_nodeContext;
  class Action_node_usage_declarationContext;
  class Action_node_prefixContext;
  class Control_nodeContext;
  class Control_node_prefixContext;
  class Merge_nodeContext;
  class Decision_nodeContext;
  class Join_nodeContext;
  class Fork_nodeContext;
  class Accept_nodeContext;
  class Accept_node_declarationContext;
  class Accept_parameter_partContext;
  class Payload_parameter_memberContext;
  class Payload_parameterContext;
  class Trigger_value_partContext;
  class Trigger_expressionContext;
  class Send_nodeContext;
  class Send_node_declarationContext;
  class Sender_receiver_partContext;
  class Node_parameter_memberContext;
  class Node_parameterContext;
  class Feature_bindingContext;
  class Assignment_nodeContext;
  class Assignment_node_declarationContext;
  class Assignment_target_memberContext;
  class Assignment_target_parameterContext;
  class Assignment_target_bindingContext;
  class Feature_chain_memberContext;
  class Owned_feature_chain_memberContext;
  class Terminate_nodeContext;
  class If_nodeContext;
  class Expression_parameter_memberContext;
  class Action_body_parameter_memberContext;
  class Action_body_parameterContext;
  class If_node_parameter_memberContext;
  class While_loop_nodeContext;
  class For_loop_nodeContext;
  class For_variable_declaration_memberContext;
  class For_variable_declarationContext;
  class Action_target_successionContext;
  class Target_successionContext;
  class Guarded_target_successionContext;
  class Default_target_successionContext;
  class Guarded_successionContext;
  class State_definitionContext;
  class State_def_bodyContext;
  class State_body_itemContext;
  class Entry_action_memberContext;
  class Do_action_memberContext;
  class Exit_action_memberContext;
  class Entry_transition_memberContext;
  class State_action_usageContext;
  class Empty_action_usageContext;
  class State_perform_action_uageContext;
  class State_accept_action_usageContext;
  class State_send_action_usageContext;
  class State_assignment_action_usageContext;
  class Transition_usage_memberContext;
  class Target_transition_usage_memberContext;
  class State_usageContext;
  class State_usage_bodyContext;
  class Exhibit_state_usageContext;
  class Transition_usageContext;
  class Target_transition_usageContext;
  class Trigger_action_memberContext;
  class Trigger_actionContext;
  class Guard_expression_memberContext;
  class Effect_behavior_memberContext;
  class Effect_behavior_usageContext;
  class Transition_perform_action_usageContext;
  class Transition_accept_action_usageContext;
  class Transition_send_action_usageContext;
  class Transition_assignment_action_usageContext;
  class Transition_succession_memberContext;
  class Transition_successionContext;
  class Calculation_definitionContext;
  class Calculation_usageContext;
  class Calculation_bodyContext;
  class Calculation_body_partContext;
  class Calculation_body_itemContext;
  class Return_parameter_memberContext;
  class Result_expression_memberContext;
  class Constraint_definitionContext;
  class Constraint_usageContext;
  class Assert_constriant_usageContext;
  class Constraint_usage_declarationContext;
  class Requirement_definitionContext;
  class Requirement_bodyContext;
  class Requirement_body_itemContext;
  class Subject_memberContext;
  class Subject_usageContext;
  class Requirement_constraint_memberContext;
  class Requriement_kindContext;
  class Requirement_constraint_usageContext;
  class Framed_concern_memberContext;
  class Framed_concern_usageContext;
  class Actor_memberContext;
  class Actor_usageContext;
  class Stakeholder_memberContext;
  class Stakeholder_usageContext;
  class Requirement_usageContext;
  class Satisfy_requirement_usageContext;
  class Satisfaction_subject_memberContext;
  class Satisfaction_parameterContext;
  class Satisfaction_feature_valueContext;
  class Satisfaction_reference_expressionContext;
  class Concern_definitionContext;
  class Concern_usageContext;
  class Case_definitionContext;
  class Case_usageContext;
  class Case_bodyContext;
  class Case_body_itemContext;
  class Objective_memberContext;
  class Objective_requirement_usageContext;
  class Analysis_case_definitionContext;
  class Analysis_case_usageContext;
  class Verification_case_definitionContext;
  class Verification_case_usageContext;
  class Requirement_verification_memberContext;
  class Requirement_verification_usageContext;
  class Use_case_definitionContext;
  class Use_case_usageContext;
  class Include_use_case_usageContext;
  class View_definitionContext;
  class View_definition_bodyContext;
  class View_definition_body_itemContext;
  class View_rendering_memberContext;
  class View_rendering_usageContext;
  class View_usageContext;
  class View_bodyContext;
  class View_body_itemContext;
  class ExposeContext;
  class Membership_exposeContext;
  class Namespace_exposeContext;
  class Viewpoint_definitionContext;
  class Viewpoint_usageContext;
  class Rendering_definitionContext;
  class Rendering_usageContext;
  class Metadata_definitionContext;
  class Prefix_metadata_annotationContext;
  class Prefix_metadata_memberContext;
  class Prefix_metadata_usageContext;
  class Metadata_usageContext;
  class Metadata_usage_declarationContext;
  class Metadata_bodyContext;
  class Metadata_body_usage_memberContext;
  class Metadata_body_usageContext;
  class Extended_definitionContext;
  class Extended_usageContext;
  class Defined_byContext;
  class ElementsContext;
  class IdentificationContext;
  class Relationship_owned_elementsContext;
  class Relationship_owned_elementContext;
  class Owned_related_elementContext;
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
  class Feature_declarationContext;
  class Feature_identificationContext;
  class Feature_relationship_partContext;
  class Chaining_partContext;
  class Inverting_partContext;
  class Type_featuring_partContext;
  class Feature_specialization_partContext;
  class Feature_specializationContext;
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
  class ExpressionContext;
  class PredicateContext;
  class Boolean_expressionContext;
  class InvariantContext;
  class Owned_expression_reference_memberContext;
  class Owned_expression_referenceContext;
  class Owned_expression_memberContext;
  class Owned_expressionsContext;
  class Owned_expressionContext;
  class Eased_owned_expressionContext;
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
  class Argument_memberContext;
  class ArgumentContext;
  class Argument_valueContext;
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
  class Primary_argument_valueContext;
  class Primary_argumentContext;
  class Primary_argument_memberContext;
  class Non_feature_chain_primary_expressionContext;
  class Non_feature_chain_primary_argument_valueContext;
  class Non_feature_chain_primary_argumentContext;
  class Non_feature_chain_primary_argument_memberContext;
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
  class Owned_multiplicity_rangeContext;
  class Multiplicity_boundsContext;
  class Multiplicity_expression_memberContext;
  class Internal_multiplicity_expression_memberContext;
  class MetaclassContext;
  class Prefix_metadata_featureContext;
  class Metadata_featureContext;
  class Metadata_feature_declarationContext;
  class Metadata_body_elementContext;
  class Metadata_body_feature_memberContext;
  class Metadata_body_featureContext;
  class Library_packageContext;
  class Package_declarationContext;
  class Element_filter_memberContext;
  class Meta_assignmentContext; 

  class SYSMLV2FILE_EXPORT StartContext : public antlr4::ParserRuleContext {
  public:
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<Start_elementContext *> start_element();
    Start_elementContext* start_element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StartContext* start();

  class SYSMLV2FILE_EXPORT Start_elementContext : public antlr4::ParserRuleContext {
  public:
    Start_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementContext *element();
    Usage_elementContext *usage_element();
    Definition_elementContext *definition_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Start_elementContext* start_element();

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

  class SYSMLV2FILE_EXPORT Relationship_bodyContext : public antlr4::ParserRuleContext {
  public:
    Relationship_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Owned_annotationContext *owned_annotation();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Relationship_bodyContext* relationship_body();

  class SYSMLV2FILE_EXPORT DependencyContext : public antlr4::ParserRuleContext {
  public:
    DependencyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_DEPENDENCY();
    Dependency_declarationContext *dependency_declaration();
    Relationship_bodyContext *relationship_body();
    std::vector<Prefix_metadata_annotationContext *> prefix_metadata_annotation();
    Prefix_metadata_annotationContext* prefix_metadata_annotation(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DependencyContext* dependency();

  class SYSMLV2FILE_EXPORT Dependency_declarationContext : public antlr4::ParserRuleContext {
  public:
    Dependency_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Qualified_nameContext *> qualified_name();
    Qualified_nameContext* qualified_name(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Dependency_declarationContext* dependency_declaration();

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

  class SYSMLV2FILE_EXPORT Annotating_memberContext : public antlr4::ParserRuleContext {
  public:
    Annotating_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotating_elementContext *annotating_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Annotating_memberContext* annotating_member();

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
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *KEYWORD_LOCALE();
    antlr4::tree::TerminalNode *STRING_VALUE();
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
    IdentificationContext *identification();
    antlr4::tree::TerminalNode *REGULAR_COMMENT();
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
    std::vector<Package_body_elementContext *> package_body_element();
    Package_body_elementContext* package_body_element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Root_namespaceContext* root_namespace();

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

  class SYSMLV2FILE_EXPORT Package_bodyContext : public antlr4::ParserRuleContext {
  public:
    Package_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Package_body_elementContext *> package_body_element();
    Package_body_elementContext* package_body_element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Package_bodyContext* package_body();

  class SYSMLV2FILE_EXPORT Package_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Package_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Package_memberContext *package_member();
    Element_filter_memberContext *element_filter_member();
    Alias_memberContext *alias_member();
    Namespace_importContext *namespace_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Package_body_elementContext* package_body_element();

  class SYSMLV2FILE_EXPORT Package_memberContext : public antlr4::ParserRuleContext {
  public:
    Package_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_elementContext *usage_element();
    Definition_elementContext *definition_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Package_memberContext* package_member();

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

  class SYSMLV2FILE_EXPORT Definition_elementContext : public antlr4::ParserRuleContext {
  public:
    Definition_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PackageContext *package();
    Library_packageContext *library_package();
    Annotating_elementContext *annotating_element();
    DependencyContext *dependency();
    Attribute_definitionContext *attribute_definition();
    Enumeration_definitionContext *enumeration_definition();
    Occurrence_definitionContext *occurrence_definition();
    Individual_definitionContext *individual_definition();
    Item_definitionContext *item_definition();
    Part_definitionContext *part_definition();
    Connection_definitionContext *connection_definition();
    Flow_definitionContext *flow_definition();
    Interface_definitionContext *interface_definition();
    Port_definitionContext *port_definition();
    Action_definitionContext *action_definition();
    Calculation_definitionContext *calculation_definition();
    State_definitionContext *state_definition();
    Constraint_definitionContext *constraint_definition();
    Requirement_definitionContext *requirement_definition();
    Concern_definitionContext *concern_definition();
    Case_definitionContext *case_definition();
    Analysis_case_definitionContext *analysis_case_definition();
    Verification_case_definitionContext *verification_case_definition();
    View_definitionContext *view_definition();
    Viewpoint_definitionContext *viewpoint_definition();
    Rendering_definitionContext *rendering_definition();
    Metadata_definitionContext *metadata_definition();
    Extended_definitionContext *extended_definition();
    Non_feature_elementContext *non_feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Definition_elementContext* definition_element();

  class SYSMLV2FILE_EXPORT Usage_elementContext : public antlr4::ParserRuleContext {
  public:
    Usage_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_occurrence_usage_elementContext *non_occurrence_usage_element();
    Occurrence_usage_elementContext *occurrence_usage_element();
    Feature_elementContext *feature_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Usage_elementContext* usage_element();

  class SYSMLV2FILE_EXPORT Basic_definition_prefixContext : public antlr4::ParserRuleContext {
  public:
    Basic_definition_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ABSTRACT();
    antlr4::tree::TerminalNode *KEYWORD_VARIATION();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Basic_definition_prefixContext* basic_definition_prefix();

  class SYSMLV2FILE_EXPORT Definition_extension_keywordContext : public antlr4::ParserRuleContext {
  public:
    Definition_extension_keywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Prefix_metadata_memberContext *prefix_metadata_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Definition_extension_keywordContext* definition_extension_keyword();

  class SYSMLV2FILE_EXPORT Definition_prefixContext : public antlr4::ParserRuleContext {
  public:
    Definition_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Basic_definition_prefixContext *basic_definition_prefix();
    std::vector<Definition_extension_keywordContext *> definition_extension_keyword();
    Definition_extension_keywordContext* definition_extension_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Definition_prefixContext* definition_prefix();

  class SYSMLV2FILE_EXPORT DefinitionContext : public antlr4::ParserRuleContext {
  public:
    DefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_declarationContext *definition_declaration();
    Definition_bodyContext *definition_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DefinitionContext* definition();

  class SYSMLV2FILE_EXPORT Definition_declarationContext : public antlr4::ParserRuleContext {
  public:
    Definition_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentificationContext *identification();
    Subsclassification_partContext *subsclassification_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Definition_declarationContext* definition_declaration();

  class SYSMLV2FILE_EXPORT Definition_bodyContext : public antlr4::ParserRuleContext {
  public:
    Definition_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Definition_body_itemContext *> definition_body_item();
    Definition_body_itemContext* definition_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Definition_bodyContext* definition_body();

  class SYSMLV2FILE_EXPORT Definition_body_itemContext : public antlr4::ParserRuleContext {
  public:
    Definition_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_memberContext *definition_member();
    Variant_usage_memberContext *variant_usage_member();
    Non_occurrence_usage_memberContext *non_occurrence_usage_member();
    Occurrence_usage_memberContext *occurrence_usage_member();
    Source_succession_memberContext *source_succession_member();
    Alias_memberContext *alias_member();
    Namespace_importContext *namespace_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Definition_body_itemContext* definition_body_item();

  class SYSMLV2FILE_EXPORT Definition_memberContext : public antlr4::ParserRuleContext {
  public:
    Definition_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Definition_elementContext *definition_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Definition_memberContext* definition_member();

  class SYSMLV2FILE_EXPORT Variant_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Variant_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_VARIANT();
    Variant_usage_elementContext *variant_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variant_usage_memberContext* variant_usage_member();

  class SYSMLV2FILE_EXPORT Non_occurrence_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Non_occurrence_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Non_occurrence_usage_elementContext *non_occurrence_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Non_occurrence_usage_memberContext* non_occurrence_usage_member();

  class SYSMLV2FILE_EXPORT Occurrence_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Occurrence_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Occurrence_usage_elementContext *occurrence_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Occurrence_usage_memberContext* occurrence_usage_member();

  class SYSMLV2FILE_EXPORT Structure_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Structure_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Structure_usage_elementContext *structure_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Structure_usage_memberContext* structure_usage_member();

  class SYSMLV2FILE_EXPORT Behavior_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Behavior_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Behavior_usage_elementContext *behavior_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Behavior_usage_memberContext* behavior_usage_member();

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

  class SYSMLV2FILE_EXPORT Ref_prefixContext : public antlr4::ParserRuleContext {
  public:
    Ref_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_directionContext *feature_direction();
    antlr4::tree::TerminalNode *KEYWORD_DERIVED();
    antlr4::tree::TerminalNode *KEYWORD_VARIATION();
    antlr4::tree::TerminalNode *KEYWORD_CONSTANT();
    antlr4::tree::TerminalNode *KEYWORD_ABSTRACT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref_prefixContext* ref_prefix();

  class SYSMLV2FILE_EXPORT Basic_usage_prefixContext : public antlr4::ParserRuleContext {
  public:
    Basic_usage_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Ref_prefixContext *ref_prefix();
    antlr4::tree::TerminalNode *KEYWORD_REF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Basic_usage_prefixContext* basic_usage_prefix();

  class SYSMLV2FILE_EXPORT End_usage_prefixContext : public antlr4::ParserRuleContext {
  public:
    End_usage_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_END();
    Owned_cross_feature_memberContext *owned_cross_feature_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  End_usage_prefixContext* end_usage_prefix();

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
    Basic_usage_prefixContext *basic_usage_prefix();
    Usage_declarationContext *usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_cross_featureContext* owned_cross_feature();

  class SYSMLV2FILE_EXPORT Usage_extention_keywordContext : public antlr4::ParserRuleContext {
  public:
    Usage_extention_keywordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Prefix_metadata_memberContext *prefix_metadata_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Usage_extention_keywordContext* usage_extention_keyword();

  class SYSMLV2FILE_EXPORT Unextended_usage_prefixContext : public antlr4::ParserRuleContext {
  public:
    Unextended_usage_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    End_usage_prefixContext *end_usage_prefix();
    Basic_usage_prefixContext *basic_usage_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Unextended_usage_prefixContext* unextended_usage_prefix();

  class SYSMLV2FILE_EXPORT Usage_prefixContext : public antlr4::ParserRuleContext {
  public:
    Usage_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unextended_usage_prefixContext *unextended_usage_prefix();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Usage_prefixContext* usage_prefix();

  class SYSMLV2FILE_EXPORT UsageContext : public antlr4::ParserRuleContext {
  public:
    UsageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_declarationContext *usage_declaration();
    Usage_completionContext *usage_completion();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UsageContext* usage();

  class SYSMLV2FILE_EXPORT Usage_declarationContext : public antlr4::ParserRuleContext {
  public:
    Usage_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentificationContext *identification();
    Feature_specialization_partContext *feature_specialization_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Usage_declarationContext* usage_declaration();

  class SYSMLV2FILE_EXPORT Usage_completionContext : public antlr4::ParserRuleContext {
  public:
    Usage_completionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_bodyContext *usage_body();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Usage_completionContext* usage_completion();

  class SYSMLV2FILE_EXPORT Usage_bodyContext : public antlr4::ParserRuleContext {
  public:
    Usage_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_bodyContext *definition_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Usage_bodyContext* usage_body();

  class SYSMLV2FILE_EXPORT Default_reference_usageContext : public antlr4::ParserRuleContext {
  public:
    Default_reference_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Ref_prefixContext *ref_prefix();
    UsageContext *usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Default_reference_usageContext* default_reference_usage();

  class SYSMLV2FILE_EXPORT Reference_usageContext : public antlr4::ParserRuleContext {
  public:
    Reference_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_REF();
    UsageContext *usage();
    End_usage_prefixContext *end_usage_prefix();
    Ref_prefixContext *ref_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Reference_usageContext* reference_usage();

  class SYSMLV2FILE_EXPORT Variant_referenceContext : public antlr4::ParserRuleContext {
  public:
    Variant_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    Usage_bodyContext *usage_body();
    std::vector<Feature_specializationContext *> feature_specialization();
    Feature_specializationContext* feature_specialization(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variant_referenceContext* variant_reference();

  class SYSMLV2FILE_EXPORT Non_occurrence_usage_elementContext : public antlr4::ParserRuleContext {
  public:
    Non_occurrence_usage_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Default_reference_usageContext *default_reference_usage();
    Reference_usageContext *reference_usage();
    Attribute_usageContext *attribute_usage();
    Enumeration_usageContext *enumeration_usage();
    Binding_connector_as_usageContext *binding_connector_as_usage();
    Succession_as_usageContext *succession_as_usage();
    Extended_usageContext *extended_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Non_occurrence_usage_elementContext* non_occurrence_usage_element();

  class SYSMLV2FILE_EXPORT Occurrence_usage_elementContext : public antlr4::ParserRuleContext {
  public:
    Occurrence_usage_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Structure_usage_elementContext *structure_usage_element();
    Behavior_usage_elementContext *behavior_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Occurrence_usage_elementContext* occurrence_usage_element();

  class SYSMLV2FILE_EXPORT Structure_usage_elementContext : public antlr4::ParserRuleContext {
  public:
    Structure_usage_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usageContext *occurrence_usage();
    Individual_usageContext *individual_usage();
    Portion_usageContext *portion_usage();
    Event_occurrence_usageContext *event_occurrence_usage();
    Item_usageContext *item_usage();
    Part_usageContext *part_usage();
    View_usageContext *view_usage();
    Rendering_usageContext *rendering_usage();
    Port_usageContext *port_usage();
    Connection_usageContext *connection_usage();
    Interface_usageContext *interface_usage();
    Allocation_usageContext *allocation_usage();
    MessageContext *message();
    Flow_usageContext *flow_usage();
    Succession_flow_usageContext *succession_flow_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Structure_usage_elementContext* structure_usage_element();

  class SYSMLV2FILE_EXPORT Behavior_usage_elementContext : public antlr4::ParserRuleContext {
  public:
    Behavior_usage_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Action_usageContext *action_usage();
    Calculation_usageContext *calculation_usage();
    State_usageContext *state_usage();
    Constraint_usageContext *constraint_usage();
    Requirement_usageContext *requirement_usage();
    Concern_usageContext *concern_usage();
    Case_usageContext *case_usage();
    Analysis_case_usageContext *analysis_case_usage();
    Verification_case_usageContext *verification_case_usage();
    Use_case_usageContext *use_case_usage();
    Viewpoint_usageContext *viewpoint_usage();
    Perform_action_usageContext *perform_action_usage();
    Exhibit_state_usageContext *exhibit_state_usage();
    Include_use_case_usageContext *include_use_case_usage();
    Assert_constriant_usageContext *assert_constriant_usage();
    Satisfy_requirement_usageContext *satisfy_requirement_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Behavior_usage_elementContext* behavior_usage_element();

  class SYSMLV2FILE_EXPORT Variant_usage_elementContext : public antlr4::ParserRuleContext {
  public:
    Variant_usage_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Variant_referenceContext *variant_reference();
    Reference_usageContext *reference_usage();
    Attribute_usageContext *attribute_usage();
    Binding_connector_as_usageContext *binding_connector_as_usage();
    Succession_as_usageContext *succession_as_usage();
    Occurrence_usageContext *occurrence_usage();
    Individual_usageContext *individual_usage();
    Portion_usageContext *portion_usage();
    Event_occurrence_usageContext *event_occurrence_usage();
    Item_usageContext *item_usage();
    Part_usageContext *part_usage();
    View_usageContext *view_usage();
    Rendering_usageContext *rendering_usage();
    Port_usageContext *port_usage();
    Connection_usageContext *connection_usage();
    Interface_usageContext *interface_usage();
    Allocation_usageContext *allocation_usage();
    MessageContext *message();
    Flow_usageContext *flow_usage();
    Succession_flow_usageContext *succession_flow_usage();
    Behavior_usage_elementContext *behavior_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variant_usage_elementContext* variant_usage_element();

  class SYSMLV2FILE_EXPORT Subsclassification_partContext : public antlr4::ParserRuleContext {
  public:
    Subsclassification_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SPECIALIZES();
    std::vector<Owned_subclassificationContext *> owned_subclassification();
    Owned_subclassificationContext* owned_subclassification(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Subsclassification_partContext* subsclassification_part();

  class SYSMLV2FILE_EXPORT CrossesContext : public antlr4::ParserRuleContext {
  public:
    CrossesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CROSSES();
    Owned_cross_subsettingContext *owned_cross_subsetting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CrossesContext* crosses();

  class SYSMLV2FILE_EXPORT Owned_cross_subsettingContext : public antlr4::ParserRuleContext {
  public:
    Owned_cross_subsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_cross_subsettingContext* owned_cross_subsetting();

  class SYSMLV2FILE_EXPORT Multiplicity_partContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_multiplicityContext *owned_multiplicity();
    antlr4::tree::TerminalNode *KEYWORD_NONUNIQUE();
    antlr4::tree::TerminalNode *KEYWORD_ORDERED();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Multiplicity_partContext* multiplicity_part();

  class SYSMLV2FILE_EXPORT Owned_multiplicityContext : public antlr4::ParserRuleContext {
  public:
    Owned_multiplicityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Multiplicity_rangeContext *multiplicity_range();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_multiplicityContext* owned_multiplicity();

  class SYSMLV2FILE_EXPORT Multiplicity_rangeContext : public antlr4::ParserRuleContext {
  public:
    Multiplicity_rangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
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

  Multiplicity_rangeContext* multiplicity_range();

  class SYSMLV2FILE_EXPORT Attribute_definitionContext : public antlr4::ParserRuleContext {
  public:
    Attribute_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_prefixContext *definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ATTRIBUTE();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Attribute_definitionContext* attribute_definition();

  class SYSMLV2FILE_EXPORT Attribute_usageContext : public antlr4::ParserRuleContext {
  public:
    Attribute_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_prefixContext *usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ATTRIBUTE();
    UsageContext *usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Attribute_usageContext* attribute_usage();

  class SYSMLV2FILE_EXPORT Enumeration_definitionContext : public antlr4::ParserRuleContext {
  public:
    Enumeration_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ENUM();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Enumeration_bodyContext *enumeration_body();
    std::vector<Definition_extension_keywordContext *> definition_extension_keyword();
    Definition_extension_keywordContext* definition_extension_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enumeration_definitionContext* enumeration_definition();

  class SYSMLV2FILE_EXPORT Enumeration_bodyContext : public antlr4::ParserRuleContext {
  public:
    Enumeration_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Annotating_memberContext *> annotating_member();
    Annotating_memberContext* annotating_member(size_t i);
    std::vector<Enumeration_usage_memberContext *> enumeration_usage_member();
    Enumeration_usage_memberContext* enumeration_usage_member(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enumeration_bodyContext* enumeration_body();

  class SYSMLV2FILE_EXPORT Enumeration_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Enumeration_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Enumerated_valueContext *enumerated_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enumeration_usage_memberContext* enumeration_usage_member();

  class SYSMLV2FILE_EXPORT Enumerated_valueContext : public antlr4::ParserRuleContext {
  public:
    Enumerated_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UsageContext *usage();
    antlr4::tree::TerminalNode *KEYWORD_ENUM();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enumerated_valueContext* enumerated_value();

  class SYSMLV2FILE_EXPORT Enumeration_usageContext : public antlr4::ParserRuleContext {
  public:
    Enumeration_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_prefixContext *usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ENUM();
    UsageContext *usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enumeration_usageContext* enumeration_usage();

  class SYSMLV2FILE_EXPORT Occurrence_definition_prefixContext : public antlr4::ParserRuleContext {
  public:
    Occurrence_definition_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Basic_definition_prefixContext *basic_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INDIVIDUAL();
    std::vector<Definition_extension_keywordContext *> definition_extension_keyword();
    Definition_extension_keywordContext* definition_extension_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Occurrence_definition_prefixContext* occurrence_definition_prefix();

  class SYSMLV2FILE_EXPORT Occurrence_definitionContext : public antlr4::ParserRuleContext {
  public:
    Occurrence_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_OCCURRENCE();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Occurrence_definitionContext* occurrence_definition();

  class SYSMLV2FILE_EXPORT Individual_definitionContext : public antlr4::ParserRuleContext {
  public:
    Individual_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_INDIVIDUAL();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();
    Basic_definition_prefixContext *basic_definition_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Individual_definitionContext* individual_definition();

  class SYSMLV2FILE_EXPORT Occurrence_usage_prefixContext : public antlr4::ParserRuleContext {
  public:
    Occurrence_usage_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Basic_usage_prefixContext *basic_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INDIVIDUAL();
    Portion_kindContext *portion_kind();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Occurrence_usage_prefixContext* occurrence_usage_prefix();

  class SYSMLV2FILE_EXPORT Occurrence_usageContext : public antlr4::ParserRuleContext {
  public:
    Occurrence_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_OCCURRENCE();
    UsageContext *usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Occurrence_usageContext* occurrence_usage();

  class SYSMLV2FILE_EXPORT Individual_usageContext : public antlr4::ParserRuleContext {
  public:
    Individual_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Basic_usage_prefixContext *basic_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INDIVIDUAL();
    UsageContext *usage();
    Portion_kindContext *portion_kind();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Individual_usageContext* individual_usage();

  class SYSMLV2FILE_EXPORT Portion_usageContext : public antlr4::ParserRuleContext {
  public:
    Portion_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Basic_usage_prefixContext *basic_usage_prefix();
    Portion_kindContext *portion_kind();
    UsageContext *usage();
    antlr4::tree::TerminalNode *KEYWORD_INDIVIDUAL();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Portion_usageContext* portion_usage();

  class SYSMLV2FILE_EXPORT Portion_kindContext : public antlr4::ParserRuleContext {
  public:
    Portion_kindContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_SNAPSHOT();
    antlr4::tree::TerminalNode *KEYWORD_TIMESLICE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Portion_kindContext* portion_kind();

  class SYSMLV2FILE_EXPORT Event_occurrence_usageContext : public antlr4::ParserRuleContext {
  public:
    Event_occurrence_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_EVENT();
    Usage_completionContext *usage_completion();
    Owned_reference_subsettingContext *owned_reference_subsetting();
    antlr4::tree::TerminalNode *KEYWORD_OCCURRENCE();
    Usage_declarationContext *usage_declaration();
    Feature_specialization_partContext *feature_specialization_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Event_occurrence_usageContext* event_occurrence_usage();

  class SYSMLV2FILE_EXPORT Source_succession_memberContext : public antlr4::ParserRuleContext {
  public:
    Source_succession_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_THEN();
    Source_successionContext *source_succession();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Source_succession_memberContext* source_succession_member();

  class SYSMLV2FILE_EXPORT Source_successionContext : public antlr4::ParserRuleContext {
  public:
    Source_successionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Source_end_memberContext *source_end_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Source_successionContext* source_succession();

  class SYSMLV2FILE_EXPORT Source_end_memberContext : public antlr4::ParserRuleContext {
  public:
    Source_end_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Source_endContext *source_end();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Source_end_memberContext* source_end_member();

  class SYSMLV2FILE_EXPORT Source_endContext : public antlr4::ParserRuleContext {
  public:
    Source_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_multiplicityContext *owned_multiplicity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Source_endContext* source_end();

  class SYSMLV2FILE_EXPORT Item_definitionContext : public antlr4::ParserRuleContext {
  public:
    Item_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ITEM();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_definitionContext* item_definition();

  class SYSMLV2FILE_EXPORT Item_usageContext : public antlr4::ParserRuleContext {
  public:
    Item_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ITEM();
    UsageContext *usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Item_usageContext* item_usage();

  class SYSMLV2FILE_EXPORT Part_definitionContext : public antlr4::ParserRuleContext {
  public:
    Part_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_PART();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Part_definitionContext* part_definition();

  class SYSMLV2FILE_EXPORT Part_usageContext : public antlr4::ParserRuleContext {
  public:
    Part_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_PART();
    UsageContext *usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Part_usageContext* part_usage();

  class SYSMLV2FILE_EXPORT Port_definitionContext : public antlr4::ParserRuleContext {
  public:
    Port_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_prefixContext *definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_PORT();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Port_definitionContext* port_definition();

  class SYSMLV2FILE_EXPORT Port_usageContext : public antlr4::ParserRuleContext {
  public:
    Port_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_PORT();
    UsageContext *usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Port_usageContext* port_usage();

  class SYSMLV2FILE_EXPORT Conjungated_port_typingContext : public antlr4::ParserRuleContext {
  public:
    Conjungated_port_typingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_CONJUNGATES();
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Conjungated_port_typingContext* conjungated_port_typing();

  class SYSMLV2FILE_EXPORT Connection_definitionContext : public antlr4::ParserRuleContext {
  public:
    Connection_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CONNECTION();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Connection_definitionContext* connection_definition();

  class SYSMLV2FILE_EXPORT Connection_usageContext : public antlr4::ParserRuleContext {
  public:
    Connection_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    Usage_bodyContext *usage_body();
    antlr4::tree::TerminalNode *KEYWORD_CONNECTION();
    Usage_declarationContext *usage_declaration();
    antlr4::tree::TerminalNode *KEYWORD_CONNECT();
    Connector_partContext *connector_part();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Connection_usageContext* connection_usage();

  class SYSMLV2FILE_EXPORT Connector_partContext : public antlr4::ParserRuleContext {
  public:
    Connector_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Binary_connector_partContext *binary_connector_part();
    Nary_connector_partContext *nary_connector_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Connector_partContext* connector_part();

  class SYSMLV2FILE_EXPORT Binary_connector_partContext : public antlr4::ParserRuleContext {
  public:
    Binary_connector_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Binary_connector_partContext* binary_connector_part();

  class SYSMLV2FILE_EXPORT Nary_connector_partContext : public antlr4::ParserRuleContext {
  public:
    Nary_connector_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Nary_connector_partContext* nary_connector_part();

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

  class SYSMLV2FILE_EXPORT Connecotr_endContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *declared_name = nullptr;
    Connecotr_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    Owned_cross_multiplicity_memberContext *owned_cross_multiplicity_member();
    antlr4::tree::TerminalNode *REFERENCES();
    antlr4::tree::TerminalNode *NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Connecotr_endContext* connecotr_end();

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

  class SYSMLV2FILE_EXPORT Binding_connector_as_usageContext : public antlr4::ParserRuleContext {
  public:
    Binding_connector_as_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_prefixContext *usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_BIND();
    Connector_end_memberContext *connector_end_member();
    Binding_end_usage_memberContext *binding_end_usage_member();
    antlr4::tree::TerminalNode *KEYWORD_BINDING();
    Usage_declarationContext *usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Binding_connector_as_usageContext* binding_connector_as_usage();

  class SYSMLV2FILE_EXPORT Binding_end_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Binding_end_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ASSIGN();
    Connector_end_memberContext *connector_end_member();
    Usage_bodyContext *usage_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Binding_end_usage_memberContext* binding_end_usage_member();

  class SYSMLV2FILE_EXPORT Succession_as_usageContext : public antlr4::ParserRuleContext {
  public:
    Succession_as_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_prefixContext *usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FIRST();
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_THEN();
    Usage_bodyContext *usage_body();
    antlr4::tree::TerminalNode *KEYWORD_SUCCSESSION();
    Usage_declarationContext *usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Succession_as_usageContext* succession_as_usage();

  class SYSMLV2FILE_EXPORT Interface_definitionContext : public antlr4::ParserRuleContext {
  public:
    Interface_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INTERFACE();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Interface_bodyContext *interface_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_definitionContext* interface_definition();

  class SYSMLV2FILE_EXPORT Interface_bodyContext : public antlr4::ParserRuleContext {
  public:
    Interface_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Interface_body_itemContext *> interface_body_item();
    Interface_body_itemContext* interface_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_bodyContext* interface_body();

  class SYSMLV2FILE_EXPORT Interface_body_itemContext : public antlr4::ParserRuleContext {
  public:
    Interface_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_memberContext *definition_member();
    Variant_usage_memberContext *variant_usage_member();
    Interface_non_occurrence_usage_memberContext *interface_non_occurrence_usage_member();
    Source_succession_memberContext *source_succession_member();
    Interface_occurrence_usage_memberContext *interface_occurrence_usage_member();
    Alias_memberContext *alias_member();
    Namespace_importContext *namespace_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_body_itemContext* interface_body_item();

  class SYSMLV2FILE_EXPORT Interface_non_occurrence_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Interface_non_occurrence_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Interface_non_occurrence_usage_elementContext *interface_non_occurrence_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_non_occurrence_usage_memberContext* interface_non_occurrence_usage_member();

  class SYSMLV2FILE_EXPORT Interface_non_occurrence_usage_elementContext : public antlr4::ParserRuleContext {
  public:
    Interface_non_occurrence_usage_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reference_usageContext *reference_usage();
    Attribute_usageContext *attribute_usage();
    Enumeration_usageContext *enumeration_usage();
    Binding_connector_as_usageContext *binding_connector_as_usage();
    Succession_as_usageContext *succession_as_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_non_occurrence_usage_elementContext* interface_non_occurrence_usage_element();

  class SYSMLV2FILE_EXPORT Interface_occurrence_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Interface_occurrence_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Interface_occurrence_usage_elementContext *interface_occurrence_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_occurrence_usage_memberContext* interface_occurrence_usage_member();

  class SYSMLV2FILE_EXPORT Interface_occurrence_usage_elementContext : public antlr4::ParserRuleContext {
  public:
    Interface_occurrence_usage_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Default_interface_endContext *default_interface_end();
    Structure_usage_elementContext *structure_usage_element();
    Behavior_usage_elementContext *behavior_usage_element();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_occurrence_usage_elementContext* interface_occurrence_usage_element();

  class SYSMLV2FILE_EXPORT Default_interface_endContext : public antlr4::ParserRuleContext {
  public:
    Default_interface_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_END();
    UsageContext *usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Default_interface_endContext* default_interface_end();

  class SYSMLV2FILE_EXPORT Interface_usageContext : public antlr4::ParserRuleContext {
  public:
    Interface_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INTERFACE();
    Interface_usage_declarationContext *interface_usage_declaration();
    Interface_bodyContext *interface_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_usageContext* interface_usage();

  class SYSMLV2FILE_EXPORT Interface_usage_declarationContext : public antlr4::ParserRuleContext {
  public:
    Interface_usage_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_declarationContext *usage_declaration();
    Value_partContext *value_part();
    antlr4::tree::TerminalNode *KEYWORD_CONNECT();
    Interface_partContext *interface_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_usage_declarationContext* interface_usage_declaration();

  class SYSMLV2FILE_EXPORT Interface_partContext : public antlr4::ParserRuleContext {
  public:
    Interface_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Binary_interface_partContext *binary_interface_part();
    Nary_interface_partContext *nary_interface_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_partContext* interface_part();

  class SYSMLV2FILE_EXPORT Binary_interface_partContext : public antlr4::ParserRuleContext {
  public:
    Binary_interface_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Interface_end_memberContext *> interface_end_member();
    Interface_end_memberContext* interface_end_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Binary_interface_partContext* binary_interface_part();

  class SYSMLV2FILE_EXPORT Nary_interface_partContext : public antlr4::ParserRuleContext {
  public:
    Nary_interface_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    std::vector<Interface_end_memberContext *> interface_end_member();
    Interface_end_memberContext* interface_end_member(size_t i);
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Nary_interface_partContext* nary_interface_part();

  class SYSMLV2FILE_EXPORT Interface_end_memberContext : public antlr4::ParserRuleContext {
  public:
    Interface_end_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Interface_endContext *interface_end();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_end_memberContext* interface_end_member();

  class SYSMLV2FILE_EXPORT Interface_endContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *declared_name = nullptr;
    Interface_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    Owned_cross_multiplicity_memberContext *owned_cross_multiplicity_member();
    antlr4::tree::TerminalNode *REFERENCES();
    antlr4::tree::TerminalNode *NAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_endContext* interface_end();

  class SYSMLV2FILE_EXPORT Allocation_definitionContext : public antlr4::ParserRuleContext {
  public:
    Allocation_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ALLOCATION();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Allocation_definitionContext* allocation_definition();

  class SYSMLV2FILE_EXPORT Allocation_usageContext : public antlr4::ParserRuleContext {
  public:
    Allocation_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    Allocation_usage_declarationContext *allocation_usage_declaration();
    Usage_bodyContext *usage_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Allocation_usageContext* allocation_usage();

  class SYSMLV2FILE_EXPORT Allocation_usage_declarationContext : public antlr4::ParserRuleContext {
  public:
    Allocation_usage_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> KEYWORD_ALLOCATION();
    antlr4::tree::TerminalNode* KEYWORD_ALLOCATION(size_t i);
    Usage_declarationContext *usage_declaration();
    Connector_partContext *connector_part();
    antlr4::tree::TerminalNode *KEYWORD_ALLOCATE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Allocation_usage_declarationContext* allocation_usage_declaration();

  class SYSMLV2FILE_EXPORT Flow_definitionContext : public antlr4::ParserRuleContext {
  public:
    Flow_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FLOW();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_definitionContext* flow_definition();

  class SYSMLV2FILE_EXPORT MessageContext : public antlr4::ParserRuleContext {
  public:
    MessageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_MESSAGE();
    Message_declarationContext *message_declaration();
    Definition_bodyContext *definition_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MessageContext* message();

  class SYSMLV2FILE_EXPORT Message_declarationContext : public antlr4::ParserRuleContext {
  public:
    Message_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_declarationContext *usage_declaration();
    Value_partContext *value_part();
    antlr4::tree::TerminalNode *KEYWORD_OF();
    Flow_payload_feature_memberContext *flow_payload_feature_member();
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    std::vector<Message_event_memberContext *> message_event_member();
    Message_event_memberContext* message_event_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Message_declarationContext* message_declaration();

  class SYSMLV2FILE_EXPORT Message_event_memberContext : public antlr4::ParserRuleContext {
  public:
    Message_event_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Message_eventContext *message_event();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Message_event_memberContext* message_event_member();

  class SYSMLV2FILE_EXPORT Message_eventContext : public antlr4::ParserRuleContext {
  public:
    Message_eventContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Message_eventContext* message_event();

  class SYSMLV2FILE_EXPORT Flow_usageContext : public antlr4::ParserRuleContext {
  public:
    Flow_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FLOW();
    Flow_declarationContext *flow_declaration();
    Definition_bodyContext *definition_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_usageContext* flow_usage();

  class SYSMLV2FILE_EXPORT Succession_flow_usageContext : public antlr4::ParserRuleContext {
  public:
    Succession_flow_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_SUCCSESSION();
    antlr4::tree::TerminalNode *KEYWORD_FLOW();
    Flow_declarationContext *flow_declaration();
    Definition_bodyContext *definition_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Succession_flow_usageContext* succession_flow_usage();

  class SYSMLV2FILE_EXPORT Flow_declarationContext : public antlr4::ParserRuleContext {
  public:
    Flow_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_declarationContext *usage_declaration();
    Value_partContext *value_part();
    std::vector<antlr4::tree::TerminalNode *> KEYWORD_OF();
    antlr4::tree::TerminalNode* KEYWORD_OF(size_t i);
    Flow_payload_feature_memberContext *flow_payload_feature_member();
    std::vector<Flow_end_memberContext *> flow_end_member();
    Flow_end_memberContext* flow_end_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_declarationContext* flow_declaration();

  class SYSMLV2FILE_EXPORT Flow_payload_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Flow_payload_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Flow_payload_featureContext *flow_payload_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_payload_feature_memberContext* flow_payload_feature_member();

  class SYSMLV2FILE_EXPORT Flow_payload_featureContext : public antlr4::ParserRuleContext {
  public:
    Flow_payload_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Payload_featureContext *payload_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_payload_featureContext* flow_payload_feature();

  class SYSMLV2FILE_EXPORT Payload_featureContext : public antlr4::ParserRuleContext {
  public:
    Payload_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentificationContext *identification();
    Payload_feature_specialization_partContext *payload_feature_specialization_part();
    Value_partContext *value_part();
    Owned_feature_typingContext *owned_feature_typing();
    Owned_multiplicityContext *owned_multiplicity();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Payload_featureContext* payload_feature();

  class SYSMLV2FILE_EXPORT Payload_feature_specialization_partContext : public antlr4::ParserRuleContext {
  public:
    Payload_feature_specialization_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Feature_specializationContext *> feature_specialization();
    Feature_specializationContext* feature_specialization(size_t i);
    Multiplicity_partContext *multiplicity_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Payload_feature_specialization_partContext* payload_feature_specialization_part();

  class SYSMLV2FILE_EXPORT Flow_end_memberContext : public antlr4::ParserRuleContext {
  public:
    Flow_end_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Flow_endContext *flow_end();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_end_memberContext* flow_end_member();

  class SYSMLV2FILE_EXPORT Flow_endContext : public antlr4::ParserRuleContext {
  public:
    Flow_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Flow_feature_memberContext *flow_feature_member();
    Flow_end_subsettingContext *flow_end_subsetting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_endContext* flow_end();

  class SYSMLV2FILE_EXPORT Flow_end_subsettingContext : public antlr4::ParserRuleContext {
  public:
    Flow_end_subsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Feature_chain_prefixContext *feature_chain_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_end_subsettingContext* flow_end_subsetting();

  class SYSMLV2FILE_EXPORT Feature_chain_prefixContext : public antlr4::ParserRuleContext {
  public:
    Feature_chain_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Owned_feature_chainingContext *> owned_feature_chaining();
    Owned_feature_chainingContext* owned_feature_chaining(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_DOT();
    antlr4::tree::TerminalNode* SYMBOL_DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_chain_prefixContext* feature_chain_prefix();

  class SYSMLV2FILE_EXPORT Flow_feature_memberContext : public antlr4::ParserRuleContext {
  public:
    Flow_feature_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Flow_featureContext *flow_feature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_feature_memberContext* flow_feature_member();

  class SYSMLV2FILE_EXPORT Flow_featureContext : public antlr4::ParserRuleContext {
  public:
    Flow_featureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Flow_feature_redefinitionContext *flow_feature_redefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_featureContext* flow_feature();

  class SYSMLV2FILE_EXPORT Flow_feature_redefinitionContext : public antlr4::ParserRuleContext {
  public:
    Flow_feature_redefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flow_feature_redefinitionContext* flow_feature_redefinition();

  class SYSMLV2FILE_EXPORT Action_definitionContext : public antlr4::ParserRuleContext {
  public:
    Action_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ACTION();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Action_bodyContext *action_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_definitionContext* action_definition();

  class SYSMLV2FILE_EXPORT Action_bodyContext : public antlr4::ParserRuleContext {
  public:
    Action_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Action_body_itemContext *> action_body_item();
    Action_body_itemContext* action_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_bodyContext* action_body();

  class SYSMLV2FILE_EXPORT Action_body_itemContext : public antlr4::ParserRuleContext {
  public:
    Action_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_behavior_body_itemContext *non_behavior_body_item();
    Initial_node_memberContext *initial_node_member();
    std::vector<Action_target_succession_memberContext *> action_target_succession_member();
    Action_target_succession_memberContext* action_target_succession_member(size_t i);
    Action_behavior_memberContext *action_behavior_member();
    Source_succession_memberContext *source_succession_member();
    Guarded_succession_memberContext *guarded_succession_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_body_itemContext* action_body_item();

  class SYSMLV2FILE_EXPORT Non_behavior_body_itemContext : public antlr4::ParserRuleContext {
  public:
    Non_behavior_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Namespace_importContext *namespace_import();
    Alias_memberContext *alias_member();
    Definition_memberContext *definition_member();
    Variant_usage_memberContext *variant_usage_member();
    Structure_usage_memberContext *structure_usage_member();
    Source_succession_memberContext *source_succession_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Non_behavior_body_itemContext* non_behavior_body_item();

  class SYSMLV2FILE_EXPORT Action_behavior_memberContext : public antlr4::ParserRuleContext {
  public:
    Action_behavior_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Behavior_usage_memberContext *behavior_usage_member();
    Action_node_memberContext *action_node_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_behavior_memberContext* action_behavior_member();

  class SYSMLV2FILE_EXPORT Initial_node_memberContext : public antlr4::ParserRuleContext {
  public:
    Initial_node_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FIRST();
    Qualified_nameContext *qualified_name();
    Relationship_bodyContext *relationship_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Initial_node_memberContext* initial_node_member();

  class SYSMLV2FILE_EXPORT Action_node_memberContext : public antlr4::ParserRuleContext {
  public:
    Action_node_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Action_nodeContext *action_node();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_node_memberContext* action_node_member();

  class SYSMLV2FILE_EXPORT Action_target_succession_memberContext : public antlr4::ParserRuleContext {
  public:
    Action_target_succession_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Action_target_successionContext *action_target_succession();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_target_succession_memberContext* action_target_succession_member();

  class SYSMLV2FILE_EXPORT Guarded_succession_memberContext : public antlr4::ParserRuleContext {
  public:
    Guarded_succession_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Guarded_successionContext *guarded_succession();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Guarded_succession_memberContext* guarded_succession_member();

  class SYSMLV2FILE_EXPORT Action_usageContext : public antlr4::ParserRuleContext {
  public:
    Action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ACTION();
    Action_usage_declarationContext *action_usage_declaration();
    Action_bodyContext *action_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_usageContext* action_usage();

  class SYSMLV2FILE_EXPORT Action_usage_declarationContext : public antlr4::ParserRuleContext {
  public:
    Action_usage_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_declarationContext *usage_declaration();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_usage_declarationContext* action_usage_declaration();

  class SYSMLV2FILE_EXPORT Perform_action_usageContext : public antlr4::ParserRuleContext {
  public:
    Perform_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_PERFORM();
    Perform_action_usage_declarationContext *perform_action_usage_declaration();
    Action_bodyContext *action_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Perform_action_usageContext* perform_action_usage();

  class SYSMLV2FILE_EXPORT Perform_action_usage_declarationContext : public antlr4::ParserRuleContext {
  public:
    Perform_action_usage_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    Feature_specialization_partContext *feature_specialization_part();
    antlr4::tree::TerminalNode *KEYWORD_ACTION();
    Usage_declarationContext *usage_declaration();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Perform_action_usage_declarationContext* perform_action_usage_declaration();

  class SYSMLV2FILE_EXPORT Action_nodeContext : public antlr4::ParserRuleContext {
  public:
    Action_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Control_nodeContext *control_node();
    Send_nodeContext *send_node();
    Accept_nodeContext *accept_node();
    Assignment_nodeContext *assignment_node();
    Terminate_nodeContext *terminate_node();
    If_nodeContext *if_node();
    While_loop_nodeContext *while_loop_node();
    For_loop_nodeContext *for_loop_node();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_nodeContext* action_node();

  class SYSMLV2FILE_EXPORT Action_node_usage_declarationContext : public antlr4::ParserRuleContext {
  public:
    Action_node_usage_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ACTION();
    Usage_declarationContext *usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_node_usage_declarationContext* action_node_usage_declaration();

  class SYSMLV2FILE_EXPORT Action_node_prefixContext : public antlr4::ParserRuleContext {
  public:
    Action_node_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    Action_node_usage_declarationContext *action_node_usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_node_prefixContext* action_node_prefix();

  class SYSMLV2FILE_EXPORT Control_nodeContext : public antlr4::ParserRuleContext {
  public:
    Control_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Merge_nodeContext *merge_node();
    Decision_nodeContext *decision_node();
    Join_nodeContext *join_node();
    Fork_nodeContext *fork_node();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Control_nodeContext* control_node();

  class SYSMLV2FILE_EXPORT Control_node_prefixContext : public antlr4::ParserRuleContext {
  public:
    Control_node_prefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Ref_prefixContext *ref_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INDIVIDIAL();
    Portion_kindContext *portion_kind();
    Usage_extention_keywordContext *usage_extention_keyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Control_node_prefixContext* control_node_prefix();

  class SYSMLV2FILE_EXPORT Merge_nodeContext : public antlr4::ParserRuleContext {
  public:
    Merge_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Control_node_prefixContext *control_node_prefix();
    Usage_declarationContext *usage_declaration();
    Action_bodyContext *action_body();
    antlr4::tree::TerminalNode *KEYWORD_MERGE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Merge_nodeContext* merge_node();

  class SYSMLV2FILE_EXPORT Decision_nodeContext : public antlr4::ParserRuleContext {
  public:
    Decision_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Control_node_prefixContext *control_node_prefix();
    Usage_declarationContext *usage_declaration();
    Action_bodyContext *action_body();
    antlr4::tree::TerminalNode *KEYWORD_DECIDE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Decision_nodeContext* decision_node();

  class SYSMLV2FILE_EXPORT Join_nodeContext : public antlr4::ParserRuleContext {
  public:
    Join_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Control_node_prefixContext *control_node_prefix();
    Usage_declarationContext *usage_declaration();
    Action_bodyContext *action_body();
    antlr4::tree::TerminalNode *KEYWORD_DECIDE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Join_nodeContext* join_node();

  class SYSMLV2FILE_EXPORT Fork_nodeContext : public antlr4::ParserRuleContext {
  public:
    Fork_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Control_node_prefixContext *control_node_prefix();
    Usage_declarationContext *usage_declaration();
    Action_bodyContext *action_body();
    antlr4::tree::TerminalNode *KEYWORD_FORK();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Fork_nodeContext* fork_node();

  class SYSMLV2FILE_EXPORT Accept_nodeContext : public antlr4::ParserRuleContext {
  public:
    Accept_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    Accept_node_declarationContext *accept_node_declaration();
    Action_bodyContext *action_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Accept_nodeContext* accept_node();

  class SYSMLV2FILE_EXPORT Accept_node_declarationContext : public antlr4::ParserRuleContext {
  public:
    Accept_node_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ACCEPT();
    Accept_parameter_partContext *accept_parameter_part();
    Action_node_usage_declarationContext *action_node_usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Accept_node_declarationContext* accept_node_declaration();

  class SYSMLV2FILE_EXPORT Accept_parameter_partContext : public antlr4::ParserRuleContext {
  public:
    Accept_parameter_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Payload_parameter_memberContext *payload_parameter_member();
    antlr4::tree::TerminalNode *KEYWORD_VIA();
    Node_parameter_memberContext *node_parameter_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Accept_parameter_partContext* accept_parameter_part();

  class SYSMLV2FILE_EXPORT Payload_parameter_memberContext : public antlr4::ParserRuleContext {
  public:
    Payload_parameter_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Payload_parameterContext *payload_parameter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Payload_parameter_memberContext* payload_parameter_member();

  class SYSMLV2FILE_EXPORT Payload_parameterContext : public antlr4::ParserRuleContext {
  public:
    Payload_parameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Payload_featureContext *payload_feature();
    IdentificationContext *identification();
    Trigger_value_partContext *trigger_value_part();
    Payload_feature_specialization_partContext *payload_feature_specialization_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Payload_parameterContext* payload_parameter();

  class SYSMLV2FILE_EXPORT Trigger_value_partContext : public antlr4::ParserRuleContext {
  public:
    Trigger_value_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Trigger_expressionContext *trigger_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Trigger_value_partContext* trigger_value_part();

  class SYSMLV2FILE_EXPORT Trigger_expressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *kind = nullptr;
    Trigger_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_memberContext *argument_member();
    antlr4::tree::TerminalNode *KEYWORD_AT();
    antlr4::tree::TerminalNode *KEYWORD_AFTER();
    Argument_expression_memberContext *argument_expression_member();
    antlr4::tree::TerminalNode *KEYWORD_WHEN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Trigger_expressionContext* trigger_expression();

  class SYSMLV2FILE_EXPORT Send_nodeContext : public antlr4::ParserRuleContext {
  public:
    Send_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_SEND();
    Action_bodyContext *action_body();
    Action_usage_declarationContext *action_usage_declaration();
    Node_parameter_memberContext *node_parameter_member();
    Sender_receiver_partContext *sender_receiver_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Send_nodeContext* send_node();

  class SYSMLV2FILE_EXPORT Send_node_declarationContext : public antlr4::ParserRuleContext {
  public:
    Send_node_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_SEND();
    Node_parameter_memberContext *node_parameter_member();
    Action_node_usage_declarationContext *action_node_usage_declaration();
    Sender_receiver_partContext *sender_receiver_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Send_node_declarationContext* send_node_declaration();

  class SYSMLV2FILE_EXPORT Sender_receiver_partContext : public antlr4::ParserRuleContext {
  public:
    Sender_receiver_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_VIA();
    std::vector<Node_parameter_memberContext *> node_parameter_member();
    Node_parameter_memberContext* node_parameter_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sender_receiver_partContext* sender_receiver_part();

  class SYSMLV2FILE_EXPORT Node_parameter_memberContext : public antlr4::ParserRuleContext {
  public:
    Node_parameter_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Node_parameterContext *node_parameter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Node_parameter_memberContext* node_parameter_member();

  class SYSMLV2FILE_EXPORT Node_parameterContext : public antlr4::ParserRuleContext {
  public:
    Node_parameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_bindingContext *feature_binding();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Node_parameterContext* node_parameter();

  class SYSMLV2FILE_EXPORT Feature_bindingContext : public antlr4::ParserRuleContext {
  public:
    Feature_bindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expressionContext *owned_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_bindingContext* feature_binding();

  class SYSMLV2FILE_EXPORT Assignment_nodeContext : public antlr4::ParserRuleContext {
  public:
    Assignment_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    Assignment_node_declarationContext *assignment_node_declaration();
    Action_bodyContext *action_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assignment_nodeContext* assignment_node();

  class SYSMLV2FILE_EXPORT Assignment_node_declarationContext : public antlr4::ParserRuleContext {
  public:
    Assignment_node_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ASSIGN();
    Assignment_target_memberContext *assignment_target_member();
    Feature_chain_memberContext *feature_chain_member();
    antlr4::tree::TerminalNode *SYMBOL_DEF_ASSIGN();
    Node_parameter_memberContext *node_parameter_member();
    Action_node_usage_declarationContext *action_node_usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assignment_node_declarationContext* assignment_node_declaration();

  class SYSMLV2FILE_EXPORT Assignment_target_memberContext : public antlr4::ParserRuleContext {
  public:
    Assignment_target_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Assignment_target_parameterContext *assignment_target_parameter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assignment_target_memberContext* assignment_target_member();

  class SYSMLV2FILE_EXPORT Assignment_target_parameterContext : public antlr4::ParserRuleContext {
  public:
    Assignment_target_parameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Assignment_target_bindingContext *assignment_target_binding();
    antlr4::tree::TerminalNode *SYMBOL_DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assignment_target_parameterContext* assignment_target_parameter();

  class SYSMLV2FILE_EXPORT Assignment_target_bindingContext : public antlr4::ParserRuleContext {
  public:
    Assignment_target_bindingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_chain_primary_expressionContext *non_feature_chain_primary_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assignment_target_bindingContext* assignment_target_binding();

  class SYSMLV2FILE_EXPORT Feature_chain_memberContext : public antlr4::ParserRuleContext {
  public:
    SysMLv2Parser::Qualified_nameContext *memberElement = nullptr;
    Feature_chain_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_chain_memberContext* feature_chain_member();

  class SYSMLV2FILE_EXPORT Owned_feature_chain_memberContext : public antlr4::ParserRuleContext {
  public:
    Owned_feature_chain_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_feature_chainContext *owned_feature_chain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_feature_chain_memberContext* owned_feature_chain_member();

  class SYSMLV2FILE_EXPORT Terminate_nodeContext : public antlr4::ParserRuleContext {
  public:
    Terminate_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_TERMINATE();
    Action_bodyContext *action_body();
    Action_node_usage_declarationContext *action_node_usage_declaration();
    Node_parameter_memberContext *node_parameter_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Terminate_nodeContext* terminate_node();

  class SYSMLV2FILE_EXPORT If_nodeContext : public antlr4::ParserRuleContext {
  public:
    If_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Action_node_prefixContext *action_node_prefix();
    antlr4::tree::TerminalNode *KEYWORD_IF();
    Expression_parameter_memberContext *expression_parameter_member();
    std::vector<Action_body_parameter_memberContext *> action_body_parameter_member();
    Action_body_parameter_memberContext* action_body_parameter_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_ELSE();
    If_node_parameter_memberContext *if_node_parameter_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_nodeContext* if_node();

  class SYSMLV2FILE_EXPORT Expression_parameter_memberContext : public antlr4::ParserRuleContext {
  public:
    Expression_parameter_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expressionContext *owned_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expression_parameter_memberContext* expression_parameter_member();

  class SYSMLV2FILE_EXPORT Action_body_parameter_memberContext : public antlr4::ParserRuleContext {
  public:
    Action_body_parameter_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Action_body_parameterContext *action_body_parameter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_body_parameter_memberContext* action_body_parameter_member();

  class SYSMLV2FILE_EXPORT Action_body_parameterContext : public antlr4::ParserRuleContext {
  public:
    Action_body_parameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    antlr4::tree::TerminalNode *KEYWORD_ACTION();
    std::vector<Action_body_itemContext *> action_body_item();
    Action_body_itemContext* action_body_item(size_t i);
    Usage_declarationContext *usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_body_parameterContext* action_body_parameter();

  class SYSMLV2FILE_EXPORT If_node_parameter_memberContext : public antlr4::ParserRuleContext {
  public:
    If_node_parameter_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    If_nodeContext *if_node();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_node_parameter_memberContext* if_node_parameter_member();

  class SYSMLV2FILE_EXPORT While_loop_nodeContext : public antlr4::ParserRuleContext {
  public:
    While_loop_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Action_node_prefixContext *action_node_prefix();
    Action_body_parameter_memberContext *action_body_parameter_member();
    antlr4::tree::TerminalNode *KEYWORD_WHILE();
    std::vector<Expression_parameter_memberContext *> expression_parameter_member();
    Expression_parameter_memberContext* expression_parameter_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_LOOP();
    antlr4::tree::TerminalNode *KEYWORD_UNTIL();
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  While_loop_nodeContext* while_loop_node();

  class SYSMLV2FILE_EXPORT For_loop_nodeContext : public antlr4::ParserRuleContext {
  public:
    For_loop_nodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Action_node_prefixContext *action_node_prefix();
    antlr4::tree::TerminalNode *KEYWORD_FOR();
    For_variable_declaration_memberContext *for_variable_declaration_member();
    antlr4::tree::TerminalNode *KEYWORD_IN();
    Node_parameter_memberContext *node_parameter_member();
    Action_body_parameter_memberContext *action_body_parameter_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_loop_nodeContext* for_loop_node();

  class SYSMLV2FILE_EXPORT For_variable_declaration_memberContext : public antlr4::ParserRuleContext {
  public:
    For_variable_declaration_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_declarationContext *usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_variable_declaration_memberContext* for_variable_declaration_member();

  class SYSMLV2FILE_EXPORT For_variable_declarationContext : public antlr4::ParserRuleContext {
  public:
    For_variable_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_declarationContext *usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_variable_declarationContext* for_variable_declaration();

  class SYSMLV2FILE_EXPORT Action_target_successionContext : public antlr4::ParserRuleContext {
  public:
    Action_target_successionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_bodyContext *usage_body();
    Target_successionContext *target_succession();
    Guarded_target_successionContext *guarded_target_succession();
    Default_target_successionContext *default_target_succession();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Action_target_successionContext* action_target_succession();

  class SYSMLV2FILE_EXPORT Target_successionContext : public antlr4::ParserRuleContext {
  public:
    Target_successionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Source_end_memberContext *source_end_member();
    antlr4::tree::TerminalNode *KEYWORD_THEN();
    Connector_end_memberContext *connector_end_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Target_successionContext* target_succession();

  class SYSMLV2FILE_EXPORT Guarded_target_successionContext : public antlr4::ParserRuleContext {
  public:
    Guarded_target_successionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Guard_expression_memberContext *guard_expression_member();
    antlr4::tree::TerminalNode *KEYWORD_THEN();
    Transition_succession_memberContext *transition_succession_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Guarded_target_successionContext* guarded_target_succession();

  class SYSMLV2FILE_EXPORT Default_target_successionContext : public antlr4::ParserRuleContext {
  public:
    Default_target_successionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ELSE();
    Transition_succession_memberContext *transition_succession_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Default_target_successionContext* default_target_succession();

  class SYSMLV2FILE_EXPORT Guarded_successionContext : public antlr4::ParserRuleContext {
  public:
    Guarded_successionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_FIRST();
    Feature_chain_memberContext *feature_chain_member();
    Guard_expression_memberContext *guard_expression_member();
    antlr4::tree::TerminalNode *KEYWORD_THEN();
    Transition_succession_memberContext *transition_succession_member();
    Usage_bodyContext *usage_body();
    antlr4::tree::TerminalNode *KEYWORD_SUCCSESSION();
    Usage_declarationContext *usage_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Guarded_successionContext* guarded_succession();

  class SYSMLV2FILE_EXPORT State_definitionContext : public antlr4::ParserRuleContext {
  public:
    State_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_STATE();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    State_def_bodyContext *state_def_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_definitionContext* state_definition();

  class SYSMLV2FILE_EXPORT State_def_bodyContext : public antlr4::ParserRuleContext {
  public:
    State_def_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    State_body_itemContext *state_body_item();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    antlr4::tree::TerminalNode *KEYWORD_PARALLEL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_def_bodyContext* state_def_body();

  class SYSMLV2FILE_EXPORT State_body_itemContext : public antlr4::ParserRuleContext {
  public:
    State_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_behavior_body_itemContext *non_behavior_body_item();
    Behavior_usage_memberContext *behavior_usage_member();
    Source_succession_memberContext *source_succession_member();
    std::vector<Target_transition_usage_memberContext *> target_transition_usage_member();
    Target_transition_usage_memberContext* target_transition_usage_member(size_t i);
    Transition_usage_memberContext *transition_usage_member();
    Entry_action_memberContext *entry_action_member();
    std::vector<Entry_transition_memberContext *> entry_transition_member();
    Entry_transition_memberContext* entry_transition_member(size_t i);
    Do_action_memberContext *do_action_member();
    Exit_action_memberContext *exit_action_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_body_itemContext* state_body_item();

  class SYSMLV2FILE_EXPORT Entry_action_memberContext : public antlr4::ParserRuleContext {
  public:
    Entry_action_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    State_action_usageContext *state_action_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Entry_action_memberContext* entry_action_member();

  class SYSMLV2FILE_EXPORT Do_action_memberContext : public antlr4::ParserRuleContext {
  public:
    Do_action_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    State_action_usageContext *state_action_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Do_action_memberContext* do_action_member();

  class SYSMLV2FILE_EXPORT Exit_action_memberContext : public antlr4::ParserRuleContext {
  public:
    Exit_action_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    State_action_usageContext *state_action_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Exit_action_memberContext* exit_action_member();

  class SYSMLV2FILE_EXPORT Entry_transition_memberContext : public antlr4::ParserRuleContext {
  public:
    Entry_transition_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    Guarded_target_successionContext *guarded_target_succession();
    antlr4::tree::TerminalNode *KEYWORD_THEN();
    Target_successionContext *target_succession();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Entry_transition_memberContext* entry_transition_member();

  class SYSMLV2FILE_EXPORT State_action_usageContext : public antlr4::ParserRuleContext {
  public:
    State_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Empty_action_usageContext *empty_action_usage();
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    State_perform_action_uageContext *state_perform_action_uage();
    State_accept_action_usageContext *state_accept_action_usage();
    State_send_action_usageContext *state_send_action_usage();
    State_assignment_action_usageContext *state_assignment_action_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_action_usageContext* state_action_usage();

  class SYSMLV2FILE_EXPORT Empty_action_usageContext : public antlr4::ParserRuleContext {
  public:
    Empty_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Empty_action_usageContext* empty_action_usage();

  class SYSMLV2FILE_EXPORT State_perform_action_uageContext : public antlr4::ParserRuleContext {
  public:
    State_perform_action_uageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Perform_action_usage_declarationContext *perform_action_usage_declaration();
    Action_bodyContext *action_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_perform_action_uageContext* state_perform_action_uage();

  class SYSMLV2FILE_EXPORT State_accept_action_usageContext : public antlr4::ParserRuleContext {
  public:
    State_accept_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Accept_node_declarationContext *accept_node_declaration();
    Action_bodyContext *action_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_accept_action_usageContext* state_accept_action_usage();

  class SYSMLV2FILE_EXPORT State_send_action_usageContext : public antlr4::ParserRuleContext {
  public:
    State_send_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Send_node_declarationContext *send_node_declaration();
    Action_bodyContext *action_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_send_action_usageContext* state_send_action_usage();

  class SYSMLV2FILE_EXPORT State_assignment_action_usageContext : public antlr4::ParserRuleContext {
  public:
    State_assignment_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Assignment_node_declarationContext *assignment_node_declaration();
    Action_bodyContext *action_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_assignment_action_usageContext* state_assignment_action_usage();

  class SYSMLV2FILE_EXPORT Transition_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Transition_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Transition_usageContext *transition_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Transition_usage_memberContext* transition_usage_member();

  class SYSMLV2FILE_EXPORT Target_transition_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Target_transition_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Target_transition_usageContext *target_transition_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Target_transition_usage_memberContext* target_transition_usage_member();

  class SYSMLV2FILE_EXPORT State_usageContext : public antlr4::ParserRuleContext {
  public:
    State_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_STATE();
    Action_usage_declarationContext *action_usage_declaration();
    State_usage_bodyContext *state_usage_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_usageContext* state_usage();

  class SYSMLV2FILE_EXPORT State_usage_bodyContext : public antlr4::ParserRuleContext {
  public:
    State_usage_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    antlr4::tree::TerminalNode *KEYWORD_PARALLEL();
    std::vector<State_body_itemContext *> state_body_item();
    State_body_itemContext* state_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  State_usage_bodyContext* state_usage_body();

  class SYSMLV2FILE_EXPORT Exhibit_state_usageContext : public antlr4::ParserRuleContext {
  public:
    Exhibit_state_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_EXHIBIT();
    State_usage_bodyContext *state_usage_body();
    Owned_reference_subsettingContext *owned_reference_subsetting();
    antlr4::tree::TerminalNode *KEYWORD_STATE();
    Usage_declarationContext *usage_declaration();
    Value_partContext *value_part();
    Feature_specialization_partContext *feature_specialization_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Exhibit_state_usageContext* exhibit_state_usage();

  class SYSMLV2FILE_EXPORT Transition_usageContext : public antlr4::ParserRuleContext {
  public:
    Transition_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_TRANSISTION();
    Feature_chain_memberContext *feature_chain_member();
    antlr4::tree::TerminalNode *KEYWORD_THEN();
    Transition_succession_memberContext *transition_succession_member();
    Action_bodyContext *action_body();
    Usage_declarationContext *usage_declaration();
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    Trigger_action_memberContext *trigger_action_member();
    Guard_expression_memberContext *guard_expression_member();
    Effect_behavior_memberContext *effect_behavior_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Transition_usageContext* transition_usage();

  class SYSMLV2FILE_EXPORT Target_transition_usageContext : public antlr4::ParserRuleContext {
  public:
    Target_transition_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_THEN();
    Transition_succession_memberContext *transition_succession_member();
    Action_bodyContext *action_body();
    antlr4::tree::TerminalNode *KEYWORD_TRANSISTION();
    Trigger_action_memberContext *trigger_action_member();
    Guard_expression_memberContext *guard_expression_member();
    Effect_behavior_memberContext *effect_behavior_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Target_transition_usageContext* target_transition_usage();

  class SYSMLV2FILE_EXPORT Trigger_action_memberContext : public antlr4::ParserRuleContext {
  public:
    Trigger_action_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ACCEPT();
    Trigger_actionContext *trigger_action();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Trigger_action_memberContext* trigger_action_member();

  class SYSMLV2FILE_EXPORT Trigger_actionContext : public antlr4::ParserRuleContext {
  public:
    Trigger_actionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Accept_parameter_partContext *accept_parameter_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Trigger_actionContext* trigger_action();

  class SYSMLV2FILE_EXPORT Guard_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Guard_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_IF();
    Owned_expressionContext *owned_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Guard_expression_memberContext* guard_expression_member();

  class SYSMLV2FILE_EXPORT Effect_behavior_memberContext : public antlr4::ParserRuleContext {
  public:
    Effect_behavior_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_DO();
    Effect_behavior_usageContext *effect_behavior_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Effect_behavior_memberContext* effect_behavior_member();

  class SYSMLV2FILE_EXPORT Effect_behavior_usageContext : public antlr4::ParserRuleContext {
  public:
    Effect_behavior_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Empty_action_usageContext *empty_action_usage();
    Transition_perform_action_usageContext *transition_perform_action_usage();
    Transition_accept_action_usageContext *transition_accept_action_usage();
    Transition_send_action_usageContext *transition_send_action_usage();
    Transition_assignment_action_usageContext *transition_assignment_action_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Effect_behavior_usageContext* effect_behavior_usage();

  class SYSMLV2FILE_EXPORT Transition_perform_action_usageContext : public antlr4::ParserRuleContext {
  public:
    Transition_perform_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Perform_action_usage_declarationContext *perform_action_usage_declaration();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Action_body_itemContext *> action_body_item();
    Action_body_itemContext* action_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Transition_perform_action_usageContext* transition_perform_action_usage();

  class SYSMLV2FILE_EXPORT Transition_accept_action_usageContext : public antlr4::ParserRuleContext {
  public:
    Transition_accept_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Accept_node_declarationContext *accept_node_declaration();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Action_body_itemContext *> action_body_item();
    Action_body_itemContext* action_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Transition_accept_action_usageContext* transition_accept_action_usage();

  class SYSMLV2FILE_EXPORT Transition_send_action_usageContext : public antlr4::ParserRuleContext {
  public:
    Transition_send_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Send_node_declarationContext *send_node_declaration();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Action_body_itemContext *> action_body_item();
    Action_body_itemContext* action_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Transition_send_action_usageContext* transition_send_action_usage();

  class SYSMLV2FILE_EXPORT Transition_assignment_action_usageContext : public antlr4::ParserRuleContext {
  public:
    Transition_assignment_action_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Assignment_node_declarationContext *assignment_node_declaration();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Action_body_itemContext *> action_body_item();
    Action_body_itemContext* action_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Transition_assignment_action_usageContext* transition_assignment_action_usage();

  class SYSMLV2FILE_EXPORT Transition_succession_memberContext : public antlr4::ParserRuleContext {
  public:
    Transition_succession_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Transition_successionContext *transition_succession();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Transition_succession_memberContext* transition_succession_member();

  class SYSMLV2FILE_EXPORT Transition_successionContext : public antlr4::ParserRuleContext {
  public:
    Transition_successionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Connector_end_memberContext *connector_end_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Transition_successionContext* transition_succession();

  class SYSMLV2FILE_EXPORT Calculation_definitionContext : public antlr4::ParserRuleContext {
  public:
    Calculation_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CALC();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Calculation_bodyContext *calculation_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Calculation_definitionContext* calculation_definition();

  class SYSMLV2FILE_EXPORT Calculation_usageContext : public antlr4::ParserRuleContext {
  public:
    Calculation_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CALC();
    Action_usage_declarationContext *action_usage_declaration();
    Calculation_bodyContext *calculation_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Calculation_usageContext* calculation_usage();

  class SYSMLV2FILE_EXPORT Calculation_bodyContext : public antlr4::ParserRuleContext {
  public:
    Calculation_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    Calculation_body_partContext *calculation_body_part();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Calculation_bodyContext* calculation_body();

  class SYSMLV2FILE_EXPORT Calculation_body_partContext : public antlr4::ParserRuleContext {
  public:
    Calculation_body_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Calculation_body_itemContext *> calculation_body_item();
    Calculation_body_itemContext* calculation_body_item(size_t i);
    Result_expression_memberContext *result_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Calculation_body_partContext* calculation_body_part();

  class SYSMLV2FILE_EXPORT Calculation_body_itemContext : public antlr4::ParserRuleContext {
  public:
    Calculation_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Action_body_itemContext *action_body_item();
    Return_parameter_memberContext *return_parameter_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Calculation_body_itemContext* calculation_body_item();

  class SYSMLV2FILE_EXPORT Return_parameter_memberContext : public antlr4::ParserRuleContext {
  public:
    Return_parameter_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_RETURN();
    Usage_elementContext *usage_element();
    Member_prefixContext *member_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Return_parameter_memberContext* return_parameter_member();

  class SYSMLV2FILE_EXPORT Result_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Result_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expressionContext *owned_expression();
    Member_prefixContext *member_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Result_expression_memberContext* result_expression_member();

  class SYSMLV2FILE_EXPORT Constraint_definitionContext : public antlr4::ParserRuleContext {
  public:
    Constraint_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_declarationContext *definition_declaration();
    Calculation_bodyContext *calculation_body();
    Occurrence_definition_prefixContext *occurrence_definition_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Constraint_definitionContext* constraint_definition();

  class SYSMLV2FILE_EXPORT Constraint_usageContext : public antlr4::ParserRuleContext {
  public:
    Constraint_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_CONSTRAINT();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Calculation_bodyContext *calculation_body();
    Occurrence_usage_prefixContext *occurrence_usage_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Constraint_usageContext* constraint_usage();

  class SYSMLV2FILE_EXPORT Assert_constriant_usageContext : public antlr4::ParserRuleContext {
  public:
    Assert_constriant_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ASSERT();
    Calculation_bodyContext *calculation_body();
    Owned_reference_subsettingContext *owned_reference_subsetting();
    antlr4::tree::TerminalNode *KEYWORD_CONSTRAINT();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    antlr4::tree::TerminalNode *KEYWORD_NOT();
    Feature_specialization_partContext *feature_specialization_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assert_constriant_usageContext* assert_constriant_usage();

  class SYSMLV2FILE_EXPORT Constraint_usage_declarationContext : public antlr4::ParserRuleContext {
  public:
    Constraint_usage_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Usage_declarationContext *usage_declaration();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Constraint_usage_declarationContext* constraint_usage_declaration();

  class SYSMLV2FILE_EXPORT Requirement_definitionContext : public antlr4::ParserRuleContext {
  public:
    Requirement_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_REQUIREMENT();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Requirement_bodyContext *requirement_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Requirement_definitionContext* requirement_definition();

  class SYSMLV2FILE_EXPORT Requirement_bodyContext : public antlr4::ParserRuleContext {
  public:
    Requirement_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Requirement_body_itemContext *> requirement_body_item();
    Requirement_body_itemContext* requirement_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Requirement_bodyContext* requirement_body();

  class SYSMLV2FILE_EXPORT Requirement_body_itemContext : public antlr4::ParserRuleContext {
  public:
    Requirement_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_body_itemContext *definition_body_item();
    Subject_memberContext *subject_member();
    Requirement_constraint_memberContext *requirement_constraint_member();
    Framed_concern_memberContext *framed_concern_member();
    Requirement_verification_memberContext *requirement_verification_member();
    Actor_memberContext *actor_member();
    Stakeholder_memberContext *stakeholder_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Requirement_body_itemContext* requirement_body_item();

  class SYSMLV2FILE_EXPORT Subject_memberContext : public antlr4::ParserRuleContext {
  public:
    Subject_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Subject_usageContext *subject_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Subject_memberContext* subject_member();

  class SYSMLV2FILE_EXPORT Subject_usageContext : public antlr4::ParserRuleContext {
  public:
    Subject_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_SUBJECT();
    UsageContext *usage();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Subject_usageContext* subject_usage();

  class SYSMLV2FILE_EXPORT Requirement_constraint_memberContext : public antlr4::ParserRuleContext {
  public:
    Requirement_constraint_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Requriement_kindContext *requriement_kind();
    Requirement_constraint_usageContext *requirement_constraint_usage();
    Member_prefixContext *member_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Requirement_constraint_memberContext* requirement_constraint_member();

  class SYSMLV2FILE_EXPORT Requriement_kindContext : public antlr4::ParserRuleContext {
  public:
    Requriement_kindContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ASSUME();
    antlr4::tree::TerminalNode *KEYWORD_REQUIRE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Requriement_kindContext* requriement_kind();

  class SYSMLV2FILE_EXPORT Requirement_constraint_usageContext : public antlr4::ParserRuleContext {
  public:
    Requirement_constraint_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    Requirement_bodyContext *requirement_body();
    Feature_specialization_partContext *feature_specialization_part();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Calculation_bodyContext *calculation_body();
    antlr4::tree::TerminalNode *KEYWORD_CONSTRAINT();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Requirement_constraint_usageContext* requirement_constraint_usage();

  class SYSMLV2FILE_EXPORT Framed_concern_memberContext : public antlr4::ParserRuleContext {
  public:
    Framed_concern_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_FRAME();
    Framed_concern_usageContext *framed_concern_usage();
    Member_prefixContext *member_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Framed_concern_memberContext* framed_concern_member();

  class SYSMLV2FILE_EXPORT Framed_concern_usageContext : public antlr4::ParserRuleContext {
  public:
    Framed_concern_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    Calculation_bodyContext *calculation_body();
    Feature_specialization_partContext *feature_specialization_part();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    antlr4::tree::TerminalNode *KEYWORD_CONSTRAINT();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Framed_concern_usageContext* framed_concern_usage();

  class SYSMLV2FILE_EXPORT Actor_memberContext : public antlr4::ParserRuleContext {
  public:
    Actor_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Actor_usageContext *actor_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Actor_memberContext* actor_member();

  class SYSMLV2FILE_EXPORT Actor_usageContext : public antlr4::ParserRuleContext {
  public:
    Actor_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ACTOR();
    UsageContext *usage();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Actor_usageContext* actor_usage();

  class SYSMLV2FILE_EXPORT Stakeholder_memberContext : public antlr4::ParserRuleContext {
  public:
    Stakeholder_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    Stakeholder_usageContext *stakeholder_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stakeholder_memberContext* stakeholder_member();

  class SYSMLV2FILE_EXPORT Stakeholder_usageContext : public antlr4::ParserRuleContext {
  public:
    Stakeholder_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_STAKEHOLDER();
    Usage_extention_keywordContext *usage_extention_keyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Stakeholder_usageContext* stakeholder_usage();

  class SYSMLV2FILE_EXPORT Requirement_usageContext : public antlr4::ParserRuleContext {
  public:
    Requirement_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_REQUIREMENT();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Requirement_bodyContext *requirement_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Requirement_usageContext* requirement_usage();

  class SYSMLV2FILE_EXPORT Satisfy_requirement_usageContext : public antlr4::ParserRuleContext {
  public:
    Satisfy_requirement_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ASSERT();
    antlr4::tree::TerminalNode *KEYWORD_SATISFY();
    Requirement_bodyContext *requirement_body();
    Owned_reference_subsettingContext *owned_reference_subsetting();
    antlr4::tree::TerminalNode *KEYWORD_REQUIREMENT();
    Usage_declarationContext *usage_declaration();
    antlr4::tree::TerminalNode *KEYWORD_NOT();
    Value_partContext *value_part();
    antlr4::tree::TerminalNode *KEYWORD_BY();
    Satisfaction_subject_memberContext *satisfaction_subject_member();
    Feature_specialization_partContext *feature_specialization_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Satisfy_requirement_usageContext* satisfy_requirement_usage();

  class SYSMLV2FILE_EXPORT Satisfaction_subject_memberContext : public antlr4::ParserRuleContext {
  public:
    Satisfaction_subject_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Satisfaction_parameterContext *satisfaction_parameter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Satisfaction_subject_memberContext* satisfaction_subject_member();

  class SYSMLV2FILE_EXPORT Satisfaction_parameterContext : public antlr4::ParserRuleContext {
  public:
    Satisfaction_parameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Satisfaction_feature_valueContext *satisfaction_feature_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Satisfaction_parameterContext* satisfaction_parameter();

  class SYSMLV2FILE_EXPORT Satisfaction_feature_valueContext : public antlr4::ParserRuleContext {
  public:
    Satisfaction_feature_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Satisfaction_reference_expressionContext *satisfaction_reference_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Satisfaction_feature_valueContext* satisfaction_feature_value();

  class SYSMLV2FILE_EXPORT Satisfaction_reference_expressionContext : public antlr4::ParserRuleContext {
  public:
    Satisfaction_reference_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_chain_memberContext *feature_chain_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Satisfaction_reference_expressionContext* satisfaction_reference_expression();

  class SYSMLV2FILE_EXPORT Concern_definitionContext : public antlr4::ParserRuleContext {
  public:
    Concern_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CONCERN();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Requirement_bodyContext *requirement_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Concern_definitionContext* concern_definition();

  class SYSMLV2FILE_EXPORT Concern_usageContext : public antlr4::ParserRuleContext {
  public:
    Concern_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CONCERN();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Requirement_bodyContext *requirement_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Concern_usageContext* concern_usage();

  class SYSMLV2FILE_EXPORT Case_definitionContext : public antlr4::ParserRuleContext {
  public:
    Case_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CASE();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Case_bodyContext *case_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Case_definitionContext* case_definition();

  class SYSMLV2FILE_EXPORT Case_usageContext : public antlr4::ParserRuleContext {
  public:
    Case_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_CASE();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Case_bodyContext *case_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Case_usageContext* case_usage();

  class SYSMLV2FILE_EXPORT Case_bodyContext : public antlr4::ParserRuleContext {
  public:
    Case_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<Case_body_itemContext *> case_body_item();
    Case_body_itemContext* case_body_item(size_t i);
    Result_expression_memberContext *result_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Case_bodyContext* case_body();

  class SYSMLV2FILE_EXPORT Case_body_itemContext : public antlr4::ParserRuleContext {
  public:
    Case_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Action_body_itemContext *action_body_item();
    Subject_memberContext *subject_member();
    Actor_memberContext *actor_member();
    Objective_memberContext *objective_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Case_body_itemContext* case_body_item();

  class SYSMLV2FILE_EXPORT Objective_memberContext : public antlr4::ParserRuleContext {
  public:
    Objective_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_OBJECTIVE();
    Objective_requirement_usageContext *objective_requirement_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Objective_memberContext* objective_member();

  class SYSMLV2FILE_EXPORT Objective_requirement_usageContext : public antlr4::ParserRuleContext {
  public:
    Objective_requirement_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Requirement_bodyContext *requirement_body();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Objective_requirement_usageContext* objective_requirement_usage();

  class SYSMLV2FILE_EXPORT Analysis_case_definitionContext : public antlr4::ParserRuleContext {
  public:
    Analysis_case_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ANALYSIS();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Case_bodyContext *case_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Analysis_case_definitionContext* analysis_case_definition();

  class SYSMLV2FILE_EXPORT Analysis_case_usageContext : public antlr4::ParserRuleContext {
  public:
    Analysis_case_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_ANALYSIS();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Case_bodyContext *case_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Analysis_case_usageContext* analysis_case_usage();

  class SYSMLV2FILE_EXPORT Verification_case_definitionContext : public antlr4::ParserRuleContext {
  public:
    Verification_case_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_VERIFICATION();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Case_bodyContext *case_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Verification_case_definitionContext* verification_case_definition();

  class SYSMLV2FILE_EXPORT Verification_case_usageContext : public antlr4::ParserRuleContext {
  public:
    Verification_case_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_VERIFICATION();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Case_bodyContext *case_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Verification_case_usageContext* verification_case_usage();

  class SYSMLV2FILE_EXPORT Requirement_verification_memberContext : public antlr4::ParserRuleContext {
  public:
    Requirement_verification_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_VERIFY();
    Requirement_verification_usageContext *requirement_verification_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Requirement_verification_memberContext* requirement_verification_member();

  class SYSMLV2FILE_EXPORT Requirement_verification_usageContext : public antlr4::ParserRuleContext {
  public:
    Requirement_verification_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    Requirement_bodyContext *requirement_body();
    std::vector<Feature_specializationContext *> feature_specialization();
    Feature_specializationContext* feature_specialization(size_t i);
    Constraint_usage_declarationContext *constraint_usage_declaration();
    antlr4::tree::TerminalNode *KEYWORD_REQUIREMENT();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Requirement_verification_usageContext* requirement_verification_usage();

  class SYSMLV2FILE_EXPORT Use_case_definitionContext : public antlr4::ParserRuleContext {
  public:
    Use_case_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_USE();
    antlr4::tree::TerminalNode *KEYWORD_CASE();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Case_bodyContext *case_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Use_case_definitionContext* use_case_definition();

  class SYSMLV2FILE_EXPORT Use_case_usageContext : public antlr4::ParserRuleContext {
  public:
    Use_case_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_USE();
    antlr4::tree::TerminalNode *KEYWORD_CASE();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Case_bodyContext *case_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Use_case_usageContext* use_case_usage();

  class SYSMLV2FILE_EXPORT Include_use_case_usageContext : public antlr4::ParserRuleContext {
  public:
    Include_use_case_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_INCLUDE();
    Case_bodyContext *case_body();
    Owned_reference_subsettingContext *owned_reference_subsetting();
    antlr4::tree::TerminalNode *KEYWORD_USE();
    antlr4::tree::TerminalNode *KEYWORD_CASE();
    Usage_declarationContext *usage_declaration();
    Value_partContext *value_part();
    Feature_specialization_partContext *feature_specialization_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Include_use_case_usageContext* include_use_case_usage();

  class SYSMLV2FILE_EXPORT View_definitionContext : public antlr4::ParserRuleContext {
  public:
    View_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_VIEW();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    View_definition_bodyContext *view_definition_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  View_definitionContext* view_definition();

  class SYSMLV2FILE_EXPORT View_definition_bodyContext : public antlr4::ParserRuleContext {
  public:
    View_definition_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<View_definition_body_itemContext *> view_definition_body_item();
    View_definition_body_itemContext* view_definition_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  View_definition_bodyContext* view_definition_body();

  class SYSMLV2FILE_EXPORT View_definition_body_itemContext : public antlr4::ParserRuleContext {
  public:
    View_definition_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_body_itemContext *definition_body_item();
    Element_filter_memberContext *element_filter_member();
    View_rendering_memberContext *view_rendering_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  View_definition_body_itemContext* view_definition_body_item();

  class SYSMLV2FILE_EXPORT View_rendering_memberContext : public antlr4::ParserRuleContext {
  public:
    View_rendering_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_prefixContext *member_prefix();
    antlr4::tree::TerminalNode *KEYWORD_RENDER();
    View_rendering_usageContext *view_rendering_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  View_rendering_memberContext* view_rendering_member();

  class SYSMLV2FILE_EXPORT View_rendering_usageContext : public antlr4::ParserRuleContext {
  public:
    View_rendering_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    Usage_bodyContext *usage_body();
    Feature_specialization_partContext *feature_specialization_part();
    UsageContext *usage();
    antlr4::tree::TerminalNode *KEYWORD_RENDERING();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  View_rendering_usageContext* view_rendering_usage();

  class SYSMLV2FILE_EXPORT View_usageContext : public antlr4::ParserRuleContext {
  public:
    View_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_VIEW();
    View_bodyContext *view_body();
    Usage_declarationContext *usage_declaration();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  View_usageContext* view_usage();

  class SYSMLV2FILE_EXPORT View_bodyContext : public antlr4::ParserRuleContext {
  public:
    View_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    std::vector<View_body_itemContext *> view_body_item();
    View_body_itemContext* view_body_item(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  View_bodyContext* view_body();

  class SYSMLV2FILE_EXPORT View_body_itemContext : public antlr4::ParserRuleContext {
  public:
    View_body_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Definition_body_itemContext *definition_body_item();
    Element_filter_memberContext *element_filter_member();
    View_rendering_memberContext *view_rendering_member();
    ExposeContext *expose();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  View_body_itemContext* view_body_item();

  class SYSMLV2FILE_EXPORT ExposeContext : public antlr4::ParserRuleContext {
  public:
    ExposeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_EXPOSE();
    Relationship_bodyContext *relationship_body();
    Membership_exposeContext *membership_expose();
    Namespace_exposeContext *namespace_expose();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExposeContext* expose();

  class SYSMLV2FILE_EXPORT Membership_exposeContext : public antlr4::ParserRuleContext {
  public:
    Membership_exposeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Membership_importContext *membership_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Membership_exposeContext* membership_expose();

  class SYSMLV2FILE_EXPORT Namespace_exposeContext : public antlr4::ParserRuleContext {
  public:
    Namespace_exposeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Namespace_importContext *namespace_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Namespace_exposeContext* namespace_expose();

  class SYSMLV2FILE_EXPORT Viewpoint_definitionContext : public antlr4::ParserRuleContext {
  public:
    Viewpoint_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_VIEWPOINT();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    Definition_declarationContext *definition_declaration();
    Requirement_bodyContext *requirement_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Viewpoint_definitionContext* viewpoint_definition();

  class SYSMLV2FILE_EXPORT Viewpoint_usageContext : public antlr4::ParserRuleContext {
  public:
    Viewpoint_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_VIEWPOINT();
    Constraint_usage_declarationContext *constraint_usage_declaration();
    Requirement_bodyContext *requirement_body();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Viewpoint_usageContext* viewpoint_usage();

  class SYSMLV2FILE_EXPORT Rendering_definitionContext : public antlr4::ParserRuleContext {
  public:
    Rendering_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_definition_prefixContext *occurrence_definition_prefix();
    antlr4::tree::TerminalNode *KEYWORD_RENDERING();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Rendering_definitionContext* rendering_definition();

  class SYSMLV2FILE_EXPORT Rendering_usageContext : public antlr4::ParserRuleContext {
  public:
    Rendering_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Occurrence_usage_prefixContext *occurrence_usage_prefix();
    antlr4::tree::TerminalNode *KEYWORD_RENDERING();
    UsageContext *usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Rendering_usageContext* rendering_usage();

  class SYSMLV2FILE_EXPORT Metadata_definitionContext : public antlr4::ParserRuleContext {
  public:
    Metadata_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_METADATA();
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();
    antlr4::tree::TerminalNode *KEYWORD_ABSTRACT();
    std::vector<Definition_extension_keywordContext *> definition_extension_keyword();
    Definition_extension_keywordContext* definition_extension_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_definitionContext* metadata_definition();

  class SYSMLV2FILE_EXPORT Prefix_metadata_annotationContext : public antlr4::ParserRuleContext {
  public:
    Prefix_metadata_annotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_HASHTAG();
    Prefix_metadata_usageContext *prefix_metadata_usage();
    Annotating_elementContext *annotating_element();

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
    Prefix_metadata_usageContext *prefix_metadata_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Prefix_metadata_memberContext* prefix_metadata_member();

  class SYSMLV2FILE_EXPORT Prefix_metadata_usageContext : public antlr4::ParserRuleContext {
  public:
    Prefix_metadata_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_feature_typingContext *owned_feature_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Prefix_metadata_usageContext* prefix_metadata_usage();

  class SYSMLV2FILE_EXPORT Metadata_usageContext : public antlr4::ParserRuleContext {
  public:
    Metadata_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_usage_declarationContext *metadata_usage_declaration();
    Metadata_bodyContext *metadata_body();
    antlr4::tree::TerminalNode *SYMBOL_AT();
    antlr4::tree::TerminalNode *KEYWORD_METADATA();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_ABOUT();
    std::vector<AnnotationContext *> annotation();
    AnnotationContext* annotation(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_usageContext* metadata_usage();

  class SYSMLV2FILE_EXPORT Metadata_usage_declarationContext : public antlr4::ParserRuleContext {
  public:
    Metadata_usage_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_feature_typingContext *owned_feature_typing();
    IdentificationContext *identification();
    Defined_byContext *defined_by();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_usage_declarationContext* metadata_usage_declaration();

  class SYSMLV2FILE_EXPORT Metadata_bodyContext : public antlr4::ParserRuleContext {
  public:
    Metadata_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *SYMBOL_CURLY_BRACKET_CLOSE();
    Definition_memberContext *definition_member();
    Metadata_body_usage_memberContext *metadata_body_usage_member();
    Alias_memberContext *alias_member();
    Namespace_importContext *namespace_import();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_bodyContext* metadata_body();

  class SYSMLV2FILE_EXPORT Metadata_body_usage_memberContext : public antlr4::ParserRuleContext {
  public:
    Metadata_body_usage_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_body_usageContext *metadata_body_usage();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_body_usage_memberContext* metadata_body_usage_member();

  class SYSMLV2FILE_EXPORT Metadata_body_usageContext : public antlr4::ParserRuleContext {
  public:
    Metadata_body_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_redefinitionContext *owned_redefinition();
    Metadata_bodyContext *metadata_body();
    antlr4::tree::TerminalNode *KEYWORD_REF();
    antlr4::tree::TerminalNode *REDEFINES();
    Feature_specialization_partContext *feature_specialization_part();
    Value_partContext *value_part();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_body_usageContext* metadata_body_usage();

  class SYSMLV2FILE_EXPORT Extended_definitionContext : public antlr4::ParserRuleContext {
  public:
    Extended_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_DEF();
    DefinitionContext *definition();
    Basic_definition_prefixContext *basic_definition_prefix();
    std::vector<Definition_extension_keywordContext *> definition_extension_keyword();
    Definition_extension_keywordContext* definition_extension_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Extended_definitionContext* extended_definition();

  class SYSMLV2FILE_EXPORT Extended_usageContext : public antlr4::ParserRuleContext {
  public:
    Extended_usageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unextended_usage_prefixContext *unextended_usage_prefix();
    UsageContext *usage();
    std::vector<Usage_extention_keywordContext *> usage_extention_keyword();
    Usage_extention_keywordContext* usage_extention_keyword(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Extended_usageContext* extended_usage();

  class SYSMLV2FILE_EXPORT Defined_byContext : public antlr4::ParserRuleContext {
  public:
    Defined_byContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_TYPED_BY();
    antlr4::tree::TerminalNode *KEYWORD_DEFINED();
    antlr4::tree::TerminalNode *KEYWORD_BY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Defined_byContext* defined_by();

  class SYSMLV2FILE_EXPORT ElementsContext : public antlr4::ParserRuleContext {
  public:
    ElementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
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
    Visibility_indicatorContext *visibility_indicator();
    antlr4::tree::TerminalNode *KEYWORD_ALL();
    Relationship_bodyContext *relationship_body();

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
    Annotating_elementContext *annotating_element();
    Non_feature_elementContext *non_feature_element();
    Feature_elementContext *feature_element();
    Additional_optionsContext *additional_options();

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
    antlr4::tree::TerminalNode *SPECIALIZES();
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
    antlr4::tree::TerminalNode *CONJUGATES();
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
    std::vector<ElementContext *> element();
    ElementContext* element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_body_elementsContext* type_body_elements();

  class SYSMLV2FILE_EXPORT Type_body_elementContext : public antlr4::ParserRuleContext {
  public:
    Type_body_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
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
    antlr4::tree::TerminalNode *SPECIALIZES();
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
    antlr4::tree::TerminalNode *CONJUGATES();
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
    antlr4::tree::TerminalNode *SPECIALIZES();
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
    antlr4::tree::TerminalNode *SPECIALIZES();
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
    Type_bodyContext *type_body();
    antlr4::tree::TerminalNode *KEYWORD_FEATURE();
    Prefix_metadata_memberContext *prefix_metadata_member();
    Feature_prefixContext *feature_prefix();
    SubsettingsContext *subsettings();
    Feature_assignmentContext *feature_assignment();
    Feature_valueContext *feature_value();
    Feature_declarationContext *feature_declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FeatureContext* feature();

  class SYSMLV2FILE_EXPORT Feature_prefixContext : public antlr4::ParserRuleContext {
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
    antlr4::tree::TerminalNode *KEYWORD_VAR();
    antlr4::tree::TerminalNode *KEYWORD_COMPOSITE();
    antlr4::tree::TerminalNode *KEYWORD_PORTION();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_prefixContext* feature_prefix();

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
    Type_bodyContext *type_body();

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

  class SYSMLV2FILE_EXPORT Feature_specializationContext : public antlr4::ParserRuleContext {
  public:
    Feature_specializationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypingsContext *typings();
    SubsettingsContext *subsettings();
    ReferencesContext *references();
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
    antlr4::tree::TerminalNode *TYPED_BY();
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
    std::vector<Owned_subsettingContext *> owned_subsetting();
    Owned_subsettingContext* owned_subsetting(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SYMBOL_COMMA();
    antlr4::tree::TerminalNode* SYMBOL_COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubsettingsContext* subsettings();

  class SYSMLV2FILE_EXPORT SubsetsContext : public antlr4::ParserRuleContext {
  public:
    SubsetsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUBSETS();
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
    antlr4::tree::TerminalNode *REFERENCES();
    Owned_reference_subsettingContext *owned_reference_subsetting();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReferencesContext* references();

  class SYSMLV2FILE_EXPORT RedefinitionsContext : public antlr4::ParserRuleContext {
  public:
    RedefinitionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RedefinesContext *redefines();
    antlr4::tree::TerminalNode *SYMBOL_COMMA();
    Owned_redefinitionContext *owned_redefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RedefinitionsContext* redefinitions();

  class SYSMLV2FILE_EXPORT RedefinesContext : public antlr4::ParserRuleContext {
  public:
    RedefinesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REDEFINES();
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
    antlr4::tree::TerminalNode *TYPED_BY();
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
    antlr4::tree::TerminalNode *SUBSETS();
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

  class SYSMLV2FILE_EXPORT RedefinitionContext : public antlr4::ParserRuleContext {
  public:
    RedefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REDEFINES();
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
    antlr4::tree::TerminalNode *KEYWORD_CONNECTOR();
    Connector_declarationContext *connector_declaration();
    Type_bodyContext *type_body();
    Type_prefixContext *type_prefix();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConnectorContext* connector();

  class SYSMLV2FILE_EXPORT Connector_declarationContext : public antlr4::ParserRuleContext {
  public:
    Connector_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_declarationContext *feature_declaration();
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
    antlr4::tree::TerminalNode *KEYWORD_FROM();
    std::vector<Connector_end_memberContext *> connector_end_member();
    Connector_end_memberContext* connector_end_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_TO();
    antlr4::tree::TerminalNode *KEYWORD_ALL();

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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Nary_connector_declarationContext* nary_connector_declaration();

  class SYSMLV2FILE_EXPORT Connector_endContext : public antlr4::ParserRuleContext {
  public:
    Connector_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_reference_subsettingContext *owned_reference_subsetting();
    antlr4::tree::TerminalNode *NAME();
    antlr4::tree::TerminalNode *REFERENCES();
    Multiplicity_boundsContext *multiplicity_bounds();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Connector_endContext* connector_end();

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
    antlr4::tree::TerminalNode *SYMBOL_EQUALS();
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
    Feature_declarationContext *feature_declaration();
    Function_bodyContext *function_body();
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
    Owned_expressionsContext *owned_expressions();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_expression_memberContext* owned_expression_member();

  class SYSMLV2FILE_EXPORT Owned_expressionsContext : public antlr4::ParserRuleContext {
  public:
    Owned_expressionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Owned_expressionContext *> owned_expression();
    Owned_expressionContext* owned_expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_expressionsContext* owned_expressions();

  class SYSMLV2FILE_EXPORT Owned_expressionContext : public antlr4::ParserRuleContext {
  public:
    Owned_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Base_expressionContext *base_expression();
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Owned_expressionContext* owned_expression();

  class SYSMLV2FILE_EXPORT Eased_owned_expressionContext : public antlr4::ParserRuleContext {
  public:
    Eased_owned_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primary_expressionContext *primary_expression();
    Extend_expressionContext *extend_expression();
    Metaclassification_expressionContext *metaclassification_expression();
    Unary_operator_expressionContext *unary_operator_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Eased_owned_expressionContext* eased_owned_expression();

  class SYSMLV2FILE_EXPORT Conditional_expressionContext : public antlr4::ParserRuleContext {
  public:
    Conditional_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_IF();
    Argument_memberContext *argument_member();
    antlr4::tree::TerminalNode *SYMBOL_QUESTION();
    std::vector<Argument_expression_memberContext *> argument_expression_member();
    Argument_expression_memberContext* argument_expression_member(size_t i);
    antlr4::tree::TerminalNode *KEYWORD_ELSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Conditional_expressionContext* conditional_expression();

  class SYSMLV2FILE_EXPORT Conditional_binary_operator_expressionContext : public antlr4::ParserRuleContext {
  public:
    Conditional_binary_operator_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_memberContext *argument_member();
    Conditional_binary_operatorContext *conditional_binary_operator();
    Argument_expression_memberContext *argument_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Conditional_binary_operator_expressionContext* conditional_binary_operator_expression();

  class SYSMLV2FILE_EXPORT Conditional_binary_operatorContext : public antlr4::ParserRuleContext {
  public:
    Conditional_binary_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DQUESTION();
    antlr4::tree::TerminalNode *KEYWORD_OR();
    antlr4::tree::TerminalNode *KEYWORD_AND();
    antlr4::tree::TerminalNode *KEYWORD_IMPLIES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Conditional_binary_operatorContext* conditional_binary_operator();

  class SYSMLV2FILE_EXPORT Binary_operator_expressionContext : public antlr4::ParserRuleContext {
  public:
    Binary_operator_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_memberContext *argument_member();
    Binary_operatorContext *binary_operator();
    Owned_expressionsContext *owned_expressions();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Binary_operator_expressionContext* binary_operator_expression();

  class SYSMLV2FILE_EXPORT Binary_operatorContext : public antlr4::ParserRuleContext {
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Binary_operatorContext* binary_operator();

  class SYSMLV2FILE_EXPORT Unary_operator_expressionContext : public antlr4::ParserRuleContext {
  public:
    Unary_operator_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unary_operatorContext *unary_operator();
    Owned_expressionsContext *owned_expressions();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Unary_operator_expressionContext* unary_operator_expression();

  class SYSMLV2FILE_EXPORT Unary_operatorContext : public antlr4::ParserRuleContext {
  public:
    Unary_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_PLUS();
    antlr4::tree::TerminalNode *SYMBOL_MINUS();
    antlr4::tree::TerminalNode *SYMBOL_CONJUGATES();
    antlr4::tree::TerminalNode *KEYWORD_NOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Unary_operatorContext* unary_operator();

  class SYSMLV2FILE_EXPORT Classification_expressionContext : public antlr4::ParserRuleContext {
  public:
    Classification_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_memberContext *argument_member();
    Classification_test_operatorContext *classification_test_operator();
    Type_reference_memberContext *type_reference_member();
    Cast_operatorContext *cast_operator();
    Type_result_memberContext *type_result_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Classification_expressionContext* classification_expression();

  class SYSMLV2FILE_EXPORT ClassificationContext : public antlr4::ParserRuleContext {
  public:
    ClassificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classification_test_operatorContext *classification_test_operator();
    Type_reference_memberContext *type_reference_member();
    Argument_memberContext *argument_member();
    Cast_operatorContext *cast_operator();
    Type_result_memberContext *type_result_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassificationContext* classification();

  class SYSMLV2FILE_EXPORT Classification_test_operatorContext : public antlr4::ParserRuleContext {
  public:
    Classification_test_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ISTYPE();
    antlr4::tree::TerminalNode *KEYWORD_HASTYPE();
    antlr4::tree::TerminalNode *SYMBOL_AT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Classification_test_operatorContext* classification_test_operator();

  class SYSMLV2FILE_EXPORT Cast_operatorContext : public antlr4::ParserRuleContext {
  public:
    Cast_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_AS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Cast_operatorContext* cast_operator();

  class SYSMLV2FILE_EXPORT Metaclassification_expressionContext : public antlr4::ParserRuleContext {
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metaclassification_expressionContext* metaclassification_expression();

  class SYSMLV2FILE_EXPORT Argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArgumentContext *argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Argument_memberContext* argument_member();

  class SYSMLV2FILE_EXPORT ArgumentContext : public antlr4::ParserRuleContext {
  public:
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_valueContext *argument_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentContext* argument();

  class SYSMLV2FILE_EXPORT Argument_valueContext : public antlr4::ParserRuleContext {
  public:
    Argument_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Eased_owned_expressionContext *eased_owned_expression();
    antlr4::tree::TerminalNode *STRING_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Argument_valueContext* argument_value();

  class SYSMLV2FILE_EXPORT Argument_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Argument_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_expressionContext *argument_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Argument_expression_memberContext* argument_expression_member();

  class SYSMLV2FILE_EXPORT Argument_expressionContext : public antlr4::ParserRuleContext {
  public:
    Argument_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Argument_expression_valueContext *argument_expression_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Argument_expressionContext* argument_expression();

  class SYSMLV2FILE_EXPORT Argument_expression_valueContext : public antlr4::ParserRuleContext {
  public:
    Argument_expression_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Owned_expression_referenceContext *owned_expression_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Argument_expression_valueContext* argument_expression_value();

  class SYSMLV2FILE_EXPORT Metadata_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Metadata_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_argumentContext *metadata_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_argument_memberContext* metadata_argument_member();

  class SYSMLV2FILE_EXPORT Metadata_argumentContext : public antlr4::ParserRuleContext {
  public:
    Metadata_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_valueContext *metadata_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_argumentContext* metadata_argument();

  class SYSMLV2FILE_EXPORT Metadata_valueContext : public antlr4::ParserRuleContext {
  public:
    Metadata_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Metadata_referenceContext *metadata_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_valueContext* metadata_value();

  class SYSMLV2FILE_EXPORT Metadata_referenceContext : public antlr4::ParserRuleContext {
  public:
    Metadata_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_nameContext *qualified_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_referenceContext* metadata_reference();

  class SYSMLV2FILE_EXPORT Metadataclassification_test_operatorContext : public antlr4::ParserRuleContext {
  public:
    Metadataclassification_test_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadataclassification_test_operatorContext* metadataclassification_test_operator();

  class SYSMLV2FILE_EXPORT Meta_cast_operatorContext : public antlr4::ParserRuleContext {
  public:
    Meta_cast_operatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Meta_cast_operatorContext* meta_cast_operator();

  class SYSMLV2FILE_EXPORT Extend_expressionContext : public antlr4::ParserRuleContext {
  public:
    Extend_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYWORD_ALL();
    Type_reference_memberContext *type_reference_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Extend_expressionContext* extend_expression();

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

  class SYSMLV2FILE_EXPORT Primary_expressionsContext : public antlr4::ParserRuleContext {
  public:
    Primary_expressionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Primary_expressionContext *> primary_expression();
    Primary_expressionContext* primary_expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Primary_expressionsContext* primary_expressions();

  class SYSMLV2FILE_EXPORT Primary_expressionContext : public antlr4::ParserRuleContext {
  public:
    Primary_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Feature_chain_expressionContext *feature_chain_expression();
    Non_feature_chain_primary_expressionContext *non_feature_chain_primary_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Primary_expressionContext* primary_expression();

  class SYSMLV2FILE_EXPORT Primary_argument_valueContext : public antlr4::ParserRuleContext {
  public:
    Primary_argument_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primary_expressionContext *primary_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Primary_argument_valueContext* primary_argument_value();

  class SYSMLV2FILE_EXPORT Primary_argumentContext : public antlr4::ParserRuleContext {
  public:
    Primary_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primary_argument_valueContext *primary_argument_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Primary_argumentContext* primary_argument();

  class SYSMLV2FILE_EXPORT Primary_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Primary_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primary_argumentContext *primary_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Primary_argument_memberContext* primary_argument_member();

  class SYSMLV2FILE_EXPORT Non_feature_chain_primary_expressionContext : public antlr4::ParserRuleContext {
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Non_feature_chain_primary_expressionContext* non_feature_chain_primary_expression();

  class SYSMLV2FILE_EXPORT Non_feature_chain_primary_argument_valueContext : public antlr4::ParserRuleContext {
  public:
    Non_feature_chain_primary_argument_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Non_feature_chain_primary_expressionContext *non_feature_chain_primary_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Non_feature_chain_primary_argument_valueContext* non_feature_chain_primary_argument_value();

  class SYSMLV2FILE_EXPORT Non_feature_chain_primary_argumentContext : public antlr4::ParserRuleContext {
  public:
    Non_feature_chain_primary_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primary_argumentContext *primary_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Non_feature_chain_primary_argumentContext* non_feature_chain_primary_argument();

  class SYSMLV2FILE_EXPORT Non_feature_chain_primary_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Non_feature_chain_primary_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primary_argumentContext *primary_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Non_feature_chain_primary_argument_memberContext* non_feature_chain_primary_argument_member();

  class SYSMLV2FILE_EXPORT Bracket_expressionContext : public antlr4::ParserRuleContext {
  public:
    Bracket_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_OPEN();
    Sequence_expression_list_memberContext *sequence_expression_list_member();
    antlr4::tree::TerminalNode *SYMBOL_SQUARE_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Bracket_expressionContext* bracket_expression();

  class SYSMLV2FILE_EXPORT Index_expressionContext : public antlr4::ParserRuleContext {
  public:
    Index_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_HASHTAG();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    Sequence_expression_list_memberContext *sequence_expression_list_member();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Index_expressionContext* index_expression();

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
    Owned_expressionsContext *owned_expressions();
    antlr4::tree::TerminalNode *SYMBOL_COMMA();
    Sequence_operator_expressionContext *sequence_operator_expression();

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

  class SYSMLV2FILE_EXPORT Feature_chain_expressionContext : public antlr4::ParserRuleContext {
  public:
    Feature_chain_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    Feature_chain_memberContext *feature_chain_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Feature_chain_expressionContext* feature_chain_expression();

  class SYSMLV2FILE_EXPORT Collect_expressionContext : public antlr4::ParserRuleContext {
  public:
    Collect_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT();
    Body_expression_memberContext *body_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Collect_expressionContext* collect_expression();

  class SYSMLV2FILE_EXPORT Select_expressionContext : public antlr4::ParserRuleContext {
  public:
    Select_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_DOT_QUESTION();
    Body_expression_memberContext *body_expression_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Select_expressionContext* select_expression();

  class SYSMLV2FILE_EXPORT Function_operation_expressionContext : public antlr4::ParserRuleContext {
  public:
    Function_operation_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOL_ARROW();
    Reference_typingContext *reference_typing();
    Body_argument_memberContext *body_argument_member();
    Function_reference_argument_memberContext *function_reference_argument_member();
    Argument_expressionContext *argument_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_operation_expressionContext* function_operation_expression();

  class SYSMLV2FILE_EXPORT Body_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Body_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_argumentContext *body_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Body_argument_memberContext* body_argument_member();

  class SYSMLV2FILE_EXPORT Body_argumentContext : public antlr4::ParserRuleContext {
  public:
    Body_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_argument_valueContext *body_argument_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Body_argumentContext* body_argument();

  class SYSMLV2FILE_EXPORT Body_argument_valueContext : public antlr4::ParserRuleContext {
  public:
    Body_argument_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_expressionContext *body_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Body_argument_valueContext* body_argument_value();

  class SYSMLV2FILE_EXPORT Body_expression_memberContext : public antlr4::ParserRuleContext {
  public:
    Body_expression_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Body_expressionContext *body_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Body_expression_memberContext* body_expression_member();

  class SYSMLV2FILE_EXPORT Function_reference_argument_memberContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_argument_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_reference_argumentContext *function_reference_argument();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_reference_argument_memberContext* function_reference_argument_member();

  class SYSMLV2FILE_EXPORT Function_reference_argumentContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_argumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_reference_memberContext *function_reference_member();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_reference_argumentContext* function_reference_argument();

  class SYSMLV2FILE_EXPORT Function_reference_arugment_valueContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_arugment_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_reference_expressionContext *function_reference_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_reference_arugment_valueContext* function_reference_arugment_value();

  class SYSMLV2FILE_EXPORT Function_reference_expressionContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reference_typingContext *reference_typing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_reference_expressionContext* function_reference_expression();

  class SYSMLV2FILE_EXPORT Function_reference_memberContext : public antlr4::ParserRuleContext {
  public:
    Function_reference_memberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_referenceContext *function_reference();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_reference_memberContext* function_reference_member();

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

  class SYSMLV2FILE_EXPORT Base_expressionContext : public antlr4::ParserRuleContext {
  public:
    Base_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Invocation_expressionContext *invocation_expression();
    Null_expressionContext *null_expression();
    Literal_expressionContext *literal_expression();
    Feature_reference_expressionContext *feature_reference_expression();
    Metadata_access_expressionContext *metadata_access_expression();
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
    antlr4::tree::TerminalNode *SYMBOL_EQUALS();
    Owned_expressionsContext *owned_expressions();

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
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_OPEN();
    Function_body_partContext *function_body_part();
    antlr4::tree::TerminalNode *SYMBOL_ROUND_BRACKET_CLOSE();

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
    antlr4::tree::TerminalNode *SPECIALIZES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MetaclassContext* metaclass();

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
    antlr4::tree::TerminalNode *SYMBOL_TYPED_BY();
    antlr4::tree::TerminalNode *KEYWORD_TYPED();
    antlr4::tree::TerminalNode *KEYWORD_BY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_feature_declarationContext* metadata_feature_declaration();

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
    Feature_specialization_partContext *feature_specialization_part();
    Value_partContext *value_part();
    antlr4::tree::TerminalNode *SYMBOL_REDEFINES();
    antlr4::tree::TerminalNode *KEYWORD_REDEFINES();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Metadata_body_featureContext* metadata_body_feature();

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
    antlr4::tree::TerminalNode *SYMBOL_STATEMENT_DELIMITER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Meta_assignmentContext* meta_assignment();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

