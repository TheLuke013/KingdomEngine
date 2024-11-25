#ifndef IMGUI_THEME_H
#define IMGUI_THEME_H

#include <ImGui/imgui.h>

namespace KE
{
    enum Theme
    {
        DEFAULT,
        DARK,
        LIGHT
    };

    class ImGuiTheme
    {
    public:
        ImGuiTheme(Theme theme);
        ~ImGuiTheme();

        void SetDefaultTheme();
        void SetDarkTheme();
        void SetLightTheme();

        void SetTheme(Theme theme);
        Theme GetTheme() { return theme; }

    private:
        Theme theme;

    };
}

#endif
