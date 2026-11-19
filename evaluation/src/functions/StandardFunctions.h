#pragma once

#include <sysmlv2/evaluation/FunctionRegistry.h>

namespace SysMLv2::Evaluation::Functions {

    /// DataFunctions: `+ - * / % ** ^ < > <= >= not xor | & ..`
    void registerDataFunctions(FunctionRegistry& registry);
    /// BaseFunctions: `== != === !== ,`
    void registerBaseFunctions(FunctionRegistry& registry);
    /// ControlFunctions: `if and or implies ??`
    void registerControlFunctions(FunctionRegistry& registry);
    /// SequenceFunctions (size, isEmpty, notEmpty, equals, same, includes, includesOnly, excludes, union, intersection, including,
    /// includingAt, excluding, excludingAt, subsequence, head, tail, last) and `#`.
    void registerSequenceFunctions(FunctionRegistry& registry);
    /// NumericalFunctions / DataFunctions min max / IntegerFunctions ... RealFunctions / BooleanFunctions / TrigFunctions: sum, product,
    /// abs, isZero, isUnit, min, max, sqrt, floor, round, gcd, rat, ToInteger, ToNatural, ToRational, ToReal, ToBoolean, ToString, sin,
    /// cos, arcsin, arccos, arctan.
    void registerScalarFunctions(FunctionRegistry& registry);
    /// StringFunctions: Length, Substring.
    void registerStringFunctions(FunctionRegistry& registry);
}
