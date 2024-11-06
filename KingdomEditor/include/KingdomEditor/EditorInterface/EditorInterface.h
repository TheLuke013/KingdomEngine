#ifndef EDITOR_INTERFACE_H
#define EDITOR_INTERFACE_H

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <KingdomEngine/ImGui/ImGuiManager.h>

#include <string>
#include <vector>
#include <unordered_map>

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

	struct EditorInterfaceProperties
	{
		ImVec2 position;
		ImVec2 size;
		ImGuiWindowFlags flags;
		DockSide dockSide;
		bool isInitialized;
		bool isVisible;
		std::string name;
	};

	class EditorInterface
	{
	public:
		EditorInterface(const std::string& name, float xPos, float yPos, float xSize, float ySize, bool visible, DockSide dockSide = NONE);
		virtual ~EditorInterface();

		void Render();

		virtual void OnRender() = 0;

		EditorInterfaceProperties properties;

	};

	class EditorInterfaceManager
	{
	public:
		static EditorInterfaceManager& Get();

		void Register(EditorInterface* interface_);
		void UpdateInterfaces();
		void UpdateInterfacesDockspace(KE::ImGuiManager& imguiManager);
		void SetEIVisible(const std::string& eiName, bool visible);

	private:
		EditorInterfaceManager() {}

		std::vector<EditorInterface*> interfaces;
		std::unordered_map<std::string, EditorInterface*> interfaceMap;
	};
}

#define UPDATE_EDITOR_INTERFACES() Editor::EditorInterfaceManager::Get().UpdateInterfaces();
#define UPDATE_EI_DOCKSPACE(imguiManager) Editor::EditorInterfaceManager::Get().UpdateInterfacesDockspace(imguiManager);
#define REGISTER_EDITOR_INTERFACE(interface_) Editor::EditorInterfaceManager::Get().Register(interface_);
#define SET_EI_VISIBLE(eiName, visible) Editor::EditorInterfaceManager::Get().SetEIVisible(eiName, visible);

#endif
