#include <iostream>
#include <Core/CarbonCore.hpp>

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

		mat = CreateRef<Carbon::Renderer::Material>();	

		Ref<Carbon::Renderer::Mesh> m = CreateRef<Carbon::Renderer::Mesh>(vertices, indices, s);

		GL_FIND_ERROR();

		Ref<Carbon::GL::Texture2D> t = Carbon::GL::Texture2D::Create("D:\\Carbon\\Carbon\\Carbon\\res\\u like boys, don't you.jpg");

		GL_FIND_ERROR();

		mat->AddUniform("tex", t);
		mat->SetMaterial(s);

		GL_FIND_ERROR();

		Carbon::GL::RendererCommands::SetClearColor(Color{ 0.25, 0.25, 0.25, 1 });

		auto& scene = Carbon::Application::GetActiveScene();
		quad = scene.CreateEntity();
		quad.AddComponent<Carbon::Transform>(Vector3{0, 0, 3});
		quad.AddComponent<Carbon::MeshRenderer>(m, mat);
		quad.AddComponent<Carbon::BoxCollider>(OnCollision, Vector3{0, 0, 0}, Vector3{1.0f, 1.0f, 1.0f});

		quad2 = scene.CreateEntity();
		quad2.AddComponent<Carbon::Transform>(Vector3{ 0, 0, 3 });
		quad2.AddComponent<Carbon::MeshRenderer>(m, mat);
		quad2.AddComponent<Carbon::BoxCollider>(OnCollision, Vector3{ 0, 0, 0 }, Vector3{ 1.0f, 1.0f, 1.0f });

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

			mat->SetUniform("tex", t);
			mat->SetMaterial(s);
		};

		ImGui::Text("Colliding: %s", quadsColliding ? "true" : "false");

		quadsColliding = false;

		float* pos = new float[3];
		pos[0] = quad2.GetComponent<Carbon::Transform>().position.x;
		pos[1] = quad2.GetComponent<Carbon::Transform>().position.y;
		pos[2] = quad2.GetComponent<Carbon::Transform>().position.z;

		if(ImGui::InputFloat3("Quad2 position: ", pos, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
		{
			quad2.GetComponent<Carbon::Transform>().position = Vector3{ pos[0], pos[1], pos[2] };
		}

		delete pos;

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

	static void OnCollision(Carbon::BoxCollider* A, Carbon::BoxCollider* B)
	{
		quadsColliding = true;
	}

private:
	Carbon::Entity quad;
	Carbon::Entity quad2;
	Ref<Carbon::GL::Shader> s;
	Ref<Carbon::Renderer::Material> mat;
	inline static bool quadsColliding = false;
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