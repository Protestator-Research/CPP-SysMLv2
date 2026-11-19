#pragma once

#include <sysmlv2/evaluation/EvaluationContext.h>
#include <sysmlv2/evaluation/Value.h>

#include <kerml/kernel/functions/Expression.h>
#include <kerml/kernel/functions/Function.h>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace SysMLv2::Evaluation {

    /// A native implementation of a function. The arguments arrive unevaluated; the implementation evaluates them with
    /// EvaluationContext::evaluate() when (and if) it needs their values.
    using NativeFunction = std::function<Value(EvaluationContext&, const std::vector<std::shared_ptr<KerML::Entities::Expression>>& arguments)>;

    /// A native implementation that gets the values of all arguments (evaluated left to right). The arguments are passed by value, so the
    /// implementation may move out of them.
    using StrictFunction = std::function<Value(EvaluationContext&, std::vector<Value> arguments)>;

    /**
     * The native implementations of library functions by qualified name in the textual notation (`DataFunctions::'+'`; the names of
     * KerML::operatorFunctions, see qualifiedNameOf()). The standard implementations are registered at the abstract root functions of
     * the Kernel Function Library, so that they also serve the specializations (IntegerFunctions::'+' -> ... -> DataFunctions::'+').
     *
     * Pointers returned by find() / lookup() stay valid while the registry exists and are not affected by registering other names;
     * registering the same name again replaces what a held pointer calls. The registry is not synchronized: concurrent find() / lookup()
     * calls are fine, registration must not run concurrently with anything else.
     */
    class SYSMLV2EVALUATION_EXPORT FunctionRegistry {
    public:
        /// An empty registry.
        FunctionRegistry() = default;

        /**
         * A registry with the core functions: DataFunctions `+ - * / % ** ^ < > <= >= not xor | & ..`, BaseFunctions `== != === !== ,`
         * and ControlFunctions `if and or implies ??`. Not implemented yet (not registered): `~ [ # all istype hastype @ @@ as meta .
         * collect select`.
         */
        [[nodiscard]] static FunctionRegistry withStandardFunctions();

        /// Registers (or replaces) the implementation of the function with the given qualified name.
        void registerFunction(const std::string& qualifiedName, NativeFunction implementation);

        /// Registers (or replaces) an implementation that evaluates all arguments first (EvaluationContext::evaluate, left to right).
        void registerStrictFunction(const std::string& qualifiedName, StrictFunction implementation);

        /// The implementation registered under the name, nullptr if there is none.
        [[nodiscard]] const NativeFunction* find(const std::string& qualifiedName) const;

        /**
         * The implementation for a function: the one registered for the function itself, else for its generals, breadth-first along
         * the owned specializations (Type::ownedSpecialization, so also subclassifications), nearest first. Safe against cyclic
         * specializations. nullptr if there is none or the function is null.
         */
        [[nodiscard]] const NativeFunction* find(const std::shared_ptr<KerML::Entities::Function>& function) const;

        /// The result of lookup(): the implementation and whether it was found for a general and not for the function itself.
        struct Match {
            const NativeFunction* implementation = nullptr;
            bool inherited = false;
            /// The implementation as it was registered by registerStrictFunction (called with values, without building expressions for
            /// them), null if it was registered with registerFunction.
            const StrictFunction* strict = nullptr;
        };

        /// Like find(function), but tells whether the implementation belongs to the function itself or is inherited from a general (a
        /// function with its own body must win over an inherited native implementation).
        [[nodiscard]] Match lookup(const std::shared_ptr<KerML::Entities::Function>& function) const;

    private:
        std::map<std::string, NativeFunction> Functions;
        std::map<std::string, StrictFunction> StrictFunctions;
    };
}
