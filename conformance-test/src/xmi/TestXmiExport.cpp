// XMI export: the writer (SysMLv2::Files::XmiWriter, Workspace::writeXmi / exportXmi) is checked by round trips.
//  - Library: the XMI files of the pilot implementation (resources/sysml.library.xmi) are loaded into a Workspace, exported to a directory, the
//    exported files are loaded into a fresh Workspace and compared with the same oracle as the import (support/ModelDiff.h); the ids of the
//    elements must be the ones of the original files.
//  - Text: SysML models of testdata/syntax/sysml/valid are resolved against the XMI library, written as XMI, read again, and the two models
//    (element by element: metaclass, names, owner, properties, relationship ends) must be the same.
//  - Determinism of the ids, and the cases in which a reference cannot be written (unresolved name, element in no file).
//  - XmiExportReview: ids across files, hrefs into other files, paths, texts XML cannot hold, failures while writing.
#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <cctype>
#include <clocale>
#include <cmath>
#include <filesystem>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

#include <kerml/KerML.h>
#include <sysml/SysML.h>
#include <sysmlv2/Workspace.h>
#include <sysmlv2/resolution/ResolutionData.h>
#include <sysmlv2/xmi/XmiWriter.h>

#include "../support/ModelDiff.h"
#include "../support/TestHelpers.h"
#include "../support/XmiReader.h"

#ifndef SYSML_LIBRARY_XMI_DIR
#error "SYSML_LIBRARY_XMI_DIR must be defined by CMake to the resources/sysml.library.xmi path"
#endif
#ifndef SYSML_VALID_DIR
#error "SYSML_VALID_DIR must be defined by CMake to the conformance-test/testdata/syntax/sysml/valid path"
#endif

namespace {

using SysMLv2::Files::ErrorType;
using SysMLv2::Files::ParserError;
using SysMLv2::Files::SourceLanguage;
using SysMLv2::Files::Workspace;
using SysMLv2::Files::XmiWriteOptions;
using SysMLv2::Files::XmiWriter;
namespace K = KerML::Entities;
namespace fs = std::filesystem;
using ElementPtr = std::shared_ptr<K::Element>;
using Errors = std::vector<std::shared_ptr<ParserError>>;

std::string describe(const std::shared_ptr<ParserError>& error) {
    static const char* kinds[] = {"SYNTAX_ERROR", "LOGICAL_ERROR", "INTERNAL_ERROR", "WARNING", "KEYWORD_MISUSE"};
    return std::string(kinds[static_cast<int>(error->errorType())]) + " " + error->getSource() + ": " + error->description();
}

std::string allErrors(const Errors& errors, size_t limit = 10) {
    std::string out;
    for (size_t i = 0; i < errors.size() && i < limit; ++i) out += "\n  " + describe(errors[i]);
    if (errors.size() > limit) out += "\n  ... " + std::to_string(errors.size() - limit) + " more";
    return out;
}

unsigned long processId() {
#ifdef _WIN32
    return static_cast<unsigned long>(_getpid());
#else
    return static_cast<unsigned long>(getpid());
#endif
}

std::string hex(unsigned long value) {
    std::ostringstream out;
    out << std::hex << value;
    return out.str();
}

// True if every error is the WARNING that a relative name was compared with an absolute root (or the other way round); with @p count, if
// there are exactly that many.
bool onlyWorkingDirectoryWarnings(const Errors& errors, std::optional<size_t> count = std::nullopt) {
    if (count && errors.size() != *count) return false;
    return std::all_of(errors.begin(), errors.end(), [](const std::shared_ptr<ParserError>& error) {
        return error->errorType() == ErrorType::WARNING && error->description().find("working directory") != std::string::npos;
    });
}

// A directory below the temporary directory that is removed at the end; the names are short (the library has deep paths, MAX_PATH). The name has
// the process id and a random part, and the directory is created exclusively (a name that exists is never reused, nothing is removed first), so
// that processes that run at the same time (ctest -j) cannot meet.
class TempDir {
public:
    TempDir() {
        static std::atomic<int> counter{0};
        static std::random_device random;
        std::error_code ec;
        for (int attempt = 0; attempt < 100; ++attempt) {
            const fs::path candidate = fs::temp_directory_path() / ("xe" + hex(processId()) + "_" + std::to_string(counter++) + "_" + hex(random() & 0xFFFFF));
            // (false: it exists already, or cannot be created; an existing one belongs to somebody else)
            if (fs::create_directory(candidate, ec) && !ec) {
                Path = candidate;
                return;
            }
        }
        throw std::runtime_error("cannot create a temporary directory below " + fs::temp_directory_path().string());
    }
    ~TempDir() {
        std::error_code ec;
        fs::remove_all(Path, ec);
    }
    TempDir(const TempDir&) = delete;
    TempDir& operator=(const TempDir&) = delete;
    const fs::path& path() const { return Path; }

private:
    fs::path Path;
};

std::vector<fs::path> xmiFiles() { return ConformanceTest::listFiles(SYSML_LIBRARY_XMI_DIR, {".sysmlx", ".kermlx"}); }

std::string keyOf(const fs::path& path) { return path.lexically_normal().generic_string(); }

std::set<std::string> idsOf(const Workspace& workspace, size_t source) {
    std::set<std::string> ids;
    for (const auto& element : workspace.elements(source)) ids.insert(element->elementId());
    return ids;
}

// What differs between the ids of two sources (a few of each side, with the metaclass), for the message of a failed test.
std::string idDifference(const Workspace& a, size_t sourceA, const Workspace& b, size_t sourceB) {
    std::map<std::string, std::string> inA;
    std::map<std::string, std::string> inB;
    for (const auto& element : a.elements(sourceA)) inA[element->elementId()] = element->getType();
    for (const auto& element : b.elements(sourceB)) inB[element->elementId()] = element->getType();
    std::string out;
    size_t shown = 0;
    for (const auto& [id, type] : inA) {
        if (inB.count(id) == 0 && ++shown <= 5) out += "\n  only in the original: " + type + " " + id;
    }
    shown = 0;
    for (const auto& [id, type] : inB) {
        if (inA.count(id) == 0 && ++shown <= 5) out += "\n  only in the export: " + type + " " + id;
    }
    return out;
}

// ---------------------------------------------------------------------------------------------------------------------
// The library
// ---------------------------------------------------------------------------------------------------------------------

// The whole library, exported once and read again.
struct RoundTrip {
    TempDir directory;
    Workspace original;
    Workspace exported;
    Errors exportErrors;
    std::vector<fs::path> files;
    std::map<std::string, size_t> exportedSourceOf;   // relative path -> source of "exported"
    ConformanceTest::Xmi::Corpus corpus{SYSML_LIBRARY_XMI_DIR};
    ConformanceTest::ModelDiff diff{corpus};

