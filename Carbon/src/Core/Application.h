#pragma once
#include "cbpch.h"
#include "LayerStack.h"
#include "Window.h"
#include "Renderer/Camera.h"
#include "CarbonTypes.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "ImGUI/ImGUILayer.h"

int main();

namespace Carbon {
	class Application
	{
	public:
		Application(const std::string name);
		virtual ~Application();

		static Application& Get() { return *instance; }
		static Scene& GetActiveScene() { return *scene; }

		Window& GetWindow() { return *window; };
		void OnEvent(Event& e);
	protected:
		LayerStack layerStack;
		Ref<Renderer::Camera> camera;
		static Scope<Scene> scene;

	private:
		Scope<Window> window;
		ImGUILayer* imguiLayer;
		static Scope<Application> instance;
		bool running;
		void Run();
		friend int ::main();
	};
}
