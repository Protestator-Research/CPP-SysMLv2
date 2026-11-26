//
// The ids of the elements of the model libraries, see LibraryElementIds.h.
//
#include <kerml/model/LibraryElementIds.h>
#include <kerml/KerML.h>

#include <boost/uuid/name_generator_sha1.hpp>
#include <boost/uuid/namespaces.hpp>
#include <optional>
#include <string>
#include <unordered_set>

namespace KerML::Entities {
    namespace {
        /// Whether an element whose path is made of positions (no qualified name identifies it: unnamed elements, the relationships that are not the
        /// membership of a named element, the memberships of unnamed elements) gets an id of the model library. The one place that decides it.
        /// Off: the ownership structure that the text parser builds for these elements is not the one of the official model (the official XMI has
        /// implied elements, other relationships and another order), so the positions that their paths are made of would put the official ids on
        /// other elements. Turn it on once the parser builds the same structure; everything else (root namespace, package, named elements and
        /// their memberships) does not depend on it.
        constexpr bool kPositionalIds = false;

        bool getsPositionalId(const Element&) {
            return kPositionalIds;
        }

        /// The path of an element that is identified by its position (the paths below it are positional as well, or named: a named element does not
        /// depend on the path of its owner): not made at all while no positional id is assigned.
        std::string positionalPath(const std::string& owner, std::size_t index) {
            return kPositionalIds ? owner + "/" + std::to_string(index) : std::string();
        }

        /// An element of the walk with what its owner could tell about it.
        struct Frame {
            Element* element = nullptr;
            /// The qualified name of the element, if it has one.
            std::optional<std::string> qualifiedName;
            /// The path of the element.
            std::string path;
            /// Relationships: the qualified name of the element that the OwningMembership owns, if it has one, and that element.
            std::optional<std::string> memberQualifiedName;
            const Element* member = nullptr;
        };

        bool isOwnedBy(const Element& element, const Element* owner) {
            return owner != nullptr && element.owningRelationship().get() == owner;
        }
    }

    boost::uuids::uuid libraryPackageId(LibraryLanguage language, const std::string& packageName) {
        const std::string url = (language == LibraryLanguage::KerML ? "https://www.omg.org/spec/KerML/" : "https://www.omg.org/spec/SysML/") + packageName;
        return boost::uuids::name_generator_sha1(boost::uuids::ns::url())(url.data(), url.size());
    }

    const std::string& defaultLibraryVendorBase() {
        static const std::string base = "https://sysml.protestator-research.com/";
        return base;
    }

    std::string normalizeLibraryVendorBase(const std::string& vendorBase) {
        const auto first = vendorBase.find_first_not_of(" \t\r\n");
        if (first == std::string::npos)
            return defaultLibraryVendorBase();
        const std::string trimmed = vendorBase.substr(first, vendorBase.find_last_not_of(" \t\r\n") - first + 1);
        return trimmed.back() == '/' ? trimmed : trimmed + "/";
    }

    boost::uuids::uuid vendorPackageId(const std::string& vendorBase, const std::string& packageName) {
        const std::string url = normalizeLibraryVendorBase(vendorBase) + packageName;
        return boost::uuids::name_generator_sha1(boost::uuids::ns::url())(url.data(), url.size());
    }

    boost::uuids::uuid libraryPackageIdOf(const LibraryPackage& package, LibraryLanguage language, const std::string& vendorBase) {
        const std::string name = package.declaredName().value_or("");
        return package.isStandard() ? libraryPackageId(language, name) : vendorPackageId(vendorBase, name);
    }

    boost::uuids::uuid libraryElementId(const boost::uuids::uuid& packageId, const std::string& path) {
        return boost::uuids::name_generator_sha1(packageId)(path.data(), path.size());
    }

    bool getsLibraryIds(const std::shared_ptr<Element>& package) {
        const auto libraryPackage = std::dynamic_pointer_cast<LibraryPackage>(package);
        if (!libraryPackage || !libraryPackage->declaredName().has_value())
            return false;
        const auto membership = std::dynamic_pointer_cast<OwningMembership>(libraryPackage->owningRelationship());
        if (!membership)
            return false;
        const auto root = std::dynamic_pointer_cast<Namespace>(membership->owningRelatedElement());
        return root && !root->owningRelationship();
    }

