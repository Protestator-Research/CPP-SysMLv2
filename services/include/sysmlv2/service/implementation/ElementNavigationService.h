//
// Created by Moritz Herzog on 19.03.25.
//

#pragma once

#include <map>
#include <sysmlv2/service/interfaces/IElementNavigationService.h>
#include <sysmlv2/service/sysmlv2service_global.h>

namespace SysMLv2::API {
    /**
     * @class ElementNavigationService
     * @version 1.0 Beta 3
     * @author Moritz Herzog
     * Implementation of the IElementNavigationService
     * @see IElementNavigationService
     */
    class SYSMLV2SERVICE_EXPORT ElementNavigationService : public IElementNavigationService{
    public:
        ElementNavigationService() = default;
        virtual ~ElementNavigationService() = default;

        std::vector<std::shared_ptr<KerML::Entities::Element>> getElements(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit) override;

        std::shared_ptr<KerML::Entities::Element> getElementById(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit, boost::uuids::uuid elementId) override;

        std::vector<std::shared_ptr<KerML::Entities::Relationship>>
        getRelationshipsByRelatedElement(std::shared_ptr<SysMLv2::REST::Project> project,
                                         std::shared_ptr<SysMLv2::REST::Commit> commit,
                                         boost::uuids::uuid elementId, int direction) override;

        std::vector<std::shared_ptr<KerML::Entities::Element>>
        getRootElements(std::shared_ptr<SysMLv2::REST::Project> project,
                        std::shared_ptr<SysMLv2::REST::Commit> commit) override;

    protected:

    };
}
