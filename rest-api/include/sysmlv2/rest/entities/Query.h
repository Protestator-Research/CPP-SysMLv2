//
// Created by Moritz Herzog on 23.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <vector>
#include <sysmlv2/rest/entities/Record.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::REST {
    class Data;
}

namespace SysMLv2::REST {
    /**
     * Represents an abstract baseclass that is used for the SysMLv2 API
     * @class Query
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT Query : public Record {
    public:
        Query() = delete;
        Query(std::string name,std::vector<std::string> select, std::vector<std::shared_ptr<Data>> scope, std::vector<std::string> order);
        explicit Query(std::string jsonStringOrName);

        std::string serializeToJson() override;

        ~Query() override = default;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::vector<std::string> Select;
        std::vector<std::shared_ptr<Data>> Scope;
        std::vector<std::string> Order;
    };
}
