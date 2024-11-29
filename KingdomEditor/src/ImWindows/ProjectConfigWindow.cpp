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
		    //get current project properties
		    if (ProjectManager::Get().GetLoadedProject())
            {
                inputProjectName = ProjectManager::Get().GetLoadedProject()->properties.name;
                glVersion = ProjectManager::Get().GetLoadedProject()->properties.glVersion;
            }

            //render widgets
            strncpy(nameStr, inputProjectName.c_str(), sizeof(nameStr) - 1);
            nameStr[sizeof(nameStr) - 1] = '\0';

            if (ProjectManager::Get().GetLoadedProject())
            {
                ImGui::PushItemWidth(200);
                ImGui::InputText("Name", nameStr, IM_ARRAYSIZE(nameStr));
                ImGui::PopItemWidth();

                inputProjectName.assign(nameStr);

                GLVersionCombo(glVersion);
            }
            else
            {
                ImGui::Text("No project loaded");
            }

			//update project properties if they changed
			if (ProjectManager::Get().GetLoadedProject())
            {
                if (ProjectManager::Get().GetLoadedProject()->properties.name != inputProjectName)
                {
                    ProjectManager::Get().GetLoadedProject()->properties.name = inputProjectName;
                }
                else if (ProjectManager::Get().GetLoadedProject()->properties.glVersion != glVersion)
                {
                    ProjectManager::Get().GetLoadedProject()->properties.glVersion = glVersion;
                }
            }
		}

    private:
        char nameStr[128];
        std::string inputProjectName;
        int glVersion;

	};

	ProjectConfigWindow projectConfigWindow;
}
