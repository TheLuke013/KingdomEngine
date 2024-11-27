#ifndef WINDOW_H
#define WINDOW_H

#include "KingdomEngine/Renderer/Renderer.h"

#include <string>

namespace KE
{
	struct WindowProperties
	{
		std::string title = "Kingdom Engine";
		int width = 1024, height = 600;
		bool isMaximized = false;
		SDL_WindowFlags flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	};

	class Window
	{
	public:
		Window();
		Window(const std::string& title, int width, int height, bool maximized);
		~Window();

		bool Create();
		void Destroy();
		void Update();
		void SetTitle(const std::string& title);

		SDL_Window* Get() { return window; }

		WindowProperties properties;

	private:
		SDL_Window* window;

	};
}

#endif
