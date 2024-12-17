#include "KingdomEngine/Core/Application.h"

namespace KE
{
	Application::Application(bool isGameApplication)
		: imguiManager(ImGuiManager::Get())
	{
	    LOG_INFO(isGameApplication);
		isRunning = true;
		Application::isGameApplication = isGameApplication;

		REGISTER_EVENT_LISTENER(&appEvent);	
		REGISTER_EVENT_LISTENER(&imguiEvent);
		
		Renderer::Init();
		CreateMainWindow();
	}

	Application::~Application()
	{
	}

	// IMGUI
	void Application::ActivateImGui()
	{
		imguiManager.Setup(window.Get(), true);
		imguiManager.Enable();
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

        sprite.LoadTexture(Core::RESOURCES_DIR + "\\empty.png");
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
		OnEvent(appEvent.eventType);
		
		switch (appEvent.eventType)
		{
		case EventType::LoadGL3:
			DisableApplication();
			Renderer::SetGLVersion(OpenGL3);
			CreateMainWindow();
			if (window.Get() != nullptr)
			{
				ActivateImGui();
			}
			appEvent.eventType = EventType::None;
			break;
		case EventType::LoadGL2:
			DisableApplication();
			Renderer::SetGLVersion(OpenGL2);
			CreateMainWindow();
			if (window.Get() != nullptr)
			{
				ActivateImGui();
			}
			appEvent.eventType = EventType::None;
			break;
        case EventType::WindowClose:
			if (!imguiManager.IsEnabled())
                Quit();
			appEvent.eventType = EventType::None;
			break;
		default:
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
			{
				Renderer::GetFramebuffer().Draw(window.properties.width, window.properties.height);
				sprite.Draw();
			}

			window.Update();
			
			PROCESS_ALL_EVENTS();
			EventHandle();
		}
	}

	void Application::Quit()
	{
		isRunning = false;
	}
}
