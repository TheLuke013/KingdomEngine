#include "KingdomEditor/EditorInterface/EditorInterface.h"

namespace Editor
{
	class GameObjects : public EditorInterface
	{
	public:
		GameObjects() : EditorInterface("Game Objects", 0, 19, 172, 334, false)
		{

		}

		void OnRender() override
		{
			
		}
	};

	GameObjects gameObjects;
}
