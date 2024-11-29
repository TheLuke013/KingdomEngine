#include "KingdomEngine/ImGui/ImDialogBox.h"

namespace KE
{
    DialogResult ImDialogBox::ShowSaveDialog(const std::string& msgText)
    {
        DialogResult result = DialogResult::None;

        if (ImGui::BeginPopupModal("Save Changes?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text(msgText.c_str());
            ImGui::Separator();

            if (ImGui::Button("Save", ImVec2(120, 0)))
            {
                result = DialogResult::Save;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Don't Save", ImVec2(120, 0)))
            {
                result = DialogResult::DontSave;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                result = DialogResult::Cancel;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        return result;
    }
}
