#include <gtest/gtest.h>
#include <sysmlv2/Parser.h>
#include <sysml/SysML.h>
#include <kerml/KerML.h>
#include <sysmlv2/parser/SysMLv2Lexer.h>
#include <sysmlv2/parser/SysMLv2Parser.h>
#include <sysmlv2/parser/SysMLv2ListenerImplementation.h>
#include <kerml/kernel/packages/Package.h>

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

TEST(TestSysMLParser, IndividualDefinitionUsageAndDirection) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { individual part def Car; individual part myCar : Car; in part p : Car; }");
    ASSERT_TRUE(errors.empty());
    const auto car = named<SysMLv2::Entities::PartDefinition>(elements, "Car");
    const auto myCar = named<SysMLv2::Entities::PartUsage>(elements, "myCar");
    const auto p = named<SysMLv2::Entities::PartUsage>(elements, "p");
    ASSERT_NE(car, nullptr);
    ASSERT_NE(myCar, nullptr);
    ASSERT_NE(p, nullptr);

    EXPECT_TRUE(car->isIndividual());

    EXPECT_TRUE(myCar->isIndividual());
    EXPECT_FALSE(myCar->direction().has_value());
    ASSERT_EQ(myCar->occurrenceDefinition().size(), 1u);
    EXPECT_EQ(myCar->occurrenceDefinition()[0], car);
    EXPECT_EQ(myCar->individualDefinition(), car);
    ASSERT_EQ(myCar->partDefinition().size(), 1u);
    EXPECT_EQ(myCar->partDefinition()[0], car);

    ASSERT_TRUE(p->direction().has_value());
    EXPECT_EQ(*p->direction(), KerML::Entities::IN);
}

TEST(TestSysMLParser, IndividualUsageDirectionAndOccurrenceDefinition) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { individual def Earth; in individual e : Earth; }");
    ASSERT_TRUE(errors.empty());
    const auto earth = named<SysMLv2::Entities::OccurrenceDefinition>(elements, "Earth");
    const auto e = named<SysMLv2::Entities::OccurrenceUsage>(elements, "e");
    ASSERT_NE(earth, nullptr);
    ASSERT_NE(e, nullptr);
    EXPECT_TRUE(earth->isIndividual());

    EXPECT_TRUE(e->isIndividual());
    ASSERT_TRUE(e->direction().has_value());
    EXPECT_EQ(*e->direction(), KerML::Entities::IN);
    EXPECT_EQ(e->individualDefinition(), earth);
    ASSERT_EQ(e->occurrenceDefinition().size(), 1u);
    EXPECT_EQ(e->occurrenceDefinition()[0], earth);
}

TEST(TestSysMLParser, PortionUsagesSetIsIndividualAndPortionKind) {
    // "individual snapshot s1 : Earth;" hits the individual_usage rule with an
    // optional portion_kind; "timeslice t1 : Earth;" hits portion_usage, whose
    // KEYWORD_INDIVIDUAL is optional and absent here.
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "individual def Earth; individual snapshot s1 : Earth; timeslice t1 : Earth;");
    ASSERT_TRUE(errors.empty());
    const auto s1 = named<SysMLv2::Entities::OccurrenceUsage>(elements, "s1");
    const auto t1 = named<SysMLv2::Entities::OccurrenceUsage>(elements, "t1");
    ASSERT_NE(s1, nullptr);
    ASSERT_NE(t1, nullptr);

    EXPECT_TRUE(s1->isIndividual());
    ASSERT_TRUE(s1->portionKind().has_value());
    EXPECT_EQ(*s1->portionKind(), SysMLv2::Entities::PortionKind::snapshot);

    EXPECT_FALSE(t1->isIndividual());
    // No direction keyword: direction must stay unset (Feature default is std::nullopt).
    EXPECT_FALSE(s1->direction().has_value());
    EXPECT_FALSE(t1->direction().has_value());
    ASSERT_TRUE(t1->portionKind().has_value());
    EXPECT_EQ(*t1->portionKind(), SysMLv2::Entities::PortionKind::timeslice);
}

