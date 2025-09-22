#pragma once

#include "cbpch.h"
#include "Camera.h"
#include "Mesh.h"

namespace Carbon::Renderer
{
	class Renderer
	{
	public:

		static void BeginScene(Camera& camera);

		static void RenderMesh(Mesh& mesh);

		static void RenderMesh(Mesh& mesh, Matrix4 transform);

		static Matrix4 GetProjectionView() { return projectionView; };
	private:
		static Matrix4 projectionView;
	};
}