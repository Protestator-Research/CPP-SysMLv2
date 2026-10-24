//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <kerml/root/elements/Relationship.h>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace KerML::Entities{
    /**
     * @class Dependency
     * @author Moritz Herzog <herzogm@rptu.de>
     * @version 1.0 Beta 2
     *
     */
    class KERML_EXPORT Dependency : public Relationship{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        /**
         * Constructor of the Dependency. This constructor does allow for an empty elementID.
         * @param elementID The Element ID of the Element. If no UUID is provided, a random UUID is provided by the Software.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         */
        explicit Dependency(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        /**
         * Constructor of the Element. The element gets a random element id.
         * @param nameOrJson The declared name of the Element, or its JSON representation.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         * If the string is a JSON object (it starts with '{') it is the JSON representation of the element, see serializeToJson(); otherwise it is the declared name.
         */
        explicit Dependency(std::string nameOrJson, std::shared_ptr<Element> owner = nullptr);

        /**
         * Destructor
         */
        virtual ~Dependency() = default;

        void setClient(std::shared_ptr<Element> client);
        std::vector<std::shared_ptr<Element>> client() const;
        void setClient(std::vector<std::shared_ptr<Element>> clients);

        void setSupplier(std::shared_ptr<Element> supplier);
        std::vector<std::shared_ptr<Element>> supplier() const;
        void setSupplier(std::vector<std::shared_ptr<Element>> suppliers);


    private:
        void initialize();

        std::vector<std::shared_ptr<Element>> Client;
        std::vector<std::shared_ptr<Element>> Supplier;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Serializes the Dependency to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Dependency.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Dependency and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Dependency from its JSON representation; the stored properties of Dependency and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Dependency.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
