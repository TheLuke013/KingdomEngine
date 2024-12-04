#include "KingdomEngine/Core/Application.h"

namespace KE
{
	Application::Application()
		: imguiManager(ImGuiManager::Get()), ev(EventType::NONE)
	{
		isRunning = true;
		eventHandling = false;
		handlingGLEvent = false;

		REGISTER_EVENT_LISTENER(this);

		Renderer::Init();
		CreateWindowMaximized();
	}

	Application::~Application()
	{
	}

	// IMGUI
	void Application::ActivateImGui()
	{
		imguiManager.Init(window.Get(), true);
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

	void Application::EventHandle()
	{
		if (ev.type_ == EventType::LOAD_OPENGL2 || ev.type_ == EventType::LOAD_OPENGL3)
		{
			handlingGLEvent = true;
			eventHandling = false;
			return;
		}

		switch (ev.type_)
		{
		case EventType::RESTART_IMGUI:
			imguiManager.Restart();
			eventHandling = false;
			break;
		case EventType::ACTIVE_IMGUI:
			ActivateImGui();
			eventHandling = false;
			break;
		case EventType::DISABLE_IMGUI:
			DisableImGui();
			eventHandling = false;
			break;
		case EventType::ACTIVE_DOCKSPACE:
			imguiManager.EnableDockspace();
			eventHandling = false;
			break;
		case EventType::DISABLE_DOCKSPACE:
			imguiManager.DisableDockspace();
			eventHandling = false;
			break;
		default:
			eventHandling = false;
			break;
		}
	}

	void Application::GLEventHandle()
	{
		switch (ev.type_)
		{
		case EventType::LOAD_OPENGL3:
			DisableApplication();
			Renderer::SetGLVersion(OpenGL3);
			CreateWindowMaximized();
			if (window.Get() != nullptr)
			{
				ActivateImGui();
			}
			handlingGLEvent = false;
			break;
		case EventType::LOAD_OPENGL2:
			DisableApplication();
			Renderer::SetGLVersion(OpenGL2);
			CreateWindowMaximized();
			if (window.Get() != nullptr)
			{
				ActivateImGui();
			}
			handlingGLEvent = false;
			break;
		default:
			handlingGLEvent = false;
			break;
		}
	}

	void Application::Run()
	{
		OnReady();

		while (isRunning)
		{
			imguiManager.CreateNewFrame();

			// IMGUI DOCKSPACE
			imguiManager.BeginDockspace();
			if (imguiManager.IsEnabled())
			{
				OnDockspaceUpdate();
				OnMenuBarRender();
			}
			imguiManager.EndDockspace();

			// render client-application imgui
			if (imguiManager.IsEnabled())
			{
				OnImGuiRender();
			}

			if (eventHandling)
				EventHandle();

			Renderer::Clear(window.properties.width, window.properties.height);
			OnUpdate();
			imguiManager.Render();
			window.Update();

			if (handlingGLEvent)
				GLEventHandle();
		}
	}

	void Application::Quit()
	{
		isRunning = false;
	}

	void Application::_OnEvent(Event e)
	{
		OnEvent(e);
		ev = e;
		eventHandling = true;
	}
}
