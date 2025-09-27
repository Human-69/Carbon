#include "OpenGLRendererAPI.h"
#include "GL/glew.h"

namespace Carbon::GL::OpenGL
{
	void OpenGLRendererAPI::Init() 
	{
		glEnable(GL_BLEND);
	};

	void OpenGLRendererAPI::SetClearColor(Color color) 
	{
		glClearColor(color.x, color.y, color.z, color.w);
	};

	void OpenGLRendererAPI::Clear() 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	};

	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray> VAO, int indexCount)
	{
		VAO->Bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
	};
}