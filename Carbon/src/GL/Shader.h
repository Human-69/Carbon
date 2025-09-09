#pragma once
#include <CarbonTypes.h>
#include <string>

namespace Carbon::GL
{
	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		virtual void Bind()   = 0;
		virtual void Unbind() = 0;

		/* Setting uniforms */
		virtual void SetMatrix4(const std::string& name, const Matrix4& value)   = 0;
		virtual void SetInt(const std::string& name, const int value)			 = 0;
		virtual void SetFloat(const std::string& name, const float value) 		 = 0;
		virtual void SetVector2(const std::string& name, const Vector2& vector2) = 0;
		virtual void SetVector3(const std::string& name, const Vector3& vector3) = 0;
		virtual void SetVector4(const std::string& name, const Vector4& vector4) = 0;
	};
}