#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class Console : public KE::ImWindow
	{
	public:
		Console() : KE::ImWindow("Console", 0, 599, 1366, 98, true, KE::DockSide::DOWN)
		{

		}

		void OnRender() override
		{
			
		}
	};

	Console console;
}
