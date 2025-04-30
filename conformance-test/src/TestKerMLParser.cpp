//
// Created by Moritz Herzog on 07.04.25.
//

#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include <parsing/kerml/KerMLParser.h>
#include <parsing/kerml/KerMLLexer.h>
#include <parsing/kerml/KerMLListener.h>
#include <parsing/kerml/KerMlErrorListener.h>


TEST(TestKerMLParser, TestAddressBookModel) {
    std::string valueToParse = "private import ScalarValues::*;\n"
                               "package AddressBookModel {\n"
                               "\t\n"
                               "\tclass Entry {\n"
                               "\t\tname: String;\n"
                               "\t\taddress: String;\n"
                               "\t}\n"
                               "\t\n"
                               "\tclass AddressBook {\n"
                               "\t\tentries: Entry[*];\n"
                               "\t}\n"
                               "\t\n"
                               "}";



    // Provide the input text in a stream
    antlr4::ANTLRInputStream input(valueToParse);

    KerMLErrorListener *listener = new KerMLErrorListener();

    // Create a lexer from the input
    KerMLLexer lexer(&input);
    lexer.addErrorListener(listener);

    // Create a token stream from the lexer
    antlr4::CommonTokenStream tokens(&lexer);


    // Create a parser from the token stream
    KerMLParser parser(&tokens);
    parser.addErrorListener(listener);

    // Display the parse tree
    //std::cout << parser.start()->toStringTree() << std::endl;
    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
}

TEST(TestKerMLParser, ConformanceTestA2Atoms) {
    std::string valueToParse = "package Atoms {\n"
                               "\tdoc\n"
                               "\t/* This package defines a keyword (atom) for classifiers with\n"
                               "\t * exactly one instance and are disjoint from any others\n"
                               "\t * marked with this keyword.\n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Metaobjects::Metaobject;\n"
                               "\t\n"
                               "\tclassifier Atom;\n"
                               "\tmetaclass <atom> AtomMetadata specializes Metaobject {\n"
                               "\t\tbaseType = Atom meta KerML::Classifier;\n"
                               "\t}\n"
                               "}";

    // Provide the input text in a stream
    antlr4::ANTLRInputStream input(valueToParse);

    KerMLErrorListener *listener = new KerMLErrorListener();

    // Create a lexer from the input
    KerMLLexer lexer(&input);
    lexer.addErrorListener(listener);

    // Create a token stream from the lexer
    antlr4::CommonTokenStream tokens(&lexer);


    // Create a parser from the token stream
    KerMLParser parser(&tokens);
    parser.addErrorListener(listener);

    // Display the parse tree
    //std::cout << parser.start()->toStringTree() << std::endl;
    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
}

