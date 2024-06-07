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
		sprite = new KE::Sprite("../resources/textures/013.png", shader);
		sprite->SetPosition(0, 1);
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

		if (glfwGetKey(GetWindow().Get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			Quit();
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

private:
	KE::Shader shader;
	KE::Sprite* sprite;
	glm::vec2 spritePos;
};

KE::Application* KE::CreateApplication()
{
	return new EditorApplication();
}