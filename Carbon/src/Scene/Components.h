#pragma once

#include "cbpch.h"

namespace Carbon
{
	namespace Renderer 
	{
		class Mesh;
	}

	struct Transform
	{

		Transform(Vector3 position) : position(position) {};

		Vector3 position;
	};

	struct MeshRenderer
	{
		MeshRenderer(Ref<Renderer::Mesh> mesh) : mesh(mesh) {};

		Ref<Renderer::Mesh> mesh;
	};

}