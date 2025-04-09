//
// Created by Moritz Herzog on 19.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef DIGITALTWIN_RECORD_H
#define DIGITALTWIN_RECORD_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <string>
#include <list>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <entities/IEntity.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::Entities {
    /**
     * Represents an abstract baseclass that is used for the SysMLv2 API
     * @class Record
     * @author Moritz Herzog
     * @version 1.0
     * @see boost::uuids::uuid
     */
    class Record : public IEntity {
    public:
        /**
         * Generalized Constructor is deleted According to the SysMLv2 Standard.
         * This requires a human Identifier, that is read only. This can not be realized by a general constructor.
         */
        Record() = delete;

        /**
         * Init the Record Object with all the nesecary objects.
         * @param id Id of the Object
         * @param name Name of the Object
         * @param description Description of the Object
         */
        explicit Record(boost::uuids::uuid id, std::string name="", std::string description="");

        /**
         * Converts a JSON String into a valid Record
         * @param jsonString The JSON String that is converted to a Record or a valid name of the Record.
         */
        explicit Record(std::string jsonStringOrName);

        /**
         * Destructor
         */
        virtual ~Record();

        /**
         * Checks the equality of the individual Records.
         * @param other The other Record object to check
         * @return True if the objects are identical.
         */
        bool operator==(Record const &other) const;

        /**
         * Returns the human identifier according to the SysMLv2 standard.
         * @return Human Identifier.
         * @see std::string
         */
        [[nodiscard]] std::string getName() const;

        /**
         * Returns the list of all Aliases according ot the SysML Standard. Hereby also holds that the name aka. the
         * human identifier is part of the alias list.
         * @return All available Aliases.
         * @see std::list
         * @see std::string
         */
        [[nodiscard]] std::list<std::string> getAlias() const;

        /**
         * Appends an single alias to the aliases list of a single Record.
         * @param alias Additional alias, that will be stored in tha alias list.
         */
        void appendAlias(std::string& alias);

        /**
         * Returns the description of a Record according to the SysMLv2 standard.
         * @return A std::string containing the Description of the Record.
         */
        [[nodiscard]] std::string getDescription() const;

        /**
         * Sets a new description of the Record.
         * @param description The description is given as a std::string.
         */
        void setDescription(std::string& description);

        /**
         * Returns the ID of the Record. The ID is only gettable and not settable except the option to set the ID
         * in the constructor according to the SysMLv2 Standard.
         * @return A boost::uuids::uuid, as the ID.
         * @see boost::uuids::uuid
         */
        [[nodiscard]] boost::uuids::uuid getId() const;

        /**
         * Returns the type of the Record. The type is a complexity that is needed to parse an object. Also there is no
         * point in making the type settable, since the type is dependent on the subclass of the Record that is used.
         * @return String representation of the Type.
         */
        [[nodiscard]] std::string getType() const;

        std::string serializeToJson() override;



    protected:
        /**
         * Type of the generated class. This also enables the parsing of the element.
         */
        std::string Type;
        /**
         * Contains the name of the Record Class. This is also called human identifier within the SysMLv2 Documentation.
         */
        std::string Name;
        /**
         * Contains all Aliases of the object. Also within the Aliases the human identifier needs to be contained,
         * according to the SysMLv2 standard.
         */
        std::list<std::string> Alias;
        /**
         * Contains the description of a single Record.
         */
        std::string Description;
        /**
         * Contains the ID of a single Record. This is also stored as a UUID.
         * @see boost::uuids::uuid
         */
        boost::uuids::uuid Id;

        bool IsForCreation = false;
    };
}

#endif //DIGITALTWIN_RECORD_H
