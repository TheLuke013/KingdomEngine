#include "KingdomEngine/Renderer/Renderer.h"
#include "KingdomEngine/Core/Log.h"
#include "KingdomEngine/Core/Event.h"

#include <iostream>
#include <ImGui/imgui.h>

namespace KE
{
	OpenGLVersion Renderer::version;
	SDL_GLContext Renderer::glContext;
	ClearColor Renderer::clearColor;

	void Renderer::Init()
	{
		// INIT SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			LOG_FATAL("Failed to initialize SDL");
		}
		else
		{
			LOG_INFO("Initialized SDL");
		}

		// SET GL ATTRIBUTES
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version.majorVersion);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version.minorVersion);
	}

	void Renderer::SetContext(SDL_Window *window)
	{
		glContext = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, glContext);
		SDL_GL_SetSwapInterval(1); // VSync
	}

	void Renderer::InitGL()
	{
		// INIT GLEW
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			LOG_FATAL("Failed to initialize GLEW");
			std::cout << glewGetErrorString(err) << std::endl;
		}
		else
		{
			LOG_INFO("Initialized GLEW");
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::CheckOpenGLVersion(SDL_Window *window)
	{
		int major = version.majorVersion;
		int minor = version.minorVersion;
		const char *version = (const char *)glGetString(GL_VERSION);

		int currentMajor, currentMinor;
		sscanf(version, "%d.%d", &currentMajor, &currentMinor);

		if (!(currentMajor > major || (currentMajor == major && currentMinor >= minor)))
		{
			LOG_FATAL("Incompatible OpenGL version");
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
									 "Incompatible OpenGL Version",
									 "Your system does not support the required OpenGL version. Please update your drivers or use a compatible system.",
									 window);
			DISPATCH_EVENT(EventType::LOAD_OPENGL2);
		}
	}

	void Renderer::Clear(int width, int height)
	{
		float red = clearColor.r / 255.0f;
		float green = clearColor.g / 255.0f;
		float blue = clearColor.b / 255.0f;

		glViewport(0, 0, width, height);
		glClearColor(red, green, blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::SetGLVersion(GLVersion version_)
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
