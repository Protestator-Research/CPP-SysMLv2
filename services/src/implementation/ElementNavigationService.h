//
// Created by Moritz Herzog on 19.03.25.
//

#ifndef SYSMLV2_ELEMENTNAVIGATIONSERVICE_H
#define SYSMLV2_ELEMENTNAVIGATIONSERVICE_H

#include "../interfaces/IElementNavigationService.h"

namespace SysMLv2::API {
    class ElementNavigationService : public IElementNavigationService{
    public:
        ElementNavigationService();
        virtual ~ElementNavigationService();

        std::vector<std::shared_ptr<SysMLv2::Entities::Element>> getElements(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Commit> commit) override;

        std::shared_ptr<SysMLv2::Entities::Element> getElementById(std::shared_ptr<SysMLv2::Entities::Project> project,
                                                                   std::shared_ptr<SysMLv2::Entities::Commit> commit,
                                                                   boost::uuids::uuid elementId) override;

        std::vector<std::shared_ptr<SysMLv2::Entities::Relationship>>
        getRelationshipsByRelatedElement(std::shared_ptr<SysMLv2::Entities::Project> project,
                                         std::shared_ptr<SysMLv2::Entities::Commit> commit,
                                         boost::uuids::uuid elementId, int direction) override;

        std::vector<std::shared_ptr<SysMLv2::Entities::Element>>
        getRootElements(std::shared_ptr<SysMLv2::Entities::Project> project,
                        std::shared_ptr<SysMLv2::Entities::Commit> commit) override;

    private:

    };
}

#endif //SYSMLV2_ELEMENTNAVIGATIONSERVICE_H
