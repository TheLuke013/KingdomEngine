#include "KingdomEditor/EditorInterface/EditorInterface.h"

namespace Editor
{
	EditorInterface::EditorInterface(const std::string& name, float xPos, float yPos, float xSize, float ySize, bool collapsed)
	{
		position = ImVec2(xPos, yPos);
		size = ImVec2(xSize, ySize);
		this->collapsed = collapsed;
		this->name = name;

		isInitialized = false;

		REGISTER_EDITOR_INTERFACE(this);
	}

	EditorInterface::~EditorInterface()
	{
	}

	void EditorInterface::Render()
	{
		if (!isInitialized)
		{
			ImGui::SetNextWindowPos(position);
			ImGui::SetNextWindowSize(size);
			isInitialized = true;
		}
		ImGui::Begin(name.c_str(), &collapsed);
		OnRender();
		ImGui::End();
	}

	EditorInterfaceManager& EditorInterfaceManager::Get()
	{
		static EditorInterfaceManager* instance = new EditorInterfaceManager();
		return *instance;
	}

	void EditorInterfaceManager::Register(EditorInterface* interface)
	{
		interfaces.push_back(interface);
	}

	void EditorInterfaceManager::UpdateInterfaces()
	{
		for (auto interface : interfaces)
		{
			interface->Render();
		}
	}
}