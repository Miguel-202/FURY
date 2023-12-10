#include <Fury.h>

class ExampleLayer : public FURY::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		FURY_INFO("ExampleLayer::Update");
	}

	void OnEvent(FURY::Event& event) override
	{
		FURY_TRACE("{0}", event);
	}

};

class Sandbox : public FURY::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

FURY::Application* FURY::CreateApplication()
{
	return new Sandbox();
}