TEST(TestKerMLParser, TestJohnIndividualModel) {
    std::string valueToParse = "package JohnIndividualExample {\n"
                               "\tprivate import Objects::*;\n"
                               "\t\n"
                               "\tclass Person specializes Object {\n"
                               "\t\tdoc\n"
                               "\t\t/*\n"
                               "\t\t  This is the class of persons, each of whom has an age.\n"
                               "\t\t  It is NOT restricted to maximal portions.\n"
                               "\t\t  (The specialization of Object would normally be left implicit.)\n"
                               "\t\t*/\n"
                               "\t\n"
                               "\t\tclass Life specializes Person, Occurrences::Life;\n"
                               "\t\t\n"
                               "\t\tfeature age : ScalarValues::Natural;\n"
                               "\t  \n"
                               "\t  feature redefines portions : Person {\n"
                               "\t\t  doc\n"
                               "\t\t  /*\n"
                               "\t\t    These redefinitions enforce the \"rigidity\" constraint for Person.\n"
                               "\t\t    They ensure that all portions of a person are also persons and \n"
                               "\t\t    that a person can only be a portion of another person. This implies\n"
                               "\t\t    that the class Person must also include all the portions of any one \n"
                               "\t\t    of its instances. The redefinitions for the portion features\n"
                               "\t\t    also implicitly constraint the typing of the time slice and snapshot\n"
                               "\t\t    features, since they are subsets of portioning.\n"
                               "\t\t    (It is currently awkward to have to declare these redefinitions\n"
                               "\t\t    explicitly.)\n"
                               "\t\t  */\n"
                               "\t  }\n"
                               "\t  feature redefines portionOf : Person;\n"
                               "\t\n"
                               "\t}\n"
                               "\t\n"
                               "\tclass President specializes Person {\n"
                               "\t\tdoc\n"
                               "\t\t/*\n"
                               "\t\t  This is the class of presidents, each of which must be a time slice\n"
                               "\t\t  of the life of some individual person.\n"
                               "\t\t  (Note that this class is NOT \"rigid\".)\n"
                               "\t\t*/\n"
                               "\t\n"
                               "\t  feature redefines timeSliceOf : Person::Life [1];\n"
                               "\t}\n"
                               "\t\n"
                               "\tclass John specializes Person {\n"
                               "\t\tdoc\n"
                               "\t\t/*\n"
                               "\t\t  This is the class of the specific (individual) person who is John.\n"
                               "\t\t  There is at most one such person.\n"
                               "\t\t*/\n"
                               "\t\n"
                               "\t\tclass all JohnLife[0..1] specializes John, Occurrences::Life;\n"
                               "\t} \n"
                               "\t\n"
                               "\tclass JohnAsPresident specializes John, President {\n"
                               "\t\tdoc\n"
                               "\t\t/*\n"
                               "\t\t  This is the class of time slices of John's life in which he is\n"
                               "\t\t  a president.\n"
                               "\t\t*/\n"
                               "\t}\n"
                               "\t\n"
                               "\tclass Country specializes Object {\n"
                               "\t\tdoc\n"
                               "\t\t/*\n"
                               "\t\t  This is the class of countries, each of which may have at most one\n"
                               "\t\t  president.\n"
                               "\t\t*/\n"
                               "\t\n"
                               "\t\tclass all Life specializes Country, Occurrences::Life;\n"
                               "\n"
                               "\t\tfeature presidentOfCountry : President[0..1];\n"
                               "\t  \n"
                               "\t  \t// Rigidity constraint.\n"
                               "\t  \tfeature redefines portions : Country;\n"
                               "\t  \tfeature redefines portionOf : Country;\n"
                               "\t}\n"
                               "\t\n"
                               "\tclass UnitedStates specializes Country {\n"
                               "\t\tdoc\n"
                               "\t\t/*\n"
                               "\t\t  This is the class of the specific country that is the\n"
                               "\t\t  United States. It contains a single instance. The United States\n"
                               "\t\t  always has a president who must be at least 35 years old.\n"
                               "\t\t*/\n"
                               "\t\n"
                               "\t\tclass all USLife[1] specializes UnitedStates, Occurrences::Life ;\n"
                               "\t  \tfeature presidentOfUS[1] redefines presidentOfCountry {\n"
                               "\t   \t\tinv { age >= 35 } \n"
                               "\t  \t}\n"
                               "\t}\n"
                               "\t\n"
                               "\tclass UnitedStatesWithJohnAsPresident specializes UnitedStates {\n"
                               "\t\tdoc\n"
                               "\t\t/*\n"
                               "\t\t  This is the class of time slices of the United States during\n"
                               "\t\t  which John is president of the United States.\n"
                               "\t\t*/\n"
                               "\t\n"
                               "\t  feature redefines timeSliceOf : UnitedStates::Life;\n"
                               "\t  feature redefines presidentOfUS : JohnAsPresident;\n"
                               "\t";



    // Provide the input text in a stream
    antlr4::ANTLRInputStream input(valueToParse);

    auto listener = new KerMLErrorListener();

    // Create a lexer from the input
    KerMLLexer lexer(&input);
    lexer.addErrorListener(listener);

    // Create a token stream from the lexer
    antlr4::CommonTokenStream tokens(&lexer);


    // Create a parser from the token stream
    KerMLParser parser(&tokens);
    parser.addErrorListener(listener);

    // Display the parse tree
    std::cout << parser.start()->toStringTree() << std::endl;
    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
}

TEST(TestKerMLParser, ConformanceTestA2ModelinInstances) {
    std::string valueToParse = "package ModelingInstances {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tclassifier Vehicle;\n"
                               "\tclassifier Bicycle specializes Vehicle;\n"
                               "\tclassifier MyBike [1] specializes Bicycle;\n"
                               "\tclassifier YourBike [1] specializes Bicycle disjoint from MyBike;\n"
                               "}\n"
                               "\n"
                               "package ModelingInstancesWithAtoms {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Atoms::atom;\n"
                               "\n"
                               "\tclassifier Vehicle;\n"
                               "\tclassifier Bicycle specializes Vehicle;\n"
                               "\n"
                               "\t#atom\n"
                               "\tclassifier MyBike specializes Bicycle;\n"
                               "\t#atom\n"
                               "\tclassifier YourBike specializes Bicycle;\n"
                               "\n"
                               "\t/* Assigning feature values. */\n"
                               "\n"
                               "\tclassifier Garage {\n"
                               "\t\tfeature stores : Bicycle [*];\n"
                               "\t}\n"
                               "\tclassifier OurBicycle unions MyBike, YourBike;\n"
                               "\n"
                               "\t#atom\n"
                               "\tclassifier OurGarage specializes Garage {\n"
                               "\t\tfeature redefines stores : OurBicycle [2];\n"
                               "\t}\n"
                               "}";

    // Provide the input text in a stream
    antlr4::ANTLRInputStream input(valueToParse);

    auto listener = new KerMLErrorListener();

    // Create a lexer from the input
    KerMLLexer lexer(&input);
    lexer.addErrorListener(listener);

    // Create a token stream from the lexer
    antlr4::CommonTokenStream tokens(&lexer);


    // Create a parser from the token stream
    KerMLParser parser(&tokens);
    parser.addErrorListener(listener);

    // Display the parse tree
    std::cout << parser.start()->toStringTree() << std::endl;
    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
}

