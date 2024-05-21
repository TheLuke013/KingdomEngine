#include "KingdomEngine/Platform/Windows/Window.h"
#include "KingdomEngine/Core/Log.h"
#include "KingdomEngine/Core/Event.h"

namespace KE
{
	void Window::FramebufferResizeCallback(GLFWwindow* window, int framebufferWidth, int framebufferHeight)
	{
		glViewport(0, 0, framebufferWidth, framebufferHeight);
	}

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
		if (window)
		{
			glfwDestroyWindow(window);
		}
		glfwTerminate();
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

		glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);

		glfwMakeContextCurrent(window);

		if (gladLoadGL() == 0)
		{
			LOG_FATAL("Failed to initialize GLAD");
		}
		else
		{
			LOG_INFO("Initialized GLAD");
		}

		glEnable(GL_DEPTH_TEST);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::Clear()
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}
}