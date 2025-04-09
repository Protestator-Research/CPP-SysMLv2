//
// Created by Moritz Herzog on 29.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef DIGITALTWIN_SYSMLV2DESERIALIZER_H
#define DIGITALTWIN_SYSMLV2DESERIALIZER_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <entities/IEntity.h>

namespace SysMLv2 {
    /**
     *
     */
    class SysMLv2Deserializer {
    public:
        /**
         * Deserializes a single element, which is contained within the inputValue.
         * @param inputValue string of the element that is to deserialize
         * @return the Element given as an IEntity.
         * @see SysMLv2::Entities::IEntity
         */
        static std::shared_ptr<SysMLv2::Entities::IEntity> deserializeJsonString(std::string inputValue);

        /**
         * Deserializes a JSON Array, containing any number of Elements.
         * @param inputValue The json string of the Array.
         * @return A vector of the entities.
         * @see std::vector
         * @see SysMLv2::Entities::IEntity
         */
        static std::vector<std::shared_ptr<SysMLv2::Entities::IEntity>> deserializeJsonArray(std::string inputValue);

    private:
        static bool checkIfIsElementType(std::string type);
    };

} // SysMLv2

#endif //DIGITALTWIN_SYSMLV2DESERIALIZER_H
