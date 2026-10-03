//
// Tests of sysmlv2check: the C interface sysml_pruefe on one process-wide checking context.
//
#include <gtest/gtest.h>

#include <sysmlv2/check/Checker.h>
#include <sysmlv2/check/sysml_pruefe.h>

#include <nlohmann/json.hpp>

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <fstream>
#include <string>
#include <vector>

namespace {
    using nlohmann::json;

    /// Sends a request through the C interface and parses the response.
    json sende(const json& request) {
        const std::string text = request.dump();
        const char* answer = sysml_pruefe(text.c_str());
        EXPECT_NE(answer, nullptr);
        json result = json::parse(answer);
        sysml_freigeben(answer);
        return result;
    }

    json pruefe(const std::string& source, const json& required = json::array(), const std::string& given = "") {
        json request = {{"quelltext", source}, {"pflichtelemente", required}};
        if (!given.empty()) request["vorgabe"] = given;
        return sende(request);
    }

    /// The diagnoses with the given category and source.
    std::vector<json> select(const json& response, const std::string& category, const std::string& source = "") {
        std::vector<json> result;
        for (const auto& entry : response.at("diagnosen")) {
            if (entry.at("kategorie") == category && (source.empty() || entry.at("quelle") == source)) result.push_back(entry);
        }
        return result;
    }

    bool hasElement(const json& response, const std::string& metaclass, const std::string& qualifiedName) {
        for (const auto& element : response.at("elemente")) {
            if (element.at("metaklasse") == metaclass && element.at("qualifiedName") == qualifiedName) return true;
        }
        return false;
    }

    const char* ValidModel = "package Fahrzeuge {\n  part def Auto;\n  part def Rad;\n  part auto : Auto {\n    part raeder : Rad [4];\n  }\n}\n";
}

TEST(SysmlPruefe, ValidModelHasNoGrammarOrUnresolvedDiagnoses) {
    const json response = pruefe(ValidModel);
    EXPECT_EQ(response.at("version"), "1");
    EXPECT_FALSE(response.contains("fehler"));
    EXPECT_TRUE(select(response, "GRAMMATIK").empty()) << response.dump(2);
    EXPECT_TRUE(select(response, "LOGIK", "UNRESOLVED").empty()) << response.dump(2);
    EXPECT_TRUE(select(response, "WARNUNG").empty()) << response.dump(2);
    EXPECT_TRUE(hasElement(response, "PartDefinition", "Fahrzeuge::Auto")) << response.dump(2);
    EXPECT_TRUE(hasElement(response, "PartUsage", "Fahrzeuge::auto::raeder")) << response.dump(2);
}

#ifdef SYSMLV2CHECK_STRUCTURE_CHECK
TEST(SysmlPruefe, ValidModelsHaveNoStructureDiagnoses) {
    const std::string rich = "package R {\n  import ISQ::*;\n  import SI::*;\n  import ScalarValues::*;\n"
        "  port def DataPort { in attribute v : Real; }\n"
        "  part def Motor { attribute masse : MassValue = 100 [kg]; port p : DataPort; perform action lauf { in x : Real; } }\n"
        "  part def Rad { port q : DataPort; }\n"
        "  part def Auto { part motor : Motor [1]; part raeder : Rad [4]; connect motor.p to raeder.q; }\n"
        "  action def Fahren { action a; then action b; first a then b; }\n"
        "  state def Zustand { state aus; state an; transition t first aus accept s : Sig then an; }\n"
        "  item def Sig;\n"
        "  requirement def MasseAnf { attribute m : MassValue; require constraint { m <= 1500 [kg] } }\n"
        "  part auto : Auto;\n  satisfy MasseAnf by auto;\n  part def Unbekannt :> Fehlt { attribute z : Gibtsnicht; }\n}\n";
    for (const std::string& model : {std::string(ValidModel), rich}) {
        const json response = pruefe(model);
        EXPECT_TRUE(select(response, "GRAMMATIK").empty()) << response.dump(2);
        EXPECT_TRUE(select(response, "LOGIK", "STRUKTUR").empty()) << response.dump(2);
    }
}

TEST(SysmlPruefe, FollowUpsOfOtherDiagnosesAreNotReportedTwice) {
    // A syntax error leaves a half-built element behind: GRAMMATIK only, no STRUKTUR on top.
    const json syntax = pruefe("part def A { attribute x [0..*] = ; }");
    EXPECT_FALSE(select(syntax, "GRAMMATIK").empty()) << syntax.dump(2);
    EXPECT_TRUE(select(syntax, "LOGIK", "STRUKTUR").empty()) << syntax.dump(2);
    // An alias of a name that does not exist: exactly one Logik diagnosis (UNRESOLVED).
    const json alias = pruefe("package P { alias X for Missing; }");
    ASSERT_EQ(select(alias, "LOGIK").size(), 1u) << alias.dump(2);
    EXPECT_EQ(select(alias, "LOGIK")[0].at("quelle"), "UNRESOLVED");
}
#endif

