//
// Created by Moritz Herzog on 30.04.25.
//
#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>
#include <sysmlv2/sysmlv2file_global.h>

namespace SysMLv2::Files {
    enum SYSMLV2FILE_EXPORT ErrorType {
        ERROR,
        WARNING
    };

    class SYSMLV2FILE_EXPORT ParserError {
    public:
        ParserError(boost::uuids::uuid elementId, std::string projectName, ErrorType type, std::string description);
        /**
         * Additive constructor that also carries the source position of the error.
         * @param line 1-based line number, or -1 if unknown.
         * @param column 0-based column (ANTLR's charPositionInLine), or -1 if unknown.
         * @param source file name / source identifier the error came from, or "" if unknown.
         */
        ParserError(boost::uuids::uuid elementId, std::string projectName, ErrorType type, std::string description,
                    int line, int column, std::string source);
        virtual ~ParserError() = default;

        boost::uuids::uuid getElementID();
        std::string getProjectName();
        ErrorType errorType();
        std::string description();

        /// 1-based line number, or -1 if unknown (kept for source-compatible callers that never set it).
        int getLine() const;
        /// 0-based column (ANTLR's charPositionInLine), or -1 if unknown.
        int getColumn() const;
        /// File name / source identifier the error came from, or "" if unknown.
        std::string getSource() const;

    private:
        boost::uuids::uuid ElementId;
        std::string ProjectName;
        ErrorType Type;
        std::string Description;
        int Line = -1;
        int Column = -1;
        std::string Source;
    };
}

