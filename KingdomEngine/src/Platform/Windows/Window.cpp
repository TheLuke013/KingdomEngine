#include "KingdomEngine/Platform/Windows/Window.h"
#include "KingdomEngine/Core/Log.h"
#include "KingdomEngine/Core/Event.h"

namespace KE
{
	Window::Window()
		: window(nullptr)
	{

	}

	Window::Window(const std::string& title, int width, int height)
		: window(nullptr)
	{
		properties.title = title;
		properties.width = width;
		properties.height = height;
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		//INIT GLFW
		if (!glfwInit())
		{
			LOG_FATAL("Failed to initialize GLFW");
			return;
		}
		else
		{
			LOG_INFO("Initialized GLFW");
		}

		//SET WINDOW HINTS
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		//CREATE WINDOW
		window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, NULL);

		if (window == NULL)
		{
			glfwTerminate();
			LOG_FATAL("Failed to create window");
		}
		else
		{
			LOG_INFO("Window created");
		}

		glfwSetFramebufferSizeCallback(window, OpenGLContext::FramebufferResizeCallback);

		glfwMakeContextCurrent(window);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);

		if (IsClosed())
		{
			DISPATCH_EVENT(CLOSE_APPLICATION);
		}
	}

	void Window::Destroy()
	{
		if (window)
		{
			glfwDestroyWindow(window);
		}
		glfwTerminate();
	}
}