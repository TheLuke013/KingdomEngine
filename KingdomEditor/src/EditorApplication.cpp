#include "KingdomEditor/EditorApplication.h"

namespace Editor
{
	EditorApplication::EditorApplication()
        : defaultFont(nullptr)
	{
        //Load default font
        KE::File defaultFontFile;
        if (defaultFontFile.Open("..\\resources\\fonts\\Roboto-Regular.ttf", std::ios::in))
        {
            defaultFont = new KE::Font("Default", "..\\resources\\fonts\\Roboto-Regular.ttf", 16.f);
            ADD_FONT(defaultFont);
            KE::ImGuiManager::Get().LoadFont(defaultFont);
        }
        defaultFontFile.Close();

	    //Search for other fonts
	    KE::FontManager::Get().FindFonts("..\\resources\\fonts", ".ttf");
	}

	EditorApplication::~EditorApplication()
	{

	}

	void EditorApplication::OnReady()
	{
        ONREADY_ALL_IM_WINDOW()
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
		if (ImGui::BeginMenuBar())
		{
			//FILE
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Config")) { SET_IM_WINDOW_VISIBLE("Configuration", true); }

				ImGui::Separator();

				if (ImGui::MenuItem("Exit", "Alt+F4")) { Quit(); }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
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
