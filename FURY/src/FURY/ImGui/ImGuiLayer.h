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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}
