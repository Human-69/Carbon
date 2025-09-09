#pragma once

#include <vector>
#include <CarbonTypes.h>
#include <cb_assert.h>
#include <string>

namespace Carbon::GL
{
	enum class VertexBufferDatatype
	{
		None,
		Int, 
		Int2,
		Int3,
		Int4,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Bool,
	};

	static uint GetDatatypeSize(VertexBufferDatatype datatype)
	{
		switch (datatype)
		{
		case VertexBufferDatatype::Int: return 4;
		case VertexBufferDatatype::Int2: return 4 * 2;
		case VertexBufferDatatype::Int3: return 4 * 3;
		case VertexBufferDatatype::Int4: return 4 * 4;
			
		case VertexBufferDatatype::Float: return 4;
		case VertexBufferDatatype::Float2: return 4 * 2;
		case VertexBufferDatatype::Float3: return 4 * 3;
		case VertexBufferDatatype::Float4: return 4 * 4;

		case VertexBufferDatatype::Mat3: return 4 * 3 * 3;
		case VertexBufferDatatype::Mat4: return 4 * 4 * 4;

		case VertexBufferDatatype::Bool: return 1;
		}

		CB_ASSERT_MSG(false, "Unknown datatype!");
	}

	struct BufferElement
	{
		std::string name;
		VertexBufferDatatype type;
		uint size;
		uint offset;
		bool normalized;

		uint GetElementCount() const
		{
			switch (type)
			{
			case VertexBufferDatatype::Int: return 1;
			case VertexBufferDatatype::Int2: return 2;
			case VertexBufferDatatype::Int3: return 3;
			case VertexBufferDatatype::Int4: return 4;

			case VertexBufferDatatype::Float: return 1;
			case VertexBufferDatatype::Float2: return 2;
			case VertexBufferDatatype::Float3: return 3;
			case VertexBufferDatatype::Float4: return 4;

			case VertexBufferDatatype::Mat3: return 3;
			case VertexBufferDatatype::Mat4: return 4;

			case VertexBufferDatatype::Bool: return 1;
			}

			CB_ASSERT_MSG(false, "Unknown datatype!");
		}

		BufferElement(VertexBufferDatatype datatype, std::string& name, bool normalized = false) : type(datatype), size(GetDatatypeSize(datatype)), offset(0), name(name), normalized(normalized) {};
	};

	class BufferLayout
	{
	public:
		BufferLayout(std::initializer_list<BufferElement> elements) : elements(elements) { CalculateOffsetAndStride(); };
		BufferLayout() = default;

		uint GetStride() const { return stride; }

		const std::vector<BufferElement>& GetBufferElements() const { return elements; }

	private:

		void CalculateOffsetAndStride()
		{
			int offset = 0;
			stride = 0;
			for(auto element : elements)
			{
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}
		
		uint stride;
		std::vector<BufferElement> elements;
	};

	class VertexBuffer
	{
	public:

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetData(void* data, uint size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& bufferLayout) = 0;

		static Ref<VertexBuffer> Create(uint size);
		static Ref<VertexBuffer> Create(float* vertices, uint size);
	};

	class IndexBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetData(uint* data, uint size) = 0;

		static Ref<IndexBuffer> Create(uint* indices, uint size);
	};
}