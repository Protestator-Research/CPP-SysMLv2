#include "TestSupport.h"

#include <cmath>
#include <limits>

using namespace TestSupport;

TEST(DataFunctions, Addition) {
    runCases({
        {D("+"), {I(1), I(2)}, I(3), ""},
        {D("+"), {I(-5), I(2)}, I(-3), ""},
        {D("+"), {R(1.5), R(2.25)}, R(3.75), ""},
        {D("+"), {I(1), R(0.5)}, R(1.5), ""},
        {D("+"), {R(0.5), I(1)}, R(1.5), ""},
        {D("+"), {S("ab"), S("cd")}, S("abcd"), ""},
        {D("+"), {S(""), S("x")}, S("x"), ""},
        {D("+"), {I(5)}, I(5), ""},       // unary plus
        {D("+"), {R(2.5)}, R(2.5), ""},
        {D("+"), {I(Max), I(0)}, I(Max), ""},
        {D("+"), {I(Min), I(Max)}, I(-1), ""},
        // null propagates without a diagnostic
        {D("+"), {N(), I(1)}, N(), ""},
        {D("+"), {I(1), N()}, N(), ""},
        {D("+"), {N()}, N(), ""},
        {D("+"), {S("a"), N()}, N(), ""},
        // errors
        {D("+"), {I(Max), I(1)}, N(), "Integer overflow"},
        {D("+"), {I(1), I(Max)}, N(), "Integer overflow"},
        {D("+"), {I(Min), I(-1)}, N(), "Integer overflow"},
        {D("+"), {S("a"), I(1)}, N(), "unsupported argument types (String, Integer)"},
        {D("+"), {B(true), B(false)}, N(), "unsupported argument types (Boolean, Boolean)"},
        {D("+"), {Inf(), I(1)}, N(), "unsupported argument types (Infinity, Integer)"},
        {D("+"), {Seq({1, 2}), I(1)}, N(), "sequence of 2 items"},
        {D("+"), {B(true)}, N(), "unsupported argument types (Boolean)"},
        {D("+"), {S("a")}, N(), "unsupported argument types (String)"},
        {D("+"), {}, N(), "DataFunctions::'+': expected 1 to 2 argument(s) but got 0"},
        {D("+"), {I(1), I(2), I(3)}, N(), "expected 1 to 2 argument(s) but got 3"},
    });
}

TEST(DataFunctions, Subtraction) {
    runCases({
        {D("-"), {I(5), I(3)}, I(2), ""},
        {D("-"), {I(3), I(5)}, I(-2), ""},
        {D("-"), {R(2.5), I(1)}, R(1.5), ""},
        {D("-"), {I(1), R(0.5)}, R(0.5), ""},
        {D("-"), {I(5)}, I(-5), ""},       // unary minus
        {D("-"), {I(-5)}, I(5), ""},
        {D("-"), {R(2.5)}, R(-2.5), ""},
        {D("-"), {I(0), I(Max)}, I(-Max), ""},
        {D("-"), {I(-1), I(Max)}, I(Min), ""},
        {D("-"), {N(), I(1)}, N(), ""},
        {D("-"), {N()}, N(), ""},
        {D("-"), {I(Min), I(1)}, N(), "Integer overflow"},
        {D("-"), {I(Max), I(-1)}, N(), "Integer overflow"},
        {D("-"), {I(0), I(Min)}, N(), "Integer overflow"},
        {D("-"), {I(Min)}, N(), "Integer overflow"},
        {D("-"), {S("a"), S("b")}, N(), "unsupported argument types (String, String)"},
        {D("-"), {S("a")}, N(), "unsupported argument types (String)"},
        {D("-"), {}, N(), "expected 1 to 2 argument(s) but got 0"},
        {D("-"), {I(1), I(2), I(3)}, N(), "expected 1 to 2 argument(s) but got 3"},
    });
}

