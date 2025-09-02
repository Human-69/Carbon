#pragma once
#include "Event.h"

namespace Carbon
{
	class KeyEvent : public Event
	{
	public:
		int GetKeycode() const { return keycode; }
		int GetCategory() const override
		{
			return EventKey | EventInput;
		}
	protected:
		KeyEvent(int keycode) : keycode(keycode) {};
	private:
		int keycode;
	};

	class KeyPressed : public KeyEvent
	{
	public:
		KeyPressed(int keycode) : KeyEvent(keycode) {}

		static EventType StaticGetType()
		{
			return EventType::KeyPressed;
		}

		EventType GetType() const override
		{
			return StaticGetType();
		}

		const char* GetName() const override
		{
			return "KeyPressed";
		}
	};

	class KeyReleased : public KeyEvent
	{
	public:
		KeyReleased(int keycode) : KeyEvent(keycode) {}

		static EventType StaticGetType()
		{
			return EventType::KeyReleased;
		}

		EventType GetType() const override
		{
			return StaticGetType();
		}

		const char* GetName() const override
		{
			return "KeyReleased";
		}
	};
}