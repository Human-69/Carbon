#pragma once

#include "entt/include/entt.hpp"
#include "cbpch.h"


namespace Carbon 
{
	class Scene;

	class Entity
	{
	public:

		Entity() : registry(nullptr) {};

		template<typename T, typename ... Args>
		T& AddComponent(Args&&... args)
		{
			return registry->emplace<T>(entity, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent() 
		{
			return registry->get<T>(entity);
		}

		template<typename T>
		bool HasComponent()
		{
			return registry->any_of<T>(entity);
		}

		template<typename T, typename ... Args>
		T& GetOrAddComponent(Args&&... args)
		{
			if (HasComponent<T>())
				return GetComponent<T>();
			else
				return AddComponent<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			registry->remove<T>(entity);
		}

		bool operator==(const Entity& other)
		{
			return entity == other.entity;
		}


	private:
		Entity(entt::entity entity, entt::registry* registry) : entity(entity), registry(registry) {};
		entt::entity entity;
		//The reference to the registry that created this entity
		entt::registry* registry;

		friend class ::Carbon::Scene;
	};
}

