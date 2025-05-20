//
// Created by Moritz Herzog on 07.04.25.
//

#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include <kerml/KerMLParser.h>
#include <kerml/KerMLLexer.h>
#include <kerml/KerMLListener.h>
#include <kerml/KerMlErrorListener.h>
#include <Parser.h>
#include "kerml/KerMlListenerImplementation.h"

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


    const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
    EXPECT_EQ(returnValue.first.size(), 0);

    // Provide the input text in a stream
//    antlr4::ANTLRInputStream input(valueToParse);
//
//    KerMLErrorListener *listener = new KerMLErrorListener();
//
//     Create a lexer from the input
//    KerMLLexer lexer(&input);
//    lexer.addErrorListener(listener);
//
//     Create a token stream from the lexer
//    antlr4::CommonTokenStream tokens(&lexer);
//
//
//     Create a parser from the token stream
//    KerMLParser parser(&tokens);
//    parser.addErrorListener(listener);
//
//     Display the parse tree
//    parser.start()->toStringTree();
//    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
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
    parser.start()->toStringTree();
    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
}

//TEST(TestKerMLParser, TestJohnIndividualModel) {
//    std::string valueToParse = "package JohnIndividualExample {\n"
//                               "\tprivate import Objects::*;\n"
//                               "\t\n"
//                               "\tclass Person specializes Object {\n"
//                               "\t\tdoc\n"
//                               "\t\t/*\n"
//                               "\t\t  This is the class of persons, each of whom has an age.\n"
//                               "\t\t  It is NOT restricted to maximal portions.\n"
//                               "\t\t  (The specialization of Object would normally be left implicit.)\n"
//                               "\t\t*/\n"
//                               "\t\n"
//                               "\t\tclass Life specializes Person, Occurrences::Life;\n"
//                               "\t\t\n"
//                               "\t\tfeature age : ScalarValues::Natural;\n"
//                               "\t  \n"
//                               "\t  feature redefines portions : Person {\n"
//                               "\t\t  doc\n"
//                               "\t\t  /*\n"
//                               "\t\t    These redefinitions enforce the \"rigidity\" constraint for Person.\n"
//                               "\t\t    They ensure that all portions of a person are also persons and \n"
//                               "\t\t    that a person can only be a portion of another person. This implies\n"
//                               "\t\t    that the class Person must also include all the portions of any one \n"
//                               "\t\t    of its instances. The redefinitions for the portion features\n"
//                               "\t\t    also implicitly constraint the typing of the time slice and snapshot\n"
//                               "\t\t    features, since they are subsets of portioning.\n"
//                               "\t\t    (It is currently awkward to have to declare these redefinitions\n"
//                               "\t\t    explicitly.)\n"
//                               "\t\t  */\n"
//                               "\t  }\n"
//                               "\t  feature redefines portionOf : Person;\n"
//                               "\t\n"
//                               "\t}\n"
//                               "\t\n"
//                               "\tclass President specializes Person {\n"
//                               "\t\tdoc\n"
//                               "\t\t/*\n"
//                               "\t\t  This is the class of presidents, each of which must be a time slice\n"
//                               "\t\t  of the life of some individual person.\n"
//                               "\t\t  (Note that this class is NOT \"rigid\".)\n"
//                               "\t\t*/\n"
//                               "\t\n"
//                               "\t  feature redefines timeSliceOf : Person::Life [1];\n"
//                               "\t}\n"
//                               "\t\n"
//                               "\tclass John specializes Person {\n"
//                               "\t\tdoc\n"
//                               "\t\t/*\n"
//                               "\t\t  This is the class of the specific (individual) person who is John.\n"
//                               "\t\t  There is at most one such person.\n"
//                               "\t\t*/\n"
//                               "\t\n"
//                               "\t\tclass all JohnLife[0..1] specializes John, Occurrences::Life;\n"
//                               "\t} \n"
//                               "\t\n"
//                               "\tclass JohnAsPresident specializes John, President {\n"
//                               "\t\tdoc\n"
//                               "\t\t/*\n"
//                               "\t\t  This is the class of time slices of John's life in which he is\n"
//                               "\t\t  a president.\n"
//                               "\t\t*/\n"
//                               "\t}\n"
//                               "\t\n"
//                               "\tclass Country specializes Object {\n"
//                               "\t\tdoc\n"
//                               "\t\t/*\n"
//                               "\t\t  This is the class of countries, each of which may have at most one\n"
//                               "\t\t  president.\n"
//                               "\t\t*/\n"
//                               "\t\n"
//                               "\t\tclass all Life specializes Country, Occurrences::Life;\n"
//                               "\n"
//                               "\t\tfeature presidentOfCountry : President[0..1];\n"
//                               "\t  \n"
//                               "\t  \t// Rigidity constraint.\n"
//                               "\t  \tfeature redefines portions : Country;\n"
//                               "\t  \tfeature redefines portionOf : Country;\n"
//                               "\t}\n"
//                               "\t\n"
//                               "\tclass UnitedStates specializes Country {\n"
//                               "\t\tdoc\n"
//                               "\t\t/*\n"
//                               "\t\t  This is the class of the specific country that is the\n"
//                               "\t\t  United States. It contains a single instance. The United States\n"
//                               "\t\t  always has a president who must be at least 35 years old.\n"
//                               "\t\t*/\n"
//                               "\t\n"
//                               "\t\tclass all USLife[1] specializes UnitedStates, Occurrences::Life ;\n"
//                               "\t  \tfeature presidentOfUS[1] redefines presidentOfCountry {\n"
//                               "\t   \t\tinv { age >= 35 } \n"
//                               "\t  \t}\n"
//                               "\t}\n"
//                               "\t\n"
//                               "\tclass UnitedStatesWithJohnAsPresident specializes UnitedStates {\n"
//                               "\t\tdoc\n"
//                               "\t\t/*\n"
//                               "\t\t  This is the class of time slices of the United States during\n"
//                               "\t\t  which John is president of the United States.\n"
//                               "\t\t*/\n"
//                               "\t\n"
//                               "\t  feature redefines timeSliceOf : UnitedStates::Life;\n"
//                               "\t  feature redefines presidentOfUS : JohnAsPresident;\n"
//                               "\t";
//
//
//
//    // Provide the input text in a stream
//    antlr4::ANTLRInputStream input(valueToParse);
//
//    auto listener = new KerMLErrorListener();
//
//    // Create a lexer from the input
//    KerMLLexer lexer(&input);
//    lexer.addErrorListener(listener);
//
//    // Create a token stream from the lexer
//    antlr4::CommonTokenStream tokens(&lexer);
//
//
//    // Create a parser from the token stream
//    KerMLParser parser(&tokens);
//    parser.addErrorListener(listener);
//
//    // Display the parse tree
//    parser.start()->toStringTree();
//    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
//}

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
    auto listenerImplementation = new KerMLListenerImplementation();

    // Create a lexer from the input
    KerMLLexer lexer(&input);
    lexer.addErrorListener(listener);

    // Create a token stream from the lexer
    antlr4::CommonTokenStream tokens(&lexer);


    // Create a parser from the token stream
    KerMLParser parser(&tokens);
    parser.addErrorListener(listener);
    parser.addParseListener(listenerImplementation);

    // Display the parse tree
    parser.start()->toStringTree();
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
    parser.start()->toStringTree();
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
    parser.start()->toStringTree();
    EXPECT_EQ(listener->getSyntaxErrors().size(),0);
}

