#include <KingdomEngine/ImGui/ImWindow.h>
#include <KingdomEngine/Core/FontManager.h>

#include "KingdomEditor/Utils/GLVersionCombo.h"

namespace Editor
{
	class ConfigWindow : public KE::ImWindow
	{
	public:
		ConfigWindow() : KE::ImWindow("Engine Configuration", 397, 43, 678, 520, false, false, KE::DockSide::NONE)
		{
			properties.flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
		}

		void OnReady() override
		{

		}

		void OnRender() override
		{
		    //THEME
		    int theme = KE::ImGuiManager::Get().GetTheme();
            if (ImGui::Combo("Style Theme", &theme,
				"Default\0"
				"Dark\0"
				"Light\0"))
            {
                if (theme == KE::Theme::DEFAULT)
                {
                    KE::ImGuiManager::Get().LoadTheme(KE::Theme::DEFAULT);
                }
                else if (theme == KE::Theme::DARK)
                {
                    KE::ImGuiManager::Get().LoadTheme(KE::Theme::DARK);
                }
                else if (theme == KE::Theme::LIGHT)
                {
                    KE::ImGuiManager::Get().LoadTheme(KE::Theme::LIGHT);
                }
            }

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

			//BACKGROUND COLOR
			//ImGui::ColorEdit3("Background Color", (float*)&KE::GLContext::GetClearColor());
		}
	};

	ConfigWindow configWindow;
}
