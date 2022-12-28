#pragma once

namespace Congb {

	enum class RenderAPI
	{
		None = 0,
		OpenGL
	};

	class Renderer
	{
	public:
		inline static RenderAPI GetAPI() { return s_RendererAPI; }
	private:
		static RenderAPI s_RendererAPI;
	};

}