TEST(DataFunctions, Multiplication) {
    runCases({
        {D("*"), {I(6), I(7)}, I(42), ""},
        {D("*"), {I(-6), I(7)}, I(-42), ""},
        {D("*"), {I(0), I(Min)}, I(0), ""},
        {D("*"), {I(Min), I(1)}, I(Min), ""},
        {D("*"), {I(Max / 2), I(2)}, I(Max - 1), ""},
        {D("*"), {I(-1), I(Max)}, I(-Max), ""},
        {D("*"), {R(1.5), I(2)}, R(3.0), ""},
        {D("*"), {R(0.5), R(0.5)}, R(0.25), ""},
        {D("*"), {N(), I(2)}, N(), ""},
        {D("*"), {I(Max), I(2)}, N(), "Integer overflow"},
        {D("*"), {I(2), I(Max)}, N(), "Integer overflow"},
        {D("*"), {I(Min), I(-1)}, N(), "Integer overflow"},
        {D("*"), {I(-1), I(Min)}, N(), "Integer overflow"},
        {D("*"), {I(Min), I(Min)}, N(), "Integer overflow"},
        {D("*"), {I(Min), I(2)}, N(), "Integer overflow"},
        {D("*"), {I(Max), I(Min)}, N(), "Integer overflow"},
        {D("*"), {S("a"), I(2)}, N(), "unsupported argument types (String, Integer)"},
        {D("*"), {I(1)}, N(), "expected 2 argument(s) but got 1"},
    });
}

TEST(DataFunctions, Division) {
    runCases({
        {D("/"), {I(7), I(2)}, R(3.5), ""},          // Integer / Integer is a Real (the library: Rational)
        {D("/"), {I(6), I(3)}, R(2.0), ""},
        {D("/"), {I(-7), I(2)}, R(-3.5), ""},
        {D("/"), {R(1.0), I(4)}, R(0.25), ""},
        {D("/"), {I(Min), I(-1)}, R(9223372036854775808.0), ""},   // no Integer overflow: the result is a Real
        {D("/"), {N(), I(2)}, N(), ""},
        {D("/"), {I(2), N()}, N(), ""},
        {D("/"), {I(1), I(0)}, N(), "division by zero"},
        {D("/"), {R(1.0), I(0)}, N(), "division by zero"},
        {D("/"), {I(1), R(0.0)}, N(), "division by zero"},
        {D("/"), {I(1), R(-0.0)}, N(), "division by zero"},
        {D("/"), {S("a"), S("b")}, N(), "unsupported argument types"},
        {D("/"), {I(1), I(2), I(3)}, N(), "expected 2 argument(s) but got 3"},
    });
}

TEST(DataFunctions, Remainder) {
    // The sign of the result follows the dividend (truncated division, like C++ % and std::fmod).
    runCases({
        {D("%"), {I(7), I(3)}, I(1), ""},
        {D("%"), {I(-7), I(3)}, I(-1), ""},
        {D("%"), {I(7), I(-3)}, I(1), ""},
        {D("%"), {I(-7), I(-3)}, I(-1), ""},
        {D("%"), {I(6), I(3)}, I(0), ""},
        {D("%"), {I(Min), I(-1)}, I(0), ""},         // (undefined behaviour in C++; mathematically 0, no overflow)
        {D("%"), {I(Max), I(-1)}, I(0), ""},
        {D("%"), {I(Min), I(Max)}, I(-1), ""},
        {D("%"), {R(5.5), I(2)}, R(1.5), ""},
        {D("%"), {R(-5.5), I(2)}, R(-1.5), ""},
        {D("%"), {I(5), R(2.5)}, R(0.0), ""},
        {D("%"), {N(), I(2)}, N(), ""},
        {D("%"), {I(1), I(0)}, N(), "modulo by zero"},
        {D("%"), {R(1.0), I(0)}, N(), "modulo by zero"},
        {D("%"), {I(1), R(0.0)}, N(), "modulo by zero"},
        {D("%"), {S("a"), I(1)}, N(), "unsupported argument types"},
        {D("%"), {}, N(), "expected 2 argument(s) but got 0"},
    });
}

