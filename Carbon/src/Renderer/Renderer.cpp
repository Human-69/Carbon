#include "Renderer.h"
#include "GL/RenderCommands.h"

namespace Carbon::Renderer
{

	Matrix4 Renderer::projectionView;

	void Renderer::BeginScene(Camera& camera)
	{
		projectionView = camera.GetProjectionView();
		GL::RendererCommands::Clear();
	}

	void Renderer::RenderMesh(Mesh& mesh)
	{
		mesh.shader->Bind();

		mesh.shader->SetMatrix4("pv", Renderer::GetProjectionView());

		GL::RendererCommands::DrawIndexed(mesh.VAO, mesh.indexCount);
	}

	void Renderer::RenderMesh(Mesh& mesh, Matrix4 transform)
	{
		mesh.shader->Bind();

		mesh.shader->SetMatrix4("model", transform);

		mesh.shader->SetMatrix4("pv", Renderer::GetProjectionView());

		GL::RendererCommands::DrawIndexed(mesh.VAO, mesh.indexCount);
	}
}