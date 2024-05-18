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

		window.Create(3, 3);

		OnReady();

		while (isRunning)
		{
			while (!glfwWindowShouldClose(window.Get()))
			{
				window.Update();

				Update();

				window.Clear();
				window.SwapBuffers();
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