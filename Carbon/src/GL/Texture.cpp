#include "Texture.h"
#include "RendererAPI.h"
#include "../Platform/OpenGL/OpenGLTexture.h"

namespace Carbon::GL
{
	Ref<Texture2D> Texture2D::Create(TextureSpecification spec)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CB_ASSERT_MSG(false, "RendererAPI::API::None is not supported!");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGL::OpenGLTexture2D>(spec);
		}

		CB_ASSERT_MSG(false, "Invalid API type!");
	}

	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CB_ASSERT_MSG(false, "RendererAPI::API::None is not supported!");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGL::OpenGLTexture2D>(filepath);
		}

		CB_ASSERT_MSG(false, "Invalid API type!");
	}
}