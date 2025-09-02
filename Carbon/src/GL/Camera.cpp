#include "Camera.h"

namespace Carbon::GL
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

	void Camera::EndDraw(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}