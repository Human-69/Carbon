#pragma once

namespace Carbon 
{

	enum class EventType
	{
		WindowClose, WindowResize,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseScroll,
	};

	enum EventCategory
	{
		None = 0,
		EventApplication = 1,
		EventKey = 2,
		EventMouse = 4,
		EventInput = 8,

	};

	class Event
	{
	public:
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategory() const = 0;
		bool handled;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : e(e) {};

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if(e.GetType() == T::StaticGetType())
			{
				e.handled |= func(* (T*) & e);
				return true;
			}
			return false;
		}
	private:
		Event& e;
	};
}
