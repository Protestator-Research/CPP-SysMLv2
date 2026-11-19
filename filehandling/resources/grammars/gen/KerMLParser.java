// Generated from /home/herzog/Dokumente/Projekte/CPP-SysMLv2/filehandling/resources/grammars/KerML.g4 by ANTLR 4.13.2

    #include <sysmlv2/sysmlv2file_global.h>

import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class KerMLParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		KEYWORD_ABOUT=1, KEYWORD_ABSTRACT=2, KEYWORD_ALIAS=3, KEYWORD_ALL=4, KEYWORD_AND=5, 
		KEYWORD_AS=6, KEYWORD_ASSOC=7, KEYWORD_BEHAVIOR=8, KEYWORD_BINDING=9, 
		KEYWORD_BOOL=10, KEYWORD_BY=11, KEYWORD_CHAINS=12, KEYWORD_CLASS=13, KEYWORD_CLASSIFIER=14, 
		KEYWORD_COMMENT=15, KEYWORD_COMPOSITE=16, KEYWORD_CONJUGATE=17, KEYWORD_CONJUGATES=18, 
		KEYWORD_CONJUGATION=19, KEYWORD_CONNECTOR=20, KEYWORD_DATATYPE=21, KEYWORD_DEFAULT=22, 
		KEYWORD_DEPENDENCY=23, KEYWORD_DERIVED=24, KEYWORD_DIFFERENCES=25, KEYWORD_DISJOINING=26, 
		KEYWORD_DISJOINT=27, KEYWORD_DOC=28, KEYWORD_ELSE=29, KEYWORD_END=30, 
		KEYWORD_EXPR=31, KEYWORD_FALSE=32, KEYWORD_FEATURE=33, KEYWORD_FEATURED=34, 
		KEYWORD_FEATURING=35, KEYWORD_FILTER=36, KEYWORD_FIRST=37, KEYWORD_FLOW=38, 
		KEYWORD_FOR=39, KEYWORD_FROM=40, KEYWORD_FUNCTION=41, KEYWORD_HASTYPE=42, 
		KEYWORD_IF=43, KEYWORD_INTERSECTS=44, KEYWORD_IMPLIES=45, KEYWORD_IMPORT=46, 
		KEYWORD_IN=47, KEYWORD_INOUT=48, KEYWORD_INTERACTION=49, KEYWORD_INV=50, 
		KEYWORD_INVERSE=51, KEYWORD_INVERTING=52, KEYWORD_ISTYPE=53, KEYWORD_LANGUAGE=54, 
		KEYWORD_MEMBER=55, KEYWORD_METACLASS=56, KEYWORD_METADATA=57, KEYWORD_MULTIPLICITY=58, 
		KEYWORD_NAMESPACE=59, KEYWORD_NONUNIQUE=60, KEYWORD_NOT=61, KEYWORD_NULL=62, 
		KEYWORD_OF=63, KEYWORD_OR=64, KEYWORD_ORDERED=65, KEYWORD_OUT=66, KEYWORD_PACKAGE=67, 
		KEYWORD_PORTION=68, KEYWORD_PREDICATE=69, KEYWORD_PRIVATE=70, KEYWORD_PROTECTED=71, 
		KEYWORD_PUBLIC=72, KEYWORD_READONLY=73, KEYWORD_REDEFINES=74, KEYWORD_REDEFINITION=75, 
		KEYWORD_REFERENCES=76, KEYWORD_REP=77, KEYWORD_RETURN=78, KEYWORD_SPECIALIZATION=79, 
		KEYWORD_SPECIALIZES=80, KEYWORD_STEP=81, KEYWORD_STRUCT=82, KEYWORD_SUBCLASSIFIER=83, 
		KEYWORD_SUBSET=84, KEYWORD_SUBSETS=85, KEYWORD_SUBTYPE=86, KEYWORD_SUCCESSION=87, 
		KEYWORD_THEN=88, KEYWORD_TO=89, KEYWORD_TRUE=90, KEYWORD_TYPE=91, KEYWORD_TYPED=92, 
		KEYWORD_TYPING=93, KEYWORD_UNIONS=94, KEYWORD_XOR=95, KEYWORD_VAR=96, 
		KEYWORD_LOCALE=97, KEYWORD_STANDARD=98, KEYWORD_LIBRARY=99, KEYWORD_CONST=100, 
		KEYWORD_CONSTANT=101, KEYWORD_CROSSES=102, KEYWORD_META=103, KEYWORD_NEW=104, 
		SINGLE_LINE_NOTE=105, MULTI_LINE_NOTE=106, REGULAR_COMMENT=107, SYMBOL_COMMENT_BLOCK_START=108, 
		SYMBOL_NOTE_BLOCK_START=109, SYMBOL_COMMENT_BLOCK_END=110, SYMBOL_STATEMENT_DELIMITER=111, 
		SYMBOL_STAR=112, SYMBOL_NAMESPACE_SUBSET=113, SYMBOL_TYPED_BY=114, SYMBOL_SPECIALIZES=115, 
		SYMBOL_REFERENCES=116, SYMBOL_REDEFINES=117, SYMBOL_CONJUGATES=118, SYMBOL_CROSSES=119, 
		SYMBOL_ROUND_BRACKET_OPEN=120, SYMBOL_ROUND_BRACKET_CLOSE=121, SYMBOL_CURLY_BRACKET_OPEN=122, 
		SYMBOL_CURLY_BRACKET_CLOSE=123, SYMBOL_SQUARE_BRACKET_OPEN=124, SYMBOL_SQUARE_BRACKET_CLOSE=125, 
		SYMBOL_COMMA=126, SYMBOL_AT=127, SYMBOL_HASHTAG=128, SYMBOL_MOD=129, SYMBOL_AND=130, 
		SYMBOL_UPPER=131, SYMBOL_VERTICAL_LINE=132, SYMBOL_DOUBLE_STAR=133, SYMBOL_PLUS=134, 
		SYMBOL_MINUS=135, SYMBOL_SLASH=136, SYMBOL_ARROW=137, SYMBOL_DOT=138, 
		SYMBOL_DDOT=139, SYMBOL_SMALLER=140, SYMBOL_SMALLER_EQUAL=141, SYMBOL_ASSIGN=142, 
		SYMBOL_DEF_ASSIGN=143, SYMBOL_EQUALS=144, SYMBOL_IFF_EQUALS=145, SYMBOL_NOT_EQUALS=146, 
		SYMBOL_IFF_NOT_EQUALS=147, SYMBOL_GREATER=148, SYMBOL_GREATER_EQUALS=149, 
		SYMBOL_QUESTION=150, SYMBOL_DQUESTION=151, SYMBOL_DOT_QUESTION=152, SYMBOL_ATAT=153, 
		NAME=154, BASIC_NAME=155, UNRESTRICTED_NAME=156, DECIMAL_VALUE=157, EXPONENTIAL_VALUE=158, 
		STRING_VALUE=159, WS=160;
	public static final int
		RULE_start = 0, RULE_startRule = 1, RULE_elements = 2, RULE_identification = 3, 
		RULE_relationship_body = 4, RULE_relationship_owned_elements = 5, RULE_relationship_owned_element = 6, 
		RULE_owned_related_element = 7, RULE_dependency = 8, RULE_annotation = 9, 
		RULE_owned_annotation = 10, RULE_annotating_element = 11, RULE_comment = 12, 
		RULE_documentation = 13, RULE_textual_representation = 14, RULE_root_namespace = 15, 
		RULE_namespace = 16, RULE_namespace_declaration = 17, RULE_namespace_body = 18, 
		RULE_namespace_body_elements = 19, RULE_namespace_body_element = 20, RULE_member_prefix = 21, 
		RULE_visibility_indicator = 22, RULE_namespace_member = 23, RULE_non_feature_member = 24, 
		RULE_namespace_feature_member = 25, RULE_alias_member = 26, RULE_qualified_name = 27, 
		RULE_namespace_import = 28, RULE_import_declaration = 29, RULE_membership_import = 30, 
		RULE_filter_package = 31, RULE_filter_package_member = 32, RULE_element = 33, 
		RULE_non_feature_element = 34, RULE_feature_element = 35, RULE_additional_options = 36, 
		RULE_type = 37, RULE_type_prefix = 38, RULE_type_declaration = 39, RULE_specialization_part = 40, 
		RULE_conjugation_part = 41, RULE_type_relationship_part = 42, RULE_disjoining_part = 43, 
		RULE_unioning_part = 44, RULE_intersecting_part = 45, RULE_differencing_part = 46, 
		RULE_type_body = 47, RULE_type_body_elements = 48, RULE_type_body_element = 49, 
		RULE_specialization = 50, RULE_owned_specialization = 51, RULE_specific_type = 52, 
		RULE_general_type = 53, RULE_conjunction = 54, RULE_owned_conjugation = 55, 
		RULE_disjoining = 56, RULE_owned_disjoining = 57, RULE_unioning = 58, 
		RULE_intersecting = 59, RULE_differencing = 60, RULE_feature_member = 61, 
		RULE_type_feature_member = 62, RULE_owned_feature_member = 63, RULE_classifier = 64, 
		RULE_classifier_declaration = 65, RULE_superclassing_part = 66, RULE_subclassification = 67, 
		RULE_owned_subclassification = 68, RULE_feature = 69, RULE_anonymous_feature = 70, 
		RULE_feature_prefix = 71, RULE_end_feature_prefix = 72, RULE_basic_feature_prefix = 73, 
		RULE_owned_cross_feature_member = 74, RULE_owned_cross_feature = 75, RULE_feature_direction = 76, 
		RULE_feature_declaration = 77, RULE_feature_identification = 78, RULE_feature_relationship_part = 79, 
		RULE_chaining_part = 80, RULE_inverting_part = 81, RULE_type_featuring_part = 82, 
		RULE_feature_specialization_part = 83, RULE_multiplicity_part = 84, RULE_multiplicity_modifier = 85, 
		RULE_feature_specialization = 86, RULE_typings = 87, RULE_typed_by = 88, 
		RULE_subsettings = 89, RULE_subsets = 90, RULE_references = 91, RULE_crosses = 92, 
		RULE_redefinitions = 93, RULE_redefines = 94, RULE_feature_typing = 95, 
		RULE_owned_feature_typing = 96, RULE_subsetting = 97, RULE_owned_subsetting = 98, 
		RULE_owned_reference_subsetting = 99, RULE_owned_cross_subsetting = 100, 
		RULE_redefinition = 101, RULE_owned_redefinition = 102, RULE_owned_feature_chain = 103, 
		RULE_feature_chain = 104, RULE_owned_feature_chaining = 105, RULE_feature_inverting = 106, 
		RULE_owned_feature_inverting = 107, RULE_type_featuring = 108, RULE_owned_type_featuring = 109, 
		RULE_data_type = 110, RULE_class = 111, RULE_structure = 112, RULE_association = 113, 
		RULE_association_structure = 114, RULE_connector = 115, RULE_connector_declaration = 116, 
		RULE_binary_connector_declaration = 117, RULE_nary_connector_declaration = 118, 
		RULE_connector_end_member = 119, RULE_connector_end = 120, RULE_owned_cross_multiplicity_member = 121, 
		RULE_owned_cross_multiplicity = 122, RULE_binding_connector = 123, RULE_binding_connector_declaration = 124, 
		RULE_succession = 125, RULE_succession_declaration = 126, RULE_behavior = 127, 
		RULE_step = 128, RULE_function = 129, RULE_function_body = 130, RULE_function_body_part = 131, 
		RULE_return_feature_member = 132, RULE_result_expression_member = 133, 
		RULE_expression = 134, RULE_predicate = 135, RULE_boolean_expression = 136, 
		RULE_invariant = 137, RULE_owned_expression_reference_member = 138, RULE_owned_expression_reference = 139, 
		RULE_owned_expression_member = 140, RULE_owned_expression = 141, RULE_function_operation_arguments = 142, 
		RULE_type_reference_member = 143, RULE_type_result_member = 144, RULE_type_reference = 145, 
		RULE_reference_typing = 146, RULE_sequence_expression = 147, RULE_sequence_expression_list = 148, 
		RULE_sequence_operator_expression = 149, RULE_sequence_expression_list_member = 150, 
		RULE_function_reference = 151, RULE_feature_chain_member = 152, RULE_owned_feature_chain_member = 153, 
		RULE_base_expression = 154, RULE_null_expression = 155, RULE_feature_reference_expression = 156, 
		RULE_feature_reference_member = 157, RULE_feature_reference = 158, RULE_metadata_access_expression = 159, 
		RULE_invocation_expression = 160, RULE_internal_invocation_expression = 161, 
		RULE_constructor_expression = 162, RULE_argument_list = 163, RULE_positional_argument_list = 164, 
		RULE_named_argument_list = 165, RULE_named_argument_member = 166, RULE_named_argument = 167, 
		RULE_parameter_redefinition = 168, RULE_body_expression = 169, RULE_expression_body_member = 170, 
		RULE_expression_body = 171, RULE_literal_expression = 172, RULE_literal_boolean = 173, 
		RULE_boolean_value = 174, RULE_literal_string = 175, RULE_literal_integer = 176, 
		RULE_literal_real = 177, RULE_real_value = 178, RULE_literal_infinity = 179, 
		RULE_interaction = 180, RULE_item_flow = 181, RULE_succession_item_flow = 182, 
		RULE_item_flow_declaration = 183, RULE_item_feature_member = 184, RULE_item_feature = 185, 
		RULE_item_feature_specialization_part = 186, RULE_item_flow_end_member = 187, 
		RULE_item_flow_end = 188, RULE_item_flow_feature_member = 189, RULE_item_flow_feature = 190, 
		RULE_item_flow_redefinition = 191, RULE_value_part = 192, RULE_feature_value = 193, 
		RULE_feature_assignment = 194, RULE_multiplicity = 195, RULE_multiplicity_subset = 196, 
		RULE_multiplicity_range = 197, RULE_owned_multiplicity = 198, RULE_owned_multiplicity_range = 199, 
		RULE_multiplicity_bounds = 200, RULE_multiplicity_expression_member = 201, 
		RULE_internal_multiplicity_expression_member = 202, RULE_metaclass = 203, 
		RULE_prefix_metadata_annotation = 204, RULE_prefix_metadata_member = 205, 
		RULE_prefix_metadata_feature = 206, RULE_metadata_feature = 207, RULE_metadata_feature_declaration = 208, 
		RULE_metadata_body = 209, RULE_metadata_body_element = 210, RULE_metadata_body_feature_member = 211, 
		RULE_metadata_body_feature = 212, RULE_package = 213, RULE_library_package = 214, 
		RULE_package_declaration = 215, RULE_package_body = 216, RULE_element_filter_member = 217, 
		RULE_meta_assignment = 218, RULE_typed_by_operator = 219, RULE_specializes_operator = 220, 
		RULE_subsets_operator = 221, RULE_references_operator = 222, RULE_redefines_operator = 223, 
		RULE_conjugates_operator = 224, RULE_crosses_operator = 225;
	private static String[] makeRuleNames() {
		return new String[] {
			"start", "startRule", "elements", "identification", "relationship_body", 
			"relationship_owned_elements", "relationship_owned_element", "owned_related_element", 
			"dependency", "annotation", "owned_annotation", "annotating_element", 
			"comment", "documentation", "textual_representation", "root_namespace", 
			"namespace", "namespace_declaration", "namespace_body", "namespace_body_elements", 
			"namespace_body_element", "member_prefix", "visibility_indicator", "namespace_member", 
			"non_feature_member", "namespace_feature_member", "alias_member", "qualified_name", 
			"namespace_import", "import_declaration", "membership_import", "filter_package", 
			"filter_package_member", "element", "non_feature_element", "feature_element", 
			"additional_options", "type", "type_prefix", "type_declaration", "specialization_part", 
			"conjugation_part", "type_relationship_part", "disjoining_part", "unioning_part", 
			"intersecting_part", "differencing_part", "type_body", "type_body_elements", 
			"type_body_element", "specialization", "owned_specialization", "specific_type", 
			"general_type", "conjunction", "owned_conjugation", "disjoining", "owned_disjoining", 
			"unioning", "intersecting", "differencing", "feature_member", "type_feature_member", 
			"owned_feature_member", "classifier", "classifier_declaration", "superclassing_part", 
			"subclassification", "owned_subclassification", "feature", "anonymous_feature", 
			"feature_prefix", "end_feature_prefix", "basic_feature_prefix", "owned_cross_feature_member", 
			"owned_cross_feature", "feature_direction", "feature_declaration", "feature_identification", 
			"feature_relationship_part", "chaining_part", "inverting_part", "type_featuring_part", 
			"feature_specialization_part", "multiplicity_part", "multiplicity_modifier", 
			"feature_specialization", "typings", "typed_by", "subsettings", "subsets", 
			"references", "crosses", "redefinitions", "redefines", "feature_typing", 
			"owned_feature_typing", "subsetting", "owned_subsetting", "owned_reference_subsetting", 
			"owned_cross_subsetting", "redefinition", "owned_redefinition", "owned_feature_chain", 
			"feature_chain", "owned_feature_chaining", "feature_inverting", "owned_feature_inverting", 
			"type_featuring", "owned_type_featuring", "data_type", "class", "structure", 
			"association", "association_structure", "connector", "connector_declaration", 
			"binary_connector_declaration", "nary_connector_declaration", "connector_end_member", 
			"connector_end", "owned_cross_multiplicity_member", "owned_cross_multiplicity", 
			"binding_connector", "binding_connector_declaration", "succession", "succession_declaration", 
			"behavior", "step", "function", "function_body", "function_body_part", 
			"return_feature_member", "result_expression_member", "expression", "predicate", 
			"boolean_expression", "invariant", "owned_expression_reference_member", 
			"owned_expression_reference", "owned_expression_member", "owned_expression", 
			"function_operation_arguments", "type_reference_member", "type_result_member", 
			"type_reference", "reference_typing", "sequence_expression", "sequence_expression_list", 
			"sequence_operator_expression", "sequence_expression_list_member", "function_reference", 
			"feature_chain_member", "owned_feature_chain_member", "base_expression", 
			"null_expression", "feature_reference_expression", "feature_reference_member", 
			"feature_reference", "metadata_access_expression", "invocation_expression", 
			"internal_invocation_expression", "constructor_expression", "argument_list", 
			"positional_argument_list", "named_argument_list", "named_argument_member", 
			"named_argument", "parameter_redefinition", "body_expression", "expression_body_member", 
			"expression_body", "literal_expression", "literal_boolean", "boolean_value", 
			"literal_string", "literal_integer", "literal_real", "real_value", "literal_infinity", 
			"interaction", "item_flow", "succession_item_flow", "item_flow_declaration", 
			"item_feature_member", "item_feature", "item_feature_specialization_part", 
			"item_flow_end_member", "item_flow_end", "item_flow_feature_member", 
			"item_flow_feature", "item_flow_redefinition", "value_part", "feature_value", 
			"feature_assignment", "multiplicity", "multiplicity_subset", "multiplicity_range", 
			"owned_multiplicity", "owned_multiplicity_range", "multiplicity_bounds", 
			"multiplicity_expression_member", "internal_multiplicity_expression_member", 
			"metaclass", "prefix_metadata_annotation", "prefix_metadata_member", 
			"prefix_metadata_feature", "metadata_feature", "metadata_feature_declaration", 
			"metadata_body", "metadata_body_element", "metadata_body_feature_member", 
			"metadata_body_feature", "package", "library_package", "package_declaration", 
			"package_body", "element_filter_member", "meta_assignment", "typed_by_operator", 
			"specializes_operator", "subsets_operator", "references_operator", "redefines_operator", 
			"conjugates_operator", "crosses_operator"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'about'", "'abstract'", "'alias'", "'all'", "'and'", "'as'", "'assoc'", 
			"'behavior'", "'binding'", "'bool'", "'by'", "'chains'", "'class'", "'classifier'", 
			"'comment'", "'composite'", "'conjugate'", "'conjugates'", "'conjugation'", 
			"'connector'", "'datatype'", "'default'", "'dependency'", "'derived'", 
			"'differences'", "'disjoining'", "'disjoint'", "'doc'", "'else'", "'end'", 
			"'expr'", "'false'", "'feature'", "'featured'", "'featuring'", "'filter'", 
			"'first'", "'flow'", "'for'", "'from'", "'function'", "'hastype'", "'if'", 
			"'intersects'", "'implies'", "'import'", "'in'", "'inout'", "'interaction'", 
			"'inv'", "'inverse'", "'inverting'", "'istype'", "'language'", "'member'", 
			"'metaclass'", "'metadata'", "'multiplicity'", "'namespace'", "'nonunique'", 
			"'not'", "'null'", "'of'", "'or'", "'ordered'", "'out'", "'package'", 
			"'portion'", "'predicate'", "'private'", "'protected'", "'public'", "'readonly'", 
			"'redefines'", "'redefinition'", "'references'", "'rep'", "'return'", 
			"'specialization'", "'specializes'", "'step'", "'struct'", "'subclassifier'", 
			"'subset'", "'subsets'", "'subtype'", "'succession'", "'then'", "'to'", 
			"'true'", "'type'", "'typed'", "'typing'", "'unions'", "'xor'", "'var'", 
			"'locale'", "'standard'", "'library'", "'const'", "'constant'", "'crosses'", 
			"'meta'", "'new'", null, null, null, "'/*'", "'//*'", "'*/'", "';'", 
			"'*'", "'::'", "':'", "':>'", "'::>'", "':>>'", "'~'", "'=>'", "'('", 
			"')'", "'{'", "'}'", "'['", "']'", "','", "'@'", "'#'", "'%'", "'&'", 
			"'^'", "'|'", "'**'", "'+'", "'-'", "'/'", "'->'", "'.'", "'..'", "'<'", 
			"'<='", "'='", "':='", "'=='", "'==='", "'!='", "'!=='", "'>'", "'>='", 
			"'?'", "'??'", "'.?'", "'@@'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "KEYWORD_ABOUT", "KEYWORD_ABSTRACT", "KEYWORD_ALIAS", "KEYWORD_ALL", 
			"KEYWORD_AND", "KEYWORD_AS", "KEYWORD_ASSOC", "KEYWORD_BEHAVIOR", "KEYWORD_BINDING", 
			"KEYWORD_BOOL", "KEYWORD_BY", "KEYWORD_CHAINS", "KEYWORD_CLASS", "KEYWORD_CLASSIFIER", 
			"KEYWORD_COMMENT", "KEYWORD_COMPOSITE", "KEYWORD_CONJUGATE", "KEYWORD_CONJUGATES", 
			"KEYWORD_CONJUGATION", "KEYWORD_CONNECTOR", "KEYWORD_DATATYPE", "KEYWORD_DEFAULT", 
			"KEYWORD_DEPENDENCY", "KEYWORD_DERIVED", "KEYWORD_DIFFERENCES", "KEYWORD_DISJOINING", 
			"KEYWORD_DISJOINT", "KEYWORD_DOC", "KEYWORD_ELSE", "KEYWORD_END", "KEYWORD_EXPR", 
			"KEYWORD_FALSE", "KEYWORD_FEATURE", "KEYWORD_FEATURED", "KEYWORD_FEATURING", 
			"KEYWORD_FILTER", "KEYWORD_FIRST", "KEYWORD_FLOW", "KEYWORD_FOR", "KEYWORD_FROM", 
			"KEYWORD_FUNCTION", "KEYWORD_HASTYPE", "KEYWORD_IF", "KEYWORD_INTERSECTS", 
			"KEYWORD_IMPLIES", "KEYWORD_IMPORT", "KEYWORD_IN", "KEYWORD_INOUT", "KEYWORD_INTERACTION", 
			"KEYWORD_INV", "KEYWORD_INVERSE", "KEYWORD_INVERTING", "KEYWORD_ISTYPE", 
			"KEYWORD_LANGUAGE", "KEYWORD_MEMBER", "KEYWORD_METACLASS", "KEYWORD_METADATA", 
			"KEYWORD_MULTIPLICITY", "KEYWORD_NAMESPACE", "KEYWORD_NONUNIQUE", "KEYWORD_NOT", 
			"KEYWORD_NULL", "KEYWORD_OF", "KEYWORD_OR", "KEYWORD_ORDERED", "KEYWORD_OUT", 
			"KEYWORD_PACKAGE", "KEYWORD_PORTION", "KEYWORD_PREDICATE", "KEYWORD_PRIVATE", 
			"KEYWORD_PROTECTED", "KEYWORD_PUBLIC", "KEYWORD_READONLY", "KEYWORD_REDEFINES", 
			"KEYWORD_REDEFINITION", "KEYWORD_REFERENCES", "KEYWORD_REP", "KEYWORD_RETURN", 
			"KEYWORD_SPECIALIZATION", "KEYWORD_SPECIALIZES", "KEYWORD_STEP", "KEYWORD_STRUCT", 
			"KEYWORD_SUBCLASSIFIER", "KEYWORD_SUBSET", "KEYWORD_SUBSETS", "KEYWORD_SUBTYPE", 
			"KEYWORD_SUCCESSION", "KEYWORD_THEN", "KEYWORD_TO", "KEYWORD_TRUE", "KEYWORD_TYPE", 
			"KEYWORD_TYPED", "KEYWORD_TYPING", "KEYWORD_UNIONS", "KEYWORD_XOR", "KEYWORD_VAR", 
			"KEYWORD_LOCALE", "KEYWORD_STANDARD", "KEYWORD_LIBRARY", "KEYWORD_CONST", 
			"KEYWORD_CONSTANT", "KEYWORD_CROSSES", "KEYWORD_META", "KEYWORD_NEW", 
			"SINGLE_LINE_NOTE", "MULTI_LINE_NOTE", "REGULAR_COMMENT", "SYMBOL_COMMENT_BLOCK_START", 
			"SYMBOL_NOTE_BLOCK_START", "SYMBOL_COMMENT_BLOCK_END", "SYMBOL_STATEMENT_DELIMITER", 
			"SYMBOL_STAR", "SYMBOL_NAMESPACE_SUBSET", "SYMBOL_TYPED_BY", "SYMBOL_SPECIALIZES", 
			"SYMBOL_REFERENCES", "SYMBOL_REDEFINES", "SYMBOL_CONJUGATES", "SYMBOL_CROSSES", 
			"SYMBOL_ROUND_BRACKET_OPEN", "SYMBOL_ROUND_BRACKET_CLOSE", "SYMBOL_CURLY_BRACKET_OPEN", 
			"SYMBOL_CURLY_BRACKET_CLOSE", "SYMBOL_SQUARE_BRACKET_OPEN", "SYMBOL_SQUARE_BRACKET_CLOSE", 
			"SYMBOL_COMMA", "SYMBOL_AT", "SYMBOL_HASHTAG", "SYMBOL_MOD", "SYMBOL_AND", 
			"SYMBOL_UPPER", "SYMBOL_VERTICAL_LINE", "SYMBOL_DOUBLE_STAR", "SYMBOL_PLUS", 
			"SYMBOL_MINUS", "SYMBOL_SLASH", "SYMBOL_ARROW", "SYMBOL_DOT", "SYMBOL_DDOT", 
			"SYMBOL_SMALLER", "SYMBOL_SMALLER_EQUAL", "SYMBOL_ASSIGN", "SYMBOL_DEF_ASSIGN", 
			"SYMBOL_EQUALS", "SYMBOL_IFF_EQUALS", "SYMBOL_NOT_EQUALS", "SYMBOL_IFF_NOT_EQUALS", 
			"SYMBOL_GREATER", "SYMBOL_GREATER_EQUALS", "SYMBOL_QUESTION", "SYMBOL_DQUESTION", 
			"SYMBOL_DOT_QUESTION", "SYMBOL_ATAT", "NAME", "BASIC_NAME", "UNRESTRICTED_NAME", 
			"DECIMAL_VALUE", "EXPONENTIAL_VALUE", "STRING_VALUE", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "KerML.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public KerMLParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StartContext extends ParserRuleContext {
		public ElementsContext elements() {
			return getRuleContext(ElementsContext.class,0);
		}
		public TerminalNode EOF() { return getToken(KerMLParser.EOF, 0); }
		public StartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_start; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterStart(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitStart(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitStart(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StartContext start() throws RecognitionException {
		StartContext _localctx = new StartContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_start);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(452);
			elements();
			setState(453);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StartRuleContext extends ParserRuleContext {
		public StartContext start() {
			return getRuleContext(StartContext.class,0);
		}
		public StartRuleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_startRule; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterStartRule(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitStartRule(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitStartRule(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StartRuleContext startRule() throws RecognitionException {
		StartRuleContext _localctx = new StartRuleContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_startRule);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(455);
			start();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ElementsContext extends ParserRuleContext {
		public List<Member_prefixContext> member_prefix() {
			return getRuleContexts(Member_prefixContext.class);
		}
		public Member_prefixContext member_prefix(int i) {
			return getRuleContext(Member_prefixContext.class,i);
		}
		public List<ElementContext> element() {
			return getRuleContexts(ElementContext.class);
		}
		public ElementContext element(int i) {
			return getRuleContext(ElementContext.class,i);
		}
		public ElementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elements; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterElements(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitElements(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitElements(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ElementsContext elements() throws RecognitionException {
		ElementsContext _localctx = new ElementsContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_elements);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(462);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2260739164766988180L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & -3999754816522854401L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
				{
				{
				setState(457);
				member_prefix();
				setState(458);
				element();
				}
				}
				setState(464);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IdentificationContext extends ParserRuleContext {
		public List<TerminalNode> NAME() { return getTokens(KerMLParser.NAME); }
		public TerminalNode NAME(int i) {
			return getToken(KerMLParser.NAME, i);
		}
		public TerminalNode SYMBOL_SMALLER() { return getToken(KerMLParser.SYMBOL_SMALLER, 0); }
		public TerminalNode SYMBOL_GREATER() { return getToken(KerMLParser.SYMBOL_GREATER, 0); }
		public IdentificationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_identification; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterIdentification(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitIdentification(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitIdentification(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IdentificationContext identification() throws RecognitionException {
		IdentificationContext _localctx = new IdentificationContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_identification);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(468);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_SMALLER) {
				{
				setState(465);
				match(SYMBOL_SMALLER);
				setState(466);
				match(NAME);
				setState(467);
				match(SYMBOL_GREATER);
				}
			}

			setState(470);
			match(NAME);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Relationship_bodyContext extends ParserRuleContext {
		public TerminalNode SYMBOL_STATEMENT_DELIMITER() { return getToken(KerMLParser.SYMBOL_STATEMENT_DELIMITER, 0); }
		public TerminalNode SYMBOL_CURLY_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_OPEN, 0); }
		public Relationship_owned_elementsContext relationship_owned_elements() {
			return getRuleContext(Relationship_owned_elementsContext.class,0);
		}
		public TerminalNode SYMBOL_CURLY_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_CLOSE, 0); }
		public Relationship_bodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_relationship_body; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterRelationship_body(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitRelationship_body(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitRelationship_body(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Relationship_bodyContext relationship_body() throws RecognitionException {
		Relationship_bodyContext _localctx = new Relationship_bodyContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_relationship_body);
		try {
			setState(477);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_STATEMENT_DELIMITER:
				enterOuterAlt(_localctx, 1);
				{
				setState(472);
				match(SYMBOL_STATEMENT_DELIMITER);
				}
				break;
			case SYMBOL_CURLY_BRACKET_OPEN:
				enterOuterAlt(_localctx, 2);
				{
				{
				setState(473);
				match(SYMBOL_CURLY_BRACKET_OPEN);
				setState(474);
				relationship_owned_elements();
				setState(475);
				match(SYMBOL_CURLY_BRACKET_CLOSE);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Relationship_owned_elementsContext extends ParserRuleContext {
		public List<Relationship_owned_elementContext> relationship_owned_element() {
			return getRuleContexts(Relationship_owned_elementContext.class);
		}
		public Relationship_owned_elementContext relationship_owned_element(int i) {
			return getRuleContext(Relationship_owned_elementContext.class,i);
		}
		public Relationship_owned_elementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_relationship_owned_elements; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterRelationship_owned_elements(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitRelationship_owned_elements(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitRelationship_owned_elements(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Relationship_owned_elementsContext relationship_owned_elements() throws RecognitionException {
		Relationship_owned_elementsContext _localctx = new Relationship_owned_elementsContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_relationship_owned_elements);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(482);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2260739164766988180L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & -3999754816522854401L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
				{
				{
				setState(479);
				relationship_owned_element();
				}
				}
				setState(484);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Relationship_owned_elementContext extends ParserRuleContext {
		public Owned_related_elementContext owned_related_element() {
			return getRuleContext(Owned_related_elementContext.class,0);
		}
		public Owned_annotationContext owned_annotation() {
			return getRuleContext(Owned_annotationContext.class,0);
		}
		public Relationship_owned_elementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_relationship_owned_element; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterRelationship_owned_element(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitRelationship_owned_element(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitRelationship_owned_element(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Relationship_owned_elementContext relationship_owned_element() throws RecognitionException {
		Relationship_owned_elementContext _localctx = new Relationship_owned_elementContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_relationship_owned_element);
		try {
			setState(487);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(485);
				owned_related_element();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(486);
				owned_annotation();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_related_elementContext extends ParserRuleContext {
		public Non_feature_elementContext non_feature_element() {
			return getRuleContext(Non_feature_elementContext.class,0);
		}
		public Feature_elementContext feature_element() {
			return getRuleContext(Feature_elementContext.class,0);
		}
		public Owned_related_elementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_related_element; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_related_element(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_related_element(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_related_element(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_related_elementContext owned_related_element() throws RecognitionException {
		Owned_related_elementContext _localctx = new Owned_related_elementContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_owned_related_element);
		try {
			setState(491);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(489);
				non_feature_element();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(490);
				feature_element();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DependencyContext extends ParserRuleContext {
		public TerminalNode KEYWORD_DEPENDENCY() { return getToken(KerMLParser.KEYWORD_DEPENDENCY, 0); }
		public List<Qualified_nameContext> qualified_name() {
			return getRuleContexts(Qualified_nameContext.class);
		}
		public Qualified_nameContext qualified_name(int i) {
			return getRuleContext(Qualified_nameContext.class,i);
		}
		public TerminalNode KEYWORD_TO() { return getToken(KerMLParser.KEYWORD_TO, 0); }
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public List<Prefix_metadata_annotationContext> prefix_metadata_annotation() {
			return getRuleContexts(Prefix_metadata_annotationContext.class);
		}
		public Prefix_metadata_annotationContext prefix_metadata_annotation(int i) {
			return getRuleContext(Prefix_metadata_annotationContext.class,i);
		}
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public TerminalNode KEYWORD_FROM() { return getToken(KerMLParser.KEYWORD_FROM, 0); }
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public DependencyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_dependency; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterDependency(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitDependency(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitDependency(this);
			else return visitor.visitChildren(this);
		}
	}

	public final DependencyContext dependency() throws RecognitionException {
		DependencyContext _localctx = new DependencyContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_dependency);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(496);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_HASHTAG) {
				{
				{
				setState(493);
				prefix_metadata_annotation();
				}
				}
				setState(498);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(499);
			match(KEYWORD_DEPENDENCY);
			setState(501);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				{
				setState(500);
				identification();
				}
				break;
			}
			setState(504);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_FROM) {
				{
				setState(503);
				match(KEYWORD_FROM);
				}
			}

			setState(506);
			qualified_name();
			setState(511);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(507);
				match(SYMBOL_COMMA);
				setState(508);
				qualified_name();
				}
				}
				setState(513);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(514);
			match(KEYWORD_TO);
			setState(515);
			qualified_name();
			setState(520);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(516);
				match(SYMBOL_COMMA);
				setState(517);
				qualified_name();
				}
				}
				setState(522);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(523);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AnnotationContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public AnnotationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterAnnotation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitAnnotation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitAnnotation(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AnnotationContext annotation() throws RecognitionException {
		AnnotationContext _localctx = new AnnotationContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_annotation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(525);
			qualified_name();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_annotationContext extends ParserRuleContext {
		public Annotating_elementContext annotating_element() {
			return getRuleContext(Annotating_elementContext.class,0);
		}
		public Owned_annotationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_annotation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_annotation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_annotation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_annotation(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_annotationContext owned_annotation() throws RecognitionException {
		Owned_annotationContext _localctx = new Owned_annotationContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_owned_annotation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(527);
			annotating_element();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Annotating_elementContext extends ParserRuleContext {
		public CommentContext comment() {
			return getRuleContext(CommentContext.class,0);
		}
		public DocumentationContext documentation() {
			return getRuleContext(DocumentationContext.class,0);
		}
		public Textual_representationContext textual_representation() {
			return getRuleContext(Textual_representationContext.class,0);
		}
		public Metadata_featureContext metadata_feature() {
			return getRuleContext(Metadata_featureContext.class,0);
		}
		public Annotating_elementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotating_element; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterAnnotating_element(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitAnnotating_element(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitAnnotating_element(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Annotating_elementContext annotating_element() throws RecognitionException {
		Annotating_elementContext _localctx = new Annotating_elementContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_annotating_element);
		try {
			setState(533);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case KEYWORD_COMMENT:
			case KEYWORD_LOCALE:
			case REGULAR_COMMENT:
				enterOuterAlt(_localctx, 1);
				{
				setState(529);
				comment();
				}
				break;
			case KEYWORD_DOC:
				enterOuterAlt(_localctx, 2);
				{
				setState(530);
				documentation();
				}
				break;
			case KEYWORD_LANGUAGE:
			case KEYWORD_REP:
				enterOuterAlt(_localctx, 3);
				{
				setState(531);
				textual_representation();
				}
				break;
			case KEYWORD_METADATA:
			case SYMBOL_AT:
			case SYMBOL_HASHTAG:
				enterOuterAlt(_localctx, 4);
				{
				setState(532);
				metadata_feature();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CommentContext extends ParserRuleContext {
		public TerminalNode REGULAR_COMMENT() { return getToken(KerMLParser.REGULAR_COMMENT, 0); }
		public TerminalNode KEYWORD_COMMENT() { return getToken(KerMLParser.KEYWORD_COMMENT, 0); }
		public TerminalNode KEYWORD_LOCALE() { return getToken(KerMLParser.KEYWORD_LOCALE, 0); }
		public TerminalNode STRING_VALUE() { return getToken(KerMLParser.STRING_VALUE, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public TerminalNode KEYWORD_ABOUT() { return getToken(KerMLParser.KEYWORD_ABOUT, 0); }
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public CommentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_comment; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterComment(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitComment(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitComment(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CommentContext comment() throws RecognitionException {
		CommentContext _localctx = new CommentContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_comment);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(550);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_COMMENT) {
				{
				setState(535);
				match(KEYWORD_COMMENT);
				setState(537);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SYMBOL_SMALLER || _la==NAME) {
					{
					setState(536);
					identification();
					}
				}

				setState(548);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_ABOUT) {
					{
					setState(539);
					match(KEYWORD_ABOUT);
					setState(540);
					annotation();
					setState(545);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==SYMBOL_COMMA) {
						{
						{
						setState(541);
						match(SYMBOL_COMMA);
						setState(542);
						annotation();
						}
						}
						setState(547);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				}
			}

			setState(554);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_LOCALE) {
				{
				setState(552);
				match(KEYWORD_LOCALE);
				setState(553);
				match(STRING_VALUE);
				}
			}

			setState(556);
			match(REGULAR_COMMENT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DocumentationContext extends ParserRuleContext {
		public TerminalNode KEYWORD_DOC() { return getToken(KerMLParser.KEYWORD_DOC, 0); }
		public TerminalNode REGULAR_COMMENT() { return getToken(KerMLParser.REGULAR_COMMENT, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public TerminalNode KEYWORD_LOCALE() { return getToken(KerMLParser.KEYWORD_LOCALE, 0); }
		public TerminalNode STRING_VALUE() { return getToken(KerMLParser.STRING_VALUE, 0); }
		public DocumentationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_documentation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterDocumentation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitDocumentation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitDocumentation(this);
			else return visitor.visitChildren(this);
		}
	}

	public final DocumentationContext documentation() throws RecognitionException {
		DocumentationContext _localctx = new DocumentationContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_documentation);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(558);
			match(KEYWORD_DOC);
			setState(560);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_SMALLER || _la==NAME) {
				{
				setState(559);
				identification();
				}
			}

			setState(564);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_LOCALE) {
				{
				setState(562);
				match(KEYWORD_LOCALE);
				setState(563);
				match(STRING_VALUE);
				}
			}

			setState(566);
			match(REGULAR_COMMENT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Textual_representationContext extends ParserRuleContext {
		public TerminalNode KEYWORD_LANGUAGE() { return getToken(KerMLParser.KEYWORD_LANGUAGE, 0); }
		public TerminalNode STRING_VALUE() { return getToken(KerMLParser.STRING_VALUE, 0); }
		public TerminalNode REGULAR_COMMENT() { return getToken(KerMLParser.REGULAR_COMMENT, 0); }
		public TerminalNode KEYWORD_REP() { return getToken(KerMLParser.KEYWORD_REP, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public Textual_representationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_textual_representation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterTextual_representation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitTextual_representation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitTextual_representation(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Textual_representationContext textual_representation() throws RecognitionException {
		Textual_representationContext _localctx = new Textual_representationContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_textual_representation);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(570);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_REP) {
				{
				setState(568);
				match(KEYWORD_REP);
				setState(569);
				identification();
				}
			}

			setState(572);
			match(KEYWORD_LANGUAGE);
			setState(573);
			match(STRING_VALUE);
			setState(574);
			match(REGULAR_COMMENT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Root_namespaceContext extends ParserRuleContext {
		public Namespace_body_elementsContext namespace_body_elements() {
			return getRuleContext(Namespace_body_elementsContext.class,0);
		}
		public Root_namespaceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_root_namespace; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterRoot_namespace(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitRoot_namespace(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitRoot_namespace(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Root_namespaceContext root_namespace() throws RecognitionException {
		Root_namespaceContext _localctx = new Root_namespaceContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_root_namespace);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(576);
			namespace_body_elements();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class NamespaceContext extends ParserRuleContext {
		public Namespace_declarationContext namespace_declaration() {
			return getRuleContext(Namespace_declarationContext.class,0);
		}
		public Namespace_bodyContext namespace_body() {
			return getRuleContext(Namespace_bodyContext.class,0);
		}
		public List<Prefix_metadata_memberContext> prefix_metadata_member() {
			return getRuleContexts(Prefix_metadata_memberContext.class);
		}
		public Prefix_metadata_memberContext prefix_metadata_member(int i) {
			return getRuleContext(Prefix_metadata_memberContext.class,i);
		}
		public NamespaceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamespace(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamespace(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamespace(this);
			else return visitor.visitChildren(this);
		}
	}

	public final NamespaceContext namespace() throws RecognitionException {
		NamespaceContext _localctx = new NamespaceContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_namespace);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(581);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_HASHTAG) {
				{
				{
				setState(578);
				prefix_metadata_member();
				}
				}
				setState(583);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(584);
			namespace_declaration();
			setState(585);
			namespace_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Namespace_declarationContext extends ParserRuleContext {
		public TerminalNode KEYWORD_NAMESPACE() { return getToken(KerMLParser.KEYWORD_NAMESPACE, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public Namespace_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamespace_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamespace_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamespace_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_declarationContext namespace_declaration() throws RecognitionException {
		Namespace_declarationContext _localctx = new Namespace_declarationContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_namespace_declaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(587);
			match(KEYWORD_NAMESPACE);
			setState(588);
			identification();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Namespace_bodyContext extends ParserRuleContext {
		public TerminalNode SYMBOL_STATEMENT_DELIMITER() { return getToken(KerMLParser.SYMBOL_STATEMENT_DELIMITER, 0); }
		public TerminalNode SYMBOL_CURLY_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_OPEN, 0); }
		public Namespace_body_elementContext namespace_body_element() {
			return getRuleContext(Namespace_body_elementContext.class,0);
		}
		public TerminalNode SYMBOL_CURLY_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_CLOSE, 0); }
		public Namespace_bodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_body; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamespace_body(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamespace_body(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamespace_body(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_bodyContext namespace_body() throws RecognitionException {
		Namespace_bodyContext _localctx = new Namespace_bodyContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_namespace_body);
		try {
			setState(595);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_STATEMENT_DELIMITER:
				enterOuterAlt(_localctx, 1);
				{
				setState(590);
				match(SYMBOL_STATEMENT_DELIMITER);
				}
				break;
			case SYMBOL_CURLY_BRACKET_OPEN:
				enterOuterAlt(_localctx, 2);
				{
				{
				setState(591);
				match(SYMBOL_CURLY_BRACKET_OPEN);
				setState(592);
				namespace_body_element();
				setState(593);
				match(SYMBOL_CURLY_BRACKET_CLOSE);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Namespace_body_elementsContext extends ParserRuleContext {
		public ElementsContext elements() {
			return getRuleContext(ElementsContext.class,0);
		}
		public Namespace_body_elementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_body_elements; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamespace_body_elements(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamespace_body_elements(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamespace_body_elements(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_body_elementsContext namespace_body_elements() throws RecognitionException {
		Namespace_body_elementsContext _localctx = new Namespace_body_elementsContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_namespace_body_elements);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(597);
			elements();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Namespace_body_elementContext extends ParserRuleContext {
		public Namespace_memberContext namespace_member() {
			return getRuleContext(Namespace_memberContext.class,0);
		}
		public Alias_memberContext alias_member() {
			return getRuleContext(Alias_memberContext.class,0);
		}
		public Namespace_importContext namespace_import() {
			return getRuleContext(Namespace_importContext.class,0);
		}
		public Namespace_body_elementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_body_element; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamespace_body_element(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamespace_body_element(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamespace_body_element(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_body_elementContext namespace_body_element() throws RecognitionException {
		Namespace_body_elementContext _localctx = new Namespace_body_elementContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_namespace_body_element);
		try {
			setState(602);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,22,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(599);
				namespace_member();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(600);
				alias_member();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(601);
				namespace_import();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Member_prefixContext extends ParserRuleContext {
		public Visibility_indicatorContext visibility_indicator() {
			return getRuleContext(Visibility_indicatorContext.class,0);
		}
		public Member_prefixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_member_prefix; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMember_prefix(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMember_prefix(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMember_prefix(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Member_prefixContext member_prefix() throws RecognitionException {
		Member_prefixContext _localctx = new Member_prefixContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_member_prefix);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(605);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,23,_ctx) ) {
			case 1:
				{
				setState(604);
				visibility_indicator();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Visibility_indicatorContext extends ParserRuleContext {
		public TerminalNode KEYWORD_PUBLIC() { return getToken(KerMLParser.KEYWORD_PUBLIC, 0); }
		public TerminalNode KEYWORD_PRIVATE() { return getToken(KerMLParser.KEYWORD_PRIVATE, 0); }
		public TerminalNode KEYWORD_PROTECTED() { return getToken(KerMLParser.KEYWORD_PROTECTED, 0); }
		public Visibility_indicatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_visibility_indicator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterVisibility_indicator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitVisibility_indicator(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitVisibility_indicator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Visibility_indicatorContext visibility_indicator() throws RecognitionException {
		Visibility_indicatorContext _localctx = new Visibility_indicatorContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_visibility_indicator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(607);
			_la = _input.LA(1);
			if ( !(((((_la - 70)) & ~0x3f) == 0 && ((1L << (_la - 70)) & 7L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Namespace_memberContext extends ParserRuleContext {
		public Non_feature_memberContext non_feature_member() {
			return getRuleContext(Non_feature_memberContext.class,0);
		}
		public Namespace_feature_memberContext namespace_feature_member() {
			return getRuleContext(Namespace_feature_memberContext.class,0);
		}
		public Namespace_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamespace_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamespace_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamespace_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_memberContext namespace_member() throws RecognitionException {
		Namespace_memberContext _localctx = new Namespace_memberContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_namespace_member);
		try {
			setState(611);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,24,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(609);
				non_feature_member();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(610);
				namespace_feature_member();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Non_feature_memberContext extends ParserRuleContext {
		public Member_prefixContext member_prefix() {
			return getRuleContext(Member_prefixContext.class,0);
		}
		public Non_feature_elementContext non_feature_element() {
			return getRuleContext(Non_feature_elementContext.class,0);
		}
		public Non_feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_non_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNon_feature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNon_feature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNon_feature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Non_feature_memberContext non_feature_member() throws RecognitionException {
		Non_feature_memberContext _localctx = new Non_feature_memberContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_non_feature_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(613);
			member_prefix();
			setState(614);
			non_feature_element();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Namespace_feature_memberContext extends ParserRuleContext {
		public Member_prefixContext member_prefix() {
			return getRuleContext(Member_prefixContext.class,0);
		}
		public Feature_elementContext feature_element() {
			return getRuleContext(Feature_elementContext.class,0);
		}
		public Namespace_feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamespace_feature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamespace_feature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamespace_feature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_feature_memberContext namespace_feature_member() throws RecognitionException {
		Namespace_feature_memberContext _localctx = new Namespace_feature_memberContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_namespace_feature_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(616);
			member_prefix();
			setState(617);
			feature_element();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Alias_memberContext extends ParserRuleContext {
		public Member_prefixContext member_prefix() {
			return getRuleContext(Member_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_ALIAS() { return getToken(KerMLParser.KEYWORD_ALIAS, 0); }
		public TerminalNode KEYWORD_FOR() { return getToken(KerMLParser.KEYWORD_FOR, 0); }
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public TerminalNode SYMBOL_SMALLER() { return getToken(KerMLParser.SYMBOL_SMALLER, 0); }
		public List<TerminalNode> NAME() { return getTokens(KerMLParser.NAME); }
		public TerminalNode NAME(int i) {
			return getToken(KerMLParser.NAME, i);
		}
		public TerminalNode SYMBOL_GREATER() { return getToken(KerMLParser.SYMBOL_GREATER, 0); }
		public Alias_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_alias_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterAlias_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitAlias_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitAlias_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Alias_memberContext alias_member() throws RecognitionException {
		Alias_memberContext _localctx = new Alias_memberContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_alias_member);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(619);
			member_prefix();
			setState(620);
			match(KEYWORD_ALIAS);
			setState(624);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_SMALLER) {
				{
				setState(621);
				match(SYMBOL_SMALLER);
				setState(622);
				match(NAME);
				setState(623);
				match(SYMBOL_GREATER);
				}
			}

			setState(627);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==NAME) {
				{
				setState(626);
				match(NAME);
				}
			}

			setState(629);
			match(KEYWORD_FOR);
			setState(630);
			qualified_name();
			setState(631);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Qualified_nameContext extends ParserRuleContext {
		public List<TerminalNode> NAME() { return getTokens(KerMLParser.NAME); }
		public TerminalNode NAME(int i) {
			return getToken(KerMLParser.NAME, i);
		}
		public List<TerminalNode> SYMBOL_NAMESPACE_SUBSET() { return getTokens(KerMLParser.SYMBOL_NAMESPACE_SUBSET); }
		public TerminalNode SYMBOL_NAMESPACE_SUBSET(int i) {
			return getToken(KerMLParser.SYMBOL_NAMESPACE_SUBSET, i);
		}
		public Qualified_nameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_qualified_name; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterQualified_name(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitQualified_name(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitQualified_name(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Qualified_nameContext qualified_name() throws RecognitionException {
		Qualified_nameContext _localctx = new Qualified_nameContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_qualified_name);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(633);
			match(NAME);
			setState(638);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,27,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(634);
					match(SYMBOL_NAMESPACE_SUBSET);
					setState(635);
					match(NAME);
					}
					} 
				}
				setState(640);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,27,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Namespace_importContext extends ParserRuleContext {
		public TerminalNode KEYWORD_IMPORT() { return getToken(KerMLParser.KEYWORD_IMPORT, 0); }
		public Import_declarationContext import_declaration() {
			return getRuleContext(Import_declarationContext.class,0);
		}
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public Visibility_indicatorContext visibility_indicator() {
			return getRuleContext(Visibility_indicatorContext.class,0);
		}
		public TerminalNode KEYWORD_ALL() { return getToken(KerMLParser.KEYWORD_ALL, 0); }
		public Namespace_importContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_import; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamespace_import(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamespace_import(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamespace_import(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Namespace_importContext namespace_import() throws RecognitionException {
		Namespace_importContext _localctx = new Namespace_importContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_namespace_import);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(642);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 70)) & ~0x3f) == 0 && ((1L << (_la - 70)) & 7L) != 0)) {
				{
				setState(641);
				visibility_indicator();
				}
			}

			setState(644);
			match(KEYWORD_IMPORT);
			setState(646);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_ALL) {
				{
				setState(645);
				match(KEYWORD_ALL);
				}
			}

			setState(648);
			import_declaration();
			setState(649);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Import_declarationContext extends ParserRuleContext {
		public Membership_importContext membership_import() {
			return getRuleContext(Membership_importContext.class,0);
		}
		public Filter_packageContext filter_package() {
			return getRuleContext(Filter_packageContext.class,0);
		}
		public Import_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_import_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterImport_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitImport_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitImport_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Import_declarationContext import_declaration() throws RecognitionException {
		Import_declarationContext _localctx = new Import_declarationContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_import_declaration);
		try {
			setState(653);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,30,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(651);
				membership_import();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(652);
				filter_package();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Membership_importContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public TerminalNode SYMBOL_NAMESPACE_SUBSET() { return getToken(KerMLParser.SYMBOL_NAMESPACE_SUBSET, 0); }
		public TerminalNode SYMBOL_DOUBLE_STAR() { return getToken(KerMLParser.SYMBOL_DOUBLE_STAR, 0); }
		public TerminalNode SYMBOL_STAR() { return getToken(KerMLParser.SYMBOL_STAR, 0); }
		public Membership_importContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_membership_import; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMembership_import(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMembership_import(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMembership_import(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Membership_importContext membership_import() throws RecognitionException {
		Membership_importContext _localctx = new Membership_importContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_membership_import);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(655);
			qualified_name();
			{
			setState(657);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_NAMESPACE_SUBSET) {
				{
				setState(656);
				match(SYMBOL_NAMESPACE_SUBSET);
				}
			}

			setState(660);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_STAR || _la==SYMBOL_DOUBLE_STAR) {
				{
				setState(659);
				_la = _input.LA(1);
				if ( !(_la==SYMBOL_STAR || _la==SYMBOL_DOUBLE_STAR) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
			}

			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Filter_packageContext extends ParserRuleContext {
		public Membership_importContext membership_import() {
			return getRuleContext(Membership_importContext.class,0);
		}
		public Filter_package_memberContext filter_package_member() {
			return getRuleContext(Filter_package_memberContext.class,0);
		}
		public Filter_packageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_filter_package; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFilter_package(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFilter_package(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFilter_package(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Filter_packageContext filter_package() throws RecognitionException {
		Filter_packageContext _localctx = new Filter_packageContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_filter_package);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(662);
			membership_import();
			setState(663);
			filter_package_member();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Filter_package_memberContext extends ParserRuleContext {
		public TerminalNode SYMBOL_SQUARE_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_SQUARE_BRACKET_OPEN, 0); }
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_SQUARE_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_SQUARE_BRACKET_CLOSE, 0); }
		public Filter_package_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_filter_package_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFilter_package_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFilter_package_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFilter_package_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Filter_package_memberContext filter_package_member() throws RecognitionException {
		Filter_package_memberContext _localctx = new Filter_package_memberContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_filter_package_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(665);
			match(SYMBOL_SQUARE_BRACKET_OPEN);
			setState(666);
			owned_expression(0);
			setState(667);
			match(SYMBOL_SQUARE_BRACKET_CLOSE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ElementContext extends ParserRuleContext {
		public Additional_optionsContext additional_options() {
			return getRuleContext(Additional_optionsContext.class,0);
		}
		public Annotating_elementContext annotating_element() {
			return getRuleContext(Annotating_elementContext.class,0);
		}
		public Non_feature_elementContext non_feature_element() {
			return getRuleContext(Non_feature_elementContext.class,0);
		}
		public Feature_elementContext feature_element() {
			return getRuleContext(Feature_elementContext.class,0);
		}
		public ElementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_element; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterElement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitElement(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitElement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ElementContext element() throws RecognitionException {
		ElementContext _localctx = new ElementContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_element);
		try {
			setState(673);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,33,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(669);
				additional_options();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(670);
				annotating_element();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(671);
				non_feature_element();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(672);
				feature_element();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Non_feature_elementContext extends ParserRuleContext {
		public DependencyContext dependency() {
			return getRuleContext(DependencyContext.class,0);
		}
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ClassifierContext classifier() {
			return getRuleContext(ClassifierContext.class,0);
		}
		public Data_typeContext data_type() {
			return getRuleContext(Data_typeContext.class,0);
		}
		public NamespaceContext namespace() {
			return getRuleContext(NamespaceContext.class,0);
		}
		public ClassContext class_() {
			return getRuleContext(ClassContext.class,0);
		}
		public StructureContext structure() {
			return getRuleContext(StructureContext.class,0);
		}
		public MetaclassContext metaclass() {
			return getRuleContext(MetaclassContext.class,0);
		}
		public AssociationContext association() {
			return getRuleContext(AssociationContext.class,0);
		}
		public Association_structureContext association_structure() {
			return getRuleContext(Association_structureContext.class,0);
		}
		public InteractionContext interaction() {
			return getRuleContext(InteractionContext.class,0);
		}
		public BehaviorContext behavior() {
			return getRuleContext(BehaviorContext.class,0);
		}
		public FunctionContext function() {
			return getRuleContext(FunctionContext.class,0);
		}
		public PredicateContext predicate() {
			return getRuleContext(PredicateContext.class,0);
		}
		public MultiplicityContext multiplicity() {
			return getRuleContext(MultiplicityContext.class,0);
		}
		public PackageContext package_() {
			return getRuleContext(PackageContext.class,0);
		}
		public Library_packageContext library_package() {
			return getRuleContext(Library_packageContext.class,0);
		}
		public SpecializationContext specialization() {
			return getRuleContext(SpecializationContext.class,0);
		}
		public ConjunctionContext conjunction() {
			return getRuleContext(ConjunctionContext.class,0);
		}
		public SubclassificationContext subclassification() {
			return getRuleContext(SubclassificationContext.class,0);
		}
		public DisjoiningContext disjoining() {
			return getRuleContext(DisjoiningContext.class,0);
		}
		public Feature_invertingContext feature_inverting() {
			return getRuleContext(Feature_invertingContext.class,0);
		}
		public Feature_typingContext feature_typing() {
			return getRuleContext(Feature_typingContext.class,0);
		}
		public SubsettingContext subsetting() {
			return getRuleContext(SubsettingContext.class,0);
		}
		public RedefinitionContext redefinition() {
			return getRuleContext(RedefinitionContext.class,0);
		}
		public Type_featuringContext type_featuring() {
			return getRuleContext(Type_featuringContext.class,0);
		}
		public Namespace_importContext namespace_import() {
			return getRuleContext(Namespace_importContext.class,0);
		}
		public Non_feature_elementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_non_feature_element; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNon_feature_element(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNon_feature_element(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNon_feature_element(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Non_feature_elementContext non_feature_element() throws RecognitionException {
		Non_feature_elementContext _localctx = new Non_feature_elementContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_non_feature_element);
		try {
			setState(702);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,34,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(675);
				dependency();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(676);
				type();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(677);
				classifier();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(678);
				data_type();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(679);
				namespace();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(680);
				class_();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(681);
				structure();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(682);
				metaclass();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(683);
				association();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(684);
				association_structure();
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(685);
				interaction();
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(686);
				behavior();
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(687);
				function();
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(688);
				predicate();
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(689);
				multiplicity();
				}
				break;
			case 16:
				enterOuterAlt(_localctx, 16);
				{
				setState(690);
				package_();
				}
				break;
			case 17:
				enterOuterAlt(_localctx, 17);
				{
				setState(691);
				library_package();
				}
				break;
			case 18:
				enterOuterAlt(_localctx, 18);
				{
				setState(692);
				specialization();
				}
				break;
			case 19:
				enterOuterAlt(_localctx, 19);
				{
				setState(693);
				conjunction();
				}
				break;
			case 20:
				enterOuterAlt(_localctx, 20);
				{
				setState(694);
				subclassification();
				}
				break;
			case 21:
				enterOuterAlt(_localctx, 21);
				{
				setState(695);
				disjoining();
				}
				break;
			case 22:
				enterOuterAlt(_localctx, 22);
				{
				setState(696);
				feature_inverting();
				}
				break;
			case 23:
				enterOuterAlt(_localctx, 23);
				{
				setState(697);
				feature_typing();
				}
				break;
			case 24:
				enterOuterAlt(_localctx, 24);
				{
				setState(698);
				subsetting();
				}
				break;
			case 25:
				enterOuterAlt(_localctx, 25);
				{
				setState(699);
				redefinition();
				}
				break;
			case 26:
				enterOuterAlt(_localctx, 26);
				{
				setState(700);
				type_featuring();
				}
				break;
			case 27:
				enterOuterAlt(_localctx, 27);
				{
				setState(701);
				namespace_import();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_elementContext extends ParserRuleContext {
		public FeatureContext feature() {
			return getRuleContext(FeatureContext.class,0);
		}
		public StepContext step() {
			return getRuleContext(StepContext.class,0);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Boolean_expressionContext boolean_expression() {
			return getRuleContext(Boolean_expressionContext.class,0);
		}
		public InvariantContext invariant() {
			return getRuleContext(InvariantContext.class,0);
		}
		public ConnectorContext connector() {
			return getRuleContext(ConnectorContext.class,0);
		}
		public Binding_connectorContext binding_connector() {
			return getRuleContext(Binding_connectorContext.class,0);
		}
		public SuccessionContext succession() {
			return getRuleContext(SuccessionContext.class,0);
		}
		public Item_flowContext item_flow() {
			return getRuleContext(Item_flowContext.class,0);
		}
		public Succession_item_flowContext succession_item_flow() {
			return getRuleContext(Succession_item_flowContext.class,0);
		}
		public Feature_elementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_element; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_element(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_element(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_element(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_elementContext feature_element() throws RecognitionException {
		Feature_elementContext _localctx = new Feature_elementContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_feature_element);
		try {
			setState(714);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,35,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(704);
				feature();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(705);
				step();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(706);
				expression();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(707);
				boolean_expression();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(708);
				invariant();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(709);
				connector();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(710);
				binding_connector();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(711);
				succession();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(712);
				item_flow();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(713);
				succession_item_flow();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Additional_optionsContext extends ParserRuleContext {
		public Meta_assignmentContext meta_assignment() {
			return getRuleContext(Meta_assignmentContext.class,0);
		}
		public Additional_optionsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_additional_options; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterAdditional_options(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitAdditional_options(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitAdditional_options(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Additional_optionsContext additional_options() throws RecognitionException {
		Additional_optionsContext _localctx = new Additional_optionsContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_additional_options);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(716);
			meta_assignment();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TypeContext extends ParserRuleContext {
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_TYPE() { return getToken(KerMLParser.KEYWORD_TYPE, 0); }
		public Type_declarationContext type_declaration() {
			return getRuleContext(Type_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TypeContext type() throws RecognitionException {
		TypeContext _localctx = new TypeContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(718);
			type_prefix();
			setState(719);
			match(KEYWORD_TYPE);
			setState(720);
			type_declaration();
			setState(721);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_prefixContext extends ParserRuleContext {
		public TerminalNode KEYWORD_ABSTRACT() { return getToken(KerMLParser.KEYWORD_ABSTRACT, 0); }
		public List<Prefix_metadata_memberContext> prefix_metadata_member() {
			return getRuleContexts(Prefix_metadata_memberContext.class);
		}
		public Prefix_metadata_memberContext prefix_metadata_member(int i) {
			return getRuleContext(Prefix_metadata_memberContext.class,i);
		}
		public Type_prefixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_prefix; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_prefix(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_prefix(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_prefix(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_prefixContext type_prefix() throws RecognitionException {
		Type_prefixContext _localctx = new Type_prefixContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_type_prefix);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(724);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_ABSTRACT) {
				{
				setState(723);
				match(KEYWORD_ABSTRACT);
				}
			}

			setState(729);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_HASHTAG) {
				{
				{
				setState(726);
				prefix_metadata_member();
				}
				}
				setState(731);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_declarationContext extends ParserRuleContext {
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public TerminalNode KEYWORD_ALL() { return getToken(KerMLParser.KEYWORD_ALL, 0); }
		public Multiplicity_boundsContext multiplicity_bounds() {
			return getRuleContext(Multiplicity_boundsContext.class,0);
		}
		public List<Specialization_partContext> specialization_part() {
			return getRuleContexts(Specialization_partContext.class);
		}
		public Specialization_partContext specialization_part(int i) {
			return getRuleContext(Specialization_partContext.class,i);
		}
		public List<Conjugation_partContext> conjugation_part() {
			return getRuleContexts(Conjugation_partContext.class);
		}
		public Conjugation_partContext conjugation_part(int i) {
			return getRuleContext(Conjugation_partContext.class,i);
		}
		public List<Type_relationship_partContext> type_relationship_part() {
			return getRuleContexts(Type_relationship_partContext.class);
		}
		public Type_relationship_partContext type_relationship_part(int i) {
			return getRuleContext(Type_relationship_partContext.class,i);
		}
		public Type_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_declarationContext type_declaration() throws RecognitionException {
		Type_declarationContext _localctx = new Type_declarationContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_type_declaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(733);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_ALL) {
				{
				setState(732);
				match(KEYWORD_ALL);
				}
			}

			setState(735);
			identification();
			setState(737);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_SQUARE_BRACKET_OPEN) {
				{
				setState(736);
				multiplicity_bounds();
				}
			}

			setState(741); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				setState(741);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case KEYWORD_SPECIALIZES:
				case SYMBOL_SPECIALIZES:
					{
					setState(739);
					specialization_part();
					}
					break;
				case KEYWORD_CONJUGATES:
				case SYMBOL_CONJUGATES:
					{
					setState(740);
					conjugation_part();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(743); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==KEYWORD_CONJUGATES || ((((_la - 80)) & ~0x3f) == 0 && ((1L << (_la - 80)) & 309237645313L) != 0) );
			setState(748);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 17592353816576L) != 0) || _la==KEYWORD_UNIONS) {
				{
				{
				setState(745);
				type_relationship_part();
				}
				}
				setState(750);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Specialization_partContext extends ParserRuleContext {
		public Specializes_operatorContext specializes_operator() {
			return getRuleContext(Specializes_operatorContext.class,0);
		}
		public List<Owned_specializationContext> owned_specialization() {
			return getRuleContexts(Owned_specializationContext.class);
		}
		public Owned_specializationContext owned_specialization(int i) {
			return getRuleContext(Owned_specializationContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Specialization_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_specialization_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSpecialization_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSpecialization_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSpecialization_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Specialization_partContext specialization_part() throws RecognitionException {
		Specialization_partContext _localctx = new Specialization_partContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_specialization_part);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(751);
			specializes_operator();
			setState(752);
			owned_specialization();
			setState(757);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(753);
				match(SYMBOL_COMMA);
				setState(754);
				owned_specialization();
				}
				}
				setState(759);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Conjugation_partContext extends ParserRuleContext {
		public Conjugates_operatorContext conjugates_operator() {
			return getRuleContext(Conjugates_operatorContext.class,0);
		}
		public Owned_conjugationContext owned_conjugation() {
			return getRuleContext(Owned_conjugationContext.class,0);
		}
		public Conjugation_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_conjugation_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterConjugation_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitConjugation_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitConjugation_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Conjugation_partContext conjugation_part() throws RecognitionException {
		Conjugation_partContext _localctx = new Conjugation_partContext(_ctx, getState());
		enterRule(_localctx, 82, RULE_conjugation_part);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(760);
			conjugates_operator();
			setState(761);
			owned_conjugation();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_relationship_partContext extends ParserRuleContext {
		public Disjoining_partContext disjoining_part() {
			return getRuleContext(Disjoining_partContext.class,0);
		}
		public Unioning_partContext unioning_part() {
			return getRuleContext(Unioning_partContext.class,0);
		}
		public Intersecting_partContext intersecting_part() {
			return getRuleContext(Intersecting_partContext.class,0);
		}
		public Differencing_partContext differencing_part() {
			return getRuleContext(Differencing_partContext.class,0);
		}
		public Type_relationship_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_relationship_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_relationship_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_relationship_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_relationship_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_relationship_partContext type_relationship_part() throws RecognitionException {
		Type_relationship_partContext _localctx = new Type_relationship_partContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_type_relationship_part);
		try {
			setState(767);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case KEYWORD_DISJOINT:
				enterOuterAlt(_localctx, 1);
				{
				setState(763);
				disjoining_part();
				}
				break;
			case KEYWORD_UNIONS:
				enterOuterAlt(_localctx, 2);
				{
				setState(764);
				unioning_part();
				}
				break;
			case KEYWORD_INTERSECTS:
				enterOuterAlt(_localctx, 3);
				{
				setState(765);
				intersecting_part();
				}
				break;
			case KEYWORD_DIFFERENCES:
				enterOuterAlt(_localctx, 4);
				{
				setState(766);
				differencing_part();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Disjoining_partContext extends ParserRuleContext {
		public TerminalNode KEYWORD_DISJOINT() { return getToken(KerMLParser.KEYWORD_DISJOINT, 0); }
		public TerminalNode KEYWORD_FROM() { return getToken(KerMLParser.KEYWORD_FROM, 0); }
		public List<Owned_disjoiningContext> owned_disjoining() {
			return getRuleContexts(Owned_disjoiningContext.class);
		}
		public Owned_disjoiningContext owned_disjoining(int i) {
			return getRuleContext(Owned_disjoiningContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Disjoining_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_disjoining_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterDisjoining_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitDisjoining_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitDisjoining_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Disjoining_partContext disjoining_part() throws RecognitionException {
		Disjoining_partContext _localctx = new Disjoining_partContext(_ctx, getState());
		enterRule(_localctx, 86, RULE_disjoining_part);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(769);
			match(KEYWORD_DISJOINT);
			setState(770);
			match(KEYWORD_FROM);
			setState(771);
			owned_disjoining();
			setState(776);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(772);
				match(SYMBOL_COMMA);
				setState(773);
				owned_disjoining();
				}
				}
				setState(778);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Unioning_partContext extends ParserRuleContext {
		public TerminalNode KEYWORD_UNIONS() { return getToken(KerMLParser.KEYWORD_UNIONS, 0); }
		public List<UnioningContext> unioning() {
			return getRuleContexts(UnioningContext.class);
		}
		public UnioningContext unioning(int i) {
			return getRuleContext(UnioningContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Unioning_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unioning_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterUnioning_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitUnioning_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitUnioning_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Unioning_partContext unioning_part() throws RecognitionException {
		Unioning_partContext _localctx = new Unioning_partContext(_ctx, getState());
		enterRule(_localctx, 88, RULE_unioning_part);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(779);
			match(KEYWORD_UNIONS);
			setState(780);
			unioning();
			setState(785);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(781);
				match(SYMBOL_COMMA);
				setState(782);
				unioning();
				}
				}
				setState(787);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Intersecting_partContext extends ParserRuleContext {
		public TerminalNode KEYWORD_INTERSECTS() { return getToken(KerMLParser.KEYWORD_INTERSECTS, 0); }
		public List<IntersectingContext> intersecting() {
			return getRuleContexts(IntersectingContext.class);
		}
		public IntersectingContext intersecting(int i) {
			return getRuleContext(IntersectingContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Intersecting_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_intersecting_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterIntersecting_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitIntersecting_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitIntersecting_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Intersecting_partContext intersecting_part() throws RecognitionException {
		Intersecting_partContext _localctx = new Intersecting_partContext(_ctx, getState());
		enterRule(_localctx, 90, RULE_intersecting_part);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(788);
			match(KEYWORD_INTERSECTS);
			setState(789);
			intersecting();
			setState(794);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(790);
				match(SYMBOL_COMMA);
				setState(791);
				intersecting();
				}
				}
				setState(796);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Differencing_partContext extends ParserRuleContext {
		public TerminalNode KEYWORD_DIFFERENCES() { return getToken(KerMLParser.KEYWORD_DIFFERENCES, 0); }
		public List<DifferencingContext> differencing() {
			return getRuleContexts(DifferencingContext.class);
		}
		public DifferencingContext differencing(int i) {
			return getRuleContext(DifferencingContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Differencing_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_differencing_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterDifferencing_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitDifferencing_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitDifferencing_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Differencing_partContext differencing_part() throws RecognitionException {
		Differencing_partContext _localctx = new Differencing_partContext(_ctx, getState());
		enterRule(_localctx, 92, RULE_differencing_part);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(797);
			match(KEYWORD_DIFFERENCES);
			setState(798);
			differencing();
			setState(803);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(799);
				match(SYMBOL_COMMA);
				setState(800);
				differencing();
				}
				}
				setState(805);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_bodyContext extends ParserRuleContext {
		public TerminalNode SYMBOL_STATEMENT_DELIMITER() { return getToken(KerMLParser.SYMBOL_STATEMENT_DELIMITER, 0); }
		public TerminalNode SYMBOL_CURLY_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_OPEN, 0); }
		public Type_body_elementsContext type_body_elements() {
			return getRuleContext(Type_body_elementsContext.class,0);
		}
		public TerminalNode SYMBOL_CURLY_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_CLOSE, 0); }
		public Type_bodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_body; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_body(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_body(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_body(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_bodyContext type_body() throws RecognitionException {
		Type_bodyContext _localctx = new Type_bodyContext(_ctx, getState());
		enterRule(_localctx, 94, RULE_type_body);
		try {
			setState(811);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_STATEMENT_DELIMITER:
				enterOuterAlt(_localctx, 1);
				{
				setState(806);
				match(SYMBOL_STATEMENT_DELIMITER);
				}
				break;
			case SYMBOL_CURLY_BRACKET_OPEN:
				enterOuterAlt(_localctx, 2);
				{
				{
				setState(807);
				match(SYMBOL_CURLY_BRACKET_OPEN);
				setState(808);
				type_body_elements();
				setState(809);
				match(SYMBOL_CURLY_BRACKET_CLOSE);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_body_elementsContext extends ParserRuleContext {
		public List<Type_body_elementContext> type_body_element() {
			return getRuleContexts(Type_body_elementContext.class);
		}
		public Type_body_elementContext type_body_element(int i) {
			return getRuleContext(Type_body_elementContext.class,i);
		}
		public Type_body_elementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_body_elements; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_body_elements(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_body_elements(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_body_elements(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_body_elementsContext type_body_elements() throws RecognitionException {
		Type_body_elementsContext _localctx = new Type_body_elementsContext(_ctx, getState());
		enterRule(_localctx, 96, RULE_type_body_elements);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(816);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2296767961785952148L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & -3999754816522854401L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
				{
				{
				setState(813);
				type_body_element();
				}
				}
				setState(818);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_body_elementContext extends ParserRuleContext {
		public Type_feature_memberContext type_feature_member() {
			return getRuleContext(Type_feature_memberContext.class,0);
		}
		public Member_prefixContext member_prefix() {
			return getRuleContext(Member_prefixContext.class,0);
		}
		public ElementContext element() {
			return getRuleContext(ElementContext.class,0);
		}
		public Type_body_elementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_body_element; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_body_element(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_body_element(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_body_element(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_body_elementContext type_body_element() throws RecognitionException {
		Type_body_elementContext _localctx = new Type_body_elementContext(_ctx, getState());
		enterRule(_localctx, 98, RULE_type_body_element);
		try {
			setState(823);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,51,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(819);
				type_feature_member();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(820);
				member_prefix();
				setState(821);
				element();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SpecializationContext extends ParserRuleContext {
		public TerminalNode KEYWORD_SUBTYPE() { return getToken(KerMLParser.KEYWORD_SUBTYPE, 0); }
		public Specific_typeContext specific_type() {
			return getRuleContext(Specific_typeContext.class,0);
		}
		public Specializes_operatorContext specializes_operator() {
			return getRuleContext(Specializes_operatorContext.class,0);
		}
		public General_typeContext general_type() {
			return getRuleContext(General_typeContext.class,0);
		}
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public TerminalNode KEYWORD_SPECIALIZATION() { return getToken(KerMLParser.KEYWORD_SPECIALIZATION, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public SpecializationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_specialization; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSpecialization(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSpecialization(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSpecialization(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SpecializationContext specialization() throws RecognitionException {
		SpecializationContext _localctx = new SpecializationContext(_ctx, getState());
		enterRule(_localctx, 100, RULE_specialization);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(827);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_SPECIALIZATION) {
				{
				setState(825);
				match(KEYWORD_SPECIALIZATION);
				setState(826);
				identification();
				}
			}

			setState(829);
			match(KEYWORD_SUBTYPE);
			setState(830);
			specific_type();
			setState(831);
			specializes_operator();
			setState(832);
			general_type();
			setState(833);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_specializationContext extends ParserRuleContext {
		public General_typeContext general_type() {
			return getRuleContext(General_typeContext.class,0);
		}
		public Owned_specializationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_specialization; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_specialization(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_specialization(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_specialization(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_specializationContext owned_specialization() throws RecognitionException {
		Owned_specializationContext _localctx = new Owned_specializationContext(_ctx, getState());
		enterRule(_localctx, 102, RULE_owned_specialization);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(835);
			general_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Specific_typeContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Owned_feature_chainContext owned_feature_chain() {
			return getRuleContext(Owned_feature_chainContext.class,0);
		}
		public Specific_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_specific_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSpecific_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSpecific_type(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSpecific_type(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Specific_typeContext specific_type() throws RecognitionException {
		Specific_typeContext _localctx = new Specific_typeContext(_ctx, getState());
		enterRule(_localctx, 104, RULE_specific_type);
		try {
			setState(839);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,53,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(837);
				qualified_name();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(838);
				owned_feature_chain();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class General_typeContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Owned_feature_chainContext owned_feature_chain() {
			return getRuleContext(Owned_feature_chainContext.class,0);
		}
		public General_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_general_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterGeneral_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitGeneral_type(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitGeneral_type(this);
			else return visitor.visitChildren(this);
		}
	}

	public final General_typeContext general_type() throws RecognitionException {
		General_typeContext _localctx = new General_typeContext(_ctx, getState());
		enterRule(_localctx, 106, RULE_general_type);
		try {
			setState(843);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,54,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(841);
				qualified_name();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(842);
				owned_feature_chain();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConjunctionContext extends ParserRuleContext {
		public TerminalNode KEYWORD_CONJUGATE() { return getToken(KerMLParser.KEYWORD_CONJUGATE, 0); }
		public Conjugates_operatorContext conjugates_operator() {
			return getRuleContext(Conjugates_operatorContext.class,0);
		}
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public List<Qualified_nameContext> qualified_name() {
			return getRuleContexts(Qualified_nameContext.class);
		}
		public Qualified_nameContext qualified_name(int i) {
			return getRuleContext(Qualified_nameContext.class,i);
		}
		public List<Feature_chainContext> feature_chain() {
			return getRuleContexts(Feature_chainContext.class);
		}
		public Feature_chainContext feature_chain(int i) {
			return getRuleContext(Feature_chainContext.class,i);
		}
		public TerminalNode KEYWORD_CONJUGATION() { return getToken(KerMLParser.KEYWORD_CONJUGATION, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public ConjunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_conjunction; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterConjunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitConjunction(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitConjunction(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ConjunctionContext conjunction() throws RecognitionException {
		ConjunctionContext _localctx = new ConjunctionContext(_ctx, getState());
		enterRule(_localctx, 108, RULE_conjunction);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(847);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_CONJUGATION) {
				{
				setState(845);
				match(KEYWORD_CONJUGATION);
				setState(846);
				identification();
				}
			}

			setState(849);
			match(KEYWORD_CONJUGATE);
			setState(852);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,56,_ctx) ) {
			case 1:
				{
				setState(850);
				qualified_name();
				}
				break;
			case 2:
				{
				setState(851);
				feature_chain();
				}
				break;
			}
			setState(854);
			conjugates_operator();
			setState(857);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,57,_ctx) ) {
			case 1:
				{
				setState(855);
				qualified_name();
				}
				break;
			case 2:
				{
				setState(856);
				feature_chain();
				}
				break;
			}
			setState(859);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_conjugationContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Feature_chainContext feature_chain() {
			return getRuleContext(Feature_chainContext.class,0);
		}
		public Owned_conjugationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_conjugation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_conjugation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_conjugation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_conjugation(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_conjugationContext owned_conjugation() throws RecognitionException {
		Owned_conjugationContext _localctx = new Owned_conjugationContext(_ctx, getState());
		enterRule(_localctx, 110, RULE_owned_conjugation);
		try {
			setState(863);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,58,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(861);
				qualified_name();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(862);
				feature_chain();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DisjoiningContext extends ParserRuleContext {
		public TerminalNode KEYWORD_DISJOINT() { return getToken(KerMLParser.KEYWORD_DISJOINT, 0); }
		public TerminalNode KEYWORD_FROM() { return getToken(KerMLParser.KEYWORD_FROM, 0); }
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public List<Qualified_nameContext> qualified_name() {
			return getRuleContexts(Qualified_nameContext.class);
		}
		public Qualified_nameContext qualified_name(int i) {
			return getRuleContext(Qualified_nameContext.class,i);
		}
		public List<Feature_chainContext> feature_chain() {
			return getRuleContexts(Feature_chainContext.class);
		}
		public Feature_chainContext feature_chain(int i) {
			return getRuleContext(Feature_chainContext.class,i);
		}
		public TerminalNode KEYWORD_DISJOINING() { return getToken(KerMLParser.KEYWORD_DISJOINING, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public DisjoiningContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_disjoining; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterDisjoining(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitDisjoining(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitDisjoining(this);
			else return visitor.visitChildren(this);
		}
	}

	public final DisjoiningContext disjoining() throws RecognitionException {
		DisjoiningContext _localctx = new DisjoiningContext(_ctx, getState());
		enterRule(_localctx, 112, RULE_disjoining);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(867);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_DISJOINING) {
				{
				setState(865);
				match(KEYWORD_DISJOINING);
				setState(866);
				identification();
				}
			}

			setState(869);
			match(KEYWORD_DISJOINT);
			setState(872);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,60,_ctx) ) {
			case 1:
				{
				setState(870);
				qualified_name();
				}
				break;
			case 2:
				{
				setState(871);
				feature_chain();
				}
				break;
			}
			setState(874);
			match(KEYWORD_FROM);
			setState(877);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,61,_ctx) ) {
			case 1:
				{
				setState(875);
				qualified_name();
				}
				break;
			case 2:
				{
				setState(876);
				feature_chain();
				}
				break;
			}
			setState(879);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_disjoiningContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Feature_chainContext feature_chain() {
			return getRuleContext(Feature_chainContext.class,0);
		}
		public Owned_disjoiningContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_disjoining; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_disjoining(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_disjoining(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_disjoining(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_disjoiningContext owned_disjoining() throws RecognitionException {
		Owned_disjoiningContext _localctx = new Owned_disjoiningContext(_ctx, getState());
		enterRule(_localctx, 114, RULE_owned_disjoining);
		try {
			setState(883);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,62,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(881);
				qualified_name();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(882);
				feature_chain();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class UnioningContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Owned_feature_chainContext owned_feature_chain() {
			return getRuleContext(Owned_feature_chainContext.class,0);
		}
		public UnioningContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unioning; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterUnioning(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitUnioning(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitUnioning(this);
			else return visitor.visitChildren(this);
		}
	}

	public final UnioningContext unioning() throws RecognitionException {
		UnioningContext _localctx = new UnioningContext(_ctx, getState());
		enterRule(_localctx, 116, RULE_unioning);
		try {
			setState(887);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,63,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(885);
				qualified_name();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(886);
				owned_feature_chain();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IntersectingContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Owned_feature_chainContext owned_feature_chain() {
			return getRuleContext(Owned_feature_chainContext.class,0);
		}
		public IntersectingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_intersecting; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterIntersecting(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitIntersecting(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitIntersecting(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IntersectingContext intersecting() throws RecognitionException {
		IntersectingContext _localctx = new IntersectingContext(_ctx, getState());
		enterRule(_localctx, 118, RULE_intersecting);
		try {
			setState(891);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,64,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(889);
				qualified_name();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(890);
				owned_feature_chain();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DifferencingContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Owned_feature_chainContext owned_feature_chain() {
			return getRuleContext(Owned_feature_chainContext.class,0);
		}
		public DifferencingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_differencing; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterDifferencing(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitDifferencing(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitDifferencing(this);
			else return visitor.visitChildren(this);
		}
	}

	public final DifferencingContext differencing() throws RecognitionException {
		DifferencingContext _localctx = new DifferencingContext(_ctx, getState());
		enterRule(_localctx, 120, RULE_differencing);
		try {
			setState(895);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,65,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(893);
				qualified_name();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(894);
				owned_feature_chain();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_memberContext extends ParserRuleContext {
		public Type_feature_memberContext type_feature_member() {
			return getRuleContext(Type_feature_memberContext.class,0);
		}
		public Owned_feature_memberContext owned_feature_member() {
			return getRuleContext(Owned_feature_memberContext.class,0);
		}
		public Feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_memberContext feature_member() throws RecognitionException {
		Feature_memberContext _localctx = new Feature_memberContext(_ctx, getState());
		enterRule(_localctx, 122, RULE_feature_member);
		try {
			setState(899);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,66,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(897);
				type_feature_member();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(898);
				owned_feature_member();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_feature_memberContext extends ParserRuleContext {
		public Member_prefixContext member_prefix() {
			return getRuleContext(Member_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_MEMBER() { return getToken(KerMLParser.KEYWORD_MEMBER, 0); }
		public Feature_elementContext feature_element() {
			return getRuleContext(Feature_elementContext.class,0);
		}
		public Type_feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_feature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_feature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_feature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_feature_memberContext type_feature_member() throws RecognitionException {
		Type_feature_memberContext _localctx = new Type_feature_memberContext(_ctx, getState());
		enterRule(_localctx, 124, RULE_type_feature_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(901);
			member_prefix();
			setState(902);
			match(KEYWORD_MEMBER);
			setState(903);
			feature_element();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_feature_memberContext extends ParserRuleContext {
		public Member_prefixContext member_prefix() {
			return getRuleContext(Member_prefixContext.class,0);
		}
		public Feature_elementContext feature_element() {
			return getRuleContext(Feature_elementContext.class,0);
		}
		public Owned_feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_feature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_feature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_feature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_feature_memberContext owned_feature_member() throws RecognitionException {
		Owned_feature_memberContext _localctx = new Owned_feature_memberContext(_ctx, getState());
		enterRule(_localctx, 126, RULE_owned_feature_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(905);
			member_prefix();
			setState(906);
			feature_element();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ClassifierContext extends ParserRuleContext {
		public TerminalNode KEYWORD_CLASSIFIER() { return getToken(KerMLParser.KEYWORD_CLASSIFIER, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public ClassifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterClassifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitClassifier(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitClassifier(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ClassifierContext classifier() throws RecognitionException {
		ClassifierContext _localctx = new ClassifierContext(_ctx, getState());
		enterRule(_localctx, 128, RULE_classifier);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(909);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,67,_ctx) ) {
			case 1:
				{
				setState(908);
				type_prefix();
				}
				break;
			}
			setState(911);
			match(KEYWORD_CLASSIFIER);
			setState(912);
			classifier_declaration();
			setState(913);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Classifier_declarationContext extends ParserRuleContext {
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public TerminalNode KEYWORD_ALL() { return getToken(KerMLParser.KEYWORD_ALL, 0); }
		public Multiplicity_boundsContext multiplicity_bounds() {
			return getRuleContext(Multiplicity_boundsContext.class,0);
		}
		public Superclassing_partContext superclassing_part() {
			return getRuleContext(Superclassing_partContext.class,0);
		}
		public Conjugation_partContext conjugation_part() {
			return getRuleContext(Conjugation_partContext.class,0);
		}
		public List<Type_relationship_partContext> type_relationship_part() {
			return getRuleContexts(Type_relationship_partContext.class);
		}
		public Type_relationship_partContext type_relationship_part(int i) {
			return getRuleContext(Type_relationship_partContext.class,i);
		}
		public Classifier_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classifier_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterClassifier_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitClassifier_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitClassifier_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Classifier_declarationContext classifier_declaration() throws RecognitionException {
		Classifier_declarationContext _localctx = new Classifier_declarationContext(_ctx, getState());
		enterRule(_localctx, 130, RULE_classifier_declaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(916);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_ALL) {
				{
				setState(915);
				match(KEYWORD_ALL);
				}
			}

			setState(918);
			identification();
			setState(920);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_SQUARE_BRACKET_OPEN) {
				{
				setState(919);
				multiplicity_bounds();
				}
			}

			setState(924);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,70,_ctx) ) {
			case 1:
				{
				setState(922);
				superclassing_part();
				}
				break;
			case 2:
				{
				setState(923);
				conjugation_part();
				}
				break;
			}
			setState(929);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 17592353816576L) != 0) || _la==KEYWORD_UNIONS) {
				{
				{
				setState(926);
				type_relationship_part();
				}
				}
				setState(931);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Superclassing_partContext extends ParserRuleContext {
		public Specializes_operatorContext specializes_operator() {
			return getRuleContext(Specializes_operatorContext.class,0);
		}
		public List<Owned_subclassificationContext> owned_subclassification() {
			return getRuleContexts(Owned_subclassificationContext.class);
		}
		public Owned_subclassificationContext owned_subclassification(int i) {
			return getRuleContext(Owned_subclassificationContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Superclassing_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_superclassing_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSuperclassing_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSuperclassing_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSuperclassing_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Superclassing_partContext superclassing_part() throws RecognitionException {
		Superclassing_partContext _localctx = new Superclassing_partContext(_ctx, getState());
		enterRule(_localctx, 132, RULE_superclassing_part);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(932);
			specializes_operator();
			setState(933);
			owned_subclassification();
			setState(938);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(934);
				match(SYMBOL_COMMA);
				setState(935);
				owned_subclassification();
				}
				}
				setState(940);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SubclassificationContext extends ParserRuleContext {
		public TerminalNode KEYWORD_SUBCLASSIFIER() { return getToken(KerMLParser.KEYWORD_SUBCLASSIFIER, 0); }
		public List<Qualified_nameContext> qualified_name() {
			return getRuleContexts(Qualified_nameContext.class);
		}
		public Qualified_nameContext qualified_name(int i) {
			return getRuleContext(Qualified_nameContext.class,i);
		}
		public Specializes_operatorContext specializes_operator() {
			return getRuleContext(Specializes_operatorContext.class,0);
		}
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public TerminalNode KEYWORD_SPECIALIZATION() { return getToken(KerMLParser.KEYWORD_SPECIALIZATION, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public SubclassificationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_subclassification; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSubclassification(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSubclassification(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSubclassification(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SubclassificationContext subclassification() throws RecognitionException {
		SubclassificationContext _localctx = new SubclassificationContext(_ctx, getState());
		enterRule(_localctx, 134, RULE_subclassification);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(943);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_SPECIALIZATION) {
				{
				setState(941);
				match(KEYWORD_SPECIALIZATION);
				setState(942);
				identification();
				}
			}

			setState(945);
			match(KEYWORD_SUBCLASSIFIER);
			setState(946);
			qualified_name();
			setState(947);
			specializes_operator();
			setState(948);
			qualified_name();
			setState(949);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_subclassificationContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Owned_subclassificationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_subclassification; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_subclassification(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_subclassification(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_subclassification(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_subclassificationContext owned_subclassification() throws RecognitionException {
		Owned_subclassificationContext _localctx = new Owned_subclassificationContext(_ctx, getState());
		enterRule(_localctx, 136, RULE_owned_subclassification);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(951);
			qualified_name();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FeatureContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public TerminalNode KEYWORD_FEATURE() { return getToken(KerMLParser.KEYWORD_FEATURE, 0); }
		public Prefix_metadata_memberContext prefix_metadata_member() {
			return getRuleContext(Prefix_metadata_memberContext.class,0);
		}
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public Anonymous_featureContext anonymous_feature() {
			return getRuleContext(Anonymous_featureContext.class,0);
		}
		public FeatureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FeatureContext feature() throws RecognitionException {
		FeatureContext _localctx = new FeatureContext(_ctx, getState());
		enterRule(_localctx, 138, RULE_feature);
		int _la;
		try {
			setState(967);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,77,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(953);
				feature_prefix();
				setState(956);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case KEYWORD_FEATURE:
					{
					setState(954);
					match(KEYWORD_FEATURE);
					}
					break;
				case SYMBOL_HASHTAG:
					{
					setState(955);
					prefix_metadata_member();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(959);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1153343717072175120L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & 611926736943188483L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
					{
					setState(958);
					feature_declaration();
					}
				}

				setState(962);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
					{
					setState(961);
					value_part();
					}
				}

				setState(964);
				type_body();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(966);
				anonymous_feature();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Anonymous_featureContext extends ParserRuleContext {
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public End_feature_prefixContext end_feature_prefix() {
			return getRuleContext(End_feature_prefixContext.class,0);
		}
		public Basic_feature_prefixContext basic_feature_prefix() {
			return getRuleContext(Basic_feature_prefixContext.class,0);
		}
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public Anonymous_featureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_anonymous_feature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterAnonymous_feature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitAnonymous_feature(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitAnonymous_feature(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Anonymous_featureContext anonymous_feature() throws RecognitionException {
		Anonymous_featureContext _localctx = new Anonymous_featureContext(_ctx, getState());
		enterRule(_localctx, 140, RULE_anonymous_feature);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(971);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,78,_ctx) ) {
			case 1:
				{
				setState(969);
				end_feature_prefix();
				}
				break;
			case 2:
				{
				setState(970);
				basic_feature_prefix();
				}
				break;
			}
			setState(973);
			feature_declaration();
			setState(975);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
				{
				setState(974);
				value_part();
				}
			}

			setState(977);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_prefixContext extends ParserRuleContext {
		public End_feature_prefixContext end_feature_prefix() {
			return getRuleContext(End_feature_prefixContext.class,0);
		}
		public Basic_feature_prefixContext basic_feature_prefix() {
			return getRuleContext(Basic_feature_prefixContext.class,0);
		}
		public List<Prefix_metadata_memberContext> prefix_metadata_member() {
			return getRuleContexts(Prefix_metadata_memberContext.class);
		}
		public Prefix_metadata_memberContext prefix_metadata_member(int i) {
			return getRuleContext(Prefix_metadata_memberContext.class,i);
		}
		public Owned_cross_feature_memberContext owned_cross_feature_member() {
			return getRuleContext(Owned_cross_feature_memberContext.class,0);
		}
		public Feature_prefixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_prefix; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_prefix(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_prefix(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_prefix(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_prefixContext feature_prefix() throws RecognitionException {
		Feature_prefixContext _localctx = new Feature_prefixContext(_ctx, getState());
		enterRule(_localctx, 142, RULE_feature_prefix);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(984);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,81,_ctx) ) {
			case 1:
				{
				setState(979);
				end_feature_prefix();
				setState(981);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1153343717089017876L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & 611926773450410763L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
					{
					setState(980);
					owned_cross_feature_member();
					}
				}

				}
				break;
			case 2:
				{
				setState(983);
				basic_feature_prefix();
				}
				break;
			}
			setState(989);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,82,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(986);
					prefix_metadata_member();
					}
					} 
				}
				setState(991);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,82,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class End_feature_prefixContext extends ParserRuleContext {
		public TerminalNode KEYWORD_END() { return getToken(KerMLParser.KEYWORD_END, 0); }
		public TerminalNode KEYWORD_CONST() { return getToken(KerMLParser.KEYWORD_CONST, 0); }
		public End_feature_prefixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_end_feature_prefix; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterEnd_feature_prefix(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitEnd_feature_prefix(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitEnd_feature_prefix(this);
			else return visitor.visitChildren(this);
		}
	}

	public final End_feature_prefixContext end_feature_prefix() throws RecognitionException {
		End_feature_prefixContext _localctx = new End_feature_prefixContext(_ctx, getState());
		enterRule(_localctx, 144, RULE_end_feature_prefix);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(993);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_CONST) {
				{
				setState(992);
				match(KEYWORD_CONST);
				}
			}

			setState(995);
			match(KEYWORD_END);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Basic_feature_prefixContext extends ParserRuleContext {
		public Feature_directionContext feature_direction() {
			return getRuleContext(Feature_directionContext.class,0);
		}
		public TerminalNode KEYWORD_DERIVED() { return getToken(KerMLParser.KEYWORD_DERIVED, 0); }
		public TerminalNode KEYWORD_ABSTRACT() { return getToken(KerMLParser.KEYWORD_ABSTRACT, 0); }
		public TerminalNode KEYWORD_COMPOSITE() { return getToken(KerMLParser.KEYWORD_COMPOSITE, 0); }
		public TerminalNode KEYWORD_PORTION() { return getToken(KerMLParser.KEYWORD_PORTION, 0); }
		public TerminalNode KEYWORD_VAR() { return getToken(KerMLParser.KEYWORD_VAR, 0); }
		public TerminalNode KEYWORD_CONST() { return getToken(KerMLParser.KEYWORD_CONST, 0); }
		public TerminalNode KEYWORD_READONLY() { return getToken(KerMLParser.KEYWORD_READONLY, 0); }
		public Basic_feature_prefixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_basic_feature_prefix; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBasic_feature_prefix(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBasic_feature_prefix(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBasic_feature_prefix(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Basic_feature_prefixContext basic_feature_prefix() throws RecognitionException {
		Basic_feature_prefixContext _localctx = new Basic_feature_prefixContext(_ctx, getState());
		enterRule(_localctx, 146, RULE_basic_feature_prefix);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(998);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,84,_ctx) ) {
			case 1:
				{
				setState(997);
				feature_direction();
				}
				break;
			}
			setState(1001);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_DERIVED) {
				{
				setState(1000);
				match(KEYWORD_DERIVED);
				}
			}

			setState(1004);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_ABSTRACT) {
				{
				setState(1003);
				match(KEYWORD_ABSTRACT);
				}
			}

			setState(1007);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_COMPOSITE || _la==KEYWORD_PORTION) {
				{
				setState(1006);
				_la = _input.LA(1);
				if ( !(_la==KEYWORD_COMPOSITE || _la==KEYWORD_PORTION) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
			}

			setState(1010);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 73)) & ~0x3f) == 0 && ((1L << (_la - 73)) & 142606337L) != 0)) {
				{
				setState(1009);
				_la = _input.LA(1);
				if ( !(((((_la - 73)) & ~0x3f) == 0 && ((1L << (_la - 73)) & 142606337L) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_cross_feature_memberContext extends ParserRuleContext {
		public Owned_cross_featureContext owned_cross_feature() {
			return getRuleContext(Owned_cross_featureContext.class,0);
		}
		public Owned_cross_feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_cross_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_cross_feature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_cross_feature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_cross_feature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_cross_feature_memberContext owned_cross_feature_member() throws RecognitionException {
		Owned_cross_feature_memberContext _localctx = new Owned_cross_feature_memberContext(_ctx, getState());
		enterRule(_localctx, 148, RULE_owned_cross_feature_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1012);
			owned_cross_feature();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_cross_featureContext extends ParserRuleContext {
		public Basic_feature_prefixContext basic_feature_prefix() {
			return getRuleContext(Basic_feature_prefixContext.class,0);
		}
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Owned_cross_featureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_cross_feature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_cross_feature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_cross_feature(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_cross_feature(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_cross_featureContext owned_cross_feature() throws RecognitionException {
		Owned_cross_featureContext _localctx = new Owned_cross_featureContext(_ctx, getState());
		enterRule(_localctx, 150, RULE_owned_cross_feature);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1014);
			basic_feature_prefix();
			setState(1015);
			feature_declaration();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_directionContext extends ParserRuleContext {
		public TerminalNode KEYWORD_IN() { return getToken(KerMLParser.KEYWORD_IN, 0); }
		public TerminalNode KEYWORD_OUT() { return getToken(KerMLParser.KEYWORD_OUT, 0); }
		public TerminalNode KEYWORD_INOUT() { return getToken(KerMLParser.KEYWORD_INOUT, 0); }
		public Feature_directionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_direction; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_direction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_direction(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_direction(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_directionContext feature_direction() throws RecognitionException {
		Feature_directionContext _localctx = new Feature_directionContext(_ctx, getState());
		enterRule(_localctx, 152, RULE_feature_direction);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1017);
			_la = _input.LA(1);
			if ( !(((((_la - 47)) & ~0x3f) == 0 && ((1L << (_la - 47)) & 524291L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_declarationContext extends ParserRuleContext {
		public Feature_identificationContext feature_identification() {
			return getRuleContext(Feature_identificationContext.class,0);
		}
		public Feature_specialization_partContext feature_specialization_part() {
			return getRuleContext(Feature_specialization_partContext.class,0);
		}
		public Conjugation_partContext conjugation_part() {
			return getRuleContext(Conjugation_partContext.class,0);
		}
		public TerminalNode KEYWORD_ALL() { return getToken(KerMLParser.KEYWORD_ALL, 0); }
		public List<Feature_relationship_partContext> feature_relationship_part() {
			return getRuleContexts(Feature_relationship_partContext.class);
		}
		public Feature_relationship_partContext feature_relationship_part(int i) {
			return getRuleContext(Feature_relationship_partContext.class,i);
		}
		public Feature_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_declarationContext feature_declaration() throws RecognitionException {
		Feature_declarationContext _localctx = new Feature_declarationContext(_ctx, getState());
		enterRule(_localctx, 154, RULE_feature_declaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1020);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_ALL) {
				{
				setState(1019);
				match(KEYWORD_ALL);
				}
			}

			setState(1029);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_SMALLER:
			case NAME:
				{
				setState(1022);
				feature_identification();
				setState(1025);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case KEYWORD_IN:
				case KEYWORD_INOUT:
				case KEYWORD_NONUNIQUE:
				case KEYWORD_ORDERED:
				case KEYWORD_OUT:
				case KEYWORD_REDEFINES:
				case KEYWORD_REFERENCES:
				case KEYWORD_SUBSETS:
				case KEYWORD_TYPED:
				case KEYWORD_CROSSES:
				case SYMBOL_TYPED_BY:
				case SYMBOL_SPECIALIZES:
				case SYMBOL_REFERENCES:
				case SYMBOL_REDEFINES:
				case SYMBOL_CROSSES:
				case SYMBOL_SQUARE_BRACKET_OPEN:
					{
					setState(1023);
					feature_specialization_part();
					}
					break;
				case KEYWORD_CONJUGATES:
				case SYMBOL_CONJUGATES:
					{
					setState(1024);
					conjugation_part();
					}
					break;
				case KEYWORD_BINDING:
				case KEYWORD_BOOL:
				case KEYWORD_CHAINS:
				case KEYWORD_CONNECTOR:
				case KEYWORD_DEFAULT:
				case KEYWORD_DIFFERENCES:
				case KEYWORD_DISJOINT:
				case KEYWORD_EXPR:
				case KEYWORD_FEATURE:
				case KEYWORD_FEATURED:
				case KEYWORD_FIRST:
				case KEYWORD_FLOW:
				case KEYWORD_FROM:
				case KEYWORD_INTERSECTS:
				case KEYWORD_INV:
				case KEYWORD_INVERSE:
				case KEYWORD_OF:
				case KEYWORD_STEP:
				case KEYWORD_SUCCESSION:
				case KEYWORD_UNIONS:
				case SYMBOL_STATEMENT_DELIMITER:
				case SYMBOL_ROUND_BRACKET_OPEN:
				case SYMBOL_CURLY_BRACKET_OPEN:
				case SYMBOL_HASHTAG:
				case SYMBOL_ASSIGN:
				case SYMBOL_DEF_ASSIGN:
					break;
				default:
					break;
				}
				}
				break;
			case KEYWORD_IN:
			case KEYWORD_INOUT:
			case KEYWORD_NONUNIQUE:
			case KEYWORD_ORDERED:
			case KEYWORD_OUT:
			case KEYWORD_REDEFINES:
			case KEYWORD_REFERENCES:
			case KEYWORD_SUBSETS:
			case KEYWORD_TYPED:
			case KEYWORD_CROSSES:
			case SYMBOL_TYPED_BY:
			case SYMBOL_SPECIALIZES:
			case SYMBOL_REFERENCES:
			case SYMBOL_REDEFINES:
			case SYMBOL_CROSSES:
			case SYMBOL_SQUARE_BRACKET_OPEN:
				{
				setState(1027);
				feature_specialization_part();
				}
				break;
			case KEYWORD_CONJUGATES:
			case SYMBOL_CONJUGATES:
				{
				setState(1028);
				conjugation_part();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(1034);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2269409347375104L) != 0) || _la==KEYWORD_UNIONS) {
				{
				{
				setState(1031);
				feature_relationship_part();
				}
				}
				setState(1036);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_identificationContext extends ParserRuleContext {
		public TerminalNode SYMBOL_SMALLER() { return getToken(KerMLParser.SYMBOL_SMALLER, 0); }
		public List<TerminalNode> NAME() { return getTokens(KerMLParser.NAME); }
		public TerminalNode NAME(int i) {
			return getToken(KerMLParser.NAME, i);
		}
		public TerminalNode SYMBOL_GREATER() { return getToken(KerMLParser.SYMBOL_GREATER, 0); }
		public Feature_identificationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_identification; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_identification(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_identification(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_identification(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_identificationContext feature_identification() throws RecognitionException {
		Feature_identificationContext _localctx = new Feature_identificationContext(_ctx, getState());
		enterRule(_localctx, 156, RULE_feature_identification);
		int _la;
		try {
			setState(1044);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_SMALLER:
				enterOuterAlt(_localctx, 1);
				{
				setState(1037);
				match(SYMBOL_SMALLER);
				setState(1038);
				match(NAME);
				setState(1039);
				match(SYMBOL_GREATER);
				setState(1041);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==NAME) {
					{
					setState(1040);
					match(NAME);
					}
				}

				}
				break;
			case NAME:
				enterOuterAlt(_localctx, 2);
				{
				setState(1043);
				match(NAME);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_relationship_partContext extends ParserRuleContext {
		public Type_relationship_partContext type_relationship_part() {
			return getRuleContext(Type_relationship_partContext.class,0);
		}
		public Chaining_partContext chaining_part() {
			return getRuleContext(Chaining_partContext.class,0);
		}
		public Inverting_partContext inverting_part() {
			return getRuleContext(Inverting_partContext.class,0);
		}
		public Type_featuring_partContext type_featuring_part() {
			return getRuleContext(Type_featuring_partContext.class,0);
		}
		public Feature_relationship_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_relationship_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_relationship_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_relationship_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_relationship_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_relationship_partContext feature_relationship_part() throws RecognitionException {
		Feature_relationship_partContext _localctx = new Feature_relationship_partContext(_ctx, getState());
		enterRule(_localctx, 158, RULE_feature_relationship_part);
		try {
			setState(1050);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case KEYWORD_DIFFERENCES:
			case KEYWORD_DISJOINT:
			case KEYWORD_INTERSECTS:
			case KEYWORD_UNIONS:
				enterOuterAlt(_localctx, 1);
				{
				setState(1046);
				type_relationship_part();
				}
				break;
			case KEYWORD_CHAINS:
				enterOuterAlt(_localctx, 2);
				{
				setState(1047);
				chaining_part();
				}
				break;
			case KEYWORD_INVERSE:
				enterOuterAlt(_localctx, 3);
				{
				setState(1048);
				inverting_part();
				}
				break;
			case KEYWORD_FEATURED:
				enterOuterAlt(_localctx, 4);
				{
				setState(1049);
				type_featuring_part();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Chaining_partContext extends ParserRuleContext {
		public TerminalNode KEYWORD_CHAINS() { return getToken(KerMLParser.KEYWORD_CHAINS, 0); }
		public Owned_feature_chainingContext owned_feature_chaining() {
			return getRuleContext(Owned_feature_chainingContext.class,0);
		}
		public Feature_chainContext feature_chain() {
			return getRuleContext(Feature_chainContext.class,0);
		}
		public Chaining_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chaining_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterChaining_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitChaining_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitChaining_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Chaining_partContext chaining_part() throws RecognitionException {
		Chaining_partContext _localctx = new Chaining_partContext(_ctx, getState());
		enterRule(_localctx, 160, RULE_chaining_part);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1052);
			match(KEYWORD_CHAINS);
			setState(1055);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,96,_ctx) ) {
			case 1:
				{
				setState(1053);
				owned_feature_chaining();
				}
				break;
			case 2:
				{
				setState(1054);
				feature_chain();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Inverting_partContext extends ParserRuleContext {
		public TerminalNode KEYWORD_INVERSE() { return getToken(KerMLParser.KEYWORD_INVERSE, 0); }
		public TerminalNode KEYWORD_OF() { return getToken(KerMLParser.KEYWORD_OF, 0); }
		public Owned_feature_invertingContext owned_feature_inverting() {
			return getRuleContext(Owned_feature_invertingContext.class,0);
		}
		public Inverting_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inverting_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterInverting_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitInverting_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitInverting_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Inverting_partContext inverting_part() throws RecognitionException {
		Inverting_partContext _localctx = new Inverting_partContext(_ctx, getState());
		enterRule(_localctx, 162, RULE_inverting_part);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1057);
			match(KEYWORD_INVERSE);
			setState(1058);
			match(KEYWORD_OF);
			setState(1059);
			owned_feature_inverting();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_featuring_partContext extends ParserRuleContext {
		public TerminalNode KEYWORD_FEATURED() { return getToken(KerMLParser.KEYWORD_FEATURED, 0); }
		public TerminalNode KEYWORD_BY() { return getToken(KerMLParser.KEYWORD_BY, 0); }
		public List<Owned_type_featuringContext> owned_type_featuring() {
			return getRuleContexts(Owned_type_featuringContext.class);
		}
		public Owned_type_featuringContext owned_type_featuring(int i) {
			return getRuleContext(Owned_type_featuringContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Type_featuring_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_featuring_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_featuring_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_featuring_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_featuring_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_featuring_partContext type_featuring_part() throws RecognitionException {
		Type_featuring_partContext _localctx = new Type_featuring_partContext(_ctx, getState());
		enterRule(_localctx, 164, RULE_type_featuring_part);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1061);
			match(KEYWORD_FEATURED);
			setState(1062);
			match(KEYWORD_BY);
			setState(1063);
			owned_type_featuring();
			setState(1068);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(1064);
				match(SYMBOL_COMMA);
				setState(1065);
				owned_type_featuring();
				}
				}
				setState(1070);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_specialization_partContext extends ParserRuleContext {
		public List<Feature_specializationContext> feature_specialization() {
			return getRuleContexts(Feature_specializationContext.class);
		}
		public Feature_specializationContext feature_specialization(int i) {
			return getRuleContext(Feature_specializationContext.class,i);
		}
		public Multiplicity_partContext multiplicity_part() {
			return getRuleContext(Multiplicity_partContext.class,0);
		}
		public Feature_specialization_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_specialization_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_specialization_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_specialization_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_specialization_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_specialization_partContext feature_specialization_part() throws RecognitionException {
		Feature_specialization_partContext _localctx = new Feature_specialization_partContext(_ctx, getState());
		enterRule(_localctx, 166, RULE_feature_specialization_part);
		int _la;
		try {
			setState(1092);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case KEYWORD_IN:
			case KEYWORD_INOUT:
			case KEYWORD_OUT:
			case KEYWORD_REDEFINES:
			case KEYWORD_REFERENCES:
			case KEYWORD_SUBSETS:
			case KEYWORD_TYPED:
			case KEYWORD_CROSSES:
			case SYMBOL_TYPED_BY:
			case SYMBOL_SPECIALIZES:
			case SYMBOL_REFERENCES:
			case SYMBOL_REDEFINES:
			case SYMBOL_CROSSES:
				enterOuterAlt(_localctx, 1);
				{
				setState(1072); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(1071);
					feature_specialization();
					}
					}
					setState(1074); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==KEYWORD_IN || _la==KEYWORD_INOUT || ((((_la - 66)) & ~0x3f) == 0 && ((1L << (_la - 66)) & 13229392692512001L) != 0) );
				setState(1083);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_NONUNIQUE || _la==KEYWORD_ORDERED || _la==SYMBOL_SQUARE_BRACKET_OPEN) {
					{
					setState(1076);
					multiplicity_part();
					setState(1080);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==KEYWORD_IN || _la==KEYWORD_INOUT || ((((_la - 66)) & ~0x3f) == 0 && ((1L << (_la - 66)) & 13229392692512001L) != 0)) {
						{
						{
						setState(1077);
						feature_specialization();
						}
						}
						setState(1082);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				}
				break;
			case KEYWORD_NONUNIQUE:
			case KEYWORD_ORDERED:
			case SYMBOL_SQUARE_BRACKET_OPEN:
				enterOuterAlt(_localctx, 2);
				{
				setState(1085);
				multiplicity_part();
				setState(1089);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==KEYWORD_IN || _la==KEYWORD_INOUT || ((((_la - 66)) & ~0x3f) == 0 && ((1L << (_la - 66)) & 13229392692512001L) != 0)) {
					{
					{
					setState(1086);
					feature_specialization();
					}
					}
					setState(1091);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Multiplicity_partContext extends ParserRuleContext {
		public Multiplicity_boundsContext multiplicity_bounds() {
			return getRuleContext(Multiplicity_boundsContext.class,0);
		}
		public TerminalNode KEYWORD_ORDERED() { return getToken(KerMLParser.KEYWORD_ORDERED, 0); }
		public TerminalNode KEYWORD_NONUNIQUE() { return getToken(KerMLParser.KEYWORD_NONUNIQUE, 0); }
		public Multiplicity_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplicity_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMultiplicity_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMultiplicity_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMultiplicity_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Multiplicity_partContext multiplicity_part() throws RecognitionException {
		Multiplicity_partContext _localctx = new Multiplicity_partContext(_ctx, getState());
		enterRule(_localctx, 168, RULE_multiplicity_part);
		int _la;
		try {
			setState(1108);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,107,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1094);
				multiplicity_bounds();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1096);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SYMBOL_SQUARE_BRACKET_OPEN) {
					{
					setState(1095);
					multiplicity_bounds();
					}
				}

				setState(1106);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case KEYWORD_ORDERED:
					{
					setState(1098);
					match(KEYWORD_ORDERED);
					setState(1100);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==KEYWORD_NONUNIQUE) {
						{
						setState(1099);
						match(KEYWORD_NONUNIQUE);
						}
					}

					}
					break;
				case KEYWORD_NONUNIQUE:
					{
					setState(1102);
					match(KEYWORD_NONUNIQUE);
					setState(1104);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==KEYWORD_ORDERED) {
						{
						setState(1103);
						match(KEYWORD_ORDERED);
						}
					}

					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Multiplicity_modifierContext extends ParserRuleContext {
		public TerminalNode KEYWORD_ORDERED() { return getToken(KerMLParser.KEYWORD_ORDERED, 0); }
		public TerminalNode KEYWORD_NONUNIQUE() { return getToken(KerMLParser.KEYWORD_NONUNIQUE, 0); }
		public Multiplicity_modifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplicity_modifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMultiplicity_modifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMultiplicity_modifier(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMultiplicity_modifier(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Multiplicity_modifierContext multiplicity_modifier() throws RecognitionException {
		Multiplicity_modifierContext _localctx = new Multiplicity_modifierContext(_ctx, getState());
		enterRule(_localctx, 170, RULE_multiplicity_modifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1110);
			_la = _input.LA(1);
			if ( !(_la==KEYWORD_NONUNIQUE || _la==KEYWORD_ORDERED) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_specializationContext extends ParserRuleContext {
		public TypingsContext typings() {
			return getRuleContext(TypingsContext.class,0);
		}
		public SubsettingsContext subsettings() {
			return getRuleContext(SubsettingsContext.class,0);
		}
		public ReferencesContext references() {
			return getRuleContext(ReferencesContext.class,0);
		}
		public CrossesContext crosses() {
			return getRuleContext(CrossesContext.class,0);
		}
		public RedefinitionsContext redefinitions() {
			return getRuleContext(RedefinitionsContext.class,0);
		}
		public Feature_specializationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_specialization; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_specialization(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_specialization(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_specialization(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_specializationContext feature_specialization() throws RecognitionException {
		Feature_specializationContext _localctx = new Feature_specializationContext(_ctx, getState());
		enterRule(_localctx, 172, RULE_feature_specialization);
		try {
			setState(1117);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case KEYWORD_TYPED:
			case SYMBOL_TYPED_BY:
				enterOuterAlt(_localctx, 1);
				{
				setState(1112);
				typings();
				}
				break;
			case KEYWORD_SUBSETS:
			case SYMBOL_SPECIALIZES:
				enterOuterAlt(_localctx, 2);
				{
				setState(1113);
				subsettings();
				}
				break;
			case KEYWORD_REFERENCES:
			case SYMBOL_REFERENCES:
				enterOuterAlt(_localctx, 3);
				{
				setState(1114);
				references();
				}
				break;
			case KEYWORD_CROSSES:
			case SYMBOL_CROSSES:
				enterOuterAlt(_localctx, 4);
				{
				setState(1115);
				crosses();
				}
				break;
			case KEYWORD_IN:
			case KEYWORD_INOUT:
			case KEYWORD_OUT:
			case KEYWORD_REDEFINES:
			case SYMBOL_REDEFINES:
				enterOuterAlt(_localctx, 5);
				{
				setState(1116);
				redefinitions();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TypingsContext extends ParserRuleContext {
		public Typed_byContext typed_by() {
			return getRuleContext(Typed_byContext.class,0);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public List<Owned_feature_typingContext> owned_feature_typing() {
			return getRuleContexts(Owned_feature_typingContext.class);
		}
		public Owned_feature_typingContext owned_feature_typing(int i) {
			return getRuleContext(Owned_feature_typingContext.class,i);
		}
		public TypingsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typings; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterTypings(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitTypings(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitTypings(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TypingsContext typings() throws RecognitionException {
		TypingsContext _localctx = new TypingsContext(_ctx, getState());
		enterRule(_localctx, 174, RULE_typings);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1119);
			typed_by();
			setState(1124);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(1120);
				match(SYMBOL_COMMA);
				setState(1121);
				owned_feature_typing();
				}
				}
				setState(1126);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Typed_byContext extends ParserRuleContext {
		public Typed_by_operatorContext typed_by_operator() {
			return getRuleContext(Typed_by_operatorContext.class,0);
		}
		public Owned_feature_typingContext owned_feature_typing() {
			return getRuleContext(Owned_feature_typingContext.class,0);
		}
		public Typed_byContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typed_by; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterTyped_by(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitTyped_by(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitTyped_by(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Typed_byContext typed_by() throws RecognitionException {
		Typed_byContext _localctx = new Typed_byContext(_ctx, getState());
		enterRule(_localctx, 176, RULE_typed_by);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1127);
			typed_by_operator();
			setState(1128);
			owned_feature_typing();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SubsettingsContext extends ParserRuleContext {
		public SubsetsContext subsets() {
			return getRuleContext(SubsetsContext.class,0);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public List<Owned_subsettingContext> owned_subsetting() {
			return getRuleContexts(Owned_subsettingContext.class);
		}
		public Owned_subsettingContext owned_subsetting(int i) {
			return getRuleContext(Owned_subsettingContext.class,i);
		}
		public SubsettingsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_subsettings; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSubsettings(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSubsettings(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSubsettings(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SubsettingsContext subsettings() throws RecognitionException {
		SubsettingsContext _localctx = new SubsettingsContext(_ctx, getState());
		enterRule(_localctx, 178, RULE_subsettings);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1130);
			subsets();
			setState(1135);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(1131);
				match(SYMBOL_COMMA);
				setState(1132);
				owned_subsetting();
				}
				}
				setState(1137);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SubsetsContext extends ParserRuleContext {
		public Subsets_operatorContext subsets_operator() {
			return getRuleContext(Subsets_operatorContext.class,0);
		}
		public Owned_subsettingContext owned_subsetting() {
			return getRuleContext(Owned_subsettingContext.class,0);
		}
		public SubsetsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_subsets; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSubsets(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSubsets(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSubsets(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SubsetsContext subsets() throws RecognitionException {
		SubsetsContext _localctx = new SubsetsContext(_ctx, getState());
		enterRule(_localctx, 180, RULE_subsets);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1138);
			subsets_operator();
			setState(1139);
			owned_subsetting();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ReferencesContext extends ParserRuleContext {
		public References_operatorContext references_operator() {
			return getRuleContext(References_operatorContext.class,0);
		}
		public Owned_reference_subsettingContext owned_reference_subsetting() {
			return getRuleContext(Owned_reference_subsettingContext.class,0);
		}
		public ReferencesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_references; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterReferences(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitReferences(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitReferences(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ReferencesContext references() throws RecognitionException {
		ReferencesContext _localctx = new ReferencesContext(_ctx, getState());
		enterRule(_localctx, 182, RULE_references);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1141);
			references_operator();
			setState(1142);
			owned_reference_subsetting();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CrossesContext extends ParserRuleContext {
		public Crosses_operatorContext crosses_operator() {
			return getRuleContext(Crosses_operatorContext.class,0);
		}
		public Owned_cross_subsettingContext owned_cross_subsetting() {
			return getRuleContext(Owned_cross_subsettingContext.class,0);
		}
		public CrossesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_crosses; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterCrosses(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitCrosses(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitCrosses(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CrossesContext crosses() throws RecognitionException {
		CrossesContext _localctx = new CrossesContext(_ctx, getState());
		enterRule(_localctx, 184, RULE_crosses);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1144);
			crosses_operator();
			setState(1145);
			owned_cross_subsetting();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RedefinitionsContext extends ParserRuleContext {
		public RedefinesContext redefines() {
			return getRuleContext(RedefinesContext.class,0);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public List<Owned_redefinitionContext> owned_redefinition() {
			return getRuleContexts(Owned_redefinitionContext.class);
		}
		public Owned_redefinitionContext owned_redefinition(int i) {
			return getRuleContext(Owned_redefinitionContext.class,i);
		}
		public RedefinitionsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_redefinitions; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterRedefinitions(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitRedefinitions(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitRedefinitions(this);
			else return visitor.visitChildren(this);
		}
	}

	public final RedefinitionsContext redefinitions() throws RecognitionException {
		RedefinitionsContext _localctx = new RedefinitionsContext(_ctx, getState());
		enterRule(_localctx, 186, RULE_redefinitions);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1147);
			redefines();
			setState(1152);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(1148);
				match(SYMBOL_COMMA);
				setState(1149);
				owned_redefinition();
				}
				}
				setState(1154);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RedefinesContext extends ParserRuleContext {
		public Redefines_operatorContext redefines_operator() {
			return getRuleContext(Redefines_operatorContext.class,0);
		}
		public Owned_redefinitionContext owned_redefinition() {
			return getRuleContext(Owned_redefinitionContext.class,0);
		}
		public Feature_directionContext feature_direction() {
			return getRuleContext(Feature_directionContext.class,0);
		}
		public RedefinesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_redefines; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterRedefines(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitRedefines(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitRedefines(this);
			else return visitor.visitChildren(this);
		}
	}

	public final RedefinesContext redefines() throws RecognitionException {
		RedefinesContext _localctx = new RedefinesContext(_ctx, getState());
		enterRule(_localctx, 188, RULE_redefines);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1156);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 47)) & ~0x3f) == 0 && ((1L << (_la - 47)) & 524291L) != 0)) {
				{
				setState(1155);
				feature_direction();
				}
			}

			setState(1158);
			redefines_operator();
			setState(1159);
			owned_redefinition();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_typingContext extends ParserRuleContext {
		public TerminalNode KEYWORD_TYPING() { return getToken(KerMLParser.KEYWORD_TYPING, 0); }
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Typed_by_operatorContext typed_by_operator() {
			return getRuleContext(Typed_by_operatorContext.class,0);
		}
		public General_typeContext general_type() {
			return getRuleContext(General_typeContext.class,0);
		}
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public TerminalNode KEYWORD_SPECIALIZATION() { return getToken(KerMLParser.KEYWORD_SPECIALIZATION, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public Feature_typingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_typing; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_typing(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_typing(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_typing(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_typingContext feature_typing() throws RecognitionException {
		Feature_typingContext _localctx = new Feature_typingContext(_ctx, getState());
		enterRule(_localctx, 190, RULE_feature_typing);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1163);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_SPECIALIZATION) {
				{
				setState(1161);
				match(KEYWORD_SPECIALIZATION);
				setState(1162);
				identification();
				}
			}

			setState(1165);
			match(KEYWORD_TYPING);
			setState(1166);
			qualified_name();
			setState(1167);
			typed_by_operator();
			setState(1168);
			general_type();
			setState(1169);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_feature_typingContext extends ParserRuleContext {
		public General_typeContext general_type() {
			return getRuleContext(General_typeContext.class,0);
		}
		public Owned_feature_typingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_feature_typing; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_feature_typing(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_feature_typing(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_feature_typing(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_feature_typingContext owned_feature_typing() throws RecognitionException {
		Owned_feature_typingContext _localctx = new Owned_feature_typingContext(_ctx, getState());
		enterRule(_localctx, 192, RULE_owned_feature_typing);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1171);
			general_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SubsettingContext extends ParserRuleContext {
		public Specific_typeContext specific_type() {
			return getRuleContext(Specific_typeContext.class,0);
		}
		public Subsets_operatorContext subsets_operator() {
			return getRuleContext(Subsets_operatorContext.class,0);
		}
		public General_typeContext general_type() {
			return getRuleContext(General_typeContext.class,0);
		}
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public TerminalNode KEYWORD_SPECIALIZATION() { return getToken(KerMLParser.KEYWORD_SPECIALIZATION, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public TerminalNode KEYWORD_SUBSET() { return getToken(KerMLParser.KEYWORD_SUBSET, 0); }
		public Multiplicity_partContext multiplicity_part() {
			return getRuleContext(Multiplicity_partContext.class,0);
		}
		public SubsettingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_subsetting; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSubsetting(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSubsetting(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSubsetting(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SubsettingContext subsetting() throws RecognitionException {
		SubsettingContext _localctx = new SubsettingContext(_ctx, getState());
		enterRule(_localctx, 194, RULE_subsetting);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1175);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_SPECIALIZATION) {
				{
				setState(1173);
				match(KEYWORD_SPECIALIZATION);
				setState(1174);
				identification();
				}
			}

			setState(1178);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_SUBSET) {
				{
				setState(1177);
				match(KEYWORD_SUBSET);
				}
			}

			setState(1180);
			specific_type();
			setState(1181);
			subsets_operator();
			setState(1182);
			general_type();
			setState(1184);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_NONUNIQUE || _la==KEYWORD_ORDERED || _la==SYMBOL_SQUARE_BRACKET_OPEN) {
				{
				setState(1183);
				multiplicity_part();
				}
			}

			setState(1186);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_subsettingContext extends ParserRuleContext {
		public General_typeContext general_type() {
			return getRuleContext(General_typeContext.class,0);
		}
		public Owned_subsettingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_subsetting; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_subsetting(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_subsetting(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_subsetting(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_subsettingContext owned_subsetting() throws RecognitionException {
		Owned_subsettingContext _localctx = new Owned_subsettingContext(_ctx, getState());
		enterRule(_localctx, 196, RULE_owned_subsetting);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1188);
			general_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_reference_subsettingContext extends ParserRuleContext {
		public General_typeContext general_type() {
			return getRuleContext(General_typeContext.class,0);
		}
		public Owned_reference_subsettingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_reference_subsetting; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_reference_subsetting(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_reference_subsetting(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_reference_subsetting(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_reference_subsettingContext owned_reference_subsetting() throws RecognitionException {
		Owned_reference_subsettingContext _localctx = new Owned_reference_subsettingContext(_ctx, getState());
		enterRule(_localctx, 198, RULE_owned_reference_subsetting);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1190);
			general_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_cross_subsettingContext extends ParserRuleContext {
		public General_typeContext general_type() {
			return getRuleContext(General_typeContext.class,0);
		}
		public Owned_cross_subsettingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_cross_subsetting; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_cross_subsetting(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_cross_subsetting(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_cross_subsetting(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_cross_subsettingContext owned_cross_subsetting() throws RecognitionException {
		Owned_cross_subsettingContext _localctx = new Owned_cross_subsettingContext(_ctx, getState());
		enterRule(_localctx, 200, RULE_owned_cross_subsetting);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1192);
			general_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RedefinitionContext extends ParserRuleContext {
		public Redefines_operatorContext redefines_operator() {
			return getRuleContext(Redefines_operatorContext.class,0);
		}
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public Feature_directionContext feature_direction() {
			return getRuleContext(Feature_directionContext.class,0);
		}
		public TerminalNode KEYWORD_SPECIALIZATION() { return getToken(KerMLParser.KEYWORD_SPECIALIZATION, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public TerminalNode KEYWORD_REDEFINITION() { return getToken(KerMLParser.KEYWORD_REDEFINITION, 0); }
		public Specific_typeContext specific_type() {
			return getRuleContext(Specific_typeContext.class,0);
		}
		public Typed_byContext typed_by() {
			return getRuleContext(Typed_byContext.class,0);
		}
		public Multiplicity_partContext multiplicity_part() {
			return getRuleContext(Multiplicity_partContext.class,0);
		}
		public SubsetsContext subsets() {
			return getRuleContext(SubsetsContext.class,0);
		}
		public Feature_assignmentContext feature_assignment() {
			return getRuleContext(Feature_assignmentContext.class,0);
		}
		public RedefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_redefinition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterRedefinition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitRedefinition(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitRedefinition(this);
			else return visitor.visitChildren(this);
		}
	}

	public final RedefinitionContext redefinition() throws RecognitionException {
		RedefinitionContext _localctx = new RedefinitionContext(_ctx, getState());
		enterRule(_localctx, 202, RULE_redefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1195);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 47)) & ~0x3f) == 0 && ((1L << (_la - 47)) & 524291L) != 0)) {
				{
				setState(1194);
				feature_direction();
				}
			}

			setState(1199);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_SPECIALIZATION) {
				{
				setState(1197);
				match(KEYWORD_SPECIALIZATION);
				setState(1198);
				identification();
				}
			}

			setState(1203);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_REDEFINITION) {
				{
				setState(1201);
				match(KEYWORD_REDEFINITION);
				setState(1202);
				specific_type();
				}
			}

			setState(1205);
			redefines_operator();
			setState(1206);
			qualified_name();
			setState(1208);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_TYPED || _la==SYMBOL_TYPED_BY) {
				{
				setState(1207);
				typed_by();
				}
			}

			setState(1211);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_NONUNIQUE || _la==KEYWORD_ORDERED || _la==SYMBOL_SQUARE_BRACKET_OPEN) {
				{
				setState(1210);
				multiplicity_part();
				}
			}

			setState(1214);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_SUBSETS || _la==SYMBOL_SPECIALIZES) {
				{
				setState(1213);
				subsets();
				}
			}

			setState(1217);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_ASSIGN) {
				{
				setState(1216);
				feature_assignment();
				}
			}

			setState(1219);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_redefinitionContext extends ParserRuleContext {
		public General_typeContext general_type() {
			return getRuleContext(General_typeContext.class,0);
		}
		public Owned_redefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_redefinition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_redefinition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_redefinition(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_redefinition(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_redefinitionContext owned_redefinition() throws RecognitionException {
		Owned_redefinitionContext _localctx = new Owned_redefinitionContext(_ctx, getState());
		enterRule(_localctx, 204, RULE_owned_redefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1221);
			general_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_feature_chainContext extends ParserRuleContext {
		public Feature_chainContext feature_chain() {
			return getRuleContext(Feature_chainContext.class,0);
		}
		public Owned_feature_chainContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_feature_chain; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_feature_chain(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_feature_chain(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_feature_chain(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_feature_chainContext owned_feature_chain() throws RecognitionException {
		Owned_feature_chainContext _localctx = new Owned_feature_chainContext(_ctx, getState());
		enterRule(_localctx, 206, RULE_owned_feature_chain);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1223);
			feature_chain();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_chainContext extends ParserRuleContext {
		public List<Owned_feature_chainingContext> owned_feature_chaining() {
			return getRuleContexts(Owned_feature_chainingContext.class);
		}
		public Owned_feature_chainingContext owned_feature_chaining(int i) {
			return getRuleContext(Owned_feature_chainingContext.class,i);
		}
		public List<TerminalNode> SYMBOL_DOT() { return getTokens(KerMLParser.SYMBOL_DOT); }
		public TerminalNode SYMBOL_DOT(int i) {
			return getToken(KerMLParser.SYMBOL_DOT, i);
		}
		public Feature_chainContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_chain; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_chain(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_chain(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_chain(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_chainContext feature_chain() throws RecognitionException {
		Feature_chainContext _localctx = new Feature_chainContext(_ctx, getState());
		enterRule(_localctx, 208, RULE_feature_chain);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1225);
			owned_feature_chaining();
			setState(1228); 
			_errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					{
					setState(1226);
					match(SYMBOL_DOT);
					setState(1227);
					owned_feature_chaining();
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(1230); 
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,124,_ctx);
			} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_feature_chainingContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Owned_feature_chainingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_feature_chaining; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_feature_chaining(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_feature_chaining(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_feature_chaining(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_feature_chainingContext owned_feature_chaining() throws RecognitionException {
		Owned_feature_chainingContext _localctx = new Owned_feature_chainingContext(_ctx, getState());
		enterRule(_localctx, 210, RULE_owned_feature_chaining);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1232);
			qualified_name();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_invertingContext extends ParserRuleContext {
		public TerminalNode KEYWORD_INVERSE() { return getToken(KerMLParser.KEYWORD_INVERSE, 0); }
		public TerminalNode KEYWORD_OF() { return getToken(KerMLParser.KEYWORD_OF, 0); }
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public List<Qualified_nameContext> qualified_name() {
			return getRuleContexts(Qualified_nameContext.class);
		}
		public Qualified_nameContext qualified_name(int i) {
			return getRuleContext(Qualified_nameContext.class,i);
		}
		public List<Owned_feature_chainContext> owned_feature_chain() {
			return getRuleContexts(Owned_feature_chainContext.class);
		}
		public Owned_feature_chainContext owned_feature_chain(int i) {
			return getRuleContext(Owned_feature_chainContext.class,i);
		}
		public TerminalNode KEYWORD_INVERTING() { return getToken(KerMLParser.KEYWORD_INVERTING, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public Feature_invertingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_inverting; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_inverting(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_inverting(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_inverting(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_invertingContext feature_inverting() throws RecognitionException {
		Feature_invertingContext _localctx = new Feature_invertingContext(_ctx, getState());
		enterRule(_localctx, 212, RULE_feature_inverting);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1236);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_INVERTING) {
				{
				setState(1234);
				match(KEYWORD_INVERTING);
				setState(1235);
				identification();
				}
			}

			setState(1238);
			match(KEYWORD_INVERSE);
			setState(1241);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,126,_ctx) ) {
			case 1:
				{
				setState(1239);
				qualified_name();
				}
				break;
			case 2:
				{
				setState(1240);
				owned_feature_chain();
				}
				break;
			}
			setState(1243);
			match(KEYWORD_OF);
			setState(1246);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,127,_ctx) ) {
			case 1:
				{
				setState(1244);
				qualified_name();
				}
				break;
			case 2:
				{
				setState(1245);
				owned_feature_chain();
				}
				break;
			}
			setState(1248);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_feature_invertingContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Owned_feature_chainContext owned_feature_chain() {
			return getRuleContext(Owned_feature_chainContext.class,0);
		}
		public Owned_feature_invertingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_feature_inverting; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_feature_inverting(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_feature_inverting(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_feature_inverting(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_feature_invertingContext owned_feature_inverting() throws RecognitionException {
		Owned_feature_invertingContext _localctx = new Owned_feature_invertingContext(_ctx, getState());
		enterRule(_localctx, 214, RULE_owned_feature_inverting);
		try {
			setState(1252);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,128,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1250);
				qualified_name();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1251);
				owned_feature_chain();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_featuringContext extends ParserRuleContext {
		public TerminalNode KEYWORD_FEATURING() { return getToken(KerMLParser.KEYWORD_FEATURING, 0); }
		public List<Qualified_nameContext> qualified_name() {
			return getRuleContexts(Qualified_nameContext.class);
		}
		public Qualified_nameContext qualified_name(int i) {
			return getRuleContext(Qualified_nameContext.class,i);
		}
		public TerminalNode KEYWORD_BY() { return getToken(KerMLParser.KEYWORD_BY, 0); }
		public Relationship_bodyContext relationship_body() {
			return getRuleContext(Relationship_bodyContext.class,0);
		}
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public TerminalNode KEYWORD_OF() { return getToken(KerMLParser.KEYWORD_OF, 0); }
		public Type_featuringContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_featuring; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_featuring(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_featuring(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_featuring(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_featuringContext type_featuring() throws RecognitionException {
		Type_featuringContext _localctx = new Type_featuringContext(_ctx, getState());
		enterRule(_localctx, 216, RULE_type_featuring);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1254);
			match(KEYWORD_FEATURING);
			setState(1258);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,129,_ctx) ) {
			case 1:
				{
				setState(1255);
				identification();
				setState(1256);
				match(KEYWORD_OF);
				}
				break;
			}
			setState(1260);
			qualified_name();
			setState(1261);
			match(KEYWORD_BY);
			setState(1262);
			qualified_name();
			setState(1263);
			relationship_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_type_featuringContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Owned_type_featuringContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_type_featuring; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_type_featuring(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_type_featuring(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_type_featuring(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_type_featuringContext owned_type_featuring() throws RecognitionException {
		Owned_type_featuringContext _localctx = new Owned_type_featuringContext(_ctx, getState());
		enterRule(_localctx, 218, RULE_owned_type_featuring);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1265);
			qualified_name();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Data_typeContext extends ParserRuleContext {
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_DATATYPE() { return getToken(KerMLParser.KEYWORD_DATATYPE, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Data_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_data_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterData_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitData_type(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitData_type(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Data_typeContext data_type() throws RecognitionException {
		Data_typeContext _localctx = new Data_typeContext(_ctx, getState());
		enterRule(_localctx, 220, RULE_data_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1267);
			type_prefix();
			setState(1268);
			match(KEYWORD_DATATYPE);
			setState(1269);
			classifier_declaration();
			setState(1270);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ClassContext extends ParserRuleContext {
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_CLASS() { return getToken(KerMLParser.KEYWORD_CLASS, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public ClassContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_class; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterClass(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitClass(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitClass(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ClassContext class_() throws RecognitionException {
		ClassContext _localctx = new ClassContext(_ctx, getState());
		enterRule(_localctx, 222, RULE_class);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1272);
			type_prefix();
			setState(1273);
			match(KEYWORD_CLASS);
			setState(1274);
			classifier_declaration();
			setState(1275);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StructureContext extends ParserRuleContext {
		public TerminalNode KEYWORD_STRUCT() { return getToken(KerMLParser.KEYWORD_STRUCT, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public StructureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_structure; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterStructure(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitStructure(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitStructure(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StructureContext structure() throws RecognitionException {
		StructureContext _localctx = new StructureContext(_ctx, getState());
		enterRule(_localctx, 224, RULE_structure);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1278);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,130,_ctx) ) {
			case 1:
				{
				setState(1277);
				type_prefix();
				}
				break;
			}
			setState(1280);
			match(KEYWORD_STRUCT);
			setState(1281);
			classifier_declaration();
			setState(1282);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AssociationContext extends ParserRuleContext {
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_ASSOC() { return getToken(KerMLParser.KEYWORD_ASSOC, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public AssociationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_association; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterAssociation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitAssociation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitAssociation(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AssociationContext association() throws RecognitionException {
		AssociationContext _localctx = new AssociationContext(_ctx, getState());
		enterRule(_localctx, 226, RULE_association);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1284);
			type_prefix();
			setState(1285);
			match(KEYWORD_ASSOC);
			setState(1286);
			classifier_declaration();
			setState(1287);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Association_structureContext extends ParserRuleContext {
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_ASSOC() { return getToken(KerMLParser.KEYWORD_ASSOC, 0); }
		public TerminalNode KEYWORD_STRUCT() { return getToken(KerMLParser.KEYWORD_STRUCT, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Association_structureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_association_structure; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterAssociation_structure(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitAssociation_structure(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitAssociation_structure(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Association_structureContext association_structure() throws RecognitionException {
		Association_structureContext _localctx = new Association_structureContext(_ctx, getState());
		enterRule(_localctx, 228, RULE_association_structure);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1289);
			type_prefix();
			setState(1290);
			match(KEYWORD_ASSOC);
			setState(1291);
			match(KEYWORD_STRUCT);
			setState(1292);
			classifier_declaration();
			setState(1293);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConnectorContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_CONNECTOR() { return getToken(KerMLParser.KEYWORD_CONNECTOR, 0); }
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Connector_declarationContext connector_declaration() {
			return getRuleContext(Connector_declarationContext.class,0);
		}
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public ConnectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_connector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterConnector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitConnector(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitConnector(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ConnectorContext connector() throws RecognitionException {
		ConnectorContext _localctx = new ConnectorContext(_ctx, getState());
		enterRule(_localctx, 230, RULE_connector);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1295);
			feature_prefix();
			setState(1296);
			match(KEYWORD_CONNECTOR);
			setState(1304);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,133,_ctx) ) {
			case 1:
				{
				setState(1298);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1153343717072175120L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & 611926736943188483L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
					{
					setState(1297);
					feature_declaration();
					}
				}

				setState(1301);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
					{
					setState(1300);
					value_part();
					}
				}

				}
				break;
			case 2:
				{
				setState(1303);
				connector_declaration();
				}
				break;
			}
			setState(1306);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Connector_declarationContext extends ParserRuleContext {
		public Binary_connector_declarationContext binary_connector_declaration() {
			return getRuleContext(Binary_connector_declarationContext.class,0);
		}
		public Nary_connector_declarationContext nary_connector_declaration() {
			return getRuleContext(Nary_connector_declarationContext.class,0);
		}
		public Connector_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_connector_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterConnector_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitConnector_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitConnector_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Connector_declarationContext connector_declaration() throws RecognitionException {
		Connector_declarationContext _localctx = new Connector_declarationContext(_ctx, getState());
		enterRule(_localctx, 232, RULE_connector_declaration);
		try {
			setState(1310);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,134,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1308);
				binary_connector_declaration();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1309);
				nary_connector_declaration();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Binary_connector_declarationContext extends ParserRuleContext {
		public List<Connector_end_memberContext> connector_end_member() {
			return getRuleContexts(Connector_end_memberContext.class);
		}
		public Connector_end_memberContext connector_end_member(int i) {
			return getRuleContext(Connector_end_memberContext.class,i);
		}
		public TerminalNode KEYWORD_TO() { return getToken(KerMLParser.KEYWORD_TO, 0); }
		public TerminalNode KEYWORD_FROM() { return getToken(KerMLParser.KEYWORD_FROM, 0); }
		public TerminalNode KEYWORD_ALL() { return getToken(KerMLParser.KEYWORD_ALL, 0); }
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Binary_connector_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_binary_connector_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBinary_connector_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBinary_connector_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBinary_connector_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Binary_connector_declarationContext binary_connector_declaration() throws RecognitionException {
		Binary_connector_declarationContext _localctx = new Binary_connector_declarationContext(_ctx, getState());
		enterRule(_localctx, 234, RULE_binary_connector_declaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1320);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,137,_ctx) ) {
			case 1:
				{
				setState(1313);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1153343717072175120L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & 611926736943188483L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
					{
					setState(1312);
					feature_declaration();
					}
				}

				setState(1315);
				match(KEYWORD_FROM);
				}
				break;
			case 2:
				{
				setState(1316);
				match(KEYWORD_ALL);
				setState(1318);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_FROM) {
					{
					setState(1317);
					match(KEYWORD_FROM);
					}
				}

				}
				break;
			}
			setState(1322);
			connector_end_member();
			setState(1323);
			match(KEYWORD_TO);
			setState(1324);
			connector_end_member();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Nary_connector_declarationContext extends ParserRuleContext {
		public TerminalNode SYMBOL_ROUND_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_OPEN, 0); }
		public List<Connector_end_memberContext> connector_end_member() {
			return getRuleContexts(Connector_end_memberContext.class);
		}
		public Connector_end_memberContext connector_end_member(int i) {
			return getRuleContext(Connector_end_memberContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public TerminalNode SYMBOL_ROUND_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_CLOSE, 0); }
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Nary_connector_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nary_connector_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNary_connector_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNary_connector_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNary_connector_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Nary_connector_declarationContext nary_connector_declaration() throws RecognitionException {
		Nary_connector_declarationContext _localctx = new Nary_connector_declarationContext(_ctx, getState());
		enterRule(_localctx, 236, RULE_nary_connector_declaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1327);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1153343717072175120L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & 611926736943188483L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
				{
				setState(1326);
				feature_declaration();
				}
			}

			setState(1329);
			match(SYMBOL_ROUND_BRACKET_OPEN);
			setState(1330);
			connector_end_member();
			setState(1331);
			match(SYMBOL_COMMA);
			setState(1332);
			connector_end_member();
			setState(1337);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(1333);
				match(SYMBOL_COMMA);
				setState(1334);
				connector_end_member();
				}
				}
				setState(1339);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(1340);
			match(SYMBOL_ROUND_BRACKET_CLOSE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Connector_end_memberContext extends ParserRuleContext {
		public Connector_endContext connector_end() {
			return getRuleContext(Connector_endContext.class,0);
		}
		public Connector_end_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_connector_end_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterConnector_end_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitConnector_end_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitConnector_end_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Connector_end_memberContext connector_end_member() throws RecognitionException {
		Connector_end_memberContext _localctx = new Connector_end_memberContext(_ctx, getState());
		enterRule(_localctx, 238, RULE_connector_end_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1342);
			connector_end();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Connector_endContext extends ParserRuleContext {
		public Owned_reference_subsettingContext owned_reference_subsetting() {
			return getRuleContext(Owned_reference_subsettingContext.class,0);
		}
		public Owned_cross_multiplicity_memberContext owned_cross_multiplicity_member() {
			return getRuleContext(Owned_cross_multiplicity_memberContext.class,0);
		}
		public TerminalNode NAME() { return getToken(KerMLParser.NAME, 0); }
		public References_operatorContext references_operator() {
			return getRuleContext(References_operatorContext.class,0);
		}
		public Connector_endContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_connector_end; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterConnector_end(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitConnector_end(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitConnector_end(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Connector_endContext connector_end() throws RecognitionException {
		Connector_endContext _localctx = new Connector_endContext(_ctx, getState());
		enterRule(_localctx, 240, RULE_connector_end);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1345);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_SQUARE_BRACKET_OPEN) {
				{
				setState(1344);
				owned_cross_multiplicity_member();
				}
			}

			setState(1349);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,141,_ctx) ) {
			case 1:
				{
				setState(1347);
				match(NAME);
				setState(1348);
				references_operator();
				}
				break;
			}
			setState(1351);
			owned_reference_subsetting();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_cross_multiplicity_memberContext extends ParserRuleContext {
		public Owned_cross_multiplicityContext owned_cross_multiplicity() {
			return getRuleContext(Owned_cross_multiplicityContext.class,0);
		}
		public Owned_cross_multiplicity_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_cross_multiplicity_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_cross_multiplicity_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_cross_multiplicity_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_cross_multiplicity_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_cross_multiplicity_memberContext owned_cross_multiplicity_member() throws RecognitionException {
		Owned_cross_multiplicity_memberContext _localctx = new Owned_cross_multiplicity_memberContext(_ctx, getState());
		enterRule(_localctx, 242, RULE_owned_cross_multiplicity_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1353);
			owned_cross_multiplicity();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_cross_multiplicityContext extends ParserRuleContext {
		public Owned_multiplicityContext owned_multiplicity() {
			return getRuleContext(Owned_multiplicityContext.class,0);
		}
		public Owned_cross_multiplicityContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_cross_multiplicity; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_cross_multiplicity(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_cross_multiplicity(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_cross_multiplicity(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_cross_multiplicityContext owned_cross_multiplicity() throws RecognitionException {
		Owned_cross_multiplicityContext _localctx = new Owned_cross_multiplicityContext(_ctx, getState());
		enterRule(_localctx, 244, RULE_owned_cross_multiplicity);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1355);
			owned_multiplicity();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Binding_connectorContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_BINDING() { return getToken(KerMLParser.KEYWORD_BINDING, 0); }
		public Binding_connector_declarationContext binding_connector_declaration() {
			return getRuleContext(Binding_connector_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Binding_connectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_binding_connector; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBinding_connector(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBinding_connector(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBinding_connector(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Binding_connectorContext binding_connector() throws RecognitionException {
		Binding_connectorContext _localctx = new Binding_connectorContext(_ctx, getState());
		enterRule(_localctx, 246, RULE_binding_connector);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1357);
			feature_prefix();
			setState(1358);
			match(KEYWORD_BINDING);
			setState(1359);
			binding_connector_declaration();
			setState(1360);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Binding_connector_declarationContext extends ParserRuleContext {
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public TerminalNode KEYWORD_OF() { return getToken(KerMLParser.KEYWORD_OF, 0); }
		public List<Connector_end_memberContext> connector_end_member() {
			return getRuleContexts(Connector_end_memberContext.class);
		}
		public Connector_end_memberContext connector_end_member(int i) {
			return getRuleContext(Connector_end_memberContext.class,i);
		}
		public TerminalNode SYMBOL_ASSIGN() { return getToken(KerMLParser.SYMBOL_ASSIGN, 0); }
		public TerminalNode KEYWORD_ALL() { return getToken(KerMLParser.KEYWORD_ALL, 0); }
		public Binding_connector_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_binding_connector_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBinding_connector_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBinding_connector_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBinding_connector_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Binding_connector_declarationContext binding_connector_declaration() throws RecognitionException {
		Binding_connector_declarationContext _localctx = new Binding_connector_declarationContext(_ctx, getState());
		enterRule(_localctx, 248, RULE_binding_connector_declaration);
		int _la;
		try {
			setState(1382);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,146,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1362);
				feature_declaration();
				setState(1368);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_OF) {
					{
					setState(1363);
					match(KEYWORD_OF);
					setState(1364);
					connector_end_member();
					setState(1365);
					match(SYMBOL_ASSIGN);
					setState(1366);
					connector_end_member();
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				{
				setState(1371);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_ALL) {
					{
					setState(1370);
					match(KEYWORD_ALL);
					}
				}

				setState(1380);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_OF || _la==SYMBOL_SQUARE_BRACKET_OPEN || _la==NAME) {
					{
					setState(1374);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==KEYWORD_OF) {
						{
						setState(1373);
						match(KEYWORD_OF);
						}
					}

					setState(1376);
					connector_end_member();
					setState(1377);
					match(SYMBOL_ASSIGN);
					setState(1378);
					connector_end_member();
					}
				}

				}
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SuccessionContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_SUCCESSION() { return getToken(KerMLParser.KEYWORD_SUCCESSION, 0); }
		public Succession_declarationContext succession_declaration() {
			return getRuleContext(Succession_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public SuccessionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_succession; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSuccession(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSuccession(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSuccession(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SuccessionContext succession() throws RecognitionException {
		SuccessionContext _localctx = new SuccessionContext(_ctx, getState());
		enterRule(_localctx, 250, RULE_succession);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1384);
			feature_prefix();
			setState(1385);
			match(KEYWORD_SUCCESSION);
			setState(1386);
			succession_declaration();
			setState(1387);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Succession_declarationContext extends ParserRuleContext {
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public TerminalNode KEYWORD_FIRST() { return getToken(KerMLParser.KEYWORD_FIRST, 0); }
		public List<Connector_end_memberContext> connector_end_member() {
			return getRuleContexts(Connector_end_memberContext.class);
		}
		public Connector_end_memberContext connector_end_member(int i) {
			return getRuleContext(Connector_end_memberContext.class,i);
		}
		public TerminalNode KEYWORD_THEN() { return getToken(KerMLParser.KEYWORD_THEN, 0); }
		public TerminalNode KEYWORD_ALL() { return getToken(KerMLParser.KEYWORD_ALL, 0); }
		public Succession_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_succession_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSuccession_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSuccession_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSuccession_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Succession_declarationContext succession_declaration() throws RecognitionException {
		Succession_declarationContext _localctx = new Succession_declarationContext(_ctx, getState());
		enterRule(_localctx, 252, RULE_succession_declaration);
		int _la;
		try {
			setState(1409);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,151,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1389);
				feature_declaration();
				setState(1395);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_FIRST) {
					{
					setState(1390);
					match(KEYWORD_FIRST);
					setState(1391);
					connector_end_member();
					setState(1392);
					match(KEYWORD_THEN);
					setState(1393);
					connector_end_member();
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				{
				setState(1398);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_ALL) {
					{
					setState(1397);
					match(KEYWORD_ALL);
					}
				}

				setState(1407);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_FIRST || _la==SYMBOL_SQUARE_BRACKET_OPEN || _la==NAME) {
					{
					setState(1401);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==KEYWORD_FIRST) {
						{
						setState(1400);
						match(KEYWORD_FIRST);
						}
					}

					setState(1403);
					connector_end_member();
					setState(1404);
					match(KEYWORD_THEN);
					setState(1405);
					connector_end_member();
					}
				}

				}
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BehaviorContext extends ParserRuleContext {
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_BEHAVIOR() { return getToken(KerMLParser.KEYWORD_BEHAVIOR, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public BehaviorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_behavior; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBehavior(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBehavior(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBehavior(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BehaviorContext behavior() throws RecognitionException {
		BehaviorContext _localctx = new BehaviorContext(_ctx, getState());
		enterRule(_localctx, 254, RULE_behavior);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1411);
			type_prefix();
			setState(1412);
			match(KEYWORD_BEHAVIOR);
			setState(1413);
			classifier_declaration();
			setState(1414);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StepContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_STEP() { return getToken(KerMLParser.KEYWORD_STEP, 0); }
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public StepContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_step; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterStep(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitStep(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitStep(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StepContext step() throws RecognitionException {
		StepContext _localctx = new StepContext(_ctx, getState());
		enterRule(_localctx, 256, RULE_step);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1416);
			feature_prefix();
			setState(1417);
			match(KEYWORD_STEP);
			setState(1418);
			feature_declaration();
			setState(1420);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
				{
				setState(1419);
				value_part();
				}
			}

			setState(1422);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionContext extends ParserRuleContext {
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_FUNCTION() { return getToken(KerMLParser.KEYWORD_FUNCTION, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Function_bodyContext function_body() {
			return getRuleContext(Function_bodyContext.class,0);
		}
		public FunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFunction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFunction(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFunction(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionContext function() throws RecognitionException {
		FunctionContext _localctx = new FunctionContext(_ctx, getState());
		enterRule(_localctx, 258, RULE_function);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1424);
			type_prefix();
			setState(1425);
			match(KEYWORD_FUNCTION);
			setState(1426);
			classifier_declaration();
			setState(1427);
			function_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Function_bodyContext extends ParserRuleContext {
		public TerminalNode SYMBOL_STATEMENT_DELIMITER() { return getToken(KerMLParser.SYMBOL_STATEMENT_DELIMITER, 0); }
		public TerminalNode SYMBOL_CURLY_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_OPEN, 0); }
		public Function_body_partContext function_body_part() {
			return getRuleContext(Function_body_partContext.class,0);
		}
		public TerminalNode SYMBOL_CURLY_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_CLOSE, 0); }
		public Function_bodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function_body; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFunction_body(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFunction_body(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFunction_body(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Function_bodyContext function_body() throws RecognitionException {
		Function_bodyContext _localctx = new Function_bodyContext(_ctx, getState());
		enterRule(_localctx, 260, RULE_function_body);
		try {
			setState(1434);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_STATEMENT_DELIMITER:
				enterOuterAlt(_localctx, 1);
				{
				setState(1429);
				match(SYMBOL_STATEMENT_DELIMITER);
				}
				break;
			case SYMBOL_CURLY_BRACKET_OPEN:
				enterOuterAlt(_localctx, 2);
				{
				setState(1430);
				match(SYMBOL_CURLY_BRACKET_OPEN);
				setState(1431);
				function_body_part();
				setState(1432);
				match(SYMBOL_CURLY_BRACKET_CLOSE);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Function_body_partContext extends ParserRuleContext {
		public List<Type_body_elementContext> type_body_element() {
			return getRuleContexts(Type_body_elementContext.class);
		}
		public Type_body_elementContext type_body_element(int i) {
			return getRuleContext(Type_body_elementContext.class,i);
		}
		public List<Return_feature_memberContext> return_feature_member() {
			return getRuleContexts(Return_feature_memberContext.class);
		}
		public Return_feature_memberContext return_feature_member(int i) {
			return getRuleContext(Return_feature_memberContext.class,i);
		}
		public Result_expression_memberContext result_expression_member() {
			return getRuleContext(Result_expression_memberContext.class,0);
		}
		public Function_body_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function_body_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFunction_body_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFunction_body_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFunction_body_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Function_body_partContext function_body_part() throws RecognitionException {
		Function_body_partContext _localctx = new Function_body_partContext(_ctx, getState());
		enterRule(_localctx, 262, RULE_function_body_part);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1440);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,155,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					setState(1438);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,154,_ctx) ) {
					case 1:
						{
						setState(1436);
						type_body_element();
						}
						break;
					case 2:
						{
						setState(1437);
						return_feature_member();
						}
						break;
					}
					} 
				}
				setState(1442);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,155,_ctx);
			}
			setState(1444);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 6926549425330323536L) != 0) || ((((_la - 70)) & ~0x3f) == 0 && ((1L << (_la - 70)) & 150030577814208519L) != 0) || ((((_la - 134)) & ~0x3f) == 0 && ((1L << (_la - 134)) & 59768851L) != 0)) {
				{
				setState(1443);
				result_expression_member();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Return_feature_memberContext extends ParserRuleContext {
		public Member_prefixContext member_prefix() {
			return getRuleContext(Member_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_RETURN() { return getToken(KerMLParser.KEYWORD_RETURN, 0); }
		public Feature_elementContext feature_element() {
			return getRuleContext(Feature_elementContext.class,0);
		}
		public Return_feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_return_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterReturn_feature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitReturn_feature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitReturn_feature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Return_feature_memberContext return_feature_member() throws RecognitionException {
		Return_feature_memberContext _localctx = new Return_feature_memberContext(_ctx, getState());
		enterRule(_localctx, 264, RULE_return_feature_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1446);
			member_prefix();
			setState(1447);
			match(KEYWORD_RETURN);
			setState(1448);
			feature_element();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Result_expression_memberContext extends ParserRuleContext {
		public Member_prefixContext member_prefix() {
			return getRuleContext(Member_prefixContext.class,0);
		}
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public Result_expression_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_result_expression_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterResult_expression_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitResult_expression_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitResult_expression_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Result_expression_memberContext result_expression_member() throws RecognitionException {
		Result_expression_memberContext _localctx = new Result_expression_memberContext(_ctx, getState());
		enterRule(_localctx, 266, RULE_result_expression_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1450);
			member_prefix();
			setState(1451);
			owned_expression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExpressionContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_EXPR() { return getToken(KerMLParser.KEYWORD_EXPR, 0); }
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Function_bodyContext function_body() {
			return getRuleContext(Function_bodyContext.class,0);
		}
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitExpression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitExpression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 268, RULE_expression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1453);
			feature_prefix();
			setState(1454);
			match(KEYWORD_EXPR);
			setState(1455);
			feature_declaration();
			setState(1457);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
				{
				setState(1456);
				value_part();
				}
			}

			setState(1459);
			function_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PredicateContext extends ParserRuleContext {
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_PREDICATE() { return getToken(KerMLParser.KEYWORD_PREDICATE, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Function_bodyContext function_body() {
			return getRuleContext(Function_bodyContext.class,0);
		}
		public PredicateContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_predicate; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterPredicate(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitPredicate(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitPredicate(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PredicateContext predicate() throws RecognitionException {
		PredicateContext _localctx = new PredicateContext(_ctx, getState());
		enterRule(_localctx, 270, RULE_predicate);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1461);
			type_prefix();
			setState(1462);
			match(KEYWORD_PREDICATE);
			setState(1463);
			classifier_declaration();
			setState(1464);
			function_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Boolean_expressionContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_BOOL() { return getToken(KerMLParser.KEYWORD_BOOL, 0); }
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Function_bodyContext function_body() {
			return getRuleContext(Function_bodyContext.class,0);
		}
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public Boolean_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_boolean_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBoolean_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBoolean_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBoolean_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Boolean_expressionContext boolean_expression() throws RecognitionException {
		Boolean_expressionContext _localctx = new Boolean_expressionContext(_ctx, getState());
		enterRule(_localctx, 272, RULE_boolean_expression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1466);
			feature_prefix();
			setState(1467);
			match(KEYWORD_BOOL);
			setState(1468);
			feature_declaration();
			setState(1470);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
				{
				setState(1469);
				value_part();
				}
			}

			setState(1472);
			function_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class InvariantContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_INV() { return getToken(KerMLParser.KEYWORD_INV, 0); }
		public Function_bodyContext function_body() {
			return getRuleContext(Function_bodyContext.class,0);
		}
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public TerminalNode KEYWORD_TRUE() { return getToken(KerMLParser.KEYWORD_TRUE, 0); }
		public TerminalNode KEYWORD_FALSE() { return getToken(KerMLParser.KEYWORD_FALSE, 0); }
		public InvariantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_invariant; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterInvariant(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitInvariant(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitInvariant(this);
			else return visitor.visitChildren(this);
		}
	}

	public final InvariantContext invariant() throws RecognitionException {
		InvariantContext _localctx = new InvariantContext(_ctx, getState());
		enterRule(_localctx, 274, RULE_invariant);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1474);
			feature_prefix();
			setState(1475);
			match(KEYWORD_INV);
			setState(1477);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_FALSE || _la==KEYWORD_TRUE) {
				{
				setState(1476);
				_la = _input.LA(1);
				if ( !(_la==KEYWORD_FALSE || _la==KEYWORD_TRUE) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
			}

			setState(1480);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1153343717072175120L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & 611926736943188483L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
				{
				setState(1479);
				feature_declaration();
				}
			}

			setState(1483);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
				{
				setState(1482);
				value_part();
				}
			}

			setState(1485);
			function_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_expression_reference_memberContext extends ParserRuleContext {
		public Owned_expression_referenceContext owned_expression_reference() {
			return getRuleContext(Owned_expression_referenceContext.class,0);
		}
		public Owned_expression_reference_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_expression_reference_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_expression_reference_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_expression_reference_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_expression_reference_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_expression_reference_memberContext owned_expression_reference_member() throws RecognitionException {
		Owned_expression_reference_memberContext _localctx = new Owned_expression_reference_memberContext(_ctx, getState());
		enterRule(_localctx, 276, RULE_owned_expression_reference_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1487);
			owned_expression_reference();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_expression_referenceContext extends ParserRuleContext {
		public Owned_expression_memberContext owned_expression_member() {
			return getRuleContext(Owned_expression_memberContext.class,0);
		}
		public Owned_expression_referenceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_expression_reference; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_expression_reference(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_expression_reference(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_expression_reference(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_expression_referenceContext owned_expression_reference() throws RecognitionException {
		Owned_expression_referenceContext _localctx = new Owned_expression_referenceContext(_ctx, getState());
		enterRule(_localctx, 278, RULE_owned_expression_reference);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1489);
			owned_expression_member();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_expression_memberContext extends ParserRuleContext {
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public Owned_expression_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_expression_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_expression_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_expression_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_expression_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_expression_memberContext owned_expression_member() throws RecognitionException {
		Owned_expression_memberContext _localctx = new Owned_expression_memberContext(_ctx, getState());
		enterRule(_localctx, 280, RULE_owned_expression_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1491);
			owned_expression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_expressionContext extends ParserRuleContext {
		public Owned_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_expression; }
	 
		public Owned_expressionContext() { }
		public void copyFrom(Owned_expressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SelectExprContext extends Owned_expressionContext {
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_DOT_QUESTION() { return getToken(KerMLParser.SYMBOL_DOT_QUESTION, 0); }
		public Body_expressionContext body_expression() {
			return getRuleContext(Body_expressionContext.class,0);
		}
		public SelectExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSelectExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSelectExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSelectExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class CollectExprContext extends Owned_expressionContext {
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_DOT() { return getToken(KerMLParser.SYMBOL_DOT, 0); }
		public Body_expressionContext body_expression() {
			return getRuleContext(Body_expressionContext.class,0);
		}
		public CollectExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterCollectExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitCollectExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitCollectExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BinaryExprContext extends Owned_expressionContext {
		public Token op;
		public List<Owned_expressionContext> owned_expression() {
			return getRuleContexts(Owned_expressionContext.class);
		}
		public Owned_expressionContext owned_expression(int i) {
			return getRuleContext(Owned_expressionContext.class,i);
		}
		public TerminalNode SYMBOL_DOUBLE_STAR() { return getToken(KerMLParser.SYMBOL_DOUBLE_STAR, 0); }
		public TerminalNode SYMBOL_UPPER() { return getToken(KerMLParser.SYMBOL_UPPER, 0); }
		public TerminalNode SYMBOL_STAR() { return getToken(KerMLParser.SYMBOL_STAR, 0); }
		public TerminalNode SYMBOL_SLASH() { return getToken(KerMLParser.SYMBOL_SLASH, 0); }
		public TerminalNode SYMBOL_MOD() { return getToken(KerMLParser.SYMBOL_MOD, 0); }
		public TerminalNode SYMBOL_PLUS() { return getToken(KerMLParser.SYMBOL_PLUS, 0); }
		public TerminalNode SYMBOL_MINUS() { return getToken(KerMLParser.SYMBOL_MINUS, 0); }
		public TerminalNode SYMBOL_DDOT() { return getToken(KerMLParser.SYMBOL_DDOT, 0); }
		public TerminalNode SYMBOL_GREATER() { return getToken(KerMLParser.SYMBOL_GREATER, 0); }
		public TerminalNode SYMBOL_SMALLER() { return getToken(KerMLParser.SYMBOL_SMALLER, 0); }
		public TerminalNode SYMBOL_GREATER_EQUALS() { return getToken(KerMLParser.SYMBOL_GREATER_EQUALS, 0); }
		public TerminalNode SYMBOL_SMALLER_EQUAL() { return getToken(KerMLParser.SYMBOL_SMALLER_EQUAL, 0); }
		public TerminalNode SYMBOL_EQUALS() { return getToken(KerMLParser.SYMBOL_EQUALS, 0); }
		public TerminalNode SYMBOL_NOT_EQUALS() { return getToken(KerMLParser.SYMBOL_NOT_EQUALS, 0); }
		public TerminalNode SYMBOL_IFF_EQUALS() { return getToken(KerMLParser.SYMBOL_IFF_EQUALS, 0); }
		public TerminalNode SYMBOL_IFF_NOT_EQUALS() { return getToken(KerMLParser.SYMBOL_IFF_NOT_EQUALS, 0); }
		public TerminalNode SYMBOL_AND() { return getToken(KerMLParser.SYMBOL_AND, 0); }
		public TerminalNode KEYWORD_AND() { return getToken(KerMLParser.KEYWORD_AND, 0); }
		public TerminalNode KEYWORD_XOR() { return getToken(KerMLParser.KEYWORD_XOR, 0); }
		public TerminalNode SYMBOL_VERTICAL_LINE() { return getToken(KerMLParser.SYMBOL_VERTICAL_LINE, 0); }
		public TerminalNode KEYWORD_OR() { return getToken(KerMLParser.KEYWORD_OR, 0); }
		public TerminalNode KEYWORD_IMPLIES() { return getToken(KerMLParser.KEYWORD_IMPLIES, 0); }
		public TerminalNode SYMBOL_DQUESTION() { return getToken(KerMLParser.SYMBOL_DQUESTION, 0); }
		public BinaryExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBinaryExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBinaryExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBinaryExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ExtentExprContext extends Owned_expressionContext {
		public TerminalNode KEYWORD_ALL() { return getToken(KerMLParser.KEYWORD_ALL, 0); }
		public Type_reference_memberContext type_reference_member() {
			return getRuleContext(Type_reference_memberContext.class,0);
		}
		public ExtentExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterExtentExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitExtentExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitExtentExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ConditionalExprContext extends Owned_expressionContext {
		public TerminalNode KEYWORD_IF() { return getToken(KerMLParser.KEYWORD_IF, 0); }
		public List<Owned_expressionContext> owned_expression() {
			return getRuleContexts(Owned_expressionContext.class);
		}
		public Owned_expressionContext owned_expression(int i) {
			return getRuleContext(Owned_expressionContext.class,i);
		}
		public TerminalNode SYMBOL_QUESTION() { return getToken(KerMLParser.SYMBOL_QUESTION, 0); }
		public TerminalNode KEYWORD_ELSE() { return getToken(KerMLParser.KEYWORD_ELSE, 0); }
		public ConditionalExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterConditionalExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitConditionalExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitConditionalExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnaryExprContext extends Owned_expressionContext {
		public Token op;
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_PLUS() { return getToken(KerMLParser.SYMBOL_PLUS, 0); }
		public TerminalNode SYMBOL_MINUS() { return getToken(KerMLParser.SYMBOL_MINUS, 0); }
		public TerminalNode SYMBOL_CONJUGATES() { return getToken(KerMLParser.SYMBOL_CONJUGATES, 0); }
		public TerminalNode KEYWORD_NOT() { return getToken(KerMLParser.KEYWORD_NOT, 0); }
		public UnaryExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterUnaryExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitUnaryExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitUnaryExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IndexExprContext extends Owned_expressionContext {
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_HASHTAG() { return getToken(KerMLParser.SYMBOL_HASHTAG, 0); }
		public TerminalNode SYMBOL_ROUND_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_OPEN, 0); }
		public Sequence_expression_list_memberContext sequence_expression_list_member() {
			return getRuleContext(Sequence_expression_list_memberContext.class,0);
		}
		public TerminalNode SYMBOL_ROUND_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_CLOSE, 0); }
		public IndexExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterIndexExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitIndexExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitIndexExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BaseExprContext extends Owned_expressionContext {
		public Base_expressionContext base_expression() {
			return getRuleContext(Base_expressionContext.class,0);
		}
		public BaseExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBaseExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBaseExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBaseExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FeatureChainExprContext extends Owned_expressionContext {
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_DOT() { return getToken(KerMLParser.SYMBOL_DOT, 0); }
		public Feature_reference_memberContext feature_reference_member() {
			return getRuleContext(Feature_reference_memberContext.class,0);
		}
		public FeatureChainExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeatureChainExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeatureChainExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeatureChainExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BracketExprContext extends Owned_expressionContext {
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_SQUARE_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_SQUARE_BRACKET_OPEN, 0); }
		public Sequence_expression_list_memberContext sequence_expression_list_member() {
			return getRuleContext(Sequence_expression_list_memberContext.class,0);
		}
		public TerminalNode SYMBOL_SQUARE_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_SQUARE_BRACKET_CLOSE, 0); }
		public BracketExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBracketExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBracketExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBracketExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MetaclassificationExprContext extends Owned_expressionContext {
		public Token op;
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public Type_reference_memberContext type_reference_member() {
			return getRuleContext(Type_reference_memberContext.class,0);
		}
		public TerminalNode SYMBOL_ATAT() { return getToken(KerMLParser.SYMBOL_ATAT, 0); }
		public Type_result_memberContext type_result_member() {
			return getRuleContext(Type_result_memberContext.class,0);
		}
		public TerminalNode KEYWORD_META() { return getToken(KerMLParser.KEYWORD_META, 0); }
		public MetaclassificationExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMetaclassificationExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMetaclassificationExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMetaclassificationExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ClassificationExprContext extends Owned_expressionContext {
		public Token op;
		public Type_reference_memberContext type_reference_member() {
			return getRuleContext(Type_reference_memberContext.class,0);
		}
		public TerminalNode KEYWORD_ISTYPE() { return getToken(KerMLParser.KEYWORD_ISTYPE, 0); }
		public TerminalNode KEYWORD_HASTYPE() { return getToken(KerMLParser.KEYWORD_HASTYPE, 0); }
		public TerminalNode SYMBOL_AT() { return getToken(KerMLParser.SYMBOL_AT, 0); }
		public TerminalNode KEYWORD_AS() { return getToken(KerMLParser.KEYWORD_AS, 0); }
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public Type_result_memberContext type_result_member() {
			return getRuleContext(Type_result_memberContext.class,0);
		}
		public ClassificationExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterClassificationExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitClassificationExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitClassificationExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SequenceExprContext extends Owned_expressionContext {
		public Sequence_expressionContext sequence_expression() {
			return getRuleContext(Sequence_expressionContext.class,0);
		}
		public SequenceExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSequenceExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSequenceExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSequenceExpr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FunctionOperationExprContext extends Owned_expressionContext {
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_ARROW() { return getToken(KerMLParser.SYMBOL_ARROW, 0); }
		public Reference_typingContext reference_typing() {
			return getRuleContext(Reference_typingContext.class,0);
		}
		public Function_operation_argumentsContext function_operation_arguments() {
			return getRuleContext(Function_operation_argumentsContext.class,0);
		}
		public FunctionOperationExprContext(Owned_expressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFunctionOperationExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFunctionOperationExpr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFunctionOperationExpr(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_expressionContext owned_expression() throws RecognitionException {
		return owned_expression(0);
	}

	private Owned_expressionContext owned_expression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Owned_expressionContext _localctx = new Owned_expressionContext(_ctx, _parentState);
		Owned_expressionContext _prevctx = _localctx;
		int _startState = 282;
		enterRecursionRule(_localctx, 282, RULE_owned_expression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1509);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,162,_ctx) ) {
			case 1:
				{
				_localctx = new UnaryExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(1494);
				((UnaryExprContext)_localctx).op = _input.LT(1);
				_la = _input.LA(1);
				if ( !(_la==KEYWORD_NOT || ((((_la - 118)) & ~0x3f) == 0 && ((1L << (_la - 118)) & 196609L) != 0)) ) {
					((UnaryExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(1495);
				owned_expression(21);
				}
				break;
			case 2:
				{
				_localctx = new ConditionalExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(1496);
				match(KEYWORD_IF);
				setState(1497);
				owned_expression(0);
				setState(1498);
				match(SYMBOL_QUESTION);
				setState(1499);
				owned_expression(0);
				setState(1500);
				match(KEYWORD_ELSE);
				setState(1501);
				owned_expression(5);
				}
				break;
			case 3:
				{
				_localctx = new ClassificationExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(1503);
				((ClassificationExprContext)_localctx).op = _input.LT(1);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 9011597301252160L) != 0) || _la==SYMBOL_AT) ) {
					((ClassificationExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(1504);
				type_reference_member();
				}
				break;
			case 4:
				{
				_localctx = new ExtentExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(1505);
				match(KEYWORD_ALL);
				setState(1506);
				type_reference_member();
				}
				break;
			case 5:
				{
				_localctx = new SequenceExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(1507);
				sequence_expression();
				}
				break;
			case 6:
				{
				_localctx = new BaseExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(1508);
				base_expression();
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(1583);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,164,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(1581);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,163,_ctx) ) {
					case 1:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1511);
						if (!(precpred(_ctx, 20))) throw new FailedPredicateException(this, "precpred(_ctx, 20)");
						setState(1512);
						((BinaryExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==SYMBOL_UPPER || _la==SYMBOL_DOUBLE_STAR) ) {
							((BinaryExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1513);
						owned_expression(20);
						}
						break;
					case 2:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1514);
						if (!(precpred(_ctx, 19))) throw new FailedPredicateException(this, "precpred(_ctx, 19)");
						setState(1515);
						((BinaryExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(((((_la - 112)) & ~0x3f) == 0 && ((1L << (_la - 112)) & 16908289L) != 0)) ) {
							((BinaryExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1516);
						owned_expression(20);
						}
						break;
					case 3:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1517);
						if (!(precpred(_ctx, 18))) throw new FailedPredicateException(this, "precpred(_ctx, 18)");
						setState(1518);
						((BinaryExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==SYMBOL_PLUS || _la==SYMBOL_MINUS) ) {
							((BinaryExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1519);
						owned_expression(19);
						}
						break;
					case 4:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1520);
						if (!(precpred(_ctx, 17))) throw new FailedPredicateException(this, "precpred(_ctx, 17)");
						setState(1521);
						((BinaryExprContext)_localctx).op = match(SYMBOL_DDOT);
						setState(1522);
						owned_expression(18);
						}
						break;
					case 5:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1523);
						if (!(precpred(_ctx, 16))) throw new FailedPredicateException(this, "precpred(_ctx, 16)");
						setState(1524);
						((BinaryExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(((((_la - 140)) & ~0x3f) == 0 && ((1L << (_la - 140)) & 771L) != 0)) ) {
							((BinaryExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1525);
						owned_expression(17);
						}
						break;
					case 6:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1526);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(1527);
						((BinaryExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(((((_la - 144)) & ~0x3f) == 0 && ((1L << (_la - 144)) & 15L) != 0)) ) {
							((BinaryExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1528);
						owned_expression(12);
						}
						break;
					case 7:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1529);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(1530);
						((BinaryExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==KEYWORD_AND || _la==SYMBOL_AND) ) {
							((BinaryExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1531);
						owned_expression(11);
						}
						break;
					case 8:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1532);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(1533);
						((BinaryExprContext)_localctx).op = match(KEYWORD_XOR);
						setState(1534);
						owned_expression(10);
						}
						break;
					case 9:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1535);
						if (!(precpred(_ctx, 8))) throw new FailedPredicateException(this, "precpred(_ctx, 8)");
						setState(1536);
						((BinaryExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==KEYWORD_OR || _la==SYMBOL_VERTICAL_LINE) ) {
							((BinaryExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1537);
						owned_expression(9);
						}
						break;
					case 10:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1538);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(1539);
						((BinaryExprContext)_localctx).op = match(KEYWORD_IMPLIES);
						setState(1540);
						owned_expression(8);
						}
						break;
					case 11:
						{
						_localctx = new BinaryExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1541);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(1542);
						((BinaryExprContext)_localctx).op = match(SYMBOL_DQUESTION);
						setState(1543);
						owned_expression(7);
						}
						break;
					case 12:
						{
						_localctx = new SelectExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1544);
						if (!(precpred(_ctx, 27))) throw new FailedPredicateException(this, "precpred(_ctx, 27)");
						setState(1545);
						match(SYMBOL_DOT_QUESTION);
						setState(1546);
						body_expression();
						}
						break;
					case 13:
						{
						_localctx = new CollectExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1547);
						if (!(precpred(_ctx, 26))) throw new FailedPredicateException(this, "precpred(_ctx, 26)");
						setState(1548);
						match(SYMBOL_DOT);
						setState(1549);
						body_expression();
						}
						break;
					case 14:
						{
						_localctx = new FeatureChainExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1550);
						if (!(precpred(_ctx, 25))) throw new FailedPredicateException(this, "precpred(_ctx, 25)");
						setState(1551);
						match(SYMBOL_DOT);
						setState(1552);
						feature_reference_member();
						}
						break;
					case 15:
						{
						_localctx = new FunctionOperationExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1553);
						if (!(precpred(_ctx, 24))) throw new FailedPredicateException(this, "precpred(_ctx, 24)");
						setState(1554);
						match(SYMBOL_ARROW);
						setState(1555);
						reference_typing();
						setState(1556);
						function_operation_arguments();
						}
						break;
					case 16:
						{
						_localctx = new IndexExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1558);
						if (!(precpred(_ctx, 23))) throw new FailedPredicateException(this, "precpred(_ctx, 23)");
						setState(1559);
						match(SYMBOL_HASHTAG);
						setState(1560);
						match(SYMBOL_ROUND_BRACKET_OPEN);
						setState(1561);
						sequence_expression_list_member();
						setState(1562);
						match(SYMBOL_ROUND_BRACKET_CLOSE);
						}
						break;
					case 17:
						{
						_localctx = new BracketExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1564);
						if (!(precpred(_ctx, 22))) throw new FailedPredicateException(this, "precpred(_ctx, 22)");
						setState(1565);
						match(SYMBOL_SQUARE_BRACKET_OPEN);
						setState(1566);
						sequence_expression_list_member();
						setState(1567);
						match(SYMBOL_SQUARE_BRACKET_CLOSE);
						}
						break;
					case 18:
						{
						_localctx = new ClassificationExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1569);
						if (!(precpred(_ctx, 15))) throw new FailedPredicateException(this, "precpred(_ctx, 15)");
						setState(1570);
						((ClassificationExprContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==KEYWORD_HASTYPE || _la==KEYWORD_ISTYPE || _la==SYMBOL_AT) ) {
							((ClassificationExprContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1571);
						type_reference_member();
						}
						break;
					case 19:
						{
						_localctx = new ClassificationExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1572);
						if (!(precpred(_ctx, 14))) throw new FailedPredicateException(this, "precpred(_ctx, 14)");
						setState(1573);
						((ClassificationExprContext)_localctx).op = match(KEYWORD_AS);
						setState(1574);
						type_result_member();
						}
						break;
					case 20:
						{
						_localctx = new MetaclassificationExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1575);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(1576);
						((MetaclassificationExprContext)_localctx).op = match(SYMBOL_ATAT);
						setState(1577);
						type_reference_member();
						}
						break;
					case 21:
						{
						_localctx = new MetaclassificationExprContext(new Owned_expressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_owned_expression);
						setState(1578);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(1579);
						((MetaclassificationExprContext)_localctx).op = match(KEYWORD_META);
						setState(1580);
						type_result_member();
						}
						break;
					}
					} 
				}
				setState(1585);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,164,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Function_operation_argumentsContext extends ParserRuleContext {
		public Body_expressionContext body_expression() {
			return getRuleContext(Body_expressionContext.class,0);
		}
		public Function_referenceContext function_reference() {
			return getRuleContext(Function_referenceContext.class,0);
		}
		public Argument_listContext argument_list() {
			return getRuleContext(Argument_listContext.class,0);
		}
		public Function_operation_argumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function_operation_arguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFunction_operation_arguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFunction_operation_arguments(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFunction_operation_arguments(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Function_operation_argumentsContext function_operation_arguments() throws RecognitionException {
		Function_operation_argumentsContext _localctx = new Function_operation_argumentsContext(_ctx, getState());
		enterRule(_localctx, 284, RULE_function_operation_arguments);
		try {
			setState(1589);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_CURLY_BRACKET_OPEN:
				enterOuterAlt(_localctx, 1);
				{
				setState(1586);
				body_expression();
				}
				break;
			case NAME:
				enterOuterAlt(_localctx, 2);
				{
				setState(1587);
				function_reference();
				}
				break;
			case SYMBOL_ROUND_BRACKET_OPEN:
				enterOuterAlt(_localctx, 3);
				{
				setState(1588);
				argument_list();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_reference_memberContext extends ParserRuleContext {
		public Type_referenceContext type_reference() {
			return getRuleContext(Type_referenceContext.class,0);
		}
		public Type_reference_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_reference_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_reference_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_reference_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_reference_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_reference_memberContext type_reference_member() throws RecognitionException {
		Type_reference_memberContext _localctx = new Type_reference_memberContext(_ctx, getState());
		enterRule(_localctx, 286, RULE_type_reference_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1591);
			type_reference();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_result_memberContext extends ParserRuleContext {
		public Type_referenceContext type_reference() {
			return getRuleContext(Type_referenceContext.class,0);
		}
		public Type_result_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_result_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_result_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_result_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_result_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_result_memberContext type_result_member() throws RecognitionException {
		Type_result_memberContext _localctx = new Type_result_memberContext(_ctx, getState());
		enterRule(_localctx, 288, RULE_type_result_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1593);
			type_reference();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_referenceContext extends ParserRuleContext {
		public Reference_typingContext reference_typing() {
			return getRuleContext(Reference_typingContext.class,0);
		}
		public Type_referenceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_reference; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterType_reference(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitType_reference(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitType_reference(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Type_referenceContext type_reference() throws RecognitionException {
		Type_referenceContext _localctx = new Type_referenceContext(_ctx, getState());
		enterRule(_localctx, 290, RULE_type_reference);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1595);
			reference_typing();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Reference_typingContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Reference_typingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_reference_typing; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterReference_typing(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitReference_typing(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitReference_typing(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Reference_typingContext reference_typing() throws RecognitionException {
		Reference_typingContext _localctx = new Reference_typingContext(_ctx, getState());
		enterRule(_localctx, 292, RULE_reference_typing);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1597);
			qualified_name();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Sequence_expressionContext extends ParserRuleContext {
		public TerminalNode SYMBOL_ROUND_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_OPEN, 0); }
		public Sequence_expression_listContext sequence_expression_list() {
			return getRuleContext(Sequence_expression_listContext.class,0);
		}
		public TerminalNode SYMBOL_ROUND_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_CLOSE, 0); }
		public Sequence_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sequence_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSequence_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSequence_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSequence_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Sequence_expressionContext sequence_expression() throws RecognitionException {
		Sequence_expressionContext _localctx = new Sequence_expressionContext(_ctx, getState());
		enterRule(_localctx, 294, RULE_sequence_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1599);
			match(SYMBOL_ROUND_BRACKET_OPEN);
			setState(1600);
			sequence_expression_list();
			setState(1601);
			match(SYMBOL_ROUND_BRACKET_CLOSE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Sequence_expression_listContext extends ParserRuleContext {
		public Sequence_operator_expressionContext sequence_operator_expression() {
			return getRuleContext(Sequence_operator_expressionContext.class,0);
		}
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_COMMA() { return getToken(KerMLParser.SYMBOL_COMMA, 0); }
		public Sequence_expression_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sequence_expression_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSequence_expression_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSequence_expression_list(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSequence_expression_list(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Sequence_expression_listContext sequence_expression_list() throws RecognitionException {
		Sequence_expression_listContext _localctx = new Sequence_expression_listContext(_ctx, getState());
		enterRule(_localctx, 296, RULE_sequence_expression_list);
		int _la;
		try {
			setState(1608);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,167,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1603);
				sequence_operator_expression();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1604);
				owned_expression(0);
				setState(1606);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SYMBOL_COMMA) {
					{
					setState(1605);
					match(SYMBOL_COMMA);
					}
				}

				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Sequence_operator_expressionContext extends ParserRuleContext {
		public Owned_expression_memberContext owned_expression_member() {
			return getRuleContext(Owned_expression_memberContext.class,0);
		}
		public TerminalNode SYMBOL_COMMA() { return getToken(KerMLParser.SYMBOL_COMMA, 0); }
		public Sequence_expression_list_memberContext sequence_expression_list_member() {
			return getRuleContext(Sequence_expression_list_memberContext.class,0);
		}
		public Sequence_operator_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sequence_operator_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSequence_operator_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSequence_operator_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSequence_operator_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Sequence_operator_expressionContext sequence_operator_expression() throws RecognitionException {
		Sequence_operator_expressionContext _localctx = new Sequence_operator_expressionContext(_ctx, getState());
		enterRule(_localctx, 298, RULE_sequence_operator_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1610);
			owned_expression_member();
			setState(1611);
			match(SYMBOL_COMMA);
			setState(1612);
			sequence_expression_list_member();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Sequence_expression_list_memberContext extends ParserRuleContext {
		public Sequence_expression_listContext sequence_expression_list() {
			return getRuleContext(Sequence_expression_listContext.class,0);
		}
		public Sequence_expression_list_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sequence_expression_list_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSequence_expression_list_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSequence_expression_list_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSequence_expression_list_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Sequence_expression_list_memberContext sequence_expression_list_member() throws RecognitionException {
		Sequence_expression_list_memberContext _localctx = new Sequence_expression_list_memberContext(_ctx, getState());
		enterRule(_localctx, 300, RULE_sequence_expression_list_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1614);
			sequence_expression_list();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Function_referenceContext extends ParserRuleContext {
		public Reference_typingContext reference_typing() {
			return getRuleContext(Reference_typingContext.class,0);
		}
		public Function_referenceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function_reference; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFunction_reference(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFunction_reference(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFunction_reference(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Function_referenceContext function_reference() throws RecognitionException {
		Function_referenceContext _localctx = new Function_referenceContext(_ctx, getState());
		enterRule(_localctx, 302, RULE_function_reference);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1616);
			reference_typing();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_chain_memberContext extends ParserRuleContext {
		public Feature_reference_memberContext feature_reference_member() {
			return getRuleContext(Feature_reference_memberContext.class,0);
		}
		public Owned_feature_chain_memberContext owned_feature_chain_member() {
			return getRuleContext(Owned_feature_chain_memberContext.class,0);
		}
		public Feature_chain_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_chain_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_chain_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_chain_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_chain_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_chain_memberContext feature_chain_member() throws RecognitionException {
		Feature_chain_memberContext _localctx = new Feature_chain_memberContext(_ctx, getState());
		enterRule(_localctx, 304, RULE_feature_chain_member);
		try {
			setState(1620);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,168,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1618);
				feature_reference_member();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1619);
				owned_feature_chain_member();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_feature_chain_memberContext extends ParserRuleContext {
		public Feature_chainContext feature_chain() {
			return getRuleContext(Feature_chainContext.class,0);
		}
		public Owned_feature_chain_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_feature_chain_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_feature_chain_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_feature_chain_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_feature_chain_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_feature_chain_memberContext owned_feature_chain_member() throws RecognitionException {
		Owned_feature_chain_memberContext _localctx = new Owned_feature_chain_memberContext(_ctx, getState());
		enterRule(_localctx, 306, RULE_owned_feature_chain_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1622);
			feature_chain();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Base_expressionContext extends ParserRuleContext {
		public Invocation_expressionContext invocation_expression() {
			return getRuleContext(Invocation_expressionContext.class,0);
		}
		public Constructor_expressionContext constructor_expression() {
			return getRuleContext(Constructor_expressionContext.class,0);
		}
		public Null_expressionContext null_expression() {
			return getRuleContext(Null_expressionContext.class,0);
		}
		public Literal_expressionContext literal_expression() {
			return getRuleContext(Literal_expressionContext.class,0);
		}
		public Metadata_access_expressionContext metadata_access_expression() {
			return getRuleContext(Metadata_access_expressionContext.class,0);
		}
		public Feature_reference_expressionContext feature_reference_expression() {
			return getRuleContext(Feature_reference_expressionContext.class,0);
		}
		public Body_expressionContext body_expression() {
			return getRuleContext(Body_expressionContext.class,0);
		}
		public Base_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_base_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBase_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBase_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBase_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Base_expressionContext base_expression() throws RecognitionException {
		Base_expressionContext _localctx = new Base_expressionContext(_ctx, getState());
		enterRule(_localctx, 308, RULE_base_expression);
		try {
			setState(1631);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,169,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1624);
				invocation_expression();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1625);
				constructor_expression();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1626);
				null_expression();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1627);
				literal_expression();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(1628);
				metadata_access_expression();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(1629);
				feature_reference_expression();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(1630);
				body_expression();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Null_expressionContext extends ParserRuleContext {
		public TerminalNode KEYWORD_NULL() { return getToken(KerMLParser.KEYWORD_NULL, 0); }
		public TerminalNode SYMBOL_ROUND_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_OPEN, 0); }
		public TerminalNode SYMBOL_ROUND_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_CLOSE, 0); }
		public Null_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_null_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNull_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNull_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNull_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Null_expressionContext null_expression() throws RecognitionException {
		Null_expressionContext _localctx = new Null_expressionContext(_ctx, getState());
		enterRule(_localctx, 310, RULE_null_expression);
		try {
			setState(1636);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case KEYWORD_NULL:
				enterOuterAlt(_localctx, 1);
				{
				setState(1633);
				match(KEYWORD_NULL);
				}
				break;
			case SYMBOL_ROUND_BRACKET_OPEN:
				enterOuterAlt(_localctx, 2);
				{
				setState(1634);
				match(SYMBOL_ROUND_BRACKET_OPEN);
				setState(1635);
				match(SYMBOL_ROUND_BRACKET_CLOSE);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_reference_expressionContext extends ParserRuleContext {
		public Feature_reference_memberContext feature_reference_member() {
			return getRuleContext(Feature_reference_memberContext.class,0);
		}
		public Feature_reference_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_reference_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_reference_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_reference_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_reference_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_reference_expressionContext feature_reference_expression() throws RecognitionException {
		Feature_reference_expressionContext _localctx = new Feature_reference_expressionContext(_ctx, getState());
		enterRule(_localctx, 312, RULE_feature_reference_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1638);
			feature_reference_member();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_reference_memberContext extends ParserRuleContext {
		public Feature_referenceContext feature_reference() {
			return getRuleContext(Feature_referenceContext.class,0);
		}
		public Feature_reference_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_reference_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_reference_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_reference_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_reference_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_reference_memberContext feature_reference_member() throws RecognitionException {
		Feature_reference_memberContext _localctx = new Feature_reference_memberContext(_ctx, getState());
		enterRule(_localctx, 314, RULE_feature_reference_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1640);
			feature_reference();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_referenceContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Feature_referenceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_reference; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_reference(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_reference(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_reference(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_referenceContext feature_reference() throws RecognitionException {
		Feature_referenceContext _localctx = new Feature_referenceContext(_ctx, getState());
		enterRule(_localctx, 316, RULE_feature_reference);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1642);
			qualified_name();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Metadata_access_expressionContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public TerminalNode SYMBOL_DOT() { return getToken(KerMLParser.SYMBOL_DOT, 0); }
		public TerminalNode KEYWORD_METADATA() { return getToken(KerMLParser.KEYWORD_METADATA, 0); }
		public Metadata_access_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata_access_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMetadata_access_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMetadata_access_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMetadata_access_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Metadata_access_expressionContext metadata_access_expression() throws RecognitionException {
		Metadata_access_expressionContext _localctx = new Metadata_access_expressionContext(_ctx, getState());
		enterRule(_localctx, 318, RULE_metadata_access_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1644);
			qualified_name();
			setState(1645);
			match(SYMBOL_DOT);
			setState(1646);
			match(KEYWORD_METADATA);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Invocation_expressionContext extends ParserRuleContext {
		public Internal_invocation_expressionContext internal_invocation_expression() {
			return getRuleContext(Internal_invocation_expressionContext.class,0);
		}
		public Invocation_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_invocation_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterInvocation_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitInvocation_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitInvocation_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Invocation_expressionContext invocation_expression() throws RecognitionException {
		Invocation_expressionContext _localctx = new Invocation_expressionContext(_ctx, getState());
		enterRule(_localctx, 320, RULE_invocation_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1648);
			internal_invocation_expression();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Internal_invocation_expressionContext extends ParserRuleContext {
		public Owned_feature_typingContext owned_feature_typing() {
			return getRuleContext(Owned_feature_typingContext.class,0);
		}
		public Argument_listContext argument_list() {
			return getRuleContext(Argument_listContext.class,0);
		}
		public Internal_invocation_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_internal_invocation_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterInternal_invocation_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitInternal_invocation_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitInternal_invocation_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Internal_invocation_expressionContext internal_invocation_expression() throws RecognitionException {
		Internal_invocation_expressionContext _localctx = new Internal_invocation_expressionContext(_ctx, getState());
		enterRule(_localctx, 322, RULE_internal_invocation_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1650);
			owned_feature_typing();
			setState(1651);
			argument_list();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Constructor_expressionContext extends ParserRuleContext {
		public TerminalNode KEYWORD_NEW() { return getToken(KerMLParser.KEYWORD_NEW, 0); }
		public Owned_feature_typingContext owned_feature_typing() {
			return getRuleContext(Owned_feature_typingContext.class,0);
		}
		public Argument_listContext argument_list() {
			return getRuleContext(Argument_listContext.class,0);
		}
		public Constructor_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constructor_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterConstructor_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitConstructor_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitConstructor_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Constructor_expressionContext constructor_expression() throws RecognitionException {
		Constructor_expressionContext _localctx = new Constructor_expressionContext(_ctx, getState());
		enterRule(_localctx, 324, RULE_constructor_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1653);
			match(KEYWORD_NEW);
			setState(1654);
			owned_feature_typing();
			setState(1655);
			argument_list();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Argument_listContext extends ParserRuleContext {
		public TerminalNode SYMBOL_ROUND_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_OPEN, 0); }
		public TerminalNode SYMBOL_ROUND_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_ROUND_BRACKET_CLOSE, 0); }
		public Named_argument_listContext named_argument_list() {
			return getRuleContext(Named_argument_listContext.class,0);
		}
		public Positional_argument_listContext positional_argument_list() {
			return getRuleContext(Positional_argument_listContext.class,0);
		}
		public Argument_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_argument_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterArgument_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitArgument_list(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitArgument_list(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Argument_listContext argument_list() throws RecognitionException {
		Argument_listContext _localctx = new Argument_listContext(_ctx, getState());
		enterRule(_localctx, 326, RULE_argument_list);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1657);
			match(SYMBOL_ROUND_BRACKET_OPEN);
			setState(1660);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,171,_ctx) ) {
			case 1:
				{
				setState(1658);
				named_argument_list();
				}
				break;
			case 2:
				{
				setState(1659);
				positional_argument_list();
				}
				break;
			}
			setState(1662);
			match(SYMBOL_ROUND_BRACKET_CLOSE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Positional_argument_listContext extends ParserRuleContext {
		public List<Owned_expressionContext> owned_expression() {
			return getRuleContexts(Owned_expressionContext.class);
		}
		public Owned_expressionContext owned_expression(int i) {
			return getRuleContext(Owned_expressionContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Positional_argument_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_positional_argument_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterPositional_argument_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitPositional_argument_list(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitPositional_argument_list(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Positional_argument_listContext positional_argument_list() throws RecognitionException {
		Positional_argument_listContext _localctx = new Positional_argument_listContext(_ctx, getState());
		enterRule(_localctx, 328, RULE_positional_argument_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1664);
			owned_expression(0);
			setState(1669);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(1665);
				match(SYMBOL_COMMA);
				setState(1666);
				owned_expression(0);
				}
				}
				setState(1671);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Named_argument_listContext extends ParserRuleContext {
		public List<Named_argument_memberContext> named_argument_member() {
			return getRuleContexts(Named_argument_memberContext.class);
		}
		public Named_argument_memberContext named_argument_member(int i) {
			return getRuleContext(Named_argument_memberContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Named_argument_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_named_argument_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamed_argument_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamed_argument_list(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamed_argument_list(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Named_argument_listContext named_argument_list() throws RecognitionException {
		Named_argument_listContext _localctx = new Named_argument_listContext(_ctx, getState());
		enterRule(_localctx, 330, RULE_named_argument_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1672);
			named_argument_member();
			setState(1677);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_COMMA) {
				{
				{
				setState(1673);
				match(SYMBOL_COMMA);
				setState(1674);
				named_argument_member();
				}
				}
				setState(1679);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Named_argument_memberContext extends ParserRuleContext {
		public Named_argumentContext named_argument() {
			return getRuleContext(Named_argumentContext.class,0);
		}
		public Named_argument_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_named_argument_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamed_argument_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamed_argument_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamed_argument_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Named_argument_memberContext named_argument_member() throws RecognitionException {
		Named_argument_memberContext _localctx = new Named_argument_memberContext(_ctx, getState());
		enterRule(_localctx, 332, RULE_named_argument_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1680);
			named_argument();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Named_argumentContext extends ParserRuleContext {
		public Parameter_redefinitionContext parameter_redefinition() {
			return getRuleContext(Parameter_redefinitionContext.class,0);
		}
		public TerminalNode SYMBOL_ASSIGN() { return getToken(KerMLParser.SYMBOL_ASSIGN, 0); }
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public Named_argumentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_named_argument; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterNamed_argument(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitNamed_argument(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitNamed_argument(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Named_argumentContext named_argument() throws RecognitionException {
		Named_argumentContext _localctx = new Named_argumentContext(_ctx, getState());
		enterRule(_localctx, 334, RULE_named_argument);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1682);
			parameter_redefinition();
			setState(1683);
			match(SYMBOL_ASSIGN);
			setState(1684);
			owned_expression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Parameter_redefinitionContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Parameter_redefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parameter_redefinition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterParameter_redefinition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitParameter_redefinition(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitParameter_redefinition(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Parameter_redefinitionContext parameter_redefinition() throws RecognitionException {
		Parameter_redefinitionContext _localctx = new Parameter_redefinitionContext(_ctx, getState());
		enterRule(_localctx, 336, RULE_parameter_redefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1686);
			qualified_name();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Body_expressionContext extends ParserRuleContext {
		public Expression_body_memberContext expression_body_member() {
			return getRuleContext(Expression_body_memberContext.class,0);
		}
		public Body_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_body_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBody_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBody_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBody_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Body_expressionContext body_expression() throws RecognitionException {
		Body_expressionContext _localctx = new Body_expressionContext(_ctx, getState());
		enterRule(_localctx, 338, RULE_body_expression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1688);
			expression_body_member();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expression_body_memberContext extends ParserRuleContext {
		public Expression_bodyContext expression_body() {
			return getRuleContext(Expression_bodyContext.class,0);
		}
		public Expression_body_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression_body_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterExpression_body_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitExpression_body_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitExpression_body_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Expression_body_memberContext expression_body_member() throws RecognitionException {
		Expression_body_memberContext _localctx = new Expression_body_memberContext(_ctx, getState());
		enterRule(_localctx, 340, RULE_expression_body_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1690);
			expression_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expression_bodyContext extends ParserRuleContext {
		public TerminalNode SYMBOL_CURLY_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_OPEN, 0); }
		public Function_body_partContext function_body_part() {
			return getRuleContext(Function_body_partContext.class,0);
		}
		public TerminalNode SYMBOL_CURLY_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_CLOSE, 0); }
		public Expression_bodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression_body; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterExpression_body(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitExpression_body(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitExpression_body(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Expression_bodyContext expression_body() throws RecognitionException {
		Expression_bodyContext _localctx = new Expression_bodyContext(_ctx, getState());
		enterRule(_localctx, 342, RULE_expression_body);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1692);
			match(SYMBOL_CURLY_BRACKET_OPEN);
			setState(1693);
			function_body_part();
			setState(1694);
			match(SYMBOL_CURLY_BRACKET_CLOSE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Literal_expressionContext extends ParserRuleContext {
		public TerminalNode KEYWORD_TRUE() { return getToken(KerMLParser.KEYWORD_TRUE, 0); }
		public TerminalNode KEYWORD_FALSE() { return getToken(KerMLParser.KEYWORD_FALSE, 0); }
		public Literal_stringContext literal_string() {
			return getRuleContext(Literal_stringContext.class,0);
		}
		public Literal_integerContext literal_integer() {
			return getRuleContext(Literal_integerContext.class,0);
		}
		public Literal_realContext literal_real() {
			return getRuleContext(Literal_realContext.class,0);
		}
		public Literal_infinityContext literal_infinity() {
			return getRuleContext(Literal_infinityContext.class,0);
		}
		public Literal_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterLiteral_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitLiteral_expression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitLiteral_expression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Literal_expressionContext literal_expression() throws RecognitionException {
		Literal_expressionContext _localctx = new Literal_expressionContext(_ctx, getState());
		enterRule(_localctx, 344, RULE_literal_expression);
		try {
			setState(1702);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,174,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1696);
				match(KEYWORD_TRUE);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1697);
				match(KEYWORD_FALSE);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1698);
				literal_string();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1699);
				literal_integer();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(1700);
				literal_real();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(1701);
				literal_infinity();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Literal_booleanContext extends ParserRuleContext {
		public Boolean_valueContext boolean_value() {
			return getRuleContext(Boolean_valueContext.class,0);
		}
		public Literal_booleanContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal_boolean; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterLiteral_boolean(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitLiteral_boolean(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitLiteral_boolean(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Literal_booleanContext literal_boolean() throws RecognitionException {
		Literal_booleanContext _localctx = new Literal_booleanContext(_ctx, getState());
		enterRule(_localctx, 346, RULE_literal_boolean);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1704);
			boolean_value();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Boolean_valueContext extends ParserRuleContext {
		public TerminalNode KEYWORD_TRUE() { return getToken(KerMLParser.KEYWORD_TRUE, 0); }
		public TerminalNode KEYWORD_FALSE() { return getToken(KerMLParser.KEYWORD_FALSE, 0); }
		public Boolean_valueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_boolean_value; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterBoolean_value(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitBoolean_value(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitBoolean_value(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Boolean_valueContext boolean_value() throws RecognitionException {
		Boolean_valueContext _localctx = new Boolean_valueContext(_ctx, getState());
		enterRule(_localctx, 348, RULE_boolean_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1706);
			_la = _input.LA(1);
			if ( !(_la==KEYWORD_FALSE || _la==KEYWORD_TRUE) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Literal_stringContext extends ParserRuleContext {
		public TerminalNode STRING_VALUE() { return getToken(KerMLParser.STRING_VALUE, 0); }
		public Literal_stringContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal_string; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterLiteral_string(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitLiteral_string(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitLiteral_string(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Literal_stringContext literal_string() throws RecognitionException {
		Literal_stringContext _localctx = new Literal_stringContext(_ctx, getState());
		enterRule(_localctx, 350, RULE_literal_string);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1708);
			match(STRING_VALUE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Literal_integerContext extends ParserRuleContext {
		public TerminalNode DECIMAL_VALUE() { return getToken(KerMLParser.DECIMAL_VALUE, 0); }
		public Literal_integerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal_integer; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterLiteral_integer(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitLiteral_integer(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitLiteral_integer(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Literal_integerContext literal_integer() throws RecognitionException {
		Literal_integerContext _localctx = new Literal_integerContext(_ctx, getState());
		enterRule(_localctx, 352, RULE_literal_integer);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1710);
			match(DECIMAL_VALUE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Literal_realContext extends ParserRuleContext {
		public Real_valueContext real_value() {
			return getRuleContext(Real_valueContext.class,0);
		}
		public Literal_realContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal_real; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterLiteral_real(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitLiteral_real(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitLiteral_real(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Literal_realContext literal_real() throws RecognitionException {
		Literal_realContext _localctx = new Literal_realContext(_ctx, getState());
		enterRule(_localctx, 354, RULE_literal_real);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1712);
			real_value();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Real_valueContext extends ParserRuleContext {
		public TerminalNode SYMBOL_DOT() { return getToken(KerMLParser.SYMBOL_DOT, 0); }
		public List<TerminalNode> DECIMAL_VALUE() { return getTokens(KerMLParser.DECIMAL_VALUE); }
		public TerminalNode DECIMAL_VALUE(int i) {
			return getToken(KerMLParser.DECIMAL_VALUE, i);
		}
		public TerminalNode EXPONENTIAL_VALUE() { return getToken(KerMLParser.EXPONENTIAL_VALUE, 0); }
		public Real_valueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_real_value; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterReal_value(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitReal_value(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitReal_value(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Real_valueContext real_value() throws RecognitionException {
		Real_valueContext _localctx = new Real_valueContext(_ctx, getState());
		enterRule(_localctx, 356, RULE_real_value);
		int _la;
		try {
			setState(1720);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_DOT:
			case DECIMAL_VALUE:
				enterOuterAlt(_localctx, 1);
				{
				{
				setState(1715);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==DECIMAL_VALUE) {
					{
					setState(1714);
					match(DECIMAL_VALUE);
					}
				}

				setState(1717);
				match(SYMBOL_DOT);
				setState(1718);
				_la = _input.LA(1);
				if ( !(_la==DECIMAL_VALUE || _la==EXPONENTIAL_VALUE) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				}
				break;
			case EXPONENTIAL_VALUE:
				enterOuterAlt(_localctx, 2);
				{
				setState(1719);
				match(EXPONENTIAL_VALUE);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Literal_infinityContext extends ParserRuleContext {
		public TerminalNode SYMBOL_STAR() { return getToken(KerMLParser.SYMBOL_STAR, 0); }
		public Literal_infinityContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal_infinity; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterLiteral_infinity(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitLiteral_infinity(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitLiteral_infinity(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Literal_infinityContext literal_infinity() throws RecognitionException {
		Literal_infinityContext _localctx = new Literal_infinityContext(_ctx, getState());
		enterRule(_localctx, 358, RULE_literal_infinity);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1722);
			match(SYMBOL_STAR);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class InteractionContext extends ParserRuleContext {
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_INTERACTION() { return getToken(KerMLParser.KEYWORD_INTERACTION, 0); }
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public InteractionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interaction; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterInteraction(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitInteraction(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitInteraction(this);
			else return visitor.visitChildren(this);
		}
	}

	public final InteractionContext interaction() throws RecognitionException {
		InteractionContext _localctx = new InteractionContext(_ctx, getState());
		enterRule(_localctx, 360, RULE_interaction);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1724);
			type_prefix();
			setState(1725);
			match(KEYWORD_INTERACTION);
			setState(1726);
			classifier_declaration();
			setState(1727);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_flowContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_FLOW() { return getToken(KerMLParser.KEYWORD_FLOW, 0); }
		public Item_flow_declarationContext item_flow_declaration() {
			return getRuleContext(Item_flow_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Item_flowContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_flow; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_flow(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_flow(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_flow(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_flowContext item_flow() throws RecognitionException {
		Item_flowContext _localctx = new Item_flowContext(_ctx, getState());
		enterRule(_localctx, 362, RULE_item_flow);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1729);
			feature_prefix();
			setState(1730);
			match(KEYWORD_FLOW);
			setState(1731);
			item_flow_declaration();
			setState(1732);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Succession_item_flowContext extends ParserRuleContext {
		public Feature_prefixContext feature_prefix() {
			return getRuleContext(Feature_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_SUCCESSION() { return getToken(KerMLParser.KEYWORD_SUCCESSION, 0); }
		public TerminalNode KEYWORD_FLOW() { return getToken(KerMLParser.KEYWORD_FLOW, 0); }
		public Item_flow_declarationContext item_flow_declaration() {
			return getRuleContext(Item_flow_declarationContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Succession_item_flowContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_succession_item_flow; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSuccession_item_flow(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSuccession_item_flow(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSuccession_item_flow(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Succession_item_flowContext succession_item_flow() throws RecognitionException {
		Succession_item_flowContext _localctx = new Succession_item_flowContext(_ctx, getState());
		enterRule(_localctx, 364, RULE_succession_item_flow);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1734);
			feature_prefix();
			setState(1735);
			match(KEYWORD_SUCCESSION);
			setState(1736);
			match(KEYWORD_FLOW);
			setState(1737);
			item_flow_declaration();
			setState(1738);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_flow_declarationContext extends ParserRuleContext {
		public Feature_declarationContext feature_declaration() {
			return getRuleContext(Feature_declarationContext.class,0);
		}
		public List<Item_flow_end_memberContext> item_flow_end_member() {
			return getRuleContexts(Item_flow_end_memberContext.class);
		}
		public Item_flow_end_memberContext item_flow_end_member(int i) {
			return getRuleContext(Item_flow_end_memberContext.class,i);
		}
		public TerminalNode KEYWORD_TO() { return getToken(KerMLParser.KEYWORD_TO, 0); }
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public TerminalNode KEYWORD_OF() { return getToken(KerMLParser.KEYWORD_OF, 0); }
		public Item_feature_memberContext item_feature_member() {
			return getRuleContext(Item_feature_memberContext.class,0);
		}
		public TerminalNode KEYWORD_FROM() { return getToken(KerMLParser.KEYWORD_FROM, 0); }
		public TerminalNode KEYWORD_ALL() { return getToken(KerMLParser.KEYWORD_ALL, 0); }
		public Item_flow_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_flow_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_flow_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_flow_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_flow_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_flow_declarationContext item_flow_declaration() throws RecognitionException {
		Item_flow_declarationContext _localctx = new Item_flow_declarationContext(_ctx, getState());
		enterRule(_localctx, 366, RULE_item_flow_declaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1762);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,181,_ctx) ) {
			case 1:
				{
				setState(1740);
				feature_declaration();
				setState(1742);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
					{
					setState(1741);
					value_part();
					}
				}

				setState(1746);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_OF) {
					{
					setState(1744);
					match(KEYWORD_OF);
					setState(1745);
					item_feature_member();
					}
				}

				setState(1753);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_FROM) {
					{
					setState(1748);
					match(KEYWORD_FROM);
					setState(1749);
					item_flow_end_member();
					setState(1750);
					match(KEYWORD_TO);
					setState(1751);
					item_flow_end_member();
					}
				}

				}
				break;
			case 2:
				{
				setState(1756);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_ALL) {
					{
					setState(1755);
					match(KEYWORD_ALL);
					}
				}

				setState(1758);
				item_flow_end_member();
				setState(1759);
				match(KEYWORD_TO);
				setState(1760);
				item_flow_end_member();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_feature_memberContext extends ParserRuleContext {
		public Item_featureContext item_feature() {
			return getRuleContext(Item_featureContext.class,0);
		}
		public Item_feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_feature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_feature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_feature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_feature_memberContext item_feature_member() throws RecognitionException {
		Item_feature_memberContext _localctx = new Item_feature_memberContext(_ctx, getState());
		enterRule(_localctx, 368, RULE_item_feature_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1764);
			item_feature();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_featureContext extends ParserRuleContext {
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public Item_feature_specialization_partContext item_feature_specialization_part() {
			return getRuleContext(Item_feature_specialization_partContext.class,0);
		}
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public Owned_feature_typingContext owned_feature_typing() {
			return getRuleContext(Owned_feature_typingContext.class,0);
		}
		public Multiplicity_boundsContext multiplicity_bounds() {
			return getRuleContext(Multiplicity_boundsContext.class,0);
		}
		public Item_featureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_feature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_feature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_feature(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_feature(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_featureContext item_feature() throws RecognitionException {
		Item_featureContext _localctx = new Item_featureContext(_ctx, getState());
		enterRule(_localctx, 370, RULE_item_feature);
		int _la;
		try {
			setState(1779);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,185,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				{
				setState(1766);
				identification();
				setState(1767);
				item_feature_specialization_part();
				setState(1769);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
					{
					setState(1768);
					value_part();
					}
				}

				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				{
				setState(1771);
				owned_feature_typing();
				setState(1773);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SYMBOL_SQUARE_BRACKET_OPEN) {
					{
					setState(1772);
					multiplicity_bounds();
					}
				}

				}
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				{
				setState(1775);
				multiplicity_bounds();
				setState(1777);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==NAME) {
					{
					setState(1776);
					owned_feature_typing();
					}
				}

				}
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_feature_specialization_partContext extends ParserRuleContext {
		public Multiplicity_partContext multiplicity_part() {
			return getRuleContext(Multiplicity_partContext.class,0);
		}
		public List<Feature_specializationContext> feature_specialization() {
			return getRuleContexts(Feature_specializationContext.class);
		}
		public Feature_specializationContext feature_specialization(int i) {
			return getRuleContext(Feature_specializationContext.class,i);
		}
		public Item_feature_specialization_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_feature_specialization_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_feature_specialization_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_feature_specialization_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_feature_specialization_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_feature_specialization_partContext item_feature_specialization_part() throws RecognitionException {
		Item_feature_specialization_partContext _localctx = new Item_feature_specialization_partContext(_ctx, getState());
		enterRule(_localctx, 372, RULE_item_feature_specialization_part);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1784);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==KEYWORD_IN || _la==KEYWORD_INOUT || ((((_la - 66)) & ~0x3f) == 0 && ((1L << (_la - 66)) & 13229392692512001L) != 0)) {
				{
				{
				setState(1781);
				feature_specialization();
				}
				}
				setState(1786);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			{
			setState(1787);
			multiplicity_part();
			setState(1789);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_IN || _la==KEYWORD_INOUT || ((((_la - 66)) & ~0x3f) == 0 && ((1L << (_la - 66)) & 13229392692512001L) != 0)) {
				{
				setState(1788);
				feature_specialization();
				}
			}

			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_flow_end_memberContext extends ParserRuleContext {
		public Item_flow_endContext item_flow_end() {
			return getRuleContext(Item_flow_endContext.class,0);
		}
		public Item_flow_end_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_flow_end_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_flow_end_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_flow_end_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_flow_end_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_flow_end_memberContext item_flow_end_member() throws RecognitionException {
		Item_flow_end_memberContext _localctx = new Item_flow_end_memberContext(_ctx, getState());
		enterRule(_localctx, 374, RULE_item_flow_end_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1791);
			item_flow_end();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_flow_endContext extends ParserRuleContext {
		public Item_flow_feature_memberContext item_flow_feature_member() {
			return getRuleContext(Item_flow_feature_memberContext.class,0);
		}
		public Owned_reference_subsettingContext owned_reference_subsetting() {
			return getRuleContext(Owned_reference_subsettingContext.class,0);
		}
		public TerminalNode SYMBOL_DOT() { return getToken(KerMLParser.SYMBOL_DOT, 0); }
		public Item_flow_endContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_flow_end; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_flow_end(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_flow_end(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_flow_end(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_flow_endContext item_flow_end() throws RecognitionException {
		Item_flow_endContext _localctx = new Item_flow_endContext(_ctx, getState());
		enterRule(_localctx, 376, RULE_item_flow_end);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1796);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,188,_ctx) ) {
			case 1:
				{
				setState(1793);
				owned_reference_subsetting();
				setState(1794);
				match(SYMBOL_DOT);
				}
				break;
			}
			setState(1798);
			item_flow_feature_member();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_flow_feature_memberContext extends ParserRuleContext {
		public Item_flow_featureContext item_flow_feature() {
			return getRuleContext(Item_flow_featureContext.class,0);
		}
		public Item_flow_feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_flow_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_flow_feature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_flow_feature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_flow_feature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_flow_feature_memberContext item_flow_feature_member() throws RecognitionException {
		Item_flow_feature_memberContext _localctx = new Item_flow_feature_memberContext(_ctx, getState());
		enterRule(_localctx, 378, RULE_item_flow_feature_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1800);
			item_flow_feature();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_flow_featureContext extends ParserRuleContext {
		public Item_flow_redefinitionContext item_flow_redefinition() {
			return getRuleContext(Item_flow_redefinitionContext.class,0);
		}
		public Item_flow_featureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_flow_feature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_flow_feature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_flow_feature(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_flow_feature(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_flow_featureContext item_flow_feature() throws RecognitionException {
		Item_flow_featureContext _localctx = new Item_flow_featureContext(_ctx, getState());
		enterRule(_localctx, 380, RULE_item_flow_feature);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1802);
			item_flow_redefinition();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Item_flow_redefinitionContext extends ParserRuleContext {
		public Qualified_nameContext qualified_name() {
			return getRuleContext(Qualified_nameContext.class,0);
		}
		public Item_flow_redefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_item_flow_redefinition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterItem_flow_redefinition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitItem_flow_redefinition(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitItem_flow_redefinition(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Item_flow_redefinitionContext item_flow_redefinition() throws RecognitionException {
		Item_flow_redefinitionContext _localctx = new Item_flow_redefinitionContext(_ctx, getState());
		enterRule(_localctx, 382, RULE_item_flow_redefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1804);
			qualified_name();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Value_partContext extends ParserRuleContext {
		public Feature_valueContext feature_value() {
			return getRuleContext(Feature_valueContext.class,0);
		}
		public Value_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterValue_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitValue_part(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitValue_part(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Value_partContext value_part() throws RecognitionException {
		Value_partContext _localctx = new Value_partContext(_ctx, getState());
		enterRule(_localctx, 384, RULE_value_part);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1806);
			feature_value();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_valueContext extends ParserRuleContext {
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_ASSIGN() { return getToken(KerMLParser.SYMBOL_ASSIGN, 0); }
		public TerminalNode SYMBOL_DEF_ASSIGN() { return getToken(KerMLParser.SYMBOL_DEF_ASSIGN, 0); }
		public TerminalNode KEYWORD_DEFAULT() { return getToken(KerMLParser.KEYWORD_DEFAULT, 0); }
		public Feature_valueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_value; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_value(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_value(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_value(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_valueContext feature_value() throws RecognitionException {
		Feature_valueContext _localctx = new Feature_valueContext(_ctx, getState());
		enterRule(_localctx, 386, RULE_feature_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1814);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_ASSIGN:
				{
				setState(1808);
				match(SYMBOL_ASSIGN);
				}
				break;
			case SYMBOL_DEF_ASSIGN:
				{
				setState(1809);
				match(SYMBOL_DEF_ASSIGN);
				}
				break;
			case KEYWORD_DEFAULT:
				{
				setState(1810);
				match(KEYWORD_DEFAULT);
				setState(1812);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
					{
					setState(1811);
					_la = _input.LA(1);
					if ( !(_la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					}
				}

				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(1816);
			owned_expression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Feature_assignmentContext extends ParserRuleContext {
		public TerminalNode SYMBOL_ASSIGN() { return getToken(KerMLParser.SYMBOL_ASSIGN, 0); }
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public Feature_assignmentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_feature_assignment; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterFeature_assignment(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitFeature_assignment(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitFeature_assignment(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Feature_assignmentContext feature_assignment() throws RecognitionException {
		Feature_assignmentContext _localctx = new Feature_assignmentContext(_ctx, getState());
		enterRule(_localctx, 388, RULE_feature_assignment);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1818);
			match(SYMBOL_ASSIGN);
			setState(1819);
			owned_expression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MultiplicityContext extends ParserRuleContext {
		public Multiplicity_subsetContext multiplicity_subset() {
			return getRuleContext(Multiplicity_subsetContext.class,0);
		}
		public Multiplicity_rangeContext multiplicity_range() {
			return getRuleContext(Multiplicity_rangeContext.class,0);
		}
		public MultiplicityContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplicity; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMultiplicity(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMultiplicity(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMultiplicity(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MultiplicityContext multiplicity() throws RecognitionException {
		MultiplicityContext _localctx = new MultiplicityContext(_ctx, getState());
		enterRule(_localctx, 390, RULE_multiplicity);
		try {
			setState(1823);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,191,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1821);
				multiplicity_subset();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1822);
				multiplicity_range();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Multiplicity_subsetContext extends ParserRuleContext {
		public TerminalNode KEYWORD_MULTIPLICITY() { return getToken(KerMLParser.KEYWORD_MULTIPLICITY, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public SubsetsContext subsets() {
			return getRuleContext(SubsetsContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Multiplicity_subsetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplicity_subset; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMultiplicity_subset(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMultiplicity_subset(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMultiplicity_subset(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Multiplicity_subsetContext multiplicity_subset() throws RecognitionException {
		Multiplicity_subsetContext _localctx = new Multiplicity_subsetContext(_ctx, getState());
		enterRule(_localctx, 392, RULE_multiplicity_subset);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1825);
			match(KEYWORD_MULTIPLICITY);
			setState(1826);
			identification();
			setState(1827);
			subsets();
			setState(1828);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Multiplicity_rangeContext extends ParserRuleContext {
		public TerminalNode KEYWORD_MULTIPLICITY() { return getToken(KerMLParser.KEYWORD_MULTIPLICITY, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public Multiplicity_boundsContext multiplicity_bounds() {
			return getRuleContext(Multiplicity_boundsContext.class,0);
		}
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public Multiplicity_rangeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplicity_range; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMultiplicity_range(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMultiplicity_range(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMultiplicity_range(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Multiplicity_rangeContext multiplicity_range() throws RecognitionException {
		Multiplicity_rangeContext _localctx = new Multiplicity_rangeContext(_ctx, getState());
		enterRule(_localctx, 394, RULE_multiplicity_range);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1830);
			match(KEYWORD_MULTIPLICITY);
			setState(1831);
			identification();
			setState(1832);
			multiplicity_bounds();
			setState(1833);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_multiplicityContext extends ParserRuleContext {
		public Multiplicity_boundsContext multiplicity_bounds() {
			return getRuleContext(Multiplicity_boundsContext.class,0);
		}
		public Owned_multiplicityContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_multiplicity; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_multiplicity(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_multiplicity(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_multiplicity(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_multiplicityContext owned_multiplicity() throws RecognitionException {
		Owned_multiplicityContext _localctx = new Owned_multiplicityContext(_ctx, getState());
		enterRule(_localctx, 396, RULE_owned_multiplicity);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1835);
			multiplicity_bounds();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Owned_multiplicity_rangeContext extends ParserRuleContext {
		public Multiplicity_boundsContext multiplicity_bounds() {
			return getRuleContext(Multiplicity_boundsContext.class,0);
		}
		public Owned_multiplicity_rangeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_owned_multiplicity_range; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterOwned_multiplicity_range(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitOwned_multiplicity_range(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitOwned_multiplicity_range(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Owned_multiplicity_rangeContext owned_multiplicity_range() throws RecognitionException {
		Owned_multiplicity_rangeContext _localctx = new Owned_multiplicity_rangeContext(_ctx, getState());
		enterRule(_localctx, 398, RULE_owned_multiplicity_range);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1837);
			multiplicity_bounds();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Multiplicity_boundsContext extends ParserRuleContext {
		public TerminalNode SYMBOL_SQUARE_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_SQUARE_BRACKET_OPEN, 0); }
		public List<Multiplicity_expression_memberContext> multiplicity_expression_member() {
			return getRuleContexts(Multiplicity_expression_memberContext.class);
		}
		public Multiplicity_expression_memberContext multiplicity_expression_member(int i) {
			return getRuleContext(Multiplicity_expression_memberContext.class,i);
		}
		public TerminalNode SYMBOL_SQUARE_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_SQUARE_BRACKET_CLOSE, 0); }
		public TerminalNode SYMBOL_DDOT() { return getToken(KerMLParser.SYMBOL_DDOT, 0); }
		public Multiplicity_boundsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplicity_bounds; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMultiplicity_bounds(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMultiplicity_bounds(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMultiplicity_bounds(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Multiplicity_boundsContext multiplicity_bounds() throws RecognitionException {
		Multiplicity_boundsContext _localctx = new Multiplicity_boundsContext(_ctx, getState());
		enterRule(_localctx, 400, RULE_multiplicity_bounds);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1839);
			match(SYMBOL_SQUARE_BRACKET_OPEN);
			setState(1843);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,192,_ctx) ) {
			case 1:
				{
				setState(1840);
				multiplicity_expression_member();
				setState(1841);
				match(SYMBOL_DDOT);
				}
				break;
			}
			setState(1845);
			multiplicity_expression_member();
			setState(1846);
			match(SYMBOL_SQUARE_BRACKET_CLOSE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Multiplicity_expression_memberContext extends ParserRuleContext {
		public Internal_multiplicity_expression_memberContext internal_multiplicity_expression_member() {
			return getRuleContext(Internal_multiplicity_expression_memberContext.class,0);
		}
		public Multiplicity_expression_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplicity_expression_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMultiplicity_expression_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMultiplicity_expression_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMultiplicity_expression_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Multiplicity_expression_memberContext multiplicity_expression_member() throws RecognitionException {
		Multiplicity_expression_memberContext _localctx = new Multiplicity_expression_memberContext(_ctx, getState());
		enterRule(_localctx, 402, RULE_multiplicity_expression_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1848);
			internal_multiplicity_expression_member();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Internal_multiplicity_expression_memberContext extends ParserRuleContext {
		public Literal_expressionContext literal_expression() {
			return getRuleContext(Literal_expressionContext.class,0);
		}
		public Feature_reference_expressionContext feature_reference_expression() {
			return getRuleContext(Feature_reference_expressionContext.class,0);
		}
		public Internal_multiplicity_expression_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_internal_multiplicity_expression_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterInternal_multiplicity_expression_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitInternal_multiplicity_expression_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitInternal_multiplicity_expression_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Internal_multiplicity_expression_memberContext internal_multiplicity_expression_member() throws RecognitionException {
		Internal_multiplicity_expression_memberContext _localctx = new Internal_multiplicity_expression_memberContext(_ctx, getState());
		enterRule(_localctx, 404, RULE_internal_multiplicity_expression_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1852);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case KEYWORD_FALSE:
			case KEYWORD_TRUE:
			case SYMBOL_STAR:
			case SYMBOL_DOT:
			case DECIMAL_VALUE:
			case EXPONENTIAL_VALUE:
			case STRING_VALUE:
				{
				setState(1850);
				literal_expression();
				}
				break;
			case NAME:
				{
				setState(1851);
				feature_reference_expression();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MetaclassContext extends ParserRuleContext {
		public TerminalNode KEYWORD_METACLASS() { return getToken(KerMLParser.KEYWORD_METACLASS, 0); }
		public Type_bodyContext type_body() {
			return getRuleContext(Type_bodyContext.class,0);
		}
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public Classifier_declarationContext classifier_declaration() {
			return getRuleContext(Classifier_declarationContext.class,0);
		}
		public Type_prefixContext type_prefix() {
			return getRuleContext(Type_prefixContext.class,0);
		}
		public List<TerminalNode> NAME() { return getTokens(KerMLParser.NAME); }
		public TerminalNode NAME(int i) {
			return getToken(KerMLParser.NAME, i);
		}
		public Specializes_operatorContext specializes_operator() {
			return getRuleContext(Specializes_operatorContext.class,0);
		}
		public MetaclassContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metaclass; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMetaclass(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMetaclass(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMetaclass(this);
			else return visitor.visitChildren(this);
		}
	}

	public final MetaclassContext metaclass() throws RecognitionException {
		MetaclassContext _localctx = new MetaclassContext(_ctx, getState());
		enterRule(_localctx, 406, RULE_metaclass);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1855);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,194,_ctx) ) {
			case 1:
				{
				setState(1854);
				type_prefix();
				}
				break;
			}
			setState(1857);
			match(KEYWORD_METACLASS);
			setState(1860);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,195,_ctx) ) {
			case 1:
				{
				setState(1858);
				identification();
				}
				break;
			case 2:
				{
				setState(1859);
				classifier_declaration();
				}
				break;
			}
			setState(1863);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==NAME) {
				{
				setState(1862);
				match(NAME);
				}
			}

			setState(1868);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_SPECIALIZES || _la==SYMBOL_SPECIALIZES) {
				{
				setState(1865);
				specializes_operator();
				setState(1866);
				match(NAME);
				}
			}

			setState(1870);
			type_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Prefix_metadata_annotationContext extends ParserRuleContext {
		public TerminalNode SYMBOL_HASHTAG() { return getToken(KerMLParser.SYMBOL_HASHTAG, 0); }
		public Prefix_metadata_featureContext prefix_metadata_feature() {
			return getRuleContext(Prefix_metadata_featureContext.class,0);
		}
		public Prefix_metadata_annotationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prefix_metadata_annotation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterPrefix_metadata_annotation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitPrefix_metadata_annotation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitPrefix_metadata_annotation(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Prefix_metadata_annotationContext prefix_metadata_annotation() throws RecognitionException {
		Prefix_metadata_annotationContext _localctx = new Prefix_metadata_annotationContext(_ctx, getState());
		enterRule(_localctx, 408, RULE_prefix_metadata_annotation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1872);
			match(SYMBOL_HASHTAG);
			setState(1873);
			prefix_metadata_feature();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Prefix_metadata_memberContext extends ParserRuleContext {
		public TerminalNode SYMBOL_HASHTAG() { return getToken(KerMLParser.SYMBOL_HASHTAG, 0); }
		public Prefix_metadata_featureContext prefix_metadata_feature() {
			return getRuleContext(Prefix_metadata_featureContext.class,0);
		}
		public Prefix_metadata_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prefix_metadata_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterPrefix_metadata_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitPrefix_metadata_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitPrefix_metadata_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Prefix_metadata_memberContext prefix_metadata_member() throws RecognitionException {
		Prefix_metadata_memberContext _localctx = new Prefix_metadata_memberContext(_ctx, getState());
		enterRule(_localctx, 410, RULE_prefix_metadata_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1875);
			match(SYMBOL_HASHTAG);
			setState(1876);
			prefix_metadata_feature();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Prefix_metadata_featureContext extends ParserRuleContext {
		public Owned_feature_typingContext owned_feature_typing() {
			return getRuleContext(Owned_feature_typingContext.class,0);
		}
		public Prefix_metadata_featureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prefix_metadata_feature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterPrefix_metadata_feature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitPrefix_metadata_feature(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitPrefix_metadata_feature(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Prefix_metadata_featureContext prefix_metadata_feature() throws RecognitionException {
		Prefix_metadata_featureContext _localctx = new Prefix_metadata_featureContext(_ctx, getState());
		enterRule(_localctx, 412, RULE_prefix_metadata_feature);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1878);
			owned_feature_typing();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Metadata_featureContext extends ParserRuleContext {
		public Metadata_feature_declarationContext metadata_feature_declaration() {
			return getRuleContext(Metadata_feature_declarationContext.class,0);
		}
		public Metadata_bodyContext metadata_body() {
			return getRuleContext(Metadata_bodyContext.class,0);
		}
		public TerminalNode SYMBOL_AT() { return getToken(KerMLParser.SYMBOL_AT, 0); }
		public TerminalNode KEYWORD_METADATA() { return getToken(KerMLParser.KEYWORD_METADATA, 0); }
		public List<Prefix_metadata_memberContext> prefix_metadata_member() {
			return getRuleContexts(Prefix_metadata_memberContext.class);
		}
		public Prefix_metadata_memberContext prefix_metadata_member(int i) {
			return getRuleContext(Prefix_metadata_memberContext.class,i);
		}
		public TerminalNode KEYWORD_ABOUT() { return getToken(KerMLParser.KEYWORD_ABOUT, 0); }
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public List<TerminalNode> SYMBOL_COMMA() { return getTokens(KerMLParser.SYMBOL_COMMA); }
		public TerminalNode SYMBOL_COMMA(int i) {
			return getToken(KerMLParser.SYMBOL_COMMA, i);
		}
		public Metadata_featureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata_feature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMetadata_feature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMetadata_feature(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMetadata_feature(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Metadata_featureContext metadata_feature() throws RecognitionException {
		Metadata_featureContext _localctx = new Metadata_featureContext(_ctx, getState());
		enterRule(_localctx, 414, RULE_metadata_feature);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1883);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_HASHTAG) {
				{
				{
				setState(1880);
				prefix_metadata_member();
				}
				}
				setState(1885);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(1886);
			_la = _input.LA(1);
			if ( !(_la==KEYWORD_METADATA || _la==SYMBOL_AT) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(1887);
			metadata_feature_declaration();
			setState(1897);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_ABOUT) {
				{
				setState(1888);
				match(KEYWORD_ABOUT);
				setState(1889);
				annotation();
				setState(1894);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==SYMBOL_COMMA) {
					{
					{
					setState(1890);
					match(SYMBOL_COMMA);
					setState(1891);
					annotation();
					}
					}
					setState(1896);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			setState(1899);
			metadata_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Metadata_feature_declarationContext extends ParserRuleContext {
		public Owned_feature_typingContext owned_feature_typing() {
			return getRuleContext(Owned_feature_typingContext.class,0);
		}
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public Typed_by_operatorContext typed_by_operator() {
			return getRuleContext(Typed_by_operatorContext.class,0);
		}
		public Metadata_feature_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata_feature_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMetadata_feature_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMetadata_feature_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMetadata_feature_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Metadata_feature_declarationContext metadata_feature_declaration() throws RecognitionException {
		Metadata_feature_declarationContext _localctx = new Metadata_feature_declarationContext(_ctx, getState());
		enterRule(_localctx, 416, RULE_metadata_feature_declaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1904);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,201,_ctx) ) {
			case 1:
				{
				setState(1901);
				identification();
				setState(1902);
				typed_by_operator();
				}
				break;
			}
			setState(1906);
			owned_feature_typing();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Metadata_bodyContext extends ParserRuleContext {
		public TerminalNode SYMBOL_STATEMENT_DELIMITER() { return getToken(KerMLParser.SYMBOL_STATEMENT_DELIMITER, 0); }
		public TerminalNode SYMBOL_CURLY_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_OPEN, 0); }
		public TerminalNode SYMBOL_CURLY_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_CLOSE, 0); }
		public List<Metadata_body_elementContext> metadata_body_element() {
			return getRuleContexts(Metadata_body_elementContext.class);
		}
		public Metadata_body_elementContext metadata_body_element(int i) {
			return getRuleContext(Metadata_body_elementContext.class,i);
		}
		public Metadata_bodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata_body; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMetadata_body(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMetadata_body(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMetadata_body(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Metadata_bodyContext metadata_body() throws RecognitionException {
		Metadata_bodyContext _localctx = new Metadata_bodyContext(_ctx, getState());
		enterRule(_localctx, 418, RULE_metadata_body);
		int _la;
		try {
			setState(1917);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_STATEMENT_DELIMITER:
				enterOuterAlt(_localctx, 1);
				{
				setState(1908);
				match(SYMBOL_STATEMENT_DELIMITER);
				}
				break;
			case SYMBOL_CURLY_BRACKET_OPEN:
				enterOuterAlt(_localctx, 2);
				{
				{
				setState(1909);
				match(SYMBOL_CURLY_BRACKET_OPEN);
				setState(1913);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 944561895282205068L) != 0) || ((((_la - 66)) & ~0x3f) == 0 && ((1L << (_la - 66)) & 4613937831295263611L) != 0) || _la==NAME) {
					{
					{
					setState(1910);
					metadata_body_element();
					}
					}
					setState(1915);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(1916);
				match(SYMBOL_CURLY_BRACKET_CLOSE);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Metadata_body_elementContext extends ParserRuleContext {
		public Non_feature_memberContext non_feature_member() {
			return getRuleContext(Non_feature_memberContext.class,0);
		}
		public Metadata_body_feature_memberContext metadata_body_feature_member() {
			return getRuleContext(Metadata_body_feature_memberContext.class,0);
		}
		public Alias_memberContext alias_member() {
			return getRuleContext(Alias_memberContext.class,0);
		}
		public Import_declarationContext import_declaration() {
			return getRuleContext(Import_declarationContext.class,0);
		}
		public Metadata_body_elementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata_body_element; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMetadata_body_element(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMetadata_body_element(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMetadata_body_element(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Metadata_body_elementContext metadata_body_element() throws RecognitionException {
		Metadata_body_elementContext _localctx = new Metadata_body_elementContext(_ctx, getState());
		enterRule(_localctx, 420, RULE_metadata_body_element);
		try {
			setState(1923);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,204,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1919);
				non_feature_member();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1920);
				metadata_body_feature_member();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1921);
				alias_member();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1922);
				import_declaration();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Metadata_body_feature_memberContext extends ParserRuleContext {
		public Metadata_body_featureContext metadata_body_feature() {
			return getRuleContext(Metadata_body_featureContext.class,0);
		}
		public Metadata_body_feature_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata_body_feature_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMetadata_body_feature_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMetadata_body_feature_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMetadata_body_feature_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Metadata_body_feature_memberContext metadata_body_feature_member() throws RecognitionException {
		Metadata_body_feature_memberContext _localctx = new Metadata_body_feature_memberContext(_ctx, getState());
		enterRule(_localctx, 422, RULE_metadata_body_feature_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1925);
			metadata_body_feature();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Metadata_body_featureContext extends ParserRuleContext {
		public Owned_redefinitionContext owned_redefinition() {
			return getRuleContext(Owned_redefinitionContext.class,0);
		}
		public Metadata_bodyContext metadata_body() {
			return getRuleContext(Metadata_bodyContext.class,0);
		}
		public TerminalNode KEYWORD_FEATURE() { return getToken(KerMLParser.KEYWORD_FEATURE, 0); }
		public Redefines_operatorContext redefines_operator() {
			return getRuleContext(Redefines_operatorContext.class,0);
		}
		public Feature_specialization_partContext feature_specialization_part() {
			return getRuleContext(Feature_specialization_partContext.class,0);
		}
		public Value_partContext value_part() {
			return getRuleContext(Value_partContext.class,0);
		}
		public Metadata_body_featureContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata_body_feature; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMetadata_body_feature(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMetadata_body_feature(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMetadata_body_feature(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Metadata_body_featureContext metadata_body_feature() throws RecognitionException {
		Metadata_body_featureContext _localctx = new Metadata_body_featureContext(_ctx, getState());
		enterRule(_localctx, 424, RULE_metadata_body_feature);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1928);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_FEATURE) {
				{
				setState(1927);
				match(KEYWORD_FEATURE);
				}
			}

			setState(1931);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_REDEFINES || _la==SYMBOL_REDEFINES) {
				{
				setState(1930);
				redefines_operator();
				}
			}

			setState(1933);
			owned_redefinition();
			setState(1935);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1153343717071912960L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & 602919537688447491L) != 0)) {
				{
				setState(1934);
				feature_specialization_part();
				}
			}

			setState(1938);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_DEFAULT || _la==SYMBOL_ASSIGN || _la==SYMBOL_DEF_ASSIGN) {
				{
				setState(1937);
				value_part();
				}
			}

			setState(1940);
			metadata_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PackageContext extends ParserRuleContext {
		public Package_declarationContext package_declaration() {
			return getRuleContext(Package_declarationContext.class,0);
		}
		public Package_bodyContext package_body() {
			return getRuleContext(Package_bodyContext.class,0);
		}
		public List<Prefix_metadata_memberContext> prefix_metadata_member() {
			return getRuleContexts(Prefix_metadata_memberContext.class);
		}
		public Prefix_metadata_memberContext prefix_metadata_member(int i) {
			return getRuleContext(Prefix_metadata_memberContext.class,i);
		}
		public PackageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_package; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterPackage(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitPackage(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitPackage(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PackageContext package_() throws RecognitionException {
		PackageContext _localctx = new PackageContext(_ctx, getState());
		enterRule(_localctx, 426, RULE_package);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1945);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_HASHTAG) {
				{
				{
				setState(1942);
				prefix_metadata_member();
				}
				}
				setState(1947);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(1948);
			package_declaration();
			setState(1949);
			package_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Library_packageContext extends ParserRuleContext {
		public TerminalNode KEYWORD_LIBRARY() { return getToken(KerMLParser.KEYWORD_LIBRARY, 0); }
		public Package_declarationContext package_declaration() {
			return getRuleContext(Package_declarationContext.class,0);
		}
		public Package_bodyContext package_body() {
			return getRuleContext(Package_bodyContext.class,0);
		}
		public TerminalNode KEYWORD_STANDARD() { return getToken(KerMLParser.KEYWORD_STANDARD, 0); }
		public List<Prefix_metadata_memberContext> prefix_metadata_member() {
			return getRuleContexts(Prefix_metadata_memberContext.class);
		}
		public Prefix_metadata_memberContext prefix_metadata_member(int i) {
			return getRuleContext(Prefix_metadata_memberContext.class,i);
		}
		public Library_packageContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_library_package; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterLibrary_package(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitLibrary_package(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitLibrary_package(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Library_packageContext library_package() throws RecognitionException {
		Library_packageContext _localctx = new Library_packageContext(_ctx, getState());
		enterRule(_localctx, 428, RULE_library_package);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1952);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==KEYWORD_STANDARD) {
				{
				setState(1951);
				match(KEYWORD_STANDARD);
				}
			}

			setState(1954);
			match(KEYWORD_LIBRARY);
			setState(1958);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==SYMBOL_HASHTAG) {
				{
				{
				setState(1955);
				prefix_metadata_member();
				}
				}
				setState(1960);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(1961);
			package_declaration();
			setState(1962);
			package_body();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Package_declarationContext extends ParserRuleContext {
		public TerminalNode KEYWORD_PACKAGE() { return getToken(KerMLParser.KEYWORD_PACKAGE, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public Package_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_package_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterPackage_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitPackage_declaration(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitPackage_declaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Package_declarationContext package_declaration() throws RecognitionException {
		Package_declarationContext _localctx = new Package_declarationContext(_ctx, getState());
		enterRule(_localctx, 430, RULE_package_declaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1964);
			match(KEYWORD_PACKAGE);
			setState(1966);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SYMBOL_SMALLER || _la==NAME) {
				{
				setState(1965);
				identification();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Package_bodyContext extends ParserRuleContext {
		public TerminalNode SYMBOL_STATEMENT_DELIMITER() { return getToken(KerMLParser.SYMBOL_STATEMENT_DELIMITER, 0); }
		public TerminalNode SYMBOL_CURLY_BRACKET_OPEN() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_OPEN, 0); }
		public TerminalNode SYMBOL_CURLY_BRACKET_CLOSE() { return getToken(KerMLParser.SYMBOL_CURLY_BRACKET_CLOSE, 0); }
		public List<Namespace_body_elementContext> namespace_body_element() {
			return getRuleContexts(Namespace_body_elementContext.class);
		}
		public Namespace_body_elementContext namespace_body_element(int i) {
			return getRuleContext(Namespace_body_elementContext.class,i);
		}
		public List<Element_filter_memberContext> element_filter_member() {
			return getRuleContexts(Element_filter_memberContext.class);
		}
		public Element_filter_memberContext element_filter_member(int i) {
			return getRuleContext(Element_filter_memberContext.class,i);
		}
		public List<ElementContext> element() {
			return getRuleContexts(ElementContext.class);
		}
		public ElementContext element(int i) {
			return getRuleContext(ElementContext.class,i);
		}
		public Package_bodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_package_body; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterPackage_body(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitPackage_body(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitPackage_body(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Package_bodyContext package_body() throws RecognitionException {
		Package_bodyContext _localctx = new Package_bodyContext(_ctx, getState());
		enterRule(_localctx, 432, RULE_package_body);
		int _la;
		try {
			setState(1979);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_STATEMENT_DELIMITER:
				enterOuterAlt(_localctx, 1);
				{
				setState(1968);
				match(SYMBOL_STATEMENT_DELIMITER);
				}
				break;
			case SYMBOL_CURLY_BRACKET_OPEN:
				enterOuterAlt(_localctx, 2);
				{
				{
				setState(1969);
				match(SYMBOL_CURLY_BRACKET_OPEN);
				setState(1975);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2260739233486464924L) != 0) || ((((_la - 65)) & ~0x3f) == 0 && ((1L << (_la - 65)) & -3999754816522854401L) != 0) || _la==SYMBOL_SMALLER || _la==NAME) {
					{
					setState(1973);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,213,_ctx) ) {
					case 1:
						{
						setState(1970);
						namespace_body_element();
						}
						break;
					case 2:
						{
						setState(1971);
						element_filter_member();
						}
						break;
					case 3:
						{
						setState(1972);
						element();
						}
						break;
					}
					}
					setState(1977);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(1978);
				match(SYMBOL_CURLY_BRACKET_CLOSE);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Element_filter_memberContext extends ParserRuleContext {
		public Member_prefixContext member_prefix() {
			return getRuleContext(Member_prefixContext.class,0);
		}
		public TerminalNode KEYWORD_FILTER() { return getToken(KerMLParser.KEYWORD_FILTER, 0); }
		public Owned_expressionContext owned_expression() {
			return getRuleContext(Owned_expressionContext.class,0);
		}
		public TerminalNode SYMBOL_STATEMENT_DELIMITER() { return getToken(KerMLParser.SYMBOL_STATEMENT_DELIMITER, 0); }
		public Element_filter_memberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_element_filter_member; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterElement_filter_member(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitElement_filter_member(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitElement_filter_member(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Element_filter_memberContext element_filter_member() throws RecognitionException {
		Element_filter_memberContext _localctx = new Element_filter_memberContext(_ctx, getState());
		enterRule(_localctx, 434, RULE_element_filter_member);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1981);
			member_prefix();
			setState(1982);
			match(KEYWORD_FILTER);
			setState(1983);
			owned_expression(0);
			setState(1984);
			match(SYMBOL_STATEMENT_DELIMITER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Meta_assignmentContext extends ParserRuleContext {
		public List<Qualified_nameContext> qualified_name() {
			return getRuleContexts(Qualified_nameContext.class);
		}
		public Qualified_nameContext qualified_name(int i) {
			return getRuleContext(Qualified_nameContext.class,i);
		}
		public TerminalNode SYMBOL_ASSIGN() { return getToken(KerMLParser.SYMBOL_ASSIGN, 0); }
		public IdentificationContext identification() {
			return getRuleContext(IdentificationContext.class,0);
		}
		public TerminalNode KEYWORD_META() { return getToken(KerMLParser.KEYWORD_META, 0); }
		public TerminalNode SYMBOL_STATEMENT_DELIMITER() { return getToken(KerMLParser.SYMBOL_STATEMENT_DELIMITER, 0); }
		public Meta_assignmentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_meta_assignment; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterMeta_assignment(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitMeta_assignment(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitMeta_assignment(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Meta_assignmentContext meta_assignment() throws RecognitionException {
		Meta_assignmentContext _localctx = new Meta_assignmentContext(_ctx, getState());
		enterRule(_localctx, 436, RULE_meta_assignment);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1986);
			qualified_name();
			setState(1987);
			match(SYMBOL_ASSIGN);
			setState(1988);
			identification();
			setState(1989);
			match(KEYWORD_META);
			setState(1990);
			qualified_name();
			setState(1991);
			match(SYMBOL_STATEMENT_DELIMITER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Typed_by_operatorContext extends ParserRuleContext {
		public TerminalNode SYMBOL_TYPED_BY() { return getToken(KerMLParser.SYMBOL_TYPED_BY, 0); }
		public TerminalNode KEYWORD_TYPED() { return getToken(KerMLParser.KEYWORD_TYPED, 0); }
		public TerminalNode KEYWORD_BY() { return getToken(KerMLParser.KEYWORD_BY, 0); }
		public Typed_by_operatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typed_by_operator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterTyped_by_operator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitTyped_by_operator(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitTyped_by_operator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Typed_by_operatorContext typed_by_operator() throws RecognitionException {
		Typed_by_operatorContext _localctx = new Typed_by_operatorContext(_ctx, getState());
		enterRule(_localctx, 438, RULE_typed_by_operator);
		try {
			setState(1996);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SYMBOL_TYPED_BY:
				enterOuterAlt(_localctx, 1);
				{
				setState(1993);
				match(SYMBOL_TYPED_BY);
				}
				break;
			case KEYWORD_TYPED:
				enterOuterAlt(_localctx, 2);
				{
				setState(1994);
				match(KEYWORD_TYPED);
				setState(1995);
				match(KEYWORD_BY);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Specializes_operatorContext extends ParserRuleContext {
		public TerminalNode SYMBOL_SPECIALIZES() { return getToken(KerMLParser.SYMBOL_SPECIALIZES, 0); }
		public TerminalNode KEYWORD_SPECIALIZES() { return getToken(KerMLParser.KEYWORD_SPECIALIZES, 0); }
		public Specializes_operatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_specializes_operator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSpecializes_operator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSpecializes_operator(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSpecializes_operator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Specializes_operatorContext specializes_operator() throws RecognitionException {
		Specializes_operatorContext _localctx = new Specializes_operatorContext(_ctx, getState());
		enterRule(_localctx, 440, RULE_specializes_operator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1998);
			_la = _input.LA(1);
			if ( !(_la==KEYWORD_SPECIALIZES || _la==SYMBOL_SPECIALIZES) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Subsets_operatorContext extends ParserRuleContext {
		public TerminalNode SYMBOL_SPECIALIZES() { return getToken(KerMLParser.SYMBOL_SPECIALIZES, 0); }
		public TerminalNode KEYWORD_SUBSETS() { return getToken(KerMLParser.KEYWORD_SUBSETS, 0); }
		public Subsets_operatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_subsets_operator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterSubsets_operator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitSubsets_operator(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitSubsets_operator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Subsets_operatorContext subsets_operator() throws RecognitionException {
		Subsets_operatorContext _localctx = new Subsets_operatorContext(_ctx, getState());
		enterRule(_localctx, 442, RULE_subsets_operator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(2000);
			_la = _input.LA(1);
			if ( !(_la==KEYWORD_SUBSETS || _la==SYMBOL_SPECIALIZES) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class References_operatorContext extends ParserRuleContext {
		public TerminalNode SYMBOL_REFERENCES() { return getToken(KerMLParser.SYMBOL_REFERENCES, 0); }
		public TerminalNode KEYWORD_REFERENCES() { return getToken(KerMLParser.KEYWORD_REFERENCES, 0); }
		public References_operatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_references_operator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterReferences_operator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitReferences_operator(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitReferences_operator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final References_operatorContext references_operator() throws RecognitionException {
		References_operatorContext _localctx = new References_operatorContext(_ctx, getState());
		enterRule(_localctx, 444, RULE_references_operator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(2002);
			_la = _input.LA(1);
			if ( !(_la==KEYWORD_REFERENCES || _la==SYMBOL_REFERENCES) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Redefines_operatorContext extends ParserRuleContext {
		public TerminalNode SYMBOL_REDEFINES() { return getToken(KerMLParser.SYMBOL_REDEFINES, 0); }
		public TerminalNode KEYWORD_REDEFINES() { return getToken(KerMLParser.KEYWORD_REDEFINES, 0); }
		public Redefines_operatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_redefines_operator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterRedefines_operator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitRedefines_operator(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitRedefines_operator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Redefines_operatorContext redefines_operator() throws RecognitionException {
		Redefines_operatorContext _localctx = new Redefines_operatorContext(_ctx, getState());
		enterRule(_localctx, 446, RULE_redefines_operator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(2004);
			_la = _input.LA(1);
			if ( !(_la==KEYWORD_REDEFINES || _la==SYMBOL_REDEFINES) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Conjugates_operatorContext extends ParserRuleContext {
		public TerminalNode SYMBOL_CONJUGATES() { return getToken(KerMLParser.SYMBOL_CONJUGATES, 0); }
		public TerminalNode KEYWORD_CONJUGATES() { return getToken(KerMLParser.KEYWORD_CONJUGATES, 0); }
		public Conjugates_operatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_conjugates_operator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterConjugates_operator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitConjugates_operator(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitConjugates_operator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Conjugates_operatorContext conjugates_operator() throws RecognitionException {
		Conjugates_operatorContext _localctx = new Conjugates_operatorContext(_ctx, getState());
		enterRule(_localctx, 448, RULE_conjugates_operator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(2006);
			_la = _input.LA(1);
			if ( !(_la==KEYWORD_CONJUGATES || _la==SYMBOL_CONJUGATES) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Crosses_operatorContext extends ParserRuleContext {
		public TerminalNode SYMBOL_CROSSES() { return getToken(KerMLParser.SYMBOL_CROSSES, 0); }
		public TerminalNode KEYWORD_CROSSES() { return getToken(KerMLParser.KEYWORD_CROSSES, 0); }
		public Crosses_operatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_crosses_operator; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).enterCrosses_operator(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof KerMLListener ) ((KerMLListener)listener).exitCrosses_operator(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof KerMLVisitor ) return ((KerMLVisitor<? extends T>)visitor).visitCrosses_operator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Crosses_operatorContext crosses_operator() throws RecognitionException {
		Crosses_operatorContext _localctx = new Crosses_operatorContext(_ctx, getState());
		enterRule(_localctx, 450, RULE_crosses_operator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(2008);
			_la = _input.LA(1);
			if ( !(_la==KEYWORD_CROSSES || _la==SYMBOL_CROSSES) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 141:
			return owned_expression_sempred((Owned_expressionContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean owned_expression_sempred(Owned_expressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 20);
		case 1:
			return precpred(_ctx, 19);
		case 2:
			return precpred(_ctx, 18);
		case 3:
			return precpred(_ctx, 17);
		case 4:
			return precpred(_ctx, 16);
		case 5:
			return precpred(_ctx, 11);
		case 6:
			return precpred(_ctx, 10);
		case 7:
			return precpred(_ctx, 9);
		case 8:
			return precpred(_ctx, 8);
		case 9:
			return precpred(_ctx, 7);
		case 10:
			return precpred(_ctx, 6);
		case 11:
			return precpred(_ctx, 27);
		case 12:
			return precpred(_ctx, 26);
		case 13:
			return precpred(_ctx, 25);
		case 14:
			return precpred(_ctx, 24);
		case 15:
			return precpred(_ctx, 23);
		case 16:
			return precpred(_ctx, 22);
		case 17:
			return precpred(_ctx, 15);
		case 18:
			return precpred(_ctx, 14);
		case 19:
			return precpred(_ctx, 13);
		case 20:
			return precpred(_ctx, 12);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001\u00a0\u07db\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001"+
		"\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004"+
		"\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007"+
		"\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b"+
		"\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007"+
		"\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007"+
		"\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007"+
		"\u0015\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007"+
		"\u0018\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002\u001b\u0007"+
		"\u001b\u0002\u001c\u0007\u001c\u0002\u001d\u0007\u001d\u0002\u001e\u0007"+
		"\u001e\u0002\u001f\u0007\u001f\u0002 \u0007 \u0002!\u0007!\u0002\"\u0007"+
		"\"\u0002#\u0007#\u0002$\u0007$\u0002%\u0007%\u0002&\u0007&\u0002\'\u0007"+
		"\'\u0002(\u0007(\u0002)\u0007)\u0002*\u0007*\u0002+\u0007+\u0002,\u0007"+
		",\u0002-\u0007-\u0002.\u0007.\u0002/\u0007/\u00020\u00070\u00021\u0007"+
		"1\u00022\u00072\u00023\u00073\u00024\u00074\u00025\u00075\u00026\u0007"+
		"6\u00027\u00077\u00028\u00078\u00029\u00079\u0002:\u0007:\u0002;\u0007"+
		";\u0002<\u0007<\u0002=\u0007=\u0002>\u0007>\u0002?\u0007?\u0002@\u0007"+
		"@\u0002A\u0007A\u0002B\u0007B\u0002C\u0007C\u0002D\u0007D\u0002E\u0007"+
		"E\u0002F\u0007F\u0002G\u0007G\u0002H\u0007H\u0002I\u0007I\u0002J\u0007"+
		"J\u0002K\u0007K\u0002L\u0007L\u0002M\u0007M\u0002N\u0007N\u0002O\u0007"+
		"O\u0002P\u0007P\u0002Q\u0007Q\u0002R\u0007R\u0002S\u0007S\u0002T\u0007"+
		"T\u0002U\u0007U\u0002V\u0007V\u0002W\u0007W\u0002X\u0007X\u0002Y\u0007"+
		"Y\u0002Z\u0007Z\u0002[\u0007[\u0002\\\u0007\\\u0002]\u0007]\u0002^\u0007"+
		"^\u0002_\u0007_\u0002`\u0007`\u0002a\u0007a\u0002b\u0007b\u0002c\u0007"+
		"c\u0002d\u0007d\u0002e\u0007e\u0002f\u0007f\u0002g\u0007g\u0002h\u0007"+
		"h\u0002i\u0007i\u0002j\u0007j\u0002k\u0007k\u0002l\u0007l\u0002m\u0007"+
		"m\u0002n\u0007n\u0002o\u0007o\u0002p\u0007p\u0002q\u0007q\u0002r\u0007"+
		"r\u0002s\u0007s\u0002t\u0007t\u0002u\u0007u\u0002v\u0007v\u0002w\u0007"+
		"w\u0002x\u0007x\u0002y\u0007y\u0002z\u0007z\u0002{\u0007{\u0002|\u0007"+
		"|\u0002}\u0007}\u0002~\u0007~\u0002\u007f\u0007\u007f\u0002\u0080\u0007"+
		"\u0080\u0002\u0081\u0007\u0081\u0002\u0082\u0007\u0082\u0002\u0083\u0007"+
		"\u0083\u0002\u0084\u0007\u0084\u0002\u0085\u0007\u0085\u0002\u0086\u0007"+
		"\u0086\u0002\u0087\u0007\u0087\u0002\u0088\u0007\u0088\u0002\u0089\u0007"+
		"\u0089\u0002\u008a\u0007\u008a\u0002\u008b\u0007\u008b\u0002\u008c\u0007"+
		"\u008c\u0002\u008d\u0007\u008d\u0002\u008e\u0007\u008e\u0002\u008f\u0007"+
		"\u008f\u0002\u0090\u0007\u0090\u0002\u0091\u0007\u0091\u0002\u0092\u0007"+
		"\u0092\u0002\u0093\u0007\u0093\u0002\u0094\u0007\u0094\u0002\u0095\u0007"+
		"\u0095\u0002\u0096\u0007\u0096\u0002\u0097\u0007\u0097\u0002\u0098\u0007"+
		"\u0098\u0002\u0099\u0007\u0099\u0002\u009a\u0007\u009a\u0002\u009b\u0007"+
		"\u009b\u0002\u009c\u0007\u009c\u0002\u009d\u0007\u009d\u0002\u009e\u0007"+
		"\u009e\u0002\u009f\u0007\u009f\u0002\u00a0\u0007\u00a0\u0002\u00a1\u0007"+
		"\u00a1\u0002\u00a2\u0007\u00a2\u0002\u00a3\u0007\u00a3\u0002\u00a4\u0007"+
		"\u00a4\u0002\u00a5\u0007\u00a5\u0002\u00a6\u0007\u00a6\u0002\u00a7\u0007"+
		"\u00a7\u0002\u00a8\u0007\u00a8\u0002\u00a9\u0007\u00a9\u0002\u00aa\u0007"+
		"\u00aa\u0002\u00ab\u0007\u00ab\u0002\u00ac\u0007\u00ac\u0002\u00ad\u0007"+
		"\u00ad\u0002\u00ae\u0007\u00ae\u0002\u00af\u0007\u00af\u0002\u00b0\u0007"+
		"\u00b0\u0002\u00b1\u0007\u00b1\u0002\u00b2\u0007\u00b2\u0002\u00b3\u0007"+
		"\u00b3\u0002\u00b4\u0007\u00b4\u0002\u00b5\u0007\u00b5\u0002\u00b6\u0007"+
		"\u00b6\u0002\u00b7\u0007\u00b7\u0002\u00b8\u0007\u00b8\u0002\u00b9\u0007"+
		"\u00b9\u0002\u00ba\u0007\u00ba\u0002\u00bb\u0007\u00bb\u0002\u00bc\u0007"+
		"\u00bc\u0002\u00bd\u0007\u00bd\u0002\u00be\u0007\u00be\u0002\u00bf\u0007"+
		"\u00bf\u0002\u00c0\u0007\u00c0\u0002\u00c1\u0007\u00c1\u0002\u00c2\u0007"+
		"\u00c2\u0002\u00c3\u0007\u00c3\u0002\u00c4\u0007\u00c4\u0002\u00c5\u0007"+
		"\u00c5\u0002\u00c6\u0007\u00c6\u0002\u00c7\u0007\u00c7\u0002\u00c8\u0007"+
		"\u00c8\u0002\u00c9\u0007\u00c9\u0002\u00ca\u0007\u00ca\u0002\u00cb\u0007"+
		"\u00cb\u0002\u00cc\u0007\u00cc\u0002\u00cd\u0007\u00cd\u0002\u00ce\u0007"+
		"\u00ce\u0002\u00cf\u0007\u00cf\u0002\u00d0\u0007\u00d0\u0002\u00d1\u0007"+
		"\u00d1\u0002\u00d2\u0007\u00d2\u0002\u00d3\u0007\u00d3\u0002\u00d4\u0007"+
		"\u00d4\u0002\u00d5\u0007\u00d5\u0002\u00d6\u0007\u00d6\u0002\u00d7\u0007"+
		"\u00d7\u0002\u00d8\u0007\u00d8\u0002\u00d9\u0007\u00d9\u0002\u00da\u0007"+
		"\u00da\u0002\u00db\u0007\u00db\u0002\u00dc\u0007\u00dc\u0002\u00dd\u0007"+
		"\u00dd\u0002\u00de\u0007\u00de\u0002\u00df\u0007\u00df\u0002\u00e0\u0007"+
		"\u00e0\u0002\u00e1\u0007\u00e1\u0001\u0000\u0001\u0000\u0001\u0000\u0001"+
		"\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0005\u0002\u01cd"+
		"\b\u0002\n\u0002\f\u0002\u01d0\t\u0002\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0003\u0003\u01d5\b\u0003\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0003\u0004\u01de\b\u0004\u0001\u0005"+
		"\u0005\u0005\u01e1\b\u0005\n\u0005\f\u0005\u01e4\t\u0005\u0001\u0006\u0001"+
		"\u0006\u0003\u0006\u01e8\b\u0006\u0001\u0007\u0001\u0007\u0003\u0007\u01ec"+
		"\b\u0007\u0001\b\u0005\b\u01ef\b\b\n\b\f\b\u01f2\t\b\u0001\b\u0001\b\u0003"+
		"\b\u01f6\b\b\u0001\b\u0003\b\u01f9\b\b\u0001\b\u0001\b\u0001\b\u0005\b"+
		"\u01fe\b\b\n\b\f\b\u0201\t\b\u0001\b\u0001\b\u0001\b\u0001\b\u0005\b\u0207"+
		"\b\b\n\b\f\b\u020a\t\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\n\u0001\n"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u0216\b\u000b"+
		"\u0001\f\u0001\f\u0003\f\u021a\b\f\u0001\f\u0001\f\u0001\f\u0001\f\u0005"+
		"\f\u0220\b\f\n\f\f\f\u0223\t\f\u0003\f\u0225\b\f\u0003\f\u0227\b\f\u0001"+
		"\f\u0001\f\u0003\f\u022b\b\f\u0001\f\u0001\f\u0001\r\u0001\r\u0003\r\u0231"+
		"\b\r\u0001\r\u0001\r\u0003\r\u0235\b\r\u0001\r\u0001\r\u0001\u000e\u0001"+
		"\u000e\u0003\u000e\u023b\b\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000f\u0001\u000f\u0001\u0010\u0005\u0010\u0244\b\u0010\n"+
		"\u0010\f\u0010\u0247\t\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0003\u0012\u0254\b\u0012\u0001\u0013\u0001\u0013\u0001"+
		"\u0014\u0001\u0014\u0001\u0014\u0003\u0014\u025b\b\u0014\u0001\u0015\u0003"+
		"\u0015\u025e\b\u0015\u0001\u0016\u0001\u0016\u0001\u0017\u0001\u0017\u0003"+
		"\u0017\u0264\b\u0017\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0019\u0001"+
		"\u0019\u0001\u0019\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001a\u0001"+
		"\u001a\u0003\u001a\u0271\b\u001a\u0001\u001a\u0003\u001a\u0274\b\u001a"+
		"\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001b\u0001\u001b"+
		"\u0001\u001b\u0005\u001b\u027d\b\u001b\n\u001b\f\u001b\u0280\t\u001b\u0001"+
		"\u001c\u0003\u001c\u0283\b\u001c\u0001\u001c\u0001\u001c\u0003\u001c\u0287"+
		"\b\u001c\u0001\u001c\u0001\u001c\u0001\u001c\u0001\u001d\u0001\u001d\u0003"+
		"\u001d\u028e\b\u001d\u0001\u001e\u0001\u001e\u0003\u001e\u0292\b\u001e"+
		"\u0001\u001e\u0003\u001e\u0295\b\u001e\u0001\u001f\u0001\u001f\u0001\u001f"+
		"\u0001 \u0001 \u0001 \u0001 \u0001!\u0001!\u0001!\u0001!\u0003!\u02a2"+
		"\b!\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001"+
		"\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001"+
		"\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001"+
		"\"\u0003\"\u02bf\b\"\u0001#\u0001#\u0001#\u0001#\u0001#\u0001#\u0001#"+
		"\u0001#\u0001#\u0001#\u0003#\u02cb\b#\u0001$\u0001$\u0001%\u0001%\u0001"+
		"%\u0001%\u0001%\u0001&\u0003&\u02d5\b&\u0001&\u0005&\u02d8\b&\n&\f&\u02db"+
		"\t&\u0001\'\u0003\'\u02de\b\'\u0001\'\u0001\'\u0003\'\u02e2\b\'\u0001"+
		"\'\u0001\'\u0004\'\u02e6\b\'\u000b\'\f\'\u02e7\u0001\'\u0005\'\u02eb\b"+
		"\'\n\'\f\'\u02ee\t\'\u0001(\u0001(\u0001(\u0001(\u0005(\u02f4\b(\n(\f"+
		"(\u02f7\t(\u0001)\u0001)\u0001)\u0001*\u0001*\u0001*\u0001*\u0003*\u0300"+
		"\b*\u0001+\u0001+\u0001+\u0001+\u0001+\u0005+\u0307\b+\n+\f+\u030a\t+"+
		"\u0001,\u0001,\u0001,\u0001,\u0005,\u0310\b,\n,\f,\u0313\t,\u0001-\u0001"+
		"-\u0001-\u0001-\u0005-\u0319\b-\n-\f-\u031c\t-\u0001.\u0001.\u0001.\u0001"+
		".\u0005.\u0322\b.\n.\f.\u0325\t.\u0001/\u0001/\u0001/\u0001/\u0001/\u0003"+
		"/\u032c\b/\u00010\u00050\u032f\b0\n0\f0\u0332\t0\u00011\u00011\u00011"+
		"\u00011\u00031\u0338\b1\u00012\u00012\u00032\u033c\b2\u00012\u00012\u0001"+
		"2\u00012\u00012\u00012\u00013\u00013\u00014\u00014\u00034\u0348\b4\u0001"+
		"5\u00015\u00035\u034c\b5\u00016\u00016\u00036\u0350\b6\u00016\u00016\u0001"+
		"6\u00036\u0355\b6\u00016\u00016\u00016\u00036\u035a\b6\u00016\u00016\u0001"+
		"7\u00017\u00037\u0360\b7\u00018\u00018\u00038\u0364\b8\u00018\u00018\u0001"+
		"8\u00038\u0369\b8\u00018\u00018\u00018\u00038\u036e\b8\u00018\u00018\u0001"+
		"9\u00019\u00039\u0374\b9\u0001:\u0001:\u0003:\u0378\b:\u0001;\u0001;\u0003"+
		";\u037c\b;\u0001<\u0001<\u0003<\u0380\b<\u0001=\u0001=\u0003=\u0384\b"+
		"=\u0001>\u0001>\u0001>\u0001>\u0001?\u0001?\u0001?\u0001@\u0003@\u038e"+
		"\b@\u0001@\u0001@\u0001@\u0001@\u0001A\u0003A\u0395\bA\u0001A\u0001A\u0003"+
		"A\u0399\bA\u0001A\u0001A\u0003A\u039d\bA\u0001A\u0005A\u03a0\bA\nA\fA"+
		"\u03a3\tA\u0001B\u0001B\u0001B\u0001B\u0005B\u03a9\bB\nB\fB\u03ac\tB\u0001"+
		"C\u0001C\u0003C\u03b0\bC\u0001C\u0001C\u0001C\u0001C\u0001C\u0001C\u0001"+
		"D\u0001D\u0001E\u0001E\u0001E\u0003E\u03bd\bE\u0001E\u0003E\u03c0\bE\u0001"+
		"E\u0003E\u03c3\bE\u0001E\u0001E\u0001E\u0003E\u03c8\bE\u0001F\u0001F\u0003"+
		"F\u03cc\bF\u0001F\u0001F\u0003F\u03d0\bF\u0001F\u0001F\u0001G\u0001G\u0003"+
		"G\u03d6\bG\u0001G\u0003G\u03d9\bG\u0001G\u0005G\u03dc\bG\nG\fG\u03df\t"+
		"G\u0001H\u0003H\u03e2\bH\u0001H\u0001H\u0001I\u0003I\u03e7\bI\u0001I\u0003"+
		"I\u03ea\bI\u0001I\u0003I\u03ed\bI\u0001I\u0003I\u03f0\bI\u0001I\u0003"+
		"I\u03f3\bI\u0001J\u0001J\u0001K\u0001K\u0001K\u0001L\u0001L\u0001M\u0003"+
		"M\u03fd\bM\u0001M\u0001M\u0001M\u0003M\u0402\bM\u0001M\u0001M\u0003M\u0406"+
		"\bM\u0001M\u0005M\u0409\bM\nM\fM\u040c\tM\u0001N\u0001N\u0001N\u0001N"+
		"\u0003N\u0412\bN\u0001N\u0003N\u0415\bN\u0001O\u0001O\u0001O\u0001O\u0003"+
		"O\u041b\bO\u0001P\u0001P\u0001P\u0003P\u0420\bP\u0001Q\u0001Q\u0001Q\u0001"+
		"Q\u0001R\u0001R\u0001R\u0001R\u0001R\u0005R\u042b\bR\nR\fR\u042e\tR\u0001"+
		"S\u0004S\u0431\bS\u000bS\fS\u0432\u0001S\u0001S\u0005S\u0437\bS\nS\fS"+
		"\u043a\tS\u0003S\u043c\bS\u0001S\u0001S\u0005S\u0440\bS\nS\fS\u0443\t"+
		"S\u0003S\u0445\bS\u0001T\u0001T\u0003T\u0449\bT\u0001T\u0001T\u0003T\u044d"+
		"\bT\u0001T\u0001T\u0003T\u0451\bT\u0003T\u0453\bT\u0003T\u0455\bT\u0001"+
		"U\u0001U\u0001V\u0001V\u0001V\u0001V\u0001V\u0003V\u045e\bV\u0001W\u0001"+
		"W\u0001W\u0005W\u0463\bW\nW\fW\u0466\tW\u0001X\u0001X\u0001X\u0001Y\u0001"+
		"Y\u0001Y\u0005Y\u046e\bY\nY\fY\u0471\tY\u0001Z\u0001Z\u0001Z\u0001[\u0001"+
		"[\u0001[\u0001\\\u0001\\\u0001\\\u0001]\u0001]\u0001]\u0005]\u047f\b]"+
		"\n]\f]\u0482\t]\u0001^\u0003^\u0485\b^\u0001^\u0001^\u0001^\u0001_\u0001"+
		"_\u0003_\u048c\b_\u0001_\u0001_\u0001_\u0001_\u0001_\u0001_\u0001`\u0001"+
		"`\u0001a\u0001a\u0003a\u0498\ba\u0001a\u0003a\u049b\ba\u0001a\u0001a\u0001"+
		"a\u0001a\u0003a\u04a1\ba\u0001a\u0001a\u0001b\u0001b\u0001c\u0001c\u0001"+
		"d\u0001d\u0001e\u0003e\u04ac\be\u0001e\u0001e\u0003e\u04b0\be\u0001e\u0001"+
		"e\u0003e\u04b4\be\u0001e\u0001e\u0001e\u0003e\u04b9\be\u0001e\u0003e\u04bc"+
		"\be\u0001e\u0003e\u04bf\be\u0001e\u0003e\u04c2\be\u0001e\u0001e\u0001"+
		"f\u0001f\u0001g\u0001g\u0001h\u0001h\u0001h\u0004h\u04cd\bh\u000bh\fh"+
		"\u04ce\u0001i\u0001i\u0001j\u0001j\u0003j\u04d5\bj\u0001j\u0001j\u0001"+
		"j\u0003j\u04da\bj\u0001j\u0001j\u0001j\u0003j\u04df\bj\u0001j\u0001j\u0001"+
		"k\u0001k\u0003k\u04e5\bk\u0001l\u0001l\u0001l\u0001l\u0003l\u04eb\bl\u0001"+
		"l\u0001l\u0001l\u0001l\u0001l\u0001m\u0001m\u0001n\u0001n\u0001n\u0001"+
		"n\u0001n\u0001o\u0001o\u0001o\u0001o\u0001o\u0001p\u0003p\u04ff\bp\u0001"+
		"p\u0001p\u0001p\u0001p\u0001q\u0001q\u0001q\u0001q\u0001q\u0001r\u0001"+
		"r\u0001r\u0001r\u0001r\u0001r\u0001s\u0001s\u0001s\u0003s\u0513\bs\u0001"+
		"s\u0003s\u0516\bs\u0001s\u0003s\u0519\bs\u0001s\u0001s\u0001t\u0001t\u0003"+
		"t\u051f\bt\u0001u\u0003u\u0522\bu\u0001u\u0001u\u0001u\u0003u\u0527\b"+
		"u\u0003u\u0529\bu\u0001u\u0001u\u0001u\u0001u\u0001v\u0003v\u0530\bv\u0001"+
		"v\u0001v\u0001v\u0001v\u0001v\u0001v\u0005v\u0538\bv\nv\fv\u053b\tv\u0001"+
		"v\u0001v\u0001w\u0001w\u0001x\u0003x\u0542\bx\u0001x\u0001x\u0003x\u0546"+
		"\bx\u0001x\u0001x\u0001y\u0001y\u0001z\u0001z\u0001{\u0001{\u0001{\u0001"+
		"{\u0001{\u0001|\u0001|\u0001|\u0001|\u0001|\u0001|\u0003|\u0559\b|\u0001"+
		"|\u0003|\u055c\b|\u0001|\u0003|\u055f\b|\u0001|\u0001|\u0001|\u0001|\u0003"+
		"|\u0565\b|\u0003|\u0567\b|\u0001}\u0001}\u0001}\u0001}\u0001}\u0001~\u0001"+
		"~\u0001~\u0001~\u0001~\u0001~\u0003~\u0574\b~\u0001~\u0003~\u0577\b~\u0001"+
		"~\u0003~\u057a\b~\u0001~\u0001~\u0001~\u0001~\u0003~\u0580\b~\u0003~\u0582"+
		"\b~\u0001\u007f\u0001\u007f\u0001\u007f\u0001\u007f\u0001\u007f\u0001"+
		"\u0080\u0001\u0080\u0001\u0080\u0001\u0080\u0003\u0080\u058d\b\u0080\u0001"+
		"\u0080\u0001\u0080\u0001\u0081\u0001\u0081\u0001\u0081\u0001\u0081\u0001"+
		"\u0081\u0001\u0082\u0001\u0082\u0001\u0082\u0001\u0082\u0001\u0082\u0003"+
		"\u0082\u059b\b\u0082\u0001\u0083\u0001\u0083\u0005\u0083\u059f\b\u0083"+
		"\n\u0083\f\u0083\u05a2\t\u0083\u0001\u0083\u0003\u0083\u05a5\b\u0083\u0001"+
		"\u0084\u0001\u0084\u0001\u0084\u0001\u0084\u0001\u0085\u0001\u0085\u0001"+
		"\u0085\u0001\u0086\u0001\u0086\u0001\u0086\u0001\u0086\u0003\u0086\u05b2"+
		"\b\u0086\u0001\u0086\u0001\u0086\u0001\u0087\u0001\u0087\u0001\u0087\u0001"+
		"\u0087\u0001\u0087\u0001\u0088\u0001\u0088\u0001\u0088\u0001\u0088\u0003"+
		"\u0088\u05bf\b\u0088\u0001\u0088\u0001\u0088\u0001\u0089\u0001\u0089\u0001"+
		"\u0089\u0003\u0089\u05c6\b\u0089\u0001\u0089\u0003\u0089\u05c9\b\u0089"+
		"\u0001\u0089\u0003\u0089\u05cc\b\u0089\u0001\u0089\u0001\u0089\u0001\u008a"+
		"\u0001\u008a\u0001\u008b\u0001\u008b\u0001\u008c\u0001\u008c\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0003\u008d\u05e6\b\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d\u0001\u008d"+
		"\u0001\u008d\u0001\u008d\u0001\u008d\u0005\u008d\u062e\b\u008d\n\u008d"+
		"\f\u008d\u0631\t\u008d\u0001\u008e\u0001\u008e\u0001\u008e\u0003\u008e"+
		"\u0636\b\u008e\u0001\u008f\u0001\u008f\u0001\u0090\u0001\u0090\u0001\u0091"+
		"\u0001\u0091\u0001\u0092\u0001\u0092\u0001\u0093\u0001\u0093\u0001\u0093"+
		"\u0001\u0093\u0001\u0094\u0001\u0094\u0001\u0094\u0003\u0094\u0647\b\u0094"+
		"\u0003\u0094\u0649\b\u0094\u0001\u0095\u0001\u0095\u0001\u0095\u0001\u0095"+
		"\u0001\u0096\u0001\u0096\u0001\u0097\u0001\u0097\u0001\u0098\u0001\u0098"+
		"\u0003\u0098\u0655\b\u0098\u0001\u0099\u0001\u0099\u0001\u009a\u0001\u009a"+
		"\u0001\u009a\u0001\u009a\u0001\u009a\u0001\u009a\u0001\u009a\u0003\u009a"+
		"\u0660\b\u009a\u0001\u009b\u0001\u009b\u0001\u009b\u0003\u009b\u0665\b"+
		"\u009b\u0001\u009c\u0001\u009c\u0001\u009d\u0001\u009d\u0001\u009e\u0001"+
		"\u009e\u0001\u009f\u0001\u009f\u0001\u009f\u0001\u009f\u0001\u00a0\u0001"+
		"\u00a0\u0001\u00a1\u0001\u00a1\u0001\u00a1\u0001\u00a2\u0001\u00a2\u0001"+
		"\u00a2\u0001\u00a2\u0001\u00a3\u0001\u00a3\u0001\u00a3\u0003\u00a3\u067d"+
		"\b\u00a3\u0001\u00a3\u0001\u00a3\u0001\u00a4\u0001\u00a4\u0001\u00a4\u0005"+
		"\u00a4\u0684\b\u00a4\n\u00a4\f\u00a4\u0687\t\u00a4\u0001\u00a5\u0001\u00a5"+
		"\u0001\u00a5\u0005\u00a5\u068c\b\u00a5\n\u00a5\f\u00a5\u068f\t\u00a5\u0001"+
		"\u00a6\u0001\u00a6\u0001\u00a7\u0001\u00a7\u0001\u00a7\u0001\u00a7\u0001"+
		"\u00a8\u0001\u00a8\u0001\u00a9\u0001\u00a9\u0001\u00aa\u0001\u00aa\u0001"+
		"\u00ab\u0001\u00ab\u0001\u00ab\u0001\u00ab\u0001\u00ac\u0001\u00ac\u0001"+
		"\u00ac\u0001\u00ac\u0001\u00ac\u0001\u00ac\u0003\u00ac\u06a7\b\u00ac\u0001"+
		"\u00ad\u0001\u00ad\u0001\u00ae\u0001\u00ae\u0001\u00af\u0001\u00af\u0001"+
		"\u00b0\u0001\u00b0\u0001\u00b1\u0001\u00b1\u0001\u00b2\u0003\u00b2\u06b4"+
		"\b\u00b2\u0001\u00b2\u0001\u00b2\u0001\u00b2\u0003\u00b2\u06b9\b\u00b2"+
		"\u0001\u00b3\u0001\u00b3\u0001\u00b4\u0001\u00b4\u0001\u00b4\u0001\u00b4"+
		"\u0001\u00b4\u0001\u00b5\u0001\u00b5\u0001\u00b5\u0001\u00b5\u0001\u00b5"+
		"\u0001\u00b6\u0001\u00b6\u0001\u00b6\u0001\u00b6\u0001\u00b6\u0001\u00b6"+
		"\u0001\u00b7\u0001\u00b7\u0003\u00b7\u06cf\b\u00b7\u0001\u00b7\u0001\u00b7"+
		"\u0003\u00b7\u06d3\b\u00b7\u0001\u00b7\u0001\u00b7\u0001\u00b7\u0001\u00b7"+
		"\u0001\u00b7\u0003\u00b7\u06da\b\u00b7\u0001\u00b7\u0003\u00b7\u06dd\b"+
		"\u00b7\u0001\u00b7\u0001\u00b7\u0001\u00b7\u0001\u00b7\u0003\u00b7\u06e3"+
		"\b\u00b7\u0001\u00b8\u0001\u00b8\u0001\u00b9\u0001\u00b9\u0001\u00b9\u0003"+
		"\u00b9\u06ea\b\u00b9\u0001\u00b9\u0001\u00b9\u0003\u00b9\u06ee\b\u00b9"+
		"\u0001\u00b9\u0001\u00b9\u0003\u00b9\u06f2\b\u00b9\u0003\u00b9\u06f4\b"+
		"\u00b9\u0001\u00ba\u0005\u00ba\u06f7\b\u00ba\n\u00ba\f\u00ba\u06fa\t\u00ba"+
		"\u0001\u00ba\u0001\u00ba\u0003\u00ba\u06fe\b\u00ba\u0001\u00bb\u0001\u00bb"+
		"\u0001\u00bc\u0001\u00bc\u0001\u00bc\u0003\u00bc\u0705\b\u00bc\u0001\u00bc"+
		"\u0001\u00bc\u0001\u00bd\u0001\u00bd\u0001\u00be\u0001\u00be\u0001\u00bf"+
		"\u0001\u00bf\u0001\u00c0\u0001\u00c0\u0001\u00c1\u0001\u00c1\u0001\u00c1"+
		"\u0001\u00c1\u0003\u00c1\u0715\b\u00c1\u0003\u00c1\u0717\b\u00c1\u0001"+
		"\u00c1\u0001\u00c1\u0001\u00c2\u0001\u00c2\u0001\u00c2\u0001\u00c3\u0001"+
		"\u00c3\u0003\u00c3\u0720\b\u00c3\u0001\u00c4\u0001\u00c4\u0001\u00c4\u0001"+
		"\u00c4\u0001\u00c4\u0001\u00c5\u0001\u00c5\u0001\u00c5\u0001\u00c5\u0001"+
		"\u00c5\u0001\u00c6\u0001\u00c6\u0001\u00c7\u0001\u00c7\u0001\u00c8\u0001"+
		"\u00c8\u0001\u00c8\u0001\u00c8\u0003\u00c8\u0734\b\u00c8\u0001\u00c8\u0001"+
		"\u00c8\u0001\u00c8\u0001\u00c9\u0001\u00c9\u0001\u00ca\u0001\u00ca\u0003"+
		"\u00ca\u073d\b\u00ca\u0001\u00cb\u0003\u00cb\u0740\b\u00cb\u0001\u00cb"+
		"\u0001\u00cb\u0001\u00cb\u0003\u00cb\u0745\b\u00cb\u0001\u00cb\u0003\u00cb"+
		"\u0748\b\u00cb\u0001\u00cb\u0001\u00cb\u0001\u00cb\u0003\u00cb\u074d\b"+
		"\u00cb\u0001\u00cb\u0001\u00cb\u0001\u00cc\u0001\u00cc\u0001\u00cc\u0001"+
		"\u00cd\u0001\u00cd\u0001\u00cd\u0001\u00ce\u0001\u00ce\u0001\u00cf\u0005"+
		"\u00cf\u075a\b\u00cf\n\u00cf\f\u00cf\u075d\t\u00cf\u0001\u00cf\u0001\u00cf"+
		"\u0001\u00cf\u0001\u00cf\u0001\u00cf\u0001\u00cf\u0005\u00cf\u0765\b\u00cf"+
		"\n\u00cf\f\u00cf\u0768\t\u00cf\u0003\u00cf\u076a\b\u00cf\u0001\u00cf\u0001"+
		"\u00cf\u0001\u00d0\u0001\u00d0\u0001\u00d0\u0003\u00d0\u0771\b\u00d0\u0001"+
		"\u00d0\u0001\u00d0\u0001\u00d1\u0001\u00d1\u0001\u00d1\u0005\u00d1\u0778"+
		"\b\u00d1\n\u00d1\f\u00d1\u077b\t\u00d1\u0001\u00d1\u0003\u00d1\u077e\b"+
		"\u00d1\u0001\u00d2\u0001\u00d2\u0001\u00d2\u0001\u00d2\u0003\u00d2\u0784"+
		"\b\u00d2\u0001\u00d3\u0001\u00d3\u0001\u00d4\u0003\u00d4\u0789\b\u00d4"+
		"\u0001\u00d4\u0003\u00d4\u078c\b\u00d4\u0001\u00d4\u0001\u00d4\u0003\u00d4"+
		"\u0790\b\u00d4\u0001\u00d4\u0003\u00d4\u0793\b\u00d4\u0001\u00d4\u0001"+
		"\u00d4\u0001\u00d5\u0005\u00d5\u0798\b\u00d5\n\u00d5\f\u00d5\u079b\t\u00d5"+
		"\u0001\u00d5\u0001\u00d5\u0001\u00d5\u0001\u00d6\u0003\u00d6\u07a1\b\u00d6"+
		"\u0001\u00d6\u0001\u00d6\u0005\u00d6\u07a5\b\u00d6\n\u00d6\f\u00d6\u07a8"+
		"\t\u00d6\u0001\u00d6\u0001\u00d6\u0001\u00d6\u0001\u00d7\u0001\u00d7\u0003"+
		"\u00d7\u07af\b\u00d7\u0001\u00d8\u0001\u00d8\u0001\u00d8\u0001\u00d8\u0001"+
		"\u00d8\u0005\u00d8\u07b6\b\u00d8\n\u00d8\f\u00d8\u07b9\t\u00d8\u0001\u00d8"+
		"\u0003\u00d8\u07bc\b\u00d8\u0001\u00d9\u0001\u00d9\u0001\u00d9\u0001\u00d9"+
		"\u0001\u00d9\u0001\u00da\u0001\u00da\u0001\u00da\u0001\u00da\u0001\u00da"+
		"\u0001\u00da\u0001\u00da\u0001\u00db\u0001\u00db\u0001\u00db\u0003\u00db"+
		"\u07cd\b\u00db\u0001\u00dc\u0001\u00dc\u0001\u00dd\u0001\u00dd\u0001\u00de"+
		"\u0001\u00de\u0001\u00df\u0001\u00df\u0001\u00e0\u0001\u00e0\u0001\u00e1"+
		"\u0001\u00e1\u0001\u00e1\u0000\u0001\u011a\u00e2\u0000\u0002\u0004\u0006"+
		"\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c\u001e \"$&(*,."+
		"02468:<>@BDFHJLNPRTVXZ\\^`bdfhjlnprtvxz|~\u0080\u0082\u0084\u0086\u0088"+
		"\u008a\u008c\u008e\u0090\u0092\u0094\u0096\u0098\u009a\u009c\u009e\u00a0"+
		"\u00a2\u00a4\u00a6\u00a8\u00aa\u00ac\u00ae\u00b0\u00b2\u00b4\u00b6\u00b8"+
		"\u00ba\u00bc\u00be\u00c0\u00c2\u00c4\u00c6\u00c8\u00ca\u00cc\u00ce\u00d0"+
		"\u00d2\u00d4\u00d6\u00d8\u00da\u00dc\u00de\u00e0\u00e2\u00e4\u00e6\u00e8"+
		"\u00ea\u00ec\u00ee\u00f0\u00f2\u00f4\u00f6\u00f8\u00fa\u00fc\u00fe\u0100"+
		"\u0102\u0104\u0106\u0108\u010a\u010c\u010e\u0110\u0112\u0114\u0116\u0118"+
		"\u011a\u011c\u011e\u0120\u0122\u0124\u0126\u0128\u012a\u012c\u012e\u0130"+
		"\u0132\u0134\u0136\u0138\u013a\u013c\u013e\u0140\u0142\u0144\u0146\u0148"+
		"\u014a\u014c\u014e\u0150\u0152\u0154\u0156\u0158\u015a\u015c\u015e\u0160"+
		"\u0162\u0164\u0166\u0168\u016a\u016c\u016e\u0170\u0172\u0174\u0176\u0178"+
		"\u017a\u017c\u017e\u0180\u0182\u0184\u0186\u0188\u018a\u018c\u018e\u0190"+
		"\u0192\u0194\u0196\u0198\u019a\u019c\u019e\u01a0\u01a2\u01a4\u01a6\u01a8"+
		"\u01aa\u01ac\u01ae\u01b0\u01b2\u01b4\u01b6\u01b8\u01ba\u01bc\u01be\u01c0"+
		"\u01c2\u0000\u001a\u0001\u0000FH\u0002\u0000pp\u0085\u0085\u0002\u0000"+
		"\u0010\u0010DD\u0003\u0000II``dd\u0002\u0000/0BB\u0002\u0000<<AA\u0002"+
		"\u0000  ZZ\u0003\u0000==vv\u0086\u0087\u0004\u0000\u0006\u0006**55\u007f"+
		"\u007f\u0002\u0000\u0083\u0083\u0085\u0085\u0003\u0000pp\u0081\u0081\u0088"+
		"\u0088\u0001\u0000\u0086\u0087\u0002\u0000\u008c\u008d\u0094\u0095\u0001"+
		"\u0000\u0090\u0093\u0002\u0000\u0005\u0005\u0082\u0082\u0002\u0000@@\u0084"+
		"\u0084\u0003\u0000**55\u007f\u007f\u0001\u0000\u009d\u009e\u0001\u0000"+
		"\u008e\u008f\u0002\u000099\u007f\u007f\u0002\u0000PPss\u0002\u0000UUs"+
		"s\u0002\u0000LLtt\u0002\u0000JJuu\u0002\u0000\u0012\u0012vv\u0002\u0000"+
		"ffww\u0829\u0000\u01c4\u0001\u0000\u0000\u0000\u0002\u01c7\u0001\u0000"+
		"\u0000\u0000\u0004\u01ce\u0001\u0000\u0000\u0000\u0006\u01d4\u0001\u0000"+
		"\u0000\u0000\b\u01dd\u0001\u0000\u0000\u0000\n\u01e2\u0001\u0000\u0000"+
		"\u0000\f\u01e7\u0001\u0000\u0000\u0000\u000e\u01eb\u0001\u0000\u0000\u0000"+
		"\u0010\u01f0\u0001\u0000\u0000\u0000\u0012\u020d\u0001\u0000\u0000\u0000"+
		"\u0014\u020f\u0001\u0000\u0000\u0000\u0016\u0215\u0001\u0000\u0000\u0000"+
		"\u0018\u0226\u0001\u0000\u0000\u0000\u001a\u022e\u0001\u0000\u0000\u0000"+
		"\u001c\u023a\u0001\u0000\u0000\u0000\u001e\u0240\u0001\u0000\u0000\u0000"+
		" \u0245\u0001\u0000\u0000\u0000\"\u024b\u0001\u0000\u0000\u0000$\u0253"+
		"\u0001\u0000\u0000\u0000&\u0255\u0001\u0000\u0000\u0000(\u025a\u0001\u0000"+
		"\u0000\u0000*\u025d\u0001\u0000\u0000\u0000,\u025f\u0001\u0000\u0000\u0000"+
		".\u0263\u0001\u0000\u0000\u00000\u0265\u0001\u0000\u0000\u00002\u0268"+
		"\u0001\u0000\u0000\u00004\u026b\u0001\u0000\u0000\u00006\u0279\u0001\u0000"+
		"\u0000\u00008\u0282\u0001\u0000\u0000\u0000:\u028d\u0001\u0000\u0000\u0000"+
		"<\u028f\u0001\u0000\u0000\u0000>\u0296\u0001\u0000\u0000\u0000@\u0299"+
		"\u0001\u0000\u0000\u0000B\u02a1\u0001\u0000\u0000\u0000D\u02be\u0001\u0000"+
		"\u0000\u0000F\u02ca\u0001\u0000\u0000\u0000H\u02cc\u0001\u0000\u0000\u0000"+
		"J\u02ce\u0001\u0000\u0000\u0000L\u02d4\u0001\u0000\u0000\u0000N\u02dd"+
		"\u0001\u0000\u0000\u0000P\u02ef\u0001\u0000\u0000\u0000R\u02f8\u0001\u0000"+
		"\u0000\u0000T\u02ff\u0001\u0000\u0000\u0000V\u0301\u0001\u0000\u0000\u0000"+
		"X\u030b\u0001\u0000\u0000\u0000Z\u0314\u0001\u0000\u0000\u0000\\\u031d"+
		"\u0001\u0000\u0000\u0000^\u032b\u0001\u0000\u0000\u0000`\u0330\u0001\u0000"+
		"\u0000\u0000b\u0337\u0001\u0000\u0000\u0000d\u033b\u0001\u0000\u0000\u0000"+
		"f\u0343\u0001\u0000\u0000\u0000h\u0347\u0001\u0000\u0000\u0000j\u034b"+
		"\u0001\u0000\u0000\u0000l\u034f\u0001\u0000\u0000\u0000n\u035f\u0001\u0000"+
		"\u0000\u0000p\u0363\u0001\u0000\u0000\u0000r\u0373\u0001\u0000\u0000\u0000"+
		"t\u0377\u0001\u0000\u0000\u0000v\u037b\u0001\u0000\u0000\u0000x\u037f"+
		"\u0001\u0000\u0000\u0000z\u0383\u0001\u0000\u0000\u0000|\u0385\u0001\u0000"+
		"\u0000\u0000~\u0389\u0001\u0000\u0000\u0000\u0080\u038d\u0001\u0000\u0000"+
		"\u0000\u0082\u0394\u0001\u0000\u0000\u0000\u0084\u03a4\u0001\u0000\u0000"+
		"\u0000\u0086\u03af\u0001\u0000\u0000\u0000\u0088\u03b7\u0001\u0000\u0000"+
		"\u0000\u008a\u03c7\u0001\u0000\u0000\u0000\u008c\u03cb\u0001\u0000\u0000"+
		"\u0000\u008e\u03d8\u0001\u0000\u0000\u0000\u0090\u03e1\u0001\u0000\u0000"+
		"\u0000\u0092\u03e6\u0001\u0000\u0000\u0000\u0094\u03f4\u0001\u0000\u0000"+
		"\u0000\u0096\u03f6\u0001\u0000\u0000\u0000\u0098\u03f9\u0001\u0000\u0000"+
		"\u0000\u009a\u03fc\u0001\u0000\u0000\u0000\u009c\u0414\u0001\u0000\u0000"+
		"\u0000\u009e\u041a\u0001\u0000\u0000\u0000\u00a0\u041c\u0001\u0000\u0000"+
		"\u0000\u00a2\u0421\u0001\u0000\u0000\u0000\u00a4\u0425\u0001\u0000\u0000"+
		"\u0000\u00a6\u0444\u0001\u0000\u0000\u0000\u00a8\u0454\u0001\u0000\u0000"+
		"\u0000\u00aa\u0456\u0001\u0000\u0000\u0000\u00ac\u045d\u0001\u0000\u0000"+
		"\u0000\u00ae\u045f\u0001\u0000\u0000\u0000\u00b0\u0467\u0001\u0000\u0000"+
		"\u0000\u00b2\u046a\u0001\u0000\u0000\u0000\u00b4\u0472\u0001\u0000\u0000"+
		"\u0000\u00b6\u0475\u0001\u0000\u0000\u0000\u00b8\u0478\u0001\u0000\u0000"+
		"\u0000\u00ba\u047b\u0001\u0000\u0000\u0000\u00bc\u0484\u0001\u0000\u0000"+
		"\u0000\u00be\u048b\u0001\u0000\u0000\u0000\u00c0\u0493\u0001\u0000\u0000"+
		"\u0000\u00c2\u0497\u0001\u0000\u0000\u0000\u00c4\u04a4\u0001\u0000\u0000"+
		"\u0000\u00c6\u04a6\u0001\u0000\u0000\u0000\u00c8\u04a8\u0001\u0000\u0000"+
		"\u0000\u00ca\u04ab\u0001\u0000\u0000\u0000\u00cc\u04c5\u0001\u0000\u0000"+
		"\u0000\u00ce\u04c7\u0001\u0000\u0000\u0000\u00d0\u04c9\u0001\u0000\u0000"+
		"\u0000\u00d2\u04d0\u0001\u0000\u0000\u0000\u00d4\u04d4\u0001\u0000\u0000"+
		"\u0000\u00d6\u04e4\u0001\u0000\u0000\u0000\u00d8\u04e6\u0001\u0000\u0000"+
		"\u0000\u00da\u04f1\u0001\u0000\u0000\u0000\u00dc\u04f3\u0001\u0000\u0000"+
		"\u0000\u00de\u04f8\u0001\u0000\u0000\u0000\u00e0\u04fe\u0001\u0000\u0000"+
		"\u0000\u00e2\u0504\u0001\u0000\u0000\u0000\u00e4\u0509\u0001\u0000\u0000"+
		"\u0000\u00e6\u050f\u0001\u0000\u0000\u0000\u00e8\u051e\u0001\u0000\u0000"+
		"\u0000\u00ea\u0528\u0001\u0000\u0000\u0000\u00ec\u052f\u0001\u0000\u0000"+
		"\u0000\u00ee\u053e\u0001\u0000\u0000\u0000\u00f0\u0541\u0001\u0000\u0000"+
		"\u0000\u00f2\u0549\u0001\u0000\u0000\u0000\u00f4\u054b\u0001\u0000\u0000"+
		"\u0000\u00f6\u054d\u0001\u0000\u0000\u0000\u00f8\u0566\u0001\u0000\u0000"+
		"\u0000\u00fa\u0568\u0001\u0000\u0000\u0000\u00fc\u0581\u0001\u0000\u0000"+
		"\u0000\u00fe\u0583\u0001\u0000\u0000\u0000\u0100\u0588\u0001\u0000\u0000"+
		"\u0000\u0102\u0590\u0001\u0000\u0000\u0000\u0104\u059a\u0001\u0000\u0000"+
		"\u0000\u0106\u05a0\u0001\u0000\u0000\u0000\u0108\u05a6\u0001\u0000\u0000"+
		"\u0000\u010a\u05aa\u0001\u0000\u0000\u0000\u010c\u05ad\u0001\u0000\u0000"+
		"\u0000\u010e\u05b5\u0001\u0000\u0000\u0000\u0110\u05ba\u0001\u0000\u0000"+
		"\u0000\u0112\u05c2\u0001\u0000\u0000\u0000\u0114\u05cf\u0001\u0000\u0000"+
		"\u0000\u0116\u05d1\u0001\u0000\u0000\u0000\u0118\u05d3\u0001\u0000\u0000"+
		"\u0000\u011a\u05e5\u0001\u0000\u0000\u0000\u011c\u0635\u0001\u0000\u0000"+
		"\u0000\u011e\u0637\u0001\u0000\u0000\u0000\u0120\u0639\u0001\u0000\u0000"+
		"\u0000\u0122\u063b\u0001\u0000\u0000\u0000\u0124\u063d\u0001\u0000\u0000"+
		"\u0000\u0126\u063f\u0001\u0000\u0000\u0000\u0128\u0648\u0001\u0000\u0000"+
		"\u0000\u012a\u064a\u0001\u0000\u0000\u0000\u012c\u064e\u0001\u0000\u0000"+
		"\u0000\u012e\u0650\u0001\u0000\u0000\u0000\u0130\u0654\u0001\u0000\u0000"+
		"\u0000\u0132\u0656\u0001\u0000\u0000\u0000\u0134\u065f\u0001\u0000\u0000"+
		"\u0000\u0136\u0664\u0001\u0000\u0000\u0000\u0138\u0666\u0001\u0000\u0000"+
		"\u0000\u013a\u0668\u0001\u0000\u0000\u0000\u013c\u066a\u0001\u0000\u0000"+
		"\u0000\u013e\u066c\u0001\u0000\u0000\u0000\u0140\u0670\u0001\u0000\u0000"+
		"\u0000\u0142\u0672\u0001\u0000\u0000\u0000\u0144\u0675\u0001\u0000\u0000"+
		"\u0000\u0146\u0679\u0001\u0000\u0000\u0000\u0148\u0680\u0001\u0000\u0000"+
		"\u0000\u014a\u0688\u0001\u0000\u0000\u0000\u014c\u0690\u0001\u0000\u0000"+
		"\u0000\u014e\u0692\u0001\u0000\u0000\u0000\u0150\u0696\u0001\u0000\u0000"+
		"\u0000\u0152\u0698\u0001\u0000\u0000\u0000\u0154\u069a\u0001\u0000\u0000"+
		"\u0000\u0156\u069c\u0001\u0000\u0000\u0000\u0158\u06a6\u0001\u0000\u0000"+
		"\u0000\u015a\u06a8\u0001\u0000\u0000\u0000\u015c\u06aa\u0001\u0000\u0000"+
		"\u0000\u015e\u06ac\u0001\u0000\u0000\u0000\u0160\u06ae\u0001\u0000\u0000"+
		"\u0000\u0162\u06b0\u0001\u0000\u0000\u0000\u0164\u06b8\u0001\u0000\u0000"+
		"\u0000\u0166\u06ba\u0001\u0000\u0000\u0000\u0168\u06bc\u0001\u0000\u0000"+
		"\u0000\u016a\u06c1\u0001\u0000\u0000\u0000\u016c\u06c6\u0001\u0000\u0000"+
		"\u0000\u016e\u06e2\u0001\u0000\u0000\u0000\u0170\u06e4\u0001\u0000\u0000"+
		"\u0000\u0172\u06f3\u0001\u0000\u0000\u0000\u0174\u06f8\u0001\u0000\u0000"+
		"\u0000\u0176\u06ff\u0001\u0000\u0000\u0000\u0178\u0704\u0001\u0000\u0000"+
		"\u0000\u017a\u0708\u0001\u0000\u0000\u0000\u017c\u070a\u0001\u0000\u0000"+
		"\u0000\u017e\u070c\u0001\u0000\u0000\u0000\u0180\u070e\u0001\u0000\u0000"+
		"\u0000\u0182\u0716\u0001\u0000\u0000\u0000\u0184\u071a\u0001\u0000\u0000"+
		"\u0000\u0186\u071f\u0001\u0000\u0000\u0000\u0188\u0721\u0001\u0000\u0000"+
		"\u0000\u018a\u0726\u0001\u0000\u0000\u0000\u018c\u072b\u0001\u0000\u0000"+
		"\u0000\u018e\u072d\u0001\u0000\u0000\u0000\u0190\u072f\u0001\u0000\u0000"+
		"\u0000\u0192\u0738\u0001\u0000\u0000\u0000\u0194\u073c\u0001\u0000\u0000"+
		"\u0000\u0196\u073f\u0001\u0000\u0000\u0000\u0198\u0750\u0001\u0000\u0000"+
		"\u0000\u019a\u0753\u0001\u0000\u0000\u0000\u019c\u0756\u0001\u0000\u0000"+
		"\u0000\u019e\u075b\u0001\u0000\u0000\u0000\u01a0\u0770\u0001\u0000\u0000"+
		"\u0000\u01a2\u077d\u0001\u0000\u0000\u0000\u01a4\u0783\u0001\u0000\u0000"+
		"\u0000\u01a6\u0785\u0001\u0000\u0000\u0000\u01a8\u0788\u0001\u0000\u0000"+
		"\u0000\u01aa\u0799\u0001\u0000\u0000\u0000\u01ac\u07a0\u0001\u0000\u0000"+
		"\u0000\u01ae\u07ac\u0001\u0000\u0000\u0000\u01b0\u07bb\u0001\u0000\u0000"+
		"\u0000\u01b2\u07bd\u0001\u0000\u0000\u0000\u01b4\u07c2\u0001\u0000\u0000"+
		"\u0000\u01b6\u07cc\u0001\u0000\u0000\u0000\u01b8\u07ce\u0001\u0000\u0000"+
		"\u0000\u01ba\u07d0\u0001\u0000\u0000\u0000\u01bc\u07d2\u0001\u0000\u0000"+
		"\u0000\u01be\u07d4\u0001\u0000\u0000\u0000\u01c0\u07d6\u0001\u0000\u0000"+
		"\u0000\u01c2\u07d8\u0001\u0000\u0000\u0000\u01c4\u01c5\u0003\u0004\u0002"+
		"\u0000\u01c5\u01c6\u0005\u0000\u0000\u0001\u01c6\u0001\u0001\u0000\u0000"+
		"\u0000\u01c7\u01c8\u0003\u0000\u0000\u0000\u01c8\u0003\u0001\u0000\u0000"+
		"\u0000\u01c9\u01ca\u0003*\u0015\u0000\u01ca\u01cb\u0003B!\u0000\u01cb"+
		"\u01cd\u0001\u0000\u0000\u0000\u01cc\u01c9\u0001\u0000\u0000\u0000\u01cd"+
		"\u01d0\u0001\u0000\u0000\u0000\u01ce\u01cc\u0001\u0000\u0000\u0000\u01ce"+
		"\u01cf\u0001\u0000\u0000\u0000\u01cf\u0005\u0001\u0000\u0000\u0000\u01d0"+
		"\u01ce\u0001\u0000\u0000\u0000\u01d1\u01d2\u0005\u008c\u0000\u0000\u01d2"+
		"\u01d3\u0005\u009a\u0000\u0000\u01d3\u01d5\u0005\u0094\u0000\u0000\u01d4"+
		"\u01d1\u0001\u0000\u0000\u0000\u01d4\u01d5\u0001\u0000\u0000\u0000\u01d5"+
		"\u01d6\u0001\u0000\u0000\u0000\u01d6\u01d7\u0005\u009a\u0000\u0000\u01d7"+
		"\u0007\u0001\u0000\u0000\u0000\u01d8\u01de\u0005o\u0000\u0000\u01d9\u01da"+
		"\u0005z\u0000\u0000\u01da\u01db\u0003\n\u0005\u0000\u01db\u01dc\u0005"+
		"{\u0000\u0000\u01dc\u01de\u0001\u0000\u0000\u0000\u01dd\u01d8\u0001\u0000"+
		"\u0000\u0000\u01dd\u01d9\u0001\u0000\u0000\u0000\u01de\t\u0001\u0000\u0000"+
		"\u0000\u01df\u01e1\u0003\f\u0006\u0000\u01e0\u01df\u0001\u0000\u0000\u0000"+
		"\u01e1\u01e4\u0001\u0000\u0000\u0000\u01e2\u01e0\u0001\u0000\u0000\u0000"+
		"\u01e2\u01e3\u0001\u0000\u0000\u0000\u01e3\u000b\u0001\u0000\u0000\u0000"+
		"\u01e4\u01e2\u0001\u0000\u0000\u0000\u01e5\u01e8\u0003\u000e\u0007\u0000"+
		"\u01e6\u01e8\u0003\u0014\n\u0000\u01e7\u01e5\u0001\u0000\u0000\u0000\u01e7"+
		"\u01e6\u0001\u0000\u0000\u0000\u01e8\r\u0001\u0000\u0000\u0000\u01e9\u01ec"+
		"\u0003D\"\u0000\u01ea\u01ec\u0003F#\u0000\u01eb\u01e9\u0001\u0000\u0000"+
		"\u0000\u01eb\u01ea\u0001\u0000\u0000\u0000\u01ec\u000f\u0001\u0000\u0000"+
		"\u0000\u01ed\u01ef\u0003\u0198\u00cc\u0000\u01ee\u01ed\u0001\u0000\u0000"+
		"\u0000\u01ef\u01f2\u0001\u0000\u0000\u0000\u01f0\u01ee\u0001\u0000\u0000"+
		"\u0000\u01f0\u01f1\u0001\u0000\u0000\u0000\u01f1\u01f3\u0001\u0000\u0000"+
		"\u0000\u01f2\u01f0\u0001\u0000\u0000\u0000\u01f3\u01f5\u0005\u0017\u0000"+
		"\u0000\u01f4\u01f6\u0003\u0006\u0003\u0000\u01f5\u01f4\u0001\u0000\u0000"+
		"\u0000\u01f5\u01f6\u0001\u0000\u0000\u0000\u01f6\u01f8\u0001\u0000\u0000"+
		"\u0000\u01f7\u01f9\u0005(\u0000\u0000\u01f8\u01f7\u0001\u0000\u0000\u0000"+
		"\u01f8\u01f9\u0001\u0000\u0000\u0000\u01f9\u01fa\u0001\u0000\u0000\u0000"+
		"\u01fa\u01ff\u00036\u001b\u0000\u01fb\u01fc\u0005~\u0000\u0000\u01fc\u01fe"+
		"\u00036\u001b\u0000\u01fd\u01fb\u0001\u0000\u0000\u0000\u01fe\u0201\u0001"+
		"\u0000\u0000\u0000\u01ff\u01fd\u0001\u0000\u0000\u0000\u01ff\u0200\u0001"+
		"\u0000\u0000\u0000\u0200\u0202\u0001\u0000\u0000\u0000\u0201\u01ff\u0001"+
		"\u0000\u0000\u0000\u0202\u0203\u0005Y\u0000\u0000\u0203\u0208\u00036\u001b"+
		"\u0000\u0204\u0205\u0005~\u0000\u0000\u0205\u0207\u00036\u001b\u0000\u0206"+
		"\u0204\u0001\u0000\u0000\u0000\u0207\u020a\u0001\u0000\u0000\u0000\u0208"+
		"\u0206\u0001\u0000\u0000\u0000\u0208\u0209\u0001\u0000\u0000\u0000\u0209"+
		"\u020b\u0001\u0000\u0000\u0000\u020a\u0208\u0001\u0000\u0000\u0000\u020b"+
		"\u020c\u0003\b\u0004\u0000\u020c\u0011\u0001\u0000\u0000\u0000\u020d\u020e"+
		"\u00036\u001b\u0000\u020e\u0013\u0001\u0000\u0000\u0000\u020f\u0210\u0003"+
		"\u0016\u000b\u0000\u0210\u0015\u0001\u0000\u0000\u0000\u0211\u0216\u0003"+
		"\u0018\f\u0000\u0212\u0216\u0003\u001a\r\u0000\u0213\u0216\u0003\u001c"+
		"\u000e\u0000\u0214\u0216\u0003\u019e\u00cf\u0000\u0215\u0211\u0001\u0000"+
		"\u0000\u0000\u0215\u0212\u0001\u0000\u0000\u0000\u0215\u0213\u0001\u0000"+
		"\u0000\u0000\u0215\u0214\u0001\u0000\u0000\u0000\u0216\u0017\u0001\u0000"+
		"\u0000\u0000\u0217\u0219\u0005\u000f\u0000\u0000\u0218\u021a\u0003\u0006"+
		"\u0003\u0000\u0219\u0218\u0001\u0000\u0000\u0000\u0219\u021a\u0001\u0000"+
		"\u0000\u0000\u021a\u0224\u0001\u0000\u0000\u0000\u021b\u021c\u0005\u0001"+
		"\u0000\u0000\u021c\u0221\u0003\u0012\t\u0000\u021d\u021e\u0005~\u0000"+
		"\u0000\u021e\u0220\u0003\u0012\t\u0000\u021f\u021d\u0001\u0000\u0000\u0000"+
		"\u0220\u0223\u0001\u0000\u0000\u0000\u0221\u021f\u0001\u0000\u0000\u0000"+
		"\u0221\u0222\u0001\u0000\u0000\u0000\u0222\u0225\u0001\u0000\u0000\u0000"+
		"\u0223\u0221\u0001\u0000\u0000\u0000\u0224\u021b\u0001\u0000\u0000\u0000"+
		"\u0224\u0225\u0001\u0000\u0000\u0000\u0225\u0227\u0001\u0000\u0000\u0000"+
		"\u0226\u0217\u0001\u0000\u0000\u0000\u0226\u0227\u0001\u0000\u0000\u0000"+
		"\u0227\u022a\u0001\u0000\u0000\u0000\u0228\u0229\u0005a\u0000\u0000\u0229"+
		"\u022b\u0005\u009f\u0000\u0000\u022a\u0228\u0001\u0000\u0000\u0000\u022a"+
		"\u022b\u0001\u0000\u0000\u0000\u022b\u022c\u0001\u0000\u0000\u0000\u022c"+
		"\u022d\u0005k\u0000\u0000\u022d\u0019\u0001\u0000\u0000\u0000\u022e\u0230"+
		"\u0005\u001c\u0000\u0000\u022f\u0231\u0003\u0006\u0003\u0000\u0230\u022f"+
		"\u0001\u0000\u0000\u0000\u0230\u0231\u0001\u0000\u0000\u0000\u0231\u0234"+
		"\u0001\u0000\u0000\u0000\u0232\u0233\u0005a\u0000\u0000\u0233\u0235\u0005"+
		"\u009f\u0000\u0000\u0234\u0232\u0001\u0000\u0000\u0000\u0234\u0235\u0001"+
		"\u0000\u0000\u0000\u0235\u0236\u0001\u0000\u0000\u0000\u0236\u0237\u0005"+
		"k\u0000\u0000\u0237\u001b\u0001\u0000\u0000\u0000\u0238\u0239\u0005M\u0000"+
		"\u0000\u0239\u023b\u0003\u0006\u0003\u0000\u023a\u0238\u0001\u0000\u0000"+
		"\u0000\u023a\u023b\u0001\u0000\u0000\u0000\u023b\u023c\u0001\u0000\u0000"+
		"\u0000\u023c\u023d\u00056\u0000\u0000\u023d\u023e\u0005\u009f\u0000\u0000"+
		"\u023e\u023f\u0005k\u0000\u0000\u023f\u001d\u0001\u0000\u0000\u0000\u0240"+
		"\u0241\u0003&\u0013\u0000\u0241\u001f\u0001\u0000\u0000\u0000\u0242\u0244"+
		"\u0003\u019a\u00cd\u0000\u0243\u0242\u0001\u0000\u0000\u0000\u0244\u0247"+
		"\u0001\u0000\u0000\u0000\u0245\u0243\u0001\u0000\u0000\u0000\u0245\u0246"+
		"\u0001\u0000\u0000\u0000\u0246\u0248\u0001\u0000\u0000\u0000\u0247\u0245"+
		"\u0001\u0000\u0000\u0000\u0248\u0249\u0003\"\u0011\u0000\u0249\u024a\u0003"+
		"$\u0012\u0000\u024a!\u0001\u0000\u0000\u0000\u024b\u024c\u0005;\u0000"+
		"\u0000\u024c\u024d\u0003\u0006\u0003\u0000\u024d#\u0001\u0000\u0000\u0000"+
		"\u024e\u0254\u0005o\u0000\u0000\u024f\u0250\u0005z\u0000\u0000\u0250\u0251"+
		"\u0003(\u0014\u0000\u0251\u0252\u0005{\u0000\u0000\u0252\u0254\u0001\u0000"+
		"\u0000\u0000\u0253\u024e\u0001\u0000\u0000\u0000\u0253\u024f\u0001\u0000"+
		"\u0000\u0000\u0254%\u0001\u0000\u0000\u0000\u0255\u0256\u0003\u0004\u0002"+
		"\u0000\u0256\'\u0001\u0000\u0000\u0000\u0257\u025b\u0003.\u0017\u0000"+
		"\u0258\u025b\u00034\u001a\u0000\u0259\u025b\u00038\u001c\u0000\u025a\u0257"+
		"\u0001\u0000\u0000\u0000\u025a\u0258\u0001\u0000\u0000\u0000\u025a\u0259"+
		"\u0001\u0000\u0000\u0000\u025b)\u0001\u0000\u0000\u0000\u025c\u025e\u0003"+
		",\u0016\u0000\u025d\u025c\u0001\u0000\u0000\u0000\u025d\u025e\u0001\u0000"+
		"\u0000\u0000\u025e+\u0001\u0000\u0000\u0000\u025f\u0260\u0007\u0000\u0000"+
		"\u0000\u0260-\u0001\u0000\u0000\u0000\u0261\u0264\u00030\u0018\u0000\u0262"+
		"\u0264\u00032\u0019\u0000\u0263\u0261\u0001\u0000\u0000\u0000\u0263\u0262"+
		"\u0001\u0000\u0000\u0000\u0264/\u0001\u0000\u0000\u0000\u0265\u0266\u0003"+
		"*\u0015\u0000\u0266\u0267\u0003D\"\u0000\u02671\u0001\u0000\u0000\u0000"+
		"\u0268\u0269\u0003*\u0015\u0000\u0269\u026a\u0003F#\u0000\u026a3\u0001"+
		"\u0000\u0000\u0000\u026b\u026c\u0003*\u0015\u0000\u026c\u0270\u0005\u0003"+
		"\u0000\u0000\u026d\u026e\u0005\u008c\u0000\u0000\u026e\u026f\u0005\u009a"+
		"\u0000\u0000\u026f\u0271\u0005\u0094\u0000\u0000\u0270\u026d\u0001\u0000"+
		"\u0000\u0000\u0270\u0271\u0001\u0000\u0000\u0000\u0271\u0273\u0001\u0000"+
		"\u0000\u0000\u0272\u0274\u0005\u009a\u0000\u0000\u0273\u0272\u0001\u0000"+
		"\u0000\u0000\u0273\u0274\u0001\u0000\u0000\u0000\u0274\u0275\u0001\u0000"+
		"\u0000\u0000\u0275\u0276\u0005\'\u0000\u0000\u0276\u0277\u00036\u001b"+
		"\u0000\u0277\u0278\u0003\b\u0004\u0000\u02785\u0001\u0000\u0000\u0000"+
		"\u0279\u027e\u0005\u009a\u0000\u0000\u027a\u027b\u0005q\u0000\u0000\u027b"+
		"\u027d\u0005\u009a\u0000\u0000\u027c\u027a\u0001\u0000\u0000\u0000\u027d"+
		"\u0280\u0001\u0000\u0000\u0000\u027e\u027c\u0001\u0000\u0000\u0000\u027e"+
		"\u027f\u0001\u0000\u0000\u0000\u027f7\u0001\u0000\u0000\u0000\u0280\u027e"+
		"\u0001\u0000\u0000\u0000\u0281\u0283\u0003,\u0016\u0000\u0282\u0281\u0001"+
		"\u0000\u0000\u0000\u0282\u0283\u0001\u0000\u0000\u0000\u0283\u0284\u0001"+
		"\u0000\u0000\u0000\u0284\u0286\u0005.\u0000\u0000\u0285\u0287\u0005\u0004"+
		"\u0000\u0000\u0286\u0285\u0001\u0000\u0000\u0000\u0286\u0287\u0001\u0000"+
		"\u0000\u0000\u0287\u0288\u0001\u0000\u0000\u0000\u0288\u0289\u0003:\u001d"+
		"\u0000\u0289\u028a\u0003\b\u0004\u0000\u028a9\u0001\u0000\u0000\u0000"+
		"\u028b\u028e\u0003<\u001e\u0000\u028c\u028e\u0003>\u001f\u0000\u028d\u028b"+
		"\u0001\u0000\u0000\u0000\u028d\u028c\u0001\u0000\u0000\u0000\u028e;\u0001"+
		"\u0000\u0000\u0000\u028f\u0291\u00036\u001b\u0000\u0290\u0292\u0005q\u0000"+
		"\u0000\u0291\u0290\u0001\u0000\u0000\u0000\u0291\u0292\u0001\u0000\u0000"+
		"\u0000\u0292\u0294\u0001\u0000\u0000\u0000\u0293\u0295\u0007\u0001\u0000"+
		"\u0000\u0294\u0293\u0001\u0000\u0000\u0000\u0294\u0295\u0001\u0000\u0000"+
		"\u0000\u0295=\u0001\u0000\u0000\u0000\u0296\u0297\u0003<\u001e\u0000\u0297"+
		"\u0298\u0003@ \u0000\u0298?\u0001\u0000\u0000\u0000\u0299\u029a\u0005"+
		"|\u0000\u0000\u029a\u029b\u0003\u011a\u008d\u0000\u029b\u029c\u0005}\u0000"+
		"\u0000\u029cA\u0001\u0000\u0000\u0000\u029d\u02a2\u0003H$\u0000\u029e"+
		"\u02a2\u0003\u0016\u000b\u0000\u029f\u02a2\u0003D\"\u0000\u02a0\u02a2"+
		"\u0003F#\u0000\u02a1\u029d\u0001\u0000\u0000\u0000\u02a1\u029e\u0001\u0000"+
		"\u0000\u0000\u02a1\u029f\u0001\u0000\u0000\u0000\u02a1\u02a0\u0001\u0000"+
		"\u0000\u0000\u02a2C\u0001\u0000\u0000\u0000\u02a3\u02bf\u0003\u0010\b"+
		"\u0000\u02a4\u02bf\u0003J%\u0000\u02a5\u02bf\u0003\u0080@\u0000\u02a6"+
		"\u02bf\u0003\u00dcn\u0000\u02a7\u02bf\u0003 \u0010\u0000\u02a8\u02bf\u0003"+
		"\u00deo\u0000\u02a9\u02bf\u0003\u00e0p\u0000\u02aa\u02bf\u0003\u0196\u00cb"+
		"\u0000\u02ab\u02bf\u0003\u00e2q\u0000\u02ac\u02bf\u0003\u00e4r\u0000\u02ad"+
		"\u02bf\u0003\u0168\u00b4\u0000\u02ae\u02bf\u0003\u00fe\u007f\u0000\u02af"+
		"\u02bf\u0003\u0102\u0081\u0000\u02b0\u02bf\u0003\u010e\u0087\u0000\u02b1"+
		"\u02bf\u0003\u0186\u00c3\u0000\u02b2\u02bf\u0003\u01aa\u00d5\u0000\u02b3"+
		"\u02bf\u0003\u01ac\u00d6\u0000\u02b4\u02bf\u0003d2\u0000\u02b5\u02bf\u0003"+
		"l6\u0000\u02b6\u02bf\u0003\u0086C\u0000\u02b7\u02bf\u0003p8\u0000\u02b8"+
		"\u02bf\u0003\u00d4j\u0000\u02b9\u02bf\u0003\u00be_\u0000\u02ba\u02bf\u0003"+
		"\u00c2a\u0000\u02bb\u02bf\u0003\u00cae\u0000\u02bc\u02bf\u0003\u00d8l"+
		"\u0000\u02bd\u02bf\u00038\u001c\u0000\u02be\u02a3\u0001\u0000\u0000\u0000"+
		"\u02be\u02a4\u0001\u0000\u0000\u0000\u02be\u02a5\u0001\u0000\u0000\u0000"+
		"\u02be\u02a6\u0001\u0000\u0000\u0000\u02be\u02a7\u0001\u0000\u0000\u0000"+
		"\u02be\u02a8\u0001\u0000\u0000\u0000\u02be\u02a9\u0001\u0000\u0000\u0000"+
		"\u02be\u02aa\u0001\u0000\u0000\u0000\u02be\u02ab\u0001\u0000\u0000\u0000"+
		"\u02be\u02ac\u0001\u0000\u0000\u0000\u02be\u02ad\u0001\u0000\u0000\u0000"+
		"\u02be\u02ae\u0001\u0000\u0000\u0000\u02be\u02af\u0001\u0000\u0000\u0000"+
		"\u02be\u02b0\u0001\u0000\u0000\u0000\u02be\u02b1\u0001\u0000\u0000\u0000"+
		"\u02be\u02b2\u0001\u0000\u0000\u0000\u02be\u02b3\u0001\u0000\u0000\u0000"+
		"\u02be\u02b4\u0001\u0000\u0000\u0000\u02be\u02b5\u0001\u0000\u0000\u0000"+
		"\u02be\u02b6\u0001\u0000\u0000\u0000\u02be\u02b7\u0001\u0000\u0000\u0000"+
		"\u02be\u02b8\u0001\u0000\u0000\u0000\u02be\u02b9\u0001\u0000\u0000\u0000"+
		"\u02be\u02ba\u0001\u0000\u0000\u0000\u02be\u02bb\u0001\u0000\u0000\u0000"+
		"\u02be\u02bc\u0001\u0000\u0000\u0000\u02be\u02bd\u0001\u0000\u0000\u0000"+
		"\u02bfE\u0001\u0000\u0000\u0000\u02c0\u02cb\u0003\u008aE\u0000\u02c1\u02cb"+
		"\u0003\u0100\u0080\u0000\u02c2\u02cb\u0003\u010c\u0086\u0000\u02c3\u02cb"+
		"\u0003\u0110\u0088\u0000\u02c4\u02cb\u0003\u0112\u0089\u0000\u02c5\u02cb"+
		"\u0003\u00e6s\u0000\u02c6\u02cb\u0003\u00f6{\u0000\u02c7\u02cb\u0003\u00fa"+
		"}\u0000\u02c8\u02cb\u0003\u016a\u00b5\u0000\u02c9\u02cb\u0003\u016c\u00b6"+
		"\u0000\u02ca\u02c0\u0001\u0000\u0000\u0000\u02ca\u02c1\u0001\u0000\u0000"+
		"\u0000\u02ca\u02c2\u0001\u0000\u0000\u0000\u02ca\u02c3\u0001\u0000\u0000"+
		"\u0000\u02ca\u02c4\u0001\u0000\u0000\u0000\u02ca\u02c5\u0001\u0000\u0000"+
		"\u0000\u02ca\u02c6\u0001\u0000\u0000\u0000\u02ca\u02c7\u0001\u0000\u0000"+
		"\u0000\u02ca\u02c8\u0001\u0000\u0000\u0000\u02ca\u02c9\u0001\u0000\u0000"+
		"\u0000\u02cbG\u0001\u0000\u0000\u0000\u02cc\u02cd\u0003\u01b4\u00da\u0000"+
		"\u02cdI\u0001\u0000\u0000\u0000\u02ce\u02cf\u0003L&\u0000\u02cf\u02d0"+
		"\u0005[\u0000\u0000\u02d0\u02d1\u0003N\'\u0000\u02d1\u02d2\u0003^/\u0000"+
		"\u02d2K\u0001\u0000\u0000\u0000\u02d3\u02d5\u0005\u0002\u0000\u0000\u02d4"+
		"\u02d3\u0001\u0000\u0000\u0000\u02d4\u02d5\u0001\u0000\u0000\u0000\u02d5"+
		"\u02d9\u0001\u0000\u0000\u0000\u02d6\u02d8\u0003\u019a\u00cd\u0000\u02d7"+
		"\u02d6\u0001\u0000\u0000\u0000\u02d8\u02db\u0001\u0000\u0000\u0000\u02d9"+
		"\u02d7\u0001\u0000\u0000\u0000\u02d9\u02da\u0001\u0000\u0000\u0000\u02da"+
		"M\u0001\u0000\u0000\u0000\u02db\u02d9\u0001\u0000\u0000\u0000\u02dc\u02de"+
		"\u0005\u0004\u0000\u0000\u02dd\u02dc\u0001\u0000\u0000\u0000\u02dd\u02de"+
		"\u0001\u0000\u0000\u0000\u02de\u02df\u0001\u0000\u0000\u0000\u02df\u02e1"+
		"\u0003\u0006\u0003\u0000\u02e0\u02e2\u0003\u0190\u00c8\u0000\u02e1\u02e0"+
		"\u0001\u0000\u0000\u0000\u02e1\u02e2\u0001\u0000\u0000\u0000\u02e2\u02e5"+
		"\u0001\u0000\u0000\u0000\u02e3\u02e6\u0003P(\u0000\u02e4\u02e6\u0003R"+
		")\u0000\u02e5\u02e3\u0001\u0000\u0000\u0000\u02e5\u02e4\u0001\u0000\u0000"+
		"\u0000\u02e6\u02e7\u0001\u0000\u0000\u0000\u02e7\u02e5\u0001\u0000\u0000"+
		"\u0000\u02e7\u02e8\u0001\u0000\u0000\u0000\u02e8\u02ec\u0001\u0000\u0000"+
		"\u0000\u02e9\u02eb\u0003T*\u0000\u02ea\u02e9\u0001\u0000\u0000\u0000\u02eb"+
		"\u02ee\u0001\u0000\u0000\u0000\u02ec\u02ea\u0001\u0000\u0000\u0000\u02ec"+
		"\u02ed\u0001\u0000\u0000\u0000\u02edO\u0001\u0000\u0000\u0000\u02ee\u02ec"+
		"\u0001\u0000\u0000\u0000\u02ef\u02f0\u0003\u01b8\u00dc\u0000\u02f0\u02f5"+
		"\u0003f3\u0000\u02f1\u02f2\u0005~\u0000\u0000\u02f2\u02f4\u0003f3\u0000"+
		"\u02f3\u02f1\u0001\u0000\u0000\u0000\u02f4\u02f7\u0001\u0000\u0000\u0000"+
		"\u02f5\u02f3\u0001\u0000\u0000\u0000\u02f5\u02f6\u0001\u0000\u0000\u0000"+
		"\u02f6Q\u0001\u0000\u0000\u0000\u02f7\u02f5\u0001\u0000\u0000\u0000\u02f8"+
		"\u02f9\u0003\u01c0\u00e0\u0000\u02f9\u02fa\u0003n7\u0000\u02faS\u0001"+
		"\u0000\u0000\u0000\u02fb\u0300\u0003V+\u0000\u02fc\u0300\u0003X,\u0000"+
		"\u02fd\u0300\u0003Z-\u0000\u02fe\u0300\u0003\\.\u0000\u02ff\u02fb\u0001"+
		"\u0000\u0000\u0000\u02ff\u02fc\u0001\u0000\u0000\u0000\u02ff\u02fd\u0001"+
		"\u0000\u0000\u0000\u02ff\u02fe\u0001\u0000\u0000\u0000\u0300U\u0001\u0000"+
		"\u0000\u0000\u0301\u0302\u0005\u001b\u0000\u0000\u0302\u0303\u0005(\u0000"+
		"\u0000\u0303\u0308\u0003r9\u0000\u0304\u0305\u0005~\u0000\u0000\u0305"+
		"\u0307\u0003r9\u0000\u0306\u0304\u0001\u0000\u0000\u0000\u0307\u030a\u0001"+
		"\u0000\u0000\u0000\u0308\u0306\u0001\u0000\u0000\u0000\u0308\u0309\u0001"+
		"\u0000\u0000\u0000\u0309W\u0001\u0000\u0000\u0000\u030a\u0308\u0001\u0000"+
		"\u0000\u0000\u030b\u030c\u0005^\u0000\u0000\u030c\u0311\u0003t:\u0000"+
		"\u030d\u030e\u0005~\u0000\u0000\u030e\u0310\u0003t:\u0000\u030f\u030d"+
		"\u0001\u0000\u0000\u0000\u0310\u0313\u0001\u0000\u0000\u0000\u0311\u030f"+
		"\u0001\u0000\u0000\u0000\u0311\u0312\u0001\u0000\u0000\u0000\u0312Y\u0001"+
		"\u0000\u0000\u0000\u0313\u0311\u0001\u0000\u0000\u0000\u0314\u0315\u0005"+
		",\u0000\u0000\u0315\u031a\u0003v;\u0000\u0316\u0317\u0005~\u0000\u0000"+
		"\u0317\u0319\u0003v;\u0000\u0318\u0316\u0001\u0000\u0000\u0000\u0319\u031c"+
		"\u0001\u0000\u0000\u0000\u031a\u0318\u0001\u0000\u0000\u0000\u031a\u031b"+
		"\u0001\u0000\u0000\u0000\u031b[\u0001\u0000\u0000\u0000\u031c\u031a\u0001"+
		"\u0000\u0000\u0000\u031d\u031e\u0005\u0019\u0000\u0000\u031e\u0323\u0003"+
		"x<\u0000\u031f\u0320\u0005~\u0000\u0000\u0320\u0322\u0003x<\u0000\u0321"+
		"\u031f\u0001\u0000\u0000\u0000\u0322\u0325\u0001\u0000\u0000\u0000\u0323"+
		"\u0321\u0001\u0000\u0000\u0000\u0323\u0324\u0001\u0000\u0000\u0000\u0324"+
		"]\u0001\u0000\u0000\u0000\u0325\u0323\u0001\u0000\u0000\u0000\u0326\u032c"+
		"\u0005o\u0000\u0000\u0327\u0328\u0005z\u0000\u0000\u0328\u0329\u0003`"+
		"0\u0000\u0329\u032a\u0005{\u0000\u0000\u032a\u032c\u0001\u0000\u0000\u0000"+
		"\u032b\u0326\u0001\u0000\u0000\u0000\u032b\u0327\u0001\u0000\u0000\u0000"+
		"\u032c_\u0001\u0000\u0000\u0000\u032d\u032f\u0003b1\u0000\u032e\u032d"+
		"\u0001\u0000\u0000\u0000\u032f\u0332\u0001\u0000\u0000\u0000\u0330\u032e"+
		"\u0001\u0000\u0000\u0000\u0330\u0331\u0001\u0000\u0000\u0000\u0331a\u0001"+
		"\u0000\u0000\u0000\u0332\u0330\u0001\u0000\u0000\u0000\u0333\u0338\u0003"+
		"|>\u0000\u0334\u0335\u0003*\u0015\u0000\u0335\u0336\u0003B!\u0000\u0336"+
		"\u0338\u0001\u0000\u0000\u0000\u0337\u0333\u0001\u0000\u0000\u0000\u0337"+
		"\u0334\u0001\u0000\u0000\u0000\u0338c\u0001\u0000\u0000\u0000\u0339\u033a"+
		"\u0005O\u0000\u0000\u033a\u033c\u0003\u0006\u0003\u0000\u033b\u0339\u0001"+
		"\u0000\u0000\u0000\u033b\u033c\u0001\u0000\u0000\u0000\u033c\u033d\u0001"+
		"\u0000\u0000\u0000\u033d\u033e\u0005V\u0000\u0000\u033e\u033f\u0003h4"+
		"\u0000\u033f\u0340\u0003\u01b8\u00dc\u0000\u0340\u0341\u0003j5\u0000\u0341"+
		"\u0342\u0003\b\u0004\u0000\u0342e\u0001\u0000\u0000\u0000\u0343\u0344"+
		"\u0003j5\u0000\u0344g\u0001\u0000\u0000\u0000\u0345\u0348\u00036\u001b"+
		"\u0000\u0346\u0348\u0003\u00ceg\u0000\u0347\u0345\u0001\u0000\u0000\u0000"+
		"\u0347\u0346\u0001\u0000\u0000\u0000\u0348i\u0001\u0000\u0000\u0000\u0349"+
		"\u034c\u00036\u001b\u0000\u034a\u034c\u0003\u00ceg\u0000\u034b\u0349\u0001"+
		"\u0000\u0000\u0000\u034b\u034a\u0001\u0000\u0000\u0000\u034ck\u0001\u0000"+
		"\u0000\u0000\u034d\u034e\u0005\u0013\u0000\u0000\u034e\u0350\u0003\u0006"+
		"\u0003\u0000\u034f\u034d\u0001\u0000\u0000\u0000\u034f\u0350\u0001\u0000"+
		"\u0000\u0000\u0350\u0351\u0001\u0000\u0000\u0000\u0351\u0354\u0005\u0011"+
		"\u0000\u0000\u0352\u0355\u00036\u001b\u0000\u0353\u0355\u0003\u00d0h\u0000"+
		"\u0354\u0352\u0001\u0000\u0000\u0000\u0354\u0353\u0001\u0000\u0000\u0000"+
		"\u0355\u0356\u0001\u0000\u0000\u0000\u0356\u0359\u0003\u01c0\u00e0\u0000"+
		"\u0357\u035a\u00036\u001b\u0000\u0358\u035a\u0003\u00d0h\u0000\u0359\u0357"+
		"\u0001\u0000\u0000\u0000\u0359\u0358\u0001\u0000\u0000\u0000\u035a\u035b"+
		"\u0001\u0000\u0000\u0000\u035b\u035c\u0003\b\u0004\u0000\u035cm\u0001"+
		"\u0000\u0000\u0000\u035d\u0360\u00036\u001b\u0000\u035e\u0360\u0003\u00d0"+
		"h\u0000\u035f\u035d\u0001\u0000\u0000\u0000\u035f\u035e\u0001\u0000\u0000"+
		"\u0000\u0360o\u0001\u0000\u0000\u0000\u0361\u0362\u0005\u001a\u0000\u0000"+
		"\u0362\u0364\u0003\u0006\u0003\u0000\u0363\u0361\u0001\u0000\u0000\u0000"+
		"\u0363\u0364\u0001\u0000\u0000\u0000\u0364\u0365\u0001\u0000\u0000\u0000"+
		"\u0365\u0368\u0005\u001b\u0000\u0000\u0366\u0369\u00036\u001b\u0000\u0367"+
		"\u0369\u0003\u00d0h\u0000\u0368\u0366\u0001\u0000\u0000\u0000\u0368\u0367"+
		"\u0001\u0000\u0000\u0000\u0369\u036a\u0001\u0000\u0000\u0000\u036a\u036d"+
		"\u0005(\u0000\u0000\u036b\u036e\u00036\u001b\u0000\u036c\u036e\u0003\u00d0"+
		"h\u0000\u036d\u036b\u0001\u0000\u0000\u0000\u036d\u036c\u0001\u0000\u0000"+
		"\u0000\u036e\u036f\u0001\u0000\u0000\u0000\u036f\u0370\u0003\b\u0004\u0000"+
		"\u0370q\u0001\u0000\u0000\u0000\u0371\u0374\u00036\u001b\u0000\u0372\u0374"+
		"\u0003\u00d0h\u0000\u0373\u0371\u0001\u0000\u0000\u0000\u0373\u0372\u0001"+
		"\u0000\u0000\u0000\u0374s\u0001\u0000\u0000\u0000\u0375\u0378\u00036\u001b"+
		"\u0000\u0376\u0378\u0003\u00ceg\u0000\u0377\u0375\u0001\u0000\u0000\u0000"+
		"\u0377\u0376\u0001\u0000\u0000\u0000\u0378u\u0001\u0000\u0000\u0000\u0379"+
		"\u037c\u00036\u001b\u0000\u037a\u037c\u0003\u00ceg\u0000\u037b\u0379\u0001"+
		"\u0000\u0000\u0000\u037b\u037a\u0001\u0000\u0000\u0000\u037cw\u0001\u0000"+
		"\u0000\u0000\u037d\u0380\u00036\u001b\u0000\u037e\u0380\u0003\u00ceg\u0000"+
		"\u037f\u037d\u0001\u0000\u0000\u0000\u037f\u037e\u0001\u0000\u0000\u0000"+
		"\u0380y\u0001\u0000\u0000\u0000\u0381\u0384\u0003|>\u0000\u0382\u0384"+
		"\u0003~?\u0000\u0383\u0381\u0001\u0000\u0000\u0000\u0383\u0382\u0001\u0000"+
		"\u0000\u0000\u0384{\u0001\u0000\u0000\u0000\u0385\u0386\u0003*\u0015\u0000"+
		"\u0386\u0387\u00057\u0000\u0000\u0387\u0388\u0003F#\u0000\u0388}\u0001"+
		"\u0000\u0000\u0000\u0389\u038a\u0003*\u0015\u0000\u038a\u038b\u0003F#"+
		"\u0000\u038b\u007f\u0001\u0000\u0000\u0000\u038c\u038e\u0003L&\u0000\u038d"+
		"\u038c\u0001\u0000\u0000\u0000\u038d\u038e\u0001\u0000\u0000\u0000\u038e"+
		"\u038f\u0001\u0000\u0000\u0000\u038f\u0390\u0005\u000e\u0000\u0000\u0390"+
		"\u0391\u0003\u0082A\u0000\u0391\u0392\u0003^/\u0000\u0392\u0081\u0001"+
		"\u0000\u0000\u0000\u0393\u0395\u0005\u0004\u0000\u0000\u0394\u0393\u0001"+
		"\u0000\u0000\u0000\u0394\u0395\u0001\u0000\u0000\u0000\u0395\u0396\u0001"+
		"\u0000\u0000\u0000\u0396\u0398\u0003\u0006\u0003\u0000\u0397\u0399\u0003"+
		"\u0190\u00c8\u0000\u0398\u0397\u0001\u0000\u0000\u0000\u0398\u0399\u0001"+
		"\u0000\u0000\u0000\u0399\u039c\u0001\u0000\u0000\u0000\u039a\u039d\u0003"+
		"\u0084B\u0000\u039b\u039d\u0003R)\u0000\u039c\u039a\u0001\u0000\u0000"+
		"\u0000\u039c\u039b\u0001\u0000\u0000\u0000\u039c\u039d\u0001\u0000\u0000"+
		"\u0000\u039d\u03a1\u0001\u0000\u0000\u0000\u039e\u03a0\u0003T*\u0000\u039f"+
		"\u039e\u0001\u0000\u0000\u0000\u03a0\u03a3\u0001\u0000\u0000\u0000\u03a1"+
		"\u039f\u0001\u0000\u0000\u0000\u03a1\u03a2\u0001\u0000\u0000\u0000\u03a2"+
		"\u0083\u0001\u0000\u0000\u0000\u03a3\u03a1\u0001\u0000\u0000\u0000\u03a4"+
		"\u03a5\u0003\u01b8\u00dc\u0000\u03a5\u03aa\u0003\u0088D\u0000\u03a6\u03a7"+
		"\u0005~\u0000\u0000\u03a7\u03a9\u0003\u0088D\u0000\u03a8\u03a6\u0001\u0000"+
		"\u0000\u0000\u03a9\u03ac\u0001\u0000\u0000\u0000\u03aa\u03a8\u0001\u0000"+
		"\u0000\u0000\u03aa\u03ab\u0001\u0000\u0000\u0000\u03ab\u0085\u0001\u0000"+
		"\u0000\u0000\u03ac\u03aa\u0001\u0000\u0000\u0000\u03ad\u03ae\u0005O\u0000"+
		"\u0000\u03ae\u03b0\u0003\u0006\u0003\u0000\u03af\u03ad\u0001\u0000\u0000"+
		"\u0000\u03af\u03b0\u0001\u0000\u0000\u0000\u03b0\u03b1\u0001\u0000\u0000"+
		"\u0000\u03b1\u03b2\u0005S\u0000\u0000\u03b2\u03b3\u00036\u001b\u0000\u03b3"+
		"\u03b4\u0003\u01b8\u00dc\u0000\u03b4\u03b5\u00036\u001b\u0000\u03b5\u03b6"+
		"\u0003\b\u0004\u0000\u03b6\u0087\u0001\u0000\u0000\u0000\u03b7\u03b8\u0003"+
		"6\u001b\u0000\u03b8\u0089\u0001\u0000\u0000\u0000\u03b9\u03bc\u0003\u008e"+
		"G\u0000\u03ba\u03bd\u0005!\u0000\u0000\u03bb\u03bd\u0003\u019a\u00cd\u0000"+
		"\u03bc\u03ba\u0001\u0000\u0000\u0000\u03bc\u03bb\u0001\u0000\u0000\u0000"+
		"\u03bd\u03bf\u0001\u0000\u0000\u0000\u03be\u03c0\u0003\u009aM\u0000\u03bf"+
		"\u03be\u0001\u0000\u0000\u0000\u03bf\u03c0\u0001\u0000\u0000\u0000\u03c0"+
		"\u03c2\u0001\u0000\u0000\u0000\u03c1\u03c3\u0003\u0180\u00c0\u0000\u03c2"+
		"\u03c1\u0001\u0000\u0000\u0000\u03c2\u03c3\u0001\u0000\u0000\u0000\u03c3"+
		"\u03c4\u0001\u0000\u0000\u0000\u03c4\u03c5\u0003^/\u0000\u03c5\u03c8\u0001"+
		"\u0000\u0000\u0000\u03c6\u03c8\u0003\u008cF\u0000\u03c7\u03b9\u0001\u0000"+
		"\u0000\u0000\u03c7\u03c6\u0001\u0000\u0000\u0000\u03c8\u008b\u0001\u0000"+
		"\u0000\u0000\u03c9\u03cc\u0003\u0090H\u0000\u03ca\u03cc\u0003\u0092I\u0000"+
		"\u03cb\u03c9\u0001\u0000\u0000\u0000\u03cb\u03ca\u0001\u0000\u0000\u0000"+
		"\u03cc\u03cd\u0001\u0000\u0000\u0000\u03cd\u03cf\u0003\u009aM\u0000\u03ce"+
		"\u03d0\u0003\u0180\u00c0\u0000\u03cf\u03ce\u0001\u0000\u0000\u0000\u03cf"+
		"\u03d0\u0001\u0000\u0000\u0000\u03d0\u03d1\u0001\u0000\u0000\u0000\u03d1"+
		"\u03d2\u0003^/\u0000\u03d2\u008d\u0001\u0000\u0000\u0000\u03d3\u03d5\u0003"+
		"\u0090H\u0000\u03d4\u03d6\u0003\u0094J\u0000\u03d5\u03d4\u0001\u0000\u0000"+
		"\u0000\u03d5\u03d6\u0001\u0000\u0000\u0000\u03d6\u03d9\u0001\u0000\u0000"+
		"\u0000\u03d7\u03d9\u0003\u0092I\u0000\u03d8\u03d3\u0001\u0000\u0000\u0000"+
		"\u03d8\u03d7\u0001\u0000\u0000\u0000\u03d9\u03dd\u0001\u0000\u0000\u0000"+
		"\u03da\u03dc\u0003\u019a\u00cd\u0000\u03db\u03da\u0001\u0000\u0000\u0000"+
		"\u03dc\u03df\u0001\u0000\u0000\u0000\u03dd\u03db\u0001\u0000\u0000\u0000"+
		"\u03dd\u03de\u0001\u0000\u0000\u0000\u03de\u008f\u0001\u0000\u0000\u0000"+
		"\u03df\u03dd\u0001\u0000\u0000\u0000\u03e0\u03e2\u0005d\u0000\u0000\u03e1"+
		"\u03e0\u0001\u0000\u0000\u0000\u03e1\u03e2\u0001\u0000\u0000\u0000\u03e2"+
		"\u03e3\u0001\u0000\u0000\u0000\u03e3\u03e4\u0005\u001e\u0000\u0000\u03e4"+
		"\u0091\u0001\u0000\u0000\u0000\u03e5\u03e7\u0003\u0098L\u0000\u03e6\u03e5"+
		"\u0001\u0000\u0000\u0000\u03e6\u03e7\u0001\u0000\u0000\u0000\u03e7\u03e9"+
		"\u0001\u0000\u0000\u0000\u03e8\u03ea\u0005\u0018\u0000\u0000\u03e9\u03e8"+
		"\u0001\u0000\u0000\u0000\u03e9\u03ea\u0001\u0000\u0000\u0000\u03ea\u03ec"+
		"\u0001\u0000\u0000\u0000\u03eb\u03ed\u0005\u0002\u0000\u0000\u03ec\u03eb"+
		"\u0001\u0000\u0000\u0000\u03ec\u03ed\u0001\u0000\u0000\u0000\u03ed\u03ef"+
		"\u0001\u0000\u0000\u0000\u03ee\u03f0\u0007\u0002\u0000\u0000\u03ef\u03ee"+
		"\u0001\u0000\u0000\u0000\u03ef\u03f0\u0001\u0000\u0000\u0000\u03f0\u03f2"+
		"\u0001\u0000\u0000\u0000\u03f1\u03f3\u0007\u0003\u0000\u0000\u03f2\u03f1"+
		"\u0001\u0000\u0000\u0000\u03f2\u03f3\u0001\u0000\u0000\u0000\u03f3\u0093"+
		"\u0001\u0000\u0000\u0000\u03f4\u03f5\u0003\u0096K\u0000\u03f5\u0095\u0001"+
		"\u0000\u0000\u0000\u03f6\u03f7\u0003\u0092I\u0000\u03f7\u03f8\u0003\u009a"+
		"M\u0000\u03f8\u0097\u0001\u0000\u0000\u0000\u03f9\u03fa\u0007\u0004\u0000"+
		"\u0000\u03fa\u0099\u0001\u0000\u0000\u0000\u03fb\u03fd\u0005\u0004\u0000"+
		"\u0000\u03fc\u03fb\u0001\u0000\u0000\u0000\u03fc\u03fd\u0001\u0000\u0000"+
		"\u0000\u03fd\u0405\u0001\u0000\u0000\u0000\u03fe\u0401\u0003\u009cN\u0000"+
		"\u03ff\u0402\u0003\u00a6S\u0000\u0400\u0402\u0003R)\u0000\u0401\u03ff"+
		"\u0001\u0000\u0000\u0000\u0401\u0400\u0001\u0000\u0000\u0000\u0401\u0402"+
		"\u0001\u0000\u0000\u0000\u0402\u0406\u0001\u0000\u0000\u0000\u0403\u0406"+
		"\u0003\u00a6S\u0000\u0404\u0406\u0003R)\u0000\u0405\u03fe\u0001\u0000"+
		"\u0000\u0000\u0405\u0403\u0001\u0000\u0000\u0000\u0405\u0404\u0001\u0000"+
		"\u0000\u0000\u0406\u040a\u0001\u0000\u0000\u0000\u0407\u0409\u0003\u009e"+
		"O\u0000\u0408\u0407\u0001\u0000\u0000\u0000\u0409\u040c\u0001\u0000\u0000"+
		"\u0000\u040a\u0408\u0001\u0000\u0000\u0000\u040a\u040b\u0001\u0000\u0000"+
		"\u0000\u040b\u009b\u0001\u0000\u0000\u0000\u040c\u040a\u0001\u0000\u0000"+
		"\u0000\u040d\u040e\u0005\u008c\u0000\u0000\u040e\u040f\u0005\u009a\u0000"+
		"\u0000\u040f\u0411\u0005\u0094\u0000\u0000\u0410\u0412\u0005\u009a\u0000"+
		"\u0000\u0411\u0410\u0001\u0000\u0000\u0000\u0411\u0412\u0001\u0000\u0000"+
		"\u0000\u0412\u0415\u0001\u0000\u0000\u0000\u0413\u0415\u0005\u009a\u0000"+
		"\u0000\u0414\u040d\u0001\u0000\u0000\u0000\u0414\u0413\u0001\u0000\u0000"+
		"\u0000\u0415\u009d\u0001\u0000\u0000\u0000\u0416\u041b\u0003T*\u0000\u0417"+
		"\u041b\u0003\u00a0P\u0000\u0418\u041b\u0003\u00a2Q\u0000\u0419\u041b\u0003"+
		"\u00a4R\u0000\u041a\u0416\u0001\u0000\u0000\u0000\u041a\u0417\u0001\u0000"+
		"\u0000\u0000\u041a\u0418\u0001\u0000\u0000\u0000\u041a\u0419\u0001\u0000"+
		"\u0000\u0000\u041b\u009f\u0001\u0000\u0000\u0000\u041c\u041f\u0005\f\u0000"+
		"\u0000\u041d\u0420\u0003\u00d2i\u0000\u041e\u0420\u0003\u00d0h\u0000\u041f"+
		"\u041d\u0001\u0000\u0000\u0000\u041f\u041e\u0001\u0000\u0000\u0000\u0420"+
		"\u00a1\u0001\u0000\u0000\u0000\u0421\u0422\u00053\u0000\u0000\u0422\u0423"+
		"\u0005?\u0000\u0000\u0423\u0424\u0003\u00d6k\u0000\u0424\u00a3\u0001\u0000"+
		"\u0000\u0000\u0425\u0426\u0005\"\u0000\u0000\u0426\u0427\u0005\u000b\u0000"+
		"\u0000\u0427\u042c\u0003\u00dam\u0000\u0428\u0429\u0005~\u0000\u0000\u0429"+
		"\u042b\u0003\u00dam\u0000\u042a\u0428\u0001\u0000\u0000\u0000\u042b\u042e"+
		"\u0001\u0000\u0000\u0000\u042c\u042a\u0001\u0000\u0000\u0000\u042c\u042d"+
		"\u0001\u0000\u0000\u0000\u042d\u00a5\u0001\u0000\u0000\u0000\u042e\u042c"+
		"\u0001\u0000\u0000\u0000\u042f\u0431\u0003\u00acV\u0000\u0430\u042f\u0001"+
		"\u0000\u0000\u0000\u0431\u0432\u0001\u0000\u0000\u0000\u0432\u0430\u0001"+
		"\u0000\u0000\u0000\u0432\u0433\u0001\u0000\u0000\u0000\u0433\u043b\u0001"+
		"\u0000\u0000\u0000\u0434\u0438\u0003\u00a8T\u0000\u0435\u0437\u0003\u00ac"+
		"V\u0000\u0436\u0435\u0001\u0000\u0000\u0000\u0437\u043a\u0001\u0000\u0000"+
		"\u0000\u0438\u0436\u0001\u0000\u0000\u0000\u0438\u0439\u0001\u0000\u0000"+
		"\u0000\u0439\u043c\u0001\u0000\u0000\u0000\u043a\u0438\u0001\u0000\u0000"+
		"\u0000\u043b\u0434\u0001\u0000\u0000\u0000\u043b\u043c\u0001\u0000\u0000"+
		"\u0000\u043c\u0445\u0001\u0000\u0000\u0000\u043d\u0441\u0003\u00a8T\u0000"+
		"\u043e\u0440\u0003\u00acV\u0000\u043f\u043e\u0001\u0000\u0000\u0000\u0440"+
		"\u0443\u0001\u0000\u0000\u0000\u0441\u043f\u0001\u0000\u0000\u0000\u0441"+
		"\u0442\u0001\u0000\u0000\u0000\u0442\u0445\u0001\u0000\u0000\u0000\u0443"+
		"\u0441\u0001\u0000\u0000\u0000\u0444\u0430\u0001\u0000\u0000\u0000\u0444"+
		"\u043d\u0001\u0000\u0000\u0000\u0445\u00a7\u0001\u0000\u0000\u0000\u0446"+
		"\u0455\u0003\u0190\u00c8\u0000\u0447\u0449\u0003\u0190\u00c8\u0000\u0448"+
		"\u0447\u0001\u0000\u0000\u0000\u0448\u0449\u0001\u0000\u0000\u0000\u0449"+
		"\u0452\u0001\u0000\u0000\u0000\u044a\u044c\u0005A\u0000\u0000\u044b\u044d"+
		"\u0005<\u0000\u0000\u044c\u044b\u0001\u0000\u0000\u0000\u044c\u044d\u0001"+
		"\u0000\u0000\u0000\u044d\u0453\u0001\u0000\u0000\u0000\u044e\u0450\u0005"+
		"<\u0000\u0000\u044f\u0451\u0005A\u0000\u0000\u0450\u044f\u0001\u0000\u0000"+
		"\u0000\u0450\u0451\u0001\u0000\u0000\u0000\u0451\u0453\u0001\u0000\u0000"+
		"\u0000\u0452\u044a\u0001\u0000\u0000\u0000\u0452\u044e\u0001\u0000\u0000"+
		"\u0000\u0453\u0455\u0001\u0000\u0000\u0000\u0454\u0446\u0001\u0000\u0000"+
		"\u0000\u0454\u0448\u0001\u0000\u0000\u0000\u0455\u00a9\u0001\u0000\u0000"+
		"\u0000\u0456\u0457\u0007\u0005\u0000\u0000\u0457\u00ab\u0001\u0000\u0000"+
		"\u0000\u0458\u045e\u0003\u00aeW\u0000\u0459\u045e\u0003\u00b2Y\u0000\u045a"+
		"\u045e\u0003\u00b6[\u0000\u045b\u045e\u0003\u00b8\\\u0000\u045c\u045e"+
		"\u0003\u00ba]\u0000\u045d\u0458\u0001\u0000\u0000\u0000\u045d\u0459\u0001"+
		"\u0000\u0000\u0000\u045d\u045a\u0001\u0000\u0000\u0000\u045d\u045b\u0001"+
		"\u0000\u0000\u0000\u045d\u045c\u0001\u0000\u0000\u0000\u045e\u00ad\u0001"+
		"\u0000\u0000\u0000\u045f\u0464\u0003\u00b0X\u0000\u0460\u0461\u0005~\u0000"+
		"\u0000\u0461\u0463\u0003\u00c0`\u0000\u0462\u0460\u0001\u0000\u0000\u0000"+
		"\u0463\u0466\u0001\u0000\u0000\u0000\u0464\u0462\u0001\u0000\u0000\u0000"+
		"\u0464\u0465\u0001\u0000\u0000\u0000\u0465\u00af\u0001\u0000\u0000\u0000"+
		"\u0466\u0464\u0001\u0000\u0000\u0000\u0467\u0468\u0003\u01b6\u00db\u0000"+
		"\u0468\u0469\u0003\u00c0`\u0000\u0469\u00b1\u0001\u0000\u0000\u0000\u046a"+
		"\u046f\u0003\u00b4Z\u0000\u046b\u046c\u0005~\u0000\u0000\u046c\u046e\u0003"+
		"\u00c4b\u0000\u046d\u046b\u0001\u0000\u0000\u0000\u046e\u0471\u0001\u0000"+
		"\u0000\u0000\u046f\u046d\u0001\u0000\u0000\u0000\u046f\u0470\u0001\u0000"+
		"\u0000\u0000\u0470\u00b3\u0001\u0000\u0000\u0000\u0471\u046f\u0001\u0000"+
		"\u0000\u0000\u0472\u0473\u0003\u01ba\u00dd\u0000\u0473\u0474\u0003\u00c4"+
		"b\u0000\u0474\u00b5\u0001\u0000\u0000\u0000\u0475\u0476\u0003\u01bc\u00de"+
		"\u0000\u0476\u0477\u0003\u00c6c\u0000\u0477\u00b7\u0001\u0000\u0000\u0000"+
		"\u0478\u0479\u0003\u01c2\u00e1\u0000\u0479\u047a\u0003\u00c8d\u0000\u047a"+
		"\u00b9\u0001\u0000\u0000\u0000\u047b\u0480\u0003\u00bc^\u0000\u047c\u047d"+
		"\u0005~\u0000\u0000\u047d\u047f\u0003\u00ccf\u0000\u047e\u047c\u0001\u0000"+
		"\u0000\u0000\u047f\u0482\u0001\u0000\u0000\u0000\u0480\u047e\u0001\u0000"+
		"\u0000\u0000\u0480\u0481\u0001\u0000\u0000\u0000\u0481\u00bb\u0001\u0000"+
		"\u0000\u0000\u0482\u0480\u0001\u0000\u0000\u0000\u0483\u0485\u0003\u0098"+
		"L\u0000\u0484\u0483\u0001\u0000\u0000\u0000\u0484\u0485\u0001\u0000\u0000"+
		"\u0000\u0485\u0486\u0001\u0000\u0000\u0000\u0486\u0487\u0003\u01be\u00df"+
		"\u0000\u0487\u0488\u0003\u00ccf\u0000\u0488\u00bd\u0001\u0000\u0000\u0000"+
		"\u0489\u048a\u0005O\u0000\u0000\u048a\u048c\u0003\u0006\u0003\u0000\u048b"+
		"\u0489\u0001\u0000\u0000\u0000\u048b\u048c\u0001\u0000\u0000\u0000\u048c"+
		"\u048d\u0001\u0000\u0000\u0000\u048d\u048e\u0005]\u0000\u0000\u048e\u048f"+
		"\u00036\u001b\u0000\u048f\u0490\u0003\u01b6\u00db\u0000\u0490\u0491\u0003"+
		"j5\u0000\u0491\u0492\u0003\b\u0004\u0000\u0492\u00bf\u0001\u0000\u0000"+
		"\u0000\u0493\u0494\u0003j5\u0000\u0494\u00c1\u0001\u0000\u0000\u0000\u0495"+
		"\u0496\u0005O\u0000\u0000\u0496\u0498\u0003\u0006\u0003\u0000\u0497\u0495"+
		"\u0001\u0000\u0000\u0000\u0497\u0498\u0001\u0000\u0000\u0000\u0498\u049a"+
		"\u0001\u0000\u0000\u0000\u0499\u049b\u0005T\u0000\u0000\u049a\u0499\u0001"+
		"\u0000\u0000\u0000\u049a\u049b\u0001\u0000\u0000\u0000\u049b\u049c\u0001"+
		"\u0000\u0000\u0000\u049c\u049d\u0003h4\u0000\u049d\u049e\u0003\u01ba\u00dd"+
		"\u0000\u049e\u04a0\u0003j5\u0000\u049f\u04a1\u0003\u00a8T\u0000\u04a0"+
		"\u049f\u0001\u0000\u0000\u0000\u04a0\u04a1\u0001\u0000\u0000\u0000\u04a1"+
		"\u04a2\u0001\u0000\u0000\u0000\u04a2\u04a3\u0003\b\u0004\u0000\u04a3\u00c3"+
		"\u0001\u0000\u0000\u0000\u04a4\u04a5\u0003j5\u0000\u04a5\u00c5\u0001\u0000"+
		"\u0000\u0000\u04a6\u04a7\u0003j5\u0000\u04a7\u00c7\u0001\u0000\u0000\u0000"+
		"\u04a8\u04a9\u0003j5\u0000\u04a9\u00c9\u0001\u0000\u0000\u0000\u04aa\u04ac"+
		"\u0003\u0098L\u0000\u04ab\u04aa\u0001\u0000\u0000\u0000\u04ab\u04ac\u0001"+
		"\u0000\u0000\u0000\u04ac\u04af\u0001\u0000\u0000\u0000\u04ad\u04ae\u0005"+
		"O\u0000\u0000\u04ae\u04b0\u0003\u0006\u0003\u0000\u04af\u04ad\u0001\u0000"+
		"\u0000\u0000\u04af\u04b0\u0001\u0000\u0000\u0000\u04b0\u04b3\u0001\u0000"+
		"\u0000\u0000\u04b1\u04b2\u0005K\u0000\u0000\u04b2\u04b4\u0003h4\u0000"+
		"\u04b3\u04b1\u0001\u0000\u0000\u0000\u04b3\u04b4\u0001\u0000\u0000\u0000"+
		"\u04b4\u04b5\u0001\u0000\u0000\u0000\u04b5\u04b6\u0003\u01be\u00df\u0000"+
		"\u04b6\u04b8\u00036\u001b\u0000\u04b7\u04b9\u0003\u00b0X\u0000\u04b8\u04b7"+
		"\u0001\u0000\u0000\u0000\u04b8\u04b9\u0001\u0000\u0000\u0000\u04b9\u04bb"+
		"\u0001\u0000\u0000\u0000\u04ba\u04bc\u0003\u00a8T\u0000\u04bb\u04ba\u0001"+
		"\u0000\u0000\u0000\u04bb\u04bc\u0001\u0000\u0000\u0000\u04bc\u04be\u0001"+
		"\u0000\u0000\u0000\u04bd\u04bf\u0003\u00b4Z\u0000\u04be\u04bd\u0001\u0000"+
		"\u0000\u0000\u04be\u04bf\u0001\u0000\u0000\u0000\u04bf\u04c1\u0001\u0000"+
		"\u0000\u0000\u04c0\u04c2\u0003\u0184\u00c2\u0000\u04c1\u04c0\u0001\u0000"+
		"\u0000\u0000\u04c1\u04c2\u0001\u0000\u0000\u0000\u04c2\u04c3\u0001\u0000"+
		"\u0000\u0000\u04c3\u04c4\u0003\b\u0004\u0000\u04c4\u00cb\u0001\u0000\u0000"+
		"\u0000\u04c5\u04c6\u0003j5\u0000\u04c6\u00cd\u0001\u0000\u0000\u0000\u04c7"+
		"\u04c8\u0003\u00d0h\u0000\u04c8\u00cf\u0001\u0000\u0000\u0000\u04c9\u04cc"+
		"\u0003\u00d2i\u0000\u04ca\u04cb\u0005\u008a\u0000\u0000\u04cb\u04cd\u0003"+
		"\u00d2i\u0000\u04cc\u04ca\u0001\u0000\u0000\u0000\u04cd\u04ce\u0001\u0000"+
		"\u0000\u0000\u04ce\u04cc\u0001\u0000\u0000\u0000\u04ce\u04cf\u0001\u0000"+
		"\u0000\u0000\u04cf\u00d1\u0001\u0000\u0000\u0000\u04d0\u04d1\u00036\u001b"+
		"\u0000\u04d1\u00d3\u0001\u0000\u0000\u0000\u04d2\u04d3\u00054\u0000\u0000"+
		"\u04d3\u04d5\u0003\u0006\u0003\u0000\u04d4\u04d2\u0001\u0000\u0000\u0000"+
		"\u04d4\u04d5\u0001\u0000\u0000\u0000\u04d5\u04d6\u0001\u0000\u0000\u0000"+
		"\u04d6\u04d9\u00053\u0000\u0000\u04d7\u04da\u00036\u001b\u0000\u04d8\u04da"+
		"\u0003\u00ceg\u0000\u04d9\u04d7\u0001\u0000\u0000\u0000\u04d9\u04d8\u0001"+
		"\u0000\u0000\u0000\u04da\u04db\u0001\u0000\u0000\u0000\u04db\u04de\u0005"+
		"?\u0000\u0000\u04dc\u04df\u00036\u001b\u0000\u04dd\u04df\u0003\u00ceg"+
		"\u0000\u04de\u04dc\u0001\u0000\u0000\u0000\u04de\u04dd\u0001\u0000\u0000"+
		"\u0000\u04df\u04e0\u0001\u0000\u0000\u0000\u04e0\u04e1\u0003\b\u0004\u0000"+
		"\u04e1\u00d5\u0001\u0000\u0000\u0000\u04e2\u04e5\u00036\u001b\u0000\u04e3"+
		"\u04e5\u0003\u00ceg\u0000\u04e4\u04e2\u0001\u0000\u0000\u0000\u04e4\u04e3"+
		"\u0001\u0000\u0000\u0000\u04e5\u00d7\u0001\u0000\u0000\u0000\u04e6\u04ea"+
		"\u0005#\u0000\u0000\u04e7\u04e8\u0003\u0006\u0003\u0000\u04e8\u04e9\u0005"+
		"?\u0000\u0000\u04e9\u04eb\u0001\u0000\u0000\u0000\u04ea\u04e7\u0001\u0000"+
		"\u0000\u0000\u04ea\u04eb\u0001\u0000\u0000\u0000\u04eb\u04ec\u0001\u0000"+
		"\u0000\u0000\u04ec\u04ed\u00036\u001b\u0000\u04ed\u04ee\u0005\u000b\u0000"+
		"\u0000\u04ee\u04ef\u00036\u001b\u0000\u04ef\u04f0\u0003\b\u0004\u0000"+
		"\u04f0\u00d9\u0001\u0000\u0000\u0000\u04f1\u04f2\u00036\u001b\u0000\u04f2"+
		"\u00db\u0001\u0000\u0000\u0000\u04f3\u04f4\u0003L&\u0000\u04f4\u04f5\u0005"+
		"\u0015\u0000\u0000\u04f5\u04f6\u0003\u0082A\u0000\u04f6\u04f7\u0003^/"+
		"\u0000\u04f7\u00dd\u0001\u0000\u0000\u0000\u04f8\u04f9\u0003L&\u0000\u04f9"+
		"\u04fa\u0005\r\u0000\u0000\u04fa\u04fb\u0003\u0082A\u0000\u04fb\u04fc"+
		"\u0003^/\u0000\u04fc\u00df\u0001\u0000\u0000\u0000\u04fd\u04ff\u0003L"+
		"&\u0000\u04fe\u04fd\u0001\u0000\u0000\u0000\u04fe\u04ff\u0001\u0000\u0000"+
		"\u0000\u04ff\u0500\u0001\u0000\u0000\u0000\u0500\u0501\u0005R\u0000\u0000"+
		"\u0501\u0502\u0003\u0082A\u0000\u0502\u0503\u0003^/\u0000\u0503\u00e1"+
		"\u0001\u0000\u0000\u0000\u0504\u0505\u0003L&\u0000\u0505\u0506\u0005\u0007"+
		"\u0000\u0000\u0506\u0507\u0003\u0082A\u0000\u0507\u0508\u0003^/\u0000"+
		"\u0508\u00e3\u0001\u0000\u0000\u0000\u0509\u050a\u0003L&\u0000\u050a\u050b"+
		"\u0005\u0007\u0000\u0000\u050b\u050c\u0005R\u0000\u0000\u050c\u050d\u0003"+
		"\u0082A\u0000\u050d\u050e\u0003^/\u0000\u050e\u00e5\u0001\u0000\u0000"+
		"\u0000\u050f\u0510\u0003\u008eG\u0000\u0510\u0518\u0005\u0014\u0000\u0000"+
		"\u0511\u0513\u0003\u009aM\u0000\u0512\u0511\u0001\u0000\u0000\u0000\u0512"+
		"\u0513\u0001\u0000\u0000\u0000\u0513\u0515\u0001\u0000\u0000\u0000\u0514"+
		"\u0516\u0003\u0180\u00c0\u0000\u0515\u0514\u0001\u0000\u0000\u0000\u0515"+
		"\u0516\u0001\u0000\u0000\u0000\u0516\u0519\u0001\u0000\u0000\u0000\u0517"+
		"\u0519\u0003\u00e8t\u0000\u0518\u0512\u0001\u0000\u0000\u0000\u0518\u0517"+
		"\u0001\u0000\u0000\u0000\u0519\u051a\u0001\u0000\u0000\u0000\u051a\u051b"+
		"\u0003^/\u0000\u051b\u00e7\u0001\u0000\u0000\u0000\u051c\u051f\u0003\u00ea"+
		"u\u0000\u051d\u051f\u0003\u00ecv\u0000\u051e\u051c\u0001\u0000\u0000\u0000"+
		"\u051e\u051d\u0001\u0000\u0000\u0000\u051f\u00e9\u0001\u0000\u0000\u0000"+
		"\u0520\u0522\u0003\u009aM\u0000\u0521\u0520\u0001\u0000\u0000\u0000\u0521"+
		"\u0522\u0001\u0000\u0000\u0000\u0522\u0523\u0001\u0000\u0000\u0000\u0523"+
		"\u0529\u0005(\u0000\u0000\u0524\u0526\u0005\u0004\u0000\u0000\u0525\u0527"+
		"\u0005(\u0000\u0000\u0526\u0525\u0001\u0000\u0000\u0000\u0526\u0527\u0001"+
		"\u0000\u0000\u0000\u0527\u0529\u0001\u0000\u0000\u0000\u0528\u0521\u0001"+
		"\u0000\u0000\u0000\u0528\u0524\u0001\u0000\u0000\u0000\u0528\u0529\u0001"+
		"\u0000\u0000\u0000\u0529\u052a\u0001\u0000\u0000\u0000\u052a\u052b\u0003"+
		"\u00eew\u0000\u052b\u052c\u0005Y\u0000\u0000\u052c\u052d\u0003\u00eew"+
		"\u0000\u052d\u00eb\u0001\u0000\u0000\u0000\u052e\u0530\u0003\u009aM\u0000"+
		"\u052f\u052e\u0001\u0000\u0000\u0000\u052f\u0530\u0001\u0000\u0000\u0000"+
		"\u0530\u0531\u0001\u0000\u0000\u0000\u0531\u0532\u0005x\u0000\u0000\u0532"+
		"\u0533\u0003\u00eew\u0000\u0533\u0534\u0005~\u0000\u0000\u0534\u0539\u0003"+
		"\u00eew\u0000\u0535\u0536\u0005~\u0000\u0000\u0536\u0538\u0003\u00eew"+
		"\u0000\u0537\u0535\u0001\u0000\u0000\u0000\u0538\u053b\u0001\u0000\u0000"+
		"\u0000\u0539\u0537\u0001\u0000\u0000\u0000\u0539\u053a\u0001\u0000\u0000"+
		"\u0000\u053a\u053c\u0001\u0000\u0000\u0000\u053b\u0539\u0001\u0000\u0000"+
		"\u0000\u053c\u053d\u0005y\u0000\u0000\u053d\u00ed\u0001\u0000\u0000\u0000"+
		"\u053e\u053f\u0003\u00f0x\u0000\u053f\u00ef\u0001\u0000\u0000\u0000\u0540"+
		"\u0542\u0003\u00f2y\u0000\u0541\u0540\u0001\u0000\u0000\u0000\u0541\u0542"+
		"\u0001\u0000\u0000\u0000\u0542\u0545\u0001\u0000\u0000\u0000\u0543\u0544"+
		"\u0005\u009a\u0000\u0000\u0544\u0546\u0003\u01bc\u00de\u0000\u0545\u0543"+
		"\u0001\u0000\u0000\u0000\u0545\u0546\u0001\u0000\u0000\u0000\u0546\u0547"+
		"\u0001\u0000\u0000\u0000\u0547\u0548\u0003\u00c6c\u0000\u0548\u00f1\u0001"+
		"\u0000\u0000\u0000\u0549\u054a\u0003\u00f4z\u0000\u054a\u00f3\u0001\u0000"+
		"\u0000\u0000\u054b\u054c\u0003\u018c\u00c6\u0000\u054c\u00f5\u0001\u0000"+
		"\u0000\u0000\u054d\u054e\u0003\u008eG\u0000\u054e\u054f\u0005\t\u0000"+
		"\u0000\u054f\u0550\u0003\u00f8|\u0000\u0550\u0551\u0003^/\u0000\u0551"+
		"\u00f7\u0001\u0000\u0000\u0000\u0552\u0558\u0003\u009aM\u0000\u0553\u0554"+
		"\u0005?\u0000\u0000\u0554\u0555\u0003\u00eew\u0000\u0555\u0556\u0005\u008e"+
		"\u0000\u0000\u0556\u0557\u0003\u00eew\u0000\u0557\u0559\u0001\u0000\u0000"+
		"\u0000\u0558\u0553\u0001\u0000\u0000\u0000\u0558\u0559\u0001\u0000\u0000"+
		"\u0000\u0559\u0567\u0001\u0000\u0000\u0000\u055a\u055c\u0005\u0004\u0000"+
		"\u0000\u055b\u055a\u0001\u0000\u0000\u0000\u055b\u055c\u0001\u0000\u0000"+
		"\u0000\u055c\u0564\u0001\u0000\u0000\u0000\u055d\u055f\u0005?\u0000\u0000"+
		"\u055e\u055d\u0001\u0000\u0000\u0000\u055e\u055f\u0001\u0000\u0000\u0000"+
		"\u055f\u0560\u0001\u0000\u0000\u0000\u0560\u0561\u0003\u00eew\u0000\u0561"+
		"\u0562\u0005\u008e\u0000\u0000\u0562\u0563\u0003\u00eew\u0000\u0563\u0565"+
		"\u0001\u0000\u0000\u0000\u0564\u055e\u0001\u0000\u0000\u0000\u0564\u0565"+
		"\u0001\u0000\u0000\u0000\u0565\u0567\u0001\u0000\u0000\u0000\u0566\u0552"+
		"\u0001\u0000\u0000\u0000\u0566\u055b\u0001\u0000\u0000\u0000\u0567\u00f9"+
		"\u0001\u0000\u0000\u0000\u0568\u0569\u0003\u008eG\u0000\u0569\u056a\u0005"+
		"W\u0000\u0000\u056a\u056b\u0003\u00fc~\u0000\u056b\u056c\u0003^/\u0000"+
		"\u056c\u00fb\u0001\u0000\u0000\u0000\u056d\u0573\u0003\u009aM\u0000\u056e"+
		"\u056f\u0005%\u0000\u0000\u056f\u0570\u0003\u00eew\u0000\u0570\u0571\u0005"+
		"X\u0000\u0000\u0571\u0572\u0003\u00eew\u0000\u0572\u0574\u0001\u0000\u0000"+
		"\u0000\u0573\u056e\u0001\u0000\u0000\u0000\u0573\u0574\u0001\u0000\u0000"+
		"\u0000\u0574\u0582\u0001\u0000\u0000\u0000\u0575\u0577\u0005\u0004\u0000"+
		"\u0000\u0576\u0575\u0001\u0000\u0000\u0000\u0576\u0577\u0001\u0000\u0000"+
		"\u0000\u0577\u057f\u0001\u0000\u0000\u0000\u0578\u057a\u0005%\u0000\u0000"+
		"\u0579\u0578\u0001\u0000\u0000\u0000\u0579\u057a\u0001\u0000\u0000\u0000"+
		"\u057a\u057b\u0001\u0000\u0000\u0000\u057b\u057c\u0003\u00eew\u0000\u057c"+
		"\u057d\u0005X\u0000\u0000\u057d\u057e\u0003\u00eew\u0000\u057e\u0580\u0001"+
		"\u0000\u0000\u0000\u057f\u0579\u0001\u0000\u0000\u0000\u057f\u0580\u0001"+
		"\u0000\u0000\u0000\u0580\u0582\u0001\u0000\u0000\u0000\u0581\u056d\u0001"+
		"\u0000\u0000\u0000\u0581\u0576\u0001\u0000\u0000\u0000\u0582\u00fd\u0001"+
		"\u0000\u0000\u0000\u0583\u0584\u0003L&\u0000\u0584\u0585\u0005\b\u0000"+
		"\u0000\u0585\u0586\u0003\u0082A\u0000\u0586\u0587\u0003^/\u0000\u0587"+
		"\u00ff\u0001\u0000\u0000\u0000\u0588\u0589\u0003\u008eG\u0000\u0589\u058a"+
		"\u0005Q\u0000\u0000\u058a\u058c\u0003\u009aM\u0000\u058b\u058d\u0003\u0180"+
		"\u00c0\u0000\u058c\u058b\u0001\u0000\u0000\u0000\u058c\u058d\u0001\u0000"+
		"\u0000\u0000\u058d\u058e\u0001\u0000\u0000\u0000\u058e\u058f\u0003^/\u0000"+
		"\u058f\u0101\u0001\u0000\u0000\u0000\u0590\u0591\u0003L&\u0000\u0591\u0592"+
		"\u0005)\u0000\u0000\u0592\u0593\u0003\u0082A\u0000\u0593\u0594\u0003\u0104"+
		"\u0082\u0000\u0594\u0103\u0001\u0000\u0000\u0000\u0595\u059b\u0005o\u0000"+
		"\u0000\u0596\u0597\u0005z\u0000\u0000\u0597\u0598\u0003\u0106\u0083\u0000"+
		"\u0598\u0599\u0005{\u0000\u0000\u0599\u059b\u0001\u0000\u0000\u0000\u059a"+
		"\u0595\u0001\u0000\u0000\u0000\u059a\u0596\u0001\u0000\u0000\u0000\u059b"+
		"\u0105\u0001\u0000\u0000\u0000\u059c\u059f\u0003b1\u0000\u059d\u059f\u0003"+
		"\u0108\u0084\u0000\u059e\u059c\u0001\u0000\u0000\u0000\u059e\u059d\u0001"+
		"\u0000\u0000\u0000\u059f\u05a2\u0001\u0000\u0000\u0000\u05a0\u059e\u0001"+
		"\u0000\u0000\u0000\u05a0\u05a1\u0001\u0000\u0000\u0000\u05a1\u05a4\u0001"+
		"\u0000\u0000\u0000\u05a2\u05a0\u0001\u0000\u0000\u0000\u05a3\u05a5\u0003"+
		"\u010a\u0085\u0000\u05a4\u05a3\u0001\u0000\u0000\u0000\u05a4\u05a5\u0001"+
		"\u0000\u0000\u0000\u05a5\u0107\u0001\u0000\u0000\u0000\u05a6\u05a7\u0003"+
		"*\u0015\u0000\u05a7\u05a8\u0005N\u0000\u0000\u05a8\u05a9\u0003F#\u0000"+
		"\u05a9\u0109\u0001\u0000\u0000\u0000\u05aa\u05ab\u0003*\u0015\u0000\u05ab"+
		"\u05ac\u0003\u011a\u008d\u0000\u05ac\u010b\u0001\u0000\u0000\u0000\u05ad"+
		"\u05ae\u0003\u008eG\u0000\u05ae\u05af\u0005\u001f\u0000\u0000\u05af\u05b1"+
		"\u0003\u009aM\u0000\u05b0\u05b2\u0003\u0180\u00c0\u0000\u05b1\u05b0\u0001"+
		"\u0000\u0000\u0000\u05b1\u05b2\u0001\u0000\u0000\u0000\u05b2\u05b3\u0001"+
		"\u0000\u0000\u0000\u05b3\u05b4\u0003\u0104\u0082\u0000\u05b4\u010d\u0001"+
		"\u0000\u0000\u0000\u05b5\u05b6\u0003L&\u0000\u05b6\u05b7\u0005E\u0000"+
		"\u0000\u05b7\u05b8\u0003\u0082A\u0000\u05b8\u05b9\u0003\u0104\u0082\u0000"+
		"\u05b9\u010f\u0001\u0000\u0000\u0000\u05ba\u05bb\u0003\u008eG\u0000\u05bb"+
		"\u05bc\u0005\n\u0000\u0000\u05bc\u05be\u0003\u009aM\u0000\u05bd\u05bf"+
		"\u0003\u0180\u00c0\u0000\u05be\u05bd\u0001\u0000\u0000\u0000\u05be\u05bf"+
		"\u0001\u0000\u0000\u0000\u05bf\u05c0\u0001\u0000\u0000\u0000\u05c0\u05c1"+
		"\u0003\u0104\u0082\u0000\u05c1\u0111\u0001\u0000\u0000\u0000\u05c2\u05c3"+
		"\u0003\u008eG\u0000\u05c3\u05c5\u00052\u0000\u0000\u05c4\u05c6\u0007\u0006"+
		"\u0000\u0000\u05c5\u05c4\u0001\u0000\u0000\u0000\u05c5\u05c6\u0001\u0000"+
		"\u0000\u0000\u05c6\u05c8\u0001\u0000\u0000\u0000\u05c7\u05c9\u0003\u009a"+
		"M\u0000\u05c8\u05c7\u0001\u0000\u0000\u0000\u05c8\u05c9\u0001\u0000\u0000"+
		"\u0000\u05c9\u05cb\u0001\u0000\u0000\u0000\u05ca\u05cc\u0003\u0180\u00c0"+
		"\u0000\u05cb\u05ca\u0001\u0000\u0000\u0000\u05cb\u05cc\u0001\u0000\u0000"+
		"\u0000\u05cc\u05cd\u0001\u0000\u0000\u0000\u05cd\u05ce\u0003\u0104\u0082"+
		"\u0000\u05ce\u0113\u0001\u0000\u0000\u0000\u05cf\u05d0\u0003\u0116\u008b"+
		"\u0000\u05d0\u0115\u0001\u0000\u0000\u0000\u05d1\u05d2\u0003\u0118\u008c"+
		"\u0000\u05d2\u0117\u0001\u0000\u0000\u0000\u05d3\u05d4\u0003\u011a\u008d"+
		"\u0000\u05d4\u0119\u0001\u0000\u0000\u0000\u05d5\u05d6\u0006\u008d\uffff"+
		"\uffff\u0000\u05d6\u05d7\u0007\u0007\u0000\u0000\u05d7\u05e6\u0003\u011a"+
		"\u008d\u0015\u05d8\u05d9\u0005+\u0000\u0000\u05d9\u05da\u0003\u011a\u008d"+
		"\u0000\u05da\u05db\u0005\u0096\u0000\u0000\u05db\u05dc\u0003\u011a\u008d"+
		"\u0000\u05dc\u05dd\u0005\u001d\u0000\u0000\u05dd\u05de\u0003\u011a\u008d"+
		"\u0005\u05de\u05e6\u0001\u0000\u0000\u0000\u05df\u05e0\u0007\b\u0000\u0000"+
		"\u05e0\u05e6\u0003\u011e\u008f\u0000\u05e1\u05e2\u0005\u0004\u0000\u0000"+
		"\u05e2\u05e6\u0003\u011e\u008f\u0000\u05e3\u05e6\u0003\u0126\u0093\u0000"+
		"\u05e4\u05e6\u0003\u0134\u009a\u0000\u05e5\u05d5\u0001\u0000\u0000\u0000"+
		"\u05e5\u05d8\u0001\u0000\u0000\u0000\u05e5\u05df\u0001\u0000\u0000\u0000"+
		"\u05e5\u05e1\u0001\u0000\u0000\u0000\u05e5\u05e3\u0001\u0000\u0000\u0000"+
		"\u05e5\u05e4\u0001\u0000\u0000\u0000\u05e6\u062f\u0001\u0000\u0000\u0000"+
		"\u05e7\u05e8\n\u0014\u0000\u0000\u05e8\u05e9\u0007\t\u0000\u0000\u05e9"+
		"\u062e\u0003\u011a\u008d\u0014\u05ea\u05eb\n\u0013\u0000\u0000\u05eb\u05ec"+
		"\u0007\n\u0000\u0000\u05ec\u062e\u0003\u011a\u008d\u0014\u05ed\u05ee\n"+
		"\u0012\u0000\u0000\u05ee\u05ef\u0007\u000b\u0000\u0000\u05ef\u062e\u0003"+
		"\u011a\u008d\u0013\u05f0\u05f1\n\u0011\u0000\u0000\u05f1\u05f2\u0005\u008b"+
		"\u0000\u0000\u05f2\u062e\u0003\u011a\u008d\u0012\u05f3\u05f4\n\u0010\u0000"+
		"\u0000\u05f4\u05f5\u0007\f\u0000\u0000\u05f5\u062e\u0003\u011a\u008d\u0011"+
		"\u05f6\u05f7\n\u000b\u0000\u0000\u05f7\u05f8\u0007\r\u0000\u0000\u05f8"+
		"\u062e\u0003\u011a\u008d\f\u05f9\u05fa\n\n\u0000\u0000\u05fa\u05fb\u0007"+
		"\u000e\u0000\u0000\u05fb\u062e\u0003\u011a\u008d\u000b\u05fc\u05fd\n\t"+
		"\u0000\u0000\u05fd\u05fe\u0005_\u0000\u0000\u05fe\u062e\u0003\u011a\u008d"+
		"\n\u05ff\u0600\n\b\u0000\u0000\u0600\u0601\u0007\u000f\u0000\u0000\u0601"+
		"\u062e\u0003\u011a\u008d\t\u0602\u0603\n\u0007\u0000\u0000\u0603\u0604"+
		"\u0005-\u0000\u0000\u0604\u062e\u0003\u011a\u008d\b\u0605\u0606\n\u0006"+
		"\u0000\u0000\u0606\u0607\u0005\u0097\u0000\u0000\u0607\u062e\u0003\u011a"+
		"\u008d\u0007\u0608\u0609\n\u001b\u0000\u0000\u0609\u060a\u0005\u0098\u0000"+
		"\u0000\u060a\u062e\u0003\u0152\u00a9\u0000\u060b\u060c\n\u001a\u0000\u0000"+
		"\u060c\u060d\u0005\u008a\u0000\u0000\u060d\u062e\u0003\u0152\u00a9\u0000"+
		"\u060e\u060f\n\u0019\u0000\u0000\u060f\u0610\u0005\u008a\u0000\u0000\u0610"+
		"\u062e\u0003\u013a\u009d\u0000\u0611\u0612\n\u0018\u0000\u0000\u0612\u0613"+
		"\u0005\u0089\u0000\u0000\u0613\u0614\u0003\u0124\u0092\u0000\u0614\u0615"+
		"\u0003\u011c\u008e\u0000\u0615\u062e\u0001\u0000\u0000\u0000\u0616\u0617"+
		"\n\u0017\u0000\u0000\u0617\u0618\u0005\u0080\u0000\u0000\u0618\u0619\u0005"+
		"x\u0000\u0000\u0619\u061a\u0003\u012c\u0096\u0000\u061a\u061b\u0005y\u0000"+
		"\u0000\u061b\u062e\u0001\u0000\u0000\u0000\u061c\u061d\n\u0016\u0000\u0000"+
		"\u061d\u061e\u0005|\u0000\u0000\u061e\u061f\u0003\u012c\u0096\u0000\u061f"+
		"\u0620\u0005}\u0000\u0000\u0620\u062e\u0001\u0000\u0000\u0000\u0621\u0622"+
		"\n\u000f\u0000\u0000\u0622\u0623\u0007\u0010\u0000\u0000\u0623\u062e\u0003"+
		"\u011e\u008f\u0000\u0624\u0625\n\u000e\u0000\u0000\u0625\u0626\u0005\u0006"+
		"\u0000\u0000\u0626\u062e\u0003\u0120\u0090\u0000\u0627\u0628\n\r\u0000"+
		"\u0000\u0628\u0629\u0005\u0099\u0000\u0000\u0629\u062e\u0003\u011e\u008f"+
		"\u0000\u062a\u062b\n\f\u0000\u0000\u062b\u062c\u0005g\u0000\u0000\u062c"+
		"\u062e\u0003\u0120\u0090\u0000\u062d\u05e7\u0001\u0000\u0000\u0000\u062d"+
		"\u05ea\u0001\u0000\u0000\u0000\u062d\u05ed\u0001\u0000\u0000\u0000\u062d"+
		"\u05f0\u0001\u0000\u0000\u0000\u062d\u05f3\u0001\u0000\u0000\u0000\u062d"+
		"\u05f6\u0001\u0000\u0000\u0000\u062d\u05f9\u0001\u0000\u0000\u0000\u062d"+
		"\u05fc\u0001\u0000\u0000\u0000\u062d\u05ff\u0001\u0000\u0000\u0000\u062d"+
		"\u0602\u0001\u0000\u0000\u0000\u062d\u0605\u0001\u0000\u0000\u0000\u062d"+
		"\u0608\u0001\u0000\u0000\u0000\u062d\u060b\u0001\u0000\u0000\u0000\u062d"+
		"\u060e\u0001\u0000\u0000\u0000\u062d\u0611\u0001\u0000\u0000\u0000\u062d"+
		"\u0616\u0001\u0000\u0000\u0000\u062d\u061c\u0001\u0000\u0000\u0000\u062d"+
		"\u0621\u0001\u0000\u0000\u0000\u062d\u0624\u0001\u0000\u0000\u0000\u062d"+
		"\u0627\u0001\u0000\u0000\u0000\u062d\u062a\u0001\u0000\u0000\u0000\u062e"+
		"\u0631\u0001\u0000\u0000\u0000\u062f\u062d\u0001\u0000\u0000\u0000\u062f"+
		"\u0630\u0001\u0000\u0000\u0000\u0630\u011b\u0001\u0000\u0000\u0000\u0631"+
		"\u062f\u0001\u0000\u0000\u0000\u0632\u0636\u0003\u0152\u00a9\u0000\u0633"+
		"\u0636\u0003\u012e\u0097\u0000\u0634\u0636\u0003\u0146\u00a3\u0000\u0635"+
		"\u0632\u0001\u0000\u0000\u0000\u0635\u0633\u0001\u0000\u0000\u0000\u0635"+
		"\u0634\u0001\u0000\u0000\u0000\u0636\u011d\u0001\u0000\u0000\u0000\u0637"+
		"\u0638\u0003\u0122\u0091\u0000\u0638\u011f\u0001\u0000\u0000\u0000\u0639"+
		"\u063a\u0003\u0122\u0091\u0000\u063a\u0121\u0001\u0000\u0000\u0000\u063b"+
		"\u063c\u0003\u0124\u0092\u0000\u063c\u0123\u0001\u0000\u0000\u0000\u063d"+
		"\u063e\u00036\u001b\u0000\u063e\u0125\u0001\u0000\u0000\u0000\u063f\u0640"+
		"\u0005x\u0000\u0000\u0640\u0641\u0003\u0128\u0094\u0000\u0641\u0642\u0005"+
		"y\u0000\u0000\u0642\u0127\u0001\u0000\u0000\u0000\u0643\u0649\u0003\u012a"+
		"\u0095\u0000\u0644\u0646\u0003\u011a\u008d\u0000\u0645\u0647\u0005~\u0000"+
		"\u0000\u0646\u0645\u0001\u0000\u0000\u0000\u0646\u0647\u0001\u0000\u0000"+
		"\u0000\u0647\u0649\u0001\u0000\u0000\u0000\u0648\u0643\u0001\u0000\u0000"+
		"\u0000\u0648\u0644\u0001\u0000\u0000\u0000\u0649\u0129\u0001\u0000\u0000"+
		"\u0000\u064a\u064b\u0003\u0118\u008c\u0000\u064b\u064c\u0005~\u0000\u0000"+
		"\u064c\u064d\u0003\u012c\u0096\u0000\u064d\u012b\u0001\u0000\u0000\u0000"+
		"\u064e\u064f\u0003\u0128\u0094\u0000\u064f\u012d\u0001\u0000\u0000\u0000"+
		"\u0650\u0651\u0003\u0124\u0092\u0000\u0651\u012f\u0001\u0000\u0000\u0000"+
		"\u0652\u0655\u0003\u013a\u009d\u0000\u0653\u0655\u0003\u0132\u0099\u0000"+
		"\u0654\u0652\u0001\u0000\u0000\u0000\u0654\u0653\u0001\u0000\u0000\u0000"+
		"\u0655\u0131\u0001\u0000\u0000\u0000\u0656\u0657\u0003\u00d0h\u0000\u0657"+
		"\u0133\u0001\u0000\u0000\u0000\u0658\u0660\u0003\u0140\u00a0\u0000\u0659"+
		"\u0660\u0003\u0144\u00a2\u0000\u065a\u0660\u0003\u0136\u009b\u0000\u065b"+
		"\u0660\u0003\u0158\u00ac\u0000\u065c\u0660\u0003\u013e\u009f\u0000\u065d"+
		"\u0660\u0003\u0138\u009c\u0000\u065e\u0660\u0003\u0152\u00a9\u0000\u065f"+
		"\u0658\u0001\u0000\u0000\u0000\u065f\u0659\u0001\u0000\u0000\u0000\u065f"+
		"\u065a\u0001\u0000\u0000\u0000\u065f\u065b\u0001\u0000\u0000\u0000\u065f"+
		"\u065c\u0001\u0000\u0000\u0000\u065f\u065d\u0001\u0000\u0000\u0000\u065f"+
		"\u065e\u0001\u0000\u0000\u0000\u0660\u0135\u0001\u0000\u0000\u0000\u0661"+
		"\u0665\u0005>\u0000\u0000\u0662\u0663\u0005x\u0000\u0000\u0663\u0665\u0005"+
		"y\u0000\u0000\u0664\u0661\u0001\u0000\u0000\u0000\u0664\u0662\u0001\u0000"+
		"\u0000\u0000\u0665\u0137\u0001\u0000\u0000\u0000\u0666\u0667\u0003\u013a"+
		"\u009d\u0000\u0667\u0139\u0001\u0000\u0000\u0000\u0668\u0669\u0003\u013c"+
		"\u009e\u0000\u0669\u013b\u0001\u0000\u0000\u0000\u066a\u066b\u00036\u001b"+
		"\u0000\u066b\u013d\u0001\u0000\u0000\u0000\u066c\u066d\u00036\u001b\u0000"+
		"\u066d\u066e\u0005\u008a\u0000\u0000\u066e\u066f\u00059\u0000\u0000\u066f"+
		"\u013f\u0001\u0000\u0000\u0000\u0670\u0671\u0003\u0142\u00a1\u0000\u0671"+
		"\u0141\u0001\u0000\u0000\u0000\u0672\u0673\u0003\u00c0`\u0000\u0673\u0674"+
		"\u0003\u0146\u00a3\u0000\u0674\u0143\u0001\u0000\u0000\u0000\u0675\u0676"+
		"\u0005h\u0000\u0000\u0676\u0677\u0003\u00c0`\u0000\u0677\u0678\u0003\u0146"+
		"\u00a3\u0000\u0678\u0145\u0001\u0000\u0000\u0000\u0679\u067c\u0005x\u0000"+
		"\u0000\u067a\u067d\u0003\u014a\u00a5\u0000\u067b\u067d\u0003\u0148\u00a4"+
		"\u0000\u067c\u067a\u0001\u0000\u0000\u0000\u067c\u067b\u0001\u0000\u0000"+
		"\u0000\u067c\u067d\u0001\u0000\u0000\u0000\u067d\u067e\u0001\u0000\u0000"+
		"\u0000\u067e\u067f\u0005y\u0000\u0000\u067f\u0147\u0001\u0000\u0000\u0000"+
		"\u0680\u0685\u0003\u011a\u008d\u0000\u0681\u0682\u0005~\u0000\u0000\u0682"+
		"\u0684\u0003\u011a\u008d\u0000\u0683\u0681\u0001\u0000\u0000\u0000\u0684"+
		"\u0687\u0001\u0000\u0000\u0000\u0685\u0683\u0001\u0000\u0000\u0000\u0685"+
		"\u0686\u0001\u0000\u0000\u0000\u0686\u0149\u0001\u0000\u0000\u0000\u0687"+
		"\u0685\u0001\u0000\u0000\u0000\u0688\u068d\u0003\u014c\u00a6\u0000\u0689"+
		"\u068a\u0005~\u0000\u0000\u068a\u068c\u0003\u014c\u00a6\u0000\u068b\u0689"+
		"\u0001\u0000\u0000\u0000\u068c\u068f\u0001\u0000\u0000\u0000\u068d\u068b"+
		"\u0001\u0000\u0000\u0000\u068d\u068e\u0001\u0000\u0000\u0000\u068e\u014b"+
		"\u0001\u0000\u0000\u0000\u068f\u068d\u0001\u0000\u0000\u0000\u0690\u0691"+
		"\u0003\u014e\u00a7\u0000\u0691\u014d\u0001\u0000\u0000\u0000\u0692\u0693"+
		"\u0003\u0150\u00a8\u0000\u0693\u0694\u0005\u008e\u0000\u0000\u0694\u0695"+
		"\u0003\u011a\u008d\u0000\u0695\u014f\u0001\u0000\u0000\u0000\u0696\u0697"+
		"\u00036\u001b\u0000\u0697\u0151\u0001\u0000\u0000\u0000\u0698\u0699\u0003"+
		"\u0154\u00aa\u0000\u0699\u0153\u0001\u0000\u0000\u0000\u069a\u069b\u0003"+
		"\u0156\u00ab\u0000\u069b\u0155\u0001\u0000\u0000\u0000\u069c\u069d\u0005"+
		"z\u0000\u0000\u069d\u069e\u0003\u0106\u0083\u0000\u069e\u069f\u0005{\u0000"+
		"\u0000\u069f\u0157\u0001\u0000\u0000\u0000\u06a0\u06a7\u0005Z\u0000\u0000"+
		"\u06a1\u06a7\u0005 \u0000\u0000\u06a2\u06a7\u0003\u015e\u00af\u0000\u06a3"+
		"\u06a7\u0003\u0160\u00b0\u0000\u06a4\u06a7\u0003\u0162\u00b1\u0000\u06a5"+
		"\u06a7\u0003\u0166\u00b3\u0000\u06a6\u06a0\u0001\u0000\u0000\u0000\u06a6"+
		"\u06a1\u0001\u0000\u0000\u0000\u06a6\u06a2\u0001\u0000\u0000\u0000\u06a6"+
		"\u06a3\u0001\u0000\u0000\u0000\u06a6\u06a4\u0001\u0000\u0000\u0000\u06a6"+
		"\u06a5\u0001\u0000\u0000\u0000\u06a7\u0159\u0001\u0000\u0000\u0000\u06a8"+
		"\u06a9\u0003\u015c\u00ae\u0000\u06a9\u015b\u0001\u0000\u0000\u0000\u06aa"+
		"\u06ab\u0007\u0006\u0000\u0000\u06ab\u015d\u0001\u0000\u0000\u0000\u06ac"+
		"\u06ad\u0005\u009f\u0000\u0000\u06ad\u015f\u0001\u0000\u0000\u0000\u06ae"+
		"\u06af\u0005\u009d\u0000\u0000\u06af\u0161\u0001\u0000\u0000\u0000\u06b0"+
		"\u06b1\u0003\u0164\u00b2\u0000\u06b1\u0163\u0001\u0000\u0000\u0000\u06b2"+
		"\u06b4\u0005\u009d\u0000\u0000\u06b3\u06b2\u0001\u0000\u0000\u0000\u06b3"+
		"\u06b4\u0001\u0000\u0000\u0000\u06b4\u06b5\u0001\u0000\u0000\u0000\u06b5"+
		"\u06b6\u0005\u008a\u0000\u0000\u06b6\u06b9\u0007\u0011\u0000\u0000\u06b7"+
		"\u06b9\u0005\u009e\u0000\u0000\u06b8\u06b3\u0001\u0000\u0000\u0000\u06b8"+
		"\u06b7\u0001\u0000\u0000\u0000\u06b9\u0165\u0001\u0000\u0000\u0000\u06ba"+
		"\u06bb\u0005p\u0000\u0000\u06bb\u0167\u0001\u0000\u0000\u0000\u06bc\u06bd"+
		"\u0003L&\u0000\u06bd\u06be\u00051\u0000\u0000\u06be\u06bf\u0003\u0082"+
		"A\u0000\u06bf\u06c0\u0003^/\u0000\u06c0\u0169\u0001\u0000\u0000\u0000"+
		"\u06c1\u06c2\u0003\u008eG\u0000\u06c2\u06c3\u0005&\u0000\u0000\u06c3\u06c4"+
		"\u0003\u016e\u00b7\u0000\u06c4\u06c5\u0003^/\u0000\u06c5\u016b\u0001\u0000"+
		"\u0000\u0000\u06c6\u06c7\u0003\u008eG\u0000\u06c7\u06c8\u0005W\u0000\u0000"+
		"\u06c8\u06c9\u0005&\u0000\u0000\u06c9\u06ca\u0003\u016e\u00b7\u0000\u06ca"+
		"\u06cb\u0003^/\u0000\u06cb\u016d\u0001\u0000\u0000\u0000\u06cc\u06ce\u0003"+
		"\u009aM\u0000\u06cd\u06cf\u0003\u0180\u00c0\u0000\u06ce\u06cd\u0001\u0000"+
		"\u0000\u0000\u06ce\u06cf\u0001\u0000\u0000\u0000\u06cf\u06d2\u0001\u0000"+
		"\u0000\u0000\u06d0\u06d1\u0005?\u0000\u0000\u06d1\u06d3\u0003\u0170\u00b8"+
		"\u0000\u06d2\u06d0\u0001\u0000\u0000\u0000\u06d2\u06d3\u0001\u0000\u0000"+
		"\u0000\u06d3\u06d9\u0001\u0000\u0000\u0000\u06d4\u06d5\u0005(\u0000\u0000"+
		"\u06d5\u06d6\u0003\u0176\u00bb\u0000\u06d6\u06d7\u0005Y\u0000\u0000\u06d7"+
		"\u06d8\u0003\u0176\u00bb\u0000\u06d8\u06da\u0001\u0000\u0000\u0000\u06d9"+
		"\u06d4\u0001\u0000\u0000\u0000\u06d9\u06da\u0001\u0000\u0000\u0000\u06da"+
		"\u06e3\u0001\u0000\u0000\u0000\u06db\u06dd\u0005\u0004\u0000\u0000\u06dc"+
		"\u06db\u0001\u0000\u0000\u0000\u06dc\u06dd\u0001\u0000\u0000\u0000\u06dd"+
		"\u06de\u0001\u0000\u0000\u0000\u06de\u06df\u0003\u0176\u00bb\u0000\u06df"+
		"\u06e0\u0005Y\u0000\u0000\u06e0\u06e1\u0003\u0176\u00bb\u0000\u06e1\u06e3"+
		"\u0001\u0000\u0000\u0000\u06e2\u06cc\u0001\u0000\u0000\u0000\u06e2\u06dc"+
		"\u0001\u0000\u0000\u0000\u06e3\u016f\u0001\u0000\u0000\u0000\u06e4\u06e5"+
		"\u0003\u0172\u00b9\u0000\u06e5\u0171\u0001\u0000\u0000\u0000\u06e6\u06e7"+
		"\u0003\u0006\u0003\u0000\u06e7\u06e9\u0003\u0174\u00ba\u0000\u06e8\u06ea"+
		"\u0003\u0180\u00c0\u0000\u06e9\u06e8\u0001\u0000\u0000\u0000\u06e9\u06ea"+
		"\u0001\u0000\u0000\u0000\u06ea\u06f4\u0001\u0000\u0000\u0000\u06eb\u06ed"+
		"\u0003\u00c0`\u0000\u06ec\u06ee\u0003\u0190\u00c8\u0000\u06ed\u06ec\u0001"+
		"\u0000\u0000\u0000\u06ed\u06ee\u0001\u0000\u0000\u0000\u06ee\u06f4\u0001"+
		"\u0000\u0000\u0000\u06ef\u06f1\u0003\u0190\u00c8\u0000\u06f0\u06f2\u0003"+
		"\u00c0`\u0000\u06f1\u06f0\u0001\u0000\u0000\u0000\u06f1\u06f2\u0001\u0000"+
		"\u0000\u0000\u06f2\u06f4\u0001\u0000\u0000\u0000\u06f3\u06e6\u0001\u0000"+
		"\u0000\u0000\u06f3\u06eb\u0001\u0000\u0000\u0000\u06f3\u06ef\u0001\u0000"+
		"\u0000\u0000\u06f4\u0173\u0001\u0000\u0000\u0000\u06f5\u06f7\u0003\u00ac"+
		"V\u0000\u06f6\u06f5\u0001\u0000\u0000\u0000\u06f7\u06fa\u0001\u0000\u0000"+
		"\u0000\u06f8\u06f6\u0001\u0000\u0000\u0000\u06f8\u06f9\u0001\u0000\u0000"+
		"\u0000\u06f9\u06fb\u0001\u0000\u0000\u0000\u06fa\u06f8\u0001\u0000\u0000"+
		"\u0000\u06fb\u06fd\u0003\u00a8T\u0000\u06fc\u06fe\u0003\u00acV\u0000\u06fd"+
		"\u06fc\u0001\u0000\u0000\u0000\u06fd\u06fe\u0001\u0000\u0000\u0000\u06fe"+
		"\u0175\u0001\u0000\u0000\u0000\u06ff\u0700\u0003\u0178\u00bc\u0000\u0700"+
		"\u0177\u0001\u0000\u0000\u0000\u0701\u0702\u0003\u00c6c\u0000\u0702\u0703"+
		"\u0005\u008a\u0000\u0000\u0703\u0705\u0001\u0000\u0000\u0000\u0704\u0701"+
		"\u0001\u0000\u0000\u0000\u0704\u0705\u0001\u0000\u0000\u0000\u0705\u0706"+
		"\u0001\u0000\u0000\u0000\u0706\u0707\u0003\u017a\u00bd\u0000\u0707\u0179"+
		"\u0001\u0000\u0000\u0000\u0708\u0709\u0003\u017c\u00be\u0000\u0709\u017b"+
		"\u0001\u0000\u0000\u0000\u070a\u070b\u0003\u017e\u00bf\u0000\u070b\u017d"+
		"\u0001\u0000\u0000\u0000\u070c\u070d\u00036\u001b\u0000\u070d\u017f\u0001"+
		"\u0000\u0000\u0000\u070e\u070f\u0003\u0182\u00c1\u0000\u070f\u0181\u0001"+
		"\u0000\u0000\u0000\u0710\u0717\u0005\u008e\u0000\u0000\u0711\u0717\u0005"+
		"\u008f\u0000\u0000\u0712\u0714\u0005\u0016\u0000\u0000\u0713\u0715\u0007"+
		"\u0012\u0000\u0000\u0714\u0713\u0001\u0000\u0000\u0000\u0714\u0715\u0001"+
		"\u0000\u0000\u0000\u0715\u0717\u0001\u0000\u0000\u0000\u0716\u0710\u0001"+
		"\u0000\u0000\u0000\u0716\u0711\u0001\u0000\u0000\u0000\u0716\u0712\u0001"+
		"\u0000\u0000\u0000\u0717\u0718\u0001\u0000\u0000\u0000\u0718\u0719\u0003"+
		"\u011a\u008d\u0000\u0719\u0183\u0001\u0000\u0000\u0000\u071a\u071b\u0005"+
		"\u008e\u0000\u0000\u071b\u071c\u0003\u011a\u008d\u0000\u071c\u0185\u0001"+
		"\u0000\u0000\u0000\u071d\u0720\u0003\u0188\u00c4\u0000\u071e\u0720\u0003"+
		"\u018a\u00c5\u0000\u071f\u071d\u0001\u0000\u0000\u0000\u071f\u071e\u0001"+
		"\u0000\u0000\u0000\u0720\u0187\u0001\u0000\u0000\u0000\u0721\u0722\u0005"+
		":\u0000\u0000\u0722\u0723\u0003\u0006\u0003\u0000\u0723\u0724\u0003\u00b4"+
		"Z\u0000\u0724\u0725\u0003^/\u0000\u0725\u0189\u0001\u0000\u0000\u0000"+
		"\u0726\u0727\u0005:\u0000\u0000\u0727\u0728\u0003\u0006\u0003\u0000\u0728"+
		"\u0729\u0003\u0190\u00c8\u0000\u0729\u072a\u0003^/\u0000\u072a\u018b\u0001"+
		"\u0000\u0000\u0000\u072b\u072c\u0003\u0190\u00c8\u0000\u072c\u018d\u0001"+
		"\u0000\u0000\u0000\u072d\u072e\u0003\u0190\u00c8\u0000\u072e\u018f\u0001"+
		"\u0000\u0000\u0000\u072f\u0733\u0005|\u0000\u0000\u0730\u0731\u0003\u0192"+
		"\u00c9\u0000\u0731\u0732\u0005\u008b\u0000\u0000\u0732\u0734\u0001\u0000"+
		"\u0000\u0000\u0733\u0730\u0001\u0000\u0000\u0000\u0733\u0734\u0001\u0000"+
		"\u0000\u0000\u0734\u0735\u0001\u0000\u0000\u0000\u0735\u0736\u0003\u0192"+
		"\u00c9\u0000\u0736\u0737\u0005}\u0000\u0000\u0737\u0191\u0001\u0000\u0000"+
		"\u0000\u0738\u0739\u0003\u0194\u00ca\u0000\u0739\u0193\u0001\u0000\u0000"+
		"\u0000\u073a\u073d\u0003\u0158\u00ac\u0000\u073b\u073d\u0003\u0138\u009c"+
		"\u0000\u073c\u073a\u0001\u0000\u0000\u0000\u073c\u073b\u0001\u0000\u0000"+
		"\u0000\u073d\u0195\u0001\u0000\u0000\u0000\u073e\u0740\u0003L&\u0000\u073f"+
		"\u073e\u0001\u0000\u0000\u0000\u073f\u0740\u0001\u0000\u0000\u0000\u0740"+
		"\u0741\u0001\u0000\u0000\u0000\u0741\u0744\u00058\u0000\u0000\u0742\u0745"+
		"\u0003\u0006\u0003\u0000\u0743\u0745\u0003\u0082A\u0000\u0744\u0742\u0001"+
		"\u0000\u0000\u0000\u0744\u0743\u0001\u0000\u0000\u0000\u0745\u0747\u0001"+
		"\u0000\u0000\u0000\u0746\u0748\u0005\u009a\u0000\u0000\u0747\u0746\u0001"+
		"\u0000\u0000\u0000\u0747\u0748\u0001\u0000\u0000\u0000\u0748\u074c\u0001"+
		"\u0000\u0000\u0000\u0749\u074a\u0003\u01b8\u00dc\u0000\u074a\u074b\u0005"+
		"\u009a\u0000\u0000\u074b\u074d\u0001\u0000\u0000\u0000\u074c\u0749\u0001"+
		"\u0000\u0000\u0000\u074c\u074d\u0001\u0000\u0000\u0000\u074d\u074e\u0001"+
		"\u0000\u0000\u0000\u074e\u074f\u0003^/\u0000\u074f\u0197\u0001\u0000\u0000"+
		"\u0000\u0750\u0751\u0005\u0080\u0000\u0000\u0751\u0752\u0003\u019c\u00ce"+
		"\u0000\u0752\u0199\u0001\u0000\u0000\u0000\u0753\u0754\u0005\u0080\u0000"+
		"\u0000\u0754\u0755\u0003\u019c\u00ce\u0000\u0755\u019b\u0001\u0000\u0000"+
		"\u0000\u0756\u0757\u0003\u00c0`\u0000\u0757\u019d\u0001\u0000\u0000\u0000"+
		"\u0758\u075a\u0003\u019a\u00cd\u0000\u0759\u0758\u0001\u0000\u0000\u0000"+
		"\u075a\u075d\u0001\u0000\u0000\u0000\u075b\u0759\u0001\u0000\u0000\u0000"+
		"\u075b\u075c\u0001\u0000\u0000\u0000\u075c\u075e\u0001\u0000\u0000\u0000"+
		"\u075d\u075b\u0001\u0000\u0000\u0000\u075e\u075f\u0007\u0013\u0000\u0000"+
		"\u075f\u0769\u0003\u01a0\u00d0\u0000\u0760\u0761\u0005\u0001\u0000\u0000"+
		"\u0761\u0766\u0003\u0012\t\u0000\u0762\u0763\u0005~\u0000\u0000\u0763"+
		"\u0765\u0003\u0012\t\u0000\u0764\u0762\u0001\u0000\u0000\u0000\u0765\u0768"+
		"\u0001\u0000\u0000\u0000\u0766\u0764\u0001\u0000\u0000\u0000\u0766\u0767"+
		"\u0001\u0000\u0000\u0000\u0767\u076a\u0001\u0000\u0000\u0000\u0768\u0766"+
		"\u0001\u0000\u0000\u0000\u0769\u0760\u0001\u0000\u0000\u0000\u0769\u076a"+
		"\u0001\u0000\u0000\u0000\u076a\u076b\u0001\u0000\u0000\u0000\u076b\u076c"+
		"\u0003\u01a2\u00d1\u0000\u076c\u019f\u0001\u0000\u0000\u0000\u076d\u076e"+
		"\u0003\u0006\u0003\u0000\u076e\u076f\u0003\u01b6\u00db\u0000\u076f\u0771"+
		"\u0001\u0000\u0000\u0000\u0770\u076d\u0001\u0000\u0000\u0000\u0770\u0771"+
		"\u0001\u0000\u0000\u0000\u0771\u0772\u0001\u0000\u0000\u0000\u0772\u0773"+
		"\u0003\u00c0`\u0000\u0773\u01a1\u0001\u0000\u0000\u0000\u0774\u077e\u0005"+
		"o\u0000\u0000\u0775\u0779\u0005z\u0000\u0000\u0776\u0778\u0003\u01a4\u00d2"+
		"\u0000\u0777\u0776\u0001\u0000\u0000\u0000\u0778\u077b\u0001\u0000\u0000"+
		"\u0000\u0779\u0777\u0001\u0000\u0000\u0000\u0779\u077a\u0001\u0000\u0000"+
		"\u0000\u077a\u077c\u0001\u0000\u0000\u0000\u077b\u0779\u0001\u0000\u0000"+
		"\u0000\u077c\u077e\u0005{\u0000\u0000\u077d\u0774\u0001\u0000\u0000\u0000"+
		"\u077d\u0775\u0001\u0000\u0000\u0000\u077e\u01a3\u0001\u0000\u0000\u0000"+
		"\u077f\u0784\u00030\u0018\u0000\u0780\u0784\u0003\u01a6\u00d3\u0000\u0781"+
		"\u0784\u00034\u001a\u0000\u0782\u0784\u0003:\u001d\u0000\u0783\u077f\u0001"+
		"\u0000\u0000\u0000\u0783\u0780\u0001\u0000\u0000\u0000\u0783\u0781\u0001"+
		"\u0000\u0000\u0000\u0783\u0782\u0001\u0000\u0000\u0000\u0784\u01a5\u0001"+
		"\u0000\u0000\u0000\u0785\u0786\u0003\u01a8\u00d4\u0000\u0786\u01a7\u0001"+
		"\u0000\u0000\u0000\u0787\u0789\u0005!\u0000\u0000\u0788\u0787\u0001\u0000"+
		"\u0000\u0000\u0788\u0789\u0001\u0000\u0000\u0000\u0789\u078b\u0001\u0000"+
		"\u0000\u0000\u078a\u078c\u0003\u01be\u00df\u0000\u078b\u078a\u0001\u0000"+
		"\u0000\u0000\u078b\u078c\u0001\u0000\u0000\u0000\u078c\u078d\u0001\u0000"+
		"\u0000\u0000\u078d\u078f\u0003\u00ccf\u0000\u078e\u0790\u0003\u00a6S\u0000"+
		"\u078f\u078e\u0001\u0000\u0000\u0000\u078f\u0790\u0001\u0000\u0000\u0000"+
		"\u0790\u0792\u0001\u0000\u0000\u0000\u0791\u0793\u0003\u0180\u00c0\u0000"+
		"\u0792\u0791\u0001\u0000\u0000\u0000\u0792\u0793\u0001\u0000\u0000\u0000"+
		"\u0793\u0794\u0001\u0000\u0000\u0000\u0794\u0795\u0003\u01a2\u00d1\u0000"+
		"\u0795\u01a9\u0001\u0000\u0000\u0000\u0796\u0798\u0003\u019a\u00cd\u0000"+
		"\u0797\u0796\u0001\u0000\u0000\u0000\u0798\u079b\u0001\u0000\u0000\u0000"+
		"\u0799\u0797\u0001\u0000\u0000\u0000\u0799\u079a\u0001\u0000\u0000\u0000"+
		"\u079a\u079c\u0001\u0000\u0000\u0000\u079b\u0799\u0001\u0000\u0000\u0000"+
		"\u079c\u079d\u0003\u01ae\u00d7\u0000\u079d\u079e\u0003\u01b0\u00d8\u0000"+
		"\u079e\u01ab\u0001\u0000\u0000\u0000\u079f\u07a1\u0005b\u0000\u0000\u07a0"+
		"\u079f\u0001\u0000\u0000\u0000\u07a0\u07a1\u0001\u0000\u0000\u0000\u07a1"+
		"\u07a2\u0001\u0000\u0000\u0000\u07a2\u07a6\u0005c\u0000\u0000\u07a3\u07a5"+
		"\u0003\u019a\u00cd\u0000\u07a4\u07a3\u0001\u0000\u0000\u0000\u07a5\u07a8"+
		"\u0001\u0000\u0000\u0000\u07a6\u07a4\u0001\u0000\u0000\u0000\u07a6\u07a7"+
		"\u0001\u0000\u0000\u0000\u07a7\u07a9\u0001\u0000\u0000\u0000\u07a8\u07a6"+
		"\u0001\u0000\u0000\u0000\u07a9\u07aa\u0003\u01ae\u00d7\u0000\u07aa\u07ab"+
		"\u0003\u01b0\u00d8\u0000\u07ab\u01ad\u0001\u0000\u0000\u0000\u07ac\u07ae"+
		"\u0005C\u0000\u0000\u07ad\u07af\u0003\u0006\u0003\u0000\u07ae\u07ad\u0001"+
		"\u0000\u0000\u0000\u07ae\u07af\u0001\u0000\u0000\u0000\u07af\u01af\u0001"+
		"\u0000\u0000\u0000\u07b0\u07bc\u0005o\u0000\u0000\u07b1\u07b7\u0005z\u0000"+
		"\u0000\u07b2\u07b6\u0003(\u0014\u0000\u07b3\u07b6\u0003\u01b2\u00d9\u0000"+
		"\u07b4\u07b6\u0003B!\u0000\u07b5\u07b2\u0001\u0000\u0000\u0000\u07b5\u07b3"+
		"\u0001\u0000\u0000\u0000\u07b5\u07b4\u0001\u0000\u0000\u0000\u07b6\u07b9"+
		"\u0001\u0000\u0000\u0000\u07b7\u07b5\u0001\u0000\u0000\u0000\u07b7\u07b8"+
		"\u0001\u0000\u0000\u0000\u07b8\u07ba\u0001\u0000\u0000\u0000\u07b9\u07b7"+
		"\u0001\u0000\u0000\u0000\u07ba\u07bc\u0005{\u0000\u0000\u07bb\u07b0\u0001"+
		"\u0000\u0000\u0000\u07bb\u07b1\u0001\u0000\u0000\u0000\u07bc\u01b1\u0001"+
		"\u0000\u0000\u0000\u07bd\u07be\u0003*\u0015\u0000\u07be\u07bf\u0005$\u0000"+
		"\u0000\u07bf\u07c0\u0003\u011a\u008d\u0000\u07c0\u07c1\u0005o\u0000\u0000"+
		"\u07c1\u01b3\u0001\u0000\u0000\u0000\u07c2\u07c3\u00036\u001b\u0000\u07c3"+
		"\u07c4\u0005\u008e\u0000\u0000\u07c4\u07c5\u0003\u0006\u0003\u0000\u07c5"+
		"\u07c6\u0005g\u0000\u0000\u07c6\u07c7\u00036\u001b\u0000\u07c7\u07c8\u0005"+
		"o\u0000\u0000\u07c8\u01b5\u0001\u0000\u0000\u0000\u07c9\u07cd\u0005r\u0000"+
		"\u0000\u07ca\u07cb\u0005\\\u0000\u0000\u07cb\u07cd\u0005\u000b\u0000\u0000"+
		"\u07cc\u07c9\u0001\u0000\u0000\u0000\u07cc\u07ca\u0001\u0000\u0000\u0000"+
		"\u07cd\u01b7\u0001\u0000\u0000\u0000\u07ce\u07cf\u0007\u0014\u0000\u0000"+
		"\u07cf\u01b9\u0001\u0000\u0000\u0000\u07d0\u07d1\u0007\u0015\u0000\u0000"+
		"\u07d1\u01bb\u0001\u0000\u0000\u0000\u07d2\u07d3\u0007\u0016\u0000\u0000"+
		"\u07d3\u01bd\u0001\u0000\u0000\u0000\u07d4\u07d5\u0007\u0017\u0000\u0000"+
		"\u07d5\u01bf\u0001\u0000\u0000\u0000\u07d6\u07d7\u0007\u0018\u0000\u0000"+
		"\u07d7\u01c1\u0001\u0000\u0000\u0000\u07d8\u07d9\u0007\u0019\u0000\u0000"+
		"\u07d9\u01c3\u0001\u0000\u0000\u0000\u00d9\u01ce\u01d4\u01dd\u01e2\u01e7"+
		"\u01eb\u01f0\u01f5\u01f8\u01ff\u0208\u0215\u0219\u0221\u0224\u0226\u022a"+
		"\u0230\u0234\u023a\u0245\u0253\u025a\u025d\u0263\u0270\u0273\u027e\u0282"+
		"\u0286\u028d\u0291\u0294\u02a1\u02be\u02ca\u02d4\u02d9\u02dd\u02e1\u02e5"+
		"\u02e7\u02ec\u02f5\u02ff\u0308\u0311\u031a\u0323\u032b\u0330\u0337\u033b"+
		"\u0347\u034b\u034f\u0354\u0359\u035f\u0363\u0368\u036d\u0373\u0377\u037b"+
		"\u037f\u0383\u038d\u0394\u0398\u039c\u03a1\u03aa\u03af\u03bc\u03bf\u03c2"+
		"\u03c7\u03cb\u03cf\u03d5\u03d8\u03dd\u03e1\u03e6\u03e9\u03ec\u03ef\u03f2"+
		"\u03fc\u0401\u0405\u040a\u0411\u0414\u041a\u041f\u042c\u0432\u0438\u043b"+
		"\u0441\u0444\u0448\u044c\u0450\u0452\u0454\u045d\u0464\u046f\u0480\u0484"+
		"\u048b\u0497\u049a\u04a0\u04ab\u04af\u04b3\u04b8\u04bb\u04be\u04c1\u04ce"+
		"\u04d4\u04d9\u04de\u04e4\u04ea\u04fe\u0512\u0515\u0518\u051e\u0521\u0526"+
		"\u0528\u052f\u0539\u0541\u0545\u0558\u055b\u055e\u0564\u0566\u0573\u0576"+
		"\u0579\u057f\u0581\u058c\u059a\u059e\u05a0\u05a4\u05b1\u05be\u05c5\u05c8"+
		"\u05cb\u05e5\u062d\u062f\u0635\u0646\u0648\u0654\u065f\u0664\u067c\u0685"+
		"\u068d\u06a6\u06b3\u06b8\u06ce\u06d2\u06d9\u06dc\u06e2\u06e9\u06ed\u06f1"+
		"\u06f3\u06f8\u06fd\u0704\u0714\u0716\u071f\u0733\u073c\u073f\u0744\u0747"+
		"\u074c\u075b\u0766\u0769\u0770\u0779\u077d\u0783\u0788\u078b\u078f\u0792"+
		"\u0799\u07a0\u07a6\u07ae\u07b5\u07b7\u07bb\u07cc";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}