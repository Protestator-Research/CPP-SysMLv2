//
// Created by Moritz Herzog on 24.03.25.
//

#include "Comment.h"

namespace KerML::Entities {

    Comment::Comment() {

    }

    Comment::Comment(std::string locale, std::string body) {
        Locale = locale;
        Body = body;
    }

    std::string Comment::locale() {
        return Locale;
    }

    void Comment::setLocale(std::string locale) {
        Locale = locale;
    }

    std::string Comment::body() {
        return Body;
    }

    void Comment::setBody(std::string body) {
        Body = body;
    }
} // KerML::Entities