//
// Created by Moritz Herzog on 07.04.25.
//

#include <gtest/gtest.h>
#include <antlr4-runtime.h>
#include <kerml/parser/KerMLParser.h>
#include <kerml/parser/KerMLLexer.h>
#include <kerml/parser/KerMLListener.h>
#include <kerml/parser/KerMlErrorListener.h>
#include <sysmlv2/Parser.h>
#include <kerml/parser/KerMlListenerImplementation.h>
#include <kerml/kernel/packages/Package.h>
#include <kerml/kernel/classes/Class.h>
#include <kerml/core/features/Feature.h>
#include <kerml/KerML.h>

namespace {
template<class T>
std::vector<std::shared_ptr<T>> listenerElements(const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements) {
    std::vector<std::shared_ptr<T>> result;
    for (const auto& element : elements) {
        if (auto typed = std::dynamic_pointer_cast<T>(element)) result.push_back(typed);
    }
    return result;
}
}

TEST(TestKerMLListener, StandaloneRelationshipsAndBodies) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "class C; feature a : C; feature b : C; "
        "specialization <s> restriction subset a subsets b { doc /* subset */ } "
        "inverting inversion inverse a of b; featuring placement of a by C;");
    ASSERT_TRUE(errors.empty());
    const auto subsets = listenerElements<Subsetting>(elements);
    ASSERT_EQ(subsets.size(), 1u);
    EXPECT_EQ(subsets[0]->declaredName().value_or(""), "restriction");
    EXPECT_EQ(subsets[0]->declaredShortName().value_or(""), "s");
    EXPECT_EQ(subsets[0]->subsettingFeature()->declaredName().value_or(""), "a");
    EXPECT_EQ(subsets[0]->subsettedFeature()->declaredName().value_or(""), "b");
    EXPECT_EQ(listenerElements<Documentation>(subsets[0]->ownedElements()).size(), 1u);
    const auto inversions = listenerElements<FeatureInverting>(elements);
    ASSERT_EQ(inversions.size(), 1u);
    EXPECT_EQ(inversions[0]->invertingFeature(), subsets[0]->subsettingFeature());
    EXPECT_EQ(inversions[0]->featureInverted(), subsets[0]->subsettedFeature());
    const auto featuring = listenerElements<TypeFeaturing>(elements);
    ASSERT_EQ(featuring.size(), 1u);
    EXPECT_EQ(featuring[0]->featureOfType(), subsets[0]->subsettingFeature());
    EXPECT_EQ(featuring[0]->featuringType()->declaredName().value_or(""), "C");
}

TEST(TestKerMLListener, ConditionalValueKeepsOrderedArguments) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "feature choice = if true ? 10 else 20;");
    ASSERT_TRUE(errors.empty());
    const auto values = listenerElements<FeatureValue>(elements);
    ASSERT_EQ(values.size(), 1u);
    const auto expression = std::dynamic_pointer_cast<OperatorExpression>(values[0]->value());
    ASSERT_NE(expression, nullptr);
    EXPECT_EQ(expression->operatorName(), "if");
    ASSERT_EQ(expression->argument().size(), 3u);
    EXPECT_NE(std::dynamic_pointer_cast<LiteralBoolean>(expression->argument()[0]), nullptr);
    auto thenValue = std::dynamic_pointer_cast<LiteralInteger>(expression->argument()[1]);
    auto elseValue = std::dynamic_pointer_cast<LiteralInteger>(expression->argument()[2]);
    ASSERT_NE(thenValue, nullptr);
    ASSERT_NE(elseValue, nullptr);
    EXPECT_EQ(thenValue->value(), 10);
    EXPECT_EQ(elseValue->value(), 20);
}

TEST(TestKerMLListener, MultiplicityOptionsAndSubset) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "feature items : Integer[0..*] ordered nonunique; multiplicity count subsets items;");
    ASSERT_TRUE(errors.empty());
    std::shared_ptr<Feature> items;
    for (const auto& element : elements) {
        if (element->declaredName() == "items") items = std::dynamic_pointer_cast<Feature>(element);
    }
    ASSERT_NE(items, nullptr);
    EXPECT_TRUE(items->isOrdered());
    EXPECT_FALSE(items->isUnique());
    std::shared_ptr<Multiplicity> count;
    for (const auto& element : listenerElements<Multiplicity>(elements)) {
        if (element->declaredName() == "count") count = element;
    }
    ASSERT_NE(count, nullptr);
    ASSERT_EQ(count->ownedSubsetting().size(), 1u);
    EXPECT_EQ(count->ownedSubsetting()[0]->subsettedFeature(), items);
}

TEST(TestKerMLListener, FilterRetainsConditionAndVisibility) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "package P { private filter true; }");
    ASSERT_TRUE(errors.empty());
    const auto filters = listenerElements<ElementFilterMembership>(elements);
    ASSERT_EQ(filters.size(), 1u);
    EXPECT_EQ(filters[0]->visibility(), PRIVATE);
    EXPECT_NE(std::dynamic_pointer_cast<LiteralBoolean>(filters[0]->condition()), nullptr);
    ASSERT_NE(filters[0]->membershipOwningNamespace(), nullptr);
    EXPECT_EQ(filters[0]->membershipOwningNamespace()->declaredName().value_or(""), "P");
}

TEST(TestKerMLListener, NamespaceMembershipKeepsVisibilityAndTarget) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "namespace N { private feature value : Integer; }");
    ASSERT_TRUE(errors.empty());
    // (Every top level element is a member of the root namespace, so N has a membership as well; look at the one of `value`.)
    std::vector<std::shared_ptr<OwningMembership>> memberships;
    for (const auto& membership : listenerElements<OwningMembership>(elements)) {
        if (membership->memberElement() && membership->memberElement()->declaredName().value_or("") == "value") memberships.push_back(membership);
    }
    ASSERT_EQ(memberships.size(), 1u);
    EXPECT_EQ(memberships[0]->visibility(), PRIVATE);
    ASSERT_NE(memberships[0]->memberElement(), nullptr);
    EXPECT_EQ(memberships[0]->memberElement()->declaredName().value_or(""), "value");
    ASSERT_NE(memberships[0]->membershipOwningNamespace(), nullptr);
    EXPECT_EQ(memberships[0]->membershipOwningNamespace()->declaredName().value_or(""), "N");
}

TEST(TestKerMLListener, NamedInvocationArgumentRetainsParameterAndValue) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "function calculate; feature result = calculate(input = 42);");
    ASSERT_TRUE(errors.empty());
    const auto invocations = listenerElements<InvocationExpression>(elements);
    ASSERT_EQ(invocations.size(), 1u);
    ASSERT_EQ(invocations[0]->argument().size(), 1u);
    const auto argument = invocations[0]->argument()[0];
    ASSERT_EQ(argument->ownedRedefinition().size(), 1u);
    EXPECT_EQ(argument->ownedRedefinition()[0]->redefinedFeature()->declaredName().value_or(""), "input");
    const auto literals = listenerElements<LiteralInteger>(argument->ownedElements());
    ASSERT_EQ(literals.size(), 1u);
    EXPECT_EQ(literals[0]->value(), 42);
}

