#pragma once
#include "Core.h"
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

