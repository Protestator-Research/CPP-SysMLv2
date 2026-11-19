#include "TestSupport.h"

#include <sysmlv2/evaluation/QualifiedName.h>

#include <kerml/root/namespaces/OwningMembership.h>

using namespace TestSupport;

TEST(QualifiedName, JoinsTheNamesOfTheOwnerChain) {
    const auto root = makeRoot();
    const auto package = makePackage("DataFunctions", root);
    const auto function = makeFunction("+", package);
    EXPECT_EQ(qualifiedNameOf(*function), "DataFunctions::'+'");
    EXPECT_EQ(qualifiedNameOf(function), "DataFunctions::'+'");
    EXPECT_EQ(qualifiedNameOf(*package), "DataFunctions");
    EXPECT_EQ(qualifiedNameOf(std::shared_ptr<KerML::Entities::Element>()), "");
}

TEST(QualifiedName, EscapesUnrestrictedNamesAndReservedWords) {
    const auto root = makeRoot();
    const auto outer = makePackage("Outer Package", root);
    const auto inner = makePackage("Inner", outer);
    EXPECT_EQ(qualifiedNameOf(*makeFunction("not", inner)), "'Outer Package'::Inner::'not'");
    EXPECT_EQ(qualifiedNameOf(*makeFunction("collect", inner)), "'Outer Package'::Inner::collect");
    EXPECT_EQ(qualifiedNameOf(*makeFunction("\?\?", inner)), "'Outer Package'::Inner::'\?\?'");
    EXPECT_EQ(qualifiedNameOf(*makeFunction("it's", inner)), "'Outer Package'::Inner::'it\\'s'");
}

TEST(QualifiedName, SkipsRelationshipsOnTheChain) {
    const auto root = makeRoot();
    const auto package = makePackage("Pkg", root);
    const auto membership = std::make_shared<KerML::Entities::OwningMembership>();
    membership->setOwner(package);
    const auto function = makeFunction("f", membership);
    EXPECT_EQ(qualifiedNameOf(*function), "Pkg::f");
}

TEST(QualifiedName, AnOwnerlessPackageIsNotARootNamespace) {
    const auto package = makePackage("Alone", nullptr);
    EXPECT_EQ(qualifiedNameOf(*package), "Alone");
    EXPECT_EQ(qualifiedNameOf(*makeRoot()), "");
}

TEST(QualifiedName, UnnamedElementsFallBackToTheStoredQualifiedName) {
    const auto root = makeRoot();
    const auto package = makePackage("Pkg", root);
    const auto unnamed = std::make_shared<KerML::Entities::Function>();
    unnamed->setOwner(package);
    EXPECT_EQ(qualifiedNameOf(*unnamed), "Pkg::<unnamed>");
    unnamed->setQualifiedName(std::string("Stored::Name"));
    EXPECT_EQ(qualifiedNameOf(*unnamed), "Stored::Name");
}

TEST(QualifiedName, CyclicOwnershipTerminates) {
    const auto a = makePackage("A", nullptr);
    const auto b = makePackage("B", a);
    a->setOwner(b);
    const std::string name = qualifiedNameOf(*b);
    EXPECT_FALSE(name.empty());
    a->setOwner(nullptr);   // (the cycle is a shared_ptr cycle: break it so that the test does not leak)
}
