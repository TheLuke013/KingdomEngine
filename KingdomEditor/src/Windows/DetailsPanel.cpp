#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class DetailsPanel : public KE::ImWindow
	{
	public:
		DetailsPanel() : KE::ImWindow("Details Panel", 1184, 19, 182, 578, true, KE::DockSide::RIGHT)
		{

		}

		void OnRender() override
		{
			
		}
	};

	DetailsPanel detailsPanel;
}