TEST(DataFunctions, Power) {
    for (const std::string& name : {D("**"), D("^")}) {
        runCases({
            {name, {I(2), I(10)}, I(1024), ""},
            {name, {I(2), I(0)}, I(1), ""},
            {name, {I(0), I(0)}, I(1), ""},
            {name, {I(-2), I(3)}, I(-8), ""},
            {name, {I(10), I(18)}, I(1'000'000'000'000'000'000), ""},
            {name, {I(2), I(62)}, I(4611686018427387904), ""},
            {name, {I(-2), I(63)}, I(Min), ""},      // (fits exactly)
            {name, {I(1), I(Max)}, I(1), ""},
            {name, {I(-1), I(Max)}, I(-1), ""},
            {name, {I(0), I(Max)}, I(0), ""},
            {name, {I(2), I(-1)}, R(0.5), ""},       // a negative exponent gives a Real
            {name, {I(2), I(-2)}, R(0.25), ""},
            {name, {R(2.0), I(3)}, R(8.0), ""},
            {name, {I(4), R(0.5)}, R(2.0), ""},
            {name, {N(), I(2)}, N(), ""},
            {name, {I(2), N()}, N(), ""},
            {name, {I(2), I(63)}, N(), "Integer overflow"},
            {name, {I(2), I(64)}, N(), "Integer overflow"},
            {name, {I(10), I(19)}, N(), "Integer overflow"},
            {name, {I(-2), I(64)}, N(), "Integer overflow"},
            {name, {I(Max), I(2)}, N(), "Integer overflow"},
            {name, {I(Min), I(2)}, N(), "Integer overflow"},
            {name, {I(0), I(-1)}, N(), "division by zero"},
            {name, {R(0.0), I(-1)}, N(), "division by zero"},
            {name, {R(-1.0), R(0.5)}, N(), "result is not a finite number"},
            {name, {R(10.0), R(400.0)}, N(), "result is not a finite number"},
            {name, {S("a"), I(2)}, N(), "unsupported argument types"},
            {name, {I(2)}, N(), "expected 2 argument(s) but got 1"},
        });
    }
}

TEST(DataFunctions, NonFiniteRealsAreErrors) {
    const double inf = std::numeric_limits<double>::infinity();
    runCases({
        {D("*"), {R(1e308), R(10.0)}, N(), "DataFunctions::'*': result is not a finite number"},
        {D("*"), {R(1e308), I(10)}, N(), "result is not a finite number"},
        {D("+"), {R(1.7976931348623157e308), R(1.7976931348623157e308)}, N(), "result is not a finite number"},
        {D("-"), {R(-1.7976931348623157e308), R(1.7976931348623157e308)}, N(), "result is not a finite number"},
        {D("/"), {R(1e308), R(1e-10)}, N(), "DataFunctions::'/': result is not a finite number"},
        {D("**"), {R(10.0), R(400.0)}, N(), "result is not a finite number"},
        {D("^"), {R(-1.0), R(0.5)}, N(), "DataFunctions::'^': result is not a finite number"},
        {D("+"), {R(inf), I(1)}, N(), "operand is not a finite number"},
        {D("*"), {R(std::nan("")), I(1)}, N(), "operand is not a finite number"},
        {D("%"), {I(1), R(inf)}, N(), "operand is not a finite number"},
        {D("-"), {R(inf)}, N(), "operand is not a finite number"},
        {D("+"), {R(inf)}, N(), "operand is not a finite number"},
        {D("*"), {R(1e308), R(0.5)}, R(5e307), ""},
    });
}

