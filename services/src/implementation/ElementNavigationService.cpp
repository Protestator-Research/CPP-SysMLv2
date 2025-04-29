//
// Created by Moritz Herzog on 19.03.25.
//

#include "ElementNavigationService.h"

#include <entities/Element.h>
#include <entities/Project.h>
#include <entities/Commit.h>
#include <entities/DataVersion.h>
#include <memory>

namespace SysMLv2::API {

    ElementNavigationService::ElementNavigationService() {

    }

    std::vector<std::shared_ptr<SysMLv2::Entities::Element>>
    ElementNavigationService::getElements(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Commit> commit) {
        if(project!=commit->getOwningProject())
            throw std::runtime_error("Project does not fit the commits project");

        std::vector<std::shared_ptr<SysMLv2::Entities::Element>> elements;

        auto dataVersionsOfCommit = commit->getDataVersion();
        for(const auto &dataVersion : dataVersionsOfCommit) {
            auto payload = dataVersion->getPayload();
            try {
                elements.push_back(std::dynamic_pointer_cast<SysMLv2::Entities::Element>(payload));
            }catch (...){}
        }
        return elements;
    }

    std::shared_ptr<SysMLv2::Entities::Element>
    ElementNavigationService::getElementById(std::shared_ptr<SysMLv2::Entities::Project> project,
                                                           std::shared_ptr<SysMLv2::Entities::Commit> commit,
                                                           boost::uuids::uuid elementId) {
        if(project!=commit->getOwningProject())
            throw std::runtime_error("Project does not fit the commits project");

        auto dataVersionsOfCommit = commit->getDataVersion();
        for(const auto &dataVersion : dataVersionsOfCommit) {
            auto payload = dataVersion->getPayload();
            if(dataVersion->getId() == elementId) {
                try {
                    return std::dynamic_pointer_cast<SysMLv2::Entities::Element>(payload);
                } catch (...) {
                    throw std::runtime_error("Data element with the UUID given could not be converted to Element");
                }
            }
        }
        throw std::runtime_error("UUID not found with commit and project combination");
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