//
// Created by Moritz Herzog on 11.03.25.
//
#pragma once

#include <stdexcept>
#include <string>
#include <sysmlv2/rest/sysmlv2rest_global.h>

namespace SysMLv2::REST {
    enum SYSMLV2REST_EXPORT Direction {
        IN,
        OUT,
        BOTH
    };

    /**
     * The literal of the REST API: "in", "out" or "both".
     * @throws std::invalid_argument If the value is no Direction.
     */
    inline std::string toString(Direction direction) {
        switch (direction) {
            case IN: return "in";
            case OUT: return "out";
            case BOTH: return "both";
        }
        throw std::invalid_argument("Direction: unknown value");
    }

    /**
     * @throws std::invalid_argument If the text is none of "in", "out" or "both".
     */
    inline Direction directionFromString(const std::string& text) {
        if (text == "in") return IN;
        if (text == "out") return OUT;
        if (text == "both") return BOTH;
        throw std::invalid_argument("Direction: unknown literal '" + text + "'");
    }
}
