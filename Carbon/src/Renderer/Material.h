#pragma once
#include <variant>
#include <unordered_map>
#include <string>

#include <CarbonTypes.h>

/* carbon */
#include "../GL/Texture.h"


namespace Carbon::Renderer {

	/// <summary>
	/// Union of all possible data that can be passed to shaders
	/// </summary>
	typedef std::variant<int, float, Vector2, Vector3, Vector4, Matrix4, Ref<GL::Texture2D>> UniformValue;

	class Material
	{
	public:
		void AddUniform(const std::string& uniformName, UniformValue uniformValue);
		void SetUniform(const std::string& uniformName, UniformValue uniformValue);

		UniformValue GetUniform(const std::string& uniformName);
		void RemoveUniform(const std::string& uniformName);
	private:
		std::unordered_map<std::string, UniformValue> params;
		friend class Shader;
	};
}

