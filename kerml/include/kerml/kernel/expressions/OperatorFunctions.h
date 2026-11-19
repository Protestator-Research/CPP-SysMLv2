#pragma once

#include <cstddef>
#include <iterator>
#include <string>

namespace KerML {

    /// An operator of an OperatorExpression and the qualified name of the Kernel Function Library function it invokes.
    struct OperatorFunction {
        const char* operatorName;
        const char* functionName;
    };

    /**
     * The one table of the operators and their functions: the function named like the operator in BaseFunctions, DataFunctions or
     * ControlFunctions. It is only a table of names: whether the library that defines the functions is loaded is decided by the caller.
     * Independent of the parsers, so that it is usable on models that were loaded by other means. (`\?\?` is written escaped so that
     * the compiler sees no trigraph.)
     */
    inline constexpr OperatorFunction operatorFunctions[] = {
        // BaseFunctions
        {"==", "BaseFunctions::'=='"}, {"!=", "BaseFunctions::'!='"}, {"===", "BaseFunctions::'==='"}, {"!==", "BaseFunctions::'!=='"},
        {"[", "BaseFunctions::'['"}, {"#", "BaseFunctions::'#'"}, {",", "BaseFunctions::','"}, {"all", "BaseFunctions::'all'"},
        {"istype", "BaseFunctions::'istype'"}, {"hastype", "BaseFunctions::'hastype'"}, {"@", "BaseFunctions::'@'"},
        {"@@", "BaseFunctions::'@@'"}, {"as", "BaseFunctions::'as'"}, {"meta", "BaseFunctions::'meta'"},
        // ControlFunctions
        {".", "ControlFunctions::'.'"}, {"if", "ControlFunctions::'if'"}, {"\?\?", "ControlFunctions::'\?\?'"},
        {"and", "ControlFunctions::'and'"}, {"or", "ControlFunctions::'or'"}, {"implies", "ControlFunctions::'implies'"},
        {"collect", "ControlFunctions::collect"}, {"select", "ControlFunctions::select"},
        // DataFunctions
        {"+", "DataFunctions::'+'"}, {"-", "DataFunctions::'-'"}, {"*", "DataFunctions::'*'"}, {"/", "DataFunctions::'/'"},
        {"%", "DataFunctions::'%'"}, {"**", "DataFunctions::'**'"}, {"^", "DataFunctions::'^'"}, {"..", "DataFunctions::'..'"},
        {"<", "DataFunctions::'<'"}, {">", "DataFunctions::'>'"}, {"<=", "DataFunctions::'<='"}, {">=", "DataFunctions::'>='"},
        {"not", "DataFunctions::'not'"}, {"xor", "DataFunctions::'xor'"}, {"~", "DataFunctions::'~'"}, {"|", "DataFunctions::'|'"},
        {"&", "DataFunctions::'&'"},
    };

    /// The number of entries of operatorFunctions.
    inline constexpr std::size_t operatorFunctionCount = std::size(operatorFunctions);

    /// The qualified name of the function that an operator invokes (for example `DataFunctions::'+'`), nullptr for an operator that has
    /// none (`->`, whose function is the one the expression names itself, and every unknown name).
    inline const char* operatorFunctionName(const std::string& operatorName) {
        for (const OperatorFunction& entry : operatorFunctions) {
            if (operatorName == entry.operatorName) return entry.functionName;
        }
        return nullptr;
    }
}
