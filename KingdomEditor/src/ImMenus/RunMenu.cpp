#include <KingdomEngine/ImGui/ImMenu.h>

#include "KingdomEditor/Project/ProjectManager.h"
#include "KingdomEditor/Project/ProjectBuild.h"

#include <cstdlib>

namespace Editor
{
	class RunMenu : public KE::ImMenu
	{
	public:
		RunMenu() : KE::ImMenu("Run", true)
		{
		}

		void OnRender() override
		{
			if (Item("Build"))
			{
				ProjectBuild::Build();
			}

			if (Item("Run", "F5"))
			{
                ProjectManager::Get().RunProject();
			}
		}
	};

	RunMenu runMenu;
}
