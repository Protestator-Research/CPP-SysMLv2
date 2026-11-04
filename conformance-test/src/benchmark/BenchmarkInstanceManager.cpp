//
// Benchmark of the InstanceManager and of the Workspace on the standard library (not a test: it is not registered with CTest).
//
// Measuring points (the median of the runs, in milliseconds; a Debug build only gives relative figures):
//   1  InstanceManager::parseModel of a model that imports ISQ, SI and ScalarValues and uses part, port and action
//   2  a second parseModel on the same InstanceManager
//   3  appendNonStandardLibrary after the model was parsed
//   4  Workspace: the whole text library with loadLibrary and one resolve(), against the same files added one by one with a resolve()
//      after every file
//   5  Workspace: the library files that point 1 loaded, once as text (the embedded sources) and once as XMI (the embedded XMI files),
//      each plus one resolve(); reading/parsing and resolving are measured separately
//   6  Workspace as SysMD uses it: the whole text library at level 0 (addText + resolve), three document blocks at level 1000 (addText +
//      resolve), then replaceSource of all three blocks and resolve() (replace and resolve measured separately), and a resolve() without
//      any change
//   6x The same with the XMI library (the embedded XMI files) at level 0 and the same text blocks at level 1000
//
//   7  Workspace::addTexts of the whole library (text, then XMI) on 1 to 16 threads, against one addText per file; each followed by a
//      resolve() whose counts are printed (they must be the same in every row)
//
// Usage: conformance-benchmark [--runs=N] [--only=1,2,3,4,5,6,6x,7] [--modes=text,text-reuse,xmi,xmi-reuse]
//   (the modes are the configurations of the InstanceManager for points 1 to 3: the format of the standard library, and "reuse" keeps it
//   between the models)
//
#include <sysmlv2/service/implementation/InstanceManager.h>
#include <sysmlv2/ParserError.h>
#include <sysmlv2/Workspace.h>
#include <kerml/root/elements/Element.h>

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(Library);
CMRC_DECLARE(LibraryXmi);

namespace
{
    using Clock = std::chrono::steady_clock;

    const char* const BenchmarkModel = R"(package BenchmarkModel {
    private import ISQ::*;
    private import SI::*;
    private import ScalarValues::*;

