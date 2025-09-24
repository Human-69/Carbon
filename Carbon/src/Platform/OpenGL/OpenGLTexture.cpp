#include "OpenGLTexture.h"
#include <GL/glew.h>
#include <stb_image.h>

namespace Carbon::GL::OpenGL
{

	OpenGLTexture2D::OpenGLTexture2D(TextureSpecification spec)
	{
		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);
		GL_FIND_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		GL_FIND_ERROR();

		specification = spec;

		GLenum internalFormat;

		switch (specification.format)
		{
		case ImageFormat::R8: internalFormat = GL_R8; break;
		case ImageFormat::RG8: internalFormat = GL_RG8; break;
		case ImageFormat::RGB8: internalFormat = GL_RGB8; break;
		case ImageFormat::RGBA8: internalFormat = GL_RGBA8; break;
		default: CB_ASSERT_MSG(false, "Unknown shader format!");
		}

		glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, specification.width, specification.height);
		GL_FIND_ERROR();
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(1);

		int bpp = 0;

		unsigned char* data = stbi_load(path.c_str(), &specification.width, &specification.height, &bpp, 0);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		switch(bpp)
		{
		case 1: specification.format = ImageFormat::R8; break;
		case 2: specification.format = ImageFormat::RG8; break;
		case 3: specification.format = ImageFormat::RGB8; break;
		case 4: specification.format = ImageFormat::RGBA8; break;
		default: CB_ASSERT_MSG(false, "Unknown shader format!");
		}

		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);
		GL_FIND_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		GL_FIND_ERROR();

		GLenum internalFormat;

		switch (specification.format)
		{
		case ImageFormat::R8: internalFormat = GL_R8; break;
		case ImageFormat::RG8: internalFormat = GL_RG8; break;
		case ImageFormat::RGB8: internalFormat = GL_RGB8; break;
		case ImageFormat::RGBA8: internalFormat = GL_RGBA8; break;
		default: CB_ASSERT_MSG(false, "Unknown shader format!");
		}

		glBindTexture(GL_TEXTURE_2D, handle);
		GL_FIND_ERROR();
		glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, specification.width, specification.height);
		GL_FIND_ERROR();

		SetData(data);

		stbi_image_free(data);
	}

	void OpenGLTexture2D::SetData(void* data)
	{
		CB_ASSERT_MSG(data, "Invalid data passed!");

		GLenum format;
		GLenum internalFormat;

		switch(specification.format)
		{
		case ImageFormat::R8: format = GL_RED; internalFormat = GL_R8; break;
		case ImageFormat::RG8: format = GL_RG; internalFormat = GL_RG8; break;
		case ImageFormat::RGB8: format = GL_RGB; internalFormat = GL_RGB8; break;
		case ImageFormat::RGBA8: format = GL_RGBA; internalFormat = GL_RGBA8; break;
		default: CB_ASSERT_MSG(false, "Unknown shader format!");
		}

		glBindTexture(GL_TEXTURE_2D, handle);
		GL_FIND_ERROR();
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, specification.width, specification.height, format, GL_UNSIGNED_BYTE, data);
		GL_FIND_ERROR();
	}

	void OpenGLTexture2D::SetTextureSpecification(TextureSpecification spec) 
	{
		if(spec.format != specification.format || spec.width != specification.width || spec.height != specification.height)
		{
			specification = spec;

			GLenum internalFormat;

			switch (specification.format)
			{
			case ImageFormat::R8: internalFormat = GL_R8; break;
			case ImageFormat::RG8: internalFormat = GL_RG8; break;
			case ImageFormat::RGB8: internalFormat = GL_RGB8; break;
			case ImageFormat::RGBA8: internalFormat = GL_RGBA8; break;
			default: CB_ASSERT_MSG(false, "Unknown shader format!");
			}

			glBindTexture(GL_TEXTURE_2D, handle);
			GL_FIND_ERROR();
			glTextureStorage2D(handle, 0, internalFormat, specification.width, specification.height);
			GL_FIND_ERROR();
			return;
		}
		specification = spec;
	}

	void OpenGLTexture2D::Bind(uint textureSlot)
	{
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, handle);
		GL_FIND_ERROR();
	}

	void OpenGLTexture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_FIND_ERROR();
	}
}