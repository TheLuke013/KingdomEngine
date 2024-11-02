#include "KingdomEditor/EditorInterface/EditorInterface.h"

namespace Editor
{
	EditorInterface::EditorInterface(const std::string& name, float xPos, float yPos, float xSize, float ySize, bool collapsed, DockSide dockSide)
	{
		position = ImVec2(xPos, yPos);
		size = ImVec2(xSize, ySize);
		this->collapsed = collapsed;
		this->name = name;
		this->dockSide = dockSide;

		isInitialized = false;

		REGISTER_EDITOR_INTERFACE(this);
	}

	EditorInterface::~EditorInterface()
	{
	}

	void EditorInterface::Render()
	{
		///on the first render
		if (!isInitialized)
		{
			ImGui::SetNextWindowPos(position);
			ImGui::SetNextWindowSize(size);
			isInitialized = true;
		}

		ImGui::Begin(name.c_str(), &collapsed);
		OnRender();
		ImGui::End();
	}

	EditorInterfaceManager& EditorInterfaceManager::Get()
	{
		static EditorInterfaceManager* instance = new EditorInterfaceManager();
		return *instance;
	}

	void EditorInterfaceManager::Register(EditorInterface* interface)
	{
		interfaces.push_back(interface);
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
			const char* name = interface->GetName().c_str();

			switch (interface->GetDockSide())
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
}