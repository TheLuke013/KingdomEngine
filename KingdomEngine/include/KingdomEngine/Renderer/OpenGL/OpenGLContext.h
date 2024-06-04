#ifndef OPEN_GL_CONTEXT_H
#define OPEN_GL_CONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace KE
{
	class OpenGLContext
	{
	public:
		void Init();
		void Clear();
		static void FramebufferResizeCallback(GLFWwindow* window, int framebufferWidth, int framebufferHeight);
	};
}

#endif
