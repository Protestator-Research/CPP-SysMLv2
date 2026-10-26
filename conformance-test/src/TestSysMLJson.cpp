//
// Tests of the JSON serialization and parsing of the SysML metaclasses: the round trip of every concrete metaclass, the constructors
// that take a name or a JSON string, the enumerations, the references that are only known by their ids, the special cases (Expose,
// ConnectionDefinition::isSufficient) and the SysML element factory. Modeled on TestKerMLJson.cpp.
//

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <kerml/KerML.h>
#include <kerml/model/ElementLinker.h>
#include <sysml/SysML.h>
#include <sysmlv2/rest/serialization/SysMLv2Deserializer.h>

namespace {
    using namespace SysMLv2::Entities;
    namespace K = KerML::Entities;
    using K::Element;

    // Every concrete metaclass of SysML (the ones the factory creates). The test MetaclassListIsComplete compares it with metaclasses().
#define SYSML_CONCRETE_CLASSES(X) \
    X(AcceptActionUsage) X(ActionDefinition) X(ActionUsage) X(ActorMembership) X(AllocationDefinition) \
    X(AllocationUsage) X(AnalysisCaseDefinition) X(AnalysisCaseUsage) X(AssertConstraintUsage) \
    X(AssignmentActionUsage) X(AttributeDefinition) X(AttributeUsage) X(BindingConnectorAsUsage) \
    X(CalculationDefinition) X(CalculationUsage) X(CaseDefinition) X(CaseUsage) X(ConcernDefinition) \
    X(ConcernUsage) X(ConjugatedPortDefinition) X(ConjugatedPortTyping) X(ConnectionDefinition) \
    X(ConnectionUsage) X(ConstraintDefinition) X(ConstraintUsage) X(DecisionNode) X(Definition) \
    X(EnumerationDefinition) X(EnumerationUsage) X(EventOccurrenceUsage) X(ExhibitStateUsage) \
    X(FlowDefinition) X(FlowUsage) X(ForLoopActionUsage) X(ForkNode) X(FramedConcernMembership) \
    X(IfActionUsage) X(IncludeUseCaseUsage) X(InterfaceDefinition) X(InterfaceUsage) X(ItemDefinition) \
    X(ItemUsage) X(JoinNode) X(MembershipExpose) X(MergeNode) X(MetadataDefinition) X(MetadataUsage) \
    X(NamespaceExpose) X(ObjectiveMembership) X(OccurrenceDefinition) X(OccurrenceUsage) X(PartDefinition) \
    X(PartUsage) X(PerformActionUsage) X(PortConjugation) X(PortDefinition) X(PortUsage) X(ReferenceUsage) \
    X(RenderingDefinition) X(RenderingUsage) X(RequirementConstraintMembership) X(RequirementDefinition) \
    X(RequirementUsage) X(RequirementVerificationMembership) X(SatisfyRequirementUsage) X(SendActionUsage) \
    X(StakeholderMembership) X(StateDefinition) X(StateSubactionMembership) X(StateUsage) X(SubjectMembership) \
    X(SuccessionAsUsage) X(SuccessionFlowUsage) X(TerminateActionUsage) X(TransitionFeatureMembership) \
    X(TransitionUsage) X(TriggerInvocationExpression) X(Usage) X(UseCaseDefinition) X(UseCaseUsage) \
    X(VariantMembership) X(VerificationCaseDefinition) X(VerificationCaseUsage) X(ViewDefinition) \
    X(ViewRenderingMembership) X(ViewUsage) X(ViewpointDefinition) X(ViewpointUsage) X(WhileLoopActionUsage)

    using Lookup = std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>;

    std::string newId() {
        return boost::uuids::to_string(boost::uuids::random_generator()());
    }

    std::string idOf(Element& element) {
        return boost::uuids::to_string(element.getId());
    }

    nlohmann::json ref(Element& element) {
        return {{"@id", idOf(element)}};
    }

    nlohmann::json refs(std::initializer_list<Element*> elements) {
        nlohmann::json array = nlohmann::json::array();
        for (Element* element : elements)
            array.push_back(ref(*element));
        return array;
    }

    Lookup lookupIn(std::map<boost::uuids::uuid, std::shared_ptr<Element>>& elements) {
        return [&elements](const boost::uuids::uuid& id) -> std::shared_ptr<Element> {
            const auto it = elements.find(id);
            return it == elements.end() ? nullptr : it->second;
        };
    }

    template<class T>
    nlohmann::json serialized(T& element) {
        return nlohmann::json::parse(element.serializeToJson());
    }

    /**
     * Sets properties that are no references, so that the round trip has something to keep. SysML specific properties are only set if
     * the metaclass has them.
     */
    template<class T>
    void populate(T& element) {
        element.setDeclaredName("Name");
        element.setDeclaredShortName("short");
        element.setAliasIds({"alias1", "alias2"});
        element.setIsLibraryElement(true);
        if constexpr (requires { element.setIsVariation(true); })
            element.setIsVariation(true);
        if constexpr (requires { element.setIsIndividual(true); })
            element.setIsIndividual(true);
        if constexpr (requires { element.setIsParallel(true); })
            element.setIsParallel(true);
        if constexpr (requires { element.setPortionKind(PortionKind::timeslice); })
            element.setPortionKind(PortionKind::timeslice);
        if constexpr (requires { element.setReqId(std::string("R-1")); })
            element.setReqId(std::string("R-1"));
        if constexpr (requires { element.setKind(RequirementConstraintKind::assumption); })
            element.setKind(RequirementConstraintKind::assumption);
        if constexpr (requires { element.setKind(StateSubactionKind::exit); })
            element.setKind(StateSubactionKind::exit);
        if constexpr (requires { element.setKind(TransitionFeatureKind::effect); })
            element.setKind(TransitionFeatureKind::effect);
        if constexpr (requires { element.setKind(TriggerKind::after); })
            element.setKind(TriggerKind::after);
    }

