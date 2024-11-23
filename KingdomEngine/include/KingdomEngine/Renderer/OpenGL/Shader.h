#ifndef SHADERS_H
#define SHADERS_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

namespace KE
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		GLuint GetID() const { return programID; }

		void LoadShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
		void Activate();
		void Delete();

	private:
		GLuint programID;

	private:
		std::string GetShaderFileContents(const std::string& fileName);
		void CompileErrors(unsigned int shader, const std::string&);
	};
}

#endif