TEST(TestKerMLListener, FeatureChainPreservesOrderAndRelationships) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "feature a; feature b; feature path chains a.b;");
    ASSERT_TRUE(errors.empty());
    std::shared_ptr<Feature> path;
    for (const auto& element : elements) {
        if (element->declaredName() == "path") path = std::dynamic_pointer_cast<Feature>(element);
    }
    ASSERT_NE(path, nullptr);
    ASSERT_EQ(path->chainingFeature().size(), 2u);
    EXPECT_EQ(path->chainingFeature()[0]->declaredName().value_or(""), "a");
    EXPECT_EQ(path->chainingFeature()[1]->declaredName().value_or(""), "b");
    ASSERT_EQ(path->ownedFeatureChaining().size(), 2u);
    EXPECT_EQ(path->ownedFeatureChaining()[0]->featureChained(), path);
}

TEST(TestKerMLListener, ClassificationAndMetadataAssignmentsProduceValues) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "class C; feature source : C; feature check = source istype C; "
        "metaclass M { baseType = C meta KerML::Classifier; }");
    ASSERT_TRUE(errors.empty());
    const auto operators = listenerElements<OperatorExpression>(elements);
    ASSERT_EQ(operators.size(), 1u);
    EXPECT_EQ(operators[0]->operatorName(), "istype");
    ASSERT_EQ(operators[0]->argument().size(), 2u);
    EXPECT_NE(std::dynamic_pointer_cast<FeatureReferenceExpression>(operators[0]->argument()[0]), nullptr);
    const auto typeReference = std::dynamic_pointer_cast<InstantiationExpression>(operators[0]->argument()[1]);
    ASSERT_NE(typeReference, nullptr);
    ASSERT_NE(typeReference->instantiatedType(), nullptr);
    EXPECT_EQ(typeReference->instantiatedType()->declaredName().value_or(""), "C");
    const auto metadata = listenerElements<MetadataAccessExpression>(elements);
    ASSERT_EQ(metadata.size(), 1u);
    ASSERT_NE(metadata[0]->referencedElement(), nullptr);
    EXPECT_EQ(metadata[0]->referencedElement()->declaredName().value_or(""), "C");
    const auto values = listenerElements<FeatureValue>(elements);
    ASSERT_EQ(values.size(), 2u);
    EXPECT_EQ(values[1]->value(), metadata[0]);
}

TEST(TestKerMLParser, TestAddressBookModel) {
     std::string valueToParse = "private import ScalarValues::*;\n"
                                "package AddressBookModel {\n"
                                "\t\n"
                                "\tclass Entry {\n"
                                "\t\tfeature name: String;\n"
                                "\t\tfeature address: String;\n"
                                "\t}\n"
                                "\t\n"
                                "\tclass AddressBook {\n"
                                "\t\tfeature entries: Entry[*];\n"
                                "\t}\n"
                                "\t\n"
                                "}";


     const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
     EXPECT_EQ(returnValue.second.size(), 0);
     EXPECT_FALSE(returnValue.first.empty());

     std::shared_ptr<KerML::Entities::Package> pkg;
     for (const auto& elem : returnValue.first) {
         if (auto p = std::dynamic_pointer_cast<KerML::Entities::Package>(elem)) {
             pkg = p;
             break;
         }
     }
     ASSERT_NE(pkg, nullptr);
     EXPECT_EQ(pkg->declaredName().value_or(""), "AddressBookModel");
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

     const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
     EXPECT_EQ(returnValue.second.size(),0);
 }

// Note: TestJohnIndividualModel uses anonymous invariant syntax `inv { age >= 35 }`,
// which requires grammar update in KerML.g4 (making feature_declaration optional and function_body_part nullable).
// TEST(TestKerMLParser, TestJohnIndividualModel) {
//     std::string valueToParse = "package JohnIndividualExample {\n"
//                                "\tprivate import Objects::*;\n"
//                                "\t\n"
//                                "\tclass Person specializes Object {\n"
//                                "\t\tdoc\n"
//                                "\t\t/*\n"
//                                "\t\t  This is the class of persons, each of whom has an age.\n"
//                                "\t\t  It is NOT restricted to maximal portions.\n"
//                                "\t\t  (The specialization of Object would normally be left implicit.)\n"
//                                "\t\t*/\n"
//                                "\t\n"
//                                "\t\tclass Life specializes Person, Occurrences::Life;\n"
//                                "\t\t\n"
//                                "\t\tfeature age : ScalarValues::Natural;\n"
//                                "\t  \n"
//                                "\t  feature redefines portions : Person {\n"
//                                "\t\t  doc\n"
//                                "\t\t  /*\n"
//                                "\t\t    These redefinitions enforce the \"rigidity\" constraint for Person.\n"
//                                "\t\t    They ensure that all portions of a person are also persons and \n"
//                                "\t\t    that a person can only be a portion of another person. This implies\n"
//                                "\t\t    that the class Person must also include all the portions of any one \n"
//                                "\t\t    of its instances. The redefinitions for the portion features\n"
//                                "\t\t    also implicitly constraint the typing of the time slice and snapshot\n"
//                                "\t\t    features, since they are subsets of portioning.\n"
//                                "\t\t    (It is currently awkward to have to declare these redefinitions\n"
//                                "\t\t    explicitly.)\n"
//                                "\t\t  */\n"
//                                "\t  }\n"
//                                "\t  feature redefines portionOf : Person;\n"
//                                "\t\n"
//                                "\t}\n"
//                                "\t\n"
//                                "\tclass President specializes Person {\n"
//                                "\t\tdoc\n"
//                                "\t\t/*\n"
//                                "\t\t  This is the class of presidents, each of which must be a time slice\n"
//                                "\t\t  of the life of some individual person.\n"
//                                "\t\t  (Note that this class is NOT \"rigid\".)\n"
//                                "\t\t*/\n"
//                                "\t\n"
//                                "\t  feature redefines timeSliceOf : Person::Life [1];\n"
//                                "\t}\n"
//                                "\t\n"
//                                "\tclass John specializes Person {\n"
//                                "\t\tdoc\n"
//                                "\t\t/*\n"
//                                "\t\t  This is the class of the specific (individual) person who is John.\n"
//                                "\t\t  There is at most one such person.\n"
//                                "\t\t*/\n"
//                                "\t\n"
//                                "\t\tclass all JohnLife[0..1] specializes John, Occurrences::Life;\n"
//                                "\t} \n"
//                                "\t\n"
//                                "\tclass JohnAsPresident specializes John, President {\n"
//                                "\t\tdoc\n"
//                                "\t\t/*\n"
//                                "\t\t  This is the class of time slices of John's life in which he is\n"
//                                "\t\t  a president.\n"
//                                "\t\t*/\n"
//                                "\t}\n"
//                                "\t\n"
//                                "\tclass Country specializes Object {\n"
//                                "\t\tdoc\n"
//                                "\t\t/*\n"
//                                "\t\t  This is the class of countries, each of which may have at most one\n"
//                                "\t\t  president.\n"
//                                "\t\t*/\n"
//                                "\t\n"
//                                "\t\tclass all Life specializes Country, Occurrences::Life;\n"
//                                "\n"
//                                "\t\tfeature presidentOfCountry : President[0..1];\n"
//                                "\t  \n"
//                                "\t  \t// Rigidity constraint.\n"
//                                "\t  \tfeature redefines portions : Country;\n"
//                                "\t  \tfeature redefines portionOf : Country;\n"
//                                "\t}\n"
//                                "\t\n"
//                                "\tclass UnitedStates specializes Country {\n"
//                                "\t\tdoc\n"
//                                "\t\t/*\n"
//                                "\t\t  This is the class of the specific country that is the\n"
//                                "\t\t  United States. It contains a single instance. The United States\n"
//                                "\t\t  always has a president who must be at least 35 years old.\n"
//                                "\t\t*/\n"
//                                "\t\n"
//                                "\t\tclass all USLife[1] specializes UnitedStates, Occurrences::Life ;\n"
//                                "\t  \tfeature presidentOfUS[1] redefines presidentOfCountry {\n"
//                                "\t   \t\tinv { age >= 35 } \n"
//                                "\t  \t}\n"
//                                "\t}\n"
//                                "\t\n"
//                                "\tclass UnitedStatesWithJohnAsPresident specializes UnitedStates {\n"
//                                "\t\tdoc\n"
//                                "\t\t/*\n"
//                                "\t\t  This is the class of time slices of the United States during\n"
//                                "\t\t  which John is president of the United States.\n"
//                                "\t\t*/\n"
//                                "\t\n"
//                                "\t  feature redefines timeSliceOf : UnitedStates::Life;\n"
//                                "\t  feature redefines presidentOfUS : JohnAsPresident;\n"
//                                "\t}\n"
//                                "}";
// 
//     const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
//     EXPECT_EQ(returnValue.second.size(), 0);
// }

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

    const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
    EXPECT_EQ(returnValue.second.size(),0);
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

    const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
    EXPECT_EQ(returnValue.second.size(),0);
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

     const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
     EXPECT_EQ(returnValue.second.size(),0);
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

     const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
     EXPECT_EQ(returnValue.second.size(), 0);
 }

 //TEST(TestKerMLParser, ConformanceTestA35TimingForStructures) {
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

    const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
    EXPECT_EQ(returnValue.second.size(), 0);
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

    const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
    EXPECT_EQ(returnValue.second.size(), 0);
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

    const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
    EXPECT_EQ(returnValue.second.size(), 0);
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

    const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
    EXPECT_EQ(returnValue.second.size(), 0);
}

