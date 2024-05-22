#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <vector>

namespace KE
{
	class EBO
	{
	public:
		EBO();

		void Create(std::vector<GLuint>& indices);
		void Bind();
		void Unbind();
		void Delete();

	private:
		GLuint ID;
	};
}

#endif
