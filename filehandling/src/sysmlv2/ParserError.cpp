//
// Created by Moritz Herzog on 30.04.25.
//

#include <sysmlv2/ParserError.h>

namespace SysMLv2::Files {
    ParserError::ParserError(boost::uuids::uuid elementId, std::string projectName, ErrorType type, std::string description) {
        ElementId = elementId;
        ProjectName = projectName;
        Type=type;
        Description = description;
    }

    boost::uuids::uuid ParserError::getElementID() {
        return ElementId;
    }

    std::string ParserError::getProjectName() {
        return ProjectName;
    }

    ErrorType ParserError::errorType() {
        return Type;
    }

    std::string ParserError::description() {
        return Description;
    }
}