#include "Window.h"
#include "../Platform/Windows/WindowsWindow.h"

namespace Carbon
{
	Scope<Window> Window::Create(int width, int height, const std::string& name)
	{
#ifdef PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(width, height, name);
#else
		CB_ASSERT_MSG(false, "Unknown platform!");
#endif
	}
}