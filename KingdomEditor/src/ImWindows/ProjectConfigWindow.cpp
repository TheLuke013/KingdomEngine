#include <KingdomEngine/KingdomEngine.h>

#include "KingdomEditor/Utils/GLVersionCombo.h"
#include "KingdomEditor/ProjectManager.h"

#include <cstring>

namespace Editor
{
	class ProjectConfigWindow : public KE::ImWindow
	{
	public:
		ProjectConfigWindow() : KE::ImWindow("Project Configuration", 400, 100, 680, 480, false, false, KE::DockSide::NONE)
		{
            properties.flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
		}

		void OnReady() override
		{

		}

		void OnRender() override
		{
            ImGui::PushItemWidth(200);
            static char nameStr[128] = "";
            strncpy(nameStr, ProjectManager::Get().GetLoadedProject()->properties.name.c_str(), sizeof(nameStr) - 1);
            nameStr[sizeof(nameStr) - 1] = '\0';
            ImGui::InputText("Name", nameStr, IM_ARRAYSIZE(nameStr));
            ImGui::PopItemWidth();

            int glVersion = ProjectManager::Get().GetLoadedProject()->properties.glVersion;
			GLVersionCombo(glVersion);
		}
	};

	ProjectConfigWindow projectConfigWindow;
}