TEST(TestKerMLParser, ConformanceTestA34OneeToUnrestrictedConnectors) {
    std::string valueToParse = "\n"
        "package OneToUnrestrictedConnectorsModelToBeExecuted{\n"
        "    doc\n"
        "    /*\n"
        "     */\n"
        "\n"
        "    private import WithoutConnectorsModelToBeExecuted::BikeFork;\n"
        "\n"
        "    classifier Bicycle {\n"
        "        feature carrier : BikeBasket[*];\n"
        "        feature holdsWheel : BikeFork[*];\n"
        "        connector carrierFixed : BikeBasketFixed from[*] carrier to[1] holdsWheel;\n"
        "    }\n"
        "    classifier BikeBasket;\n"
        "\n"
        "    assoc BikeBasketFixed {\n"
        "        end feature basket : BikeBasket;\n"
        "        end feature fixedTo : BikeFork;\n"
        "    }\n"
        "}"
        "\n"
        "package OneToUnrestrictedConnectorsExecution{\n"
        "    doc\n"
        "    /*\n"
        "     */\n"
        "\n"
        "    private import Atoms::*;\n"
        "    private import OneToUnrestrictedConnectorsModelToBeExecuted::*;\n"
        "    private import OneToOneConnectorsExecution::MyBikeFork1;\n"
        "    private import OneToOneConnectorsExecution::MyBikeFork2;\n"
        "    private import OneToOneConnectorsExecution::MyBikeFork;\n"
        "\n"
        "    #atom\n"
        "    classifier MyBikeBasket1 specializes BikeBasket;\n"
        "    #atom\n"
        "    classifier MyBikeBasket2 specializes BikeBasket;\n"
        "\n"
        "    classifier MyBikeBasket unions MyBikeBasket1, MyBikeBasket2;\n"
        "\n"
        "    #atom\n"
        "    assoc MyBikeBasket1_Fork1_BBF_Link specializes BikeBasketFixed {\n"
        "        end feature redefines basket : MyBikeBasket1;\n"
        "        end feature redefines fixedTo : MyBikeFork1;\n"
        "    }\n"
        "    #atom\n"
        "    assoc MyBikeBasket2_Fork1_BBF_Link specializes BikeBasketFixed {\n"
        "        end feature redefines basket : MyBikeBasket2;\n"
        "        end feature redefines fixedTo : MyBikeFork1;\n"
        "    }\n"
        "\n"
        "    classifier MyBikeBasket_Fork_BBF_Link unions MyBikeBasket1_Fork1_BBF_Link, MyBikeBasket2_Fork1_BBF_Link;\n"
        "\n"
        "    #atom\n"
        "    classifier MyBike specializes Bicycle {\n"
        "        feature redefines carrier : MyBikeBasket[2];\n"
        "        feature redefines holdsWheel : MyBikeFork[2];\n"
        "        connector redefines carrierFixed : MyBikeBasket_Fork_BBF_Link[2] from[*] carrier to[1] holdsWheel;\n"
        "    }\n"
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
    parser.start()->toStringTree();
    EXPECT_EQ(listener->getSyntaxErrors().size(), 0);
}

