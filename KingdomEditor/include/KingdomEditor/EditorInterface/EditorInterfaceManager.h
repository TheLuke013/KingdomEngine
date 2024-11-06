#ifndef EDITOR_INTERFACE_MANAGER_H
#define EDITOR_INTERFACE_MANAGER_H

#include "KingdomEditor/EditorInterface/EditorInterface.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace Editor
{
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
