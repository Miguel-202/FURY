#pragma once

#ifdef FURY_PLATFORM_WINDOWS

extern FURY::Application* FURY::CreateApplication();
int main(int argc, char* argv)
{
	auto app = FURY::CreateApplication();
	app->Run();
	delete app;
}

#endif 
