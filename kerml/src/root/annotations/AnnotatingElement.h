//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef SYSMLV2_ANNOTATINGELEMENT_H
#define SYSMLV2_ANNOTATINGELEMENT_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <root/elements/Element.h>
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
    class KERML_EXPORT AnnotatingElement : public Element{
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
    };
}


#endif //SYSMLV2_ANNOTATINGELEMENT_H
