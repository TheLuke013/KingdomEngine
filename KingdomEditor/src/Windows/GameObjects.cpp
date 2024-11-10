#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class GameObjects : public KE::ImWindow
	{
	public:
		GameObjects() : KE::ImWindow("Game Objects", 0, 19, 172, 334, true, KE::DockSide::LEFT_BOTTOM)
		{

		}

		void OnRender() override
		{
			
		}
	};

	GameObjects gameObjects;
}
