#include "cbpch.h"
#include "Congb.h"

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

		Congb::Ref<Congb::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Congb::VertexBuffer::Create(vertices, sizeof(vertices)));

		Congb::BufferLayout layout = {
			{ Congb::ShaderDataType::Float3, "a_Position"},
			{ Congb::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertextArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		Congb::Ref<Congb::IndexBuffer> indexBuffer;
		indexBuffer.reset(Congb::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertextArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Congb::VertexArray::Create());

		float squareBVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Congb::Ref<Congb::VertexBuffer> squareVB;
		squareVB.reset(Congb::VertexBuffer::Create(squareBVertices, sizeof(squareBVertices)));
		squareVB->SetLayout({
			{ Congb::ShaderDataType::Float3, "a_Position"},
			{ Congb::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Congb::Ref<Congb::IndexBuffer> squareIB;
		squareIB.reset(Congb::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec4 v_Color;			

			void main()
			{
				v_Color = a_Color;	
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
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

		m_Shader = Congb::Shader::Create("VertexColor", vertexSrc, fragmentSrc);
		m_ShaderLibrary.Add("VertexColor", m_Shader);


		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;			

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			uniform vec3 u_Color;
			in vec3 v_Position;			

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_BlueShader = Congb::Shader::Create("BlueShader", vertexSrc2, fragmentSrc2);
		m_ShaderLibrary.Add("BlueShader", m_BlueShader);

		m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		std::dynamic_pointer_cast<Congb::OpenGLShader>(m_ShaderLibrary.Get("Texture"))->Bind();
		std::dynamic_pointer_cast<Congb::OpenGLShader>(m_ShaderLibrary.Get("Texture"))->UploadUniformInt("u_Texture", 0);

		//∂¡Œ∆¿Ì
		m_Texture = Congb::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Congb::Texture2D::Create("assets/textures/logo.png");
		m_KeqingTexture = Congb::Texture2D::Create("assets/textures/keqing.png");

	}

	void OnUpdate(Congb::Timestep timestep) override
	{
		//CB_TRACE("Delta Time: {0}s ({1}ms)", timestep.GetSeconds(), timestep.GetMilliseconds());

		if (Congb::Input::IsKeyPressed(CB_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * timestep;
		else if (Congb::Input::IsKeyPressed(CB_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * timestep;

		if (Congb::Input::IsKeyPressed(CB_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * timestep;
		else if (Congb::Input::IsKeyPressed(CB_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * timestep;

		if (Congb::Input::IsKeyPressed(CB_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		else if (Congb::Input::IsKeyPressed(CB_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;


		Congb::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Congb::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Congb::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Congb::OpenGLShader>(m_BlueShader)->Bind();
		std::dynamic_pointer_cast<Congb::OpenGLShader>(m_BlueShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Congb::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}
		}
		
// 		m_Texture->Bind();
// 		Congb::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_KeqingTexture->Bind();
		Congb::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_LogoTexture->Bind();
		Congb::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(-1.45f, 0.75f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.15f)));


		//Congb::Renderer::Submit(m_Shader, m_VertextArray);

		Congb::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Congb::Event& event) override
	{
		
	}

private:
	Congb::ShaderLibrary m_ShaderLibrary;

	Congb::Ref<Congb::Shader> m_Shader;
	Congb::Ref<Congb::VertexArray> m_VertextArray;

	Congb::Ref<Congb::Shader> m_BlueShader;
	Congb::Ref<Congb::VertexArray> m_SquareVA;

	Congb::Ref<Congb::Texture2D> m_Texture, m_LogoTexture, m_KeqingTexture;

	Congb::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 50.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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