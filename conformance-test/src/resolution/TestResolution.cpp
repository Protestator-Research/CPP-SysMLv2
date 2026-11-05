// AP10 (findings L3 / L4): scoped, qualified name resolution over a multi-file Workspace.
//
// Unit tests build small models with SysMLv2::Files::Workspace::addText and check what the names resolve to
// (KerML 8.2.3.5 / 7.2.5: local namespace, imported members, enclosing namespaces, global namespace; qualified names segment by
// segment; `::*`, `::**` and membership imports; public vs. private re-export; aliases; short names; quoted names; shadowing;
// cross-file references). The library tests load the whole standard library into one Workspace and check that every name
// resolves; references that do not are listed in conformance-test/expected_unresolved.txt (ratchet, same semantics as
// expected_failures.txt: a listed reference that now resolves fails, an unlisted unresolved one fails).
#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include <kerml/KerML.h>
#include <sysml/SysML.h>
#include <sysmlv2/Parser.h>
#include <sysmlv2/Workspace.h>
#include <sysmlv2/resolution/ResolutionData.h>

#include "../support/TestHelpers.h"

#ifndef SYSML_LIBRARY_DIR
#error "SYSML_LIBRARY_DIR must be defined by CMake to the resources/sysml.library path"
#endif
#ifndef CONFORMANCE_EXPECTED_UNRESOLVED_FILE
#error "CONFORMANCE_EXPECTED_UNRESOLVED_FILE must be defined by CMake"
#endif

