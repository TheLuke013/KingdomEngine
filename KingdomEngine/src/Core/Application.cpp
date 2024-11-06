#include "KingdomEngine/Core/Application.h"

namespace KE
{
	Application::Application()
		: imguiManager(ImGuiManager::Get())
	{
		isRunning = true;
		restartImGui = false;

		REGISTER_EVENT_LISTENER(this);

		window.GetProper().isMaximized = true;
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

			//IMGUI DOCKSPACE
			imguiManager.BeginDockspace();
			if (imguiManager.IsEnabled())
			{
				OnDockspaceUpdate();
				OnMenuBarRender();
			}
			imguiManager.EndDockspace();

			//render client-application imgui
			if (imguiManager.IsEnabled())
			{
				OnImGuiRender();
			}

			if (restartImGui)
			{
				imguiManager.Restart();
				restartImGui = false;
			}

			context.Clear();

			OnUpdate(); //updates client-application

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
		else if (e.type_ == LOAD_FONT)
		{
			restartImGui = true;
		}
	}
}