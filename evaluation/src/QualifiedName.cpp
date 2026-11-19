#include <sysmlv2/evaluation/QualifiedName.h>

#include <kerml/root/elements/NameEscaping.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>

#include <algorithm>
#include <typeinfo>
#include <vector>

namespace SysMLv2::Evaluation {

    namespace {
        enum class Part { Skip, Named, Unnamed };

        Part partOf(const KerML::Entities::Element& element, bool hasOwner, std::string& name) {
            // (a relationship (membership) is no name part, and the root namespace of a source has no owner)
            if (dynamic_cast<const KerML::Entities::Relationship*>(&element) != nullptr) return Part::Skip;
            if (!hasOwner && typeid(element) == typeid(KerML::Entities::Namespace)) return Part::Skip;
            std::optional<std::string> raw = element.declaredName();
            // (a feature without a declared name is known by the name of the feature it redefines: effectiveName(); the base class
            // returns the stored qualified name there, which is no name part)
            if (!raw.has_value() || raw->empty()) raw = element.effectiveName();
            if (raw.has_value() && !raw->empty() && !element.declaredName().has_value() && raw == element.qualifiedName()) raw.reset();
            if (!raw.has_value() || raw->empty()) raw = element.declaredShortName();
            if (!raw.has_value() || raw->empty()) return Part::Unnamed;
            name = KerML::Names::escapeName(*raw);
            return Part::Named;
        }
    }

    std::string qualifiedNameOf(const KerML::Entities::Element& element) {
        std::vector<std::string> parts;
        bool complete = true;
        std::vector<const KerML::Entities::Element*> visited;
        std::shared_ptr<KerML::Entities::Element> keepAlive;   // (the current element while we step to its owner)
        const KerML::Entities::Element* current = &element;
        while (current != nullptr) {
            if (std::find(visited.begin(), visited.end(), current) != visited.end()) break;   // cyclic ownership
            visited.push_back(current);
            std::shared_ptr<KerML::Entities::Element> owner = current->owner();
            std::string name;
            switch (partOf(*current, owner != nullptr, name)) {
                case Part::Skip: break;
                case Part::Named: parts.push_back(std::move(name)); break;
                case Part::Unnamed: parts.emplace_back("<unnamed>"); complete = false; break;
            }
            keepAlive = std::move(owner);   // (the owner is kept alive by its own owner chain, but do not rely on it for the leaf)
            current = keepAlive.get();
        }
        if (!complete) {
            if (const auto declared = element.qualifiedName(); declared.has_value()) return *declared;
        }
        std::string result;
        for (auto part = parts.rbegin(); part != parts.rend(); ++part) {
            if (!result.empty()) result += "::";
            result += *part;
        }
        return result;
    }

    std::string qualifiedNameOf(const std::shared_ptr<KerML::Entities::Element>& element) {
        return element ? qualifiedNameOf(*element) : std::string();
    }
}
