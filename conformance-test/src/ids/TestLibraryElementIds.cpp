// The ids of the elements of the model libraries (KerML 1.0, clause 9.1): the unit tests of Element::escapedName(), path() and of the two id
// functions with fixed values taken from the official XMI files (resources/sysml.library.xmi), and the end to end test that parses the standard
// library from its text and compares the ids of its elements with the ones of the official XMI files.
#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <kerml/KerML.h>
#include <kerml/model/LibraryElementIds.h>
#include <sysmlv2/Workspace.h>
#include <sysmlv2/xmi/XmiWriter.h>

#include "../support/XmiReader.h"

#ifndef SYSML_LIBRARY_DIR
#error "SYSML_LIBRARY_DIR must be defined by CMake to the resources/sysml.library path"
#endif
#ifndef SYSML_LIBRARY_XMI_DIR
#error "SYSML_LIBRARY_XMI_DIR must be defined by CMake to the resources/sysml.library.xmi path"
#endif

namespace {

namespace K = KerML::Entities;
using SysMLv2::Files::SourceLanguage;
using SysMLv2::Files::Workspace;
using ElementPtr = std::shared_ptr<K::Element>;

std::string text(const boost::uuids::uuid& id) { return boost::lexical_cast<std::string>(id); }

std::string describe(const ElementPtr& element) {
    return element->getType() + " " + element->path() + " " + element->elementId();
}

/// Calls @p visit for the root and everything it owns (relationships and elements), without recursion.
template <class Visit>
void walk(const ElementPtr& root, Visit visit) {
    std::unordered_set<const K::Element*> seen;
    std::vector<ElementPtr> pending{root};
    while (!pending.empty()) {
        ElementPtr element = pending.back();
        pending.pop_back();
        if (!element || !seen.insert(element.get()).second) continue;
        visit(element);
        for (const auto& relationship : element->ownedRelationship()) pending.push_back(relationship);
        if (const auto relationship = std::dynamic_pointer_cast<K::Relationship>(element)) {
            for (const auto& owned : relationship->ownedRelatedElement()) pending.push_back(owned);
        }
    }
}

ElementPtr findNamed(const ElementPtr& root, const std::string& qualifiedName) {
    ElementPtr found;
    walk(root, [&](const ElementPtr& element) {
        if (!found && element->computeQualifiedName() == qualifiedName) found = element;
    });
    return found;
}

// ---------------------------------------------------------------------------------------------------------------------
// The two id functions, with ids of the official XMI files (Base.kermlx, SampledFunctions.sysmlx).
// ---------------------------------------------------------------------------------------------------------------------

TEST(LibraryElementIds, IdOfATopLevelPackage) {
    EXPECT_EQ(text(K::libraryPackageId(K::LibraryLanguage::KerML, "Base")), "cdd5d1e3-fe4b-52bd-8a01-51a53f22ba47");
    EXPECT_EQ(text(K::libraryPackageId(K::LibraryLanguage::SysML, "SampledFunctions")), "c23077a9-5e53-52c9-af11-01bfd0292902");
    // the language is part of the URL
    EXPECT_NE(K::libraryPackageId(K::LibraryLanguage::KerML, "Base"), K::libraryPackageId(K::LibraryLanguage::SysML, "Base"));
}

TEST(LibraryElementIds, IdOfAContainedElement) {
    const auto base = K::libraryPackageId(K::LibraryLanguage::KerML, "Base");
    EXPECT_EQ(text(K::libraryElementId(base, "Base::Anything")), "d5b4e7df-e644-5f2f-b95e-cf6f1f6c076d");
    EXPECT_EQ(text(K::libraryElementId(base, "Base/owningMembership")), "a9f8a8e0-dadd-5c21-9ce2-414b155e5763");
    EXPECT_EQ(text(K::libraryElementId(base, "Base::Anything/owningMembership")), "5fa9ee75-dc34-54ea-917f-c0079e35dd32");
    EXPECT_EQ(text(K::libraryElementId(base, "Base/owner")), "1ad56763-6bac-5544-8fe7-829bcfe95024");

    // The name is the UTF-8 text of the path: the return parameter of SampledFunctions::Domain has the implied name "result".
    const auto sampled = K::libraryPackageId(K::LibraryLanguage::SysML, "SampledFunctions");
    EXPECT_EQ(text(K::libraryElementId(sampled, "SampledFunctions::Domain::result")), "19712a62-d614-5cd4-bafa-fe4fafdfdc06");
    EXPECT_EQ(text(K::libraryElementId(sampled, "SampledFunctions::Domain::result/owningMembership")), "ad9e2fda-7e4d-5ae2-b92c-487c5b85cf71");
}

// ---------------------------------------------------------------------------------------------------------------------
// escapedName() and path()
// ---------------------------------------------------------------------------------------------------------------------

struct Parsed {
    Workspace workspace;
    size_t source = 0;
    ElementPtr root;

