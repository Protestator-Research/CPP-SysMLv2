//
// Created by Moritz Herzog on 24.03.25.
//

#ifndef SYSMLV2_DEPENDENCY_H
#define SYSMLV2_DEPENDENCY_H

#include <root/elements/Relationship.h>

namespace KerML::Entities{
    /**
     * @class Dependency
     * @author Moritz Herzog <herzogm@rptu.de>
     * @version 1.0 Beta 2
     *
     */
    class Dependency : public Relationship{
    public:
        /**
         * Constructor of the Dependency. This constructor does allow for an empty elementID.
         * @param elementID The Element ID of the Element. If no UUID is provided, a random UUID is provided by the Software.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         */
        explicit Dependency(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        /**
         * Constructor of the Element. This constructor does not allow for an empty elementID.
         * @param elementID The Element ID of the Element as string.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         */
        explicit Dependency(std::string elementID, std::shared_ptr<Element> owner = nullptr);

        /**
         * Destructor
         */
        virtual ~Dependency() = default;

        void setClient(std::shared_ptr<Element> client);
        std::shared_ptr<Element> client() const;

        void setSupplier(std::shared_ptr<Element> supplier);
        std::shared_ptr<Element> supplier() const;


    private:
        void initialize();

        std::shared_ptr<Element> Client;
        std::shared_ptr<Element> Supplier;
    };
} // KerML::Entities

#endif //SYSMLV2_DEPENDENCY_H
