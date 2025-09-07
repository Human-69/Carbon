#pragma once
#include "Events/Event.h"
#include <string>

namespace Carbon {

	typedef void (*EventCallbackFn)(Event&);

	class Window
	{
	public:

		Window() = default;

		/// <summary>
		/// Creates a new window and a new graphics context
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="name"></param>
		/// <returns></returns>
		Window* CreateWindow(int width = 1920,
								   int height=1080,
								   std::string name="Carbon");

		virtual void SwapBuffers() = 0;
		virtual bool ShouldWindowClose() = 0;

		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
	};
}