#include "KingdomEngine/Renderer/OpenGL/Texture.h"

namespace KE
{
	Texture::Texture(const std::string& imagePath, const std::string& textureType, GLenum slot, GLenum format, GLenum pixelType)
		: ID(0), type("")
	{
		type = textureType;
		int widthImg, heightImg, numColCh;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(imagePath.c_str(), &widthImg, &heightImg, &numColCh, 0);

		glGenTextures(1, &ID);
		glActiveTexture(GL_TEXTURE0 + slot);
		unit = slot;
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(bytes);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::TextureUnit(Shader& shader, const std::string& uniform, GLuint unit)
	{
		GLuint textureUniform = glGetUniformLocation(shader.GetID(), uniform.c_str());
		shader.Activate();
		glUniform1i(textureUniform, unit);
	}

	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Delete()
	{
		glDeleteTextures(1, &ID);
	}
}