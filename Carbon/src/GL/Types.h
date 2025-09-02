#pragma once

#include <glm.hpp>

#if defined(__GNUC__)
#include <cassert>
#define _ASSERT(x) assert(x) 
#endif

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::mat4 Matrix4;
typedef unsigned int uint;