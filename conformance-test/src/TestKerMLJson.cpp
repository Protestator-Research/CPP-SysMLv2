//
// Tests of the JSON serialization and parsing of the KerML metaclasses: the round trip of every concrete metaclass, the
// constructors that take a name or a JSON string, the references that are only known by their ids, and the element factory.
//

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <map>
#include <set>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

#include <kerml/KerML.h>
#include <sysmlv2/Parser.h>
#include <sysmlv2/rest/serialization/SysMLv2Deserializer.h>

namespace {
    using namespace KerML::Entities;

    // Every concrete metaclass of KerML (the ones the factory creates).
#define KERML_CONCRETE_CLASSES(X) \
    X(AnnotatingElement) X(Annotation) X(Association) X(AssociationStructure) X(Behavior) X(BindingConnector) \
    X(BooleanExpression) X(Class) X(Classifier) X(CollectExpression) X(Comment) X(Conjugation) X(Connector) \
    X(ConstructorExpression) X(CrossSubsetting) X(DataType) X(Dependency) X(Differencing) X(Disjoining) \
    X(Documentation) X(ElementFilterMembership) X(EndFeatureMembership) X(Expression) X(Feature) \
    X(FeatureChainExpression) X(FeatureChaining) X(FeatureInverting) X(FeatureMembership) \
    X(FeatureReferenceExpression) X(FeatureTyping) X(FeatureValue) X(Flow) X(FlowEnd) X(Function) \
    X(IndexExpression) X(Interaction) X(Intersecting) X(Invariant) X(InvocationExpression) X(LibraryPackage) \
    X(LiteralBoolean) X(LiteralExpression) X(LiteralInfinity) X(LiteralInteger) X(LiteralRational) \
    X(LiteralString) X(Membership) X(MembershipImport) X(Metaclass) X(MetadataAccessExpression) \
    X(MetadataFeature) X(Multiplicity) X(MultiplicityRange) X(Namespace) X(NamespaceImport) X(NullExpression) \
    X(OperatorExpression) X(OwningMembership) X(Package) X(ParameterMembership) X(PayloadFeature) X(Predicate) \
    X(Redefinition) X(ReferenceSubsetting) X(ResultExpressionMembership) X(ReturnParameterMembership) \
    X(SelectExpression) X(Specialization) X(Step) X(Structure) X(Subclassification) X(Subsetting) X(Succession) \
    X(SuccessionFlow) X(TextualRepresentation) X(Type) X(TypeFeaturing) X(Unioning)

    /**
     * The element id of an element. (Membership hides Element::elementId with a protected function.)
     */
    std::string elementIdOf(const Element& element) {
        return element.elementId();
    }

    std::string newId() {
        return boost::uuids::to_string(boost::uuids::random_generator()());
    }

    /**
     * Creates an element by the string constructor with a name, without JSON (every metaclass but Element and Relationship takes a name).
     */
    template<class T>
    std::shared_ptr<T> create(const std::string& name) {
        return std::make_shared<T>(name);
    }

    /**
     * Sets some properties of the metaclass that are no references, so that the round trip has something to keep.
     */
    template<class T>
    void populate(T& element) {
        element.setDeclaredName("Name");
        element.setDeclaredShortName("short");
        element.setAliasIds({"alias1", "alias2"});
        element.setIsLibraryElement(true);
        bool implied = true;
        element.setImpliedIncluded(implied);
        if constexpr (std::is_base_of_v<Relationship, T>)
            element.setIsImplied(true);
        if constexpr (std::is_base_of_v<Type, T>) {
            element.setAbstract(true);
            element.setIsSufficient(true);
        }
        if constexpr (std::is_base_of_v<Feature, T>) {
            element.setDirection(OUT);
            element.setIsUnique(false);
            element.setIsOrdered(true);
            element.setIsComposite(true);
            element.setIsEnd(true);
            element.setIsDerived(true);
            element.setIsPortion(true);
            element.setIsVariable(true);
            element.setIsConstant(true);
        }
        if constexpr (std::is_base_of_v<Membership, T>) {
            element.setVisibility(PROTECTED);
            element.setMemberName("member");
            element.setMemberShortName("m");
        }
        if constexpr (std::is_base_of_v<Import, T>) {
            element.setVisibility(PUBLIC);
            element.setIsRecursive(true);
            element.setIsImportAll(true);
        }
        if constexpr (std::is_base_of_v<Comment, T>) {
            element.setLocale("de");
            element.setBody("A body");
        }
        if constexpr (std::is_base_of_v<TextualRepresentation, T>) {
            element.setLanguage("OCL");
            element.setBody("self.x > 0");
        }
        if constexpr (std::is_same_v<OperatorExpression, T>)
            element.setOperatorName("+");
        if constexpr (std::is_base_of_v<LiteralBoolean, T>)
            element.setValue(true);
        if constexpr (std::is_base_of_v<LiteralInteger, T>)
            element.setValue(42);
        if constexpr (std::is_base_of_v<LiteralRational, T>)
            element.setValue(2.5);
        if constexpr (std::is_base_of_v<LiteralString, T>)
            element.setValue("text");
        if constexpr (std::is_base_of_v<Invariant, T>)
            element.setIsNegated(true);
        if constexpr (std::is_base_of_v<FeatureValue, T>) {
            element.setIsInitial(true);
            element.setIsDefault(true);
        }
        if constexpr (std::is_base_of_v<LibraryPackage, T>)
            element.setIsStandard(true);
    }

