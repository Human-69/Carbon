#include "Application.h"
#include "GLFW/glfw3.h"

namespace Carbon
{
	Application::Application(const std::string name)
	{
		window = Window::Create(1920, 1080, name);
		window->SetEventCallback([this](Event& e) { this->OnEvent(e); });
	}

	Application::~Application()
	{
		
	}

	void Application::OnEvent(Event& e)
	{
		
	}

	void Application::Run()
	{
		while (!window->ShouldWindowClose()) {
			for (Layer* layer : layerStack)
			{
				layer->OnUpdate();
			}
			window->SwapBuffers();
			glfwPollEvents();
		}
	}
}