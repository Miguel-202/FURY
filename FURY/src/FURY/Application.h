#pragma once
#include "Core.h"
#include "Events/Event.h"
namespace FURY
{

	class FURY_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