TEST(TestSysMLParser, PartUsageWithOccurrencePrefixPortionKindAndDirection) {
    // "out snapshot part sp : Car;" is a part_usage, whose portion_kind and
    // direction both live in its occurrence_usage_prefix, not in a dedicated
    // portion/individual usage rule.
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "part def Car; out snapshot part sp : Car;");
    ASSERT_TRUE(errors.empty());
    const auto sp = named<SysMLv2::Entities::PartUsage>(elements, "sp");
    ASSERT_NE(sp, nullptr);
    ASSERT_TRUE(sp->portionKind().has_value());
    EXPECT_EQ(*sp->portionKind(), SysMLv2::Entities::PortionKind::snapshot);
    ASSERT_TRUE(sp->direction().has_value());
    EXPECT_EQ(*sp->direction(), KerML::Entities::OUT);
}

TEST(TestSysMLParser, DerivedDefinitionSnapshotsAcrossUsageKinds) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "item def Widget; item w : Widget; "
        "port def P; port pp : P; "
        "attribute def Weight; attribute wt : Weight; "
        "action def Move; action m : Move; "
        "state def S; state st : S; "
        "requirement def R; requirement r : R; "
        "enum def Color { enum red; } attribute c2 : Color; "
        "connection def Conn; connection cc : Conn; "
        "interface def IF; interface ii : IF; "
        "part def Car; part p : Car;");
    ASSERT_TRUE(errors.empty());

    const auto widget = named<SysMLv2::Entities::ItemDefinition>(elements, "Widget");
    const auto w = named<SysMLv2::Entities::ItemUsage>(elements, "w");
    ASSERT_NE(widget, nullptr);
    ASSERT_NE(w, nullptr);
    ASSERT_EQ(w->itemDefinition().size(), 1u);
    EXPECT_EQ(w->itemDefinition()[0], widget);
    ASSERT_EQ(w->occurrenceDefinition().size(), 1u);
    EXPECT_EQ(w->occurrenceDefinition()[0], widget);

    const auto portDef = named<SysMLv2::Entities::PortDefinition>(elements, "P");
    const auto pp = named<SysMLv2::Entities::PortUsage>(elements, "pp");
    ASSERT_NE(portDef, nullptr);
    ASSERT_NE(pp, nullptr);
    ASSERT_EQ(pp->portDefinition().size(), 1u);
    EXPECT_EQ(pp->portDefinition()[0], portDef);

    const auto weight = named<SysMLv2::Entities::AttributeDefinition>(elements, "Weight");
    const auto wt = named<SysMLv2::Entities::AttributeUsage>(elements, "wt");
    ASSERT_NE(weight, nullptr);
    ASSERT_NE(wt, nullptr);
    ASSERT_EQ(wt->attributeDefinition().size(), 1u);
    EXPECT_EQ(wt->attributeDefinition()[0], weight);

    const auto move = named<SysMLv2::Entities::ActionDefinition>(elements, "Move");
    const auto m = named<SysMLv2::Entities::ActionUsage>(elements, "m");
    ASSERT_NE(move, nullptr);
    ASSERT_NE(m, nullptr);
    ASSERT_EQ(m->actionDefinition().size(), 1u);
    EXPECT_EQ(m->actionDefinition()[0], move);
    ASSERT_EQ(m->occurrenceDefinition().size(), 1u);
    EXPECT_EQ(m->occurrenceDefinition()[0], move);

    const auto stateDef = named<SysMLv2::Entities::StateDefinition>(elements, "S");
    const auto st = named<SysMLv2::Entities::StateUsage>(elements, "st");
    ASSERT_NE(stateDef, nullptr);
    ASSERT_NE(st, nullptr);
    ASSERT_EQ(st->stateDefinition().size(), 1u);
    EXPECT_EQ(st->stateDefinition()[0], stateDef);
    ASSERT_EQ(st->actionDefinition().size(), 1u);
    EXPECT_EQ(st->actionDefinition()[0], stateDef);
    ASSERT_EQ(st->occurrenceDefinition().size(), 1u);
    EXPECT_EQ(st->occurrenceDefinition()[0], stateDef);

    const auto reqDef = named<SysMLv2::Entities::RequirementDefinition>(elements, "R");
    const auto r = named<SysMLv2::Entities::RequirementUsage>(elements, "r");
    ASSERT_NE(reqDef, nullptr);
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->requirementDefinition(), reqDef);
    EXPECT_EQ(r->constraintDefinition(), reqDef);
    ASSERT_EQ(r->occurrenceDefinition().size(), 1u);
    EXPECT_EQ(r->occurrenceDefinition()[0], reqDef);

    // "attribute c2 : Color;" uses the attribute_usage rule (KEYWORD_ATTRIBUTE), so c2 is a
    // plain AttributeUsage - not an EnumerationUsage, which only enumerated_value ("enum ...")
    // usages become - so only attributeDefinition (not enumerationDefinition) applies here.
    const auto colorDef = named<SysMLv2::Entities::EnumerationDefinition>(elements, "Color");
    const auto c2 = named<SysMLv2::Entities::AttributeUsage>(elements, "c2");
    ASSERT_NE(colorDef, nullptr);
    ASSERT_NE(c2, nullptr);
    ASSERT_EQ(c2->attributeDefinition().size(), 1u);
    EXPECT_EQ(c2->attributeDefinition()[0], colorDef);

    const auto connDef = named<SysMLv2::Entities::ConnectionDefinition>(elements, "Conn");
    const auto cc = named<SysMLv2::Entities::ConnectionUsage>(elements, "cc");
    ASSERT_NE(connDef, nullptr);
    ASSERT_NE(cc, nullptr);
    ASSERT_EQ(cc->connectionDefinition().size(), 1u);
    EXPECT_EQ(cc->connectionDefinition()[0], connDef);
    ASSERT_EQ(cc->partDefinition().size(), 1u);
    EXPECT_EQ(cc->partDefinition()[0], connDef);

    const auto ifDef = named<SysMLv2::Entities::InterfaceDefinition>(elements, "IF");
    const auto ii = named<SysMLv2::Entities::InterfaceUsage>(elements, "ii");
    ASSERT_NE(ifDef, nullptr);
    ASSERT_NE(ii, nullptr);
    ASSERT_EQ(ii->interfaceDefinition().size(), 1u);
    EXPECT_EQ(ii->interfaceDefinition()[0], ifDef);
    ASSERT_EQ(ii->connectionDefinition().size(), 1u);
    EXPECT_EQ(ii->connectionDefinition()[0], ifDef);

    const auto car = named<SysMLv2::Entities::PartDefinition>(elements, "Car");
    const auto p = named<SysMLv2::Entities::PartUsage>(elements, "p");
    ASSERT_NE(car, nullptr);
    ASSERT_NE(p, nullptr);
    ASSERT_EQ(p->partDefinition().size(), 1u);
    EXPECT_EQ(p->partDefinition()[0], car);
    ASSERT_EQ(p->itemDefinition().size(), 1u);
    EXPECT_EQ(p->itemDefinition()[0], car);
    ASSERT_EQ(p->occurrenceDefinition().size(), 1u);
    EXPECT_EQ(p->occurrenceDefinition()[0], car);
}

