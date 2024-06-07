#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "KingdomEngine/Renderer/OpenGL/Shader.h"
#include "KingdomEngine/Renderer/OpenGL/Texture.h"
#include "KingdomEngine/Renderer/OpenGL/VAO.h"
#include "KingdomEngine/Renderer/OpenGL/VBO.h"
#include "KingdomEngine/Renderer/OpenGL/EBO.h"

namespace KE
{
	class Sprite
	{
	public:
		Sprite(const std::string& texturePath, Shader& shader);
		~Sprite();

		void Draw();

		void SetPosition(float x, float y);
		void SetScale(float scaleX, float scaleY);
		void SetRotation(float degrees);

	private:
		VAO vao;
		VBO vbo;
		EBO ebo;
		Texture texture;
		Shader& shader;
		glm::mat4 transform;
		glm::vec2 position;
		glm::vec2 scale;
		float rotationDegrees;

		void Initialize(const std::string& texturePath);
	};
}

#endif
