#include <KingdomEngine/KingdomEngine.h>

class EditorApplication : public KE::Application
{
public:
	EditorApplication()
	{

	}

	~EditorApplication()
	{

	}

	void OnReady() override
	{
		
	}

	void Update() override
	{

	}

	void OnEvent(KE::Event e) override
	{

	}
};

KE::Application* KE::CreateApplication()
{
	return new EditorApplication();
}