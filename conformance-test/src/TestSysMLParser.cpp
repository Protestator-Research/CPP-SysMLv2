#include <gtest/gtest.h>
#include <sysmlv2/Parser.h>
#include <sysml/SysML.h>
#include <kerml/KerML.h>
#include <sysmlv2/parser/SysMLv2Lexer.h>
#include <sysmlv2/parser/SysMLv2Parser.h>
#include <sysmlv2/parser/SysMLv2ListenerImplementation.h>

namespace {
template<class T>
std::shared_ptr<T> named(const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements, const std::string& name) {
    for (const auto& element : elements) {
        if (element->declaredName() == name) {
            if (auto result = std::dynamic_pointer_cast<T>(element)) return result;
        }
    }
    return nullptr;
}
}

TEST(TestSysMLParser, NestedDefinitionsUsagesAndForwardTyping) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package VehicleModel { part def Vehicle { part engine : Engine; attribute mass : Real = 12.5; } part def Engine; }");
    ASSERT_TRUE(errors.empty());
    const auto vehicle = named<SysMLv2::Entities::PartDefinition>(elements, "Vehicle");
    const auto engine = named<SysMLv2::Entities::PartUsage>(elements, "engine");
    const auto definition = named<SysMLv2::Entities::PartDefinition>(elements, "Engine");
    ASSERT_NE(vehicle, nullptr);
    ASSERT_NE(engine, nullptr);
    ASSERT_NE(definition, nullptr);
    EXPECT_EQ(engine->owningDefinition(), vehicle);
    ASSERT_EQ(engine->definition().size(), 1u);
    EXPECT_EQ(engine->definition()[0], definition);
    ASSERT_EQ(vehicle->ownedPart().size(), 1u);
    EXPECT_EQ(vehicle->ownedPart()[0], engine);
    const auto mass = named<SysMLv2::Entities::AttributeUsage>(elements, "mass");
    ASSERT_NE(mass, nullptr);
    std::shared_ptr<KerML::Entities::FeatureValue> value;
    for (const auto& child : mass->ownedElements()) {
        if (auto candidate = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(child)) value = candidate;
    }
    ASSERT_NE(value, nullptr);
    const auto literal = std::dynamic_pointer_cast<KerML::Entities::LiteralRational>(value->value());
    ASSERT_NE(literal, nullptr);
    EXPECT_DOUBLE_EQ(literal->value(), 12.5);
}

