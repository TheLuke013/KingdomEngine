#include "KingdomEngine/ImGui/ImGuiTheme.h"

namespace KE
{
    ImGuiTheme::ImGuiTheme(Theme theme)
    {
        SetTheme(theme);
    }

    ImGuiTheme::~ImGuiTheme()
    {

    }

    void ImGuiTheme::SetDefaultTheme()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        colors[ImGuiCol_WindowBg]           = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
        colors[ImGuiCol_ChildBg]            = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);
        colors[ImGuiCol_PopupBg]            = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);

        colors[ImGuiCol_Border]             = ImVec4(0.30f, 0.30f, 0.30f, 0.8f);
        colors[ImGuiCol_BorderShadow]       = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

        colors[ImGuiCol_Header]             = ImVec4(0.33f, 0.33f, 0.33f, 0.8f);
        colors[ImGuiCol_HeaderHovered]      = ImVec4(0.40f, 0.40f, 0.40f, 0.9f);
        colors[ImGuiCol_HeaderActive]       = ImVec4(0.48f, 0.48f, 0.48f, 1.0f);

        colors[ImGuiCol_Button]             = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
        colors[ImGuiCol_ButtonHovered]      = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
        colors[ImGuiCol_ButtonActive]       = ImVec4(0.40f, 0.40f, 0.40f, 1.0f);

        colors[ImGuiCol_ScrollbarBg]        = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
        colors[ImGuiCol_ScrollbarGrab]      = ImVec4(0.28f, 0.28f, 0.28f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.50f, 0.50f, 0.50f, 1.0f);

        colors[ImGuiCol_TitleBg]            = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
        colors[ImGuiCol_TitleBgActive]      = ImVec4(0.22f, 0.22f, 0.22f, 1.0f);
        colors[ImGuiCol_TitleBgCollapsed]   = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);

        colors[ImGuiCol_MenuBarBg]          = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);

        colors[ImGuiCol_Text]               = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
        colors[ImGuiCol_TextDisabled]       = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        colors[ImGuiCol_CheckMark]          = ImVec4(0.33f, 0.78f, 1.0f, 1.0f);
        colors[ImGuiCol_SliderGrab]         = ImVec4(0.33f, 0.78f, 1.0f, 1.0f);
        colors[ImGuiCol_SliderGrabActive]   = ImVec4(0.45f, 0.85f, 1.0f, 1.0f);

        colors[ImGuiCol_Separator]          = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
        colors[ImGuiCol_SeparatorHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 1.0f);
        colors[ImGuiCol_SeparatorActive]    = ImVec4(0.50f, 0.50f, 0.50f, 1.0f);

        colors[ImGuiCol_Tab]                = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
        colors[ImGuiCol_TabHovered]         = ImVec4(0.33f, 0.33f, 0.33f, 1.0f);
        colors[ImGuiCol_TabActive]          = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
        colors[ImGuiCol_TabUnfocused]       = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);

        colors[ImGuiCol_FrameBg]          = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
        colors[ImGuiCol_FrameBgHovered]   = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
        colors[ImGuiCol_FrameBgActive]    = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);

        colors[ImGuiCol_Text]             = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
        colors[ImGuiCol_TextDisabled]     = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        colors[ImGuiCol_Border]           = ImVec4(0.30f, 0.30f, 0.30f, 0.8f);
        colors[ImGuiCol_BorderShadow]     = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

        style.FrameRounding = 4.0f;
        style.GrabRounding = 4.0f;
    }

    void ImGuiTheme::SetDarkTheme()
    {
        ImGui::StyleColorsDark();
    }

    void ImGuiTheme::SetLightTheme()
    {
        ImGui::StyleColorsLight();
    }

    void ImGuiTheme::SetTheme(Theme theme)
    {
        switch (theme)
        {
        case Theme::DEFAULT:
            ImGuiTheme::theme = Theme::DEFAULT;
            break;
        case Theme::DARK:
            ImGuiTheme::theme = Theme::DARK;
            break;
        case Theme::LIGHT:
            ImGuiTheme::theme = Theme::LIGHT;
            break;
        }
    }
}