    template<class T>
    void expectRoundTrip(const std::string& type) {
        SCOPED_TRACE(type);
        std::shared_ptr<T> original;
        ASSERT_NO_THROW(original = std::make_shared<T>(std::string("Created")));
        populate(*original);

        std::string text;
        ASSERT_NO_THROW(text = original->serializeToJson());
        const nlohmann::json json = nlohmann::json::parse(text);
        EXPECT_EQ(json.at("@type"), type);
        EXPECT_EQ(json.at("@id"), boost::uuids::to_string(original->getId()));
        EXPECT_EQ(json.at("declaredName"), "Name");
        EXPECT_EQ(json.at("declaredShortName"), "short");
        EXPECT_EQ(json.at("aliasIds"), nlohmann::json::array({"alias1", "alias2"}));
        EXPECT_EQ(json.at("isLibraryElement"), true);

        std::shared_ptr<T> copy;
        ASSERT_NO_THROW(copy = std::make_shared<T>(text));
        EXPECT_EQ(copy->getType(), type);
        EXPECT_EQ(copy->metaclassName(), type);
        EXPECT_EQ(copy->getId(), original->getId());
        ASSERT_TRUE(copy->declaredName().has_value());
        EXPECT_EQ(*copy->declaredName(), "Name");
        // (the JSON the copy was created from would be returned for what the copy does not change: look at the copy alone)
        copy->discardSourceJson();
        EXPECT_EQ(nlohmann::json::parse(copy->serializeToJson()), json);
        EXPECT_FALSE(copy->hasUnresolvedJsonReferences());
    }

    template<class T>
    void expectDefaultSerializes(const std::string& type) {
        SCOPED_TRACE(type);
        T element(std::string("x"));
        nlohmann::json json;
        ASSERT_NO_THROW(json = serialized(element));
        EXPECT_EQ(json.at("@type"), type);
        EXPECT_EQ(json.at("declaredName"), "x");
        EXPECT_TRUE(json.contains("@id"));
        // the string constructor with JSON gives the same type, and a name that merely starts like text stays a name
        EXPECT_FALSE(element.hasUnresolvedJsonReferences());
    }

    template<class T>
    void expectFactoryCreates(const std::string& type) {
        SCOPED_TRACE(type);
        const nlohmann::json json = {{"@id", newId()}, {"@type", type}, {"declaredName", "Created"}};
        std::shared_ptr<Element> created;
        ASSERT_NO_THROW(created = createElementFromJson(json.dump()));
        ASSERT_NE(created, nullptr);
        EXPECT_EQ(created->getType(), type);
        EXPECT_NE(std::dynamic_pointer_cast<T>(created), nullptr);
        ASSERT_TRUE(created->declaredName().has_value());
        EXPECT_EQ(*created->declaredName(), "Created");
    }
}

TEST(TestSysMLJson, MetaclassListIsComplete) {
    std::set<std::string> listed;
#define SYSML_LIST(Name) EXPECT_TRUE(listed.insert(#Name).second) << #Name;
    SYSML_CONCRETE_CLASSES(SYSML_LIST)
#undef SYSML_LIST
    std::set<std::string> concrete;
    for (const auto& descriptor : metaclasses()) {
        if (!descriptor.isAbstract)
            concrete.insert(std::string(descriptor.name));
    }
    EXPECT_EQ(concrete.size(), 89u);
    EXPECT_EQ(listed, concrete);
}

TEST(TestSysMLJson, RoundTripOfEveryConcreteMetaclass) {
#define SYSML_ROUND_TRIP(Name) expectRoundTrip<Name>(#Name);
    SYSML_CONCRETE_CLASSES(SYSML_ROUND_TRIP)
#undef SYSML_ROUND_TRIP
}

TEST(TestSysMLJson, DefaultConstructedElementsSerializeToValidJson) {
#define SYSML_DEFAULT(Name) expectDefaultSerializes<Name>(#Name);
    SYSML_CONCRETE_CLASSES(SYSML_DEFAULT)
#undef SYSML_DEFAULT
}

TEST(TestSysMLJson, NameOrJsonConstructor) {
    PartUsage named(std::string("engine"));
    ASSERT_TRUE(named.declaredName().has_value());
    EXPECT_EQ(*named.declaredName(), "engine");
    EXPECT_EQ(named.getType(), "PartUsage");

    const std::string id = newId();
    PartUsage parsed("  \n{\"@id\": \"" + id + "\", \"@type\": \"Element\", \"declaredName\": \"fromJson\"}");
    EXPECT_EQ(idOf(parsed), id);
    ASSERT_TRUE(parsed.declaredName().has_value());
    EXPECT_EQ(*parsed.declaredName(), "fromJson");
    // the metaclass decides the type, not the JSON
    EXPECT_EQ(parsed.getType(), "PartUsage");
    EXPECT_EQ(parsed.metaclassName(), "PartUsage");

    // a class with several bases
    ConnectionDefinition connection(nlohmann::json({{"@id", newId()}, {"declaredName", "link"}}).dump());
    EXPECT_EQ(*connection.declaredName(), "link");
    EXPECT_THROW(PartUsage(std::string("{not json")), nlohmann::json::exception);
}

