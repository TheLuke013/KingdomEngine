#ifndef OPEN_GL_CONTEXT_H
#define OPEN_GL_CONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace KE
{
	enum GLVersion
	{
		OpenGL3,
		OpenGL2
	};

	struct OpenGLVersion
	{
		int minorVersion = 1;
		int majorVersion = 2;
		GLVersion glVersion = OpenGL2;
	};

	class OpenGLContext
	{
	public:
		void Init();
		void Clear();
		static void FramebufferResizeCallback(GLFWwindow* window, int framebufferWidth, int framebufferHeight);
		static void SetGLVersion(GLVersion version_);

		static OpenGLVersion version;
	};
}

#endif