TEST(SysmlPruefe, SyntaxErrorIsGrammarWithLine) {
    const json response = pruefe("package P {\n  part def A;\n  part def ;;; B {\n}\n");
    const auto errors = select(response, "GRAMMATIK", "SYNTAX");
    ASSERT_FALSE(errors.empty()) << response.dump(2);
    bool onLineThree = false;
    for (const auto& error : errors) {
        EXPECT_TRUE(error.contains("zeile"));
        EXPECT_TRUE(error.contains("meldung"));
        if (error.value("zeile", 0) == 3) onLineThree = true;
    }
    EXPECT_TRUE(onLineThree) << response.dump(2);
}

TEST(SysmlPruefe, UnresolvedReferenceIsLogic) {
    const json response = pruefe("package P {\n  part def A;\n  part x : DoesNotExist;\n}\n");
    EXPECT_TRUE(select(response, "GRAMMATIK").empty()) << response.dump(2);
    const auto unresolved = select(response, "LOGIK", "UNRESOLVED");
    ASSERT_EQ(unresolved.size(), 1u) << response.dump(2);
    EXPECT_EQ(unresolved[0].at("name"), "DoesNotExist");
    EXPECT_EQ(unresolved[0].at("zeile"), 3);
}

TEST(SysmlPruefe, MissingRequiredElementIsLogic) {
    const json required = json::array({{{"metaklasse", "PartDefinition"}, {"name", "Auto"}},
                                       {{"metaklasse", "PartDefinition"}, {"name", "Motor"}},
                                       {{"metaklasse", "PartUsage"}, {"name", "Fahrzeuge::auto::raeder"}},
                                       {{"metaklasse", "PartUsage"}, {"name", "Auto"}}});
    const json response = pruefe(ValidModel, required);
    const auto missing = select(response, "LOGIK", "PFLICHT");
    ASSERT_EQ(missing.size(), 2u) << response.dump(2);  // Motor does not exist; "Auto" exists but is no PartUsage
    EXPECT_EQ(missing[0].at("name"), "Motor");
    EXPECT_EQ(missing[1].at("name"), "Auto");
    EXPECT_EQ(missing[1].at("element"), "PartUsage");
}

TEST(SysmlPruefe, ImportFromStandardLibraryResolves) {
    const std::string model = "package P {\n  import ScalarValues::*;\n  import ISQ::*;\n  import SI::*;\n"
                              "  attribute def Messung {\n    attribute anzahl : Integer;\n    attribute laenge : LengthValue;\n"
                              "    attribute masse : MassValue = 5 [kg];\n  }\n}\n";
    const json response = pruefe(model);
    EXPECT_TRUE(select(response, "GRAMMATIK").empty()) << response.dump(2);
    EXPECT_TRUE(select(response, "LOGIK", "UNRESOLVED").empty()) << response.dump(2);
}

TEST(SysmlPruefe, UnknownNameDespiteImportIsUnresolved) {
    const json response = pruefe("package P {\n  import ScalarValues::*;\n  attribute a : Integerr;\n}\n");
    const auto unresolved = select(response, "LOGIK", "UNRESOLVED");
    ASSERT_EQ(unresolved.size(), 1u) << response.dump(2);
    EXPECT_EQ(unresolved[0].at("name"), "Integerr");
}

TEST(SysmlPruefe, RequestsDoNotInfluenceEachOther) {
    const std::string broken = "package P {\n  part x : Gone;\n  part def ;;;\n}\n";
    const json first = pruefe(broken);
    EXPECT_FALSE(select(first, "GRAMMATIK").empty());
    EXPECT_FALSE(select(first, "LOGIK", "UNRESOLVED").empty());

    const json second = pruefe(ValidModel);
    EXPECT_TRUE(select(second, "GRAMMATIK").empty()) << second.dump(2);
    EXPECT_TRUE(select(second, "LOGIK", "UNRESOLVED").empty()) << second.dump(2);
    EXPECT_FALSE(hasElement(second, "PartUsage", "P::x"));

    // The same text gives the same answer every time, and an earlier model's elements are gone.
    EXPECT_EQ(pruefe(broken), first);
    const json third = pruefe("package Q { part def Other; }");
    EXPECT_TRUE(hasElement(third, "PartDefinition", "Q::Other"));
    EXPECT_FALSE(hasElement(third, "PartDefinition", "Fahrzeuge::Auto"));
    EXPECT_EQ(pruefe(ValidModel), second);
}