TEST(TestSysMLParser, ConstraintDefinitionViaPredicateTyping) {
    // NOTE: the SysMLv2.g4 constraint_definition rule ("occurrence_definition_prefix?
    // definition_declaration calculation_body") is missing the "KEYWORD_CONSTRAINT
    // KEYWORD_DEF" pair that every other *_definition rule has (e.g. calculation_definition),
    // so a "constraint def X;" declaration cannot currently be parsed at all - it is not
    // reachable from any start/definition_element alternative. ConstraintUsage::constraintDefinition
    // is populated whenever a constraint is typed by anything derived from KerML::Predicate, so this
    // is exercised here with a plain KerML predicate declaration instead.
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "predicate IsPositive; constraint c : IsPositive;");
    ASSERT_TRUE(errors.empty());
    const auto pred = named<KerML::Entities::Predicate>(elements, "IsPositive");
    const auto c = named<SysMLv2::Entities::ConstraintUsage>(elements, "c");
    ASSERT_NE(pred, nullptr);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->constraintDefinition(), pred);
}

namespace {
// Counts how many parsed elements carry the given declaredName. Used below to confirm that
// a nested declaration's name is NOT leaking onto some other (usually enclosing) element -
// the symptom of review defect B, where an empty enter/exit handler for the enclosing
// construct let exitUsage_declaration/exitDefinition_declaration apply identification to
// the wrong element on the ParentStack.
int countNamed(const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements, const std::string& name) {
    int count = 0;
    for (const auto& element : elements) {
        if (element && element->declaredName().value_or("") == name) ++count;
    }
    return count;
}
}

