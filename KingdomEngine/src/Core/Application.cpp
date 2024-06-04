#include "KingdomEngine/Core/Application.h"

namespace KE
{
	Application::Application()
		: imguiLayer(nullptr)
	{
		REGISTER_EVENT_LISTENER(this);

		window.Create();

		//IMGUI LAYER
		ImGuiLayer* imguiLayer = new ImGuiLayer(window.Get());
		layerStack.PushLayer(imguiLayer);

		layerStack.InitLayers();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		OnReady();

		while (isRunning)
		{
			while (!glfwWindowShouldClose(window.Get()))
			{
				window.PollEvents();
				layerStack.UpdateLayers();	
				window.Clear();

				Update();

				imguiLayer->Render();
				window.SwapBuffers();
			}
			
			if (glfwWindowShouldClose(window.Get()))
			{
				isRunning = false;
			}
		}
	}

	void Application::_OnEvent(Event e)
	{
		OnEvent(e);
		layerStack.UpdateEventLayers(e);

		if (e.type_ == CLOSE_APPLICATION)
		{
			isRunning = false;
		}
	}
}