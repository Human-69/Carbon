#include <iostream>
#include <Core/CarbonCore.hpp>
#include <Renderer/Mesh.h>
#include <Platform/Windows/WindowsWindow.h>
#include "Platform/OpenGL/OpenGLTexture.h"

static Ref<Carbon::Renderer::Camera> cam;

class SimpleLayer : public Carbon::Layer
{
public:
	virtual void OnAttach() override
	{
		s = Carbon::GL::Shader::Create("D:\\Carbon\\Carbon\\Sandbox\\src\\shader.vs", "D:\\Carbon\\Carbon\\Sandbox\\src\\shader.fragmentShader");

		std::vector<Carbon::Renderer::Vertex> vertices =
		{
			Carbon::Renderer::Vertex{Vector3{-0.5f, -0.5f, 0.0f}, Vector2{1.0f, 0.0f}},
			Carbon::Renderer::Vertex{Vector3{ 0.5f, -0.5f, 0.0f}, Vector2{0.0f, 0.0f}},
			Carbon::Renderer::Vertex{Vector3{ 0.5f,  0.5f, 0.0f}, Vector2{0.0f, 1.0f}},
			Carbon::Renderer::Vertex{Vector3{-0.5f,  0.5f, 0.0f}, Vector2{1.0f, 1.0f}},
		};

		std::vector<uint> indices = { 2, 1, 0, 
									  0, 3, 2};

		Ref<Carbon::Renderer::Mesh> m = CreateRef<Carbon::Renderer::Mesh>(vertices, indices, s);

		GL_FIND_ERROR();

		Ref<Carbon::GL::Texture2D> t = Carbon::GL::Texture2D::Create("D:\\Carbon\\Carbon\\Carbon\\res\\u like boys, don't you.jpg");

		GL_FIND_ERROR();

		t->Bind(0);

		GL_FIND_ERROR();

		s->SetInt("tex", 0);

		GL_FIND_ERROR();

		Carbon::GL::RendererCommands::SetClearColor(Color{ 0.25, 0.25, 0.25, 1 });

		auto& scene = Carbon::Application::GetActiveScene();
		quad = scene.CreateEntity();
		quad.AddComponent<Carbon::Transform>(Vector3{0, 0, 3});
		quad.AddComponent<Carbon::MeshRenderer>(m);

		input = new char[64];
		input[0] = '\0';
	};

	virtual void OnDetach() override {};

	virtual void OnImGUIRender() override 
	{
		ImGui::Begin("Cool window");
	
		if (ImGui::InputText("Texture path: ", input, 64, ImGuiInputTextFlags_EnterReturnsTrue)) 
		{
			std::string str = std::string(input);
			Ref<Carbon::GL::Texture2D> t = Carbon::GL::Texture2D::Create(str);

			GL_FIND_ERROR();

			t->Bind(0);

			GL_FIND_ERROR();

			s->SetInt("tex", 0);
		};
		ImGui::End();
	};

	virtual void OnUpdate() override 
	{
		GL_FIND_ERROR();
	};

	virtual void OnEvent(Carbon::Event& e) override 
	{
		Carbon::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Carbon::KeyPressed>([this](Carbon::KeyPressed& kp)
			{
				std::cout << "Pressed key: " << (char)kp.GetKeycode()<<"\n";
				if (kp.GetKeycode() == 'W')
				{
					cam->fov += 5;
					std::cout << "Pressed key W\n";
				}
				else if (kp.GetKeycode() == 'S')
					cam->fov -= 5;
				return true;
			});
		dispatcher.Dispatch<Carbon::KeyReleased>([this](Carbon::KeyReleased& kr)
			{
				std::cout << "Released key: " << (char)kr.GetKeycode() << "\n";
				return true;
			});
	};

private:
	Carbon::Entity quad;
	Ref<Carbon::GL::Shader> s;
	char* input;
};

class SimpleApp : public Carbon::Application
{
public:
	SimpleApp(const std::string& name) : Application(name)
	{
		auto sl = new SimpleLayer();
		sl->OnAttach();
		layerStack.PushLayer(sl);
		cam = camera;
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