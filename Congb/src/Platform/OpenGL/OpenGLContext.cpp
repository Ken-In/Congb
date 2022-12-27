#include "cbpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Congb {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandles)
		: m_WindowHandle(windowHandles)
	{
		CB_CORE_ASSERT(windowHandles, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CB_CORE_ASSERT(status, "Failed to initialize Glad!");
		
		CB_CORE_INFO("OpenGL Info:");
		CB_CORE_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		CB_CORE_INFO("Version: {0}",(const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}