TEST(DataFunctions, MixedIntegerRealOrderingIsExact) {
    // 2^53 = 9007199254740992: the Integer 2^53 + 1 is not representable as a double.
    const std::int64_t p53 = 9007199254740992;
    const double d53 = 9007199254740992.0;
    runCases({
        {D("<="), {I(p53 + 1), R(d53)}, B(false), ""},
        {D(">"), {I(p53 + 1), R(d53)}, B(true), ""},
        {D("<"), {R(d53), I(p53 + 1)}, B(true), ""},
        {D(">="), {R(d53), I(p53 + 1)}, B(false), ""},
        {D("<="), {I(p53), R(d53)}, B(true), ""},
        {D(">="), {I(p53), R(d53)}, B(true), ""},
        {D("<"), {I(p53), R(d53)}, B(false), ""},
        {D("<"), {I(p53 - 1), R(d53)}, B(true), ""},
        {D("<"), {I(-p53 - 1), R(-d53)}, B(true), ""},
        // fractions
        {D("<"), {I(2), R(2.5)}, B(true), ""},
        {D(">"), {I(3), R(2.5)}, B(true), ""},
        {D("<"), {I(-3), R(-2.5)}, B(true), ""},
        {D(">"), {I(-2), R(-2.5)}, B(true), ""},
        {D("<="), {R(2.5), I(2)}, B(false), ""},
        {D(">"), {R(-0.5), I(-1)}, B(true), ""},
        {D("<"), {I(0), R(0.5)}, B(true), ""},
        {D(">"), {I(0), R(-0.5)}, B(true), ""},
        {D(">="), {I(0), R(-0.0)}, B(true), ""},
        {D("<="), {I(0), R(-0.0)}, B(true), ""},
        // the int64 limits
        {D("<"), {I(Max), R(9223372036854775808.0)}, B(true), ""},
        {D(">"), {R(9223372036854775808.0), I(Max)}, B(true), ""},
        {D(">="), {I(Max), R(9223372036854775808.0)}, B(false), ""},
        {D("<="), {I(Min), R(-9223372036854775808.0)}, B(true), ""},
        {D(">="), {I(Min), R(-9223372036854775808.0)}, B(true), ""},
        {D(">"), {I(Min), R(-9223372036854777856.0)}, B(true), ""},   // (the double below -2^63)
        {D("<"), {I(Max), R(1e300)}, B(true), ""},
        {D(">"), {I(Min), R(-1e300)}, B(true), ""},
        // infinities and NaN
        {D("<"), {I(Max), R(std::numeric_limits<double>::infinity())}, B(true), ""},
        {D(">"), {I(Min), R(-std::numeric_limits<double>::infinity())}, B(true), ""},
        {D("<"), {I(1), R(std::nan(""))}, B(false), ""},
        {D(">="), {I(1), R(std::nan(""))}, B(false), ""},
        {D("<="), {R(std::nan("")), I(1)}, B(false), ""},
        // == uses the same comparison
        {BF("=="), {I(p53 + 1), R(d53)}, B(false), ""},
        {BF("=="), {I(p53), R(d53)}, B(true), ""},
        {BF("=="), {I(Max), R(9223372036854775808.0)}, B(false), ""},
        {BF("=="), {I(Min), R(-9223372036854775808.0)}, B(true), ""},
        {BF("=="), {I(1), R(1.0000000000000002)}, B(false), ""},
    });
}

TEST(DataFunctions, Comparisons) {
    runCases({
        {D("<"), {I(1), I(2)}, B(true), ""},
        {D("<"), {I(2), I(1)}, B(false), ""},
        {D("<"), {I(1), I(1)}, B(false), ""},
        {D("<="), {I(1), I(1)}, B(true), ""},
        {D("<="), {I(2), I(1)}, B(false), ""},
        {D(">"), {I(2), I(1)}, B(true), ""},
        {D(">"), {I(1), I(1)}, B(false), ""},
        {D(">="), {I(1), I(1)}, B(true), ""},
        {D(">="), {I(1), I(2)}, B(false), ""},
        {D("<"), {I(Min), I(Max)}, B(true), ""},   // (exact Integer comparison)
        {D("<"), {I(Max - 1), I(Max)}, B(true), ""},
        {D("<"), {I(1), R(1.5)}, B(true), ""},     // mixed Integer / Real
        {D(">="), {R(2.0), I(2)}, B(true), ""},
        {D(">"), {R(2.5), I(2)}, B(true), ""},
        {D("<"), {R(-0.0), R(0.0)}, B(false), ""},
        {D("<="), {R(-0.0), R(0.0)}, B(true), ""},
        // NaN is unordered
        {D("<"), {R(std::nan("")), I(1)}, B(false), ""},
        {D(">="), {R(std::nan("")), I(1)}, B(false), ""},
        // Strings: lexicographic by code unit
        {D("<"), {S("a"), S("b")}, B(true), ""},
        {D("<"), {S("ab"), S("b")}, B(true), ""},
        {D("<"), {S("b"), S("ab")}, B(false), ""},
        {D("<"), {S("a"), S("ab")}, B(true), ""},
        {D("<="), {S("a"), S("a")}, B(true), ""},
        {D(">="), {S("a"), S("a")}, B(true), ""},
        {D(">"), {S("a"), S("a")}, B(false), ""},
        {D("<"), {S("B"), S("a")}, B(true), ""},   // ('B' is 66, 'a' is 97)
        {D("<"), {S(""), S("a")}, B(true), ""},
        // Infinity is greater than every number
        {D(">"), {Inf(), I(Max)}, B(true), ""},
        {D("<"), {I(Max), Inf()}, B(true), ""},
        {D(">="), {Inf(), R(1e308)}, B(true), ""},
        {D("<"), {Inf(), I(5)}, B(false), ""},
        {D("<"), {Inf(), Inf()}, B(false), ""},
        {D("<="), {Inf(), Inf()}, B(true), ""},
        {D(">="), {Inf(), Inf()}, B(true), ""},
        {D(">"), {Inf(), Inf()}, B(false), ""},
        // null propagates
        {D("<"), {N(), I(1)}, N(), ""},
        {D(">="), {S("a"), N()}, N(), ""},
        // errors
        {D("<"), {S("a"), I(1)}, N(), "unsupported argument types (String, Integer)"},
        {D("<"), {B(true), B(false)}, N(), "unsupported argument types (Boolean, Boolean)"},
        {D("<="), {Inf(), S("a")}, N(), "unsupported argument types (Infinity, String)"},
        {D(">"), {Seq({1, 2}), I(1)}, N(), "sequence of 2 items"},
        {D(">="), {I(1)}, N(), "expected 2 argument(s) but got 1"},
        {D("<"), {I(1), I(2), I(3)}, N(), "expected 2 argument(s) but got 3"},
    });
}

