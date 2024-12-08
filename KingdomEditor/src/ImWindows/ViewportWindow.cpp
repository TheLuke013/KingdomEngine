#include <KingdomEngine/ImGui/ImWindow.h>

namespace Editor
{
	class ViewportWindow : public KE::ImWindow
	{
	public:
		ViewportWindow() : KE::ImWindow("Viewport", 0, 0, 0, 0, true, false, KE::DockSide::MAIN)
		{

		}

		void OnReady() override
		{

		}

		void OnRender() override
		{
		    const float window_width = ImGui::GetContentRegionAvail().x;
            const float window_height = ImGui::GetContentRegionAvail().y;

            glViewport(0, 0, static_cast<GLsizei>(window_width), static_cast<GLsizei>(window_height));

            ImVec2 pos = ImGui::GetCursorScreenPos();

            ImGui::GetWindowDrawList()->AddImage(
                (ImTextureID)KE::Renderer::GetFramebuffer().GetTextureID(),
                ImVec2(pos.x, pos.y),
                ImVec2(pos.x + window_width, pos.y + window_height),
                ImVec2(0, 1),
                ImVec2(1, 0)
            );
		}
	};

	ViewportWindow viewportWindow;
}