    template<class T>
    void expectRoundTrip(const std::string& type) {
        SCOPED_TRACE(type);
        std::shared_ptr<T> original;
        ASSERT_NO_THROW(original = create<T>("Created"));
        populate(*original);

        std::string serialized;
        ASSERT_NO_THROW(serialized = original->serializeToJson());
        const nlohmann::json json = nlohmann::json::parse(serialized);
        EXPECT_EQ(json.at("@type"), type);
        EXPECT_EQ(json.at("@id"), boost::uuids::to_string(original->getId()));
        EXPECT_EQ(json.at("elementId"), elementIdOf(*original));
        EXPECT_EQ(json.at("declaredName"), "Name");
        EXPECT_EQ(json.at("declaredShortName"), "short");
        EXPECT_EQ(json.at("aliasIds"), nlohmann::json::array({"alias1", "alias2"}));
        EXPECT_EQ(json.at("isLibraryElement"), true);

        std::shared_ptr<T> copy;
        ASSERT_NO_THROW(copy = std::make_shared<T>(serialized));
        EXPECT_EQ(copy->getType(), type);
        EXPECT_EQ(copy->getId(), original->getId());
        EXPECT_EQ(elementIdOf(*copy), elementIdOf(*original));
        ASSERT_TRUE(copy->declaredName().has_value());
        EXPECT_EQ(*copy->declaredName(), "Name");
        // (the JSON the copy was created from would be returned for what the copy does not change: look at the copy alone)
        copy->discardSourceJson();
        EXPECT_EQ(nlohmann::json::parse(copy->serializeToJson()), json);
        EXPECT_FALSE(copy->hasUnresolvedJsonReferences());
    }

    template<class T>
    void expectSerializable(const std::string& type) {
        SCOPED_TRACE(type);
        auto element = create<T>("x");
        nlohmann::json json;
        ASSERT_NO_THROW(json = nlohmann::json::parse(element->serializeToJson()));
        EXPECT_EQ(json.at("@type"), type);
    }

    template<class T>
    void expectFactoryCreates(const std::string& type) {
        SCOPED_TRACE(type);
        const nlohmann::json json = {{"@id", newId()}, {"@type", type}, {"declaredName", "Created"}};
        const auto created = createElementFromJson(json.dump());
        ASSERT_NE(created, nullptr);
        EXPECT_EQ(created->getType(), type);
        EXPECT_NE(std::dynamic_pointer_cast<T>(created), nullptr);
    }

    /**
     * Resolves ids by a map.
     */
    std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)> lookupIn(std::map<boost::uuids::uuid, std::shared_ptr<Element>>& elements) {
        return [&elements](const boost::uuids::uuid& id) -> std::shared_ptr<Element> {
            const auto it = elements.find(id);
            return it == elements.end() ? nullptr : it->second;
        };
    }
}

TEST(TestKerMLJson, RoundTripOfEveryConcreteMetaclass) {
#define KERML_ROUND_TRIP(Name) expectRoundTrip<Name>(#Name);
    KERML_CONCRETE_CLASSES(KERML_ROUND_TRIP)
#undef KERML_ROUND_TRIP
}

TEST(TestKerMLJson, DefaultConstructedElementsSerializeToValidJson) {
#define KERML_DEFAULT(Name) expectSerializable<Name>(#Name);
    KERML_CONCRETE_CLASSES(KERML_DEFAULT)
#undef KERML_DEFAULT
}

TEST(TestKerMLJson, SpecificPropertiesOfTheMetaclasses) {
    auto feature = std::make_shared<Feature>("f");
    feature->setDirection(IN_OUT);
    feature->setIsEnd(true);
    auto featureJson = nlohmann::json::parse(feature->serializeToJson());
    EXPECT_EQ(featureJson.at("direction"), "inout");
    EXPECT_EQ(featureJson.at("isEnd"), true);
    EXPECT_EQ(featureJson.at("isUnique"), true);
    EXPECT_EQ(featureJson.at("owningType"), nullptr);
    EXPECT_TRUE(featureJson.at("ownedSubsetting").is_array());
    Feature copy(feature->serializeToJson());
    ASSERT_TRUE(copy.direction().has_value());
    EXPECT_EQ(*copy.direction(), IN_OUT);
    EXPECT_TRUE(copy.isEnd());

    auto literal = std::make_shared<LiteralInteger>("l");
    literal->setValue(-7);
    EXPECT_EQ(nlohmann::json::parse(literal->serializeToJson()).at("value"), -7);
    EXPECT_EQ(LiteralInteger(literal->serializeToJson()).value(), -7);

    auto membership = std::make_shared<Membership>(newId());
    membership->setVisibility(PRIVATE);
    EXPECT_EQ(nlohmann::json::parse(membership->serializeToJson()).at("visibility"), "private");
    EXPECT_EQ(Membership(membership->serializeToJson()).visibility(), PRIVATE);

    auto op = std::make_shared<OperatorExpression>("op");
    op->setOperatorName("==");
    EXPECT_EQ(nlohmann::json::parse(op->serializeToJson()).at("operator"), "==");
    EXPECT_EQ(OperatorExpression(op->serializeToJson()).operatorName(), "==");
}