TEST(TestSysMLJson, StoredPropertiesAreWrittenAndRead) {
    EnumerationDefinition enumeration(std::string("E"));
    enumeration.setIsVariation(true);
    EXPECT_EQ(serialized(enumeration).at("isVariation"), true);
    EnumerationDefinition enumerationCopy(enumeration.serializeToJson());
    EXPECT_TRUE(enumerationCopy.isVariation());

    PartUsage usage(std::string("U"));
    EXPECT_EQ(serialized(usage).at("isVariation"), false);
    usage.setIsVariation(true);
    usage.setIsIndividual(true);
    PartUsage usageCopy(usage.serializeToJson());
    EXPECT_TRUE(usageCopy.isVariation());
    EXPECT_TRUE(usageCopy.isIndividual());

    OccurrenceDefinition definition(std::string("D"));
    definition.setIsIndividual(true);
    OccurrenceDefinition definitionCopy(definition.serializeToJson());
    EXPECT_TRUE(definitionCopy.isIndividual());

    StateUsage state(std::string("S"));
    state.setIsParallel(true);
    EXPECT_EQ(serialized(state).at("isParallel"), true);
    StateUsage stateCopy(state.serializeToJson());
    EXPECT_TRUE(stateCopy.isParallel());
    StateDefinition stateDefinition(std::string("SD"));
    stateDefinition.setIsParallel(true);
    EXPECT_TRUE(StateDefinition(stateDefinition.serializeToJson()).isParallel());

    RequirementUsage requirement(std::string("R"));
    EXPECT_TRUE(serialized(requirement).at("reqId").is_null());
    requirement.setReqId(std::string("REQ-7"));
    EXPECT_EQ(serialized(requirement).at("reqId"), "REQ-7");
    RequirementUsage requirementCopy(requirement.serializeToJson());
    ASSERT_TRUE(requirementCopy.reqId().has_value());
    EXPECT_EQ(*requirementCopy.reqId(), "REQ-7");
    // a derived many-valued String is written as an array and not read
    EXPECT_TRUE(serialized(requirement).at("text").is_array());
    RequirementUsage ignoresText(nlohmann::json({{"@id", newId()}, {"text", nlohmann::json::array({"x"})}}).dump());
    EXPECT_TRUE(ignoresText.text().empty());
}

TEST(TestSysMLJson, EnumerationsUseTheOmgLiterals) {
    struct Case { StateSubactionKind kind; const char* literal; };
    for (const Case& c : {Case{StateSubactionKind::entry, "entry"}, Case{StateSubactionKind::do_, "do"}, Case{StateSubactionKind::exit, "exit"}}) {
        SCOPED_TRACE(c.literal);
        StateSubactionMembership membership(std::string("m"));
        membership.setKind(c.kind);
        EXPECT_EQ(serialized(membership).at("kind"), c.literal);
        StateSubactionMembership copy(nlohmann::json({{"@id", newId()}, {"kind", c.literal}}).dump());
        EXPECT_TRUE(copy.kind() == c.kind);
        StateSubactionMembership again(membership.serializeToJson());
        EXPECT_TRUE(again.kind() == c.kind);
    }
    struct TransitionCase { TransitionFeatureKind kind; const char* literal; };
    for (const TransitionCase& c : {TransitionCase{TransitionFeatureKind::trigger, "trigger"}, TransitionCase{TransitionFeatureKind::guard, "guard"},
                                    TransitionCase{TransitionFeatureKind::effect, "effect"}}) {
        SCOPED_TRACE(c.literal);
        TransitionFeatureMembership membership(std::string("m"));
        membership.setKind(c.kind);
        EXPECT_EQ(serialized(membership).at("kind"), c.literal);
        TransitionFeatureMembership copy(membership.serializeToJson());
        EXPECT_TRUE(copy.kind() == c.kind);
    }
    struct TriggerCase { TriggerKind kind; const char* literal; };
    for (const TriggerCase& c : {TriggerCase{TriggerKind::when, "when"}, TriggerCase{TriggerKind::at, "at"}, TriggerCase{TriggerKind::after, "after"}}) {
        SCOPED_TRACE(c.literal);
        TriggerInvocationExpression expression(std::string("t"));
        expression.setKind(c.kind);
        EXPECT_EQ(serialized(expression).at("kind"), c.literal);
        TriggerInvocationExpression copy(expression.serializeToJson());
        EXPECT_TRUE(copy.kind() == c.kind);
    }
    for (const auto kind : {RequirementConstraintKind::assumption, RequirementConstraintKind::requirement}) {
        const char* literal = kind == RequirementConstraintKind::assumption ? "assumption" : "requirement";
        SCOPED_TRACE(literal);
        RequirementConstraintMembership membership(std::string("m"));
        membership.setKind(kind);
        EXPECT_EQ(serialized(membership).at("kind"), literal);
        RequirementConstraintMembership copy(membership.serializeToJson());
        EXPECT_TRUE(copy.kind() == kind);
        RequirementVerificationMembership verification(std::string("v"));
        verification.setKind(kind);
        EXPECT_TRUE(RequirementVerificationMembership(verification.serializeToJson()).kind() == kind);
        FramedConcernMembership concern(std::string("c"));
        concern.setKind(kind);
        EXPECT_TRUE(FramedConcernMembership(concern.serializeToJson()).kind() == kind);
    }

    // an unknown literal or a literal of the wrong JSON type keeps the default
    StateSubactionMembership unknown(nlohmann::json({{"@id", newId()}, {"kind", "sometimes"}}).dump());
    StateSubactionMembership fresh(std::string("f"));
    EXPECT_TRUE(unknown.kind() == fresh.kind());
    StateSubactionMembership wrongType(nlohmann::json({{"@id", newId()}, {"kind", 3}}).dump());
    EXPECT_TRUE(wrongType.kind() == fresh.kind());
    // the C++ spelling of the literal is not the JSON spelling
    StateSubactionMembership cppSpelling(nlohmann::json({{"@id", newId()}, {"kind", "do_"}}).dump());
    EXPECT_TRUE(cppSpelling.kind() == fresh.kind());
}

