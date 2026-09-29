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

TEST(InstanceManagerTest, RootNamespaceCreationAndLookup) {
    SysMLv2::API::InstanceManager manager;
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

TEST(InstanceManagerTest, StandardLibraryImportResolvesToLibraryElement) {
    SysMLv2::API::InstanceManager manager;
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

TEST(InstanceManagerTest, StandardLibraryIsLoadedOnDemandOnly) {
    SysMLv2::API::InstanceManager manager;
    manager.parseModel("package P { attribute def A; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    // An attribute definition needs Attributes::AttributeValue (implicit generalization), nothing of the domain libraries.
    EXPECT_NE(manager.findElementWithQualifiedName("Attributes::AttributeValue"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("ISQ"), nullptr);
    EXPECT_EQ(manager.findElementWithQualifiedName("Requirements"), nullptr);
}

TEST(InstanceManagerTest, ImportedLibraryFilesFollowTheirOwnImports) {
    SysMLv2::API::InstanceManager manager;
    // Parts.sysml imports Items, Ports, ... and Base; qualified names without an import are found through the workspace too.
    manager.parseModel("package P { part def Car; part car : Car; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    EXPECT_TRUE(manager.getUnresolvedReferences().empty());
    EXPECT_NE(manager.findElementWithQualifiedName("Parts::Part"), nullptr);
    EXPECT_NE(manager.findElementWithQualifiedName("Items::Item"), nullptr);
    EXPECT_NE(manager.findElementWithQualifiedName("Base::Anything"), nullptr);
}

TEST(InstanceManagerTest, NonStandardLibraryIsImportedAndSpecialized) {
    SysMLv2::API::InstanceManager manager;
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

TEST(InstanceManagerTest, NonStandardLibraryAppendedAfterTheModelIsPickedUp) {
    SysMLv2::API::InstanceManager manager;
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

TEST(InstanceManagerTest, UnresolvedReferencesAreWarningsWithPosition) {
    SysMLv2::API::InstanceManager manager;
    manager.parseModel("package P {\n    attribute def A :> Missing;\n}");

    EXPECT_TRUE(manager.getParserErrors().empty());
    const auto unresolved = manager.getUnresolvedReferences();
    ASSERT_EQ(unresolved.size(), 1u);
    EXPECT_EQ(unresolved.front()->errorType(), SysMLv2::Files::ErrorType::WARNING);
    EXPECT_NE(unresolved.front()->description().find("Missing"), std::string::npos);
    EXPECT_EQ(unresolved.front()->getLine(), 2);
    EXPECT_EQ(unresolved.front()->getSource(), "InstanceModel");
}

TEST(InstanceManagerTest, SyntaxErrorsOfModelAndLibrariesAreReported) {
    SysMLv2::API::InstanceManager manager;
    manager.parseModel("package P { attribute def ; ");
    ASSERT_FALSE(manager.getParserErrors().empty());
    for (const auto& error : manager.getParserErrors()) {
        EXPECT_EQ(error->errorType(), SysMLv2::Files::ErrorType::ERROR);
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

TEST(InstanceManagerTest, QualifiedNamesOfNestedElements) {
    SysMLv2::API::InstanceManager manager;
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

TEST(InstanceManagerTest, SecondParseModelGivesAFreshModel) {
    SysMLv2::API::InstanceManager manager;
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

TEST(InstanceManagerTest, EmptyModelHasARootNamespace) {
    SysMLv2::API::InstanceManager manager;
    EXPECT_EQ(manager.getRootNamespace(), nullptr);
    EXPECT_TRUE(manager.getElements().empty());
    EXPECT_EQ(manager.findElementWithQualifiedName("P"), nullptr);

    manager.parseModel("");
    EXPECT_TRUE(manager.getParserErrors().empty());
    ASSERT_NE(manager.getRootNamespace(), nullptr);
    EXPECT_TRUE(manager.getRootNamespace()->ownedMember().empty());
}

TEST(InstanceManagerTest, ModelPackageWithTheNameOfALibraryPackageIsNotReplaced) {
    SysMLv2::API::InstanceManager manager;
    manager.parseModel("package ScalarValues { attribute def Real; }");
    EXPECT_TRUE(manager.getParserErrors().empty());
    // Only the model's own package exists: no library ScalarValues is added next to it.
    EXPECT_EQ(manager.findAllElementsWithDeclaredName("ScalarValues").size(), 1u);
}
