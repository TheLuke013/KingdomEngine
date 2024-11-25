#include "KingdomEngine/ImGui/ImWindow.h"
#include "KingdomEngine/ImGui/ImWindowManager.h"

namespace KE
{
	ImWindow::ImWindow(const std::string& name, float xPos, float yPos, float xSize, float ySize, bool visible, bool isFocus, DockSide dockSide)
	{
		properties.position = ImVec2(xPos, yPos);
		properties.size = ImVec2(xSize, ySize);
		properties.name = name;
		properties.dockSide = dockSide;
		properties.isVisible = visible;
		properties.isFocus = isFocus;
		properties.flags = 0;

		properties.isInitialized = false;

		REGISTER_IM_WINDOW(this);
	}

	ImWindow::~ImWindow()
	{
	}

	void ImWindow::Render()
	{
		///on the first render
		if (!properties.isInitialized)
		{
			ImGui::SetNextWindowPos(properties.position);
			ImGui::SetNextWindowSize(properties.size);
			properties.isInitialized = true;
		}

		if (properties.isVisible)
		{
		    if (properties.isFocus)
            {
                ImGui::SetNextWindowFocus();
            }

            ImGui::Begin(properties.name.c_str(), &properties.isVisible, properties.flags);
            OnRender();
            ImGui::End();
		}
	}
}
