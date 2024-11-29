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
        Cancel
    };

    class ImDialogBox
    {
    public:
        static DialogResult ShowSaveDialog(const std::string& msgText);
    };
}

#endif