TEST(TestKerMLParser, ConformanceTestA35TimingForStructures) {
    std::string valueToParse = "\n"
                               "package TimingForStructuresModelToBeExecuted1 {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import WithoutConnectorsModelToBeExecuted::Wheel;\n"
                               "\tprivate import WithoutConnectorsModelToBeExecuted::BikeFork;\n"
                               "\tprivate import Occurrences::Occurrence;\n"
                               "\n"
                               "\tstruct Bicycle {\n"
                               "\t\tfeature rollsOn : Wheel [2] subsets timeCoincidentOccurrences;\n"
                               "\t\tfeature holdsWheel : BikeFork [2] subsets timeCoincidentOccurrences;\n"
                               "\t}\n"
                               "}\n"
                               "\n"
                               "package TimingForStructuresExecution1 {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Atoms::*;\n"
                               "\tprivate import TimingForStructuresModelToBeExecuted1::*;\n"
                               "\tprivate import OneToOneConnectorsExecution::MyWheel;\n"
                               "\tprivate import OneToOneConnectorsExecution::MyBikeFork;\n"
                               "\n"
                               "\tstruct MyBikeTimeCoincident unions MyWheel, MyBikeFork, MyBike;\n"
                               "\n"
                               "\t#atom\n"
                               "\tstruct MyBike specializes Bicycle {\n"
                               "\t\tfeature redefines self : MyBike;\n"
                               "\t\tfeature redefines timeCoincidentOccurrences : MyBikeTimeCoincident [5];\n"
                               "\t\tfeature redefines rollsOn : MyWheel;\n"
                               "\t\tfeature redefines holdsWheel : MyBikeFork;\n"
                               "\t}\n"
                               "}\n"
                               "\n"
                               "\n"
                               "package TimingForStructuresModelToBeExecuted2 {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import WithoutConnectorsModelToBeExecuted::Wheel;\n"
                               "\tprivate import WithoutConnectorsModelToBeExecuted::BikeFork;\n"
                               "\tprivate import Occurrences::Occurrence;\n"
                               "\tprivate import Occurrences::HappensDuring;\n"
                               "\n"
                               "\tstruct Bicycle {\n"
                               "\t\tfeature rollsOn : Wheel [2];\n"
                               "\t\tfeature holdsWheel : BikeFork [2];\n"
                               "\t\tfeature allParts : Occurrence unions rollsOn, holdsWheel;\n"
                               "\t\tconnector b_during_ap : HappensDuring from [1] self to [*] allParts;\n"
                               "\t}\n"
                               "}\n"
                               "\n"
                               "package TimingForStructuresExecution2 {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Atoms::*;\n"
                               "\tprivate import TimingForStructuresModelToBeExecuted2::*;\n"
                               "\tprivate import Occurrences::HappensDuring;\n"
                               "\tprivate import OneToOneConnectorsExecution::MyWheel;\n"
                               "\tprivate import OneToOneConnectorsExecution::MyBikeFork;\n"
                               "\t\n"
                               "\tstruct MyWheel1 specializes OneToOneConnectorsExecution::MyWheel1;\n"
                               "\tstruct MyWheel2 specializes OneToOneConnectorsExecution::MyWheel2;\n"
                               "    struct MyBikeFork1 specializes OneToOneConnectorsExecution::MyBikeFork1;\n"
                               "    struct MyBikeFork2 specializes OneToOneConnectorsExecution::MyBikeFork2;\n"
                               "\n"
                               "\t#atom\n"
                               "\tassoc MyBike_During_Wheel1_Link specializes HappensDuring {\n"
                               "\t\tend feature redefines shorterOccurrence : MyBike;\n"
                               "\t\tend feature redefines longerOccurrence : MyWheel1;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tassoc MyBike_During_Wheel2_Link specializes HappensDuring {\n"
                               "\t\tend feature redefines shorterOccurrence : MyBike;\n"
                               "\t\tend feature redefines longerOccurrence : MyWheel2;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tassoc MyBike_During_Fork1_Link specializes HappensDuring {\n"
                               "\t\tend feature redefines shorterOccurrence : MyBike;\n"
                               "\t\tend feature redefines longerOccurrence : MyBikeFork1;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tassoc MyBike_During_Fork2_Link specializes HappensDuring {\n"
                               "\t\tend feature redefines shorterOccurrence : MyBike;\n"
                               "\t\tend feature redefines longerOccurrence : MyBikeFork2;\n"
                               "\t}\n"
                               "\n"
                               "\tassoc MyBike_During_Parts_Link specializes HappensDuring\n"
                               "\t\tunions MyBike_During_Wheel1_Link, MyBike_During_Fork1_Link,\n"
                               "\t\t       MyBike_During_Wheel2_Link, MyBike_During_Fork2_Link;\n"
                               "\n"
                               "\tstruct MyBikeParts unions MyWheel, MyBikeFork;\n"
                               "\n"
                               "\t#atom\n"
                               "\tstruct MyBike specializes Bicycle {\n"
                               "\t\tfeature redefines rollsOn : MyWheel;\n"
                               "\t\tfeature redefines holdsWheel : MyBikeFork;\n"
                               "\t\tfeature redefines allParts : MyBikeParts [4];\n"
                               "\n"
                               "\t\tfeature redefines self : MyBike;\n"
                               "\t\tconnector redefines b_during_ap : MyBike_During_Parts_Link [4]\n"
                               "\t\t\tfrom [1] self to [*] allParts;\n"
                               "\t}\n"
                               "}\n"
                               "\n"
                               "package TimingForStructuresModelToBeExecuted3 {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import WithoutConnectorsModelToBeExecuted::Wheel;\n"
                               "\tprivate import WithoutConnectorsModelToBeExecuted::BikeFork;\n"
                               "\tprivate import Occurrences::Occurrence;\n"
                               "\tprivate import Occurrences::HappensWhile;\n"
                               "\n"
                               "\tstruct Bicycle {\n"
                               "\t\tfeature rollsOn : Wheel [2];\n"
                               "\t\tfeature holdsWheel : BikeFork [2];\n"
                               "\t\tfeature allParts : Occurrence unions rollsOn, holdsWheel;\n"
                               "\t\tfeature redefines endShot : Bicycle;\n"
                               "\t\tconnector be_while_pe : HappensWhile from [1] endShot to [*] endShot.allParts.endShot;\n"
                               "\t}\n"
                               "}\n"
                               "\n"
                               "package TimingForStructuresExecution3 {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Atoms::*;\n"
                               "\tprivate import TimingForStructuresModelToBeExecuted3::*;\n"
                               "\tprivate import Occurrences::Occurrence;\n"
                               "\tprivate import Occurrences::HappensWhile;\n"
                               "\tprivate import WithoutConnectorsModelToBeExecuted::Wheel;\n"
                               "\tprivate import WithoutConnectorsModelToBeExecuted::BikeFork;\n"
                               "\n"
                               "\t  /* End atoms */\n"
                               "\t#atom\n"
                               "\tstruct MyWheel1End specializes Wheel;\n"
                               "\t#atom\n"
                               "\tstruct MyWheel1 specializes Wheel {\n"
                               "\t\tfeature redefines endShot : MyWheel1End;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tstruct MyWheel2End specializes Wheel;\n"
                               "\t#atom\n"
                               "\tstruct MyWheel2 specializes Wheel {\n"
                               "\t\tfeature redefines endShot : MyWheel2End;\n"
                               "\t}\n"
                               "\tstruct MyBikeFork1End specializes BikeFork;\n"
                               "\t#atom\n"
                               "\tstruct MyBikeFork1 specializes BikeFork {\n"
                               "\t\tfeature redefines endShot : MyBikeFork1End;\n"
                               "\t}\n"
                               "\tstruct MyBikeFork2End specializes BikeFork;\n"
                               "\t#atom\n"
                               "\tstruct MyBikeFork2 specializes BikeFork {\n"
                               "\t\tfeature redefines endShot : MyBikeFork2End;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tstruct MyBikeEnd specializes Bicycle;\n"
                               "\n"
                               "\t  /* HappensWhile atoms */\n"
                               "\t#atom\n"
                               "\tassoc MyBikeEnd_While_Wheel1End_Link specializes HappensWhile {\n"
                               "\t\tend feature redefines thisOccurrence : MyBikeEnd;\n"
                               "\t\tend feature redefines thatOccurrence : MyWheel1End;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tassoc MyBikeEnd_While_Wheel2End_Link specializes HappensWhile {\n"
                               "\t\tend feature redefines thisOccurrence : MyBikeEnd;\n"
                               "\t\tend feature redefines thatOccurrence : MyWheel2End;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tassoc MyBikeEnd_While_Fork1End_Link specializes HappensWhile {\n"
                               "\t\tend feature redefines thisOccurrence : MyBikeEnd;\n"
                               "\t\tend feature redefines thatOccurrence : MyBikeFork1End;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tassoc MyBikeEnd_While_Fork2End_Link specializes HappensWhile {\n"
                               "\t\tend feature redefines thisOccurrence : MyBikeEnd;\n"
                               "\t\tend feature redefines thatOccurrence : MyBikeFork2End;\n"
                               "\t}\n"
                               "\n"
                               "\tassoc MyBikeEnd_While_PartsEnd_Link specializes HappensWhile\n"
                               "\t\tunions MyBikeEnd_While_Wheel1End_Link, MyBikeEnd_While_Fork1End_Link,\n"
                               "\t\t       MyBikeEnd_While_Wheel2End_Link, MyBikeEnd_While_Fork2End_Link;\n"
                               "\n"
                               "\t#atom\n"
                               "\tstruct MyBike specializes Bicycle {\n"
                               "\t\tfeature redefines endShot : MyBikeEnd;\n"
                               "\t\tconnector redefines be_while_pe : MyBikeEnd_While_PartsEnd_Link [4]\n"
                               "\t\t\tfrom [1] endShot to [*] endShot.allParts.endShot;  \n"
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
    parser.start()->toStringTree();
    EXPECT_EQ(listener->getSyntaxErrors().size(), 0);
}

