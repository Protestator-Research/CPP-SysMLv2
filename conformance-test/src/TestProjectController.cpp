#include <gtest/gtest.h>
#include <sysmlv2/service/implementation/ProjectService.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/Branch.h>

void createTestInstance(SysMLv2::API::ProjectService* projectService) {
    projectService->createProject("Test Project 1", "Description of the Test Project 1");
    projectService->createProject("Test Project 2", "Description of the Test Project 2");
    projectService->createProject("Test Project 3", "Description of the Test Project 3");
    projectService->createProject("Test Project 4", "Description of the Test Project 4");
    projectService->createProject("Test Project 5", "Description of the Test Project 5");
}

TEST(ProjectConformanceTest, CreateProjectSucess) {
    SysMLv2::API::ProjectService* projectService = new SysMLv2::API::ProjectService();
    std::string projectName = "TestName";
    std::string description = "Description of the test Project";
    auto project = projectService->createProject(projectName, description);
    EXPECT_FALSE(project == nullptr);
    EXPECT_EQ(project->getName(), projectName);
    EXPECT_EQ(projectService->getProjects().size(), 1);
    EXPECT_FALSE(project->getDefaultBranch()== nullptr);
    EXPECT_EQ(project->getDefaultBranch()->getName(), "main");
    EXPECT_EQ(project->getDescription(), description);
}

TEST(ProjectConformanceTest, GetProjects) {
    SysMLv2::API::ProjectService* projectService = new SysMLv2::API::ProjectService();
    createTestInstance(projectService);
    EXPECT_EQ(projectService->getProjects().size(), 5);
}

TEST(ProjectConformanceTest, GetProjectsWithId) {
    SysMLv2::API::ProjectService* projectService = new SysMLv2::API::ProjectService();
    createTestInstance(projectService);
    for(const auto& project : projectService->getProjects()) {
        EXPECT_EQ(projectService->getProjectById(project->getId())->getId(),project->getId());
    }
}

#include <sysmlv2/service/implementation/InstanceManager.h>
#include <kerml/root/namespaces/Namespace.h>
#include <kerml/root/namespaces/OwningMembership.h>
#include <kerml/root/elements/Element.h>

// The tests of the InstanceManager run for both formats of the standard library (text and XMI).
class InstanceManagerTest : public ::testing::TestWithParam<SysMLv2::API::StandardLibraryFormat> {
protected:
    void configure(SysMLv2::API::InstanceManager& manager, bool reuse = false) const {
        manager.setStandardLibraryFormat(GetParam());
        manager.setReuseStandardLibrary(reuse);
    }
};

TEST_P(InstanceManagerTest, RootNamespaceCreationAndLookup) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    std::string model = "package VehiclePackage { part def Car; }";

    manager.parseModel(model);

    auto rootNs = manager.getRootNamespace();
    ASSERT_NE(rootNs, nullptr);

    EXPECT_FALSE(rootNs->ownedMember().empty());

    auto vehiclePkg = manager.findElementWithQualifiedName("VehiclePackage");
    ASSERT_NE(vehiclePkg, nullptr);
    EXPECT_EQ(vehiclePkg->declaredName().value_or(""), "VehiclePackage");
    EXPECT_EQ(vehiclePkg->owner(), rootNs);
    EXPECT_NE(vehiclePkg->owningMembership(), nullptr);

    auto car = manager.findElementWithQualifiedName("VehiclePackage::Car");
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->declaredName().value_or(""), "Car");
    EXPECT_EQ(car->owner(), vehiclePkg);
}


// ---------------------------------------------------------------------------------------------------------------------
// InstanceManager on top of SysMLv2::Files::Workspace: standard library on demand, user libraries, errors, qualified names.
// ---------------------------------------------------------------------------------------------------------------------
#include <sysmlv2/ParserError.h>
#include <sysmlv2/resolution/ResolutionData.h>
#include <kerml/core/features/Feature.h>
#include <kerml/core/types/Specialization.h>
#include <kerml/core/types/Type.h>
#include <kerml/root/elements/Relationship.h>
#include <algorithm>
#include <string>

namespace {
    bool mentions(const std::vector<std::shared_ptr<SysMLv2::Files::ParserError>>& errors, const std::string& text) {
        return std::any_of(errors.begin(), errors.end(), [&text](const std::shared_ptr<SysMLv2::Files::ParserError>& error) {
            return error->description().find(text) != std::string::npos;
        });
    }
}

TEST_P(InstanceManagerTest, StandardLibraryImportResolvesToLibraryElement) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package P { private import ScalarValues::*; part def A { attribute x : Real; } }");

    EXPECT_TRUE(manager.getParserErrors().empty());
    // No reference of the model is unresolved: in particular not `ScalarValues` and not `Real`.
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    EXPECT_FALSE(mentions(manager.getUnresolvedReferences(), "Real"));

    auto real = manager.findElementWithQualifiedName("ScalarValues::Real");
    ASSERT_NE(real, nullptr);
    EXPECT_FALSE(SysMLv2::Files::isUnresolved(real));

    auto x = std::dynamic_pointer_cast<KerML::Entities::Feature>(manager.findElementWithQualifiedName("P::A::x"));
    ASSERT_NE(x, nullptr);
    ASSERT_EQ(x->type().size(), 1u);
    EXPECT_EQ(x->type().front(), real);
    EXPECT_FALSE(SysMLv2::Files::isUnresolved(x->type().front()));

    // The library element is owned by its own source: ScalarValues owns Real.
    ASSERT_NE(real->owner(), nullptr);
    EXPECT_EQ(real->owner(), manager.findElementWithQualifiedName("ScalarValues"));
    // The elements of the standard library are part of getElements() but not of the model elements.
    const auto all = manager.getElements();
    const auto modelOnly = manager.getModelElements();
    EXPECT_NE(std::find(all.begin(), all.end(), real), all.end());
    EXPECT_EQ(std::find(modelOnly.begin(), modelOnly.end(), real), modelOnly.end());
    EXPECT_LT(modelOnly.size(), all.size());
}