namespace {

using SysMLv2::Files::isUnresolved;
using SysMLv2::Files::SourceLanguage;
using SysMLv2::Files::Workspace;
using ElementPtr = std::shared_ptr<KerML::Entities::Element>;

template <class T>
std::shared_ptr<T> as(const ElementPtr& element) {
    return std::dynamic_pointer_cast<T>(element);
}

/// The first type of the feature with the given (qualified) name, or null.
std::shared_ptr<KerML::Entities::Type> typeOf(const Workspace& ws, const std::string& featureName) {
    const auto feature = as<KerML::Entities::Feature>(ws.find(featureName));
    if (!feature || feature->type().empty()) return nullptr;
    return feature->type().front();
}

/// Resolves one text (SysML) as a workspace of its own.
struct One {
    Workspace ws;
    explicit One(const std::string& text, SourceLanguage language = SourceLanguage::SysML, const std::string& name = "test.sysml") {
        ws.addText(text, name, language);
        ws.resolve();
    }
};

// ---------------------------------------------------------------------------------------------------------------------
// Scoping
// ---------------------------------------------------------------------------------------------------------------------

TEST(NameResolution, LocalMember) {
    One m("package P { part def A; part a : A; }");
    const auto type = typeOf(m.ws, "P::a");
    ASSERT_NE(type, nullptr);
    EXPECT_EQ(type.get(), m.ws.find("P::A").get());
    EXPECT_FALSE(isUnresolved(type));
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

TEST(NameResolution, EnclosingNamespaces) {
    One m("package P { part def A; package Q { package R { part a : A; } } }");
    const auto type = typeOf(m.ws, "P::Q::R::a");
    ASSERT_NE(type, nullptr);
    EXPECT_EQ(type.get(), m.ws.find("P::A").get());
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

TEST(NameResolution, GlobalNamespaceHoldsTheRootPackages) {
    One m("package Lib { part def A; }\npackage U { part a : Lib::A; }");
    EXPECT_EQ(typeOf(m.ws, "U::a").get(), m.ws.find("Lib::A").get());
    EXPECT_EQ(m.ws.rootPackages().size(), 2u);
    // `$::Lib::A` starts at the global namespace explicitly.
    EXPECT_EQ(m.ws.find("$::Lib::A").get(), m.ws.find("Lib::A").get());
}

TEST(NameResolution, QualifiedNamesAreResolvedSegmentBySegment) {
    One m("package P { package Q { part def A; } }\npackage R { part a : P::Q::A; part b : P::A; }");
    EXPECT_EQ(typeOf(m.ws, "R::a").get(), m.ws.find("P::Q::A").get());
    // P::A does not exist (A is a member of Q, not of P): the reference is reported, not guessed.
    ASSERT_EQ(m.ws.unresolvedReferences().size(), 1u);
    EXPECT_EQ(m.ws.unresolvedReferences().front().name, "P::A");
    EXPECT_TRUE(isUnresolved(typeOf(m.ws, "R::b")));
}

TEST(NameResolution, ShadowingPrefersTheInnermostNamespace) {
    One m("package P {\n part def A;\n part outer : A;\n package Q {\n  part def A;\n  part inner : A;\n }\n}");
    EXPECT_EQ(typeOf(m.ws, "P::outer").get(), m.ws.find("P::A").get());
    EXPECT_EQ(typeOf(m.ws, "P::Q::inner").get(), m.ws.find("P::Q::A").get());
    EXPECT_NE(m.ws.find("P::A").get(), m.ws.find("P::Q::A").get());
}

TEST(NameResolution, LocalMembersShadowImportedMembers) {
    One m("package Lib { part def A; }\npackage U { import Lib::*; part def A; part a : A; }");
    EXPECT_EQ(typeOf(m.ws, "U::a").get(), m.ws.find("U::A").get());
}

TEST(NameResolution, QuotedNamesAreComparedWithoutTheirQuotes) {
    One m("package P { part def 'My Def'; part a : 'My Def'; }\npackage Q { part b : P::'My Def'; }");
    EXPECT_EQ(typeOf(m.ws, "P::a").get(), m.ws.find("P::'My Def'").get());
    EXPECT_EQ(typeOf(m.ws, "Q::b").get(), m.ws.find("P::'My Def'").get());
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

TEST(NameResolution, ShortNames) {
    One m("package P { part def <kg> Kilogram; part c : kg; }\npackage Q { part a : P::kg; part b : P::Kilogram; }");
    const auto kilogram = m.ws.find("P::Kilogram");
    ASSERT_NE(kilogram, nullptr);
    EXPECT_EQ(m.ws.find("P::kg").get(), kilogram.get());
    EXPECT_EQ(typeOf(m.ws, "P::c").get(), kilogram.get());
    EXPECT_EQ(typeOf(m.ws, "Q::a").get(), kilogram.get());
    EXPECT_EQ(typeOf(m.ws, "Q::b").get(), kilogram.get());
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

TEST(NameResolution, ShortNameOfAFeatureWithATypingIsFound) {
    One m("package P { part def M; part <kg> kilogram : M; part x subsets kg; }");
    const auto x = as<KerML::Entities::Feature>(m.ws.find("P::x"));
    ASSERT_NE(x, nullptr);
    ASSERT_EQ(x->ownedSubsetting().size(), 1u);
    EXPECT_EQ(x->ownedSubsetting().front()->subsettedFeature().get(), m.ws.find("P::kilogram").get());
    EXPECT_EQ(typeOf(m.ws, "P::kilogram").get(), m.ws.find("P::M").get());
}

TEST(NameResolution, Aliases) {
    One m("package P { part def Real; alias R for Real; alias <s> S for Real; }\npackage Q { part x : P::R; part y : P::S; part z : P::s; }");
    const auto real = m.ws.find("P::Real");
    ASSERT_NE(real, nullptr);
    EXPECT_EQ(typeOf(m.ws, "Q::x").get(), real.get());
    EXPECT_EQ(typeOf(m.ws, "Q::y").get(), real.get());
    EXPECT_EQ(typeOf(m.ws, "Q::z").get(), real.get());
    EXPECT_EQ(m.ws.find("P::R").get(), real.get());
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

TEST(NameResolution, AliasesAreVisibleThroughImports) {
    One m("package P { part def Real; alias R for Real; }\npackage Q { import P::*; part x : R; }");
    EXPECT_EQ(typeOf(m.ws, "Q::x").get(), m.ws.find("P::Real").get());
}

TEST(NameResolution, PrivateAliasesAreNotVisibleFromOutside) {
    One m("package P { part def Real; private alias R for Real; }\npackage Q { part x : P::R; }");
    EXPECT_TRUE(isUnresolved(typeOf(m.ws, "Q::x")));
    ASSERT_EQ(m.ws.unresolvedReferences().size(), 1u);
}

// ---------------------------------------------------------------------------------------------------------------------
// Imports
// ---------------------------------------------------------------------------------------------------------------------

TEST(NameResolution, NamespaceImportImportsPublicMembers) {
    One m("package Lib { part def A; private part def Secret; }\npackage U { import Lib::*; part a : A; part s : Secret; }");
    EXPECT_EQ(typeOf(m.ws, "U::a").get(), m.ws.find("Lib::A").get());
    EXPECT_TRUE(isUnresolved(typeOf(m.ws, "U::s")));
    ASSERT_EQ(m.ws.unresolvedReferences().size(), 1u);
    EXPECT_EQ(m.ws.unresolvedReferences().front().name, "Secret");
}

TEST(NameResolution, ImportAllAlsoImportsPrivateMembers) {
    One m("package Lib { private part def Secret; }\npackage U { import all Lib::*; part s : Secret; }");
    EXPECT_EQ(typeOf(m.ws, "U::s").get(), m.ws.find("Secret", m.ws.find("Lib")).get());
    EXPECT_NE(typeOf(m.ws, "U::s"), nullptr);
    EXPECT_FALSE(isUnresolved(typeOf(m.ws, "U::s")));
}

TEST(NameResolution, NamespaceImportIsNotRecursive) {
    One m("package Lib { package Inner { part def B; } part def A; }\npackage U { import Lib::*; part a : A; part b : B; part c : Inner::B; }");
    EXPECT_EQ(typeOf(m.ws, "U::a").get(), m.ws.find("Lib::A").get());
    EXPECT_TRUE(isUnresolved(typeOf(m.ws, "U::b")));
    EXPECT_EQ(typeOf(m.ws, "U::c").get(), m.ws.find("Lib::Inner::B").get());
}

TEST(NameResolution, RecursiveImportReachesNestedNamespaces) {
    One m("package Lib { package Inner { package Deep { part def C; } part def B; } part def A; }\n"
          "package U { import Lib::**; part a : A; part b : B; part c : C; }");
    EXPECT_EQ(typeOf(m.ws, "U::a").get(), m.ws.find("Lib::A").get());
    EXPECT_EQ(typeOf(m.ws, "U::b").get(), m.ws.find("Lib::Inner::B").get());
    EXPECT_EQ(typeOf(m.ws, "U::c").get(), m.ws.find("Lib::Inner::Deep::C").get());
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

TEST(NameResolution, MembershipImportImportsOneMember) {
    One m("package Lib { part def A; part def C; }\npackage U { import Lib::A; part a : A; part c : C; }");
    EXPECT_EQ(typeOf(m.ws, "U::a").get(), m.ws.find("Lib::A").get());
    EXPECT_TRUE(isUnresolved(typeOf(m.ws, "U::c")));
    ASSERT_EQ(m.ws.unresolvedReferences().size(), 1u);
    EXPECT_EQ(m.ws.unresolvedReferences().front().name, "C");
}

TEST(NameResolution, MembershipImportBringsInTheMemberEvenThroughAnotherImport) {
    One m("package Lib { part def A; }\npackage Mid { public import Lib::*; }\npackage U { import Mid::A; part a : A; }");
    EXPECT_EQ(typeOf(m.ws, "U::a").get(), m.ws.find("Lib::A").get());
}

TEST(NameResolution, PublicImportsAreReExported) {
    One m("package Lib { part def A; }\npackage Mid { public import Lib::*; }\npackage U { import Mid::*; part a : A; }\npackage V { part b : Mid::A; }");
    EXPECT_EQ(typeOf(m.ws, "U::a").get(), m.ws.find("Lib::A").get());
    EXPECT_EQ(typeOf(m.ws, "V::b").get(), m.ws.find("Lib::A").get());
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

TEST(NameResolution, PrivateImportsAreNotReExported) {
    One m("package Lib { part def A; }\n"
          "package Mid { private import Lib::*; part inside : A; }\n"
          "package U { import Mid::*; part a : A; }\n"
          "package V { part b : Mid::A; }");
    // Inside Mid the private import is visible ...
    EXPECT_EQ(typeOf(m.ws, "Mid::inside").get(), m.ws.find("Lib::A").get());
    // ... from outside it is not.
    EXPECT_TRUE(isUnresolved(typeOf(m.ws, "U::a")));
    EXPECT_TRUE(isUnresolved(typeOf(m.ws, "V::b")));
    EXPECT_EQ(m.ws.unresolvedReferences().size(), 2u);
}

TEST(NameResolution, AnImportWithoutVisibilityIsPrivate) {
    One m("package Lib { part def A; }\npackage Mid { import Lib::*; }\npackage U { import Mid::*; part a : A; }");
    EXPECT_TRUE(isUnresolved(typeOf(m.ws, "U::a")));
}

TEST(NameResolution, ReExportChainsAcrossSeveralPackages) {
    One m("package L1 { part def A; }\npackage L2 { public import L1::*; }\npackage L3 { public import L2::*; }\n"
          "package U { import L3::*; part a : A; }");
    EXPECT_EQ(typeOf(m.ws, "U::a").get(), m.ws.find("L1::A").get());
}

TEST(NameResolution, CyclicImportsTerminate) {
    One m("package A { public import B::*; part def X; }\npackage B { public import A::*; part def Y; }\n"
          "package U { import A::*; part x : X; part y : Y; part z : Nope; }");
    EXPECT_EQ(typeOf(m.ws, "U::x").get(), m.ws.find("A::X").get());
    EXPECT_EQ(typeOf(m.ws, "U::y").get(), m.ws.find("B::Y").get());
    ASSERT_EQ(m.ws.unresolvedReferences().size(), 1u);
}

TEST(NameResolution, ImportsAndAliasesAreRecordedInTheModel) {
    One m("package Lib { part def A; }\npackage U { public import Lib::*; private import all Lib::A; alias X for Lib::A; }");
    // `import Lib::*;` imports the members of a namespace (a NamespaceImport), `import all Lib::A;` a single membership (a MembershipImport).
    std::vector<std::shared_ptr<KerML::Entities::NamespaceImport>> imports;
    std::vector<std::shared_ptr<KerML::Entities::MembershipImport>> membershipImports;
    for (const auto& element : m.ws.elements(0)) {
        if (auto import = as<KerML::Entities::NamespaceImport>(element)) imports.push_back(import);
        if (auto import = as<KerML::Entities::MembershipImport>(element)) membershipImports.push_back(import);
    }
    ASSERT_EQ(imports.size(), 1u);
    ASSERT_EQ(membershipImports.size(), 1u);
    EXPECT_EQ(imports[0]->visibility(), KerML::Entities::PUBLIC);
    EXPECT_EQ(imports[0]->importedNamespace().get(), m.ws.find("Lib").get());
    EXPECT_FALSE(imports[0]->isImportAll());
    EXPECT_EQ(membershipImports[0]->visibility(), KerML::Entities::PRIVATE);
    EXPECT_TRUE(membershipImports[0]->isImportAll());
    ASSERT_NE(membershipImports[0]->importedMembership(), nullptr);
    EXPECT_EQ(membershipImports[0]->importedMembership()->memberElement().get(), m.ws.find("Lib::A").get());
    // The alias is a membership of the target in U, and the target knows the alias.
    const auto a = m.ws.find("Lib::A");
    ASSERT_NE(a, nullptr);
    const auto aliases = a->aliasIds();
    EXPECT_NE(std::find(aliases.begin(), aliases.end(), "X"), aliases.end());
}

// ---------------------------------------------------------------------------------------------------------------------
// Inheritance and the other relationships
// ---------------------------------------------------------------------------------------------------------------------

TEST(NameResolution, RedefinitionFindsTheInheritedFeature) {
    One m("package P { part def A { part x; } part def B :> A { part y :>> x; } }");
    const auto y = as<KerML::Entities::Feature>(m.ws.find("P::B::y"));
    ASSERT_NE(y, nullptr);
    ASSERT_EQ(y->ownedRedefinition().size(), 1u);
    EXPECT_EQ(y->ownedRedefinition().front()->redefinedFeature().get(), m.ws.find("P::A::x").get());
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

TEST(NameResolution, InheritedMembersAreFoundByTheirSimpleName) {
    One m("package P { part def A { part x; } part def B :> A { part y subsets x; } }");
    const auto y = as<KerML::Entities::Feature>(m.ws.find("P::B::y"));
    ASSERT_NE(y, nullptr);
    ASSERT_EQ(y->ownedSubsetting().size(), 1u);
    EXPECT_EQ(y->ownedSubsetting().front()->subsettedFeature().get(), m.ws.find("P::A::x").get());
}

TEST(NameResolution, FeatureChainsFollowTheTypeOfTheirFirstFeature) {
    One m("package P { part def T { part m; } part def A { part t : T; part u subsets t.m; } }");
    const auto u = as<KerML::Entities::Feature>(m.ws.find("P::A::u"));
    ASSERT_NE(u, nullptr);
    ASSERT_EQ(u->ownedSubsetting().size(), 1u);
    EXPECT_EQ(u->ownedSubsetting().front()->subsettedFeature().get(), m.ws.find("P::T::m").get());
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

TEST(NameResolution, SpecializationTargetsAreResolved) {
    One m("package Lib { part def A; }\npackage U { import Lib::*; part def B :> A; }");
    const auto b = as<KerML::Entities::Classifier>(m.ws.find("U::B"));
    ASSERT_NE(b, nullptr);
    ASSERT_EQ(b->ownedSubclassification().size(), 1u);
    EXPECT_EQ(b->ownedSubclassification().front()->superclassifier().get(), m.ws.find("Lib::A").get());
}

TEST(NameResolution, DerivedDefinitionsStillFollowTheResolvedTyping) {
    One m("package P { part def A; part a : A; }");
    const auto a = as<SysMLv2::Entities::PartUsage>(m.ws.find("P::a"));
    ASSERT_NE(a, nullptr);
    ASSERT_EQ(a->partDefinition().size(), 1u);
    EXPECT_EQ(a->partDefinition().front().get(), m.ws.find("P::A").get());
}

TEST(NameResolution, DependencyEndsAndCommentTargetsAreResolved) {
    One m("package P { part def A; part def B; dependency D from A to B; comment C about A /* hi */ }");
    std::shared_ptr<KerML::Entities::Dependency> dependency;
    std::shared_ptr<KerML::Entities::Comment> comment;
    for (const auto& element : m.ws.elements()) {
        if (!dependency) dependency = as<KerML::Entities::Dependency>(element);
        if (!comment) comment = as<KerML::Entities::Comment>(element);
    }
    ASSERT_NE(dependency, nullptr);
    ASSERT_EQ(dependency->client().size(), 1u);
    ASSERT_EQ(dependency->supplier().size(), 1u);
    EXPECT_EQ(dependency->client().front().get(), m.ws.find("P::A").get());
    EXPECT_EQ(dependency->supplier().front().get(), m.ws.find("P::B").get());
    ASSERT_NE(comment, nullptr);
    ASSERT_EQ(comment->annotatedElement().size(), 1u);
    EXPECT_EQ(comment->annotatedElement().front().get(), m.ws.find("P::A").get());
}

// ---------------------------------------------------------------------------------------------------------------------
// Several sources
// ---------------------------------------------------------------------------------------------------------------------

TEST(NameResolution, CrossFileReferencesAreResolvedOverTheUnionOfAllSources) {
    Workspace ws;
    // The using file comes first: nothing is resolved while a file is parsed.
    ws.addText("package U { import Lib::*; part a : A; part b : Lib::A; }", "u.sysml");
    ws.addText("package Lib { part def A; }", "lib.sysml");
    ws.resolve();
    EXPECT_EQ(ws.sourceCount(), 2u);
    EXPECT_TRUE(ws.unresolvedReferences().empty());
    EXPECT_EQ(typeOf(ws, "U::a").get(), ws.find("Lib::A").get());
    EXPECT_EQ(typeOf(ws, "U::b").get(), ws.find("Lib::A").get());
    EXPECT_EQ(ws.sourceName(0), "u.sysml");
    EXPECT_EQ(ws.rootPackages().size(), 2u);
}

TEST(NameResolution, ResolveCanBeRepeatedAfterAddingSources) {
    Workspace ws;
    ws.addText("package U { import Lib::*; part a : A; }", "u.sysml");
    ws.resolve();
    EXPECT_EQ(ws.unresolvedReferences().size(), 2u);  // the import and the typing
    EXPECT_TRUE(isUnresolved(typeOf(ws, "U::a")));
    ws.addText("package Lib { part def A; }", "lib.sysml");
    ws.resolve();
    EXPECT_TRUE(ws.unresolvedReferences().empty());
    EXPECT_EQ(typeOf(ws, "U::a").get(), ws.find("Lib::A").get());
    EXPECT_FALSE(isUnresolved(typeOf(ws, "U::a")));
}

TEST(NameResolution, KerMLAndSysMLSourcesShareOneGlobalNamespace) {
    Workspace ws;
    ws.addText("package Base { classifier Anything; }\npackage Mid { public import Base::*; }", "base.kerml");
    ws.addText("package U { import Mid::*; part def P :> Anything; }", "u.sysml");
    ws.addText("package N { import Mid::*; classifier C specializes Anything; }", "n.kerml");
    ws.resolve();
    EXPECT_TRUE(ws.unresolvedReferences().empty());
    const auto p = as<KerML::Entities::Classifier>(ws.find("U::P"));
    const auto c = as<KerML::Entities::Classifier>(ws.find("N::C"));
    ASSERT_NE(p, nullptr);
    ASSERT_NE(c, nullptr);
    ASSERT_EQ(p->ownedSubclassification().size(), 1u);
    ASSERT_EQ(c->ownedSubclassification().size(), 1u);
    EXPECT_EQ(p->ownedSubclassification().front()->superclassifier().get(), ws.find("Base::Anything").get());
    EXPECT_EQ(c->ownedSubclassification().front()->superclassifier().get(), ws.find("Base::Anything").get());
}

TEST(NameResolution, KerMLImportVisibility) {
    Workspace ws;
    ws.addText("package Lib { classifier A; }\npackage Pub { public import Lib::*; }\npackage Priv { private import Lib::*; }\n"
               "package U { import Pub::*; classifier X specializes A; }\npackage V { import Priv::*; classifier Y specializes A; }",
               "t.kerml");
    ws.resolve();
    const auto x = as<KerML::Entities::Classifier>(ws.find("U::X"));
    const auto y = as<KerML::Entities::Classifier>(ws.find("V::Y"));
    ASSERT_NE(x, nullptr);
    ASSERT_NE(y, nullptr);
    ASSERT_EQ(x->ownedSubclassification().size(), 1u);
    ASSERT_EQ(y->ownedSubclassification().size(), 1u);
    EXPECT_EQ(x->ownedSubclassification().front()->superclassifier().get(), ws.find("Lib::A").get());
    EXPECT_TRUE(isUnresolved(y->ownedSubclassification().front()->superclassifier()));
}

TEST(NameResolution, KerMLFeatureTypingAndSubsettingUseScopedLookup) {
    One m("package P { datatype D; class C { feature f : D; feature g subsets f; } }", SourceLanguage::KerML, "t.kerml");
    EXPECT_EQ(typeOf(m.ws, "P::C::f").get(), m.ws.find("P::D").get());
    const auto g = as<KerML::Entities::Feature>(m.ws.find("P::C::g"));
    ASSERT_NE(g, nullptr);
    ASSERT_EQ(g->ownedSubsetting().size(), 1u);
    EXPECT_EQ(g->ownedSubsetting().front()->subsettedFeature().get(), m.ws.find("P::C::f").get());
    EXPECT_TRUE(m.ws.unresolvedReferences().empty());
}

// ---------------------------------------------------------------------------------------------------------------------
// Unresolved references
// ---------------------------------------------------------------------------------------------------------------------

TEST(UnresolvedReferences, AreReportedWithPositionAndIdentifiablePlaceholders) {
    One m("package P {\n  part a : Nope;\n}", SourceLanguage::SysML, "x.sysml");
    const auto& unresolved = m.ws.unresolvedReferences();
    ASSERT_EQ(unresolved.size(), 1u);
    EXPECT_EQ(unresolved[0].name, "Nope");
    EXPECT_EQ(unresolved[0].sourceName, "x.sysml");
    EXPECT_EQ(unresolved[0].line, 2);
    EXPECT_GE(unresolved[0].column, 0);
    EXPECT_EQ(unresolved[0].kind, SysMLv2::Files::ReferenceKind::Type);
    EXPECT_TRUE(isUnresolved(unresolved[0].placeholder));
    // The model keeps the placeholder as the type ...
    const auto type = typeOf(m.ws, "P::a");
    ASSERT_NE(type, nullptr);
    EXPECT_TRUE(isUnresolved(type));
    EXPECT_EQ(type->declaredName().value_or(""), "Nope");
    // ... but never as a member of a namespace or of the element list, and never as a DataType.
    for (const auto& element : m.ws.elements()) {
        EXPECT_FALSE(isUnresolved(element));
        EXPECT_EQ(as<KerML::Entities::DataType>(element), nullptr);
    }
    EXPECT_EQ(type->owner(), nullptr);
}

TEST(UnresolvedReferences, CanBeReportedAsWarnings) {
    One m("package P {\n  part a : Nope;\n  part b : Missing::Name;\n}");
    const auto warnings = m.ws.unresolvedAsWarnings(0);
    ASSERT_EQ(warnings.size(), 2u);
    for (const auto& warning : warnings) {
        EXPECT_EQ(warning->errorType(), SysMLv2::Files::ErrorType::WARNING);
        EXPECT_EQ(warning->getSource(), "test.sysml");
    }
    EXPECT_EQ(warnings[0]->getLine(), 2);
    EXPECT_EQ(warnings[1]->getLine(), 3);
    EXPECT_NE(warnings[1]->description().find("Missing::Name"), std::string::npos);
    EXPECT_TRUE(m.ws.errors().empty());  // syntax errors only
}

TEST(UnresolvedReferences, TheParserApiReportsThemOnRequest) {
    const std::string text = "part def X {\n  attribute s : String;\n  attribute n : Integer;\n}";
    const auto quiet = SysMLv2::Files::Parser::parseSysMLv2(text);
    EXPECT_TRUE(quiet.second.empty());
    const auto loud = SysMLv2::Files::Parser::parseSysMLv2(text, "x.sysml", true);
    ASSERT_EQ(loud.second.size(), 2u);
    EXPECT_EQ(loud.second[0]->errorType(), SysMLv2::Files::ErrorType::WARNING);
    EXPECT_EQ(loud.second[0]->getLine(), 2);
    EXPECT_EQ(loud.second[1]->getLine(), 3);
    // The parser does not invent String / Integer any more: no element of that name exists, the typings stay unresolved.
    for (const auto& element : loud.first) {
        EXPECT_NE(element->declaredName().value_or(""), "String");
        EXPECT_NE(element->declaredName().value_or(""), "Integer");
        EXPECT_FALSE(isUnresolved(element));
    }
    const auto kerml = SysMLv2::Files::Parser::parseKerML("classifier C specializes Nope;", "c.kerml", true);
    ASSERT_EQ(kerml.second.size(), 1u);
    EXPECT_EQ(kerml.second[0]->errorType(), SysMLv2::Files::ErrorType::WARNING);
}

// An unresolved name that a package of the workspace defines is reported with the import that would make it visible.
TEST(UnresolvedReferences, HintTheMissingImport) {
    Workspace ws;
    ws.addText("package Lib { attribute <kg> kilogram; part def Engine; }", "lib.sysml");
    ws.addText("package U { attribute m = 1 [kg]; part e : Engine; }", "user.sysml");
    ws.resolve();
    const auto warnings = ws.unresolvedAsWarnings(1);
    ASSERT_EQ(warnings.size(), 2u);
    EXPECT_NE(warnings[0]->description().find("unresolved reference to feature 'kg'"), std::string::npos);
    EXPECT_NE(warnings[0]->description().find("Lib::kilogram (short name 'kg') is not visible here: add 'private import Lib::*;'"), std::string::npos);
    EXPECT_NE(warnings[1]->description().find("Lib::Engine is not visible here: add 'private import Lib::*;'"), std::string::npos);
    EXPECT_EQ(warnings[1]->description().find("short name"), std::string::npos);
    // (a candidate was found: no hint about loadLibrary())
    EXPECT_EQ(warnings[0]->description().find("loadLibrary"), std::string::npos);
}

TEST(UnresolvedReferences, HintSeveralCandidatePackages) {
    Workspace ws;
    ws.addText("package A { part def Engine; }", "a.sysml");
    ws.addText("package B { part def Engine; }", "b.sysml");
    ws.addText("package 'C d' { part def Engine; }", "c.sysml");
    ws.addText("package U { part e : Engine; }", "user.sysml");
    ws.resolve();
    const auto warnings = ws.unresolvedAsWarnings(3);
    ASSERT_EQ(warnings.size(), 1u);
    EXPECT_NE(warnings[0]->description().find("candidates that are not visible here: 'C d'::Engine, A::Engine, B::Engine; import one of their packages, e.g. 'private import"),
              std::string::npos) << warnings[0]->description();
}

TEST(UnresolvedReferences, HintOnlyForMembersOfPackagesAndOfTheRightKind) {
    Workspace ws;
    // "inner" is a member of a part def (not importable with a package import), "min" is a feature in P and a function in Q
    ws.addText("package P { part def Holder { attribute inner; } attribute <min> minute; }", "p.sysml");
    ws.addText("package Q { calc def min; }", "q.sysml");
    ws.addText("package U { attribute a : inner; attribute b = min; }", "user.sysml");
    ws.resolve();
    const auto warnings = ws.unresolvedAsWarnings(2);
    ASSERT_EQ(warnings.size(), 2u);
    bool inner = false;
    bool min = false;
    for (const auto& warning : warnings) {
        const auto& text = warning->description();
        if (text.find("'inner'") != std::string::npos) {
            inner = true;
            EXPECT_EQ(text.find("not visible here"), std::string::npos) << text;
        } else if (text.find("feature 'min'") != std::string::npos) {
            min = true;
            EXPECT_NE(text.find("P::minute (short name 'min')"), std::string::npos) << text;
            EXPECT_EQ(text.find("Q::"), std::string::npos) << text;
        }
    }
    EXPECT_TRUE(inner);
    EXPECT_TRUE(min);
}

TEST(UnresolvedReferences, HintListsAPackageOnceAndSkipsPrivateMembers) {
    Workspace ws;
    // the same package in two sources: one candidate; a private member is not imported by `import P::*`
    ws.addText("package Lib { part def Engine; }", "lib1.sysml");
    ws.addText("package Lib { part def Engine; }", "lib2.sysml");
    ws.addText("package Hidden { private part def Secret; }", "hidden.sysml");
    ws.addText("package U { part e : Engine; part s : Secret; }", "user.sysml");
    ws.resolve();
    const auto warnings = ws.unresolvedAsWarnings(3);
    ASSERT_EQ(warnings.size(), 2u);
    EXPECT_NE(warnings[0]->description().find("; Lib::Engine is not visible here: add 'private import Lib::*;'"), std::string::npos) << warnings[0]->description();
    EXPECT_EQ(warnings[1]->description().find("not visible here"), std::string::npos) << warnings[1]->description();
}

TEST(UnresolvedReferences, HintTheMissingLibraryOnlyIfItIsNotInTheWorkspace) {
    const auto alone = SysMLv2::Files::Parser::parseSysMLv2("package U { private import SI::*; attribute r = 1 [min]; }", "u.sysml", true);
    ASSERT_FALSE(alone.second.empty());
    EXPECT_NE(alone.second[0]->description().find("unresolved reference to namespace 'SI' (the standard library is not loaded; "), std::string::npos)
        << alone.second[0]->description();
    // a package of the model is no library; names that a package defines get the import hint instead
    Workspace ws;
    ws.addText("package Lib { part def Engine; }", "lib.sysml");
    ws.addText("package U { part e : Engine; part f : Missing; }", "user.sysml");
    ws.resolve();
    const auto warnings = ws.unresolvedAsWarnings(1);
    ASSERT_EQ(warnings.size(), 2u);
    EXPECT_EQ(warnings[0]->description().find("standard library"), std::string::npos);
    EXPECT_NE(warnings[1]->description().find("the standard library is not loaded"), std::string::npos);
    // the library is recognised by its package Base, however it was added (the application adds it with addText)
    Workspace loaded;
    loaded.addText("standard library package Base { abstract classifier Anything; }", "Base.kerml", SourceLanguage::KerML);
    loaded.addText("package U { part f : Missing; }", "user.sysml");
    loaded.resolve();
    const auto fromLibrary = loaded.unresolvedAsWarnings(1);
    ASSERT_EQ(fromLibrary.size(), 1u);
    EXPECT_EQ(fromLibrary[0]->description(), "unresolved reference to type 'Missing'");
}

TEST(UnresolvedReferences, ABaseTypeNameResolvesOnlyIfTheLibraryIsLoaded) {
    const std::string model = "package M { private import ScalarValues::*; attribute a : Real; }";
    {
        One alone(model);
        ASSERT_EQ(alone.ws.unresolvedReferences().size(), 2u);  // the import and the typing
        EXPECT_TRUE(isUnresolved(typeOf(alone.ws, "M::a")));
    }
    Workspace ws;
    ws.addText(model, "m.sysml");
    ws.addText("standard library package ScalarValues { datatype Real; }", "ScalarValues.kerml", SourceLanguage::KerML);
    ws.resolve();
    EXPECT_TRUE(ws.unresolvedReferences().empty());
    EXPECT_EQ(typeOf(ws, "M::a").get(), ws.find("ScalarValues::Real").get());
}

// ---------------------------------------------------------------------------------------------------------------------
// The standard library as one workspace
// ---------------------------------------------------------------------------------------------------------------------

class LibraryResolution : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        workspace = std::make_unique<Workspace>();
        const auto start = std::chrono::steady_clock::now();
        fileCount = workspace->loadLibrary(SYSML_LIBRARY_DIR);
        const auto parsed = std::chrono::steady_clock::now();
        workspace->resolve();
        const auto resolved = std::chrono::steady_clock::now();
        parseSeconds = std::chrono::duration<double>(parsed - start).count();
        resolveSeconds = std::chrono::duration<double>(resolved - parsed).count();
        std::cout << "[  INFO  ] library: " << fileCount << " files, parse " << parseSeconds << " s, resolve " << resolveSeconds
                  << " s, " << workspace->referenceCount() << " references, " << workspace->unresolvedReferences().size()
                  << " unresolved, " << workspace->notAttemptedReferences().size() << " not attempted" << std::endl;
    }
    static void TearDownTestSuite() { workspace.reset(); }

    static std::unique_ptr<Workspace> workspace;
    static size_t fileCount;
    static double parseSeconds;
    static double resolveSeconds;

    static std::string keyOf(const SysMLv2::Files::UnresolvedReferenceInfo& reference) {
        const std::filesystem::path root(SYSML_LIBRARY_DIR);
        auto relative = std::filesystem::path(reference.sourceName).lexically_relative(root).generic_string();
        if (relative.empty() || relative.rfind("..", 0) == 0) relative = std::filesystem::path(reference.sourceName).generic_string();
        return "library/" + relative + ":" + std::to_string(reference.line) + ":" + reference.name;
    }
};

std::unique_ptr<Workspace> LibraryResolution::workspace;
size_t LibraryResolution::fileCount = 0;
double LibraryResolution::parseSeconds = 0;
double LibraryResolution::resolveSeconds = 0;

TEST_F(LibraryResolution, LoadsEveryLibraryFileWithoutSyntaxErrors) {
    const auto files = ConformanceTest::listFiles(SYSML_LIBRARY_DIR, {".sysml", ".kerml"});
    EXPECT_EQ(fileCount, files.size());
    EXPECT_EQ(workspace->sourceCount(), files.size());
    EXPECT_TRUE(workspace->errors().empty());
    for (const auto& error : workspace->errors()) ADD_FAILURE() << error->getSource() << ":" << error->getLine() << " " << error->description();
}

// Test is currently removed, since it is highly dependend on the machine itself. Please use only for local tests.
// TEST_F(LibraryResolution, LoadAndResolveStayWithinTheTimeBudget) {
//     double budget = 60.0;
//     if (const char* env = std::getenv("SYSML_RESOLVE_BUDGET_S")) {
//         try {
//             budget = std::stod(env);
//         } catch (...) {
//         }
//     }
//     RecordProperty("parse_seconds", std::to_string(parseSeconds));
//     RecordProperty("resolve_seconds", std::to_string(resolveSeconds));
//     EXPECT_LT(parseSeconds + resolveSeconds, budget) << "load " << parseSeconds << " s + resolve " << resolveSeconds << " s";
// }

TEST_F(LibraryResolution, EveryReferenceIsResolvedExceptTheListedOnes) {
    static const auto expected = ConformanceTest::loadExpectedFailures(CONFORMANCE_EXPECTED_UNRESOLVED_FILE);
    std::set<std::string> actual;
    for (const auto& reference : workspace->unresolvedReferences()) actual.insert(keyOf(reference));

    for (const auto& key : actual) {
        if (expected.count(key) == 0) ADD_FAILURE() << "unresolved reference not listed in expected_unresolved.txt: " << key;
    }
    for (const auto& key : expected) {
        if (actual.count(key) == 0) ADD_FAILURE() << key << " now resolves; remove it from expected_unresolved.txt";
    }
    EXPECT_GT(workspace->referenceCount(), 10000u);
    EXPECT_EQ(workspace->referenceCount(), workspace->resolvedReferenceCount() + workspace->unresolvedReferences().size() +
                                               workspace->notAttemptedReferences().size());
}

TEST_F(LibraryResolution, PlaceholdersAreNeverPartOfTheElementList) {
    size_t count = 0;
    for (const auto& element : workspace->elements()) {
        ++count;
        ASSERT_NE(element, nullptr);
        EXPECT_FALSE(isUnresolved(element)) << element->declaredName().value_or("?");
    }
    EXPECT_GT(count, 10000u);
    // No fake base types: exactly one String / Real / Boolean datatype exists, the library's.
    for (const char* name : {"String", "Boolean", "Real", "Integer", "Natural", "Positive"}) {
        size_t datatypes = 0;
        for (const auto& element : workspace->elements()) {
            if (element->declaredName().value_or("") == name && std::dynamic_pointer_cast<KerML::Entities::DataType>(element)) ++datatypes;
        }
        EXPECT_EQ(datatypes, 1u) << name;
    }
}

TEST_F(LibraryResolution, SiKilogramIsTypedByTheMassUnitOfISQBase) {
    // SI.sysml: `attribute <kg> kilogram : MassUnit`. SI imports ISQ::* and ISQ re-exports ISQBase::* publicly.
    const auto type = typeOf(*workspace, "SI::kilogram");
    ASSERT_NE(type, nullptr);
    EXPECT_FALSE(isUnresolved(type));
    const auto massUnit = workspace->find("ISQBase::MassUnit");
    ASSERT_NE(massUnit, nullptr);
    EXPECT_EQ(type.get(), massUnit.get());
    EXPECT_EQ(workspace->find("SI::kg").get(), workspace->find("SI::kilogram").get());  // short name
}

TEST_F(LibraryResolution, PublicReExportReachesThroughISQButPrivateImportsDoNot) {
    const auto massUnit = workspace->find("ISQBase::MassUnit");
    ASSERT_NE(massUnit, nullptr);
    EXPECT_EQ(workspace->find("ISQ::MassUnit").get(), massUnit.get());
    EXPECT_EQ(workspace->find("ISQ::DurationValue").get(), workspace->find("ISQBase::DurationValue").get());
    // `private import ScalarValues::Real;` in ISQ is not visible from outside.
    EXPECT_EQ(workspace->find("ISQ::Real"), nullptr);
}

TEST_F(LibraryResolution, ScalarValuesRealIsFoundThroughAPrivateImport) {
    // Quantities.sysml: `attribute exponent: Real[1]` with `private import ScalarValues::Real`.
    const auto type = typeOf(*workspace, "Quantities::QuantityPowerFactor::exponent");
    ASSERT_NE(type, nullptr);
    const auto real = workspace->find("ScalarValues::Real");
    ASSERT_NE(real, nullptr);
    EXPECT_EQ(type.get(), real.get());
    EXPECT_FALSE(isUnresolved(type));
}

TEST_F(LibraryResolution, KerMLDataValueSpecializesBaseAnything) {
    // Base.kerml: `abstract datatype DataValue specializes Anything`, Anything from the same package.
    const auto dataValue = std::dynamic_pointer_cast<KerML::Entities::Type>(workspace->find("Base::DataValue"));
    ASSERT_NE(dataValue, nullptr);
    ASSERT_FALSE(dataValue->ownedSpecialization().empty());
    EXPECT_EQ(dataValue->ownedSpecialization().front()->general().get(), workspace->find("Base::Anything").get());
    // Occurrences.kerml reaches Anything through `private import Base::Anything;` (a membership import).
    const auto occurrence = std::dynamic_pointer_cast<KerML::Entities::Type>(workspace->find("Occurrences::Occurrence"));
    ASSERT_NE(occurrence, nullptr);
    ASSERT_FALSE(occurrence->ownedSpecialization().empty());
    EXPECT_EQ(occurrence->ownedSpecialization().front()->general().get(), workspace->find("Base::Anything").get());
}

TEST_F(LibraryResolution, SysMLPartsPartIsTheTypeOfPartsParts) {
    // Parts.sysml: `abstract part parts: Part[0..*] nonunique :> items` and `abstract part def Part :> Item`.
    const auto type = typeOf(*workspace, "Parts::parts");
    ASSERT_NE(type, nullptr);
    EXPECT_EQ(type.get(), workspace->find("Parts::Part").get());
    const auto part = std::dynamic_pointer_cast<KerML::Entities::Classifier>(workspace->find("Parts::Part"));
    ASSERT_NE(part, nullptr);
    ASSERT_FALSE(part->ownedSubclassification().empty());
    EXPECT_EQ(part->ownedSubclassification().front()->superclassifier().get(), workspace->find("Items::Item").get());
    // Items.sysml refers to Part through `private import Parts::Part;`.
    const auto subparts = std::dynamic_pointer_cast<KerML::Entities::Feature>(workspace->find("Items::Item::subparts"));
    ASSERT_NE(subparts, nullptr);
    ASSERT_FALSE(subparts->type().empty());
    EXPECT_EQ(subparts->type().front().get(), workspace->find("Parts::Part").get());
}

TEST_F(LibraryResolution, SysMLMetadataDefinitionsReachKerMLThroughImports) {
    // SysML.sysml: `public import KerML::Kernel::*` (which re-exports Core and Root): `metadata def Definition specializes Classifier`.
    const auto definition = std::dynamic_pointer_cast<KerML::Entities::Classifier>(workspace->find("SysML::Systems::Definition"));
    ASSERT_NE(definition, nullptr);
    ASSERT_FALSE(definition->ownedSubclassification().empty());
    EXPECT_EQ(definition->ownedSubclassification().front()->superclassifier().get(), workspace->find("KerML::Core::Classifier").get());
}

TEST_F(LibraryResolution, AUnitOfTheLibraryThatIsNotImportedIsHinted) {
    // `min` is the short name of SI::minute (a feature); the functions RealFunctions::min etc. are no features. SI is not imported by ISQ.
    const size_t user = workspace->addText("package U { private import ISQ::*; attribute r = 3000 [min^-1]; }", "user.sysml", SourceLanguage::SysML, 1);
    workspace->resolve();
    const auto warnings = workspace->unresolvedAsWarnings(user);
    std::string all;
    for (const auto& warning : warnings) all += warning->description() + "\n";
    ASSERT_FALSE(warnings.empty());
    EXPECT_NE(all.find("unresolved reference to feature 'min'; SI::minute (short name 'min') is not visible here: add 'private import SI::*;'"), std::string::npos) << all;
    EXPECT_EQ(all.find("standard library"), std::string::npos);
    // (the placeholder source is emptied again for the other tests)
    workspace->replaceSource(user, "", SourceLanguage::SysML);
    workspace->resolve();
}

// A unit written in the multiplicity (`attribute m : X [kg] = 3;`) is reported; the unit belongs after the value (`= 3 [kg]`).
namespace {
    /// A mini library with a unit (sources 0 - 2) and a user text.
    struct UnitFixture {
        Workspace ws;
        size_t user = 0;
        UnitFixture(const std::string& userText, SourceLanguage language = SourceLanguage::SysML) {
            // (the package Base marks the standard library as loaded: no hint about it)
            ws.addText("standard library package Base { abstract classifier Anything; }", "Base.kerml", SourceLanguage::KerML);
            ws.addText("package MeasurementReferences { abstract attribute def ScalarMeasurementReference; abstract attribute def MeasurementUnit :> ScalarMeasurementReference; }",
                       "MeasurementReferences.sysml");
            ws.addText("package SI { private import MeasurementReferences::*; attribute <kg> kilogram : MeasurementUnit; }", "SI.sysml");
            user = ws.addText(userText, "user.sysml", language);
            ws.resolve();
        }
        std::vector<std::string> warnings() const {
            std::vector<std::string> texts;
            for (const auto& warning : ws.unresolvedAsWarnings(user)) texts.push_back(warning->description());
            return texts;
        }
    };

    /// The number of warnings that remark on a multiplicity.
    size_t unitWarnings(const std::vector<std::string>& texts) {
        return static_cast<size_t>(std::count_if(texts.begin(), texts.end(), [](const std::string& text) { return text.find("multiplicity") != std::string::npos; }));
    }
}

TEST(UnitInMultiplicity, AnUnresolvedUnitExpressionIsHinted) {
    UnitFixture f("package U { attribute def X; attribute m : X ['kg*s^-1'] = 1; }");
    const auto warnings = f.warnings();
    ASSERT_EQ(warnings.size(), 1u);
    EXPECT_NE(warnings[0].find("unresolved reference to feature ''kg*s^-1'' in the multiplicity of 'm'; '[...]' after a type is a multiplicity, not a unit: "
                               "write the unit after the value, e.g. '= <value> [kg*s^-1]' (inside quotes, '*', '/' and '^' are part of one name, not operators)"),
              std::string::npos) << warnings[0];
}

TEST(UnitInMultiplicity, AUnitThatIsNotImportedIsHinted) {
    UnitFixture f("package U { attribute def X; attribute m : X [kg] = 1; }");
    const auto warnings = f.warnings();
    ASSERT_EQ(warnings.size(), 1u);
    EXPECT_NE(warnings[0].find("in the multiplicity of 'm'"), std::string::npos) << warnings[0];
    EXPECT_NE(warnings[0].find("SI::kilogram (short name 'kg') is not visible here: add 'private import SI::*;'"), std::string::npos) << warnings[0];
    EXPECT_NE(warnings[0].find("not a unit"), std::string::npos) << warnings[0];
}

TEST(UnitInMultiplicity, AResolvedUnitIsReported) {
    UnitFixture f("package U {\n  private import SI::*;\n  attribute def X;\n  attribute m : X [kg] = 1;\n}");
    const auto warnings = f.warnings();
    ASSERT_EQ(warnings.size(), 1u);
    EXPECT_EQ(warnings[0],
              "the multiplicity of 'm' refers to the measurement unit SI::kilogram ('kg'): '[...]' after a type is a multiplicity, not a unit; "
              "write the unit after the value, e.g. '= <value> [kg]'");
    const auto positions = f.ws.unresolvedAsWarnings(f.user);
    ASSERT_EQ(positions.size(), 1u);
    EXPECT_EQ(positions[0]->errorType(), SysMLv2::Files::ErrorType::WARNING);
    EXPECT_EQ(positions[0]->getLine(), 4);
    EXPECT_EQ(positions[0]->getSource(), "user.sysml");
}

TEST(UnitInMultiplicity, WarningsAreOrderedByPosition) {
    UnitFixture f("package U {\n  private import SI::*;\n  attribute def X;\n  attribute a : X [kg] = 1;\n  attribute b : Nope;\n  attribute c : X ['m/s'] = 1;\n  attribute d : X [kg] = 1;\n}");
    const auto warnings = f.ws.unresolvedAsWarnings(f.user);
    ASSERT_EQ(warnings.size(), 4u);
    EXPECT_EQ(warnings[0]->getLine(), 4);
    EXPECT_NE(warnings[0]->description().find("the multiplicity of 'a' refers to the measurement unit SI::kilogram"), std::string::npos) << warnings[0]->description();
    EXPECT_EQ(warnings[1]->getLine(), 5);
    EXPECT_NE(warnings[1]->description().find("unresolved reference to type 'Nope'"), std::string::npos) << warnings[1]->description();
    EXPECT_EQ(warnings[2]->getLine(), 6);
    EXPECT_NE(warnings[2]->description().find("in the multiplicity of 'c'"), std::string::npos) << warnings[2]->description();
    EXPECT_EQ(warnings[3]->getLine(), 7);
    EXPECT_NE(warnings[3]->description().find("the multiplicity of 'd' refers"), std::string::npos) << warnings[3]->description();
}

TEST(UnitInMultiplicity, AnUnknownSourceHasNoWarnings) {
    UnitFixture f("package U { attribute def X; attribute m : X [kg] = 1; }");
    EXPECT_TRUE(f.ws.unresolvedAsWarnings(99).empty());
}

TEST(UnitInMultiplicity, ARedefiningFeatureIsNamedByTheFeatureItRedefines) {
    UnitFixture f("package U {\n  private import SI::*;\n  attribute def X;\n  part def Base { attribute mass : X; }\n  part def Car :> Base { attribute :>> mass [kg]; }\n}");
    const auto warnings = f.warnings();
    ASSERT_EQ(warnings.size(), 1u);
    EXPECT_NE(warnings[0].find("the multiplicity of 'mass' refers to the measurement unit SI::kilogram"), std::string::npos) << warnings[0];
}

TEST(UnitInMultiplicity, AQualifiedShortNameIsRenderedFromTheUnit) {
    UnitFixture f("package U {\n  attribute def X;\n  attribute a : X [SI::kg];\n}");
    const auto warnings = f.warnings();
    ASSERT_EQ(warnings.size(), 1u);
    EXPECT_NE(warnings[0].find("refers to the measurement unit SI::kilogram ('kg'): "), std::string::npos) << warnings[0];
    EXPECT_NE(warnings[0].find("e.g. '= <value> [SI::kg]'"), std::string::npos) << warnings[0];
}

TEST(UnitInMultiplicity, RangeSubsettingAndMultiplicityElements) {
    UnitFixture f(
        "package U {\n  private import SI::*;\n  attribute def X;\n  attribute y : X;\n  attribute a : X [1..kg];\n  attribute x :> y [kg];\n"
        "  attribute b : X [kg..*];\n}");
    const auto warnings = f.warnings();
    ASSERT_EQ(warnings.size(), 3u);
    EXPECT_NE(warnings[0].find("the multiplicity of 'a' refers"), std::string::npos) << warnings[0];
    EXPECT_NE(warnings[1].find("the multiplicity of 'x' refers"), std::string::npos) << warnings[1];
    EXPECT_NE(warnings[2].find("the multiplicity of 'b' refers"), std::string::npos) << warnings[2];
    UnitFixture kerml("package U { private import SI::*; classifier X; feature f : X; multiplicity m [kg]; }", SourceLanguage::KerML);
    const auto kermlWarnings = kerml.warnings();
    ASSERT_EQ(kermlWarnings.size(), 1u);
    EXPECT_NE(kermlWarnings[0].find("the multiplicity of 'm' refers"), std::string::npos) << kermlWarnings[0];
}

TEST(UnitInMultiplicity, OtherBoundsAndUnitsAfterTheValueAreNotRemarkedOn) {
    UnitFixture f(
        "package U {\n  private import SI::*;\n  attribute def X;\n  attribute n = 3;\n  attribute a : X [n];\n  attribute b : X [0..*];\n  attribute c : X [1];\n"
        "  attribute d : X [n..*];\n  attribute m : X = 1 [kg];\n}");
    EXPECT_EQ(unitWarnings(f.warnings()), 0u);
    UnitFixture missing("package U { attribute def X; attribute a : X [n]; attribute m : X = 1 ['kg*s^-1']; }");
    const auto warnings = missing.warnings();
    ASSERT_EQ(warnings.size(), 2u);
    EXPECT_EQ(warnings[0], "unresolved reference to feature 'n'");
    EXPECT_EQ(unitWarnings(warnings), 0u);
}

TEST(UnitInMultiplicity, AReturnFeatureOfAFunctionOrCalculation) {
    UnitFixture f(
        "package U {\n  private import SI::*;\n  attribute def X;\n"
        "  calc def F { in a : X; in b : X; return feature airMassFlow : X ['kg*s^-1'] = (a * 256 + b) * 0.01; }\n"
        "  function G { return feature mass : X [kg] = 1; }\n}");
    const auto warnings = f.warnings();
    ASSERT_EQ(warnings.size(), 2u);
    EXPECT_NE(warnings[0].find("unresolved reference to feature ''kg*s^-1'' in the multiplicity of 'airMassFlow'; '[...]' after a type"), std::string::npos) << warnings[0];
    EXPECT_NE(warnings[1].find("the multiplicity of 'mass' refers to the measurement unit SI::kilogram ('kg')"), std::string::npos) << warnings[1];
}

TEST(UnitInMultiplicity, OnlyAFeatureTypedByAUnitIsReported) {
    UnitFixture unit("package U { private import MeasurementReferences::*; attribute def X; attribute n : MeasurementUnit; attribute a : X [n]; }");
    EXPECT_EQ(unitWarnings(unit.warnings()), 1u);
    UnitFixture plain("package U { private import SI::*; attribute def X; attribute n : X; attribute a : X [n]; }");
    EXPECT_EQ(unitWarnings(plain.warnings()), 0u);
}

TEST(UnitInMultiplicity, KerML) {
    UnitFixture f("package U { private import SI::*; classifier X; feature m : X [kg]; feature q : X ['kg*s^-1']; feature n; feature o : X [n]; }",
                  SourceLanguage::KerML);
    const auto warnings = f.warnings();
    ASSERT_EQ(warnings.size(), 2u);
    EXPECT_NE(warnings[0].find("the multiplicity of 'm' refers to the measurement unit SI::kilogram ('kg')"), std::string::npos) << warnings[0];
    EXPECT_NE(warnings[1].find("unresolved reference to feature ''kg*s^-1'' in the multiplicity of 'q'; '[...]' after a type is a multiplicity"), std::string::npos) << warnings[1];
}

TEST_F(LibraryResolution, UnitsInAMultiplicityAreReported) {
    const std::string model =
        "package U {\n"
        "  private import ScalarValues::*;\n  private import ISQ::*;\n  private import SI::*;\n"
        "  part def P {\n"
        "    attribute q : MassFlowRateValue ['kg*s^-1'] = 1;\n"
        "    attribute r : MassFlowRateValue ['kg\xE2\x8B\x85s\xE2\x81\xBB\xC2\xB9'] = 1;\n"
        "    attribute s : MassValue [kg] = 1;\n"
        "    attribute t : MassValue = 1 [kg];\n"
        "  }\n}";
    const size_t user = workspace->addText(model, "user.sysml", SourceLanguage::SysML, 1);
    workspace->resolve();
    std::vector<std::string> texts;
    std::string all;
    for (const auto& warning : workspace->unresolvedAsWarnings(user)) {
        texts.push_back(warning->description());
        all += warning->description() + "\n";
    }
    std::cout << all;
    ASSERT_EQ(texts.size(), 3u) << all;
    EXPECT_NE(texts[0].find("in the multiplicity of 'q'; '[...]' after a type is a multiplicity, not a unit"), std::string::npos) << all;
    EXPECT_NE(texts[1].find("the multiplicity of 'r' refers to the measurement unit SI::"), std::string::npos) << all;
    EXPECT_NE(texts[2].find("the multiplicity of 's' refers to the measurement unit SI::kilogram ('kg')"), std::string::npos) << all;
    // (the placeholder source is emptied again for the other tests)
    workspace->replaceSource(user, "", SourceLanguage::SysML);
    workspace->resolve();
}

// ---------------------------------------------------------------------------------------------------------------------
// Workspace::replaceSource: exchange one source, keep the others (library) resolved
// ---------------------------------------------------------------------------------------------------------------------

/// A small "library" (source 0) and a replaceable user text (source 1) that imports it.
struct ReplaceFixture {
    Workspace ws;
    size_t library = 0;
    size_t user = 0;
    ReplaceFixture() {
        library = ws.addText("package Lib { part def Base; part def Other { part inner : Base; } part def Broken : Missing; }", "lib.sysml");
        user = ws.addText("package U { import Lib::*; part x : Base; }", "user.sysml");
        ws.resolve();
    }
    size_t unresolvedOf(size_t source) const {
        size_t count = 0;
        for (const auto& info : ws.unresolvedReferences()) {
            if (info.source == source) ++count;
        }
        return count;
    }
};

TEST(ReplaceSource, ReplacedTextIsResolvedAgainstTheOtherSources) {
    ReplaceFixture f;
    EXPECT_EQ(f.unresolvedOf(f.user), 0u);
    const auto oldX = f.ws.find("U::x");
    ASSERT_NE(oldX, nullptr);

    f.ws.replaceSource(f.user, "package V { import Lib::*; part y : Other; part z : Base; }");
    f.ws.resolve();

    EXPECT_EQ(f.ws.sourceCount(), 2u);
    EXPECT_EQ(f.ws.sourceName(f.user), "user.sysml");
    EXPECT_EQ(f.ws.find("U::x"), nullptr);
    EXPECT_NE(f.ws.find("V::y"), nullptr);
    EXPECT_EQ(f.unresolvedOf(f.user), 0u);
    EXPECT_EQ(typeOf(f.ws, "V::y").get(), f.ws.find("Lib::Other").get());
    EXPECT_EQ(typeOf(f.ws, "V::z").get(), f.ws.find("Lib::Base").get());
    EXPECT_NE(f.ws.find("U::x"), oldX);
}

TEST(ReplaceSource, UnresolvedReferencesAppearAndDisappear) {
    ReplaceFixture f;
    EXPECT_EQ(f.unresolvedOf(f.user), 0u);

    f.ws.replaceSource(f.user, "package U { import Lib::*; part x : Nope; part y : AlsoNope; }");
    f.ws.resolve();
    EXPECT_EQ(f.unresolvedOf(f.user), 2u);
    const auto warnings = f.ws.unresolvedAsWarnings(f.user);
    ASSERT_EQ(warnings.size(), 2u);
    EXPECT_EQ(warnings[0]->getSource(), "user.sysml");

    f.ws.replaceSource(f.user, "package U { import Lib::*; part x : Nope; }");
    f.ws.resolve();
    EXPECT_EQ(f.unresolvedOf(f.user), 1u);

    f.ws.replaceSource(f.user, "package U { import Lib::*; part x : Base; }");
    f.ws.resolve();
    EXPECT_EQ(f.unresolvedOf(f.user), 0u);
    EXPECT_TRUE(f.ws.errors(f.user).empty());
}

TEST(ReplaceSource, ReplacingDropsTheOldErrorsAndElements) {
    ReplaceFixture f;
    f.ws.replaceSource(f.user, "package U { part def ;;; }");
    f.ws.resolve();
    EXPECT_FALSE(f.ws.errors(f.user).empty());

    f.ws.replaceSource(f.user, "package U { part def A; }");
    f.ws.resolve();
    EXPECT_TRUE(f.ws.errors(f.user).empty());

    f.ws.replaceSource(f.user, "");
    f.ws.resolve();
    EXPECT_TRUE(f.ws.elements(f.user).empty());
    EXPECT_EQ(f.ws.rootNamespace(f.user), nullptr);
    EXPECT_EQ(f.unresolvedOf(f.user), 0u);
    EXPECT_EQ(f.ws.find("U::A"), nullptr);
}

TEST(ReplaceSource, OtherSourcesKeepTheirResolvedAndUnresolvedReferences) {
    ReplaceFixture f;
    const auto inner = typeOf(f.ws, "Lib::Other::inner");
    ASSERT_NE(inner, nullptr);
    EXPECT_EQ(inner.get(), f.ws.find("Lib::Base").get());
    EXPECT_EQ(f.unresolvedOf(f.library), 1u);  // `Missing`
    const size_t libraryReferences = f.ws.referenceCount() - 2;  // everything but the two references of the user text (import, type)

    for (int round = 0; round < 3; ++round) {
        f.ws.replaceSource(f.user, "package U" + std::to_string(round) + " { import Lib::*; part x : Base; part y : Gone; }");
        f.ws.resolve();
        EXPECT_EQ(typeOf(f.ws, "Lib::Other::inner").get(), inner.get());
        EXPECT_EQ(f.unresolvedOf(f.library), 1u);
        EXPECT_EQ(f.unresolvedOf(f.user), 1u);
        EXPECT_EQ(f.ws.resolvedReferenceCount(), libraryReferences - 1 + 2);  // library: all but `Missing`; user: import and `Base`
    }
    // The replaced source is not mentioned in the list of the library's unresolved references.
    for (const auto& info : f.ws.unresolvedReferences()) {
        EXPECT_TRUE(info.source == f.library || info.source == f.user);
        EXPECT_EQ(info.sourceName, info.source == f.library ? "lib.sysml" : "user.sysml");
    }
}

TEST(ReplaceSource, MultipleReplacementsGiveTheSameResultAsAFreshWorkspace) {
    ReplaceFixture f;
    const std::vector<std::string> texts = {
        "package U { import Lib::*; part x : Base; }",
        "package U { part x : Base; }",
        "package W { import Lib::*; part a : Other; part b : Base; part c : Missing2; }",
        "package W { import Lib::Base; part a : Base; }",
        "package U { import Lib::*; part x : Base; }",
    };
    for (const auto& text : texts) {
        f.ws.replaceSource(f.user, text);
        f.ws.resolve();

        Workspace fresh;
        fresh.addText("package Lib { part def Base; part def Other { part inner : Base; } part def Broken : Missing; }", "lib.sysml");
        const size_t freshUser = fresh.addText(text, "user.sysml");
        fresh.resolve();
        EXPECT_EQ(f.unresolvedOf(f.user), [&] {
            size_t count = 0;
            for (const auto& info : fresh.unresolvedReferences()) count += info.source == freshUser ? 1 : 0;
            return count;
        }()) << text;
        EXPECT_EQ(f.ws.elements(f.user).size(), fresh.elements(freshUser).size()) << text;
        EXPECT_EQ(f.ws.resolvedReferenceCount(), fresh.resolvedReferenceCount()) << text;
    }
}

TEST(ReplaceSource, KeepsTheLanguageOfTheSourceUnlessGiven) {
    Workspace ws;
    const size_t kerml = ws.addText("package K { class A; }", "k.kerml");
    ws.replaceSource(kerml, "package K { class B; classifier C specializes B; }");
    ws.resolve();
    EXPECT_TRUE(ws.errors(kerml).empty());
    EXPECT_NE(ws.find("K::B"), nullptr);
    EXPECT_TRUE(ws.unresolvedReferences().empty());

    ws.replaceSource(kerml, "package S { part def A; }", SourceLanguage::SysML);
    ws.resolve();
    EXPECT_TRUE(ws.errors(kerml).empty());
    EXPECT_NE(ws.find("S::A"), nullptr);
    EXPECT_THROW(ws.replaceSource(7, "package X;"), std::out_of_range);
}

TEST(ReplaceSource, ReplacedElementsAreFreed) {
    Workspace ws;
    ws.addText("package Lib { part def Base; part def Other :> Base { part inner : Base; } }", "lib.sysml");
    const size_t user = ws.addText("package U { import Lib::*; }", "user.sysml");
    ws.resolve();
    for (int round = 0; round < 5; ++round) {
        ws.replaceSource(user, "package U { import Lib::*; part def A :> Other { part p : A; part q : Base; attribute n; } part a : A; part gone : Nope; }");
        ws.resolve();
        std::vector<std::weak_ptr<KerML::Entities::Element>> probes;
        for (const auto& element : ws.elements(user)) probes.push_back(element);
        probes.push_back(ws.rootNamespace(user));
        for (const auto& info : ws.unresolvedReferences()) probes.push_back(info.placeholder);
        ASSERT_GT(probes.size(), 10u);
        ws.replaceSource(user, "package U { }");
        size_t alive = 0;
        for (const auto& probe : probes) alive += probe.expired() ? 0 : 1;
        EXPECT_EQ(alive, 0u) << "round " << round << " of " << probes.size() << " elements";
    }
    // The library is intact.
    ws.resolve();
    EXPECT_TRUE(ws.find("Lib::Other::inner") != nullptr);
    EXPECT_EQ(typeOf(ws, "Lib::Other::inner").get(), ws.find("Lib::Base").get());
}

TEST(ReplaceSource, ReferenceNamesAreAvailableBeforeResolve) {
    Workspace ws;
    const size_t user = ws.addText("package U { import ISQ::*; part x : Parts::Part; }", "user.sysml");
    const auto names = ws.referenceNames(user);
    EXPECT_NE(std::find(names.begin(), names.end(), "ISQ"), names.end());
    EXPECT_NE(std::find(names.begin(), names.end(), "Parts::Part"), names.end());
}

// ---------------------------------------------------------------------------------------------------------------------
// Source levels
// ---------------------------------------------------------------------------------------------------------------------

namespace {
size_t unresolvedIn(const Workspace& ws, size_t source) {
    size_t count = 0;
    for (const auto& info : ws.unresolvedReferences()) count += info.source == source ? 1 : 0;
    return count;
}
// The library refers to two names it does not define (`Missing`, a top-level element, and the package `Foo`), which the model defines.
const char* LevelLibrary = "package Lib { part def Base; part uses : Missing; }\npackage Lib2 { public import Lib::*; part b : Base; }\npackage Lib3 { import Foo::*; }";
const char* LevelUser = "part def Missing;\npackage Foo { part def F; }\npackage U { import Lib2::*; part x : Base; part m : Missing; part f : Foo::F; }";
}

TEST(SourceLevels, WithoutLevelsALibraryReferenceCanResolveToAModelElement) {
    Workspace ws;
    const size_t library = ws.addText(LevelLibrary, "lib.sysml");
    ws.addText(LevelUser, "user.sysml");
    ws.resolve();
    EXPECT_EQ(unresolvedIn(ws, library), 0u);  // `Missing` and `Foo` of the library found the elements of the model: the problem the levels solve
}

TEST(SourceLevels, ALibraryReferenceNeverResolvesToAHigherLevel) {
    Workspace ws;
    const size_t library = ws.addText(LevelLibrary, "lib.sysml", SourceLanguage::Auto, 0);
    const size_t user = ws.addText(LevelUser, "user.sysml", SourceLanguage::Auto, 2);
    EXPECT_EQ(ws.sourceLevel(library), 0);
    EXPECT_EQ(ws.sourceLevel(user), 2);
    ws.resolve();
    EXPECT_EQ(unresolvedIn(ws, library), 2u);   // `Missing` and `Foo` stay unresolved in the library
    EXPECT_EQ(unresolvedIn(ws, user), 0u);      // the model sees the library (Base through Lib2) and its own Missing and Foo
    EXPECT_EQ(typeOf(ws, "U::x").get(), ws.find("Lib::Base").get());
    // Replacing the model keeps the level, and the library stays clean.
    ws.replaceSource(user, LevelUser);
    ws.resolve();
    EXPECT_EQ(ws.sourceLevel(user), 2);
    EXPECT_EQ(unresolvedIn(ws, library), 2u);
}

TEST(SourceLevels, EqualLevelsSeeEachOtherAndAMiddleLevelSeesTheLowerOnly) {
    Workspace ws;
    const size_t a = ws.addText("package A { part def X; part ya : B::Y; }", "a.sysml", SourceLanguage::Auto, 1);
    const size_t b = ws.addText("package B { part def Y; part xb : A::X; }", "b.sysml", SourceLanguage::Auto, 1);
    ws.resolve();
    EXPECT_EQ(unresolvedIn(ws, a), 0u);
    EXPECT_EQ(unresolvedIn(ws, b), 0u);

    Workspace levels;
    const size_t low = levels.addText("package A { part def X; part ya : B::Y; }", "a.sysml", SourceLanguage::Auto, 0);
    const size_t high = levels.addText("package B { part def Y; part xb : A::X; }", "b.sysml", SourceLanguage::Auto, 1);
    levels.resolve();
    EXPECT_EQ(unresolvedIn(levels, low), 1u);   // `B::Y` is in the higher source
    EXPECT_EQ(unresolvedIn(levels, high), 0u);
}

TEST(SourceLevels, ImplicitGeneralsAreNotShadowedByAModel) {
    Workspace ws;
    ws.addText("standard library package Base { abstract classifier Anything; abstract feature things : Anything; }\n"
               "package Parts { part def Part; }", "lib.kerml", SourceLanguage::KerML, 0);
    const size_t user = ws.addText("package Base { part def Fake; }\npackage U { part def A; part a : A; }", "user.sysml", SourceLanguage::SysML, 2);
    ws.resolve();
    EXPECT_EQ(unresolvedIn(ws, user), 0u);
    const auto a = as<KerML::Entities::Feature>(ws.find("U::a"));
    ASSERT_NE(a, nullptr);
}

TEST(SourceLevels, AnAliasOfAHigherLevelIsInvisibleToALowerOne) {
    const char* library = "package Lib { part def Base; part uses : Shortcut; }";
    // (an alias at the top level is KerML only)
    const char* model = "alias Shortcut for Lib::Base;\npackage U { feature x : Shortcut; }";
    Workspace ws;
    const size_t lib = ws.addText(library, "lib.sysml", SourceLanguage::Auto, 0);
    const size_t user = ws.addText(model, "user.kerml", SourceLanguage::KerML, 2);
    ws.resolve();
    EXPECT_EQ(unresolvedIn(ws, lib), 1u);
    EXPECT_EQ(unresolvedIn(ws, user), 0u);
}

// ---------------------------------------------------------------------------------------------------------------------
// Incremental resolution: a source that is added after a resolve() is added to the index of the resolver, which is not built again
// ---------------------------------------------------------------------------------------------------------------------

/// "<source name>:<line>:<name>" of every unresolved reference.
std::set<std::string> unresolvedKeys(const Workspace& ws) {
    std::set<std::string> keys;
    for (const auto& info : ws.unresolvedReferences()) keys.insert(info.sourceName + ":" + std::to_string(info.line) + ":" + info.name);
    return keys;
}

/// What a workspace that resolved in several steps and one that resolved once have to agree on.
/// (@p targets: also what every reference resolved to, see ConformanceTest::resolvedGenerals(). A reference binds to what is known when it is
/// resolved and is not looked at again, so the targets only have to agree if everything a reference needs was added before it was resolved.)
void expectSameResolution(const Workspace& steps, const Workspace& once, const std::string& what, bool targets = true) {
    EXPECT_EQ(steps.sourceCount(), once.sourceCount()) << what;
    EXPECT_EQ(steps.referenceCount(), once.referenceCount()) << what;
    EXPECT_EQ(steps.resolvedReferenceCount(), once.resolvedReferenceCount()) << what;
    EXPECT_EQ(steps.unresolvedReferences().size(), once.unresolvedReferences().size()) << what;
    EXPECT_EQ(unresolvedKeys(steps), unresolvedKeys(once)) << what;
    EXPECT_EQ(steps.elements().size(), once.elements().size()) << what;
    if (targets) ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(steps.elements()), ConformanceTest::resolvedGenerals(once.elements()), what);
}

// The documented differences of the library loaded file by file against the whole library (see the test, 7 references: a reference binds to
// what is known when it is resolved): the lines of resolvedGenerals() (sorted) that only one of the two workspaces has.
const std::vector<std::string> ExpectedStepwiseDifferencesFromSteps = {
    "Interfaces::participant::thisParticipant :> Base::Anything::self,",
    "ShapeItems::ConeOrCylinder::af::innerSpaceDimension :> Objects::StructuredSpaceObject::StructuredSurface::innerSpaceDimension, Objects::StructuredSpaceObject::innerSpaceDimension,",
    "ShapeItems::ConeOrCylinder::base::innerSpaceDimension :> Objects::StructuredSpaceObject::StructuredSurface::innerSpaceDimension, Objects::StructuredSpaceObject::innerSpaceDimension,",
    "ShapeItems::CuboidOrTriangularPrism::ff::edges :> ShapeItems::Polygon::edges, ShapeItems::Polyhedron::faces::edges,",
    "ShapeItems::CuboidOrTriangularPrism::rf::edges :> ShapeItems::Polygon::edges, ShapeItems::Polyhedron::faces::edges,",
    "ShapeItems::Disc::edges::innerSpaceDimension :> Objects::StructuredSpaceObject::innerSpaceDimension, Objects::StructuredSpaceObject::StructuredCurve::innerSpaceDimension,",
    "ShapeItems::Polyhedron::faces::innerSpaceDimension :> Objects::StructuredSpaceObject::StructuredCurve::innerSpaceDimension, Objects::StructuredSpaceObject::innerSpaceDimension,",
};
const std::vector<std::string> ExpectedStepwiseDifferencesFromWhole = {
    "Interfaces::participant::thisParticipant :> Ports::Port::self,",
    "ShapeItems::ConeOrCylinder::af::innerSpaceDimension :> Objects::StructuredSpaceObject::StructuredSurface::innerSpaceDimension, Objects::StructuredSpaceObject::StructuredSurface::innerSpaceDimension,",
    "ShapeItems::ConeOrCylinder::base::innerSpaceDimension :> Objects::StructuredSpaceObject::StructuredSurface::innerSpaceDimension, Objects::StructuredSpaceObject::StructuredSurface::innerSpaceDimension,",
    "ShapeItems::CuboidOrTriangularPrism::ff::edges :> ShapeItems::Polygon::edges, Objects::StructuredSpaceObject::faces::edges,",
    "ShapeItems::CuboidOrTriangularPrism::rf::edges :> ShapeItems::Polygon::edges, Objects::StructuredSpaceObject::faces::edges,",
    "ShapeItems::Disc::edges::innerSpaceDimension :> Objects::StructuredSpaceObject::StructuredCurve::innerSpaceDimension, Objects::StructuredSpaceObject::StructuredCurve::innerSpaceDimension,",
    "ShapeItems::Polyhedron::faces::innerSpaceDimension :> Objects::StructuredSpaceObject::StructuredCurve::innerSpaceDimension, Objects::StructuredSpaceObject::StructuredSurface::innerSpaceDimension,",
};

TEST(IncrementalResolution, LibraryInStepsGivesTheSameResultAsTheWholeLibrary) {
    const auto files = ConformanceTest::listFiles(SYSML_LIBRARY_DIR, {".sysml", ".kerml"});
    Workspace whole;
    EXPECT_EQ(whole.loadLibrary(SYSML_LIBRARY_DIR), files.size());
    whole.resolve();

    Workspace steps;
    for (const auto& file : files) {
        steps.addFile(file.string());
        steps.resolve();
    }
    expectSameResolution(steps, whole, "library file by file", false);
    EXPECT_TRUE(steps.errors().empty());
    // The targets differ for the references that bind to what is known when they are resolved (Interfaces is resolved before Ports is
    // there, and its `thisParticipant :>> self` binds to what it found then): exactly these lines, in this workspace and not in the other.
    {
        const auto stepLines = ConformanceTest::resolvedGenerals(steps.elements());
        const auto wholeLines = ConformanceTest::resolvedGenerals(whole.elements());
        std::vector<std::string> onlySteps, onlyWhole;
        std::set_difference(stepLines.begin(), stepLines.end(), wholeLines.begin(), wholeLines.end(), std::back_inserter(onlySteps));
        std::set_difference(wholeLines.begin(), wholeLines.end(), stepLines.begin(), stepLines.end(), std::back_inserter(onlyWhole));
        EXPECT_EQ(onlySteps, ExpectedStepwiseDifferencesFromSteps) << "lines that only the file by file workspace has";
        EXPECT_EQ(onlyWhole, ExpectedStepwiseDifferencesFromWhole) << "lines that only the whole library workspace has";
    }

    // In the order of the dependencies (the kernel libraries, the systems library, the domain libraries) the results agree completely.
    Workspace batches;
    for (const char* part : {"/KerML/", "/SystemsLibrary/", "/DomainLibraries/"}) {
        for (const auto& file : files) {
            std::string path = file.generic_string();
            if (path.find(part) != std::string::npos) batches.addFile(file.string());
        }
        batches.resolve();
    }
    expectSameResolution(batches, whole, "library in batches");
}

TEST(IncrementalResolution, ReferencesToLaterSourcesStayUnresolvedUntilTheyAreAdded) {
    Workspace steps;
    const size_t a = steps.addText("package A { part x : B::Y; part z : B::Missing; }", "a.sysml");
    steps.resolve();
    EXPECT_EQ(unresolvedIn(steps, a), 2u);

    steps.addText("package B { part def Y; }", "b.sysml");
    steps.resolve();
    EXPECT_EQ(unresolvedIn(steps, a), 1u);
    EXPECT_EQ(typeOf(steps, "A::x").get(), steps.find("B::Y").get());

    Workspace once;
    once.addText("package A { part x : B::Y; part z : B::Missing; }", "a.sysml");
    once.addText("package B { part def Y; }", "b.sysml");
    once.resolve();
    expectSameResolution(steps, once, "later source");
}

TEST(IncrementalResolution, NamesOfAnonymousRedefinitionsAreRegisteredOnce) {
    // `part redefines p` has no name of its own: it is known as `p` from its (pending) redefinition on, and `q :>> p` refers to it.
    const char* user = "package U { part def B :> L::A { part :>> p; part q :>> p; } }";
    const char* library = "package L { part def A { part p; } }";
    Workspace steps;
    steps.addText(user, "user.sysml");
    steps.resolve();
    steps.resolve();  // (nothing new: the pending redefinition is retried)
    steps.addText(library, "lib.sysml");
    steps.resolve();

    Workspace once;
    once.addText(user, "user.sysml");
    once.addText(library, "lib.sysml");
    once.resolve();
    expectSameResolution(steps, once, "anonymous redefinition", false);   // (the targets of q are checked below and in RedefinitionTargetDoesNotDependOnWhenTheLibraryIsAdded)
    EXPECT_TRUE(steps.unresolvedReferences().empty());
    EXPECT_TRUE(once.unresolvedReferences().empty());

    // The name p is registered once for B (not twice, not for the library), in both workspaces: there is one feature p among the members of B.
    for (const Workspace* ws : {&steps, &once}) {
        const auto b = ws->find("U::B");
        ASSERT_NE(b, nullptr);
        size_t featuresPOfB = 0;
        for (const auto& element : ws->elements()) {
            const auto feature = as<KerML::Entities::Feature>(element);
            if (feature && feature->owner() == b && feature->effectiveName().value_or("") == "p") ++featuresPOfB;   // (`part :>> p` has no declared name)
        }
        EXPECT_EQ(featuresPOfB, 1u);
    }

    // Per KerML a redefined feature is looked up through the general types of the owning type: `q :>> p` in B redefines the p of A. With
    // everything there at once it does.
    const auto q = as<KerML::Entities::Feature>(once.find("U::B::q"));
    ASSERT_NE(q, nullptr);
    ASSERT_FALSE(q->ownedSpecialization().empty());
    const auto target = q->ownedSpecialization().front()->general();
    ASSERT_NE(target, nullptr);
    EXPECT_FALSE(isUnresolved(target));
    EXPECT_EQ(target, once.find("L::A::p"));
}

// `q :>> p` redefines the p of L::A (redefined features are looked up via the general types of the owning type), not the feature of B that
// redefines p: while the library is missing the generals of B are unknown, and the redefinition is not accepted from what is found in B.
TEST(IncrementalResolution, RedefinitionTargetDoesNotDependOnWhenTheLibraryIsAdded) {
    const char* user = "package U { part def B :> L::A { part :>> p; part q :>> p; } }";
    const char* library = "package L { part def A { part p; } }";
    Workspace steps;
    steps.addText(user, "user.sysml");
    steps.resolve();
    steps.addText(library, "lib.sysml");
    steps.resolve();
    const auto q = as<KerML::Entities::Feature>(steps.find("U::B::q"));
    ASSERT_NE(q, nullptr);
    ASSERT_FALSE(q->ownedSpecialization().empty());
    EXPECT_EQ(q->ownedSpecialization().front()->general(), steps.find("L::A::p"));
}

TEST(IncrementalResolution, RedefinitionBindsToTheInheritedFeatureInBothLoadOrders) {
    const char* user = "package U { part def B :> L::A { part :>> p; part q :>> p; } }";
    const char* library = "package L { part def A { part p; } }";
    for (const bool libraryFirst : {false, true}) {
        Workspace ws;
        if (libraryFirst) {
            ws.addText(library, "lib.sysml");
            ws.resolve();
            ws.addText(user, "user.sysml");
        } else {
            ws.addText(user, "user.sysml");
            ws.addText(library, "lib.sysml");
        }
        ws.resolve();
        EXPECT_TRUE(ws.unresolvedReferences().empty()) << libraryFirst;
        const auto q = as<KerML::Entities::Feature>(ws.find("U::B::q"));
        ASSERT_NE(q, nullptr);
        ASSERT_FALSE(q->ownedSpecialization().empty());
        EXPECT_EQ(q->ownedSpecialization().front()->general(), ws.find("L::A::p")) << libraryFirst;
        // (the `:>> p` of B redefines it as well)
        const auto b = ws.find("U::B");
        for (const auto& element : ws.elements()) {
            const auto feature = as<KerML::Entities::Feature>(element);
            if (!feature || feature->owner() != b || feature->declaredName().has_value() || feature->effectiveName().value_or("") != "p") continue;
            ASSERT_FALSE(feature->ownedSpecialization().empty());
            EXPECT_EQ(feature->ownedSpecialization().front()->general(), ws.find("L::A::p")) << libraryFirst;
        }
    }
}

TEST(IncrementalResolution, RedefinitionWithAMissingGeneralStaysUnresolvedInsteadOfBindingToASibling) {
    // The general of B does not exist: `q :>> p` must not bind to the feature of B that redefines p (a sibling), it stays open.
    Workspace ws;
    ws.addText("package U { part def B :> Missing { part :>> p; part q :>> p; } }", "user.sysml");
    ws.resolve();
    ws.resolve();   // (retried, still open)
    const auto q = as<KerML::Entities::Feature>(ws.find("U::B::q"));
    ASSERT_NE(q, nullptr);
    bool boundToSibling = false;
    for (const auto& specialization : q->ownedSpecialization()) {
        const auto general = specialization->general();
        if (general && !isUnresolved(general)) boundToSibling = true;
    }
    EXPECT_FALSE(boundToSibling);
    bool qOpen = false;
    for (const auto& info : ws.unresolvedReferences()) {
        // (the reference is written in the feature q: its context element)
        const auto context = as<KerML::Entities::Feature>(info.context);
        if (info.name == "p" && context && context->declaredName().value_or("") == "q") qOpen = true;
    }
    EXPECT_TRUE(qOpen);
}

TEST(IncrementalResolution, PlaceholderOfAnUnresolvedQuotedNameHasTheNameWithoutQuotes) {
    Workspace ws;
    ws.addText("package U { part def B { part :>> 'x y'; part a : Missing::'q r'; part b : 'm n'; } }", "user.sysml");
    ws.resolve();
    std::set<std::string> names;
    for (const auto& info : ws.unresolvedReferences()) {
        ASSERT_NE(info.placeholder, nullptr) << info.name;
        names.insert(info.placeholder->declaredName().value_or("<none>"));
    }
    EXPECT_EQ(names, (std::set<std::string>{"x y", "q r", "m n"}));
}

TEST(IncrementalResolution, ReplaceSourceAfterIncrementalRunsGivesTheSameResultAsAFreshWorkspace) {
    const char* lib1 = "package Lib { part def Base; part def Other { part inner : Base; } part def Broken : Missing; }";
    const char* lib2 = "package Lib2 { public import Lib::*; part def Third :> Other; part uses : Absent; }";
    const std::vector<std::string> texts = {
        "package U { import Lib2::*; part x : Third; }",
        "package U { part x : Base; }",
        "package W { import Lib::*; part a : Other; part b : Base; part c : Missing2; }",
        "package W { import Lib2::Third; part a : Third; part b : Lib::Base; }",
        "package U { import Lib2::*; part x : Third; }",
    };

    Workspace steps;
    steps.addText(lib1, "lib1.sysml");
    steps.resolve();
    steps.addText(lib2, "lib2.sysml");
    steps.resolve();
    const size_t user = steps.addText(texts.front(), "user.sysml");
    steps.resolve();
    for (const auto& text : texts) {
        steps.replaceSource(user, text);
        steps.resolve();

        Workspace fresh;
        fresh.addText(lib1, "lib1.sysml");
        fresh.addText(lib2, "lib2.sysml");
        fresh.addText(text, "user.sysml");
        fresh.resolve();
        expectSameResolution(steps, fresh, text);
    }
}

namespace {
/// The general type of the (only) specialization of the unnamed feature that @p owner owns: the feature it redefines.
ElementPtr redefinedByTheAnonymousFeatureOf(const Workspace& ws, const std::string& ownerName) {
    const auto owner = ws.find(ownerName);
    for (const auto& element : ws.elements()) {
        const auto feature = as<KerML::Entities::Feature>(element);
        if (!feature || feature->declaredName().has_value() || feature->owner() != owner) continue;
        const auto specializations = feature->ownedSpecialization();
        if (!specializations.empty()) return specializations.front()->general();
    }
    return nullptr;
}
}

TEST(IncrementalResolution, AnonymousRedefinitionsKeepTheirEffectiveNamesWhenTheResolverIsBuiltAnew) {
    // `attribute :>> m` of Sub has no name: it is known as `m`, and the `:>> m` of My redefines it, not the m of Base.
    const char* library = "package L { part def Base { attribute m; } part def Sub :> Base { attribute :>> m; } }";
    const char* user = "package U { part def My :> L::Sub { attribute :>> m; } }";
    Workspace ws;
    ws.addText(library, "lib.sysml");
    ws.resolve();
    const size_t source = ws.addText(user, "user.sysml");
    ws.resolve();
    auto redefined = redefinedByTheAnonymousFeatureOf(ws, "U::My");
    ASSERT_NE(redefined, nullptr);
    EXPECT_EQ(redefined->owner(), ws.find("L::Sub"));

    // The resolver is built anew by replaceSource: what was resolved before (the library) must still give its names.
    ws.replaceSource(source, user);
    ws.resolve();
    redefined = redefinedByTheAnonymousFeatureOf(ws, "U::My");
    ASSERT_NE(redefined, nullptr);
    EXPECT_EQ(redefined->owner(), ws.find("L::Sub"));

    Workspace once;
    once.addText(library, "lib.sysml");
    once.addText(user, "user.sysml");
    once.resolve();
    ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(ws.elements()), ConformanceTest::resolvedGenerals(once.elements()), "replaced");
}

TEST(IncrementalResolution, GeneralsKeepTheOrderOfTheDeclarations) {
    // `S :> G1, G2` with G1 from a source that is added later: the specializations (and the lookup through the generals) stay G1, G2.
    const char* user = "package U { part def S :> L::G1, G2 { } part def G2 { attribute x; } }";
    const char* library = "package L { part def G1 { attribute x; } }";
    Workspace steps;
    steps.addText(user, "user.sysml");
    steps.resolve();
    steps.addText(library, "lib.sysml");
    steps.resolve();
    Workspace once;
    once.addText(user, "user.sysml");
    once.addText(library, "lib.sysml");
    once.resolve();
    ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(steps.elements()), ConformanceTest::resolvedGenerals(once.elements()), "generals order");
    ASSERT_NE(steps.find("L::G1"), nullptr);
    ASSERT_NE(steps.find("U::G2"), nullptr);
    ASSERT_NE(steps.find("U::S::x"), nullptr);
    ASSERT_NE(once.find("U::S::x"), nullptr);
    const auto s = as<KerML::Entities::Type>(steps.find("U::S"));
    ASSERT_NE(s, nullptr);
    ASSERT_EQ(s->ownedSpecialization().size(), 2u);
    EXPECT_EQ(s->ownedSpecialization()[0]->general().get(), steps.find("L::G1").get());
    EXPECT_EQ(s->ownedSpecialization()[1]->general().get(), steps.find("U::G2").get());
    // `x` is found through the generals in their order: G1 first.
    EXPECT_EQ(ConformanceTest::qualifiedNameOf(steps.find("U::S::x")), ConformanceTest::qualifiedNameOf(once.find("U::S::x")));
}

TEST(IncrementalResolution, FindAfterAddTextNeedsNoResolve) {
    Workspace ws;
    ws.addText("package Lib { part def Base; }", "lib.sysml");
    EXPECT_NE(ws.find("Lib::Base"), nullptr);    // (the index is built by find() without a resolve)
    ws.resolve();

    ws.addText("package U { import Lib::*; part def X :> Base; part x : X; }", "user.sysml");
    EXPECT_NE(ws.find("U::X"), nullptr);
    EXPECT_NE(ws.find("U::x"), nullptr);
    EXPECT_NE(ws.find("Lib::Base"), nullptr);
    EXPECT_EQ(ws.find("U::Nope"), nullptr);

    ws.addText("package V { part def Y; }", "v.sysml");
    EXPECT_NE(ws.find("V::Y"), nullptr);
    EXPECT_NE(ws.find("U::X"), nullptr);

    // The references of the added sources are still resolved by the next resolve().
    ws.resolve();
    EXPECT_TRUE(ws.unresolvedReferences().empty());
    EXPECT_EQ(typeOf(ws, "U::x").get(), ws.find("U::X").get());
}

TEST(IncrementalResolution, ASourceOfALowerLevelNeedsAFullRebuildAndGivesTheSameResult) {
    const char* library = "standard library package Base { abstract classifier Anything; abstract feature things : Anything; }\npackage Parts { part def Part; }";
    const char* model = "package Base { part def Fake; }\npackage U { part def A; part a : A; part ref : Parts::Part; }";

    Workspace steps;
    const size_t user = steps.addText(model, "user.sysml", SourceLanguage::SysML, 2);
    steps.resolve();
    EXPECT_EQ(unresolvedIn(steps, user), 1u);   // Parts is not loaded yet
    steps.addText(library, "lib.kerml", SourceLanguage::KerML, 0);
    steps.resolve();

    Workspace once;
    once.addText(model, "user.sysml", SourceLanguage::SysML, 2);
    once.addText(library, "lib.kerml", SourceLanguage::KerML, 0);
    once.resolve();
    expectSameResolution(steps, once, "lower level added later");
    EXPECT_EQ(unresolvedIn(steps, user), unresolvedIn(once, user));
}

// ---------------------------------------------------------------------------------------------------------------------
// Incremental replaceSource: a document above its libraries is exchanged in the index of the resolver, which is not built again
// ---------------------------------------------------------------------------------------------------------------------

namespace {
/// What one source resolved to, and what stayed unresolved, written as lines.
/// (@p global: also the counts and the unresolved references of all sources; false: only the document)
void expectSameDocument(const Workspace& incremental, size_t slotIncremental, const Workspace& reference, size_t slotReference, const std::string& what,
                        bool global = true) {
    if (global) {
        EXPECT_EQ(incremental.referenceCount(), reference.referenceCount()) << what;
        EXPECT_EQ(incremental.resolvedReferenceCount(), reference.resolvedReferenceCount()) << what;
        EXPECT_EQ(incremental.unresolvedReferences().size(), reference.unresolvedReferences().size()) << what;
        EXPECT_EQ(unresolvedKeys(incremental), unresolvedKeys(reference)) << what;
    } else {
        EXPECT_EQ(unresolvedIn(incremental, slotIncremental), unresolvedIn(reference, slotReference)) << what;
    }
    EXPECT_EQ(incremental.elements(slotIncremental).size(), reference.elements(slotReference).size()) << what;
    ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(incremental.elements(slotIncremental)),
                                     ConformanceTest::resolvedGenerals(reference.elements(slotReference)), what);
}
}

TEST(ReplaceSourceIncremental, ADocumentAboveItsLibrariesGivesTheSameResultAsAFreshWorkspace) {
    const char* lib1 = "package Lib { part def Base; part def Other { part inner : Base; } part def Broken : Missing; }";
    const char* lib2 = "package Lib2 { public import Lib::*; part def Third :> Other; part uses : Absent; }";
    const std::vector<std::string> texts = {
        "package U { import Lib2::*; part x : Third; }",
        "package U { part x : Base; }",
        "package W { import Lib::*; part a : Other; part b : Base; part c : Missing2; }",
        "package W { import Lib2::Third; part a : Third; part b : Lib::Base; part def D :> Third { part redefines inner; part k :>> inner; } }",
        "package U { import Lib2::*; part x : Third; }",
        "",
    };

    Workspace steps;
    steps.addText(lib1, "lib1.sysml", SourceLanguage::SysML, 0);
    steps.addText(lib2, "lib2.sysml", SourceLanguage::SysML, 100);
    const size_t user = steps.addText("package Empty { }", "user.sysml", SourceLanguage::SysML, 1000);
    steps.resolve();
    for (const auto& text : texts) {
        steps.replaceSource(user, text);
        steps.resolve();

        Workspace fresh;
        fresh.addText(lib1, "lib1.sysml", SourceLanguage::SysML, 0);
        fresh.addText(lib2, "lib2.sysml", SourceLanguage::SysML, 100);
        const size_t slot = fresh.addText(text, "user.sysml", SourceLanguage::SysML, 1000);
        fresh.resolve();
        expectSameResolution(steps, fresh, text);
        expectSameDocument(steps, user, fresh, slot, text);
    }
}

TEST(ReplaceSourceIncremental, SeveralReplacementsBeforeOneResolveAndSeveralDocuments) {
    const char* library = "package Lib { part def Base { attribute m; } part def Sub :> Base { attribute :>> m; } }";
    const auto makeOne = [](const std::string& body) { return "package One { import Lib::*; " + body + " }"; };
    const auto makeTwo = [](const std::string& body) { return "package Two { import One::*; private import Lib::*; " + body + " }"; };

    Workspace steps;
    steps.addText(library, "lib.sysml", SourceLanguage::SysML, 0);
    const size_t one = steps.addText(makeOne(""), "one.sysml", SourceLanguage::SysML, 1000);
    const size_t two = steps.addText(makeTwo(""), "two.sysml", SourceLanguage::SysML, 1000);
    steps.resolve();

    const std::vector<std::pair<std::string, std::string>> rounds = {
        {"part def A :> Sub { attribute :>> m; }", "part def B :> A { attribute :>> m; } part b : B;"},
        {"part def A :> Base;", "part b : A; part c : Missing;"},
        {"part def A :> Sub { attribute :>> m; } part def Z;", "part def B :> A { attribute :>> m; } part b : B; part z : Z;"},
    };
    for (size_t round = 0; round < rounds.size(); ++round) {
        const auto& [first, second] = rounds[round];
        // (twice before the resolve: the first of the replacements is never indexed)
        steps.replaceSource(one, makeOne("part def Gone;"));
        steps.replaceSource(two, makeTwo("part gone : Gone;"));
        steps.replaceSource(one, makeOne(first));
        steps.replaceSource(two, makeTwo(second));
        steps.resolve();

        Workspace fresh;
        fresh.addText(library, "lib.sysml", SourceLanguage::SysML, 0);
        const size_t freshOne = fresh.addText(makeOne(first), "one.sysml", SourceLanguage::SysML, 1000);
        const size_t freshTwo = fresh.addText(makeTwo(second), "two.sysml", SourceLanguage::SysML, 1000);
        fresh.resolve();
        expectSameResolution(steps, fresh, "round " + std::to_string(round));
        expectSameDocument(steps, one, fresh, freshOne, "one, round " + std::to_string(round));
        expectSameDocument(steps, two, fresh, freshTwo, "two, round " + std::to_string(round));
    }
}

TEST(ReplaceSourceIncremental, FindSeesTheNewVersionWithoutAResolve) {
    Workspace ws;
    ws.addText("package Lib { part def Base; }", "lib.sysml", SourceLanguage::SysML, 0);
    const size_t user = ws.addText("package U { part def Old; }", "user.sysml", SourceLanguage::SysML, 1000);
    ws.resolve();
    EXPECT_NE(ws.find("U::Old"), nullptr);
    ws.replaceSource(user, "package U { import Lib::*; part def New :> Base; }");
    EXPECT_EQ(ws.find("U::Old"), nullptr);
    EXPECT_NE(ws.find("U::New"), nullptr);
    EXPECT_NE(ws.find("Lib::Base"), nullptr);
    ws.resolve();
    EXPECT_TRUE(ws.unresolvedReferences().empty());
    EXPECT_EQ(ws.resolvedReferenceCount(), ws.referenceCount());
}

TEST(ReplaceSourceIncremental, ASourceOfTheSameLevelAsAnotherOneIsIndexedAnew) {
    // The library has the level of the document: its references could be bound to the old version, so the index is built again.
    const char* lib = "package Lib { import U::*; part def Needs :> Wanted; }";
    const std::vector<std::string> texts = {"package U { part def Wanted; }", "package U { part def Other; }", "package U { part def Wanted { part p; } }"};
    Workspace steps;
    steps.addText(lib, "lib.sysml", SourceLanguage::SysML, 5);
    const size_t user = steps.addText("package U { }", "user.sysml", SourceLanguage::SysML, 5);
    steps.resolve();
    for (const auto& text : texts) {
        steps.replaceSource(user, text);
        steps.resolve();
        Workspace fresh;
        fresh.addText(lib, "lib.sysml", SourceLanguage::SysML, 5);
        fresh.addText(text, "user.sysml", SourceLanguage::SysML, 5);
        fresh.resolve();
        // (the library keeps what it resolved before: only the document has to agree)
        expectSameDocument(steps, user, fresh, 1, text, false);
    }

    // A document below the library (a lower level than the other source) is a full rebuild as well.
    Workspace below;
    below.addText("package Lib { part def Base; }", "lib.sysml", SourceLanguage::SysML, 10);
    const size_t doc = below.addText("package D { }", "doc.sysml", SourceLanguage::SysML, 1);
    below.resolve();
    below.replaceSource(doc, "package D { part x : Lib::Base; }");
    below.resolve();
    EXPECT_EQ(unresolvedIn(below, doc), 1u);   // (Lib is above D)
}

TEST(ReplaceSourceIncremental, ALibraryThatStaysBehindIsNotDamaged) {
    // The library's own references to the standard-like base elements, and their order, must not change while a document is replaced.
    const char* base = "standard library package Base { abstract classifier Anything; abstract feature things : Anything; }";
    const char* lib = "package L { part def A { part p; } part def B :> A { part redefines p; } part def C :> B, A; }";
    Workspace ws;
    ws.addText(base, "base.kerml", SourceLanguage::KerML, 0);
    ws.addText(lib, "lib.sysml", SourceLanguage::SysML, 0);
    const size_t doc = ws.addText("package U { }", "doc.sysml", SourceLanguage::SysML, 1000);
    ws.resolve();
    const auto before = ConformanceTest::resolvedGenerals(ws.elements());
    const auto resolvedBefore = ws.resolvedReferenceCount();
    for (int round = 0; round < 4; ++round) {
        ws.replaceSource(doc, "package U { import L::*; part def D :> C { part redefines p; part q :>> p; } part d : D; part e : Missing" + std::to_string(round) + "; }");
        ws.resolve();
        EXPECT_EQ(ws.unresolvedReferences().size(), 1u);
        ws.replaceSource(doc, "package U { }");
        ws.resolve();
        EXPECT_TRUE(ws.unresolvedReferences().empty());
        EXPECT_EQ(ws.resolvedReferenceCount(), resolvedBefore);
        ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(ws.elements()), before, "round " + std::to_string(round));
    }
}

TEST(ReplaceSourceIncremental, InvalidateIndexMakesAnElementAddedThroughTheApiFindable) {
    Workspace ws;
    ws.addText("package P { part def A; }", "p.sysml", SourceLanguage::SysML, 0);
    ws.resolve();
    const auto p = as<KerML::Entities::Namespace>(ws.find("P"));
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(ws.find("P::Added"), nullptr);
    auto added = std::make_shared<KerML::Entities::Package>();
    added->setDeclaredName("Added");
    p->appendOwnedElement(added);   // (what the index walks: the owned elements)
    // (the index was built before: it does not know the new element)
    ws.invalidateIndex();
    EXPECT_EQ(ws.find("P::Added"), added);
    ws.resolve();
    EXPECT_EQ(ws.find("P::Added"), added);
    EXPECT_NE(ws.find("P::A"), nullptr);
}

namespace {
/// A directory below the temporary directory that is removed at the end (short names: MAX_PATH).
struct ScratchDirectory {
    std::filesystem::path path;
    ScratchDirectory() {
        static int counter = 0;
        path = std::filesystem::temp_directory_path() / ("rs" + std::to_string(std::rand() & 0xFFFFF) + "_" + std::to_string(counter++));
        std::filesystem::create_directories(path);
    }
    ~ScratchDirectory() {
        std::error_code ec;
        std::filesystem::remove_all(path, ec);
    }
};

void writeText(const std::filesystem::path& file, const std::string& text) {
    std::ofstream(file, std::ios::binary) << text;
}
}

TEST(ReplaceSourceIncremental, TheOrderOfTheGeneralsOfAnXmiSourceDoesNotDependOnWhatIsLinked) {
    // `S :> G1, G2, G3` where G2 is in another file that is added after the first resolve (Finding B: the ordinal of a general is its
    // place in the document, not the number of those that are linked).
    ScratchDirectory source, xmi;
    writeText(source.path / "a.sysml",
              "package A { import B::*; part def G1 { attribute x; } part def G3 { attribute x; } part def S :> G1, G2, G3; part def T :> G3, G2, G1; }");
    writeText(source.path / "b.sysml", "package B { part def G2 { attribute x; } }");
    {
        Workspace export_;
        export_.addFile((source.path / "a.sysml").string());
        export_.addFile((source.path / "b.sysml").string());
        export_.resolve();
        ASSERT_TRUE(export_.unresolvedReferences().empty());
        ASSERT_TRUE(export_.exportXmi(xmi.path.string()).empty());
    }
    const auto generalsOf = [](const Workspace& ws, const std::string& name) {
        std::vector<std::string> names;
        const auto type = as<KerML::Entities::Type>(ws.find(name));
        if (!type) return names;
        for (const auto& specialization : type->ownedSpecialization()) {
            const auto general = specialization->general();
            names.push_back(general && !isUnresolved(general) ? ConformanceTest::qualifiedNameOf(general) : std::string("?"));
        }
        return names;
    };

    Workspace steps;
    steps.addFile((xmi.path / "a.sysmlx").string());
    steps.resolve();
    EXPECT_NE(steps.find("A::S"), nullptr);
    steps.addFile((xmi.path / "b.sysmlx").string());
    steps.resolve();

    Workspace once;
    once.addFile((xmi.path / "a.sysmlx").string());
    once.addFile((xmi.path / "b.sysmlx").string());
    once.resolve();

    EXPECT_EQ(generalsOf(steps, "A::S"), (std::vector<std::string>{"A::G1", "B::G2", "A::G3"}));
    EXPECT_EQ(generalsOf(steps, "A::T"), (std::vector<std::string>{"A::G3", "B::G2", "A::G1"}));
    EXPECT_EQ(generalsOf(steps, "A::S"), generalsOf(once, "A::S"));
    // The lookup through the generals follows the declaration order: x of G1 first for S, x of G3 first for T.
    for (const auto* name : {"A::S::x", "A::T::x"}) {
        ASSERT_NE(steps.find(name), nullptr) << name;
        ASSERT_NE(once.find(name), nullptr) << name;
        EXPECT_EQ(ConformanceTest::qualifiedNameOf(steps.find(name)), ConformanceTest::qualifiedNameOf(once.find(name))) << name;
        EXPECT_EQ(steps.find(name)->owner(), steps.find(std::string(name) == "A::S::x" ? "A::G1" : "A::G3")) << name;
    }
}

TEST(ReplaceSourceIncremental, ADocumentOverAnXmiLibraryIsExchangedIncrementally) {
    ScratchDirectory source, xmi;
    writeText(source.path / "base.sysml", "package Base { part def Thing { attribute m; } part def Sub :> Thing { attribute :>> m; } }");
    {
        Workspace export_;
        export_.addFile((source.path / "base.sysml").string());
        export_.resolve();
        ASSERT_TRUE(export_.exportXmi(xmi.path.string()).empty());
    }
    const std::vector<std::string> texts = {
        "package M { import Base::*; part t : Sub { attribute :>> m; } }",
        "package M { import Base::Thing; part t : Thing; part u : Nope; }",
        "package M { import Base::*; part def X :> Sub; part x : X; }",
    };
    const auto library = (xmi.path / "base.sysmlx").string();
    Workspace steps;
    steps.addFile(library, 0);
    const size_t doc = steps.addText("package M { }", "doc.sysml", SourceLanguage::SysML, 1000);
    steps.resolve();
    for (const auto& text : texts) {
        steps.replaceSource(doc, text);
        steps.resolve();
        Workspace fresh;
        fresh.addFile(library, 0);
        const size_t slot = fresh.addText(text, "doc.sysml", SourceLanguage::SysML, 1000);
        fresh.resolve();
        expectSameResolution(steps, fresh, text);
        expectSameDocument(steps, doc, fresh, slot, text);
    }
    // An XMI source that is replaced always gets a new index; the result is the same as with a new workspace.
    const std::string xml = ConformanceTest::readFile(xmi.path / "base.sysmlx");
    // (the document refers to the old elements of the library, so it is replaced as well: see replaceSource())
    steps.replaceSource(0, xml, SourceLanguage::Xmi);
    steps.replaceSource(doc, texts.back());
    steps.resolve();
    Workspace fresh;
    fresh.addFile(library, 0);
    const size_t slot = fresh.addText(texts.back(), "doc.sysml", SourceLanguage::SysML, 1000);
    fresh.resolve();
    expectSameResolution(steps, fresh, "replaced XMI source");
    expectSameDocument(steps, doc, fresh, slot, "replaced XMI source");
}

/// The whole text library at level 0 and a document at level 1000 that is replaced; the library is loaded once for all tests of the fixture.
/// Two workspaces: one exchanges the document incrementally, the other has its index thrown away before every replacement (a new index over
/// all sources, what replaceSource() did before it was incremental).
class ReplaceOverLibrary : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        const auto start = std::chrono::steady_clock::now();
        incremental = std::make_unique<Workspace>();
        reference = std::make_unique<Workspace>();
        for (Workspace* ws : {incremental.get(), reference.get()}) {
            EXPECT_GT(ws->loadLibrary(SYSML_LIBRARY_DIR), 80u);
            ws->resolve();
        }
        slotIncremental = incremental->addText("package Doc { }", "doc.sysml", SourceLanguage::SysML, 1000);
        slotReference = reference->addText("package Doc { }", "doc.sysml", SourceLanguage::SysML, 1000);
        incremental->resolve();
        reference->resolve();
        baseline = ConformanceTest::resolvedGenerals(incremental->elements());
        std::cout << "[  INFO  ] two libraries loaded in "
                  << std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count() << " s" << std::endl;
    }
    static void TearDownTestSuite() {
        incremental.reset();
        reference.reset();
    }

    /// Replaces the document of both workspaces (incrementally, and with a new index), resolves and compares.
    static void replaceAndCompare(const std::string& text, const std::string& what) {
        incremental->replaceSource(slotIncremental, text);
        incremental->resolve();
        reference->invalidateIndex();
        reference->replaceSource(slotReference, text);
        reference->resolve();
        expectSameDocument(*incremental, slotIncremental, *reference, slotReference, what);
    }

    static std::unique_ptr<Workspace> incremental;
    static std::unique_ptr<Workspace> reference;
    static size_t slotIncremental;
    static size_t slotReference;
    static std::vector<std::string> baseline;
};

std::unique_ptr<Workspace> ReplaceOverLibrary::incremental;
std::unique_ptr<Workspace> ReplaceOverLibrary::reference;
size_t ReplaceOverLibrary::slotIncremental = 0;
size_t ReplaceOverLibrary::slotReference = 0;
std::vector<std::string> ReplaceOverLibrary::baseline;

TEST_F(ReplaceOverLibrary, EveryValidModelIsTheSameWhenItIsReplacedIncrementally) {
    const auto files = ConformanceTest::listFiles(CONFORMANCE_SYSML_VALID_DIR, {".sysml"});
    ASSERT_GT(files.size(), 40u);
    const auto start = std::chrono::steady_clock::now();
    for (const auto& file : files) {
        SCOPED_TRACE(file.filename().string());
        const std::string text = ConformanceTest::readFile(file);
        // (twice: the second replacement exchanges a source that was exchanged before; slightly different text)
        replaceAndCompare(text, file.filename().string());
        replaceAndCompare(text + "\npackage ReplacedAgain { part def Added; part added : Added; }\n", file.filename().string() + " (changed)");
    }
    std::cout << "[  INFO  ] " << files.size() << " models, replaced twice each, in "
              << std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count() << " s" << std::endl;
}

TEST_F(ReplaceOverLibrary, TheLibraryIsTheSameAfterAllReplacements) {
    // (runs after the test above, which replaced the document many times; both workspaces end with an empty document)
    replaceAndCompare("package Doc { }", "empty document");
    ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(incremental->elements()), baseline, "library, incremental");
    ConformanceTest::expectSameLines(ConformanceTest::resolvedGenerals(reference->elements()), baseline, "library, with a new index");
    EXPECT_TRUE(incremental->unresolvedReferences().empty());
    EXPECT_EQ(incremental->resolvedReferenceCount(), reference->resolvedReferenceCount());
}

