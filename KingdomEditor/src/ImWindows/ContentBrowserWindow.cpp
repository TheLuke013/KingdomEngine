#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class ContentBrowserWindow : public KE::ImWindow
	{
	public:
		ContentBrowserWindow() : KE::ImWindow("Content Browser", 0, 355, 172, 242, true, KE::DockSide::LEFT_TOP)
		{

		}

		void OnRender() override
		{

		}
	};

	ContentBrowserWindow contentBrowserWindow;
}
