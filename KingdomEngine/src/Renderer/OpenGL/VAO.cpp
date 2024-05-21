#include "KIngdomEngine/Renderer/OpenGL/VAO.h"

namespace KE
{
	VAO::VAO()
		: ID(0)
	{
		
	}

	void VAO::Create()
	{
		glGenVertexArrays(1, &ID);
	}

	void VAO::LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	{
		vbo.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		vbo.Unbind();
	}

	void VAO::Bind()
	{
		glBindVertexArray(ID);
	}

	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}
}