TEST(TestKerMLParser, ConformanceTestA36Sequences) {
    std::string valueToParse = "\n"
                               "package SequencesModelToBeExecuted {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tbehavior Manufacture {\n"
                               "\t\tstep paint : Paint [1];\n"
                               "\t\tstep dry : Dry [*];\n"
                               "\t\tsuccession p_before_d first [1] paint then [1] dry;\n"
                               "\t\tstep ship : Ship [*];\n"
                               "\t\tsuccession d_before_s first [1] dry then [1] ship;\n"
                               "\t}\n"
                               "\tbehavior Paint;\n"
                               "\tbehavior Dry;\n"
                               "\tbehavior Ship;\n"
                               "}\n"
                               "\n"
                               "package SequencesExecution {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Atoms::*;\n"
                               "\tprivate import SequencesModelToBeExecuted::*;\n"
                               "\tprivate import Occurrences::Occurrence;\n"
                               "\tprivate import Occurrences::HappensBefore;\n"
                               "\n"
                               "\t#atom\n"
                               "\tbehavior MyPaint specializes Paint;\n"
                               "\t#atom\n"
                               "\tbehavior MyDry specializes Dry;\n"
                               "\n"
                               "\t#atom\n"
                               "\tassoc MyPaint_Before_Dry_Link specializes HappensBefore {\n"
                               "\t\tend feature redefines earlierOccurrence : MyPaint;\n"
                               "\t\tend feature redefines laterOccurrence : MyDry;\n"
                               "\t}\n"
                               "\n"
                               "\tbehavior MyManufactureStepsPD unions MyPaint, MyDry;\n"
                               "\n"
                               "\t#atom\n"
                               "\tbehavior MyShip specializes Ship;\n"
                               "\n"
                               "\t#atom\n"
                               "\tassoc MyDry_Before_Ship_Link specializes HappensBefore {\n"
                               "\t\tend feature redefines earlierOccurrence : MyDry;\n"
                               "\t\tend feature redefines laterOccurrence : MyShip;\n"
                               "\t}\n"
                               "\n"
                               "\tbehavior MyManufactureStepsPDS unions MyManufactureStepsPD, MyShip;\n"
                               "\n"
                               "\t#atom\n"
                               "\tbehavior MyManufacture specializes Manufacture {\n"
                               "\t\tfeature redefines timeEnclosedOccurrences : MyManufactureStepsPDS [3];\n"
                               "\t\tstep redefines paint : MyPaint;\n"
                               "\t\tstep redefines dry : MyDry [1];\n"
                               "\t\tsuccession redefines p_before_d : MyPaint_Before_Dry_Link [1] first paint then dry;\n"
                               "\t\tstep redefines ship : MyShip [1];\n"
                               "\t\tsuccession redefines d_before_s : MyDry_Before_Ship_Link [1] first dry then ship;\n"
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
    parser.start()->toStringTree();
    EXPECT_EQ(listener->getSyntaxErrors().size(), 0);
}


