#include "Shader.h"
#include "../Platform/OpenGL/OpenGLShader.h"
#include "RendererAPI.h"
#include "cb_assert.h"

namespace Carbon::GL
{
	Ref<Shader> Shader::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		switch(RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CB_ASSERT_MSG(false, "RendererAPI::API::None is not supported!");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGL::OpenGLShader>(vertexShaderPath, fragmentShaderPath);
		}

		CB_ASSERT_MSG(false, "Invalid API type!");
	}
}