#pragma once
#include <CarbonTypes.h>

/* Carbon::GL */
#include "Shader.h"
#include "Camera.h"
#include "Buffer.h"


namespace Carbon::GL
{
	struct Vertex
	{
		Vector3 position;
		Vector2 uv;
	};

	class Mesh
	{
	public:
		/// <summary>
		/// Carbon::GL::Mesh, generates openGL buffers and leaves them empty
		/// </summary>
		Mesh(Ref<Shader> shader);

		/// <summary>
		/// Carbon::GL::Mesh, generates openGL buffers and loads the data into them
		/// </summary>
		Mesh(std::vector<Vertex>& vertices, std::vector<uint>& indices, Ref<Shader> shader);

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
		Ref<Shader> shader;
		uint VAO;
		Ref<VertexBuffer> VBO;
		Ref<IndexBuffer> IBO;
	};
}