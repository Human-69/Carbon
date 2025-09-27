#include "Core/Input.h"
#include "Core/Application.h"
#include "GLFW/glfw3.h"

namespace Carbon
{

	Vector2 Input::lastmousepos;
	Vector2 Input::currentmousepos;

	void Input::OnBeginFrame() 
	{
		currentmousepos = GetMousePos();
	}

	void Input::OnEndFrame() 
	{
		lastmousepos = currentmousepos;
	}

	Vector2 Input::GetMouseOffset()
	{
		return currentmousepos - lastmousepos;
	}

	Vector2 Input::GetMousePos() 
	{
		glm::dvec2 mp;
		glfwGetCursorPos((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), &mp.x, &mp.y);
		return Vector2{ (float)mp.x, (float)mp.y };
	}

	bool Input::GetMouseButtonDown(uint mousebutton) 
	{
		return glfwGetMouseButton((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), mousebutton) == GLFW_PRESS;
	}

	bool Input::GetKeyDown(uint keycode) 
	{
		return glfwGetKey((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), keycode) == GLFW_PRESS;
	}
}