#include "KingdomEditor/EditorInterface/EditorInterface.h"

namespace Editor
{
	class Console : public EditorInterface
	{
	public:
		Console() : EditorInterface("Console", 0, 599, 1366, 98, false, DOWN)
		{

		}

		void OnRender() override
		{
			
		}
	};

	Console console;
}
