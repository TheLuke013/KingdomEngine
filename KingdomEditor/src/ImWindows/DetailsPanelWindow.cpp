#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class DetailsPanelWindow : public KE::ImWindow
	{
	public:
		DetailsPanelWindow() : KE::ImWindow("Details Panel", 1184, 19, 182, 578, true, false, KE::DockSide::RIGHT)
		{

		}

		void OnReady() override
		{

		}

		void OnRender() override
		{

		}
	};

	DetailsPanelWindow detailsPanelWindow;
}
