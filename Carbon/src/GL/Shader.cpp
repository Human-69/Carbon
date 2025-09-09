#include "Shader.h"
#include "cbpch.h"

/* opengl */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::string dumpStream(std::ifstream& stream)
{
	std::stringstream ss;
	ss << stream.rdbuf();
	return ss.str();
}

namespace Carbon::GL
{
	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		*this = CreateShader(vertexShaderPath, fragmentShaderPath);
	}

	Shader Shader::CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		std::ifstream vsSource(vertexShaderPath);
		std::ifstream fsSource(fragmentShaderPath);

		CB_ASSERT(vsSource && fsSource);

		std::string vertexSource = dumpStream(vsSource);
		std::string fragmentSource = dumpStream(fsSource);

		uint vertexShader;
		uint fragmentShader;

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vertexsrc = vertexSource.c_str();
		const char* fragmentsrc = fragmentSource.c_str();

		glShaderSource(vertexShader, 1, &vertexsrc, NULL);
		glShaderSource(fragmentShader, 1, &fragmentsrc, NULL);

		glCompileShader(vertexShader);

		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		uint shaderProgram;
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINKING::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return GL::Shader(shaderProgram);
	}

	void Shader::Bind()
	{
		glUseProgram(handle);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::ApplyMaterial(Material material)
	{
		int texSlot = 0;
		int maxTexSlots;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTexSlots);
		for(auto& [name, value] : material.params)
		{
			std::visit([&](auto&& val) 
			{
				using T = std::decay_t<decltype(val)>;

				if constexpr (std::is_same_v<T, int>)
					SetInt(name, val);
				else if constexpr (std::is_same_v<T, float>)
					SetFloat(name, val);
				else if constexpr (std::is_same_v<T, Vector2>)
					SetVector2(name, val);
				else if constexpr (std::is_same_v<T, Vector3>)
					SetVector3(name, val);
				else if constexpr (std::is_same_v<T, Vector4>)
					SetVector4(name, val);
				else if constexpr (std::is_same_v<T, Matrix4>)
					SetMatrix4(name, val);
				else if constexpr (std::is_same_v<T, Texture2D>)
				{
					Texture2D** t_ptr = std::get<Texture2D*>(value);
					(*t_ptr)->Bind(texSlot);
					SetInt(name, texSlot++);
				}
				else if constexpr (std::is_same_v<T, TextureCubemap>)
				{
					TextureCubemap** t_ptr = std::get<TextureCubemap*>(value);
					(*t_ptr)->Bind(texSlot);
					SetInt(name, texSlot++);
				}
			}, value);

			CB_ASSERT(texSlot < maxTexSlots);
		}
	}

	void Shader::SetMatrix4(const std::string& name, const Matrix4& value)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
		Unbind();
	}

	void Shader::SetInt(const std::string& name, const int value)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform1i(loc, value);
		Unbind();
	}

	void Shader::SetFloat(const std::string& name, const float value)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform1f(loc, value);
		Unbind();
	}

	void Shader::SetVector2(const std::string& name, const Vector2& vector2)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform2f(loc, vector2.x, vector2.y);
		Unbind();
	}

	void Shader::SetVector3(const std::string& name, const Vector3& vector3)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform3f(loc, vector3.x, vector3.y, vector3.z);
		Unbind();
	}

	void Shader::SetVector4(const std::string& name, const Vector4& vector4)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform4f(loc, vector4.x, vector4.y, vector4.z, vector4.w);
		Unbind();
	}

	uint Shader::GetLocation(const std::string& name)
	{
		int loc = glGetUniformLocation(handle, name.c_str());
		std::string err = name + " doesn't exist in the shader!";
		CB_ASSERT_MSG(loc != -1, err);
		return loc;
	}

}



