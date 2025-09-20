#include "Application.h"
#include "GLFW/glfw3.h"

namespace Carbon
{

	Scope<Application> Application::instance;

	Application::Application(const std::string name)
	{
		window = Window::Create(1920, 1080, name);
		window->SetEventCallback([this](Event& e) { this->OnEvent(e); });
		camera = CreateRef<Renderer::Camera>(60, 0.01, 100, 16.0f/9.0f);
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
		//The top most(last) layers receive events first
		//Reverse iterate
		for (int i = (int)layerStack.size() - 1; i >= 0; i--) 
		{
			//If the last layer handled the event don't pass it on
			if (e.handled) break;
			(*(layerStack.begin() + i))->OnEvent(e);
		}
	}

	void Application::Run()
	{
		while (running) 
		{
			Time::OnUpdate();
			Input::OnBeginFrame();

			camera->BegindDraw();

			//Top most layers(last) render last
			//Forward iterate
			for (Layer* layer : layerStack)
			{
				layer->OnUpdate();
			}
			
			window->OnUpdate();
			Input::OnEndFrame();
		}
	}
}