#pragma once
#include "Utils/Time.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Carbon
{
	class Input
	{
	public:
		static void OnBeginFrame();
		static void OnEndFrame();
		static Vector2 GetMouseOffset();
		static Vector2 GetMousePos();
		static bool GetMouseButtonDown(uint mousebutton);
		static bool GetKeyDown(uint keycode);
	private:
		static Vector2 lastmousepos;
		static Vector2 currentmousepos;
	};	
}