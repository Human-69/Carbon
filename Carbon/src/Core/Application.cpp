#include "Application.h"
#include "GL/RenderCommands.h"
#include "GLFW/glfw3.h"

namespace Carbon
{

	Scope<Application> Application::instance;
	Scope<Scene> Application::scene = CreateScope<Scene>();;

	Application::Application(const std::string name)
	{
		window = Window::Create(1920, 1080, name);
		window->SetEventCallback([this](Event& e) { this->OnEvent(e); });
		camera = CreateRef<Renderer::Camera>(60, 0.01, 100, 16.0f / 9.0f);
		imguiLayer = new ImGUILayer();
		layerStack.PushOverlay(imguiLayer);
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
			Carbon::GL::RendererCommands::Clear();

			scene->OnUpdate(*camera);

			imguiLayer->Begin();

			//Top most layers(last) render last
			//Forward iterate through normal layers
			for(auto layerIdx = layerStack.begin(); layerIdx!=layerStack.beginOverlay(); ++layerIdx)
			{
				auto layer = *layerIdx;
				layer->OnUpdate();
				layer->OnImGUIRender();
			}

			for (auto overlayIdx = layerStack.beginOverlay(); overlayIdx != layerStack.end(); ++overlayIdx)
			{
				auto overlay = *overlayIdx;
				overlay->OnUpdate();
				overlay->OnImGUIRender();
			}

			imguiLayer->End();

			
			window->OnUpdate();
			Input::OnEndFrame();
		}
	}
}