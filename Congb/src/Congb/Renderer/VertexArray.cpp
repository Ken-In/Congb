#include "cbpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Congb {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		CB_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}