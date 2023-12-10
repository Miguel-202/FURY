#pragma once
#include "Core.h"

#include "Window.h"
#include "FURY/LayerStack.h"
#include "Events/Event.h"
#include "FURY/Events/ApplicationEvent.h"

namespace FURY
{

	class FURY_API Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);


	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

