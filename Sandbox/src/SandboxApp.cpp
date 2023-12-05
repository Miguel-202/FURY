#include <Fury.h>

class Sandbox : public FURY::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

FURY::Application* FURY::CreateApplication()
{
	return new Sandbox();
}