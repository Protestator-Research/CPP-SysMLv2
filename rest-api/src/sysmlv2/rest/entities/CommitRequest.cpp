#include <iostream>
#include <sysmlv2/rest/entities/CommitRequest.h>
#include <sysmlv2/rest/entities/DataVersion.h>

namespace SysMLv2::REST
{
	CommitRequest::CommitRequest(std::string jsonStringOrName)
	{
	}

	CommitRequest::CommitRequest(std::string description, std::vector<std::shared_ptr<DataVersion>> changeRequested)
	{
	}

	std::string CommitRequest::serializeToJson()
	{

		std::string jsonElements = "[\r\n";
		for (size_t i = 0; i < ChangeRequested.size(); i++) {
			std::cout << "Adding JSON ELEMENT " << i << std::endl;
			jsonElements += ChangeRequested[i]->serializeToJson();
			std::cout << "\r" << jsonElements << std::endl;

			if (i != (ChangeRequested.size() - 1))
				jsonElements += ",\r\n";
		}
		jsonElements += "]\r\n";


	}

	std::vector<std::shared_ptr<DataVersion>> CommitRequest::changeRequested()
	{
		return ChangeRequested;
	}

	std::string CommitRequest::description()
	{
		return Description;
	}
}
