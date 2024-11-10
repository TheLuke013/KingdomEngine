#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include "KingdomEngine/Core/Window.h"
#include "KingdomEngine/Core/Font.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_opengl2.h>
#include <ImGui/imgui_internal.h>

namespace KE
{
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

		void Init(GLFWwindow* window);
		void Disable();
		void Restart();
		void CreateNewFrame();
		void Render();
		void LoadFont(Font* font);

		void BeginDockspace();
		void EndDockspace();

		bool IsEnabled() const { return isEnabled; }

		ImGuiID GetDockspaceID() { return dockspaceID; }
		DockSides& GetDockSides() { return dockSides; }

		int DetectGLContextVersion();

	private:
		ImGuiManager();
		~ImGuiManager();

		GLFWwindow* window;
		bool isEnabled;
		bool newFrameIsCalled;
		ImGuiID dockspaceID;
		DockSides dockSides;
		Font* loadedFont;

	};
}

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   