TEST(TestKerMLParser, TestKerMLAdvancedEntities) {
    std::string valueToParse = "package TestPkg {\n"
                               "\timport OtherPkg::singleItem;\n"
                               "\tclassifier A;\n"
                               "\tclassifier B;\n"
                               "\tdependency Dep from A to B;\n"
                               "\tconjugate A conjugates B;\n"
                               "\tdisjoint A from B;\n"
                               "\tsubclassifier A specializes B;\n"
                               "\tclass Holder {\n"
                               "\t\tfeature featA;\n"
                               "\t\tfeature featB;\n"
                               "\t\tconnector c from featA to featB;\n"
                               "\t}\n"
                               "\tfunction testFn {\n"
                               "\t\treturn feature retVal;\n"
                               "\t\t(retVal)\n"
                               "\t}\n"
                               "}";

    const auto returnValue = SysMLv2::Files::Parser::parseKerML(valueToParse);
    EXPECT_EQ(returnValue.second.size(), 0);
    EXPECT_FALSE(returnValue.first.empty());

    bool foundDep = false;
    bool foundMemImport = false;
    bool foundConjugation = false;
    bool foundDisjoining = false;
    bool foundSubclassification = false;
    bool foundReturnParamMem = false;
    bool foundResultExprMem = false;
    bool foundFeatureMem = false;
    bool foundEndFeatureMem = false;

    for (const auto& elem : returnValue.first) {
        if (std::dynamic_pointer_cast<KerML::Entities::Dependency>(elem)) foundDep = true;
        if (std::dynamic_pointer_cast<KerML::Entities::MembershipImport>(elem)) foundMemImport = true;
        if (std::dynamic_pointer_cast<KerML::Entities::Conjugation>(elem)) foundConjugation = true;
        if (std::dynamic_pointer_cast<KerML::Entities::Disjoining>(elem)) foundDisjoining = true;
        if (std::dynamic_pointer_cast<KerML::Entities::Subclassification>(elem)) foundSubclassification = true;
        if (std::dynamic_pointer_cast<KerML::Entities::ReturnParameterMembership>(elem)) foundReturnParamMem = true;
        if (std::dynamic_pointer_cast<KerML::Entities::ResultExpressionMembership>(elem)) foundResultExprMem = true;
        if (std::dynamic_pointer_cast<KerML::Entities::FeatureMembership>(elem)) foundFeatureMem = true;
        if (std::dynamic_pointer_cast<KerML::Entities::EndFeatureMembership>(elem)) foundEndFeatureMem = true;
    }

    EXPECT_TRUE(foundDep);
    EXPECT_TRUE(foundMemImport);
    EXPECT_TRUE(foundConjugation);
    EXPECT_TRUE(foundDisjoining);
    EXPECT_TRUE(foundSubclassification);
    EXPECT_TRUE(foundReturnParamMem);
    EXPECT_TRUE(foundResultExprMem);
    EXPECT_TRUE(foundFeatureMem);
    EXPECT_TRUE(foundEndFeatureMem);
}

namespace {
// Returns the sequence of element type names, in creation order, skipping the DataTypes
// injected by the parser's implicit prelude (they are identical for both forms below and
// are not the point of the comparison).
std::vector<std::string> typeSequenceSkippingDataTypes(const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements) {
    std::vector<std::string> result;
    for (const auto& element : elements) {
        if (!element) continue;
        if (element->getType() == "DataType") continue;
        result.push_back(element->getType());
    }
    return result;
}
}

