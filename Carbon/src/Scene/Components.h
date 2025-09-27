#pragma once

#include "cbpch.h"
#include "Entity.h"

namespace Carbon
{
	namespace Renderer 
	{
		class Mesh;
		class Material;
	}

	struct Transform
	{
		Transform(Vector3 position, Vector3 size) : position(position), size(size) {};

		Vector3 position;
		Vector3 size;
	};

	struct MeshRenderer
	{
		MeshRenderer(Ref<Renderer::Mesh> mesh, Ref<Renderer::Material> material) : mesh(mesh), material(material) {};

		Ref<Renderer::Material> material;
		Ref<Renderer::Mesh> mesh;
	};

	struct BoxCollider;

	typedef std::function<void(Entity colliderA, Entity colliderB)> OnCollisionFn;

	struct BoxCollider
	{
		BoxCollider(OnCollisionFn onCollision, Vector3 offset, Vector3 size) : onCollision(onCollision), offset(offset), size(size) {}

		Vector3 offset; // Offset from the objects transform.position
		Vector3 size; //Width, Height and Depth of the box
		OnCollisionFn onCollision;
	};

}