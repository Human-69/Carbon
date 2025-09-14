#pragma once
#include <GL/Buffer.h>

namespace Carbon::GL::OpenGL
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint size);
		OpenGLVertexBuffer(float* vertices, uint size);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetData(const void* data, uint size) override;

		virtual const BufferLayout& GetLayout() const override { return layout; };
		virtual void SetLayout(const BufferLayout& bufferLayout) override { layout = bufferLayout; };

	private:
		BufferLayout layout;
		uint handle;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint* data, uint size);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetData(const uint* data, uint size) override;
	private:
		uint handle;
	};
}