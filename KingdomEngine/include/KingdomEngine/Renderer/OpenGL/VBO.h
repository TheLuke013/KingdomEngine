#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>

#include <vector>

namespace KE
{
	class VBO
	{
	public:
		VBO();

		void Create(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();

	private:
		GLuint ID;
	};
}

#endif