    RoundTrip() {
        files = xmiFiles();
        for (const auto& file : files) original.addFile(file.string());
        original.resolve();
        XmiWriteOptions options;
        options.exportRoot = SYSML_LIBRARY_XMI_DIR;   // (the files keep their layout below the root of the library)
        exportErrors = original.exportXmi(directory.path().string(), options);
        for (const auto& file : files) {
            const fs::path relative = fs::relative(file, SYSML_LIBRARY_XMI_DIR);
            const size_t source = exported.addFile((directory.path() / relative).string());
            exportedSourceOf[relative.generic_string()] = source;
        }
        exported.resolve();
    }
};

RoundTrip& roundTrip() {
    static RoundTrip instance;
    return instance;
}

TEST(XmiExportLibrary, ExportWritesEveryFileWithoutErrors) {
    RoundTrip& rt = roundTrip();
    EXPECT_EQ(rt.files.size(), 94u);
    EXPECT_TRUE(rt.exportErrors.empty()) << rt.exportErrors.size() << " error(s)/warning(s)" << allErrors(rt.exportErrors);
    for (const auto& file : rt.files) {
        const fs::path written = rt.directory.path() / fs::relative(file, SYSML_LIBRARY_XMI_DIR);
        EXPECT_TRUE(fs::exists(written)) << written;
    }
}

TEST(XmiExportLibrary, ExportedFilesAreReadWithoutErrorsOrUnresolvedReferences) {
    RoundTrip& rt = roundTrip();
    ASSERT_EQ(rt.exported.sourceCount(), rt.files.size());
    const Errors errors = rt.exported.errors();
    EXPECT_TRUE(errors.empty()) << errors.size() << " error(s)/warning(s)" << allErrors(errors);
    const auto& unresolved = rt.exported.unresolvedReferences();
    for (size_t i = 0; i < unresolved.size() && i < 10; ++i) {
        ADD_FAILURE() << "unresolved reference " << unresolved[i].name << " in " << unresolved[i].sourceName << ":" << unresolved[i].line;
    }
    EXPECT_TRUE(unresolved.empty()) << unresolved.size() << " unresolved href(s)";
}

struct FileCase {
    fs::path path;
    std::string key;
};

void PrintTo(const FileCase& c, std::ostream* os) { *os << c.key; }

std::vector<FileCase> buildCases() {
    std::vector<FileCase> cases;
    for (const auto& path : xmiFiles()) cases.push_back({path, fs::relative(path, SYSML_LIBRARY_XMI_DIR).generic_string()});
    return cases;
}

class XmiExportFile : public ::testing::TestWithParam<FileCase> {};

// The exported file describes the same model as the original: it matches the oracle of the original file, and its elements have the ids of the
// original ones.
TEST_P(XmiExportFile, ExportedModelMatchesTheOriginalFile) {
    RoundTrip& rt = roundTrip();
    const auto& testCase = GetParam();
    const auto source = rt.exportedSourceOf.find(testCase.key);
    ASSERT_NE(source, rt.exportedSourceOf.end()) << testCase.key;

    const auto result = rt.diff.compare(rt.exported.elements(source->second), rt.corpus.file(testCase.path));
    EXPECT_GT(result.comparedElements, 0u) << testCase.key;
    EXPECT_EQ(result.total(), 0u) << testCase.key;
    if (result.total() != 0) {
        for (const auto& [category, messages] : result.differences) {
            for (size_t i = 0; i < messages.size() && i < 10; ++i) std::cout << "  [" << category << "] " << messages[i] << "\n";
        }
    }

    const size_t originalSource = rt.original.findSource(testCase.path.string());
    ASSERT_LT(originalSource, rt.original.sourceCount()) << testCase.key;
    EXPECT_EQ(rt.original.elements(originalSource).size(), rt.exported.elements(source->second).size()) << testCase.key;
    EXPECT_TRUE(idsOf(rt.original, originalSource) == idsOf(rt.exported, source->second))
        << "the ids differ in " << testCase.key << idDifference(rt.original, originalSource, rt.exported, source->second);
}

INSTANTIATE_TEST_SUITE_P(XmiExportLibrary, XmiExportFile, ::testing::ValuesIn(buildCases()),
                         [](const ::testing::TestParamInfo<FileCase>& info) { return ConformanceTest::sanitizeTestName(info.param.key); });

// ---------------------------------------------------------------------------------------------------------------------
// Determinism
// ---------------------------------------------------------------------------------------------------------------------

TEST(XmiExportDeterminism, ElementIdExportOfTheSameWorkspaceIsByteIdentical) {
    RoundTrip& rt = roundTrip();
    const fs::path file = fs::path(SYSML_LIBRARY_XMI_DIR) / "Systems Library" / "Parts.sysmlx";
    const size_t source = rt.original.findSource(file.string());
    ASSERT_LT(source, rt.original.sourceCount());
    TempDir directory;
    EXPECT_TRUE(rt.original.writeXmi(source, (directory.path() / "a.sysmlx").string()).empty());
    EXPECT_TRUE(rt.original.writeXmi(source, (directory.path() / "b.sysmlx").string()).empty());
    const std::string a = ConformanceTest::readFile(directory.path() / "a.sysmlx");
    EXPECT_FALSE(a.empty());
    EXPECT_EQ(a, ConformanceTest::readFile(directory.path() / "b.sysmlx"));
}

// Elements that came from an XMI file keep their ids in every mode, so for a library the name based export is the element id export.
TEST(XmiExportDeterminism, ImportedIdsAreKeptByTheNameBasedMode) {
    RoundTrip& rt = roundTrip();
    const fs::path file = fs::path(SYSML_LIBRARY_XMI_DIR) / "Systems Library" / "Parts.sysmlx";
    const size_t source = rt.original.findSource(file.string());
    ASSERT_LT(source, rt.original.sourceCount());
    TempDir directory;
    XmiWriteOptions named;
    named.ids = XmiWriteOptions::IdMode::NameBased;
    EXPECT_TRUE(rt.original.writeXmi(source, (directory.path() / "a.sysmlx").string()).empty());
    EXPECT_TRUE(rt.original.writeXmi(source, (directory.path() / "b.sysmlx").string(), named).empty());
    EXPECT_EQ(ConformanceTest::readFile(directory.path() / "a.sysmlx"), ConformanceTest::readFile(directory.path() / "b.sysmlx"));
}

// ---------------------------------------------------------------------------------------------------------------------
// Text models
// ---------------------------------------------------------------------------------------------------------------------

std::unordered_set<const K::Element*> listedBy(const Workspace& workspace, size_t source) {
    std::unordered_set<const K::Element*> listed;
    for (const auto& element : workspace.elements(source)) listed.insert(element.get());
    listed.insert(workspace.rootNamespace(source).get());
    return listed;
}

// What a model is, element by element (in the order of the ownership tree): metaclass, id, names, owner, the stored properties of the common
// metaclasses and the ends of the relationships (as ids).
void describeTree(const ElementPtr& root, const std::unordered_set<const K::Element*>& listed, std::vector<std::string>& out) {
    std::unordered_set<const K::Element*> seen;
    // (an unresolved reference is not written: it reads back as none)
    const auto id = [](const ElementPtr& element) {
        const bool detached = element && !element->owner() && !element->owningRelationship();   // (the stub of an unresolved import)
        return element && !detached && !SysMLv2::Files::isUnresolved(element) ? element->elementId() : std::string("-");
    };
    const std::function<void(const ElementPtr&, const std::string&)> visit = [&](const ElementPtr& element, const std::string& position) {
        // (the classes of the model create structure of their own, such as the end features of a connector, which a source does not list)
        if (!element || listed.count(element.get()) == 0 || !seen.insert(element.get()).second) return;
        std::ostringstream line;
        // (the writer writes the abstract InstantiationExpression that the parsers create for a type reference as an InvocationExpression)
        line << position << " " << (element->getType() == "InstantiationExpression" ? std::string("InvocationExpression") : element->getType()) << " " << element->elementId() << " name=" << element->declaredName().value_or("<none>")
             << " short=" << element->declaredShortName().value_or("<none>") << " owner=" << id(element->owner());
        if (const auto type = std::dynamic_pointer_cast<K::Type>(element)) line << " abstract=" << type->isAbstract() << " sufficient=" << type->isSufficient();
        if (const auto feature = std::dynamic_pointer_cast<K::Feature>(element)) {
            line << " unique=" << feature->isUnique() << " ordered=" << feature->isOrdered() << " composite=" << feature->isComposite()
                 << " end=" << feature->isEnd() << " derived=" << feature->isDerived() << " portion=" << feature->isPortion()
                 << " variable=" << feature->isVariable() << " constant=" << feature->isConstant();
            line << " direction=" << (feature->direction() ? std::to_string(static_cast<int>(*feature->direction())) : std::string("-"));
        }
        if (const auto membership = std::dynamic_pointer_cast<K::Membership>(element)) {
            line << " visibility=" << static_cast<int>(membership->visibility()) << " member=" << id(membership->memberElement())
                 << " memberName=" << membership->memberName().value_or("<none>");
        }
        if (const auto import = std::dynamic_pointer_cast<K::Import>(element)) {
            line << " visibility=" << static_cast<int>(import->visibility()) << " recursive=" << import->isRecursive() << " all=" << import->isImportAll();
        }
        if (const auto membershipImport = std::dynamic_pointer_cast<K::MembershipImport>(element)) {
            const auto imported = membershipImport->importedMembership();
            line << " imported=" << id(imported);
        }
        if (const auto namespaceImport = std::dynamic_pointer_cast<K::NamespaceImport>(element)) line << " imported=" << id(namespaceImport->importedNamespace());
        if (const auto specialization = std::dynamic_pointer_cast<K::Specialization>(element)) {
            line << " general=" << id(specialization->general()) << " specific=" << id(specialization->specific());
        }
        if (const auto typing = std::dynamic_pointer_cast<K::FeatureTyping>(element)) line << " typed=" << id(typing->typedFeature());
        if (const auto chaining = std::dynamic_pointer_cast<K::FeatureChaining>(element)) line << " chaining=" << id(chaining->chainingFeature());
        if (const auto comment = std::dynamic_pointer_cast<K::Comment>(element)) line << " body=" << comment->body();
        if (const auto integer = std::dynamic_pointer_cast<K::LiteralInteger>(element)) line << " value=" << integer->value();
        if (const auto text = std::dynamic_pointer_cast<K::LiteralString>(element)) line << " value=" << text->value();
        if (const auto boolean = std::dynamic_pointer_cast<K::LiteralBoolean>(element)) line << " value=" << boolean->value();
        if (const auto real = std::dynamic_pointer_cast<K::LiteralRational>(element)) line << " value=" << real->value();
        if (const auto expression = std::dynamic_pointer_cast<K::OperatorExpression>(element)) line << " operator=" << expression->operatorName();
        out.push_back(line.str());
        size_t index = 0;
        for (const auto& relationship : element->ownedRelationship()) visit(relationship, position + "/r" + std::to_string(index++));
        if (const auto relationship = std::dynamic_pointer_cast<K::Relationship>(element); relationship && !std::dynamic_pointer_cast<K::Namespace>(element)) {
            index = 0;
            for (const auto& related : relationship->ownedRelatedElement()) visit(related, position + "/e" + std::to_string(index++));
        }
    };
    visit(root, "");
}

// A SysML model, resolved against the XMI library: written with writeXmi and read again.
class XmiExportText : public ::testing::TestWithParam<std::string> {
public:
    // The library, loaded once for all tests: the textual model is replaced by every test.
    struct Context {
        Workspace text;
        Workspace xmi;
        size_t textSource = 0;
        size_t xmiSource = 0;
        Context() {
            for (const auto& file : xmiFiles()) {
                text.addFile(file.string());
                xmi.addFile(file.string());
            }
            textSource = text.addText("", "model.sysml", SourceLanguage::SysML, 1);
            xmiSource = xmi.addText("", "model.sysmlx", SourceLanguage::Xmi, 1);
        }
    };
    static Context& context() {
        static Context instance;
        return instance;
    }
};

std::vector<std::string> modelFiles() {
    std::vector<std::string> names;
    for (const char* name : {"definitions.sysml", "part_usage.sysml", "attribute_usage.sysml", "imports.sysml", "port_usage.sysml", "action_def.sysml",
                             "state_def.sysml", "requirement_usage.sysml", "expr_operators.sysml", "interface_usage.sysml", "redefinition_lists.sysml",
                             "ref_usage.sysml", "constraint_def_empty.sysml", "directed_default_value.sysml"}) {
        if (fs::exists(fs::path(SYSML_VALID_DIR) / name)) names.push_back(name);
    }
    return names;
}

TEST_P(XmiExportText, WrittenAndReadAgainIsTheSameModel) {
    auto& ctx = context();
    const std::string text = ConformanceTest::readFile(fs::path(SYSML_VALID_DIR) / GetParam());
    ctx.text.replaceSource(ctx.textSource, text, SourceLanguage::SysML);
    ctx.text.resolve();
    ASSERT_TRUE(ctx.text.errors(ctx.textSource).empty()) << allErrors(ctx.text.errors(ctx.textSource));
    const auto root = ctx.text.rootNamespace(ctx.textSource);
    ASSERT_NE(root, nullptr);

    // The implicit generalizations are not part of the ownership structure: nothing in it is implied.
    std::vector<std::string> before;
    describeTree(root, listedBy(ctx.text, ctx.textSource), before);
    ASSERT_GE(before.size(), 3u);
    for (const auto& element : ctx.text.elements(ctx.textSource)) {
        if (const auto relationship = std::dynamic_pointer_cast<K::Relationship>(element)) EXPECT_FALSE(relationship->isImplied()) << element->getType();
    }

    TempDir directory;
    const fs::path file = directory.path() / "model.sysmlx";
    const Errors errors = ctx.text.writeXmi(ctx.textSource, file.string());
    // (the files are not self contained: what the library does not define stays unresolved, which is a warning, and is not written)
    for (const auto& error : errors) {
        EXPECT_EQ(error->errorType(), ErrorType::WARNING) << describe(error);
        EXPECT_NE(error->description().find("unresolved reference"), std::string::npos) << describe(error);
    }
    const std::string xml = ConformanceTest::readFile(file);
    ASSERT_FALSE(xml.empty());

    ctx.xmi.replaceSource(ctx.xmiSource, xml, SourceLanguage::Xmi);
    ctx.xmi.resolve();
    EXPECT_TRUE(ctx.xmi.errors(ctx.xmiSource).empty()) << allErrors(ctx.xmi.errors(ctx.xmiSource));
    for (const auto& reference : ctx.xmi.unresolvedReferences()) ADD_FAILURE() << "unresolved href " << reference.name;

    std::vector<std::string> after;
    describeTree(ctx.xmi.rootNamespace(ctx.xmiSource), listedBy(ctx.xmi, ctx.xmiSource), after);
    ASSERT_EQ(before.size(), after.size());
    size_t different = 0;
    for (size_t i = 0; i < before.size(); ++i) {
        if (before[i] == after[i]) continue;
        if (++different <= 5) ADD_FAILURE() << "element " << i << " differs:\n  text: " << before[i] << "\n  xmi:  " << after[i];
    }
    EXPECT_EQ(different, 0u);
}

INSTANTIATE_TEST_SUITE_P(XmiExportText, XmiExportText, ::testing::ValuesIn(modelFiles()),
                         [](const ::testing::TestParamInfo<std::string>& info) { return ConformanceTest::sanitizeTestName(info.param); });

// A model that is complete with the library: the references into the library are hrefs to its files, and nothing is lost.
TEST(XmiExportTextLibrary, ReferencesIntoTheLibraryAreHrefs) {
    auto& ctx = XmiExportText::context();
    ctx.text.replaceSource(ctx.textSource,
                           "package Demo { private import ScalarValues::*; attribute count : Integer; part def Engine { attribute power : Real; } "
                           "attribute greeting : String = \"hi\"; attribute n : Integer = 3 + 4; }",
                           SourceLanguage::SysML);
    ctx.text.resolve();
    ASSERT_TRUE(ctx.text.unresolvedReferences().empty());
    TempDir directory;
    const fs::path file = directory.path() / "demo.sysmlx";
    const Errors errors = ctx.text.writeXmi(ctx.textSource, file.string());
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    const std::string xml = ConformanceTest::readFile(file);
    const auto integer = ctx.text.find("ScalarValues::Integer");
    ASSERT_NE(integer, nullptr);
    EXPECT_NE(xml.find("ScalarValues.kermlx#" + integer->elementId() + "\""), std::string::npos) << "the typing of count refers to the file of ScalarValues";
    EXPECT_NE(xml.find("href=\"../"), std::string::npos);
    EXPECT_EQ(xml.find("href=\"" + std::string(SYSML_LIBRARY_XMI_DIR)), std::string::npos) << "the paths are relative";

    std::vector<std::string> before;
    describeTree(ctx.text.rootNamespace(ctx.textSource), listedBy(ctx.text, ctx.textSource), before);
    ctx.xmi.replaceSource(ctx.xmiSource, xml, SourceLanguage::Xmi);
    ctx.xmi.resolve();
    EXPECT_TRUE(ctx.xmi.errors(ctx.xmiSource).empty()) << allErrors(ctx.xmi.errors(ctx.xmiSource));
    EXPECT_TRUE(ctx.xmi.unresolvedReferences().empty());
    std::vector<std::string> after;
    describeTree(ctx.xmi.rootNamespace(ctx.xmiSource), listedBy(ctx.xmi, ctx.xmiSource), after);
    EXPECT_TRUE(before == after);
    const auto count = ConformanceTest::named<K::Feature>(ctx.xmi.elements(ctx.xmiSource), "count");
    ASSERT_NE(count, nullptr);
    ASSERT_EQ(count->type().size(), 1u);
    EXPECT_EQ(count->type().front()->elementId(), integer->elementId());
}

// ---------------------------------------------------------------------------------------------------------------------
// Name based ids
// ---------------------------------------------------------------------------------------------------------------------

const char* const NamedModel =
    "package Demo { part def Engine { attribute power : ScalarValues::Real; } part car { part engine : Engine; } "
    "attribute count : ScalarValues::Integer = 3; comment about Engine /* the engine */ }";

std::string exportNamed(const std::string& model, bool nameBased) {
    Workspace workspace;
    workspace.addText("package ScalarValues { attribute def Real; attribute def Integer; }", "lib.sysml", SourceLanguage::SysML, 0);
    const size_t source = workspace.addText(model, "model.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    TempDir directory;
    XmiWriteOptions options;
    if (nameBased) options.ids = XmiWriteOptions::IdMode::NameBased;
    const Errors errors = workspace.writeXmi(source, (directory.path() / "m.sysmlx").string(), options);
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    return ConformanceTest::readFile(directory.path() / "m.sysmlx");
}

TEST(XmiExportDeterminism, NameBasedExportIsByteIdenticalAcrossRuns) {
    // two separately parsed workspaces: the element ids differ, the name based ids do not
    const std::string first = exportNamed(NamedModel, true);
    const std::string second = exportNamed(NamedModel, true);
    EXPECT_FALSE(first.empty());
    EXPECT_EQ(first, second);
    // while the element ids of the parser are new in every run
    EXPECT_NE(exportNamed(NamedModel, false), exportNamed(NamedModel, false));
}

TEST(XmiExportDeterminism, NameBasedIdsAreUniqueAndAreUuids) {
    const std::string xml = exportNamed(NamedModel, true);
    std::set<std::string> ids;
    size_t count = 0;
    for (size_t at = xml.find("xmi:id=\""); at != std::string::npos; at = xml.find("xmi:id=\"", at + 1)) {
        const std::string id = xml.substr(at + 8, 36);
        EXPECT_EQ(id[14], '5') << id;   // version 5
        ids.insert(id);
        ++count;
    }
    EXPECT_GT(count, 10u);
    EXPECT_EQ(ids.size(), count);
}

TEST(XmiExportDeterminism, ElementIdExportOfAWorkspaceIsByteIdentical) {
    Workspace workspace;
    const size_t source = workspace.addText(NamedModel, "model.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    TempDir directory;
    workspace.writeXmi(source, (directory.path() / "a.sysmlx").string());
    workspace.writeXmi(source, (directory.path() / "b.sysmlx").string());
    EXPECT_EQ(ConformanceTest::readFile(directory.path() / "a.sysmlx"), ConformanceTest::readFile(directory.path() / "b.sysmlx"));
}

// The ids of the elements of a text are the element ids of the parser, and the reader gives them back.
TEST(XmiExportTextIds, ElementIdModeKeepsTheElementIds) {
    Workspace workspace;
    const size_t source = workspace.addText("package P { part def A; part a : A; }", "p.sysml", SourceLanguage::SysML);
    workspace.resolve();
    TempDir directory;
    const fs::path file = directory.path() / "p.sysmlx";
    EXPECT_TRUE(workspace.writeXmi(source, file.string()).empty());
    Workspace again;
    const size_t read = again.addFile(file.string());
    again.resolve();
    EXPECT_TRUE(again.errors().empty()) << allErrors(again.errors());
    EXPECT_TRUE(again.unresolvedReferences().empty());
    EXPECT_EQ(idsOf(workspace, source).size() >= 1u, true);
    for (const auto& id : idsOf(workspace, source)) {
        EXPECT_EQ(idsOf(again, read).count(id), 1u) << id;
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// References that cannot be written
// ---------------------------------------------------------------------------------------------------------------------

TEST(XmiExportNegative, UnresolvedNameIsAWarningAndThePropertyIsOmitted) {
    Workspace workspace;
    const size_t source = workspace.addText("package P { part def A :> Missing; part a : Unknown; part b : A; }", "p.sysml", SourceLanguage::SysML);
    workspace.resolve();
    ASSERT_EQ(workspace.unresolvedReferences().size(), 2u);
    TempDir directory;
    const fs::path file = directory.path() / "p.sysmlx";
    const Errors errors = workspace.writeXmi(source, file.string());
    ASSERT_FALSE(errors.empty());
    size_t missing = 0;
    size_t unknown = 0;
    for (const auto& error : errors) {
        EXPECT_EQ(error->errorType(), ErrorType::WARNING) << describe(error);
        const std::string text = error->description();
        EXPECT_NE(text.find("unresolved reference"), std::string::npos) << text;
        if (text.find("'Missing'") != std::string::npos) {
            ++missing;
            EXPECT_NE(text.find("PartDefinition 'A'"), std::string::npos) << text;
            EXPECT_NE(text.find("'superclassifier'"), std::string::npos) << text;
        }
        if (text.find("'Unknown'") != std::string::npos) {
            ++unknown;
            EXPECT_NE(text.find("'type'"), std::string::npos) << text;
        }
    }
    EXPECT_EQ(missing, 1u) << allErrors(errors);
    EXPECT_EQ(unknown, 1u) << allErrors(errors);

    // the file is written without the two references and can be read: only the typing of b is complete
    const std::string xml = ConformanceTest::readFile(file);
    EXPECT_EQ(xml.find("Missing"), std::string::npos);
    EXPECT_EQ(xml.find("Unknown"), std::string::npos);
    Workspace again;
    const size_t read = again.addFile(file.string());
    again.resolve();
    EXPECT_TRUE(again.errors(read).empty()) << allErrors(again.errors(read));
    const auto b = ConformanceTest::named<K::Feature>(again.elements(read), "b");
    ASSERT_NE(b, nullptr);
    ASSERT_EQ(b->ownedTyping().size(), 1u);
    EXPECT_EQ(b->ownedTyping().front()->type(), ConformanceTest::named<K::Type>(again.elements(read), "A"));
}

TEST(XmiExportNegative, ElementInNoFileIsAnErrorAndTheReferenceIsNotWritten) {
    Workspace workspace;
    workspace.addText("package L { part def Base; }", "l.sysml", SourceLanguage::SysML, 0);
    const size_t model = workspace.addText("package M { part def D :> L::Base; }", "m.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    ASSERT_TRUE(workspace.unresolvedReferences().empty());
    const auto base = ConformanceTest::named<K::Type>(workspace.elements(), "Base");
    ASSERT_NE(base, nullptr);

    Errors errors;
    const std::string xml = XmiWriter::write(workspace.rootNamespace(model), "m.sysmlx", {}, errors);
    ASSERT_FALSE(errors.empty());
    for (const auto& error : errors) {
        EXPECT_EQ(error->errorType(), ErrorType::LOGICAL_ERROR) << describe(error);
        EXPECT_NE(error->description().find("is in no file"), std::string::npos) << error->description();
        EXPECT_NE(error->description().find("Base"), std::string::npos) << error->description();
    }
    EXPECT_EQ(xml.find("href"), std::string::npos);
    EXPECT_EQ(xml.find(base->elementId()), std::string::npos);

    // with a file for the element the same reference is an href, relative to the directory of the written file, spaces encoded
    Errors located;
    const std::string linked = XmiWriter::write(
        workspace.rootNamespace(model), "out/m.sysmlx",
        [&](const K::Element& element) -> std::optional<std::string> {
            if (element.elementId() == base->elementId()) return std::string("lib dir/l.sysmlx");
            return std::nullopt;
        },
        located);
    EXPECT_TRUE(located.empty()) << allErrors(located);
    EXPECT_NE(linked.find("href=\"../lib%20dir/l.sysmlx#" + base->elementId() + "\""), std::string::npos) << linked;
}

TEST(XmiExportNegative, NullRootWritesNothing) {
    Errors errors;
    EXPECT_TRUE(XmiWriter::write(nullptr, "x.sysmlx", {}, errors).empty());
    EXPECT_TRUE(errors.empty());
}

// The name based id of an element is the same in the file of the element and in the hrefs that other files have to it.
TEST(XmiExportWorkspace, NameBasedIdsMatchAcrossTheFilesOfAnExport) {
    TempDir source;
    {
        std::ofstream(source.path() / "base.sysml") << "package Base { part def Thing; attribute def Mass; }";
        std::ofstream(source.path() / "model.sysml") << "package App { import Base::*; part t : Thing { attribute m : Mass; } }";
    }
    const auto exportAndRead = [&](std::vector<std::string>& texts) {
        Workspace workspace;
        workspace.addFile((source.path() / "base.sysml").string());
        workspace.addFile((source.path() / "model.sysml").string());
        workspace.resolve();
        TempDir out;
        XmiWriteOptions options;
        options.ids = XmiWriteOptions::IdMode::NameBased;
        const Errors errors = workspace.exportXmi(out.path().string(), options);
        EXPECT_TRUE(errors.empty()) << allErrors(errors);
        texts = {ConformanceTest::readFile(out.path() / "base.sysmlx"), ConformanceTest::readFile(out.path() / "model.sysmlx")};
        Workspace again;
        EXPECT_EQ(again.loadLibrary(out.path().string()), 2u);
        again.resolve();
        EXPECT_TRUE(again.errors().empty()) << allErrors(again.errors());
        EXPECT_TRUE(again.unresolvedReferences().empty());
        const auto t = ConformanceTest::named<K::Feature>(again.elements(), "t");
        ASSERT_NE(t, nullptr);
        ASSERT_EQ(t->type().size(), 1u);
        EXPECT_EQ(t->type().front()->declaredName().value_or(""), "Thing");
        EXPECT_FALSE(SysMLv2::Files::isUnresolved(t->type().front()));
    };
    std::vector<std::string> first;
    std::vector<std::string> second;
    exportAndRead(first);
    exportAndRead(second);
    ASSERT_EQ(first.size(), 2u);
    EXPECT_EQ(first, second);   // (two runs: new element ids, the same name based ids)
}

TEST(XmiExportWorkspace, ExportKeepsTheRelativeLayoutAndRenamesTheExtensions) {
    TempDir source;
    fs::create_directories(source.path() / "lib");
    {
        std::ofstream(source.path() / "lib" / "base.sysml") << "package Base { part def Thing; }";
        std::ofstream(source.path() / "model.sysml") << "package App { import Base::*; part t : Thing; }";
        std::ofstream(source.path() / "kernel.kerml") << "package K { classifier C; }";
    }
    Workspace workspace;
    workspace.addFile((source.path() / "lib" / "base.sysml").string());
    workspace.addFile((source.path() / "model.sysml").string());
    workspace.addFile((source.path() / "kernel.kerml").string());
    workspace.resolve();
    TempDir out;
    XmiWriteOptions options;
    options.exportRoot = source.path().string();
    const Errors errors = workspace.exportXmi(out.path().string(), options);
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_TRUE(fs::exists(out.path() / "lib" / "base.sysmlx"));
    EXPECT_TRUE(fs::exists(out.path() / "model.sysmlx"));
    EXPECT_TRUE(fs::exists(out.path() / "kernel.kermlx"));

    // the exported directory is a library of its own
    Workspace again;
    EXPECT_EQ(again.loadLibrary(out.path().string()), 3u);
    again.resolve();
    EXPECT_TRUE(again.errors().empty()) << allErrors(again.errors());
    EXPECT_TRUE(again.unresolvedReferences().empty());
    const auto t = ConformanceTest::named<K::Feature>(again.elements(), "t");
    ASSERT_NE(t, nullptr);
    ASSERT_EQ(t->type().size(), 1u);
    EXPECT_EQ(t->type().front()->declaredName().value_or(""), "Thing");
    EXPECT_NE(ConformanceTest::readFile(out.path() / "model.sysmlx").find("href=\"lib/base.sysmlx#"), std::string::npos);
}

// ---------------------------------------------------------------------------------------------------------------------
// Review findings of the writer (ids across files, references into other files, paths, texts, failures)
// ---------------------------------------------------------------------------------------------------------------------

// The start tags of an XMI text, one string each ("<ownedRelationship xsi:type=... >"); declarations and end tags are left out.
std::vector<std::string> startTags(const std::string& xml) {
    std::vector<std::string> tags;
    for (size_t at = xml.find('<'); at != std::string::npos; at = xml.find('<', at + 1)) {
        if (at + 1 >= xml.size() || xml[at + 1] == '/' || xml[at + 1] == '?') continue;
        const size_t end = xml.find('>', at);
        if (end == std::string::npos) break;
        tags.push_back(xml.substr(at, end - at + 1));
    }
    return tags;
}

std::string tagName(const std::string& tag) {
    const size_t end = tag.find_first_of(" />", 1);
    return tag.substr(1, end - 1);
}

std::string attributeOf(const std::string& tag, const std::string& name) {
    const std::string needle = " " + name + "=\"";
    const size_t at = tag.find(needle);
    if (at == std::string::npos) return std::string();
    const size_t start = at + needle.size();
    return tag.substr(start, tag.find('"', start) - start);
}

// The ids (xmi:id) of the elements of the metaclass in a file, in the order of the file.
std::vector<std::string> idsOfType(const std::string& xml, const std::string& type, const std::string& name = std::string()) {
    std::vector<std::string> ids;
    for (const auto& tag : startTags(xml)) {
        if (attributeOf(tag, "xsi:type") != "sysml:" + type) continue;
        if (!name.empty() && attributeOf(tag, "declaredName") != name) continue;
        ids.push_back(attributeOf(tag, "xmi:id"));
    }
    return ids;
}

// The href of the first tag with that name: the path and the id.
struct Href {
    std::string file;
    std::string id;
};

Href hrefOf(const std::string& xml, const std::string& tag) {
    for (const auto& candidate : startTags(xml)) {
        if (tagName(candidate) != tag) continue;
        const std::string href = attributeOf(candidate, "href");
        if (href.empty()) continue;
        const size_t hash = href.find('#');
        return {href.substr(0, hash), hash == std::string::npos ? std::string() : href.substr(hash + 1)};
    }
    return {};
}

std::shared_ptr<K::Namespace> topPackage(const Workspace& workspace, size_t source) {
    for (const auto& relationship : workspace.rootNamespace(source)->ownedRelationship()) {
        if (const auto membership = std::dynamic_pointer_cast<K::OwningMembership>(relationship)) {
            if (auto ns = std::dynamic_pointer_cast<K::Namespace>(membership->ownedMemberElement())) return ns;
        }
    }
    return nullptr;
}

// The membership of an alias (a membership that does not own its member) of a namespace.
std::shared_ptr<K::Membership> aliasOf(const std::shared_ptr<K::Namespace>& ns) {
    for (const auto& relationship : ns->ownedRelationship()) {
        if (std::dynamic_pointer_cast<K::OwningMembership>(relationship)) continue;
        if (auto membership = std::dynamic_pointer_cast<K::Membership>(relationship)) return membership;
    }
    return nullptr;
}

// A member the classes of the model could have made on their own: owned by the namespace through a membership, but listed by no source.
ElementPtr addUnlistedMember(const std::shared_ptr<K::Namespace>& owner, const std::string& name) {
    auto member = std::make_shared<K::Feature>();
    member->setDeclaredName(name);
    auto membership = std::make_shared<K::OwningMembership>();
    membership->setOwningRelatedElement(owner);
    membership->setOwner(owner);
    membership->setOwnedMemberElement(member);
    membership->setMemberElement(member);
    member->setOwningRelationship(membership);
    member->setOwner(owner);
    auto relationships = owner->ownedRelationship();
    relationships.push_back(membership);
    owner->setOwnedRelationship(relationships);
    owner->appendOwnedElement(membership);
    membership->appendOwnedElement(member);
    return member;
}

XmiWriteOptions nameBased() {
    XmiWriteOptions options;
    options.ids = XmiWriteOptions::IdMode::NameBased;
    return options;
}

// Finding 1: the name based ids start from the file, not from what the file contains.
TEST(XmiExportReview, NameBasedIdsDifferBetweenFilesThatDeclareTheSamePackage) {
    TempDir source;
    {
        std::ofstream(source.path() / "a.sysml") << "package P { part def Thing; part x : Thing; }";
        std::ofstream(source.path() / "b.sysml") << "package P { part def Thing; part x : Thing; }";
    }
    Workspace workspace;
    workspace.addFile((source.path() / "a.sysml").string());
    workspace.addFile((source.path() / "b.sysml").string());
    workspace.resolve();
    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string(), nameBased());
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    std::set<std::string> a;
    std::set<std::string> b;
    size_t countA = 0;
    size_t countB = 0;
    for (const auto& tag : startTags(ConformanceTest::readFile(out.path() / "a.sysmlx"))) {
        a.insert(attributeOf(tag, "xmi:id"));
        ++countA;
    }
    for (const auto& tag : startTags(ConformanceTest::readFile(out.path() / "b.sysmlx"))) {
        b.insert(attributeOf(tag, "xmi:id"));
        ++countB;
    }
    EXPECT_GT(countA, 5u);
    EXPECT_EQ(a.size(), countA);
    EXPECT_EQ(b.size(), countB);
    std::vector<std::string> shared;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(shared));
    EXPECT_TRUE(shared.empty()) << shared.size() << " id(s) are in both files";

    // the ids depend on the path relative to the export root only, not on where the root is
    TempDir moved;
    EXPECT_TRUE(workspace.exportXmi(moved.path().string(), nameBased()).empty());
    EXPECT_EQ(ConformanceTest::readFile(out.path() / "a.sysmlx"), ConformanceTest::readFile(moved.path() / "a.sysmlx"));
}

// Finding 1: an id that two files share is reported (the references between files find the target by id).
TEST(XmiExportReview, AnIdUsedInTwoFilesIsAnError) {
    TempDir directory;
    {
        Workspace workspace;
        const size_t source = workspace.addText("package P { part def Thing; }", "x.sysml", SourceLanguage::SysML);
        workspace.resolve();
        EXPECT_TRUE(workspace.writeXmi(source, (directory.path() / "x.sysmlx").string()).empty());
        fs::copy_file(directory.path() / "x.sysmlx", directory.path() / "y.sysmlx");
    }
    Workspace workspace;
    workspace.addFile((directory.path() / "x.sysmlx").string());
    workspace.addFile((directory.path() / "y.sysmlx").string());
    workspace.resolve();
    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string());
    size_t shared = 0;
    for (const auto& error : errors) {
        if (error->errorType() == ErrorType::LOGICAL_ERROR && error->description().find("is also used in the file") != std::string::npos) ++shared;
    }
    EXPECT_GT(shared, 0u) << allErrors(errors);
}

// Finding 2: a reference to an element in another file uses the id the element has in that file, also if the owner file had to number it.
TEST(XmiExportReview, HrefToAnElementWithANumberedIdUsesTheIdOfTheFile) {
    Workspace workspace;
    const size_t a = workspace.addText("package P { part def D; part def D; }", "a.sysml", SourceLanguage::SysML, 0);
    const size_t b = workspace.addText("package Q { alias Z for P::D; }", "b.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    const auto p = topPackage(workspace, a);
    ASSERT_NE(p, nullptr);
    std::vector<ElementPtr> definitions;
    for (const auto& relationship : p->ownedRelationship()) {
        if (const auto membership = std::dynamic_pointer_cast<K::OwningMembership>(relationship)) definitions.push_back(membership->ownedMemberElement());
    }
    ASSERT_EQ(definitions.size(), 2u);
    const auto alias = aliasOf(topPackage(workspace, b));
    ASSERT_NE(alias, nullptr);
    alias->setMemberElement(definitions[1]);   // the second D: the one that gets the numbered key

    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string(), nameBased());
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    const std::vector<std::string> ids = idsOfType(ConformanceTest::readFile(out.path() / "a.sysmlx"), "PartDefinition", "D");
    ASSERT_EQ(ids.size(), 2u);
    ASSERT_NE(ids[0], ids[1]);
    const Href href = hrefOf(ConformanceTest::readFile(out.path() / "b.sysmlx"), "memberElement");
    EXPECT_EQ(href.file, "a.sysmlx");
    EXPECT_EQ(href.id, ids[1]) << "the href has to name the element that is written (the second D), not the first one";

    // writing the one file gives the same id
    TempDir single;
    EXPECT_TRUE(workspace.writeXmi(b, (single.path() / "b.sysmlx").string(), nameBased()).empty());
    EXPECT_EQ(hrefOf(ConformanceTest::readFile(single.path() / "b.sysmlx"), "memberElement").id, ids[1]);
}

// Finding 2: the same for an element the writer moved to another owner (a membership that another membership owns as its member is also listed
// by the namespace; the file has it below the owner it was written for first).
TEST(XmiExportReview, HrefToAnElementTheWriterMovedUsesTheIdOfTheFile) {
    Workspace workspace;
    const size_t a = workspace.addText("package P { part def A; part def B; }", "a.sysml", SourceLanguage::SysML, 0);
    const size_t b = workspace.addText("package Q { alias Z for P::A; }", "b.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    const auto p = topPackage(workspace, a);
    ASSERT_NE(p, nullptr);
    const auto relationships = p->ownedRelationship();
    ASSERT_EQ(relationships.size(), 2u);
    const auto first = relationships[0];
    const auto second = relationships[1];
    second->appendElementToOwnedRelatedElement(first);
    first->setOwningRelatedElement(second);
    const auto alias = aliasOf(topPackage(workspace, b));
    ASSERT_NE(alias, nullptr);
    alias->setMemberElement(first);

    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string(), nameBased());
    for (const auto& error : errors) EXPECT_NE(error->errorType(), ErrorType::LOGICAL_ERROR) << describe(error);
    const std::string xml = ConformanceTest::readFile(out.path() / "a.sysmlx");
    std::string nested;
    for (const auto& tag : startTags(xml)) {
        if (tagName(tag) == "ownedRelatedElement" && attributeOf(tag, "xsi:type") == "sysml:OwningMembership") nested = attributeOf(tag, "xmi:id");
    }
    ASSERT_FALSE(nested.empty()) << "the membership is written inside the other one";
    const Href href = hrefOf(ConformanceTest::readFile(out.path() / "b.sysmlx"), "memberElement");
    EXPECT_EQ(href.file, "a.sysmlx");
    EXPECT_EQ(href.id, nested);
}

// Finding 3 and 4: an element the model owns but no source lists is neither written nor can it be referenced.
TEST(XmiExportReview, ReferenceToAnElementTheOtherFileDoesNotWriteIsAnError) {
    Workspace workspace;
    const size_t a = workspace.addText("package P { part def D; }", "a.sysml", SourceLanguage::SysML, 0);
    const size_t b = workspace.addText("package Q { alias Z for P::D; }", "b.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    const auto extra = addUnlistedMember(topPackage(workspace, a), "extra");
    const auto alias = aliasOf(topPackage(workspace, b));
    ASSERT_NE(alias, nullptr);
    alias->setMemberElement(extra);

    TempDir out;
    const Errors errors = workspace.writeXmi(b, (out.path() / "b.sysmlx").string());
    size_t missing = 0;
    for (const auto& error : errors) {
        if (error->errorType() == ErrorType::LOGICAL_ERROR && error->description().find("'extra'") != std::string::npos) ++missing;
    }
    EXPECT_EQ(missing, 1u) << allErrors(errors);
    const std::string xml = ConformanceTest::readFile(out.path() / "b.sysmlx");
    EXPECT_EQ(xml.find(extra->elementId()), std::string::npos);
    EXPECT_EQ(xml.find("href"), std::string::npos);
}

// Finding 4: what the source does not list is reported, not dropped silently; many are summarized.
TEST(XmiExportReview, ElementsTheSourceDoesNotListAreReported) {
    Workspace workspace;
    const size_t a = workspace.addText("package P { part def D; }", "a.sysml", SourceLanguage::SysML, 0);
    workspace.resolve();
    TempDir out;
    {
        const auto p = topPackage(workspace, a);
        addUnlistedMember(p, "extra");
        const Errors errors = workspace.writeXmi(a, (out.path() / "a.sysmlx").string());
        ASSERT_EQ(errors.size(), 1u) << allErrors(errors);
        EXPECT_EQ(errors[0]->errorType(), ErrorType::WARNING);
        EXPECT_NE(errors[0]->description().find("OwningMembership"), std::string::npos) << describe(errors[0]);
        EXPECT_NE(errors[0]->description().find("does not list"), std::string::npos) << describe(errors[0]);
        EXPECT_EQ(ConformanceTest::readFile(out.path() / "a.sysmlx").find("extra"), std::string::npos);
    }
    {
        const auto p = topPackage(workspace, a);
        for (int i = 0; i < 11; ++i) addUnlistedMember(p, "more" + std::to_string(i));
        const Errors errors = workspace.writeXmi(a, (out.path() / "a.sysmlx").string());
        ASSERT_EQ(errors.size(), 11u) << allErrors(errors);   // (10 one by one and the summary of the other two)
        EXPECT_NE(errors.back()->description().find("2 more elements"), std::string::npos) << describe(errors.back());
        for (const auto& error : errors) EXPECT_EQ(error->errorType(), ErrorType::WARNING);
    }
}

const char* const ConnectorXmi =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<sysml:Package xmi:version=\"2.0\" xmlns:xmi=\"http://www.omg.org/XMI\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
    "xmlns:sysml=\"https://www.omg.org/spec/SysML/20250201\" xmi:id=\"00000000-0000-4000-8000-000000000001\" "
    "elementId=\"00000000-0000-4000-8000-000000000001\" declaredName=\"P\">\n"
    "  <ownedRelationship xsi:type=\"sysml:OwningMembership\" xmi:id=\"00000000-0000-4000-8000-000000000002\" elementId=\"00000000-0000-4000-8000-000000000002\">\n"
    "    <ownedRelatedElement xsi:type=\"sysml:Connector\" xmi:id=\"00000000-0000-4000-8000-000000000003\" elementId=\"00000000-0000-4000-8000-000000000003\" declaredName=\"c\">\n"
    "      <ownedRelationship xsi:type=\"sysml:EndFeatureMembership\" xmi:id=\"00000000-0000-4000-8000-000000000004\" elementId=\"00000000-0000-4000-8000-000000000004\">\n"
    "        <ownedRelatedElement xsi:type=\"sysml:Feature\" xmi:id=\"00000000-0000-4000-8000-000000000005\" elementId=\"00000000-0000-4000-8000-000000000005\" "
    "isEnd=\"true\" declaredName=\"e1\"/>\n"
    "      </ownedRelationship>\n"
    "    </ownedRelatedElement>\n"
    "  </ownedRelationship>\n"
    "</sysml:Package>\n";

// Finding 5: the end feature of an XMI file is written in its end feature membership again (the reader gave the membership a stand-in); this
// does not apply to what the caller excludes with XmiWriteOptions::include.
TEST(XmiExportReview, EndFeaturesOfAnXmiFileAreAdoptedOnlyWhereTheSourceListsThem) {
    Workspace workspace;
    const size_t source = workspace.addText(ConnectorXmi, "p.sysmlx", SourceLanguage::Xmi, 0);
    ASSERT_TRUE(workspace.errors(source).empty()) << allErrors(workspace.errors(source));
    const std::string endFeature = "00000000-0000-4000-8000-000000000005";

    TempDir out;
    Errors errors = workspace.writeXmi(source, (out.path() / "p.sysmlx").string());
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_NE(ConformanceTest::readFile(out.path() / "p.sysmlx").find(endFeature), std::string::npos) << "the end feature is written";

    // the relationship that follows the end feature membership: not listed by the source (the reader made it)
    ElementPtr connector;
    for (const auto& element : workspace.elements(source)) {
        if (element->declaredName() == std::string("c")) connector = element;
    }
    ASSERT_NE(connector, nullptr);
    const auto relationships = connector->ownedRelationship();
    ASSERT_GE(relationships.size(), 2u);
    const auto wrapper = relationships[1];
    const auto listed = listedBy(workspace, source);
    ASSERT_EQ(listed.count(wrapper.get()), 0u);

    // the caller excludes that relationship: what it owns is not written either
    XmiWriteOptions options;
    options.include = [wrapper](const K::Element& element) { return &element != wrapper.get(); };
    errors = workspace.writeXmi(source, (out.path() / "q.sysmlx").string(), options);
    for (const auto& error : errors) EXPECT_EQ(error->errorType(), ErrorType::WARNING) << describe(error);   // (what the source does not list is reported)
    EXPECT_EQ(ConformanceTest::readFile(out.path() / "q.sysmlx").find(endFeature), std::string::npos) << "an exclusion of the caller is not undone";
}

// Finding 6: names and paths with characters above U+007F are written as percent-encoded UTF-8 and read again.
TEST(XmiExportReview, NonAsciiFileNamesAreWrittenAsPercentEncodedUtf8) {
    TempDir source;
    const fs::path other = source.path() / fs::path(std::u8string(u8"Gr\u00F6\u00DFen.sysml"));
    {
        std::ofstream(source.path() / "big.sysml") << "package Big { import G::*; part z : Y; }";
        std::ofstream(other) << "package G { part def Y; }";
    }
    // (Workspace takes the paths in the narrow encoding of the system: a code page without these characters cannot run this test; the encoding
    // of the writer itself is checked independently of it by Utf8PathsAreEncodedIndependentOfTheCodePage)
    std::string narrow;
    try {
        narrow = other.string();
    } catch (const std::exception&) {
    }
    if (narrow.empty() || fs::path(narrow) != other) GTEST_SKIP() << "the narrow encoding of the system cannot hold the file name";
    Workspace workspace;
    workspace.addFile((source.path() / "big.sysml").string());
    workspace.addFile(narrow);
    workspace.resolve();
    ASSERT_TRUE(workspace.unresolvedReferences().empty());
    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string());
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_TRUE(fs::exists(out.path() / fs::path(std::u8string(u8"Gr\u00F6\u00DFen.sysmlx"))));
    const std::string xml = ConformanceTest::readFile(out.path() / "big.sysmlx");
    EXPECT_NE(xml.find("href=\"Gr%C3%B6%C3%9Fen.sysmlx#"), std::string::npos) << xml;
    for (const char c : xml) EXPECT_LT(static_cast<unsigned char>(c), 0x80) << "no raw non-ASCII byte in the file";

    Workspace again;
    EXPECT_EQ(again.loadLibrary(out.path().string()), 2u);
    again.resolve();
    EXPECT_TRUE(again.errors().empty()) << allErrors(again.errors());
    EXPECT_TRUE(again.unresolvedReferences().empty());
    const auto z = ConformanceTest::named<K::Feature>(again.elements(), "z");
    ASSERT_NE(z, nullptr);
    ASSERT_EQ(z->type().size(), 1u);
    EXPECT_EQ(z->type().front()->declaredName().value_or(""), "Y");
}

#ifdef _WIN32
// Finding 6: a file that no relative path leads to (another drive) is written as a file URI, which the reader accepts.
TEST(XmiExportReview, TargetOnAnotherDriveIsAFileUri) {
    TempDir directory;
    Workspace workspace;
    const size_t lib = workspace.addText("package L { part def Base; }", "l.sysml", SourceLanguage::SysML, 0);
    const size_t model = workspace.addText("package M { part def D :> L::Base; }", "m.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    ASSERT_TRUE(workspace.unresolvedReferences().empty());
    EXPECT_TRUE(workspace.writeXmi(lib, (directory.path() / "l.sysmlx").string()).empty());
    const auto base = ConformanceTest::named<K::Type>(workspace.elements(), "Base");
    ASSERT_NE(base, nullptr);

    Errors errors;
    const std::string xml = XmiWriter::write(
        workspace.rootNamespace(model), "C:/out/m.sysmlx",
        [&](const K::Element& element) -> std::optional<std::string> {
            if (element.elementId() == base->elementId()) return std::string("Z:/x lib/l.sysmlx");
            return std::nullopt;
        },
        errors);
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_NE(xml.find("href=\"file:///Z:/x%20lib/l.sysmlx#" + base->elementId() + "\""), std::string::npos) << xml;

    Workspace again;
    again.addFile((directory.path() / "l.sysmlx").string());
    const size_t read = again.addText(xml, "m.sysmlx", SourceLanguage::Xmi, 1);
    again.resolve();
    EXPECT_TRUE(again.errors(read).empty()) << allErrors(again.errors(read));
    EXPECT_TRUE(again.unresolvedReferences().empty());
}
#endif

// Finding 7: the original type of a port conjugation and the type of a conjugated port typing equal another property, but the reader does not
// derive them: they are written and come back.
const char* const PortXmi =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<sysml:Package xmi:version=\"2.0\" xmlns:xmi=\"http://www.omg.org/XMI\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
    "xmlns:sysml=\"https://www.omg.org/spec/SysML/20250201\" xmi:id=\"00000000-0000-4000-8000-000000000001\" "
    "elementId=\"00000000-0000-4000-8000-000000000001\" declaredName=\"P\">\n"
    "  <ownedRelationship xsi:type=\"sysml:OwningMembership\" xmi:id=\"00000000-0000-4000-8000-000000000002\" elementId=\"00000000-0000-4000-8000-000000000002\">\n"
    "    <ownedRelatedElement xsi:type=\"sysml:PortDefinition\" xmi:id=\"00000000-0000-4000-8000-000000000003\" elementId=\"00000000-0000-4000-8000-000000000003\" declaredName=\"Pd\"/>\n"
    "  </ownedRelationship>\n"
    "  <ownedRelationship xsi:type=\"sysml:OwningMembership\" xmi:id=\"00000000-0000-4000-8000-000000000004\" elementId=\"00000000-0000-4000-8000-000000000004\">\n"
    "    <ownedRelatedElement xsi:type=\"sysml:ConjugatedPortDefinition\" xmi:id=\"00000000-0000-4000-8000-000000000005\" elementId=\"00000000-0000-4000-8000-000000000005\" declaredName=\"Cpd\">\n"
    "      <ownedRelationship xsi:type=\"sysml:PortConjugation\" xmi:id=\"00000000-0000-4000-8000-000000000006\" elementId=\"00000000-0000-4000-8000-000000000006\" "
    "conjugatedType=\"00000000-0000-4000-8000-000000000005\" originalPortDefinition=\"00000000-0000-4000-8000-000000000003\" "
    "originalType=\"00000000-0000-4000-8000-000000000003\"/>\n"
    "    </ownedRelatedElement>\n"
    "  </ownedRelationship>\n"
    "  <ownedRelationship xsi:type=\"sysml:OwningMembership\" xmi:id=\"00000000-0000-4000-8000-000000000007\" elementId=\"00000000-0000-4000-8000-000000000007\">\n"
    "    <ownedRelatedElement xsi:type=\"sysml:PortUsage\" xmi:id=\"00000000-0000-4000-8000-000000000008\" elementId=\"00000000-0000-4000-8000-000000000008\" declaredName=\"u\">\n"
    "      <ownedRelationship xsi:type=\"sysml:ConjugatedPortTyping\" xmi:id=\"00000000-0000-4000-8000-000000000009\" elementId=\"00000000-0000-4000-8000-000000000009\" "
    "typedFeature=\"00000000-0000-4000-8000-000000000008\" conjugatedPortDefinition=\"00000000-0000-4000-8000-000000000005\" "
    "type=\"00000000-0000-4000-8000-000000000005\"/>\n"
    "    </ownedRelatedElement>\n"
    "  </ownedRelationship>\n"
    "</sysml:Package>\n";

TEST(XmiExportReview, PortConjugationAndConjugatedPortTypingKeepTheirTypes) {
    Workspace workspace;
    const size_t source = workspace.addText(PortXmi, "p.sysmlx", SourceLanguage::Xmi, 0);
    workspace.resolve();
    ASSERT_TRUE(workspace.errors(source).empty()) << allErrors(workspace.errors(source));
    TempDir out;
    const Errors errors = workspace.writeXmi(source, (out.path() / "q.sysmlx").string());
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    const std::string xml = ConformanceTest::readFile(out.path() / "q.sysmlx");
    size_t typings = 0;
    size_t conjugations = 0;
    for (const auto& tag : startTags(xml)) {
        if (attributeOf(tag, "xsi:type") == "sysml:ConjugatedPortTyping") {
            ++typings;
            EXPECT_FALSE(attributeOf(tag, "type").empty()) << "the type of the conjugated port typing is written: " << tag;
            EXPECT_FALSE(attributeOf(tag, "conjugatedPortDefinition").empty()) << tag;
        }
        if (attributeOf(tag, "xsi:type") == "sysml:PortConjugation") {
            ++conjugations;
            EXPECT_FALSE(attributeOf(tag, "originalType").empty()) << "the original type of the port conjugation is written: " << tag;
            EXPECT_FALSE(attributeOf(tag, "originalPortDefinition").empty()) << tag;
        }
    }
    EXPECT_EQ(typings, 1u);
    EXPECT_EQ(conjugations, 1u);

    Workspace again;
    const size_t read = again.addFile((out.path() / "q.sysmlx").string());
    again.resolve();
    EXPECT_TRUE(again.errors(read).empty()) << allErrors(again.errors(read));
    size_t checked = 0;
    for (const auto& element : again.elements(read)) {
        if (const auto typing = std::dynamic_pointer_cast<SysMLv2::Entities::ConjugatedPortTyping>(element)) {
            ASSERT_NE(typing->type(), nullptr);
            EXPECT_EQ(typing->type()->declaredName().value_or(""), "Cpd");
            ASSERT_NE(typing->conjugatedPortDefinition(), nullptr);
            ++checked;
        }
        if (const auto conjugation = std::dynamic_pointer_cast<SysMLv2::Entities::PortConjugation>(element)) {
            ASSERT_NE(conjugation->originalType(), nullptr);
            EXPECT_EQ(conjugation->originalType()->declaredName().value_or(""), "Pd");
            ++checked;
        }
    }
    EXPECT_EQ(checked, 2u);
}

// Finding 8: texts that XML cannot hold are written with U+FFFD and reported.
TEST(XmiExportReview, TextsXmlCannotHoldAreReplacedAndReported) {
    Workspace workspace;
    const size_t source = workspace.addText("package P { comment C /* x */ }", "p.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    std::shared_ptr<K::Comment> comment;
    for (const auto& element : workspace.elements(source)) {
        if (auto found = std::dynamic_pointer_cast<K::Comment>(element)) comment = found;
    }
    ASSERT_NE(comment, nullptr);
    struct Case {
        std::string body;
        std::string written;
    };
    const std::vector<Case> cases = {
        {std::string("a\x01" "b", 3), "a\xEF\xBF\xBD" "b"},                      // control character
        {std::string("a\0b", 3), "a\xEF\xBF\xBD" "b"},                           // NUL: not cut off at the C string
        {std::string("a\xFF" "b", 3), "a\xEF\xBF\xBD" "b"},                      // not UTF-8
        {std::string("a\xED\xA0\x80" "b", 5), "a\xEF\xBF\xBD\xEF\xBF\xBD\xEF\xBF\xBD" "b"},   // encoded surrogate
        {std::string("a\xEF\xBF\xBE" "b", 5), "a\xEF\xBF\xBD" "b"},              // U+FFFE
        {"tab\t line\n \xC3\xB6 \xF0\x9F\x98\x80", "tab\t line\n \xC3\xB6 \xF0\x9F\x98\x80"},   // fine: nothing replaced
    };
    for (const auto& c : cases) {
        comment->setBody(c.body);
        TempDir out;
        const Errors errors = workspace.writeXmi(source, (out.path() / "p.sysmlx").string());
        const std::string xml = ConformanceTest::readFile(out.path() / "p.sysmlx");
        const bool clean = c.body == c.written;
        size_t warnings = 0;
        for (const auto& error : errors) {
            EXPECT_EQ(error->errorType(), ErrorType::WARNING) << describe(error);
            if (error->description().find("'body'") != std::string::npos && error->description().find("Comment") != std::string::npos) ++warnings;
        }
        EXPECT_EQ(warnings, clean ? 0u : 1u) << allErrors(errors);
        for (const char ch : xml) {
            const auto byte = static_cast<unsigned char>(ch);
            EXPECT_TRUE(byte >= 0x20 || byte == '\t' || byte == '\n' || byte == '\r') << "control character in the file";
        }
        // the file can be read, and the body is the replaced text
        Workspace again;
        const size_t read = again.addText(xml, "p.sysmlx", SourceLanguage::Xmi, 1);
        EXPECT_TRUE(again.errors(read).empty()) << allErrors(again.errors(read));
        std::shared_ptr<K::Comment> back;
        for (const auto& element : again.elements(read)) {
            if (auto found = std::dynamic_pointer_cast<K::Comment>(element)) back = found;
        }
        ASSERT_NE(back, nullptr);
        EXPECT_EQ(back->body(), c.written);
    }
}

// Finding 9 and 11: nothing to write (the root is excluded) neither creates nor changes the file.
TEST(XmiExportReview, NothingToWriteLeavesTheFileAlone) {
    Workspace workspace;
    const size_t source = workspace.addText("package P { part def D; }", "p.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    TempDir out;
    XmiWriteOptions options;
    options.include = [](const K::Element&) { return false; };
    const fs::path fresh = out.path() / "fresh.sysmlx";
    Errors errors = workspace.writeXmi(source, fresh.string(), options);
    ASSERT_EQ(errors.size(), 1u) << allErrors(errors);
    EXPECT_EQ(errors[0]->errorType(), ErrorType::INTERNAL_ERROR);
    EXPECT_FALSE(fs::exists(fresh));

    const fs::path existing = out.path() / "existing.sysmlx";
    std::ofstream(existing) << "KEEP";
    errors = workspace.writeXmi(source, existing.string(), options);
    EXPECT_FALSE(errors.empty());
    EXPECT_EQ(ConformanceTest::readFile(existing), "KEEP");
    EXPECT_FALSE(fs::exists(fs::path(existing.string() + ".tmp")));
}

// Finding 10 and 3: the lookup of the sources is not kept between two writes; a model that changed between them is written as it is now.
TEST(XmiExportReview, WriteAfterAnEditOfTheModelIsNotStale) {
    Workspace workspace;
    const size_t a = workspace.addText("package P { part def D; }", "a.sysml", SourceLanguage::SysML, 0);
    const size_t b = workspace.addText("package Q { alias Z for P::D; }", "b.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    TempDir out;
    EXPECT_TRUE(workspace.writeXmi(b, (out.path() / "b.sysmlx").string()).empty());
    EXPECT_FALSE(hrefOf(ConformanceTest::readFile(out.path() / "b.sysmlx"), "memberElement").id.empty());

    // D is taken out of the package: no file writes it any more
    const auto p = topPackage(workspace, a);
    p->setOwnedRelationship({});
    p->setOwnedElements({});
    const Errors errors = workspace.writeXmi(b, (out.path() / "b2.sysmlx").string());
    size_t missing = 0;
    for (const auto& error : errors) {
        if (error->errorType() == ErrorType::LOGICAL_ERROR && error->description().find("PartDefinition 'D'") != std::string::npos) ++missing;
    }
    EXPECT_EQ(missing, 1u) << allErrors(errors);
    EXPECT_EQ(ConformanceTest::readFile(out.path() / "b2.sysmlx").find("href"), std::string::npos);
}

// Finding 11: a failure while one file is written is reported for that file; the other files are written and no exception escapes.
TEST(XmiExportReview, FailureOfOneFileDoesNotStopTheExport) {
    Workspace workspace;
    workspace.addText("package Good { part def G; }", "good.sysml", SourceLanguage::SysML, 1);
    workspace.addText("package Bad { part def B; }", "bad.sysml", SourceLanguage::SysML, 1);
    workspace.addText("package Fine { part def F; }", "fine.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    TempDir out;
    std::ofstream(out.path() / "bad.sysmlx") << "KEEP";
    XmiWriteOptions options;
    options.include = [](const K::Element& element) {
        if (element.declaredName() == std::string("Bad")) throw std::runtime_error("boom");
        return true;
    };
    Errors errors;
    EXPECT_NO_THROW(errors = workspace.exportXmi(out.path().string(), options));
    size_t internal = 0;
    for (const auto& error : errors) {
        if (error->errorType() == ErrorType::INTERNAL_ERROR && error->description().find("boom") != std::string::npos) ++internal;
    }
    EXPECT_GE(internal, 1u) << allErrors(errors);
    EXPECT_TRUE(fs::exists(out.path() / "good.sysmlx"));
    EXPECT_TRUE(fs::exists(out.path() / "fine.sysmlx"));
    EXPECT_EQ(ConformanceTest::readFile(out.path() / "bad.sysmlx"), "KEEP");
    EXPECT_FALSE(fs::exists(out.path() / "bad.sysmlx.tmp"));
    EXPECT_NO_THROW(workspace.writeXmi(1, (out.path() / "single.sysmlx").string(), options));
    EXPECT_FALSE(fs::exists(out.path() / "single.sysmlx"));
    EXPECT_THROW(workspace.writeXmi(7, (out.path() / "x.sysmlx").string()), std::out_of_range);
}

// Finding 12a: the special values of a real are the xsd:double literals.
TEST(XmiExportReview, SpecialRealValuesAreWrittenAsXsdLiterals) {
    Workspace workspace;
    const size_t source = workspace.addText("package P { attribute a = 1.5; }", "p.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    std::shared_ptr<K::LiteralRational> literal;
    for (const auto& element : workspace.elements(source)) {
        if (auto found = std::dynamic_pointer_cast<K::LiteralRational>(element)) literal = found;
    }
    ASSERT_NE(literal, nullptr);
    const std::vector<std::pair<double, std::string>> cases = {
        {std::numeric_limits<double>::infinity(), "INF"}, {-std::numeric_limits<double>::infinity(), "-INF"}, {std::numeric_limits<double>::quiet_NaN(), "NaN"}};
    for (const auto& [value, text] : cases) {
        literal->setValue(value);
        TempDir out;
        const Errors errors = workspace.writeXmi(source, (out.path() / "p.sysmlx").string());
        EXPECT_TRUE(errors.empty()) << allErrors(errors);
        const std::string xml = ConformanceTest::readFile(out.path() / "p.sysmlx");
        EXPECT_NE(xml.find(" value=\"" + text + "\""), std::string::npos) << text;
        Workspace again;
        const size_t read = again.addText(xml, "p.sysmlx", SourceLanguage::Xmi, 1);
        EXPECT_TRUE(again.errors(read).empty()) << allErrors(again.errors(read));
        std::shared_ptr<K::LiteralRational> back;
        for (const auto& element : again.elements(read)) {
            if (auto found = std::dynamic_pointer_cast<K::LiteralRational>(element)) back = found;
        }
        ASSERT_NE(back, nullptr);
        if (std::isnan(value)) {
            EXPECT_TRUE(std::isnan(back->value()));
        } else {
            EXPECT_EQ(back->value(), value);
        }
    }
}

// Finding 12b: a member added to the top level of a file does not change the ids of the other members.
TEST(XmiExportReview, NameBasedIdsDoNotDependOnTheOtherTopLevelMembers) {
    const auto idsOfDefinitions = [](const std::string& model) {
        Workspace workspace;
        const size_t source = workspace.addText(model, "m.sysml", SourceLanguage::SysML, 1);
        workspace.resolve();
        TempDir out;
        EXPECT_TRUE(workspace.writeXmi(source, (out.path() / "m.sysmlx").string(), nameBased()).empty());
        return idsOfType(ConformanceTest::readFile(out.path() / "m.sysmlx"), "PartDefinition", "A");
    };
    const auto before = idsOfDefinitions("package P { part def A; }");
    const auto after = idsOfDefinitions("package P { part def A; } package Extra { }");
    ASSERT_EQ(before.size(), 1u);
    EXPECT_EQ(before, after);
}

// Finding 12c: two sources whose names differ in case only do not overwrite each other.
TEST(XmiExportReview, SourcesThatDifferInCaseOnlyAreWrittenToDifferentFiles) {
    Workspace workspace;
    workspace.addText("package Upper { part def U; }", "Model.sysml", SourceLanguage::SysML, 1);
    workspace.addText("package Lower { part def L; }", "model.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string());
    size_t warnings = 0;
    for (const auto& error : errors) {
        EXPECT_EQ(error->errorType(), ErrorType::WARNING) << describe(error);
        if (error->description().find("another source") != std::string::npos) ++warnings;
    }
    EXPECT_EQ(warnings, 1u) << allErrors(errors);
    std::set<std::string> names;
    for (const auto& entry : fs::directory_iterator(out.path())) names.insert(entry.path().filename().string());
    EXPECT_EQ(names, (std::set<std::string>{"Model.sysmlx", "model_2.sysmlx"}));
    EXPECT_NE(ConformanceTest::readFile(out.path() / "Model.sysmlx").find("Upper"), std::string::npos);
    EXPECT_NE(ConformanceTest::readFile(out.path() / "model_2.sysmlx").find("Lower"), std::string::npos);
}

// ---------------------------------------------------------------------------------------------------------------------
// Follow-up review findings (N2 - N4) and test gaps
// ---------------------------------------------------------------------------------------------------------------------

// Restores the working directory at the end of the scope.
class WorkingDirectory {
public:
    explicit WorkingDirectory(const fs::path& directory) : Saved(fs::current_path()) { fs::current_path(directory); }
    ~WorkingDirectory() {
        std::error_code ec;
        fs::current_path(Saved, ec);
    }
    WorkingDirectory(const WorkingDirectory&) = delete;
    WorkingDirectory& operator=(const WorkingDirectory&) = delete;

private:
    fs::path Saved;
};

size_t countOf(const std::string& text, const std::string& part) {
    size_t count = 0;
    for (size_t at = text.find(part); at != std::string::npos; at = text.find(part, at + part.size())) ++count;
    return count;
}

bool endsWith(const std::string& text, const std::string& suffix) {
    return text.size() >= suffix.size() && text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

// The first href of any tag: the path and the id.
Href anyHref(const std::string& xml) {
    for (const auto& candidate : startTags(xml)) {
        const std::string href = attributeOf(candidate, "href");
        if (href.empty()) continue;
        const size_t hash = href.find('#');
        return {href.substr(0, hash), hash == std::string::npos ? std::string() : href.substr(hash + 1)};
    }
    return {};
}

// N2: sources whose only common ancestor is the root of the file system do not take the directories above it into their keys and into the
// layout of the export (no "Users/alice/..." in the ids and in the paths of the files).
TEST(XmiExportFollowUp, SourcesWithOnlyTheRootInCommonAreNamedByTheirFileNames) {
    const fs::path root = fs::temp_directory_path().root_path();
    ASSERT_FALSE(root.empty());
    const auto exportWith = [&](const std::string& firstDirectory, TempDir& out) {
        Workspace workspace;
        workspace.addText("package A { part def X; }", (root / firstDirectory / "x" / "a.sysml").string(), SourceLanguage::SysML, 1);
        workspace.addText("package B { part def Y; }", (root / "xq_other" / "b.sysml").string(), SourceLanguage::SysML, 1);
        workspace.resolve();
        const Errors errors = workspace.exportXmi(out.path().string(), nameBased());
        EXPECT_TRUE(errors.empty()) << allErrors(errors);
    };
    TempDir first;
    TempDir second;
    exportWith("xq_first", first);
    exportWith("xq_second", second);
    EXPECT_TRUE(fs::exists(first.path() / "a.sysmlx"));
    EXPECT_TRUE(fs::exists(first.path() / "b.sysmlx"));
    size_t files = 0;
    for (const auto& entry : fs::recursive_directory_iterator(first.path())) {
        if (entry.is_regular_file()) ++files;
    }
    EXPECT_EQ(files, 2u) << "no directories below the output directory";
    // the ids start from the file name, not from the directory above it
    EXPECT_EQ(ConformanceTest::readFile(first.path() / "a.sysmlx"), ConformanceTest::readFile(second.path() / "a.sysmlx"));
    EXPECT_EQ(ConformanceTest::readFile(first.path() / "b.sysmlx"), ConformanceTest::readFile(second.path() / "b.sysmlx"));
}

// N2: the key of a source that is given by a bare name does not depend on the working directory.
TEST(XmiExportFollowUp, NameBasedExportDoesNotDependOnTheWorkingDirectory) {
    TempDir library;
    fs::create_directories(library.path() / "lib");
    const std::string libraryFile = (library.path() / "lib" / "b.sysml").string();
    const auto exportFrom = [&](const fs::path& directory, TempDir& out) {
        fs::create_directories(directory);
        WorkingDirectory guard(directory);
        Workspace workspace;
        workspace.addText("package Demo { part def Engine { attribute power; } part car { part engine : Engine; } comment about Engine /* the engine */ }", "a.sysml", SourceLanguage::SysML, 1);
        workspace.addText("package B { part def Y; }", libraryFile, SourceLanguage::SysML, 1);
        workspace.resolve();
        const Errors errors = workspace.exportXmi(out.path().string(), nameBased());
        EXPECT_TRUE(errors.empty()) << allErrors(errors);
    };
    TempDir first;
    TempDir second;
    TempDir out1;
    TempDir out2;
    exportFrom(first.path() / "deep" / "er", out1);
    exportFrom(second.path() / "other", out2);
    EXPECT_TRUE(fs::exists(out1.path() / "a.sysmlx"));
    ASSERT_TRUE(fs::exists(out2.path() / "a.sysmlx"));
    EXPECT_EQ(ConformanceTest::readFile(out1.path() / "a.sysmlx"), ConformanceTest::readFile(out2.path() / "a.sysmlx"));

    // bare and relative names are compared with a relative root as they are: no working directory in the keys
    Workspace workspace;
    workspace.addText("package A { }", "a.sysml", SourceLanguage::SysML, 1);
    workspace.addText("package B { }", "sub/b.sysml", SourceLanguage::SysML, 1);
    XmiWriteOptions options;
    options.exportRoot = ".";
    TempDir out3;
    EXPECT_TRUE(workspace.exportXmi(out3.path().string(), options).empty());
    EXPECT_TRUE(fs::exists(out3.path() / "a.sysmlx"));
    EXPECT_TRUE(fs::exists(out3.path() / "sub" / "b.sysmlx"));

    // and without a root they are named by their file names
    TempDir out4;
    EXPECT_TRUE(workspace.exportXmi(out4.path().string()).empty());
    EXPECT_TRUE(fs::exists(out4.path() / "a.sysmlx"));
    EXPECT_TRUE(fs::exists(out4.path() / "b.sysmlx"));
}

#ifdef _WIN32
// N2: the file systems of Windows do not tell "C:" from "c:" (nor "Q" from "q"): the sources share their directory.
TEST(XmiExportFollowUp, DriveLettersAndDirectoriesAreComparedWithoutRegardToTheCaseOnWindows) {
    Workspace workspace;
    workspace.addText("package A { }", "C:/Xq/a.sysml", SourceLanguage::SysML, 1);
    workspace.addText("package B { }", "c:/xq/sub/b.sysml", SourceLanguage::SysML, 1);
    TempDir out;
    XmiWriteOptions options;
    options.exportRoot = "c:/XQ";
    const Errors errors = workspace.exportXmi(out.path().string(), options);
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_TRUE(fs::exists(out.path() / "a.sysmlx"));
    EXPECT_TRUE(fs::exists(out.path() / "sub" / "b.sysmlx"));
}
#endif

// N3: XmiWriter::write() without XmiWriteOptions::listed writes the end feature of an XMI file in its end feature membership again.
TEST(XmiExportFollowUp, EndFeatureOfAnXmiFileIsAdoptedWithoutAListedCallback) {
    Workspace workspace;
    const size_t source = workspace.addText(ConnectorXmi, "p.sysmlx", SourceLanguage::Xmi, 0);
    ASSERT_TRUE(workspace.errors(source).empty()) << allErrors(workspace.errors(source));

    Errors errors;
    const std::string xml = XmiWriter::write(workspace.rootNamespace(source), "p.sysmlx", {}, errors);
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_EQ(countOf(xml, "sysml:EndFeatureMembership"), 1u) << xml;
    EXPECT_EQ(countOf(xml, "sysml:OwningMembership"), 1u) << xml;   // (the one of the connector)
    EXPECT_EQ(countOf(xml, "sysml:Feature\""), 1u) << xml;          // (no stand-in)
    EXPECT_EQ(countOf(xml, "sysml:FeatureMembership"), 0u) << xml;  // (no wrapper)
    EXPECT_EQ(countOf(xml, "00000000-0000-4000-8000-000000000005"), 2u) << xml;   // (xmi:id and elementId of the end feature)

    TempDir out;
    ASSERT_TRUE(workspace.writeXmi(source, (out.path() / "p.sysmlx").string()).empty());
    EXPECT_EQ(xml, ConformanceTest::readFile(out.path() / "p.sysmlx"));

    // read again: the same number of features as in the file it came from
    Workspace again;
    const size_t reread = again.addText(xml, "q.sysmlx", SourceLanguage::Xmi, 0);
    ASSERT_TRUE(again.errors(reread).empty()) << allErrors(again.errors(reread));
    const auto featuresOf = [](const Workspace& w, size_t index) {
        size_t features = 0;
        for (const auto& element : w.elements(index)) {
            if (std::dynamic_pointer_cast<K::Feature>(element)) ++features;
        }
        return features;
    };
    EXPECT_EQ(featuresOf(again, reread), featuresOf(workspace, source));
}

// N3: the adoption is for what the reader made. An end feature membership of a text is written as it is, and so is the structure of an XMI file
// if the caller says that the source lists all of it.
TEST(XmiExportFollowUp, EndFeatureMembershipsOfATextAreNotAdopted) {
    Workspace workspace;
    const size_t source = workspace.addText("package P { part a; part b; connector c from a to b; }", "t.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    Errors withoutListed;
    const std::string direct = XmiWriter::write(workspace.rootNamespace(source), "t.sysmlx", {}, withoutListed);
    EXPECT_GE(countOf(direct, "sysml:EndFeatureMembership"), 2u) << direct;
    // every end feature membership of the text keeps its own end feature
    EXPECT_EQ(countOf(direct, "sysml:EndFeatureMembership"), countOf(direct, "isEnd=\"true\"")) << direct;

    // a callback that lists everything: nothing is a stand-in, the structure of an XMI file is written as it is (stand-in and wrapper)
    Workspace xmi;
    const size_t read = xmi.addText(ConnectorXmi, "p.sysmlx", SourceLanguage::Xmi, 0);
    XmiWriteOptions options;
    options.listed = [](const K::Element&) { return true; };
    Errors errors;
    const std::string everything = XmiWriter::write(xmi.rootNamespace(read), "p.sysmlx", {}, errors, options);
    EXPECT_EQ(countOf(everything, "sysml:FeatureMembership"), 1u) << everything;   // (the wrapper)
    EXPECT_EQ(countOf(everything, "sysml:Feature\""), 2u) << everything;            // (and the stand-in)
}

// N4: the include of the caller is for the file that is written, not for the id tables of the files it refers to.
TEST(XmiExportFollowUp, IncludeOfWriteXmiIsNotAppliedToTheOtherSources) {
    Workspace workspace;
    const size_t library = workspace.addText("package L { part def Base; part def Other; }", "l.sysml", SourceLanguage::SysML, 0);
    const size_t model = workspace.addText("package M { part def D :> L::Base; part def Zzz; }", "m.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    ASSERT_TRUE(workspace.unresolvedReferences().empty());

    TempDir out;
    XmiWriteOptions excluding;
    excluding.include = [](const K::Element& element) { return element.declaredName() != std::string("Base") && element.declaredName() != std::string("Zzz"); };
    Errors errors = workspace.writeXmi(model, (out.path() / "m.sysmlx").string(), excluding);
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    std::string xml = ConformanceTest::readFile(out.path() / "m.sysmlx");
    EXPECT_TRUE(endsWith(anyHref(xml).file, "l.sysmlx")) << xml;   // (the reference into the library is written)
    EXPECT_EQ(xml.find("Zzz"), std::string::npos) << "the include applies to the written file";

    // an include that throws for an element of the other source is never called for it
    int calls = 0;
    XmiWriteOptions throwing;
    throwing.include = [&calls](const K::Element& element) {
        if (element.declaredName() == std::string("Base") || element.declaredName() == std::string("Other")) {
            ++calls;
            throw std::runtime_error("boom");
        }
        return true;
    };
    errors = workspace.writeXmi(model, (out.path() / "m2.sysmlx").string(), throwing);
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_EQ(calls, 0);
    EXPECT_TRUE(endsWith(anyHref(ConformanceTest::readFile(out.path() / "m2.sysmlx")).file, "l.sysmlx"));

    // keepsId of the caller is for every file that is written with these options, the library as well: the references into the library
    // have to use the ids that the library file gets when it is written with the same options (the element keeps its element id)
    XmiWriteOptions keeping = nameBased();
    keeping.keepsId = [](const K::Element& element) { return element.declaredName() == std::string("Base"); };
    ASSERT_TRUE(workspace.writeXmi(model, (out.path() / "m4.sysmlx").string(), keeping).empty());
    ASSERT_TRUE(workspace.writeXmi(library, (out.path() / "l4.sysmlx").string(), keeping).empty());
    const Href href = anyHref(ConformanceTest::readFile(out.path() / "m4.sysmlx"));
    const std::string libraryXml = ConformanceTest::readFile(out.path() / "l4.sysmlx");
    ASSERT_FALSE(href.id.empty());
    EXPECT_NE(libraryXml.find("xmi:id=\"" + href.id + "\""), std::string::npos) << "the id of the href is not in the library file: " << href.id;
    const auto base = ConformanceTest::named<K::Type>(workspace.elements(), "Base");
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(href.id, base->elementId());
}

// N4: exportXmi() gives every file the same options. A table of ids that cannot be built is not built again for every reference; the failure
// is reported once, with its file, and the references into that file are named one by one.
TEST(XmiExportFollowUp, FailedIdTableIsBuiltOnceAndReportedOnce) {
    Workspace workspace;
    workspace.addText("package L { part def Base; }", "l.sysml", SourceLanguage::SysML, 0);
    workspace.addText("package M { part a : L::Base; part b : L::Base; part c : L::Base; part d : L::Base; part e : L::Base; part f : L::Base; }", "m.sysml",
                      SourceLanguage::SysML, 1);
    workspace.resolve();
    ASSERT_TRUE(workspace.unresolvedReferences().empty());
    int throws = 0;
    XmiWriteOptions options;
    options.include = [&throws](const K::Element& element) {
        if (element.declaredName() == std::string("Base")) {
            ++throws;
            throw std::runtime_error("boom");
        }
        return true;
    };
    TempDir out;
    Errors errors;
    ASSERT_NO_THROW(errors = workspace.exportXmi(out.path().string(), options));
    EXPECT_LE(throws, 2) << "once for the table, once for the file itself";
    size_t internal = 0;
    size_t unwritable = 0;
    size_t reasons = 0;
    for (const auto& error : errors) {
        if (error->errorType() == ErrorType::INTERNAL_ERROR && error->description().find("boom") != std::string::npos) ++internal;
        if (error->errorType() == ErrorType::LOGICAL_ERROR) ++unwritable;
        if (error->description().find("could not be assigned") != std::string::npos && error->description().find("boom") != std::string::npos) ++reasons;
        EXPECT_EQ(error->description().find("is in no file"), std::string::npos) << "misleading: " << describe(error);
    }
    EXPECT_EQ(internal, 1u) << allErrors(errors, 30);
    EXPECT_EQ(unwritable, 7u) << allErrors(errors, 30);   // (the six references, one by one, and why they cannot be written)
    EXPECT_EQ(reasons, 1u) << allErrors(errors, 30);      // (the reason, once for the file that refers to the failed one)
    EXPECT_FALSE(fs::exists(out.path() / "l.sysmlx"));
    EXPECT_TRUE(fs::exists(out.path() / "m.sysmlx"));
}

// Gap: IdMode::NameBased through the public XmiWriter::write() without foreignId cannot derive the id of a foreign element: an error, no href.
TEST(XmiExportFollowUp, NameBasedWithoutForeignIdReportsTheForeignReference) {
    Workspace workspace;
    workspace.addText("package L { part def Base; }", "l.sysml", SourceLanguage::SysML, 0);
    const size_t model = workspace.addText("package M { part def D :> L::Base; }", "m.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    const auto base = ConformanceTest::named<K::Type>(workspace.elements(), "Base");
    ASSERT_NE(base, nullptr);
    Errors errors;
    const std::string xml = XmiWriter::write(
        workspace.rootNamespace(model), "m.sysmlx",
        [&](const K::Element& element) -> std::optional<std::string> {
            if (element.elementId() == base->elementId()) return std::string("l.sysmlx");
            return std::nullopt;
        },
        errors, nameBased());
    ASSERT_FALSE(errors.empty());
    for (const auto& error : errors) {
        EXPECT_EQ(error->errorType(), ErrorType::LOGICAL_ERROR) << describe(error);
        EXPECT_NE(error->description().find("Base"), std::string::npos) << error->description();
    }
    EXPECT_EQ(xml.find("href"), std::string::npos);
    EXPECT_EQ(xml.find(base->elementId()), std::string::npos);
}

// Gap: the file is written to a temporary file and renamed: an existing target is replaced as a whole, and no temporary file is left.
TEST(XmiExportFollowUp, ExistingTargetFileIsReplacedByTheExport) {
    Workspace workspace;
    const size_t source = workspace.addText("package P { part def D; }", "p.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    TempDir out;
    ASSERT_TRUE(workspace.writeXmi(source, (out.path() / "fresh.sysmlx").string()).empty());
    const std::string expected = ConformanceTest::readFile(out.path() / "fresh.sysmlx");
    ASSERT_FALSE(expected.empty());

    const fs::path existing = out.path() / "existing.sysmlx";
    std::ofstream(existing) << std::string(expected.size() * 3, 'x');   // (longer than the new text)
    EXPECT_TRUE(workspace.writeXmi(source, existing.string()).empty());
    EXPECT_EQ(ConformanceTest::readFile(existing), expected);
    EXPECT_FALSE(fs::exists(fs::path(existing.string() + ".tmp")));

    TempDir directory;
    std::ofstream(directory.path() / "p.sysmlx") << "OLD";
    EXPECT_TRUE(workspace.exportXmi(directory.path().string()).empty());
    EXPECT_NE(ConformanceTest::readFile(directory.path() / "p.sysmlx").find("<sysml:"), std::string::npos);
    EXPECT_FALSE(fs::exists(directory.path() / "p.sysmlx.tmp"));
}

// Gap: names with characters above U+007F are percent-encoded UTF-8 whatever the narrow encoding of the system is (the paths given to the
// writer are UTF-8).
TEST(XmiExportFollowUp, Utf8PathsAreEncodedIndependentOfTheCodePage) {
    Workspace workspace;
    workspace.addText("package L { part def Base; }", "l.sysml", SourceLanguage::SysML, 0);
    const size_t model = workspace.addText("package M { part def D :> L::Base; }", "m.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    const auto base = ConformanceTest::named<K::Type>(workspace.elements(), "Base");
    ASSERT_NE(base, nullptr);
    const std::u8string library = u8"\u00FCber/Gr\u00F6\u00DFen \u20AC.sysmlx";
    const std::u8string target = u8"\u00FCber/out/m.sysmlx";
    Errors errors;
    const std::string xml = XmiWriter::write(
        workspace.rootNamespace(model), std::string(target.begin(), target.end()),
        [&](const K::Element& element) -> std::optional<std::string> {
            if (element.elementId() == base->elementId()) return std::string(library.begin(), library.end());
            return std::nullopt;
        },
        errors);
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_NE(xml.find("href=\"../Gr%C3%B6%C3%9Fen%20%E2%82%AC.sysmlx#" + base->elementId() + "\""), std::string::npos) << xml;
    for (const char c : xml) EXPECT_LT(static_cast<unsigned char>(c), 0x80);
}

// Gap: the formatting of the relative href, with the forms of POSIX paths (a leading "/"), without a second drive.
TEST(XmiExportFollowUp, RelativeHrefAcrossDirectories) {
    Workspace workspace;
    workspace.addText("package L { part def Base; }", "l.sysml", SourceLanguage::SysML, 0);
    const size_t model = workspace.addText("package M { part def D :> L::Base; }", "m.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    const auto base = ConformanceTest::named<K::Type>(workspace.elements(), "Base");
    ASSERT_NE(base, nullptr);
    const auto href = [&](const std::string& target, const std::string& library) {
        Errors errors;
        const std::string xml = XmiWriter::write(
            workspace.rootNamespace(model), target,
            [&](const K::Element& element) -> std::optional<std::string> {
                if (element.elementId() == base->elementId()) return library;
                return std::nullopt;
            },
            errors);
        EXPECT_TRUE(errors.empty()) << allErrors(errors);
        return anyHref(xml).file;
    };
    EXPECT_EQ(href("/xq/out/sub/m.sysmlx", "/xq/lib/x lib/l.sysmlx"), "../../lib/x%20lib/l.sysmlx");
    EXPECT_EQ(href("/xq/m.sysmlx", "/xq/lib/l.sysmlx"), "lib/l.sysmlx");
    EXPECT_EQ(href("/xq/a/b/m.sysmlx", "/xq/l.sysmlx"), "../../l.sysmlx");
    EXPECT_EQ(href("/xq/a/m.sysmlx", "/xq/a/l#1%.sysmlx"), "l%231%25.sysmlx");
}

// ---------------------------------------------------------------------------------------------------------------------
// The explicit export root (XmiWriteOptions::exportRoot) and the review findings that came with it
// ---------------------------------------------------------------------------------------------------------------------

// Every xmi:id of a text, in the order of the file.
std::vector<std::string> allXmiIds(const std::string& xml) {
    std::vector<std::string> ids;
    for (const auto& tag : startTags(xml)) {
        const std::string id = attributeOf(tag, "xmi:id");
        if (!id.empty()) ids.push_back(id);
    }
    return ids;
}

void writeText(const fs::path& file, const std::string& text) {
    fs::create_directories(file.parent_path());
    std::ofstream(file, std::ios::binary) << text;
}

// A model "<top>/Users/<user>/proj/m.sysml" and a library "<top>/Users/Public/lib/Base.kerml" (and sub/Deep.kerml below it).
struct ProjectTree {
    TempDir directory;
    fs::path top;
    fs::path project;
    fs::path library;

    explicit ProjectTree(const std::string& user) {
        top = directory.path();
        project = top / "Users" / user / "proj";
        library = top / "Users" / "Public" / "lib";
        writeText(project / "m.sysml", "package M { import Base::*; part x : Thing; }");
        writeText(library / "Base.kerml", "package Base { classifier Thing; }");
        writeText(library / "sub" / "Deep.kerml", "package Deep { classifier Down; }");
    }
};

// Loads the tree like a caller does (the library from its directory, the model as a file); returns the index of the model.
size_t loadTree(Workspace& workspace, const ProjectTree& tree) {
    EXPECT_EQ(workspace.loadLibrary(tree.library.string()), 2u);
    const size_t model = workspace.addFile((tree.project / "m.sysml").string(), 1);
    workspace.resolve();
    return model;
}

XmiWriteOptions rooted(const fs::path& root) {
    XmiWriteOptions options = nameBased();
    options.exportRoot = root.string();
    return options;
}

// A: the key of a source below the export root is its path relative to it; the library has the key of its load root. The ids do not depend on
// the directories above (the name of a user), and the output of writeXmi() has the ids of exportXmi().
TEST(XmiExportRoot, KeysAreRelativeToTheRootAndDoNotDependOnTheDirectoriesAbove) {
    ProjectTree alice("alice");
    ProjectTree bob("bobby");
    const auto exportTree = [](const ProjectTree& tree, TempDir& out) {
        Workspace workspace;
        loadTree(workspace, tree);
        const Errors errors = workspace.exportXmi(out.path().string(), rooted(tree.project));
        EXPECT_TRUE(errors.empty()) << allErrors(errors);
    };
    TempDir outAlice;
    TempDir outBob;
    exportTree(alice, outAlice);
    exportTree(bob, outBob);
    EXPECT_TRUE(fs::exists(outAlice.path() / "m.sysmlx"));
    EXPECT_TRUE(fs::exists(outAlice.path() / "Base.kermlx")) << "the library is named relative to its load root";
    EXPECT_TRUE(fs::exists(outAlice.path() / "sub" / "Deep.kermlx"));
    for (const char* file : {"m.sysmlx", "Base.kermlx", "sub/Deep.kermlx"}) {
        SCOPED_TRACE(file);
        ASSERT_TRUE(fs::exists(outBob.path() / file));
        EXPECT_EQ(ConformanceTest::readFile(outAlice.path() / file), ConformanceTest::readFile(outBob.path() / file));
    }

    // writeXmi() with the same root gives the model the ids that exportXmi() gave it
    Workspace workspace;
    const size_t model = loadTree(workspace, alice);
    TempDir single;
    const Errors errors = workspace.writeXmi(model, (single.path() / "m.sysmlx").string(), rooted(alice.project));
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_EQ(allXmiIds(ConformanceTest::readFile(single.path() / "m.sysmlx")), allXmiIds(ConformanceTest::readFile(outAlice.path() / "m.sysmlx")));
}

// A: the key of a source never depends on the other sources.
TEST(XmiExportRoot, AddingASourceDoesNotChangeTheOtherKeys) {
    ProjectTree tree("alice");
    TempDir without;
    TempDir with;
    {
        Workspace workspace;
        loadTree(workspace, tree);
        EXPECT_TRUE(workspace.exportXmi(without.path().string(), rooted(tree.project)).empty());
    }
    {
        Workspace workspace;
        loadTree(workspace, tree);
        workspace.addText("package Elsewhere { part def Z; }", (tree.top / "Elsewhere" / "far" / "z.sysml").string(), SourceLanguage::SysML, 1);
        workspace.addText("package Rel { }", "r.sysml", SourceLanguage::SysML, 1);
        workspace.resolve();
        const Errors errors = workspace.exportXmi(with.path().string(), rooted(tree.project));
        // ("r.sysml" is relative and the root is not: the comparison depends on the working directory, and the export says so)
        EXPECT_TRUE(onlyWorkingDirectoryWarnings(errors, 1)) << allErrors(errors);
    }
    for (const char* file : {"m.sysmlx", "Base.kermlx", "sub/Deep.kermlx"}) {
        SCOPED_TRACE(file);
        EXPECT_EQ(ConformanceTest::readFile(without.path() / file), ConformanceTest::readFile(with.path() / file));
    }
    EXPECT_TRUE(fs::exists(with.path() / "z.sysmlx"));
    EXPECT_TRUE(fs::exists(with.path() / "r.sysmlx"));
}

// A: a source that is not below the root falls back to its load root, and without a load root to its file name.
TEST(XmiExportRoot, SourcesOutsideTheRootFallBackToTheirLoadRootAndThenTheirFileName) {
    ProjectTree tree("alice");
    TempDir sibling;
    Workspace workspace;
    const size_t model = loadTree(workspace, tree);
    (void)model;
    // a file of the library that is added on its own (no load root): the file name
    workspace.addFile((tree.library / "sub" / "Deep.kerml").string(), 0);
    TempDir out;
    // the root is a directory of its own, below which there is nothing
    fs::create_directories(sibling.path() / "emptyroot");
    const Errors errors = workspace.exportXmi(out.path().string(), rooted(sibling.path() / "emptyroot"));
    // (Deep.kerml twice: once from the load root as sub/Deep.kermlx, once by its file name Deep.kermlx)
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_TRUE(fs::exists(out.path() / "m.sysmlx")) << "the model is not below the root: its file name";
    EXPECT_TRUE(fs::exists(out.path() / "Base.kermlx"));
    EXPECT_TRUE(fs::exists(out.path() / "sub" / "Deep.kermlx"));
    EXPECT_TRUE(fs::exists(out.path() / "Deep.kermlx"));

    // the fallback is the same as without any root
    TempDir plain;
    EXPECT_TRUE(workspace.exportXmi(plain.path().string(), nameBased()).empty());
    for (const char* file : {"m.sysmlx", "Base.kermlx", "sub/Deep.kermlx", "Deep.kermlx"}) {
        SCOPED_TRACE(file);
        EXPECT_EQ(ConformanceTest::readFile(out.path() / file), ConformanceTest::readFile(plain.path() / file));
    }
}

// A: without a root, a library loaded from a directory keeps the layout below that directory, and anything else is named by its file name.
TEST(XmiExportRoot, WithoutARootTheLoadRootOrTheFileNameIsTheKey) {
    ProjectTree tree("alice");
    Workspace workspace;
    loadTree(workspace, tree);
    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string());
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_TRUE(fs::exists(out.path() / "m.sysmlx"));
    EXPECT_TRUE(fs::exists(out.path() / "Base.kermlx"));
    EXPECT_TRUE(fs::exists(out.path() / "sub" / "Deep.kermlx"));
    size_t files = 0;
    for (const auto& entry : fs::recursive_directory_iterator(out.path())) {
        if (entry.is_regular_file()) ++files;
    }
    EXPECT_EQ(files, 3u);
    // (the directories above never get into the layout)
    EXPECT_FALSE(fs::exists(out.path() / "Users"));
}

// A: a key is never absolute and never leaves the export directory, whatever the names of the sources are.
TEST(XmiExportRoot, KeysNeverEscapeTheExportDirectory) {
    TempDir container;
    const fs::path out = container.path() / "out";
    fs::create_directories(out);
    {
        Workspace workspace;
        workspace.addText("package A { }", "../escape/a.sysml", SourceLanguage::SysML, 1);
        workspace.addText("package B { }", "../../escape/b.sysml", SourceLanguage::SysML, 1);
        workspace.addText("package C { }", (container.path() / "x" / ".." / ".." / "c.sysml").string(), SourceLanguage::SysML, 1);
        workspace.addText("package D { }", (container.path() / "dd" / "d.sysml").string(), SourceLanguage::SysML, 1);
        workspace.resolve();
        for (const std::string root : {std::string(), std::string(".."), std::string("../.."), (container.path() / "dd").string(), (container.path() / "x" / "..").string()}) {
            SCOPED_TRACE(root);
            XmiWriteOptions options = nameBased();
            options.exportRoot = root;
            const Errors errors = workspace.exportXmi(out.string(), options);
            // (relative names with an absolute root and the other way round: the warning about the working directory, nothing else)
            EXPECT_TRUE(onlyWorkingDirectoryWarnings(errors)) << allErrors(errors);
        }
    }
    for (const auto& entry : fs::recursive_directory_iterator(container.path())) {
        if (!entry.is_regular_file()) continue;
        const fs::path relative = fs::relative(entry.path(), container.path());
        EXPECT_EQ(relative.begin()->string(), "out") << "written outside the export directory: " << entry.path();
    }
    EXPECT_FALSE(fs::exists(container.path() / "escape"));
    EXPECT_FALSE(fs::exists(container.path().parent_path() / "escape" / "a.sysmlx"));
}

// A: the components of the root are compared without regard to the case on Windows.
#ifdef _WIN32
TEST(XmiExportRoot, TheRootIsComparedWithoutRegardToTheCaseOnWindows) {
    ProjectTree tree("alice");
    Workspace workspace;
    loadTree(workspace, tree);
    std::string upper = tree.project.string();
    for (auto& c : upper) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    TempDir out;
    TempDir expected;
    EXPECT_TRUE(workspace.exportXmi(out.path().string(), rooted(upper)).empty());
    EXPECT_TRUE(workspace.exportXmi(expected.path().string(), rooted(tree.project)).empty());
    EXPECT_EQ(ConformanceTest::readFile(out.path() / "m.sysmlx"), ConformanceTest::readFile(expected.path() / "m.sysmlx"));
}
#endif

// Finding 3: a table of ids that cannot be built is reported once per file that refers to it, with the reason.
TEST(XmiExportRoot, WriteXmiReportsWhyTheIdsOfAnotherSourceCannotBeAssigned) {
    Workspace workspace;
    workspace.addText("package L { part def Base; }", "l.sysml", SourceLanguage::SysML, 0);
    const size_t model = workspace.addText("package M { part a : L::Base; part b : L::Base; part c : L::Base; }", "m.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    ASSERT_TRUE(workspace.unresolvedReferences().empty());
    XmiWriteOptions options = nameBased();
    options.keepsId = [](const K::Element& element) {
        if (element.declaredName() == std::string("Base")) throw std::runtime_error("boom");
        return false;
    };
    TempDir out;
    Errors errors;
    ASSERT_NO_THROW(errors = workspace.writeXmi(model, (out.path() / "m.sysmlx").string(), options));
    size_t reasons = 0;
    for (const auto& error : errors) {
        const std::string& text = error->description();
        if (text.find("could not be assigned") != std::string::npos && text.find("boom") != std::string::npos && text.find("l.sysmlx") != std::string::npos) ++reasons;
        EXPECT_EQ(text.find("is in no file"), std::string::npos) << "misleading: " << describe(error);
    }
    EXPECT_EQ(reasons, 1u) << allErrors(errors, 30);
}

// Finding 1: the keepsId of the caller counts for the other sources as well (see IncludeOfWriteXmiIsNotAppliedToTheOtherSources).

// Finding 4: a text source and an XMI source that are written to the same file: the second one is renamed (_2), and the references from
// writeXmi() point to the renamed file, as in an export. The collision is reported.
TEST(XmiExportRoot, WriteXmiReferencesTheRenamedFileOfACollidingSource) {
    TempDir directory;
    const fs::path base = directory.path() / "src";
    fs::create_directories(base);
    Workspace workspace;
    workspace.addText(ConnectorXmi, (base / "B.sysmlx").string(), SourceLanguage::Xmi, 0);
    workspace.addText("package L { part def Base; }", (base / "B.sysml").string(), SourceLanguage::SysML, 0);
    const size_t model = workspace.addText("package M { part def D :> L::Base; }", (base / "m.sysml").string(), SourceLanguage::SysML, 1);
    workspace.resolve();
    ASSERT_TRUE(workspace.unresolvedReferences().empty());

    TempDir out;
    const Errors errors = workspace.writeXmi(model, (out.path() / "m.sysmlx").string());
    const Href href = anyHref(ConformanceTest::readFile(out.path() / "m.sysmlx"));
    EXPECT_TRUE(endsWith(href.file, "B_2.sysmlx")) << href.file;
    size_t collisions = 0;
    for (const auto& error : errors) {
        EXPECT_EQ(error->errorType(), ErrorType::WARNING) << describe(error);
        if (error->description().find("another source") != std::string::npos) ++collisions;
    }
    EXPECT_EQ(collisions, 1u) << allErrors(errors);

    // exportXmi() writes the same file
    TempDir exported;
    Workspace again;
    again.addText(ConnectorXmi, (base / "B.sysmlx").string(), SourceLanguage::Xmi, 0);
    again.addText("package L { part def Base; }", (base / "B.sysml").string(), SourceLanguage::SysML, 0);
    again.addText("package M { part def D :> L::Base; }", (base / "m.sysml").string(), SourceLanguage::SysML, 1);
    again.resolve();
    XmiWriteOptions options;
    options.exportRoot = base.string();
    (void)again.exportXmi(exported.path().string(), options);
    EXPECT_TRUE(fs::exists(exported.path() / "B_2.sysmlx"));
    EXPECT_TRUE(endsWith(anyHref(ConformanceTest::readFile(exported.path() / "m.sysmlx")).file, "B_2.sysmlx"));
}

// Finding 5: the warning of a collision says why the files collide.
TEST(XmiExportRoot, CollisionWarningsNameTheirCause) {
    const fs::path root = fs::temp_directory_path().root_path();
    {
        // the same file name in two directories, no root and no load root to tell them apart
        Workspace workspace;
        workspace.addText("package A { }", (root / "xq_one" / "a.sysml").string(), SourceLanguage::SysML, 1);
        workspace.addText("package B { }", (root / "xq_two" / "a.sysml").string(), SourceLanguage::SysML, 1);
        TempDir out;
        const Errors errors = workspace.exportXmi(out.path().string());
        ASSERT_EQ(errors.size(), 1u) << allErrors(errors);
        EXPECT_EQ(errors[0]->errorType(), ErrorType::WARNING);
        EXPECT_NE(errors[0]->description().find("another source"), std::string::npos) << describe(errors[0]);
        EXPECT_NE(errors[0]->description().find("same file name"), std::string::npos) << describe(errors[0]);
        EXPECT_EQ(errors[0]->description().find("differ in case"), std::string::npos) << describe(errors[0]);
        EXPECT_TRUE(fs::exists(out.path() / "a.sysmlx"));
        EXPECT_TRUE(fs::exists(out.path() / "a_2.sysmlx"));
    }
    {
        // names that differ in case only
        Workspace workspace;
        workspace.addText("package A { }", "Model.sysml", SourceLanguage::SysML, 1);
        workspace.addText("package B { }", "model.sysml", SourceLanguage::SysML, 1);
        TempDir out;
        const Errors errors = workspace.exportXmi(out.path().string());
        ASSERT_EQ(errors.size(), 1u) << allErrors(errors);
        EXPECT_NE(errors[0]->description().find("differ in case"), std::string::npos) << describe(errors[0]);
    }
}

// Finding 6: the case of the names is folded without the locale of the program.
TEST(XmiExportRoot, CaseFoldingDoesNotDependOnTheLocale) {
    // (A and a with diaeresis, written as bytes: the source file is not read as UTF-8 by every compiler)
    std::u8string upper;
    upper += char8_t(0xC3);
    upper += char8_t(0x84);
    upper += u8"rger.sysml";
    std::u8string lower;
    lower += char8_t(0xC3);
    lower += char8_t(0xA4);
    lower += u8"rger.sysml";
    const std::string narrowUpper = fs::path(upper).string();
    const std::string narrowLower = fs::path(lower).string();
    if (narrowUpper.empty() || fs::path(narrowUpper) != fs::path(upper) || fs::path(narrowLower) != fs::path(lower)) {
        GTEST_SKIP() << "the narrow encoding of the system cannot hold the file names";
    }
    const auto warningsFor = [&]() {
        Workspace workspace;
        workspace.addText("package A { }", narrowUpper, SourceLanguage::SysML, 1);
        workspace.addText("package B { }", narrowLower, SourceLanguage::SysML, 1);
        TempDir out;
        size_t collisions = 0;
        const Errors errors = workspace.exportXmi(out.path().string());
        for (const auto& error : errors) {
            if (error->description().find("differ in case") != std::string::npos) ++collisions;
        }
        return collisions;
    };
    const std::string saved = std::setlocale(LC_ALL, nullptr);
    const size_t inClassic = warningsFor();
    size_t inOther = inClassic;
    bool switched = false;
    for (const char* name : {"German_Germany.1252", "de_DE.UTF-8", "de_DE.ISO-8859-1", "French_France.1252", "en_US.UTF-8", ".1252"}) {
        if (std::setlocale(LC_ALL, name) != nullptr) {
            switched = true;
            inOther = warningsFor();
            break;
        }
    }
    std::setlocale(LC_ALL, saved.c_str());
    EXPECT_EQ(inClassic, 1u) << "the umlauts differ in case only";
    if (switched) EXPECT_EQ(inOther, inClassic);
}

// Low: the wrapper that the end feature adoption leaves out may own further relationships, which are lost: a WARNING says so.
TEST(XmiExportRoot, RelationshipsOfTheDroppedEndFeatureWrapperAreReported) {
    Workspace workspace;
    const size_t source = workspace.addText(ConnectorXmi, "p.sysmlx", SourceLanguage::Xmi, 0);
    ASSERT_TRUE(workspace.errors(source).empty()) << allErrors(workspace.errors(source));
    ElementPtr connector;
    for (const auto& element : workspace.elements(source)) {
        if (element->declaredName() == std::string("c")) connector = element;
    }
    ASSERT_NE(connector, nullptr);
    const auto relationships = connector->ownedRelationship();
    ASSERT_GE(relationships.size(), 2u);
    const auto wrapper = relationships[1];
    wrapper->setOwnedRelationship({std::make_shared<K::Membership>()});

    const auto reported = [](const Errors& errors) {
        size_t count = 0;
        for (const auto& error : errors) {
            if (error->errorType() == ErrorType::WARNING && error->description().find("further relationship") != std::string::npos) ++count;
        }
        return count;
    };
    TempDir out;
    const Errors viaWorkspace = workspace.writeXmi(source, (out.path() / "p.sysmlx").string());
    EXPECT_EQ(reported(viaWorkspace), 1u) << allErrors(viaWorkspace);
    Errors direct;
    XmiWriter::write(workspace.rootNamespace(source), "p.sysmlx", {}, direct);
    EXPECT_EQ(reported(direct), 1u) << allErrors(direct);
}

// ---------------------------------------------------------------------------------------------------------------------
// Last review points: replaceSource and the load root, XMI sources in a collision, the reason of a collision, the case folding of Windows,
// keys that are no file names, a root and a source that are not both relative or absolute, the temporary directories of the tests
// ---------------------------------------------------------------------------------------------------------------------

// The file names (the part after the last "/") that the hrefs of an XMI text lead to.
std::set<std::string> hrefFileNames(const std::string& xml) {
    std::set<std::string> names;
    for (const auto& tag : startTags(xml)) {
        const std::string href = attributeOf(tag, "href");
        if (href.empty()) continue;
        const std::string file = href.substr(0, href.find('#'));
        names.insert(file.substr(file.find_last_of('/') + 1));
    }
    return names;
}

size_t warningsWith(const Errors& errors, const std::string& text) {
    size_t count = 0;
    for (const auto& error : errors) {
        if (error->errorType() == ErrorType::WARNING && error->description().find(text) != std::string::npos) ++count;
    }
    return count;
}

// Point 1: a source that is replaced keeps the directory it was loaded from, so the file key (and with it the name based ids) stay the same.
TEST(XmiExportLastReview, ReplaceSourceKeepsTheLoadRoot) {
    ProjectTree tree("alice");
    Workspace workspace;
    loadTree(workspace, tree);
    size_t deep = workspace.sourceCount();
    for (size_t i = 0; i < workspace.sourceCount(); ++i) {
        if (endsWith(workspace.sourceName(i), "Deep.kerml")) deep = i;
    }
    ASSERT_LT(deep, workspace.sourceCount());
    TempDir before;
    TempDir after;
    EXPECT_TRUE(workspace.exportXmi(before.path().string(), nameBased()).empty());
    ASSERT_TRUE(fs::exists(before.path() / "sub" / "Deep.kermlx"));

    workspace.replaceSource(deep, "package Deep { classifier Down; }");
    workspace.resolve();
    const Errors errors = workspace.exportXmi(after.path().string(), nameBased());
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    EXPECT_TRUE(fs::exists(after.path() / "sub" / "Deep.kermlx")) << "the nested relative path is kept";
    EXPECT_FALSE(fs::exists(after.path() / "Deep.kermlx"));
    EXPECT_EQ(ConformanceTest::readFile(before.path() / "sub" / "Deep.kermlx"), ConformanceTest::readFile(after.path() / "sub" / "Deep.kermlx"))
        << "the ids do not change";
}

// An XMI file in the shape of the library files: a namespace with the package P, which owns the part definition Q.
const char* const PackageXmi =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<sysml:Namespace xmi:version=\"2.0\" xmlns:xmi=\"http://www.omg.org/XMI\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
    "xmlns:sysml=\"https://www.omg.org/spec/SysML/20250201\" xmi:id=\"00000000-0000-4000-8000-0000000000a1\" "
    "elementId=\"00000000-0000-4000-8000-0000000000a1\">\n"
    "  <ownedRelationship xsi:type=\"sysml:OwningMembership\" xmi:id=\"00000000-0000-4000-8000-0000000000a2\" elementId=\"00000000-0000-4000-8000-0000000000a2\">\n"
    "    <ownedRelatedElement xsi:type=\"sysml:Package\" xmi:id=\"00000000-0000-4000-8000-0000000000a3\" elementId=\"00000000-0000-4000-8000-0000000000a3\" declaredName=\"P\">\n"
    "      <ownedRelationship xsi:type=\"sysml:OwningMembership\" xmi:id=\"00000000-0000-4000-8000-0000000000a4\" elementId=\"00000000-0000-4000-8000-0000000000a4\">\n"
    "        <ownedRelatedElement xsi:type=\"sysml:PartDefinition\" xmi:id=\"00000000-0000-4000-8000-0000000000a5\" elementId=\"00000000-0000-4000-8000-0000000000a5\" declaredName=\"Q\"/>\n"
    "      </ownedRelationship>\n"
    "    </ownedRelatedElement>\n"
    "  </ownedRelationship>\n"
    "</sysml:Namespace>\n";

// Point 2: an XMI source keeps the key of its own file in a collision with a text source, whichever of them was loaded first.
TEST(XmiExportLastReview, XmiSourceWinsTheCollisionWhicheverWasLoadedFirst) {
    TempDir directory;
    const fs::path base = directory.path() / "src";
    std::map<std::string, std::string> firstOrder;   // file -> text, for the order XMI first
    for (const bool xmiFirst : {true, false}) {
        SCOPED_TRACE(xmiFirst ? "XMI source first" : "text source first");
        Workspace workspace;
        const auto addXmi = [&] { workspace.addText(PackageXmi, (base / "B.sysmlx").string(), SourceLanguage::Xmi, 0); };
        const auto addText = [&] { workspace.addText("package L { part def Base; }", (base / "B.sysml").string(), SourceLanguage::SysML, 0); };
        if (xmiFirst) {
            addXmi();
            addText();
        } else {
            addText();
            addXmi();
        }
        const size_t model = workspace.addText("package M { part def D :> L::Base; part def E :> P::Q; }", (base / "m.sysml").string(), SourceLanguage::SysML, 1);
        workspace.resolve();
        for (const auto& info : workspace.unresolvedReferences()) ADD_FAILURE() << "unresolved: " << info.name << " in " << info.sourceName;
        ASSERT_TRUE(workspace.unresolvedReferences().empty());

        XmiWriteOptions options = nameBased();
        options.exportRoot = base.string();
        TempDir out;
        const Errors errors = workspace.exportXmi(out.path().string(), options);
        EXPECT_EQ(warningsWith(errors, "another source"), 1u) << allErrors(errors);
        EXPECT_EQ(errors.size(), 1u) << allErrors(errors);
        const std::string xmiFile = ConformanceTest::readFile(out.path() / "B.sysmlx");
        const std::string textFile = ConformanceTest::readFile(out.path() / "B_2.sysmlx");
        EXPECT_NE(xmiFile.find("declaredName=\"P\""), std::string::npos) << "the XMI source keeps its file";
        EXPECT_NE(textFile.find("declaredName=\"L\""), std::string::npos) << "the text source is renamed";
        EXPECT_EQ(hrefFileNames(ConformanceTest::readFile(out.path() / "m.sysmlx")), (std::set<std::string>{"B.sysmlx", "B_2.sysmlx"}));
        const std::map<std::string, std::string> files = {{"B.sysmlx", xmiFile}, {"B_2.sysmlx", textFile}, {"m.sysmlx", ConformanceTest::readFile(out.path() / "m.sysmlx")}};
        if (xmiFirst) {
            firstOrder = files;
        } else {
            EXPECT_EQ(files, firstOrder) << "the keys, and with them the ids, do not depend on the order";
        }

        // writeXmi(): the references lead to the real file of the XMI source, and the text source is the renamed one
        TempDir single;
        const Errors written = workspace.writeXmi(model, (single.path() / "m.sysmlx").string(), options);
        EXPECT_EQ(warningsWith(written, "another source"), 1u) << allErrors(written);
        EXPECT_EQ(hrefFileNames(ConformanceTest::readFile(single.path() / "m.sysmlx")), (std::set<std::string>{"B.sysmlx", "B_2.sysmlx"}));
        EXPECT_EQ(allXmiIds(ConformanceTest::readFile(single.path() / "m.sysmlx")), allXmiIds(files.at("m.sysmlx"))) << "writeXmi() gives the model the ids of exportXmi()";
    }
}

// Point 3: the reason of a collision names the holder of the key: a source that was renamed before is not "a name that differs in case", and two
// sources with the same path are not told apart by directories they do not have.
TEST(XmiExportLastReview, CollisionReasonsFollowTheHolderOfTheKey) {
    const fs::path root = fs::temp_directory_path().root_path();
    {
        Workspace workspace;
        workspace.addText("package A { }", (root / "xq_one" / "a.sysml").string(), SourceLanguage::SysML, 1);
        workspace.addText("package B { }", (root / "xq_two" / "a.sysml").string(), SourceLanguage::SysML, 1);
        workspace.addText("package C { }", (root / "xq_three" / "a_2.sysml").string(), SourceLanguage::SysML, 1);
        TempDir out;
        const Errors errors = workspace.exportXmi(out.path().string());
        ASSERT_EQ(errors.size(), 2u) << allErrors(errors);
        EXPECT_NE(errors[0]->description().find("same file name"), std::string::npos) << describe(errors[0]);
        EXPECT_NE(errors[1]->description().find("renamed"), std::string::npos) << describe(errors[1]);
        EXPECT_EQ(errors[1]->description().find("differ in case"), std::string::npos) << describe(errors[1]);
        EXPECT_TRUE(fs::exists(out.path() / "a.sysmlx"));
        EXPECT_TRUE(fs::exists(out.path() / "a_2.sysmlx"));
        EXPECT_TRUE(fs::exists(out.path() / "a_2_2.sysmlx"));
    }
    {
        // the same path twice
        Workspace workspace;
        workspace.addText("package A { }", (root / "xq_one" / "a.sysml").string(), SourceLanguage::SysML, 1);
        workspace.addText("package B { }", (root / "xq_one" / "a.sysml").string(), SourceLanguage::SysML, 1);
        TempDir out;
        const Errors errors = workspace.exportXmi(out.path().string());
        ASSERT_EQ(errors.size(), 1u) << allErrors(errors);
        EXPECT_NE(errors[0]->description().find("same path"), std::string::npos) << describe(errors[0]);
        EXPECT_EQ(errors[0]->description().find("neither is below"), std::string::npos) << describe(errors[0]);
    }
}

#ifdef _WIN32
// The names (UTF-8) as the narrow names of the system, or nothing if its code page cannot hold them (the names of the sources are narrow).
std::optional<std::pair<std::string, std::string>> narrowNames(const std::u8string& a, const std::u8string& b) {
    try {
        const fs::path pathA(a);
        const fs::path pathB(b);
        const std::string narrowA = pathA.string();
        const std::string narrowB = pathB.string();
        if (narrowA.empty() || narrowB.empty() || fs::path(narrowA) != pathA || fs::path(narrowB) != pathB) return std::nullopt;
        return std::make_pair(narrowA, narrowB);
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

// The files "<a>.sysml" and "<b>.sysml" (the names are given as UTF-8 bytes): how many collisions the export reports, and how many files it writes.
std::optional<std::pair<size_t, size_t>> exportOfNames(const std::vector<unsigned char>& a, const std::vector<unsigned char>& b) {
    std::u8string nameA;
    std::u8string nameB;
    for (const unsigned char c : a) nameA += static_cast<char8_t>(c);
    for (const unsigned char c : b) nameB += static_cast<char8_t>(c);
    nameA += u8"x.sysml";
    nameB += u8"x.sysml";
    const auto narrow = narrowNames(nameA, nameB);
    if (!narrow) return std::nullopt;
    Workspace workspace;
    workspace.addText("package A { }", narrow->first, SourceLanguage::SysML, 1);
    workspace.addText("package B { }", narrow->second, SourceLanguage::SysML, 1);
    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string());
    size_t files = 0;
    for (const auto& entry : fs::directory_iterator(out.path())) {
        if (entry.is_regular_file()) ++files;
    }
    return std::make_pair(warningsWith(errors, "another source"), files);
}

// Point 4: on Windows the case is folded the way the file system does, so two names that it takes for one are a collision (and the second
// export does not silently replace the first). The names need a code page that holds the characters (Greek, Cyrillic): without one the
// test is skipped.
TEST(XmiExportLastReview, CaseFoldingFollowsTheFileSystemOfWindows) {
    struct Pair {
        const char* what;
        std::vector<unsigned char> a;
        std::vector<unsigned char> b;
        size_t collisions;
    };
    const Pair pairs[] = {
        {"Ghe with upstroke U+0490 / U+0491", {0xD2, 0x90}, {0xD2, 0x91}, 1},
        {"Alpha with tonos U+0386 / U+03AC", {0xCE, 0x86}, {0xCE, 0xAC}, 1},
        {"Sigma U+03A3 / small sigma U+03C3", {0xCE, 0xA3}, {0xCF, 0x83}, 1},
        // (NTFS keeps the final sigma apart: its upper case table maps U+03C2 to itself, checked by creating the files; so does the system's
        // upper casing, which the program uses)
        {"Sigma U+03A3 / final sigma U+03C2 are two names on NTFS", {0xCE, 0xA3}, {0xCF, 0x82}, 0},
        {"small sigma U+03C3 / final sigma U+03C2 are two names on NTFS", {0xCF, 0x83}, {0xCF, 0x82}, 0},
        {"Cyrillic Ya U+042F / ya U+044F (table of the program)", {0xD0, 0xAF}, {0xD1, 0x8F}, 1},
        {"Latin Extended-B: A with caron U+01CD / U+01CE", {0xC7, 0x8D}, {0xC7, 0x8E}, 1},
        {"Latin Extended Additional U+1E00 / U+1E01", {0xE1, 0xB8, 0x80}, {0xE1, 0xB8, 0x81}, 1},
        {"fullwidth A U+FF21 / a U+FF41", {0xEF, 0xBC, 0xA1}, {0xEF, 0xBD, 0x81}, 1},
        {"different letters (alpha, beta)", {0xCE, 0xB1}, {0xCE, 0xB2}, 0},
    };
    bool ran = false;
    for (const auto& pair : pairs) {
        SCOPED_TRACE(pair.what);
        const auto result = exportOfNames(pair.a, pair.b);
        if (!result) continue;
        ran = true;
        EXPECT_EQ(result->first, pair.collisions);
        EXPECT_EQ(result->second, 2u) << "both sources are written, neither replaces the other";
    }
    if (!ran) GTEST_SKIP() << "the narrow encoding of the system cannot hold any of the file names";
}
#endif

// Point 5: a name that is no file name (an XMI source called ".") is not a key: it is called source_<n>.sysmlx, and a WARNING says so.
TEST(XmiExportLastReview, ADotIsNoKey) {
    Workspace workspace;
    workspace.addText(ConnectorXmi, ".", SourceLanguage::Xmi, 0);
    workspace.resolve();
    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string(), nameBased());
    EXPECT_EQ(errors.size(), 1u) << allErrors(errors);
    EXPECT_EQ(warningsWith(errors, "no file name"), 1u) << allErrors(errors);
    std::set<std::string> names;
    for (const auto& entry : fs::directory_iterator(out.path())) names.insert(entry.path().filename().string());
    EXPECT_EQ(names, (std::set<std::string>{"source_1.sysmlx"}));
}

// Point 6: a relative root with an absolute source (or the other way round) depends on the working directory: a WARNING says so; both absolute
// or both relative is fine.
TEST(XmiExportLastReview, MixedRelativeAndAbsoluteRootIsWarnedAbout) {
    TempDir directory;
    const fs::path absolute = directory.path() / "proj";
    const auto exportWith = [&](const std::string& sourceName, const std::string& root) {
        Workspace workspace;
        workspace.addText("package A { }", sourceName, SourceLanguage::SysML, 1);
        XmiWriteOptions options = nameBased();
        options.exportRoot = root;
        TempDir out;
        return workspace.exportXmi(out.path().string(), options);
    };
    const Errors mixed = exportWith("sub/a.sysml", absolute.string());
    EXPECT_EQ(warningsWith(mixed, "working directory"), 1u) << allErrors(mixed);
    const Errors mixedTheOtherWay = exportWith((absolute / "a.sysml").string(), "proj");
    EXPECT_EQ(warningsWith(mixedTheOtherWay, "working directory"), 1u) << allErrors(mixedTheOtherWay);
    EXPECT_TRUE(exportWith("sub/a.sysml", "sub").empty());
    EXPECT_TRUE(exportWith((absolute / "a.sysml").string(), absolute.string()).empty());

    // writeXmi() says it as well
    Workspace workspace;
    const size_t source = workspace.addText("package A { }", "sub/a.sysml", SourceLanguage::SysML, 1);
    XmiWriteOptions options = nameBased();
    options.exportRoot = absolute.string();
    TempDir out;
    const Errors written = workspace.writeXmi(source, (out.path() / "a.sysmlx").string(), options);
    EXPECT_EQ(warningsWith(written, "working directory"), 1u) << allErrors(written);
}

// Point 7: the temporary directories of the tests are created exclusively, with the process id in the name.
TEST(XmiExportLastReview, TempDirsAreDistinctAndNamedByTheProcess) {
    TempDir a;
    TempDir b;
    EXPECT_NE(a.path(), b.path());
    EXPECT_TRUE(fs::is_directory(a.path()));
    EXPECT_TRUE(fs::is_directory(b.path()));
    EXPECT_EQ(a.path().filename().string().find("xe" + hex(processId()) + "_"), 0u) << a.path();
    EXPECT_TRUE(fs::is_empty(a.path())) << "a directory that exists is never taken over";
}

// ---------------------------------------------------------------------------------------------------------------------
// Final review: same-named XMI sources in writeXmi(), synthesized names, one warning per root
// ---------------------------------------------------------------------------------------------------------------------

// The file parts of all hrefs of an XMI text (everything before the '#'), as written.
std::set<std::string> hrefFiles(const std::string& xml) {
    std::set<std::string> files;
    for (const auto& tag : startTags(xml)) {
        const std::string href = attributeOf(tag, "href");
        if (!href.empty()) files.insert(href.substr(0, href.find('#')));
    }
    return files;
}

// The XMI text of PackageXmi for another package: the ids, the package and the part definition differ.
std::string otherPackageXmi() {
    std::string text = PackageXmi;
    for (size_t at = text.find("0000000000a"); at != std::string::npos; at = text.find("0000000000a", at)) text[at + 10] = 'b';
    const auto replace = [&](const std::string& from, const std::string& to) {
        const size_t at = text.find(from);
        ASSERT_NE(at, std::string::npos);
        text.replace(at, from.size(), to);
    };
    replace("declaredName=\"P\"", "declaredName=\"R\"");
    replace("declaredName=\"Q\"", "declaredName=\"S\"");
    return text;
}

// N1: two XMI sources with the same file name in different directories, which nothing tells apart: writeXmi() references the real files of both
// (the key of the second one may get a number, its file does not).
TEST(XmiExportFinalReview, WriteXmiReferencesTheRealFilesOfSameNamedXmiSources) {
    TempDir directory;
    const fs::path src = directory.path() / "src";
    fs::create_directories(src / "x");
    fs::create_directories(src / "y");
    {
        std::ofstream(src / "x" / "model.sysmlx") << PackageXmi;
        std::ofstream(src / "y" / "model.sysmlx") << otherPackageXmi();
    }
    const auto build = [&](Workspace& workspace) {
        workspace.addFile((src / "x" / "model.sysmlx").string(), 0);
        workspace.addFile((src / "y" / "model.sysmlx").string(), 0);
        return workspace.addText("package M { part def D :> P::Q; part def E :> R::S; }", (src / "m.sysml").string(), SourceLanguage::SysML, 1);
    };
    Workspace workspace;
    const size_t model = build(workspace);
    workspace.resolve();
    for (const auto& info : workspace.unresolvedReferences()) ADD_FAILURE() << "unresolved: " << info.name << " in " << info.sourceName;
    ASSERT_TRUE(workspace.unresolvedReferences().empty());

    TempDir out;
    const fs::path file = out.path() / "m.sysmlx";
    const Errors errors = workspace.writeXmi(model, file.string());
    for (const auto& error : errors) EXPECT_EQ(error->errorType(), ErrorType::WARNING) << describe(error);
    const std::set<std::string> hrefs = hrefFiles(ConformanceTest::readFile(file));
    ASSERT_EQ(hrefs.size(), 2u) << allErrors(errors);
    std::set<fs::path> targets;
    for (const auto& href : hrefs) {
        const fs::path target = (out.path() / fs::path(href)).lexically_normal();
        EXPECT_TRUE(fs::exists(target)) << "dangling href " << href;
        std::error_code ec;
        targets.insert(fs::weakly_canonical(target, ec));
    }
    std::error_code ec;
    EXPECT_EQ(targets, (std::set<fs::path>{fs::weakly_canonical(src / "x" / "model.sysmlx", ec), fs::weakly_canonical(src / "y" / "model.sysmlx", ec)}));
    for (const auto& href : hrefs) EXPECT_EQ(href.find("model_2"), std::string::npos) << href;

    // a fresh workspace reads the written file together with the two files and resolves everything
    Workspace again;
    again.addFile((src / "x" / "model.sysmlx").string(), 0);
    again.addFile((src / "y" / "model.sysmlx").string(), 0);
    again.addFile(file.string(), 1);
    again.resolve();
    EXPECT_TRUE(again.errors().empty()) << allErrors(again.errors());
    for (const auto& info : again.unresolvedReferences()) ADD_FAILURE() << "unresolved: " << info.name << " in " << info.sourceName;

    // the export puts the second one to a key of its own, as before (one directory)
    TempDir exported;
    Workspace third;
    build(third);
    third.resolve();
    const Errors exportErrors = third.exportXmi(exported.path().string());
    EXPECT_EQ(warningsWith(exportErrors, "another source"), 1u) << allErrors(exportErrors);
    EXPECT_TRUE(fs::exists(exported.path() / "model.sysmlx"));
    EXPECT_TRUE(fs::exists(exported.path() / "model_2.sysmlx"));
}

// The same for two libraries loaded from different directories with the same relative path.
TEST(XmiExportFinalReview, WriteXmiReferencesTheRealFilesOfSameNamedLibraryFiles) {
    TempDir directory;
    for (const char* name : {"l1", "l2"}) fs::create_directories(directory.path() / name / "sub");
    std::ofstream(directory.path() / "l1" / "sub" / "m.sysml") << "package A1 { part def T1; }";
    std::ofstream(directory.path() / "l2" / "sub" / "m.sysml") << "package A2 { part def T2; }";
    Workspace workspace;
    workspace.loadLibrary((directory.path() / "l1").string());
    workspace.loadLibrary((directory.path() / "l2").string());
    const size_t model = workspace.addText("package M { part def X :> A1::T1; part def Y :> A2::T2; }", (directory.path() / "model.sysml").string(), SourceLanguage::SysML, 1);
    workspace.resolve();
    ASSERT_TRUE(workspace.unresolvedReferences().empty());
    TempDir out;
    const Errors errors = workspace.writeXmi(model, (out.path() / "model.sysmlx").string());
    for (const auto& error : errors) EXPECT_EQ(error->errorType(), ErrorType::WARNING) << describe(error);
    std::set<fs::path> targets;
    for (const auto& href : hrefFiles(ConformanceTest::readFile(out.path() / "model.sysmlx"))) {
        std::error_code ec;
        targets.insert(fs::weakly_canonical((out.path() / fs::path(href)).lexically_normal(), ec));
    }
    std::error_code ec;
    EXPECT_EQ(targets, (std::set<fs::path>{fs::weakly_canonical(directory.path() / "l1" / "sub" / "m.sysmlx", ec),
                                           fs::weakly_canonical(directory.path() / "l2" / "sub" / "m.sysmlx", ec)}));
}

// A synthesized name source_<n> never makes a real file of that name the one that is renamed.
TEST(XmiExportFinalReview, SynthesizedNamesAreAssignedAfterTheRealOnes) {
    Workspace workspace;
    workspace.addText(ConnectorXmi, ".", SourceLanguage::Xmi, 0);
    workspace.addText(otherPackageXmi(), "source_1.sysmlx", SourceLanguage::Xmi, 0);
    workspace.resolve();
    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string(), nameBased());
    EXPECT_EQ(warningsWith(errors, "no file name"), 1u) << allErrors(errors);
    EXPECT_NE(ConformanceTest::readFile(out.path() / "source_1.sysmlx").find("declaredName=\"R\""), std::string::npos) << "the real file keeps its name";
    EXPECT_TRUE(fs::exists(out.path() / "source_1_2.sysmlx")) << "the synthesized one is renamed";
}

// N2: a library of a relative directory with an absolute export root: one WARNING for the pair, with the number of the sources.
TEST(XmiExportFinalReview, MixedRootsAreWarnedAboutOncePerRoot) {
    TempDir directory;
    const fs::path library = directory.path() / "lib";
    fs::create_directories(library);
    for (const char* name : {"a", "b", "c", "d", "e"}) {
        std::ofstream(library / (std::string(name) + ".sysml")) << "package P" << name << " { part def T" << name << "; }";
    }
    std::error_code ec;
    const fs::path relative = fs::relative(library, fs::current_path(), ec);
    if (ec || relative.empty() || relative.is_absolute()) GTEST_SKIP() << "no relative path from the working directory to the temporary directory";
    Workspace workspace;
    workspace.loadLibrary(relative.string());
    ASSERT_EQ(workspace.sourceCount(), 5u);
    const size_t model = workspace.addText("package M { part def X :> Pa::Ta; part def Y :> Pb::Tb; }", "model.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    ASSERT_TRUE(workspace.unresolvedReferences().empty());

    XmiWriteOptions options = nameBased();
    options.exportRoot = (directory.path() / "proj").string();
    TempDir out;
    const Errors errors = workspace.exportXmi(out.path().string(), options);
    EXPECT_EQ(warningsWith(errors, "working directory"), 1u) << allErrors(errors, 20);
    EXPECT_EQ(warningsWith(errors, "6 sources"), 1u) << allErrors(errors, 20);
    EXPECT_EQ(warningsWith(errors, "export root"), 1u) << allErrors(errors, 20);

    // writeXmi(): the written source and the two it refers to, in one warning
    TempDir single;
    const Errors written = workspace.writeXmi(model, (single.path() / "model.sysmlx").string(), options);
    EXPECT_EQ(warningsWith(written, "working directory"), 1u) << allErrors(written, 20);
    EXPECT_EQ(warningsWith(written, "3 sources"), 1u) << allErrors(written, 20);
}


}  // namespace
