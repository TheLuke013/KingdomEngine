#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

namespace KE
{
	class Framebuffer
	{
	public:
		Framebuffer();

		void Create(int width, int height);
		void Bind();
		void Unbind();
		void Delete();
		GLuint GetTextureID() const { return framebufferTexture; }
		void Draw(int width, int height);

	private:
		GLuint FBO;
		GLuint RBO;
		GLuint rectVAO, rectVBO;
		GLuint framebufferTexture;
	};
}

#endif
