#include "Material.h"
#include "cbpch.h"

namespace Carbon::GL
{
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
		_ASSERT(params.find(uniformName) != params.end());

		params[uniformName] = uniformValue;
	}

	UniformValue Material::GetUniform(const std::string& uniformName)
	{
		_ASSERT(params.find(uniformName) != params.end());

		return params[uniformName];
	}

	void Material::RemoveUniform(const std::string& uniformName)
	{
		_ASSERT(params.find(uniformName) != params.end());

		params.erase(params.find(uniformName));
	}
}