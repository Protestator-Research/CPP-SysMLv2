// Workspace::addTexts (parallel loading) and the cancellation of a load.
//
// The whole standard library is loaded as text and as XMI with addTexts() on 1, 2 and 8 threads and, as the reference, with one addText()
// per file; then resolve(). Everything that can be seen of the result must be the same: the names and indices of the sources, their errors,
// the unresolved references, the number of resolved references, what the references resolved to (and in which order the specializations
// of a type are), and the qualified names of all elements. Each variant is loaded once (the snapshot is taken, the workspace dropped), the
// load times are printed.
#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <sysmlv2/Workspace.h>

#include "../support/TestHelpers.h"

#ifndef SYSML_LIBRARY_DIR
#error "SYSML_LIBRARY_DIR must be defined by CMake"
#endif
#ifndef SYSML_LIBRARY_XMI_DIR
#error "SYSML_LIBRARY_XMI_DIR must be defined by CMake"
#endif

namespace {

using SysMLv2::Files::SourceLanguage;
using SysMLv2::Files::TextInput;
using SysMLv2::Files::Workspace;
namespace fs = std::filesystem;

/// The files of the library in the order of Workspace::loadLibrary() (sorted by path), as inputs.
std::vector<TextInput> libraryInputs(bool xmi) {
    std::vector<std::string> paths;
    for (fs::recursive_directory_iterator it(xmi ? SYSML_LIBRARY_XMI_DIR : SYSML_LIBRARY_DIR), end; it != end; ++it) {
        if (!it->is_regular_file()) continue;
        const auto extension = it->path().extension().string();
        const bool wanted = xmi ? (extension == ".kermlx" || extension == ".sysmlx") : (extension == ".kerml" || extension == ".sysml");
        if (wanted) paths.push_back(it->path().string());
    }
    std::sort(paths.begin(), paths.end());
    std::vector<TextInput> inputs;
    for (const auto& path : paths) inputs.push_back({ConformanceTest::readFile(path), path, SourceLanguage::Auto, 0});
    return inputs;
}

/// Everything that can be seen of a loaded and resolved workspace.
struct Snapshot {
    std::vector<size_t> indices;
    std::vector<std::string> names;
    std::vector<std::string> errors;
    std::vector<std::string> unresolved;
    size_t resolvedCount = 0;
    std::vector<std::string> generals;
    std::vector<std::string> qualifiedNames;
    double loadSeconds = 0;
    double resolveSeconds = 0;
};

Snapshot snapshotOf(Workspace& ws, std::vector<size_t> indices, double loadSeconds, double resolveSeconds) {
    Snapshot snapshot;
    snapshot.indices = std::move(indices);
    snapshot.loadSeconds = loadSeconds;
    snapshot.resolveSeconds = resolveSeconds;
    for (size_t source = 0; source < ws.sourceCount(); ++source) {
        snapshot.names.push_back(ws.sourceName(source) + "#" + std::to_string(ws.sourceLevel(source)));
        for (const auto& error : ws.errors(source)) {
            snapshot.errors.push_back(std::to_string(source) + ":" + std::to_string(error->getLine()) + ":" + std::to_string(error->getColumn()) +
                                      ":" + error->description());
        }
    }
    for (const auto& info : ws.unresolvedReferences()) {
        snapshot.unresolved.push_back(std::to_string(info.source) + ":" + info.sourceName + ":" + std::to_string(info.line) + ":" +
                                      std::to_string(info.column) + ":" + info.name + ":" + std::to_string(static_cast<int>(info.kind)) + ":" +
                                      std::to_string(static_cast<int>(info.role)));
    }
    snapshot.resolvedCount = ws.resolvedReferenceCount();
    const auto elements = ws.elements();
    snapshot.generals = ConformanceTest::resolvedGenerals(elements);
    for (const auto& element : elements) snapshot.qualifiedNames.push_back(ConformanceTest::qualifiedNameOf(element));
    std::sort(snapshot.qualifiedNames.begin(), snapshot.qualifiedNames.end());
    return snapshot;
}

/// Loads the library: threads == 0 with one addText() per file, else with addTexts() on that many threads.
Snapshot load(bool xmi, unsigned threads) {
    auto inputs = libraryInputs(xmi);
    Workspace ws;
    std::vector<size_t> indices;
    const auto start = std::chrono::steady_clock::now();
    if (threads == 0) {
        for (auto& input : inputs) indices.push_back(ws.addText(std::move(input.text), std::move(input.name), input.language, input.level));
    } else {
        indices = ws.addTexts(std::move(inputs), threads);
    }
    const auto loaded = std::chrono::steady_clock::now();
    ws.resolve();
    const auto resolved = std::chrono::steady_clock::now();
    return snapshotOf(ws, std::move(indices), std::chrono::duration<double>(loaded - start).count(),
                      std::chrono::duration<double>(resolved - loaded).count());
}

void expectSame(const Snapshot& actual, const Snapshot& expected, const std::string& what) {
    EXPECT_EQ(actual.indices, expected.indices) << what;
    EXPECT_EQ(actual.names, expected.names) << what;
    EXPECT_EQ(actual.errors, expected.errors) << what;
    EXPECT_EQ(actual.unresolved, expected.unresolved) << what;
    EXPECT_EQ(actual.resolvedCount, expected.resolvedCount) << what;
    ConformanceTest::expectSameLines(actual.generals, expected.generals, what + ", generals");
    EXPECT_EQ(actual.qualifiedNames.size(), expected.qualifiedNames.size()) << what;
    EXPECT_TRUE(actual.qualifiedNames == expected.qualifiedNames) << what << ": the qualified names differ";
}

void checkLibrary(bool xmi) {
    const std::string format = xmi ? "XMI" : "text";
    const Snapshot reference = load(xmi, 0);
    ASSERT_GT(reference.names.size(), 50u);
    // (the references of the XMI files are resolved by id while linking, which resolvedReferenceCount() does not count)
    if (!xmi) ASSERT_GT(reference.resolvedCount, 1000u);
    ASSERT_GT(reference.qualifiedNames.size(), 10000u);
    ASSERT_FALSE(reference.generals.empty());
    std::cout << "[  INFO  ] " << format << " library, " << reference.names.size() << " files, " << reference.resolvedCount
              << " resolved, " << reference.unresolved.size() << " unresolved; one addText per file: load " << reference.loadSeconds
              << " s, resolve " << reference.resolveSeconds << " s" << std::endl;
    for (const unsigned threads : {1u, 2u, 8u}) {
        const Snapshot parallel = load(xmi, threads);
        std::cout << "[  INFO  ] " << format << " library, addTexts on " << threads << " thread(s): load " << parallel.loadSeconds
                  << " s, resolve " << parallel.resolveSeconds << " s" << std::endl;
        expectSame(parallel, reference, format + ", " + std::to_string(threads) + " threads");
    }
}

TEST(ParallelLoading, TextLibraryEqualsAddTextOneByOne) { checkLibrary(false); }

TEST(ParallelLoading, XmiLibraryEqualsAddTextOneByOne) { checkLibrary(true); }

TEST(ParallelLoading, ProgressRisesByOneAndEndsAtTotal) {
    auto inputs = libraryInputs(false);
    inputs.resize(40);
    for (const unsigned threads : {1u, 4u}) {
        Workspace ws;
        std::vector<std::pair<size_t, size_t>> calls;
        std::atomic<int> inside{0};
        std::atomic<bool> overlapped{false};
        ws.addTexts(inputs, threads, [&](size_t done, size_t total) {
            if (inside.fetch_add(1) != 0) overlapped = true;
            calls.emplace_back(done, total);   // (no lock: the calls must not overlap)
            std::this_thread::yield();
            inside.fetch_sub(1);
        });
        EXPECT_FALSE(overlapped) << threads;
        ASSERT_EQ(calls.size(), inputs.size()) << threads;
        for (size_t i = 0; i < calls.size(); ++i) EXPECT_EQ(calls[i], std::make_pair(i + 1, inputs.size())) << threads;
        EXPECT_EQ(ws.sourceCount(), inputs.size());
    }
}

TEST(ParallelLoading, CancelFromTheProgressCallbackLeavesTheWorkspaceUnchanged) {
    auto inputs = libraryInputs(false);
    inputs.resize(30);
    Workspace ws;
    ws.addText("package First;", "first.sysml");
    auto cancelled = std::make_shared<std::atomic<bool>>(false);
    ws.setCancellation(cancelled);
    for (const unsigned threads : {1u, 2u, 4u}) {
        EXPECT_THROW(ws.addTexts(inputs, threads, [&](size_t done, size_t) { if (done == 1) cancelled->store(true); }),
                     SysMLv2::Files::ParseCancelled) << threads;
        EXPECT_EQ(ws.sourceCount(), 1u) << threads;
        cancelled->store(false);
    }
    // nothing of the failed calls is left: a call that is not cancelled gives the sources at the indices behind the first one
    const auto indices = ws.addTexts(inputs, 4);
    ASSERT_EQ(indices.size(), inputs.size());
    EXPECT_EQ(indices.front(), 1u);
    EXPECT_EQ(indices.back(), inputs.size());
    EXPECT_EQ(ws.sourceCount(), inputs.size() + 1);
    ws.resolve();
    EXPECT_GT(ws.resolvedReferenceCount(), 0u);
}

TEST(ParallelLoading, DeadlineInOneInputLeavesTheWorkspaceUnchanged) {
    // (a text with many tokens: the deadline is looked at every few hundred tokens)
    std::string big = "package Big {";
    for (int i = 0; i < 3000; ++i) big += " part def P" + std::to_string(i) + " { attribute a" + std::to_string(i) + "; }";
    big += " }";
    std::vector<TextInput> inputs = {{"package Small;", "small.sysml", SourceLanguage::Auto, 0}, {big, "big.sysml", SourceLanguage::Auto, 0}};
    Workspace ws;
    ws.addText("package First;", "first.sysml");
    ws.setParseDeadline(std::chrono::steady_clock::now() - std::chrono::seconds(1));
    for (const unsigned threads : {1u, 2u}) {
        bool timeout = false;
        try {
            ws.addTexts(inputs, threads);
        } catch (const SysMLv2::Files::ParseCancelled&) {
            ADD_FAILURE() << "a deadline is no cancellation";
        } catch (const SysMLv2::Files::ParseTimeout&) {
            timeout = true;
        }
        EXPECT_TRUE(timeout) << threads;
        EXPECT_EQ(ws.sourceCount(), 1u) << threads;
    }
    ws.clearParseDeadline();
    EXPECT_EQ(ws.addTexts(inputs, 2), (std::vector<size_t>{1, 2}));
    EXPECT_EQ(ws.sourceCount(), 3u);
}

}  // namespace
