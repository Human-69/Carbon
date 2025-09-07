#include "WindowsWindow.h"
#include "cbpch.h"

#include "GL/glew.h"

namespace Carbon
{
	WindowsWindow::WindowsWindow(int width, int height, std::string name)
	{
		CB_ASSERT_MSG(glfwInit(), "Failed to initialize glfw!");
		WindowsWindow* w;
		window = glfwCreateWindow(width, height, (name == "" ? "Carbon" : name).c_str(), NULL, NULL);
		CB_ASSERT_MSG(window, "Failed to create a window!");
		
		context = new GL::OpenGLContext(window);
		context->Init();

		data.width = width;
		data.height = height;
		data.name = (name == "" ? "Carbon" : name);
		data.eventCallback = nullptr;
		glfwSetWindowUserPointer(window, &data);
	}

	int WindowsWindow::GetWidth()
	{
		return data.width;
	}

	int WindowsWindow::GetHeight()
	{
		return data.height;
	}

	void WindowsWindow::SwapBuffers()
	{
		context->SwapBuffers();
	}

	bool WindowsWindow::ShouldWindowClose()
	{
		return glfwWindowShouldClose(window);
	}
}