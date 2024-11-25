#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class LogsWindow : public KE::ImWindow
	{
	public:
		LogsWindow() : KE::ImWindow("Logs", 0, 599, 1366, 136, true, false, KE::DockSide::DOWN)
		{
            properties.flags = ImGuiWindowFlags_AlwaysAutoResize;
		}

		void OnReady() override
		{

		}

		void OnRender() override
		{

		}
	};

	LogsWindow logsWindow;
}
