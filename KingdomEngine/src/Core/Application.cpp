#include "KingdomEngine/Core/Application.h"

namespace KE
{
	Application::Application()
		: imguiManager(ImGuiManager::Get())
	{
		isRunning = true;
		restartImGui = false;
		loadGL2 = false;
		loadGL3 = false;

		REGISTER_EVENT_LISTENER(this);

		Renderer::Init();
		CreateWindowMaximized();
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

	void Application::CreateWindowMaximized()
	{
		window.properties.isMaximized = true;
		if (!window.Create())
        {
            Quit();
        }
		Renderer::SetContext(window.Get());
		Renderer::InitGL();
		Renderer::CheckOpenGLVersion(window.Get());
	}

	void Application::DisableApplication()
	{
		DisableImGui();
		window.Destroy();
	}

	void Application::Run()
	{
		OnReady();

		while (isRunning)
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

			//Resart ImGui
			if (restartImGui)
			{
				imguiManager.Restart();
				restartImGui = false;
			}

			Renderer::Clear();
			OnUpdate(); //updates client-application
			imguiManager.Render();
			window.Update();

			//Restart Application if OpenGL version was changed
			if (loadGL3)
			{
				DisableApplication();
				Renderer::SetGLVersion(OpenGL3);
				CreateWindowMaximized();
				if (window.Get() != nullptr) { ActivateImGui(); }
				loadGL3 = false;
			}
			else if (loadGL2)
			{
				DisableApplication();
				Renderer::SetGLVersion(OpenGL2);
				CreateWindowMaximized();
				if (window.Get() != nullptr) { ActivateImGui(); }
				loadGL2 = false;
			}
		}
	}

	void Application::Quit()
	{
		isRunning = false;
	}

	void Application::_OnEvent(Event e)
	{
		OnEvent(e);

		if (e.type_ == EventType::CLOSE_APPLICATION)
		{
			Quit();
		}
		else if (e.type_ == EventType::RESTART_IMGUI)
		{
			restartImGui = true;
		}
		else if (e.type_ == EventType::LOAD_OPENGL3)
		{
			loadGL3 = true;
			loadGL2 = false;
		}
		else if (e.type_ == EventType::LOAD_OPENGL2)
		{
			loadGL2 = true;
			loadGL3 = false;
		}
	}
}
