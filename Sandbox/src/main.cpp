#include <iostream>
#include <Core/CarbonCore.hpp>
#include <GL/CarbonGL.hpp>
#include <Platform/Windows/WindowsWindow.h>


int main()
{
	std::cout << "Running!\n";

	Carbon::WindowsWindow w(1920, 1080, "Window");

	while(!w.ShouldWindowClose())
	{
		w.SwapBuffers();
		glfwPollEvents();
	}

	return 0;
}