    explicit Parsed(const std::string& model, SourceLanguage language = SourceLanguage::SysML) {
        source = workspace.addText(model, language == SourceLanguage::KerML ? "model.kerml" : "model.sysml", language);
        root = workspace.rootNamespace(source);
    }
};

TEST(LibraryElementIdsPath, EscapedName) {
    Parsed model("package P { part def A; part def 'B c'; part def 'action'; part def 'it\\'s'; part def '1st'; }");
    ASSERT_TRUE(model.root);
    EXPECT_EQ(findNamed(model.root, "P")->escapedName(), "P");
    EXPECT_EQ(findNamed(model.root, "P::A")->escapedName(), "A");
    // a name that is no basic name is quoted, the backslash and the single quote are escaped
    const auto spaced = findNamed(model.root, "P::'B c'");
    ASSERT_TRUE(spaced);
    EXPECT_EQ(spaced->escapedName(), "'B c'");
    const auto quote = findNamed(model.root, "P::'it\\'s'");
    ASSERT_TRUE(quote);
    EXPECT_EQ(quote->escapedName(), "'it\\'s'");
    EXPECT_EQ(findNamed(model.root, "P::'1st'")->escapedName(), "'1st'");
    // the reserved words are basic names for the qualified names of the libraries
    const auto keyword = findNamed(model.root, "P::action");
    ASSERT_TRUE(keyword);
    EXPECT_EQ(keyword->escapedName(), "action");
    // no name, no escaped name
    EXPECT_FALSE(model.root->escapedName().has_value());
}

TEST(LibraryElementIdsPath, ElementWithAQualifiedNameHasItAsPath) {
    Parsed model("package P { part def 'B c' { attribute x; } }");
    ASSERT_TRUE(model.root);
    const auto x = findNamed(model.root, "P::'B c'::x");
    ASSERT_TRUE(x);
    EXPECT_EQ(x->path(), "P::'B c'::x");
    EXPECT_EQ(x->computeQualifiedName(), "P::'B c'::x");
}

TEST(LibraryElementIdsPath, MembershipOfANamedElementEndsWithOwningMembership) {
    Parsed model("package P { part def A { attribute x; } }");
    ASSERT_TRUE(model.root);
    const auto a = findNamed(model.root, "P::A");
    const auto x = findNamed(model.root, "P::A::x");
    ASSERT_TRUE(a && x);
    ASSERT_TRUE(a->owningRelationship());
    EXPECT_EQ(a->owningRelationship()->path(), "P::A/owningMembership");
    // the membership of a feature is a FeatureMembership, an OwningMembership as well
    ASSERT_TRUE(x->owningRelationship());
    EXPECT_EQ(x->owningRelationship()->path(), "P::A::x/owningMembership");
    EXPECT_EQ(findNamed(model.root, "P")->owningRelationship()->path(), "P/owningMembership");
}

TEST(LibraryElementIdsPath, UnnamedElementsAreCountedInTheirOwner) {
    // The documentation is the first thing that P owns, the part def the second.
    Parsed model("package P { doc /* first */ part def A; comment /* second */ }");
    ASSERT_TRUE(model.root);
    const auto package = findNamed(model.root, "P");
    ASSERT_TRUE(package);
    const auto relationships = package->ownedRelationship();
    ASSERT_GE(relationships.size(), 3u);
    // the relationship is owned by P: path of P, "/", the position among the owned relationships of P
    EXPECT_EQ(relationships[0]->path(), "P/1");
    EXPECT_EQ(relationships[2]->path(), "P/3");
    // the documentation is owned by the relationship: its path, "/", the position among its owned related elements
    const auto owned = relationships[0]->ownedRelatedElement();
    ASSERT_EQ(owned.size(), 1u);
    EXPECT_EQ(owned[0]->path(), "P/1/1");
    // the root namespace has no path
    EXPECT_EQ(model.root->path(), "");
}

TEST(LibraryElementIdsPath, QualifiedNameIsComputedFromTheModel) {
    Parsed model("package P { part def A { part b; } }");
    ASSERT_TRUE(model.root);
    const auto b = findNamed(model.root, "P::A::b");
    ASSERT_TRUE(b);
    // the stored string is not what path() uses
    b->setQualifiedName("something::else");
    EXPECT_EQ(b->path(), "P::A::b");
}

// ---------------------------------------------------------------------------------------------------------------------
// The ids that Workspace assigns to the library packages of the sources it parses
// ---------------------------------------------------------------------------------------------------------------------

bool isRandomId(const boost::uuids::uuid& id) { return id.version() == boost::uuids::uuid::version_random_number_based; }

TEST(LibraryElementIdsWorkspace, SysMLLibraryPackageGetsStandardIds) {
    Parsed model("standard library package Lib { part def A { attribute x; } doc /* d */ }");
    ASSERT_TRUE(model.root);
    const auto package = findNamed(model.root, "Lib");
    ASSERT_TRUE(package);
    const auto packageId = K::libraryPackageId(K::LibraryLanguage::SysML, "Lib");
    EXPECT_EQ(package->elementIdAsUUID(), packageId);
    EXPECT_EQ(findNamed(model.root, "Lib::A")->elementIdAsUUID(), K::libraryElementId(packageId, "Lib::A"));
    EXPECT_EQ(findNamed(model.root, "Lib::A::x")->elementIdAsUUID(), K::libraryElementId(packageId, "Lib::A::x"));
    EXPECT_EQ(package->owningRelationship()->elementIdAsUUID(), K::libraryElementId(packageId, "Lib/owningMembership"));
    EXPECT_EQ(model.root->elementIdAsUUID(), K::libraryElementId(packageId, "Lib/owner"));
    // the Data id of the element is the same
    EXPECT_EQ(package->getId(), packageId);
    EXPECT_EQ(package->elementId(), text(packageId));
    // unnamed elements: the relationship of the documentation is owned by the package; it keeps its random id
    const auto doc = package->ownedRelationship().at(1);
    EXPECT_TRUE(isRandomId(doc->elementIdAsUUID()));
}

TEST(LibraryElementIdsWorkspace, KerMLLibraryPackageUsesTheKerMLUrl) {
    Parsed model("standard library package Lib { classifier A; }", SourceLanguage::KerML);
    ASSERT_TRUE(model.root);
    const auto package = findNamed(model.root, "Lib");
    ASSERT_TRUE(package);
    EXPECT_EQ(package->elementIdAsUUID(), K::libraryPackageId(K::LibraryLanguage::KerML, "Lib"));
}

TEST(LibraryElementIdsWorkspace, OrdinaryPackagesKeepRandomIds) {
    Parsed model("package P { part def A; }");
    ASSERT_TRUE(model.root);
    EXPECT_TRUE(isRandomId(findNamed(model.root, "P")->elementIdAsUUID()));
    EXPECT_TRUE(isRandomId(findNamed(model.root, "P::A")->elementIdAsUUID()));
    EXPECT_TRUE(isRandomId(model.root->elementIdAsUUID()));
}

TEST(LibraryElementIdsWorkspace, TheIdsOfNamedElementsDoNotDependOnTheRun) {
    const std::string library = "library package Lib { part def A { attribute x; } part def B :> A; }";
    Parsed first(library);
    Parsed second(library);
    for (const char* name : {"Lib", "Lib::A", "Lib::A::x", "Lib::B"}) {
        EXPECT_EQ(findNamed(first.root, name)->elementId(), findNamed(second.root, name)->elementId()) << name;
        // (and the membership of a named element)
        EXPECT_EQ(findNamed(first.root, name)->owningRelationship()->elementId(), findNamed(second.root, name)->owningRelationship()->elementId()) << name;
    }
    for (const auto& model : {&first, &second}) {
        std::set<std::string> distinct;
        size_t count = 0;
        walk(model->root, [&](const ElementPtr& element) {
            ++count;
            distinct.insert(element->elementId());
        });
        EXPECT_EQ(distinct.size(), count) << "two elements have the same id";
    }
}

std::string readFile(const std::filesystem::path& path) {
    std::ifstream in(path);
    std::stringstream content;
    content << in.rdbuf();
    return content.str();
}

/// A directory that no other run (or test) uses.
std::filesystem::path uniqueDirectory(const std::string& prefix) {
    static int counter = 0;
    const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
    const auto directory = std::filesystem::temp_directory_path() / (prefix + "-" + std::to_string(stamp) + "-" + std::to_string(++counter));
    std::filesystem::create_directories(directory);
    return directory;
}

TEST(LibraryElementIdsWorkspace, ExportKeepsTheStandardIds) {
    Parsed model("standard library package Lib { part def A; }");
    const auto package = findNamed(model.root, "Lib");
    ASSERT_TRUE(package);
    const auto directory = uniqueDirectory("library-element-ids-export");
    const auto file = directory / "Lib.sysmlx";
    SysMLv2::Files::XmiWriteOptions options;
    options.ids = SysMLv2::Files::XmiWriteOptions::IdMode::NameBased;
    EXPECT_TRUE(model.workspace.writeXmi(model.source, file.string(), options).empty());
    const std::string xml = readFile(file);
    const auto packageId = K::libraryPackageId(K::LibraryLanguage::SysML, "Lib");
    EXPECT_NE(xml.find(text(packageId)), std::string::npos);
    EXPECT_NE(xml.find(text(K::libraryElementId(packageId, "Lib::A"))), std::string::npos);
    EXPECT_NE(xml.find(text(K::libraryElementId(packageId, "Lib/owner"))), std::string::npos);
    // an ordinary package gets the name based id of the project
    Parsed ordinary("package P { part def A; }");
    const auto other = directory / "P.sysmlx";
    EXPECT_TRUE(ordinary.workspace.writeXmi(ordinary.source, other.string(), options).empty());
    EXPECT_EQ(readFile(other).find(text(packageId)), std::string::npos);
    std::error_code ignored;
    std::filesystem::remove_all(directory, ignored);
}

// ---------------------------------------------------------------------------------------------------------------------
// Duplicate names, short names, the stored qualified name, deep models, and ids that follow the resolved names
// ---------------------------------------------------------------------------------------------------------------------

std::vector<ElementPtr> allElements(const ElementPtr& root) {
    std::vector<ElementPtr> elements;
    walk(root, [&](const ElementPtr& element) { elements.push_back(element); });
    return elements;
}

TEST(LibraryElementIdsWorkspace, MembersWithTheSameNameGetDifferentIds) {
    Parsed model("standard library package L { part def A; part def A { attribute x; } part def B; }");
    ASSERT_TRUE(model.root);
    const auto packageId = K::libraryPackageId(K::LibraryLanguage::SysML, "L");
    // only the first of the members with the same name has a qualified name, the other is identified by its position
    std::vector<ElementPtr> definitions;
    walk(model.root, [&](const ElementPtr& element) {
        if (element->declaredName() == std::optional<std::string>("A")) definitions.push_back(element);
    });
    ASSERT_EQ(definitions.size(), 2u);
    const auto first = std::find_if(definitions.begin(), definitions.end(), [](const ElementPtr& e) { return e->computeQualifiedName().has_value(); });
    ASSERT_NE(first, definitions.end());
    const ElementPtr duplicate = first == definitions.begin() ? definitions[1] : definitions[0];
    EXPECT_EQ((*first)->path(), "L::A");
    EXPECT_FALSE(duplicate->computeQualifiedName().has_value());
    EXPECT_EQ((*first)->elementIdAsUUID(), K::libraryElementId(packageId, "L::A"));
    EXPECT_EQ((*first)->owningRelationship()->elementIdAsUUID(), K::libraryElementId(packageId, "L::A/owningMembership"));
    // (unnamed elements, and the elements that no qualified name identifies, keep their random ids)
    EXPECT_TRUE(isRandomId(duplicate->elementIdAsUUID()));
    EXPECT_TRUE(isRandomId(duplicate->owningRelationship()->elementIdAsUUID()));
    EXPECT_EQ(duplicate->path().rfind("L/", 0), 0u) << duplicate->path();
    // no two elements of the source have the same id
    std::set<std::string> ids;
    for (const auto& element : allElements(model.root)) EXPECT_TRUE(ids.insert(element->elementId()).second) << describe(element);

    // so the export has nothing to complain about (and the elements compare as different)
    const auto directory = uniqueDirectory("library-element-ids-duplicates");
    SysMLv2::Files::XmiWriteOptions options;
    options.ids = SysMLv2::Files::XmiWriteOptions::IdMode::NameBased;
    EXPECT_TRUE(model.workspace.writeXmi(model.source, (directory / "L.sysmlx").string(), options).empty());
    options.ids = SysMLv2::Files::XmiWriteOptions::IdMode::ElementId;
    EXPECT_TRUE(model.workspace.writeXmi(model.source, (directory / "L2.sysmlx").string(), options).empty());
    std::error_code ignored;
    std::filesystem::remove_all(directory, ignored);
    EXPECT_NE(duplicate->elementId(), (*first)->elementId());
}

TEST(LibraryElementIdsWorkspace, TwoTopLevelPackagesWithTheSameNameGetDifferentIds) {
    Parsed model("standard library package L { part def A; } library package L { part def A; }");
    ASSERT_TRUE(model.root);
    std::set<std::string> ids;
    for (const auto& element : allElements(model.root)) EXPECT_TRUE(ids.insert(element->elementId()).second) << describe(element);
}

TEST(LibraryElementIdsWorkspace, ShortNameIsTheNameWhenThereIsNoOther) {
    Parsed model("standard library package L { part def <s> { attribute x; } part def <t> named { attribute y; } }");
    ASSERT_TRUE(model.root);
    const auto packageId = K::libraryPackageId(K::LibraryLanguage::SysML, "L");
    const auto definition = findNamed(model.root, "L::s");
    ASSERT_TRUE(definition);
    EXPECT_EQ(definition->path(), "L::s");
    EXPECT_EQ(definition->elementIdAsUUID(), K::libraryElementId(packageId, "L::s"));
    EXPECT_EQ(findNamed(model.root, "L::s::x")->path(), "L::s::x");
    EXPECT_EQ(definition->owningRelationship()->path(), "L::s/owningMembership");
    // a name wins over the short name
    EXPECT_TRUE(findNamed(model.root, "L::named"));
    EXPECT_TRUE(findNamed(model.root, "L::named::y"));
    EXPECT_FALSE(findNamed(model.root, "L::t"));
}

TEST(LibraryElementIdsWorkspace, TheStoredQualifiedNameIsNeverAName) {
    Parsed model("standard library package L { part def <s> { attribute x; } part def A { attribute :>> y; } }");
    ASSERT_TRUE(model.root);
    const auto definition = findNamed(model.root, "L::s");
    ASSERT_TRUE(definition);
    // what a service stores after parsing (also for the elements that have no name)
    for (const auto& element : allElements(model.root)) element->setQualifiedName("Stored::" + element->elementId());
    EXPECT_EQ(definition->escapedName(), "s");
    EXPECT_EQ(definition->path(), "L::s");
    EXPECT_EQ(findNamed(model.root, "L::s::x")->path(), "L::s::x");
    // an unnamed element stays unnamed, however it was stored
    const auto relationship = definition->owningRelationship();
    ASSERT_TRUE(relationship);
    EXPECT_FALSE(relationship->escapedName().has_value());
    // and the ids of a later assignment are the same
    const auto before = definition->elementIdAsUUID();
    model.workspace.invalidateIndex();
    model.workspace.resolve();
    EXPECT_EQ(definition->elementIdAsUUID(), before);
}

TEST(LibraryElementIdsWorkspace, ADeepModelIsLinear) {
    // `1 + 1 + ... + 1` with 3000 terms nests 3000 levels to the left. Finding the path of every element from the first named owner (quadratic work,
    // and with strings that grow with the depth: minutes) made the parse of a library with this expression unusable. The bound is far above what
    // the linear walk needs (a few seconds in a debug build) and far below the time of the walk that starts at every element.
    std::string expression = "1";
    for (int term = 1; term < 3000; ++term) expression += " + 1";
    const auto begin = std::chrono::steady_clock::now();
    Parsed model("standard library package L { attribute a = " + expression + "; }");
    model.workspace.resolve();
    const double seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - begin).count();
    std::cout << "  3000 terms in a library package: parse, ids and resolve took " << seconds << " s\n";
    ASSERT_TRUE(model.root);
    EXPECT_LT(seconds, 120.0);
    size_t count = 0;
    std::set<std::string> ids;
    walk(model.root, [&](const ElementPtr& element) {
        ++count;
        ids.insert(element->elementId());
    });
    EXPECT_GT(count, 3000u * 2);
    EXPECT_EQ(ids.size(), count) << "two elements have the same id";
    const auto packageId = K::libraryPackageId(K::LibraryLanguage::SysML, "L");
    EXPECT_EQ(findNamed(model.root, "L::a")->elementIdAsUUID(), K::libraryElementId(packageId, "L::a"));
}

