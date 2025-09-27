#pragma once
#include "Event.h"
#include "cbpch.h"

namespace Carbon 
{
	struct MouseButtonEvent : public Event
	{
	public:
		int GetCategory() const override { return EventMouse | EventInput; }
		int GetMouseButton() const { return mouseButton; }

	protected:
		MouseButtonEvent(int mouseButton) : mouseButton(mouseButton) {}

	private:
		int mouseButton;
	};

	struct MouseButtonPressed : public MouseButtonEvent
	{
	public:
		MouseButtonPressed(int mouseButton) : MouseButtonEvent(mouseButton) {};

		static EventType StaticGetType() { return EventType::MouseButtonPressed; }
		EventType GetType() const override { return StaticGetType(); }
		const char* GetName() const override { return "MouseButtonPressed"; }

	};

	struct MouseButtonReleased : public MouseButtonEvent
	{
	public:
		MouseButtonReleased(int mouseButton) : MouseButtonEvent(mouseButton) {};

		static EventType StaticGetType() { return EventType::MouseButtonReleased; }
		EventType GetType() const override { return StaticGetType(); }
		const char* GetName() const override { return "MouseButtonReleased"; }
	};

	struct MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(Vector2 pos) : pos(pos) {}

		static EventType StaticGetType() { return EventType::MouseMoved; }
		EventType GetType() const override { return StaticGetType(); }
		const char* GetName() const override { return "MouseMoved"; }
		int GetCategory() const override { return EventMouse | EventInput; }
		Vector2 GetMousePos() const { return pos; }

	private:
		Vector2 pos;
	};
}