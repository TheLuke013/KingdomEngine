#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class ProjectsWindow : public KE::ImWindow
	{
	public:
		ProjectsWindow() : KE::ImWindow("Projects", 400, 100, 680, 480, true, true, KE::DockSide::NONE)
		{
            properties.flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
		}

		void OnReady() override
		{

		}

		void OnRender() override
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
                properties.isVisible = false;
                properties.isFocus = false;
            }
		}
	};

	ProjectsWindow projectsWindow;
}
