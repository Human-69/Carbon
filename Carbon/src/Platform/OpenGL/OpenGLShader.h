#pragma once
#include "../GL/Shader.h"

namespace Carbon::GL::OpenGL {
    class OpenGLShader : public Shader
    {
    public:
		OpenGLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        virtual void Bind()   override;
		virtual void Unbind() override;

		virtual void SetMatrix4(const std::string& name, const Matrix4& value)   override;
		virtual void SetInt(const std::string& name, const int value)			 override;
		virtual void SetFloat(const std::string& name, const float value) 		 override;
		virtual void SetVector2(const std::string& name, const Vector2& vector2) override;
		virtual void SetVector3(const std::string& name, const Vector3& vector3) override;
		virtual void SetVector4(const std::string& name, const Vector4& vector4) override;
	private:
		uint handle;
		uint GetLocation(const std::string& name);
    };
}

