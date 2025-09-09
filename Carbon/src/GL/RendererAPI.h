#pragma once
#include <CarbonTypes.h>

namespace Carbon::GL
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None, OpenGL,
		};

		static API GetAPI() { return api; };

		static Scope<RendererAPI> CreateRenderAPI();

	private:
		static inline API api = API::OpenGL;
	};
}