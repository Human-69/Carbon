#include "Mesh.h"

namespace Carbon::GL
{

	Mesh::Mesh(Shader* shader)
	{
		vertexCount = 0;
		indexCount = 0;

		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		VBO.AddAttribPointer(&Vertex::position, 3, GL_FLOAT);
		VBO.AddAttribPointer(&Vertex::uv, 2, GL_FLOAT);

		VBO.Bind();
		IBO.Bind();

		glBindVertexArray(0);
		VBO.Unbind();
		IBO.Unbind();

		this->shader = shader;
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices, Shader* shader)
	{
		vertexCount = vertices.size();
		indexCount = indices.size();

		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		VBO.SetData(vertices);
		IBO.SetData(indices);

		VBO.AddAttribPointer(&Vertex::position, 3, GL_FLOAT);
		VBO.AddAttribPointer(&Vertex::uv, 2, GL_FLOAT);

		VBO.Bind();
		IBO.Bind();

		glBindVertexArray(0);
		VBO.Unbind();
		IBO.Unbind();

		this->shader = shader;
	}

	void Mesh::LoadData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
	{
		vertexCount = vertices.size();
		indexCount = indices.size();

		VBO.SetData(vertices);
		IBO.SetData(indices);
	}

	void Mesh::Render()
	{
		shader->Bind();
		
		glBindVertexArray(VAO);

		shader->SetMatrix4("pv", projectionView);

		shader->Bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
	}
}