TEST(SysmlPruefe, GivenTextIsVisibleToTheModelButNotReported) {
    const std::string given = "package Vorgabe {\n  part def Basis;\n  part def ;;;\n}\n";
    const std::string model = "package M {\n  import Vorgabe::*;\n  part b : Basis;\n}\n";
    const json response = pruefe(model, json::array(), given);
    EXPECT_TRUE(select(response, "GRAMMATIK").empty()) << response.dump(2);
    EXPECT_TRUE(select(response, "LOGIK", "UNRESOLVED").empty()) << response.dump(2);
    EXPECT_FALSE(hasElement(response, "PartDefinition", "Vorgabe::Basis"));

    // Without the given text the name is unresolved again.
    EXPECT_EQ(select(pruefe(model), "LOGIK", "UNRESOLVED").size(), 2u);  // `Vorgabe` (import) and `Basis`
}

TEST(SysmlPruefe, InvalidRequestsGiveAnError) {
    for (const char* request : {"", "not json", "[]", "{}", "{\"quelltext\": 5}"}) {
        const char* answer = sysml_pruefe(request);
        const json response = json::parse(answer);
        sysml_freigeben(answer);
        EXPECT_TRUE(response.contains("fehler")) << request;
        EXPECT_TRUE(response.at("diagnosen").empty());
    }
    const char* answer = sysml_pruefe(nullptr);
    EXPECT_TRUE(json::parse(answer).contains("fehler"));
    sysml_freigeben(answer);
    sysml_freigeben(nullptr);
}

TEST(SysmlPruefe, EmptyTextIsValid) {
    const json response = pruefe("");
    EXPECT_TRUE(response.at("diagnosen").empty()) << response.dump(2);
    EXPECT_TRUE(response.at("elemente").empty());
}

namespace {
    using SysMLv2::Check::Checker;

    json askJson(Checker& checker, const json& request) { return json::parse(checker.check(request.dump())); }
    json ask(Checker& checker, const std::string& text) { return askJson(checker, json{{"quelltext", text}}); }

    const char* MeasurementModel = "package P {\n  import ScalarValues::*;\n  import ISQ::*;\n  import SI::*;\n  attribute def Messung {\n"
                                   "    attribute laenge : LengthValue;\n    attribute masse : MassValue = 5 [kg];\n  }\n}\n";
    // Defines packages that the library defines, too, and that a library file that is loaded later refers to.
    const char* PoisonModel = "package ISQBase { }\npackage ISQMechanics { }\npackage Quantities { part def X; }\npackage P { import ISQ::*; }\n";
    const char* NeutralModel = "package Q { part def Plain; }";
}

TEST(SysmlPruefeContext, ModelWithLibraryPackageNamesDoesNotPoisonLaterRequests) {
    Checker checker;
    const json poisoned = ask(checker, PoisonModel);
    EXPECT_TRUE(select(poisoned, "GRAMMATIK").empty()) << poisoned.dump(2);
    // The library was loaded while the model was in the workspace under the names of the library packages.
    for (int round = 0; round < 2; ++round) {
        const json clean = ask(checker, MeasurementModel);
        EXPECT_TRUE(select(clean, "LOGIK", "UNRESOLVED").empty()) << "round " << round << clean.dump(2);
        EXPECT_TRUE(select(clean, "GRAMMATIK").empty());
        EXPECT_TRUE(select(ask(checker, NeutralModel), "LOGIK").empty());
    }
}

TEST(SysmlPruefeContext, CleanRequestFirstThenPoisonThenClean) {
    Checker checker;
    EXPECT_TRUE(select(ask(checker, NeutralModel), "LOGIK").empty());
    EXPECT_TRUE(select(ask(checker, PoisonModel), "GRAMMATIK").empty());
    const json clean = ask(checker, MeasurementModel);
    EXPECT_TRUE(select(clean, "LOGIK", "UNRESOLVED").empty()) << clean.dump(2);
    // The poisoning request still sees its own packages and the library through its import.
    const json again = ask(checker, PoisonModel);
    EXPECT_TRUE(select(again, "LOGIK", "UNRESOLVED").empty()) << again.dump(2);
    EXPECT_TRUE(hasElement(again, "Package", "ISQBase"));
}

TEST(SysmlPruefeContext, QuotedNamesAreNormalized) {
    Checker checker;
    const json request = {{"quelltext", "package P { part def 'Mein Auto'; part 'mein auto' : 'Mein Auto'; }"},
                          {"pflichtelemente", json::array({{{"metaklasse", "PartDefinition"}, {"name", "Mein Auto"}},
                                                           {{"metaklasse", "PartDefinition"}, {"name", "'Mein Auto'"}},
                                                           {{"metaklasse", "PartDefinition"}, {"name", "P::'Mein Auto'"}},
                                                           {{"metaklasse", "PartUsage"}, {"name", "P::mein auto"}},
                                                           {{"metaklasse", "PartDefinition"}, {"name", "Mein Wagen"}}})}};
    const json response = askJson(checker, request);
    const auto missing = select(response, "LOGIK", "PFLICHT");
    ASSERT_EQ(missing.size(), 1u) << response.dump(2);
    EXPECT_EQ(missing[0].at("name"), "Mein Wagen");
    EXPECT_TRUE(select(response, "LOGIK", "UNRESOLVED").empty()) << response.dump(2);
    EXPECT_TRUE(hasElement(response, "PartDefinition", "P::Mein Auto")) << response.dump(2);
    EXPECT_TRUE(hasElement(response, "PartUsage", "P::mein auto")) << response.dump(2);
}

