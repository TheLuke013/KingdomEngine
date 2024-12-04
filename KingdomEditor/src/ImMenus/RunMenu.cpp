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
				DISPATCH_EVENT(KE::EventType::DISABLE_IMGUI);
			}

			if (Item("Stop", "Esc"))
			{
				DISPATCH_EVENT(KE::EventType::ACTIVE_IMGUI);
			}
		}
	};

	RunMenu runMenu;
}