TEST(LibraryElementIdsWorkspace, TheIdsFollowTheNamesThatResolvingGives) {
    // L1::D::f redefines the feature with the short name s of L2::E: it is named after that feature (alpha), which is only known when L2 is
    // there. L1 is parsed first, so until L2 is added the reference is a placeholder named s, and the id of f is the one of "L1::D::s" (an id that
    // is not final); the resolved references of L1 change when L2 is added, and so does the id.
    const std::string user = "standard library package L1 { part def D :> L2::E { attribute :>> s; part def Other; } }";
    const std::string library = "standard library package L2 { part def E { attribute <s> alpha; } }";
    Workspace workspace;
    const size_t first = workspace.addText(user, "L1.sysml", SourceLanguage::SysML);
    workspace.resolve();
    const auto root = workspace.rootNamespace(first);
    const auto packageId = K::libraryPackageId(K::LibraryLanguage::SysML, "L1");
    const auto other = findNamed(root, "L1::D::Other");
    const auto definition = findNamed(root, "L1::D");
    ASSERT_TRUE(other && definition);
    EXPECT_FALSE(findNamed(root, "L1::D::alpha"));
    const auto otherId = other->elementIdAsUUID();
    const auto definitionId = definition->elementIdAsUUID();

    workspace.addText(library, "L2.sysml", SourceLanguage::SysML);
    workspace.resolve();
    const auto redefining = findNamed(root, "L1::D::alpha");
    ASSERT_TRUE(redefining) << "the redefinition is not named after the redefined feature";
    EXPECT_EQ(redefining->elementIdAsUUID(), K::libraryElementId(packageId, "L1::D::alpha"));
    // what did not change keeps its id
    EXPECT_EQ(other->elementIdAsUUID(), otherId);
    EXPECT_EQ(definition->elementIdAsUUID(), definitionId);
    // another pass changes nothing
    workspace.setLibraryVendorBase(workspace.libraryVendorBase());
    workspace.resolve();
    EXPECT_EQ(redefining->elementIdAsUUID(), K::libraryElementId(packageId, "L1::D::alpha"));
    EXPECT_EQ(other->elementIdAsUUID(), otherId);
    // and nothing is shared
    std::set<std::string> ids;
    for (const auto& element : allElements(root)) EXPECT_TRUE(ids.insert(element->elementId()).second) << describe(element);
}