TEST_F(ReplaceOverLibrary, ADocumentThatUsesTheLibraryEqualsAFreshWorkspace) {
    // The same, against a workspace that was never replaced (a new library: parsed once more).
    const char* text =
        "package Doc { private import ISQ::*; private import SI::*; private import ScalarValues::*; private import Parts::*;\n"
        "  part def Engine { attribute power : PowerValue; attribute m : MassValue; }\n"
        "  part def Vehicle :> Part { part engine : Engine; attribute topSpeed : SpeedValue; attribute :>> mass; }\n"
        "  part fleet : Vehicle[3] { part redefines engine; attribute :>> mass = 3 [kg]; }\n"
        "}";
    replaceAndCompare(text, "doc over the library");
    replaceAndCompare(std::string(text) + "\npackage More { import Doc::*; part v : Vehicle; }\n", "doc over the library, changed");

    Workspace fresh;
    EXPECT_GT(fresh.loadLibrary(SYSML_LIBRARY_DIR), 80u);
    const size_t slot = fresh.addText(std::string(text) + "\npackage More { import Doc::*; part v : Vehicle; }\n", "doc.sysml", SourceLanguage::SysML, 1000);
    fresh.resolve();
    expectSameDocument(*incremental, slotIncremental, fresh, slot, "fresh workspace");
    EXPECT_EQ(incremental->resolvedReferenceCount(), fresh.resolvedReferenceCount());
}

