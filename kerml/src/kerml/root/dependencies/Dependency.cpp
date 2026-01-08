//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/dependencies/Dependency.h>

namespace KerML {
    namespace Entities {


        void Dependency::setClient(std::shared_ptr<Element> client) {
            Client = client;
        }

        std::shared_ptr<Element> Dependency::client() const {
            return Client;
        }

        void Dependency::setSupplier(std::shared_ptr<Element> supplier) {
            Supplier = supplier;
        }

        std::shared_ptr<Element> Dependency::supplier() const {
            return Supplier;
        }

        Dependency::Dependency(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
        Relationship(elementID, owner) {
            initialize();
            _dType = "Dependency";
        }

        Dependency::Dependency(std::string elementID, std::shared_ptr<Element> owner) :
        Relationship(elementID, owner) {
            initialize();
            _dType = "Dependency";
        }

        void Dependency::initialize() {
            Client = nullptr;
            Supplier = nullptr;
        }

    } // Entities
} // KerML