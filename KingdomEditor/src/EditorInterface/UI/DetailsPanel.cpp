#include "KingdomEditor/EditorInterface/EditorInterface.h"

namespace Editor
{
	class DetailsPanel : public EditorInterface
	{
	public:
		DetailsPanel() : EditorInterface("Details Panel", 1184, 19, 182, 578, false, RIGHT)
		{

		}

		void OnRender() override
		{
			
		}
	};

	DetailsPanel detailsPanel;
}
