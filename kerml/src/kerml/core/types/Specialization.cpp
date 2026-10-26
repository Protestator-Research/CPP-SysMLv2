//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <stdexcept>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/core/types/Type.h>
#include <kerml/core/types/Specialization.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

//---------------------------------------------------------
namespace KerML::Entities
{
	Specialization::Specialization()
	{
		_dType = "Specialization";
	}

	Specialization::Specialization(std::shared_ptr<Type> general, std::shared_ptr<Type> specific)
	{
		_dType = "Specialization";

		if (general == nullptr)
			throw std::runtime_error("General type is not allowed to be null");
		General = general;

		if (specific == nullptr)
			throw std::runtime_error("Specific type is not allowed to be null");
		Specific = specific;
	}

	std::shared_ptr<Type> Specialization::general() const
	{
		return General;
	}

	void Specialization::setGeneral(std::shared_ptr<Type> general)
	{
		clearUnresolvedJsonReferences("general");
		if (general == nullptr)
			throw std::runtime_error("General type is not allowed to be null");

		General = general;
	}

	std::shared_ptr<Type> Specialization::specific() const
	{
		return Specific;
	}

	void Specialization::setSpecific(std::shared_ptr<Type> specific)
	{
		clearUnresolvedJsonReferences("specific");
		if (specific == nullptr)
			throw std::runtime_error("Specific type is not allowed to be null");

		Specific = specific;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Specialization::Specialization(const std::string& nameOrJson) :
        Specialization() {
        _dType = "Specialization";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Specialization::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["owningType"] = Json::reference(unresolvedJsonReferences("owningType"), Specialization::owningType());
        json["general"] = Json::reference(unresolvedJsonReferences("general"), Specialization::general());
        json["specific"] = Json::reference(unresolvedJsonReferences("specific"), Specialization::specific());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Specialization::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "owningType", ids))
            setUnresolvedJsonReferences("owningType", ids);
        if (Json::readReferences(json, "general", ids))
            setUnresolvedJsonReferences("general", ids);
        if (Json::readReferences(json, "specific", ids))
            setUnresolvedJsonReferences("specific", ids);
    }

    void Specialization::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("owningType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Specialization::setOwningType(std::move(target));
                    clearUnresolvedJsonReferences("owningType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("general")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Specialization::setGeneral(std::move(target));
                    clearUnresolvedJsonReferences("general");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("general", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("specific")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Specialization::setSpecific(std::move(target));
                    clearUnresolvedJsonReferences("specific");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("specific", *ids);
            }
        }
    }
}
// END GENERATED JSON
