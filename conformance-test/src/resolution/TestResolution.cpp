// AP10 (findings L3 / L4): scoped, qualified name resolution over a multi-file Workspace.
//
// Unit tests build small models with SysMLv2::Files::Workspace::addText and check what the names resolve to
// (KerML 8.2.3.5 / 7.2.5: local namespace, imported members, enclosing namespaces, global namespace; qualified names segment by
// segment; `::*`, `::**` and membership imports; public vs. private re-export; aliases; short names; quoted names; shadowing;
// cross-file references). The library tests load the whole standard library into one Workspace and check that every name
// resolves; references that do not are listed in conformance-test/expected_unresolved.txt (ratchet, same semantics as
// expected_failures.txt: a listed reference that now resolves fails, an unlisted unresolved one fails).
#include <gtest/gtest.h>

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <set>
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

TEST_F(LibraryResolution, LoadAndResolveStayWithinTheTimeBudget) {
    double budget = 60.0;
    if (const char* env = std::getenv("SYSML_RESOLVE_BUDGET_S")) {
        try {
            budget = std::stod(env);
        } catch (...) {
        }
    }
    RecordProperty("parse_seconds", std::to_string(parseSeconds));
    RecordProperty("resolve_seconds", std::to_string(resolveSeconds));
    EXPECT_LT(parseSeconds + resolveSeconds, budget) << "load " << parseSeconds << " s + resolve " << resolveSeconds << " s";
}

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

}  // namespace