// Regression test for review defect A: `anonymous_feature` is an alternative INSIDE the
// `feature` rule (feature: ... | anonymous_feature), not a separate parse-tree layer, so
// enterFeature/exitFeature already push/pop/attach the Feature for that same context
// regardless of which alternative matched. enter/exitAnonymous_feature must therefore be
// true no-ops, so the anonymous form (`in x : T;`) produces an element-type sequence
// IDENTICAL to the explicit form (`feature x : T;`), and `x` keeps direction IN and name
// "x" either way.
TEST(TestKerMLParser, AnonymousFeatureMatchesExplicitFeatureStructure) {
    using namespace KerML::Entities;

    const auto explicitForm = SysMLv2::Files::Parser::parseKerML(
        "package P { function f { feature x : T; return feature r : R; } }");
    ASSERT_TRUE(explicitForm.second.empty());

    const auto anonymousForm = SysMLv2::Files::Parser::parseKerML(
        "package P { function f { in x : T; return r : R; } }");
    ASSERT_TRUE(anonymousForm.second.empty());

    const auto explicitTypes = typeSequenceSkippingDataTypes(explicitForm.first);
    const auto anonymousTypes = typeSequenceSkippingDataTypes(anonymousForm.first);
    EXPECT_EQ(explicitTypes, anonymousTypes)
        << "anonymous_feature must not push a second, empty Feature/OwningMembership pair";

    // The anonymous form's `x` must be the same shape as the explicit form's: a Feature
    // named "x" with direction IN, not an extra empty Feature.
    const auto explicitFeatures = listenerElements<Feature>(explicitForm.first);
    const auto anonymousFeatures = listenerElements<Feature>(anonymousForm.first);
    ASSERT_EQ(explicitFeatures.size(), anonymousFeatures.size());

    auto findByName = [](const std::vector<std::shared_ptr<Feature>>& features, const std::string& name) {
        for (const auto& f : features) if (f->declaredName().value_or("") == name) return f;
        return std::shared_ptr<Feature>();
    };
    auto anonX = findByName(anonymousFeatures, "x");
    ASSERT_NE(anonX, nullptr);
    ASSERT_TRUE(anonX->direction().has_value());
    EXPECT_EQ(*anonX->direction(), FeatureDirectionKind::IN);

    // No feature in the anonymous form's element list should be an unnamed/empty Feature
    // (that was the symptom of the double-push bug: an extra Feature with no name).
    for (const auto& f : anonymousFeatures) {
        EXPECT_FALSE(f->declaredName().value_or("").empty())
            << "found an unnamed Feature - likely a leftover double push from anonymous_feature";
    }
}

// Regression test for the isUnique/KEYWORD_ALL bug: exitFeature_declaration used to set
// isUnique from KEYWORD_ALL (FeatureDeclaration's unrelated "isSufficient" marker), which
// forced isUnique() to false on every feature not using the (rare) 'all' marker. Uniqueness
// must come only from 'nonunique' in the multiplicity part (default true when absent).
TEST(TestKerMLParser, FeatureDeclarationIsUniqueNotFromKeywordAll) {
    using namespace KerML::Entities;

    const auto nonunique = SysMLv2::Files::Parser::parseKerML(
        "package P { class C { feature a[*] nonunique; } }");
    ASSERT_TRUE(nonunique.second.empty());
    const auto nonuniqueFeatures = listenerElements<Feature>(nonunique.first);
    bool foundA = false;
    for (const auto& f : nonuniqueFeatures) {
        if (f->declaredName().value_or("") == "a") {
            foundA = true;
            EXPECT_FALSE(f->isUnique());
        }
    }
    EXPECT_TRUE(foundA);

    const auto defaultUnique = SysMLv2::Files::Parser::parseKerML(
        "package P { class C { feature b[*]; } }");
    ASSERT_TRUE(defaultUnique.second.empty());
    const auto defaultFeatures = listenerElements<Feature>(defaultUnique.first);
    bool foundB = false;
    for (const auto& f : defaultFeatures) {
        if (f->declaredName().value_or("") == "b") {
            foundB = true;
            EXPECT_TRUE(f->isUnique());
        }
    }
    EXPECT_TRUE(foundB);
}

// ---- AP8: expression grammar (KerML 1.1, clause 8.2.5.8), operator trees, precedence and associativity ----
namespace {
using namespace KerML::Entities;

std::shared_ptr<Expression> kermlValue(const std::string& expression) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML("feature x = " + expression + ";");
    if (!errors.empty()) {
        ADD_FAILURE() << "syntax error in '" << expression << "': " << errors.front()->description();
        return nullptr;
    }
    for (const auto& element : elements) {
        if (auto value = std::dynamic_pointer_cast<FeatureValue>(element)) return value->value();
    }
    ADD_FAILURE() << "no feature value for '" << expression << "'";
    return nullptr;
}

std::shared_ptr<OperatorExpression> operatorOf(const std::shared_ptr<Expression>& expression, const std::string& name,
                                               size_t arguments) {
    const auto op = std::dynamic_pointer_cast<OperatorExpression>(expression);
    if (!op) {
        ADD_FAILURE() << "expected an OperatorExpression '" << name << "'";
        return nullptr;
    }
    EXPECT_EQ(op->operatorName(), name);
    EXPECT_EQ(op->argument().size(), arguments);
    return op->argument().size() == arguments ? op : nullptr;
}

void expectReference(const std::shared_ptr<Expression>& expression, const std::string& name) {
    const auto reference = std::dynamic_pointer_cast<FeatureReferenceExpression>(expression);
    ASSERT_NE(reference, nullptr);
    ASSERT_NE(reference->referent(), nullptr);
    EXPECT_EQ(reference->referent()->declaredName().value_or(""), name);
}

void expectInteger(const std::shared_ptr<Expression>& expression, long long value) {
    const auto literal = std::dynamic_pointer_cast<LiteralInteger>(expression);
    ASSERT_NE(literal, nullptr);
    EXPECT_EQ(literal->value(), value);
}

void expectTypeReference(const std::shared_ptr<Expression>& expression, const std::string& name) {
    const auto reference = std::dynamic_pointer_cast<InstantiationExpression>(expression);
    ASSERT_NE(reference, nullptr);
    ASSERT_NE(reference->instantiatedType(), nullptr);
    EXPECT_EQ(reference->instantiatedType()->declaredName().value_or(""), name);
}
}

TEST(TestKerMLExpressions, MultiplicationBindsTighterThanAddition) {
    const auto sum = operatorOf(kermlValue("2 * 3 + 1"), "+", 2);
    ASSERT_NE(sum, nullptr);
    const auto product = operatorOf(sum->argument()[0], "*", 2);
    ASSERT_NE(product, nullptr);
    expectInteger(product->argument()[0], 2);
    expectInteger(product->argument()[1], 3);
    expectInteger(sum->argument()[1], 1);
}

TEST(TestKerMLExpressions, BinaryOperatorsGroupToTheLeft) {
    const auto outer = operatorOf(kermlValue("1 - 2 - 3"), "-", 2);
    ASSERT_NE(outer, nullptr);
    const auto inner = operatorOf(outer->argument()[0], "-", 2);
    ASSERT_NE(inner, nullptr);
    expectInteger(inner->argument()[0], 1);
    expectInteger(inner->argument()[1], 2);
    expectInteger(outer->argument()[1], 3);
}

