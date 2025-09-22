#pragma once
#include <CarbonTypes.h>
#include "Window.h"

struct GLFWwindow;

namespace Carbon::Renderer
{
	/// <summary>
	/// Carbon::GL::projectionView, the combined matrix of projection and view. Calculated by Carbon::GL::BeginDraw every frame
	/// </summary>
	inline Matrix4 projectionView = Matrix4(1.0f);

	class Camera
	{
	public:
		Camera(float fov, float nearClipPlane, float farClipPlane, float aspect) : fov(fov), nearClipPlane(nearClipPlane), farClipPlane(farClipPlane), aspectRatio(aspect) {};

		Matrix4 GetProjectionView() const 
		{
			Matrix4 projection = glm::perspective(glm::radians(fov), aspectRatio, nearClipPlane, farClipPlane);
			Matrix4 view = glm::lookAt(position, position + forward, up);
			return projection * view;
		}

		Vector3 position = Vector3{ 0, 0, 0 };
		float fov;

	private:
		Vector3 forward = Vector3{0, 0, 1};
		Vector3 up = Vector3{ 0, 1, 0 };

		float nearClipPlane;
		float farClipPlane;
		float aspectRatio;
	};

}