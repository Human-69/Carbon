#pragma once
#include "GL/Context.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Carbon::GL {
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};
}