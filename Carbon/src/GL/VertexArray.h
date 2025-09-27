#pragma once
#include <CarbonTypes.h>
#include "Buffer.h"


namespace Carbon::GL
{
	class VertexArray
	{
	public:
		virtual void Bind()   = 0;
		virtual void Unbind() = 0;

		virtual void SetVertexBuffer(Ref<VertexBuffer> buffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer> buffer)   = 0;

		static Ref<VertexArray> Create();
	};
}