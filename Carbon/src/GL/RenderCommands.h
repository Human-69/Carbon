#pragma once

#include <CarbonTypes.h>
#include "RendererAPI.h"

namespace Carbon::GL
{
	class RendererCommands
	{
	public:
		static void Init()
		{
			api->Init();
		}

		static void SetClearColor(Color color)
		{
			api->SetClearColor(color);
		}

		static void Clear()
		{
			api->Clear();
		}

		static void DrawIndexed(Ref<VertexArray> VAO, int indexCount)
		{
			api->DrawIndexed(VAO, indexCount);
		}

	private:
		static Scope<RendererAPI> api;
	};
}