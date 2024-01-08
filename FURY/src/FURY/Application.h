#pragma once
#include "Core.h"

#include "Window.h"
#include "FURY/LayerStack.h"
#include "Events/Event.h"
#include "FURY/Events/ApplicationEvent.h"

#include "FURY/ImGui/ImGuiLayer.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);


	private:

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

