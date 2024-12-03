#include "KingdomEngine/ImGui/ImDialogBox.h"

namespace KE
{
    int ImDialogBox::flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;

    DialogResult ImDialogBox::ShowSaveDialog(const std::string& msgText)
    {
        DialogResult result = DialogResult::None;

        if (ImGui::BeginPopupModal("Save Changes?", NULL, flags))
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

    DialogResult ImDialogBox::ShowExcludeDialog(const std::string& msgText)
    {
        DialogResult result = DialogResult::None;

        if (ImGui::BeginPopupModal("Please Confirm", NULL, flags))
        {
            ImGui::Text(msgText.c_str());
            ImGui::Separator();

	        static bool removeFiles = false;
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.30f, 0.30f, 0.30f, 1.0f));
            ImGui::Checkbox("##", &removeFiles);
            ImGui::PopStyleColor();

            ImGui::SameLine();
            ImGui::Text("Delete project files? (this action is permanent!)");

            if (ImGui::Button("Remove", ImVec2(120, 0)))
            {
                if (removeFiles)
                {
                    result = DialogResult::ConfirmAndRemoveFiles;
                }
                else
                {
                    result = DialogResult::Confirm;
                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                removeFiles = false;
                result = DialogResult::Cancel;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        return result;
    }
}
