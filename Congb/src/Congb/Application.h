#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Congb/Events/ApplicationEvent.h"


namespace Congb{
	class CONGB_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//to be defined in client
	Application* CreateApplication();
}

