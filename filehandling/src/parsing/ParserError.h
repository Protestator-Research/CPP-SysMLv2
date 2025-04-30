//
// Created by Moritz Herzog on 30.04.25.
//

#ifndef SYSML_PARSERERROR_H
#define SYSML_PARSERERROR_H

#include <string>
#include <boost/uuid/uuid.hpp>

namespace SysMLv2::Files {
    enum ErrorType {
        ERROR,
        WARNING
    };

    class ParserError {
    public:
        ParserError(boost::uuids::uuid elementId, std::string projectName, ErrorType type, std::string description);
        ~ParserError() = default;

        boost::uuids::uuid getElementID();
        std::string getProjectName();
        ErrorType errorType();
        std::string description();

    private:
        boost::uuids::uuid ElementId;
        std::string ProjectName;
        ErrorType Type;
        std::string Description;
    };
}

#endif //SYSML_PARSERERROR_H
