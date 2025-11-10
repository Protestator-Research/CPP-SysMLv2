#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/CommitRequest.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

namespace SysMLv2::REST
{
	CommitRequest::CommitRequest(const std::string& jsonStringOrDescription) :
	Type("CommitRequest")
	{
		try {
			CommitRequest::deserializeAndPopulate(jsonStringOrDescription);
		}
		catch (...)
		{
			Description = jsonStringOrDescription;
		}
	}

	CommitRequest::CommitRequest(const std::string& description, const std::vector<std::shared_ptr<DataVersion>>& changeRequested) :
	Type("CommitRequest")
	{
		Description = description;
		ChangeRequested = changeRequested;
	}

	std::string CommitRequest::serializeToJson()
	{
		nlohmann::json jsonGeneration;

		jsonGeneration[JSON_TYPE_ENTITY] = Type;
		jsonGeneration[JSON_DESCRIPTION_ENTITY] = Description;

		std::string jsonElements = "[\r\n";
		for (size_t i = 0; i < ChangeRequested.size(); i++) {
			jsonElements += ChangeRequested[i]->serializeToJson();

			if (i != (ChangeRequested.size() - 1))
				jsonElements += ",\r\n";
		}
		jsonElements += "]\r\n";

		jsonGeneration[JSON_CHANGE_ENTITY] = nlohmann::json::parse(jsonElements);
		return jsonGeneration.dump(JSON_INTENT);
	}

	std::vector<std::shared_ptr<DataVersion>> CommitRequest::changeRequested()
	{
		return ChangeRequested;
	}

	std::string CommitRequest::description()
	{
		return Description;
	}

	void CommitRequest::deserializeAndPopulate(const std::string& jsonValue)
	{
		nlohmann::json parsedElement = nlohmann::json::parse(jsonValue);
		Description = parsedElement[JSON_DESCRIPTION_ENTITY];
		std::vector<nlohmann::json> arrayValues = parsedElement[JSON_CHANGE_ENTITY].get<std::vector<nlohmann::json>>();
		for (const auto value : arrayValues)
		{
			auto changeToBeAdded = std::make_shared<DataVersion>(value.dump());
			ChangeRequested.push_back(changeToBeAdded);
		}
	}
}
