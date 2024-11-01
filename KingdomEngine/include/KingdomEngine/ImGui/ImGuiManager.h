#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include "KingdomEngine/Platform/Windows/Window.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_opengl2.h>

namespace KE
{
	class ImGuiManager
	{
	public:
		ImGuiManager();
		~ImGuiManager();

		void Init(GLFWwindow* window);
		void Disable();
		void CreateNewFrame();
		void Render();

		void BeginDockspace();
		void EndDockspace();

		bool IsEnabled() const { return isEnabled; }

		int DetectGLContextVersion();

	private:
		GLFWwindow* window;
		bool isEnabled;
		bool newFrameIsCalled;

	};
}

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   