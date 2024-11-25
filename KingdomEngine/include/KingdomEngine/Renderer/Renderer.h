#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#define NO_SDL_GLEXT
#include <GL/glew.h>
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
        int majorVersion = 2;
		int minorVersion = 1;
		GLVersion glVersion = OpenGL2;
	};

	class Renderer
	{
	public:
		static void Init();
		static void SetContext(SDL_Window* window);
		static void InitGL();
		static void CheckOpenGLVersion(SDL_Window* window);
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
