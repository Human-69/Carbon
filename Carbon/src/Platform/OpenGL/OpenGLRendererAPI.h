#pragma once
#include <GL/RendererAPI.h>

namespace Carbon::GL::OpenGL {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(Color color) override;

		virtual void Clear() override;

		virtual void DrawIndexed(Ref<VertexArray> VAO, int indexCount) override;
	};
}