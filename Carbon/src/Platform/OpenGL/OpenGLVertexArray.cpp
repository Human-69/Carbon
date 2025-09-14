#include "OpenGLVertexArray.h"
#include <GL/glew.h>

namespace Carbon::GL::OpenGL 
{

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &vao);
	}


	void OpenGLVertexArray::Bind() 
	{
		glBindVertexArray(vao);
	};

	void OpenGLVertexArray::Unbind() 
	{
		glBindVertexArray(0);
	};
	
	void OpenGLVertexArray::SetVertexBuffer(Ref<VertexBuffer> buffer)
	{
		Bind();
		buffer->Bind();

		int stride = buffer->GetLayout().GetStride();
		int index = 0;

		for(auto& element : buffer->GetLayout().GetBufferElements())
		{
			GLenum type = GL_FLOAT;

			switch (element.type)
			{
			case VertexBufferDatatype::Int: 
			case VertexBufferDatatype::Int2:
			case VertexBufferDatatype::Int3:
			case VertexBufferDatatype::Int4:
				type=GL_INT; break;

			case VertexBufferDatatype::Float: 
			case VertexBufferDatatype::Float2:
			case VertexBufferDatatype::Float3:
			case VertexBufferDatatype::Float4:
				type = GL_FLOAT; break;
			case VertexBufferDatatype::Mat3:
			case VertexBufferDatatype::Mat4:
				CB_ASSERT_MSG(false, "Buffer element types Mat3 and Mat4 are currently not supported!"); break;

			case VertexBufferDatatype::Bool:
				type=GL_BOOL; break;
			}

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index++, element.GetElementCount(), type, element.normalized ? GL_TRUE : GL_FALSE, stride, (void*)element.offset);
		}
	};

	void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer> buffer) 
	{
		Bind();
		buffer->Bind();
	};

}