TEST(TestKerMLExpressions, ExponentiationGroupsToTheRightAndBindsTighterThanMultiplication) {
    const auto power = operatorOf(kermlValue("a ^ b ^ c"), "^", 2);
    ASSERT_NE(power, nullptr);
    expectReference(power->argument()[0], "a");
    const auto inner = operatorOf(power->argument()[1], "^", 2);
    ASSERT_NE(inner, nullptr);
    expectReference(inner->argument()[0], "b");
    expectReference(inner->argument()[1], "c");

    const auto product = operatorOf(kermlValue("2 * 3 ** 2"), "*", 2);
    ASSERT_NE(product, nullptr);
    expectInteger(product->argument()[0], 2);
    ASSERT_NE(operatorOf(product->argument()[1], "**", 2), nullptr);
}

TEST(TestKerMLExpressions, UnaryOperatorsBindTighterThanExponentiation) {
    const auto power = operatorOf(kermlValue("-x ** 2"), "**", 2);
    ASSERT_NE(power, nullptr);
    const auto negation = operatorOf(power->argument()[0], "-", 1);
    ASSERT_NE(negation, nullptr);
    expectReference(negation->argument()[0], "x");
    expectInteger(power->argument()[1], 2);

    const auto sum = operatorOf(kermlValue("-w + x * y"), "+", 2);
    ASSERT_NE(sum, nullptr);
    ASSERT_NE(operatorOf(sum->argument()[0], "-", 1), nullptr);
    ASSERT_NE(operatorOf(sum->argument()[1], "*", 2), nullptr);
}

TEST(TestKerMLExpressions, LogicalOperatorPrecedence) {
    const auto disjunction = operatorOf(kermlValue("a or b and c"), "or", 2);
    ASSERT_NE(disjunction, nullptr);
    expectReference(disjunction->argument()[0], "a");
    const auto conjunction = operatorOf(disjunction->argument()[1], "and", 2);
    ASSERT_NE(conjunction, nullptr);
    expectReference(conjunction->argument()[0], "b");
    expectReference(conjunction->argument()[1], "c");

    // '|' and '&' share the level of 'or' and 'and'; 'xor' lies between them.
    const auto bitwise = operatorOf(kermlValue("a | b xor c & d"), "|", 2);
    ASSERT_NE(bitwise, nullptr);
    const auto exclusive = operatorOf(bitwise->argument()[1], "xor", 2);
    ASSERT_NE(exclusive, nullptr);
    ASSERT_NE(operatorOf(exclusive->argument()[1], "&", 2), nullptr);

    // implies binds tighter than ??, equality tighter than and, relational tighter than equality.
    const auto coalescing = operatorOf(kermlValue("a ?? b implies c"), "??", 2);
    ASSERT_NE(coalescing, nullptr);
    ASSERT_NE(operatorOf(coalescing->argument()[1], "implies", 2), nullptr);
    const auto both = operatorOf(kermlValue("a < b == c > d and e"), "and", 2);
    ASSERT_NE(both, nullptr);
    const auto equality = operatorOf(both->argument()[0], "==", 2);
    ASSERT_NE(equality, nullptr);
    ASSERT_NE(operatorOf(equality->argument()[0], "<", 2), nullptr);
    ASSERT_NE(operatorOf(equality->argument()[1], ">", 2), nullptr);
    ASSERT_NE(operatorOf(kermlValue("not a and b"), "and", 2), nullptr);
}

TEST(TestKerMLExpressions, RangeSitsBetweenAdditionAndRelational) {
    const auto relation = operatorOf(kermlValue("1 .. 2 + 3 < 9"), "<", 2);
    ASSERT_NE(relation, nullptr);
    const auto range = operatorOf(relation->argument()[0], "..", 2);
    ASSERT_NE(range, nullptr);
    expectInteger(range->argument()[0], 1);
    ASSERT_NE(operatorOf(range->argument()[1], "+", 2), nullptr);
}

TEST(TestKerMLExpressions, ClassificationAndCastOperators) {
    const auto cast = operatorOf(kermlValue("x as T"), "as", 2);
    ASSERT_NE(cast, nullptr);
    expectReference(cast->argument()[0], "x");
    expectTypeReference(cast->argument()[1], "T");

    const auto equality = operatorOf(kermlValue("x istype T == true"), "==", 2);
    ASSERT_NE(equality, nullptr);
    ASSERT_NE(operatorOf(equality->argument()[0], "istype", 2), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<LiteralBoolean>(equality->argument()[1]), nullptr);

    // Relational operators bind tighter than classification.
    const auto test = operatorOf(kermlValue("a + 1 hastype T"), "hastype", 2);
    ASSERT_NE(test, nullptr);
    ASSERT_NE(operatorOf(test->argument()[0], "+", 2), nullptr);

    EXPECT_NE(operatorOf(kermlValue("x @ T"), "@", 2), nullptr);
    // The operators may be used without a first operand.
    const auto prefix = operatorOf(kermlValue("istype T"), "istype", 1);
    ASSERT_NE(prefix, nullptr);
    expectTypeReference(prefix->argument()[0], "T");
    EXPECT_NE(operatorOf(kermlValue("@T"), "@", 1), nullptr);
}

TEST(TestKerMLExpressions, MetaclassificationOperators) {
    const auto test = operatorOf(kermlValue("x @@ M"), "@@", 2);
    ASSERT_NE(test, nullptr);
    expectReference(test->argument()[0], "x");
    expectTypeReference(test->argument()[1], "M");
    const auto cast = operatorOf(kermlValue("x meta KerML::Feature"), "meta", 2);
    ASSERT_NE(cast, nullptr);
    expectTypeReference(cast->argument()[1], "Feature");
}

TEST(TestKerMLExpressions, ParenthesisedCastFeedsFeatureChain) {
    const auto chain = std::dynamic_pointer_cast<FeatureChainExpression>(kermlValue("(x as T).y"));
    ASSERT_NE(chain, nullptr);
    ASSERT_NE(chain->targetFeature(), nullptr);
    EXPECT_EQ(chain->targetFeature()->declaredName().value_or(""), "y");
    ASSERT_EQ(chain->argument().size(), 1u);
    ASSERT_NE(operatorOf(chain->argument()[0], "as", 2), nullptr);
}

TEST(TestKerMLExpressions, FeatureChainsAreLeftNested) {
    const auto outer = std::dynamic_pointer_cast<FeatureChainExpression>(kermlValue("a.b.c"));
    ASSERT_NE(outer, nullptr);
    EXPECT_EQ(outer->targetFeature()->declaredName().value_or(""), "c");
    ASSERT_EQ(outer->argument().size(), 1u);
    const auto inner = std::dynamic_pointer_cast<FeatureChainExpression>(outer->argument()[0]);
    ASSERT_NE(inner, nullptr);
    EXPECT_EQ(inner->targetFeature()->declaredName().value_or(""), "b");
    ASSERT_EQ(inner->argument().size(), 1u);
    expectReference(inner->argument()[0], "a");
}

