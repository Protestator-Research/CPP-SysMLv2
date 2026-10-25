//
// Tests of the query entities of the REST API (AP 3): Query, QueryRequest, PrimitiveConstraint, CompositeConstraint,
// the string mapping of Operator, JoinOperator, ChangeType and Direction and the change filter of the versioning service.
//

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <kerml/kernel/packages/Package.h>
#include "support/CerrCapture.h"
#include <sysmlv2/rest/Deprecation.h>
#include <sysmlv2/rest/entities/ChangeType.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Constraint.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/Direction.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/Query.h>
#include <sysmlv2/rest/entities/QueryRequest.h>
#include <sysmlv2/service/implementation/ProjectVersioningService.h>

using namespace SysMLv2::REST;
using nlohmann::json;

namespace {
    const std::string QueryId = "3b5dd1c9-0d0f-4d6a-9a53-3a8a6c3f6f10";
    const std::string ProjectId = "6e701bf8-7793-49de-9b0e-2f43376edabf";
    const std::string DataId = "11111111-2222-4333-8444-555555555555";

    std::size_t countWarnings(const std::string& output) {
        std::size_t count = 0;
        for (auto pos = output.find("Deprecated:"); pos != std::string::npos; pos = output.find("Deprecated:", pos + 1))
            ++count;
        return count;
    }

    boost::uuids::uuid uuidOf(const std::string& id) {
        return boost::uuids::string_generator()(id);
    }

    json annexBQuery() {
        return json::parse(R"({
            "@id": "3b5dd1c9-0d0f-4d6a-9a53-3a8a6c3f6f10",
            "@type": "Query",
            "owningProject": {"@id": "6e701bf8-7793-49de-9b0e-2f43376edabf"},
            "scope": [],
            "select": ["owner", "@type", "name", "@id"],
            "where": {"@type": "PrimitiveConstraint", "inverse": false, "operator": "=", "property": "@type", "value": "PartDefinition"}
        })");
    }

    class RestQuery : public ::testing::Test {
    protected:
        void SetUp() override { resetDeprecationWarningsForTesting(); }
    };

    std::shared_ptr<KerML::Entities::Package> makePackage(const std::string& name) {
        auto package = std::make_shared<KerML::Entities::Package>();
        package->setDeclaredName(name);
        return package;
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
// Enum string mapping
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestQuery, OperatorLiterals) {
    const std::vector<std::pair<Operator, std::string>> literals = {
        {Operator::InstanceOf, "instanceOf"}, {Operator::Equal, "="}, {Operator::Less, "<"}, {Operator::LessOrEqual, "<="},
        {Operator::Greater, ">"}, {Operator::GreaterOrEqual, ">="}, {Operator::In, "in"}};
    for (const auto& [op, text] : literals) {
        EXPECT_EQ(toString(op), text);
        EXPECT_EQ(operatorFromString(text), op);
    }
    EXPECT_THROW(operatorFromString("=="), std::invalid_argument);
    EXPECT_THROW(operatorFromString(""), std::invalid_argument);
    EXPECT_EQ(toString(JoinOperator::And), "and");
    EXPECT_EQ(toString(JoinOperator::Or), "or");
    EXPECT_EQ(joinOperatorFromString("or"), JoinOperator::Or);
    EXPECT_THROW(joinOperatorFromString("xor"), std::invalid_argument);
}

TEST_F(RestQuery, ChangeTypeAndDirectionLiterals) {
    EXPECT_EQ(toString(CREATED), "CREATED");
    EXPECT_EQ(toString(UPDATED), "UPDATED");
    EXPECT_EQ(toString(DELETED), "DELETED");
    EXPECT_EQ(changeTypeFromString("CREATED"), CREATED);
    EXPECT_EQ(changeTypeFromString("UPDATED"), UPDATED);
    EXPECT_EQ(changeTypeFromString("DELETED"), DELETED);
    EXPECT_THROW(changeTypeFromString("created"), std::invalid_argument);
    // The numeric values did not change.
    EXPECT_EQ(static_cast<int>(CREATED), 0);
    EXPECT_EQ(static_cast<int>(UPDATED), 1);
    EXPECT_EQ(static_cast<int>(DELETED), 2);

    EXPECT_EQ(toString(IN), "in");
    EXPECT_EQ(toString(OUT), "out");
    EXPECT_EQ(toString(BOTH), "both");
    EXPECT_EQ(directionFromString("in"), IN);
    EXPECT_EQ(directionFromString("out"), OUT);
    EXPECT_EQ(directionFromString("both"), BOTH);
    EXPECT_THROW(directionFromString("IN"), std::invalid_argument);
    EXPECT_EQ(static_cast<int>(IN), 0);
    EXPECT_EQ(static_cast<int>(BOTH), 2);
}

