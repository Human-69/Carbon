#include "OpenGLContext.h"
#include "cbpch.h"

namespace Carbon::GL {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : windowHandle(windowHandle)
	{
		
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle);

		CB_ASSERT_MSG(glewInit() == GLEW_OK, "Failed to initialize GLEW!");

		std::cout << "Created new OpenGL context\n";
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}