    std::size_t assignLibraryElementIds(const std::shared_ptr<Element>& package, LibraryLanguage language, std::vector<Element*>* assigned,
                                        std::set<boost::uuids::uuid>* taken, const std::string& vendorBase) {
        if (!getsLibraryIds(package))
            return 0;
        const auto membership = std::dynamic_pointer_cast<OwningMembership>(package->owningRelationship());
        const auto root = std::dynamic_pointer_cast<Namespace>(membership->owningRelatedElement());

        // The position of the membership among the relationships of the root namespace, and the members with the same name before the package.
        const std::string name = package->escapedName().value_or("");
        const auto rootRelationships = root->ownedRelationship();
        std::size_t position = 0;
        bool nameTaken = false;
        for (std::size_t index = 0; index < rootRelationships.size() && position == 0; ++index) {
            if (rootRelationships[index] == membership) {
                position = index + 1;
                break;
            }
            const auto earlier = std::dynamic_pointer_cast<OwningMembership>(rootRelationships[index]);
            const auto member = earlier ? earlier->ownedMemberElement() : nullptr;
            if (member && member->escapedName() == name)
                nameTaken = true;
        }
        if (position == 0 || membership->owningRelationship() || membership->owningRelatedElement() != root)
            return 0;   // not in the list of its owner

        const boost::uuids::uuid packageId = libraryPackageIdOf(*std::dynamic_pointer_cast<LibraryPackage>(package), language, vendorBase);
        std::set<boost::uuids::uuid> ownTaken;
        std::set<boost::uuids::uuid>& used = taken ? *taken : ownTaken;
        std::size_t count = 0;
        const auto assign = [&](Element& element, const boost::uuids::uuid& id) {
            if (!used.insert(id).second)
                return;
            element.assignElementId(id);
            ++count;
            if (assigned)
                assigned->push_back(&element);
        };

        const std::optional<std::string> packageName = nameTaken ? std::nullopt : std::optional<std::string>(name);
        const std::string membershipPath = packageName ? *packageName + "/owningMembership" : "/" + std::to_string(position);
        const std::string packagePath = packageName ? *packageName : membershipPath + "/1";
        if (position == 1)
            assign(*root, libraryElementId(packageId, packagePath + "/owner"));
        if (packageName || getsPositionalId(*membership))
            assign(*membership, libraryElementId(packageId, membershipPath));
        assign(*package, packageId);

        // The elements below the package, in the order of the text: every element and relationship is made from the information of its owner.
        std::unordered_set<const Element*> visited;
        std::vector<Frame> pending;
        pending.push_back(Frame{package.get(), packageName, packagePath, std::nullopt, nullptr});
        std::vector<Frame> children;
        while (!pending.empty()) {
            const Frame frame = std::move(pending.back());
            pending.pop_back();
            if (!visited.insert(frame.element).second)
                continue;
            const bool isPackage = frame.element == package.get();
            if (!isPackage && (frame.qualifiedName.has_value() || frame.memberQualifiedName.has_value() || getsPositionalId(*frame.element)))
                assign(*frame.element, libraryElementId(packageId, frame.path));

            children.clear();
            // The elements that a relationship owns, counted from 1.
            if (const auto* relationship = dynamic_cast<const Relationship*>(frame.element)) {
                std::size_t index = 0;
                for (const auto& owned : relationship->ownedRelatedElement()) {
                    ++index;
                    if (!owned || !isOwnedBy(*owned, relationship))
                        continue;
                    // (the qualified name of the member of an OwningMembership was made by the owner of the membership)
                    std::optional<std::string> qualifiedName = owned.get() == frame.member ? frame.memberQualifiedName : std::nullopt;
                    std::string path = qualifiedName ? *qualifiedName : positionalPath(frame.path, index);
                    children.push_back(Frame{owned.get(), std::move(qualifiedName), std::move(path), std::nullopt, nullptr});
                }
            }
            // The relationships that an element owns, counted from 1: the names of the members of a namespace are made here, the first of the same name wins.
            const bool isNamespace = dynamic_cast<const Namespace*>(frame.element) != nullptr;
            std::unordered_set<std::string> names;
            std::size_t index = 0;
            for (const auto& owned : frame.element->ownedRelationship()) {
                ++index;
                if (!owned || owned->owningRelationship() || owned->owningRelatedElement().get() != frame.element)
                    continue;
                std::optional<std::string> memberName;
                const Element* member = nullptr;
                if (const auto owning = std::dynamic_pointer_cast<OwningMembership>(owned); owning && isNamespace) {
                    const auto owner = owning->ownedMemberElement();
                    if (owner && isOwnedBy(*owner, owned.get())) {
                        member = owner.get();
                        const auto escaped = owner->escapedName();
                        if (escaped.has_value() && names.insert(escaped.value()).second && frame.qualifiedName.has_value())
                            memberName = *frame.qualifiedName + "::" + escaped.value();
                    }
                }
                std::string path = memberName ? *memberName + "/owningMembership" : positionalPath(frame.path, index);
                children.push_back(Frame{owned.get(), std::nullopt, std::move(path), std::move(memberName), member});
            }
            for (auto it = children.rbegin(); it != children.rend(); ++it)
                pending.push_back(std::move(*it));
        }
        return count;
    }
} // KerML::Entities
