//
// Deferred name-resolution data recorded by the KerML / SysML v2 parse listeners.
//
// The listeners no longer resolve names while walking a parse tree. Every name that refers to another
// element (typing, specialization, subsetting, redefinition, alias target, import target, dependency
// end, ...) is recorded here as a PendingReference, together with the scope it was written in and a
// callback that patches the model once the target is known. A SysMLv2::Files::Workspace then resolves
// all pending references of all loaded sources against the union of their namespaces (see Resolver.h).
//
#pragma once

#include <sysmlv2/sysmlv2file_global.h>

#include <kerml/root/elements/Element.h>
#include <kerml/root/namespaces/VisibilityKind.h>
#include <kerml/root/namespaces/Membership.h>
#include <kerml/core/types/Type.h>
#include <kerml/core/classifiers/Classifier.h>
#include <kerml/core/features/Feature.h>

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace antlr4 {
    class ParserRuleContext;
}

namespace SysMLv2::Files {

    /**
     * The kind of element a reference must resolve to. A candidate of another kind is skipped during the
     * lookup (it does not shadow a matching candidate further out).
     */
    enum class ReferenceKind {
        Element,
        /// Any KerML::Entities::Namespace (package, type, feature, ...): the target of `import A::*`.
        Namespace,
        Type,
        Classifier,
        Feature
    };

    /**
     * How the reference is used.
     */
    enum class ReferenceRole {
        /// A plain reference (dependency end, comment target, expression operand, ...).
        Plain,
        /// The target becomes a general type of ReferenceSpec::specific (typing, subclassification, subsetting, ...).
        /// Resolved targets are remembered so that members of the target are inherited by `specific`.
        Generalization,
        /// Like Generalization, but an unqualified name is first looked up among the members that the owner of
        /// `specific` inherits (a redefinition targets an inherited feature, never the feature itself).
        Redefinition,
        /// The target of an alias membership.
        Alias,
        /// The imported namespace / element of an import.
        Import,
        /// A reference that is recorded (so that it is reported) but for which no scoped resolution is attempted yet
        /// (for example the parameter names of named invocation arguments).
        NotAttempted,
        /// The target of a feature chain `left.name` whose left operand is not a plain name chain (`(a, b).r`, `f(x).y`, `(x as T).f`):
        /// PendingReference::operand is the left operand, and the name is looked up among the features of its static result type (see Resolver.h).
        /// Resolved after all other references. If the type is not known the reference is reported as not attempted, as before; if the type is
        /// known and has no such feature (PendingReference::absent) it is an unresolved reference like those of plain feature chains.
        /// Where the members of a sequence or the branches of an `if` have different features of that name, the target is the nearest feature that all of
        /// them redefine; if there is none (features that only subset a common one, or unrelated ones) it stays not attempted. Features that the type
        /// imports count as its members. The type of an operator expression, of the invocation of a behavior (`A().y`) and of a unary `as T` is not
        /// known: those chains stay not attempted.
        ChainTarget
    };

    /**
     * Marker mix-in of the placeholder elements that stand in for a reference that could not (yet) be resolved.
     * Placeholders are never contained in an element list returned by the parser or the workspace. They are only
     * reachable through the relationship that refers to them, and can be identified with isUnresolved().
     */
    class UnresolvedMarker {
    public:
        virtual ~UnresolvedMarker() = default;
        /// The name exactly as written in the source (for example "ScalarValues::Real").
        std::string reference;
    };

    class UnresolvedElement : public KerML::Entities::Element, public UnresolvedMarker {};
    class UnresolvedType : public KerML::Entities::Type, public UnresolvedMarker {};
    class UnresolvedClassifier : public KerML::Entities::Classifier, public UnresolvedMarker {};
    class UnresolvedFeature : public KerML::Entities::Feature, public UnresolvedMarker {};

