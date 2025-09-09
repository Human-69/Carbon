#pragma once
#include <CarbonTypes.h>

#include <stb_image.h>
#include <string>
#include <vector>
#include "cb_assert.h"

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

	
	enum class ImageFormat
	{
		R8,
		RG8,
		RGB8,
		RGBA8,
	};

	struct TextureSpecification
	{
		int width;
		int height;
		ImageFormat format;
		bool generateMipMaps = true;
	};

	class Texture
	{
	public:
		
		virtual int GetWidth() const  = 0;
		virtual int GetHeight() const = 0;

		virtual const TextureSpecification& GetSpecification() = 0;
		virtual void SetTextureSpecification(TextureSpecification spec) = 0;

		virtual void SetData(void* data) = 0;

		virtual void Bind(uint textureSlot) = 0;
		virtual void Unbind()				= 0;
	};


	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(TextureSpecification spec);
		static Ref<Texture2D> Create(const std::string& path);
	};
}

