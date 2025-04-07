//
// Created by Moritz Herzog on 07.04.25.
//

#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include <parsing/kerml/KerMLParser.h>
#include <parsing/kerml/KerMLLexer.h>
#include <parsing/kerml/KerMLListener.h>


TEST(TestKerMLParser, TestVehicleDefinitions) {
    std::string valueToParse = "package VehicleDefinitions {\n"
                               "\tdoc\n"
                               "\t/*\n"
                               "\t * Example vehicle definitions model.\n"
                               "\t */\n"
                               "\n"
                               "\t\n"
                               "\t/* BLOCKS */\n"
                               "\t\n"
                               "\tclass Vehicle;\t\n"
                               "\tclass Transmission;\t\n"
                               "\tclass AxleAssembly;\n"
                               "\tclass Axle;\t\n"
                               "\tclass Wheel;\n"
                               "\tclass Lugbolt {\n"
                               "\t\ttighteningTorque[1] : ScalarValues::Real;\n"
                               "\t}\n"
                               "\t\n"
                               "\t/* INTERFACE BLOCKS */\n"
                               "\t\n"
                               "\tclass DriveIF { \n"
                               "\t\tin driveTorque: ScalarValues::Real;\n"
                               "\t}\n"
                               "\t\n"
                               "\tclass AxleMountIF { \n"
                               "\t\tout transferredTorque : ScalarValues::Real;\n"
                               "\t}\n"
                               "\t\n"
                               "\tclass WheelHubIF { \n"
                               "\t\tin appliedTorque : ScalarValues::Real;\n"
                               "\t}\n"
                               "\t\n"
                               "\t/* ASSOCIATION BLOCKS */\n"
                               "\t\n"
                               "\tassoc Mounting {\n"
                               "\t\tdoc\n"
                               "\t\t/*\n"
                               "\t\t *  mounting a Wheel to an Axle.\n"
                               "\t\t */\n"
                               "\t\n"
                               "\t\tend axleMount: AxleMountIF;\n"
                               "\t\tend hub: WheelHubIF;\n"
                               "\t}\n"
                               "}";

    // Provide the input text in a stream
    antlr4::ANTLRInputStream input(valueToParse);

    // Create a lexer from the input
    KerMLLexer lexer(&input);

    // Create a token stream from the lexer
    antlr4::CommonTokenStream tokens(&lexer);

    // Create a parser from the token stream
    KerMLParser parser(&tokens);
    EXPECT_FALSE(parser.start()->exception!= nullptr);
    EXPECT_FALSE(parser.start()->elements()->exception!= nullptr);
    EXPECT_FALSE(parser.start()->elements()->element().empty());
    for(const auto& element : parser.start()->elements()->element())
    {
        EXPECT_FALSE(element->exception != nullptr);
    }
    // Display the parse tree
    //std::cout << parser.start()->toStringTree() << std::endl;
}