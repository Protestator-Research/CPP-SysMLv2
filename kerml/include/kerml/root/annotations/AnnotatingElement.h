//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
#include <kerml/model/Forward.h>
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <kerml/root/elements/Element.h>
#include <boost/uuid/uuid.hpp>
#include <memory>
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../../kerml_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities {
    class Annotation;

    /**
     * @class AnnotatingElement
     * @author Moritz Herzog <herzogm@rptu.de>
     * @version Version 1.0 Beta 3
     * @brief Represents an element that allows for anntoations.
     */
    class KERML_EXPORT AnnotatingElement : public virtual Element{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        /**
         * @brief Constructor
         */
        AnnotatingElement();
        /**
         * @brief Destructor
         * The destructor can be default, because we are using shared_prts thruout the whole library
         */
        virtual ~AnnotatingElement() = default;

        /**
         * Represents the elements that are annotated by this AnnotatingElement. 
         */
        std::vector<std::shared_ptr<Element>> annotatedElements();
        /**
         * @brief Allows to add a element to the AnnotatedElements vector.
         * @param element One shared Pointer with the Element Type.
         */
        void appendAnnotatedElement(std::shared_ptr<Element> element);
        /**
         * @brief Allows to apppend multible elments in the annoted elements vector.
         * @param elements 
         */
        void appendAnnotatedElements(std::vector<std::shared_ptr<Element>> elements);
        
        /**
         * @brief 
         * @return 
         */
        std::vector<std::shared_ptr<Annotation>> annotations();
        /**
         * @brief 
         * @param annotation 
         */
        void appendAnnotation(std::shared_ptr<Annotation> annotation);
        /**
         * @brief 
         * @param annotations 
         */
        void appendAnnotations(std::vector<std::shared_ptr<Annotation>> annotations);

        /**
         * @brief 
         * @return 
         */
        std::vector<std::shared_ptr<Annotation>> ownedAnnotatingRelationships();
        /**
         * @brief 
         * @param annotation 
         */
        void appendAnnotatingRelationship(std::shared_ptr<Annotation> annotation);
        /**
         * @brief 
         * @param annotations 
         */
        void appendAnnotatingRelationships(std::vector<std::shared_ptr<Annotation>> annotations);

        /**
         * @brief 
         * @return 
         */
        std::shared_ptr<Annotation> owningAnnotatingRelationship();
        /**
         * @brief 
         * @param annotation 
         */
        void setOwningAnnotatingRelationship(std::shared_ptr<Annotation> annotation);
    private:
        /**
         * @brief Sorts the AnnotatedElements.
         * This is called everytime, when a new annotatedElement is added.
         */
        void sortAnnotatedElements();

        /**
         * @brief 
         */
        std::vector<std::shared_ptr<Element>> AnnotatedElements;
        /**
         * @brief 
         */
        std::vector<std::shared_ptr<Annotation>> Annotations;
        /**
         * @brief 
         */
        std::vector<std::shared_ptr<Annotation>> OwnedAnnotatingRelationship;
        /**
         * @brief 
         */
        std::shared_ptr<Annotation> OwningAnnotatingRelationship;
    public:
        std::vector<std::shared_ptr<Element>> annotatedElement() const;
        std::vector<std::shared_ptr<Annotation>> annotation() const;
        std::vector<std::shared_ptr<Annotation>> ownedAnnotatingRelationship() const;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a AnnotatingElement either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "AnnotatingElement".
         * @param nameOrJson The JSON representation of the AnnotatingElement, or its declared name.
         */
        explicit AnnotatingElement(const std::string& nameOrJson);

        /**
         * Serializes the AnnotatingElement to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the AnnotatingElement.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of AnnotatingElement and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the AnnotatingElement from its JSON representation; the stored properties of AnnotatingElement and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the AnnotatingElement.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
