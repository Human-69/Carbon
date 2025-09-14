#pragma once

#include "Window.h"
#include "../OpenGL/OpenGLContext.h"

namespace Carbon {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(int width = 1920, int height = 1080, std::string name = "Carbon");

		virtual void SetEventCallback(const EventCallbackFn& callback) override;

		virtual int GetWidth() override;
		virtual int GetHeight() override;

		virtual void SwapBuffers() override;
		virtual bool ShouldWindowClose() override;

		struct WindowData
		{
			int width;
			int height;
			std::string name;
			EventCallbackFn eventCallback;
		};

	private:
		WindowData data;
		GLFWwindow* window;
		GL::OpenGLContext* context;
	};
}