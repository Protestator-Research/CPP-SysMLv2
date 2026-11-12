#pragma once

#include <sysmlv2/evaluation/FunctionRegistry.h>

namespace SysMLv2::Evaluation::Functions {

    /// DataFunctions: `+ - * / % ** ^ < > <= >= not xor | & ..`
    void registerDataFunctions(FunctionRegistry& registry);
    /// BaseFunctions: `== != === !== ,`
    void registerBaseFunctions(FunctionRegistry& registry);
    /// ControlFunctions: `if and or implies ??`
    void registerControlFunctions(FunctionRegistry& registry);
}
