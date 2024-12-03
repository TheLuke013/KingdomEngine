#ifndef IM_DIALOG_BOX_H
#define IM_DIALOG_BOX_H

#include <ImGui/imgui.h>
#include <string>

namespace KE
{
    enum class DialogResult
    {
        None,
        Save,
        DontSave,
        Cancel,
        Confirm,
        ConfirmAndRemoveFiles
    };

    class ImDialogBox
    {
    public:
        static DialogResult ShowSaveDialog(const std::string& msgText);
        static DialogResult ShowExcludeDialog(const std::string& msgText);

    private:
        static int flags;
    };
}

#endif
