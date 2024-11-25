#ifndef IM_MENU_H
#define IM_MENU_H

#include <string>

#include <ImGui/imgui.h>

namespace KE
{
    struct ImMenuProperties
    {
        std::string label;
        bool isEnabled;
    };

    class ImMenu
    {
    public:
        ImMenu(const std::string &label, bool enabled);
        virtual ~ImMenu();

        virtual void OnRender() = 0;

        void Render();
        bool Item(const char* label, const char* shortcut = (const char *)0);
        void Separate();

        ImMenuProperties properties;
    };
}

#endif