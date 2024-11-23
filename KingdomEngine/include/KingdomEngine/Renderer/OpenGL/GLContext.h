#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <ImGui/imgui.h>

namespace KE
{
	enum GLVersion
	{
		OpenGL3,
		OpenGL2
	};

	struct OpenGLVersion
	{
		int minorVersion = 2;
		int majorVersion = 2;
		GLVersion glVersion = OpenGL2;
	};

	class GLContext
	{
	public:
		static void Init(SDL_Window* window);
		static void Clear();

		static void SetGLVersion(GLVersion version_);
		static SDL_GLContext& GetContext() { return glContext; }
		static ImVec4& GetClearColor() { return clearColor; }
		static OpenGLVersion& GetVersion() { return version; }

	private:
		static OpenGLVersion version;
		static SDL_GLContext glContext;
		static ImVec4 clearColor;
	};
}

#endif
