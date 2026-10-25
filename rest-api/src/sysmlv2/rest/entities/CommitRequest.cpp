#include <nlohmann/json.hpp>
#include <stdexcept>
#include <sysmlv2/rest/entities/CommitRequest.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include "RestJson.h"

namespace SysMLv2::REST
{
	CommitRequest::CommitRequest(const std::string& jsonStringOrDescription) :
	Type("Commit")
	{
		if (Internal::looksLikeJson(jsonStringOrDescription))
			CommitRequest::deserializeAndPopulate(jsonStringOrDescription);
		else
			Description = jsonStringOrDescription;
	}

	CommitRequest::CommitRequest(const std::string& description, const std::vector<std::shared_ptr<DataVersion>>& changeRequested,
	                             const std::vector<boost::uuids::uuid>& previousCommits) :
	Type("Commit")
	{
		Description = description;
		ChangeRequested = changeRequested;
		PreviousCommits = previousCommits;
	}

	std::string CommitRequest::serializeToJson()
	{
		nlohmann::json jsonGeneration;

		jsonGeneration[JSON_TYPE_ENTITY] = Type;
		jsonGeneration[JSON_DESCRIPTION_ENTITY] = Description;

		// create: payload (identity omitted); update: payload and identity; delete: identity and no payload.
		nlohmann::json changes = nlohmann::json::array();
		for (const auto& change : ChangeRequested) {
			if (change != nullptr)
				changes.push_back(nlohmann::json::parse(change->serializeAsRequest()));
		}
		jsonGeneration[JSON_CHANGE_ENTITY] = changes;

		if (!PreviousCommits.empty())
			Internal::writeReferences(jsonGeneration, JSON_PREVIOUS_COMMITS_ENTITY, PreviousCommits);
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

	std::vector<boost::uuids::uuid> CommitRequest::previousCommits() const
	{
		return PreviousCommits;
	}

	void CommitRequest::deserializeAndPopulate(const std::string& jsonValue)
	{
		const nlohmann::json parsedElement = Internal::parseObject(jsonValue, "CommitRequest");
		try {
			const auto type = parsedElement.find(JSON_TYPE_ENTITY);
			if (type != parsedElement.end() && type->is_string() && type->get<std::string>() == "CommitRequest")
				warnDeprecated("JSON \"@type\": \"CommitRequest\"", "\"@type\": \"Commit\"");

			Description = Internal::readOptionalString(parsedElement, JSON_DESCRIPTION_ENTITY);

			ChangeRequested.clear();
			const auto changeEntry = parsedElement.find(JSON_CHANGE_ENTITY);
			if (changeEntry != parsedElement.end() && !changeEntry->is_null()) {
				if (!changeEntry->is_array())
					throw std::invalid_argument("'" + JSON_CHANGE_ENTITY + "' must be an array or null");
				// Null entries are skipped, like in the other arrays.
				for (const auto& value : *changeEntry)
					if (!value.is_null())
						ChangeRequested.push_back(std::make_shared<DataVersion>(value.dump()));
			}

			PreviousCommits = Internal::readReferences(parsedElement, JSON_PREVIOUS_COMMITS_ENTITY, JSON_PREV_COMMITS);
		} catch (const std::exception& ex) {
			throw std::invalid_argument(std::string("CommitRequest: ") + ex.what());
		}
	}
}