// ---------------------------------------------------------------------------------------------------------------------------
// Constraints
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestQuery, PrimitiveConstraintEveryOperatorRoundTrips) {
    for (const auto op : {Operator::InstanceOf, Operator::Equal, Operator::Less, Operator::LessOrEqual, Operator::Greater,
                          Operator::GreaterOrEqual, Operator::In}) {
        PrimitiveConstraint constraint(true, "size", op, json(5));
        const json written = json::parse(constraint.serializeToJson());
        EXPECT_EQ(written["@type"], "PrimitiveConstraint");
        EXPECT_EQ(written["operator"], toString(op));
        EXPECT_EQ(written["inverse"], true);
        EXPECT_EQ(written["value"], 5);

        PrimitiveConstraint read(written.dump());
        EXPECT_EQ(read.getOperator(), op);
        EXPECT_TRUE(read.isInverse());
        EXPECT_EQ(read.getProperty(), "size");
        EXPECT_EQ(json::parse(read.serializeToJson()), written);
    }
}

TEST_F(RestQuery, PrimitiveConstraintSingleAndMultipleValues) {
    PrimitiveConstraint single(false, "name", Operator::Equal, json("a"));
    EXPECT_TRUE(single.isSingleValue());
    EXPECT_EQ(json::parse(single.serializeToJson())["value"], "a");
    EXPECT_EQ(single.getValues(), json::array({"a"}));

    PrimitiveConstraint multiple(false, "name", Operator::In, json::array({"a", "b", 3, true, nullptr}));
    EXPECT_FALSE(multiple.isSingleValue());
    const json written = json::parse(multiple.serializeToJson());
    EXPECT_EQ(written["value"], json::array({"a", "b", 3, true, nullptr}));
    PrimitiveConstraint read(written.dump());
    EXPECT_FALSE(read.isSingleValue());
    EXPECT_EQ(read.getValues(), multiple.getValues());

    // An array with one element stays an array, a single value stays single.
    PrimitiveConstraint arrayOfOne(R"({"@type":"PrimitiveConstraint","property":"p","operator":"in","value":["x"]})");
    EXPECT_FALSE(arrayOfOne.isSingleValue());
    EXPECT_EQ(json::parse(arrayOfOne.serializeToJson())["value"], json::array({"x"}));
    PrimitiveConstraint singleNull(R"({"@type":"PrimitiveConstraint","property":"p","operator":"=","value":null})");
    EXPECT_TRUE(singleNull.isSingleValue());
    // inverse is optional on reading.
    EXPECT_FALSE(singleNull.isInverse());
}

TEST_F(RestQuery, PrimitiveConstraintRejectsInvalid) {
    EXPECT_THROW(PrimitiveConstraint(false, "", Operator::Equal, json("a")), std::invalid_argument);
    EXPECT_THROW(PrimitiveConstraint(false, "p", Operator::Equal, json::array()), std::invalid_argument);
    EXPECT_THROW(PrimitiveConstraint(false, "p", Operator::Equal, json::object()), std::invalid_argument);
    EXPECT_THROW(PrimitiveConstraint(false, "p", Operator::Equal, json::array({json::array()})), std::invalid_argument);
    // unknown operator
    try {
        PrimitiveConstraint bad(R"({"@type":"PrimitiveConstraint","property":"p","operator":"~","value":1})");
        FAIL() << "expected an exception";
    } catch (const std::invalid_argument& ex) {
        EXPECT_NE(std::string(ex.what()).find("PrimitiveConstraint"), std::string::npos);
        EXPECT_NE(std::string(ex.what()).find("'~'"), std::string::npos);
    }
    EXPECT_THROW(PrimitiveConstraint(R"({"@type":"PrimitiveConstraint","operator":"=","value":1})"), std::invalid_argument);
    EXPECT_THROW(PrimitiveConstraint(R"({"@type":"PrimitiveConstraint","property":"p","value":1})"), std::invalid_argument);
    EXPECT_THROW(PrimitiveConstraint(R"({"@type":"PrimitiveConstraint","property":"p","operator":"="})"), std::invalid_argument);
    EXPECT_THROW(PrimitiveConstraint(R"({"@type":"CompositeConstraint","property":"p","operator":"=","value":1})"), std::invalid_argument);
    EXPECT_THROW(PrimitiveConstraint("{not json"), std::invalid_argument);
}

