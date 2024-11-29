#include <KingdomEngine/KingdomEngine.h>

#include "KingdomEditor/DialogBox/SaveProjectDialogBox.h"

namespace Editor
{
	class FileMenu : public KE::ImMenu
	{
	public:
		FileMenu() : KE::ImMenu("File", true)
		{

		}

		void OnRender() override
		{
		    if (ImGui::BeginMenu("New"))
            {
                if (ImGui::MenuItem("Project"))
                {
                    if (ProjectManager::Get().GetLoadedProject())
                    {
                        SaveProjectDialog::SetShow();
                    }
                    else
                    {
                        SET_IM_WINDOW_VISIBLE("Projects", true);
                    }
                }
                ImGui::EndMenu();
            }

		    Separate();

		    if (Item("Open"))
			{

			}

			Separate();

			if (Item("Close Project"))
			{
                if (ProjectManager::Get().GetLoadedProject())
                {
                    SaveProjectDialog::SetShow();
                }
                else
                {
                    SET_IM_WINDOW_VISIBLE("Projects", true);
                }
			}

		    Separate();

		    if (Item("Project Config"))
			{
                SET_IM_WINDOW_VISIBLE("Project Configuration", true);
			}

			if (Item("Engine Config"))
			{
				SET_IM_WINDOW_VISIBLE("Engine Configuration", true);
			}

			Separate();

			if (Item("Exit", "Alt+F4"))
			{
				DISPATCH_EVENT(KE::EventType::CLOSE_APPLICATION);
			}
		}
	};

	FileMenu fileMenu;
}
