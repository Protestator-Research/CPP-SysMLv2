//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/Multiplicity.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {
	Multiplicity::Multiplicity(unsigned minimum)
	{
		_dType = "Multiplicity";
		MinimumNumber = minimum;
		MaximumNumber = MinimumNumber;
	}

	Multiplicity::Multiplicity(unsigned minimum, unsigned maximum)
	{
		_dType = "Multiplicity";
		MinimumNumber = minimum;
		MaximumNumber = maximum;
	}

	Multiplicity::Multiplicity(unsigned minimum, bool unlimited)
	{
		_dType = "Multiplicity";
		MinimumNumber = minimum;
		setIsUnlimited(unlimited);
	}

	unsigned Multiplicity::minimum() const
	{
		return MinimumNumber;
	}

	void Multiplicity::setMinimum(unsigned minimum)
	{
		MinimumNumber = minimum;
	}

	unsigned Multiplicity::maximum() const
	{
		return MaximumNumber;
	}

	void Multiplicity::setMaximum(unsigned maximum)
	{
		MaximumNumber = maximum;
	}

	bool Multiplicity::isUnlimited() const
	{
		return MaximumNumber == MinimumNumber;
	}

	void Multiplicity::setIsUnlimited(bool isUnlimited)
	{
		if (isUnlimited)
			MaximumNumber = MinimumNumber;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Multiplicity::Multiplicity(const std::string& nameOrJson) :
        Multiplicity() {
        _dType = "Multiplicity";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Multiplicity::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Feature::serializeToJson());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Multiplicity::deserializeAndPopulate(const std::string& jsonString) {
        Feature::deserializeAndPopulate(jsonString);
    }

    void Multiplicity::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Feature::resolveJsonReferences(lookup);
    }
}
// END GENERATED JSON
