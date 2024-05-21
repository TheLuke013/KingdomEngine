#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

namespace KE
{
	class EBO
	{
	public:
		EBO();

		void Create(GLuint* indices, GLsizeiptr size);
		void Bind();
		void Unbind();
		void Delete();

	private:
		GLuint ID;
	};
}

#endif
