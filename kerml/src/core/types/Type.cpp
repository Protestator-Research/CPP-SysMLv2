//
// Created by Moritz Herzog on 25.03.25.
//

#include "Type.h"
#include "../features/Multiplicity.h"

namespace KerML {
    namespace Entities {
        Type::Type(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
            Namespace(elementID, owner) {

        }

        Type::Type(std::string namespaceName, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
            Namespace(namespaceName, elementID, owner) {

        }

        std::vector<std::shared_ptr<Membership>>
        Type::visibleMemberships(std::vector<std::shared_ptr<Namespace>> excluded, bool isRecursive, bool includeAll) {
            return Namespace::visibleMemberships(excluded, isRecursive, includeAll);
        }

        std::vector<std::shared_ptr<Membership>>
        Type::inheritedMemberships(std::vector<std::shared_ptr<Namespace>> excludedNamespace,
                                   std::vector<std::shared_ptr<Type>> excludedTypes, bool excludeImplied) {
            return std::vector<std::shared_ptr<Membership>>();
        }

        std::vector<std::shared_ptr<Membership>>
        Type::inheritableMemberships(std::vector<std::shared_ptr<Namespace>> excludedNamespace,
                                     std::vector<std::shared_ptr<Type>> excludedTypes, bool excludeImplied) {
            return std::vector<std::shared_ptr<Membership>>();
        }

        std::vector<std::shared_ptr<Membership>>
        Type::nonPrivateMemberships(std::vector<std::shared_ptr<Namespace>> excludedNamespace,
                                    std::vector<std::shared_ptr<Type>> excludedTypes, bool excludeImplied) {
            return std::vector<std::shared_ptr<Membership>>();
        }

        std::vector<std::shared_ptr<Membership>>
        Type::removeRedefinedFeature(std::vector<std::shared_ptr<Membership>> memberships) {
            return std::vector<std::shared_ptr<Membership>>();
        }

        std::vector<std::shared_ptr<Feature>> Type::allRedefinedFeaturesOf(std::shared_ptr<Membership> membership) {
            return std::vector<std::shared_ptr<Feature>>();
        }

        FeatureDirectionKind Type::directionOf(std::shared_ptr<Feature> feature) {
            return OUT;
        }

        FeatureDirectionKind
        Type::directionOfExcluding(std::shared_ptr<Feature> feature, std::vector<std::shared_ptr<Type>> excluded) {
            return OUT;
        }

        std::vector<std::shared_ptr<Type>> Type::supertypes(bool excludeImplied) {
            return std::vector<std::shared_ptr<Type>>();
        }

        std::vector<std::shared_ptr<Type>> Type::allSupertypes() {
            return std::vector<std::shared_ptr<Type>>();
        }

        bool Type::specializes(std::shared_ptr<Type> supertype) {
            return false;
        }

        bool Type::specializesFromLibrary(std::string libraryTypeName) {
            return false;
        }

        void Type::isCompatibleWith(std::shared_ptr<Type> otherType) {

        }

        std::vector<std::shared_ptr<Multiplicity>> Type::multiplicities() {
            return { };
        }

        bool Type::isAbstract() {
            return false;
        }

        void Type::setAbstract(bool isAbstract) {

        }

        bool Type::isSufficient() {
            return false;
        }

        void Type::setIsSufficient(bool isSuffdidient) {

        }

        void Type::setIsConjugated(bool isConjugated) {

        }

        bool Type::isConjugated() {
            return false;
        }

        std::vector<std::shared_ptr<Type>> Type::differencingType() const{
            return std::vector<std::shared_ptr<Type>>();
        }

        void Type::setDifferencingType(std::vector<std::shared_ptr<Type>> differencingType) {

        }

        void Type::appendDifferencingType(std::shared_ptr<Type> differencingType) {

        }

        void Type::appendDifferencingType(std::vector<std::shared_ptr<Type>> differencingType) {

        }

        std::vector<std::shared_ptr<Feature>> Type::directedFeature() const {
            return std::vector<std::shared_ptr<Feature>>();
        }
    } // Entities
} // KerML