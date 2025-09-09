#pragma once
#include <CarbonTypes.h>

/* carbon */
#include "Material.h"

namespace Carbon::GL
{
	class Shader
	{
	public:
		Shader() = default;

		Shader(int handle) : handle(handle) {};

		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		static Shader CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		void Bind();
		void Unbind();

		void ApplyMaterial(Material material);

		/* Setting uniforms */
		void SetMatrix4(const std::string& name, const Matrix4& value);
		void SetInt(const std::string& name, const int value);
		void SetFloat(const std::string& name, const float value);
		void SetVector2(const std::string& name, const Vector2& vector2);
		void SetVector3(const std::string& name, const Vector3& vector3);
		void SetVector4(const std::string& name, const Vector4& vector4);

		uint handle = -1;
	private:
		uint GetLocation(const std::string& name);
	};
}