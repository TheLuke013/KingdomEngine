#include "KingdomEngine/Renderer/OpenGL/Texture.h"

namespace KE
{
	Texture::Texture()
		: ID(0), type(GLenum())
	{
		
	}

	void Texture::Create(const std::string& imagePath, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
	{
		type = textureType;
		int widthImg, heightImg, numColCh;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(imagePath.c_str(), &widthImg, &heightImg, &numColCh, 0);

		glGenTextures(1, &ID);
		glActiveTexture(slot);
		glBindTexture(textureType, ID);

		glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(textureType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
		glGenerateMipmap(textureType);

		stbi_image_free(bytes);
		glBindTexture(textureType, 0);
	}

	void Texture::TextureUnit(Shader& shader, const std::string& uniform, GLuint unit)
	{
		GLuint textureUniform = glGetUniformLocation(shader.GetID(), uniform.c_str());
		shader.Activate();
		glUniform1i(textureUniform, unit);
	}

	void Texture::Bind()
	{
		glBindTexture(type, ID);
	}

	void Texture::Unbind()
	{
		glBindTexture(type, 0);
	}

	void Texture::Delete()
	{
		glDeleteTextures(1, &ID);
	}
}