TEST(TestKerMLParser, ConformanceTestA32WithoutConnectors) {
    std::string valueToParse = "package WithoutConnectorsModelToBeExecuted {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tclassifier Bicycle {\n"
                               "\t\tfeature rollsOn : Wheel [2];\n"
                               "\t\tfeature holdsWheel : BikeFork [*];\n"
                               "\t}\n"
                               "\tclassifier Wheel;\n"
                               "\tclassifier BikeFork;\n"
                               "}\n"
                               "\n"
                               "package WithoutConnectorsExecution {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Atoms::*;\n"
                               "\tprivate import WithoutConnectorsModelToBeExecuted::*;\n"
                               "\n"
                               "\t#atom\n"
                               "\tclassifier MyWheel1 specializes Wheel;\n"
                               "\t#atom\n"
                               "\tclassifier MyWheel2 specializes Wheel;\n"
                               "\n"
                               "\tclassifier MyWheel unions MyWheel1, MyWheel2;\n"
                               "\n"
                               "\t#atom\n"
                               "\tclassifier MyBike specializes Bicycle {\n"
                               "\t\tfeature redefines rollsOn : MyWheel;\n"
                               "\t}\n"
                               "}\n"
                               "\n"
                               "\n"
                               "";

    // Provide the input text in a stream
    antlr4::ANTLRInputStream input(valueToParse);

    auto listener = new KerMLErrorListener();

    // Create a lexer from the input
    KerMLLexer lexer(&input);
    lexer.addErrorListener(listener);

    // Create a token stream from the lexer
    antlr4::CommonTokenStream tokens(&lexer);


    // Create a parser from the token stream
    KerMLParser parser(&tokens);
    parser.addErrorListener(listener);

    // Display the parse tree
    std::cout << parser.start()->toStringTree() << std::endl;
    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
}

TEST(TestKerMLParser, ConformanceTestA33OneToOneConnectors) {
    std::string valueToParse = "\n"
                               "package OneToOneConnectorsModelToBeExecuted {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "    public import WithoutConnectorsModelToBeExecuted::Wheel;\n"
                               "    public import WithoutConnectorsModelToBeExecuted::BikeFork;\n"
                               "\n"
                               "\tclassifier Bicycle {\n"
                               "\t\tfeature rollsOn : Wheel [2];\n"
                               "\t\tfeature holdsWheel : BikeFork [*];\n"
                               "\t\tconnector fixWheel : BikeWheelFixed from [1] rollsOn to [1] holdsWheel;\n"
                               "\t}\n"
                               "\tassoc BikeWheelFixed {\n"
                               "\t\tend feature wheel : Wheel;\n"
                               "\t\tend feature fixedTo : BikeFork;\n"
                               "\t}\n"
                               "}\n"
                               "\n"
                               "package OneToOneConnectorsExecution {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Atoms::*;\n"
                               "\tpublic import OneToOneConnectorsModelToBeExecuted::*;\n"
                               "\tpublic import WithoutConnectorsExecution::MyWheel1;\n"
                               "\tpublic import WithoutConnectorsExecution::MyWheel2;\n"
                               "\tpublic import WithoutConnectorsExecution::MyWheel;\n"
                               "\n"
                               "\t#atom\n"
                               "\tclassifier MyBikeFork1 specializes BikeFork;\n"
                               "\t#atom\n"
                               "\tclassifier MyBikeFork2 specializes BikeFork;\n"
                               "\n"
                               "\tclassifier MyBikeFork unions MyBikeFork1, MyBikeFork2;\n"
                               "\n"
                               "\t#atom\n"
                               " \tassoc MyBikeWheel1_Fork1_BWF_Link specializes BikeWheelFixed {\n"
                               "\t\tend feature redefines wheel : MyWheel1;\n"
                               "\t\tend feature redefines fixedTo : MyBikeFork1;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tassoc MyBikeWheel2_Fork2_BWF_Link specializes BikeWheelFixed {\n"
                               "\t\tend feature redefines wheel : MyWheel2;\n"
                               "\t\tend feature redefines fixedTo : MyBikeFork2;\n"
                               "\t}\n"
                               "\n"
                               "\tclassifier MyBikeWheel_Fork_BWF_Link unions MyBikeWheel1_Fork1_BWF_Link, MyBikeWheel2_Fork2_BWF_Link;\n"
                               "\n"
                               "\t#atom\n"
                               "\tclassifier MyBike specializes Bicycle {\n"
                               "\t\tfeature redefines rollsOn : MyWheel;\n"
                               "\t\tfeature redefines holdsWheel : MyBikeFork;\n"
                               "\t\tconnector redefines fixWheel : MyBikeWheel_Fork_BWF_Link [2] from [1] rollsOn to [1] holdsWheel;\n"
                               "\t}\n"
                               "}";

    // Provide the input text in a stream
    antlr4::ANTLRInputStream input(valueToParse);

    auto listener = new KerMLErrorListener();

    // Create a lexer from the input
    KerMLLexer lexer(&input);
    lexer.addErrorListener(listener);

    // Create a token stream from the lexer
    antlr4::CommonTokenStream tokens(&lexer);


    // Create a parser from the token stream
    KerMLParser parser(&tokens);
    parser.addErrorListener(listener);

    // Display the parse tree
    std::cout << parser.start()->toStringTree() << std::endl;
    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
}