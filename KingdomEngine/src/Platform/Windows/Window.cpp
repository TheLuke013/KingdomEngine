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

	void Window::Create(int glMajorVersion = 3, int glMinorVersion = 3)
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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVersion);
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
	}

	void Window::Update()
	{
		glfwPollEvents();
	}

	void Window::Clear()
	{
		glClearColor(1.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
		glFlush();
	}
}