TEST_F(RestQuery, CompositeConstraintNestedRoundTrip) {
    auto a = std::make_shared<PrimitiveConstraint>(false, "@type", Operator::Equal, json("PartDefinition"));
    auto b = std::make_shared<PrimitiveConstraint>(true, "name", Operator::In, json::array({"x", "y"}));
    auto c = std::make_shared<PrimitiveConstraint>(false, "size", Operator::GreaterOrEqual, json(2.5));
    auto inner = std::make_shared<CompositeConstraint>(JoinOperator::Or, std::vector<std::shared_ptr<Constraint>>{b, c});
    CompositeConstraint outer(JoinOperator::And, {a, inner});

    const json written = json::parse(outer.serializeToJson());
    EXPECT_EQ(written["@type"], "CompositeConstraint");
    EXPECT_EQ(written["operator"], "and");
    ASSERT_EQ(written["constraint"].size(), 2u);
    EXPECT_EQ(written["constraint"][1]["operator"], "or");

    CompositeConstraint read(written.dump());
    EXPECT_EQ(read.getOperator(), JoinOperator::And);
    ASSERT_EQ(read.getConstraints().size(), 2u);
    EXPECT_NE(std::dynamic_pointer_cast<PrimitiveConstraint>(read.getConstraints()[0]), nullptr);
    const auto readInner = std::dynamic_pointer_cast<CompositeConstraint>(read.getConstraints()[1]);
    ASSERT_NE(readInner, nullptr);
    EXPECT_EQ(readInner->getOperator(), JoinOperator::Or);
    EXPECT_EQ(json::parse(read.serializeToJson()), written);

    // The factory chooses the class by "@type".
    const auto viaFactory = Constraint::fromJson(written.dump());
    EXPECT_NE(std::dynamic_pointer_cast<CompositeConstraint>(viaFactory), nullptr);
    EXPECT_EQ(viaFactory->getType(), "CompositeConstraint");
}

TEST_F(RestQuery, CompositeConstraintNeedsTwoConstraints) {
    auto a = std::make_shared<PrimitiveConstraint>(false, "p", Operator::Equal, json(1));
    EXPECT_THROW(CompositeConstraint(JoinOperator::And, {}), std::invalid_argument);
    EXPECT_THROW(CompositeConstraint(JoinOperator::And, {a}), std::invalid_argument);
    EXPECT_THROW(CompositeConstraint(JoinOperator::And, {a, nullptr}), std::invalid_argument);

    const json one = {{"@type", "CompositeConstraint"}, {"operator", "and"}, {"constraint", json::array({json::parse(a->serializeToJson())})}};
    EXPECT_THROW(CompositeConstraint(one.dump()), std::invalid_argument);
    const json none = {{"@type", "CompositeConstraint"}, {"operator", "and"}, {"constraint", json::array()}};
    EXPECT_THROW(CompositeConstraint(none.dump()), std::invalid_argument);
    const json missing = {{"@type", "CompositeConstraint"}, {"operator", "and"}};
    EXPECT_THROW(CompositeConstraint(missing.dump()), std::invalid_argument);
    const json badOperator = {{"@type", "CompositeConstraint"}, {"operator", "xor"}, {"constraint", json::array({1, 2})}};
    EXPECT_THROW(CompositeConstraint(badOperator.dump()), std::invalid_argument);
    // an invalid inner constraint
    const json badInner = {{"@type", "CompositeConstraint"}, {"operator", "or"},
                           {"constraint", json::array({json::parse(a->serializeToJson()), json{{"@type", "Nope"}}})}};
    EXPECT_THROW(CompositeConstraint(badInner.dump()), std::invalid_argument);
}

