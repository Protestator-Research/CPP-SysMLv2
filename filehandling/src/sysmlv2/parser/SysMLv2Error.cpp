//
// Created by Moritz Herzog on 08.04.25.
//

#include <sysmlv2/parser/SysMLv2Error.h>
//namespace KerML::Parser {
SysMLError::SysMLError(KerML::Parser::ErrorTypes errorType, int line, int postionInLine, std::string message) {
	Line = line;
	PositionInLine = postionInLine;
	ErrorType = errorType;
	ErrorMessage = message;
}

std::string SysMLError::message() {
	return ErrorMessage;
}

int SysMLError::line() {
	return Line;
}

int SysMLError::positionInLine() {
	return PositionInLine;
}

KerML::Parser::ErrorTypes SysMLError::errorType() {
	return ErrorType;
}
//}