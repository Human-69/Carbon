#include "OpenGLShader.h"
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


namespace Carbon::GL::OpenGL
{
	OpenGLShader::OpenGLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
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

		handle = glCreateProgram();

		glAttachShader(handle, vertexShader);
		glAttachShader(handle, fragmentShader);
		glLinkProgram(handle);

		glGetProgramiv(handle, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(handle, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINKING::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(handle);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetMatrix4(const std::string& name, const Matrix4& value)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetInt(const std::string& name, const int value)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform1i(loc, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, const float value)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform1f(loc, value);
	}

	void OpenGLShader::SetVector2(const std::string& name, const Vector2& vector2)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform2f(loc, vector2.x, vector2.y);
	}

	void OpenGLShader::SetVector3(const std::string& name, const Vector3& vector3)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform3f(loc, vector3.x, vector3.y, vector3.z);
	}

	void OpenGLShader::SetVector4(const std::string& name, const Vector4& vector4)
	{
		Bind();
		uint loc = GetLocation(name);
		glUniform4f(loc, vector4.x, vector4.y, vector4.z, vector4.w);
	}

	uint OpenGLShader::GetLocation(const std::string& name)
	{
		int loc = glGetUniformLocation(handle, name.c_str());
		std::string err = name + " doesn't exist in the shader!";
		CB_ASSERT_MSG(loc != -1, err);
		return loc;
	}
}