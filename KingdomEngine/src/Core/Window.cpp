#include "KingdomEngine/Core/Window.h"
#include "KingdomEngine/Core/Log.h"
#include "KingdomEngine/Core/Event.h"
#include "KingdomEngine/ImGui/ImGuiManager.h"

#include <ImGui/imgui_impl_sdl2.h>

#include <sstream>

namespace KE
{
	Window::Window()
		: window(nullptr)
	{

	}

	Window::Window(const std::string& title, int width, int height, bool maximized)
		: window(nullptr)
	{
		properties.title = title;
		properties.width = width;
		properties.height = height;
		properties.isMaximized = maximized;
	}

	Window::~Window()
	{
		Destroy();
	}

	bool Window::Create()
	{
		//CREATE WINDOW
		window = SDL_CreateWindow(
			properties.title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			properties.width,
			properties.height,
			properties.flags);

		if (window == NULL)
		{
			Destroy();
			LOG_FATAL("Failed to create window");
			return false;
		}
		else
		{
			LOG_INFO("Window created");
		}

		if (properties.isMaximized)
		{
			SDL_MaximizeWindow(window);
		}

		return true;
	}

	void Window::Update()
	{
		//Update window events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (ImGuiManager::Get().IsEnabled())
				ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				DISPATCH_EVENT(EventType::CLOSE_APPLICATION);
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				DISPATCH_EVENT(EventType::CLOSE_APPLICATION);
		}
		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
		{
			SDL_Delay(10);
		}

		SDL_GL_SwapWindow(window);

		//update window size properties
		SDL_GetWindowSize(window, &properties.width, &properties.height);
	}

	void Window::Destroy()
	{
		if (window)
		{
			SDL_GL_DeleteContext(Renderer::GetContext());
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
	}

	void Window::SetTitle(const std::string& title)
	{
	    SDL_SetWindowTitle(window, title.c_str());
	}
}
