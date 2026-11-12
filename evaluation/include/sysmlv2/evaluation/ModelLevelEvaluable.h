#pragma once

#include <sysmlv2/evaluation/sysmlv2evaluation_global.h>

#include <kerml/kernel/functions/Expression.h>

#include <memory>

namespace SysMLv2::Evaluation {

    /**
     * Whether an expression is model-level evaluable (KerML 8.4.4.9: its value can be computed from the model alone). This implements
     * the rules as recalled from the specification (no copy of the specification and no values written by a reference implementation
     * were available to compare with: the XMI of the standard library carries no Expression::isModelLevelEvaluable value):
     *  - literal expressions, `null` and metadata access expressions are;
     *  - an operator expression or invocation (also `.`, `#`, `[`, select, collect, `istype`, `hastype`, `@`, `@@`, `as`, `meta`) is
     *    if every argument is and the function it invokes is. The library does not carry the flag for its functions, so a function
     *    counts as evaluable if it is one of the operator functions or lives in a package of the Kernel Function Library (a name that
     *    ends in `Functions`); user functions and functions of other packages do not. The type operand of `istype`, `as`, ... counts;
     *  - a feature reference is if its referent is `Anything::self` or redefines it, or (and the referent is not being checked
     *    already, which would be a cycle) the referent is itself a model-level evaluable Expression, or its owning type is a metaclass,
     *    or it has no featuring type (it is not owned by a type) and has either no value or a model-level evaluable value;
     *  - a feature chain is if its argument is and the target feature satisfies the reference rule;
     *  - everything else (constructors, bodies, unresolved references) is not.
     * It tells whether the specification calls an expression evaluable, not whether this module can evaluate it. It does not write
     * Expression::isModelLevelEvaluable().
     */
    [[nodiscard]] SYSMLV2EVALUATION_EXPORT bool isModelLevelEvaluable(const std::shared_ptr<KerML::Entities::Expression>& expression);
}
