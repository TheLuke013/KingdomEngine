#ifndef IM_MENU_MANAGER_H
#define IM_MENU_MANAGER_H

#include "KingdomEngine/ImGui/ImMenu.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace KE
{
    class ImMenuManager
    {
        public:
        static ImMenuManager& Get();

		void Register(ImMenu* imWMenu_);
		void UpdateAllMenus();
		void SetMenuEnable(const std::string& menuName, bool enabled);

        private:
        ImMenuManager() {}

		std::vector<ImMenu*> menus;
		std::unordered_map<std::string, ImMenu*> menusMap;
    };
}

#define UPDATE_ALL_IM_MENU() KE::ImMenuManager::Get().UpdateAllMenus();
#define REGISTER_IM_MENU(imMenu_) KE::ImMenuManager::Get().Register(imMenu_);
#define SET_IM_MENU_ENABLE(menuName, visible) KE::ImMenuManager::Get().SetMenuEnable(menuName, visible);

#endif