TEST_F(RestQuery, ConstraintFactoryRejectsUnknownType) {
    EXPECT_THROW(Constraint::fromJson(R"({"property":"p"})"), std::invalid_argument);
    EXPECT_THROW(Constraint::fromJson(R"({"@type":"Query"})"), std::invalid_argument);
    EXPECT_THROW(Constraint::fromJson("[1]"), std::invalid_argument);
    EXPECT_THROW(Constraint::fromJson("{"), std::invalid_argument);
}

// ---------------------------------------------------------------------------------------------------------------------------
// Query and QueryRequest
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestQuery, ParsesAnnexBQuery) {
    CerrCapture capture;
    Query query(annexBQuery().dump());
    EXPECT_EQ(query.getId(), uuidOf(QueryId));
    EXPECT_EQ(query.getType(), "Query");
    EXPECT_EQ(query.getSelect(), (std::vector<std::string>{"owner", "@type", "name", "@id"}));
    EXPECT_TRUE(query.getScope().empty());
    EXPECT_TRUE(query.getOrderBy().empty());
    ASSERT_NE(query.getOwningProject(), nullptr);
    EXPECT_EQ(query.getOwningProject()->getId(), uuidOf(ProjectId));
    const auto where = std::dynamic_pointer_cast<PrimitiveConstraint>(query.getWhere());
    ASSERT_NE(where, nullptr);
    EXPECT_EQ(where->getProperty(), "@type");
    EXPECT_EQ(where->getOperator(), Operator::Equal);
    EXPECT_TRUE(where->isSingleValue());
    EXPECT_EQ(where->getValues(), json::array({"PartDefinition"}));
    EXPECT_EQ(countWarnings(capture.str()), 0u);

    const json written = json::parse(query.serializeToJson());
    EXPECT_EQ(written["where"], annexBQuery()["where"]);
    EXPECT_EQ(written["owningProject"], annexBQuery()["owningProject"]);
    EXPECT_EQ(written["select"], annexBQuery()["select"]);
    EXPECT_EQ(written["scope"], json::array());
    EXPECT_EQ(written["orderBy"], json::array());
}

TEST_F(RestQuery, QueryRoundTrip) {
    CerrCapture capture;
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    auto data = std::make_shared<Data>(uuidOf(DataId));
    auto where = std::make_shared<PrimitiveConstraint>(false, "name", Operator::Equal, json("x"));
    Query query("my query", {"name", "@id"}, {data}, {"name"}, where, project);

    const json written = json::parse(query.serializeToJson());
    EXPECT_EQ(written["@type"], "Query");
    EXPECT_EQ(written["name"], "my query");
    EXPECT_EQ(written["orderBy"], json::array({"name"}));
    EXPECT_FALSE(written.contains("order"));
    EXPECT_EQ(written["scope"], json::array({json{{"@id", DataId}}}));
    EXPECT_EQ(written["owningProject"], (json{{"@id", ProjectId}}));
    EXPECT_TRUE(written.contains("where"));

    Query read(written.dump());
    EXPECT_EQ(read.getId(), query.getId());
    EXPECT_EQ(read.getName(), "my query");
    EXPECT_EQ(read.getSelect(), query.getSelect());
    EXPECT_EQ(read.getOrderBy(), query.getOrderBy());
    ASSERT_EQ(read.getScope().size(), 1u);
    EXPECT_EQ(read.getScope()[0]->getId(), uuidOf(DataId));
    EXPECT_EQ(json::parse(read.serializeToJson()), written);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestQuery, QueryWithoutWhereAndProject) {
    CerrCapture capture;
    // the constructor of earlier versions keeps working without a warning
    Query query("q", {"name"}, {}, {"name"});
    const json written = json::parse(query.serializeToJson());
    EXPECT_FALSE(written.contains("where"));
    EXPECT_TRUE(written["owningProject"].is_null());
    EXPECT_EQ(query.getWhere(), nullptr);
    EXPECT_EQ(query.getOwningProject(), nullptr);
    Query read(written.dump());
    EXPECT_EQ(read.getOwningProject(), nullptr);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestQuery, QuerySetters) {
    Query query("q", {"a"}, {}, {});
    query.setSelect({"b"});
    query.setOrderBy({"c"});
    query.setScope({std::make_shared<Data>(uuidOf(DataId))});
    query.setWhere(std::make_shared<PrimitiveConstraint>(false, "p", Operator::Less, json(1)));
    query.setOwningProject(std::make_shared<Project>(json{{"@id", ProjectId}}.dump()));
    const json written = json::parse(query.serializeToJson());
    EXPECT_EQ(written["select"], json::array({"b"}));
    EXPECT_EQ(written["orderBy"], json::array({"c"}));
    EXPECT_EQ(written["scope"].size(), 1u);
    EXPECT_EQ(written["where"]["operator"], "<");
    EXPECT_EQ(written["owningProject"]["@id"], ProjectId);
}

