#include "KingdomEditor/EditorApplication.h"

namespace Editor
{
	EditorApplication::EditorApplication()
	{
		
	}

	EditorApplication::~EditorApplication()
	{

	}

	void EditorApplication::OnReady()
	{
		KE::FontManager::Get().FindFonts("..\\resources\\fonts", ".ttf");
	}

	void EditorApplication::OnUpdate()
	{
		
	}

	void EditorApplication::OnEvent(KE::Event e)
	{
		
	}

	void EditorApplication::OnImGuiRender()
	{
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