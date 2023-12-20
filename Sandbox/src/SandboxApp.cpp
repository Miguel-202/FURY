#include <Fury.h>

#include <imgui/imgui.h>

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
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
	}

	~Sandbox()
	{

	}
};

FURY::Application* FURY::CreateApplication()
{
	return new Sandbox();
}