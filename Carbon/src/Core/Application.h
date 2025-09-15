#pragma once
#include "cbpch.h"
#include "LayerStack.h"
#include "Window.h"
#include "CarbonTypes.h"

int main();

namespace Carbon {
	class Application
	{
	public:
		Application(const std::string name);
		virtual ~Application();

		void OnEvent(Event& e);
	protected:
		LayerStack layerStack;

	private:
		Scope<Window> window;
		bool running;
		void Run();
		friend int ::main();
	};
}
