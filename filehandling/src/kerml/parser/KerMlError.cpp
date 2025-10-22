//
// Created by Moritz Herzog on 08.04.25.
//

#include <kerml/parser/KerMlError.h>
//namespace KerML::Parser {
    KerMLError::KerMLError(KerMLErrorType errorType, int line, int postionInLine, std::string message) {
        Line = line;
        PositionInLine = postionInLine;
        ErrorType = errorType;
        ErrorMessage = message;
    }

    std::string KerMLError::message() {
        return ErrorMessage;
    }

    int KerMLError::line() {
        return Line;
    }

    int KerMLError::positionInLine() {
        return PositionInLine;
    }

    KerMLErrorType KerMLError::errorType() {
        return ErrorType;
    }
//}