//
// Abstract-syntax ownership of a parsed source (KerML 8.3.2 Root, 9.2.5 Core, SysML 8.3).
//
// The listeners build the elements of a source and record which element declared which (the owned elements of the
// enclosing element). Once a source is parsed, buildOwnership() adds the abstract-syntax structure:
//   - every owned member of a namespace is related to it through exactly one membership (OwningMembership or a subclass:
//     FeatureMembership, EndFeatureMembership, ParameterMembership, ReturnParameterMembership, ResultExpressionMembership,
//     VariantMembership, SubjectMembership, ActorMembership, ...); the owningRelationship, owner, owningRelatedElement,
//     memberElement and the namespace / type collections (ownedMembership, ownedMember, ownedFeatureMembership, ownedFeature, ...) are set;
//   - every other owned relationship (Specialization, FeatureTyping, Import, ...) gets its owning related element and owner;
//   - the top level elements of the source are owned by a root namespace.
// Memberships that a listener already created (aliases, `variant`, `subject`, the wrappers of the KerML listener) are completed,
// never duplicated. The function may be applied to a source once; it is idempotent.
//
#pragma once

#include <sysmlv2/sysmlv2file_global.h>
#include <kerml/root/elements/Element.h>
#include <kerml/root/namespaces/VisibilityKind.h>

#include <memory>
#include <unordered_map>
#include <vector>

namespace SysMLv2::Files {

    /**
     * The membership a listener wants for a member. Automatic lets buildOwnership decide (a feature of a type: FeatureMembership,
     * anything else: OwningMembership).
     */
    enum class MembershipKind {
        Automatic,
        Owning,
        Feature,
        EndFeature,
        Parameter,
        ReturnParameter,
        ResultExpression,
        Variant,
        Subject,
        Actor,
        Stakeholder,
        Objective,
        AssumedConstraint,
        RequiredConstraint,
        FramedConcern,
        VerifiedRequirement,
        EntryAction,
        DoAction,
        ExitAction,
        TriggerAction,
        GuardExpression,
        EffectBehavior,
        ViewRendering,
        ElementFilter
    };

    using MembershipKinds = std::unordered_map<const KerML::Entities::Element*, MembershipKind>;

    /**
     * A member rule of a grammar that is being walked: the listener notes the kind of membership the rule stands for when the rule
     * is entered and, once the rule is left, attaches it to the element that the rule added to the enclosing element.
     */
    struct MemberMark {
        const void* context = nullptr;
        const KerML::Entities::Element* owner = nullptr;
        std::size_t ownedCount = 0;
        MembershipKind kind = MembershipKind::Automatic;
        bool hasVisibility = false;
        KerML::Entities::VisibilityKind visibility = KerML::Entities::PUBLIC;
    };

    SYSMLV2FILE_EXPORT void beginMember(std::vector<MemberMark>& marks, const void* context, MembershipKind kind,
                                        const std::shared_ptr<KerML::Entities::Element>& owner);
    /** As beginMember, for a member rule that is written with a visibility (`private feature x;`). */
    SYSMLV2FILE_EXPORT void beginMemberWithVisibility(std::vector<MemberMark>& marks, const void* context,
                                                      KerML::Entities::VisibilityKind visibility,
                                                      const std::shared_ptr<KerML::Entities::Element>& owner);
    /**
     * Leaves the member rule @p context (every mark that was made for it); @p owner is the element on top of the parent stack.
     * The kind of membership is recorded in @p kinds and the declared visibility in @p visibilities (if given).
     */
    SYSMLV2FILE_EXPORT void endMember(std::vector<MemberMark>& marks, const void* context,
                                      const std::shared_ptr<KerML::Entities::Element>& owner, MembershipKinds& kinds,
                                      std::unordered_map<const KerML::Entities::Element*, KerML::Entities::VisibilityKind>* visibilities = nullptr);

    struct OwnershipInput {
        /// All elements of the source in creation order. The memberships and the root namespace that are created are appended.
        std::vector<std::shared_ptr<KerML::Entities::Element>>* elements = nullptr;
        /// The root namespace of the source if the listener created one, otherwise a root namespace is created.
        std::shared_ptr<KerML::Entities::Element> root;
        /// The kind of membership wanted for a member (see MembershipKind); members that are not listed are Automatic.
        MembershipKinds kinds;
        /// The declared visibility of members (members that are not listed keep the visibility of their membership, public by default).
        const std::unordered_map<const KerML::Entities::Element*, KerML::Entities::VisibilityKind>* visibility = nullptr;
        /// true if the created root namespace is to be appended to the elements (the KerML listener does this for its own root).
        bool appendRoot = false;
    };

    /**
     * Builds the ownership structure of one source.
     * @return the root namespace that owns the top level elements of the source.
     */
    SYSMLV2FILE_EXPORT std::shared_ptr<KerML::Entities::Element> buildOwnership(OwnershipInput& input);
}
