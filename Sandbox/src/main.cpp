#include <iostream>
#include <Core/CarbonCore.hpp>
#include <GLFW/glfw3.h>

static Ref<Carbon::Renderer::Camera> cam;

struct Velocity
{
	Velocity(Vector3 initialVelocity) : velocity(initialVelocity) {};
	Vector3 velocity;
};

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

		Ref<Carbon::Renderer::Mesh> square = CreateRef<Carbon::Renderer::Mesh>(vertices, indices, s);

		auto& scene = Carbon::Application::GetActiveScene();
		paddle = scene.CreateEntity();
		paddle.AddComponent<Carbon::Transform>(Vector3{ 2.95f, 0, 3 }, Vector3{0.25f, 0.75f, 1});
		paddle.AddComponent<Carbon::MeshRenderer>(square, mat);
		paddle.AddComponent<Carbon::BoxCollider>(OnCollision, Vector3{ 0, 0, 0 }, Vector3{ 0.25f, 0.75f, 1 });

		paddle2 = scene.CreateEntity();
		paddle2.AddComponent<Carbon::Transform>(Vector3{ -2.95f, 0, 3 }, Vector3{ 0.25f, 0.75f, 1 });
		paddle2.AddComponent<Carbon::MeshRenderer>(square, mat);
		paddle2.AddComponent<Carbon::BoxCollider>(OnCollision, Vector3{ 0, 0, 0 }, Vector3{ 0.25f, 0.75f, 1 });

		ball = scene.CreateEntity();
		ball.AddComponent<Carbon::Transform>(Vector3{ 1.5f, 0, 3 }, Vector3{ 0.2f, 0.2f, 0.2f });
		ball.AddComponent<Carbon::MeshRenderer>(square, mat);
		ball.AddComponent<Carbon::BoxCollider>(OnCollision, Vector3{ 0, 0, 0 }, Vector3{ 0.2f, 0.2f, 0.2f });
		ball.AddComponent<Velocity>(glm::normalize(Vector3{0.5f, 0.5f, 0}));

		input = new char[64];
		input[0] = '\0';
	};

	virtual void OnDetach() override {};

	virtual void OnImGUIRender() override 
	{
		ImGui::Begin("Cool window");

		ImGui::Text("Colliding: %s", quadsColliding ? "true" : "false");

		ImGui::Text("Deltatime: %f\nElapsed time: %f\nLast frame elapsed time: %f", Carbon::Time::GetTime().deltatime, Carbon::Time::GetTime().elapsedTime, Carbon::Time::lastframetime);

		ImGui::Text("Score player A(left) - %d", scorePlayerA);

		ImGui::Text("Score player B(right) - %d", scorePlayerB);

		quadsColliding = false;

		float* paddleDims = new float[3];
		paddleDims[0] = paddle2.GetComponent<Carbon::Transform>().size.x;
		paddleDims[1] = paddle2.GetComponent<Carbon::Transform>().size.y;
		paddleDims[2] = paddle2.GetComponent<Carbon::Transform>().size.z;

		if (ImGui::InputFloat3("Paddle dims: ", paddleDims, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
		{
			paddle.GetComponent<Carbon::Transform>().size = Vector3{ paddleDims[0], paddleDims[1], paddleDims[2] };
			paddle2.GetComponent<Carbon::Transform>().size = Vector3{ paddleDims[0], paddleDims[1], paddleDims[2] };
		}

		float* ballsize = new float[1];
		ballsize[0] = ball.GetComponent<Carbon::Transform>().size.x;

		if (ImGui::InputFloat("Ball size: ", ballsize, 0.f, 0.f, "%.6f", ImGuiInputTextFlags_EnterReturnsTrue))
		{
			ball.GetComponent<Carbon::Transform>().size = Vector3{*ballsize, *ballsize, *ballsize};
		}

		ImGui::InputFloat("Ball speed: ", &ballSpeed, 0.f, 0.f, "%.6f");

		ImGui::SliderFloat("Paddle speed: ", &paddleSpeed, 0.0f, 10.0f, "%.5f");

		ImGui::End();
	};

	virtual void OnUpdate() override 
	{
		GL_FIND_ERROR();

		if (Carbon::Input::GetKeyDown(GLFW_KEY_UP))
			paddle2.GetComponent<Carbon::Transform>().position.y += Carbon::Time::GetTime().deltatime * paddleSpeed;

		if (Carbon::Input::GetKeyDown(GLFW_KEY_DOWN))
			paddle2.GetComponent<Carbon::Transform>().position.y -= Carbon::Time::GetTime().deltatime * paddleSpeed;


		if (Carbon::Input::GetKeyDown(GLFW_KEY_W))
			paddle.GetComponent<Carbon::Transform>().position.y += Carbon::Time::GetTime().deltatime * paddleSpeed;

		if (Carbon::Input::GetKeyDown(GLFW_KEY_S))
			paddle.GetComponent<Carbon::Transform>().position.y -= Carbon::Time::GetTime().deltatime * paddleSpeed;

		Carbon::Transform& ballTransform = ball.GetComponent<Carbon::Transform>();
		Velocity& ballVelocity = ball.GetComponent<Velocity>();

		ballTransform.position += ballVelocity.velocity * ballSpeed * Carbon::Time::GetTime().deltatime;

		if (ballTransform.position.x < -3.077f || ballTransform.position.x > 3.077f)
		{
			if (ballVelocity.velocity.x < 0)
				scorePlayerA++;
			else if (ballVelocity.velocity.x > 0)
				scorePlayerB++;
			ballTransform.position.x = 0;
			ballTransform.position.y = 0;
			ballVelocity.velocity.x = -ballVelocity.velocity.x;
		}
		if (ballTransform.position.y < -1.732f || ballTransform.position.y > 1.732f) 
		{
			ballVelocity.velocity.y = -ballVelocity.velocity.y;
		}
	};

	virtual void OnEvent(Carbon::Event& e) override 
	{

	};

	static void OnCollision(Carbon::Entity A, Carbon::Entity B)
	{
		if(A == ball && (B == paddle || B == paddle2))
		{
			A.GetComponent<Velocity>().velocity.x *= -1;
		}
		
	}

private:
	static inline Carbon::Entity paddle;
	static inline Carbon::Entity paddle2;
	static inline Carbon::Entity ball;

	Ref<Carbon::GL::Shader> s;
	Ref<Carbon::Renderer::Material> mat;
	inline static bool quadsColliding = false;
	int scorePlayerA;
	int scorePlayerB;
	char* input;
	float paddleSpeed = 1.5f;
	float ballSpeed = 1.0f;
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