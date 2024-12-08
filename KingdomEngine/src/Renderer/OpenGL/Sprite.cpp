#include "KingdomEngine/Renderer/OpenGL/Sprite.h"

namespace KE
{
	Sprite::Sprite()
		: shader(Renderer::GetDefaultShader()), transform(glm::mat4(1.0f))
	{

	}

	Sprite::~Sprite()
	{
		Delete();
	}

	void Sprite::LoadTexture(const std::string& texturePath)
	{
	    texture.LoadTexture(texturePath, "diffuse", 0, GL_UNSIGNED_BYTE);
	    Initialize(texturePath);
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

	void Sprite::Delete()
	{
	    vao.Delete();
		vbo.Delete();
		ebo.Delete();
		texture.Delete();
	}

	void Sprite::SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
	}

	void Sprite::SetScale(float scaleX, float scaleY)
	{
		scale.x = scaleX;
		scale.y = scaleY;
		transform = glm::scale(transform, glm::vec3(scale.x, scale.y, 1.0f));
	}

	void Sprite::SetRotation(float degrees)
	{
		rotationDegrees = degrees;
		transform = glm::rotate(transform, glm::radians(rotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
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
