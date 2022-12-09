#include "Application.h"
#include <stdio.h>

#include "Congb/Events/ApplicationEvent.h"
#include "Congb/Log.h"

namespace Congb {

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
		{
			CB_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			CB_TRACE(e);
		}

		while (true); 
	}
}
