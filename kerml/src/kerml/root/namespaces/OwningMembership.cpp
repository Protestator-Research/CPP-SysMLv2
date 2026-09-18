//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/namespaces/OwningMembership.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities
{
	OwningMembership::OwningMembership()
	{
		_dType = "OwningMembership";
	}

	std::string OwningMembership::path()
	{
		//TODO Implement
		return Membership::path();
	}

	std::string OwningMembership::ownedMemberElementId()
	{
		auto element = ownedMemberElement();
        return element ? element->elementId() : boost::lexical_cast<std::string>(OwnedMemberElementId);
	}

	boost::uuids::uuid OwningMembership::ownedMemberElementIdAsUuid()
	{
		auto element = ownedMemberElement();
        return element ? element->elementIdAsUUID() : OwnedMemberElementId;
	}

	void OwningMembership::setOwnedMemberElementId(std::string ownedMemeberElementId)
	{
		OwnedMemberElementId = boost::uuids::string_generator()(ownedMemeberElementId);
	}

	void OwningMembership::setOwnedMemberElementId(boost::uuids::uuid ownedMemeberElementId)
	{
		OwnedMemberElementId = ownedMemeberElementId;
	}

	std::string OwningMembership::ownedMemberShortName()
	{
		auto element = ownedMemberElement();
        return element ? element->declaredShortName().value_or("") : OwnedMemberShortName;
	}

	void OwningMembership::setOwnedMemberShortName(std::string ownedMemberShortName)
	{
		OwnedMemberShortName = ownedMemberShortName;
	}

	std::string OwningMembership::ownedMemberName()
	{
		auto element = ownedMemberElement();
        return element ? element->declaredName().value_or("") : OwnedMemberName;
	}

	void OwningMembership::setOwnedMemberName(std::string ownedMemberName)
	{
		OwnedMemberName = ownedMemberName;
	}
}
