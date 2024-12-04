#ifndef EXCLUDE_PROJECT_DIALOG_BOX_H
#define EXCLUDE_PROJECT_DIALOG_BOX_H

#include "KingdomEditor/ProjectManager.h"

namespace Editor
{
    class ExcludeProjectDialog
    {
    public:
        static KE::DialogResult Show()
        {
            if (showing)
            {
                KE::DialogResult dialogResult = KE::DialogResult::None;

                ImGui::OpenPopup("Please Confirm");
                KE::DialogResult result = KE::ImDialogBox::ShowExcludeDialog("Are you sure you want to delete this project?");
                if (result != KE::DialogResult::None)
                {
                    dialogResult = result;
                }

                switch (dialogResult)
                {
                case KE::DialogResult::Confirm:
                    showing = false;
                    ProjectManager::Get().RemoveProject(projectNameToRemove);
                    projectNameToRemove = "";
                    break;
                case KE::DialogResult::ConfirmAndRemoveFiles:
                    // remove project files
                    for (const auto &project : ProjectManager::Get().GetProjects())
                    {
                        if (project->properties.name == projectNameToRemove)
                        {
                            KE::Directory projDir;
                            projDir.Remove(project->properties.path);
                            break;
                        }
                    }

                    ProjectManager::Get().RemoveProject(projectNameToRemove);
                    projectNameToRemove = "";
                    showing = false;
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

        static void SetProjectName(const std::string &projectName)
        {
            projectNameToRemove = projectName;
        }

        static bool IsShowing() { return showing; }

    private:
        static bool showing;
        static std::string projectNameToRemove;
    };
}

#endif
