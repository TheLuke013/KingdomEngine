#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#include <KingdomEngine/Core/Application.h>
#include <KingdomEngine/Core/EntryPoint.h>
#include <KingdomEngine/Core/FontManager.h>
#include <KingdomEngine/ImGui/ImMenuManager.h>

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

	private:
		bool closeAfterSave;

	};
}

#endif
