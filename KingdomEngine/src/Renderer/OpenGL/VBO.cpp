#include "KIngdomEngine/Renderer/OpenGL/VBO.h"

namespace KE
{
	VBO::VBO()
		: ID(0)
	{
		
	}

	void VBO::Create(std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}

	void VBO::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VBO::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::Delete()
	{
		glDeleteBuffers(1, &ID);
	}
}