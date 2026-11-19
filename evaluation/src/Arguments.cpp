#include "Arguments.h"

#include <kerml/core/features/Feature.h>
#include <kerml/core/features/FeatureMembership.h>
#include <kerml/kernel/featurevalues/FeatureValue.h>
#include <kerml/kernel/functions/ParameterMembership.h>
#include <kerml/kernel/functions/ReturnParameterMembership.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Membership.h>

#include <typeinfo>

namespace SysMLv2::Evaluation {

    // The text parsers, the pilot implementation's XMI and the XMI of XmiWriter build an invocation differently:
    //  - parsed text: argument() lists the values; each value is owned by a parameter feature that is exactly a Feature (directly,
    //    or through its FeatureValue), whose owner is the invocation.
    //  - pilot XMI: argument() is empty. The arguments are the owned ParameterMemberships (member: a Feature with direction in and a
    //    FeatureValue that holds the value expression), followed by a ReturnParameterMembership (the result, direction out).
    //  - XMI of XmiWriter (read back): argument() is empty. The operands are owned directly through plain FeatureMemberships (member:
    //    the value expression itself), in order.
    // Only one of the shapes is present in a model, and the relationships of the others do not occur in it, so nothing is counted twice.

    std::shared_ptr<KerML::Entities::Expression> featureValueExpression(const std::shared_ptr<KerML::Entities::Feature>& feature) {
        for (const auto& owned : feature->ownedElements()) {
            if (const auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(owned)) {
                if (auto expression = value->value()) return expression;
            }
        }
        return nullptr;
    }

    ArgumentList argumentsOf(const KerML::Entities::InvocationExpression& invocation) {
        ArgumentList list;
        list.Values = invocation.argument();
        if (!list.Values.empty()) return list;
        for (const auto& relationship : invocation.ownedRelationship()) {
            if (!relationship) continue;
            const KerML::Entities::Relationship& object = *relationship;
            if (dynamic_cast<KerML::Entities::ReturnParameterMembership*>(relationship.get())) continue;
            const auto* membership = dynamic_cast<KerML::Entities::Membership*>(relationship.get());
            if (membership == nullptr) continue;
            const auto member = membership->memberElement();
            if (dynamic_cast<KerML::Entities::ParameterMembership*>(relationship.get())) {
                const auto parameter = std::dynamic_pointer_cast<KerML::Entities::Feature>(member);
                if (!parameter) continue;
                const auto direction = parameter->direction();
                if (direction && *direction == KerML::Entities::OUT) continue;
                if (auto value = featureValueExpression(parameter)) list.Values.push_back(std::move(value));
                else list.MissingValue = true;   // (an argument that cannot be evaluated: never skip it, the order would be wrong)
            } else if (typeid(object) == typeid(KerML::Entities::FeatureMembership)) {
                // (exactly a FeatureMembership: not a result expression or any other subclass)
                if (auto expression = std::dynamic_pointer_cast<KerML::Entities::Expression>(member)) list.Values.push_back(std::move(expression));
            }
        }
        return list;
    }

    std::shared_ptr<KerML::Entities::Function> invokedFunctionOf(const KerML::Entities::InvocationExpression& invocation) {
        if (auto function = invocation.function()) return function;
        if (auto function = std::dynamic_pointer_cast<KerML::Entities::Function>(invocation.instantiatedType())) return function;
        for (const auto& relationship : invocation.ownedRelationship()) {
            if (!relationship) continue;
            const KerML::Entities::Relationship& object = *relationship;
            if (typeid(object) != typeid(KerML::Entities::Membership)) continue;   // (exactly a Membership, not a subclass)
            if (auto function = std::dynamic_pointer_cast<KerML::Entities::Function>(dynamic_cast<KerML::Entities::Membership&>(*relationship).memberElement()))
                return function;
        }
        return nullptr;
    }

    std::shared_ptr<KerML::Entities::Type> invokedTypeOf(const KerML::Entities::InstantiationExpression& invocation) {
        if (auto function = invocation.function()) return function;
        if (auto type = invocation.instantiatedType()) return type;
        for (const auto& relationship : invocation.ownedRelationship()) {
            if (!relationship) continue;
            const KerML::Entities::Relationship& object = *relationship;
            if (typeid(object) != typeid(KerML::Entities::Membership)) continue;
            if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(dynamic_cast<KerML::Entities::Membership&>(*relationship).memberElement())) return type;
        }
        return nullptr;
    }
}
