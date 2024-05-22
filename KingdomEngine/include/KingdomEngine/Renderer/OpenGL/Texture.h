#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"

namespace KE
{
	class Texture
	{
	public:
		std::string type;

		Texture(const std::string& imagePath, const std::string& textureType, GLenum slot, GLenum format, GLenum pixelType);

		void TextureUnit(Shader& shader, const std::string& uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();

	private:
		GLuint ID;
		GLuint unit;

	};
}

#endif