TEST(DataFunctions, BooleanOperators) {
    runCases({
        {D("not"), {B(true)}, B(false), ""},
        {D("not"), {B(false)}, B(true), ""},
        {D("not"), {N()}, N(), ""},
        {D("not"), {I(1)}, N(), "unsupported argument types (Integer)"},
        {D("not"), {B(true), B(true)}, N(), "expected 1 argument(s) but got 2"},
        {D("not"), {}, N(), "expected 1 argument(s) but got 0"},
        {D("xor"), {B(true), B(false)}, B(true), ""},
        {D("xor"), {B(true), B(true)}, B(false), ""},
        {D("xor"), {B(false), B(false)}, B(false), ""},
        {D("xor"), {N(), B(true)}, N(), ""},
        {D("xor"), {B(true), I(1)}, N(), "unsupported argument types (Boolean, Integer)"},
        {D("|"), {B(false), B(false)}, B(false), ""},
        {D("|"), {B(false), B(true)}, B(true), ""},
        {D("|"), {B(true), B(true)}, B(true), ""},
        {D("|"), {B(true), N()}, N(), ""},
        {D("|"), {I(1), B(true)}, N(), "unsupported argument types (Integer, Boolean)"},
        {D("|"), {B(true)}, N(), "expected 2 argument(s) but got 1"},
        {D("&"), {B(true), B(true)}, B(true), ""},
        {D("&"), {B(true), B(false)}, B(false), ""},
        {D("&"), {B(false), B(false)}, B(false), ""},
        {D("&"), {N(), N()}, N(), ""},
        {D("&"), {S("true"), B(true)}, N(), "unsupported argument types (String, Boolean)"},
    });
}

TEST(DataFunctions, Range) {
    runCases({
        {D(".."), {I(1), I(3)}, Seq({1, 2, 3}), ""},
        {D(".."), {I(3), I(3)}, Seq({3}), ""},
        {D(".."), {I(-1), I(1)}, Seq({-1, 0, 1}), ""},
        {D(".."), {I(4), I(3)}, N(), ""},            // empty: lower > upper
        {D(".."), {I(Max), I(Min)}, N(), ""},
        {D(".."), {N(), I(3)}, N(), ""},
        {D(".."), {I(1), N()}, N(), ""},
        {D(".."), {I(1), I(10)}, Seq({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}), "", 10},   // exactly at the limit
        {D(".."), {I(Max - 1), I(Max)}, Seq({Max - 1, Max}), ""},                   // (no overflow at the upper end)
        {D(".."), {I(1), I(11)}, N(), "longer than the maximum sequence length of 10", 10},
        {D(".."), {I(Min), I(Max)}, N(), "longer than the maximum sequence length"},
        {D(".."), {I(0), I(Max)}, N(), "longer than the maximum sequence length"},
        {D(".."), {R(1.0), I(3)}, N(), "unsupported argument types (Real, Integer)"},
        {D(".."), {I(1), S("3")}, N(), "unsupported argument types (Integer, String)"},
        {D(".."), {I(1)}, N(), "expected 2 argument(s) but got 1"},
    });
}
