#include "KingdomEngine/Renderer/OpenGL/OpenGLContext.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
	OpenGLVersion OpenGLContext::version;

	void OpenGLContext::Init()
	{
		if (gladLoadGL() == 0)
		{
			LOG_FATAL("Failed to initialize GLAD");
		}
		else
		{
			LOG_INFO("Initialized GLAD");
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLContext::Clear()
	{
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLContext::FramebufferResizeCallback(GLFWwindow* window, int framebufferWidth, int framebufferHeight)
	{
		glViewport(0, 0, framebufferWidth, framebufferHeight);
	}

	void OpenGLContext::SetGLVersion(GLVersion version_)
	{
		if (version_ == OpenGL2)
		{
			version.glVersion = OpenGL2;
			version.minorVersion = 1;
			version.majorVersion = 2;
		}
		else if (version_ == OpenGL3)
		{
			version.glVersion = OpenGL3;
			version.minorVersion = 3;
			version.majorVersion = 3;
		}
	}
}