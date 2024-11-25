#ifndef IM_WINDOW_H
#define IM_WINDOW_H

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <KingdomEngine/ImGui/ImGuiManager.h>

#include <string>

namespace KE
{
	enum class DockSide
	{
		NONE,
		MAIN,
		LEFT,
		RIGHT,
		DOWN,
		LEFT_TOP,
		LEFT_BOTTOM
	};

	struct ImWindowProperties
	{
		ImVec2 position;
		ImVec2 size;
		ImGuiWindowFlags flags;
		DockSide dockSide;
		bool isInitialized;
		bool isVisible;
		bool isFocus;
		std::string name;
	};

	class ImWindow
	{
	public:
		ImWindow(const std::string& name, float xPos, float yPos, float xSize, float ySize, bool visible, bool isFocus, DockSide dockSide = DockSide::NONE);
		virtual ~ImWindow();

		void Render();

        virtual void OnReady() = 0;
		virtual void OnRender() = 0;

		ImWindowProperties properties;

	};
}

#endif