// Regression tests for review defect B: 15 (+1) SysMLv2ListenerImplementation handlers had
// empty enter/exit bodies. Because exitUsage_declaration/exitDefinition_declaration apply
// identification to ParentStack.top(), an empty handler for the enclosing construct let a
// nested declaration's name overwrite the enclosing element's name instead of its own. Each
// test below checks: (1) the outer package is still named "P", (2) the expected element
// exists with the expected metaclass and name, and (3) no other element in the model carries
// the inner declaration's name (i.e. it was not misapplied to the enclosing element).

TEST(TestSysMLParser, UseCaseDefinitionWithActorAndObjectiveKeepsOwnIdentity) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { use case def U { actor a; objective o; } }");
    ASSERT_TRUE(errors.empty());

    const auto pkg = named<KerML::Entities::Package>(elements, "P");
    ASSERT_NE(pkg, nullptr);

    const auto useCaseDef = named<SysMLv2::Entities::UseCaseDefinition>(elements, "U");
    ASSERT_NE(useCaseDef, nullptr);

    const auto actor = named<SysMLv2::Entities::PartUsage>(elements, "a");
    ASSERT_NE(actor, nullptr);
    const auto objective = named<SysMLv2::Entities::RequirementUsage>(elements, "o");
    ASSERT_NE(objective, nullptr);

    // Before the fix, "U" (the use case definition's own name) was overwritten by "a" or "o"
    // (the last-exited nested declaration), because Use_case_definition/Actor_usage/
    // Objective_requirement_usage had empty handlers.
    EXPECT_EQ(countNamed(elements, "U"), 1);
    EXPECT_EQ(countNamed(elements, "a"), 1);
    EXPECT_EQ(countNamed(elements, "o"), 1);
}

TEST(TestSysMLParser, RequirementDefinitionWithConstraintKeepsOwnIdentity) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { requirement def R { require constraint c; } }");
    ASSERT_TRUE(errors.empty());

    const auto pkg = named<KerML::Entities::Package>(elements, "P");
    ASSERT_NE(pkg, nullptr);

    const auto reqDef = named<SysMLv2::Entities::RequirementDefinition>(elements, "R");
    ASSERT_NE(reqDef, nullptr);

    const auto constraint = named<SysMLv2::Entities::ConstraintUsage>(elements, "c");
    ASSERT_NE(constraint, nullptr);

    // Before the fix, "R" was overwritten by "c" because Requirement_constraint_usage had an
    // empty handler and did not push its own ConstraintUsage onto the ParentStack.
    EXPECT_EQ(countNamed(elements, "R"), 1);
    EXPECT_EQ(countNamed(elements, "c"), 1);
}

TEST(TestSysMLParser, RequirementDefinitionWithFramedConcernKeepsOwnIdentity) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { requirement def R { frame constraint c; } }");
    ASSERT_TRUE(errors.empty());

    const auto pkg = named<KerML::Entities::Package>(elements, "P");
    ASSERT_NE(pkg, nullptr);

    const auto reqDef = named<SysMLv2::Entities::RequirementDefinition>(elements, "R");
    ASSERT_NE(reqDef, nullptr);

    const auto concern = named<SysMLv2::Entities::ConcernUsage>(elements, "c");
    ASSERT_NE(concern, nullptr);

    EXPECT_EQ(countNamed(elements, "R"), 1);
    EXPECT_EQ(countNamed(elements, "c"), 1);
}

TEST(TestSysMLParser, StateDefinitionWithEntryActionKeepsOwnIdentity) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { state def S { entry; } }");
    ASSERT_TRUE(errors.empty());

    const auto pkg = named<KerML::Entities::Package>(elements, "P");
    ASSERT_NE(pkg, nullptr);

    const auto stateDef = named<SysMLv2::Entities::StateDefinition>(elements, "S");
    ASSERT_NE(stateDef, nullptr);

    // Before the fix, State_perform_action_uage (the rule actually matched by a bare
    // "entry;") had an empty handler, so identification from its inner action_body could
    // corrupt whichever element was on top of the ParentStack (here, the enclosing
    // StateDefinition itself would lose its name "S").
    EXPECT_EQ(countNamed(elements, "S"), 1);
}

