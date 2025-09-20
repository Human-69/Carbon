#include "WindowsWindow.h"
#include "cbpch.h"

#include "GL/glew.h"

namespace Carbon
{
	WindowsWindow::WindowsWindow(int width, int height, std::string name)
	{
		CB_ASSERT_MSG(glfwInit(), "Failed to initialize glfw!");
		window = glfwCreateWindow(width, height, (name == "" ? "Carbon" : name).c_str(), NULL, NULL);
		CB_ASSERT_MSG(window, "Failed to create a window!");
		
		context = CreateScope<GL::OpenGLContext>(window);
		context->Init();

		glfwSetKeyCallback(window, [](GLFWwindow* glfwwindow, int key, int scancode, int action, int mods)->void 
			{
				WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(glfwwindow);
				KeyEvent* e;
				if(action == GLFW_PRESS) e = new KeyPressed(key);
				else if(action == GLFW_RELEASE) e = new KeyReleased(key);

				if (windowData->eventCallback && action != GLFW_REPEAT)
					windowData->eventCallback(*e);
			});

		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* glfwwindow, int width, int height)->void
			{
				WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(glfwwindow);
				WindowResizeEvent e(width, height);
				if (windowData->eventCallback)
					windowData->eventCallback(e);
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* glfwwindow)->void
			{
				WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(glfwwindow);
				WindowCloseEvent e;
				if (windowData->eventCallback)
					windowData->eventCallback(e);
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
				MouseButtonEvent* e;
				if (action == GLFW_PRESS) e = new MouseButtonPressed(button);
				else if (action == GLFW_RELEASE) e = new MouseButtonReleased(button);
				
				if (windowData->eventCallback)
					windowData->eventCallback(*e);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

				MouseMoveEvent mme(Vector2{ xpos, ypos });
				
				if (windowData->eventCallback)
					windowData->eventCallback(mme);
			});

		data.width = width;
		data.height = height;
		data.name = (name == "" ? "Carbon" : name);
		data.eventCallback = nullptr;
		glfwSetWindowUserPointer(window, &data);
	}

	void WindowsWindow::OnUpdate()
	{
		SwapBuffers();
		glfwPollEvents();
	}
		
	void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		data.eventCallback = callback;
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