#ifndef CONSOLE_WINDOW_H
#define CONSOLE_WINDOW_H

#include <KingdomEngine/ImGui/ImWindow.h>

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
}

#endif
