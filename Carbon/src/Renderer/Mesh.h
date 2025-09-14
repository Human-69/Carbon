#pragma once
#include <CarbonTypes.h>

/* Carbon::GL */
#include "Camera.h"
#include "../GL/Shader.h"
#include "../GL/Buffer.h"
#include "../GL/VertexArray.h"


namespace Carbon::Renderer
{
	struct Vertex
	{
		Vector3 position;
		Vector2 uv;
	};

	class Mesh
	{
	public:

		Mesh() = default;

		/// <summary>
		/// Carbon::GL::Mesh, generates openGL buffers and leaves them empty
		/// </summary>
		Mesh(Ref<GL::Shader> shader);

		/// <summary>
		/// Carbon::GL::Mesh, generates openGL buffers and loads the data into them
		/// </summary>
		Mesh(std::vector<Vertex>& vertices, std::vector<uint>& indices, Ref<GL::Shader> shader);

		/// <summary>
		/// Carbon::GL::Mesh::LoadData, uploads the given data to the GPU buffers
		/// </summary>
		void LoadData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);

		/// <summary>
		/// Renders at 0,0, 0 with no scaling and no rotation
		/// </summary>
		void Render();

		/// <summary>
		/// Renders the mesh according to the transform provided
		/// </summary>
		void Render(Matrix4 transform);

		int vertexCount;
		int indexCount;
	private:
		Ref<GL::Shader> shader;
		Ref<GL::VertexArray> VAO;
		Ref<GL::VertexBuffer> VBO;
		Ref<GL::IndexBuffer> IBO;
	};
}