#include "KingdomEngine/Renderer/OpenGL/Shader.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
	Shader::Shader()
		: programID(0)
	{

	}

	Shader::~Shader()
	{
		glDeleteProgram(programID);
	}

	void Shader::LoadShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		//LOAD SHADERS FROM FILE
		std::string vertexCode = GetShaderFileContents(vertexShaderFile);
		std::string fragmentCode = GetShaderFileContents(fragmentShaderFile);

		if (vertexCode == "" || fragmentCode == "")
		{
			return;
		}

		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();

		//VERTEX SHADER
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		CompileErrors(vertexShader, "Vertex Shader");

		//FRAGMENT SHADER
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		CompileErrors(fragmentShader, "Fragment Shader");

		//SHADER PROGRAM
		programID = glCreateProgram();
		glAttachShader(programID, vertexShader);
		glAttachShader(programID, fragmentShader);
		glLinkProgram(programID);
		CompileErrors(programID, "Shader Program");

		//DELETE SHADERS
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::Activate()
	{
		glUseProgram(programID);
	}

	void Shader::Delete()
	{
		glDeleteProgram(programID);
	}

	std::string Shader::GetShaderFileContents(const std::string& fileName)
	{
		std::ifstream file(fileName, std::ios::binary);
		std::string contents = "";

		if (file)
		{
			file.seekg(0, std::ios::end);
			contents.resize(file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&contents[0], contents.size());
			file.close();

			LOG_INFO("Loaded Shader file: " + fileName);
			return(contents);
		}
		else
		{
			LOG_ERROR("Failed to open Shader file: " + fileName);
			return "";
		}

		return "";
	}

	void Shader::CompileErrors(unsigned int shader, const std::string& type)
	{
		GLint hasCompiled;
		char infoLog[1024];
		if (type != "Shader Program")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				LOG_ERROR("Shader compilation error for: " + type);
			}
		}
		else
		{
			glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				LOG_ERROR("Shader linking error for: " + type);
			}
		}
	}
}