TEST(TestKerMLJson, NameOrJsonConstructor) {
    Package named("MyPackage");
    ASSERT_TRUE(named.declaredName().has_value());
    EXPECT_EQ(*named.declaredName(), "MyPackage");
    EXPECT_EQ(named.getType(), "Package");

    const std::string id = newId();
    Package parsed(R"({"@id":")" + id + R"(","@type":"Package","declaredName":"FromJson","declaredShortName":"fj"})");
    ASSERT_TRUE(parsed.declaredName().has_value());
    EXPECT_EQ(*parsed.declaredName(), "FromJson");
    EXPECT_EQ(*parsed.declaredShortName(), "fj");
    EXPECT_EQ(boost::uuids::to_string(parsed.getId()), id);
    EXPECT_EQ(parsed.elementId(), id);
    EXPECT_EQ(parsed.getType(), "Package");

    // leading whitespace does not matter
    Package padded("  \n\t{\"@id\":\"" + id + "\",\"declaredName\":\"Padded\"}");
    EXPECT_EQ(*padded.declaredName(), "Padded");

    // a name that is no JSON stays a name, even if it contains braces
    Package braces("a{b}");
    EXPECT_EQ(*braces.declaredName(), "a{b}");

    // the classes with a base constructor that takes a name
    Type type("T");
    EXPECT_EQ(*type.declaredName(), "T");
    Classifier classifier("C");
    EXPECT_EQ(*classifier.declaredName(), "C");
    Namespace ns("N");
    EXPECT_EQ(*ns.declaredName(), "N");
    Namespace nsJson(R"({"@id":")" + id + R"(","declaredName":"NJ"})");
    EXPECT_EQ(*nsJson.declaredName(), "NJ");
    EXPECT_EQ(nsJson.elementId(), id);
    Type typeJson(R"({"@id":")" + id + R"(","declaredName":"TJ"})");
    EXPECT_EQ(*typeJson.declaredName(), "TJ");
    EXPECT_EQ(typeJson.elementId(), id);
    Classifier classifierJson(R"({"@id":")" + id + R"(","declaredName":"CJ","isAbstract":true})");
    EXPECT_EQ(*classifierJson.declaredName(), "CJ");
    EXPECT_TRUE(classifierJson.isAbstract());

    // a name constructor for the metaclasses with virtual bases is called by the most derived class only
    Interaction interaction("I");
    EXPECT_EQ(*interaction.declaredName(), "I");
    Interaction interactionJson(R"({"@id":")" + id + R"(","declaredName":"IJ","isAbstract":true,"isImplied":true})");
    EXPECT_EQ(*interactionJson.declaredName(), "IJ");
    EXPECT_TRUE(interactionJson.isAbstract());
    EXPECT_TRUE(interactionJson.isImplied());
    EXPECT_EQ(interactionJson.elementId(), id);
}

TEST(TestKerMLJson, ElementAndRelationshipTakeAnElementIdOrJson) {
    const std::string id = newId();
    Element byId(id);
    EXPECT_EQ(byId.elementId(), id);
    EXPECT_EQ(boost::uuids::to_string(byId.getId()), id);

    Element byJson(R"({"@id":")" + id + R"(","declaredName":"E","isImpliedIncluded":true})");
    EXPECT_EQ(byJson.elementId(), id);
    EXPECT_EQ(boost::uuids::to_string(byJson.getId()), id);
    EXPECT_EQ(*byJson.declaredName(), "E");
    EXPECT_TRUE(byJson.isImpliedIncluded());

    // only the elementId is given
    Element byElementId(R"({"elementId":")" + id + R"("})");
    EXPECT_EQ(byElementId.elementId(), id);
    EXPECT_EQ(boost::uuids::to_string(byElementId.getId()), id);

    Relationship relationshipById(id);
    EXPECT_EQ(relationshipById.elementId(), id);
    Relationship relationshipByJson(R"({"@id":")" + id + R"(","isImplied":true})");
    EXPECT_EQ(relationshipByJson.elementId(), id);
    EXPECT_TRUE(relationshipByJson.isImplied());

    // the other relationships take a name, like every metaclass but Element and Relationship
    Specialization specialization("a name");
    ASSERT_TRUE(specialization.declaredName().has_value());
    EXPECT_EQ(*specialization.declaredName(), "a name");
    EXPECT_NO_THROW(Specialization("abc"));
    EXPECT_EQ(*Annotation("note").declaredName(), "note");
    EXPECT_EQ(*Dependency("dep").declaredName(), "dep");
    EXPECT_EQ(*NamespaceImport("imp").declaredName(), "imp");
    EXPECT_EQ(*FeatureMembership("fm").declaredName(), "fm");

    EXPECT_ANY_THROW(Element(std::string("no uuid")));
    EXPECT_ANY_THROW(Package("{not json"));
    EXPECT_ANY_THROW(Element(std::string("{\"@id\":")));
}

TEST(TestKerMLJson, ParsingToleratesMissingAndWrongProperties) {
    Feature feature(R"({"@id":"c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4","@type":"Feature","owner":"","name":null,"aliasIds":"x","declaredName":5,"isEnd":"yes","direction":"sideways","ownedSubsetting":"broken","type":[1,{"@id":"nope"}]})");
    EXPECT_EQ(feature.elementId(), "c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4");
    EXPECT_FALSE(feature.declaredName().has_value());
    EXPECT_EQ(feature.isEnd(), Feature("x").isEnd());
    EXPECT_FALSE(feature.direction().has_value());
    EXPECT_FALSE(feature.hasUnresolvedJsonReferences());

    Feature empty(R"({})");
    EXPECT_NO_THROW(empty.serializeToJson());
    // only a JSON object is JSON, everything else is a name
    EXPECT_EQ(*Feature("[1,2]").declaredName(), "[1,2]");
    EXPECT_THROW(Feature("{\"@id\":"), std::exception);
}

