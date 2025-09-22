#pragma once
#include "cbpch.h"
#include "Renderer/Mesh.h"
#include "Entity.h"
#include "Components.h"
#include <entt/include/entt.hpp>

namespace Carbon
{
	class Scene
	{
	public:

		Scene() {};

		Entity CreateEntity() { return Entity(registry.create(), &registry); }

		template<typename Type, typename... Other, typename... Exclude>
		auto GetView(entt::exclude_t<Exclude...> ex = entt::exclude_t{}) {
			return registry.view<Type, Other..., Exclude...>(ex);
		}

		void OnUpdate(Renderer::Camera& mainCamera);
	private:
		entt::registry registry;
		friend class Carbon::Entity;
	};
}