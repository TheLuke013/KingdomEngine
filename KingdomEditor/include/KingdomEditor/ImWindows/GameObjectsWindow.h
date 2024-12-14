#ifndef GAME_OBJECTS_WINDOW_H
#define GAME_OBJECTS_WINDOW_H

#include <KingdomEngine/ImGui/ImWindow.h>

namespace Editor
{
	class GameObjectsWindow : public KE::ImWindow
	{
	public:
		GameObjectsWindow() : KE::ImWindow("Objects", 0, 19, 172, 334, true, false, KE::DockSide::LEFT_TOP)
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
