#ifndef IM_WINDOW_MANAGER_H
#define IM_WINDOW_MANAGER_H

#include "KingdomEngine/ImGui/ImWindow.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace KE
{
	class ImWindowManager
	{
	public:
		static ImWindowManager& Get();

		void Register(ImWindow* imWindow_);
		void Remove(const std::string& windowName);
		void OnReadyAllWindows();
		void UpdateAllWindows();
		void UpdateAllWindowsDockspace(KE::ImGuiManager& imguiManager);
		void SetWindowVisible(const std::string& windowName, bool visible);
		bool GetWindowVisible(const std::string& windowName);

	private:
		ImWindowManager() {}

		std::vector<ImWindow*> windows;
		std::unordered_map<std::string, ImWindow*> windowsMap;
	};
}

#define ONREADY_ALL_IM_WINDOW() KE::ImWindowManager::Get().OnReadyAllWindows();
#define UPDATE_ALL_IM_WINDOW() KE::ImWindowManager::Get().UpdateAllWindows();
#define UPDATE_ALL_IM_WINDOW_DOCKSPACE(imguiManager) KE::ImWindowManager::Get().UpdateAllWindowsDockspace(imguiManager);
#define REGISTER_IM_WINDOW(imWindow_) KE::ImWindowManager::Get().Register(imWindow_);
#define REMOVE_IM_WINDOW(windowName) KE::ImWindowManager::Get().Remove(windowName);
#define SET_IM_WINDOW_VISIBLE(windowName, visible) KE::ImWindowManager::Get().SetWindowVisible(windowName, visible);
#define GET_IM_WINDOW_VISIBLE(windowName) KE::ImWindowManager::Get().GetWindowVisible(windowName);

#endif
