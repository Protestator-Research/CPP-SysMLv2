#pragma once

// Private: the arguments of an invocation expression, whatever way the model was built (see Arguments.cpp). Shared by the Evaluator and
// the native `,` function, which flattens nested sequence operators.

#include <kerml/kernel/expressions/InstantiationExpression.h>
#include <kerml/kernel/expressions/InvocationExpression.h>
#include <kerml/kernel/functions/Expression.h>
#include <kerml/kernel/functions/Function.h>

#include <memory>
#include <vector>

namespace SysMLv2::Evaluation {

    struct ArgumentList {
        std::vector<std::shared_ptr<KerML::Entities::Expression>> Values;
        /// True if an input parameter of an XMI-shaped invocation has no value expression; Values then lacks that argument and must
        /// not be used for a call.
        bool MissingValue = false;
    };

    /// The arguments of an invocation, in order. Zero-argument calls stay zero-argument.
    ArgumentList argumentsOf(const KerML::Entities::InvocationExpression& invocation);

    /// The function that an invocation invokes: function(), the instantiated type if it is a Function, or the member of the plain
    /// Membership that the XMI import creates for it. Null if there is none.
    std::shared_ptr<KerML::Entities::Function> invokedFunctionOf(const KerML::Entities::InvocationExpression& invocation);

    /// The type that an invocation invokes: invokedFunctionOf(), else the instantiated type or the member of the plain Membership if
    /// that is a type that is no function (a calculation usage or a parameter that holds a function value). Null if there is none.
    std::shared_ptr<KerML::Entities::Type> invokedTypeOf(const KerML::Entities::InstantiationExpression& invocation);

    /// The expression of the FeatureValue that the feature owns (null if there is none).
    std::shared_ptr<KerML::Entities::Expression> featureValueExpression(const std::shared_ptr<KerML::Entities::Feature>& feature);
}
