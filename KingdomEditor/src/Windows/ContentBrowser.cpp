#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
	class ContentBrowser : public KE::ImWindow
	{
	public:
		ContentBrowser() : KE::ImWindow("Content Browser", 0, 355, 172, 242, true, KE::DockSide::LEFT_TOP)
		{

		}

		void OnRender() override
		{
			
		}
	};

	ContentBrowser contentBrowser;
}
