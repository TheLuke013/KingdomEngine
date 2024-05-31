#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "KingdomEngine/Core/Layer.h"
#include "KingdomEngine/Platform/Windows/Window.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

namespace KE
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(GLFWwindow* window);
		~ImGuiLayer();

		void OnReady() override;
		void Update() override;
		void _OnEvent(Event e) override;

		void Render();

	private:
		GLFWwindow* window;
		ImGuiIO io;

	};
}

#endif
