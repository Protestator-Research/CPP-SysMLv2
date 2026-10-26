//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/root/namespaces/MembershipImport.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {
	MembershipImport::MembershipImport()
	{
		_dType = "MembershipImport";
	}

	std::vector<std::shared_ptr<Membership>> MembershipImport::importedMemberships(
		std::vector<std::shared_ptr<Namespace>>)
	{
		//TODO Implement
        return std::vector<std::shared_ptr<Membership>>();
	}

	std::shared_ptr<Membership> MembershipImport::importedMembership() const
	{
		return ImportedMembership;
	}

	void MembershipImport::setImportedMembership(std::shared_ptr<Membership> importedMembership)
	{
		clearUnresolvedJsonReferences("importedMembership");
		ImportedMembership = importedMembership;
	}
} // KerML::Entities

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    MembershipImport::MembershipImport(const std::string& nameOrJson) :
        MembershipImport() {
        _dType = "MembershipImport";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string MembershipImport::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Import::serializeToJson());
        json["importedMembership"] = Json::reference(unresolvedJsonReferences("importedMembership"), MembershipImport::importedMembership());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void MembershipImport::deserializeAndPopulate(const std::string& jsonString) {
        Import::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "importedMembership", ids))
            setUnresolvedJsonReferences("importedMembership", ids);
    }

    void MembershipImport::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Import::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("importedMembership")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Membership>(lookup(ids->front()))) {
                    MembershipImport::setImportedMembership(std::move(target));
                    clearUnresolvedJsonReferences("importedMembership");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("importedMembership", *ids);
            }
        }
    }
}
// END GENERATED JSON
