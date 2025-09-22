#pragma once

#include "Layer.h"

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_internal.h>

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "Window.h"

namespace Carbon
{
	class ImGUILayer : public Layer
	{
	public:
		virtual void OnAttach() override;

		virtual void OnDetach() override;
		
		virtual void OnImGUIRender() override;

		void Begin();

		void End();

		virtual void OnUpdate() override;

		virtual void OnEvent(Carbon::Event& e) override;
	};
}