TEST(TestKerMLJson, UnresolvedReferencesSurviveARoundTrip) {
    const std::string id = newId();
    const std::string general = newId();
    const std::string specific = newId();
    const nlohmann::json input = {
        {"@id", id},
        {"@type", "Specialization"},
        {"general", {{"@id", general}}},
        {"specific", {{"@id", specific}}},
        {"owningRelatedElement", {{"@id", specific}}},
        {"ownedRelatedElement", nlohmann::json::array()},
        {"source", nlohmann::json::array({{{"@id", specific}}})},
        {"target", nlohmann::json::array({{{"@id", general}}})}
    };
    Specialization parsed(input.dump());
    EXPECT_TRUE(parsed.hasUnresolvedJsonReferences());
    EXPECT_EQ(parsed.general(), nullptr);

    parsed.discardSourceJson();
    const nlohmann::json first = nlohmann::json::parse(parsed.serializeToJson());
    EXPECT_EQ(first.at("general"), nlohmann::json({{"@id", general}}));
    EXPECT_EQ(first.at("specific"), nlohmann::json({{"@id", specific}}));
    EXPECT_EQ(first.at("owningRelatedElement"), nlohmann::json({{"@id", specific}}));
    EXPECT_EQ(first.at("source"), nlohmann::json::array({{{"@id", specific}}}));
    EXPECT_EQ(first.at("target"), nlohmann::json::array({{{"@id", general}}}));

    Specialization again(first.dump());
    EXPECT_EQ(nlohmann::json::parse(again.serializeToJson()), first);

    // a many-valued reference of an element that is no relationship
    const std::string client = newId();
    const std::string supplierA = newId();
    const std::string supplierB = newId();
    Dependency dependency(nlohmann::json({{"@id", newId()}, {"@type", "Dependency"}, {"client", nlohmann::json::array({{{"@id", client}}})},
                                          {"supplier", nlohmann::json::array({{{"@id", supplierA}}, {{"@id", supplierB}}})}}).dump());
    dependency.discardSourceJson();
    const auto dependencyJson = nlohmann::json::parse(dependency.serializeToJson());
    EXPECT_EQ(dependencyJson.at("client"), nlohmann::json::array({{{"@id", client}}}));
    EXPECT_EQ(dependencyJson.at("supplier"), nlohmann::json::array({{{"@id", supplierA}}, {{"@id", supplierB}}}));
    Dependency dependencyAgain(dependency.serializeToJson());
    dependencyAgain.discardSourceJson();
    EXPECT_EQ(nlohmann::json::parse(dependencyAgain.serializeToJson()), dependencyJson);

    // the references of a plain Element (old versions wrote "ownedRelationships" and "" for an empty reference)
    const std::string relationship = newId();
    Element element(nlohmann::json({{"@id", newId()}, {"ownedRelationships", nlohmann::json::array({{{"@id", relationship}}})}, {"owningRelationship", ""}}).dump());
    element.discardSourceJson();
    EXPECT_EQ(nlohmann::json::parse(element.serializeToJson()).at("ownedRelationship"), nlohmann::json::array({{{"@id", relationship}}}));
    EXPECT_TRUE(nlohmann::json::parse(element.serializeToJson()).at("owningRelationship").is_null());
}

TEST(TestKerMLJson, ResolveJsonReferencesLinksTheElements) {
    auto a = std::make_shared<Type>("A");
    auto b = std::make_shared<Type>("B");
    auto notAType = std::make_shared<Package>("P");
    std::map<boost::uuids::uuid, std::shared_ptr<Element>> elements;
    for (const auto& element : std::vector<std::shared_ptr<Element>>{a, b, notAType})
        elements[element->getId()] = element;
    const auto lookup = lookupIn(elements);

    const nlohmann::json input = {
        {"@id", newId()},
        {"@type", "Specialization"},
        {"general", {{"@id", boost::uuids::to_string(a->getId())}}},
        {"specific", {{"@id", boost::uuids::to_string(b->getId())}}}
    };
    Specialization specialization(input.dump());
    specialization.discardSourceJson();
    ASSERT_TRUE(specialization.hasUnresolvedJsonReferences());
    specialization.resolveJsonReferences(lookup);
    EXPECT_FALSE(specialization.hasUnresolvedJsonReferences());
    EXPECT_EQ(specialization.general(), a);
    EXPECT_EQ(specialization.specific(), b);

    const auto resolved = nlohmann::json::parse(specialization.serializeToJson());
    EXPECT_EQ(resolved.at("general"), nlohmann::json({{"@id", boost::uuids::to_string(a->getId())}}));
    EXPECT_EQ(resolved.at("specific"), nlohmann::json({{"@id", boost::uuids::to_string(b->getId())}}));

    // an unknown id and an element of the wrong type stay unresolved, and are still written
    const std::string unknown = newId();
    const nlohmann::json partial = {
        {"@id", newId()},
        {"@type", "Specialization"},
        {"general", {{"@id", boost::uuids::to_string(notAType->getId())}}},
        {"specific", {{"@id", unknown}}}
    };
    Specialization partlyResolved(partial.dump());
    partlyResolved.discardSourceJson();
    partlyResolved.resolveJsonReferences(lookup);
    EXPECT_TRUE(partlyResolved.hasUnresolvedJsonReferences());
    EXPECT_EQ(partlyResolved.general(), nullptr);
    EXPECT_EQ(partlyResolved.specific(), nullptr);
    const auto partialJson = nlohmann::json::parse(partlyResolved.serializeToJson());
    EXPECT_EQ(partialJson.at("general"), partial.at("general"));
    EXPECT_EQ(partialJson.at("specific"), partial.at("specific"));

    // a many-valued reference is resolved if all its elements are found
    const nlohmann::json many = {
        {"@id", newId()},
        {"@type", "Dependency"},
        {"client", nlohmann::json::array({{{"@id", boost::uuids::to_string(a->getId())}}})},
        {"supplier", nlohmann::json::array({{{"@id", boost::uuids::to_string(b->getId())}}, {{"@id", unknown}}})}
    };
    Dependency dependency(many.dump());
    dependency.discardSourceJson();
    dependency.resolveJsonReferences(lookup);
    EXPECT_TRUE(dependency.hasUnresolvedJsonReferences());
    ASSERT_EQ(dependency.client().size(), 1u);
    EXPECT_EQ(dependency.client().front(), a);
    EXPECT_TRUE(dependency.supplier().empty());
    EXPECT_EQ(nlohmann::json::parse(dependency.serializeToJson()).at("supplier"), many.at("supplier"));

    elements[boost::uuids::string_generator()(unknown)] = a;
    dependency.resolveJsonReferences(lookup);
    EXPECT_FALSE(dependency.hasUnresolvedJsonReferences());
    EXPECT_EQ(dependency.supplier().size(), 2u);

    // the references of the base classes are resolved by the derived classes
    const nlohmann::json owned = {
        {"@id", newId()},
        {"@type", "Redefinition"},
        {"redefinedFeature", {{"@id", unknown}}},
        {"subsettedFeature", {{"@id", unknown}}},
        {"general", {{"@id", boost::uuids::to_string(a->getId())}}}
    };
    auto feature = std::make_shared<Feature>("F");
    elements[boost::uuids::string_generator()(unknown)] = feature;
    Redefinition redefinition(owned.dump());
    EXPECT_TRUE(redefinition.hasUnresolvedJsonReferences());
    redefinition.resolveJsonReferences(lookup);
    EXPECT_EQ(redefinition.redefinedFeature(), feature);
    EXPECT_EQ(redefinition.subsettedFeature(), feature);
    EXPECT_EQ(redefinition.general(), a);
    EXPECT_FALSE(redefinition.hasUnresolvedJsonReferences());
}

