#include "VertexArray.h"
#include "RendererAPI.h"
#include "../Platform/OpenGL/OpenGLVertexArray.h"

namespace Carbon::GL
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CB_ASSERT_MSG(false, "RendererAPI::API::None is not supported!");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGL::OpenGLVertexArray>();
		}

		CB_ASSERT_MSG(false, "Invalid API type!");
	}
}