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
#include "../entities/DigitalTwin.h"
#include "../entities/Element.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>

namespace SysMLv2 {
    SysMLv2::Entities::IEntity *SysMLv2Deserializer::deserializeJsonString(std::string inputValue) {

        nlohmann::json json = nlohmann::json::parse(inputValue);

        std::string type = CPSBASELIB::STD_EXTENTION::StringExtention::toLower(
                json[Entities::JSON_TYPE_ENTITY].get<std::string>());

        if(type==Entities::PROJECT_TYPE)
            return new Entities::Project(inputValue);

        if(type==Entities::DATA_IDENTITY_TYPE)
            return new Entities::DataIdentity(inputValue);

        if(type==Entities::BRANCH_TYPE)
            return new Entities::Branch(inputValue);

        if(type==Entities::TAG_TYPE)
            return new Entities::Tag(inputValue);

        if(type==Entities::QUERY_TYPE)
            return new Entities::Query(inputValue);

        if(type==Entities::DIGITAL_TWIN_TYPE)
            return new Entities::DigitalTwin(inputValue);

        if(checkIfIsElementType(type))
            return new Entities::Element(inputValue);

        return nullptr;
    }

    std::vector<SysMLv2::Entities::IEntity*> SysMLv2Deserializer::deserializeJsonArray(std::string inputValue) {
        nlohmann::json json = nlohmann::json::parse(inputValue);
        std::vector<nlohmann::json> arrayValues = json.get<std::vector<nlohmann::json>>();
        std::vector<SysMLv2::Entities::IEntity*> returnValues;
        returnValues.reserve(arrayValues.size());
        for(const nlohmann::json& elem : arrayValues) {
            returnValues.emplace_back(SysMLv2Deserializer::deserializeJsonString(elem.dump()));
        }
        return returnValues;
    }

    bool SysMLv2Deserializer::checkIfIsElementType(std::string type) {
        std::vector<std::string> element_names = {"Element", "AnnotatingElement","Annotation", "Association", "Classifier", "Class", "Comment", "Connector", "DataType", "Dependency", "Documentation", "Element", "FeatureTyping", "NamespaceImport", "MembershipImport", "Multiplicity", "Specialization", "Subsetting", "Type", "Feature", "Expression", "Invairant", "Package", "Namespace", "Redefinition", "Relationship", "ReferencedSubsetting", "TextualRepresentation"};

        for(auto elem_name : element_names)
            if(type == CPSBASELIB::STD_EXTENTION::StringExtention::toLower(elem_name))
                return true;

        return false;
    }

    std::string SysMLv2Deserializer::splitString(std::string stringToSplit, char delimiter) {
        std::vector<std::string> returnValue;
        std::istringstream stream(stringToSplit);
        std::string line;
        while (getline(stream, line, delimiter)) {
            returnValue.push_back(line);
        }

        return returnValue;
    }

} // SysMLv2