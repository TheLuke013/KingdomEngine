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
		REGISTER_EVENT_LISTENER(this);

		window.Create();

		OnReady();

		while (isRunning)
		{
			while (!glfwWindowShouldClose(window.Get()))
			{
				window.Clear();

				Update();

				window.SwapBuffers();
				window.PollEvents();
			}
			
			if (glfwWindowShouldClose(window.Get()))
			{
				isRunning = false;
			}
		}
	}

	void Application::_OnEvent(Event e)
	{
		OnEvent(e);

		if (e.type_ == CLOSE_APPLICATION)
		{
			isRunning = false;
		}
	}
}