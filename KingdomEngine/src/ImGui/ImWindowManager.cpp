#include "KingdomEngine/ImGui/ImWindowManager.h"

namespace KE
{
	ImWindowManager& ImWindowManager::Get()
	{
		static ImWindowManager* instance = new ImWindowManager();
		return *instance;
	}

	void ImWindowManager::Register(ImWindow* imWindow_)
	{
		windows.push_back(imWindow_);
		windowsMap[imWindow_->properties.name] = imWindow_;
	}

	void ImWindowManager::OnReadyAllWindows()
	{
	    for (auto window : windows)
		{
			window->OnReady();
		}
	}

	void ImWindowManager::UpdateAllWindows()
	{
		for (auto window : windows)
		{
			window->Render();
		}
	}

	void ImWindowManager::UpdateAllWindowsDockspace(KE::ImGuiManager& imguiManager)
	{
		for (auto window : windows)
		{
			const char* name = window->properties.name.c_str();

			switch (window->properties.dockSide)
			{
			case DockSide::LEFT_TOP:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_left_top);
				break;
			case DockSide::LEFT_BOTTOM:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_left_bottom);
				break;
			case DockSide::RIGHT:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_right);
				break;
			case DockSide::DOWN:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_down);
				break;
			case DockSide::MAIN:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_main);
				break;
			default:
				break;
			}
		}
	}

	void ImWindowManager::SetWindowVisible(const std::string& windowName, bool visible)
	{
		auto it = windowsMap.find(windowName);
		if (it != windowsMap.end())
		{
			it->second->properties.isVisible = visible;
			it->second->properties.isInitialized = false;
		}
	}
}
