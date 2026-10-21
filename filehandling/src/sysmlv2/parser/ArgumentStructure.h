//
// Helpers shared by the KerML and the SysML listener for the abstract syntax of invocations and constructors.
//
// Internal header (not installed): both listeners include it relatively, as src/kerml/parser and src/sysmlv2/parser are not on the
// include path.
//

#ifndef SYSMLV2_PARSER_ARGUMENTSTRUCTURE_H
#define SYSMLV2_PARSER_ARGUMENTSTRUCTURE_H

#include <kerml/KerML.h>
#include <memory>
#include <typeinfo>
#include <vector>

namespace SysMLv2::Files {
	// A plain invocation (`f(a, b)`), not one of its subclasses (operators...): the arguments of it are parameters of the invoked
	// function, each owned through a ParameterMembership.
	inline bool isPlainInvocation(const std::shared_ptr<KerML::Entities::Element>& element) {
		return element != nullptr && typeid(*element) == typeid(KerML::Entities::InvocationExpression);
	}

	inline bool isConstructor(const std::shared_ptr<KerML::Entities::Element>& element) {
		return element != nullptr && typeid(*element) == typeid(KerML::Entities::ConstructorExpression);
	}

	// An expression whose arguments are parameter features: plain invocations and constructors.
	inline bool isArgumentHost(const std::shared_ptr<KerML::Entities::Element>& element) {
		return isPlainInvocation(element) || isConstructor(element);
	}

	// A feature that is exactly a Feature (not an Expression or any other subclass): the parameter features that were created for the
	// arguments and the result feature of a constructor, which argumentParameterOwner relies on.
	inline bool isArgumentParameter(const std::shared_ptr<KerML::Entities::Element>& element) {
		return element != nullptr && typeid(*element) == typeid(KerML::Entities::Feature);
	}

	inline std::shared_ptr<KerML::Entities::Feature> makeArgumentParameter() {
		auto parameter = std::make_shared<KerML::Entities::Feature>();
		parameter->setDirection(KerML::Entities::IN);
		return parameter;
	}

	// The element that owns the parameters of the arguments: the invocation itself, but for a constructor its result feature (the
	// only feature it owns directly). It is null for a constructor without a result feature.
	inline std::shared_ptr<KerML::Entities::Type> argumentParameterOwner(const std::shared_ptr<KerML::Entities::Element>& host) {
		if (isPlainInvocation(host)) return std::dynamic_pointer_cast<KerML::Entities::Type>(host);
		if (!isConstructor(host)) return nullptr;
		for (const auto& owned : host->ownedElements()) {
			if (isArgumentParameter(owned)) return std::dynamic_pointer_cast<KerML::Entities::Type>(owned);
		}
		return nullptr;
	}

	// Whether the arguments of the element are parameter features. False for a constructor whose type is missing (syntax error): its
	// arguments are then kept the flat way.
	inline bool acceptsArgumentParameters(const std::shared_ptr<KerML::Entities::Element>& element) {
		return isArgumentHost(element) && argumentParameterOwner(element) != nullptr;
	}

	// The result of a constructor: it exists without arguments too and owns the parameters of the arguments. The caller registers it
	// (Elements, OwnershipKinds[result] = ReturnParameter).
	inline std::shared_ptr<KerML::Entities::Feature> makeConstructorResult(const std::shared_ptr<KerML::Entities::ConstructorExpression>& constructor) {
		const auto result = std::make_shared<KerML::Entities::Feature>();
		result->setDirection(KerML::Entities::OUT);
		result->setOwner(constructor);
		constructor->appendOwnedElement(result);
		return result;
	}

	// A positional argument: a parameter feature whose feature value is the expression. The feature value is returned, the caller
	// registers it and the parameter (Elements) and appends the parameter to its owner (see argumentParameterOwner).
	inline std::shared_ptr<KerML::Entities::FeatureValue> makePositionalArgument(const std::shared_ptr<KerML::Entities::Expression>& expression,
		std::shared_ptr<KerML::Entities::Feature>& parameter) {
		parameter = makeArgumentParameter();
		const auto value = std::make_shared<KerML::Entities::FeatureValue>();
		value->setFeatureWithValue(parameter);
		value->setValue(expression);
		value->setOwner(parameter);
		value->appendOwnedElement(expression);
		expression->setOwner(value);
		parameter->appendOwnedElement(value);
		return value;
	}

	// The non-owning membership of the invoked type, which is the first owned relationship of the invocation or constructor. The caller
	// sets its member element and registers it (Elements).
	inline std::shared_ptr<KerML::Entities::Membership> makeTypeMembership(const std::shared_ptr<KerML::Entities::InstantiationExpression>& expr) {
		const auto membership = std::make_shared<KerML::Entities::Membership>();
		membership->setOwner(expr);
		auto owned = expr->ownedElements();
		owned.insert(owned.begin(), membership);
		expr->setOwnedElements(owned);
		return membership;
	}
}

#endif // SYSMLV2_PARSER_ARGUMENTSTRUCTURE_H
