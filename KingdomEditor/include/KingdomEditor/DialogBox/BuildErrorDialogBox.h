#ifndef BUILD_ERROR_DIALOG_BOX_H
#define BUILD_ERROR_DIALOG_BOX_H

namespace Editor
{
    class BuildErrorDialog
    {
    public:
        static KE::DialogResult Show()
        {
            if (showing)
            {
                KE::DialogResult dialogResult = KE::DialogResult::None;

                ImGui::OpenPopup("GenericDialogBox");
                KE::DialogResult result = KE::ImDialogBox::ShowDialogBox("An error occurred while generating build files or building the project");
                if (result != KE::DialogResult::None)
                {
                    dialogResult = result;
                }

                switch (dialogResult)
                {
                case KE::DialogResult::Confirm:
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
