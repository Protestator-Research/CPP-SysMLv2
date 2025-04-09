#include <gtest/gtest.h>
#include <implementation/ProjectService.h>
#include <entities/Project.h>
#include <entities/Branch.h>

void createTestInstance(SysMLv2::API::ProjectService* projectService) {
    projectService->createProject("Test Project 1", "Description of the Test Project 1");
    projectService->createProject("Test Project 2", "Description of the Test Project 2");
    projectService->createProject("Test Project 3", "Description of the Test Project 3");
    projectService->createProject("Test Project 4", "Description of the Test Project 4");
    projectService->createProject("Test Project 5", "Description of the Test Project 5");
}

TEST(ProjectConformanceTest, CreateProjectSucess) {
    SysMLv2::API::ProjectService* projectService = new SysMLv2::API::ProjectService();
    std::string projectName = "TestName";
    std::string description = "Description of the test Project";
    auto project = projectService->createProject(projectName, description);
    EXPECT_FALSE(project == nullptr);
    EXPECT_EQ(project->getName(), projectName);
    EXPECT_EQ(projectService->getProjects().size(), 1);
    EXPECT_FALSE(project->getDefaultBranch()== nullptr);
    EXPECT_EQ(project->getDefaultBranch()->getName(), "main");
    EXPECT_EQ(project->getDescription(), description);
}

TEST(ProjectConformanceTest, GetProjects) {
    SysMLv2::API::ProjectService* projectService = new SysMLv2::API::ProjectService();
    createTestInstance(projectService);
    EXPECT_EQ(projectService->getProjects().size(), 5);
}

