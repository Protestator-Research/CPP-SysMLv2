//
// Created by Moritz Herzog on 24.03.25.
//

#include "Documentation.h"

namespace KerML::Entities {

    Documentation::Documentation(std::shared_ptr<Element> documentedElement, std::string locale, std::string body) :
	Comment(locale, body){
        DocumentedElement = documentedElement;
    }

    std::shared_ptr<Element> Documentation::documentedElement() {
        return DocumentedElement;
    }

    void Documentation::setDocumentedElement(std::shared_ptr<Element> documentedElement) {
        DocumentedElement = documentedElement;
    }
} // KerML::Entities