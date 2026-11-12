#pragma once

// Private: how a feature is bound in a featuring context. The model has no instances, so the "instance" that a feature reference is
// evaluated in (the target) is an element of the model: a usage (`part p : P`) or a definition. The value of a feature in such a context
// is the value of its effective binding: the feature value of the most specific feature in the specialization closure of the target that
// is the feature itself or (transitively) redefines it.

#include <kerml/core/features/Feature.h>
#include <kerml/core/types/Type.h>
#include <kerml/kernel/expressions/FeatureChainExpression.h>
#include <kerml/kernel/expressions/FeatureReferenceExpression.h>
#include <kerml/kernel/functions/Expression.h>

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace SysMLv2::Evaluation {

    /// The feature that a reference expression refers to: referent(), else (XMI of the pilot implementation) the member of its plain
    /// Membership. Null if the model records none (an unresolved referent, which XmiWriter does not write).
    std::shared_ptr<KerML::Entities::Feature> referentOf(const KerML::Entities::FeatureReferenceExpression& reference);

    /// The expression that the pilot's XMI wraps in a reference without a referent: the lazily evaluated operand of `if`, `and`, `or`,
    /// `??`, ... and the body `{ ... }` of an expression are references that own the expression through a FeatureMembership. Parsed text
    /// has the operand itself there, and a plain Expression for a body. Null if the reference is not such a wrapper.
    std::shared_ptr<KerML::Entities::Expression> wrappedExpressionOf(const KerML::Entities::FeatureReferenceExpression& reference);

    /// The feature after the dot of a feature chain: targetFeature(), else the member of its plain Membership (pilot XMI).
    std::shared_ptr<KerML::Entities::Feature> chainTargetOf(const KerML::Entities::FeatureChainExpression& chain);

    /// True for the placeholder that the parser keeps for a name that could not be resolved: a feature that no element owns.
    bool isUnresolvedPlaceholder(const KerML::Entities::Feature& feature);

    /// The path of a navigation: the instance (a usage or definition) that a feature is looked up in, and the outer instances that it
    /// was reached through (`c.e.x` enters the nested usage `e` of the definition of `c`, whose outer instance is `c`). Innermost first;
    /// the Parent is null for an instance that was not reached through another one. The public `target` of the Evaluator is a path of
    /// length one: nested instances are only known when they are reached through a chain.
    struct Path {
        std::shared_ptr<KerML::Entities::Element> Element;
        std::shared_ptr<const Path> Parent;
    };
    using PathPtr = std::shared_ptr<const Path>;

    /// Same instances in the same order (the identity of a path, for the detection of cycles).
    bool samePath(const PathPtr& a, const PathPtr& b);

    /// The FeatureValue of a feature: its expression, and whether it is a `default` value. {nullptr, false} if there is none.
    struct BoundValue {
        std::shared_ptr<KerML::Entities::Expression> Expression;
        bool IsDefault = false;
    };
    BoundValue boundValueOf(const std::shared_ptr<KerML::Entities::Feature>& feature);

    /// The effective binding of a feature in a context, see Navigation::resolve().
    struct Resolution {
        /// The most specific feature that is the feature or redefines it (the feature itself without a context). Null if @c Ambiguity.
        std::shared_ptr<KerML::Entities::Feature> Effective;
        /// The most specific feature with a bound value (non-default values first, `default` values only if there is none), null if none.
        std::shared_ptr<KerML::Entities::Feature> Binding;
        std::shared_ptr<KerML::Entities::Expression> Value;
        /// Not empty if two unrelated features both bind a (non-default or default) value and neither is more specific ("A and B").
        std::string Ambiguity;
        /// The bound (non-default) values that the Binding overrides, which KerML only allows for default values.
        std::vector<std::shared_ptr<KerML::Entities::Feature>> Overridden;
        /// The `default` values that are more specific than the Binding and are ignored because a bound value exists.
        std::vector<std::shared_ptr<KerML::Entities::Feature>> IgnoredDefaults;
    };

    /// Per-evaluation-call cache and queries. Not thread safe; one per call.
    class Navigation {
    public:
        /// The effective binding of @p feature in the context @p context (null: no context, the feature itself).
        Resolution resolve(const std::shared_ptr<KerML::Entities::Feature>& feature, const std::shared_ptr<KerML::Entities::Element>& context);

        /// The feature with the given name among the features of the context and of its generals (the most specific one; a redefining
        /// feature is known by the name of what it redefines). Null if there is none; @p ambiguous is set if several unrelated ones
        /// are equally specific.
        std::shared_ptr<KerML::Entities::Feature> findByName(const std::string& name, const std::shared_ptr<KerML::Entities::Element>& context, bool& ambiguous);

        /// The instance in which a reference to @p feature, written in a value that is evaluated at @p path, is looked up: the first
        /// instance of the path (innermost first) of which the owner of the feature is a type, else the first of the lexical owners of
        /// the instances that has it (a reference to a feature of an enclosing type is a reference to that feature of the enclosing
        /// instance). The path itself if none does.
        PathPtr contextFor(const std::shared_ptr<KerML::Entities::Feature>& feature, const PathPtr& path);

        /// True for a feature without a value that stands for an element of the model rather than for data: an enumeration literal, a
        /// usage of any other kind than an attribute or reference usage (part, item, action, port, connection, state, ..., typed or not;
        /// the metaclass is read from Element::getType(), so the module needs no sysml), and a feature that is typed by a Class and by no
        /// DataType. A plain attribute, or an untyped feature, is not.
        bool denotesElement(const std::shared_ptr<KerML::Entities::Feature>& feature);

        /// The type that features @p element: the owner of the nearest feature (the element itself if it is one) that is owned by a type
        /// that is no Expression, null if there is none (a feature of a package). It stands for "any instance of that type".
        std::shared_ptr<KerML::Entities::Element> featuringContext(const std::shared_ptr<KerML::Entities::Element>& element);

        /// False if @p target is no context for @p feature: the feature is owned by a type that is none of the types of the target nor of
        /// the types of its lexical owners (a feature of a package conforms to everything).
        bool conforms(const std::shared_ptr<KerML::Entities::Feature>& feature, const std::shared_ptr<KerML::Entities::Element>& target);

    private:
        const std::vector<std::shared_ptr<KerML::Entities::Type>>& closure(KerML::Entities::Type& type);
        const std::vector<std::shared_ptr<KerML::Entities::Feature>>& ownedFeatures(const std::shared_ptr<KerML::Entities::Type>& type);
        bool moreSpecific(const std::shared_ptr<KerML::Entities::Feature>& a, const std::shared_ptr<KerML::Entities::Feature>& b);
        std::vector<std::shared_ptr<KerML::Entities::Feature>> maximal(const std::vector<std::shared_ptr<KerML::Entities::Feature>>& candidates);

        std::unordered_map<const KerML::Entities::Type*, std::vector<std::shared_ptr<KerML::Entities::Type>>> Closures;
        std::unordered_map<const KerML::Entities::Type*, std::vector<std::shared_ptr<KerML::Entities::Feature>>> Owned;
        std::unordered_map<const KerML::Entities::Feature*, std::vector<std::shared_ptr<KerML::Entities::Feature>>> Redefined;
        std::map<std::pair<const KerML::Entities::Feature*, const KerML::Entities::Element*>, Resolution> Resolved;
        std::unordered_map<const KerML::Entities::Feature*, bool> Denotes;

        /// Everything a feature redefines, transitively (not the feature itself).
        const std::vector<std::shared_ptr<KerML::Entities::Feature>>& redefinedBy(const std::shared_ptr<KerML::Entities::Feature>& feature);
    };
}
