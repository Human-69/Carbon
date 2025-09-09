#include <iostream>
#include <Core/CarbonCore.hpp>
#include <GL/Mesh.h>
#include <Platform/Windows/WindowsWindow.h>

int main()
{
	std::cout << "Running!\n";

	Carbon::WindowsWindow w(1920, 1080, "Window");

	Carbon::GL::Shader s("D:\\Carbon\\Carbon\\Sandbox\\src\\shader.vs", "D:\\Carbon\\Carbon\\Sandbox\\src\\shader.fragmentShader");

	std::vector<Carbon::GL::Vertex> vertices =
	{
		Carbon::GL::Vertex{Vector3{-0.5f, -0.5f, 0.f}},
		Carbon::GL::Vertex{Vector3{0.5f, -0.5f, 0.f}},
		Carbon::GL::Vertex{Vector3{0.f, 0.5f, 0.f}},
	};

	std::vector<uint> indices = { 2, 1, 0 };

	Carbon::GL::Mesh m(vertices, indices, &s);

	while (!w.ShouldWindowClose())
	{
		glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		m.Render();

		w.SwapBuffers();
		glfwPollEvents();
	}

	return 0;
}