#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class ConsoleWindow : public KE::ImWindow
	{
	public:
		ConsoleWindow() : KE::ImWindow("Console", 0, 599, 1366, 98, true, false, KE::DockSide::DOWN)
		{

		}

		void OnReady() override
		{

		}

		void OnRender() override
		{

		}
	};

	ConsoleWindow consoleWindow;
}
