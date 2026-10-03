//
// C interface of sysmlv2check. See sysml_pruefe.h.
//
#include <sysmlv2/check/sysml_pruefe.h>
#include <sysmlv2/check/Checker.h>

#include <nlohmann/json.hpp>

#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <vector>

namespace {
    std::mutex mutex;
    SysMLv2::Check::Checker* checker = nullptr;  // lives until the process ends (no destruction order problems)

    SysMLv2::Check::Checker& context() {
        if (checker == nullptr) checker = new SysMLv2::Check::Checker();
        return *checker;
    }
}

#ifdef __EMSCRIPTEN__
#include <emscripten/heap.h>
#endif

extern "C" {

const char* sysml_pruefe(const char* anfrageJson) {
    std::string response;
    try {
        std::lock_guard<std::mutex> lock(mutex);
        response = context().check(anfrageJson != nullptr ? anfrageJson : "");
    } catch (...) {
        response = R"({"version":"1","fehler":"internal error","diagnosen":[],"vorgabeFehler":[],"elemente":[]})";
    }
    char* copy = static_cast<char*>(std::malloc(response.size() + 1));
    if (copy == nullptr) return nullptr;
    std::memcpy(copy, response.c_str(), response.size() + 1);
    return copy;
}

unsigned int sysml_speicher(void) {
#ifdef __EMSCRIPTEN__
    return static_cast<unsigned int>(emscripten_get_heap_size());
#else
    return 0;
#endif
}

int sysml_vorwaermen(const char* paketeJson) {
    try {
        const auto packages = nlohmann::json::parse(paketeJson != nullptr ? paketeJson : "", nullptr, false);
        if (!packages.is_array()) return -1;
        std::vector<std::string> names;
        for (const auto& entry : packages) {
            if (!entry.is_string()) return -1;
            names.push_back(entry.get<std::string>());
        }
        std::lock_guard<std::mutex> lock(mutex);
        return static_cast<int>(context().preload(names));
    } catch (...) {
        return -1;
    }
}

int sysml_konfigurieren(const char* konfigJson) {
    try {
        const auto config = nlohmann::json::parse(konfigJson != nullptr ? konfigJson : "", nullptr, false);
        if (!config.is_object()) return 0;
        std::lock_guard<std::mutex> lock(mutex);
        auto limits = context().limits();
        if (config.contains("maxBytes") && config["maxBytes"].is_number_unsigned()) limits.maxTextBytes = config["maxBytes"].get<size_t>();
        if (config.contains("maxTiefe") && config["maxTiefe"].is_number_unsigned()) limits.maxNestingDepth = config["maxTiefe"].get<size_t>();
        const auto set = [&config](const char* key, size_t& value) {
            if (config.contains(key) && config[key].is_number_unsigned()) value = config[key].get<size_t>();
        };
        set("maxTokens", limits.maxTokens);
        set("maxKette", limits.maxChainLength);
        set("maxOperatoren", limits.maxOperators);
        set("maxMs", limits.maxParseMillis);
        set("maxLadeMs", limits.maxLoadMillis);
        set("maxDiagnosen", limits.maxDiagnostics);
        context().setLimits(limits);
        return 1;
    } catch (...) {
        return 0;
    }
}

void sysml_freigeben(const char* antwort) {
    std::free(const_cast<char*>(antwort));
}

}
