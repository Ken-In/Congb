#include "cbpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Congb {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}