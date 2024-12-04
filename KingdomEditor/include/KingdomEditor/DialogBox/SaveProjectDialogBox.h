#ifndef SAVE_PROJECT_DIALOG_BOX_H
#define SAVE_PROJECT_DIALOG_BOX_H

#include "KingdomEditor/Project/ProjectManager.h"

namespace Editor
{
    class SaveProjectDialog
    {
    public:
        static KE::DialogResult Show()
        {
            if (showing)
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
                    ProjectManager::Get().GetLoadedProject()->SaveKepFile();
                    ProjectManager::Get().UnloadProject();
                    showing = false;
                    SET_IM_WINDOW_VISIBLE("Projects", true);
                    break;
                case KE::DialogResult::DontSave:
                    ProjectManager::Get().UnloadProject();
                    showing = false;
                    SET_IM_WINDOW_VISIBLE("Projects", true);
                    break;
                case KE::DialogResult::Cancel:
                    showing = false;
                    break;
                default:
                    break;
                }

                return dialogResult;
            }

            return KE::DialogResult::None;
        }

        static void SetShow()
        {
            showing = true;
        }

        static bool IsShowing() { return showing; }

    private:
        static bool showing;

    };
}

#endif
