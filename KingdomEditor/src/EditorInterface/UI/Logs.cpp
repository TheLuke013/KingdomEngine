#include "KingdomEditor/EditorInterface/EditorInterface.h"

namespace Editor
{
	class Logs : public EditorInterface
	{
	public:
		Logs() : EditorInterface("Logs", 0, 599, 1366, 136, true, DOWN)
		{

		}

		void OnRender() override
		{
			
		}
	};

	Logs Logs;
}
