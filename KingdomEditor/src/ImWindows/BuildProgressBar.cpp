#include <KingdomEngine/KingdomEngine.h>

#include "KingdomEditor/Project/ProjectBuild.h"

namespace Editor
{
	class BuildProgressBar : public KE::ImWindow
	{
	public:
		BuildProgressBar() : KE::ImWindow("BuildProgressBar", 600, 250, 300, 100, false, true, KE::DockSide::NONE)
		{
            properties.flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
		}

		void OnReady() override
		{

		}

		void OnRender() override
		{
			ImGui::SetCursorPos(ImVec2(100, 10));
            ImGui::Text("Building Project...");

			if (ProjectBuild::generatingBuildFiles)
			{
				ImGui::SetCursorPos(ImVec2(70, 30));
            	ImGui::Text("Generating build files");
			}
			else
			{
				ImGui::SetCursorPos(ImVec2(70, 30));
            	ImGui::Text("Compiling project");
			}

            ImGui::SetCursorPos(ImVec2(50, 50));
            ImGui::PushItemWidth(200);
            ImGui::ProgressBar(ProjectBuild::buildProgress, ImVec2(0.0f, 0.0f));
            ImGui::PopItemWidth();
		}
	};

	BuildProgressBar buildProgressBar;
}