TEST(TestSysMLJson, OptionalPortionKind) {
    OccurrenceUsage usage(std::string("o"));
    EXPECT_FALSE(usage.portionKind().has_value());
    EXPECT_TRUE(serialized(usage).at("portionKind").is_null());
    OccurrenceUsage emptyCopy(usage.serializeToJson());
    EXPECT_FALSE(emptyCopy.portionKind().has_value());

    usage.setPortionKind(PortionKind::snapshot);
    EXPECT_EQ(serialized(usage).at("portionKind"), "snapshot");
    OccurrenceUsage snapshotCopy(usage.serializeToJson());
    ASSERT_TRUE(snapshotCopy.portionKind().has_value());
    EXPECT_TRUE(*snapshotCopy.portionKind() == PortionKind::snapshot);

    usage.setPortionKind(PortionKind::timeslice);
    EXPECT_EQ(serialized(usage).at("portionKind"), "timeslice");
    OccurrenceUsage timesliceCopy(usage.serializeToJson());
    ASSERT_TRUE(timesliceCopy.portionKind().has_value());
    EXPECT_TRUE(*timesliceCopy.portionKind() == PortionKind::timeslice);

    // the value can be cleared again, and a null in the JSON leaves the default
    usage.setPortionKind(std::nullopt);
    EXPECT_TRUE(serialized(usage).at("portionKind").is_null());
    OccurrenceUsage nullCopy(nlohmann::json({{"@id", newId()}, {"portionKind", nullptr}}).dump());
    EXPECT_FALSE(nullCopy.portionKind().has_value());
}

TEST(TestSysMLJson, ExposeForwardsToImport) {
    MembershipExpose membership(std::string("e"));
    // the defaults of Expose
    EXPECT_TRUE(membership.visibility() == K::VisibilityKind::PROTECTED);
    EXPECT_TRUE(membership.isImportAll());
    auto json = serialized(membership);
    EXPECT_EQ(json.at("visibility"), "protected");
    EXPECT_EQ(json.at("isImportAll"), true);
    EXPECT_EQ(json.at("@type"), "MembershipExpose");

    membership.setVisibility(K::VisibilityKind::PUBLIC);
    membership.setIsImportAll(false);
    json = serialized(membership);
    EXPECT_EQ(json.at("visibility"), "public");
    EXPECT_EQ(json.at("isImportAll"), false);

    MembershipExpose copy(membership.serializeToJson());
    EXPECT_TRUE(copy.visibility() == K::VisibilityKind::PUBLIC);
    EXPECT_FALSE(copy.isImportAll());
    // the SysML property and the KerML Import property are the same value
    K::Import& import = copy;
    EXPECT_TRUE(import.visibility() == K::VisibilityKind::PUBLIC);
    EXPECT_FALSE(import.isImportAll());
    copy.discardSourceJson();
    EXPECT_EQ(serialized(copy), json);

    NamespaceExpose namespaceExpose(nlohmann::json({{"@id", newId()}, {"visibility", "private"}, {"isImportAll", false}}).dump());
    EXPECT_TRUE(namespaceExpose.visibility() == K::VisibilityKind::PRIVATE);
    EXPECT_FALSE(namespaceExpose.isImportAll());
    EXPECT_EQ(serialized(namespaceExpose).at("visibility"), "private");
}

TEST(TestSysMLJson, ConnectionDefinitionIsSufficientIsBothMembers) {
    ConnectionDefinition connection(std::string("c"));
    EXPECT_TRUE(connection.isSufficient());
    EXPECT_EQ(serialized(connection).at("isSufficient"), true);

    connection.setIsSufficient(false);
    EXPECT_EQ(serialized(connection).at("isSufficient"), false);
    ConnectionDefinition copy(connection.serializeToJson());
    EXPECT_FALSE(copy.isSufficient());
    // the member of the KerML Type is set as well
    K::Type& type = copy;
    EXPECT_FALSE(type.isSufficient());
    copy.discardSourceJson();
    EXPECT_EQ(serialized(copy).at("isSufficient"), false);

    // the SysML value is the one that is written, even if the Type member differs
    ConnectionDefinition differing(std::string("d"));
    differing.setIsSufficient(true);
    K::Type& differingType = differing;
    differingType.setIsSufficient(false);
    EXPECT_EQ(serialized(differing).at("isSufficient"), true);

    ConnectionDefinition fromTrue(nlohmann::json({{"@id", newId()}, {"isSufficient", true}}).dump());
    K::Type& fromTrueType = fromTrue;
    EXPECT_TRUE(fromTrue.isSufficient());
    EXPECT_TRUE(fromTrueType.isSufficient());
}

TEST(TestSysMLJson, FactoryCreatesTheMetaclassOfTheType) {
#define SYSML_FACTORY(Name) expectFactoryCreates<Name>(#Name);
    SYSML_CONCRETE_CLASSES(SYSML_FACTORY)
#undef SYSML_FACTORY
}

