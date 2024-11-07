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
		if (glfwGetKey(GetWindow().Get(), GLFW_KEY_1) == GLFW_PRESS)
		{
			ActivateImGui();
		}

		if (glfwGetKey(GetWindow().Get(), GLFW_KEY_2) == GLFW_PRESS)
		{
			DisableImGui();
		}
	}

	void EditorApplication::OnEvent(KE::Event e)
	{
		
	}

	void EditorApplication::OnImGuiRender()
	{
		//ImGui::ShowDemoWindow();
		UPDATE_EDITOR_INTERFACES();
	}

	void EditorApplication::OnMenuBarRender()
	{
		if (ImGui::BeginMenuBar())
		{
			//FILE
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Config")) { SET_EI_VISIBLE("Configuration", true); }

				ImGui::Separator();

				if (ImGui::MenuItem("Exit", "Alt+F4")) { Quit(); }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}

	void EditorApplication::OnDockspaceUpdate()
	{
		UPDATE_EI_DOCKSPACE(KE::ImGuiManager::Get());
	}
}

KE::Application* KE::CreateApplication()
{
	return new Editor::EditorApplication();
}