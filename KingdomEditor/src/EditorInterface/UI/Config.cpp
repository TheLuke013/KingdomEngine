#include "KingdomEditor/EditorInterface/EditorInterface.h"

#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class Config : public EditorInterface
	{
	public:
		Config() : EditorInterface("Configuration", 397, 43, 678, 520, false, NONE)
		{
			properties.isVisible = false;
			properties.flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
		}

		void OnRender() override
		{
			//OPENGL VERSION
			static int glVersion = 1;
			ImGui::Combo("OpenGL Version", &glVersion,
				"OpenGL 3\0"
				"OpenGL 2\0");

			//TEXT FONT
			if (ImGui::TreeNode("Text Font"))
			{
				for (const auto& font : KE::FontManager::Get().GetFonts())
				{
					if (ImGui::Selectable(font->properties.name.c_str()))
					{
						KE::ImGuiManager::Get().LoadFont(font);
					}
				}
				ImGui::TreePop();
			}
		}
	};

	Config config;
}
