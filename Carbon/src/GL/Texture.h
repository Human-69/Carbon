#pragma once
#include "cbglpch.h"

#include "Types.h"

#include <stb_image.h>

/* opengl */
#include <GL/glew.h>

#define GL_FIND_ERROR() \
	do { \
        GLenum err; \
        while((err = glGetError()) != GL_NO_ERROR) { \
            fprintf(stderr, "OpenGL error %d in file %s at line %d\n", err, __FILE__, __LINE__); \
        } \
    } while(0)

namespace Carbon::GL {
	/// <summary>
	/// A generic texture for storing image data on the GPU
	/// </summary>
	/// <typeparam name="target">Can be either GL_TEXTURE_2D or GL_TEXTURE_CUBE_MAP</typeparam>
	template<int target>
	class Texture
	{
	public:
		template<int i = target, typename = std::enable_if_t<i == GL_TEXTURE_2D, int>>
		Texture(std::string texturePath)
		{
			stbi_set_flip_vertically_on_load(1);
			unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &bpp, 0);

			std::cout << target << ", ";

			uint format;

			switch (bpp)
			{
			case 1: format = GL_RED; break;
			case 2: format = GL_RG; break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
			default: format = GL_RGB; break;
			}

			GLenum internalFormat;
			switch (bpp)
			{
			case 1: internalFormat = GL_R8; break;
			case 2: internalFormat = GL_RG8; break;
			case 3: internalFormat = GL_RGB8; break;
			case 4: internalFormat = GL_RGBA8; break;
			default: internalFormat = GL_RGB8; break;
			}

			std::cout << bpp << ", " << width << ", " << height << "\n";

			glGenTextures(1, &handle);
			GL_FIND_ERROR();
			glBindTexture(target, handle);
			GL_FIND_ERROR();

			glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
			GL_FIND_ERROR();

			_ASSERT(data);

			glTexImage2D(target, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			GL_FIND_ERROR();
			//glGenerateMipmap(target);
			glBindTexture(target, 0);
			GL_FIND_ERROR();
		}

		template<int i = target, typename = std::enable_if_t<i == GL_TEXTURE_CUBE_MAP, int>>
		Texture(std::vector<std::string> filepaths)
		{

		}

		void Bind(int slot = 0)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(target, handle);
		}

		void Unbind()
		{
			glBindTexture(target, 0);
		}

	private:
		uint handle;
		int width;
		int height;
		int bpp;
	};

	typedef Texture<GL_TEXTURE_2D> Texture2D;
	typedef Texture<GL_TEXTURE_CUBE_MAP> TextureCubemap;

}