TEST(SysmlPruefeContext, ErrorsOfTheGivenTextAreReportedSeparately) {
    Checker checker;
    const json response = askJson(checker, json{{"quelltext", "package M { import V::*; part b : Basis; }"},
                                             {"vorgabe", "package V {\n  part def Basis;\n  part x : Unknown;\n  part def ;;;\n}\n"}});
    EXPECT_TRUE(select(response, "GRAMMATIK").empty()) << response.dump(2);
    EXPECT_TRUE(select(response, "LOGIK").empty()) << response.dump(2);
    const auto& given = response.at("vorgabeFehler");
    bool syntax = false;
    bool unresolved = false;
    for (const auto& entry : given) {
        EXPECT_EQ(entry.at("quelle"), "VORGABE");
        if (entry.at("kategorie") == "GRAMMATIK") syntax = entry.contains("zeile");
        if (entry.at("kategorie") == "LOGIK" && entry.value("name", "") == "Unknown") unresolved = true;
    }
    EXPECT_TRUE(syntax) << response.dump(2);
    EXPECT_TRUE(unresolved) << response.dump(2);
    EXPECT_TRUE(ask(checker, NeutralModel).at("vorgabeFehler").empty());
}

TEST(SysmlPruefeContext, InputLimitsAreChecked) {
    Checker checker;
    Checker::Limits limits;
    limits.maxTextBytes = 200;
    limits.maxNestingDepth = 8;
    checker.setLimits(limits);
    EXPECT_EQ(checker.limits().maxNestingDepth, 8u);

    const json big = ask(checker, "package P { // " + std::string(300, 'x') + "\n}");
    EXPECT_EQ(big.at("fehler"), "zuGross");
    EXPECT_TRUE(big.at("diagnosen").empty());

    std::string deep;
    for (int i = 0; i < 9; ++i) deep += "package P" + std::to_string(i) + " { ";
    for (int i = 0; i < 9; ++i) deep += "} ";
    EXPECT_EQ(ask(checker, deep).at("fehler"), "zuTief");
    EXPECT_EQ(askJson(checker, json{{"quelltext", "package A;"}, {"vorgabe", deep}}).at("fehler"), "zuTief");

    // Braces in comments, strings and quoted names do not count; the depth at the limit is fine.
    const json fine = ask(checker, "package P { /* {{{{{{{{{{{{ */ doc /* ((((((((((( */ part def 'a{{{{{{{{{{{{{' ; }");
    EXPECT_FALSE(fine.contains("fehler")) << fine.dump(2);
    std::string atLimit;
    for (int i = 0; i < 8; ++i) atLimit += "package P" + std::to_string(i) + " { ";
    for (int i = 0; i < 8; ++i) atLimit += "} ";
    EXPECT_FALSE(ask(checker, atLimit).contains("fehler"));

    // The limits are also reachable through the C interface.
    EXPECT_EQ(sysml_konfigurieren("{\"maxBytes\": 100000, \"maxTiefe\": 3}"), 1);
    const json viaC = pruefe(std::string("package A { package B { package C { package D { } } } }"));
    EXPECT_EQ(viaC.at("fehler"), "zuTief");
    EXPECT_EQ(sysml_konfigurieren("[]"), 0);
    EXPECT_EQ(sysml_konfigurieren("{\"maxTiefe\": 64}"), 1);
}

TEST(SysmlPruefeContext, PreloadLoadsPackagesInAdvance) {
    Checker checker;
    const size_t before = checker.loadedLibraryCount();
    const size_t added = checker.preload({"ISQ", "SI", "ScalarValues", "Attributes", "Nonexistent"});
    EXPECT_GT(added, 10u);
    EXPECT_EQ(checker.loadedLibraryCount(), before + added);
    EXPECT_EQ(checker.preload({"ISQ"}), 0u);

    const size_t loaded = checker.loadedLibraryCount();
    const json response = ask(checker, MeasurementModel);
    EXPECT_TRUE(select(response, "LOGIK", "UNRESOLVED").empty()) << response.dump(2);
    EXPECT_EQ(checker.loadedLibraryCount(), loaded);   // nothing had to be loaded for the request
    EXPECT_EQ(sysml_vorwaermen("[\"ISQ\"]") >= 0, true);
    EXPECT_EQ(sysml_vorwaermen("{}"), -1);
    EXPECT_EQ(sysml_vorwaermen("[1]"), -1);
}

