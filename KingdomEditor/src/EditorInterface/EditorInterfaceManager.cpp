#include "KingdomEditor/EditorInterface/EditorInterfaceManager.h"

namespace Editor
{
	EditorInterfaceManager& EditorInterfaceManager::Get()
	{
		static EditorInterfaceManager* instance = new EditorInterfaceManager();
		return *instance;
	}

	void EditorInterfaceManager::Register(EditorInterface* interface_)
	{
		interfaces.push_back(interface_);
		interfaceMap[interface_->properties.name] = interface_;
	}

	void EditorInterfaceManager::UpdateInterfaces()
	{
		for (auto interface : interfaces)
		{
			interface->Render();
		}
	}

	void EditorInterfaceManager::UpdateInterfacesDockspace(KE::ImGuiManager& imguiManager)
	{
		for (auto interface : interfaces)
		{
			const char* name = interface->properties.name.c_str();

			switch (interface->properties.dockSide)
			{
			case LEFT_TOP:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_left_top);
				break;
			case LEFT_BOTTOM:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_left_bottom);
				break;
			case RIGHT:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_right);
				break;
			case DOWN:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_down);
				break;
			case MAIN:
				ImGui::DockBuilderDockWindow(name, imguiManager.GetDockSides().dock_main);
				break;
			default:
				break;
			}
		}
	}

	void EditorInterfaceManager::SetEIVisible(const std::string& eiName, bool visible)
	{
		auto it = interfaceMap.find(eiName);
		if (it != interfaceMap.end())
		{
			it->second->properties.isVisible = visible;
		}
	}
}