#ifndef APPLICATION_H
#define APPLICATION_H

#include "KingdomEngine/Core/Log.h"
#include "kingdomEngine/Platform/Windows/Window.h"
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

		Window& GetWindow() { return window; }
		OpenGLContext& GetContext() { return context; }
		ImGuiManager& GetImGuiManager() { return imguiManager; }

		void Run();
		void Quit();

	private:
		bool isRunning;
		Window window;
		OpenGLContext context;
		ImGuiManager imguiManager;

		void _OnEvent(Event e) override;
	};

	Application* CreateApplication();
}

#endif