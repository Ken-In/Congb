#include "cbpch.h"
#include "Congb.h"

#include "imgui/imgui.h"

class ExampleLayer : public Congb::Layer
{
public:
	ExampleLayer()
		: Layer("Example") ,m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertextArray.reset(Congb::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Congb::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Congb::VertexBuffer::Create(vertices, sizeof(vertices)));

		Congb::BufferLayout layout = {
			{ Congb::ShaderDataType::Float3, "a_Position"},
			{ Congb::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertextArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<Congb::IndexBuffer> indexBuffer;
		indexBuffer.reset(Congb::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertextArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Congb::VertexArray::Create());

		float squareBVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Congb::VertexBuffer> squareVB;
		squareVB.reset(Congb::VertexBuffer::Create(squareBVertices, sizeof(squareBVertices)));
		squareVB->SetLayout({
			{ Congb::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Congb::IndexBuffer> squareIB;
		squareIB.reset(Congb::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			
			out vec4 v_Color;			

			void main()
			{
				v_Color = a_Color;	
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
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

		m_Shader.reset(new Congb::Shader(vertexSrc, fragmentSrc));


		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;			

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;			

			void main()
			{
				color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
			}
		)";

		m_BlueShader.reset(new Congb::Shader(vertexSrc2, fragmentSrc2));

	}

	void OnUpdate() override
	{
		if (Congb::Input::IsKeyPressed(CB_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed;
		else if (Congb::Input::IsKeyPressed(CB_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed;

		if (Congb::Input::IsKeyPressed(CB_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed;
		else if (Congb::Input::IsKeyPressed(CB_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed;

		if (Congb::Input::IsKeyPressed(CB_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Congb::Input::IsKeyPressed(CB_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		Congb::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Congb::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Congb::Renderer::BeginScene(m_Camera);

		Congb::Renderer::Submit(m_BlueShader, m_SquareVA);
		Congb::Renderer::Submit(m_Shader, m_VertextArray);

		Congb::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Congb::Event& event) override
	{
		
	}

private:
	std::shared_ptr<Congb::Shader> m_Shader;
	std::shared_ptr<Congb::VertexArray> m_VertextArray;

	std::shared_ptr<Congb::Shader> m_BlueShader;
	std::shared_ptr<Congb::VertexArray> m_SquareVA;

	Congb::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.01f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 1.0f;
};

class SandBox : public Congb::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{

	}

};

Congb::Application* Congb::CreateApplication()
{
	return new SandBox();
}