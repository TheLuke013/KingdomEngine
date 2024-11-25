#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class DetailsPanelWindow : public KE::ImWindow
	{
	public:
		DetailsPanelWindow() : KE::ImWindow("Details Panel", 1184, 19, 182, 578, true, KE::DockSide::RIGHT)
		{

		}

		void OnRender() override
		{

		}
	};

	DetailsPanelWindow detailsPanelWindow;
}
