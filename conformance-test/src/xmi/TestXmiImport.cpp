// XMI import: the XMI files of the OMG pilot implementation (resources/sysml.library.xmi, the explicit variant) are read into a Workspace,
// resolved, and the model that the importer built is compared with the same XMI files through the oracle of the abstract-syntax suite
// (support/ModelDiff.h): named elements and their metaclasses, owners, memberships, aliases and the explicit relationships.
// The negative cases under testdata/xmi/negative check the ParserErrors of malformed or inconsistent files.
#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <kerml/KerML.h>
#include <sysmlv2/Parser.h>
#include <sysmlv2/Workspace.h>
#include <sysmlv2/resolution/ResolutionData.h>

#include "../support/ModelDiff.h"
#include "../support/TestHelpers.h"
#include "../support/XmiReader.h"

#ifndef SYSML_LIBRARY_XMI_DIR
#error "SYSML_LIBRARY_XMI_DIR must be defined by CMake to the resources/sysml.library.xmi path"
#endif
#ifndef XMI_NEGATIVE_DIR
#error "XMI_NEGATIVE_DIR must be defined by CMake to the conformance-test/testdata/xmi/negative path"
#endif

namespace {

using SysMLv2::Files::ErrorType;
using SysMLv2::Files::Parser;
using SysMLv2::Files::ParserError;
using SysMLv2::Files::SourceLanguage;
using SysMLv2::Files::Workspace;
namespace K = KerML::Entities;
using ElementPtr = std::shared_ptr<K::Element>;

std::vector<std::filesystem::path> xmiFiles() { return ConformanceTest::listFiles(SYSML_LIBRARY_XMI_DIR, {".sysmlx", ".kermlx"}); }

std::string describe(const std::shared_ptr<ParserError>& error) {
    static const char* kinds[] = {"SYNTAX_ERROR", "LOGICAL_ERROR", "INTERNAL_ERROR", "WARNING", "KEYWORD_MISUSE"};
    return std::string(kinds[static_cast<int>(error->errorType())]) + " " + error->getSource() + ":" + std::to_string(error->getLine()) + ": " +
           error->description();
}

std::string allErrors(const std::vector<std::shared_ptr<ParserError>>& errors) {
    std::string out;
    for (const auto& error : errors) out += "\n  " + describe(error);
    return out;
}

// The whole library as XMI in one workspace; built once.
struct Library {
    Workspace workspace;
    std::vector<std::filesystem::path> files;
    std::map<std::string, size_t> sourceOf;
    ConformanceTest::Xmi::Corpus corpus{SYSML_LIBRARY_XMI_DIR};
    ConformanceTest::ModelDiff diff{corpus};

    static std::string keyOf(const std::filesystem::path& path) { return path.lexically_normal().generic_string(); }

