//
// Constraints of a Query.
//
#include <sysmlv2/rest/entities/Constraint.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <stdexcept>
#include "RestJson.h"

namespace SysMLv2::REST {
    namespace {
        const std::string PrimitiveType = "PrimitiveConstraint";
        const std::string CompositeType = "CompositeConstraint";

        void checkType(const nlohmann::json& json, const std::string& expected) {
            const auto type = json.find(JSON_TYPE_ENTITY);
            if (type == json.end() || type->is_null())
                return;
            if (!type->is_string() || !Internal::equalsIgnoreCase(type->get<std::string>(), expected))
                throw std::invalid_argument("'@type' must be \"" + expected + "\"");
        }

        bool isPrimitive(const nlohmann::json& value) {
            return value.is_string() || value.is_boolean() || value.is_number() || value.is_null();
        }
    }

    std::string toString(Operator op) {
        switch (op) {
            case Operator::InstanceOf: return "instanceOf";
            case Operator::Equal: return "=";
            case Operator::Less: return "<";
            case Operator::LessOrEqual: return "<=";
            case Operator::Greater: return ">";
            case Operator::GreaterOrEqual: return ">=";
            case Operator::In: return "in";
        }
        throw std::invalid_argument("Operator: unknown value");
    }

    std::string toString(JoinOperator op) {
        switch (op) {
            case JoinOperator::And: return "and";
            case JoinOperator::Or: return "or";
        }
        throw std::invalid_argument("JoinOperator: unknown value");
    }

    Operator operatorFromString(const std::string& text) {
        for (const auto op : {Operator::InstanceOf, Operator::Equal, Operator::Less, Operator::LessOrEqual, Operator::Greater,
                              Operator::GreaterOrEqual, Operator::In}) {
            if (toString(op) == text)
                return op;
        }
        throw std::invalid_argument("Operator: unknown literal '" + text + "'");
    }

    JoinOperator joinOperatorFromString(const std::string& text) {
        for (const auto op : {JoinOperator::And, JoinOperator::Or}) {
            if (toString(op) == text)
                return op;
        }
        throw std::invalid_argument("JoinOperator: unknown literal '" + text + "'");
    }

    // ---------------------------------------------------------------------------------------------------------------
    // Constraint
    // ---------------------------------------------------------------------------------------------------------------

    std::shared_ptr<Constraint> Constraint::fromJson(const std::string& jsonString) {
        return fromJsonValue(Internal::parseObject(jsonString, "Constraint"));
    }

    std::shared_ptr<Constraint> Constraint::fromJsonValue(const nlohmann::json& json) {
        if (!json.is_object())
            throw std::invalid_argument("Constraint: JSON object expected");
        const auto type = json.find(JSON_TYPE_ENTITY);
        if (type == json.end() || !type->is_string())
            throw std::invalid_argument("Constraint: '@type' is missing");
        const auto typeName = type->get<std::string>();
        if (Internal::equalsIgnoreCase(typeName, PrimitiveType))
            return std::shared_ptr<PrimitiveConstraint>(new PrimitiveConstraint(Parsed{}, json));
        if (Internal::equalsIgnoreCase(typeName, CompositeType))
            return std::shared_ptr<CompositeConstraint>(new CompositeConstraint(Parsed{}, json));
        throw std::invalid_argument("Constraint: unknown '@type' \"" + typeName + "\"");
    }

    // ---------------------------------------------------------------------------------------------------------------
    // PrimitiveConstraint
    // ---------------------------------------------------------------------------------------------------------------

