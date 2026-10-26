//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/dependencies/Dependency.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML {
    namespace Entities {


        void Dependency::setClient(std::shared_ptr<Element> client) {
            clearUnresolvedJsonReferences("client");
            Client = client ? std::vector<std::shared_ptr<Element>>{client} : std::vector<std::shared_ptr<Element>>{};
        }

        std::vector<std::shared_ptr<Element>> Dependency::client() const {
            return Client;
        }

        void Dependency::setSupplier(std::shared_ptr<Element> supplier) {
            clearUnresolvedJsonReferences("supplier");
            Supplier = supplier ? std::vector<std::shared_ptr<Element>>{supplier} : std::vector<std::shared_ptr<Element>>{};
        }

        std::vector<std::shared_ptr<Element>> Dependency::supplier() const {
            return Supplier;
        }

        Dependency::Dependency(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
        Element(elementID, owner), Relationship(elementID, owner) {
            initialize();
            _dType = "Dependency";
        }

        Dependency::Dependency(std::string nameOrJson, std::shared_ptr<Element> owner) :
        Element(boost::uuids::random_generator()(), owner), Relationship(boost::uuids::random_generator()(), owner) {
            initialize();
            _dType = "Dependency";
            if (Json::looksLikeJson(nameOrJson)) {
                deserializeAndPopulate(nameOrJson);
                captureJsonSource(nameOrJson);
            } else {
                setDeclaredName(nameOrJson);
            }
        }

        void Dependency::initialize() {
            Client.clear();
            Supplier.clear();
        }

    } // Entities
} // KerML
namespace KerML::Entities {
void Dependency::setClient(std::vector<std::shared_ptr<Element>> clients) { clearUnresolvedJsonReferences("client"); Client = std::move(clients); }
void Dependency::setSupplier(std::vector<std::shared_ptr<Element>> suppliers) { clearUnresolvedJsonReferences("supplier"); Supplier = std::move(suppliers); }
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    std::string Dependency::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["client"] = Json::reference(unresolvedJsonReferences("client"), Dependency::client());
        json["supplier"] = Json::reference(unresolvedJsonReferences("supplier"), Dependency::supplier());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Dependency::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "client", ids))
            setUnresolvedJsonReferences("client", ids);
        if (Json::readReferences(json, "supplier", ids))
            setUnresolvedJsonReferences("supplier", ids);
    }

    void Dependency::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("client")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Element>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Dependency::setClient(std::move(resolved));
                    clearUnresolvedJsonReferences("client");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("client", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("supplier")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Element>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Dependency::setSupplier(std::move(resolved));
                    clearUnresolvedJsonReferences("supplier");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("supplier", *ids);
            }
        }
    }
}
// END GENERATED JSON
