#ifndef APPLICATION_H
#define APPLICATION_H

#include "KingdomEngine/Core/Log.h"
#include "kingdomEngine/Core/Window.h"
#include "KingdomEngine/Core/Event.h"
#include "KingdomEngine/ImGui/ImGuiManager.h"

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
		virtual void OnImGuiRender() = 0;
		virtual void OnMenuBarRender() = 0;
		virtual void OnDockspaceUpdate() = 0;

		void ActivateImGui();
		void DisableImGui();
		void CreateWindowMaximized();
		void DisableApplication();
		void EventHandle();
		void GLEventHandle();

		Window& GetWindow() { return window; }

		void Run();
		void Quit();

	private:
		bool isRunning;
		bool eventHandling;
		bool handlingGLEvent;
		Event ev;
		Window window;
		ImGuiManager& imguiManager;

		void _OnEvent(Event e) override;
	};

	Application* CreateApplication();
}

#endif