    port def PowerPort {
        attribute voltage : ElectricPotentialDifferenceValue;
        attribute current : ElectricCurrentValue;
    }
    action def Drive {
        in attribute target : LengthValue;
        out attribute distance : LengthValue;
    }
    part def Engine {
        attribute power : PowerValue;
        port supply : PowerPort;
    }
    part def Vehicle {
        attribute mass : MassValue;
        attribute topSpeed : SpeedValue;
        attribute name : String;
        part engine : Engine;
        port power : PowerPort;
        perform action drive : Drive;
    }
    part fleet : Vehicle[3];
})";

    // Point 6: three document blocks that refer to each other (the second variant has slightly changed text).
    std::vector<std::string> documentBlocks(int variant)
    {
        const std::string extra = variant == 0 ? "" : " attribute extra" + std::to_string(variant) + " : Real;";
        return {
            "package DocOne { private import ISQ::*; private import SI::*; private import ScalarValues::*;"
            " port def PowerPort { attribute voltage : ElectricPotentialDifferenceValue; attribute current : ElectricCurrentValue; }"
            " part def Engine { attribute power : PowerValue; port supply : PowerPort;" + extra + " } }",
            "package DocTwo { private import ISQ::*; private import ScalarValues::*; private import DocOne::*;"
            " part def Vehicle { attribute mass : MassValue; attribute name : String; part engine : Engine; port power : PowerPort;" + extra + " } }",
            "package DocThree { private import ISQ::*; private import SI::*; private import DocOne::*; private import DocTwo::*;"
            " part fleet : Vehicle[3] { attribute topSpeed : SpeedValue; } part spare : Engine; attribute total : LengthValue;" + extra + " }"};
    }

    const char* const BenchmarkLibrary = "package BenchmarkLibrary { private import ScalarValues::*; attribute def Gadget { attribute weight : Real; } }";

    double milliseconds(Clock::duration duration)
    {
        return std::chrono::duration<double, std::milli>(duration).count();
    }

    template <class F>
    double timed(F&& function)
    {
        const auto start = Clock::now();
        function();
        return milliseconds(Clock::now() - start);
    }

    double median(std::vector<double> values)
    {
        if (values.empty())
            return 0;
        std::sort(values.begin(), values.end());
        const std::size_t middle = values.size() / 2;
        return values.size() % 2 == 1 ? values[middle] : (values[middle - 1] + values[middle]) / 2;
    }

    void report(const std::string& name, const std::vector<double>& runs)
    {
        std::cout << std::left << std::setw(58) << name << std::right << std::setw(12) << std::fixed << std::setprecision(1) << median(runs)
                  << " ms   (";
        for (std::size_t index = 0; index < runs.size(); ++index)
            std::cout << (index == 0 ? "" : " ") << std::setprecision(0) << runs[index];
        std::cout << ")" << std::endl;
    }

    /// The files of an embedded directory tree as pairs of the name of the file without extension (the names of the library files are
    /// unique) and the path.
    void collect(const cmrc::embedded_filesystem& fs, const std::string& directory, std::vector<std::pair<std::string, std::string>>& files)
    {
        for (const auto& entry : fs.iterate_directory(directory))
        {
            const std::string name = entry.filename();
            const std::string path = directory.empty() ? name : directory + "/" + name;
            if (entry.is_directory())
            {
                collect(fs, path, files);
            }
            else if (name.ends_with(".kerml") || name.ends_with(".sysml") || name.ends_with(".kermlx") || name.ends_with(".sysmlx"))
            {
                files.emplace_back(name.substr(0, name.rfind('.')), path);
            }
        }
    }

    /// The names of the top-level packages among the elements that the InstanceManager holds.
    std::set<std::string> topLevelPackages(const SysMLv2::API::InstanceManager& manager)
    {
        std::set<std::string> names;
        for (const auto& element : manager.getElements())
        {
            if (!element || element->getType().find("Package") == std::string::npos || !element->declaredName().has_value())
                continue;
            if (element->qualifiedName().has_value() && element->qualifiedName()->find("::") == std::string::npos)
                names.insert(element->declaredName().value());
        }
        return names;
    }

    std::string readEmbedded(const cmrc::embedded_filesystem& fs, const std::string& path)
    {
        const auto data = fs.open(path);
        return std::string(data.begin(), data.end());
    }

    std::vector<std::string> libraryFiles()
    {
        namespace fs = std::filesystem;
        std::vector<std::string> files;
        for (fs::recursive_directory_iterator it(SYSML_LIBRARY_DIR), end; it != end; ++it)
        {
            if (!it->is_regular_file())
                continue;
            const auto extension = it->path().extension().string();
            if (extension == ".kerml" || extension == ".sysml")
                files.push_back(it->path().string());
        }
        std::sort(files.begin(), files.end());
        return files;
    }

    /// Points 1 to 3 for one configuration of the InstanceManager.
    void pointsOneToThree(int runs, SysMLv2::API::StandardLibraryFormat format, bool reuse, const std::string& mode)
    {
        std::vector<double> parse, again, append;
        std::size_t errors = 0, unresolved = 0, elements = 0;
        for (int run = 0; run < runs; ++run)
        {
            SysMLv2::API::InstanceManager manager;
            manager.setStandardLibraryFormat(format);
            manager.setReuseStandardLibrary(reuse);
            parse.push_back(timed([&] { manager.parseModel(BenchmarkModel); }));
            errors = manager.getParserErrors().size();
            unresolved = manager.getUnresolvedReferences().size();
            elements = manager.getElements().size();
            again.push_back(timed([&] { manager.parseModel(BenchmarkModel); }));
            append.push_back(timed([&] { manager.appendNonStandardLibrary(BenchmarkLibrary); }));
        }
        report("1  InstanceManager::parseModel [" + mode + "]", parse);
        report("2  second parseModel on the same instance [" + mode + "]", again);
        report("3  appendNonStandardLibrary after parseModel [" + mode + "]", append);
        std::cout << "   (point 1: " << errors << " parser errors, " << unresolved << " unresolved references, " << elements << " elements)" << std::endl;
    }

    void pointFour(int runs)
    {
        const std::vector<std::string> files = libraryFiles();

        std::vector<double> whole, oneByOne;
        std::size_t wholeResolved = 0, wholeUnresolved = 0, stepResolved = 0, stepUnresolved = 0;
        for (int run = 0; run < runs; ++run)
        {
            {
                SysMLv2::Files::Workspace workspace;
                whole.push_back(timed([&] {
                    workspace.loadLibrary(SYSML_LIBRARY_DIR);
                    workspace.resolve();
                }));
                wholeResolved = workspace.resolvedReferenceCount();
                wholeUnresolved = workspace.unresolvedReferences().size();
            }
            {
                SysMLv2::Files::Workspace workspace;
                oneByOne.push_back(timed([&] {
                    for (const auto& file : files)
                    {
                        workspace.addFile(file);
                        workspace.resolve();
                    }
                }));
                stepResolved = workspace.resolvedReferenceCount();
                stepUnresolved = workspace.unresolvedReferences().size();
            }
        }
        report("4a Workspace: loadLibrary + one resolve (" + std::to_string(files.size()) + " files)", whole);
        report("4b Workspace: addFile + resolve after every file", oneByOne);
        std::cout << "   (4a: " << wholeResolved << " resolved, " << wholeUnresolved << " unresolved; 4b: " << stepResolved << " resolved, "
                  << stepUnresolved << " unresolved)" << std::endl;
    }

    void pointFive(int runs)
    {
        SysMLv2::API::InstanceManager manager;
        manager.parseModel(BenchmarkModel);
        const std::set<std::string> packages = topLevelPackages(manager);

        const auto textFs = cmrc::Library::get_filesystem();
        const auto xmiFs = cmrc::LibraryXmi::get_filesystem();
        std::vector<std::pair<std::string, std::string>> textFiles, xmiFiles;
        collect(textFs, "", textFiles);
        collect(xmiFs, "", xmiFiles);

        const auto select = [&packages](const std::vector<std::pair<std::string, std::string>>& all) {
            std::vector<std::string> paths;
            for (const auto& [name, path] : all)
            {
                if (packages.count(name) != 0)
                    paths.push_back(path);
            }
            return paths;
        };
        const std::vector<std::string> textPaths = select(textFiles);
        const std::vector<std::string> xmiPaths = select(xmiFiles);

        std::vector<double> textLoad, textResolve, xmiLoad, xmiResolve;
        std::size_t textResolved = 0, textUnresolved = 0, xmiResolved = 0, xmiUnresolved = 0;
        for (int run = 0; run < runs; ++run)
        {
            {
                SysMLv2::Files::Workspace workspace;
                textLoad.push_back(timed([&] {
                    for (const auto& path : textPaths)
                        workspace.addText(readEmbedded(textFs, path), path,
                                          path.ends_with(".kerml") ? SysMLv2::Files::SourceLanguage::KerML : SysMLv2::Files::SourceLanguage::SysML);
                }));
                textResolve.push_back(timed([&] { workspace.resolve(); }));
                textResolved = workspace.resolvedReferenceCount();
                textUnresolved = workspace.unresolvedReferences().size();
            }
            {
                SysMLv2::Files::Workspace workspace;
                xmiLoad.push_back(timed([&] {
                    for (const auto& path : xmiPaths)
                        workspace.addText(readEmbedded(xmiFs, path), path, SysMLv2::Files::SourceLanguage::Xmi);
                }));
                xmiResolve.push_back(timed([&] { workspace.resolve(); }));
                xmiResolved = workspace.resolvedReferenceCount();
                xmiUnresolved = workspace.unresolvedReferences().size();
            }
        }
        std::cout << "   (point 5 set: " << packages.size() << " top-level packages, " << textPaths.size() << " text files, " << xmiPaths.size()
                  << " XMI files)" << std::endl;
        report("5a Text: parse the files (addText)", textLoad);
        report("5b Text: resolve", textResolve);
        report("5c XMI:  read the files (addText)", xmiLoad);
        report("5d XMI:  resolve (link + name resolution)", xmiResolve);
        std::vector<double> textTotal, xmiTotal;
        for (std::size_t index = 0; index < textLoad.size(); ++index)
        {
            textTotal.push_back(textLoad[index] + textResolve[index]);
            xmiTotal.push_back(xmiLoad[index] + xmiResolve[index]);
        }
        report("5e Text: total", textTotal);
        report("5f XMI:  total", xmiTotal);
        std::cout << "   (text: " << textResolved << " resolved, " << textUnresolved << " unresolved; XMI: " << xmiResolved << " resolved, "
                  << xmiUnresolved << " unresolved)" << std::endl;
    }

    void pointSix(int runs, bool xmiLibrary = false)
    {
        const auto textFs = xmiLibrary ? cmrc::LibraryXmi::get_filesystem() : cmrc::Library::get_filesystem();
        std::vector<std::pair<std::string, std::string>> textFiles;
        collect(textFs, "", textFiles);
        const auto language = [xmiLibrary](const std::string& path) {
            if (xmiLibrary)
                return SysMLv2::Files::SourceLanguage::Xmi;
            return path.ends_with(".kerml") ? SysMLv2::Files::SourceLanguage::KerML : SysMLv2::Files::SourceLanguage::SysML;
        };
        const std::string point = xmiLibrary ? "6x" : "6";

        std::vector<double> library, libraryResolve, firstBlocks, firstResolve, replace, resolveAfter, resolveIdle;
        std::size_t unresolved = 0;
        for (int run = 0; run < runs; ++run)
        {
            SysMLv2::Files::Workspace workspace;
            library.push_back(timed([&] {
                for (const auto& [name, path] : textFiles)
                    workspace.addText(readEmbedded(textFs, path), path, language(path), 0);
            }));
            libraryResolve.push_back(timed([&] { workspace.resolve(); }));

            std::vector<size_t> slots;
            const auto blocks = documentBlocks(0);
            firstBlocks.push_back(timed([&] {
                for (std::size_t index = 0; index < blocks.size(); ++index)
                    slots.push_back(workspace.addText(blocks[index], "doc" + std::to_string(index), SysMLv2::Files::SourceLanguage::SysML, 1000));
            }));
            firstResolve.push_back(timed([&] { workspace.resolve(); }));
            unresolved = workspace.unresolvedReferences().size();

            const auto changed = documentBlocks(run + 1);
            replace.push_back(timed([&] {
                for (std::size_t index = 0; index < slots.size(); ++index)
                    workspace.replaceSource(slots[index], changed[index], SysMLv2::Files::SourceLanguage::SysML);
            }));
            resolveAfter.push_back(timed([&] { workspace.resolve(); }));
            unresolved = workspace.unresolvedReferences().size();
            resolveIdle.push_back(timed([&] { workspace.resolve(); }));
        }
        std::cout << "   (point " << point << " set: " << textFiles.size() << (xmiLibrary ? " XMI" : " text") << " library files, 3 document blocks)" << std::endl;
        report(point + "a library at level 0: addText of all files", library);
        report(point + "b library at level 0: resolve", libraryResolve);
        report(point + "c 3 document blocks at level 1000: addText", firstBlocks);
        report(point + "d 3 document blocks at level 1000: first resolve", firstResolve);
        report(point + "e replaceSource of all 3 blocks", replace);
        report(point + "f resolve after replaceSource", resolveAfter);
        report(point + "g resolve without any change", resolveIdle);
        std::cout << "   (" << point << ": " << unresolved << " unresolved references after the last replace)" << std::endl;
    }

    void pointSeven(int runs)
    {
        std::cout << "   (point 7: std::thread::hardware_concurrency() = " << std::thread::hardware_concurrency() << ")" << std::endl;
        for (const bool xmi : {false, true})
        {
            const auto fs = xmi ? cmrc::LibraryXmi::get_filesystem() : cmrc::Library::get_filesystem();
            std::vector<std::pair<std::string, std::string>> files;
            collect(fs, "", files);
            const auto language = [xmi](const std::string& path) {
                if (xmi)
                    return SysMLv2::Files::SourceLanguage::Xmi;
                return path.ends_with(".kerml") ? SysMLv2::Files::SourceLanguage::KerML : SysMLv2::Files::SourceLanguage::SysML;
            };
            const std::string format = xmi ? "XMI" : "text";
            std::vector<std::string> contents;
            for (const auto& [name, path] : files)
                contents.push_back(readEmbedded(fs, path));
            for (const unsigned threads : {0u, 1u, 2u, 3u, 4u, 6u, 8u, 12u, 16u})
            {
                std::vector<double> load, resolve;
                std::size_t resolved = 0, unresolved = 0, errors = 0;
                for (int run = 0; run < runs; ++run)
                {
                    SysMLv2::Files::Workspace workspace;
                    std::vector<SysMLv2::Files::TextInput> inputs;
                    for (std::size_t index = 0; index < files.size(); ++index)
                        inputs.push_back({contents[index], files[index].second, language(files[index].second), 0});
                    load.push_back(timed([&] {
                        if (threads == 0)
                        {
                            for (auto& input : inputs)
                                workspace.addText(std::move(input.text), std::move(input.name), input.language, input.level);
                        }
                        else
                        {
                            workspace.addTexts(std::move(inputs), threads);
                        }
                    }));
                    resolve.push_back(timed([&] { workspace.resolve(); }));
                    resolved = workspace.resolvedReferenceCount();
                    unresolved = workspace.unresolvedReferences().size();
                    errors = workspace.errors().size();
                }
                const std::string how = threads == 0 ? "one addText per file" : "addTexts, " + std::to_string(threads) + " thread(s)";
                report("7 " + format + " library: " + how, load);
                report("  " + format + " resolve after it", resolve);
                std::cout << "   (" << resolved << " resolved, " << unresolved << " unresolved, " << errors << " errors)" << std::endl;
            }
        }
    }
}

