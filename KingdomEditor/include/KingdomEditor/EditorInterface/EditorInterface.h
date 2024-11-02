#ifndef EDITOR_INTERFACE_H
#define EDITOR_INTERFACE_H

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <KingdomEngine/ImGui/ImGuiManager.h>

#include <string>
#include <vector>

namespace Editor
{
	enum DockSide
	{
		NONE,
		MAIN,
		LEFT,
		RIGHT,
		DOWN,
		LEFT_TOP,
		LEFT_BOTTOM
	};

	class EditorInterface
	{
	public:
		EditorInterface(const std::string& name, float xPos, float yPos, float xSize, float ySize, bool collapsed, DockSide dockSide = NONE);
		virtual ~EditorInterface();

		void Render();
		DockSide& GetDockSide() { return dockSide; }
		std::string& GetName() { return name; }

		virtual void OnRender() = 0;

	private:
		ImVec2 position;
		ImVec2 size;
		DockSide dockSide;
		bool collapsed;
		bool isInitialized;
		std::string name;
	};

	class EditorInterfaceManager
	{
	public:
		static EditorInterfaceManager& Get();

		void Register(EditorInterface* interface);
		void UpdateInterfaces();
		void UpdateInterfacesDockspace(KE::ImGuiManager& imguiManager);

	private:
		EditorInterfaceManager() {}

		std::vector<EditorInterface*> interfaces;
	};
}

#define UPDATE_EDITOR_INTERFACES() Editor::EditorInterfaceManager::Get().UpdateInterfaces();
#define UPDATE_EI_DOCKSPACE(imguiManager) Editor::EditorInterfaceManager::Get().UpdateInterfacesDockspace(imguiManager);
#define REGISTER_EDITOR_INTERFACE(interface_) Editor::EditorInterfaceManager::Get().Register(interface_);

#endif
