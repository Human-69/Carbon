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
		Camera(float fov, float nearClipPlane, float farClipPlane, float aspect);

		/// <summary>
		/// Carbon::GL::Camera::BegindDraw, prepares the scene to be drawn from this camera
		/// </summary>
		void BegindDraw();

		/// <summary>
		/// Finishes drawing to the screen, swaps buffers and polls events
		/// </summary>
		void EndDraw(Window& window);

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