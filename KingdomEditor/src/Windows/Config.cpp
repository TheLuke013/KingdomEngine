#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class Config : public KE::ImWindow
	{
	public:
		Config() : KE::ImWindow("Configuration", 397, 43, 678, 520, false, KE::DockSide::NONE)
		{
			properties.flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
		}

		void OnRender() override
		{
			//OPENGL VERSION
			int glVersion = KE::Renderer::GetVersion().glVersion;
			if (ImGui::Combo("OpenGL Version", &glVersion,
				"OpenGL 3\0"
				"OpenGL 2\0"))
			{
				if (glVersion == KE::GLVersion::OpenGL2)
				{
					DISPATCH_EVENT(KE::EventType::LOAD_OPENGL2);
					LOG_WARN("Switching OpenGL version to OpenGL 2.1!");
				}
				else if (glVersion == KE::GLVersion::OpenGL3)
				{
					DISPATCH_EVENT(KE::EventType::LOAD_OPENGL3);
					LOG_WARN("Switching OpenGL version to OpenGL 3.3!");
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

	Config config;
}
