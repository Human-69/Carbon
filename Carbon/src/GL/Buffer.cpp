#include "Buffer.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"
#include "RendererAPI.h"

namespace Carbon::GL
{
	Ref<VertexBuffer> VertexBuffer::Create(uint size)
	{
		switch (RendererAPI::GetAPI()) 
		{
		case RendererAPI::API::None: CB_ASSERT_MSG(false, "RendererAPI::API::None is not supported!");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGL::OpenGLVertexBuffer>(size);
		}

		CB_ASSERT_MSG(false, "Invalid API type!");
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CB_ASSERT_MSG(false, "RendererAPI::API::None is not supported!");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGL::OpenGLVertexBuffer>(vertices, size);
		}

		CB_ASSERT_MSG(false, "Invalid API type!");
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint* indices, uint size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CB_ASSERT_MSG(false, "RendererAPI::API::None is not supported!");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGL::OpenGLIndexBuffer>(indices, size);
		}

		CB_ASSERT_MSG(false, "Invalid API type!");
	}
}