#include "cbpch.h"
#include "Congb.h"

class ExampleLayer : public Congb::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		CB_INFO("ExampleLayer::Update");
	}

	void OnEvent(Congb::Event& event) override
	{
		CB_TRACE("{0}", event);
	}

};

class SandBox : public Congb::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushOverLay(new Congb::ImGuiLayer());
	}

	~SandBox()
	{

	}

};

Congb::Application* Congb::CreateApplication()
{
	return new SandBox();
}