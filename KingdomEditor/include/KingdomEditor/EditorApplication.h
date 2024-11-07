#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#include <KingdomEngine/KingdomEngine.h>

#include "KingdomEditor/EditorInterface/EditorInterfaceManager.h"

namespace Editor
{
	class EditorApplication : public KE::Application
	{
	public:
		EditorApplication();
		~EditorApplication();

		void OnReady() override;
		void OnUpdate() override;
		void OnEvent(KE::Event e) override;
		void OnImGuiRender() override;
		void OnMenuBarRender() override;
		void OnDockspaceUpdate() override;

	};
}

#endif