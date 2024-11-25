#include "KingdomEngine/ImGui/ImMenu.h"
#include "KingdomEngine/ImGui/ImMenuManager.h"

namespace KE
{
    ImMenu::ImMenu(const std::string &label, bool enabled)
    {
        properties.label = label;
        properties.isEnabled = enabled;

        REGISTER_IM_MENU(this);
    }

    ImMenu::~ImMenu()
    {
    }

    void ImMenu::Render()
    {
        if (ImGui::BeginMenu(properties.label.c_str(), properties.isEnabled))
        {
            OnRender();
            ImGui::EndMenu();
        }
    }

    bool ImMenu::Item(const char *label, const char *shortcut)
    {
        return ImGui::MenuItem(label, shortcut);
    }

    void ImMenu::Separate()
    {
        ImGui::Separator();
    }
}