TEST(TestSysMLParser, UseCaseDefinitionWithSeparateUsageKeepsOwnIdentity) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { use case def U; use case u : U; }");
    ASSERT_TRUE(errors.empty());

    const auto pkg = named<KerML::Entities::Package>(elements, "P");
    ASSERT_NE(pkg, nullptr);

    const auto useCaseDef = named<SysMLv2::Entities::UseCaseDefinition>(elements, "U");
    ASSERT_NE(useCaseDef, nullptr);
    const auto useCaseUsage = named<SysMLv2::Entities::UseCaseUsage>(elements, "u");
    ASSERT_NE(useCaseUsage, nullptr);

    // Before the fix, Use_case_definition had an empty handler, so exitDefinition_declaration
    // applied "U"'s identification to the enclosing Package instead of a UseCaseDefinition.
    EXPECT_EQ(countNamed(elements, "P"), 1);
    EXPECT_EQ(countNamed(elements, "U"), 1);
    EXPECT_EQ(countNamed(elements, "u"), 1);
}


// ---- AP8: expression grammar in SysML v2 textual notation ----
namespace {
std::shared_ptr<KerML::Entities::Expression> sysmlAttributeValue(const std::string& expression) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2("attribute x = " + expression + ";");
    if (!errors.empty()) {
        ADD_FAILURE() << "syntax error in '" << expression << "': " << errors.front()->description();
        return nullptr;
    }
    for (const auto& element : elements) {
        if (auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(element)) return value->value();
    }
    ADD_FAILURE() << "no feature value for '" << expression << "'";
    return nullptr;
}
}

TEST(TestSysMLExpressions, PrecedenceOfArithmeticAndLogicalOperators) {
    using namespace KerML::Entities;
    const auto sum = std::dynamic_pointer_cast<OperatorExpression>(sysmlAttributeValue("2 * 3 + 1"));
    ASSERT_NE(sum, nullptr);
    EXPECT_EQ(sum->operatorName(), "+");
    ASSERT_EQ(sum->argument().size(), 2u);
    const auto product = std::dynamic_pointer_cast<OperatorExpression>(sum->argument()[0]);
    ASSERT_NE(product, nullptr);
    EXPECT_EQ(product->operatorName(), "*");
    ASSERT_EQ(product->argument().size(), 2u);
    EXPECT_NE(std::dynamic_pointer_cast<LiteralInteger>(sum->argument()[1]), nullptr);

    const auto disjunction = std::dynamic_pointer_cast<OperatorExpression>(sysmlAttributeValue("a or b and c"));
    ASSERT_NE(disjunction, nullptr);
    EXPECT_EQ(disjunction->operatorName(), "or");
    ASSERT_EQ(disjunction->argument().size(), 2u);
    EXPECT_NE(std::dynamic_pointer_cast<FeatureReferenceExpression>(disjunction->argument()[0]), nullptr);
    const auto conjunction = std::dynamic_pointer_cast<OperatorExpression>(disjunction->argument()[1]);
    ASSERT_NE(conjunction, nullptr);
    EXPECT_EQ(conjunction->operatorName(), "and");
}

