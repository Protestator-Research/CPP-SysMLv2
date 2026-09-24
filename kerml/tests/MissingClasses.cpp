#include <kerml/kernel/expressions/ConstructorExpression.h>
#include <kerml/kernel/expressions/IndexExpression.h>
#include <kerml/kernel/interactions/FlowEnd.h>
#include <kerml/kernel/interactions/PayloadFeature.h>
#include <kerml/kernel/functions/ResultExpressionMembership.h>
#include <kerml/kernel/functions/ResultExpressionMembersip.h>
#include <kerml/kernel/functions/Function.h>
#include <kerml/root/namespaces/NamespaceImport.h>
#include <kerml/root/namespaces/Namespace.h>
#include <kerml/root/namespaces/Membership.h>
#include <iostream>
#include <stdexcept>
#include <type_traits>

using namespace KerML::Entities;

static_assert(std::is_convertible_v<ConstructorExpression*, InstantiationExpression*>);
static_assert(std::is_convertible_v<IndexExpression*, OperatorExpression*>);
static_assert(std::is_convertible_v<IndexExpression*, Expression*>);
static_assert(std::is_convertible_v<FlowEnd*, Feature*>);
static_assert(std::is_convertible_v<PayloadFeature*, Feature*>);
static_assert(std::is_convertible_v<ResultExpressionMembership*, FeatureMembership*>);
static_assert(std::is_same_v<ResultExpressionMembersip, ResultExpressionMembership>);

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

template<class Action>
void requireInvalid(Action action) {
    try { action(); }
    catch (const std::invalid_argument&) { return; }
    throw std::runtime_error("Expected invalid_argument");
}

// Check that the specialized property uses FeatureMembership's storage.
struct ResultProbe : ResultExpressionMembership {
    using FeatureMembership::ownedMemberFeature;
};

int main() {
    try {
        ConstructorExpression constructor;
        IndexExpression index;
        FlowEnd end;
        PayloadFeature payload;
        ResultExpressionMembership membership;
        require(constructor.getType() == "ConstructorExpression", "constructor identity");
        require(index.getType() == "IndexExpression", "index identity");
        require(end.getType() == "FlowEnd", "flow end identity");
        require(payload.getType() == "PayloadFeature", "payload identity");
        require(membership.getType() == "ResultExpressionMembership", "membership identity");
        require(end.isEnd(), "flow end must initialize isEnd");

        OperatorExpression& base = index;
        require(base.operatorName() == "#", "index operator default");
        base.setOperatorName("#");
        requireInvalid([&] { base.setOperatorName("+"); });
        require(base.operatorName() == "#", "failed update must retain index operator");
        OperatorExpression generalOperator;
        generalOperator.setOperatorName("+");
        require(generalOperator.operatorName() == "+", "general operators remain configurable");

        auto result = std::make_shared<ConstructorExpression>();
        auto function = std::make_shared<Function>();
        ResultProbe probe;
        require(!probe.ownedResultExpression(), "two-phase initial state");
        probe.setOwnedResultExpression(result);
        require(probe.ownedMemberFeature() == result, "base storage must reflect result");
        probe.setOwningType(function);
        require(probe.owningType() == function, "function owner");
        requireInvalid([&] { probe.setOwnedResultExpression(nullptr); });
        requireInvalid([&] { probe.setOwningType(std::make_shared<Type>()); });
        requireInvalid([&] { probe.setOwningType(nullptr); });
        require(probe.ownedResultExpression() == result, "failed update must retain result");
        require(probe.owningType() == function, "failed update must retain owner");
        auto replacement = std::make_shared<IndexExpression>();
        probe.setOwnedResultExpression(replacement);
        require(probe.ownedMemberFeature() == replacement, "replacement must update base storage");
        probe.setOwningType(result);
        require(probe.owningType() == result, "expression owner");
        ResultExpressionMembersip legacy(result, function);
        require(legacy.ownedResultExpression() == result, "legacy alias construction");
        requireInvalid([&] { ResultExpressionMembership invalid(nullptr, function); });

        // NamespaceImport::importedMemberships tests
        {
            NamespaceImport ni;
            require(ni.importedMemberships({}).empty(), "null importedNamespace returns empty memberships");

            auto targetNs = std::make_shared<Namespace>("TargetNS");
            ni.setImportedNamespace(targetNs);
            require(ni.importedMemberships({targetNs}).empty(), "excluded importedNamespace returns empty memberships");

            auto mem1 = std::make_shared<Membership>();
            mem1->setVisibility(PUBLIC);
            auto mem2 = std::make_shared<Membership>();
            mem2->setVisibility(PRIVATE);
            targetNs->appendOwnedMembership(mem1);
            targetNs->appendOwnedMembership(mem2);

            // Default: isImportAll is false -> only PUBLIC memberships returned
            auto imported = ni.importedMemberships({});
            require(imported.size() == 1, "only public memberships imported when isImportAll is false");
            require(imported[0] == mem1, "correct public membership imported");

            // With isImportAll = true -> both PUBLIC and PRIVATE memberships returned
            ni.setIsImportAll(true);
            imported = ni.importedMemberships({});
            require(imported.size() == 2, "all memberships imported when isImportAll is true");
        }

        std::cout << "KerML representation tests passed\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