    Library() {
        files = xmiFiles();
        for (const auto& file : files) workspace.addFile(file.string());
        workspace.resolve();
        for (size_t i = 0; i < workspace.sourceCount(); ++i) sourceOf[keyOf(workspace.sourceName(i))] = i;
    }
};

Library& library() {
    static Library instance;
    return instance;
}

// ---------------------------------------------------------------------------------------------------------------------
// The library
// ---------------------------------------------------------------------------------------------------------------------

TEST(XmiLibrary, EveryFileIsLoadedWithoutErrorsOrUnresolvedReferences) {
    Library& lib = library();
    EXPECT_EQ(lib.files.size(), 94u);
    EXPECT_EQ(lib.workspace.sourceCount(), lib.files.size());

    std::vector<std::string> problems;
    for (const auto& error : lib.workspace.errors()) problems.push_back(describe(error));
    EXPECT_TRUE(problems.empty()) << problems.size() << " error(s)/warning(s), first: " << (problems.empty() ? "" : problems.front());

    const auto& unresolved = lib.workspace.unresolvedReferences();
    for (size_t i = 0; i < unresolved.size() && i < 10; ++i) {
        ADD_FAILURE() << "unresolved reference " << unresolved[i].name << " in " << unresolved[i].sourceName << ":" << unresolved[i].line;
    }
    EXPECT_TRUE(unresolved.empty()) << unresolved.size() << " unresolved reference(s)";

    for (size_t i = 0; i < lib.workspace.sourceCount(); ++i) {
        EXPECT_FALSE(lib.workspace.elements(i).empty()) << lib.workspace.sourceName(i);
        ASSERT_NE(lib.workspace.rootNamespace(i), nullptr) << lib.workspace.sourceName(i);
    }
}

struct FileCase {
    std::filesystem::path path;
    std::string key;
};

void PrintTo(const FileCase& c, std::ostream* os) { *os << c.key; }

std::vector<FileCase> buildCases() {
    std::vector<FileCase> cases;
    const std::filesystem::path root(SYSML_LIBRARY_XMI_DIR);
    for (const auto& path : xmiFiles()) cases.push_back({path, std::filesystem::relative(path, root).generic_string()});
    return cases;
}

class XmiFile : public ::testing::TestWithParam<FileCase> {};

// The model that the importer built from the file is the model the file describes: the same named elements with the same metaclasses,
// owners, memberships and explicit relationships as the oracle reads from the same XML.
TEST_P(XmiFile, ImportedModelMatchesTheFile) {
    Library& lib = library();
    const auto& testCase = GetParam();
    const auto source = lib.sourceOf.find(Library::keyOf(testCase.path));
    ASSERT_NE(source, lib.sourceOf.end()) << testCase.key;

    const auto result = lib.diff.compare(lib.workspace.elements(source->second), lib.corpus.file(testCase.path));
    EXPECT_GT(result.comparedElements, 0u) << testCase.key;
    EXPECT_EQ(result.total(), 0u) << testCase.key;
    if (result.total() != 0) {
        for (const auto& [category, messages] : result.differences) {
            for (size_t i = 0; i < messages.size() && i < 10; ++i) std::cout << "  [" << category << "] " << messages[i] << "\n";
        }
    }
}

INSTANTIATE_TEST_SUITE_P(XmiLibrary, XmiFile, ::testing::ValuesIn(buildCases()),
                         [](const ::testing::TestParamInfo<FileCase>& info) { return ConformanceTest::sanitizeTestName(info.param.key); });

TEST(XmiLibrary, ElementsKeepTheirIdsAndProperties) {
    Library& lib = library();
    const auto base = lib.sourceOf.at(Library::keyOf(std::filesystem::path(SYSML_LIBRARY_XMI_DIR) / "Kernel Libraries" / "Kernel Semantic Library" / "Base.kermlx"));
    const auto& elements = lib.workspace.elements(base);

    const auto package = ConformanceTest::named<K::LibraryPackage>(elements, "Base");
    ASSERT_NE(package, nullptr);
    EXPECT_EQ(package->elementId(), "cdd5d1e3-fe4b-52bd-8a01-51a53f22ba47");
    EXPECT_TRUE(package->isStandard());

    const auto anything = ConformanceTest::named<K::Classifier>(elements, "Anything");
    ASSERT_NE(anything, nullptr);
    EXPECT_EQ(anything->elementId(), "d5b4e7df-e644-5f2f-b95e-cf6f1f6c076d");
    EXPECT_TRUE(anything->isAbstract());
    EXPECT_EQ(anything->getType(), "Classifier");

    // ownership: Anything is owned by Base through an OwningMembership, which Base lists
    ASSERT_NE(anything->owningRelationship(), nullptr);
    EXPECT_EQ(anything->owningRelationship()->getType(), "OwningMembership");
    EXPECT_EQ(anything->owner(), package);
    EXPECT_EQ(anything->owningNamespace(), package);
    EXPECT_EQ(std::dynamic_pointer_cast<K::OwningMembership>(anything->owningRelationship())->ownedMemberElement(), anything);
    bool listed = false;
    for (const auto& membership : package->ownedMembership()) listed = listed || membership == anything->owningRelationship();
    EXPECT_TRUE(listed);

    // a feature of Anything, typed by Anything in the same file
    const auto self = ConformanceTest::named<K::Feature>(elements, "self");
    ASSERT_NE(self, nullptr);
    EXPECT_EQ(self->owningRelationship()->getType(), "FeatureMembership");
    ASSERT_EQ(self->ownedTyping().size(), 1u);
    EXPECT_EQ(self->ownedTyping().front()->type(), anything);
    EXPECT_EQ(self->ownedTyping().front()->typedFeature(), self);
    EXPECT_EQ(self->ownedTyping().front()->owningRelatedElement(), self);
    ASSERT_EQ(self->type().size(), 1u);
    EXPECT_EQ(self->type().front(), anything);
    EXPECT_FALSE(SysMLv2::Files::isUnresolved(self->type().front()));
    ASSERT_FALSE(self->ownedSubsetting().empty());
    EXPECT_NE(self->ownedSubsetting().front()->subsettedFeature(), nullptr);

    // ids are the ids of the file, in the elements and in the workspace's index
    const auto* oracleFile = &lib.corpus.file(std::filesystem::path(SYSML_LIBRARY_XMI_DIR) / "Kernel Libraries" / "Kernel Semantic Library" / "Base.kermlx");
    std::set<std::string> ids;
    for (const auto& element : elements) ids.insert(element->elementId());
    for (const auto& oracleElement : oracleFile->elements) {
        if (!oracleElement.id.empty()) EXPECT_EQ(ids.count(oracleElement.id), 1u) << oracleElement.id;
    }
    EXPECT_EQ(elements.size(), oracleFile->elements.size());
}

TEST(XmiLibrary, ReferencesBetweenFilesAreResolvedToTheElementsOfTheOtherFiles) {
    Library& lib = library();
    std::unordered_map<const K::Element*, size_t> sourceOfElement;
    for (size_t i = 0; i < lib.workspace.sourceCount(); ++i) {
        for (const auto& element : lib.workspace.elements(i)) sourceOfElement[element.get()] = i;
    }
    size_t crossFile = 0;
    size_t unresolved = 0;
    for (size_t i = 0; i < lib.workspace.sourceCount(); ++i) {
        for (const auto& element : lib.workspace.elements(i)) {
            const auto specialization = std::dynamic_pointer_cast<K::Specialization>(element);
            if (!specialization) continue;
            const auto general = specialization->general();
            ASSERT_NE(general, nullptr);
            if (SysMLv2::Files::isUnresolved(general)) {
                ++unresolved;
                continue;
            }
            const auto where = sourceOfElement.find(general.get());
            ASSERT_NE(where, sourceOfElement.end()) << "the general type of a specialization in " << lib.workspace.sourceName(i) << " is no element of the workspace";
            if (where->second != i) ++crossFile;
        }
    }
    EXPECT_EQ(unresolved, 0u);
    EXPECT_GT(crossFile, 1000u);
}

// A textual model is resolved against the library that was loaded from XMI; the references of the library are not resolved again.
TEST(XmiLibrary, TextualModelResolvesAgainstTheXmiLibrary) {
    Library& lib = library();
    Workspace workspace;
    for (const auto& file : lib.files) workspace.addFile(file.string());
    const size_t model = workspace.addText(
        "package Demo { private import ScalarValues::*; attribute count : Integer; part def Engine { attribute power : Real; } "
        "attribute greeting : String; }",
        "demo.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();

    EXPECT_TRUE(workspace.errors(model).empty());
    EXPECT_TRUE(workspace.unresolvedReferences().empty());
    const auto count = ConformanceTest::named<K::Feature>(workspace.elements(model), "count");
    ASSERT_NE(count, nullptr);
    ASSERT_EQ(count->type().size(), 1u);
    const auto integer = count->type().front();
    ASSERT_NE(integer, nullptr);
    EXPECT_FALSE(SysMLv2::Files::isUnresolved(integer));
    EXPECT_EQ(integer->declaredName().value_or(""), "Integer");
    ASSERT_NE(workspace.find("ScalarValues::Integer"), nullptr);
    EXPECT_EQ(integer, workspace.find("ScalarValues::Integer"));

    // the element is the one of the XMI source
    bool fromXmi = false;
    for (size_t i = 0; i < workspace.sourceCount() && !fromXmi; ++i) {
        if (i == model) continue;
        for (const auto& element : workspace.elements(i)) {
            if (element == integer) {
                fromXmi = true;
                break;
            }
        }
    }
    EXPECT_TRUE(fromXmi);

    // qualified names are found through the owners of the XMI model
    EXPECT_NE(workspace.find("ScalarValues::Real"), nullptr);
    EXPECT_NE(workspace.find("Base::Anything"), nullptr);
}

TEST(XmiLibrary, ReplacingATextualSourceDoesNotDisturbTheXmiSources) {
    Library& lib = library();
    Workspace workspace;
    for (const auto& file : lib.files) workspace.addFile(file.string());
    const size_t model = workspace.addText("package A { attribute x : ScalarValues::Integer; }", "a.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    EXPECT_TRUE(workspace.unresolvedReferences().empty());
    workspace.replaceSource(model, "package A { attribute y : ScalarValues::Real; }");
    workspace.resolve();
    EXPECT_TRUE(workspace.unresolvedReferences().empty());
    EXPECT_NE(ConformanceTest::named<K::Feature>(workspace.elements(model), "y"), nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------
// Parser and Workspace entry points
// ---------------------------------------------------------------------------------------------------------------------

TEST(XmiParser, ParseFileDispatchesByTheExtension) {
    const std::filesystem::path attributes = std::filesystem::path(SYSML_LIBRARY_XMI_DIR) / "Systems Library" / "Attributes.sysmlx";
    ASSERT_TRUE(std::filesystem::exists(attributes));
    auto [elements, errors] = Parser::parseFile(attributes.string());
    EXPECT_FALSE(elements.empty());
    EXPECT_TRUE(errors.empty());
    EXPECT_EQ(elements.front()->getType(), "Namespace");
    EXPECT_NE(ConformanceTest::named<K::LibraryPackage>(elements, "Attributes"), nullptr);

    // the references to other files cannot be resolved by a single file: warnings if asked for
    auto [again, warnings] = Parser::parseFile(attributes.string(), true);
    EXPECT_FALSE(warnings.empty());
    for (const auto& warning : warnings) {
        EXPECT_EQ(warning->errorType(), ErrorType::WARNING);
        EXPECT_EQ(warning->getSource(), attributes.string());
        EXPECT_GT(warning->getLine(), 0);
    }
}

TEST(XmiParser, ParseXmiReadsAText) {
    const std::string text = ConformanceTest::readFile(std::filesystem::path(SYSML_LIBRARY_XMI_DIR) / "Kernel Libraries" / "Kernel Semantic Library" / "Base.kermlx");
    auto [elements, errors] = Parser::parseXmi(text, "Base.kermlx");
    EXPECT_FALSE(elements.empty());
    EXPECT_TRUE(errors.empty());
    EXPECT_NE(ConformanceTest::named<K::Classifier>(elements, "Anything"), nullptr);
    // Base refers to ScalarValues, which is another file: a single file cannot resolve that
    auto [warned, warnings] = Parser::parseXmi(text, "Base.kermlx", true);
    ASSERT_FALSE(warnings.empty());
    for (const auto& warning : warnings) {
        EXPECT_EQ(warning->errorType(), ErrorType::WARNING);
        EXPECT_EQ(warning->getSource(), "Base.kermlx");
        EXPECT_NE(warning->description().find("ScalarValues.kermlx#"), std::string::npos) << describe(warning);
    }
}

TEST(XmiParser, AutoRecognizesTheXmiExtensions) {
    const std::string text = ConformanceTest::readFile(std::filesystem::path(SYSML_LIBRARY_XMI_DIR) / "Kernel Libraries" / "Kernel Semantic Library" / "Base.kermlx");
    for (const char* name : {"a.kermlx", "a.sysmlx", "a.xmi"}) {
        Workspace workspace;
        const size_t source = workspace.addText(text, name);
        workspace.resolve();
        EXPECT_TRUE(workspace.errors(source).empty()) << name;
        EXPECT_NE(ConformanceTest::named<K::Classifier>(workspace.elements(source), "Anything"), nullptr) << name;
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// Negative cases
// ---------------------------------------------------------------------------------------------------------------------

std::filesystem::path negative(const char* name) { return std::filesystem::path(XMI_NEGATIVE_DIR) / name; }

// The 1-based number of the first line of the file that contains @p marker.
int lineOf(const std::filesystem::path& path, const std::string& marker) {
    std::istringstream in(ConformanceTest::readFile(path));
    std::string line;
    int number = 0;
    while (std::getline(in, line)) {
        ++number;
        if (line.find(marker) != std::string::npos) return number;
    }
    return -1;
}

std::shared_ptr<ParserError> findError(const std::vector<std::shared_ptr<ParserError>>& errors, ErrorType type, const std::string& text) {
    for (const auto& error : errors) {
        if (error->errorType() == type && error->description().find(text) != std::string::npos) return error;
    }
    return nullptr;
}

TEST(XmiNegative, MalformedXmlIsASyntaxErrorWithALine) {
    const auto path = negative("malformed.sysmlx");
    auto [elements, errors] = Parser::parseFile(path.string());
    const auto error = findError(errors, ErrorType::SYNTAX_ERROR, "malformed XML");
    ASSERT_NE(error, nullptr) << allErrors(errors);
    EXPECT_EQ(error->getSource(), path.string());
    EXPECT_GT(error->getLine(), 0);
    EXPECT_TRUE(elements.empty());
}

TEST(XmiNegative, UnknownMetaclassIsReportedAtItsElement) {
    const auto path = negative("unknown_type.sysmlx");
    auto [elements, errors] = Parser::parseFile(path.string());
    const auto error = findError(errors, ErrorType::LOGICAL_ERROR, "unknown metaclass 'Bogus'");
    ASSERT_NE(error, nullptr) << allErrors(errors);
    EXPECT_EQ(error->getSource(), path.string());
    EXPECT_EQ(error->getLine(), lineOf(path, "sysml:Bogus"));
    // the rest of the file is still read
    EXPECT_NE(ConformanceTest::named<K::LibraryPackage>(elements, "Neg"), nullptr);
}

TEST(XmiNegative, AbstractMetaclassCannotBeInstantiated) {
    const auto path = negative("abstract_type.sysmlx");
    auto [elements, errors] = Parser::parseFile(path.string());
    const auto error = findError(errors, ErrorType::LOGICAL_ERROR, "'Relationship' is abstract");
    ASSERT_NE(error, nullptr) << allErrors(errors);
    EXPECT_EQ(error->getLine(), lineOf(path, "sysml:Relationship"));
}

TEST(XmiNegative, InvalidEnumerationLiteral) {
    const auto path = negative("bad_enum.sysmlx");
    auto [elements, errors] = Parser::parseFile(path.string());
    const auto error = findError(errors, ErrorType::SYNTAX_ERROR, "invalid value 'hidden' for property 'visibility'");
    ASSERT_NE(error, nullptr) << allErrors(errors);
    EXPECT_NE(error->description().find("VisibilityKind"), std::string::npos);
    EXPECT_EQ(error->getLine(), lineOf(path, "visibility=\"hidden\""));
}

TEST(XmiNegative, InvalidBoolean) {
    const auto path = negative("bad_boolean.sysmlx");
    auto [elements, errors] = Parser::parseFile(path.string());
    const auto error = findError(errors, ErrorType::SYNTAX_ERROR, "invalid value 'maybe' for property 'isAbstract'");
    ASSERT_NE(error, nullptr) << allErrors(errors);
    EXPECT_EQ(error->getLine(), lineOf(path, "isAbstract=\"maybe\""));
}

TEST(XmiNegative, UnknownAttributeIsAWarning) {
    const auto path = negative("unknown_attribute.sysmlx");
    auto [elements, errors] = Parser::parseFile(path.string());
    const auto warning = findError(errors, ErrorType::WARNING, "unknown attribute 'frobnicate'");
    ASSERT_NE(warning, nullptr) << allErrors(errors);
    EXPECT_EQ(warning->getLine(), lineOf(path, "frobnicate"));
    for (const auto& error : errors) EXPECT_EQ(error->errorType(), ErrorType::WARNING) << describe(error);
    const auto classifier = ConformanceTest::named<K::Classifier>(elements, "A");
    EXPECT_NE(classifier, nullptr);
}

TEST(XmiNegative, DanglingHrefKeepsAPlaceholderAndWarns) {
    const auto path = negative("dangling_href.sysmlx");
    Workspace workspace;
    const size_t source = workspace.addFile(path.string());
    workspace.resolve();
    EXPECT_TRUE(workspace.errors(source).empty()) << allErrors(workspace.errors(source));
    ASSERT_EQ(workspace.unresolvedReferences().size(), 1u);
    const auto& info = workspace.unresolvedReferences().front();
    EXPECT_NE(info.name.find("Missing Library/Missing.kermlx#00000000-0000-4000-8000-0000000009ff"), std::string::npos) << info.name;
    EXPECT_EQ(info.line, lineOf(path, "sysml:FeatureTyping"));
    EXPECT_EQ(info.sourceName, path.string());

    const auto warnings = workspace.unresolvedAsWarnings(source);
    ASSERT_EQ(warnings.size(), 1u);
    EXPECT_EQ(warnings.front()->errorType(), ErrorType::WARNING);
    EXPECT_EQ(warnings.front()->getSource(), path.string());
    EXPECT_NE(warnings.front()->description().find("Missing.kermlx"), std::string::npos);

    const auto feature = ConformanceTest::named<K::Feature>(workspace.elements(source), "f");
    ASSERT_NE(feature, nullptr);
    ASSERT_EQ(feature->ownedTyping().size(), 1u);
    EXPECT_TRUE(SysMLv2::Files::isUnresolved(feature->ownedTyping().front()->type()));
    EXPECT_EQ(feature->ownedTyping().front()->typedFeature(), feature);

    // the same through the Parser
    auto [elements, errors] = Parser::parseFile(path.string(), true);
    ASSERT_EQ(errors.size(), 1u) << allErrors(errors);
    EXPECT_EQ(errors.front()->errorType(), ErrorType::WARNING);
}

TEST(XmiNegative, ReferenceToAnIdThatNoElementHas) {
    const auto path = negative("dangling_id.sysmlx");
    Workspace workspace;
    const size_t source = workspace.addFile(path.string());
    workspace.resolve();
    ASSERT_EQ(workspace.unresolvedReferences().size(), 1u);
    EXPECT_EQ(workspace.unresolvedReferences().front().name, "00000000-0000-4000-8000-0000000009fe");
    const auto warnings = workspace.unresolvedAsWarnings(source);
    ASSERT_EQ(warnings.size(), 1u);
    EXPECT_EQ(warnings.front()->getLine(), lineOf(path, "sysml:FeatureTyping"));
}

TEST(XmiNegative, ReferenceToAnElementOfTheWrongMetaclass) {
    const auto path = negative("wrong_target.sysmlx");
    Workspace workspace;
    const size_t source = workspace.addFile(path.string());
    workspace.resolve();
    // the id is the one of a membership, but a FeatureTyping.type has to be a Type
    const auto error = findError(workspace.errors(source), ErrorType::LOGICAL_ERROR, "cannot set property 'type'");
    ASSERT_NE(error, nullptr) << allErrors(workspace.errors(source));
    EXPECT_NE(error->description().find("not a Type"), std::string::npos) << error->description();
    EXPECT_EQ(error->getLine(), lineOf(path, "sysml:FeatureTyping"));
    EXPECT_TRUE(workspace.unresolvedReferences().empty());
}

// A package with a classifier A and a feature f whose FeatureTyping points to @p href (the href attribute of the type tag).
std::string typingXmi(const std::string& href) {
    return
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<sysml:Package xmi:version=\"2.0\" xmlns:xmi=\"http://www.omg.org/XMI\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
        "xmlns:sysml=\"https://www.omg.org/spec/SysML/20250201\" xmi:id=\"00000000-0000-4000-8000-000000000001\" "
        "elementId=\"00000000-0000-4000-8000-000000000001\" declaredName=\"P\">\n"
        "  <ownedRelationship xsi:type=\"sysml:OwningMembership\" xmi:id=\"00000000-0000-4000-8000-000000000002\" elementId=\"00000000-0000-4000-8000-000000000002\">\n"
        "    <ownedRelatedElement xsi:type=\"sysml:Classifier\" xmi:id=\"00000000-0000-4000-8000-000000000201\" elementId=\"00000000-0000-4000-8000-000000000201\" declaredName=\"A\"/>\n"
        "  </ownedRelationship>\n"
        "  <ownedRelationship xsi:type=\"sysml:OwningMembership\" xmi:id=\"00000000-0000-4000-8000-000000000003\" elementId=\"00000000-0000-4000-8000-000000000003\">\n"
        "    <ownedRelatedElement xsi:type=\"sysml:Feature\" xmi:id=\"00000000-0000-4000-8000-000000000202\" elementId=\"00000000-0000-4000-8000-000000000202\" declaredName=\"f\">\n"
        "      <ownedRelationship xsi:type=\"sysml:FeatureTyping\" xmi:id=\"00000000-0000-4000-8000-000000000301\" elementId=\"00000000-0000-4000-8000-000000000301\" "
        "typedFeature=\"00000000-0000-4000-8000-000000000202\">\n"
        "        <type href=\"" + href + "\"/>\n"
        "      </ownedRelationship>\n"
        "    </ownedRelatedElement>\n"
        "  </ownedRelationship>\n"
        "</sysml:Package>\n";
}

// The file part of an href is for display only: bytes that are no UTF-8 (a percent escape of Latin-1, a raw byte, a lone surrogate) never throw,
// and the target is found by its id.
TEST(XmiNegative, HrefWithInvalidUtf8InTheFilePartDoesNotThrow) {
    const std::string target = "00000000-0000-4000-8000-000000000201";
    const std::vector<std::string> files = {"x%FF.sysmlx", "Gr%F6%DFen.sysmlx", std::string("raw\xFF\xFE.sysmlx"), "%C3.sysmlx", "%ED%A0%80.sysmlx",
                                            "file:///d/%FF/f.sysmlx", "../%80%80/x.sysmlx"};
    for (const auto& file : files) {
        SCOPED_TRACE(file);
        Workspace workspace;
        size_t source = 0;
        ASSERT_NO_THROW(source = workspace.addText(typingXmi(file + "#" + target), "m.sysmlx", SourceLanguage::Xmi, 0));
        ASSERT_NO_THROW(workspace.resolve());
        EXPECT_TRUE(workspace.unresolvedReferences().empty()) << allErrors(workspace.errors(source));
        const auto f = ConformanceTest::named<K::Feature>(workspace.elements(source), "f");
        ASSERT_NE(f, nullptr);
        ASSERT_EQ(f->ownedTyping().size(), 1u);
        const auto type = f->ownedTyping().front()->type();
        ASSERT_NE(type, nullptr);
        EXPECT_EQ(type->declaredName().value_or(""), "A");
        EXPECT_FALSE(SysMLv2::Files::isUnresolved(type));
    }
}

TEST(XmiNegative, HrefWithInvalidUtf8ToAnUnknownIdIsAnUnresolvedReference) {
    for (const std::string file : {std::string("x%FF.sysmlx"), std::string("raw\xFF.sysmlx")}) {
        SCOPED_TRACE(file);
        Workspace workspace;
        size_t source = 0;
        ASSERT_NO_THROW(source = workspace.addText(typingXmi(file + "#00000000-0000-4000-8000-0000000009ff"), "m.sysmlx", SourceLanguage::Xmi, 0));
        ASSERT_NO_THROW(workspace.resolve());
        EXPECT_TRUE(workspace.errors(source).empty()) << allErrors(workspace.errors(source));
        ASSERT_EQ(workspace.unresolvedReferences().size(), 1u);
        EXPECT_NE(workspace.unresolvedReferences().front().name.find("00000000-0000-4000-8000-0000000009ff"), std::string::npos);
        EXPECT_EQ(workspace.unresolvedAsWarnings(source).size(), 1u);
    }
}

// A well-formed UTF-8 file part is still normalised relative to the directory of the file that holds the href.
TEST(XmiNegative, HrefWithUtf8InTheFilePartIsShownNormalised) {
    Workspace workspace;
    const size_t source = workspace.addText(typingXmi("sub/../Gr%C3%B6%C3%9Fen.sysmlx#00000000-0000-4000-8000-0000000009ff"), "dir/m.sysmlx", SourceLanguage::Xmi, 0);
    workspace.resolve();
    ASSERT_EQ(workspace.unresolvedReferences().size(), 1u) << allErrors(workspace.errors(source));
    const std::string& name = workspace.unresolvedReferences().front().name;
    EXPECT_NE(name.find("dir/Gr\xC3\xB6\xC3\x9F" "en.sysmlx#"), std::string::npos) << name;
}

// The text shown for an href whose file part is no UTF-8 (the fallback of the reader joins and normalises it as plain text): relative to the
// directory of the file that holds the href, with "/" as separator, "." and ".." resolved, absolute forms kept.
TEST(XmiNegative, DisplayTextOfAnHrefWithInvalidUtf8InTheFilePart) {
    struct Case {
        std::string name;
        std::string href;
        std::string expected;
    };
    const std::vector<Case> cases = {
        {"dir/m.sysmlx", "x%FF.sysmlx", "dir/x\xFF.sysmlx"},
        {"dir/m.sysmlx", "sub/../x%FF.sysmlx", "dir/x\xFF.sysmlx"},
        {"dir/m.sysmlx", "../%FF/x.sysmlx", "\xFF/x.sysmlx"},
        {"dir/m.sysmlx", "../../x%FF.sysmlx", "../x\xFF.sysmlx"},
        {"m.sysmlx", "a/%FF.sysmlx", "a/\xFF.sysmlx"},
        {"dir\\m.sysmlx", "x%FF.sysmlx", "dir/x\xFF.sysmlx"},
        {"dir/m.sysmlx", "file:///d/%FF/f.sysmlx", "/d/\xFF/f.sysmlx"},
        {"dir/m.sysmlx", "file:///D:/x%FF/f.sysmlx", "D:/x\xFF/f.sysmlx"},
    };
    for (const auto& c : cases) {
        SCOPED_TRACE(c.name + " + " + c.href);
        Workspace workspace;
        const size_t source = workspace.addText(typingXmi(c.href + "#00000000-0000-4000-8000-0000000009ff"), c.name, SourceLanguage::Xmi, 0);
        workspace.resolve();
        ASSERT_EQ(workspace.unresolvedReferences().size(), 1u) << allErrors(workspace.errors(source));
        EXPECT_EQ(workspace.unresolvedReferences().front().name, c.expected + "#00000000-0000-4000-8000-0000000009ff");
    }
}

TEST(XmiNegative, MissingFileIsAnErrorOfTheSource) {
    Workspace workspace;
    const size_t source = workspace.addFile((std::filesystem::path(XMI_NEGATIVE_DIR) / "does_not_exist.sysmlx").string());
    ASSERT_EQ(workspace.errors(source).size(), 1u);
    EXPECT_EQ(workspace.errors(source).front()->errorType(), ErrorType::INTERNAL_ERROR);
    EXPECT_TRUE(workspace.elements(source).empty());
}

}  // namespace