TEST(TestSysMLExpressions, CastUnaryConditionalIndexAndUnits) {
    using namespace KerML::Entities;
    const auto power = std::dynamic_pointer_cast<OperatorExpression>(sysmlAttributeValue("-x ** 2"));
    ASSERT_NE(power, nullptr);
    EXPECT_EQ(power->operatorName(), "**");
    const auto negation = std::dynamic_pointer_cast<OperatorExpression>(power->argument()[0]);
    ASSERT_NE(negation, nullptr);
    EXPECT_EQ(negation->operatorName(), "-");
    EXPECT_EQ(negation->argument().size(), 1u);

    const auto cast = std::dynamic_pointer_cast<OperatorExpression>(sysmlAttributeValue("x as T"));
    ASSERT_NE(cast, nullptr);
    EXPECT_EQ(cast->operatorName(), "as");
    ASSERT_EQ(cast->argument().size(), 2u);
    const auto type = std::dynamic_pointer_cast<InstantiationExpression>(cast->argument()[1]);
    ASSERT_NE(type, nullptr);
    ASSERT_NE(type->instantiatedType(), nullptr);
    EXPECT_EQ(type->instantiatedType()->declaredName().value_or(""), "T");

    const auto conditional = std::dynamic_pointer_cast<OperatorExpression>(sysmlAttributeValue("if a ? 1 else 2"));
    ASSERT_NE(conditional, nullptr);
    EXPECT_EQ(conditional->operatorName(), "if");
    EXPECT_EQ(conditional->argument().size(), 3u);

    const auto index = std::dynamic_pointer_cast<IndexExpression>(sysmlAttributeValue("a#(1)"));
    ASSERT_NE(index, nullptr);
    EXPECT_EQ(index->argument().size(), 2u);

    const auto bracket = std::dynamic_pointer_cast<OperatorExpression>(sysmlAttributeValue("273.15 [K]"));
    ASSERT_NE(bracket, nullptr);
    EXPECT_EQ(bracket->operatorName(), "[");
    ASSERT_EQ(bracket->argument().size(), 2u);
    const auto number = std::dynamic_pointer_cast<LiteralRational>(bracket->argument()[0]);
    ASSERT_NE(number, nullptr);
    EXPECT_DOUBLE_EQ(number->value(), 273.15);
}

TEST(TestSysMLExpressions, InvocationsAndCollectionOperators) {
    using namespace KerML::Entities;
    const auto call = std::dynamic_pointer_cast<InvocationExpression>(sysmlAttributeValue("f(1, 2 + 3)"));
    ASSERT_NE(call, nullptr);
    ASSERT_NE(call->instantiatedType(), nullptr);
    EXPECT_EQ(call->instantiatedType()->declaredName().value_or(""), "f");
    EXPECT_EQ(call->argument().size(), 2u);

    const auto select = std::dynamic_pointer_cast<OperatorExpression>(sysmlAttributeValue("s->select {in x; x > 0}"));
    ASSERT_NE(select, nullptr);
    EXPECT_EQ(select->operatorName(), "->");
    ASSERT_EQ(select->argument().size(), 2u);

    const auto chain = std::dynamic_pointer_cast<FeatureChainExpression>(sysmlAttributeValue("a.b.c"));
    ASSERT_NE(chain, nullptr);
    ASSERT_NE(chain->targetFeature(), nullptr);
    EXPECT_EQ(chain->targetFeature()->declaredName().value_or(""), "c");
}

TEST(TestSysMLExpressions, ExpressionsInConstraintsAndCalculations) {
    const auto result = SysMLv2::Files::Parser::parseSysMLv2(
        "package P { attribute def Mass; part def V { attribute m : Mass = 1.5 [kg]; attribute n = m * 2 + 1;"
        " constraint limit { m <= 10 [kg] and n > 0 } } "
        "calc def Half { in x : Real; x / 2 } "
        "action def A { in n : Integer; if n > 0 { } else { } } }");
    EXPECT_TRUE(result.second.empty()) << (result.second.empty() ? "" : result.second.front()->description());
}

// ---- Phase 2 gate: constructs of the standard library that the grammar used to reject ----
namespace {
template<class T>
std::shared_ptr<T> gateNamed(const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements, const std::string& name) {
    for (const auto& element : elements) {
        if (element && element->declaredName() == name) {
            if (auto typed = std::dynamic_pointer_cast<T>(element)) return typed;
        }
    }
    return nullptr;
}
}

TEST(TestSysMLListener, EndUsageOwnsItsCrossFeature) {
    // SysML 8.2.2.6: EndUsagePrefix = 'end' ( OwnedCrossFeatureMember )?
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "part def Hub; connection def C { end connectingHub [1..*] part hub : Hub; }");
    ASSERT_TRUE(errors.empty());
    const auto hub = gateNamed<SysMLv2::Entities::PartUsage>(elements, "hub");
    const auto cross = gateNamed<SysMLv2::Entities::ReferenceUsage>(elements, "connectingHub");
    ASSERT_NE(hub, nullptr);
    ASSERT_NE(cross, nullptr);
    EXPECT_TRUE(hub->isEnd());
    EXPECT_FALSE(cross->isEnd());
    EXPECT_EQ(cross->owner(), hub);
    ASSERT_TRUE(hub->crossFeature().has_value());
    EXPECT_EQ(hub->crossFeature().value(), cross);
    EXPECT_TRUE(cross->multiplicity().has_value());
    EXPECT_FALSE(hub->multiplicity().has_value());
}

