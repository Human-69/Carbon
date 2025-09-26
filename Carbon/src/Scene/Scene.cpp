#include "Scene.h"
#include "Renderer/Renderer.h"

namespace Carbon 
{

	bool IsCollidingAABB(Vector3 posA, Vector3 sizeA, Vector3 posB, Vector3 sizeB)
	{
		Vector3 minA = posA;
		Vector3 maxA = posA + sizeA;
		Vector3 minB = posB;
		Vector3 maxB = posB + sizeB;
		return (
			minA.x <= maxB.x &&
			maxA.x >= minB.x &&
			minA.y <= maxB.y &&
			maxA.y >= minB.y &&
			minA.z <= maxB.z &&
			maxA.z >= minB.z
			);
	}

	void Scene::OnUpdate(Renderer::Camera& mainCamera)
	{
		Renderer::Renderer::BeginScene(mainCamera);

		// Perform collision checks on every entity with a Transform and a BoxCollider
		auto colliderView = GetView<Transform, BoxCollider>();
		for(auto [entity, transform, boxCollider] : colliderView.each())
		{
			// Check collision against every other boxCollider
			for (auto [entity2, transform2, boxCollider2] : colliderView.each())
			{
				// Make sure the entities are different objects
				if (entity == entity2) continue;

				if(IsCollidingAABB(transform.position+boxCollider.offset, boxCollider.size, transform2.position+boxCollider2.offset, boxCollider2.size))
				{
					if (boxCollider.onCollision)
						collisionQueue.push_back(std::make_tuple(boxCollider.onCollision, &boxCollider, &boxCollider2));
				}
			}
		}

		for (auto& [collisonfn, boxColliderA, boxColliderB] : collisionQueue)
			collisonfn(boxColliderA, boxColliderB);

		collisionQueue.clear();

		// Render every entity with a MeshRenderer and a Transform
		for (auto [entity, transform, renderer] : GetView<Transform, MeshRenderer>().each())
		{
			Matrix4 model = Matrix4(1);
			model = glm::translate(model, transform.position);
			Renderer::Renderer::RenderMesh(*renderer.mesh, model);
		}
	}
}