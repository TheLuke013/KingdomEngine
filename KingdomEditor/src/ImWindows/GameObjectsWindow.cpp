#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class GameObjectsWindow : public KE::ImWindow
	{
	public:
		GameObjectsWindow() : KE::ImWindow("Game Objects", 0, 19, 172, 334, true, KE::DockSide::LEFT_BOTTOM)
		{

		}

		void OnRender() override
		{

		}
	};

	GameObjectsWindow gameObjectsWindow;
}
