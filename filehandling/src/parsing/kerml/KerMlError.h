//
// Created by Moritz Herzog on 08.04.25.
//

#ifndef SYSMLV2_KERMLERROR_H
#define SYSMLV2_KERMLERROR_H

#include <string>

enum KerMLErrorType {
    SYNTAX_ERROR,
    AMBIGUITY_ERROR,
    CONTEXT_SENSITIVITY_ERROR,
    ATTEMPTING_FULL_CONTEXT_ERROR
};


class KerMLError {
public:
    KerMLError() = delete;
    KerMLError(KerMLErrorType errorType, int line, int postionInLine, std::string message);
    virtual ~KerMLError() = default;

    std::string message();
    int line();
    int positionInLine();

    KerMLErrorType errorType();

private:
    KerMLErrorType ErrorType;
    std::string ErrorMessage;
    int Line;
    int PositionInLine;

};


#endif //SYSMLV2_KERMLERROR_H
