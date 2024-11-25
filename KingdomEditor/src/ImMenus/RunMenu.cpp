#include <KingdomEngine/KingdomEngine.h>

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

			}

			if (Item("Run"))
			{

			}

			if (Item("Build and Run"))
			{

			}
		}
	};

	RunMenu runMenu;
}
