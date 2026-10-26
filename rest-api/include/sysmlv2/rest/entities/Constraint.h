//
// Constraints of a Query (SysML v2 API, 7.1.4): Constraint, PrimitiveConstraint, CompositeConstraint.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/IEntity.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------

namespace SysMLv2::REST {
    /**
     * The operator of a PrimitiveConstraint. The JSON literals are "instanceOf", "=", "<", "<=", ">", ">=" and "in".
     */
    enum class Operator {
        InstanceOf,
        Equal,
        Less,
        LessOrEqual,
        Greater,
        GreaterOrEqual,
        In
    };

    /**
     * The operator of a CompositeConstraint. The JSON literals are "and" and "or".
     */
    enum class JoinOperator {
        And,
        Or
    };

    /** The JSON literal of the operator, e.g. "<=". */
    SYSMLV2REST_EXPORT std::string toString(Operator op);
    /** The JSON literal of the join operator, "and" or "or". */
    SYSMLV2REST_EXPORT std::string toString(JoinOperator op);
    /** @throws std::invalid_argument If the text is no Operator literal. */
    SYSMLV2REST_EXPORT Operator operatorFromString(const std::string& text);
    /** @throws std::invalid_argument If the text is no JoinOperator literal. */
    SYSMLV2REST_EXPORT JoinOperator joinOperatorFromString(const std::string& text);

    /**
     * Abstract base class of the constraints of a Query.
     * @class Constraint
     */
    class SYSMLV2REST_EXPORT Constraint : public IEntity {
    public:
        ~Constraint() override = default;

        /**
         * Reads a constraint; the concrete class is chosen by "@type" ("PrimitiveConstraint" or "CompositeConstraint").
         * @throws std::invalid_argument If the text is no JSON object, "@type" is missing or unknown or the constraint is invalid.
         */
        static std::shared_ptr<Constraint> fromJson(const std::string& jsonString);

        /**
         * Like fromJson(const std::string&) for an already parsed JSON value.
         */
        static std::shared_ptr<Constraint> fromJsonValue(const nlohmann::json& json);

        /** The "@type" of the constraint. */
        [[nodiscard]] virtual std::string getType() const = 0;

    protected:
        Constraint() = default;

        /** Tag for the private constructors of the subclasses that take an already parsed JSON object. */
        struct Parsed {};
    };

    /**
     * A constraint on a single property: {"@type": "PrimitiveConstraint", "inverse": false, "property": "@type",
     * "operator": "=", "value": "PartDefinition"}.
     *
     * The value is a list of primitives (string, boolean, number or null; a UUID is a string). The standard has the
     * multiplicity [1..*], Annex B writes a single value without an array. Both forms are read. The form is kept: a value
     * given as a single primitive (or read as one) is written as a single primitive, a given array is written as an array.
     * @class PrimitiveConstraint
     */
    class SYSMLV2REST_EXPORT PrimitiveConstraint : public Constraint {
    public:
        PrimitiveConstraint() = delete;

        /**
         * @param inverse Inverts the meaning of the constraint.
         * @param property The name of the property that is tested.
         * @param op The comparison.
         * @param value A primitive (single value form) or a non-empty array of primitives.
         * @throws std::invalid_argument If the property is empty, the value is empty or contains no primitives.
         */
        PrimitiveConstraint(bool inverse, std::string property, Operator op, nlohmann::json value);

        /**
         * @param jsonString A JSON object of a PrimitiveConstraint.
         * @throws std::invalid_argument If the text is no JSON object, "property", "operator" or "value" is missing or invalid.
         */
        explicit PrimitiveConstraint(const std::string& jsonString);

        std::string serializeToJson() override;

        [[nodiscard]] std::string getType() const override;
        [[nodiscard]] bool isInverse() const;
        [[nodiscard]] std::string getProperty() const;
        [[nodiscard]] Operator getOperator() const;

        /** The values as a JSON array (also if a single value was given). */
        [[nodiscard]] nlohmann::json getValues() const;

        /** True if the value is written as a single primitive and not as an array. */
        [[nodiscard]] bool isSingleValue() const;

    protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

    private:
        friend class Constraint;
        /** Reads an already parsed JSON object. */
        PrimitiveConstraint(Parsed, const nlohmann::json& json);
        void populate(const nlohmann::json& json);
        void setValue(const nlohmann::json& value);

        bool Inverse = false;
        std::string Property;
        Operator Op = Operator::Equal;
        nlohmann::json Values = nlohmann::json::array();
        bool SingleValue = false;
    };

    /**
     * Joins at least two constraints with "and" or "or".
     * @class CompositeConstraint
     */
    class SYSMLV2REST_EXPORT CompositeConstraint : public Constraint {
    public:
        CompositeConstraint() = delete;

        /**
         * @throws std::invalid_argument If there are less than two constraints or one of them is nullptr.
         */
        CompositeConstraint(JoinOperator op, std::vector<std::shared_ptr<Constraint>> constraints);

        /**
         * @param jsonString A JSON object of a CompositeConstraint.
         * @throws std::invalid_argument If the text is no JSON object, the operator is unknown, or "constraint" is no array
         * of at least two valid constraints.
         */
        explicit CompositeConstraint(const std::string& jsonString);

        std::string serializeToJson() override;

        [[nodiscard]] std::string getType() const override;
        [[nodiscard]] JoinOperator getOperator() const;
        [[nodiscard]] std::vector<std::shared_ptr<Constraint>> getConstraints() const;

    protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

    private:
        friend class Constraint;
        /** Reads an already parsed JSON object. */
        CompositeConstraint(Parsed, const nlohmann::json& json);
        void populate(const nlohmann::json& json);
        JoinOperator Op = JoinOperator::And;
        std::vector<std::shared_ptr<Constraint>> Constraints;
    };
}
