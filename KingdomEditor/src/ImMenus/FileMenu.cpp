#include <KingdomEngine/ImGui/ImMenu.h>

#include "KingdomEditor/DialogBox/SaveProjectDialogBox.h"
#include "KingdomEditor/Utils/Globals.h"

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

			if (Item("Save Project"))
			{
				ProjectManager::Get().GetLoadedProject()->SaveKepFile();
			}
			
			if (Item("Save File"))
			{
				Globals::CAN_SAVE_FILE = true;
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