TEST(TestKerMLParser, ConformanceTestA37DecisionsAndMerges) {
    std::string valueToParse = "\n"
                               "package DecisionsAndMergesModelToBeExecuted {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import ControlPerformances::DecisionPerformance;\n"
                               "\tprivate import ControlPerformances::MergePerformance;\n"
                               "\tprivate import Occurrences::HappensBefore;\n"
                               "\tprivate import Links::SelfLink;\n"
                               "\n"
                               "\tbehavior Manufacture {\n"
                               "\t\t  /* Before decision. */\n"
                               "\t\tstep admit : Admit [1];\n"
                               "\t\tsuccession a_before_i first [1] admit then [1] inspect;\n"
                               "\n"
                               "\t\t  /* Decision. */\n"
                               "\t\tstep inspect : DecisionPerformance [*];\n"
                               "\n"
                               "\t\t  /* Two decision branches. */\n"
                               "\t\tsuccession i_before_f first [1] inspect then [0..1] finish;\n"
                               "\t\tstep finish : Touchup [*];\n"
                               "\t\tsuccession i_before_r first [1] inspect then [0..1] recycle;\n"
                               "\t\tstep recycle : MarkForRecycling [*];\n"
                               "\n"
                               "\t\t  /* Two merge branches. */\n"
                               "\t\tsuccession f_before_ms first [0..1] finish then [1] mShip;\n"
                               "\t\tsuccession r_before_ms first [0..1] recycle then [1] mShip;\n"
                               "\n"
                               "\t\t  /* Merge */\n"
                               "\t\tstep mShip : MergePerformance [*];\n"
                               "\n"
                               "\t\t  /* After merge */\n"
                               "\t\tsuccession ms_before_s first [1] mShip then [1] ship;\n"
                               "\t\tstep ship : Ship [*];\n"
                               "\n"
                               "\t\t  /* Decision and merge timing constraints. */\n"
                               "\t\tfeature inspectOutgoingHBLinks : HappensBefore [*] unions i_before_f, i_before_r;\n"
                               "\t\tconnector bindIOHBL : SelfLink from [1] inspectOutgoingHBLinks to [1] inspect.outgoingHBLink;\n"
                               "\t\tfeature mShipIncomingHBLinks : HappensBefore [*] unions f_before_ms, r_before_ms;\n"
                               "\t\tconnector bindmSIHBL : SelfLink from [1] mShipIncomingHBLinks to [1] mShip.incomingHBLink;\n"
                               "\t}\n"
                               "\tbehavior Admit;\n"
                               "\tbehavior Touchup;\n"
                               "\tbehavior MarkForRecycling;\n"
                               "\tbehavior Ship;\n"
                               "}\n"
                               "\n"
                               "package DecisionsAndMergesExecution {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Atoms::*;\n"
                               "\tprivate import DecisionsAndMergesModelToBeExecuted::*;\n"
                               "\tprivate import Occurrences::Occurrence;\n"
                               "\tprivate import Occurrences::HappensBefore;\n"
                               "\tprivate import ControlPerformances::DecisionPerformance;\n"
                               "\tprivate import ControlPerformances::MergePerformance;\n"
                               "\n"
                               "\t  /* Before decision. */\n"
                               "\t#atom\n"
                               "\tbehavior MyAdmit specializes Admit;\n"
                               "\n"
                               "\t  /* Decision. */\n"
                               "\t#atom\n"
                               "\tbehavior MyInspect specializes DecisionPerformance;\n"
                               "\t#atom\n"
                               "\tassoc MyAdmit_Before_Inspect_Link specializes HappensBefore {\n"
                               "\t\tend feature redefines earlierOccurrence : MyAdmit;\n"
                               "\t\tend feature redefines laterOccurrence : MyInspect;\n"
                               "\t}\n"
                               "\n"
                               "\t  /* One decision branch taken. */\n"
                               "\t#atom\n"
                               "\tbehavior MyTouchup specializes Touchup;\n"
                               "\t#atom\n"
                               "\tassoc MyInspect_Before_Touchup_Link specializes HappensBefore {\n"
                               "\t\tend feature redefines earlierOccurrence : MyInspect;\n"
                               "\t\tend feature redefines laterOccurrence : MyTouchup;\n"
                               "\t}\n"
                               "\n"
                               "\t  /* One merge branch taken. Merge. */\n"
                               "\t#atom\n"
                               "\tbehavior MyMergeToShip specializes MergePerformance;\n"
                               "\t#atom\n"
                               "\tassoc MyTouchup_Before_Merge_Link specializes HappensBefore {\n"
                               "\t\tend feature redefines earlierOccurrence : MyTouchup;\n"
                               "\t\tend feature redefines laterOccurrence : MyMergeToShip;\n"
                               "\t}\n"
                               "\n"
                               "\t  /* After merge. */\n"
                               "\t#atom\n"
                               "\tbehavior MyShip specializes Ship;\n"
                               "\t#atom\n"
                               "\tassoc MyMerge_Before_Ship_Link specializes HappensBefore {\n"
                               "\t\tend feature redefines earlierOccurrence : MyMergeToShip;\n"
                               "\t\tend feature redefines laterOccurrence : Ship;\n"
                               "\t}\n"
                               "\n"
                               "\tbehavior MyManufactureSteps unions MyAdmit, MyInspect, MyTouchup, MyMergeToShip, MyShip;\n"
                               "\n"
                               "\t#atom\n"
                               "\tbehavior MyManufacture specializes Manufacture {\n"
                               "\t\tfeature redefines timeEnclosedOccurrences : MyManufactureSteps [5];\n"
                               "\n"
                               "\t  \t    /* Before decision. */\n"
                               "\t\tstep redefines admit : MyAdmit [1];\n"
                               "\n"
                               "\t\t  /* Decision. */\n"
                               "\t\tstep redefines inspect : MyInspect [1];\n"
                               "\t\tsuccession redefines a_before_i : MyAdmit_Before_Inspect_Link [1] first admit then inspect;\n"
                               "\n"
                               "\t\t  /* One decision branch taken. */\n"
                               "\t\tstep redefines finish : MyTouchup [1];\n"
                               "\t\tsuccession redefines i_before_f : MyInspect_Before_Touchup_Link [1] first inspect then finish;\n"
                               "\n"
                               "\t\t  /* One merge branch taken. */\n"
                               "\t\tsuccession redefines f_before_ms : MyTouchup_Before_Merge_Link [1] first finish then mShip;\n"
                               "\n"
                               "\t\t  /* Merge. */        \n"
                               "\t\tstep redefines mShip: MyMergeToShip [1];\n"
                               "\n"
                               "\t\t   /* After merge */\n"
                               "\t\tstep redefines ship : MyShip [1];\n"
                               "\t\tsuccession redefines ms_before_s : MyMerge_Before_Ship_Link [1] first mShip then ship;\n"
                               "\n"
                               "\t\t  /* Decision and merge timing constraints. */  \n"
                               "\t\tfeature redefines inspectOutgoingHBLinks : MyInspect_Before_Touchup_Link;\n"
                               "\t\tfeature redefines mShipIncomingHBLinks : MyTouchup_Before_Merge_Link;\n"
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
    parser.start()->toStringTree();
    EXPECT_EQ(listener->getSyntaxErrors().size(), 0);
}

