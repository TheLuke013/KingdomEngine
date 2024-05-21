#include <KingdomEngine/KingdomEngine.h>

#include "Camera.h"

class EditorApplication : public KE::Application
{
public:
	KE::Shader shaders;
	KE::VAO vao;
	KE::VBO vbo;
	KE::EBO ebo;
	KE::Texture texture;

	Camera camera;

	GLuint uniformID;

	EditorApplication()
		: shaders(KE::Shader()), vao(KE::VAO()), vbo(KE::VBO()), ebo(KE::EBO()),
		texture(KE::Texture()), uniformID(0), camera(Camera())
	{

	}

	~EditorApplication()
	{

	}

	void OnReady() override
	{
		GLfloat vertices[] =
		{ //     COORDINATES     /        COLORS      /   TexCoord  //
			-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
			-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
			 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
			 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
		};

		// Indices for vertices order
		GLuint indices[] =
		{
			0, 2, 1, // Upper triangle
			0, 3, 2 // Lower triangle
		};

		shaders.LoadShaders("resource/shaders/default.vert", "resource/shaders/default.frag");

		vao.Create();
		vao.Bind();

		vbo.Create(vertices, sizeof(vertices));
		ebo.Create(indices, sizeof(indices));

		vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();

		uniformID = glGetUniformLocation(shaders.GetID(), "scale");

		texture.Create("resource/textures/013.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		texture.TextureUnit(shaders, "tex0", 0);

		camera.Create(window.properties.width, window.properties.height, glm::vec3(0.0f, 0.0f, 0.0f));
	}

	void Update() override
	{
		shaders.Activate();

		camera.Inputs(window.Get());
		camera.Matrix(45.0f, 0.1f, 100.0f, shaders, "camMatrix");

		glUniform1f(uniformID, 0.1f);

		texture.Bind();
		vao.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void OnEvent(KE::Event e) override
	{

	}
};

KE::Application* KE::CreateApplication()
{
	return new EditorApplication();
}