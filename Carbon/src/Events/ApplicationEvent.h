#pragma once
#include "Event.h"

namespace Carbon
{
	class WindowCloseEvent : public Event
	{
	public:

		static EventType StaticGetType()
		{
			return EventType::WindowClose;
		}

		EventType GetType() const override
		{
			return StaticGetType();
		}

		const char* GetName() const override
		{
			return "WindowClose";
		}

		int GetCategory() const override
		{
			return EventApplication;
		}
	};

	class WindowResizeEvent : public Event
	{
	public:

		WindowResizeEvent(int width, int height) : width(width), height(height) {};

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }

		static EventType StaticGetType()
		{
			return EventType::WindowResize;
		}

		EventType GetType() const override
		{
			return StaticGetType();
		}

		const char* GetName() const override
		{
			return "WindowResize";
		}

		int GetCategory() const override
		{
			return EventApplication;
		}

	private:
		int width;
		int height;
	};
}