TEST(SysmlPruefeContext, ManyRequestsDoNotGrowTheMemory) {
    Checker checker;
    const auto rss = [] {
        std::ifstream statm("/proc/self/statm");
        size_t size = 0, resident = 0;
        statm >> size >> resident;
        return resident * 4096 / (1024 * 1024);
    };
    const std::string model = "package P {\n  part def D0 { part p0 : D0; attribute a0; }\n  part def D1 { part p1 : D1; attribute a1; }\n"
                              "  part def D2 { part p2 : D2; attribute a2; }\n  part x : Nope;\n}\n";
    for (int i = 0; i < 10; ++i) ask(checker, model);   // warm up: library files, allocator
    const size_t before = rss();
    for (int i = 0; i < 150; ++i) ask(checker, model);
    const size_t after = rss();
    std::cout << "[memory] RSS " << before << " MB before, " << after << " MB after 150 more requests\n";
    if (before > 0) EXPECT_LT(after, before + 30);   // a leak of 1.7 MB per request would be 250 MB
}

TEST(SysmlPruefeContext, ShortNamesOfLibraryPackagesLoadThePackage) {
    Checker checker;
    const size_t before = checker.loadedLibraryCount();
    const json response = ask(checker, "package P { import USCU::*; attribute l : LengthValue; }");
    EXPECT_TRUE(select(response, "GRAMMATIK").empty()) << response.dump(2);
    const auto unresolved = select(response, "LOGIK", "UNRESOLVED");
    EXPECT_TRUE(unresolved.empty()) << response.dump(2);   // `import USCU::*` resolves, and what the package imports (ISQ) is loaded
    EXPECT_GT(checker.loadedLibraryCount(), before);
    EXPECT_EQ(checker.preload({"USCU"}), 0u);               // already loaded under its name
}

TEST(SysmlPruefeContext, UnterminatedCommentsAndStringsDoNotHideTheNesting) {
    Checker checker;
    std::string nested;
    for (int i = 0; i < 70; ++i) nested += "package P" + std::to_string(i) + " { ";
    for (int i = 0; i < 70; ++i) nested += "} ";
    for (const std::string prefix : {"/* ", "\" ", "' ", "/* \" ' ", "// x\n/* "}) {
        EXPECT_EQ(ask(checker, prefix + nested).at("fehler"), "zuTief") << prefix;
    }
    // A terminated comment around the nesting is a comment.
    EXPECT_FALSE(ask(checker, "/* " + nested + " */ package Q;").contains("fehler"));
}

TEST(SysmlPruefeContext, TokenAndChainLimits) {
    Checker checker;
    std::string chain = "package E { attribute a = x";
    for (int i = 0; i < 45000; ++i) chain += ".y";
    chain += "; }";
    Checker::Limits big;
    big.maxTextBytes = 1000000;
    checker.setLimits(big);
    EXPECT_EQ(ask(checker, chain).at("fehler"), "zuGross");   // 90000 tokens

    std::string shortChain = "package E { attribute a = x";
    for (int i = 0; i < 70; ++i) shortChain += ".y";
    shortChain += "; }";
    EXPECT_EQ(ask(checker, shortChain).at("fehler"), "zuLang");
    std::string qualified = "package E { attribute a : ";
    for (int i = 0; i < 70; ++i) qualified += "Q::";
    qualified += "Z; }";
    EXPECT_EQ(ask(checker, qualified).at("fehler"), "zuLang");

    std::string multiplicities = "package E { part p : X";
    for (int i = 0; i < 30000; ++i) multiplicities += "[1]";
    multiplicities += "; }";
    EXPECT_EQ(ask(checker, multiplicities).at("fehler"), "zuGross");

    // A chain just below the limit and an ordinary model pass the scan.
    std::string fine = "package E { attribute a = x";
    for (int i = 0; i < 60; ++i) fine += ".y";
    fine += "; }";
    EXPECT_FALSE(ask(checker, fine).contains("fehler"));
    EXPECT_FALSE(ask(checker, ValidModel).contains("fehler"));
}

