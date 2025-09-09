#include "RendererAPI.h"
#include "../Platform/OpenGL/OpenGLRenderAPI.h"
#include "cb_assert.h"

namespace Carbon::GL
{
	Scope<RendererAPI> RendererAPI::CreateRenderAPI()
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CB_ASSERT_MSG(false, "RendererAPI::API::None is not supported!");
		case RendererAPI::API::OpenGL: return CreateScope<OpenGL::OpenGLRenderAPI>();
		}

		CB_ASSERT_MSG(false, "Invalid API type!");
	}
}