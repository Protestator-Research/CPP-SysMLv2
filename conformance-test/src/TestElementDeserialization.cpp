//
// Tests of the deserialization of elements (SysMLv2Deserializer, Element::fromJson, DataVersion, CommitRequest).
//

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <memory>
#include <string>

#include <kerml/root/elements/Element.h>
#include <kerml/kernel/packages/Package.h>
#include <sysmlv2/rest/entities/CommitRequest.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/serialization/SysMLv2Deserializer.h>

namespace {
    const std::string ElementJson = R"({"@id":"c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4","@type":"Element","aliasIds":[],"declaredName":"SmokeTest","declaredShortName":"","documentation":[],"elementId":"c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4","isImpliedIncluded":false,"isLibraryElement":false,"name":"","ownedAnnotation":[],"ownedElements":[],"ownedRelationships":[],"owner":"","owningRelationship":"","qualifiedName":"","shortName":"","textualRepresentation":[]})";

    void expectRoundTrip(const std::string& json, const std::string& type, const std::string& declaredName) {
        auto entity = SysMLv2::SysMLv2Deserializer::deserializeJsonString(json);
        ASSERT_NE(entity, nullptr);
        auto element = std::dynamic_pointer_cast<KerML::Entities::Element>(entity);
        ASSERT_NE(element, nullptr);
        EXPECT_EQ(element->getType(), type);
        ASSERT_TRUE(element->declaredName().has_value());
        EXPECT_EQ(element->declaredName().value(), declaredName);
        EXPECT_EQ(nlohmann::json::parse(element->serializeToJson()), nlohmann::json::parse(json));
        EXPECT_EQ(boost::uuids::to_string(element->getId()), nlohmann::json::parse(json)["@id"].get<std::string>());
    }
}

TEST(TestElementDeserialization, Element) {
    KerML::Entities::Element original;
    original.setDeclaredName("Plain");
    expectRoundTrip(original.serializeToJson(), "Element", "Plain");
    expectRoundTrip(ElementJson, "Element", "SmokeTest");
}

TEST(TestElementDeserialization, Package) {
    KerML::Entities::Package original;
    original.setDeclaredName("MyPackage");
    ASSERT_EQ(original.getType(), "Package");
    expectRoundTrip(original.serializeToJson(), "Package", "MyPackage");
}

TEST(TestElementDeserialization, ToleratesMissingAndWrongFields) {
    const std::string json = R"({"@id":"c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4","@type":"Feature","owner":"","name":null,"aliasIds":"x","declaredName":5,"elementId":"","isLibraryElement":"yes"})";
    std::shared_ptr<SysMLv2::REST::IEntity> entity;
    ASSERT_NO_THROW(entity = SysMLv2::SysMLv2Deserializer::deserializeJsonString(json));
    auto element = std::dynamic_pointer_cast<KerML::Entities::Element>(entity);
    ASSERT_NE(element, nullptr);
    EXPECT_EQ(element->getType(), "Feature");
    EXPECT_FALSE(element->declaredName().has_value());
    EXPECT_FALSE(element->isLibraryElement());
    EXPECT_EQ(element->elementId(), "c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4");
}

TEST(TestElementDeserialization, WithoutIdIsNull) {
    EXPECT_EQ(SysMLv2::SysMLv2Deserializer::deserializeJsonString(R"({"@type":"Package","declaredName":"x"})"), nullptr);
    EXPECT_EQ(SysMLv2::SysMLv2Deserializer::deserializeJsonString(R"({"@type":"Element"})"), nullptr);
}

TEST(TestElementDeserialization, MalformedJsonThrows) {
    EXPECT_ANY_THROW(SysMLv2::SysMLv2Deserializer::deserializeJsonString("{not json"));
}

TEST(TestElementDeserialization, DataVersionWithPackagePayload) {
    KerML::Entities::Package package;
    package.setDeclaredName("Payload");
    const nlohmann::json version = {
        {"@id", "11111111-2222-4333-8444-555555555555"},
        {"@type", "DataVersion"},
        {"alias", {""}},
        {"payload", nlohmann::json::parse(package.serializeToJson())}
    };
    SysMLv2::REST::DataVersion dataVersion(version.dump());
    ASSERT_NE(dataVersion.getPayload(), nullptr);
    EXPECT_EQ(dataVersion.getPayload()->getType(), "Package");
}

TEST(TestElementDeserialization, CommitRequestWithElementPayload) {
    const nlohmann::json request = {
        {"@type", "CommitRequest"},
        {"change", {{
            {"@id", "11111111-2222-4333-8444-555555555555"},
            {"@type", "DataVersion"},
            {"alias", {""}},
            {"payload", nlohmann::json::parse(ElementJson)}
        }}},
        {"description", "smoke commit"}
    };
    SysMLv2::REST::CommitRequest commitRequest(request.dump());
    ASSERT_EQ(commitRequest.changeRequested().size(), 1u);
    ASSERT_NE(commitRequest.changeRequested()[0]->getPayload(), nullptr);
    EXPECT_EQ(commitRequest.description(), "smoke commit");
}
