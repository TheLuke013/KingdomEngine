#ifndef EBO_H
#define EBO_H

#include <GL/glew.h>

#include <vector>

namespace KE
{
	class EBO
	{
	public:
		EBO();

		void Create(std::vector<GLuint>& indices);
		void Create(GLuint* indices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();

	private:
		GLuint ID;
	};
}

#endif