    /// True if @p text (the text of an expression without white space) is a plain name or a chain of names, `a`, `A::b`, `a.b.c`,
    /// that a reference can be resolved from; false for anything else, for example `(x as T)`, `f(x)` or `a + b`.
    inline bool isPlainNameChain(const std::string& text) {
        if (text.empty() || (text.front() >= '0' && text.front() <= '9')) return false;
        bool quoted = false;
        for (size_t i = 0; i < text.size(); ++i) {
            const char c = text[i];
            if (quoted) {
                if (c == '\\' && i + 1 < text.size()) ++i;
                else if (c == '\'') quoted = false;
                continue;
            }
            if (c == '\'') {
                quoted = true;
            } else if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == ':' || c == '.' || c == '$')) {
                return false;
            }
        }
        return !quoted && text.back() != '.' && text.back() != ':';
    }

    /// True if @p element is a placeholder for an unresolved reference.
    inline bool isUnresolved(const KerML::Entities::Element* element) {
        return element != nullptr && dynamic_cast<const UnresolvedMarker*>(element) != nullptr;
    }
    inline bool isUnresolved(const std::shared_ptr<KerML::Entities::Element>& element) {
        return isUnresolved(element.get());
    }

    /**
     * Creates a placeholder of the class matching @p kind (Type, Classifier, Feature or Element) whose declared name is
     * the last segment of @p name.
     */
    std::shared_ptr<KerML::Entities::Element> SYSMLV2FILE_EXPORT makePlaceholder(ReferenceKind kind, const std::string& name);

    /**
     * One name that has to be resolved.
     */
    struct PendingReference {
        /// The name as written, for example "A", "A::B", "'x y'::z" or a feature chain "a.b.c".
        std::string name;
        ReferenceKind kind = ReferenceKind::Element;
        ReferenceRole role = ReferenceRole::Plain;
        /// The element the reference is written in / belongs to.
        std::shared_ptr<KerML::Entities::Element> context;
        /// true: resolve from the scope enclosing @c context (the reference belongs to a relationship owned by
        /// @c context, e.g. the typing of a feature). false: resolve from @c context itself (the reference is written
        /// in the body of the namespace @c context, e.g. an alias, an import or a comment target).
        bool relativeToOwner = true;
        /// Generalization / Redefinition: the element that receives the resolved target as a general type.
        std::shared_ptr<KerML::Entities::Element> specific;
        /// The placeholder currently used by the model in place of the target.
        std::shared_ptr<KerML::Entities::Element> placeholder;
        /// Patches the model with the resolved target. Called at most once, only on success.
        std::function<void(const std::shared_ptr<KerML::Entities::Element>&)> apply;
        int line = -1;
        int column = -1;
        /// The reference is written in the bounds of a multiplicity (`[kg]`, `[n]`). Does not change how it is resolved; it lets the workspace
        /// warn when a unit stands there (the unit belongs after the value).
        bool inMultiplicity = false;
        /// ChainTarget: the left operand of the chain (an expression of the model).
        std::shared_ptr<KerML::Entities::Element> operand;
        /// Set by the resolver. ChainTarget: the static type of the operand is known and has no feature of that name (or several that are
        /// unrelated); the reference is then reported as unresolved instead of not attempted.
        bool absent = false;
        /// ChainTarget with `absent`: the name(s) of the type(s) of the operand in which the name was looked up (for the message).
        std::string absentIn;
        /// Set by the resolver.
        std::shared_ptr<KerML::Entities::Element> resolvedTarget;
        /// Index of the source (Workspace) this reference was recorded for; set by the workspace.
        size_t source = 0;
        /// Position of the reference in its source (set by the workspace; XmiDocument::generalizations(): the position of the relationship
        /// in the document). Together with `source` it orders the references as they are declared; it does not change when other
        /// sources are added or replaced.
        size_t order = 0;
        bool resolved = false;
    };

    /**
     * An `import` declaration recorded in the body of a namespace.
     */
    struct ImportRecord {
        /// Namespace that owns the import; null for an import at the root of the source.
        std::shared_ptr<KerML::Entities::Element> owner;
        /// The import model element (NamespaceImport or MembershipImport).
        std::shared_ptr<KerML::Entities::Element> element;
        /// Imported qualified name without the "::*" / "::**" suffix.
        std::string target;
        /// true for `import A::B;` (imports the membership), false for `import A::*;` / `import A::**;`.
        bool isMembershipImport = false;
        bool isRecursive = false;
        bool isImportAll = false;
        KerML::Entities::VisibilityKind visibility = KerML::Entities::PRIVATE;
        /// Filled by the resolver: the imported namespace or element.
        std::shared_ptr<KerML::Entities::Element> resolvedTarget;
        int line = -1;
        int column = -1;
    };

    /**
     * An `alias` membership recorded in the body of a namespace.
     */
    struct AliasRecord {
        std::shared_ptr<KerML::Entities::Element> owner;
        std::shared_ptr<KerML::Entities::Membership> membership;
        std::string name;
        std::string shortName;
        std::string target;
        KerML::Entities::VisibilityKind visibility = KerML::Entities::PUBLIC;
        /// Filled by the resolver.
        std::shared_ptr<KerML::Entities::Element> resolvedTarget;
        int line = -1;
        int column = -1;
    };

    /// A problem a listener found while building the model (not a syntax error); the Workspace reports it as a logical error.
    struct ListenerDiagnostic {
        std::string message;
        int line = -1;
        int column = -1;
        /// A warning (something that was read differently before is not read at all now) instead of an error.
        bool warning = false;
    };

    /**
     * Everything a listener records for name resolution while it walks one parse tree.
     */
    struct ResolutionData {
        /// The root namespace of the source if the listener creates one (KerML), otherwise null (SysML: the root
        /// scope consists of the top-level elements that have no owner).
        std::shared_ptr<KerML::Entities::Element> root;
        std::vector<PendingReference> references;
        std::vector<std::shared_ptr<ImportRecord>> imports;
        std::vector<std::shared_ptr<AliasRecord>> aliases;
        /// Declared visibility of the members that were declared with an explicit or default visibility.
        /// Elements not listed here are public.
        std::unordered_map<const KerML::Entities::Element*, KerML::Entities::VisibilityKind> visibility;
        /// Problems of the listener itself, e.g. a real literal that does not fit a double.
        std::vector<ListenerDiagnostic> diagnostics;
    };

    /**
     * Small helper shared by the listeners for recording references.
     */
    class SYSMLV2FILE_EXPORT ReferenceRecorder {
    public:
        ResolutionData data;

        /**
         * Creates the placeholder for @p name (see makePlaceholder) and records the reference. @p patch is called with
         * the placeholder that was handed out and the resolved element once the workspace has found it.
         * @return the placeholder to be used by the model until the reference is resolved.
         */
        template <class T = KerML::Entities::Element>
        std::shared_ptr<T> replacing(const std::string& name, ReferenceKind kind, ReferenceRole role,
                                     const std::shared_ptr<KerML::Entities::Element>& context, bool relativeToOwner,
                                     const std::shared_ptr<KerML::Entities::Element>& specific,
                                     antlr4::ParserRuleContext* position,
                                     std::function<void(const std::shared_ptr<T>&, const std::shared_ptr<T>&)> patch) {
            auto placeholder = std::dynamic_pointer_cast<T>(makePlaceholder(kind, name));
            record(placeholder, name, kind, role, context, relativeToOwner, specific, position,
                   [patch, placeholder](const std::shared_ptr<KerML::Entities::Element>& target) {
                       if (auto typed = std::dynamic_pointer_cast<T>(target)) patch(placeholder, typed);
                   });
            return placeholder;
        }

        /// Like replacing(), for patches that do not need the placeholder.
        template <class T = KerML::Entities::Element>
        std::shared_ptr<T> reference(const std::string& name, ReferenceKind kind, ReferenceRole role,
                                     const std::shared_ptr<KerML::Entities::Element>& context, bool relativeToOwner,
                                     const std::shared_ptr<KerML::Entities::Element>& specific,
                                     antlr4::ParserRuleContext* position,
                                     std::function<void(const std::shared_ptr<T>&)> patch) {
            return replacing<T>(name, kind, role, context, relativeToOwner, specific, position,
                                [patch](const std::shared_ptr<T>&, const std::shared_ptr<T>& resolved) { if (patch) patch(resolved); });
        }

        /// Records a reference for an already created placeholder.
        void record(const std::shared_ptr<KerML::Entities::Element>& placeholder, const std::string& name, ReferenceKind kind,
                    ReferenceRole role, const std::shared_ptr<KerML::Entities::Element>& context, bool relativeToOwner,
                    const std::shared_ptr<KerML::Entities::Element>& specific, antlr4::ParserRuleContext* position,
                    std::function<void(const std::shared_ptr<KerML::Entities::Element>&)> apply);
    };

    /// Replaces every occurrence of @p from by @p to in @p values.
    template <class Base, class T>
    bool replaceInVector(std::vector<std::shared_ptr<Base>>& values, const std::shared_ptr<Base>& from, const std::shared_ptr<T>& to) {
        bool changed = false;
        for (auto& value : values) {
            if (value == from) {
                value = to;
                changed = true;
            }
        }
        return changed;
    }
}