TEST(LibraryElementIdsWorkspace, ReplacingASourceKeepsTheIdsOfWhatDidNotChange) {
    Workspace workspace;
    const size_t source = workspace.addText("standard library package L { part def A { attribute x; } part def B; }", "L.sysml", SourceLanguage::SysML);
    workspace.resolve();
    const auto packageId = K::libraryPackageId(K::LibraryLanguage::SysML, "L");
    workspace.replaceSource(source, "standard library package L { part def A { attribute y; } part def B; }");
    workspace.resolve();
    const auto root = workspace.rootNamespace(source);
    ASSERT_TRUE(root);
    EXPECT_EQ(findNamed(root, "L::B")->elementIdAsUUID(), K::libraryElementId(packageId, "L::B"));
    EXPECT_EQ(findNamed(root, "L::A::y")->elementIdAsUUID(), K::libraryElementId(packageId, "L::A::y"));
    EXPECT_FALSE(findNamed(root, "L::A::x"));
    std::set<std::string> ids;
    for (const auto& element : allElements(root)) EXPECT_TRUE(ids.insert(element->elementId()).second) << describe(element);
}

TEST(LibraryElementIdsWorkspace, UnnamedElementsKeepRandomIds) {
    const std::string library = "standard library package Lib { doc /* d */ part def A { attribute x = 1 + 2; } part def <s>; }";
    Parsed first(library);
    Parsed second(library);
    ASSERT_TRUE(first.root && second.root);
    const auto packageId = K::libraryPackageId(K::LibraryLanguage::SysML, "Lib");
    size_t named = 0, unnamed = 0;
    std::set<std::string> firstUnnamed;
    walk(first.root, [&](const ElementPtr& element) {
        const bool standard = element->elementIdAsUUID() == K::libraryElementId(packageId, element->path()) || element->elementIdAsUUID() == packageId;
        // an element has a standard id if its path is its qualified name, or the membership of such an element, or it is the root namespace
        const auto member = std::dynamic_pointer_cast<K::OwningMembership>(element) ? std::dynamic_pointer_cast<K::OwningMembership>(element)->ownedMemberElement() : nullptr;
        const bool nameBased = element->computeQualifiedName().has_value() || (member && member->computeQualifiedName().has_value()) || element == first.root;
        if (nameBased) {
            ++named;
            EXPECT_TRUE(standard || element == first.root) << describe(element);
        } else {
            ++unnamed;
            EXPECT_TRUE(isRandomId(element->elementIdAsUUID())) << describe(element);
            firstUnnamed.insert(element->elementId());
        }
    });
    EXPECT_GT(named, 4u);
    EXPECT_GT(unnamed, 4u);
    // the random ids differ between two parses, the standard ones do not
    walk(second.root, [&](const ElementPtr& element) {
        if (!element->computeQualifiedName().has_value() && element != second.root && !std::dynamic_pointer_cast<K::OwningMembership>(element))
            EXPECT_EQ(firstUnnamed.count(element->elementId()), 0u) << describe(element);
    });
    EXPECT_EQ(findNamed(first.root, "Lib::A::x")->elementIdAsUUID(), findNamed(second.root, "Lib::A::x")->elementIdAsUUID());
}

