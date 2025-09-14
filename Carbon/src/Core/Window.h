#pragma once
#include "Events/Event.h"
#include <string>
#include <CarbonTypes.h>
#include <functional>

namespace Carbon {

	typedef std::function<void(Event& e)> EventCallbackFn;

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
		static Scope<Window> Create(int width = 1920,
									int height=1080,
									const std::string& name="Carbon");

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void SwapBuffers() = 0;
		virtual bool ShouldWindowClose() = 0;

		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
	};
}