TEST_F(RestQuery, QueryNameAndInvalidJson) {
    Query named("just a name");
    EXPECT_EQ(named.getName(), "just a name");
    EXPECT_FALSE(named.getId().is_nil());
    try {
        Query broken("{not json");
        FAIL() << "expected an exception";
    } catch (const std::invalid_argument& ex) {
        EXPECT_NE(std::string(ex.what()).find("Query"), std::string::npos);
    }
    json bad = annexBQuery();
    bad["select"] = 5;
    EXPECT_THROW(Query(bad.dump()), std::invalid_argument);
    bad = annexBQuery();
    bad["where"] = json{{"@type", "PrimitiveConstraint"}, {"property", "p"}, {"operator", "?"}, {"value", 1}};
    try {
        Query broken(bad.dump());
        FAIL() << "expected an exception";
    } catch (const std::invalid_argument& ex) {
        EXPECT_NE(std::string(ex.what()).find("Query"), std::string::npos);
    }
    bad = annexBQuery();
    bad["owningProject"] = "no reference";
    EXPECT_THROW(Query(bad.dump()), std::invalid_argument);
    bad = annexBQuery();
    bad["scope"] = json::array({"no reference"});
    EXPECT_THROW(Query(bad.dump()), std::invalid_argument);
}

TEST_F(RestQuery, OldOrderFieldWarnsOnce) {
    CerrCapture capture;
    json old = annexBQuery();
    old["order"] = json::array({"name", "@id"});
    Query query(old.dump());
    EXPECT_EQ(query.getOrderBy(), (std::vector<std::string>{"name", "@id"}));
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_NE(capture.str().find("\"order\""), std::string::npos);
    EXPECT_NE(capture.str().find("\"orderBy\""), std::string::npos);
    // the new field wins and is the only one written
    const json written = json::parse(query.serializeToJson());
    EXPECT_EQ(written["orderBy"], json::array({"name", "@id"}));
    EXPECT_FALSE(written.contains("order"));
    // once per run
    Query again(old.dump());
    EXPECT_EQ(countWarnings(capture.str()), 1u);
}

TEST_F(RestQuery, OldScopeWithFullDataWarnsOnce) {
    CerrCapture capture;
    json old = annexBQuery();
    old["scope"] = json::array({json{{"@id", DataId}, {"@type", "Package"}}});
    Query query(old.dump());
    ASSERT_EQ(query.getScope().size(), 1u);
    EXPECT_EQ(query.getScope()[0]->getId(), uuidOf(DataId));
    EXPECT_EQ(query.getScope()[0]->getType(), "Package");
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_NE(capture.str().find("scope"), std::string::npos);
    EXPECT_EQ(json::parse(query.serializeToJson())["scope"], json::array({json{{"@id", DataId}}}));
}