TEST(LibraryElementIdsWorkspace, NonStandardLibrariesUseTheVendorBase) {
    // Expected values computed independently (python: uuid.uuid5(uuid.NAMESPACE_URL, url), and uuid5 of that in the namespace of the package).
    EXPECT_EQ(K::defaultLibraryVendorBase(), "https://sysml.protestator-research.com/");
    EXPECT_EQ(text(K::vendorPackageId("", "MyLib")), "39ac6c19-8d3a-5c4e-b134-a1ae043a6871");
    EXPECT_EQ(text(K::vendorPackageId(K::defaultLibraryVendorBase(), "MyLib")), "39ac6c19-8d3a-5c4e-b134-a1ae043a6871");
    EXPECT_EQ(text(K::vendorPackageId("https://example.org/sysml", "MyLib")), "56f7ba4d-b9e3-5fe9-8467-8f2e43001ad4");
    EXPECT_EQ(text(K::vendorPackageId("https://example.org/sysml/", "MyLib")), "56f7ba4d-b9e3-5fe9-8467-8f2e43001ad4");

    Parsed model("library package MyLib { part def A; }");
    ASSERT_TRUE(model.root);
    EXPECT_EQ(text(findNamed(model.root, "MyLib")->elementIdAsUUID()), "39ac6c19-8d3a-5c4e-b134-a1ae043a6871");
    EXPECT_EQ(text(findNamed(model.root, "MyLib::A")->elementIdAsUUID()), "7f3b9d83-f04a-593f-a4d8-0006cea2a494");
    // the same for KerML
    Parsed kerml("library package MyLib { classifier A; }", SourceLanguage::KerML);
    EXPECT_EQ(text(findNamed(kerml.root, "MyLib")->elementIdAsUUID()), "39ac6c19-8d3a-5c4e-b134-a1ae043a6871");
}

TEST(LibraryElementIdsWorkspace, ANonStandardPackageWithTheNameOfAStandardOneDoesNotGetTheOfficialId) {
    Parsed user("library package ScalarValues { part def A; }");
    Parsed standard("standard library package ScalarValues { part def A; }");
    ASSERT_TRUE(user.root && standard.root);
    const auto official = K::libraryPackageId(K::LibraryLanguage::SysML, "ScalarValues");
    EXPECT_EQ(text(official), "f30273bb-b118-50dc-9fd9-6bb911801b67");
    EXPECT_EQ(findNamed(standard.root, "ScalarValues")->elementIdAsUUID(), official);
    EXPECT_NE(findNamed(user.root, "ScalarValues")->elementIdAsUUID(), official);
    EXPECT_EQ(findNamed(user.root, "ScalarValues")->elementIdAsUUID(), K::vendorPackageId("", "ScalarValues"));
    EXPECT_NE(findNamed(user.root, "ScalarValues::A")->elementIdAsUUID(), findNamed(standard.root, "ScalarValues::A")->elementIdAsUUID());
}

TEST(LibraryElementIdsWorkspace, TheVendorBaseIsASetting) {
    Workspace workspace;
    EXPECT_EQ(workspace.libraryVendorBase(), "https://sysml.protestator-research.com/");
    workspace.setLibraryVendorBase("https://example.org/sysml");
    EXPECT_EQ(workspace.libraryVendorBase(), "https://example.org/sysml/");
    const size_t source = workspace.addText("library package MyLib { part def A; } standard library package Std { part def B; }", "m.sysml", SourceLanguage::SysML);
    const auto root = workspace.rootNamespace(source);
    ASSERT_TRUE(root);
    EXPECT_EQ(text(findNamed(root, "MyLib")->elementIdAsUUID()), "56f7ba4d-b9e3-5fe9-8467-8f2e43001ad4");
    EXPECT_EQ(text(findNamed(root, "MyLib::A")->elementIdAsUUID()), "be17d377-6dbf-5b3f-a419-71d9cd1c9581");
    const auto standardId = findNamed(root, "Std")->elementIdAsUUID();
    EXPECT_EQ(standardId, K::libraryPackageId(K::LibraryLanguage::SysML, "Std"));

    // a change after the parse is used by the next resolve(), for all sources; the standard packages do not change
    workspace.setLibraryVendorBase("");
    EXPECT_EQ(workspace.libraryVendorBase(), K::defaultLibraryVendorBase());
    workspace.resolve();
    EXPECT_EQ(text(findNamed(root, "MyLib")->elementIdAsUUID()), "39ac6c19-8d3a-5c4e-b134-a1ae043a6871");
    EXPECT_EQ(text(findNamed(root, "MyLib::A")->elementIdAsUUID()), "7f3b9d83-f04a-593f-a4d8-0006cea2a494");
    EXPECT_EQ(findNamed(root, "Std")->elementIdAsUUID(), standardId);
}

TEST(LibraryElementIdsWorkspace, TheSameTextHasOtherIdsUnderAnotherBase) {
    const std::string library = "library package MyLib { part def A { attribute x; } }";
    Workspace one, two;
    one.setLibraryVendorBase("https://one.example/");
    two.setLibraryVendorBase("https://two.example/");
    const auto first = one.rootNamespace(one.addText(library, "m.sysml", SourceLanguage::SysML));
    const auto second = two.rootNamespace(two.addText(library, "m.sysml", SourceLanguage::SysML));
    for (const char* name : {"MyLib", "MyLib::A", "MyLib::A::x"}) {
        EXPECT_NE(findNamed(first, name)->elementIdAsUUID(), findNamed(second, name)->elementIdAsUUID()) << name;
        EXPECT_FALSE(isRandomId(findNamed(first, name)->elementIdAsUUID()));
    }
}

TEST(LibraryElementIdsWorkspace, TheStoredQualifiedNameDoesNotChangeTheNameOfAResultParameter) {
    // The result of G has only a short name; F specializes G, so its (unnamed) result is known by that name. The qualified names that a service stores
    // after parsing must not become names (the effective name falls back to them).
    Parsed model("standard library package L { function G { return feature <r> : Anything; } function F specializes G { return feature : Anything; } }",
                 SourceLanguage::KerML);
    model.workspace.resolve();
    ASSERT_TRUE(model.root);
    std::map<ElementPtr, std::string> before;
    for (const auto& element : allElements(model.root)) before[element] = element->elementId();
    const auto function = findNamed(model.root, "L::F");
    ASSERT_TRUE(function);
    const auto result = function->ownedRelationship().back()->ownedRelatedElement().front();
    const std::string path = result->path();
    EXPECT_EQ(path.rfind("L::F::", 0), 0u) << path;

    for (const auto& element : allElements(model.root)) element->setQualifiedName("Stored::" + element->elementId());
    model.workspace.invalidateIndex();
    model.workspace.resolve();
    EXPECT_EQ(result->path(), path);
    for (const auto& element : allElements(model.root)) EXPECT_EQ(element->elementId(), before[element]) << element->getType() << " " << element->path();
}

