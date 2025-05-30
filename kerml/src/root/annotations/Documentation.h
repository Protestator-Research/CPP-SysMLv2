//
// Created by Moritz Herzog on 24.03.25.
//

#ifndef SYSMLV2_DOCUMENTATION_H
#define SYSMLV2_DOCUMENTATION_H

#include "Comment.h"

namespace KerML::Entities {
    class Documentation : public Comment {
    public:
        Documentation();
        explicit Documentation(std::shared_ptr<Element> documentedElement, std::string locale = "", std::string body = "");

        ~Documentation() override = default;

        std::shared_ptr<Element> documentedElement();

        void setDocumentedElement(std::shared_ptr<Element> documentedElement);

    private:
        std::shared_ptr<Element> DocumentedElement;
    };
} // KerML::Entities

#endif //SYSMLV2_DOCUMENTATION_H