TEST_F(RestQuery, QueryRequestRoundTrip) {
    CerrCapture capture;
    auto where = std::make_shared<PrimitiveConstraint>(false, "@type", Operator::Equal, json("PartDefinition"));
    QueryRequest request("req", {"name"}, {std::make_shared<Data>(uuidOf(DataId))}, {"name"}, where);
    const json written = json::parse(request.serializeToJson());
    EXPECT_EQ(written["@type"], "Query");
    EXPECT_FALSE(written.contains("@id"));
    EXPECT_FALSE(written.contains("owningProject"));
    EXPECT_EQ(written["name"], "req");
    EXPECT_EQ(written["scope"], json::array({json{{"@id", DataId}}}));
    EXPECT_EQ(written["where"]["value"], "PartDefinition");

    QueryRequest read(written.dump());
    EXPECT_TRUE(read.getId().is_nil());
    EXPECT_EQ(read.getName(), "req");
    EXPECT_EQ(read.getSelect(), request.getSelect());
    EXPECT_EQ(read.getOrderBy(), request.getOrderBy());
    ASSERT_NE(read.getWhere(), nullptr);
    EXPECT_EQ(json::parse(read.serializeToJson()), written);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestQuery, QueryRequestFromAnnexBIgnoresIdAndProject) {
    QueryRequest read(annexBQuery().dump());
    EXPECT_TRUE(read.getId().is_nil());
    const json written = json::parse(read.serializeToJson());
    EXPECT_FALSE(written.contains("@id"));
    EXPECT_FALSE(written.contains("owningProject"));
    EXPECT_EQ(written["select"], annexBQuery()["select"]);

    EXPECT_THROW(QueryRequest(R"({"@type":"Commit"})"), std::invalid_argument);
    EXPECT_THROW(QueryRequest("{not json"), std::invalid_argument);
    QueryRequest named("a name");
    EXPECT_TRUE(named.getId().is_nil());
    EXPECT_EQ(named.getName(), "a name");
}

TEST_F(RestQuery, QueryRequestOldOrderWarnsOnce) {
    CerrCapture capture;
    QueryRequest read(R"({"@type":"Query","select":["a"],"order":["a"]})");
    EXPECT_EQ(read.getOrderBy(), (std::vector<std::string>{"a"}));
    EXPECT_EQ(countWarnings(capture.str()), 1u);
}

// ---------------------------------------------------------------------------------------------------------------------------
// ProjectVersioningService::getCommitChange
// ---------------------------------------------------------------------------------------------------------------------------

namespace {
    struct ChangeFixture {
        std::shared_ptr<Project> project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
        std::shared_ptr<KerML::Entities::Package> existing = makePackage("existing");
        std::shared_ptr<KerML::Entities::Package> fresh = makePackage("fresh");
        std::shared_ptr<KerML::Entities::Package> removed = makePackage("removed");
        std::shared_ptr<Commit> grandParent = std::make_shared<Commit>("grand parent", project);
        std::shared_ptr<Commit> parent;
        std::shared_ptr<Commit> commit;
        std::shared_ptr<DataVersion> updated;
        std::shared_ptr<DataVersion> created;
        std::shared_ptr<DataVersion> deleted;
        SysMLv2::API::ProjectVersioningService service;

        ChangeFixture() {
            // "existing" and "removed" were created two commits back, so the ancestors are searched, too.
            grandParent->addChange(std::make_shared<DataVersion>(existing));
            grandParent->addChange(std::make_shared<DataVersion>(removed));
            parent = std::make_shared<Commit>("parent", project, std::vector<std::shared_ptr<Commit>>{grandParent});
            commit = std::make_shared<Commit>("commit", project, std::vector<std::shared_ptr<Commit>>{parent});
            updated = std::make_shared<DataVersion>(existing);
            created = std::make_shared<DataVersion>(fresh);
            deleted = std::make_shared<DataVersion>(nullptr, std::make_shared<DataIdentity>(removed->getId()));
            commit->addChange(updated);
            commit->addChange(created);
            commit->addChange(deleted);
        }

        std::vector<std::shared_ptr<DataVersion>> filter(std::vector<ChangeType> types) {
            std::vector<int> values;
            for (const auto type : types)
                values.push_back(static_cast<int>(type));
            return service.getCommitChange(project, commit, values);
        }
    };
}