TEST(LibraryElementIdsWorkspace, TheIdsOfFeaturesNamedByAnAliasAreFinalAfterResolve) {
    // `:>> gg` names the feature after what gg stands for (g): known only when the reference is resolved; until then the placeholder has the name gg.
    Parsed model("library package L { part def B { attribute g; alias gg for g; } part def A :> B { attribute :>> gg; } }");
    ASSERT_TRUE(model.root);
    model.workspace.resolve();
    const auto packageId = K::vendorPackageId(K::defaultLibraryVendorBase(), "L");
    const auto feature = findNamed(model.root, "L::A::g");
    ASSERT_TRUE(feature) << "the redefining feature is not named after the feature that the alias stands for";
    EXPECT_EQ(feature->elementIdAsUUID(), K::libraryElementId(packageId, "L::A::g"));
    EXPECT_FALSE(findNamed(model.root, "L::A::gg"));
}

TEST(LibraryElementIdsWorkspace, NoIdIsSharedBetweenSources) {
    const std::string library = "standard library package L { part def A; }";
    for (const bool together : {false, true}) {
        Workspace workspace;
        if (together) {
            workspace.addTexts({{library, "one.sysml", SourceLanguage::SysML, 0}, {library, "two.sysml", SourceLanguage::SysML, 0}}, 2);
        } else {
            workspace.addText(library, "one.sysml", SourceLanguage::SysML);
            workspace.addText(library, "two.sysml", SourceLanguage::SysML);
        }
        workspace.resolve();
        const auto first = workspace.rootNamespace(0);
        const auto second = workspace.rootNamespace(1);
        ASSERT_TRUE(first && second);
        std::set<std::string> ids;
        size_t count = 0;
        for (const auto& root : {first, second}) {
            for (const auto& element : allElements(root)) {
                ids.insert(element->elementId());
                ++count;
            }
        }
        EXPECT_EQ(ids.size(), count) << "an id is shared";
        // the first source has the ids of the name, the second random ones
        const auto packageId = K::libraryPackageId(K::LibraryLanguage::SysML, "L");
        EXPECT_EQ(findNamed(first, "L")->elementIdAsUUID(), packageId);
        EXPECT_EQ(findNamed(first, "L::A")->elementIdAsUUID(), K::libraryElementId(packageId, "L::A"));
        EXPECT_TRUE(isRandomId(findNamed(second, "L")->elementIdAsUUID()));
        EXPECT_TRUE(isRandomId(findNamed(second, "L::A")->elementIdAsUUID()));
        // and the export has nothing to complain about
        const auto directory = uniqueDirectory("library-element-ids-sources");
        SysMLv2::Files::XmiWriteOptions options;
        const auto errors = workspace.exportXmi(directory.string(), options);
        EXPECT_TRUE(errors.empty()) << errors.size() << " errors, the first: " << (errors.empty() ? std::string() : errors.front()->description());
        std::error_code ignored;
        std::filesystem::remove_all(directory, ignored);
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// The standard library from its text against the official XMI files
// ---------------------------------------------------------------------------------------------------------------------

/// How many of the official ids the text model has, and on which kind of element.
struct Counter {
    size_t total = 0;
    /// The text model has the id on an element of the same metaclass.
    size_t sameMetaclass = 0;
    /// The text model has the id, but on an element of another metaclass (the id is the one of another thing: not a match).
    size_t otherMetaclass = 0;
    /// Of the ids on an element of the same metaclass, the ones whose element has not the path that the XML gives (checked where the XML gives one).
    size_t pathMismatch = 0;
    std::vector<std::string> misses;

    void add(const ElementPtr& found, const std::string& officialType, const std::string& description, const std::optional<std::string>& officialPath = std::nullopt) {
        ++total;
        if (found && found->getType() == officialType) {
            ++sameMetaclass;
            if (officialPath && found->path() != *officialPath) {
                ++pathMismatch;
                if (misses.size() < 8) misses.push_back("path " + found->path() + " instead of " + *officialPath);
            }
            return;
        }
        if (found) ++otherMetaclass;
        if (misses.size() < 8) misses.push_back((found ? "on a " + found->getType() + ": " : std::string("absent: ")) + description);
    }
    double rate() const { return total == 0 ? 1.0 : static_cast<double>(sameMetaclass) / static_cast<double>(total); }
};

bool isNamed(const ElementPtr& element) { return element->computeQualifiedName().has_value(); }

/// The shape of what an element owns below it, down to the next named elements (which have a shape of their own): the types of the owned
/// relationships and of the unnamed elements they own, in order. The nesting of the unnamed elements is shallow in the libraries.
std::string shapeOf(const ElementPtr& element) {
    std::string shape;
    for (const auto& relationship : element->ownedRelationship()) {
        shape += "[" + relationship->getType();
        for (const auto& owned : relationship->ownedRelatedElement()) {
            shape += " ";
            shape += isNamed(owned) ? "named:" + owned->getType() : owned->getType() + shapeOf(owned);
        }
        shape += "]";
    }
    return shape;
}

/// The unnamed elements and relationships that @p element owns below it, down to the next named elements.
std::vector<ElementPtr> unnamedBelow(const ElementPtr& element) {
    std::vector<ElementPtr> result;
    std::vector<ElementPtr> pending{element};
    while (!pending.empty()) {
        ElementPtr current = pending.back();
        pending.pop_back();
        for (const auto& relationship : current->ownedRelationship()) {
            result.push_back(relationship);
            for (const auto& owned : relationship->ownedRelatedElement()) {
                if (owned && !isNamed(owned)) {
                    result.push_back(owned);
                    pending.push_back(owned);
                }
            }
        }
    }
    return result;
}

/// A feature without a name that is a parameter of its type (other than the result: its name is implied by the type, see Feature::impliedName()): the
/// implied redefinition of the parameter of a specialized type gives it the name of that parameter in the official model, which the implied relationships
/// are not part of the XMI for, and the names of what it owns, and the paths of the relationships around it, are made of it.
bool isUnnamedParameter(const ElementPtr& element) {
    return std::dynamic_pointer_cast<K::Feature>(element) && !element->name().has_value() &&
           std::dynamic_pointer_cast<K::ParameterMembership>(element->owningRelationship()) &&
           !std::dynamic_pointer_cast<K::ReturnParameterMembership>(element->owningRelationship());
}

/// Whether the id of the element depends on the name of an unnamed parameter: the element is one, it is owned by one (directly or indirectly), or it is
/// the membership of one.
bool dependsOnAnImpliedName(const ElementPtr& element) {
    ElementPtr current = element;
    if (const auto membership = std::dynamic_pointer_cast<K::OwningMembership>(element); membership && membership->ownedMemberElement()) {
        current = membership->ownedMemberElement();
    }
    for (std::unordered_set<const K::Element*> seen; current && seen.insert(current.get()).second;) {
        if (isUnnamedParameter(current)) return true;
        if (const auto relationship = std::dynamic_pointer_cast<K::Relationship>(current); relationship && !relationship->owningRelationship()) {
            current = relationship->owningRelatedElement();
        } else {
            current = current->owningRelationship();
        }
    }
    return false;
}

bool isMembershipOfAMember(const ElementPtr& element, const std::function<bool(const ElementPtr&)>& isMember) {
    const auto membership = std::dynamic_pointer_cast<K::OwningMembership>(element);
    return membership && membership->ownedMemberElement() && isMember(membership->ownedMemberElement());
}

// The comparison. Every element of the official XMI files is looked up by its id among the ids of the library parsed from text, and the metaclass of
// the element that carries the id must be the one of the official element (an id on an element of another metaclass is counted separately: it is
// not a match). The classification of the official side comes from the XML of the files (support/XmiReader.h: declared names, the names that the
// explicit redefinitions give, ownership), not from the code under test. What is asserted:
//  - the root namespace, the top-level packages, every element that the XML gives a qualified name, the owning memberships of these elements, and
//    the elements whose name is the implied name of a result parameter, with their memberships: all ids are on elements of the right metaclass;
//  - the unnamed elements and relationships below a named element for which the text model owns the same relationships and elements (same types, same order):
//    all ids are on elements of the right metaclass, with the exception of the known defect below.
// Unnamed elements and relationships keep random ids today (see getsPositionalId()), so their official ids are not in the text model: that is the known gap,
// reported below. The shape analysis tells how far the parser is from the official structure (the pools only matter once positional ids are turned on).
// What is reported, not asserted:
//  - "different shape": the official model has structure that the text parser does not build or builds in another order, so the positions that the
//    paths of the unnamed elements are made of differ, and so do their ids. The output lists the types that the official model has more or less
//    often (typeSurplus): it has many more Feature, ReturnParameterMembership, ParameterMembership, FeatureValue, MultiplicityRange and Membership
//    elements, the text model many more FeatureMembership and Multiplicity ones, so the parser builds the expressions, the multiplicities and
//    the implied features differently. (The abstract-syntax suite does not compare the anonymous elements and what is below them either, see
//    support/ModelDiff.h.) Whether such elements should get ids at all is decided in one place (getsPositionalId() in LibraryElementIds.cpp).
//  - KNOWN DEFECT, "same shape, depends on the name of an unnamed parameter": an unnamed parameter other than the result (for example the subject of
//    Requirements::DesignConstraintCheck) is named after the parameter that it implicitly redefines in the official model. The implied relationships are
//    neither in the XMI nor in the text model, so the ids of these parameters, of their memberships and of what they own are wrong. Not an artefact of
//    the measurement: only the names of result parameters are derived (Feature::impliedName()).
struct Comparison {
    std::map<std::string, Counter> counters;
    /// The unnamed elements and relationships, by what the text model owns below the same named element as the official model: "same shape" if it owns the
    /// same relationships and elements (by type and order), else "different shape".
    std::map<std::string, Counter> shapes;
    /// For the named elements whose shape differs: how often a type occurs in the official model more (+) or less (-) often than in the text model.
    std::map<std::string, long> typeSurplus;
    size_t sameShapeNamed = 0;
    size_t differentShapeNamed = 0;
    std::unordered_map<std::string, ElementPtr> textById;   // every element of the library parsed from text
    size_t xmiElements = 0;
    size_t xmiPackages = 0;
    double textSeconds = 0;
    double passSeconds = 0;
    /// The ids of the text library that are not random (version 4) and are not an id of the official files.
    size_t standardIds = 0;
    size_t standardIdsNotOfficial = 0;

    Comparison() {
        // (no id is assigned here: the ids are the ones that the Workspace assigned while it parsed and resolved)
        Workspace text;
        const auto begin = std::chrono::steady_clock::now();
        const size_t files = text.loadLibrary(SYSML_LIBRARY_DIR);
        EXPECT_GT(files, 0u);
        text.resolve();
        textSeconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - begin).count();
        // (what one assignment pass over the whole library costs: the next resolve() assigns again after a change of the base)
        const auto pass = std::chrono::steady_clock::now();
        text.setLibraryVendorBase(text.libraryVendorBase());
        text.resolve();
        passSeconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - pass).count();
        for (size_t source = 0; source < text.sourceCount(); ++source) {
            walk(text.rootNamespace(source), [&](const ElementPtr& element) { textById.emplace(element->elementId(), element); });
        }
        ConformanceTest::Xmi::Corpus corpus{SYSML_LIBRARY_XMI_DIR};
        std::unordered_set<std::string> officialIds;
        for (const auto& path : corpus.listFiles()) {
            for (const auto& entry : corpus.file(path).byId) officialIds.insert(entry.first);
        }
        for (const auto& [id, element] : textById) {
            if (isRandomId(element->elementIdAsUUID())) continue;
            ++standardIds;
            if (officialIds.count(id) == 0) ++standardIdsNotOfficial;
        }
        const auto textElement = [this](const std::string& id) -> ElementPtr {
            const auto found = textById.find(id);
            return found == textById.end() ? nullptr : found->second;
        };

        Workspace xmi;
        EXPECT_GT(xmi.loadLibrary(SYSML_LIBRARY_XMI_DIR), 0u);
        xmi.resolve();
        for (size_t source = 0; source < xmi.sourceCount(); ++source) {
            const ElementPtr root = xmi.rootNamespace(source);
            if (!root) continue;
            const auto& file = corpus.file(xmi.sourceName(source));
            // The XML side: the official type of an element, and whether its qualified name is known without the code under test.
            const auto xmlIndex = [&](const ElementPtr& element) {
                const auto found = file.byId.find(element->elementId());
                return found == file.byId.end() ? -1 : found->second;
            };
            const auto officialType = [&](const ElementPtr& element) {
                const int index = xmlIndex(element);
                return index < 0 ? element->getType() : file.elements[static_cast<size_t>(index)].type;
            };
            const auto xmlNamed = [&](const ElementPtr& element) {
                const int index = xmlIndex(element);
                return index >= 0 && corpus.qualifiedName(file, index).has_value();
            };
            const auto xmlPath = [&](const ElementPtr& element) -> std::optional<std::string> {
                const int index = xmlIndex(element);
                return index < 0 ? std::nullopt : corpus.qualifiedName(file, index);
            };
            // An element without a name that the ReturnParameterMembership of its owner owns: the result parameter, which has an implied name.
            const auto xmlResultParameter = [&](const ElementPtr& element) {
                const int index = xmlIndex(element);
                if (index < 0 || xmlNamed(element)) return false;
                const auto& xml = file.elements[static_cast<size_t>(index)];
                return xml.owningRelationship >= 0 && xml.name.empty() && xml.shortName.empty() &&
                       file.elements[static_cast<size_t>(xml.owningRelationship)].type == "ReturnParameterMembership";
            };

            std::vector<ElementPtr> owners{root};
            walk(root, [&](const ElementPtr& element) {
                ++xmiElements;
                if (element != root && isNamed(element)) owners.push_back(element);
                std::string category;
                std::optional<std::string> officialPath;
                if (element == root) {
                    category = "root namespace";
                } else if (std::dynamic_pointer_cast<K::LibraryPackage>(element) && element->owningRelationship() &&
                           element->owningRelationship()->owningRelatedElement() == root) {
                    category = "top-level package";
                    ++xmiPackages;
                    officialPath = xmlPath(element);
                } else if (xmlNamed(element)) {
                    category = "element with a qualified name";
                    officialPath = xmlPath(element);
                } else if (isMembershipOfAMember(element, xmlNamed)) {
                    category = "owning membership of a named element";
                    const auto member = std::dynamic_pointer_cast<K::OwningMembership>(element)->ownedMemberElement();
                    officialPath = *xmlPath(member) + "/owningMembership";
                } else if (isNamed(element)) {
                    // (named by the code under test, by the implied name of a result parameter: it is a result parameter by the XML, or it is below one)
                    category = xmlResultParameter(element) ? "result parameter (implied name)" : "named only by the implied name of the result parameter that owns it (not asserted)";
                } else if (isMembershipOfAMember(element, isNamed)) {
                    const auto member = std::dynamic_pointer_cast<K::OwningMembership>(element)->ownedMemberElement();
                    category = xmlResultParameter(member) ? "owning membership of a result parameter (implied name)" : "owning membership of such an element (not asserted)";
                } else {
                    return;   // the unnamed ones are counted below
                }
                counters[category].add(textElement(element->elementId()), officialType(element), describe(element), officialPath);
            });

            // The unnamed elements and relationships below the root namespace and every named element.
            std::unordered_set<const K::Element*> counted;
            for (const auto& owner : owners) {
                std::vector<ElementPtr> unnamed;
                for (const auto& element : unnamedBelow(owner)) {
                    if (!isMembershipOfAMember(element, isNamed) && counted.insert(element.get()).second) unnamed.push_back(element);
                }
                if (unnamed.empty()) continue;
                const auto counterpart = textById.find(owner->elementId());
                const bool same = counterpart != textById.end() && shapeOf(counterpart->second) == shapeOf(owner);
                ++(same ? sameShapeNamed : differentShapeNamed);
                for (const auto& element : unnamed) {
                    const std::string pool = !same ? "different shape"
                                             : dependsOnAnImpliedName(element) ? "KNOWN DEFECT: same shape, depends on the name of an unnamed parameter"
                                                                                : "same shape";
                    shapes[pool].add(textElement(element->elementId()), officialType(element), describe(element));
                }
                if (!same && counterpart != textById.end()) {
                    for (const auto& element : unnamed) ++typeSurplus[element->getType()];
                    for (const auto& element : unnamedBelow(counterpart->second)) {
                        if (!isMembershipOfAMember(element, isNamed)) --typeSurplus[element->getType()];
                    }
                }
            }
        }
    }
};

