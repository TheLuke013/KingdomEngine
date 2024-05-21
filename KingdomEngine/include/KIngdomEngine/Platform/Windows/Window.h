#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace KE
{
	struct WindowProperties
	{
		std::string title = "Kingdom Engine";
		int width = 1024, height = 600;
		int framebufferWidth = 0, framebufferHeight = 0;
	};

	class Window
	{
	private:
		static void FramebufferResizeCallback(GLFWwindow* window, int framebufferWidth, int framebufferHeight);

	public:
		Window();
		Window(const std::string& title, int width, int height);
		~Window();

		void Create(int glMajorVersion, int glMinorVersion);
		void PollEvents();
		void Clear();
		void SwapBuffers();


		GLFWwindow* Get() const { return window; }

	private:
		GLFWwindow* window;
		WindowProperties properties;

	};
}

#endif
