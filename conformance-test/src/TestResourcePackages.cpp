#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include <kerml/parser/KerMLParser.h>
#include <kerml/parser/KerMLLexer.h>
#include <kerml/parser/KerMLListener.h>
#include <kerml/parser/KerMlErrorListener.h>
#include <sysmlv2/Parser.h>
#include <kerml/parser/KerMlListenerImplementation.h>
#include <kerml/root/elements/Element.h>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(Library);

TEST(TestResourcePackages, TestReadabilityOfBase) {
    auto fs = cmrc::Library::get_filesystem();
    auto data = fs.open("sysml.library/KerML/Semantic/Base.kerml");
    std::string content(data.begin(), data.end());
#ifdef WIN32
    std::string expected = "standard library package Base {\r\n\tdoc \r\n\t/*\r\n\t * This package defines the classifiers and features that provide the bases for the typing\r\n\t * of all elements in the language.\r\n\t */\r\n\t \t\t\r\n\tabstract datatype DataValue specializes Anything {\r\n\t\tdoc\r\n\t\t/*\r\n\t\t * Value is the most general classifier of entities that are values that do not change\r\n\t\t * over time.\r\n\t\t */\r\n\t\t\r\n\t\tfeature self: DataValue redefines Anything::self;\r\n\t}\r\n\t\r\n\tabstract feature things: Anything [1..*] nonunique {\r\n\t\tdoc\r\n\t\t/*\r\n\t\t * things is the top-level feature in the language.\r\n\t\t */\r\n\r\n\t\tfeature that : Anything[1] {\r\n\t\t\tdoc\r\n\t\t\t/*\r\n\t\t\t * For each value of things, the \"featuring instance\" of that value. \r\n\t\t\t * This is enforced by declaring Anything::self to be the chaining of things.that, \r\n\t\t\t * restricting it the single value of self.\r\n\t\t\t */\t\t\t\r\n\t\t}\r\n\t}\r\n\t\r\n\tabstract feature dataValues: DataValue[0..*] nonunique subsets things {\r\n\t\tdoc\r\n\t\t/*\r\n\t\t * dataValues is a specialization of things restricted to type DataValue.\r\n\t\t */\r\n\t}\r\n\t\t \r\n\tabstract feature naturals: ScalarValues::Natural[0..*] subsets dataValues {\r\n\t\tdoc\r\n\t\t/*\r\n\t\t * naturals is a specialization of dataValues restricted to type Natural. \r\n\t\t * It is the root feature of all multiplicities, which map from a feature to\r\n\t\t * the set of Natural numbers representing allowable cardinalities of the feature.\r\n\t\t */\r\n\t}\r\n\t\r\n\tmultiplicity exactlyOne [1..1] {\r\n\t\tdoc\r\n\t\t/*\r\n\t\t * exactlyOne is a multiplicity range requiring a cardinality of exactly one.\r\n\t\t */\r\n\t}\r\n\t\r\n\tmultiplicity zeroOrOne [0..1] {\r\n\t\tdoc\r\n\t\t/*\r\n\t\t * zeroOrOne is a multiplicity range requiring a cardinality of zero or one.\r\n\t\t */\t\t\r\n\t}\r\n\t\r\n\tmultiplicity oneToMany [1..*] {\r\n\t\tdoc\r\n\t\t/*\r\n\t\t * oneToMany is a multiplicity range allowing any cardinality of one or more.\r\n\t\t */\r\n\t}\r\n\t\r\n\tmultiplicity zeroToMany [0..*] {\r\n\t\tdoc\r\n\t\t/*\r\n\t\t * zeroToMany is a multiplicity range allowing any cardinality of zero or more\r\n\t\t * (that is, no restriction).\r\n\t\t */\r\n\t}\r\n\r\n\tabstract classifier Anything {\r\n\t\tdoc\r\n\t\t/*\r\n\t     * Anything is the top level generalized type in the language. \r\n\t     */\r\n\t\t\r\n\t\tfeature self: Anything[1] subsets things chains things.that {\r\n\t\t\tdoc\r\n\t\t\t/*\r\n\t\t\t * The source of a SelfLink of this thing to itself. self is thus a feature that\r\n\t\t\t * relates everything to itself. It is also the value of the nested \"that\" feature\r\n\t\t\t * of all other things featured by this thing.\r\n\t\t\t */\r\n\t\t}\r\n\t}\r\n\t\r\n}";
#else
    std::string expected = "standard library package Base {\n\tdoc \n\t/*\n\t * This package defines the classifiers and features that provide the bases for the typing\n\t * of all elements in the language.\n\t */\n\t \t\t\n\tabstract datatype DataValue specializes Anything {\n\t\tdoc\n\t\t/*\n\t\t * Value is the most general classifier of entities that are values that do not change\n\t\t * over time.\n\t\t */\n\t\t\n\t\tfeature self: DataValue redefines Anything::self;\n\t}\n\t\n\tabstract feature things: Anything [1..*] nonunique {\n\t\tdoc\n\t\t/*\n\t\t * things is the top-level feature in the language.\n\t\t */\n\n\t\tfeature that : Anything[1] {\n\t\t\tdoc\n\t\t\t/*\n\t\t\t * For each value of things, the \"featuring instance\" of that value. \n\t\t\t * This is enforced by declaring Anything::self to be the chaining of things.that, \n\t\t\t * restricting it the single value of self.\n\t\t\t */\t\t\t\n\t\t}\n\t}\n\t\n\tabstract feature dataValues: DataValue[0..*] nonunique subsets things {\n\t\tdoc\n\t\t/*\n\t\t * dataValues is a specialization of things restricted to type DataValue.\n\t\t */\n\t}\n\t\t \n\tabstract feature naturals: ScalarValues::Natural[0..*] subsets dataValues {\n\t\tdoc\n\t\t/*\n\t\t * naturals is a specialization of dataValues restricted to type Natural. \n\t\t * It is the root feature of all multiplicities, which map from a feature to\n\t\t * the set of Natural numbers representing allowable cardinalities of the feature.\n\t\t */\n\t}\n\t\n\tmultiplicity exactlyOne [1..1] {\n\t\tdoc\n\t\t/*\n\t\t * exactlyOne is a multiplicity range requiring a cardinality of exactly one.\n\t\t */\n\t}\n\t\n\tmultiplicity zeroOrOne [0..1] {\n\t\tdoc\n\t\t/*\n\t\t * zeroOrOne is a multiplicity range requiring a cardinality of zero or one.\n\t\t */\t\t\n\t}\n\t\n\tmultiplicity oneToMany [1..*] {\n\t\tdoc\n\t\t/*\n\t\t * oneToMany is a multiplicity range allowing any cardinality of one or more.\n\t\t */\n\t}\n\t\n\tmultiplicity zeroToMany [0..*] {\n\t\tdoc\n\t\t/*\n\t\t * zeroToMany is a multiplicity range allowing any cardinality of zero or more\n\t\t * (that is, no restriction).\n\t\t */\n\t}\n\n\tabstract classifier Anything {\n\t\tdoc\n\t\t/*\n\t     * Anything is the top level generalized type in the language. \n\t     */\n\t\t\n\t\tfeature self: Anything[1] subsets things chains things.that {\n\t\t\tdoc\n\t\t\t/*\n\t\t\t * The source of a SelfLink of this thing to itself. self is thus a feature that\n\t\t\t * relates everything to itself. It is also the value of the nested \"that\" feature\n\t\t\t * of all other things featured by this thing.\n\t\t\t */\n\t\t}\n\t}\n\t\n}";
#endif
    ASSERT_EQ(content, expected);
}

//TEST(TestResourcePackages, TestParsingBase) {
//    auto fs = cmrc::Library::get_filesystem();
//    auto data = fs.open("sysml.library/KerML/Semantic/Base.kerml");
//    std::string content(data.begin(), data.end());
//
//    antlr4::ANTLRInputStream input(content);
//    auto* listener = new KerMLErrorListener();
//    auto* listenerImplementation = new KerMLListenerImplementation();
//    KerMLLexer lexer(&input);
//    lexer.addErrorListener(listener);
//    antlr4::CommonTokenStream tokens(&lexer);
//    KerMLParser parser(&tokens);
//    parser.addErrorListener(listener);
//    parser.addParseListener(listenerImplementation);
//
//    // start parsing at file level
//    parser.start();
//
//    std::vector<std::shared_ptr<KerML::Entities::Element>> elements = listenerImplementation->getElements();
//    auto syntaxErrors = listener->getSyntaxErrors();
//    
//    delete listenerImplementation;
//    delete listener;
//
//    ASSERT_EQ(syntaxErrors.size(), 0);
//
//}