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
#include "OwningMembership.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities
{
	OwningMembership::OwningMembership()
	{
	}

	std::string OwningMembership::path()
	{
		//TODO Implement
		return Membership::path();
	}

	std::string OwningMembership::ownedMemberElementId()
	{
		return boost::lexical_cast<std::string>(OwnedMemberElementId);
	}

	boost::uuids::uuid OwningMembership::ownedMemberElementIdAsUuid()
	{
		return OwnedMemberElementId;
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
		return OwnedMemberShortName;
	}

	void OwningMembership::setOwnedMemberShortName(std::string ownedMemberShortName)
	{
		OwnedMemberShortName = ownedMemberShortName;
	}

	std::string OwningMembership::ownedMemberName()
	{
		return OwnedMemberName;
	}

	void OwningMembership::setOwnedMemberName(std::string ownedMemberName)
	{
		OwnedMemberName = ownedMemberName;
	}
}
