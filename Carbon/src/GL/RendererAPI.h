#pragma once
#include <CarbonTypes.h>
#include "VertexArray.h"

namespace Carbon::GL
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None, OpenGL,
		};

		virtual void Init() = 0;

		virtual void SetClearColor(Color color) = 0;
		
		virtual void Clear() = 0;

		virtual void DrawIndexed(Ref<VertexArray> VAO, int indexCount) = 0;

		static API GetAPI() { return api; };

		static Scope<RendererAPI> Create();

	private:
		static inline API api = API::OpenGL;
	};
}