#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <vector>

#include "KingdomEngine/Renderer/OpenGL/Vertex.h"

namespace KE
{
	class VBO
	{
	public:
		VBO();

		void Create(std::vector<Vertex>& vertices);
		void Bind();
		void Unbind();
		void Delete();

	private:
		GLuint ID;
	};
}

#endif
