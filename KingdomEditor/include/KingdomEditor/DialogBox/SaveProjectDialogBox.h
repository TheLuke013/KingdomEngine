#ifndef SAVE_PROJECT_DIALOG_BOX_H
#define SAVE_PROJECT_DIALOG_BOX_H

#include "KingdomEditor/ProjectManager.h"

namespace Editor
{
    class SaveProjectDialog
    {
    public:
        static void Show()
        {
            if (showSaveProjectDialog)
            {
                KE::DialogResult dialogResult = KE::DialogResult::None;

                ImGui::OpenPopup("Save Changes?");
                KE::DialogResult result = KE::ImDialogBox::ShowSaveDialog("Do you want to save changes to this project?");
                if (result != KE::DialogResult::None)
                {
                    dialogResult = result;
                }

                switch (dialogResult)
                {
                case KE::DialogResult::Save:
                    ProjectManager::Get().UnloadProject();
                    showSaveProjectDialog = false;
                    SET_IM_WINDOW_VISIBLE("Projects", true);
                    break;
                case KE::DialogResult::DontSave:
                    ProjectManager::Get().UnloadProject();
                    showSaveProjectDialog = false;
                    SET_IM_WINDOW_VISIBLE("Projects", true);
                    break;
                case KE::DialogResult::Cancel:
                    showSaveProjectDialog = false;
                    break;
                default:
                    break;
                }
            }
        }

        static void SetShow()
        {
            showSaveProjectDialog = true;
        }

    private:
        static bool showSaveProjectDialog;

    };
}

#endif
