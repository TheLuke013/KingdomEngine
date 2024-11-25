#include <KingdomEngine/KingdomEngine.h>

#include "KingdomEditor/Utils/GLVersionCombo.h"

namespace Editor
{
	class ProjectsWindow : public KE::ImWindow
	{
	public:
		ProjectsWindow() : KE::ImWindow("Projects", 400, 100, 680, 480, true, true, KE::DockSide::NONE)
		{
            properties.flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
            renderingProjects = true;
            renderingNewProject = false;
		}

		void OnReady() override
		{

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
                renderingProjects = false;
                renderingNewProject = true;
                properties.isFocus = false;
            }
		}

		void RenderNewProject()
		{
            ImGui::SetCursorPos(ImVec2(14.5, 30));
            ImGui::Text("New Project");

            ImGui::SetCursorPos(ImVec2(33, 125));
            ImGui::PushItemWidth(200);
            static char str4[128] = "My Project";
            ImGui::InputText("Name", str4, IM_ARRAYSIZE(str4));
            ImGui::PopItemWidth();

            ImGui::SetCursorPos(ImVec2(33, 160));
            int glVersion = KE::Renderer::GetVersion().glVersion;
			GLVersionCombo(glVersion);

            ImGui::SetCursorPos(ImVec2(430, 420));
            if (ImGui::Button("Create", ImVec2(106, 32)))
            {
                LOG_INFO("Creating project");
                properties.isVisible = false;
            }

            ImGui::SetCursorPos(ImVec2(565, 420));
            if (ImGui::Button("Back", ImVec2(106, 32)))
            {
                renderingProjects = true;
                renderingNewProject = false;
                properties.isFocus = true;
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
	};

	ProjectsWindow projectsWindow;
}