TEST(TestKerMLExpressions, IndexExpression) {
    const auto index = std::dynamic_pointer_cast<IndexExpression>(kermlValue("a#(1)"));
    ASSERT_NE(index, nullptr);
    EXPECT_EQ(index->operatorName(), "#");
    ASSERT_EQ(index->argument().size(), 2u);
    expectReference(index->argument()[0], "a");
    expectInteger(index->argument()[1], 1);

    // Index and feature chain are postfix operators of the same precedence and group to the left.
    const auto chain = std::dynamic_pointer_cast<FeatureChainExpression>(kermlValue("m#(1).c"));
    ASSERT_NE(chain, nullptr);
    ASSERT_EQ(chain->argument().size(), 1u);
    EXPECT_NE(std::dynamic_pointer_cast<IndexExpression>(chain->argument()[0]), nullptr);
}

TEST(TestKerMLExpressions, BracketExpressionForQuantityUnits) {
    const auto bracket = operatorOf(kermlValue("273.15 [K]"), "[", 2);
    ASSERT_NE(bracket, nullptr);
    const auto value = std::dynamic_pointer_cast<LiteralRational>(bracket->argument()[0]);
    ASSERT_NE(value, nullptr);
    EXPECT_DOUBLE_EQ(value->value(), 273.15);
    expectReference(bracket->argument()[1], "K");

    // The bracket binds tighter than the arithmetic operators around it.
    const auto sum = operatorOf(kermlValue("1 + 2 [m] * 3"), "+", 2);
    ASSERT_NE(sum, nullptr);
    const auto product = operatorOf(sum->argument()[1], "*", 2);
    ASSERT_NE(product, nullptr);
    ASSERT_NE(operatorOf(product->argument()[0], "[", 2), nullptr);
}

TEST(TestKerMLExpressions, ConditionalExpression) {
    const auto conditional = operatorOf(kermlValue("if a ? 1 else 2"), "if", 3);
    ASSERT_NE(conditional, nullptr);
    expectReference(conditional->argument()[0], "a");
    expectInteger(conditional->argument()[1], 1);
    expectInteger(conditional->argument()[2], 2);

    // The conditional has the lowest precedence: its else branch extends over the rest of the expression.
    const auto nested = operatorOf(kermlValue("if a ? 1 else if b ? 2 else 3 + 4"), "if", 3);
    ASSERT_NE(nested, nullptr);
    const auto inner = operatorOf(nested->argument()[2], "if", 3);
    ASSERT_NE(inner, nullptr);
    ASSERT_NE(operatorOf(inner->argument()[2], "+", 2), nullptr);
}

TEST(TestKerMLExpressions, SequenceExpressions) {
    const auto sequence = operatorOf(kermlValue("(1, 2, 3)"), ",", 2);
    ASSERT_NE(sequence, nullptr);
    expectInteger(sequence->argument()[0], 1);
    const auto rest = operatorOf(sequence->argument()[1], ",", 2);
    ASSERT_NE(rest, nullptr);
    expectInteger(rest->argument()[0], 2);
    expectInteger(rest->argument()[1], 3);

    // A parenthesised expression is just the expression, a trailing comma is allowed, () is null.
    ASSERT_NE(operatorOf(kermlValue("(1 + 2) * 3"), "*", 2), nullptr);
    expectInteger(kermlValue("(1,)"), 1);
    EXPECT_NE(std::dynamic_pointer_cast<NullExpression>(kermlValue("()")), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<NullExpression>(kermlValue("null")), nullptr);
}

TEST(TestKerMLExpressions, InvocationSelectCollectAndBodyExpressions) {
    const auto arrow = std::dynamic_pointer_cast<OperatorExpression>(kermlValue("s->select {in x; x > 0}"));
    ASSERT_NE(arrow, nullptr);
    EXPECT_EQ(arrow->operatorName(), "->");
    ASSERT_NE(arrow->instantiatedType(), nullptr);
    EXPECT_EQ(arrow->instantiatedType()->declaredName().value_or(""), "select");
    ASSERT_EQ(arrow->argument().size(), 2u);
    expectReference(arrow->argument()[0], "s");
    EXPECT_NE(arrow->argument()[1], nullptr);

    const auto reduce = std::dynamic_pointer_cast<OperatorExpression>(kermlValue("s->reduce '+'"));
    ASSERT_NE(reduce, nullptr);
    ASSERT_EQ(reduce->argument().size(), 2u);
    expectTypeReference(reduce->argument()[1], "'+'");

    const auto sized = std::dynamic_pointer_cast<OperatorExpression>(kermlValue("s->size()"));
    ASSERT_NE(sized, nullptr);
    EXPECT_EQ(sized->argument().size(), 1u);

    const auto select = std::dynamic_pointer_cast<SelectExpression>(kermlValue("s.?{ x > 0 }"));
    ASSERT_NE(select, nullptr);
    ASSERT_EQ(select->argument().size(), 2u);
    expectReference(select->argument()[0], "s");
    const auto collect = std::dynamic_pointer_cast<CollectExpression>(kermlValue("s.{ x }"));
    ASSERT_NE(collect, nullptr);
    ASSERT_EQ(collect->argument().size(), 2u);
}

TEST(TestKerMLExpressions, InvocationsWithPositionalAndNamedArguments) {
    const auto call = std::dynamic_pointer_cast<InvocationExpression>(kermlValue("f(a, b + 1)"));
    ASSERT_NE(call, nullptr);
    ASSERT_NE(call->instantiatedType(), nullptr);
    EXPECT_EQ(call->instantiatedType()->declaredName().value_or(""), "f");
    ASSERT_EQ(call->argument().size(), 2u);
    expectReference(call->argument()[0], "a");
    ASSERT_NE(operatorOf(call->argument()[1], "+", 2), nullptr);

    const auto named = std::dynamic_pointer_cast<InvocationExpression>(kermlValue("f(x = 1, y = a == b)"));
    ASSERT_NE(named, nullptr);
    ASSERT_EQ(named->argument().size(), 2u);
    ASSERT_EQ(named->argument()[1]->ownedRedefinition().size(), 1u);
    EXPECT_EQ(named->argument()[1]->ownedRedefinition()[0]->redefinedFeature()->declaredName().value_or(""), "y");

    const auto constructed = std::dynamic_pointer_cast<ConstructorExpression>(kermlValue("new T(1, 2)"));
    ASSERT_NE(constructed, nullptr);
    ASSERT_NE(constructed->instantiatedType(), nullptr);
    EXPECT_EQ(constructed->instantiatedType()->declaredName().value_or(""), "T");
    EXPECT_EQ(constructed->argument().size(), 2u);
}

TEST(TestKerMLExpressions, ExtentMetadataAccessAndLiterals) {
    const auto extent = operatorOf(kermlValue("all T"), "all", 1);
    ASSERT_NE(extent, nullptr);
    expectTypeReference(extent->argument()[0], "T");
    EXPECT_NE(std::dynamic_pointer_cast<MetadataAccessExpression>(kermlValue("x.metadata")), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<LiteralInfinity>(kermlValue("*")), nullptr);
    const auto text = std::dynamic_pointer_cast<LiteralString>(kermlValue("\"hi\""));
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->value(), "hi");
    const auto exponent = std::dynamic_pointer_cast<LiteralRational>(kermlValue("1.5e3"));
    ASSERT_NE(exponent, nullptr);
    EXPECT_DOUBLE_EQ(exponent->value(), 1500.0);
    const auto plain = std::dynamic_pointer_cast<LiteralRational>(kermlValue("2e2"));
    ASSERT_NE(plain, nullptr);
    EXPECT_DOUBLE_EQ(plain->value(), 200.0);
}

