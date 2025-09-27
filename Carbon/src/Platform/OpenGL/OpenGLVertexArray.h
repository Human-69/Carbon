#pragma once
#include "../GL/VertexArray.h"
#include "OpenGLBuffer.h"

namespace Carbon::GL::OpenGL {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();

		virtual void Bind()   override;
		virtual void Unbind() override;

		virtual void SetVertexBuffer(Ref<VertexBuffer> buffer) override;
		virtual void SetIndexBuffer(Ref<IndexBuffer> buffer)   override;
	private:
		Ref<OpenGLVertexBuffer> vertexBuffer;
		Ref<OpenGLIndexBuffer> indexBuffer;
		uint vao;
	};
}

