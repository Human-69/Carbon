#include "Scene.h"
#include "Renderer/Renderer.h"

namespace Carbon 
{

	void Scene::OnUpdate(Renderer::Camera& mainCamera)
	{
		Renderer::Renderer::BeginScene(mainCamera);

		//Render every entity with a MeshRenderer and a Transform
		for (auto [entity, transform, renderer] : GetView<Transform, MeshRenderer>().each())
		{
			Matrix4 model = Matrix4(1);
			model = glm::translate(model, transform.position);
			Renderer::Renderer::RenderMesh(*renderer.mesh, model);
		}
	}
}