TEST(TestKerMLJson, FactoryCreatesTheMetaclassOfTheType) {
    const auto create = [](const std::string& type) {
        const nlohmann::json json = {{"@id", newId()}, {"@type", type}, {"declaredName", "Created"}};
        return createElementFromJson(json.dump());
    };

    auto package = create("Package");
    ASSERT_NE(std::dynamic_pointer_cast<Package>(package), nullptr);
    EXPECT_EQ(package->getType(), "Package");
    EXPECT_EQ(*package->declaredName(), "Created");

    EXPECT_NE(std::dynamic_pointer_cast<Feature>(create("Feature")), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<Package>(create("LibraryPackage")), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<LibraryPackage>(create("LibraryPackage")), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<Redefinition>(create("Redefinition")), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<Subsetting>(create("Redefinition")), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<Flow>(create("SuccessionFlow")), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<TextualRepresentation>(create("TextualRepresentation")), nullptr);
    EXPECT_EQ(std::dynamic_pointer_cast<Feature>(create("Package")), nullptr);

#define KERML_FACTORY(Name) expectFactoryCreates<Name>(#Name);
    KERML_CONCRETE_CLASSES(KERML_FACTORY)
#undef KERML_FACTORY

    // an unknown type, and "Element" itself, stay plain Elements with their JSON
    const std::string unknownJson = nlohmann::json({{"@id", newId()}, {"@type", "PartUsage"}, {"declaredName", "Car"}, {"isVariation", true}}).dump();
    auto unknown = createElementFromJson(unknownJson);
    ASSERT_NE(unknown, nullptr);
    EXPECT_EQ(unknown->getType(), "PartUsage");
    EXPECT_EQ(nlohmann::json::parse(unknown->serializeToJson()), nlohmann::json::parse(unknownJson));
    EXPECT_EQ(create("Element")->getType(), "Element");

    EXPECT_THROW(createElementFromJson(R"({"@type":"Package"})"), std::invalid_argument);
    EXPECT_THROW(createElementFromJson(R"({"@type":"Package","@id":"nope"})"), std::invalid_argument);
    EXPECT_THROW(createElementFromJson(R"({"@type":"PartUsage"})"), std::invalid_argument);
    EXPECT_THROW(createElementFromJson("[]"), std::invalid_argument);
    EXPECT_ANY_THROW(createElementFromJson("{not json"));
}

// ---------------------------------------------------------------------------------------------------------------------------------
// Behaviour of the elements that were created from JSON
// ---------------------------------------------------------------------------------------------------------------------------------

namespace {
    /**
     * The elements of a parsed model: the parsed elements and everything they own.
     */
    std::vector<std::shared_ptr<Element>> allElementsOf(const std::vector<std::shared_ptr<Element>>& roots) {
        std::vector<std::shared_ptr<Element>> result;
        std::set<const Element*> seen;
        std::vector<std::shared_ptr<Element>> queue(roots.begin(), roots.end());
        while (!queue.empty()) {
            const auto element = queue.back();
            queue.pop_back();
            if (!element || !seen.insert(element.get()).second)
                continue;
            result.push_back(element);
            for (const auto& owned : element->ownedElements())
                queue.push_back(owned);
            for (const auto& relationship : element->ownedRelationship())
                queue.push_back(relationship);
            if (const auto relationship = std::dynamic_pointer_cast<Relationship>(element)) {
                for (const auto& owned : relationship->ownedRelatedElement())
                    queue.push_back(owned);
            }
        }
        return result;
    }

    /**
     * The properties whose order the model defines: the stored ones. The derived collections are compared without their order, because
     * the order in which the elements are handed over decides it.
     */
    bool orderMatters(const std::string& property) {
        return property == "ownedRelationship" || property == "ownedRelatedElement" || property == "source" || property == "target" ||
               property == "aliasIds";
    }

    std::string shortened(const nlohmann::json& value) {
        const auto text = value.dump();
        return text.size() > 160 ? text.substr(0, 160) + "..." : text;
    }

    /**
     * The differences of two JSON objects as text, one line per property.
     */
    std::string differences(const nlohmann::json& expected, const nlohmann::json& actual) {
        std::string result;
        for (auto it = expected.begin(); it != expected.end(); ++it) {
            const auto other = actual.find(it.key());
            if (other == actual.end()) {
                result += "  missing " + it.key() + "\n";
                continue;
            }
            if (*other == it.value())
                continue;
            if (it.value().is_array() && other->is_array() && !orderMatters(it.key())) {
                std::multiset<std::string> a, b;
                for (const auto& item : it.value())
                    a.insert(item.dump());
                for (const auto& item : *other)
                    b.insert(item.dump());
                if (a == b)
                    continue;
            }
            result += "  " + it.key() + ": expected " + shortened(it.value()) + " but was " + shortened(*other) + "\n";
        }
        for (auto it = actual.begin(); it != actual.end(); ++it) {
            if (expected.find(it.key()) == expected.end())
                result += "  unexpected " + it.key() + "\n";
        }
        return result;
    }
}