TEST_P(InstanceManagerTest, StandardLibraryIsLoadedOnDemandOnly) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package P { attribute def A; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    // An attribute definition needs Attributes::AttributeValue (implicit generalization), nothing of the domain libraries.
    EXPECT_NE(manager.findElementWithQualifiedName("Attributes::AttributeValue"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("ISQ"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("Requirements"), nullptr);
}

TEST_P(InstanceManagerTest, ImportedLibraryFilesFollowTheirOwnImports) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    // Parts.sysml imports Items, Ports, ... and Base; qualified names without an import are found through the workspace too.
    manager.parseModel("package P { part def Car; part car : Car; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    EXPECT_NE(manager.findElementWithQualifiedName("Parts::Part"), nullptr);
    EXPECT_NE(manager.findElementWithQualifiedName("Items::Item"), nullptr);
    EXPECT_NE(manager.findElementWithQualifiedName("Base::Anything"), nullptr);
}

TEST_P(InstanceManagerTest, NonStandardLibraryIsImportedAndSpecialized) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.appendNonStandardLibrary("package VehicleLibrary { private import ScalarValues::*; attribute def Vehicle { attribute mass : Real; } }");
    manager.parseModel("package Fleet { private import VehicleLibrary::*; attribute def Truck :> Vehicle; }");

    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());

    auto vehicle = manager.findElementWithQualifiedName("VehicleLibrary::Vehicle");
    ASSERT_NE(vehicle, nullptr);
    auto truck = std::dynamic_pointer_cast<KerML::Entities::Type>(manager.findElementWithQualifiedName("Fleet::Truck"));
    ASSERT_NE(truck, nullptr);
    ASSERT_EQ(truck->ownedSpecialization().size(), 1u);
    EXPECT_EQ(truck->ownedSpecialization().front()->general(), vehicle);

    // The library is a source of its own: its root namespace is not the root namespace of the instance model.
    auto rootNs = manager.getRootNamespace();
    ASSERT_NE(rootNs, nullptr);
    EXPECT_EQ(truck->owner()->owner(), rootNs);
    EXPECT_NE(vehicle->owner()->owner(), rootNs);
    // Elements of the instance model are found among the model elements, those of the library as well (non-standard library).
    const auto modelOnly = manager.getModelElements();
    EXPECT_NE(std::find(modelOnly.begin(), modelOnly.end(), vehicle), modelOnly.end());
    EXPECT_EQ(manager.findAllElementsWithDeclaredName("Vehicle").size(), 1u);
}

TEST_P(InstanceManagerTest, NonStandardLibraryAppendedAfterTheModelIsPickedUp) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package Fleet { private import VehicleLibrary::*; attribute def Truck :> Vehicle; }");
    // The library is missing: the references are reported as warnings, not as errors.
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_FALSE(manager.getUnresolvedReferences().empty());
    EXPECT_TRUE(mentions(manager.getUnresolvedReferences(), "VehicleLibrary"));
    for (const auto& warning : manager.getUnresolvedReferences())
        EXPECT_EQ(warning->errorType(), SysMLv2::Files::ErrorType::WARNING);

    manager.appendNonStandardLibrary("package VehicleLibrary { attribute def Vehicle; }");
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    EXPECT_NE(manager.findElementWithQualifiedName("VehicleLibrary::Vehicle"), nullptr);
}

TEST_P(InstanceManagerTest, UnresolvedReferencesAreWarningsWithPosition) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package P {\n    attribute def A :> Missing;\n}");

    EXPECT_TRUE(manager.getParserErrors().empty());
    const auto unresolved = manager.getUnresolvedReferences();
    ASSERT_EQ(unresolved.size(), 1u);
    EXPECT_EQ(unresolved.front()->errorType(), SysMLv2::Files::ErrorType::WARNING);
    EXPECT_NE(unresolved.front()->description().find("Missing"), std::string::npos);
    EXPECT_EQ(unresolved.front()->getLine(), 2);
    EXPECT_EQ(unresolved.front()->getSource(), "InstanceModel");
}

TEST_P(InstanceManagerTest, SyntaxErrorsOfModelAndLibrariesAreReported) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package P { attribute def ; ");
    ASSERT_FALSE(manager.getParserErrors().empty());
    for (const auto& error : manager.getParserErrors()) {
        EXPECT_EQ(error->errorType(), SysMLv2::Files::ErrorType::SYNTAX_ERROR);
        EXPECT_EQ(error->getSource(), "InstanceModel");
    }
    // The rest of the model is still available and there is a root namespace.
    EXPECT_NE(manager.getRootNamespace(), nullptr);

    manager.parseModel("package P { attribute def A; }");
    EXPECT_TRUE(manager.getParserErrors().empty());

    manager.appendNonStandardLibrary("package Broken { attribute def ; ");
    ASSERT_FALSE(manager.getParserErrors().empty());
    for (const auto& error : manager.getParserErrors())
        EXPECT_EQ(error->getSource(), "NonStandardLibrary1");
}