TEST(SysmlPruefeContext, ParseDeadline) {
    Checker checker;
    ask(checker, NeutralModel);
    std::string model = "package P {\n";
    for (int i = 0; i < 300; ++i) model += "  part def D" + std::to_string(i) + " { part p" + std::to_string(i) + " : D" + std::to_string(i) + "; attribute a" + std::to_string(i) + "; }\n";
    model += "}\n";
    Checker::Limits limits = checker.limits();
    limits.maxParseMillis = 1;
    checker.setLimits(limits);
    const auto start = std::chrono::steady_clock::now();
    const json timedOut = ask(checker, model);
    const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
    EXPECT_EQ(timedOut.at("fehler"), "zeitueberschreitung") << timedOut.dump(2);
    EXPECT_LT(ms, 2000);
    EXPECT_TRUE(timedOut.at("diagnosen").empty());
    // The context is fine afterwards.
    limits.maxParseMillis = 20000;
    checker.setLimits(limits);
    const json ok = ask(checker, model);
    EXPECT_FALSE(ok.contains("fehler")) << ok.dump(2);
    EXPECT_TRUE(select(ok, "GRAMMATIK").empty());
    EXPECT_TRUE(hasElement(ok, "PartDefinition", "P::D299"));
    // The deadline is also configurable through the C interface.
    EXPECT_EQ(sysml_konfigurieren("{\"maxMs\": 1}"), 1);
    EXPECT_EQ(pruefe(model).at("fehler"), "zeitueberschreitung");
    EXPECT_EQ(sysml_konfigurieren("{\"maxMs\": 20000, \"maxTokens\": 20000, \"maxKette\": 64}"), 1);
}

TEST(SysmlPruefeContext, TheIdOfARequestIsReturned) {
    Checker checker;
    EXPECT_EQ(askJson(checker, json{{"quelltext", "package A;"}, {"id", 17}}).at("id"), 17);
    EXPECT_EQ(askJson(checker, json{{"quelltext", "package A;"}, {"id", "abc"}}).at("id"), "abc");
    EXPECT_EQ(askJson(checker, json{{"quelltext", 5}, {"id", "e"}}).at("id"), "e");          // error response
    EXPECT_EQ(askJson(checker, json{{"quelltext", "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{"}, {"id", json{{"n", 1}}}}).at("id"), (json{{"n", 1}}));
    EXPECT_FALSE(askJson(checker, json{{"quelltext", "package A;"}}).contains("id"));
}

TEST(SysmlPruefeCli, StdoutHoldsOnlyResponseLinesWithTheirIds) {
    const std::string input = std::tmpnam(nullptr);
    {
        std::ofstream out(input);
        out << json{{"id", 1}, {"quelltext", "package A { part def X; }"}}.dump() << "\n";
        out << json{{"id", "zwei"}, {"quelltext", "package B { part x : Gone; part def ;;; }"}}.dump() << "\n";
        out << "\n";
        out << "not json\n";
        out << json{{"id", 4}, {"quelltext", 7}}.dump() << "\n";
        out << json{{"id", 5}, {"quelltext", "package C { part def Q; }"}}.dump() << "\n";
    }
    const std::string command = std::string(SYSMLV2CHECK_CLI) + " --lines < " + input + " 2>/dev/null";
    FILE* pipe = popen(command.c_str(), "r");
    ASSERT_NE(pipe, nullptr);
    std::string output;
    char buffer[4096];
    while (size_t n = fread(buffer, 1, sizeof buffer, pipe)) output.append(buffer, n);
    EXPECT_EQ(pclose(pipe), 0);
    std::remove(input.c_str());

    std::vector<json> responses;
    size_t start = 0;
    while (start < output.size()) {
        const size_t end = output.find('\n', start);
        ASSERT_NE(end, std::string::npos);
        const json line = json::parse(output.substr(start, end - start), nullptr, false);
        ASSERT_FALSE(line.is_discarded()) << "stdout line is not JSON: " << output.substr(start, end - start);
        responses.push_back(line);
        start = end + 1;
    }
    ASSERT_EQ(responses.size(), 5u) << output;   // the empty line is skipped
    EXPECT_EQ(responses[0].at("id"), 1);
    EXPECT_EQ(responses[1].at("id"), "zwei");
    EXPECT_FALSE(responses[2].contains("id"));    // not JSON: nothing to return
    EXPECT_EQ(responses[2].at("fehler"), "request is not a JSON object");
    EXPECT_EQ(responses[3].at("id"), 4);
    EXPECT_EQ(responses[4].at("id"), 5);
}

TEST(SysmlPruefeContext, ManyForcedTimeoutsInARowDoNotKillTheProcess) {
    Checker checker;
    std::string model = "package P {\n";
    for (int i = 0; i < 100; ++i) model += "  part def D" + std::to_string(i) + " { part p" + std::to_string(i) + " : D" + std::to_string(i) + "; }\n";
    model += "}\n";
    ask(checker, model);   // loads the library packages the model needs
    Checker::Limits limits = checker.limits();
    const auto rss = [] {
        std::ifstream statm("/proc/self/statm");
        size_t size = 0, resident = 0;
        statm >> size >> resident;
        return resident * 4096 / (1024 * 1024);
    };
    limits.maxParseMillis = 1;
    checker.setLimits(limits);
    size_t timeouts = 0;
    size_t before = 0;
    for (int i = 0; i < 300; ++i) {
        if (i == 50) before = rss();
        const json response = ask(checker, model);
        if (response.value("fehler", "") == "zeitueberschreitung") ++timeouts;
    }
    const size_t after = rss();
    std::cout << "[timeouts] " << timeouts << " of 300 requests timed out; RSS " << before << " MB at request 50, " << after << " MB at 300\n";
    EXPECT_GT(timeouts, 250u);
    limits.maxParseMillis = 20000;
    checker.setLimits(limits);
    const json ok = ask(checker, model);
    EXPECT_FALSE(ok.contains("fehler")) << ok.dump(2);
    EXPECT_TRUE(select(ok, "GRAMMATIK").empty());
    EXPECT_TRUE(hasElement(ok, "PartDefinition", "P::D99"));
    if (before > 0) EXPECT_LT(after, before + 30);
}

