#include <KingdomEngine/KingdomEngine.h>

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
			    std::string projectName = ProjectManager::Get().GetLoadedProject()->properties.name;
			    std::string gameLibPath = ProjectManager::Get().GetLoadedProject()->properties.path + "\\build\\" + projectName + ".dll";
                KE::GameLoader::Get().LoadGame(gameLibPath);
			}

			if (Item("Stop", "Esc"))
			{
                KE::GameLoader::Get().UnloadGame();
			}
		}
	};

	RunMenu runMenu;
}