TEST_P(InstanceManagerTest, QualifiedNamesOfNestedElements) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package Outer { package Inner { attribute def Leaf { attribute weight; } } alias Short for Inner::Leaf; }");
    EXPECT_TRUE(manager.getParserErrors().empty());

    auto outer = manager.findElementWithQualifiedName("Outer");
    auto inner = manager.findElementWithQualifiedName("Outer::Inner");
    auto leaf = manager.findElementWithQualifiedName("Outer::Inner::Leaf");
    auto weight = manager.findElementWithQualifiedName("Outer::Inner::Leaf::weight");
    ASSERT_NE(outer, nullptr);
    ASSERT_NE(inner, nullptr);
    ASSERT_NE(leaf, nullptr);
    ASSERT_NE(weight, nullptr);
    EXPECT_EQ(inner->owner(), outer);
    EXPECT_EQ(leaf->owner(), inner);
    EXPECT_EQ(weight->owner(), leaf);
    EXPECT_NE(leaf->owningMembership(), nullptr);
    EXPECT_EQ(leaf->qualifiedName().value_or(""), "Outer::Inner::Leaf");
    EXPECT_EQ(weight->qualifiedName().value_or(""), "Outer::Inner::Leaf::weight");
    EXPECT_EQ(outer->owner(), manager.getRootNamespace());

    // An alias is resolved by the workspace's scoped lookup.
    EXPECT_EQ(manager.findElementWithQualifiedName("Outer::Short"), leaf);

    EXPECT_EQ(manager.findElementWithQualifiedName("Outer::Inner::Missing"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("Inner"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName(""), nullptr);

    // By declared name and by id.
    const auto leaves = manager.findAllElementsWithDeclaredName("Leaf");
    ASSERT_EQ(leaves.size(), 1u);
    EXPECT_EQ(leaves.front(), leaf);
    EXPECT_EQ(manager.findElementWithId(leaf->getId()), leaf);
    EXPECT_EQ(manager.findElementWithId(boost::uuids::uuid{}), nullptr);
}

TEST_P(InstanceManagerTest, QualifiedNamesAreWrittenWithEscapedNamesAndEffectiveNames) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package 'my pkg' { part 'a b'; part def A { part p; } part def B :> A { part :>> p; } attribute '!=' ; attribute 'a\\tb'; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    std::set<std::string> names;
    for (const auto& element : manager.getModelElements()) {
        if (element->qualifiedName().has_value()) names.insert(element->qualifiedName().value());
    }
    // (the names are stored without quotes and written with them where the notation needs them; `:>> p` is known as p)
    for (const char* expected : {"'my pkg'", "'my pkg'::'a b'", "'my pkg'::'!='", "'my pkg'::'a\\tb'", "'my pkg'::B::p", "'my pkg'::A::p"}) {
        EXPECT_EQ(names.count(expected), 1u) << expected;
    }
    EXPECT_EQ(manager.findAllElementsWithDeclaredName("a b").size(), 1u);
    EXPECT_EQ(manager.findAllElementsWithDeclaredName("a\tb").size(), 1u);
    size_t declaredP = 0;
    for (const auto& element : manager.getModelElements()) {
        if (element->declaredName().value_or("") == "p") ++declaredP;
    }
    EXPECT_EQ(declaredP, 1u);   // (only A::p has the declared name p)
}

TEST_P(InstanceManagerTest, ReservedWordsAreQuotedInQualifiedNames) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package P { import BooleanFunctions::*; import DataFunctions::*; import ControlFunctions::*; part 'action'; attribute 'in' ; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    // (the names of the elements are the plain words; the qualified names write them as the notation requires: a reserved word is no basic name)
    for (const char* expected : {"BooleanFunctions::'not'", "DataFunctions::'xor'", "ControlFunctions::'if'", "P::'action'", "P::'in'"}) {
        const auto found = manager.findElementWithQualifiedName(expected);
        ASSERT_NE(found, nullptr) << expected;
        EXPECT_EQ(found->qualifiedName().value_or(""), expected);
    }
}

TEST_P(InstanceManagerTest, SecondParseModelGivesAFreshModel) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package First { attribute def A; }");
    auto firstRoot = manager.getRootNamespace();
    auto firstPackage = manager.findElementWithQualifiedName("First");
    ASSERT_NE(firstRoot, nullptr);
    ASSERT_NE(firstPackage, nullptr);
    const auto firstId = firstPackage->getId();

    manager.parseModel("package Second { attribute def B; }");
    auto secondRoot = manager.getRootNamespace();
    ASSERT_NE(secondRoot, nullptr);
    EXPECT_NE(secondRoot, firstRoot);
    EXPECT_EQ(manager.findElementWithQualifiedName("First"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("First::A"), nullptr);
    EXPECT_EQ(manager.findElementWithId(firstId), nullptr);
    EXPECT_TRUE(manager.findAllElementsWithDeclaredName("A").empty());
    auto second = manager.findElementWithQualifiedName("Second");
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second->owner(), secondRoot);
    ASSERT_EQ(secondRoot->ownedMember().size(), 1u);
    EXPECT_EQ(secondRoot->ownedMember().front(), second);

    // The same text again is a new set of elements as well.
    manager.parseModel("package Second { attribute def B; }");
    EXPECT_NE(manager.findElementWithQualifiedName("Second"), second);
    EXPECT_NE(manager.getRootNamespace(), secondRoot);
}

TEST_P(InstanceManagerTest, EmptyModelHasARootNamespace) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    EXPECT_EQ(manager.getRootNamespace(), nullptr);
    EXPECT_TRUE(manager.getElements().empty());
    EXPECT_EQ(manager.findElementWithQualifiedName("P"), nullptr);

    manager.parseModel("");
    EXPECT_TRUE(manager.getParserErrors().empty());
    ASSERT_NE(manager.getRootNamespace(), nullptr);
    EXPECT_TRUE(manager.getRootNamespace()->ownedMember().empty());
}

TEST_P(InstanceManagerTest, ModelPackageWithTheNameOfALibraryPackageIsNotReplaced) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel("package ScalarValues { attribute def Real; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    // Only the model's own package exists: no library ScalarValues is added next to it.
    EXPECT_EQ(manager.findAllElementsWithDeclaredName("ScalarValues").size(), 1u);
}

// ---------------------------------------------------------------------------------------------------------------------
// Lookup tables, the mode that keeps the standard library, the formats of the standard library.
// ---------------------------------------------------------------------------------------------------------------------
#include <map>
#include <algorithm>
#include "support/TestHelpers.h"
#include <set>

