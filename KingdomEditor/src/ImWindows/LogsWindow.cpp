#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class LogsWindow : public KE::ImWindow
	{
	public:
		LogsWindow() : KE::ImWindow("Logs", 0, 599, 1366, 136, true, KE::DockSide::DOWN)
		{

		}

		void OnRender() override
		{

		}
	};

	LogsWindow logsWindow;
}
