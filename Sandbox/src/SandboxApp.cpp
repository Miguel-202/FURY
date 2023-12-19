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
		if (FURY::Input::IsKeyPressed(FURY_KEY_TAB))
			FURY_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(FURY::Event& event) override
	{
		// FURY_TRACE("{0}", event);
	}

};

class Sandbox : public FURY::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new FURY::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

FURY::Application* FURY::CreateApplication()
{
	return new Sandbox();
}