TEST(TestKerMLParser, ConformanceTestA38ChangingFeatureValues) {
    std::string valueToParse = "\n"
                               "package ChangingFeatureValuesModelToBeExecuted {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import ScalarValues::Boolean;\n"
                               "\tprivate import FeatureReferencingPerformances::FeatureWritePerformance;\n"
                               "\n"
                               "\tbehavior Manufacture {\n"
                               "\t\tfeature objectToFinish : Product [1];\n"
                               "\t\tstep paint : Paint [1] {\n"
                               "\t\t\tredefines objectToPaint = objectToFinish;\n"
                               "\t\t}\n"
                               "\t\tstep dry : Dry [*] {\n"
                               "\t\t\tredefines objectToDry = objectToFinish;\n"
                               "\t\t}\n"
                               "\t\tsuccession p_before_d first [1] paint then [1] dry;\n"
                               "\t\tstep ship : Ship [*] {\n"
                               "\t\t\tredefines objectToShip = objectToFinish;\n"
                               "\t\t}\n"
                               "\t\tsuccession d_before_s first [1] dry then [1] ship;\n"
                               "\t}\n"
                               "\n"
                               "\tstruct Product {\n"
                               "\t\tvar feature isPainted : Boolean [1] := false;\n"
                               "\t\tvar feature isDry : Boolean [1] := true;\n"
                               "\t\tvar feature isShipped : Boolean [1] := false;\n"
                               "\t}\n"
                               "\n"
                               "\tbehavior Paint {\n"
                               "\t\tfeature objectToPaint : Product [1];\n"
                               "\n"
                               "\t\tstep painting : FeatureWritePerformance [1] {\n"
                               "\t\t\tin redefines onOccurrence : Product = objectToPaint {\n"
                               "\t\t\t\tredefines startingAt : Product {\n"
                               "\t\t\t\t\tredefines accessedFeature : Boolean [1] subsets isDry; } }\n"
                               "\t\t\tin redefines replacementValues = false;\n"
                               "\t\t}\n"
                               "\n"
                               "\t\tsuccession p_before_p first [1] painting then [1] painted;\n"
                               "\t\tstep painted : FeatureWritePerformance [*] {\n"
                               "\t\t\tin redefines onOccurrence : Product = objectToPaint {\n"
                               "\t\t\t\tredefines startingAt : Product {\n"
                               "\t\t\t\t\tredefines accessedFeature : Boolean [1] subsets isPainted; } }\n"
                               "\t\t\tin redefines replacementValues = true;\n"
                               "\t\t}\n"
                               "\t}\n"
                               "\n"
                               "\tbehavior Dry {\n"
                               "\t\tfeature objectToDry : Product [1];\n"
                               "\t\tstep dried : FeatureWritePerformance [1] {\n"
                               "\t\t\tin redefines onOccurrence : Product = objectToDry {\n"
                               "\t\t\t\tredefines startingAt : Product {\n"
                               "\t\t\t\t\tredefines accessedFeature : Boolean [1] subsets isDry; } }\n"
                               "\t\t\tin redefines replacementValues = true;\n"
                               "\t\t}\n"
                               "\t}\n"
                               "\n"
                               "\tbehavior Ship {\n"
                               "\t\tfeature objectToShip : Product [1];  \n"
                               "\t\tstep shipped : FeatureWritePerformance [1] {\n"
                               "\t\t\tin redefines onOccurrence : Product = objectToShip {\n"
                               "\t\t\t\tredefines startingAt : Product {\n"
                               "\t\t\t\t\tredefines accessedFeature : Boolean [1] subsets isShipped; } }\n"
                               "\t\t\tin redefines replacementValues = true;\n"
                               "\t\t}\n"
                               "\t}\n"
                               "}\n"
                               "\n"
                               "package ChangingFeatureValuesExecution {\n"
                               "\tdoc\n"
                               "\t/* \n"
                               "\t */\n"
                               "\n"
                               "\tprivate import Atoms::*;\n"
                               "\tprivate import ChangingFeatureValuesModelToBeExecuted::*;\n"
                               "\tprivate import Occurrences::Occurrence;\n"
                               "\tprivate import Occurrences::HappensBefore;\n"
                               "\tprivate import FeatureReferencingPerformances::FeatureWritePerformance;\n"
                               "\n"
                               "\tstruct ProductTimeSlice specializes Product {\n"
                               "\t\tfeature redefines isPainted;\n"
                               "\t\tfeature redefines isDry;\n"
                               "\t\tfeature redefines isShipped;\n"
                               "\t}\n"
                               "\n"
                               "\t#atom\n"
                               "\tstruct MyProduct specializes Product {\n"
                               "\t\tfeature beforePaint : ProductTimeSlice [1] subsets timeSlices;\n"
                               "\t\tfeature whilePainting : ProductTimeSlice [1] subsets timeSlices;\n"
                               "\t\tfeature afterPaint : ProductTimeSlice [1] subsets timeSlices;\n"
                               "\t\tfeature afterDry : ProductTimeSlice [1] subsets timeSlices;\n"
                               "\t\tfeature afterShip : ProductTimeSlice [1] subsets timeSlices;  \n"
                               "\t}\n"
                               "\n"
                               "\tbehavior MyProductFeatureWrite specializes FeatureWritePerformance {\n"
                               "\t\tin redefines onOccurrence : MyProduct;\n"
                               "\t}\n"
                               "\n"
                               "\t#atom\n"
                               "\tbehavior PaintingMyProductFeatureWrite specializes MyProductFeatureWrite;\n"
                               "\t#atom\n"
                               "\tbehavior PaintedMyProductFeatureWrite specializes MyProductFeatureWrite;\n"
                               "\t#atom\n"
                               "\tassoc MyPaintingFW_Before_PaintFW_Link specializes HappensBefore {\n"
                               "\t\tend feature redefines earlierOccurrence : PaintingMyProductFeatureWrite;\n"
                               "\t\tend feature redefines laterOccurrence : PaintedMyProductFeatureWrite;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tbehavior MyPaint specializes Paint {\n"
                               "\t\tfeature redefines objectToPaint : MyProduct;\n"
                               "\t\tstep redefines painting : PaintingMyProductFeatureWrite;\n"
                               "\t\tstep redefines painted : PaintedMyProductFeatureWrite;\n"
                               "\t\tsuccession redefines p_before_p : MyPaintingFW_Before_PaintFW_Link first painting then painted;\n"
                               "\t}\n"
                               "\n"
                               "\t#atom\n"
                               "\tbehavior MyDry specializes Dry {\n"
                               "\t\tfeature redefines objectToDry : MyProduct;\n"
                               "\t\tstep redefines dried : MyProductFeatureWrite;  \n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tassoc MyPaint_Before_Dry_Link specializes HappensBefore {\n"
                               "\t\tend feature redefines earlierOccurrence : MyPaint;\n"
                               "\t\tend feature redefines laterOccurrence : MyDry;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tbehavior MyShip specializes Ship {\n"
                               "\t\tfeature redefines objectToShip : MyProduct;\n"
                               "\t\tstep redefines shipped : MyProductFeatureWrite;  \n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tassoc MyDry_Before_Ship_Link specializes HappensBefore {\n"
                               "\t\tend feature redefines earlierOccurrence : MyDry;\n"
                               "\t\tend feature redefines laterOccurrence : MyShip;\n"
                               "\t}\n"
                               "\t#atom\n"
                               "\tbehavior MyManufacture specializes Manufacture {\n"
                               "\t\tfeature redefines objectToFinish : MyProduct;\n"
                               "\t\tfeature redefines startShot subsets objectToFinish.beforePaint.startShot.timeCoincidentOccurrences;\n"
                               "\t\tfeature obPiP chains objectToFinish.beforePaint.isPainted = false;\n"
                               "\t\tfeature obPiD chains objectToFinish.beforePaint.isDry = true;\n"
                               "\t\tfeature obPiS chains objectToFinish.beforePaint.isShipped = false;\n"
                               "\n"
                               "\n"
                               "\t\tstep redefines paint : MyPaint;\n"
                               "\t\tfeature subsets objectToFinish.beforePaint.immediateSuccessors,\n"
                               "\t\t\t\tobjectToFinish.whilePainting.startShot.timeCoincidentOccurrences\n"
                               "\t\t\tchains paint.painting.endShot;\n"
                               "\t\tfeature owPiP chains objectToFinish.whilePainting.isPainted = false;\n"
                               "\t\tfeature owPiD chains objectToFinish.whilePainting.isDry = false;\n"
                               "\t\tfeature owPiS chains objectToFinish.whilePainting.isShipped = false;\n"
                               "\n"
                               "\n"
                               "\t\tfeature subsets objectToFinish.whilePainting.immediateSuccessors,\n"
                               "\t\t\t\tobjectToFinish.afterPaint.startShot.timeCoincidentOccurrences\n"
                               "\t\t\tchains paint.painted.endShot;\n"
                               "\t\tfeature oaPiP chains objectToFinish.afterPaint.isPainted = true;\n"
                               "\t\tfeature oaPiD chains objectToFinish.afterPaint.isDry = false;\n"
                               "\t\tfeature oaPiS chains objectToFinish.afterPaint.isShipped = false;\n"
                               "\n"
                               "\n"
                               "\t\tstep redefines dry : MyDry;\n"
                               "\t\tsuccession redefines p_before_d : MyPaint_Before_Dry_Link [1] first paint then dry;\n"
                               "\t\tfeature subsets objectToFinish.afterPaint.immediateSuccessors,\n"
                               "\t\t\t\tobjectToFinish.afterDry.startShot.timeCoincidentOccurrences\n"
                               "\t\t\tchains dry.dried.endShot;\n"
                               "\t\tfeature oaDiP chains objectToFinish.afterDry.isPainted = true;\n"
                               "\t\tfeature oaDiD chains objectToFinish.afterDry.isDry = true;\n"
                               "\t\tfeature oaDiS chains objectToFinish.afterDry.isShipped = false;\n"
                               "\n"
                               "\n"
                               "\t\tstep redefines ship : MyShip;\n"
                               "\t\tsuccession redefines d_before_s : MyDry_Before_Ship_Link [1] first dry then ship;\n"
                               "\t\tfeature subsets objectToFinish.afterDry.immediateSuccessors,\n"
                               "\t\t\t\tobjectToFinish.afterShip.startShot.timeCoincidentOccurrences\n"
                               "\t\t\tchains ship.shipped.endShot;\n"
                               "\t\tfeature redefines endShot subsets objectToFinish.afterShip.timeCoincidentOccurrences;\n"
                               "\t\tfeature oaSiP chains objectToFinish.afterShip.isPainted = true;\n"
                               "\t\tfeature oaSiD chains objectToFinish.afterShip.isDry = true;\n"
                               "\t\tfeature oaSiS chains objectToFinish.afterShip.isShipped = true;\n"
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
    parser.start()->toStringTree();
    EXPECT_EQ(listener->getSyntaxErrors().size(), 0);
}