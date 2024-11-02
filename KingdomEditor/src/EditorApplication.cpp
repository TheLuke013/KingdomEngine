#include "KingdomEditor/EditorApplication.h"

namespace Editor
{
	EditorApplication::EditorApplication()
		: sprite(nullptr), spritePos(glm::vec2(0.0f, 0.0f))
	{
		
	}

	EditorApplication::~EditorApplication()
	{

	}

	void EditorApplication::OnReady()
	{
		shader.LoadShaders("../resources/shaders/gl2/sprite.vert", "../resources/shaders/gl2/sprite.frag");
		sprite = new KE::Sprite("../resources/textures/TheLuke.png", shader);
	}

	void EditorApplication::OnUpdate()
	{
		if (glfwGetKey(GetWindow().Get(), GLFW_KEY_A) == GLFW_PRESS)
		{
			spritePos.x -= 0.001f;
			sprite->SetPosition(spritePos.x, spritePos.y);
		}

		if (glfwGetKey(GetWindow().Get(), GLFW_KEY_D) == GLFW_PRESS)
		{
			spritePos.x += 0.001f;
			sprite->SetPosition(spritePos.x, spritePos.y);
		}

		if (glfwGetKey(GetWindow().Get(), GLFW_KEY_1) == GLFW_PRESS)
		{
			ActivateImGui();
		}

		if (glfwGetKey(GetWindow().Get(), GLFW_KEY_2) == GLFW_PRESS)
		{
			DisableImGui();
		}

		//sprite->Draw();
	}

	void EditorApplication::OnEvent(KE::Event e)
	{

	}

	void EditorApplication::OnImGuiRender()
	{
		UPDATE_EDITOR_INTERFACES();
	}

	void EditorApplication::OnMenuBarRender()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit", "Alt+F4")) { Quit(); }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}

	void EditorApplication::OnDockspaceUpdate()
	{
		UPDATE_EI_DOCKSPACE(GetImGuiManager());
	}
}

KE::Application* KE::CreateApplication()
{
	return new Editor::EditorApplication();
}