int main(int argc, char** argv)
{
    int runs = 5;
    std::set<int> only;
    bool only6x = false;
    // The configurations of the InstanceManager for points 1 to 3: the format of the standard library, and whether it is kept between the models.
    std::vector<std::string> modes = {"text", "text-reuse", "xmi", "xmi-reuse"};
    for (int index = 1; index < argc; ++index)
    {
        if (std::strncmp(argv[index], "--runs=", 7) == 0)
        {
            runs = std::max(1, std::atoi(argv[index] + 7));
        }
        else if (std::strncmp(argv[index], "--modes=", 8) == 0)
        {
            modes.clear();
            std::stringstream list(argv[index] + 8);
            for (std::string item; std::getline(list, item, ',');)
                modes.push_back(item);
        }
        else if (std::strncmp(argv[index], "--only=", 7) == 0)
        {
            std::stringstream list(argv[index] + 7);
            for (std::string item; std::getline(list, item, ',');)
            {
                if (item == "6x")
                    only6x = true;
                else
                    only.insert(std::atoi(item.c_str()));
            }
        }
    }
    const auto wanted = [&only, &only6x](int point) { return (only.empty() && !only6x) || only.count(point) != 0; };

    std::cout << "conformance-benchmark: median of " << runs << " runs" << std::endl;
    if (wanted(1) || wanted(2) || wanted(3))
    {
        for (const auto& mode : modes)
        {
            const bool xmi = mode.rfind("xmi", 0) == 0;
            pointsOneToThree(runs, xmi ? SysMLv2::API::StandardLibraryFormat::Xmi : SysMLv2::API::StandardLibraryFormat::Text,
                             mode.find("reuse") != std::string::npos, mode);
        }
    }
    if (wanted(4))
        pointFour(runs);
    if (wanted(5))
        pointFive(runs);
    if (wanted(6))
        pointSix(runs);
    if ((only.empty() && !only6x) || only6x)
        pointSix(runs, true);
    if (wanted(7))
        pointSeven(runs);
    return 0;
}
