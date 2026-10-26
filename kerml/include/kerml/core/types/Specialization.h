//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
#include <kerml/model/Forward.h>
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Relationship.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities
{
    class Type;
}
//---------------------------------------------------------
namespace KerML::Entities {
    /**
     * @class Specialization
     * @brief Displays a Specialization Relation between two types.
     * @version 1.0 Beta 4
     * 
     */
    class KERML_EXPORT Specialization  : public Relationship {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
	    /**
	     * Constructor
	     */
	    Specialization();
	    /**
	     * Constructor for the specialization class. Since the standard does not allow for empty general and specific type.
	     * @param general The type that is specialized by the specific type.
	     * @param specific The type that specializes the general type.
	     */
	    Specialization(std::shared_ptr<Type> general, std::shared_ptr<Type> specific);
	    /**
	     * Destructor
	     */
	    ~Specialization() override = default;

	    /**
	     * Gives access to the general type of the Specialization Relationship. 
	     * @return General Type as shared Pointer.
	     */
	    std::shared_ptr<Type> general() const;
	    /**
	     * This method allows to set the general type for a object.
	     * @param general The general Type given by the KerML Model
	     */
	    void setGeneral(std::shared_ptr<Type> general);

	    /**
	     * Gives access to the specific type.
	     * @return The specific type of the KerML Model as a shared pointer.
	     */
	    std::shared_ptr<Type> specific() const;
	    /**
	     * This method allows to set the specific type of a KerML model.
	     * @param specific The Specifigc Type as a shared_pointer
	     */
	    void setSpecific(std::shared_ptr<Type> specific);

    private:
        std::shared_ptr<Type> General;
        std::shared_ptr<Type> Specific;
    public:
        std::shared_ptr<Type> owningType() const;
        void setOwningType(std::shared_ptr<Type> value);

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Specialization either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Specialization".
         * @param nameOrJson The JSON representation of the Specialization, or its declared name.
         */
        explicit Specialization(const std::string& nameOrJson);

        /**
         * Serializes the Specialization to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Specialization.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Specialization and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Specialization from its JSON representation; the stored properties of Specialization and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Specialization.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
