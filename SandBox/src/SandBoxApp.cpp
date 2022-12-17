#include "cbpch.h"
#include "Congb.h"

#include "imgui/imgui.h"

class ExampleLayer : public Congb::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//CB_INFO("ExampleLayer::Update");

		if (Congb::Input::IsKeyPressed(CB_KEY_TAB))
			CB_INFO("Tab key is pressed!");
	}

	void OnImGuiRender() override
	{
// 		ImGui::Begin("Test");
// 		ImGui::Text("Hello World");
// 		ImGui::End();
	}

	void OnEvent(Congb::Event& event) override
	{
		//CB_TRACE("{0}", event);
		if (event.GetEventType() == Congb::EventType::KeyPressed)
		{
			Congb::KeyPressedEvent& e = (Congb::KeyPressedEvent&)event;
			CB_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

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