TEST(TestKerMLExpressions, JuxtapositionIsNoLongerASequence) {
    // "2 3" used to parse as a two-element sequence; only a comma builds a sequence.
    const auto result = SysMLv2::Files::Parser::parseKerML("feature x = 2 3;");
    EXPECT_FALSE(result.second.empty());
    EXPECT_FALSE(SysMLv2::Files::Parser::parseKerML("feature x = 1 + ;").second.empty());
    EXPECT_FALSE(SysMLv2::Files::Parser::parseKerML("feature x = if a ? 1;").second.empty());
}

// ---- Phase 2 gate: constructs of the standard library that the grammar used to reject ----
namespace {
template<class T>
std::shared_ptr<T> namedElement(const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements, const std::string& name) {
    for (const auto& element : elements) {
        if (element && element->declaredName() == name) {
            if (auto typed = std::dynamic_pointer_cast<T>(element)) return typed;
        }
    }
    return nullptr;
}

template<class T>
bool ownsElement(const std::shared_ptr<KerML::Entities::Element>& parent, const std::shared_ptr<T>& child) {
    if (!parent || !child) return false;
    const auto owned = parent->ownedElements();
    return std::find(owned.begin(), owned.end(), std::static_pointer_cast<KerML::Entities::Element>(child)) != owned.end();
}
}

TEST(TestKerMLListener, EndFeatureOwnsItsCrossFeature) {
    using namespace KerML::Entities;
    // KerML 8.2.4.3.1: EndFeaturePrefix ( OwnedCrossFeatureMember )? - the cross feature is a Feature of its own,
    // declared between 'end' and 'feature', and owned by the end feature.
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "assoc A { end p [*] feature b : T; }");
    ASSERT_TRUE(errors.empty());
    const auto end = namedElement<Feature>(elements, "b");
    const auto cross = namedElement<Feature>(elements, "p");
    ASSERT_NE(end, nullptr);
    ASSERT_NE(cross, nullptr);
    EXPECT_TRUE(end->isEnd());
    EXPECT_FALSE(cross->isEnd());
    EXPECT_EQ(cross->owner(), end);
    EXPECT_TRUE(ownsElement(end, cross));
    ASSERT_TRUE(end->crossFeature().has_value());
    EXPECT_EQ(end->crossFeature().value(), cross);
    // The bounds belong to the cross feature, not to the end feature.
    EXPECT_TRUE(cross->multiplicity().has_value());
    EXPECT_FALSE(end->multiplicity().has_value());
    // ... and the cross feature is not one of the featured members of the end feature.
    EXPECT_TRUE(end->ownedFeature().empty());
}

TEST(TestKerMLListener, AnonymousCrossFeatureCarriesTheBounds) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "assoc A { end [1] feature a references x; end feature c; }");
    ASSERT_TRUE(errors.empty());
    const auto end = namedElement<Feature>(elements, "a");
    ASSERT_NE(end, nullptr);
    EXPECT_TRUE(end->isEnd());
    ASSERT_TRUE(end->crossFeature().has_value());
    const auto cross = end->crossFeature().value();
    ASSERT_NE(cross, nullptr);
    EXPECT_FALSE(cross->declaredName().has_value());
    EXPECT_EQ(cross->owner(), end);
    EXPECT_TRUE(cross->multiplicity().has_value());
    EXPECT_FALSE(end->multiplicity().has_value());
    // An end feature without cross feature member has none.
    const auto plain = namedElement<Feature>(elements, "c");
    ASSERT_NE(plain, nullptr);
    EXPECT_TRUE(plain->isEnd());
    EXPECT_FALSE(plain->crossFeature().has_value());
}

TEST(TestKerMLListener, CrossesClauseCreatesCrossSubsetting) {
    using namespace KerML::Entities;
    // KerML 8.2.4.3.1: Crosses = CROSSES OwnedCrossSubsetting (both 'crosses' and '=>'; feature chains are allowed)
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "assoc A { end feature f : T crosses a.b; end feature g : T => h; }");
    ASSERT_TRUE(errors.empty());
    const auto crossings = listenerElements<CrossSubsetting>(elements);
    ASSERT_EQ(crossings.size(), 2u);
    const auto f = namedElement<Feature>(elements, "f");
    const auto g = namedElement<Feature>(elements, "g");
    ASSERT_NE(f, nullptr);
    ASSERT_NE(g, nullptr);
    ASSERT_TRUE(f->ownedCrossSubsetting().has_value());
    EXPECT_EQ(f->ownedCrossSubsetting().value()->crossedFeature()->declaredName().value_or(""), "a.b");
    EXPECT_EQ(f->ownedCrossSubsetting().value()->crossingFeature(), f);
    ASSERT_TRUE(g->ownedCrossSubsetting().has_value());
    EXPECT_EQ(g->ownedCrossSubsetting().value()->crossedFeature()->declaredName().value_or(""), "h");
    EXPECT_TRUE(ownsElement(f, f->ownedCrossSubsetting().value()));
}

TEST(TestKerMLListener, InvariantWithoutDeclarationBelongsToItsBehavior) {
    using namespace KerML::Entities;
    // KerML 7.4.9.4 / 8.2.5.7.4: 'inv { ... }' and 'inv false { ... }' need no name or feature declaration.
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "behavior B { inv { true } private inv { false } inv false { true } inv true named { true } }");
    ASSERT_TRUE(errors.empty());
    const auto behavior = namedElement<Behavior>(elements, "B");
    ASSERT_NE(behavior, nullptr);
    const auto invariants = listenerElements<Invariant>(elements);
    ASSERT_EQ(invariants.size(), 4u);
    size_t negated = 0;
    for (const auto& invariant : invariants) {
        EXPECT_TRUE(ownsElement(behavior, invariant));
        const auto features = behavior->ownedFeature();
        EXPECT_NE(std::find(features.begin(), features.end(), std::static_pointer_cast<Feature>(invariant)), features.end());
        if (invariant->isNegated()) ++negated;
    }
    EXPECT_EQ(negated, 1u);
    EXPECT_EQ(invariants[3]->declaredName().value_or(""), "named");
    EXPECT_FALSE(invariants[0]->declaredName().has_value());
}

