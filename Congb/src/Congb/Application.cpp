#include "cbpch.h"
#include "Application.h"

#include "Congb/Events/ApplicationEvent.h"
#include "Congb/Log.h"

namespace Congb {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}
