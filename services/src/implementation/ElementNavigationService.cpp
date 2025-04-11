//
// Created by Moritz Herzog on 19.03.25.
//

#include "ElementNavigationService.h"

namespace SysMLv2::API {

    ElementNavigationService::ElementNavigationService() {

    }

    std::vector<std::shared_ptr<SysMLv2::Entities::Element>>
    ElementNavigationService::getElements(std::shared_ptr<SysMLv2::Entities::Project>,
                                                        std::shared_ptr<SysMLv2::Entities::Commit>) {
        return std::vector<std::shared_ptr<SysMLv2::Entities::Element>>();
    }

    std::shared_ptr<SysMLv2::Entities::Element>
    ElementNavigationService::getElementById(std::shared_ptr<SysMLv2::Entities::Project>,
                                                           std::shared_ptr<SysMLv2::Entities::Commit>,
                                                           boost::uuids::uuid) {
        return std::shared_ptr<SysMLv2::Entities::Element>();
    }

    std::vector<std::shared_ptr<SysMLv2::Entities::Relationship>> ElementNavigationService::getRelationshipsByRelatedElement(
            std::shared_ptr<SysMLv2::Entities::Project>, std::shared_ptr<SysMLv2::Entities::Commit>,
            boost::uuids::uuid, int) {
        return std::vector<std::shared_ptr<SysMLv2::Entities::Relationship>>();
    }

    std::vector<std::shared_ptr<SysMLv2::Entities::Element>> ElementNavigationService::getRootElements(std::shared_ptr<SysMLv2::Entities::Project>, std::shared_ptr<SysMLv2::Entities::Commit>) {
        return std::vector<std::shared_ptr<SysMLv2::Entities::Element>>();
    }

}