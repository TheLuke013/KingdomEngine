#ifndef EDITOR_INTERFACE_H
#define EDITOR_INTERFACE_H

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <KingdomEngine/ImGui/ImGuiManager.h>

#include <string>

namespace Editor
{
	enum DockSide
	{
		NONE,
		MAIN,
		LEFT,
		RIGHT,
		DOWN,
		LEFT_TOP,
		LEFT_BOTTOM
	};

	struct EditorInterfaceProperties
	{
		ImVec2 position;
		ImVec2 size;
		ImGuiWindowFlags flags;
		DockSide dockSide;
		bool isInitialized;
		bool isVisible;
		std::string name;
	};

	class EditorInterface
	{
	public:
		EditorInterface(const std::string& name, float xPos, float yPos, float xSize, float ySize, bool visible, DockSide dockSide = NONE);
		virtual ~EditorInterface();

		void Render();

		virtual void OnRender() = 0;

		EditorInterfaceProperties properties;

	};
}

#endif
