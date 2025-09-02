#pragma once

#include "cbpch.h"
#include "Events/Event.h"
#include <GLFW/glfw3.h>

namespace Carbon {

	typedef void (*EventCallbackFn)(Event&);

	class Window
	{
	public:
		/// <summary>
		/// Creates a new window and a new OpenGL context
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="name"></param>
		/// <returns></returns>
		static Window CreateWindow(int width=1920,
								   int height=1080,
								   std::string name="Carbon");

		int GetWidth();
		int GetHeight();

	private:
		GLFWwindow* window;

		struct WindowData
		{
			int width;
			int height;
			std::string name;
			EventCallbackFn eventCallback;
		};
	};
}