namespace {
    /// "<source>:<line>:<column>:<description>" of every warning: what two runs have to agree on.
    std::multiset<std::string> keysOf(const std::vector<std::shared_ptr<SysMLv2::Files::ParserError>>& errors) {
        std::multiset<std::string> keys;
        for (const auto& error : errors) {
            keys.insert(error->getSource() + ":" + std::to_string(error->getLine()) + ":" + std::to_string(error->getColumn()) + ":" + error->description());
        }
        return keys;
    }

    std::set<std::string> qualifiedNamesOf(const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements) {
        std::set<std::string> names;
        for (const auto& element : elements) {
            if (element && element->qualifiedName().has_value()) names.insert(element->qualifiedName().value());
        }
        return names;
    }

    const char* const FleetModel = "package Fleet { private import ScalarValues::*; part def Truck { attribute weight : Real; part axle : Axle[2]; } part def Axle; part truck : Truck; }";
    const char* const PlantModel = "package Plant { private import ScalarValues::*; private import Fleet::*; part def Crane :> Truck { attribute height : Real; } }";
}

TEST_P(InstanceManagerTest, LookupTablesAgreeWithTheElements) {
    SysMLv2::API::InstanceManager manager;
    configure(manager);
    manager.parseModel(FleetModel);
    ASSERT_TRUE(manager.getParserErrors().empty());

    const auto& elements = manager.getElements();
    ASSERT_GT(elements.size(), 100u);
    EXPECT_EQ(&manager.getElements(), &elements);  // (the getters return the member, not a copy)

    std::map<std::string, std::vector<KerML::Entities::Element*>> byName;
    std::set<std::string> qualified;
    for (const auto& element : elements) {
        ASSERT_NE(element, nullptr);
        EXPECT_EQ(manager.findElementWithId(element->getId()), element);
        if (element->declaredName().has_value()) byName[element->declaredName().value()].push_back(element.get());
        if (element->qualifiedName().has_value()) qualified.insert(element->qualifiedName().value());
    }
    for (const auto& [name, expected] : byName) {
        const auto found = manager.findAllElementsWithDeclaredName(name);
        ASSERT_EQ(found.size(), expected.size()) << name;
        size_t index = 0;
        for (const auto& element : found) EXPECT_EQ(element.get(), expected[index++]) << name;  // in the order of getElements()
    }
    for (const auto& name : qualified) {
        const auto found = manager.findElementWithQualifiedName(name);
        ASSERT_NE(found, nullptr) << name;
        // (the scoped lookup comes first: it finds a redefined or chained feature as the feature it stands for, so only the other elements
        // have to be found under their own name)
        if (!std::dynamic_pointer_cast<KerML::Entities::Feature>(found)) EXPECT_EQ(found->qualifiedName().value_or(""), name);
    }
    EXPECT_TRUE(manager.findAllElementsWithDeclaredName("NoSuchElement").empty());
    EXPECT_EQ(manager.findElementWithQualifiedName("Fleet::NoSuchElement"), nullptr);
    EXPECT_EQ(manager.findElementWithId(boost::uuids::uuid{}), nullptr);
}

