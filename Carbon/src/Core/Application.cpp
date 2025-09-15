#include "Application.h"
#include "GLFW/glfw3.h"

namespace Carbon
{
	Application::Application(const std::string name)
	{
		window = Window::Create(1920, 1080, name);
		window->SetEventCallback([this](Event& e) { this->OnEvent(e); });
		running = true;
	}

	Application::~Application()
	{
		
	}

	void Application::OnEvent(Event& e)
	{
		/* Application events */
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& wce)->bool
			{
				running = false;
				return true;
			});
		dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& wre)
			{
				/* TODO: Actually resize the viewport */
				return true;
			});

		/* Input events */
		//Input events are handled by layers
		for (Layer* layer : layerStack)
			layer->OnEvent(e);
	}

	void Application::Run()
	{
		while (running) {
			for (Layer* layer : layerStack)
			{
				layer->OnUpdate();
			}
			window->SwapBuffers();
			glfwPollEvents();
		}
	}
}