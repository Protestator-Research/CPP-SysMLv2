#include <kerml/KerML.h>
#include <algorithm>
#include <utility>
#include "RepresentationSupport.h"
namespace KerML::Entities {
std::vector<std::shared_ptr<Relationship>> Element::ownedRelationship() const { return OwnedRelationships; }
void Element::setOwnedRelationship(std::vector<std::shared_ptr<Relationship>> value) { detail::checkCollection(value, true, -1); OwnedRelationships = std::move(value); }
std::vector<std::shared_ptr<Element>> Element::ownedElement() const { return OwnedElements; }
void Element::setOwnedElement(std::vector<std::shared_ptr<Element>> value) { detail::checkCollection(value, true, -1); OwnedElements = std::move(value); }
std::vector<std::shared_ptr<Documentation>> Element::documentation() const { return Documentations; }
void Element::setDocumentation(std::vector<std::shared_ptr<Documentation>> value) { detail::checkCollection(value, true, -1); Documentations = std::move(value); }
std::vector<std::shared_ptr<Annotation>> Element::ownedAnnotation() const { return OwnedAnnotations; }
void Element::setOwnedAnnotation(std::vector<std::shared_ptr<Annotation>> value) { detail::checkCollection(value, true, -1); OwnedAnnotations = std::move(value); }
std::vector<std::shared_ptr<TextualRepresentation>> Element::textualRepresentation() const { return TextualRepresentations; }
void Element::setTextualRepresentation(std::vector<std::shared_ptr<TextualRepresentation>> value) { detail::checkCollection(value, true, -1); TextualRepresentations = std::move(value); }
std::shared_ptr<Relationship> Element::owningRelationship() const { return OwningRelationship; }
void Element::setOwningRelationship(std::shared_ptr<Relationship> value) { OwningRelationship = std::move(value); }
std::shared_ptr<OwningMembership> Element::owningMembership() const { return std::dynamic_pointer_cast<OwningMembership>(OwningRelationship); }
std::shared_ptr<Namespace> Element::owningNamespace() const { auto membership = owningMembership(); return membership ? membership->membershipOwningNamespace() : nullptr; }
std::optional<std::string> Element::shortName() const { return effectiveShortName(); }
std::optional<std::string> Element::name() const { return effectiveName(); }
std::optional<std::string> Element::qualifiedName() const { return QualifiedName.empty() ? std::optional<std::string>{} : QualifiedName; }
void Element::setQualifiedName(std::optional<std::string> value) { QualifiedName = value.value_or(""); }
bool Element::isLibraryElement() const { return IsLibraryElement; }
void Element::setIsLibraryElement(bool value) { IsLibraryElement = value; }
std::vector<std::shared_ptr<Element>> Relationship::source() const { return Source; }
void Relationship::setSource(std::vector<std::shared_ptr<Element>> value) { detail::checkCollection(value, true, -1); Source = std::move(value); }
std::vector<std::shared_ptr<Element>> Relationship::target() const { return Target; }
void Relationship::setTarget(std::vector<std::shared_ptr<Element>> value) { detail::checkCollection(value, true, -1); Target = std::move(value); }
std::vector<std::shared_ptr<Element>> Relationship::relatedElement() const { auto result = Source; result.insert(result.end(), Target.begin(), Target.end()); return result.empty() ? RelatedElements : result; }
std::shared_ptr<Element> Membership::memberElement() const { auto values = target(); return values.empty() ? nullptr : values.front(); }
void Membership::setMemberElement(std::shared_ptr<Element> value) { setTarget(value ? std::vector<std::shared_ptr<Element>>{std::move(value)} : std::vector<std::shared_ptr<Element>>{}); }
std::shared_ptr<Namespace> Membership::membershipOwningNamespace() const { return std::dynamic_pointer_cast<Namespace>(owningRelatedElement()); }
void Membership::setMembershipOwningNamespace(std::shared_ptr<Namespace> value) { setOwningRelatedElement(value); setSource(value ? std::vector<std::shared_ptr<Element>>{std::move(value)} : std::vector<std::shared_ptr<Element>>{}); }
std::string Membership::memberElementId() const { auto member = memberElement(); return member ? member->elementId() : std::string{}; }
std::shared_ptr<Element> OwningMembership::ownedMemberElement() const { return memberElement(); }
void OwningMembership::setOwnedMemberElement(std::shared_ptr<Element> value) { setMemberElement(value); setOwnedRelatedElements(value ? std::vector<std::shared_ptr<Element>>{std::move(value)} : std::vector<std::shared_ptr<Element>>{}); }
std::shared_ptr<Element> Import::importedElement() const { if (auto membership = dynamic_cast<const MembershipImport*>(this)) { auto m = membership->importedMembership(); return m ? m->memberElement() : nullptr; } if (auto ns = dynamic_cast<const NamespaceImport*>(this)) return const_cast<NamespaceImport*>(ns)->importedNamespace(); return nullptr; }
std::shared_ptr<Type> Specialization::owningType() const { return std::dynamic_pointer_cast<Type>(owningRelatedElement()); }
void Specialization::setOwningType(std::shared_ptr<Type> value) { setOwningRelatedElement(std::move(value)); }
std::shared_ptr<Feature> FeatureTyping::owningFeature() const { return std::dynamic_pointer_cast<Feature>(owningRelatedElement()); }
void FeatureTyping::setOwningFeature(std::shared_ptr<Feature> value) { setOwningRelatedElement(std::move(value)); }
std::shared_ptr<Element> TextualRepresentation::representedElement() const { return owner(); }
void TextualRepresentation::setRepresentedElement(std::shared_ptr<Element> value) { setOwner(std::move(value)); }
std::shared_ptr<Type> Conjugation::conjugatedType() const { return const_cast<Conjugation*>(this)->conjungatedType(); }
std::shared_ptr<Type> Intersecting::typeIntersected() const { return const_cast<Intersecting*>(this)->typeIntersecting(); }
std::vector<std::shared_ptr<Feature>> Type::feature() const { return const_cast<Type*>(this)->features(); }
std::vector<std::shared_ptr<FeatureMembership>> Type::featureMembership() const { return const_cast<Type*>(this)->featureMemberships(); }
std::vector<std::shared_ptr<Membership>> Type::inheritedMembership() const { return const_cast<Type*>(this)->inheritedMemberships(); }
std::optional<std::shared_ptr<Conjugation>> Type::ownedConjugator() const { return const_cast<Type*>(this)->conjugation(); }
std::vector<std::shared_ptr<Membership>> Namespace::membership() const { return const_cast<Namespace*>(this)->memberships(); }
std::vector<std::shared_ptr<Membership>> Namespace::importedMembership() const { return const_cast<Namespace*>(this)->importedMemberships(); }
std::vector<std::shared_ptr<Element>> AnnotatingElement::annotatedElement() const { return const_cast<AnnotatingElement*>(this)->annotatedElements(); }
std::vector<std::shared_ptr<Annotation>> AnnotatingElement::annotation() const { return const_cast<AnnotatingElement*>(this)->annotations(); }
std::vector<std::shared_ptr<Annotation>> AnnotatingElement::ownedAnnotatingRelationship() const { return const_cast<AnnotatingElement*>(this)->ownedAnnotatingRelationships(); }
}
