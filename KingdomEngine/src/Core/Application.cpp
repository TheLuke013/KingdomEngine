#include "KingdomEngine/Core/Application.h"

namespace KE
{
	Application::Application()
		: imguiLayer(nullptr)
	{
		REGISTER_EVENT_LISTENER(this);

		window.Create();

		context.Init();

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
			while (!window.IsClosed())
			{
				layerStack.UpdateLayers();	
				context.Clear();

				OnUpdate();

				imguiLayer->Render();
				window.Update();
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