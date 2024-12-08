#include "KingdomEngine/Core/Application.h"

#ifdef _WIN32

extern KE::Application* KE::CreateApplication();

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
