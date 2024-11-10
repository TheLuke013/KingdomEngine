#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class Logs : public KE::ImWindow
	{
	public:
		Logs() : KE::ImWindow("Logs", 0, 599, 1366, 136, true, KE::DockSide::DOWN)
		{

		}

		void OnRender() override
		{
			
		}
	};

	Logs Logs;
}
