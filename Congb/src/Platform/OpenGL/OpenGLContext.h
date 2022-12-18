#pragma once
#include "Congb/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Congb {
	
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandles);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}