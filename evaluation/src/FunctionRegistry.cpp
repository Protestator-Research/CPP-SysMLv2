#include <sysmlv2/evaluation/FunctionRegistry.h>
#include <sysmlv2/evaluation/QualifiedName.h>

#include "functions/StandardFunctions.h"

#include <kerml/core/types/Specialization.h>
#include <kerml/core/types/Type.h>

#include <deque>
#include <set>
#include <utility>

namespace SysMLv2::Evaluation {

    FunctionRegistry FunctionRegistry::withStandardFunctions() {
        FunctionRegistry registry;
        Functions::registerDataFunctions(registry);
        Functions::registerBaseFunctions(registry);
        Functions::registerControlFunctions(registry);
        return registry;
    }

    void FunctionRegistry::registerFunction(const std::string& qualifiedName, NativeFunction implementation) {
        Functions[qualifiedName] = std::move(implementation);
    }

    void FunctionRegistry::registerStrictFunction(const std::string& qualifiedName, StrictFunction implementation) {
        registerFunction(qualifiedName,
            [implementation = std::move(implementation)](EvaluationContext& context,
                                                          const std::vector<std::shared_ptr<KerML::Entities::Expression>>& arguments) {
                std::vector<Value> values;
                values.reserve(arguments.size());
                for (const auto& argument : arguments) values.push_back(context.evaluate(argument));
                return implementation(context, std::move(values));
            });
    }

    const NativeFunction* FunctionRegistry::find(const std::string& qualifiedName) const {
        const auto found = Functions.find(qualifiedName);
        return found == Functions.end() ? nullptr : &found->second;
    }

    const NativeFunction* FunctionRegistry::find(const std::shared_ptr<KerML::Entities::Function>& function) const {
        return lookup(function).implementation;
    }

    FunctionRegistry::Match FunctionRegistry::lookup(const std::shared_ptr<KerML::Entities::Function>& function) const {
        if (!function) return {};
        std::deque<std::shared_ptr<KerML::Entities::Type>> queue;
        std::set<const KerML::Entities::Type*> visited;
        queue.push_back(function);
        visited.insert(function.get());
        while (!queue.empty()) {
            const std::shared_ptr<KerML::Entities::Type> current = std::move(queue.front());
            queue.pop_front();
            if (const NativeFunction* found = find(qualifiedNameOf(*current))) return Match{found, current != function};
            for (const auto& specialization : current->ownedSpecialization()) {
                const std::shared_ptr<KerML::Entities::Type> general = specialization ? specialization->general() : nullptr;
                if (general && visited.insert(general.get()).second) queue.push_back(general);
            }
        }
        return {};
    }
}
