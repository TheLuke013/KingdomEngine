#include "KingdomEngine/Platform/Windows/Window.h"
#include "KingdomEngine/Core/Log.h"
#include "KingdomEngine/Core/Event.h"

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
		glfwSetErrorCallback(Window::ErrorCallback);

		//INIT GLFW
		if (!glfwInit())
		{
			LOG_FATAL("Failed to initialize GLFW");
			return false;
		}
		else
		{
			LOG_INFO("Initialized GLFW");
		}

		//SET WINDOW HINTS
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLContext::version.majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLContext::version.minorVersion);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		//CREATE WINDOW
		window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, NULL);

		if (window == NULL)
		{
			glfwTerminate();
			LOG_FATAL("Failed to create window");
			return false;
		}
		else
		{
			LOG_INFO("Window created");
		}

		if (properties.isMaximized)
		{
			glfwMaximizeWindow(window);
		}

		glfwSetFramebufferSizeCallback(window, OpenGLContext::FramebufferResizeCallback);
		glfwMakeContextCurrent(window);

		return true;
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

	void Window::ErrorCallback(int error, const char* description)
	{
		std::stringstream errorMsg;
		errorMsg << "GLFW Error: " << error << " - " << description;
		LOG_FATAL(errorMsg.str());

	}
}