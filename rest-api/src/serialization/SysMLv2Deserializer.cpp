//
// Created by Moritz Herzog on 29.02.24.
//

#include "SysMLv2Deserializer.h"
#include "../entities/JSONEntities.h"
#include "../entities/Project.h"
#include "../entities/DataIdentity.h"
#include "../entities/Branch.h"
#include "../entities/Tag.h"
#include "../entities/Query.h"
#include "../entities/Element.h"
#include "../entities/Commit.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>

namespace SysMLv2 {
    std::shared_ptr<SysMLv2::REST::IEntity> SysMLv2Deserializer::deserializeJsonString(std::string inputValue) {

        nlohmann::json json = nlohmann::json::parse(inputValue);

        std::string type = json[REST::JSON_TYPE_ENTITY].get<std::string>();
        std::transform(type.begin(), type.end(), type.begin(), [](unsigned char c){ return std::tolower(c); });

        if(type==REST::PROJECT_TYPE)
            return std::make_shared<REST::Project>(inputValue);

        if(type==REST::DATA_IDENTITY_TYPE)
            return std::make_shared<REST::DataIdentity>(inputValue);

        if(type==REST::BRANCH_TYPE)
            return std::make_shared<REST::Branch>(inputValue);

        if(type==REST::TAG_TYPE)
            return std::make_shared<REST::Tag>(inputValue);

        if(type==REST::QUERY_TYPE)
            return std::make_shared<REST::Query>(inputValue);

        if(type==REST::COMMIT_TYPE)
            return std::make_shared<REST::Commit>(inputValue);

        if(checkIfIsElementType(type))
            return std::make_shared<REST::Element>(inputValue);

        return nullptr;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> SysMLv2Deserializer::deserializeJsonArray(std::string inputValue) {
        nlohmann::json json = nlohmann::json::parse(inputValue);
        std::vector<nlohmann::json> arrayValues = json.get<std::vector<nlohmann::json>>();
        std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> returnValues;
        returnValues.reserve(arrayValues.size());
        for(const nlohmann::json& elem : arrayValues) {
            returnValues.emplace_back(SysMLv2Deserializer::deserializeJsonString(elem.dump()));
        }
        return returnValues;
    }

    bool SysMLv2Deserializer::checkIfIsElementType(std::string type) {
        std::vector<std::string> element_names = {"Element", "AnnotatingElement","Annotation", "Association", "Classifier", "Class", "Comment", "Connector", "DataType", "Dependency", "Documentation", "Element", "FeatureTyping", "NamespaceImport", "MembershipImport", "Multiplicity", "Specialization", "Subsetting", "Type", "Feature", "Expression", "Invairant", "Package", "Namespace", "Redefinition", "Relationship", "ReferencedSubsetting", "TextualRepresentation"};

        for(auto elem_name : element_names) {
            std::transform(elem_name.begin(), elem_name.end(), elem_name.begin(), [](unsigned char c){ return std::tolower(c); });
            if (type == elem_name)
                return true;
        }

        return false;
    }

} // SysMLv2