TEST(SysmlPruefeContext, RunsOfPrefixOperatorsAreLimitedAndDoNotOverflowTheStack) {
    Checker checker;
    for (const std::string op : {"-", "+", "~", "!", "not ", "- ", "@"}) {
        std::string text = "package P { attribute a = ";
        for (int i = 0; i < 8000; ++i) text += op;
        text += "1; }";
        EXPECT_EQ(ask(checker, text).at("fehler"), "zuTief") << op;
    }
    EXPECT_FALSE(ask(checker, "package P { attribute a = - - - 1 + not true; }").contains("fehler"));
    // With the limits switched off the parse runs on a thread with a large stack: it may be slow, but it must not crash.
    Checker::Limits limits = checker.limits();
    limits.maxNestingDepth = 1000000;
    limits.maxOperators = 1000000;
    limits.maxParseMillis = 10000;
    checker.setLimits(limits);
    std::string text = "package P { attribute a = ";
    for (int i = 0; i < 8000; ++i) text += "-";
    text += "1; }";
    const json response = ask(checker, text);
    EXPECT_TRUE(response.contains("diagnosen"));
    EXPECT_TRUE(!response.contains("fehler") || response.at("fehler") == "zeitueberschreitung") << response.value("fehler", "");
}

TEST(SysmlPruefeContext, LoadingLibraryPackagesDuringARequestHasALimit) {
    Checker checker;
    Checker::Limits limits = checker.limits();
    limits.maxLoadMillis = 1;
    checker.setLimits(limits);
    const json refused = ask(checker, "package P { import ISQ::*; import SI::*; import Time::*; import USCU::*; }");
    EXPECT_EQ(refused.at("fehler"), "zeitueberschreitung") << refused.dump(2);
    // What was loaded stays; with the limit lifted the request goes through.
    limits.maxLoadMillis = 600000;
    checker.setLimits(limits);
    const json response = ask(checker, "package P { import ISQ::*; import SI::*; import Time::*; import USCU::*; }");
    EXPECT_FALSE(response.contains("fehler")) << response.dump(2);
    EXPECT_TRUE(select(response, "LOGIK").empty()) << response.dump(2);
}

TEST(SysmlPruefeContext, AfterAnInterruptedLoadTheLibraryIsCompletedByTheNextRequests) {
    Checker checker;
    Checker::Limits limits = checker.limits();
    limits.maxLoadMillis = 1500;   // enough for the first files, not for ISQ and what it imports
    checker.setLimits(limits);
    const json first = ask(checker, MeasurementModel);
    EXPECT_EQ(first.value("fehler", ""), "zeitueberschreitung") << first.dump(2);
    // Every further request continues loading; none of them may report a name of the library as unresolved because of the gap.
    bool finished = false;
    for (int attempt = 0; attempt < 40 && !finished; ++attempt) {
        const json response = ask(checker, MeasurementModel);
        if (response.value("fehler", "") == "zeitueberschreitung") continue;
        finished = true;
        EXPECT_TRUE(select(response, "LOGIK", "UNRESOLVED").empty()) << attempt << response.dump(2);
        EXPECT_TRUE(select(response, "GRAMMATIK").empty());
    }
    EXPECT_TRUE(finished);
    limits.maxLoadMillis = 600000;
    checker.setLimits(limits);
    EXPECT_TRUE(select(ask(checker, MeasurementModel), "LOGIK", "UNRESOLVED").empty());
}

TEST(SysmlPruefeContext, PreloadingEverythingLoadsTheWholeLibrary) {
    Checker checker;
    const size_t added = checker.preload({"*"});
    EXPECT_EQ(checker.loadedLibraryCount(), 94u);
    EXPECT_GT(added, 80u);
    EXPECT_EQ(checker.preload({"alle"}), 0u);
    const size_t loaded = checker.loadedLibraryCount();
    const json response = ask(checker, MeasurementModel);
    EXPECT_TRUE(select(response, "LOGIK", "UNRESOLVED").empty()) << response.dump(2);
    EXPECT_EQ(checker.loadedLibraryCount(), loaded);
}

