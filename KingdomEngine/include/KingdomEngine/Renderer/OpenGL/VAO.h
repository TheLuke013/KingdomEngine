#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "KIngdomEngine/Renderer/OpenGL/VBO.h"

namespace KE
{
	class VAO
	{
	public:
		VAO();

		void Create();
		void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents,GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();

	private:
		GLuint ID;
	};
}

#endif
