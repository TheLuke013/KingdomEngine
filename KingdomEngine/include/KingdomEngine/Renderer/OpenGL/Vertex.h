#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

namespace KE
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texUV;
	};
}

#endif
