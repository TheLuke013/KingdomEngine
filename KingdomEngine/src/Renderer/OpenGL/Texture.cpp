#include "KingdomEngine/Renderer/OpenGL/Texture.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
	Texture::Texture()
		: ID(0), unit(0), type("")
	{

	}

	void Texture::LoadTexture(const std::string& imagePath, const std::string& textureType, GLenum slot, GLenum pixelType)
	{
        //LOAD IMAGE
        type = textureType;
		int widthImg, heightImg, numColCh;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(imagePath.c_str(), &widthImg, &heightImg, &numColCh, 0);

		//CHECK FOR ERRORS
		if (bytes)
		{
			LOG_INFO("Loaded texture file: " + imagePath);
		}
		else
		{
			LOG_ERROR("Failed to load texture: " + imagePath);
			LOG_ERROR("ERROR: " + std::string(stbi_failure_reason()));
			return;
		}

		//GENERATE TEXTURE AND DEFINES FILTERS
		glGenTextures(1, &ID);
		glActiveTexture(GL_TEXTURE0 + slot);
		unit = slot;
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//defines the texture format based on the number of channels in the loaded image
		if (numColCh == 3)
		{
			format = GL_RGB;
		}
		else if (numColCh == 4)
		{
			format = GL_RGBA;
		}
		else
		{
			LOG_INFO("Unsupported number of channels: " + std::to_string(numColCh));
			stbi_image_free(bytes);
			glBindTexture(GL_TEXTURE_2D, 0);
			return;
		}

		//CREATE TEXTURE AND GENERATE MIPMAP
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
