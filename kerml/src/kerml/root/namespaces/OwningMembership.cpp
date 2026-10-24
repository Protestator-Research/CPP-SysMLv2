//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/namespaces/OwningMembership.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities
{
	OwningMembership::OwningMembership()
	{
		_dType = "OwningMembership";
	}

	std::string OwningMembership::path()
	{
		//TODO Implement
		return Membership::path();
	}

	std::string OwningMembership::ownedMemberElementId()
	{
		auto element = ownedMemberElement();
        return element ? element->elementId() : boost::lexical_cast<std::string>(OwnedMemberElementId);
	}

	boost::uuids::uuid OwningMembership::ownedMemberElementIdAsUuid()
	{
		auto element = ownedMemberElement();
        return element ? element->elementIdAsUUID() : OwnedMemberElementId;
	}

	void OwningMembership::setOwnedMemberElementId(std::string ownedMemeberElementId)
	{
		OwnedMemberElementId = boost::uuids::string_generator()(ownedMemeberElementId);
	}

	void OwningMembership::setOwnedMemberElementId(boost::uuids::uuid ownedMemeberElementId)
	{
		OwnedMemberElementId = ownedMemeberElementId;
	}

	std::string OwningMembership::ownedMemberShortName()
	{
		auto element = ownedMemberElement();
        return element ? element->declaredShortName().value_or("") : OwnedMemberShortName;
	}

	void OwningMembership::setOwnedMemberShortName(std::string ownedMemberShortName)
	{
		OwnedMemberShortName = ownedMemberShortName;
	}

	std::string OwningMembership::ownedMemberName()
	{
		auto element = ownedMemberElement();
        return element ? element->declaredName().value_or("") : OwnedMemberName;
	}

	void OwningMembership::setOwnedMemberName(std::string ownedMemberName)
	{
		OwnedMemberName = ownedMemberName;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    OwningMembership::OwningMembership(const std::string& nameOrJson) :
        OwningMembership() {
        _dType = "OwningMembership";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string OwningMembership::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Membership::serializeToJson());
        json["ownedMemberElement"] = Json::reference(unresolvedJsonReferences("ownedMemberElement"), OwningMembership::ownedMemberElement());
        json["ownedMemberElementId"] = Json::idText(OwningMembership::ownedMemberElementId(), unresolvedJsonReferences("memberElement"));
        json["ownedMemberShortName"] = Json::value(OwningMembership::ownedMemberShortName());
        json["ownedMemberName"] = Json::value(OwningMembership::ownedMemberName());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void OwningMembership::deserializeAndPopulate(const std::string& jsonString) {
        Membership::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "ownedMemberElement", ids))
            setUnresolvedJsonReferences("ownedMemberElement", ids);
    }

    void OwningMembership::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Membership::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("ownedMemberElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(ids->front()))) {
                    OwningMembership::setOwnedMemberElement(std::move(target));
                    clearUnresolvedJsonReferences("ownedMemberElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedMemberElement", *ids);
            }
        }
    }
}
// END GENERATED JSON