TEST(TestKerMLJson, RebuildsTheDerivedPropertiesOfAParsedModel) {
    const auto parsed = SysMLv2::Files::Parser::parseKerML(
        "package Pkg {\n"
        "  doc /* The documentation */\n"
        "  class A { feature x : B [0..1]; feature y subsets x; end feature e : A; }\n"
        "  class B specializes A;\n"
        "  datatype D;\n"
        "  struct S :> B { feature w : D = 3 + 4; }\n"
        "  alias Al for A;\n"
        "  import Pkg::*;\n"
        "  feature chained : A { feature z redefines A::x; }\n"
        "  behavior Bh { in feature p : D; }\n"
        "  function Fn { in feature q : D; return feature r : D = q; }\n"
        "  assoc As { end feature a : A; end feature b : B; }\n"
        "}\n");
    ASSERT_TRUE(parsed.second.empty());
    const auto model = allElementsOf(parsed.first);
    ASSERT_GT(model.size(), 40u);

    std::vector<std::string> jsons;
    for (const auto& element : model)
        jsons.push_back(element->serializeToJson());
    const auto copies = createElementsFromJson(jsons);
    ASSERT_EQ(copies.size(), model.size());

    std::string report;
    size_t unresolved = 0;
    for (size_t i = 0; i < model.size(); ++i) {
        copies[i]->discardSourceJson();
        if (copies[i]->hasUnresolvedJsonReferences())
            ++unresolved;
        const auto expected = nlohmann::json::parse(model[i]->serializeToJson());
        const auto actual = nlohmann::json::parse(copies[i]->serializeToJson());
        const auto difference = differences(expected, actual);
        if (!difference.empty())
            report += expected.at("@type").get<std::string>() + " " + expected.at("@id").get<std::string>() + " (" +
                      (expected.at("declaredName").is_string() ? expected.at("declaredName").get<std::string>() : std::string("-")) + ")\n" + difference;
    }
    EXPECT_EQ(unresolved, 0u);
    EXPECT_EQ(report, "");
}

TEST(TestKerMLJson, ServerPayloadIsReturnedUnchanged) {
    const std::string id = newId();
    const std::string membership = newId();
    const std::string member = newId();
    nlohmann::json payload = {
        {"@id", id},
        {"@type", "Package"},
        {"elementId", id},
        {"declaredName", "FromServer"},
        {"aliasIds", nlohmann::json::array()},
        {"ownedRelationship", nlohmann::json::array({{{"@id", membership}}})},
        {"ownedMembership", nlohmann::json::array({{{"@id", membership}}})},
        {"ownedMember", nlohmann::json::array({{{"@id", member}}})},
        {"member", nlohmann::json::array({{{"@id", member}}})},
        {"ownedElement", nlohmann::json::array({{{"@id", membership}}})},
        {"qualifiedName", "FromServer"},
        {"serverOnlyProperty", {{"nested", true}}}
    };
    // (the element writes more than the payload holds, but everything of the payload is unchanged, unknown properties included)
    const auto expectContainsPayload = [&payload](const nlohmann::json& json) {
        for (auto it = payload.begin(); it != payload.end(); ++it) {
            ASSERT_NE(json.find(it.key()), json.end()) << it.key();
            EXPECT_EQ(json.at(it.key()), it.value()) << it.key();
        }
    };
    Package package(payload.dump());
    expectContainsPayload(nlohmann::json::parse(package.serializeToJson()));

    // the same through the factory
    const auto created = createElementFromJson(payload.dump());
    expectContainsPayload(nlohmann::json::parse(created->serializeToJson()));

    // a property that is changed afterwards is written; the others stay as they were
    package.setDeclaredName("Renamed");
    const auto changed = nlohmann::json::parse(package.serializeToJson());
    EXPECT_EQ(changed.at("declaredName"), "Renamed");
    EXPECT_EQ(changed.at("ownedMember"), payload.at("ownedMember"));
    EXPECT_EQ(changed.at("serverOnlyProperty"), payload.at("serverOnlyProperty"));
    EXPECT_EQ(changed.at("ownedRelationship"), payload.at("ownedRelationship"));

    // an element that is created without JSON does not know any source
    package.discardSourceJson();
    const auto own = nlohmann::json::parse(package.serializeToJson());
    EXPECT_EQ(own.at("declaredName"), "Renamed");
    // (the ids of the references that are not resolved are still known, the unknown property is gone)
    EXPECT_EQ(own.at("ownedMember"), payload.at("ownedMember"));
    EXPECT_EQ(own.find("serverOnlyProperty"), own.end());
}

TEST(TestKerMLJson, ElementsOfOneBatchAreLinked) {
    const std::string namespaceId = newId();
    const std::string membershipId = newId();
    const std::string memberId = newId();
    const std::vector<std::string> jsons = {
        nlohmann::json({{"@id", namespaceId}, {"@type", "Package"}, {"declaredName", "P"}, {"ownedRelationship", nlohmann::json::array({{{"@id", membershipId}}})}}).dump(),
        nlohmann::json({{"@id", membershipId}, {"@type", "OwningMembership"}, {"owningRelatedElement", {{"@id", namespaceId}}},
                        {"ownedRelatedElement", nlohmann::json::array({{{"@id", memberId}}})}, {"memberElement", {{"@id", memberId}}}}).dump(),
        nlohmann::json({{"@id", memberId}, {"@type", "Class"}, {"declaredName", "C"}, {"owningRelationship", {{"@id", membershipId}}}}).dump()};
    const auto elements = createElementsFromJson(jsons);
    ASSERT_EQ(elements.size(), 3u);
    const auto package = std::dynamic_pointer_cast<Package>(elements[0]);
    const auto membership = std::dynamic_pointer_cast<OwningMembership>(elements[1]);
    const auto member = std::dynamic_pointer_cast<Class>(elements[2]);
    ASSERT_TRUE(package && membership && member);
    EXPECT_FALSE(package->hasUnresolvedJsonReferences());
    EXPECT_EQ(membership->owningRelatedElement(), package);
    EXPECT_EQ(member->owningRelationship(), membership);
    EXPECT_EQ(member->owner(), package);
    ASSERT_EQ(package->ownedMember().size(), 1u);
    EXPECT_EQ(package->ownedMember().front(), member);
    ASSERT_EQ(package->ownedMembership().size(), 1u);
    EXPECT_EQ(package->member().size(), 1u);
    EXPECT_EQ(package->ownedRelationship().size(), 1u);
    EXPECT_FALSE(package->ownedElements().empty());

    // linking a second time does not duplicate anything
    linkElements(elements);
    EXPECT_EQ(package->ownedMember().size(), 1u);
    EXPECT_EQ(package->ownedMembership().size(), 1u);
}

