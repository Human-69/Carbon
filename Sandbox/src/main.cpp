#include <iostream>
#include <Core/CarbonCore.hpp>
#include <GL/Mesh.h>
#include <Platform/Windows/WindowsWindow.h>
#include "Platform/OpenGL/OpenGLTexture.h"

int main()
{
	std::cout << "Running!\n";

	Carbon::WindowsWindow w(1920, 1080, "Window");

	Ref<Carbon::GL::Shader> s = Carbon::GL::Shader::Create("D:\\Carbon\\Carbon\\Sandbox\\src\\shader.vs", "D:\\Carbon\\Carbon\\Sandbox\\src\\shader.fragmentShader");

	std::vector<Carbon::GL::Vertex> vertices =
	{
		Carbon::GL::Vertex{Vector3{-0.5f, -0.5f, 0.f}, Vector2{0, 0}},
		Carbon::GL::Vertex{Vector3{0.5f, -0.5f, 0.f}, Vector2{1, 0}},
		Carbon::GL::Vertex{Vector3{0.f, 0.5f, 0.f}, Vector2{0.5, 1}},
	};

	std::vector<uint> indices = { 2, 1, 0 };

	Carbon::GL::Mesh m(vertices, indices, s);

	GL_FIND_ERROR();

	Ref<Carbon::GL::Texture2D> t = Carbon::GL::Texture2D::Create("D:\\Carbon\\Carbon\\Carbon\\res\\u like boys, don't you.jpg");

	GL_FIND_ERROR();

	t->Bind(0);

	GL_FIND_ERROR();

	s->SetInt("tex", 0);

	GL_FIND_ERROR();

	while (!w.ShouldWindowClose())
	{
		glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		m.Render();
		GL_FIND_ERROR();

		w.SwapBuffers();
		glfwPollEvents();
	}

	return 0;
}