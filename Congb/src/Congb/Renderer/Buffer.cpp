#include "cbpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Congb {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		CB_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}


	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}
		CB_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}