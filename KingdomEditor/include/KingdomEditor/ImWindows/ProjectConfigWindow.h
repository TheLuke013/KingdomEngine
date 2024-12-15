#ifndef PROJECTS_CONFIG_WINDOW_H
#define PROJECTS_CONFIG_WINDOW_H

#include <KingdomEngine/ImGui/ImWindow.h>

#include "KingdomEditor/Utils/GLVersionCombo.h"
#include "KingdomEditor/Project/ProjectManager.h"
#include "KingdomEditor/Utils/Globals.h"

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
		    if (ProjectManager::Get().GetLoadedProject() && Globals::PROJECT_CHANGED)
            {
                projProp.name = ProjectManager::Get().GetLoadedProject()->properties.name;
                projProp.glVersion = ProjectManager::Get().GetLoadedProject()->properties.glVersion;
                projProp.backgroundColor = ProjectManager::Get().GetLoadedProject()->properties.backgroundColor;
				projProp.windowProperties.title = ProjectManager::Get().GetLoadedProject()->properties.windowProperties.title;
				projProp.windowProperties.width = ProjectManager::Get().GetLoadedProject()->properties.windowProperties.width;
				projProp.windowProperties.height = ProjectManager::Get().GetLoadedProject()->properties.windowProperties.height;
				
                changed = false;
                Globals::PROJECT_CHANGED = false;
            }

            //render widgets
            strncpy(nameStr, projProp.name.c_str(), sizeof(nameStr) - 1);
            nameStr[sizeof(nameStr) - 1] = '\0';
			
			strncpy(windowTitleStr, projProp.windowProperties.title.c_str(), sizeof(windowTitleStr) - 1);
            windowTitleStr[sizeof(windowTitleStr) - 1] = '\0';

            if (ProjectManager::Get().GetLoadedProject())
            {
                //Project name
                ImGui::PushItemWidth(200);
                ImGui::InputText("Name", nameStr, IM_ARRAYSIZE(nameStr));
                ImGui::PopItemWidth();

                projProp.name.assign(nameStr);

                //GL Version
                GLVersionCombo(projProp.glVersion);

                //Background Color
                static bool showBGColor = false;
                if (ImGui::Button("Background Color"))
                {
                    showBGColor = !showBGColor;
                }

                static ImVec4 color = ImVec4(projProp.backgroundColor.r,
                                             projProp.backgroundColor.g,
                                             projProp.backgroundColor.b,
                                             projProp.backgroundColor.a);

                if (showBGColor)
                {
                    ImGui::SetNextWindowSize(ImVec2(350, 350));
                    ImGui::Begin("Color Picker", &showBGColor, ImGuiWindowFlags_NoResize);

                    if (ImGui::ColorPicker4("Background Color", (float*)&color))
                    {
                        projProp.backgroundColor.r = color.x;
                        projProp.backgroundColor.g = color.y;
                        projProp.backgroundColor.b = color.z;
                        projProp.backgroundColor.a = color.w;
                    }

                    ImGui::End();
                }
				
				//Window Properties
				ImGui::Separator();
				ImGui::Text("Window Propertie");
				
				ImGui::PushItemWidth(200);
				ImGui::InputText("Window Title", windowTitleStr, IM_ARRAYSIZE(windowTitleStr));
				ImGui::PopItemWidth();
				projProp.windowProperties.title.assign(windowTitleStr);
				
				ImGui::InputInt("Window Width", &projProp.windowProperties.width);
				ImGui::InputInt("Window Height", &projProp.windowProperties.height);
            }
            else
            {
                ImGui::Text("No project loaded");
            }

            ImGui::SetCursorPos(ImVec2(10, 450));
            if (ImGui::Button("Save Changes"))
            {
                //update project properties if they changed
                if (ProjectManager::Get().GetLoadedProject())
                {
                    if (ProjectManager::Get().GetLoadedProject()->properties.name != projProp.name)
                    {
                        ProjectManager::Get().GetJson().GetData().RemoveMember(ProjectManager::Get().GetLoadedProject()->properties.name.c_str());
                        ProjectManager::Get().GetLoadedProject()->properties.name = projProp.name;
                        ProjectManager::Get().UpdateLoadedProjectJsonData();
                    }

                    ProjectManager::Get().GetLoadedProject()->properties.backgroundColor = projProp.backgroundColor;
                    ProjectManager::Get().GetLoadedProject()->properties.glVersion = projProp.glVersion;
					
					ProjectManager::Get().GetLoadedProject()->properties.windowProperties.title = projProp.windowProperties.title;
					ProjectManager::Get().GetLoadedProject()->properties.windowProperties.width = projProp.windowProperties.width;
					ProjectManager::Get().GetLoadedProject()->properties.windowProperties.height = projProp.windowProperties.height;
					
					ProjectManager::Get().GetLoadedProject()->SaveKepFile();
                    changed = true;
                }
            }
		}

    private:
        char nameStr[128];
		char windowTitleStr[128];
        ProjectProperties projProp;
        bool changed;

	};
}

#endif