TEST(TestKerMLJson, ASetterOverridesTheIdThatWasReadFromJson) {
    auto a = std::make_shared<Type>("A");
    auto c = std::make_shared<Type>("C");
    std::map<boost::uuids::uuid, std::shared_ptr<Element>> elements;
    elements[a->getId()] = a;
    elements[c->getId()] = c;
    const auto lookup = lookupIn(elements);

    const nlohmann::json input = {{"@id", newId()}, {"@type", "Specialization"}, {"general", {{"@id", boost::uuids::to_string(a->getId())}}}};
    Specialization specialization(input.dump());
    specialization.discardSourceJson();
    specialization.setGeneral(c);
    EXPECT_EQ(nlohmann::json::parse(specialization.serializeToJson()).at("general"), nlohmann::json({{"@id", boost::uuids::to_string(c->getId())}}));
    specialization.resolveJsonReferences(lookup);
    EXPECT_EQ(specialization.general(), c);
    EXPECT_FALSE(specialization.hasUnresolvedJsonReferences());

    // a many-valued property that is emptied is empty
    const nlohmann::json dependencyInput = {{"@id", newId()}, {"@type", "Dependency"},
                                            {"supplier", nlohmann::json::array({{{"@id", newId()}}, {{"@id", newId()}}})}};
    Dependency dependency(dependencyInput.dump());
    dependency.discardSourceJson();
    ASSERT_TRUE(dependency.hasUnresolvedJsonReferences());
    dependency.setSupplier(std::vector<std::shared_ptr<Element>>{});
    EXPECT_TRUE(nlohmann::json::parse(dependency.serializeToJson()).at("supplier").empty());
    EXPECT_FALSE(dependency.hasUnresolvedJsonReferences());

    // the setters of Element
    Element element(R"({"@id":")" + newId() + R"(","ownedRelationship":[{"@id":")" + newId() + R"("}]})");
    ASSERT_TRUE(element.hasUnresolvedJsonReferences());
    element.setOwnedRelationship({});
    EXPECT_FALSE(element.hasUnresolvedJsonReferences());
}

TEST(TestKerMLJson, ParsingKeepsTheFixedOperatorOfAnExpression) {
    const auto parse = [](const std::string& type, const std::string& op) {
        return nlohmann::json({{"@id", newId()}, {"@type", type}, {"operator", op}}).dump();
    };
    CollectExpression collect(parse("CollectExpression", "+"));
    EXPECT_EQ(collect.operatorName(), "collect");
    SelectExpression select(parse("SelectExpression", "+"));
    EXPECT_EQ(select.operatorName(), "select");
    IndexExpression index(parse("IndexExpression", "+"));
    EXPECT_EQ(index.operatorName(), "#");
    FeatureChainExpression chain(parse("FeatureChainExpression", "+"));
    EXPECT_EQ(chain.operatorName(), ".");
    EXPECT_NO_THROW(createElementFromJson(parse("FeatureChainExpression", "")));
    const auto created = std::dynamic_pointer_cast<SelectExpression>(createElementFromJson(parse("SelectExpression", "nonsense")));
    ASSERT_NE(created, nullptr);
    EXPECT_EQ(created->operatorName(), "select");
    created->discardSourceJson();
    EXPECT_EQ(nlohmann::json::parse(created->serializeToJson()).at("operator"), "select");

    // a valid operator is read
    OperatorExpression free(parse("OperatorExpression", "=="));
    EXPECT_EQ(free.operatorName(), "==");
    CollectExpression same(parse("CollectExpression", "collect"));
    EXPECT_EQ(same.operatorName(), "collect");
}

TEST(TestKerMLJson, OneRefusedReferenceDoesNotStopTheOthers) {
    auto a = std::make_shared<Package>("A");
    auto b = std::make_shared<Package>("B");
    std::map<boost::uuids::uuid, std::shared_ptr<Element>> elements;
    elements[a->getId()] = a;
    elements[b->getId()] = b;
    const auto idOf = [](const std::shared_ptr<Package>& p) { return boost::uuids::to_string(p->getId()); };
    // the same element twice in "source" is refused by the model (a collection holds an element once), "target" is fine
    const nlohmann::json input = {{"@id", newId()}, {"@type", "Relationship"},
                                  {"source", nlohmann::json::array({{{"@id", idOf(a)}}, {{"@id", idOf(a)}}})},
                                  {"target", nlohmann::json::array({{{"@id", idOf(b)}}})}};
    Relationship relationship(input.dump());
    relationship.discardSourceJson();
    relationship.resolveJsonReferences(lookupIn(elements));
    EXPECT_TRUE(relationship.source().empty());
    ASSERT_EQ(relationship.target().size(), 1u);
    EXPECT_EQ(relationship.target().front(), b);
    EXPECT_TRUE(relationship.hasUnresolvedJsonReferences());
    EXPECT_EQ(nlohmann::json::parse(relationship.serializeToJson()).at("source"), input.at("source"));
}

TEST(TestKerMLJson, DerivedNamesAreNotReadFromJson) {
    const std::string id = newId();
    Package package(nlohmann::json({{"@id", id}, {"@type", "Package"}, {"name", nullptr}, {"declaredName", nullptr}, {"qualifiedName", "P::x"}, {"shortName", "s"}}).dump());
    package.discardSourceJson();
    const auto json = nlohmann::json::parse(package.serializeToJson());
    EXPECT_TRUE(json.at("name").is_null());
    EXPECT_TRUE(json.at("shortName").is_null());
    EXPECT_TRUE(json.at("declaredName").is_null());
    EXPECT_FALSE(package.name().has_value());

    Package named(nlohmann::json({{"@id", id}, {"declaredName", "N"}, {"declaredShortName", "n"}}).dump());
    named.discardSourceJson();
    const auto namedJson = nlohmann::json::parse(named.serializeToJson());
    EXPECT_EQ(namedJson.at("name"), "N");
    EXPECT_EQ(namedJson.at("shortName"), "n");
}

