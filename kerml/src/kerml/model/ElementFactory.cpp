//
// Creates the KerML metaclasses from their JSON representation.
//
#include <kerml/model/ElementFactory.h>
#include <kerml/model/ElementLinker.h>
#include <kerml/KerML.h>

#include <boost/uuid/string_generator.hpp>
#include <nlohmann/json.hpp>
#include <functional>
#include <map>
#include <stdexcept>

#include "JsonSupport.h"

namespace KerML::Entities {
    namespace {
        using Creator = std::function<std::shared_ptr<Element>(const std::string&)>;

        /**
         * The concrete metaclasses by their name (the "@type" of the JSON). Element is no entry, because a plain Element keeps
         * its JSON (see Element::fromJson()).
         */
        const std::map<std::string, Creator>& creators() {
            static const std::map<std::string, Creator> registry = {
                {"AnnotatingElement", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<AnnotatingElement>(json); }},
                {"Annotation", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Annotation>(json); }},
                {"Association", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Association>(json); }},
                {"AssociationStructure", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<AssociationStructure>(json); }},
                {"Behavior", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Behavior>(json); }},
                {"BindingConnector", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<BindingConnector>(json); }},
                {"BooleanExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<BooleanExpression>(json); }},
                {"Class", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Class>(json); }},
                {"Classifier", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Classifier>(json); }},
                {"CollectExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<CollectExpression>(json); }},
                {"Comment", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Comment>(json); }},
                {"Conjugation", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Conjugation>(json); }},
                {"Connector", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Connector>(json); }},
                {"ConstructorExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<ConstructorExpression>(json); }},
                {"CrossSubsetting", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<CrossSubsetting>(json); }},
                {"DataType", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<DataType>(json); }},
                {"Dependency", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Dependency>(json); }},
                {"Differencing", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Differencing>(json); }},
                {"Disjoining", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Disjoining>(json); }},
                {"Documentation", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Documentation>(json); }},
                {"ElementFilterMembership", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<ElementFilterMembership>(json); }},
                {"EndFeatureMembership", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<EndFeatureMembership>(json); }},
                {"Expression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Expression>(json); }},
                {"Feature", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Feature>(json); }},
                {"FeatureChainExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<FeatureChainExpression>(json); }},
                {"FeatureChaining", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<FeatureChaining>(json); }},
                {"FeatureInverting", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<FeatureInverting>(json); }},
                {"FeatureMembership", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<FeatureMembership>(json); }},
                {"FeatureReferenceExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<FeatureReferenceExpression>(json); }},
                {"FeatureTyping", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<FeatureTyping>(json); }},
                {"FeatureValue", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<FeatureValue>(json); }},
                {"Flow", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Flow>(json); }},
                {"FlowEnd", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<FlowEnd>(json); }},
                {"Function", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Function>(json); }},
                {"IndexExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<IndexExpression>(json); }},
                {"Interaction", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Interaction>(json); }},
                {"Intersecting", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Intersecting>(json); }},
                {"Invariant", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Invariant>(json); }},
                {"InvocationExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<InvocationExpression>(json); }},
                {"LibraryPackage", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<LibraryPackage>(json); }},
                {"LiteralBoolean", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<LiteralBoolean>(json); }},
                {"LiteralExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<LiteralExpression>(json); }},
                {"LiteralInfinity", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<LiteralInfinity>(json); }},
                {"LiteralInteger", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<LiteralInteger>(json); }},
                {"LiteralRational", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<LiteralRational>(json); }},
                {"LiteralString", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<LiteralString>(json); }},
                {"Membership", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Membership>(json); }},
                {"MembershipImport", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<MembershipImport>(json); }},
                {"Metaclass", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Metaclass>(json); }},
                {"MetadataAccessExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<MetadataAccessExpression>(json); }},
                {"MetadataFeature", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<MetadataFeature>(json); }},
                {"Multiplicity", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Multiplicity>(json); }},
                {"MultiplicityRange", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<MultiplicityRange>(json); }},
                {"Namespace", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Namespace>(json); }},
                {"NamespaceImport", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<NamespaceImport>(json); }},
                {"NullExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<NullExpression>(json); }},
                {"OperatorExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<OperatorExpression>(json); }},
                {"OwningMembership", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<OwningMembership>(json); }},
                {"Package", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Package>(json); }},
                {"ParameterMembership", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<ParameterMembership>(json); }},
                {"PayloadFeature", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<PayloadFeature>(json); }},
                {"Predicate", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Predicate>(json); }},
                {"Redefinition", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Redefinition>(json); }},
                {"ReferenceSubsetting", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<ReferenceSubsetting>(json); }},
                {"ResultExpressionMembership", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<ResultExpressionMembership>(json); }},
                {"ReturnParameterMembership", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<ReturnParameterMembership>(json); }},
                {"SelectExpression", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<SelectExpression>(json); }},
                {"Specialization", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Specialization>(json); }},
                {"Step", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Step>(json); }},
                {"Structure", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Structure>(json); }},
                {"Subclassification", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Subclassification>(json); }},
                {"Subsetting", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Subsetting>(json); }},
                {"Succession", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Succession>(json); }},
                {"SuccessionFlow", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<SuccessionFlow>(json); }},
                {"TextualRepresentation", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<TextualRepresentation>(json); }},
                {"Type", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Type>(json); }},
                {"TypeFeaturing", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<TypeFeaturing>(json); }},
                {"Unioning", [](const std::string& json) -> std::shared_ptr<Element> { return std::make_shared<Unioning>(json); }},
            };
            return registry;
        }
    }

    std::shared_ptr<Element> createElementFromJson(const std::string& jsonString) {
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        if (!json.is_object())
            throw std::invalid_argument("The JSON of an Element must be an object.");

        const auto type = json.find("@type");
        if (type != json.end() && type->is_string()) {
            const auto creator = creators().find(type->get<std::string>());
            if (creator != creators().end()) {
                const auto id = json.find("@id");
                if (id == json.end() || !Json::parseIdentity(*id))
                    throw std::invalid_argument("The JSON of an Element requires a valid \"@id\".");
                return creator->second(jsonString);
            }
        }
        return Element::fromJson(jsonString);
    }

    std::vector<std::shared_ptr<Element>> createElementsFromJson(const std::vector<std::string>& jsons) {
        std::vector<std::shared_ptr<Element>> elements;
        elements.reserve(jsons.size());
        for (const auto& json : jsons)
            elements.push_back(createElementFromJson(json));
        linkElements(elements);
        return elements;
    }
}
