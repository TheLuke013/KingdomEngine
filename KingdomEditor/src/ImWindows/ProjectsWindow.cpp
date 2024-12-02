#include <KingdomEngine/KingdomEngine.h>

#include "KingdomEditor/Utils/GLVersionCombo.h"
#include "KingdomEditor/ProjectManager.h"

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
		}

		void RenderNewProject()
		{
            ImGui::SetCursorPos(ImVec2(14.5, 30));
            ImGui::Text("New Project");

            ImGui::SetCursorPos(ImVec2(33, 125));
            ImGui::PushItemWidth(200);
            ImGui::InputText("Name", nameStr, IM_ARRAYSIZE(nameStr));
            ImGui::PopItemWidth();

            ImGui::SetCursorPos(ImVec2(33, 160));
			GLVersionCombo(glVersion);

            ImGui::SetCursorPos(ImVec2(430, 420));
            if (ImGui::Button("Create", ImVec2(106, 32)))
            {
                std::string kepFile = std::string(nameStr) + ".kep";

                Project project(nameStr, "", kepFile, glVersion);
                ProjectManager::Get().AddProject(project);
                ProjectManager::Get().LoadProject(project);
                ProjectManager::Get().SaveProjectsFile();

                properties.isVisible = false;
                ResetForms();
            }

            ImGui::SetCursorPos(ImVec2(565, 420));
            if (ImGui::Button("Back", ImVec2(106, 32)))
            {
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
		}

    private:
        bool renderingProjects;
        bool renderingNewProject;
        char nameStr[128];
        int glVersion;
	};

	ProjectsWindow projectsWindow;
}
