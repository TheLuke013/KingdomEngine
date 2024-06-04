#include "KingdomEngine/Renderer/OpenGL/Sprite.h"

namespace KE
{
	Sprite::Sprite(const std::string& texturePath, Shader& shader)
		: shader(shader), texture(texturePath, "diffuse", 0, GL_UNSIGNED_BYTE), transform(glm::mat4(1.0f))
	{
		Initialize(texturePath);
	}

	Sprite::~Sprite()
	{
		vao.Delete();
		vbo.Delete();
		ebo.Delete();
		texture.Delete();
	}

	void Sprite::Draw()
	{
		shader.Activate();
		texture.Bind();
		vao.Bind();

		GLuint transformLoc = glGetUniformLocation(shader.GetID(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		vao.Unbind();
		texture.Unbind();
	}

	void Sprite::SetPosition(float x, float y)
	{
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
	}

	void Sprite::SetScale(float scaleX, float scaleY)
	{
		transform = glm::scale(transform, glm::vec3(scaleX, scaleY, 1.0f));
	}

	void Sprite::Initialize(const std::string& texturePath)
	{
		float vertices[] = {
			// positions          // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		vao.Create();
		vao.Bind();

		vbo.Create(vertices, sizeof(vertices));
		ebo.Create(indices, sizeof(indices));

		vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
		vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();
	}
}