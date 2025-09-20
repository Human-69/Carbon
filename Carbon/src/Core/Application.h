#pragma once
#include "cbpch.h"
#include "LayerStack.h"
#include "Window.h"
#include "Renderer/Camera.h"
#include "CarbonTypes.h"
#include "Input.h"

int main();

namespace Carbon {
	class Application
	{
	public:
		Application(const std::string name);
		virtual ~Application();

		static Application& Get() { return *instance; }

		Window& GetWindow() { return *window; };
		void OnEvent(Event& e);
	protected:
		LayerStack layerStack;
		Ref<Renderer::Camera> camera;

	private:
		Scope<Window> window;
		static Scope<Application> instance;
		bool running;
		void Run();
		friend int ::main();
	};
}
