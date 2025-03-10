//
// Created by Moritz Herzog on 23.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef DIGITALTWIN_DIGITALTWIN_H
#define DIGITALTWIN_DIGITALTWIN_H

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <string>
#include <boost/uuid/uuid.hpp>
#include <vector>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Record.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities {
    class DataIdentity;
}


namespace SysMLv2::Entities {
    /**
     * This class Represents a Digital Twin Object that is sent to the Digital Twin Client and Server.
     * @class DigitalTwin
     * @author Moritz Herzog
     * @version 1.0
     * @see Record
     */
    class DigitalTwin : public Record {
    public:
        /**
         * Default Constructor
         * Is deleted, because Record has a deleted default constructor.
         */
        DigitalTwin() = delete;

        /**
         * Constructor that is used to parse the digital twin data or to set only the name of the DT.
         * @param jsonString The given string.
         */
        DigitalTwin(std::string jsonString);

        /**
         * 
         * @param name 
         * @param connectedElements 
         * @param commitId 
         */
        DigitalTwin(std::string name, std::vector<boost::uuids::uuid> connectedElements, boost::uuids::uuid commitId);

        /**
         * Destructor.
         */
        ~DigitalTwin();

        /**
         * Checks the Equality of the digital twin.
         * @param other The other digital twn to check.
         * @return True if the digital twins are equal.
         */
        bool operator==(DigitalTwin const &other);

        boost::uuids::uuid commitId() const;

        boost::uuids::uuid parentProjectId() const;

        std::string serializeToJson() override;

        std::vector<boost::uuids::uuid> getConnectedModels();


    private:
        boost::uuids::uuid ParentProjectId;
        boost::uuids::uuid CommitId;
        std::vector<boost::uuids::uuid> ConnectedModels;

    };
}


#endif //DIGITALTWIN_DIGITALTWIN_H
