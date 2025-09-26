#include "Material.h"
#include "cbpch.h"

namespace Carbon::Renderer
{

	void Material::SetMaterial(Ref<GL::Shader> shader)
	{
		int texSlot = 0;
		int maxTexSlots;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTexSlots);
		for (auto& [name, value] : params)
		{
			std::visit([&](auto&& val)
				{
					using T = std::decay_t<decltype(val)>;

					if constexpr (std::is_same_v<T, int>)
						shader->SetInt(name, val);
					else if constexpr (std::is_same_v<T, float>)
						shader->SetFloat(name, val);
					else if constexpr (std::is_same_v<T, Vector2>)
						shader->SetVector2(name, val);
					else if constexpr (std::is_same_v<T, Vector3>)
						shader->SetVector3(name, val);
					else if constexpr (std::is_same_v<T, Vector4>)
						shader->SetVector4(name, val);
					else if constexpr (std::is_same_v<T, Matrix4>)
						shader->SetMatrix4(name, val);
					else if constexpr (std::is_same_v<T, Ref<GL::Texture>>)
					{
						Ref<GL::Texture> t = std::get<Ref<GL::Texture>>(val);
						t->Bind(texSlot);
						shader->SetInt(name, texSlot++);
					}
				}, value);

			CB_ASSERT(texSlot < maxTexSlots);
		}
	}

	void Material::AddUniform(const std::string& uniformName, UniformValue uniformValue)
	{

		if (params.find(uniformName) != params.end()) 
		{
			SetUniform(uniformName, uniformValue); //The uniform exists, don't add it again
			return;
		}

		params.insert({ uniformName, uniformValue });
	}

	void Material::SetUniform(const std::string& uniformName, UniformValue uniformValue)
	{
		CB_ASSERT(params.find(uniformName) != params.end());

		params[uniformName] = uniformValue;
	}

	UniformValue Material::GetUniform(const std::string& uniformName)
	{
		CB_ASSERT(params.find(uniformName) != params.end());

		return params[uniformName];
	}

	void Material::RemoveUniform(const std::string& uniformName)
	{
		CB_ASSERT(params.find(uniformName) != params.end());

		params.erase(params.find(uniformName));
	}
}