TEST(ReplaceSource, ElementsOfSysMLSpecificMetaclassesAreFreed) {
    const char* text =
        "package M {\n"
        "  import ScalarValues::*;\n"
        "  item def Stoff; item stoff : Stoff;\n"
        "  part def Motor { port p : Anschluss; attribute n : Integer = 3; }\n"
        "  port def Anschluss; part motor : Motor { port q : Anschluss; }\n"
        "  connection def Verbindung; connection v : Verbindung connect a to b;\n"
        "  action def Fahre { in x : Integer; action schritt; first start; then schritt; then done; }\n"
        "  state def Zustand { entry action e; state s1; state s2; transition t first s1 then s2; }\n"
        "  requirement def Anf { subject s : Motor; doc /* text */ require constraint { n > 0 } }\n"
        "  constraint def Grenze { in x : Integer; x < 10 }\n"
        "  calc def Rechne { in a : Integer; return : Integer = a + 1; }\n"
        "  enum def Farbe { enum rot; enum gruen; }\n"
        "  view def Sicht; use case def Fall { objective o; }\n"
        "  metadata def Meta; occurrence def Ereignis; interface def Schnitt; allocation def Zuordnung;\n"
        "  part def A :> Motor; part a : A redefines motor; alias Kurz for Motor; comment /* c */\n"
        "}\n";
    Workspace ws;
    ws.addText("package Lib { part def Base; }", "lib.sysml");
    const size_t user = ws.addText("", "user.sysml");
    for (int round = 0; round < 3; ++round) {
        ws.replaceSource(user, text);
        ws.resolve();
        std::vector<std::weak_ptr<KerML::Entities::Element>> probes;
        std::set<std::string> metaclasses;
        for (const auto& element : ws.elements(user)) {
            probes.push_back(element);
            metaclasses.insert(element->getType());
        }
        probes.push_back(ws.rootNamespace(user));
        for (const auto& info : ws.unresolvedReferences()) probes.push_back(info.placeholder);
        ASSERT_GT(probes.size(), 50u);
        EXPECT_GT(metaclasses.size(), 15u);   // many different metaclasses were exercised
        ws.replaceSource(user, "");
        size_t alive = 0;
        for (const auto& probe : probes) alive += probe.expired() ? 0 : 1;
        EXPECT_EQ(alive, 0u) << "round " << round << " of " << probes.size() << " elements";
    }
}


