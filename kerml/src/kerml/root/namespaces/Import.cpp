//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/root/namespaces/Import.h>
#include <kerml/root/namespaces/Namespace.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML {
    namespace Entities {
        Import::Import(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) : Element(elementID, owner), Relationship(elementID, owner) {
            ImportOwningNamespace = nullptr;
            Visibility = VisibilityKind::PRIVATE;
            IsImportAll = false;
            IsRecursive = false;
            _dType = "Import";
        }

        Import::Import(std::string nameOrJson, std::shared_ptr<Element> owner) :
            Element(boost::uuids::random_generator()(), owner), Relationship(boost::uuids::random_generator()(), owner) {
            ImportOwningNamespace = nullptr;
            Visibility = VisibilityKind::PRIVATE;
            IsImportAll = false;
            IsRecursive = false;
            _dType = "Import";
            if (Json::looksLikeJson(nameOrJson)) {
                deserializeAndPopulate(nameOrJson);
                captureJsonSource(nameOrJson);
            } else {
                setDeclaredName(nameOrJson);
            }
        }

        Import::Import(VisibilityKind visibility, bool isRecursive, bool isImportAll,
                       std::shared_ptr<Namespace> importOwningNamespace, boost::uuids::uuid elementID,
                       std::shared_ptr<Element> owner) : Element(elementID, owner), Relationship(elementID,owner){
            Visibility = visibility;
            IsImportAll = isImportAll;
            IsRecursive = isRecursive;
            ImportOwningNamespace = std::move(importOwningNamespace);
            _dType = "Import";
        }

        void Import::setVisibility(VisibilityKind visibility) {
            Visibility = visibility;
        }

        VisibilityKind Import::visibility() const {
            return Visibility;
        }

        bool Import::isImportAll() const {
            return IsImportAll;
        }

        void Import::setIsImportAll(bool isImportAll) {
            IsImportAll = isImportAll;
        }

        bool Import::isRecursive() const {
            return IsRecursive;
        }

        void Import::setIsRecursive(bool isRecursive) {
            IsRecursive = isRecursive;
        }

        std::shared_ptr<Namespace> Import::importOwningNamespace() const {
            return ImportOwningNamespace;
        }

        void Import::setImportOwningNamespace(const std::shared_ptr<Namespace>& importOwningNamespace) {
            clearUnresolvedJsonReferences("importOwningNamespace");
            ImportOwningNamespace = importOwningNamespace;
        }
    } // Entities
} // KerML

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    std::string Import::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["importOwningNamespace"] = Json::reference(unresolvedJsonReferences("importOwningNamespace"), Import::importOwningNamespace());
        json["visibility"] = Json::value(Import::visibility());
        json["isRecursive"] = Json::value(Import::isRecursive());
        json["isImportAll"] = Json::value(Import::isImportAll());
        json["importedElement"] = Json::reference(unresolvedJsonReferences("importedElement"), Import::importedElement());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Import::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "importOwningNamespace", ids))
            setUnresolvedJsonReferences("importOwningNamespace", ids);
        {
            VisibilityKind value{};
            if (Json::readEnum(json, "visibility", value)) {
                try {
                    Import::setVisibility(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        {
            bool value{};
            if (Json::readBool(json, "isRecursive", value)) {
                try {
                    Import::setIsRecursive(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        {
            bool value{};
            if (Json::readBool(json, "isImportAll", value)) {
                try {
                    Import::setIsImportAll(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
    }

    void Import::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("importOwningNamespace")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Namespace>(lookup(ids->front()))) {
                    Import::setImportOwningNamespace(std::move(target));
                    clearUnresolvedJsonReferences("importOwningNamespace");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("importOwningNamespace", *ids);
            }
        }
    }
}
// END GENERATED JSON
