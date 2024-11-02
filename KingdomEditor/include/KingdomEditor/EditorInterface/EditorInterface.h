#ifndef EDITOR_INTERFACE_H
#define EDITOR_INTERFACE_H

#include <ImGui/imgui.h>

#include <string>
#include <vector>

namespace Editor
{
	class EditorInterface
	{
	public:
		EditorInterface(const std::string& name, float xPos, float yPos, float xSize, float ySize, bool collapsed);
		virtual ~EditorInterface();

		void Render();

		virtual void OnRender() = 0;
	private:
		ImVec2 position;
		ImVec2 size;
		bool collapsed;
		bool isInitialized;
		std::string name;
	};

	class EditorInterfaceManager
	{
	public:
		static EditorInterfaceManager& Get();

		void Register(EditorInterface* interface);
		void UpdateInterfaces();

	private:
		EditorInterfaceManager() {}

		std::vector<EditorInterface*> interfaces;
	};
}

#define UPDATE_EDITOR_INTERFACES() Editor::EditorInterfaceManager::Get().UpdateInterfaces();
#define REGISTER_EDITOR_INTERFACE(interface_) Editor::EditorInterfaceManager::Get().Register(interface_);

#endif
