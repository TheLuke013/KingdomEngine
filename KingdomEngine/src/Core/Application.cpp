#include "KingdomEngine/Core/Application.h"

namespace KE
{
	Application::Application(bool isGameApplication)
		: imguiManager(ImGuiManager::Get()), ev(EventType::NONE)
	{
	    LOG_INFO(isGameApplication);
		isRunning = true;
		eventHandling = false;
		handlingGLEvent = false;
		this->isGameApplication = isGameApplication;

		REGISTER_EVENT_LISTENER(this);

		Renderer::Init();

		CreateMainWindow();
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

	void Application::CreateMainWindow()
	{
	    if (isGameApplication)
        {
            OS::SetCurrentDir(OS::GetCurrentDir() + "\\..");
        }
        else
        {
            window.properties.isMaximized = true;
        }

		if (!window.Create())
		{
			Quit();
		}

		//configure renderer
		Renderer::SetContext(window.Get());
		Renderer::InitGL();
        Renderer::CheckOpenGLVersion(window.Get());
        Renderer::GetFramebuffer().Create(window.properties.width, window.properties.height);

        //load shaders
        if (Renderer::GetVersion().glVersion == GLVersion::OpenGL2)
        {
            Renderer::GetDefaultShader().LoadShaders(Core::SHADERS_GL2 + "\\sprite.vert", Core::SHADERS_GL2 + "\\sprite.frag");
        }
        else if (Renderer::GetVersion().glVersion == GLVersion::OpenGL3)
        {
            Renderer::GetDefaultShader().LoadShaders(Core::SHADERS_GL3 + "\\sprite.vert", Core::SHADERS_GL3 + "\\sprite.frag");
        }

        sprite.LoadTexture("");
	}

	void Application::DisableApplication()
	{
	    sprite.Delete();
		DisableImGui();
		Renderer::GetFramebuffer().Delete();
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
        case EventType::CLOSE_APPLICATION:
			if (!imguiManager.IsEnabled())
                Quit();
			eventHandling = false;
			break;
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
			CreateMainWindow();
			if (window.Get() != nullptr)
			{
				ActivateImGui();
			}
			handlingGLEvent = false;
			break;
		case EventType::LOAD_OPENGL2:
			DisableApplication();
			Renderer::SetGLVersion(OpenGL2);
			CreateMainWindow();
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

			Renderer::GetFramebuffer().Bind();
			Renderer::Clear(window.properties.width, window.properties.height);
			OnUpdate();
			Renderer::GetFramebuffer().Unbind();

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
				OnImGuiRender();

            imguiManager.Render();

            if (!imguiManager.IsEnabled())
                Renderer::GetFramebuffer().Draw(window.properties.width, window.properties.height);

			window.Update();

			if (eventHandling)
				EventHandle();

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
