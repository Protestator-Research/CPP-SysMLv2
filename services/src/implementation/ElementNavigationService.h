//
// Created by Moritz Herzog on 19.03.25.
//

#ifndef SYSMLV2_ELEMENTNAVIGATIONSERVICE_H
#define SYSMLV2_ELEMENTNAVIGATIONSERVICE_H

#include <map>

#include "../interfaces/IElementNavigationService.h"
#include "../sysmlv2service_global.h"

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
        ElementNavigationService();
        virtual ~ElementNavigationService() = default;

        std::vector<std::shared_ptr<SysMLv2::Entities::Element>> getElements(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Commit> commit) override;

        std::shared_ptr<SysMLv2::Entities::Element> getElementById(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Commit> commit, boost::uuids::uuid elementId) override;

        std::vector<std::shared_ptr<SysMLv2::Entities::Relationship>>
        getRelationshipsByRelatedElement(std::shared_ptr<SysMLv2::Entities::Project> project,
                                         std::shared_ptr<SysMLv2::Entities::Commit> commit,
                                         boost::uuids::uuid elementId, int direction) override;

        std::vector<std::shared_ptr<SysMLv2::Entities::Element>>
        getRootElements(std::shared_ptr<SysMLv2::Entities::Project> project,
                        std::shared_ptr<SysMLv2::Entities::Commit> commit) override;

    protected:

    };
}

#endif //SYSMLV2_ELEMENTNAVIGATIONSERVICE_H
