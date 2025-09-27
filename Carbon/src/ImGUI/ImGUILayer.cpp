#include "ImGUILayer.h"
#include "Application.h"

namespace Carbon
{
	void ImGUILayer::OnAttach()
	{
		ImGuiContext* context = ImGui::CreateContext();
		ImGui::SetCurrentContext(context);
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void ImGUILayer::OnDetach()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	};

	void ImGUILayer::OnImGUIRender()
	{

	};

	void ImGUILayer::Begin()
	{
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
	};

	void ImGUILayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGui::EndFrame();
	};

	void ImGUILayer::OnUpdate()
	{

	};

	void ImGUILayer::OnEvent(Carbon::Event& e)
	{

	}
}