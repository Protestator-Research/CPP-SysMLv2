// The ControlFunctions of the Kernel Function Library that are implemented natively. Their arguments are evaluated on demand, left to
// right, so that the branch that is not taken (and the second operand of a decided `and` / `or` / `implies`) is never evaluated.
// A null condition or left operand gives null without a diagnostic.

#include "FunctionSupport.h"
#include "StandardFunctions.h"

#include <utility>

namespace SysMLv2::Evaluation::Functions {

    namespace {
        using Expressions = std::vector<std::shared_ptr<KerML::Entities::Expression>>;

        /// Evaluates a Boolean operand. nullopt: null or not a Boolean (a type error has been reported in the second case).
        std::optional<bool> booleanOperand(EvaluationContext& context, const std::string& name, const std::shared_ptr<KerML::Entities::Expression>& argument) {
            const Value value = context.evaluate(argument);
            if (value.isNull()) return std::nullopt;
            const auto result = value.asBoolean();
            if (!result) typeError(context, name, Arguments{value});
            return result;
        }

        /// `and`, `or`, `implies`: `decidedBy` is the value of the first operand that decides the result, which is then `decidedResult`.
        NativeFunction shortCircuit(std::string name, bool decidedBy, bool decidedResult) {
            return [name = std::move(name), decidedBy, decidedResult](EvaluationContext& context, const Expressions& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                const auto first = booleanOperand(context, name, arguments[0]);
                if (!first) return Value();
                if (*first == decidedBy) return Value::boolean(decidedResult);
                const auto second = booleanOperand(context, name, arguments[1]);
                if (!second) return Value();
                return Value::boolean(*second);
            };
        }

        NativeFunction conditional() {
            const std::string name = "ControlFunctions::'if'";
            return [name](EvaluationContext& context, const Expressions& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 3)) return Value();
                const auto condition = booleanOperand(context, name, arguments[0]);
                if (!condition) return Value();
                if (*condition) return context.evaluate(arguments[1]);
                if (arguments.size() == 3) return context.evaluate(arguments[2]);
                return Value();   // (no else branch)
            };
        }

        NativeFunction nullCoalescing() {
            const std::string name = "ControlFunctions::'\?\?'";
            return [name](EvaluationContext& context, const Expressions& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                Value first = context.evaluate(arguments[0]);
                if (!first.isNull()) return first;
                return context.evaluate(arguments[1]);
            };
        }
    }

    void registerControlFunctions(FunctionRegistry& registry) {
        registry.registerFunction("ControlFunctions::'if'", conditional());
        // and: false and _ = false;  or: true or _ = true;  implies: false implies _ = true
        registry.registerFunction("ControlFunctions::'and'", shortCircuit("ControlFunctions::'and'", false, false));
        registry.registerFunction("ControlFunctions::'or'", shortCircuit("ControlFunctions::'or'", true, true));
        registry.registerFunction("ControlFunctions::'implies'", shortCircuit("ControlFunctions::'implies'", false, true));
        registry.registerFunction("ControlFunctions::'\?\?'", nullCoalescing());
    }
}