TEST(TestSysMLJson, FactoryFallsBackToKerMLAndToPlainElements) {
    const auto kerml = createElementFromJson(nlohmann::json({{"@id", newId()}, {"@type", "Package"}, {"declaredName", "P"}}).dump());
    ASSERT_NE(kerml, nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<K::Package>(kerml), nullptr);
    EXPECT_EQ(kerml->getType(), "Package");

    const auto feature = createElementFromJson(nlohmann::json({{"@id", newId()}, {"@type", "Feature"}}).dump());
    EXPECT_NE(std::dynamic_pointer_cast<K::Feature>(feature), nullptr);
    EXPECT_EQ(std::dynamic_pointer_cast<Usage>(feature), nullptr);

    // the base metaclasses Usage and Definition are concrete in the metamodel
    EXPECT_NE(std::dynamic_pointer_cast<Usage>(createElementFromJson(nlohmann::json({{"@id", newId()}, {"@type", "Usage"}}).dump())), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<Definition>(createElementFromJson(nlohmann::json({{"@id", newId()}, {"@type", "Definition"}}).dump())), nullptr);

    // an unknown type and an abstract SysML metaclass are plain elements that keep their type
    for (const char* type : {"NoSuchMetaclass", "LoopActionUsage", "ControlNode", "Expose", "ConnectorAsUsage"}) {
        SCOPED_TRACE(type);
        const auto plain = createElementFromJson(nlohmann::json({{"@id", newId()}, {"@type", type}, {"declaredName", "x"}}).dump());
        ASSERT_NE(plain, nullptr);
        EXPECT_EQ(plain->getType(), type);
        EXPECT_EQ(std::dynamic_pointer_cast<Usage>(plain), nullptr);
        EXPECT_EQ(std::dynamic_pointer_cast<Definition>(plain), nullptr);
    }
    // a JSON without type
    const auto untyped = createElementFromJson(nlohmann::json({{"@id", newId()}}).dump());
    ASSERT_NE(untyped, nullptr);
    EXPECT_EQ(untyped->getType(), "Element");
}

TEST(TestSysMLJson, ReferencesToPortDefinitionsAreResolved) {
    auto portDefinition = std::make_shared<PortDefinition>(std::string("PD"));
    auto conjugated = std::make_shared<ConjugatedPortDefinition>(std::string("~PD"));
    auto notAPort = std::make_shared<PartDefinition>(std::string("X"));
    std::map<boost::uuids::uuid, std::shared_ptr<Element>> elements;
    for (const std::shared_ptr<Element>& element : std::vector<std::shared_ptr<Element>>{portDefinition, conjugated, notAPort})
        elements[element->getId()] = element;
    const auto lookup = lookupIn(elements);

    // PortConjugation: the stored originalPortDefinition and the derived conjugatedPortDefinition
    const nlohmann::json conjugationJson = {{"@id", newId()}, {"@type", "PortConjugation"},
                                            {"originalPortDefinition", ref(*portDefinition)}, {"conjugatedPortDefinition", ref(*conjugated)}};
    PortConjugation conjugation(conjugationJson.dump());
    conjugation.discardSourceJson();
    ASSERT_TRUE(conjugation.hasUnresolvedJsonReferences());
    EXPECT_EQ(conjugation.originalPortDefinition(), nullptr);
    // unresolved references are written unchanged
    const auto unresolved = serialized(conjugation);
    EXPECT_EQ(unresolved.at("originalPortDefinition"), conjugationJson.at("originalPortDefinition"));
    EXPECT_EQ(unresolved.at("conjugatedPortDefinition"), conjugationJson.at("conjugatedPortDefinition"));
    conjugation.resolveJsonReferences(lookup);
    EXPECT_FALSE(conjugation.hasUnresolvedJsonReferences());
    EXPECT_EQ(conjugation.originalPortDefinition(), portDefinition);
    EXPECT_EQ(conjugation.conjugatedPortDefinition(), conjugated);
    const auto resolved = serialized(conjugation);
    EXPECT_EQ(resolved.at("originalPortDefinition"), ref(*portDefinition));
    EXPECT_EQ(resolved.at("conjugatedPortDefinition"), ref(*conjugated));

    // ConjugatedPortTyping
    const nlohmann::json typingJson = {{"@id", newId()}, {"@type", "ConjugatedPortTyping"}, {"conjugatedPortDefinition", ref(*conjugated)},
                                       {"portDefinition", ref(*portDefinition)}};
    ConjugatedPortTyping typing(typingJson.dump());
    typing.discardSourceJson();
    EXPECT_EQ(typing.conjugatedPortDefinition(), nullptr);
    EXPECT_EQ(serialized(typing).at("conjugatedPortDefinition"), typingJson.at("conjugatedPortDefinition"));
    typing.resolveJsonReferences(lookup);
    EXPECT_EQ(typing.conjugatedPortDefinition(), conjugated);
    EXPECT_EQ(typing.portDefinition(), portDefinition);
    EXPECT_FALSE(typing.hasUnresolvedJsonReferences());

    // an element of the wrong type and an unknown id stay unresolved and are still written
    const std::string unknown = newId();
    const nlohmann::json wrong = {{"@id", newId()}, {"@type", "PortConjugation"}, {"originalPortDefinition", ref(*notAPort)},
                                  {"conjugatedPortDefinition", {{"@id", unknown}}}};
    PortConjugation wrongConjugation(wrong.dump());
    wrongConjugation.discardSourceJson();
    wrongConjugation.resolveJsonReferences(lookup);
    EXPECT_TRUE(wrongConjugation.hasUnresolvedJsonReferences());
    EXPECT_EQ(wrongConjugation.originalPortDefinition(), nullptr);
    EXPECT_EQ(wrongConjugation.conjugatedPortDefinition(), nullptr);
    const auto wrongJson = serialized(wrongConjugation);
    EXPECT_EQ(wrongJson.at("originalPortDefinition"), wrong.at("originalPortDefinition"));
    EXPECT_EQ(wrongJson.at("conjugatedPortDefinition"), wrong.at("conjugatedPortDefinition"));

    // the unresolved ids survive a round trip through a new object
    PortConjugation again(wrongConjugation.serializeToJson());
    again.discardSourceJson();
    EXPECT_EQ(serialized(again).at("conjugatedPortDefinition"), wrong.at("conjugatedPortDefinition"));
}