TEST(TestKerMLJson, ConstructorsWithANullPointerStayUnambiguous) {
    Documentation documentation(nullptr);
    EXPECT_EQ(documentation.documentedElement(), nullptr);
    EXPECT_ANY_THROW(FeatureTyping(nullptr));
}

TEST(TestKerMLJson, PlainElementKeepsItsType) {
    Element element(nlohmann::json({{"@id", newId()}, {"@type", "PartUsage"}, {"declaredName", "Car"}}).dump());
    EXPECT_EQ(element.getType(), "PartUsage");
    // the metaclasses keep their own type
    Package package(nlohmann::json({{"@id", newId()}, {"@type", "Feature"}}).dump());
    EXPECT_EQ(package.getType(), "Package");
}

TEST(TestKerMLJson, MemberElementIdIsKnownWhileTheMemberIsUnresolved) {
    const std::string member = newId();
    OwningMembership membership(nlohmann::json({{"@id", newId()}, {"@type", "OwningMembership"}, {"memberElement", {{"@id", member}}}}).dump());
    membership.discardSourceJson();
    const auto json = nlohmann::json::parse(membership.serializeToJson());
    EXPECT_EQ(json.at("memberElementId"), member);
    EXPECT_EQ(json.at("ownedMemberElementId"), member);
}

TEST(TestKerMLJson, RebuildsTheDerivedPropertiesThatTheJsonLacks) {
    const auto parsed = SysMLv2::Files::Parser::parseKerML(
        "package Pkg {\n"
        "  class A { feature x : B [0..1]; end feature e : A; }\n"
        "  class B specializes A;\n"
        "  import Pkg::*;\n"
        "  struct S :> B { feature w : A; }\n"
        "}\n");
    ASSERT_TRUE(parsed.second.empty());
    const auto model = allElementsOf(parsed.first);

    // JSON that only holds the stored properties of the owner relations, like a hand written payload
    // (the parsers do not agree about the ownedElement of a membership that owns a feature, so that property is not compared here)
    const std::vector<std::string> rebuilt = {"owner", "ownedMember", "member", "ownedMembership", "membership", "ownedFeatureMembership",
                                              "featureMembership", "ownedFeature", "ownedEndFeature", "owningType", "owningFeatureMembership",
                                              "ownedTyping", "type", "ownedImport", "documentedElement", "membershipOwningNamespace",
                                              "ownedSpecialization", "owningFeature", "endOwningType", "importOwningNamespace"};
    std::vector<std::string> jsons;
    for (const auto& element : model) {
        auto json = nlohmann::json::parse(element->serializeToJson());
        for (const auto& key : rebuilt) {
            // ("type" is derived for a feature, but stored for a feature typing)
            if (key == "type" && json.at("@type") == "FeatureTyping")
                continue;
            json.erase(key);
        }
        json.erase("ownedElement");
        jsons.push_back(json.dump());
    }
    const auto copies = createElementsFromJson(jsons);
    ASSERT_EQ(copies.size(), model.size());
    std::string report;
    for (size_t i = 0; i < model.size(); ++i) {
        copies[i]->discardSourceJson();
        const auto expected = nlohmann::json::parse(model[i]->serializeToJson());
        const auto actual = nlohmann::json::parse(copies[i]->serializeToJson());
        nlohmann::json expectedPart, actualPart;
        for (const auto& key : rebuilt) {
            if (expected.contains(key))
                expectedPart[key] = expected.at(key);
            if (actual.contains(key))
                actualPart[key] = actual.at(key);
        }
        const auto difference = differences(expectedPart, actualPart);
        if (!difference.empty())
            report += expected.at("@type").get<std::string>() + " " + expected.at("@id").get<std::string>() + "\n" + difference;
    }
    EXPECT_EQ(report, "");
}

TEST(TestKerMLJson, ArraysOfElementsAreLinkedByTheDeserializer) {
    const std::string namespaceId = newId();
    const std::string membershipId = newId();
    const std::string memberId = newId();
    const nlohmann::json array = nlohmann::json::array({
        {{"@id", namespaceId}, {"@type", "Package"}, {"declaredName", "P"}, {"ownedRelationship", nlohmann::json::array({{{"@id", membershipId}}})},
         {"ownedMember", nlohmann::json::array({{{"@id", memberId}}})}},
        {{"@id", membershipId}, {"@type", "OwningMembership"}, {"owningRelatedElement", {{"@id", namespaceId}}}, {"memberElement", {{"@id", memberId}}}},
        {{"@id", memberId}, {"@type", "Class"}, {"declaredName", "C"}, {"owningRelationship", {{"@id", membershipId}}}, {"isAbstract", true}}});
    const auto entities = SysMLv2::SysMLv2Deserializer::deserializeJsonArray(array.dump());
    ASSERT_EQ(entities.size(), 3u);
    const auto package = std::dynamic_pointer_cast<Package>(entities[0]);
    const auto member = std::dynamic_pointer_cast<Class>(entities[2]);
    ASSERT_TRUE(package && member);
    ASSERT_EQ(package->ownedMember().size(), 1u);
    EXPECT_EQ(package->ownedMember().front(), member);
    EXPECT_EQ(member->owner(), package);
    EXPECT_FALSE(package->hasUnresolvedJsonReferences());
    // the payload is written back with everything it held
    const auto written = nlohmann::json::parse(package->serializeToJson());
    EXPECT_EQ(written.at("ownedMember"), array[0].at("ownedMember"));
    EXPECT_EQ(written.at("ownedRelationship"), array[0].at("ownedRelationship"));

    // a single element keeps what it can not link
    const auto single = std::dynamic_pointer_cast<Package>(SysMLv2::SysMLv2Deserializer::deserializeJsonString(array[0].dump()));
    ASSERT_NE(single, nullptr);
    EXPECT_EQ(nlohmann::json::parse(single->serializeToJson()).at("ownedMember"), array[0].at("ownedMember"));
}
