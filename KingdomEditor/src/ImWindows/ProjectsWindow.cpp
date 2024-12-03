#include <KingdomEngine/KingdomEngine.h>

#include "KingdomEditor/Utils/GLVersionCombo.h"
#include "KingdomEditor/ProjectManager.h"
#include "KingdomEditor/Utils/Globals.h"

#include <cstring>

namespace Editor
{
    class ProjectsWindow : public KE::ImWindow
    {
    public:
        ProjectsWindow() : KE::ImWindow("Projects", 400, 100, 680, 480, true, true, KE::DockSide::NONE)
        {
            properties.flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
            SwitchToRenderProjects();
            removingProject = false;
            removingProjectName = "";
        }

        void OnReady() override
        {
        }

        void ResetForms()
        {
            strncpy(nameStr, "My Project", sizeof(nameStr) - 1);
            nameStr[sizeof(nameStr) - 1] = '\0';

            glVersion = KE::Renderer::GetVersion().glVersion;
        }

        void SwitchToRenderProjects()
        {
            renderingProjects = true;
            renderingNewProject = false;
            properties.isFocus = true;
        }

        void SwitchToNewProject()
        {
            renderingProjects = false;
            renderingNewProject = true;
            properties.isFocus = false;
        }

        void RenderProjects()
        {
            ImGui::SetCursorPos(ImVec2(14.5, 30));
            ImGui::Text("Projects");

            ImGui::SetCursorPos(ImVec2(430, 30));
            if (ImGui::Button("Open", ImVec2(106, 32)))
            {
                LOG_INFO("Open a project");
            }

            ImGui::SetCursorPos(ImVec2(565, 30));
            if (ImGui::Button("New Project", ImVec2(106, 32)))
            {
                ResetForms();
                SwitchToNewProject();
            }

            if (ImGui::BeginChild("ProjectsList", ImVec2(650, 380), true, ImGuiWindowFlags_AlwaysVerticalScrollbar))
            {
                for (const auto &project : ProjectManager::Get().GetProjects())
                {
                    ImDrawList *draw_list = ImGui::GetWindowDrawList();
                    ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
                    ImVec2 child_size = ImVec2(620, 75);

                    ImVec2 p0 = cursor_pos;
                    ImVec2 p1 = ImVec2(p0.x + child_size.x, p0.y + child_size.y);

                    draw_list->AddRect(p0, p1, IM_COL32(255, 255, 255, 255), 0.0f, 0, 1.0f);

                    if (ImGui::BeginChild(project->properties.name.c_str(), child_size))
                    {
                        ImGui::SetCursorPos(ImVec2(10, 10));
                        ImGui::Text(project->properties.name.c_str());

                        ImGui::SetCursorPos(ImVec2(500, 5));
                        if (ImGui::Button("Open", ImVec2(95, 25)))
                        {
                            ProjectManager::Get().LoadProject(project->properties.name);
                            properties.isVisible = false;
                            ResetForms();
                            SwitchToNewProject();
                        }

                        ImGui::SetCursorPos(ImVec2(500, 40));
                        if (ImGui::Button("Remove", ImVec2(95, 25)))
                        {
                            removingProjectName = project->properties.name;
                            removingProject = true;
                        }

                        ImGui::EndChild();

                        ImDrawList *draw_list = ImGui::GetWindowDrawList();
                        ImVec2 p0 = ImGui::GetItemRectMin();
                        ImVec2 p1 = ImGui::GetItemRectMax();
                        draw_list->AddRect(p0, p1, IM_COL32(255, 255, 255, 255), 0.0f, 0, 1.0f);
                    }

                    ImGui::Dummy(ImVec2(0, 5));
                }
                ImGui::EndChild();
            }
        }

        void RenderNewProject()
        {
            static bool nameExists = false;
            static bool dirExists = false;

            ImGui::SetCursorPos(ImVec2(14.5, 30));
            ImGui::Text("New Project");

            ImGui::SetCursorPos(ImVec2(33, 125));
            ImGui::PushItemWidth(200);
            ImGui::InputText("Name", nameStr, IM_ARRAYSIZE(nameStr));
            ImGui::PopItemWidth();

            ImGui::SetCursorPos(ImVec2(33, 160));
            GLVersionCombo(glVersion);

            if (nameExists)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                ImGui::SetCursorPos(ImVec2(14.5, 200));
                ImGui::Text("There is already a project with that name");
                ImGui::PopStyleColor();
            }
            else if (dirExists)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                ImGui::SetCursorPos(ImVec2(14.5, 200));
                ImGui::Text("There is already a directory with that name in current directory");
                ImGui::PopStyleColor();
            }

            ImGui::SetCursorPos(ImVec2(430, 420));
            if (ImGui::Button("Create", ImVec2(106, 32)))
            {
                for (const auto &project : ProjectManager::Get().GetProjects())
                {
                    if (project->properties.name == nameStr)
                    {
                        nameExists = true;
                        break;
                    }
                }

                if (nameExists)
                {
                    LOG_ERROR("There is already a project with that name");
                }
                else
                {
                    std::string path = KE_PROJECTS_DIRECTORY + "\\" + nameStr;
                    std::string kepFile = std::string(nameStr) + ".kep";
                    KE::Directory dir;

                    if (!dir.DirExists(path))
                    {
                        Project project(nameStr, path, kepFile, glVersion);
                        ProjectManager::Get().AddProject(project);
                        ProjectManager::Get().LoadProject(nameStr);
                        ProjectManager::Get().SaveProjectsFile();

                        properties.isVisible = false;
                        ResetForms();
                    }
                    else
                    {
                        LOG_ERROR("There is already a directory with that name in current directory");
                        dirExists = true;
                    }
                }
            }

            ImGui::SetCursorPos(ImVec2(565, 420));
            if (ImGui::Button("Back", ImVec2(106, 32)))
            {
                nameExists = false;
                dirExists = false;
                SwitchToRenderProjects();
            }
        }

        void OnRender() override
        {
            if (renderingProjects)
            {
                RenderProjects();
            }
            else if (renderingNewProject)
            {
                RenderNewProject();
            }

            if (removingProject)
            {
                ProjectManager::Get().RemoveProject(removingProjectName);
                removingProject = false;
            }
        }

    private:
        bool renderingProjects;
        bool renderingNewProject;

        bool removingProject;
        std::string removingProjectName;

        char nameStr[128];
        int glVersion;
    };

    ProjectsWindow projectsWindow;
}
