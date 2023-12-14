#pragma once

#include "FURY/Layer.h"

#include "FURY/Events/MouseEvent.h"
#include "FURY/Events/ApplicationEvent.h"
#include "FURY/Events/KeyEvent.h"

namespace FURY
{
	class FURY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);

	private:
		float m_Time = 0.0f;
	};
}