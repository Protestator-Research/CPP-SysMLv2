//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/kerml_global.h>
#include <kerml/root/annotations/AnnotatingElement.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace KerML::Entities {
    class KERML_EXPORT Comment  : public AnnotatingElement{
    public:
        Comment();
        Comment(std::string locale, std::string body);
        ~Comment() override = default;

        std::string locale();
        void setLocale(std::string locale);

        std::string body();
        void setBody(std::string body);

    protected:

    private:
        std::string Locale;
        std::string Body;
    };
} // KerML::Entities
