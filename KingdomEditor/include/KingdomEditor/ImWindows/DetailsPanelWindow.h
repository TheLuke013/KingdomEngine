#ifndef DETAILS_PANEL_WINDOW_H
#define DETAILS_PANEL_WINDOW_H

#include <KingdomEngine/ImGui/ImWindow.h>

namespace Editor
{
	class DetailsPanelWindow : public KE::ImWindow
	{
	public:
		DetailsPanelWindow() : KE::ImWindow("Properties", 1184, 19, 182, 578, true, false, KE::DockSide::RIGHT)
		{

		}

		void OnReady() override
		{

		}

		void OnRender() override
		{

		}
	};
}

#endif
