//
// Created by Moritz Herzog on 30.04.25.
//

#include "Parser.h"
#include "kerml/KerMlErrorListener.h"
#include "kerml/KerMLLexer.h"
#include "kerml/KerMLParser.h"

#include <antlr4-common.h>
#include <boost/uuid/uuid_generators.hpp>


namespace SysMLv2::Files {
    std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>, std::vector<std::shared_ptr<ParserError>>>
   Parser::parseKerML(std::string text) {
        antlr4::ANTLRInputStream input(text);
        KerMLErrorListener *listener = new KerMLErrorListener();
        KerMLLexer lexer(&input);
        lexer.addErrorListener(listener);
        antlr4::CommonTokenStream tokens(&lexer);
        KerMLParser parser(&tokens);
        parser.addErrorListener(listener);
        std::cout << parser.start()->toStringTree() << std::endl;
        std::vector<std::shared_ptr<KerML::Entities::Element>> elements;
        auto syntaxErrors  = listener->getSyntaxErrors();
        std::vector<std::shared_ptr<ParserError>> errorVector = std::vector<std::shared_ptr<SysMLv2::Files::ParserError>>(syntaxErrors.size());
        for(const auto& error:syntaxErrors) {
            errorVector.push_back(std::make_shared<ParserError>(boost::uuids::random_generator()(),"",ErrorType::ERROR, error->message()));
        }
        return std::make_pair(elements, errorVector);
    }

}