TEST(TestSysMLParser, DefinitionFamilies) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "attribute def Length; item def Cargo; port def P; connection def C; interface def I; "
        "action def A; calc def Calculation; requirement def R; concern def Concern; "
        "case def Case; analysis def Analysis; verification def Verification; "
        "view def View; viewpoint def Viewpoint; rendering def Rendering; metadata def Metadata;");
    ASSERT_TRUE(errors.empty());
    EXPECT_NE(named<SysMLv2::Entities::AttributeDefinition>(elements, "Length"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::ItemDefinition>(elements, "Cargo"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::PortDefinition>(elements, "P"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::ConnectionDefinition>(elements, "C"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::InterfaceDefinition>(elements, "I"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::ActionDefinition>(elements, "A"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::CalculationDefinition>(elements, "Calculation"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::RequirementDefinition>(elements, "R"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::ConcernDefinition>(elements, "Concern"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::CaseDefinition>(elements, "Case"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::AnalysisCaseDefinition>(elements, "Analysis"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::VerificationCaseDefinition>(elements, "Verification"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::ViewDefinition>(elements, "View"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::ViewpointDefinition>(elements, "Viewpoint"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::RenderingDefinition>(elements, "Rendering"), nullptr);
    EXPECT_NE(named<SysMLv2::Entities::MetadataDefinition>(elements, "Metadata"), nullptr);
}

TEST(TestSysMLParser, SpecializationMultiplicityAndPrefixes) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "abstract part def Base; part def Derived specializes Base { in attribute values : Integer[0..*] nonunique; }");
    ASSERT_TRUE(errors.empty());
    const auto base = named<SysMLv2::Entities::PartDefinition>(elements, "Base");
    const auto derived = named<SysMLv2::Entities::PartDefinition>(elements, "Derived");
    ASSERT_NE(base, nullptr);
    ASSERT_NE(derived, nullptr);
    EXPECT_TRUE(base->isAbstract());
    ASSERT_EQ(derived->ownedSubclassification().size(), 1u);
    EXPECT_EQ(derived->ownedSubclassification()[0]->general(), base);
    const auto values = named<SysMLv2::Entities::AttributeUsage>(elements, "values");
    ASSERT_NE(values, nullptr);
    EXPECT_EQ(values->direction(), KerML::Entities::IN);
    EXPECT_FALSE(values->isOrdered());
    EXPECT_FALSE(values->isUnique());
    ASSERT_TRUE(values->multiplicity().has_value());
    ASSERT_NE(*values->multiplicity(), nullptr);
    EXPECT_EQ((*values->multiplicity())->minimum(), 0u);
    EXPECT_TRUE((*values->multiplicity())->isUnlimited());
}

TEST(TestSysMLParser, SyntaxErrorsHaveNoNullEntries) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2("part def ;");
    ASSERT_FALSE(errors.empty());
    for (const auto& error : errors) EXPECT_NE(error, nullptr);
}

TEST(TestSysMLParser, ListenerCanWalkAndBeReused) {
    SysMLv2ListenerImplementation listener;
    for (const auto name : {"FirstModel", "SecondModel"}) {
        antlr4::ANTLRInputStream input(std::string("part def ") + name + ";");
        SysMLv2Lexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        SysMLv2Parser parser(&tokens);
        auto tree = parser.start();
        ASSERT_EQ(parser.getNumberOfSyntaxErrors(), 0u);
        antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
        const auto elements = listener.getElements();
        EXPECT_NE(named<SysMLv2::Entities::PartDefinition>(elements, name), nullptr);
        size_t count = 0;
        for (const auto& element : elements) if (std::dynamic_pointer_cast<SysMLv2::Entities::PartDefinition>(element)) ++count;
        EXPECT_EQ(count, 1u);
    }
}

TEST(TestSysMLParser, ImportsAliasesAndQualifiedNames) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package Types { part def Engine; } package Other { part def Engine; } "
        "package Model { private import Types::*; alias Motor for Types::Engine; part a : Engine; part b : Motor; part c : Other::Engine; }");
    ASSERT_TRUE(errors.empty());
    const auto a = named<SysMLv2::Entities::PartUsage>(elements, "a");
    const auto b = named<SysMLv2::Entities::PartUsage>(elements, "b");
    const auto c = named<SysMLv2::Entities::PartUsage>(elements, "c");
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    ASSERT_NE(c, nullptr);
    ASSERT_EQ(a->definition().size(), 1u);
    ASSERT_EQ(b->definition().size(), 1u);
    ASSERT_EQ(c->definition().size(), 1u);
    EXPECT_EQ(a->definition()[0], b->definition()[0]);
    EXPECT_NE(a->definition()[0], c->definition()[0]);
    EXPECT_EQ(a->definition()[0]->owner()->declaredName().value_or(""), "Types");
    EXPECT_EQ(c->definition()[0]->owner()->declaredName().value_or(""), "Other");
}

TEST(TestSysMLParser, ConnectionEndsAndReferenceSubsetting) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "part def System { port a; port b; connection link connect a to b; }");
    ASSERT_TRUE(errors.empty());
    const auto connection = named<SysMLv2::Entities::ConnectionUsage>(elements, "link");
    ASSERT_NE(connection, nullptr);
    ASSERT_EQ(connection->connectorEnd().size(), 2u);
    for (const auto& end : connection->connectorEnd()) {
        ASSERT_TRUE(end->ownedReferenceSubsetting().has_value());
        const auto target = (*end->ownedReferenceSubsetting())->subsettedFeature();
        ASSERT_NE(target, nullptr);
        EXPECT_NE(std::dynamic_pointer_cast<SysMLv2::Entities::PortUsage>(target), nullptr);
    }
}

TEST(TestSysMLParser, EnumerationsVariantsAndRequirementSubjects) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "enum def Color { enum red; enum green; } variation part def Choice { variant part selected; } "
        "requirement def R { subject target; }");
    ASSERT_TRUE(errors.empty());
    const auto color = named<SysMLv2::Entities::EnumerationDefinition>(elements, "Color");
    ASSERT_NE(color, nullptr);
    EXPECT_NE(named<SysMLv2::Entities::EnumerationUsage>(elements, "red"), nullptr);
    const auto choice = named<SysMLv2::Entities::PartDefinition>(elements, "Choice");
    ASSERT_NE(choice, nullptr);
    EXPECT_TRUE(choice->isVariation());
    ASSERT_EQ(choice->variantMembership().size(), 1u);
    ASSERT_NE(choice->variantMembership()[0]->ownedVariantUsage(), nullptr);
    EXPECT_EQ(choice->variantMembership()[0]->ownedVariantUsage()->declaredName().value_or(""), "selected");
    bool hasSubject = false;
    for (const auto& element : elements) {
        if (auto subject = std::dynamic_pointer_cast<SysMLv2::Entities::SubjectMembership>(element)) {
            hasSubject = true;
            ASSERT_NE(subject->memberElement(), nullptr);
            EXPECT_EQ(subject->memberElement()->declaredName().value_or(""), "target");
        }
    }
    EXPECT_TRUE(hasSubject);
}

TEST(TestSysMLParser, ConditionalExpressionsKeepArgumentOrder) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "attribute chosen : Integer = if true ? 10 else 20;");
    ASSERT_TRUE(errors.empty());
    const auto chosen = named<SysMLv2::Entities::AttributeUsage>(elements, "chosen");
    ASSERT_NE(chosen, nullptr);
    std::shared_ptr<KerML::Entities::FeatureValue> value;
    for (const auto& child : chosen->ownedElements()) {
        if (auto candidate = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(child)) value = candidate;
    }
    ASSERT_NE(value, nullptr);
    const auto condition = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(value->value());
    ASSERT_NE(condition, nullptr);
    EXPECT_EQ(condition->operatorName(), "if");
    ASSERT_EQ(condition->argument().size(), 3u);
    auto first = std::dynamic_pointer_cast<KerML::Entities::LiteralInteger>(condition->argument()[1]);
    auto second = std::dynamic_pointer_cast<KerML::Entities::LiteralInteger>(condition->argument()[2]);
    ASSERT_NE(first, nullptr);
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(first->value(), 10);
    EXPECT_EQ(second->value(), 20);
}

TEST(TestSysMLParser, DependencyAndExplicitCommentTargets) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "part def Source; part def Target; dependency relation from Source to Target; "
        "comment note about Target /* explanation */");
    ASSERT_TRUE(errors.empty());
    auto source = named<SysMLv2::Entities::PartDefinition>(elements, "Source");
    auto target = named<SysMLv2::Entities::PartDefinition>(elements, "Target");
    auto dependency = named<KerML::Entities::Dependency>(elements, "relation");
    ASSERT_NE(dependency, nullptr);
    ASSERT_EQ(dependency->client().size(), 1u);
    ASSERT_EQ(dependency->supplier().size(), 1u);
    EXPECT_EQ(dependency->client()[0], source);
    EXPECT_EQ(dependency->supplier()[0], target);
    auto comment = named<KerML::Entities::Comment>(elements, "note");
    ASSERT_NE(comment, nullptr);
    ASSERT_EQ(comment->annotatedElements().size(), 1u);
    EXPECT_EQ(comment->annotatedElements()[0], target);
}

