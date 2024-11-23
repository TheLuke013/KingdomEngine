#include "KingdomEngine/Renderer/OpenGL/GLContext.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
	OpenGLVersion GLContext::version;
	SDL_GLContext GLContext::glContext;
	ImVec4 GLContext::clearColor;

	void GLContext::Init(SDL_Window* window)
	{
		clearColor = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
		glContext = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, glContext);
		SDL_GL_SetSwapInterval(1); // Enable vsync
	}

	void GLContext::Clear()
	{
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLContext::SetGLVersion(GLVersion version_)
	{
		if (version_ == OpenGL2)
		{
			version.glVersion = OpenGL2;
			version.minorVersion = 2;
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