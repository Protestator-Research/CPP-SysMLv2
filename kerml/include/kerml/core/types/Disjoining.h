//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once


#include <kerml//root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Disjoining
     * @version 1.0 Beta 4
     * @brief 
     * @author Moritz Herzog <herzogm@rptu.de>
     */
    class KERML_EXPORT Disjoining : public Relationship{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
	    Disjoining() = delete;
	    /**
	     * Constructor of the Element
	     * @param typeDisjoined 
	     * @param disjoiningType 
	     */
	    Disjoining(std::shared_ptr<Type> typeDisjoined, std::shared_ptr<Type> disjoiningType);
    	~Disjoining() override = default;


        std::shared_ptr<Type> typeDisjoined();
        void setTypeDisjoined(std::shared_ptr<Type> typeDisjoined);

        std::shared_ptr<Type> disjoiningType();
        void setDisjoiningType(std::shared_ptr<Type> disjoiningType);

    public:
        std::shared_ptr<Type> owningType();
        void setOwningType(std::shared_ptr<Type> owningType);

    private:
        std::shared_ptr<Type> TypeDisjoined;
        std::shared_ptr<Type> DisjoiningType;

        std::shared_ptr<Type> OwningType;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Disjoining either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Disjoining".
         * @param nameOrJson The JSON representation of the Disjoining, or its declared name.
         */
        explicit Disjoining(const std::string& nameOrJson);

        /**
         * Serializes the Disjoining to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Disjoining.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Disjoining and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Disjoining from its JSON representation; the stored properties of Disjoining and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Disjoining.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}