TEST(TestSysMLJson, SnapshotReferenceIsReadResolvedAndOverridden) {
    auto first = std::make_shared<PartDefinition>(std::string("A"));
    auto second = std::make_shared<PartDefinition>(std::string("B"));
    auto notADefinition = std::make_shared<PartUsage>(std::string("U"));
    std::map<boost::uuids::uuid, std::shared_ptr<Element>> elements;
    for (const std::shared_ptr<Element>& element : std::vector<std::shared_ptr<Element>>{first, second, notADefinition})
        elements[element->getId()] = element;
    const auto lookup = lookupIn(elements);

    const nlohmann::json input = {{"@id", newId()}, {"@type", "PartUsage"}, {"partDefinition", refs({first.get(), second.get()})}};
    PartUsage usage(input.dump());
    usage.discardSourceJson();
    EXPECT_TRUE(usage.partDefinition().empty());
    ASSERT_TRUE(usage.hasUnresolvedJsonReferences());
    EXPECT_EQ(serialized(usage).at("partDefinition"), input.at("partDefinition"));
    usage.resolveJsonReferences(lookup);
    EXPECT_FALSE(usage.hasUnresolvedJsonReferences());
    ASSERT_EQ(usage.partDefinition().size(), 2u);
    EXPECT_EQ(usage.partDefinition()[0], first);
    EXPECT_EQ(usage.partDefinition()[1], second);
    EXPECT_EQ(serialized(usage).at("partDefinition"), input.at("partDefinition"));

    // a many-valued reference is resolved only if all elements are found with the right type
    PartUsage partly(nlohmann::json({{"@id", newId()}, {"partDefinition", refs({first.get(), notADefinition.get()})}}).dump());
    partly.discardSourceJson();
    partly.resolveJsonReferences(lookup);
    EXPECT_TRUE(partly.hasUnresolvedJsonReferences());
    EXPECT_TRUE(partly.partDefinition().empty());
    EXPECT_EQ(serialized(partly).at("partDefinition"), refs({first.get(), notADefinition.get()}));

    // a setter overrides the id that was read from JSON
    PartUsage overridden(input.dump());
    overridden.discardSourceJson();
    overridden.setPartDefinition({second});
    EXPECT_FALSE(overridden.hasUnresolvedJsonReferences());
    EXPECT_EQ(serialized(overridden).at("partDefinition"), refs({second.get()}));
    overridden.resolveJsonReferences(lookup);
    ASSERT_EQ(overridden.partDefinition().size(), 1u);
    EXPECT_EQ(overridden.partDefinition().front(), second);

    // append goes through the setter too
    PartUsage appended(input.dump());
    appended.discardSourceJson();
    appended.appendPartDefinition(second);
    EXPECT_FALSE(appended.hasUnresolvedJsonReferences());
    EXPECT_EQ(serialized(appended).at("partDefinition"), refs({second.get()}));

    // a single-valued stored reference
    PortConjugation conjugation(nlohmann::json({{"@id", newId()}, {"originalPortDefinition", {{"@id", newId()}}}}).dump());
    conjugation.discardSourceJson();
    auto port = std::make_shared<PortDefinition>(std::string("P"));
    conjugation.setOriginalPortDefinition(port);
    EXPECT_FALSE(conjugation.hasUnresolvedJsonReferences());
    EXPECT_EQ(serialized(conjugation).at("originalPortDefinition"), ref(*port));

    // an emptied many-valued property is empty
    PartUsage emptied(input.dump());
    emptied.discardSourceJson();
    emptied.setPartDefinition({});
    EXPECT_TRUE(serialized(emptied).at("partDefinition").empty());
    EXPECT_FALSE(emptied.hasUnresolvedJsonReferences());
}

TEST(TestSysMLJson, OneRefusedReferenceDoesNotStopTheOthers) {
    auto definition = std::make_shared<PartDefinition>(std::string("D"));
    std::map<boost::uuids::uuid, std::shared_ptr<Element>> elements;
    elements[definition->getId()] = definition;
    // the same element twice in "partDefinition" is refused by the model (no duplicates), "itemDefinition" of the base class is fine
    const nlohmann::json input = {{"@id", newId()}, {"@type", "PartUsage"}, {"partDefinition", refs({definition.get(), definition.get()})},
                                  {"itemDefinition", refs({definition.get()})}};
    PartUsage usage(input.dump());
    usage.discardSourceJson();
    usage.resolveJsonReferences(lookupIn(elements));
    EXPECT_TRUE(usage.partDefinition().empty());
    ASSERT_EQ(usage.itemDefinition().size(), 1u);
    EXPECT_EQ(usage.itemDefinition().front(), definition);
    EXPECT_TRUE(usage.hasUnresolvedJsonReferences());
    EXPECT_EQ(serialized(usage).at("partDefinition"), input.at("partDefinition"));
}

TEST(TestSysMLJson, DerivedViewsAreNotReadFromJson) {
    auto member = std::make_shared<PartUsage>(std::string("m"));
    PartDefinition definition(nlohmann::json({{"@id", newId()}, {"ownedPart", refs({member.get()})}, {"ownedUsage", refs({member.get()})},
                                              {"usage", refs({member.get()})}}).dump());
    EXPECT_FALSE(definition.hasUnresolvedJsonReferences());
    EXPECT_TRUE(definition.ownedPart().empty());
    EXPECT_TRUE(definition.ownedUsage().empty());
    // (the JSON the element was created from is returned for what it can not reproduce itself: look at the object alone)
    definition.discardSourceJson();
    EXPECT_TRUE(serialized(definition).at("ownedPart").empty());
    EXPECT_TRUE(serialized(definition).at("usage").empty());

    // a derived scalar is computed
    ReferenceUsage reference(nlohmann::json({{"@id", newId()}, {"isReference", false}}).dump());
    EXPECT_TRUE(reference.isReference());
}

