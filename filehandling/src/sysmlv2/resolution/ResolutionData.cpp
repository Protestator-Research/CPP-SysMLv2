//
// Deferred name-resolution data recorded by the parse listeners. See ResolutionData.h.
//
#include <sysmlv2/resolution/ResolutionData.h>

#include "antlr4-runtime.h"

namespace SysMLv2::Files {

    namespace {
        // The placeholder of `A::b` is named `b`; a feature chain `a.b` keeps its text as the name.
        std::string lastSegment(const std::string& name) {
            const auto colon = name.rfind("::");
            return colon == std::string::npos ? name : name.substr(colon + 2);
        }
    }

    std::shared_ptr<KerML::Entities::Element> makePlaceholder(ReferenceKind kind, const std::string& name) {
        std::shared_ptr<KerML::Entities::Element> placeholder;
        UnresolvedMarker* marker = nullptr;
        switch (kind) {
            case ReferenceKind::Type: {
                auto typed = std::make_shared<UnresolvedType>();
                marker = typed.get();
                placeholder = typed;
                break;
            }
            case ReferenceKind::Classifier: {
                auto typed = std::make_shared<UnresolvedClassifier>();
                marker = typed.get();
                placeholder = typed;
                break;
            }
            case ReferenceKind::Feature: {
                auto typed = std::make_shared<UnresolvedFeature>();
                marker = typed.get();
                placeholder = typed;
                break;
            }
            case ReferenceKind::Element:
            case ReferenceKind::Namespace:
            default: {
                auto typed = std::make_shared<UnresolvedElement>();
                marker = typed.get();
                placeholder = typed;
                break;
            }
        }
        marker->reference = name;
        placeholder->setDeclaredName(lastSegment(name));
        return placeholder;
    }

    void ReferenceRecorder::record(const std::shared_ptr<KerML::Entities::Element>& placeholder, const std::string& name,
                                   ReferenceKind kind, ReferenceRole role, const std::shared_ptr<KerML::Entities::Element>& context,
                                   bool relativeToOwner, const std::shared_ptr<KerML::Entities::Element>& specific,
                                   antlr4::ParserRuleContext* position,
                                   std::function<void(const std::shared_ptr<KerML::Entities::Element>&)> apply) {
        PendingReference reference;
        reference.name = name;
        reference.kind = kind;
        reference.role = role;
        reference.context = context;
        reference.relativeToOwner = relativeToOwner;
        reference.specific = specific;
        reference.placeholder = placeholder;
        reference.apply = std::move(apply);
        if (position != nullptr && position->getStart() != nullptr) {
            reference.line = static_cast<int>(position->getStart()->getLine());
            reference.column = static_cast<int>(position->getStart()->getCharPositionInLine());
        }
        data.references.push_back(std::move(reference));
    }
}
