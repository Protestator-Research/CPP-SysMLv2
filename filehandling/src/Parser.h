//
// Created by Moritz Herzog on 30.04.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include "ParserError.h"
#include <vector>
#include <memory>
#include <utility>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "sysmlv2file_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities {
    class Element;
}


namespace SysMLv2::Files {
	/**
	 * @class Parser
	 * @version 1.0 Beta 3
	 * @author Moritz Herzog <herzogm@rptu.de>
	 * @brief Defines the Parser for the SysML and KerML Standard.
	 * Generally Speaking this is a wrapper class for the ANTLR Implementaiton, to make it easyer for future users. Allowing to get the resources with less code.
	 */
	class SYSMLV2FILE_EXPORT Parser {
    public:
		/**
		 * Parses the KerML text given by the user.
		 * @param text KerML Text that should be parsed.
		 * @return A pair of the vectors of the parsed Elements, but also the Parser Errors.
		 * @see KerML::Entities
		 * @see ParserError
		 */
		static std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>,std::vector<std::shared_ptr<ParserError>>> parseKerML(std::string text);
    };
}
