#include "KingdomEngine/Core/Application.h"

namespace KE
{
	Application::Application()
	{

	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		OnReady();

		while (isRunning)
		{
			Update();
		}
	}
}