// ---------------------------------------------------------------------------------------------------------------------
// The abstract syntax of an invocation: Membership of the invoked type, one ParameterMembership per argument.
// ---------------------------------------------------------------------------------------------------------------------

namespace {
std::shared_ptr<KerML::Entities::InvocationExpression> invocationOf(Workspace& ws, const std::string& attribute) {
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ws.find(attribute));
    if (!feature) return nullptr;
    for (const auto& relationship : feature->ownedRelationship()) {
        if (auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(relationship))
            return std::dynamic_pointer_cast<KerML::Entities::InvocationExpression>(value->value());
    }
    return nullptr;
}

void expectInvocationStructure(const std::shared_ptr<KerML::Entities::InvocationExpression>& call, const std::shared_ptr<KerML::Entities::Element>& function,
                               bool named) {
    using namespace KerML::Entities;
    ASSERT_NE(call, nullptr);
    ASSERT_NE(function, nullptr);
    EXPECT_EQ(call->instantiatedType().get(), function.get());
    const auto relationships = call->ownedRelationship();
    ASSERT_EQ(relationships.size(), 3u);
    // The invoked type: a membership that does not own its member.
    EXPECT_NE(std::dynamic_pointer_cast<Membership>(relationships[0]), nullptr);
    EXPECT_EQ(std::dynamic_pointer_cast<OwningMembership>(relationships[0]), nullptr);
    EXPECT_EQ(std::dynamic_pointer_cast<Membership>(relationships[0])->memberElement().get(), function.get());
    // The arguments: parameter memberships of in features that own a feature value.
    ASSERT_EQ(call->argument().size(), 2u);
    for (size_t i = 1; i <= 2; ++i) {
        const auto membership = std::dynamic_pointer_cast<ParameterMembership>(relationships[i]);
        ASSERT_NE(membership, nullptr);
        EXPECT_EQ(std::dynamic_pointer_cast<ReturnParameterMembership>(membership), nullptr);
        const auto parameter = std::dynamic_pointer_cast<Feature>(membership->memberElement());
        ASSERT_NE(parameter, nullptr);
        EXPECT_EQ(parameter->direction(), IN);
        EXPECT_FALSE(parameter->declaredName().has_value());
        FeatureValue* value = nullptr;
        size_t redefinitions = 0;
        for (const auto& relationship : parameter->ownedRelationship()) {
            if (auto fv = std::dynamic_pointer_cast<FeatureValue>(relationship)) value = fv.get();
            if (std::dynamic_pointer_cast<Redefinition>(relationship)) ++redefinitions;
        }
        ASSERT_NE(value, nullptr);
        EXPECT_EQ(value->value().get(), call->argument()[i - 1].get());
        EXPECT_EQ(redefinitions, named ? 1u : 0u);
    }
}
}  // namespace

