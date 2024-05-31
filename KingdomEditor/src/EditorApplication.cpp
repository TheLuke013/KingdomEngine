#include <KingdomEngine/KingdomEngine.h>

class EditorApplication : public KE::Application
{
public:
	KE::Shader shader;
	KE::Sprite* sprite;

	EditorApplication()
		: sprite(nullptr)
	{

	}

	~EditorApplication()
	{

	}

	void OnReady() override
	{
		shader.LoadShaders("../resources/shaders/sprite.vert", "../resources/shaders/sprite.frag");
		sprite = new KE::Sprite("../resources/textures/013.png", shader);
	}

	void Update() override
	{
		sprite->Draw();
	}

	void OnEvent(KE::Event e) override
	{

	}
};

KE::Application* KE::CreateApplication()
{
	return new EditorApplication();
}