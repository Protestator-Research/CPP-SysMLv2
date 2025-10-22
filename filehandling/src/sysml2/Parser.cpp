//
// Created by Moritz Herzog on 30.04.25.
//

#include <sysmlv2/Parser.h>
#include <kerml/parser/KerMlErrorListener.h>
#include <kerml/parser/KerMLLexer.h>
#include <kerml/parser/KerMLParser.h>
#include <kerml/parser/KerMlListenerImplementation.h>

#include <antlr4-common.h>
#include <boost/uuid/uuid_generators.hpp>


namespace SysMLv2::Files {
    std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>, std::vector<std::shared_ptr<ParserError>>> Parser::parseKerML(std::string text) {
        antlr4::ANTLRInputStream input(text);
        auto *listener = new KerMLErrorListener();
        auto* listenerImplementation = new KerMLListenerImplementation();
        KerMLLexer lexer(&input);
        lexer.addErrorListener(listener);
        antlr4::CommonTokenStream tokens(&lexer);
        KerMLParser parser(&tokens);
        parser.addErrorListener(listener);
        parser.addParseListener(listenerImplementation);

        // start parsing at file level
        parser.start();

        std::vector<std::shared_ptr<KerML::Entities::Element>> elements = listenerImplementation->getElements();
        auto syntaxErrors  = listener->getSyntaxErrors();
        std::vector<std::shared_ptr<ParserError>> errorVector = std::vector<std::shared_ptr<SysMLv2::Files::ParserError>>(syntaxErrors.size());
        for(const auto& error:syntaxErrors) {
            errorVector.push_back(std::make_shared<ParserError>(boost::uuids::random_generator()(),"",ErrorType::ERROR, error->message()));
        }

        // Cleanup; So no memory leaks happend.
        delete listenerImplementation;
        delete listener;

        return std::make_pair(elements, errorVector);
    }

    std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>, std::vector<std::shared_ptr<ParserError>>> Parser
    ::parseSysMLv2(std::string text) {
        return std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>, std::vector<std::shared_ptr<ParserError>>>();
    }
}