TEST(InvocationStructure, TypeMembershipAndParameterMemberships) {
    One m("package M {\n"
          "  attribute def Real; attribute def Boolean;\n"
          "  function Verify { in feature x1 : Real; in feature x2 : Real; return bool valid : Boolean; }\n"
          "  part def P {\n"
          "    attribute x1 : Real := 0.0;\n"
          "    attribute x2 : Real := 0.0;\n"
          "    derived attribute r : Boolean = Verify(x1, x2);\n"
          "    attribute n : Boolean = Verify(x1 = x1, x2 = 2);\n"
          "  }\n"
          "}\n");
    const auto verify = m.ws.find("M::Verify");
    ASSERT_NE(verify, nullptr);
    EXPECT_FALSE(isUnresolved(std::dynamic_pointer_cast<KerML::Entities::Type>(verify)));

    const auto positional = invocationOf(m.ws, "M::P::r");
    expectInvocationStructure(positional, verify, false);
    const auto first = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(positional->argument()[0]);
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first->referent().get(), m.ws.find("M::P::x1").get());
    const auto second = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(positional->argument()[1]);
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second->referent().get(), m.ws.find("M::P::x2").get());

    const auto named = invocationOf(m.ws, "M::P::n");
    expectInvocationStructure(named, verify, true);
    const auto namedFirst = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(named->argument()[0]);
    ASSERT_NE(namedFirst, nullptr);
    EXPECT_EQ(namedFirst->referent().get(), m.ws.find("M::P::x1").get());
    EXPECT_NE(std::dynamic_pointer_cast<KerML::Entities::LiteralInteger>(named->argument()[1]), nullptr);

    for (const auto& info : m.ws.unresolvedReferences()) ADD_FAILURE() << "unresolved: " << info.name;
}