TEST_P(InstanceManagerTest, ReuseModeKeepsTheStandardLibraryAndDropsTheOldModel) {
    SysMLv2::API::InstanceManager manager;
    configure(manager, true);
    manager.parseModel(FleetModel);
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    const auto real = manager.findElementWithQualifiedName("ScalarValues::Real");
    ASSERT_NE(real, nullptr);
    const auto truck = manager.findElementWithQualifiedName("Fleet::Truck");
    ASSERT_NE(truck, nullptr);
    const auto oldId = truck->getId();
    const auto oldRoot = manager.getRootNamespace();
    const size_t libraryElements = manager.getElements().size() - manager.getModelElements().size();

    manager.parseModel("package Garage { private import ScalarValues::*; part def Bay { attribute length : Real; } }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    // Nothing of the old model is left ...
    EXPECT_EQ(manager.findElementWithQualifiedName("Fleet"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("Fleet::Truck"), nullptr);
    EXPECT_EQ(manager.findElementWithId(oldId), nullptr);
    EXPECT_TRUE(manager.findAllElementsWithDeclaredName("Truck").empty());
    EXPECT_NE(manager.getRootNamespace(), oldRoot);
    for (const auto& element : manager.getElements()) EXPECT_NE(element, truck);
    // ... and the standard library is the one that was loaded before, not a new copy.
    EXPECT_EQ(manager.findElementWithQualifiedName("ScalarValues::Real"), real);
    EXPECT_EQ(manager.getElements().size() - manager.getModelElements().size(), libraryElements);
    const auto length = std::dynamic_pointer_cast<KerML::Entities::Feature>(manager.findElementWithQualifiedName("Garage::Bay::length"));
    ASSERT_NE(length, nullptr);
    ASSERT_EQ(length->type().size(), 1u);
    EXPECT_EQ(length->type().front(), real);
    ASSERT_NE(manager.findElementWithQualifiedName("Garage"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("Garage")->owner(), manager.getRootNamespace());
}

TEST_P(InstanceManagerTest, ReuseModeAddsLibrariesTheNextModelNeeds) {
    SysMLv2::API::InstanceManager manager;
    configure(manager, true);
    manager.parseModel("package A { attribute def X; }");
    EXPECT_NE(manager.findElementWithQualifiedName("Attributes::AttributeValue"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("Parts::Part"), nullptr);
    const auto value = manager.findElementWithQualifiedName("Attributes::AttributeValue");

    manager.parseModel("package B { part def Car; part car : Car; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    EXPECT_NE(manager.findElementWithQualifiedName("Parts::Part"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("Attributes::AttributeValue"), value);  // (stays loaded)
}

TEST_P(InstanceManagerTest, ReuseModeAppendsNonStandardLibraries) {
    SysMLv2::API::InstanceManager manager;
    configure(manager, true);
    manager.parseModel("package Fleet { private import VehicleLibrary::*; attribute def Truck :> Vehicle; }");
    EXPECT_FALSE(manager.getUnresolvedReferences().empty());
    EXPECT_TRUE(manager.getParserErrors().empty());

    manager.appendNonStandardLibrary("package VehicleLibrary { private import ScalarValues::*; attribute def Vehicle { attribute mass : Real; } }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    const auto vehicle = manager.findElementWithQualifiedName("VehicleLibrary::Vehicle");
    ASSERT_NE(vehicle, nullptr);
    const auto real = manager.findElementWithQualifiedName("ScalarValues::Real");
    ASSERT_NE(real, nullptr);
    const auto truck = std::dynamic_pointer_cast<KerML::Entities::Type>(manager.findElementWithQualifiedName("Fleet::Truck"));
    ASSERT_NE(truck, nullptr);
    ASSERT_EQ(truck->ownedSpecialization().size(), 1u);
    EXPECT_EQ(truck->ownedSpecialization().front()->general(), vehicle);
    const auto modelOnly = manager.getModelElements();
    EXPECT_NE(std::find(modelOnly.begin(), modelOnly.end(), vehicle), modelOnly.end());
    EXPECT_EQ(std::find(modelOnly.begin(), modelOnly.end(), real), modelOnly.end());

    // A second library, and then a new model: the libraries are parsed again with it and the standard library stays.
    manager.appendNonStandardLibrary("package Tools { attribute def Hammer; }");
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    EXPECT_EQ(manager.findElementWithQualifiedName("ScalarValues::Real"), real);
    manager.parseModel("package Fleet2 { private import VehicleLibrary::*; private import Tools::*; attribute def Truck2 :> Vehicle; attribute h : Hammer; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    EXPECT_EQ(manager.findElementWithQualifiedName("Fleet"), nullptr);
    EXPECT_NE(manager.findElementWithQualifiedName("Tools::Hammer"), nullptr);
    EXPECT_NE(manager.findElementWithQualifiedName("VehicleLibrary::Vehicle"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("ScalarValues::Real"), real);

    // The errors of a library are reported with the name of its source.
    manager.appendNonStandardLibrary("package Broken { attribute def ; ");
    ASSERT_FALSE(manager.getParserErrors().empty());
    for (const auto& error : manager.getParserErrors()) EXPECT_EQ(error->getSource(), "NonStandardLibrary3");
}

TEST_P(InstanceManagerTest, ReuseModeBuildsAnewForAPackageWithTheNameOfALoadedLibraryPackage) {
    SysMLv2::API::InstanceManager manager;
    configure(manager, true);
    manager.parseModel("package P { private import ScalarValues::*; attribute def A { attribute x : Real; } }");
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    EXPECT_EQ(manager.findAllElementsWithDeclaredName("ScalarValues").size(), 1u);
    const auto library = manager.findElementWithQualifiedName("ScalarValues");

    manager.parseModel("package ScalarValues { attribute def Real; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    // Only the package of the model exists: the one of the library is not loaded next to it.
    EXPECT_EQ(manager.findAllElementsWithDeclaredName("ScalarValues").size(), 1u);
    EXPECT_NE(manager.findElementWithQualifiedName("ScalarValues"), library);
    EXPECT_EQ(manager.getModelElements().size() > 0, true);

    // A non-standard library does the same.
    manager.parseModel("package P { private import ScalarValues::*; attribute def A { attribute x : Real; } }");
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    manager.appendNonStandardLibrary("package ScalarValues { attribute def Real; }");
    EXPECT_EQ(manager.findAllElementsWithDeclaredName("ScalarValues").size(), 1u);
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
}

TEST_P(InstanceManagerTest, ReuseModeGivesTheResultOfTheDefaultMode) {
    SysMLv2::API::InstanceManager plain;
    configure(plain, false);
    SysMLv2::API::InstanceManager reuse;
    configure(reuse, true);

    const auto expectEqual = [&](const std::string& step) {
        EXPECT_EQ(keysOf(reuse.getParserErrors()), keysOf(plain.getParserErrors())) << step;
        EXPECT_EQ(keysOf(reuse.getUnresolvedReferences()), keysOf(plain.getUnresolvedReferences())) << step;
        EXPECT_EQ(reuse.getModelElements().size(), plain.getModelElements().size()) << step;
        EXPECT_EQ(qualifiedNamesOf(reuse.getModelElements()), qualifiedNamesOf(plain.getModelElements())) << step;
        ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(reuse.getModelElements()), ConformanceTest::resolvedGenerals(plain.getModelElements()), step);
        // (what the plain mode resolved in the library, the reuse mode resolved the same way)
        const auto reuseLibrary = ConformanceTest::resolvedGenerals(reuse.getElements());
        const auto plainLibrary = ConformanceTest::resolvedGenerals(plain.getElements());
        EXPECT_TRUE(std::includes(reuseLibrary.begin(), reuseLibrary.end(), plainLibrary.begin(), plainLibrary.end())) << step;
        // (the reuse mode keeps the libraries of the earlier models: at least what the plain mode loaded)
        const auto reuseNames = qualifiedNamesOf(reuse.getElements());
        for (const auto& name : qualifiedNamesOf(plain.getElements())) EXPECT_EQ(reuseNames.count(name), 1u) << step << ": " << name;
    };
    const auto both = [&](auto&& action, const std::string& step) {
        action(plain);
        action(reuse);
        expectEqual(step);
    };

    both([](SysMLv2::API::InstanceManager& m) { m.parseModel(FleetModel); }, "Fleet");
    both([](SysMLv2::API::InstanceManager& m) { m.parseModel(PlantModel); }, "Plant without its library");
    both([](SysMLv2::API::InstanceManager& m) { m.appendNonStandardLibrary(FleetModel); }, "library appended");
    both([](SysMLv2::API::InstanceManager& m) { m.parseModel("package Q { part def P; part p : P; port q; action a; }"); }, "Q");
    both([](SysMLv2::API::InstanceManager& m) { m.parseModel("package Q { attribute def ; "); }, "syntax error");
    both([](SysMLv2::API::InstanceManager& m) { m.parseModel("package Q { attribute def A :> Missing; }"); }, "unresolved");
    both([](SysMLv2::API::InstanceManager& m) { m.appendNonStandardLibrary("package Late { part def L; }"); }, "second library");
    both([](SysMLv2::API::InstanceManager& m) { m.parseModel(""); }, "empty");
}

TEST_P(InstanceManagerTest, ChangingTheModeBuildsTheWorkspaceAnew) {
    SysMLv2::API::InstanceManager manager;
    configure(manager, false);
    manager.parseModel(FleetModel);
    const auto first = manager.findElementWithQualifiedName("Fleet");
    manager.setReuseStandardLibrary(true);
    EXPECT_TRUE(manager.reuseStandardLibrary());
    manager.parseModel(FleetModel);
    EXPECT_NE(manager.findElementWithQualifiedName("Fleet"), first);
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    manager.setReuseStandardLibrary(false);
    manager.parseModel(PlantModel);
    EXPECT_FALSE(manager.getUnresolvedReferences().empty());  // (Fleet is not defined: the reference of the import)
}

#include "support/TestHelpers.h"

#ifndef CONFORMANCE_SYSML_VALID_DIR
#error "CONFORMANCE_SYSML_VALID_DIR must be defined by CMake to the testdata/syntax/sysml/valid path"
#endif

// The standard library in the XMI format has to leave the same references of the models unresolved as the text format. (Both managers keep
// the standard library between the models, so that the 47 models do not load it again each: that mode is checked against the default one above.)
TEST(InstanceManagerFormats, TextAndXmiLeaveTheSameReferencesUnresolved) {
    SysMLv2::API::InstanceManager text;
    text.setStandardLibraryFormat(SysMLv2::API::StandardLibraryFormat::Text);
    text.setReuseStandardLibrary(true);
    SysMLv2::API::InstanceManager xmi;
    xmi.setReuseStandardLibrary(true);
    xmi.setStandardLibraryFormat(SysMLv2::API::StandardLibraryFormat::Xmi);

    const auto files = ConformanceTest::listFiles(CONFORMANCE_SYSML_VALID_DIR, {".sysml"});
    ASSERT_GT(files.size(), 20u);
    size_t unresolved = 0;
    for (const auto& file : files) {
        const std::string content = ConformanceTest::readFile(file);
        text.parseModel(content);
        xmi.parseModel(content);
        const std::string name = file.filename().string();
        EXPECT_EQ(keysOf(xmi.getParserErrors()), keysOf(text.getParserErrors())) << name;
        EXPECT_EQ(keysOf(xmi.getUnresolvedReferences()), keysOf(text.getUnresolvedReferences())) << name;
        EXPECT_EQ(xmi.getModelElements().size(), text.getModelElements().size()) << name;
        EXPECT_EQ(qualifiedNamesOf(xmi.getModelElements()), qualifiedNamesOf(text.getModelElements())) << name;
        ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(xmi.getModelElements()), ConformanceTest::resolvedGenerals(text.getModelElements()), name);
        unresolved += text.getUnresolvedReferences().size();
    }
    RecordProperty("models", std::to_string(files.size()));
    RecordProperty("unresolved_references", std::to_string(unresolved));
}

// The qualified names (assignQualifiedNames) of ALL elements of the two formats, the library ones included, agree for every one of the valid
// models: as multisets of "<qualified name> <metaclass>". Both managers keep the standard library between the models (reuse mode, as above),
// so the elements of a model are the elements of the library packages it needs plus its own.
namespace {
using ElementList = std::vector<std::shared_ptr<KerML::Entities::Element>>;

/// The category of a differing "<qualified name> <metaclass>": the metaclass, or "<metaclass> (chain)" for an element named after the text of a
/// feature chain (`a.b` is a quoted name with a dot: the XMI has an anonymous Feature with FeatureChainings there).
std::string categoryOf(const std::string& key) {
    const std::string metaclass = key.substr(key.rfind(' ') + 1);
    const std::string qualified = key.substr(0, key.rfind(' '));
    const size_t last = qualified.rfind("::");
    const std::string segment = last == std::string::npos ? qualified : qualified.substr(last + 2);
    if (segment.size() > 2 && segment.front() == '\'' && segment.find('.') != std::string::npos) return metaclass + " (chain)";
    return metaclass;
}

std::map<std::string, size_t> qualifiedNameCounts(const ElementList& elements) {
    std::map<std::string, size_t> counts;
    for (const auto& element : elements) {
        if (element && element->qualifiedName().has_value()) ++counts[element->qualifiedName().value() + " " + element->getType()];
    }
    return counts;
}

/// The differences that the two formats are allowed to have: exactly "<qualified name> <metaclass>", the reason. Keep it as short as possible and
/// never list a difference in the name of a named element that both formats have (that is a bug): these are elements that only the XMI library has.
const std::map<std::string, std::string>& allowedQualifiedNameDifferences() {
    static const std::map<std::string, std::string> allowed = {
        // KNOWN GAP of the text parser, not a difference the specification allows: the text listener does not create the ParameterMemberships of a
        // TransitionUsage (the source parameter and the payload parameter that the grammar produces from EmptyParameterMember). The XMI of the library
        // has them: next to the unnamed source parameter a ReferenceUsage named like the payload, apart from the payload parameter of the
        // AcceptActionUsage itself. So Actions::AcceptAction::aState::aTransition::apayload has two ReferenceUsages in the XMI and one in the text.
        {"Actions::AcceptAction::aState::aTransition::apayload ReferenceUsage", "payload parameter of the TransitionUsage (not created by the text parser)"},
    };
    return allowed;
}
}

TEST(InstanceManagerFormats, TextAndXmiAssignTheSameQualifiedNamesToAllElements) {
    SysMLv2::API::InstanceManager text;
    text.setStandardLibraryFormat(SysMLv2::API::StandardLibraryFormat::Text);
    text.setReuseStandardLibrary(true);
    SysMLv2::API::InstanceManager xmi;
    xmi.setReuseStandardLibrary(true);
    xmi.setStandardLibraryFormat(SysMLv2::API::StandardLibraryFormat::Xmi);

    const auto files = ConformanceTest::listFiles(CONFORMANCE_SYSML_VALID_DIR, {".sysml"});
    ASSERT_GT(files.size(), 20u);
    // names that are looked up in every model besides the declared names of the model itself
    const std::vector<std::string> libraryNames = {"Anything", "!=", "length", "Real", "Integer", "p", "self", "Parts", "Part", "elements", "mRef", "ISQ", "x", "result"};

    std::map<std::string, size_t> allowedSeen;          // allowed difference -> number of models in which the key occurred
    std::map<std::string, size_t> categories;           // metaclass -> number of differing elements
    std::map<std::string, std::string> examples;        // metaclass -> an example
    size_t elementsCompared = 0;
    size_t nameLookups = 0;
    for (const auto& file : files) {
        const std::string content = ConformanceTest::readFile(file);
        text.parseModel(content);
        xmi.parseModel(content);
        const std::string name = file.filename().string();
        SCOPED_TRACE(name);
        EXPECT_EQ(keysOf(xmi.getParserErrors()), keysOf(text.getParserErrors()));
        EXPECT_EQ(keysOf(xmi.getUnresolvedReferences()), keysOf(text.getUnresolvedReferences()));

        const auto textCounts = qualifiedNameCounts(text.getElements());
        const auto xmiCounts = qualifiedNameCounts(xmi.getElements());
        elementsCompared += text.getElements().size();
        for (const auto& [key, count] : textCounts) {
            if (allowedQualifiedNameDifferences().count(key) != 0) {
                ++allowedSeen[key];
                continue;
            }
            const auto other = xmiCounts.find(key);
            const size_t otherCount = other == xmiCounts.end() ? 0 : other->second;
            if (otherCount == count) continue;
            const std::string metaclass = categoryOf(key);
            categories[metaclass] += count > otherCount ? count - otherCount : otherCount - count;
            if (examples.count(metaclass) == 0) examples[metaclass] = name + ": " + key + " text=" + std::to_string(count) + " xmi=" + std::to_string(otherCount);
        }
        for (const auto& [key, count] : xmiCounts) {
            if (textCounts.count(key) != 0 || allowedQualifiedNameDifferences().count(key) != 0) continue;
            const std::string metaclass = categoryOf(key);
            categories[metaclass] += count;
            if (examples.count(metaclass) == 0) examples[metaclass] = name + ": " + key + " text=0 xmi=" + std::to_string(count);
        }

        // findAllElementsWithDeclaredName: the declared names of the model and some names of the library
        std::set<std::string> names(libraryNames.begin(), libraryNames.end());
        for (const auto& element : text.getModelElements()) {
            if (element->declaredName().has_value()) names.insert(element->declaredName().value());
        }
        for (const auto& declared : names) {
            const auto describe = [&declared](SysMLv2::API::InstanceManager& manager) {
                std::multiset<std::string> found;
                for (const auto& element : manager.findAllElementsWithDeclaredName(declared)) {
                    const std::string key = element->qualifiedName().value_or("") + " " + element->getType();
                    if (allowedQualifiedNameDifferences().count(key) == 0) found.insert(key);
                }
                return found;
            };
            EXPECT_EQ(describe(xmi), describe(text)) << "findAllElementsWithDeclaredName(" << declared << ")";
            ++nameLookups;
        }
    }
    size_t total = 0;
    for (const auto& [metaclass, count] : categories) {
        std::cout << "[  DIFF  ] " << metaclass << ": " << count << "  e.g. " << examples[metaclass] << std::endl;
        total += count;
        ADD_FAILURE() << "not allowed: " << metaclass << " (" << count << "), e.g. " << examples[metaclass];
    }
    // (an entry of the list that no model needs any more is removed)
    for (const auto& [key, reason] : allowedQualifiedNameDifferences()) EXPECT_EQ(allowedSeen[key], files.size()) << key << ": " << reason;
    std::cout << "[  INFO  ] " << files.size() << " models, " << elementsCompared << " elements compared, " << nameLookups << " name lookups, " << total
              << " differing qualified names" << std::endl;
}

TEST_P(InstanceManagerTest, AnonymousRedefinitionBindsToTheRedefinedFeatureOfTheGeneral) {
    // ISQBase: `LengthValue :> ScalarQuantityValue { attribute :>> mRef ...; }` redefines mRef without a name of its own, so it is known as
    // `mRef` in LengthValue, and the `:>> mRef` of a specialization of LengthValue redefines that one, not the mRef of the general types.
    const char* model = "package P { private import ISQBase::*; attribute def MyLen :> LengthValue { attribute :>> mRef; } }";
    for (const bool reuse : {false, true}) {
        SysMLv2::API::InstanceManager manager;
        configure(manager, reuse);
        if (reuse) manager.parseModel("package First { attribute def A; }");  // (the next model is not the first one of the manager)
        manager.parseModel(model);
        EXPECT_TRUE(manager.getParserErrors().empty()) << reuse;
        EXPECT_TRUE(manager.getUnresolvedReferences().empty()) << reuse;

        const auto lengthValue = manager.findElementWithQualifiedName("ISQBase::LengthValue");
        const auto myLen = manager.findElementWithQualifiedName("P::MyLen");
        ASSERT_NE(lengthValue, nullptr) << reuse;
        ASSERT_NE(myLen, nullptr) << reuse;
        std::shared_ptr<KerML::Entities::Element> redefined;
        for (const auto& element : manager.getModelElements()) {
            const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(element);
            if (!feature || feature->declaredName().has_value() || feature->owner() != myLen) continue;
            for (const auto& specialization : feature->ownedSpecialization()) redefined = specialization->general();
        }
        ASSERT_NE(redefined, nullptr) << reuse;
        EXPECT_EQ(redefined->owner(), lengthValue) << reuse << ": bound to " << ConformanceTest::qualifiedNameOf(redefined);
    }
}

INSTANTIATE_TEST_SUITE_P(StandardLibraryFormats, InstanceManagerTest, ::testing::Values(SysMLv2::API::StandardLibraryFormat::Text, SysMLv2::API::StandardLibraryFormat::Xmi),
    [](const ::testing::TestParamInfo<SysMLv2::API::StandardLibraryFormat>& info) {
        return info.param == SysMLv2::API::StandardLibraryFormat::Text ? "Text" : "Xmi";
    });

TEST(InstanceManagerFormats, DefaultsAreTheXmiLibraryAndANewWorkspaceForEveryModel) {
    SysMLv2::API::InstanceManager manager;
    EXPECT_EQ(manager.standardLibraryFormat(), SysMLv2::API::StandardLibraryFormat::Xmi);
    EXPECT_FALSE(manager.reuseStandardLibrary());
}

// Finding C: with the XMI library, a model that defines a package with the name of a standard library package is processed with the text
// (the id based XMI files cannot bind to it by name): the same references stay unresolved, in the model and in the library, and the same errors.
TEST(InstanceManagerFormats, AModelThatDefinesAStandardPackageGivesTheSameResultInBothFormats) {
    const std::vector<std::string> models = {
        "package Base { part def Mine; }\npackage Other { import Base::*; part m : Mine; part q : ScalarValues::Real; }",
        "package ScalarValues { attribute def Real; } package U { import ScalarValues::*; attribute r : Real; attribute x : Missing; }",
    };
    for (const bool reuse : {false, true}) {
        SysMLv2::API::InstanceManager text;
        text.setStandardLibraryFormat(SysMLv2::API::StandardLibraryFormat::Text);
        text.setReuseStandardLibrary(reuse);
        SysMLv2::API::InstanceManager xmi;
        xmi.setStandardLibraryFormat(SysMLv2::API::StandardLibraryFormat::Xmi);
        xmi.setReuseStandardLibrary(reuse);
        EXPECT_EQ(xmi.standardLibraryFormat(), SysMLv2::API::StandardLibraryFormat::Xmi);

        // (in the reuse mode: a model of the XMI kind, then models that need the text, then the XMI kind again, and a library appended)
        std::vector<std::string> steps;
        if (reuse) steps.push_back("package Plain { part def A; part a : A; }");
        for (const auto& model : models) steps.push_back(model);
        if (reuse) steps.push_back("package Plain2 { part def B; port p; }");
        // (the first and the last model define no package of the library: the XMI manager reads the XMI files there, so only what the
        // model got has to agree; for the others it has the text, and everything of the library has to agree as well)
        const auto plain = [&](size_t step) { return reuse && (step == 0 || step + 1 == steps.size()); };
        for (size_t step = 0; step < steps.size(); ++step) {
            const std::string what = std::string(reuse ? "reuse" : "plain") + ", step " + std::to_string(step);
            text.parseModel(steps[step]);
            xmi.parseModel(steps[step]);
            EXPECT_EQ(xmi.standardLibraryFormat(), SysMLv2::API::StandardLibraryFormat::Xmi) << what;   // (the configured format stays)
            EXPECT_EQ(xmi.getParserErrors().size(), text.getParserErrors().size()) << what;
            EXPECT_EQ(keysOf(xmi.getParserErrors()), keysOf(text.getParserErrors())) << what;
            EXPECT_EQ(keysOf(xmi.getUnresolvedReferences()), keysOf(text.getUnresolvedReferences())) << what;
            EXPECT_EQ(qualifiedNamesOf(xmi.getModelElements()), qualifiedNamesOf(text.getModelElements())) << what;
            ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(xmi.getModelElements()), ConformanceTest::resolvedGenerals(text.getModelElements()), what);
            if (plain(step)) continue;
            // (the library sources: what their references bound to, and which of them stay unresolved, is part of these lines)
            ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(xmi.getElements()), ConformanceTest::resolvedGenerals(text.getElements()), what);
            EXPECT_EQ(qualifiedNamesOf(xmi.getElements()), qualifiedNamesOf(text.getElements())) << what;
        }
        if (!reuse) continue;
        text.appendNonStandardLibrary("package Base { part def FromLibrary; }");
        xmi.appendNonStandardLibrary("package Base { part def FromLibrary; }");
        EXPECT_EQ(keysOf(xmi.getUnresolvedReferences()), keysOf(text.getUnresolvedReferences())) << reuse;
        ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(xmi.getElements()), ConformanceTest::resolvedGenerals(text.getElements()), "library appended");
    }
}

// Finding D: only a name that starts with no quote and whose part before the # is an XMI file is an href. A name that contains a # in
// quotes is a name: the library package it starts with is still loaded.
TEST(InstanceManagerFormats, ANameWithAHashInQuotesIsLoadedByItsFirstSegment) {
    for (const auto format : {SysMLv2::API::StandardLibraryFormat::Text, SysMLv2::API::StandardLibraryFormat::Xmi}) {
        SysMLv2::API::InstanceManager manager;
        manager.setStandardLibraryFormat(format);
        manager.parseModel("package P { import ScalarValues::*; part x : Missing::'a#b'; part y : ScalarValues::'c#d'; attribute r : Real; }");
        EXPECT_NE(manager.findElementWithQualifiedName("ScalarValues::Real"), nullptr);
        const auto unresolved = keysOf(manager.getUnresolvedReferences());
        EXPECT_EQ(unresolved.size(), 2u);   // (the two names with a # in quotes: neither exists)
    }
}
