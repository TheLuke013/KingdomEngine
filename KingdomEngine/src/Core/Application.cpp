#include "KingdomEngine/Core/Application.h"
#include "KingdomEngine/GUI/ImGuiLayer.h"

namespace KE
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		REGISTER_EVENT_LISTENER(this);

		window.Create();

		OnReady();

		//IMGUI LAYER
		ImGuiLayer* imguiLayer = new ImGuiLayer(window.Get());
		layerStack.PushLayer(imguiLayer);

		layerStack.InitLayers();

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