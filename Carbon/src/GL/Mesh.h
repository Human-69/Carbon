#pragma once
#include "cbglpch.h"

#include "Types.h"

/* opengl */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
		Mesh(Shader* shader);

		/// <summary>
		/// Carbon::GL::Mesh, generates openGL buffers and loads the data into them
		/// </summary>
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices, Shader* shader);

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
		Shader* shader;
		uint VAO;
		Buffer<Vertex> VBO = Buffer<Vertex>(GL_ARRAY_BUFFER);
		Buffer<uint> IBO = Buffer<uint>(GL_ELEMENT_ARRAY_BUFFER);
	};
}