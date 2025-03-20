//
// Created by Moritz Herzog on 19.03.25.
//

#include "ElementNavigationService.h"

std::vector<std::shared_ptr<SysMLv2::Entities::Element>>
SysMLv2::API::ElementNavigationService::getElements(std::shared_ptr<SysMLv2::Entities::Project> ,
                                                    std::shared_ptr<SysMLv2::Entities::Commit> ) {
    return std::vector<std::shared_ptr<SysMLv2::Entities::Element>>();
}

std::shared_ptr<SysMLv2::Entities::Element>
SysMLv2::API::ElementNavigationService::getElementById(std::shared_ptr<SysMLv2::Entities::Project> ,
                                                       std::shared_ptr<SysMLv2::Entities::Commit> ,
                                                       boost::uuids::uuid ) {
    return std::shared_ptr<SysMLv2::Entities::Element>();
}

std::vector<std::shared_ptr<SysMLv2::Entities::Relationship>>
SysMLv2::API::ElementNavigationService::getRelationshipsByRelatedElement(
        std::shared_ptr<SysMLv2::Entities::Project> , std::shared_ptr<SysMLv2::Entities::Commit> ,
        boost::uuids::uuid , int ) {
    return std::vector<std::shared_ptr<SysMLv2::Entities::Relationship>>();
}

std::vector<std::shared_ptr<SysMLv2::Entities::Element>>
SysMLv2::API::ElementNavigationService::getRootElements(std::shared_ptr<SysMLv2::Entities::Project> ,
                                                        std::shared_ptr<SysMLv2::Entities::Commit> ) {
    return std::vector<std::shared_ptr<SysMLv2::Entities::Element>>();
}
