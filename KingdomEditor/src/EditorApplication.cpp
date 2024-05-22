#include <KingdomEngine/KingdomEngine.h>

class EditorApplication : public KE::Application
{
public:
	KE::Shader shader;
	KE::Shader lightShader;
	KE::Camera camera;

	KE::Mesh light;
	KE::Mesh floor;

	EditorApplication()
		: camera(window.properties.width, window.properties.height, glm::vec3(0.0f, 1.0f, 0.0f))
	{

	}

	~EditorApplication()
	{

	}

	void OnReady() override
	{
		KE::Vertex vertices[] =
		{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
			KE::Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
			KE::Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
			KE::Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
			KE::Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
		};

		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3
		};

		KE::Vertex lightVertices[] =
		{ //     COORDINATES     //
			KE::Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
			KE::Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
			KE::Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
			KE::Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
			KE::Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
			KE::Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
			KE::Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
			KE::Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
		};

		GLuint lightIndices[] =
		{
			0, 1, 2,
			0, 2, 3,
			0, 4, 7,
			0, 7, 3,
			3, 7, 6,
			3, 6, 2,
			2, 6, 5,
			2, 5, 1,
			1, 5, 4,
			1, 4, 0,
			4, 5, 6,
			4, 6, 7
		};

		KE::Texture textures[]
		{
			KE::Texture(("resource/textures/woodTexture.png"), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
			KE::Texture(("resource/textures/woodTexture_s.png"), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
		};

		//SHADER
		shader.LoadShaders("resource/shaders/default.vert", "resource/shaders/default.frag");
		std::vector <KE::Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(KE::Vertex));
		std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
		std::vector <KE::Texture> tex(textures, textures + sizeof(textures) / sizeof(KE::Texture));
		floor.Create(verts, ind, tex);

		//LIGHT SHADER
		lightShader.LoadShaders("resource/shaders/light.vert", "resource/shaders/light.frag");
		std::vector <KE::Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(KE::Vertex));
		std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
		light.Create(lightVerts, lightInd, tex);

		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 lightPos = glm::vec3(0.0f, 1.5f, 0.0f);
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);

		glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4 objectModel = glm::mat4(1.0f);
		objectModel = glm::translate(objectModel, objectPos);

		lightShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		glUniform4f(glGetUniformLocation(lightShader.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		shader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
		glUniform4f(glGetUniformLocation(shader.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shader.GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	}

	void Update() override
	{
		camera.Inputs(window.Get());
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		floor.Draw(shader, camera);
		light.Draw(lightShader, camera);

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