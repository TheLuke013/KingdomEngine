#ifndef APPLICATION_H
#define APPLICATION_H

#include "KingdomEngine/Core/Log.h"
#include "kingdomEngine/Platform/Windows/Window.h"
#include "KingdomEngine/Core/Event.h"
#include "KingdomEngine/Core/LayerStack.h"
#include "KingdomEngine/GUI/ImGuiLayer.h"

namespace KE
{
	class Application : EventListener
	{
	public:
		Window window;

		Application();
		virtual ~Application();

		void Run();
		void _OnEvent(Event e) override;

		virtual void OnEvent(Event e) = 0;
		virtual void OnReady() = 0;
		virtual void Update() = 0;

	private:
		bool isRunning = true;
		LayerStack layerStack;
		ImGuiLayer* imguiLayer;
	};

	Application* CreateApplication();
}

#endif