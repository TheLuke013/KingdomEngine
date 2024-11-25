#include "KingdomEngine/ImGui/ImMenuManager.h"

namespace KE
{
	ImMenuManager &ImMenuManager::Get()
	{
		static ImMenuManager *instance = new ImMenuManager();
		return *instance;
	}

	void ImMenuManager::Register(ImMenu *imMenu_)
	{
		menus.push_back(imMenu_);
		menusMap[imMenu_->properties.label] = imMenu_;
	}

	void ImMenuManager::UpdateAllMenus()
	{
		if (ImGui::BeginMenuBar())
		{
			for (auto menu : menus)
			{
				menu->Render();
			}
			ImGui::EndMenuBar();
		}
	}

	void ImMenuManager::SetMenuEnable(const std::string &menuName, bool enabled)
	{
		auto it = menusMap.find(menuName);
		if (it != menusMap.end())
		{
			it->second->properties.isEnabled = enabled;
		}
	}
}