namespace {
// The constructor: Membership of the instantiated type, then the result feature (a ReturnParameterMembership) that owns the parameters.
void expectConstructorStructure(const std::shared_ptr<KerML::Entities::ConstructorExpression>& call, const std::shared_ptr<KerML::Entities::Element>& type,
                                size_t arguments, bool named) {
    using namespace KerML::Entities;
    ASSERT_NE(call, nullptr);
    ASSERT_NE(type, nullptr);
    EXPECT_EQ(call->instantiatedType().get(), type.get());
    const auto relationships = call->ownedRelationship();
    ASSERT_EQ(relationships.size(), 2u);
    const auto typeMembership = std::dynamic_pointer_cast<Membership>(relationships[0]);
    ASSERT_NE(typeMembership, nullptr);
    EXPECT_EQ(std::dynamic_pointer_cast<OwningMembership>(typeMembership), nullptr);
    EXPECT_EQ(typeMembership->memberElement().get(), type.get());
    const auto resultMembership = std::dynamic_pointer_cast<ReturnParameterMembership>(relationships[1]);
    ASSERT_NE(resultMembership, nullptr);
    EXPECT_EQ(resultMembership->owningType().get(), call.get());
    const auto result = std::dynamic_pointer_cast<Feature>(resultMembership->memberElement());
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->direction(), OUT);
    EXPECT_FALSE(result->declaredName().has_value());
    ASSERT_TRUE(result->owningType().has_value());
    EXPECT_EQ(result->owningType()->get(), call.get());
    // The result is the only feature of the constructor.
    ASSERT_EQ(call->ownedFeature().size(), 1u);
    EXPECT_EQ(call->ownedFeature()[0].get(), result.get());
    // The parameters are owned by the result, not by the constructor.
    const auto parameters = result->ownedRelationship();
    ASSERT_EQ(parameters.size(), arguments);
    ASSERT_EQ(call->argument().size(), arguments);
    for (size_t i = 0; i < arguments; ++i) {
        const auto membership = std::dynamic_pointer_cast<ParameterMembership>(parameters[i]);
        ASSERT_NE(membership, nullptr);
        EXPECT_EQ(membership->owningType().get(), result.get());
        const auto parameter = std::dynamic_pointer_cast<Feature>(membership->memberElement());
        ASSERT_NE(parameter, nullptr);
        EXPECT_EQ(parameter->direction(), IN);
        EXPECT_FALSE(parameter->declaredName().has_value());
        FeatureValue* value = nullptr;
        size_t redefinitions = 0;
        for (const auto& relationship : parameter->ownedRelationship()) {
            if (auto fv = std::dynamic_pointer_cast<FeatureValue>(relationship)) value = fv.get();
            if (std::dynamic_pointer_cast<Redefinition>(relationship)) ++redefinitions;
        }
        ASSERT_NE(value, nullptr);
        EXPECT_EQ(value->value().get(), call->argument()[i].get());
        EXPECT_EQ(redefinitions, named ? 1u : 0u);
    }
}

std::shared_ptr<KerML::Entities::ConstructorExpression> constructorOf(Workspace& ws, const std::string& attribute) {
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ws.find(attribute));
    if (!feature) return nullptr;
    for (const auto& relationship : feature->ownedRelationship()) {
        if (auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(relationship))
            return std::dynamic_pointer_cast<KerML::Entities::ConstructorExpression>(value->value());
    }
    return nullptr;
}

void expectConstructorsOfTheTestModel(Workspace& ws) {
    using namespace KerML::Entities;
    const auto type = ws.find("M::C");
    ASSERT_NE(type, nullptr);
    const struct { const char* name; size_t arguments; bool named; } cases[] = {
        {"M::P::named", 2, true}, {"M::P::positional", 2, false}, {"M::P::empty", 0, false}};
    for (const auto& c : cases) {
        SCOPED_TRACE(c.name);
        const auto call = constructorOf(ws, c.name);
        expectConstructorStructure(call, type, c.arguments, c.named);
        if (!call) continue;
        for (size_t i = 0; i < c.arguments; ++i) {
            // The argument is a reference to the feature of the outer scope, not to the parameter itself.
            const auto reference = std::dynamic_pointer_cast<FeatureReferenceExpression>(call->argument()[i]);
            ASSERT_NE(reference, nullptr);
            EXPECT_EQ(reference->referent().get(), ws.find(i == 0 ? "M::P::p" : "M::P::q").get());
        }
    }
    for (const auto& info : ws.unresolvedReferences()) ADD_FAILURE() << "unresolved: " << info.name;
}
}  // namespace

TEST(InvocationStructure, ConstructorResultOwnsParameterMemberships) {
    One m("package M {\n"
          "  attribute def Real;\n"
          "  part def C { attribute p : Real; attribute q : Real; }\n"
          "  part def P {\n"
          "    attribute p : Real;\n"
          "    attribute q : Real;\n"
          "    attribute named = new C(p = p, q = q);\n"
          "    attribute positional = new C(p, q);\n"
          "    attribute empty = new C();\n"
          "  }\n"
          "}\n");
    expectConstructorsOfTheTestModel(m.ws);
}

// A constructor as an argument of an invocation (positional and named) and inside a named argument of a constructor: every call keeps
// the structure of its own.
TEST(InvocationStructure, NestedCallsKeepTheirOwnStructure) {
    using namespace KerML::Entities;
    One m("package M {\n"
          "  attribute def Real;\n"
          "  part def C { attribute p : Real; }\n"
          "  function f { in a : C; in b : C; }\n"
          "  part def P {\n"
          "    attribute p : Real;\n"
          "    attribute viaPositional = f(new C(p), new C(p = p));\n"
          "    attribute viaNamed = f(a = new C(p), b = new C());\n"
          "    attribute inConstructor = new C(p = new C(p));\n"
          "  }\n"
          "}\n");
    const auto f = m.ws.find("M::f");
    const auto c = m.ws.find("M::C");
    ASSERT_NE(f, nullptr);
    ASSERT_NE(c, nullptr);
    const struct { const char* name; bool named; } cases[] = {{"M::P::viaPositional", false}, {"M::P::viaNamed", true}};
    for (const auto& k : cases) {
        SCOPED_TRACE(k.name);
        const auto call = invocationOf(m.ws, k.name);
        expectInvocationStructure(call, f, k.named);
        if (!call) continue;
        const auto first = std::dynamic_pointer_cast<ConstructorExpression>(call->argument()[0]);
        const auto second = std::dynamic_pointer_cast<ConstructorExpression>(call->argument()[1]);
        expectConstructorStructure(first, c, 1, false);
        // `new C(p = p)` has a named argument, `new C()` none.
        expectConstructorStructure(second, c, k.named ? 0 : 1, !k.named);
    }
    const auto outer = constructorOf(m.ws, "M::P::inConstructor");
    expectConstructorStructure(outer, c, 1, true);
    if (outer) expectConstructorStructure(std::dynamic_pointer_cast<ConstructorExpression>(outer->argument()[0]), c, 1, false);
    for (const auto& info : m.ws.unresolvedReferences()) ADD_FAILURE() << "unresolved: " << info.name;
}

