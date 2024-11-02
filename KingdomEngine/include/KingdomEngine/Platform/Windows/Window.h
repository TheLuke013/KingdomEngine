#ifndef WINDOW_H
#define WINDOW_H

#include "KingdomEngine/Renderer/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <string>

namespace KE
{
	struct WindowProperties
	{
		std::string title = "Kingdom Engine";
		int width = 1024, height = 600;
		int framebufferWidth = 0, framebufferHeight = 0;
		bool isMaximized = false;
	};

	class Window
	{
	public:
		Window();
		Window(const std::string& title, int width, int height, bool maximized);
		~Window();

		void Create();
		void Update();
		void Destroy();

		bool IsClosed() { return glfwWindowShouldClose(window); }


		GLFWwindow* Get() const { return window; }
		WindowProperties& GetProper() { return properties; }

	private:
		WindowProperties properties;
		GLFWwindow* window;

	};
}

#endif
