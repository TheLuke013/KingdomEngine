#include "KingdomEngine/Core/Application.h"

#ifdef _WIN32

extern KE::Application* KE::CreateApplication();

#ifdef GAME_APPLICATION

#include "KingdomEngine/Core/IO/File.h"
#include "KingdomEngine/Core/JSON.h"
#include "KingdomEngine/Renderer/Renderer.h"

int main(int argc, char** argv)
{
	KE::Log::Init("logs.txt");
	LOG_INFO("Engine initialized");
	
	//properties
	std::string windowTitle = "";
	std::string backgroundColor = "";
	int windowWidth = 0;
	int windowHeight = 0;
	int glVersion = 0;
	
	//search application arguments
	if (argc > 1)
	{
		for (int i = 0; i < argc; i++)
		{
			if (i == 1)
			{
				KE::File propertiesFile;
				KE::JSON propertiesJson;
				
				if (propertiesFile.Exists(argv[i]))
				{
					propertiesFile.Open(argv[i], KE::ModeFlags::READ);
					propertiesJson.Parse(propertiesFile.Read(), true);
					propertiesFile.Close();
					
					windowTitle = propertiesJson.GetValue<std::string>("project", "window_title", "Window Title");
					windowWidth = propertiesJson.GetValue<int>("project", "window_width", 1024);
					windowHeight = propertiesJson.GetValue<int>("project", "window_height", 600);
					glVersion = propertiesJson.GetValue<int>("project", "gl_version", 1);
					backgroundColor = propertiesJson.GetValue<std::string>("project", "background_color", "#000000");
				}
				else
				{
					LOG_FATAL("Properties file not found or does not exist");
				}
			}
		}
	}
	
	//set renderer properties
	KE::Renderer::GetVersion().glVersion = static_cast<KE::GLVersion>(glVersion);
	KE::Renderer::GetClearColor().FromHex(backgroundColor);

	auto app = KE::CreateApplication();
	
	//set window properties
	app->GetWindow().SetTitle(windowTitle);
	app->GetWindow().SetSize(windowWidth, windowHeight);
	
	//run application
	app->Run();
	delete app;

	return 0;
}
#else
int main(int argc, char** argv)
{
	KE::Log::Init("logs.txt");
	LOG_INFO("Engine initialized");

	auto app = KE::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
#endif

#endif