TEST(TestSysMLListener, DirectedAttributeCalcAndReferenceUsagesKeepDirection) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "action def A { in attribute a : Real = 1.0; out ref r : Real; inout x = 2; }");
    ASSERT_TRUE(errors.empty());
    const auto action = gateNamed<SysMLv2::Entities::ActionDefinition>(elements, "A");
    const auto a = gateNamed<SysMLv2::Entities::AttributeUsage>(elements, "a");
    const auto r = gateNamed<SysMLv2::Entities::ReferenceUsage>(elements, "r");
    const auto x = gateNamed<SysMLv2::Entities::ReferenceUsage>(elements, "x");
    ASSERT_NE(action, nullptr);
    ASSERT_NE(a, nullptr);
    ASSERT_NE(r, nullptr);
    ASSERT_NE(x, nullptr);
    EXPECT_EQ(a->direction(), KerML::Entities::IN);
    EXPECT_EQ(r->direction(), KerML::Entities::OUT);
    EXPECT_EQ(x->direction(), KerML::Entities::IN_OUT);
    EXPECT_EQ(a->owner(), action);
    EXPECT_EQ(r->owner(), action);
    bool hasValue = false;
    for (const auto& child : a->ownedElements()) {
        if (std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(child)) hasValue = true;
    }
    EXPECT_TRUE(hasValue);
}

TEST(TestSysMLListener, StateDefinitionWithSeveralBodyItems) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "state def S { entry action init; state a; state b; transition first a then b; }");
    ASSERT_TRUE(errors.empty());
    const auto s = gateNamed<SysMLv2::Entities::StateDefinition>(elements, "S");
    const auto a = gateNamed<SysMLv2::Entities::StateUsage>(elements, "a");
    const auto b = gateNamed<SysMLv2::Entities::StateUsage>(elements, "b");
    ASSERT_NE(s, nullptr);
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    EXPECT_EQ(a->owner(), s);
    EXPECT_EQ(b->owner(), s);
}

TEST(TestSysMLListener, ReturnParameterInCaseDefinition) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "case def K { subject s; return result : Real; }");
    ASSERT_TRUE(errors.empty());
    const auto k = gateNamed<SysMLv2::Entities::CaseDefinition>(elements, "K");
    const auto result = gateNamed<SysMLv2::Entities::Usage>(elements, "result");
    ASSERT_NE(k, nullptr);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->owner(), k);
}

TEST(TestSysMLListener, SatisfyWithoutAssertIsARequirementUsage) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "requirement def R; part def P { satisfy requirement req : R; }");
    ASSERT_TRUE(errors.empty());
    const auto p = gateNamed<SysMLv2::Entities::PartDefinition>(elements, "P");
    const auto req = gateNamed<SysMLv2::Entities::SatisfyRequirementUsage>(elements, "req");
    ASSERT_NE(p, nullptr);
    ASSERT_NE(req, nullptr);
    EXPECT_EQ(req->owner(), p);
}

TEST(TestSysMLListener, KerMLOnlyKeywordsAreUsableAsNames) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "part def P { attribute step; attribute bool; attribute function; attribute type; attribute feature; }");
    ASSERT_TRUE(errors.empty());
    for (const char* n : {"step", "bool", "function", "type", "feature"}) {
        const auto u = gateNamed<SysMLv2::Entities::AttributeUsage>(elements, n);
        EXPECT_NE(u, nullptr) << n;
    }
}

TEST(TestSysMLListener, UsageWithBodyExpression) {
    const auto [elements, errors] = SysMLv2::Files::Parser::parseSysMLv2(
        "calc def C { in x : Real; attribute y = { in z; z + 1 }; }");
    EXPECT_TRUE(errors.empty());
    EXPECT_NE(gateNamed<SysMLv2::Entities::CalculationDefinition>(elements, "C"), nullptr);
    EXPECT_NE(gateNamed<SysMLv2::Entities::AttributeUsage>(elements, "y"), nullptr);
}
