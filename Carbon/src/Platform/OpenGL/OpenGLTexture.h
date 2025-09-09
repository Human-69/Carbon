#pragma once

#include "../GL/Texture.h"

namespace Carbon::GL::OpenGL 
{
	class OpenGLTexture2D : public Texture2D
	{
	public:

		OpenGLTexture2D(TextureSpecification spec);
		OpenGLTexture2D(const std::string& path);

		virtual int GetWidth()  const override { return specification.width; };
		virtual int GetHeight() const override { return specification.height; };

		virtual const TextureSpecification& GetSpecification() override { return specification; };
		virtual void SetTextureSpecification(TextureSpecification spec) override;

		virtual void SetData(void* data) override;

		virtual void Bind(uint textureSlot) override;
		virtual void Unbind()				override;
		uint handle;
	private:
		TextureSpecification specification;
	};
}