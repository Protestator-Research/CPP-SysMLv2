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
#include <kerml/root/annotations/Comment.h>
#include <kerml/root/elements/Element.h>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace KerML::Entities {
	/**
	 * @class Documentation
	 * @author Moritz Herzog
	 * @version 1.0 Beta 3
	 * @brief Abstract representation of the Documentation element.
	 * 
	 */
	class KERML_EXPORT Documentation : public Comment {
    public:
		explicit Documentation(std::shared_ptr<Element> documentedElement = nullptr, std::string locale = "", std::string body = "");

        ~Documentation() override = default;

        std::shared_ptr<Element> documentedElement();

        void setDocumentedElement(std::shared_ptr<Element> documentedElement);

    private:
        std::shared_ptr<Element> DocumentedElement;
    };
} // KerML::Entities
