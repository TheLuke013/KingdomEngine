#ifndef APPLICATION_H
#define APPLICATION_H

#include "KingdomEngine/Core/Core.h"
#include "KingdomEngine/Core/Log.h"
#include "kingdomEngine/Core/Window.h"
#include "KingdomEngine/ImGui/ImGuiManager.h"
#include "KingdomEngine/Renderer/OpenGL/Sprite.h"

#include "KingdomEngine/Events/ApplicationEvent.h"
#include "KingdomEngine/Events/ImGuiEvent.h"

namespace KE
{
	class Application
	{
	public:
		Application(bool isGameApplication);
		virtual ~Application();

		virtual void OnEvent(EventType evType) = 0;
		virtual void OnReady() = 0;
		virtual void OnUpdate() = 0;
		#ifndef GAME_APPLICATION
		virtual void OnImGuiRender() = 0;
		virtual void OnMenuBarRender() = 0;
		virtual void OnDockspaceUpdate() = 0;
		#endif

		void ActivateImGui();
		void DisableImGui();
		void CreateMainWindow();
		void DisableApplication();
		void EventHandle();

		Window& GetWindow() { return window; }

		void Run();
		void Quit();

	private:
		bool isRunning;
		bool isGameApplication;
		ApplicationEvent appEvent;
		Window window;
		ImGuiManager& imguiManager;
		ImGuiEvent imguiEvent;
		Sprite sprite;
	};

	Application* CreateApplication();
}

#endif
