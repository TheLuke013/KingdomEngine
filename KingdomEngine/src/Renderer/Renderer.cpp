#include "KingdomEngine/Renderer/Renderer.h"
#include "KingdomEngine/Core/Log.h"
#include "KingdomEngine/Core/Event.h"
#include "KingdomEngine/ImGui/ImWindowManager.h"

#include <iostream>

namespace KE
{
	OpenGLVersion Renderer::version;
	SDL_GLContext Renderer::glContext;
	ImVec4 Renderer::clearColor;

	void Renderer::Init()
	{
		//INIT SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			LOG_FATAL("Failed to initialize SDL");
		}
		else
		{
			LOG_INFO("Initialized SDL");
		}

		//SET GL ATTRIBUTES
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version.majorVersion);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, version.minorVersion);

		clearColor = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
	}

	void Renderer::SetContext(SDL_Window* window)
	{
        glContext = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, glContext);
        SDL_GL_SetSwapInterval(1); // VSync
	}

	void Renderer::InitGL()
	{
	    //INIT GLEW
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

	void Renderer::CheckOpenGLVersion(SDL_Window* window)
	{
        int major = version.majorVersion;
	    int minor = version.minorVersion;
        const char* version = (const char*)glGetString(GL_VERSION);

        int currentMajor, currentMinor;
        sscanf(version, "%d.%d", &currentMajor, &currentMinor);

        if (!(currentMajor > major || (currentMajor == major && currentMinor >= minor)))
        {
            LOG_FATAL("Incompatible OpenGL version");
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Incompatible OpenGL Version",
                                 "Your system does not support the required OpenGL version. Please update your drivers or use a compatible system.",
                                 window);
            SET_IM_WINDOW_VISIBLE("Configuration", false);
            DISPATCH_EVENT(EventType::LOAD_OPENGL2);
        }
    }

	void Renderer::Clear()
	{
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
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
