#ifndef MESH_H
#define MESH_H

#include <string>

#include "KingdomEngine/Renderer/OpenGL/VAO.h"
#include "KingdomEngine/Renderer/OpenGL/EBO.h"
#include "KingdomEngine/Renderer/OpenGL/Camera.h"
#include "KingdomEngine/Renderer/OpenGL/Texture.h"

namespace KE
{
	class Mesh
	{
	public:
		Mesh();

		void Create(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
		void Draw(Shader& shader, Camera& camera);

	private:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		VAO vao;
	};
}

#endif
