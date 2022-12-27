#pragma once
#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Congb/Events/ApplicationEvent.h"

#include "Congb/ImGui/ImGuiLayer.h"


namespace Congb{
	class CONGB_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& getWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertextArray, m_VertexBuffer, m_IndexBuffer;

		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();
}