TEST_F(RestQuery, CommitChangeFilterEachAlone) {
    CerrCapture capture;
    ChangeFixture f;
    const auto createdOnly = f.filter({CREATED});
    ASSERT_EQ(createdOnly.size(), 1u);
    EXPECT_EQ(createdOnly[0], f.created);
    const auto updatedOnly = f.filter({UPDATED});
    ASSERT_EQ(updatedOnly.size(), 1u);
    EXPECT_EQ(updatedOnly[0], f.updated);
    const auto deletedOnly = f.filter({DELETED});
    ASSERT_EQ(deletedOnly.size(), 1u);
    EXPECT_EQ(deletedOnly[0], f.deleted);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestQuery, CommitChangeFilterCombined) {
    ChangeFixture f;
    const auto createdAndDeleted = f.filter({CREATED, DELETED});
    ASSERT_EQ(createdAndDeleted.size(), 2u);
    EXPECT_EQ(createdAndDeleted[0], f.created);
    EXPECT_EQ(createdAndDeleted[1], f.deleted);

    const auto updatedAndDeleted = f.filter({UPDATED, DELETED});
    ASSERT_EQ(updatedAndDeleted.size(), 2u);
    EXPECT_EQ(updatedAndDeleted[0], f.updated);
    EXPECT_EQ(updatedAndDeleted[1], f.deleted);

    const auto all = f.filter({CREATED, UPDATED, DELETED});
    ASSERT_EQ(all.size(), 3u);
    EXPECT_EQ(all[0], f.updated);
    EXPECT_EQ(all[1], f.created);
    EXPECT_EQ(all[2], f.deleted);
}

TEST_F(RestQuery, CommitChangeEmptyFilterReturnsAll) {
    ChangeFixture f;
    EXPECT_EQ(f.filter({}).size(), 3u);
}

TEST_F(RestQuery, CommitChangeWithoutPreviousCommitsIsCreated) {
    ChangeFixture f;
    auto first = std::make_shared<Commit>("first", f.project);
    first->addChange(std::make_shared<DataVersion>(makePackage("a")));
    EXPECT_EQ(f.service.getCommitChange(f.project, first, {static_cast<int>(CREATED)}).size(), 1u);
    EXPECT_TRUE(f.service.getCommitChange(f.project, first, {static_cast<int>(UPDATED)}).empty());
}

namespace {
    std::shared_ptr<DataVersion> deletionOf(const std::shared_ptr<KerML::Entities::Package>& package) {
        return std::make_shared<DataVersion>(nullptr, std::make_shared<DataIdentity>(package->getId()));
    }
}

TEST_F(RestQuery, CommitChangeRecreationAfterDeletionIsCreated) {
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    auto package = makePackage("x");
    auto a = std::make_shared<Commit>("A", project);
    a->addChange(std::make_shared<DataVersion>(package));
    auto b = std::make_shared<Commit>("B", project, std::vector<std::shared_ptr<Commit>>{a});
    b->addChange(deletionOf(package));
    auto c = std::make_shared<Commit>("C", project, std::vector<std::shared_ptr<Commit>>{b});
    auto recreated = std::make_shared<DataVersion>(package);
    c->addChange(recreated);

    SysMLv2::API::ProjectVersioningService service;
    EXPECT_EQ(service.getCommitChange(project, c, {static_cast<int>(CREATED)}).size(), 1u);
    EXPECT_TRUE(service.getCommitChange(project, c, {static_cast<int>(UPDATED)}).empty());
    // the deletion commit itself: the Data exists before it
    EXPECT_EQ(service.getCommitChange(project, b, {static_cast<int>(DELETED)}).size(), 1u);
}

TEST_F(RestQuery, CommitChangeMergeCommitExistsInAnyParent) {
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    auto package = makePackage("x");
    auto base = std::make_shared<Commit>("base", project);
    base->addChange(std::make_shared<DataVersion>(package));
    auto deleting = std::make_shared<Commit>("deleting", project, std::vector<std::shared_ptr<Commit>>{base});
    deleting->addChange(deletionOf(package));
    auto keeping = std::make_shared<Commit>("keeping", project, std::vector<std::shared_ptr<Commit>>{base});
    keeping->addChange(std::make_shared<DataVersion>(makePackage("other")));

    auto merge = std::make_shared<Commit>("merge", project, std::vector<std::shared_ptr<Commit>>{deleting, keeping});
    merge->addChange(std::make_shared<DataVersion>(package));
    SysMLv2::API::ProjectVersioningService service;
    EXPECT_EQ(service.getCommitChange(project, merge, {static_cast<int>(UPDATED)}).size(), 1u);
    EXPECT_TRUE(service.getCommitChange(project, merge, {static_cast<int>(CREATED)}).empty());

    // both parents deleted it
    auto deleting2 = std::make_shared<Commit>("deleting2", project, std::vector<std::shared_ptr<Commit>>{base});
    deleting2->addChange(deletionOf(package));
    auto merge2 = std::make_shared<Commit>("merge2", project, std::vector<std::shared_ptr<Commit>>{deleting, deleting2});
    merge2->addChange(std::make_shared<DataVersion>(package));
    EXPECT_EQ(service.getCommitChange(project, merge2, {static_cast<int>(CREATED)}).size(), 1u);
}

