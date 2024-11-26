#include "KingdomEditor/EditorApplication.h"

namespace Editor
{
	EditorApplication::EditorApplication()
        : defaultFont(nullptr)
	{
        //Search fonts and load default font
        KE::FontManager::Get().FindFonts("..\\resources\\fonts", ".ttf");

        for (const auto& font : KE::FontManager::Get().GetFonts())
        {
            if (font->properties.filePath == "..\\resources\\fonts\\Roboto-Regular.ttf")
            {
                font->properties.name = "Default";
                KE::ImGuiManager::Get().LoadFont(font);
            }
            else if (font->properties.filePath == "..\\resources\\fonts\\Roboto-Bold.ttf")
            {
                font->properties.name = "Default Bold";;
            }
        }
	}

	EditorApplication::~EditorApplication()
	{

	}

	void EditorApplication::OnReady()
	{
        ONREADY_ALL_IM_WINDOW();
	}

	void EditorApplication::OnUpdate()
	{

	}

	void EditorApplication::OnEvent(KE::Event e)
	{

	}

	void EditorApplication::OnImGuiRender()
	{
	    //ImGui::ShowMetricsWindow();
		//ImGui::ShowDemoWindow();
		UPDATE_ALL_IM_WINDOW();
	}

	void EditorApplication::OnMenuBarRender()
	{
        UPDATE_ALL_IM_MENU();
	}

	void EditorApplication::OnDockspaceUpdate()
	{
		UPDATE_ALL_IM_WINDOW_DOCKSPACE(KE::ImGuiManager::Get());
	}
}

KE::Application* KE::CreateApplication()
{
	return new Editor::EditorApplication();
}
