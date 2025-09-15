#include <iostream>
#include <Core/CarbonCore.hpp>
#include <Renderer/Mesh.h>
#include <Platform/Windows/WindowsWindow.h>
#include "Platform/OpenGL/OpenGLTexture.h"

class SimpleLayer : public Carbon::Layer
{
public:
	virtual void OnAttach() override
	{
		Ref<Carbon::GL::Shader> s = Carbon::GL::Shader::Create("D:\\Carbon\\Carbon\\Sandbox\\src\\shader.vs", "D:\\Carbon\\Carbon\\Sandbox\\src\\shader.fragmentShader");

		std::vector<Carbon::Renderer::Vertex> vertices =
		{
			Carbon::Renderer::Vertex{Vector3{-0.5f, -0.5f, 0.f}, Vector2{0, 0}},
			Carbon::Renderer::Vertex{Vector3{0.5f, -0.5f, 0.f}, Vector2{1, 0}},
			Carbon::Renderer::Vertex{Vector3{0.f, 0.5f, 0.f}, Vector2{0.5, 1}},
		};

		std::vector<uint> indices = { 2, 1, 0 };

		m = Carbon::Renderer::Mesh(vertices, indices, s);

		GL_FIND_ERROR();

		Ref<Carbon::GL::Texture2D> t = Carbon::GL::Texture2D::Create("D:\\Carbon\\Carbon\\Carbon\\res\\u like boys, don't you.jpg");

		GL_FIND_ERROR();

		t->Bind(0);

		GL_FIND_ERROR();

		s->SetInt("tex", 0);

		GL_FIND_ERROR();

		Carbon::GL::RendererCommands::SetClearColor(Color{ 0.25, 1, 0.25, 1 });
	};

	virtual void OnDetach() override {};

	virtual void OnUpdate() override 
	{
		Carbon::GL::RendererCommands::Clear();

		m.Render();
		GL_FIND_ERROR();
	};

	virtual void OnEvent(Carbon::Event& e) override 
	{
		Carbon::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Carbon::KeyPressed>([this](Carbon::KeyPressed& kp)
			{
				std::cout << "Pressed key: " << (char)kp.GetKeycode()<<"\n";
				return true;
			});
		dispatcher.Dispatch<Carbon::KeyReleased>([this](Carbon::KeyReleased& kr)
			{
				std::cout << "Released key: " << (char)kr.GetKeycode() << "\n";
				return true;
			});
	};

private:
	Carbon::Renderer::Mesh m;
};

class SimpleApp : public Carbon::Application
{
public:
	SimpleApp(const std::string& name) : Application(name)
	{
		auto sl = new SimpleLayer();
		sl->OnAttach();
		layerStack.PushLayer(sl);
	}

	~SimpleApp()
	{
	}

private:	
};

Scope<Carbon::Application> CreateApplication(const std::string name)
{
	return CreateScope<SimpleApp>(name);
}