TEST(TestKerMLListener, FeaturePrefixModifiersInSpecOrder) {
    using namespace KerML::Entities;
    // BasicFeaturePrefix = direction? derived? abstract? ( composite | portion )? var?
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "class C { derived composite var feature f : T; abstract portion feature p; in feature i; end feature e; }");
    ASSERT_TRUE(errors.empty());
    const auto f = namedElement<Feature>(elements, "f");
    ASSERT_NE(f, nullptr);
    EXPECT_TRUE(f->isDerived());
    EXPECT_TRUE(f->isComposite());
    EXPECT_TRUE(f->isVariable());
    EXPECT_FALSE(f->isPortion());
    EXPECT_FALSE(f->isEnd());
    const auto p = namedElement<Feature>(elements, "p");
    ASSERT_NE(p, nullptr);
    EXPECT_TRUE(p->isAbstract());
    EXPECT_TRUE(p->isPortion());
    EXPECT_FALSE(p->isComposite());
    const auto i = namedElement<Feature>(elements, "i");
    ASSERT_NE(i, nullptr);
    ASSERT_TRUE(i->direction().has_value());
    EXPECT_EQ(i->direction().value(), FeatureDirectionKind::IN);
    const auto e = namedElement<Feature>(elements, "e");
    ASSERT_NE(e, nullptr);
    EXPECT_TRUE(e->isEnd());
    EXPECT_FALSE(e->isDerived());
}

TEST(TestKerMLListener, BindingConnectorUsesSingleEqualsSign) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "class C { feature a; feature b; binding x of a = b; binding [0..1] a = [1] b; }");
    ASSERT_TRUE(errors.empty());
    const auto bindings = listenerElements<BindingConnector>(elements);
    ASSERT_EQ(bindings.size(), 2u);
    EXPECT_EQ(bindings[0]->declaredName().value_or(""), "x");
    EXPECT_FALSE(bindings[1]->declaredName().has_value());
    for (const auto& binding : bindings) {
        EXPECT_EQ(binding->connectorEnd().size(), 2u);
    }
    const auto cls = namedElement<Class>(elements, "C");
    ASSERT_NE(cls, nullptr);
    EXPECT_TRUE(ownsElement(cls, bindings[0]));
    EXPECT_TRUE(ownsElement(cls, bindings[1]));
    EXPECT_FALSE(SysMLv2::Files::Parser::parseKerML("class C { feature a; feature b; binding a == b; }").second.empty());
}

TEST(TestKerMLListener, ConnectorsWithoutFromAndWithoutEnds) {
    using namespace KerML::Entities;
    // Connector = FeaturePrefix 'connector' ( FeatureDeclaration? ValuePart? | ConnectorDeclaration ) TypeBody
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "class C { feature a; feature b; connector [0..1] a to [1..*] b; connector k : T { } "
        "abstract connector m : T from a to b; }");
    ASSERT_TRUE(errors.empty());
    const auto connectors = listenerElements<Connector>(elements);
    ASSERT_EQ(connectors.size(), 3u);
    EXPECT_EQ(connectors[0]->connectorEnd().size(), 2u);
    EXPECT_EQ(connectors[1]->declaredName().value_or(""), "k");
    EXPECT_TRUE(connectors[1]->connectorEnd().empty());
    EXPECT_EQ(connectors[2]->declaredName().value_or(""), "m");
    EXPECT_TRUE(connectors[2]->isAbstract());
    EXPECT_EQ(connectors[2]->connectorEnd().size(), 2u);
    // the end multiplicities stay on the ends, not on the connector
    EXPECT_FALSE(connectors[0]->multiplicity().has_value());
    for (const auto& end : connectors[0]->connectorEnd()) {
        EXPECT_TRUE(end->isEnd());
        EXPECT_TRUE(end->multiplicity().has_value());
    }
}

TEST(TestKerMLListener, MemberFeatureInTypeBody) {
    using namespace KerML::Entities;
    // TypeFeatureMember = MemberPrefix 'member' FeatureElement is part of the TypeBodyElement alternatives
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "datatype D { member feature 'private' : D[1]; private member feature 'protected' : D[1]; }");
    ASSERT_TRUE(errors.empty());
    const auto datatype = namedElement<DataType>(elements, "D");
    ASSERT_NE(datatype, nullptr);
    const auto priv = namedElement<Feature>(elements, "'private'");
    const auto prot = namedElement<Feature>(elements, "'protected'");
    ASSERT_NE(priv, nullptr);
    ASSERT_NE(prot, nullptr);
    EXPECT_TRUE(ownsElement(datatype, priv));
    EXPECT_TRUE(ownsElement(datatype, prot));
    EXPECT_EQ(priv->owner(), datatype);
}

TEST(TestKerMLListener, RedefinitionAndSubsettingListsKeepEveryTarget) {
    using namespace KerML::Entities;
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "class C { feature a redefines x, y::z, w; feature b subsets p, q, r; }");
    ASSERT_TRUE(errors.empty());
    const auto a = namedElement<Feature>(elements, "a");
    const auto b = namedElement<Feature>(elements, "b");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_EQ(a->ownedRedefinition().size(), 3u);
    EXPECT_EQ(a->ownedRedefinition()[2]->redefinedFeature()->declaredName().value_or(""), "w");
    EXPECT_EQ(b->ownedSubsetting().size(), 3u);
}

TEST(TestKerMLListener, CommentAboutWithoutName) {
    using namespace KerML::Entities;
    // Comment = ( 'comment' Identification ( 'about' Annotation ( ',' Annotation )* )? )? ...: the Identification may be empty
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "class A; class B; comment about A, B /* about two */ comment named about A /* about one */");
    ASSERT_TRUE(errors.empty());
    const auto comments = listenerElements<Comment>(elements);
    ASSERT_EQ(comments.size(), 2u);
    EXPECT_FALSE(comments[0]->declaredName().has_value());
    EXPECT_EQ(comments[0]->annotatedElement().size(), 2u);
    EXPECT_EQ(comments[1]->declaredName().value_or(""), "named");
}

TEST(TestKerMLListener, MultiplicityModifiersWithoutBounds) {
    using namespace KerML::Entities;
    // MultiplicityPart = OwnedMultiplicity | ( OwnedMultiplicity )? ( 'ordered' ( 'nonunique' )? | 'nonunique' ( 'ordered' )? )
    const auto [elements, errors] = SysMLv2::Files::Parser::parseKerML(
        "class C { feature a : T ordered; feature b : T nonunique; feature c : T nonunique ordered; feature d : T[2]; }");
    ASSERT_TRUE(errors.empty());
    const auto a = namedElement<Feature>(elements, "a");
    const auto b = namedElement<Feature>(elements, "b");
    const auto c = namedElement<Feature>(elements, "c");
    const auto d = namedElement<Feature>(elements, "d");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);
    ASSERT_NE(d, nullptr);
    EXPECT_TRUE(a->isOrdered());
    EXPECT_TRUE(a->isUnique());
    EXPECT_FALSE(b->isOrdered());
    EXPECT_FALSE(b->isUnique());
    EXPECT_TRUE(c->isOrdered());
    EXPECT_FALSE(c->isUnique());
    EXPECT_FALSE(d->isOrdered());
    EXPECT_TRUE(d->isUnique());
    EXPECT_FALSE(a->multiplicity().has_value());
    EXPECT_TRUE(d->multiplicity().has_value());
    EXPECT_FALSE(SysMLv2::Files::Parser::parseKerML("feature f : T ordered ordered;").second.empty());
}
