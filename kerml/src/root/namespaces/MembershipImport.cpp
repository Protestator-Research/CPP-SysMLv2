//
// Created by Moritz Herzog on 25.03.25.
//

#include "MembershipImport.h"

namespace KerML::Entities {
	MembershipImport::MembershipImport()
	{
	}

	std::vector<std::shared_ptr<Membership>> MembershipImport::importedMemberships(
		std::vector<std::shared_ptr<Namespace>>)
	{
		//TODO Implement
        return std::vector<std::shared_ptr<Membership>>();
	}

	std::shared_ptr<Membership> MembershipImport::importedMembership() const
	{
		return ImportedMembership;
	}

	void MembershipImport::setImportedMembership(std::shared_ptr<Membership> importedMembership)
	{
		ImportedMembership = importedMembership;
	}
} // KerML::Entities