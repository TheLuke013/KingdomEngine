#include "KingdomEditor/EditorInterface/EditorInterface.h"

namespace Editor
{
	class ContentBrowser : public EditorInterface
	{
	public:
		ContentBrowser() : EditorInterface("Content Browser", 0, 355, 172, 242, true, LEFT_TOP)
		{

		}

		void OnRender() override
		{
			
		}
	};

	ContentBrowser contentBrowser;
}
