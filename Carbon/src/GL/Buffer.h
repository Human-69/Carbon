#pragma once
#include "cbglpch.h"

#include "Types.h"

/* opengl */
#include <GL/glew.h>

namespace Carbon::GL
{
	/// <summary>
	/// A buffer for GPU data
	/// </summary>
	template<typename T>
	class Buffer
	{
	public:
		Buffer(uint target, std::vector<T> data) : target(target), elementSize(sizeof(T))
		{
			glGenBuffers(1, &handle);
			glBindBuffer(target, handle);
			glBufferData(target, elementSize * data.size(), data.data(), GL_STATIC_DRAW);
			glBindBuffer(target, 0);
		}

		Buffer(uint target, int numElements) : target(target), elementSize(sizeof(T))
		{
			glGenBuffers(1, &handle);
			glBindBuffer(target, handle);
			glBufferData(target, elementSize * numElements, NULL, GL_STATIC_DRAW);
			glBindBuffer(target, 0);
		}

		Buffer(uint target) : target(target), elementSize(sizeof(T))
		{
			glGenBuffers(1, &handle);
			glBindBuffer(target, handle);
			glBindBuffer(target, 0);
		}

		Buffer() : elementSize(sizeof(T))
		{
			glGenBuffers(1, &handle);
		}

		void SetData(std::vector<T> data)
		{
			Bind();
			glBufferData(target, elementSize * data.size(), data.data(), GL_STATIC_DRAW);
			Unbind();
		}

		template<typename U = T, typename Member, typename std::enable_if<std::is_class<U>::value || std::is_union<T>::value, int>::type = 0>
		
		void AddAttribPointer(Member U::* member, int count, GLenum type)
		{
			Bind();
			glVertexAttribPointer(vertexAtrribIndex, count, type, GL_FALSE, elementSize, reinterpret_cast<const void*>(&(reinterpret_cast<U*>(0)->*member)));
			glEnableVertexAttribArray(vertexAtrribIndex++);
			Unbind();
		}

		void Bind()
		{
			glBindBuffer(target, handle);
		}

		void Unbind()
		{
			glBindBuffer(target, 0);
		}

	private:
		uint handle;
		uint target;
		uint elementSize;
		uint vertexAtrribIndex = 0;
	};
}