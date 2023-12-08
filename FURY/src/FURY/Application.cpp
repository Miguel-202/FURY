#include "FURYpch.h"
#include "Application.h"

#include "FURY/Events/ApplicationEvent.h"
#include "FURY/Log.h"

namespace FURY
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
			FURY_TRACE(e);
		if (e.IsInCategory(EventCategoryInput))
			FURY_TRACE(e);

		while (true)
		{

		}
	}
}