TEST(SysmlPruefeContext, LongOperatorChainsAreRefused) {
    Checker checker;
    for (const std::string op : {"1 + ", "a ** ", "true implies ", "true or ", "if true ? 1 else "}) {
        std::string text = "package P { attribute x = ";
        for (int i = 0; i < 300; ++i) text += op;
        text += "1; }";
        EXPECT_EQ(ask(checker, text).value("fehler", ""), "zuTief") << op;
    }
    std::string several = "package P {";
    for (int i = 0; i < 100; ++i) several += " attribute a" + std::to_string(i) + " = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9;";
    several += " }";
    EXPECT_FALSE(ask(checker, several).contains("fehler"));   // the count restarts at every `;`
    EXPECT_EQ(sysml_konfigurieren("{\"maxOperatoren\": 3}"), 1);
    EXPECT_EQ(pruefe("package P { attribute x = 1 + 1 + 1 + 1 + 1; }").value("fehler", ""), "zuTief");
    EXPECT_EQ(sysml_konfigurieren("{\"maxOperatoren\": 256}"), 1);
}

TEST(SysmlPruefeContext, TheNumberOfDiagnosesIsLimited) {
    Checker checker;
    std::string text = "package P { ";
    for (int i = 0; i < 3000; ++i) text += "\xC3\xA9";
    text += " }";
    const json response = ask(checker, text);
    EXPECT_LE(response.at("diagnosen").size(), 200u);
    EXPECT_GT(response.at("weitereDiagnosen").get<size_t>(), 0u) << response.dump(2).substr(0, 500);
    EXPECT_EQ(response.at("diagnosen").size() + response.at("weitereDiagnosen").get<size_t>() >= 200u, true);
    EXPECT_EQ(ask(checker, NeutralModel).at("weitereDiagnosen"), 0);
    Checker::Limits limits = checker.limits();
    limits.maxDiagnostics = 3;
    checker.setLimits(limits);
    EXPECT_EQ(ask(checker, "package P { part x : A; part y : B; part z : C; part w : D; part v : E; }").at("diagnosen").size(), 3u);
}

TEST(SysmlPruefeContext, AnIdThatIsNullIsReturned) {
    Checker checker;
    const json response = json::parse(checker.check("{\"quelltext\": \"package A;\", \"id\": null}"));
    ASSERT_TRUE(response.contains("id"));
    EXPECT_TRUE(response.at("id").is_null());
}

TEST(SysmlPruefeCli, UnusableArgumentsEndWithExitCodeTwo) {
    for (const char* argument : {"--max-ms=abc", "--max-ms=", "--max-ms=-5", "--max-tiefe=1x", "--unknown"}) {
        const std::string command = std::string(SYSMLV2CHECK_CLI) + " " + argument + " < /dev/null 2>/dev/null";
        const int status = std::system(command.c_str());
        EXPECT_EQ(WEXITSTATUS(status), 2) << argument;
    }
    EXPECT_EQ(WEXITSTATUS(std::system((std::string(SYSMLV2CHECK_CLI) + " --max-ms=500 < /dev/null 2>/dev/null").c_str())), 0);
}

TEST(SysmlPruefe, TimingWithWarmParser) {
    // Measured on a fresh context (not the process-wide one): creation, then requests that need ever more library packages. NOT a cold
    // measurement: the parser caches (ANTLR DFA) of this process are already warm from the tests before, which makes loading library
    // files faster than in a fresh process; use the command line program for cold numbers (see the README).
    using Clock = std::chrono::steady_clock;
    const auto since = [](Clock::time_point start) { return std::chrono::duration<double, std::milli>(Clock::now() - start).count(); };
    auto start = Clock::now();
    SysMLv2::Check::Checker checker;
    const double creation = since(start);
    const std::string attributes = "package P {\n  import ISQ::*;\n  import SI::*;\n  import ScalarValues::*;\n"
                                   "  attribute def Messung {\n    attribute masse : MassValue = 5 [kg];\n    attribute laenge : LengthValue = 2 [m];\n  }\n}\n";
    const std::string parts = "package Q {\n  part def Motor;\n  part motor : Motor;\n}\n";
    const auto time = [&](const std::string& text) {
        start = Clock::now();
        const json response = json::parse(checker.check(json{{"quelltext", text}}.dump()));
        const double ms = since(start);
        EXPECT_TRUE(select(response, "GRAMMATIK").empty()) << response.dump(2);
        EXPECT_TRUE(select(response, "LOGIK", "UNRESOLVED").empty()) << response.dump(2);
        return ms;
    };
    const double first = time(attributes);
    const double second = time(attributes);
    const double firstParts = time(parts);
    const double secondParts = time(parts);
    std::cout << "[timing, warm parser] context creation: " << creation << " ms; request with ISQ/SI import: first " << first << " ms, second "
              << second << " ms; request with part def: first " << firstParts << " ms, second " << secondParts << " ms; library files loaded: "
              << checker.loadedLibraryCount() << "\n";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
