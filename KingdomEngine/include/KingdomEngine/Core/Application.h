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
		Application();
		virtual ~Application();

		virtual void OnEvent(Event e) = 0;
		virtual void OnReady() = 0;
		virtual void OnUpdate() = 0;

		void Run();
		void _OnEvent(Event e) override;

	private:
		bool isRunning = true;
		Window window;
		LayerStack layerStack;
		ImGuiLayer* imguiLayer;
		OpenGLContext context;
	};

	Application* CreateApplication();
}

#endif