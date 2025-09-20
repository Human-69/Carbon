#include "Camera.h"
#include "cbpch.h"

/* glfw */
#include <GLFW/glfw3.h>

namespace Carbon::Renderer
{
	Camera::Camera(float fov, float nearClipPlane, float farClipPlane, float aspect) : fov(fov), nearClipPlane(nearClipPlane), farClipPlane(farClipPlane), aspectRatio(aspect)
	{
		
	}

	void Camera::BegindDraw()
	{
		Matrix4 projection = glm::perspective(glm::radians(fov), aspectRatio, nearClipPlane, farClipPlane);
		Matrix4 view = glm::lookAt(position, position+forward, up);
		projectionView = projection * view;	
	}

	void Camera::EndDraw(Window& window)
	{
		window.OnUpdate();
	}
}