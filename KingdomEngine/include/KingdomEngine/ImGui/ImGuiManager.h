#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include "KingdomEngine/Core/Window.h"
#include "KingdomEngine/Core/Font.h"
#include "KingdomEngine/ImGui/ImGuiTheme.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl2.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_opengl2.h>
#include <ImGui/imgui_internal.h>

namespace KE
{
	class ImGuiEvent;
	
	struct DockSides
	{
		ImGuiID dock_main;
		ImGuiID dock_left;
		ImGuiID dock_right;
		ImGuiID dock_down;
		ImGuiID dock_left_top;
		ImGuiID dock_left_bottom;
	};

	class ImGuiManager
	{
	public:
		static ImGuiManager& Get();

		void Setup(SDL_Window* window, bool enableDockspace);
		void Enable();
		void Disable();
		void Restart();
		void CreateNewFrame();
		void Render();
		void LoadFont(Font* font);
		void LoadTheme(Theme theme);

		void BeginDockspace();
		void EndDockspace();
		void EnableDockspace();
		void DisableDockspace();

		bool IsEnabled() const { return isEnabled; }
		bool DockspaceIsEnabled() const { return dockspaceIsEnabled; }
		bool NewFrameIsCalled() { return newFrameIsCalled; }
		ImGuiID GetDockspaceID() { return dockspaceID; }
		DockSides& GetDockSides() { return dockSides; }
		Theme GetTheme() { return theme.GetTheme(); }

		int DetectGLContextVersion();

	private:
		ImGuiManager();
		~ImGuiManager();

		SDL_Window* window;
		bool isEnabled;
		bool dockspaceIsEnabled;
		bool newFrameIsCalled;
		ImGuiID dockspaceID;
		DockSides dockSides;
		Font* loadedFont;
		ImGuiTheme theme;

	};
}

#endif
