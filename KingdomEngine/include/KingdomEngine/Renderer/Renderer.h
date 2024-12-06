#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "KingdomEngine/Renderer/OpenGL/Framebuffer.h"
#include "KingdomEngine/Renderer/OpenGL/Shader.h"
#include "KingdomEngine/Core/Color.h"

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
		static void Clear(int width, int height);

		static void SetGLVersion(GLVersion version_);
		static SDL_GLContext& GetContext() { return glContext; }
		static Color& GetClearColor() { return clearColor; }
		static OpenGLVersion& GetVersion() { return version; }

		static Framebuffer& GetFramebuffer() { return framebuffer; }
		static Shader& GetDefaultShader() { return defaultShader; }

	private:
		static OpenGLVersion version;
		static SDL_GLContext glContext;
		static Color clearColor;
		static Framebuffer framebuffer;
		static Shader defaultShader;
	};
}

#endif
