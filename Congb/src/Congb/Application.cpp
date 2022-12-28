#include "cbpch.h"
#include "Application.h"

#include "Congb/Log.h"

#include "glad/glad.h"

#include "Input.h"

#include <memory>


namespace Congb {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Congb::ShaderDataType::Float:	   return GL_FLOAT;
			case Congb::ShaderDataType::Float2:	   return GL_FLOAT;
			case Congb::ShaderDataType::Float3:	   return GL_FLOAT;
			case Congb::ShaderDataType::Float4:	   return GL_FLOAT;
			case Congb::ShaderDataType::Mat3:	   return GL_FLOAT;
			case Congb::ShaderDataType::Mat4:	   return GL_FLOAT;
			case Congb::ShaderDataType::Int:	   return GL_INT;
			case Congb::ShaderDataType::Int2:	   return GL_INT;
			case Congb::ShaderDataType::Int3:	   return GL_INT;
			case Congb::ShaderDataType::Int4:	   return GL_INT;
			case Congb::ShaderDataType::Bool:	   return GL_BOOL;
		}

		CB_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
	{
		CB_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		//设置回调函数
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();

		PushOverLay(m_ImGuiLayer);

		// vertex array
		glGenVertexArrays(1, &m_VertextArray);
		glBindVertexArray(m_VertextArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
						{ ShaderDataType::Float3, "a_Position"},
						{ ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		for (const auto& element : m_VertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				m_VertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);
			index++;
		}



		unsigned int indices[3] = {0, 1, 2};
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec4 v_Color;			

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				v_Color = a_Color;	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec4 v_Color;
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event & e)
	{
		//当e为关闭事件时 调用OnWindowClosed
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		//遍历层栈 每层依次处理事件 直到事件处理完成跳出
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}


	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertextArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (auto layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