TEST(TestSysMLJson, ParsingToleratesMissingAndWrongProperties) {
    const std::string id = newId();
    ASSERT_NO_THROW(PartUsage(nlohmann::json({{"@id", id}}).dump()));
    ASSERT_NO_THROW(PartUsage(std::string("{}")));
    PartUsage wrong(nlohmann::json({{"@id", id}, {"declaredName", 5}, {"isVariation", "yes"}, {"isIndividual", 1}, {"portionKind", "bogus"},
                                    {"partDefinition", "text"}, {"itemDefinition", 3}, {"direction", true},
                                    {"ownedRelationship", nlohmann::json::array({"x", 4, {{"@id", "not-a-uuid"}}})}}).dump());
    EXPECT_EQ(idOf(wrong), id);
    EXPECT_FALSE(wrong.declaredName().has_value());
    EXPECT_FALSE(wrong.isVariation());
    EXPECT_FALSE(wrong.isIndividual());
    EXPECT_FALSE(wrong.portionKind().has_value());
    EXPECT_TRUE(wrong.partDefinition().empty());
    EXPECT_FALSE(wrong.hasUnresolvedJsonReferences());
    EXPECT_NO_THROW(wrong.serializeToJson());

    RequirementUsage wrongReqId(nlohmann::json({{"@id", id}, {"reqId", 5}}).dump());
    EXPECT_FALSE(wrongReqId.reqId().has_value());
    ConnectionDefinition wrongSufficient(nlohmann::json({{"@id", id}, {"isSufficient", "no"}}).dump());
    EXPECT_TRUE(wrongSufficient.isSufficient());
}

TEST(TestSysMLJson, FactoryAndConstructorRejectBrokenJson) {
    EXPECT_THROW(createElementFromJson("{broken"), nlohmann::json::exception);
    EXPECT_THROW(createElementFromJson(""), nlohmann::json::exception);
    EXPECT_THROW(createElementFromJson("[1, 2]"), std::invalid_argument);
    EXPECT_THROW(createElementFromJson("\"text\""), std::invalid_argument);
    EXPECT_THROW(createElementFromJson(R"({"@type": "PartUsage"})"), std::invalid_argument);
    EXPECT_THROW(createElementFromJson(R"({"@type": "PartUsage", "@id": "not-a-uuid"})"), std::invalid_argument);
    EXPECT_THROW(createElementFromJson(R"({"@type": "PartUsage", "@id": 7})"), std::invalid_argument);
    EXPECT_THROW(createElementFromJson(R"({"@type": "Package"})"), std::invalid_argument);
    EXPECT_THROW(createElementsFromJson({nlohmann::json({{"@id", newId()}, {"@type", "PartUsage"}}).dump(), "{broken"}), nlohmann::json::exception);
    EXPECT_THROW(PartUsage(std::string("{\"@id\": ")), nlohmann::json::exception);
}

TEST(TestSysMLJson, ServerPayloadKeepsWhatTheModelDoesNotKnow) {
    const std::string id = newId();
    const nlohmann::json payload = {{"@id", id}, {"@type", "PartUsage"}, {"declaredName", "FromServer"}, {"serverOnlyProperty", {{"nested", true}}},
                                    {"partDefinition", nlohmann::json::array({{{"@id", newId()}}})}};
    const auto created = createElementFromJson(payload.dump());
    const auto written = nlohmann::json::parse(created->serializeToJson());
    for (auto it = payload.begin(); it != payload.end(); ++it) {
        ASSERT_TRUE(written.contains(it.key())) << it.key();
        EXPECT_EQ(written.at(it.key()), it.value()) << it.key();
    }
    created->setDeclaredName("Renamed");
    EXPECT_EQ(nlohmann::json::parse(created->serializeToJson()).at("declaredName"), "Renamed");
    created->discardSourceJson();
    EXPECT_FALSE(nlohmann::json::parse(created->serializeToJson()).contains("serverOnlyProperty"));
}

namespace {
    struct Model {
        std::string packageId = newId(), packageMembershipId = newId(), definitionId = newId(), featureMembershipId = newId(), usageId = newId(),
                    typingId = newId();

        std::vector<std::string> jsons() const {
            return {
                nlohmann::json({{"@id", packageId}, {"@type", "Package"}, {"declaredName", "P"},
                                {"ownedRelationship", nlohmann::json::array({{{"@id", packageMembershipId}}})}}).dump(),
                nlohmann::json({{"@id", packageMembershipId}, {"@type", "OwningMembership"}, {"owningRelatedElement", {{"@id", packageId}}},
                                {"ownedRelatedElement", nlohmann::json::array({{{"@id", definitionId}}})}, {"memberElement", {{"@id", definitionId}}}}).dump(),
                nlohmann::json({{"@id", definitionId}, {"@type", "PartDefinition"}, {"declaredName", "Engine"},
                                {"owningRelationship", {{"@id", packageMembershipId}}},
                                {"ownedRelationship", nlohmann::json::array({{{"@id", featureMembershipId}}})}}).dump(),
                nlohmann::json({{"@id", featureMembershipId}, {"@type", "FeatureMembership"}, {"owningRelatedElement", {{"@id", definitionId}}},
                                {"ownedRelatedElement", nlohmann::json::array({{{"@id", usageId}}})}, {"memberElement", {{"@id", usageId}}}}).dump(),
                nlohmann::json({{"@id", usageId}, {"@type", "PartUsage"}, {"declaredName", "engine"}, {"owningRelationship", {{"@id", featureMembershipId}}},
                                {"ownedRelationship", nlohmann::json::array({{{"@id", typingId}}})}}).dump(),
                nlohmann::json({{"@id", typingId}, {"@type", "FeatureTyping"}, {"owningRelatedElement", {{"@id", usageId}}},
                                {"typedFeature", {{"@id", usageId}}}, {"type", {{"@id", definitionId}}}, {"specific", {{"@id", usageId}}},
                                {"general", {{"@id", definitionId}}}}).dump()};
        }
    };
}