Comparison& comparison() {
    static Comparison instance;
    return instance;
}

TEST(LibraryElementIdsStandardLibrary, TheIdsOfTheTextAgreeWithTheOfficialXmi) {
    Comparison& result = comparison();
    ASSERT_GT(result.xmiPackages, 0u);
    std::cout << "text library: " << result.textById.size() << " elements, parsed, resolved and identified in " << result.textSeconds
              << " s (a second resolve() with an assignment pass over all sources: " << result.passSeconds << " s); XMI library: " << result.xmiElements << " elements\n";
    size_t all = 0, allSame = 0, allOther = 0;
    const auto print = [&](const std::string& name, const Counter& counter) {
        all += counter.total;
        allSame += counter.sameMetaclass;
        allOther += counter.otherMetaclass;
        std::cout << "    " << name << ": " << counter.sameMetaclass << " of " << counter.total << " ids on an element of the same metaclass ("
                  << counter.rate() * 100 << " %), " << counter.otherMetaclass << " on an element of another metaclass, "
                  << counter.total - counter.sameMetaclass - counter.otherMetaclass << " not in the text model, " << counter.pathMismatch
                  << " with another path than the XML gives\n";
        for (const auto& miss : counter.misses) std::cout << "        " << miss << "\n";
    };
    std::cout << "  elements that a qualified name identifies:\n";
    for (const auto& [category, counter] : result.counters) print(category, counter);
    std::cout << "  unnamed elements and relationships (named elements with the same shape below them: " << result.sameShapeNamed
              << ", with a different shape: " << result.differentShapeNamed << "):\n";
    for (const auto& [shape, counter] : result.shapes) print(shape, counter);
    std::cout << "  all elements of the official model: " << allSame << " of " << all << " ids on an element of the same metaclass, " << allOther
              << " on an element of another metaclass\n";
    std::cout << "  types that the official model has more (+) or less (-) often than the text model below the named elements of a different shape:\n";
    for (const auto& [type, surplus] : result.typeSurplus) {
        if (surplus != 0) std::cout << "    " << type << ": " << (surplus > 0 ? "+" : "") << surplus << "\n";
    }

    // Asserted: the root namespaces, the top-level packages, the elements that the XML gives a qualified name, their owning memberships, and the
    // elements named by the implied name of a result parameter with their memberships have their official id, on an element of the right metaclass.
    for (const char* category : {"root namespace", "top-level package", "element with a qualified name", "owning membership of a named element",
                                 "result parameter (implied name)", "owning membership of a result parameter (implied name)"}) {
        const Counter& counter = result.counters[category];
        EXPECT_GT(counter.total, 0u) << category;
        EXPECT_EQ(counter.sameMetaclass, counter.total) << category;
        // (and the path of the element, which the id is made of, is the one that the XML gives, where it gives one)
        EXPECT_EQ(counter.pathMismatch, 0u) << category;
    }
    // Every id of the text library that is not random is an id of the official files (no id of an element that the official model does not have).
    std::cout << "  ids of the text library that are not random: " << result.standardIds << ", of which not in the official files: " << result.standardIdsNotOfficial << "\n";
    EXPECT_GT(result.standardIds, 0u);
    EXPECT_EQ(result.standardIdsNotOfficial, 0u);
    // No official id is on an element of another metaclass, anywhere.
    EXPECT_EQ(allOther, 0u);
    // The gap: the unnamed elements and relationships keep their random ids (getsPositionalId() in LibraryElementIds.cpp), so their official ids are not in the text model.
    std::cout << "  official ids that the text model does not have (the unnamed elements and relationships, known gap): " << all - allSame - allOther << " of " << all << "\n";
}

} // namespace