    PrimitiveConstraint::PrimitiveConstraint(bool inverse, std::string property, Operator op, nlohmann::json value) :
        Inverse(inverse), Property(std::move(property)), Op(op) {
        if (Property.empty())
            throw std::invalid_argument("PrimitiveConstraint: 'property' must not be empty");
        try {
            setValue(value);
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("PrimitiveConstraint: ") + ex.what());
        }
    }

    PrimitiveConstraint::PrimitiveConstraint(const std::string& jsonString) {
        PrimitiveConstraint::deserializeAndPopulate(jsonString);
    }

    void PrimitiveConstraint::setValue(const nlohmann::json& value) {
        if (value.is_array()) {
            if (value.empty())
                throw std::invalid_argument("'value' needs at least one value");
            for (const auto& entry : value) {
                if (!isPrimitive(entry))
                    throw std::invalid_argument("'value' may only contain strings, booleans, numbers or null");
            }
            Values = value;
            SingleValue = false;
        } else if (isPrimitive(value)) {
            Values = nlohmann::json::array({value});
            SingleValue = true;
        } else {
            throw std::invalid_argument("'value' must be a primitive or an array of primitives");
        }
    }

    std::string PrimitiveConstraint::serializeToJson() {
        nlohmann::json json;
        json[JSON_TYPE_ENTITY] = PrimitiveType;
        json[JSON_INVERSE_ENTITY] = Inverse;
        json[JSON_PROPERTY_ENTITY] = Property;
        json[JSON_OPERATOR_ENTITY] = toString(Op);
        json[JSON_VALUE_ENTITY] = SingleValue ? Values.front() : Values;
        return json.dump(JSON_INTENT);
    }

    std::string PrimitiveConstraint::getType() const {
        return PrimitiveType;
    }

    bool PrimitiveConstraint::isInverse() const {
        return Inverse;
    }

    std::string PrimitiveConstraint::getProperty() const {
        return Property;
    }

    Operator PrimitiveConstraint::getOperator() const {
        return Op;
    }

    nlohmann::json PrimitiveConstraint::getValues() const {
        return Values;
    }

    bool PrimitiveConstraint::isSingleValue() const {
        return SingleValue;
    }

    PrimitiveConstraint::PrimitiveConstraint(Parsed, const nlohmann::json& json) {
        populate(json);
    }

    void PrimitiveConstraint::deserializeAndPopulate(const std::string& jsonString) {
        populate(Internal::parseObject(jsonString, PrimitiveType));
    }

    void PrimitiveConstraint::populate(const nlohmann::json& json) {
        try {
            checkType(json, PrimitiveType);
            Inverse = Internal::readOptionalBool(json, JSON_INVERSE_ENTITY).value_or(false);

            Property = Internal::readOptionalString(json, JSON_PROPERTY_ENTITY);
            if (Property.empty())
                throw std::invalid_argument("'property' is required");

            const auto op = Internal::readOptionalString(json, JSON_OPERATOR_ENTITY);
            if (op.empty())
                throw std::invalid_argument("'operator' is required");
            Op = operatorFromString(op);

            if (!json.contains(JSON_VALUE_ENTITY))
                throw std::invalid_argument("'value' is required");
            setValue(json[JSON_VALUE_ENTITY]);
        } catch (const std::exception& ex) {
            throw std::invalid_argument(PrimitiveType + ": " + ex.what());
        }
    }

    // ---------------------------------------------------------------------------------------------------------------
    // CompositeConstraint
    // ---------------------------------------------------------------------------------------------------------------

    CompositeConstraint::CompositeConstraint(JoinOperator op, std::vector<std::shared_ptr<Constraint>> constraints) :
        Op(op), Constraints(std::move(constraints)) {
        if (Constraints.size() < 2)
            throw std::invalid_argument("CompositeConstraint: at least two constraints are required");
        for (const auto& constraint : Constraints) {
            if (constraint == nullptr)
                throw std::invalid_argument("CompositeConstraint: a constraint is nullptr");
        }
    }

    CompositeConstraint::CompositeConstraint(const std::string& jsonString) {
        CompositeConstraint::deserializeAndPopulate(jsonString);
    }

    std::string CompositeConstraint::serializeToJson() {
        nlohmann::json json;
        json[JSON_TYPE_ENTITY] = CompositeType;
        json[JSON_OPERATOR_ENTITY] = toString(Op);
        nlohmann::json constraints = nlohmann::json::array();
        for (const auto& constraint : Constraints)
            constraints.push_back(nlohmann::json::parse(constraint->serializeToJson()));
        json[JSON_CONSTRAINT_ENTITY] = constraints;
        return json.dump(JSON_INTENT);
    }

    std::string CompositeConstraint::getType() const {
        return CompositeType;
    }

    JoinOperator CompositeConstraint::getOperator() const {
        return Op;
    }

    std::vector<std::shared_ptr<Constraint>> CompositeConstraint::getConstraints() const {
        return Constraints;
    }

    CompositeConstraint::CompositeConstraint(Parsed, const nlohmann::json& json) {
        populate(json);
    }

    void CompositeConstraint::deserializeAndPopulate(const std::string& jsonString) {
        populate(Internal::parseObject(jsonString, CompositeType));
    }

    void CompositeConstraint::populate(const nlohmann::json& json) {
        try {
            checkType(json, CompositeType);

            const auto op = Internal::readOptionalString(json, JSON_OPERATOR_ENTITY);
            if (op.empty())
                throw std::invalid_argument("'operator' is required");
            const auto joinOperator = joinOperatorFromString(op);

            const auto found = json.find(JSON_CONSTRAINT_ENTITY);
            if (found == json.end() || !found->is_array())
                throw std::invalid_argument("'constraint' must be an array");
            if (found->size() < 2)
                throw std::invalid_argument("'constraint' needs at least two constraints");

            std::vector<std::shared_ptr<Constraint>> constraints;
            for (const auto& entry : *found)
                constraints.push_back(Constraint::fromJsonValue(entry));

            Op = joinOperator;
            Constraints = std::move(constraints);
        } catch (const std::exception& ex) {
            throw std::invalid_argument(CompositeType + ": " + ex.what());
        }
    }
}