namespace {
// The parameter of an argument without a value (syntax error): it is kept with its redefinition, but has no feature value.
void expectParameterWithoutValue(const std::shared_ptr<KerML::Entities::Type>& owner, const char* trace) {
    using namespace KerML::Entities;
    SCOPED_TRACE(trace);
    ASSERT_NE(owner, nullptr);
    const auto features = owner->ownedFeature();
    ASSERT_EQ(features.size(), 1u);
    EXPECT_EQ(features[0]->direction(), IN);
    size_t redefinitions = 0;
    for (const auto& relationship : features[0]->ownedRelationship()) {
        EXPECT_EQ(std::dynamic_pointer_cast<FeatureValue>(relationship), nullptr);
        if (std::dynamic_pointer_cast<Redefinition>(relationship)) ++redefinitions;
    }
    EXPECT_EQ(redefinitions, 1u);
}

// The first invocation / constructor of the model (the broken calls are the only ones). The error recovery of the parser drops what
// follows a syntax error, so the calls are looked up in the elements and not by name.
template <class T>
std::shared_ptr<T> firstCallOf(Workspace& ws) {
    for (const auto& element : ws.elements(0)) {
        if (element && typeid(*element) == typeid(T)) return std::dynamic_pointer_cast<T>(element);
    }
    return nullptr;
}

void expectArgumentsWithoutValue(Workspace& ws) {
    using namespace KerML::Entities;
    EXPECT_FALSE(ws.errors().empty());
    for (const auto& element : ws.elements(0)) {
        if (auto value = std::dynamic_pointer_cast<FeatureValue>(element)) EXPECT_NE(value->value(), nullptr);
    }
    // The calls are still there, but without arguments: the parameters without a value add none.
    const auto a = firstCallOf<InvocationExpression>(ws);
    ASSERT_NE(a, nullptr);
    EXPECT_TRUE(a->argument().empty());
    expectParameterWithoutValue(a, "invocation");
    const auto b = firstCallOf<ConstructorExpression>(ws);
    ASSERT_NE(b, nullptr);
    EXPECT_TRUE(b->argument().empty());
    const auto result = b->ownedFeature();
    ASSERT_EQ(result.size(), 1u);
    expectParameterWithoutValue(result[0], "constructor");
}
}  // namespace

// Syntax errors in the arguments leave no feature value without a value.
TEST(InvocationStructure, MissingNamedArgumentValueLeavesNoEmptyFeatureValue) {
    One m("package M {\n"
          "  attribute def Real;\n"
          "  part def C { attribute p : Real; }\n"
          "  function f { in x : Real; }\n"
          "  part def P {\n"
          "    attribute a = f(x = );\n"
          "    attribute b = new C(p = );\n"
          "  }\n"
          "}\n", SourceLanguage::SysML, "errors.sysml");
    expectArgumentsWithoutValue(m.ws);
}

// KerML: the same abstract syntax for invocations and constructors.
TEST(InvocationStructure, KerMLTypeMembershipAndParameterMemberships) {
    One m("package M {\n"
          "  datatype Real;\n"
          "  datatype Boolean;\n"
          "  function Verify { in x1 : Real; in x2 : Real; return valid : Boolean; }\n"
          "  classifier P {\n"
          "    feature x1 : Real;\n"
          "    feature x2 : Real;\n"
          "    feature r : Boolean = Verify(x1, x2);\n"
          "    feature n : Boolean = Verify(x1 = x1, x2 = 2);\n"
          "  }\n"
          "}\n", SourceLanguage::KerML, "test.kerml");
    const auto verify = m.ws.find("M::Verify");
    ASSERT_NE(verify, nullptr);
    const auto positional = invocationOf(m.ws, "M::P::r");
    expectInvocationStructure(positional, verify, false);
    const auto first = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(positional->argument()[0]);
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first->referent().get(), m.ws.find("M::P::x1").get());
    const auto named = invocationOf(m.ws, "M::P::n");
    expectInvocationStructure(named, verify, true);
    // `x1 = x1`: the value is the feature of the class, not the parameter of the argument.
    const auto namedFirst = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(named->argument()[0]);
    ASSERT_NE(namedFirst, nullptr);
    EXPECT_EQ(namedFirst->referent().get(), m.ws.find("M::P::x1").get());
    EXPECT_NE(std::dynamic_pointer_cast<KerML::Entities::LiteralInteger>(named->argument()[1]), nullptr);
    for (const auto& info : m.ws.unresolvedReferences()) ADD_FAILURE() << "unresolved: " << info.name;
}

// `f(x = x)`: the name of the named argument is no member of the scope of its value (it resolved to the argument itself before).
TEST(InvocationStructure, KerMLNamedArgumentValueResolvesToTheOuterFeature) {
    One m("package M {\n"
          "  datatype Real;\n"
          "  function f { in x : Real; in y : Real; return z : Real; }\n"
          "  classifier P {\n"
          "    feature x : Real;\n"
          "    feature r : Real = f(x = x, y = 2);\n"
          "  }\n"
          "}\n", SourceLanguage::KerML, "test.kerml");
    const auto call = invocationOf(m.ws, "M::P::r");
    expectInvocationStructure(call, m.ws.find("M::f"), true);
    ASSERT_NE(call, nullptr);
    ASSERT_EQ(call->argument().size(), 2u);
    const auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(call->argument()[0]);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->referent().get(), m.ws.find("M::P::x").get());
    for (const auto& info : m.ws.unresolvedReferences()) ADD_FAILURE() << "unresolved: " << info.name;
}

TEST(InvocationStructure, KerMLConstructorResultOwnsParameterMemberships) {
    One m("package M {\n"
          "  datatype Real;\n"
          "  datatype C { feature p : Real; feature q : Real; }\n"
          "  classifier P {\n"
          "    feature p : Real;\n"
          "    feature q : Real;\n"
          "    feature named = new C(p = p, q = q);\n"
          "    feature positional = new C(p, q);\n"
          "    feature empty = new C();\n"
          "  }\n"
          "}\n", SourceLanguage::KerML, "test.kerml");
    expectConstructorsOfTheTestModel(m.ws);
}

TEST(InvocationStructure, KerMLNestedCallsKeepTheirOwnStructure) {
    using namespace KerML::Entities;
    One m("package M {\n"
          "  datatype Real;\n"
          "  datatype C { feature p : Real; }\n"
          "  function f { in a : C; in b : C; }\n"
          "  classifier P {\n"
          "    feature p : Real;\n"
          "    feature viaPositional = f(new C(p), new C(p = p));\n"
          "    feature viaNamed = f(a = new C(p), b = new C());\n"
          "  }\n"
          "}\n", SourceLanguage::KerML, "test.kerml");
    const auto f = m.ws.find("M::f");
    const auto c = m.ws.find("M::C");
    const struct { const char* name; bool named; } cases[] = {{"M::P::viaPositional", false}, {"M::P::viaNamed", true}};
    for (const auto& k : cases) {
        SCOPED_TRACE(k.name);
        const auto call = invocationOf(m.ws, k.name);
        expectInvocationStructure(call, f, k.named);
        if (!call) continue;
        expectConstructorStructure(std::dynamic_pointer_cast<ConstructorExpression>(call->argument()[0]), c, 1, false);
        expectConstructorStructure(std::dynamic_pointer_cast<ConstructorExpression>(call->argument()[1]), c, k.named ? 0 : 1, !k.named);
    }
    for (const auto& info : m.ws.unresolvedReferences()) ADD_FAILURE() << "unresolved: " << info.name;
}

TEST(InvocationStructure, KerMLSyntaxErrorsInArguments) {
    One m("package M {\n"
          "  datatype Real;\n"
          "  datatype C { feature p : Real; }\n"
          "  function f { in x : Real; }\n"
          "  classifier P {\n"
          "    feature a = f(x = );\n"
          "    feature b = new C(p = );\n"
          "  }\n"
          "}\n", SourceLanguage::KerML, "errors.kerml");
    expectArgumentsWithoutValue(m.ws);
}

// A constructor typed by a feature chain (`new q.c(p)`): the arguments are parameters of the result. In KerML the chain feature is
// owned by the constructor as well (relationships: type membership, FeatureMembership of the chain, result as ReturnParameterMembership,
// as the chain is built before the result); SysML builds no chain feature.
void expectChainConstructor(Workspace& ws, bool chainFeature) {
    using namespace KerML::Entities;
    const auto call = constructorOf(ws, "M::P::a");
    ASSERT_NE(call, nullptr);
    const auto relationships = call->ownedRelationship();
    ASSERT_EQ(relationships.size(), chainFeature ? 3u : 2u);
    EXPECT_NE(std::dynamic_pointer_cast<Membership>(relationships[0]), nullptr);
    const auto resultMembership = std::dynamic_pointer_cast<ReturnParameterMembership>(relationships.back());
    ASSERT_NE(resultMembership, nullptr);
    const auto result = std::dynamic_pointer_cast<Feature>(resultMembership->memberElement());
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->direction(), OUT);
    if (chainFeature) {
        // The chain feature owns no parameter.
        const auto chainMembership = std::dynamic_pointer_cast<FeatureMembership>(relationships[1]);
        ASSERT_NE(chainMembership, nullptr);
        const auto chain = std::dynamic_pointer_cast<Feature>(chainMembership->memberElement());
        ASSERT_NE(chain, nullptr);
        EXPECT_NE(chain.get(), result.get());
        EXPECT_FALSE(chain->ownedFeatureChaining().empty());
        for (const auto& relationship : chain->ownedRelationship())
            EXPECT_EQ(std::dynamic_pointer_cast<ParameterMembership>(relationship), nullptr);
    }
    EXPECT_EQ(call->ownedFeature().size(), chainFeature ? 2u : 1u);
    // The only argument is the one parameter of the result and refers to the outer feature.
    const auto parameters = result->ownedRelationship();
    ASSERT_EQ(parameters.size(), 1u);
    const auto membership = std::dynamic_pointer_cast<ParameterMembership>(parameters[0]);
    ASSERT_NE(membership, nullptr);
    EXPECT_EQ(membership->owningType().get(), result.get());
    ASSERT_EQ(call->argument().size(), 1u);
    const auto reference = std::dynamic_pointer_cast<FeatureReferenceExpression>(call->argument()[0]);
    ASSERT_NE(reference, nullptr);
    EXPECT_EQ(reference->referent().get(), ws.find("M::P::p").get());
}

TEST(InvocationStructure, KerMLChainTypedConstructorKeepsArgumentsOnTheResult) {
    One m("package M {\n"
          "  datatype Real;\n"
          "  classifier Q { feature c : Real; }\n"
          "  classifier P {\n"
          "    feature q : Q;\n"
          "    feature p : Real;\n"
          "    feature a = new q.c(p);\n"
          "  }\n"
          "}\n", SourceLanguage::KerML, "chain.kerml");
    expectChainConstructor(m.ws, true);
}

TEST(InvocationStructure, ChainTypedConstructorKeepsArgumentsOnTheResult) {
    One m("package M {\n"
          "  attribute def Real;\n"
          "  part def Q { attribute c : Real; }\n"
          "  part def P {\n"
          "    attribute q : Q;\n"
          "    attribute p : Real;\n"
          "    attribute a = new q.c(p);\n"
          "  }\n"
          "}\n");
    expectChainConstructor(m.ws, false);
}

// An invocation of a function by a feature chain (`q.c(p)`): next to the type membership and the chain feature the call owns one
// ParameterMembership per argument (the chain feature owns none).
TEST(InvocationStructure, KerMLChainInvocationOwnsItsParameterMemberships) {
    One m("package M {\n"
          "  datatype Real;\n"
          "  classifier Q { function c { in x : Real; } }\n"
          "  classifier P {\n"
          "    feature q : Q;\n"
          "    feature p : Real;\n"
          "    feature a = q.c(p);\n"
          "  }\n"
          "}\n", SourceLanguage::KerML, "chain.kerml");
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(m.ws.find("M::P::a"));
    ASSERT_NE(feature, nullptr);
    std::shared_ptr<KerML::Entities::InvocationExpression> call;
    for (const auto& relationship : feature->ownedRelationship()) {
        if (auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(relationship))
            call = std::dynamic_pointer_cast<KerML::Entities::InvocationExpression>(value->value());
    }
    ASSERT_NE(call, nullptr);
    ASSERT_EQ(call->ownedRelationship().size(), 3u);
    EXPECT_NE(std::dynamic_pointer_cast<KerML::Entities::Membership>(call->ownedRelationship()[0]), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<KerML::Entities::FeatureMembership>(call->ownedRelationship()[1]), nullptr);
    size_t parameters = 0;
    for (const auto& relationship : call->ownedRelationship()) {
        const auto membership = std::dynamic_pointer_cast<KerML::Entities::ParameterMembership>(relationship);
        if (!membership) continue;
        ++parameters;
        EXPECT_EQ(membership->owningType().get(), call.get());
    }
    EXPECT_EQ(parameters, 1u);
    ASSERT_EQ(call->argument().size(), 1u);
    const auto reference = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(call->argument()[0]);
    ASSERT_NE(reference, nullptr);
    EXPECT_EQ(reference->referent().get(), m.ws.find("M::P::p").get());
}

// Broken constructors (the type is missing or not an identifier): the parse does not break and the structure stays consistent. The
// parser recovers a type, so the constructor has a result that owns the parameters of the arguments.
TEST(InvocationStructure, KerMLBrokenConstructorsStayConsistent) {
    One m("package M {\n"
          "  datatype Real;\n"
          "  classifier P {\n"
          "    feature a = new (1, 2);\n"
          "    feature b = new (x = 1);\n"
          "  }\n"
          "}\n", SourceLanguage::KerML, "errors.kerml");
    EXPECT_FALSE(m.ws.errors().empty());
    for (const auto& element : m.ws.elements(0)) {
        if (auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(element)) EXPECT_NE(value->value(), nullptr);
        if (auto call = std::dynamic_pointer_cast<KerML::Entities::ConstructorExpression>(element)) {
            // The arguments are parameters of the result, never of the constructor itself.
            size_t results = 0;
            for (const auto& relationship : call->ownedRelationship()) {
                if (std::dynamic_pointer_cast<KerML::Entities::ReturnParameterMembership>(relationship)) ++results;
                else EXPECT_EQ(std::dynamic_pointer_cast<KerML::Entities::ParameterMembership>(relationship), nullptr);
            }
            EXPECT_EQ(results, 1u);
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// addTexts() and setCancellation() (smoke tests; the equivalence over the whole library is in the parallel loading tests)
// ---------------------------------------------------------------------------------------------------------------------

std::vector<SysMLv2::Files::TextInput> smallTexts() {
    return {
        {"package Lib { part def A; part def B :> A; }", "lib.sysml", SourceLanguage::Auto, 0},
        {"package U { import Lib::*; part a : A; part b : Missing; }", "use.sysml", SourceLanguage::Auto, 1},
        {"package Broken { part def ; }", "broken.sysml", SourceLanguage::SysML, 1},
    };
}

TEST(WorkspaceAddTexts, EqualsAddTextOneByOne) {
    Workspace reference;
    for (const auto& input : smallTexts()) reference.addText(input.text, input.name, input.language, input.level);
    reference.resolve();
    for (const unsigned threads : {1u, 2u, 0u, 8u}) {
        Workspace ws;
        std::vector<std::pair<size_t, size_t>> calls;
        const auto indices = ws.addTexts(smallTexts(), threads, [&](size_t done, size_t total) { calls.emplace_back(done, total); });
        ws.resolve();
        SCOPED_TRACE(threads);
        ASSERT_EQ(indices, (std::vector<size_t>{0, 1, 2}));
        ASSERT_EQ(ws.sourceCount(), reference.sourceCount());
        for (size_t i = 0; i < ws.sourceCount(); ++i) {
            EXPECT_EQ(ws.sourceName(i), reference.sourceName(i));
            EXPECT_EQ(ws.sourceLevel(i), reference.sourceLevel(i));
            EXPECT_EQ(ws.errors(i).size(), reference.errors(i).size());
        }
        EXPECT_GT(ws.errors(2).size(), 0u);
        EXPECT_EQ(ws.unresolvedReferences().size(), reference.unresolvedReferences().size());
        EXPECT_EQ(ws.resolvedReferenceCount(), reference.resolvedReferenceCount());
        EXPECT_EQ(typeOf(ws, "U::a").get(), ws.find("Lib::A").get());
        ASSERT_EQ(calls.size(), 3u);
        for (size_t i = 0; i < calls.size(); ++i) EXPECT_EQ(calls[i], std::make_pair(i + 1, size_t(3)));
    }
    // (the indices continue after the sources that are there already)
    Workspace ws;
    ws.addText("package First;", "first.sysml");
    EXPECT_EQ(ws.addTexts(smallTexts(), 2), (std::vector<size_t>{1, 2, 3}));
    EXPECT_TRUE(ws.addTexts({}, 4).empty());
    EXPECT_EQ(ws.sourceCount(), 4u);
}

TEST(WorkspaceCancellation, CancelledBeforeAddTextsLeavesTheWorkspaceUnchanged) {
    Workspace ws;
    ws.addText("package First;", "first.sysml");
    auto cancelled = std::make_shared<std::atomic<bool>>(true);
    ws.setCancellation(cancelled);
    for (const unsigned threads : {1u, 3u}) {
        EXPECT_THROW(ws.addTexts(smallTexts(), threads), SysMLv2::Files::ParseCancelled);
        EXPECT_EQ(ws.sourceCount(), 1u);
    }
    EXPECT_THROW(ws.addTexts(smallTexts(), 2), SysMLv2::Files::ParseTimeout);   // (a ParseCancelled is a ParseTimeout)
    EXPECT_THROW(ws.addText("package X;", "x.sysml"), SysMLv2::Files::ParseCancelled);
    EXPECT_THROW(ws.addText("<xmi/>", "x.sysmlx"), SysMLv2::Files::ParseCancelled);
    EXPECT_EQ(ws.sourceCount(), 1u);
    cancelled->store(false);
    EXPECT_EQ(ws.addTexts(smallTexts(), 2).size(), 3u);
    EXPECT_EQ(ws.sourceCount(), 4u);
    ws.setCancellation(nullptr);
}

TEST(WorkspaceCancellation, CancelledResolveBehavesLikeATimeout) {
    std::string text = "package P { part def A;";
    for (int i = 0; i < 60; ++i) text += " part a" + std::to_string(i) + " : A;";
    text += " }";
    Workspace ws;
    ws.addText(text, "many.sysml");
    auto cancelled = std::make_shared<std::atomic<bool>>(true);
    ws.setCancellation(cancelled);
    EXPECT_THROW(ws.resolve(), SysMLv2::Files::ParseCancelled);
    cancelled->store(false);
    ws.resolve();
    EXPECT_TRUE(ws.unresolvedReferences().empty());
    EXPECT_EQ(typeOf(ws, "P::a7").get(), ws.find("P::A").get());
}

}  // namespace
