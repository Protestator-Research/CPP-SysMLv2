//
// Created by Moritz Herzog on 30.04.25.
//

#include <sysmlv2/Parser.h>

#include <kerml/parser/KerMlErrorListener.h>
#include <kerml/parser/KerMLLexer.h>
#include <kerml/parser/KerMLParser.h>
#include <kerml/parser/KerMlListenerImplementation.h>

#include <sysmlv2/parser/SysMLv2ErrorListener.h>
#include <sysmlv2/parser/SysMLv2Error.h>
#include <sysmlv2/parser/SysMLv2ListenerImplementation.h>
#include <sysmlv2/parser/SysMLv2Lexer.h>
#include <sysmlv2/parser/SysMLv2Parser.h>

#include <antlr4-common.h>
#include <boost/uuid/uuid_generators.hpp>


namespace SysMLv2::Files {
    std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>, std::vector<std::shared_ptr<ParserError>>> Parser::parseKerML(std::string text) {
        antlr4::ANTLRInputStream input(text);
        auto errorlistener = new KerMLErrorListener();
        auto listenerImplementation = new KerMLListenerImplementation();
        KerMLLexer lexer(&input);
        lexer.addErrorListener(errorlistener);
        antlr4::CommonTokenStream tokens(&lexer);
        KerMLParser parser(&tokens);
        parser.addErrorListener(errorlistener);
        parser.addParseListener(listenerImplementation);

        // start parsing at file level
        parser.start();

        std::vector<std::shared_ptr<KerML::Entities::Element>> elements = listenerImplementation->getElements();
        auto syntaxErrors = errorlistener->getSyntaxErrors();
        std::vector<std::shared_ptr<ParserError>> errorVector;
        errorVector.reserve(syntaxErrors.size());
        for(const auto& error:syntaxErrors) {
            errorVector.push_back(std::make_shared<ParserError>(boost::uuids::random_generator()(),"",ErrorType::ERROR, error->message()));
        }

        // Cleanup; So no memory leaks happend.
        delete listenerImplementation;
        delete errorlistener;

        return std::make_pair(elements, errorVector);
    }

    std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>, std::vector<std::shared_ptr<ParserError>>> Parser
    ::parseSysMLv2(std::string text) {
        antlr4::ANTLRInputStream input(text);
        SysMLErrorListenener errorlistener;
        SysMLv2ListenerImplementation listenerImplementation;
        SysMLv2Lexer lexer(&input);
        lexer.addErrorListener(&errorlistener);
        antlr4::CommonTokenStream tokens(&lexer);
        SysMLv2Parser parser(&tokens);
        parser.addErrorListener(&errorlistener);
        parser.addParseListener(&listenerImplementation);
        // start parsing at file level
        parser.start();

        auto elements = listenerImplementation.getElements();
        auto syntaxErrors = errorlistener.getSyntaxErrors();
        std::vector<std::shared_ptr<ParserError>> errorVector;
        errorVector.reserve(syntaxErrors.size());
        for (const auto& error : syntaxErrors) {
            errorVector.push_back(std::make_shared<ParserError>(boost::uuids::random_generator()(), "", ErrorType::ERROR, error->message()));
        }

        return std::make_pair(elements, errorVector);
    }
}
