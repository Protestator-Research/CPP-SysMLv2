//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once
#include <kerml/model/Forward.h>


#include <kerml/root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Conjugation
     * @brief Defines the conjungation relationship.
     * @version 1.0 Beta 4
     * @author Moritz Herzog <herzogm@rptu.de>
     */
    class KERML_EXPORT Conjugation : public Relationship{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
	    /**
	     * Protected construction supports derived representations before their references are populated.
	     */
	    public:
        // Allow derived representations to be populated before validation.
        Conjugation();
    public:
	    /**
	     * Constructor for the Conjugation. This is required considering the Standard
	     * @param originalType The provided Type, that was original
	     * @param conjugatedType The conjugated type, that is resulting
	     */
	    Conjugation(std::shared_ptr<Type> originalType, std::shared_ptr<Type> conjugatedType);
        ~Conjugation() override = default;

        std::shared_ptr<Type> originalType();
        void setOrginalType(std::shared_ptr<Type> originalType);

        std::shared_ptr<Type> conjungatedType();
        void setConjungatedType(std::shared_ptr<Type> conjungatedType);

    public:
        std::shared_ptr<Type> owningType();
        void setOwningType(std::shared_ptr<Type> owningType);

    private:
        std::shared_ptr<Type> OriginalType;
        std::shared_ptr<Type> ConjugatedType;

        std::shared_ptr<Type> OwningType;

    public:
        std::shared_ptr<Type> conjugatedType() const;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Conjugation either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Conjugation".
         * @param nameOrJson The JSON representation of the Conjugation, or its declared name.
         */
        explicit Conjugation(const std::string& nameOrJson);

        /**
         * Serializes the Conjugation to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Conjugation.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Conjugation and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Conjugation from its JSON representation; the stored properties of Conjugation and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Conjugation.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}


namespace KerML::Entities { using Conjungation = Conjugation; }
