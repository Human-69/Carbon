#include "Mesh.h"
#include "cbpch.h"

/* opengl */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Carbon::GL
{

	Mesh::Mesh(Ref<Shader> shader)
	{
		vertexCount = 0;
		indexCount = 0;

		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		VBO->Bind();
		IBO->Bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		VBO->Unbind();
		IBO->Unbind();

		this->shader = shader;
	}

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint>& indices, Ref<Shader> shader)
	{
		vertexCount = vertices.size();
		indexCount = indices.size();

		VBO = VertexBuffer::Create(vertices.size() * sizeof(Vertex));
		VBO->SetData(vertices.data(), vertices.size() * sizeof(Vertex));
		IBO = IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint));

		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		VBO->Bind();
		IBO->Bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		VBO->Unbind();
		IBO->Unbind();

		this->shader = shader;
	}

	void Mesh::LoadData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
	{
		
	}

	void Mesh::Render()
	{
		shader->Bind();
		
		glBindVertexArray(VAO);
		VBO->Bind();
		IBO->Bind();

		shader->Bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
	}
}