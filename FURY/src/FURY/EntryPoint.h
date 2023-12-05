#pragma once

#ifdef FURY_PLATFORM_WINDOWS

extern FURY::Application* FURY::CreateApplication();
int main(int argc, char* argv)
{
	FURY::Log::Init();
	FURY_CORE_WARN("Initialized Log!");
	int a = 132;
	FURY_INFO("Hello! Var = {0}", a);

	auto app = FURY::CreateApplication();
	app->Run();
	delete app;
}

#endif 
