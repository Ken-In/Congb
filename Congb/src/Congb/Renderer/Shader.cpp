#include "cbpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Congb {
	
	Congb::Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		}
		CB_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Congb::Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CB_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		CB_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}