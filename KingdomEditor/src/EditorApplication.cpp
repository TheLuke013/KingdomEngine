#include <KingdomEngine/KingdomEngine.h>
#include <KingdomEngine/Renderer/OpenGL/Shader.h>
#include <KingdomEngine/Renderer/OpenGL/VAO.h>
#include <KingdomEngine/Renderer/OpenGL/VBO.h>
#include <KingdomEngine/Renderer/OpenGL/EBO.h>

class EditorApplication : public KE::Application
{
public:
	KE::Shader shaders;
	KE::VAO vao;
	KE::VBO vbo;
	KE::EBO ebo;

	EditorApplication()
		: shaders(KE::Shader()), vao(KE::VAO()), vbo(KE::VBO()), ebo(KE::EBO())
	{

	}

	~EditorApplication()
	{

	}

	void OnReady() override
	{
		GLfloat vertices[] =
		{ //               COORDINATES                  /     COLORS           //
			-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
			 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
			 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
			-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
			 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
			 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
		};

		GLuint indices[] =
		{
			0, 3, 5, // Lower left triangle
			3, 2, 4, // Lower right triangle
			5, 4, 1 // Upper triangle
		};

		shaders.LoadShaders("resource/shaders/default.vert", "resource/shaders/default.frag");

		vao.Create();
		vao.Bind();

		vbo.Create(vertices, sizeof(vertices));
		ebo.Create(indices, sizeof(indices));

		vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();

		GLuint uniformID = glGetUniformLocation(shaders.GetID(), "scale");
		glUniform1f(uniformID, 0.1f);
	}

	void Update() override
	{
		shaders.Activate();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	}

	void OnEvent(KE::Event e) override
	{

	}
};

KE::Application* KE::CreateApplication()
{
	return new EditorApplication();
}