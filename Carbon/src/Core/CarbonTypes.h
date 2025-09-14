#pragma once

#include <glm.hpp>
#include <memory>

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::mat4 Matrix4;
typedef glm::vec4 Color;
typedef unsigned int uint;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}


template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}