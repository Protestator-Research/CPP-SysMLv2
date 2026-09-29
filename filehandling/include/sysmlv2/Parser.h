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
#include <sysmlv2/ParserError.h>
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
		 * @param sourceName Optional file name / source identifier, recorded on any ParserError produced. Existing
		 *        callers that omit it keep compiling and behaving as before.
		 * @param reportUnresolvedAsWarnings true: every name that could not be resolved within this text is also returned as a
		 *        ParserError of type WARNING (with its position). Names are resolved among the elements of the text only; to
		 *        resolve against other sources (for example the standard library) use SysMLv2::Files::Workspace.
		 * @return A pair of the vectors of the parsed Elements, but also the Parser Errors.
		 * @see KerML::Entities
		 * @see ParserError
		 * @see Workspace
		 */
		static std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>,std::vector<std::shared_ptr<ParserError>>> parseKerML(std::string text, std::string sourceName = "", bool reportUnresolvedAsWarnings = false);

		/**
		 * Parses the SysML text given by the user.
		 * @param text
		 * @param sourceName Optional file name / source identifier, recorded on any ParserError produced. Existing
		 *        callers that omit it keep compiling and behaving as before.
		 * @param reportUnresolvedAsWarnings see parseKerML.
		 * @return
		 */
		static std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>,std::vector<std::shared_ptr<ParserError>>> parseSysMLv2(std::string text, std::string sourceName = "", bool reportUnresolvedAsWarnings = false);

		/**
		 * Reads the file at @p path and parses it with parseKerML or parseSysMLv2, chosen by its extension
		 * (".kerml" vs. everything else, treated as SysML v2). The file's path is used as the ParserError source name.
		 * @param path Path to the file to parse.
		 * @param reportUnresolvedAsWarnings see parseKerML.
		 * @return A pair of the vectors of the parsed Elements, but also the Parser Errors. On a file that cannot be
		 *         opened, the elements vector is empty and a single ParserError describes the failure.
		 */
		static std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>,std::vector<std::shared_ptr<ParserError>>> parseFile(const std::string& path, bool reportUnresolvedAsWarnings = false);
    };
}