namespace {
    // Gives the test access to the commit storage of the service.
    struct StoringService : SysMLv2::API::ProjectVersioningService {
        void store(const std::shared_ptr<Project>& project, const std::shared_ptr<Commit>& commit) {
            ProjectIdCommitMap[project->getId()].push_back(commit);
        }
    };
}

TEST_F(RestQuery, CommitChangeCycleTerminatesAndUnknownFilterValueIsIgnored) {
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    // Stored commit S has itself as previous commit (by reference), so resolving the reference leads to a cycle.
    const auto idOfS = uuidOf(DataId);
    auto reference = std::make_shared<Commit>(json{{"@id", DataId}}.dump());
    auto stored = std::make_shared<Commit>(idOfS, "S", project, std::vector<std::shared_ptr<Commit>>{reference});
    StoringService service;
    service.store(project, stored);
    auto head = std::make_shared<Commit>("head", project, std::vector<std::shared_ptr<Commit>>{stored});
    auto change = std::make_shared<DataVersion>(makePackage("y"));
    head->addChange(change);

    EXPECT_EQ(service.getCommitChange(project, head, {static_cast<int>(CREATED)}).size(), 1u);
    // an unknown value in the filter is ignored
    EXPECT_TRUE(service.getCommitChange(project, head, {42}).empty());
    EXPECT_EQ(service.getCommitChange(project, head, {42, static_cast<int>(CREATED)}).size(), 1u);
}

TEST_F(RestQuery, CommitChangeResolvesReferenceOnlyPreviousCommit) {
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    auto package = makePackage("x");
    SysMLv2::API::ProjectVersioningService service;
    auto branch = std::make_shared<Branch>("main");
    // the stored previous commit holds the change
    auto previous = service.createCommit(std::make_shared<DataVersion>(package), branch, project);

    // a reference to it, as read from JSON: only the id is known
    auto reference = std::make_shared<Commit>(json{{"@id", boost::uuids::to_string(previous->getId())}}.dump());
    ASSERT_TRUE(reference->getChange().empty());
    auto commit = std::make_shared<Commit>("next", project, std::vector<std::shared_ptr<Commit>>{reference});
    commit->addChange(std::make_shared<DataVersion>(package));
    EXPECT_EQ(service.getCommitChange(project, commit, {static_cast<int>(UPDATED)}).size(), 1u);
    EXPECT_TRUE(service.getCommitChange(project, commit, {static_cast<int>(CREATED)}).empty());

    // an unknown reference counts as "nothing existed"
    auto unknown = std::make_shared<Commit>(json{{"@id", DataId}}.dump());
    auto other = std::make_shared<Commit>("other", project, std::vector<std::shared_ptr<Commit>>{unknown});
    other->addChange(std::make_shared<DataVersion>(package));
    EXPECT_EQ(service.getCommitChange(project, other, {static_cast<int>(CREATED)}).size(), 1u);
}

TEST_F(RestQuery, QueryRejectsWrongType) {
    json bad = annexBQuery();
    bad["@type"] = "Commit";
    try {
        Query broken(bad.dump());
        FAIL() << "expected an exception";
    } catch (const std::invalid_argument& ex) {
        EXPECT_NE(std::string(ex.what()).find("Query:"), std::string::npos);
    }
    bad["@type"] = nullptr;
    EXPECT_NO_THROW(Query(bad.dump()));
    bad.erase("@type");
    EXPECT_NO_THROW(Query(bad.dump()));
}
