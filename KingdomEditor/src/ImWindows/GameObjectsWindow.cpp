#include <KingdomEngine/KingdomEngine.h>

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

	GameObjectsWindow gameObjectsWindow;
}
