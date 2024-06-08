#include <KingdomEngine/KingdomEngine.h>

class EditorApplication : public KE::Application
{
public:
	EditorApplication()
		: sprite(nullptr), spritePos(glm::vec2(0.0f, 0.0f))
	{

	}

	~EditorApplication()
	{

	}

	void OnReady() override
	{
		shader.LoadShaders("../resources/shaders/sprite.vert", "../resources/shaders/sprite.frag");
		sprite = new KE::Sprite("../resources/textures/TheLuke.png", shader);
	}

	void OnUpdate() override
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

		sprite->Draw();
	}

	void OnEvent(KE::Event e) override
	{

	}

	void OnImGuiRender() override
	{
		//ImGui::ShowDemoWindow();

		ImGui::Begin("Content Browser");
		ImGui::End();

		ImGui::Begin("Game Objects");
		ImGui::End();

		ImGui::Begin("Details Panel");
		ImGui::End();

		ImGui::Begin("Console");
		ImGui::End();
	}

	void OnMenuBarRender() override
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

private:
	KE::Shader shader;
	KE::Sprite* sprite;
	glm::vec2 spritePos;
};

KE::Application* KE::CreateApplication()
{
	return new EditorApplication();
}