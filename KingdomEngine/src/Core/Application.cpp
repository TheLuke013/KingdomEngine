#include "KingdomEngine/Core/Application.h"

namespace KE
{
	Application::Application()
	{
		isRunning = true;

		REGISTER_EVENT_LISTENER(this);

		window.Create();

		context.Init();

		ActivateImGui();
	}

	Application::~Application()
	{

	}

	//IMGUI
	void Application::ActivateImGui()
	{
		imguiManager.Init(window.Get());
	}

	void Application::DisableImGui()
	{
		imguiManager.Disable();
	}

	void Application::Run()
	{
		OnReady();

		while (isRunning && !window.IsClosed())
		{
			imguiManager.CreateNewFrame();

			context.Clear();

			OnUpdate();

			imguiManager.Render();

			window.Update();
		}
	}

	void Application::Quit()
	{
		isRunning = false;
	}

	void Application::_OnEvent(Event e)
	{
		OnEvent(e);

		if (e.type_ == CLOSE_APPLICATION)
		{
			Quit();
		}
	}
}