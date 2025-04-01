//
// Created by Moritz Herzog on 20.03.25.
//

#ifndef SYSMLV2_ELEMENT_H
#define SYSMLV2_ELEMENT_H

#include <memory>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <vector>




namespace KerML::Entities {
    class Namespace;
    class Documentation;
    class Annotation;
    class Relationship;
    class TextualRepresentation;

    /**
     * @class Element
     * @author Moritz Herzog
     * @version 1.0 Beta 2
     * @brief This part of the model allows the identification of all elements.
     * This part of the model allows the identification of all elements. This is a core concept of the KerML and SysML syntax.
     * Also this class is required for the REST-API and the parsing of the models.
     */
    class Element {
    public:
        /**
         * Constructor of the Element. This constructor does not allow for an empty elementID.
         * @param elementID The Element ID of the Element. If no UUID is provided, a random UUID is provided by the Software.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         */
        explicit Element(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        /**
         * Constructor of the Element. This constructor does not allow for an empty elementID.
         * @param elementID The Element ID of the Element as string.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         */
        explicit Element(std::string elementID, std::shared_ptr<Element> owner = nullptr);

        /**
         * Destructor
         */
        virtual ~Element();

        /**
         * Gives access to the ElementId as a string.
         * @return String of the element Id.
         */
        [[nodiscard]] std::string elementId() const;

        /**
         * Gives acces to the ElementId as a uuid. This makes the internal comparison eayser.
         * @return Element id of the Element as a uuid.
         */
        boost::uuids::uuid elementIdAsUUID() const;

        /**
         * Sets the various alternative Identifiers and overrides them with the given value.
         * @param aliasIds The given AliasIds.
         */
        void setAliasIds(std::vector<std::string> aliasIds);

        /**
         * Add another alternative Identifier.
         * @param aliasId the given alternative Identifier.
         */
        void appendAliasId(std::string& aliasId);

        /**
         * Gives access to the alternative Identifiers for one specific element.
         * @return A vector of the values. Not possible to set values via this function.
         */
        [[nodiscard]] std::vector<std::string> aliasIds() const;

        /**
         * Sets the declared short name, this is an optional alternative name of the Element. This may act as a modeller-
         * specific identifier.
         * @param declaredShortName The wanted declared short name.
         */
        void setDeclaredShortName(std::string& declaredShortName);

        /**
         * Returns the declared short name. This is a modeller-specific primary name. It has the responsibility of beeing
         * unique in the specific context or within a model.
         * @return The declared short name.
         */
        [[nodiscard]] std::string declaredShortName() const;

        /**
         * Sets the declared name of the Element.
         * @param declaredName declared name of the Element.
         */
        void setDeclaredName(std::string& declaredName);

        /**
         * Gives access to the declared name.
         * @return The internally stored declared name.
         */
        [[nodiscard]] std::string declaredName() const;

        /**
         * Sets if element is included in a implied.
         * @param isImpliedIncluded
         */
        void setImpliedIncluded(bool& isImpliedIncluded);

        /**
         *
         * @return
         */
        bool isImpliedIncluded() const;

        /**
         *
         * @return
         */
        std::string escapedName() const;

        /**
         *
         * @return
         */
        std::string effectiveShortName() const;

        /**
         *
         * @return
         */
        std::string effectiveName() const;

        /**
         *
         * @return
         */
        virtual std::shared_ptr<Namespace> libraryNamespace() const;

        /**
         * This operator is deleted, because the ElementId can not be reset by definition.
         * @param other The element that one wants to set this element to.
         * @return This element.
         */
        Element& operator=(const Element& other) = delete;

        /**
         *
         * @param other
         * @return
         */
        virtual bool operator==(const Element& other);

        /**
         *
         * @param other
         * @return
         */
        virtual bool operator<(const Element& other);

        /**
         *
         * @param other
         * @return
         */
        virtual bool operator>(const Element& other);

        /**
         *
         * @param other
         * @return
         */
        virtual bool operator<=(const Element& other);

        /**
         *
         * @param other
         * @return
         */
        virtual bool operator>=(const Element& other);

    protected:
        std::shared_ptr<Element> Owner = nullptr;
        std::vector<std::shared_ptr<Element>> OwnedElements;
        std::string ShortName;
        std::string Name;
        std::string QualifiedName;

        /**
         * Is true if the Element is contained in an ownership tree of a library.
         */
        bool IsLibraryElement = false;

        /**
         * Represents the documentation, shared by this Element. This List needs to be ordered
         */
        std::vector<std::shared_ptr<Documentation>> Documentations;

        /**
         *
         */
        std::vector<std::shared_ptr<Annotation>> OwnedAnnotations;

        /**
         *
         */
        std::vector<std::shared_ptr<TextualRepresentation>> TextualRepresentations;

        /**
        * Orders the OwnedRelationships in their Array. This is reuired per definition and needs to be called with
        * with every adding of a relationship.
        */
        void orderOwnedRelationships();

        /**
         * Orders the Owned Elements. This is per definition required. With every adding and removing of one OwnedElements
         * this function needs to be called.
         */
        void orderOwnedElements();
    private:
        /**
        * Orders the AliasIds in their Array. Is per definition required to have the AliasIds always ordered.
        */
        void orderAliasIds();

        /**
         * Represents the global unique Identifier.
         * In this case the ElementId is stored as a UUID, against the standard. Allowing us to address even more elements in an
         * ElementId is according to the KerML standard not allowed to change.
         */
        const boost::uuids::uuid ElementId;

        /**
         * Alternative descriptors of the specific element.
         */
        std::vector<std::string> AliasIds;
        /**
         * An optional alternative name of the 
         */
        std::string DeclaredShortName;
        std::string DeclaredName;

        /**
         * Represents the Relationships for which this Element is the owning related Element.
         */
        std::vector<std::shared_ptr<Relationship>> OwnedRelationships;

        bool IsImpliedIncluded = false;


    };

} // KerML::Entities


#endif //SYSMLV2_ELEMENT_H
