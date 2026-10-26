//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/root/namespaces/NamespaceImport.h>
#include <kerml/root/namespaces/Namespace.h>
#include <algorithm>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {
    NamespaceImport::NamespaceImport(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
    Element(elementID, owner), Import(elementID, owner) {
        ImportedNamespace = nullptr;
        _dType = "NamespaceImport";
    }

    NamespaceImport::NamespaceImport(std::string nameOrJson, std::shared_ptr<Element> owner) :
    Element(boost::uuids::random_generator()(), owner), Import(boost::uuids::random_generator()(), owner) {
        ImportedNamespace = nullptr;
        _dType = "NamespaceImport";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::vector<std::shared_ptr<Membership>> NamespaceImport::importedMemberships(std::vector<std::shared_ptr<Namespace>> excluded) {
        if (!ImportedNamespace || std::find(excluded.begin(), excluded.end(), ImportedNamespace) != excluded.end()) {
            return {};
        }

        excluded.push_back(ImportedNamespace);
        return ImportedNamespace->visibleMemberships(excluded, isRecursive(), isImportAll());
    }

    NamespaceImport::NamespaceImport(VisibilityKind visibility, bool isRecursive, bool isImportAll, std::shared_ptr<Namespace> importOwningNamespace, std::shared_ptr<Namespace> importedNamespace, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
     Element(elementID, owner), Import(visibility, isRecursive, isImportAll, importOwningNamespace, elementID, owner) {
        _dType = "NamespaceImport";
        ImportedNamespace = importedNamespace;
    }

    std::shared_ptr<Namespace> NamespaceImport::importedNamespace() {
        return ImportedNamespace;
    }

    void NamespaceImport::setImportedNamespace(std::shared_ptr<Namespace> importedNamespace) {
        clearUnresolvedJsonReferences("importedNamespace");
        ImportedNamespace = importedNamespace;
    }
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    std::string NamespaceImport::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Import::serializeToJson());
        json["importedNamespace"] = Json::reference(unresolvedJsonReferences("importedNamespace"), NamespaceImport::importedNamespace());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void NamespaceImport::deserializeAndPopulate(const std::string& jsonString) {
        Import::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "importedNamespace", ids))
            setUnresolvedJsonReferences("importedNamespace", ids);
    }

    void NamespaceImport::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Import::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("importedNamespace")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Namespace>(lookup(ids->front()))) {
                    NamespaceImport::setImportedNamespace(std::move(target));
                    clearUnresolvedJsonReferences("importedNamespace");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("importedNamespace", *ids);
            }
        }
    }
}
// END GENERATED JSON
