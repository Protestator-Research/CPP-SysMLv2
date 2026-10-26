//
// Created by Moritz Herzog on 11.03.25.
//
#pragma once

#include <stdexcept>
#include <string>
#include <sysmlv2/rest/sysmlv2rest_global.h>


namespace SysMLv2::REST{
    enum SYSMLV2REST_EXPORT ChangeType {
        CREATED,
        UPDATED,
        DELETED
    };

    /**
     * The literal of the REST API: "CREATED", "UPDATED" or "DELETED".
     * @throws std::invalid_argument If the value is no ChangeType.
     */
    inline std::string toString(ChangeType changeType) {
        switch (changeType) {
            case CREATED: return "CREATED";
            case UPDATED: return "UPDATED";
            case DELETED: return "DELETED";
        }
        throw std::invalid_argument("ChangeType: unknown value");
    }

    /**
     * @throws std::invalid_argument If the text is none of "CREATED", "UPDATED" or "DELETED".
     */
    inline ChangeType changeTypeFromString(const std::string& text) {
        if (text == "CREATED") return CREATED;
        if (text == "UPDATED") return UPDATED;
        if (text == "DELETED") return DELETED;
        throw std::invalid_argument("ChangeType: unknown literal '" + text + "'");
    }
}