TEST(TestSysMLParser, FeatureSpecializationRedefinition) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { "
        "  part def Vehicle { attribute mass : Real; } "
        "  part def Car :> Vehicle { attribute carMass :>> mass; } "
        "}");
    ASSERT_TRUE(errors.empty());
    const auto carMass = named<SysMLv2::Entities::AttributeUsage>(elements, "carMass");
    ASSERT_NE(carMass, nullptr);
    ASSERT_EQ(carMass->ownedRedefinition().size(), 1u);
    const auto redef = carMass->ownedRedefinition()[0];
    ASSERT_NE(redef, nullptr);
    ASSERT_NE(redef->redefinedFeature(), nullptr);
    EXPECT_EQ(redef->redefinedFeature()->declaredName(), "mass");
    EXPECT_EQ(redef->redefiningFeature(), carMass);
}

TEST(TestSysMLParser, AnonymousRedefinitionUsage) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { "
        "  part def Vehicle { attribute mass : Real; } "
        "  part def Car :> Vehicle { :>> mass; } "
        "}");
    ASSERT_TRUE(errors.empty());
    std::shared_ptr<KerML::Entities::Feature> redefFeature;
    for (const auto& elem : elements) {
        if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(elem)) {
            if (feat->declaredName() == "mass" && !feat->ownedRedefinition().empty()) {
                redefFeature = feat;
                break;
            }
        }
    }
    ASSERT_NE(redefFeature, nullptr);
    ASSERT_EQ(redefFeature->ownedRedefinition().size(), 1u);
    const auto redef = redefFeature->ownedRedefinition()[0];
    ASSERT_NE(redef, nullptr);
    ASSERT_NE(redef->redefinedFeature(), nullptr);
    EXPECT_EQ(redef->redefinedFeature()->declaredName(), "mass");
    EXPECT_EQ(redef->redefiningFeature(), redefFeature);
}

