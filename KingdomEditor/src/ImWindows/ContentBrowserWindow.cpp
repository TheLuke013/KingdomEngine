#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class ContentBrowserWindow : public KE::ImWindow
	{
	public:
		ContentBrowserWindow() : KE::ImWindow("Content Browser", 0, 355, 172, 242, true, false, KE::DockSide::LEFT_BOTTOM)
		{

		}

		void OnReady() override
		{

		}

		void OnRender() override
		{
			
		}
	};

	ContentBrowserWindow contentBrowserWindow;
}