TEST(TestSysMLJson, ElementsOfOneBatchAreLinked) {
    const Model model;
    const auto elements = createElementsFromJson(model.jsons());
    ASSERT_EQ(elements.size(), 6u);
    const auto package = std::dynamic_pointer_cast<K::Package>(elements[0]);
    const auto definition = std::dynamic_pointer_cast<PartDefinition>(elements[2]);
    const auto featureMembership = std::dynamic_pointer_cast<K::FeatureMembership>(elements[3]);
    const auto usage = std::dynamic_pointer_cast<PartUsage>(elements[4]);
    const auto typing = std::dynamic_pointer_cast<K::FeatureTyping>(elements[5]);
    ASSERT_TRUE(package && definition && featureMembership && usage && typing);
    EXPECT_EQ(definition->getType(), "PartDefinition");
    EXPECT_EQ(usage->getType(), "PartUsage");

    for (const auto& element : elements)
        EXPECT_FALSE(element->hasUnresolvedJsonReferences()) << element->getType();

    // ownership
    EXPECT_EQ(definition->owner(), package);
    ASSERT_EQ(package->ownedMember().size(), 1u);
    EXPECT_EQ(package->ownedMember().front(), definition);
    EXPECT_EQ(usage->owner(), definition);
    EXPECT_EQ(featureMembership->owningRelatedElement(), definition);
    EXPECT_FALSE(package->ownedElements().empty());
    const auto ownedByDefinition = definition->ownedElements();
    EXPECT_NE(std::find(ownedByDefinition.begin(), ownedByDefinition.end(), std::static_pointer_cast<Element>(featureMembership)), ownedByDefinition.end());

    // features and the SysML views on them
    const auto features = definition->ownedFeature();
    ASSERT_EQ(features.size(), 1u);
    EXPECT_EQ(features.front(), usage);
    ASSERT_EQ(definition->ownedPart().size(), 1u);
    EXPECT_EQ(definition->ownedPart().front(), usage);
    ASSERT_EQ(definition->ownedUsage().size(), 1u);
    EXPECT_EQ(definition->ownedUsage().front(), usage);
    EXPECT_EQ(usage->owningDefinition(), definition);
    EXPECT_EQ(usage->owningUsage(), nullptr);

    // typing
    EXPECT_EQ(typing->typedFeature(), usage);
    EXPECT_EQ(typing->type(), definition);
    ASSERT_FALSE(usage->type().empty());
    EXPECT_EQ(usage->type().front(), definition);
    ASSERT_EQ(usage->definition().size(), 1u);
    EXPECT_EQ(usage->definition().front(), definition);

    // linking a second time does not duplicate anything
    K::linkElements(elements);
    EXPECT_EQ(package->ownedMember().size(), 1u);
    EXPECT_EQ(definition->ownedPart().size(), 1u);
    EXPECT_EQ(definition->ownedFeature().size(), 1u);

    // the linked model is written with the identities of its neighbours
    const auto written = serialized(*usage);
    EXPECT_EQ(written.at("@type"), "PartUsage");
    EXPECT_EQ(written.at("owner"), ref(*definition));
    EXPECT_EQ(written.at("owningDefinition"), ref(*definition));
}

TEST(TestSysMLJson, ArraysOfElementsAreLinkedByTheDeserializer) {
    const Model model;
    nlohmann::json array = nlohmann::json::array();
    for (const auto& json : model.jsons())
        array.push_back(nlohmann::json::parse(json));
    const auto entities = SysMLv2::SysMLv2Deserializer::deserializeJsonArray(array.dump());
    ASSERT_EQ(entities.size(), 6u);
    const auto definition = std::dynamic_pointer_cast<PartDefinition>(entities[2]);
    const auto usage = std::dynamic_pointer_cast<PartUsage>(entities[4]);
    ASSERT_TRUE(definition && usage);
    EXPECT_EQ(usage->owner(), definition);
    ASSERT_EQ(definition->ownedPart().size(), 1u);
    EXPECT_EQ(definition->ownedPart().front(), usage);
    EXPECT_FALSE(usage->hasUnresolvedJsonReferences());

    const auto single = std::dynamic_pointer_cast<PartUsage>(SysMLv2::SysMLv2Deserializer::deserializeJsonString(array[4].dump()));
    ASSERT_NE(single, nullptr);
    EXPECT_EQ(single->getType(), "PartUsage");
    EXPECT_TRUE(single->hasUnresolvedJsonReferences());
    EXPECT_EQ(nlohmann::json::parse(single->serializeToJson()).at("owningRelationship"), array[4].at("owningRelationship"));

    const auto unknown = SysMLv2::SysMLv2Deserializer::deserializeJsonString(nlohmann::json({{"@id", newId()}, {"@type", "NoSuchType"}}).dump());
    ASSERT_NE(unknown, nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<Element>(unknown), nullptr);
}
