//
// Created by Moritz Herzog on 08.04.25.
//

#pragma once

#include <string>
#include <sysmlv2/sysmlv2file_global.h>
#include <kerml/ErrorTypes.h>


    class SYSMLV2FILE_EXPORT SysMLError {
    public:
        SysMLError() = delete;


        SysMLError(KerML::Parser::ErrorTypes errorType, int line, int postionInLine, std::string message);

        virtual ~SysMLError() = default;

        std::string message();

        int line();

        int positionInLine();

        KerML::Parser::ErrorTypes errorType();

    private:
        KerML::Parser::ErrorTypes ErrorType;
        std::string ErrorMessage;
        int Line;
        int PositionInLine;

    };
//}
