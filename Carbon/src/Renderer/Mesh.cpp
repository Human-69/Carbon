#include "Mesh.h"
#include "cbpch.h"
#include "../GL/RenderCommands.h"

/* opengl */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Carbon::Renderer
{

	Mesh::Mesh(Ref<GL::Shader> shader)
	{
		vertexCount = 0;
		indexCount = 0;

		VAO = GL::VertexArray::Create();
		VBO = GL::VertexBuffer::Create(0);
		IBO = GL::IndexBuffer::Create({}, 0);

		GL::BufferLayout layout(
			{
				GL::BufferElement(GL::VertexBufferDatatype::Float3, "Position", false),
				GL::BufferElement(GL::VertexBufferDatatype::Float2, "UV", false),
			});

		VBO->SetLayout(layout);
		VAO->SetVertexBuffer(VBO);
		VAO->SetIndexBuffer(IBO);

		this->shader = shader;
	}

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint>& indices, Ref<GL::Shader> shader)
	{
		vertexCount = vertices.size();
		indexCount = indices.size();

		VAO = GL::VertexArray::Create();
		VBO = GL::VertexBuffer::Create(vertices.size() * sizeof(Vertex));
		VBO->SetData(vertices.data(), vertices.size() * sizeof(Vertex));
		IBO = GL::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint));

		GL::BufferLayout layout(
			{
				GL::BufferElement(GL::VertexBufferDatatype::Float3, "Position", false),
				GL::BufferElement(GL::VertexBufferDatatype::Float2, "UV", false),
			});
	
		VBO->SetLayout(layout);
		VAO->SetVertexBuffer(VBO);
		VAO->SetIndexBuffer(IBO);

		this->shader = shader;
	}

	void Mesh::LoadData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
	{
		vertexCount = vertices.size();
		indexCount = indices.size();

		VBO->SetData(vertices.data(), vertices.size() * sizeof(Vertex));
		IBO->SetData(indices.data(), indices.size() * sizeof(uint));
	}

	void Mesh::Render()
	{
		shader->Bind();

		GL::RendererCommands::DrawIndexed(VAO, indexCount);
	}
}