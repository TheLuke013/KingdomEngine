#ifndef IMGUI_EVENT_H
#define IMGUI_EVENT_H

#include "KingdomEngine/Events/Event.h"
#include "KingdomEngine/ImGui/ImGuiManager.h"

namespace KE
{	
	class ImGuiEvent : public EventListener
	{
	public:	
		void _OnEvent() override
		{
			switch (eventType)
			{
				case EventType::RestartImGui:
					ImGuiManager::Get().Restart();
					eventType = EventType::None;
					break;
				case EventType::EnableImGui:
					ImGuiManager::Get().Enable();
					eventType = EventType::None;
					break;
				case EventType::DisableImGui:
					ImGuiManager::Get().Disable();
					eventType = EventType::None;
					break;
				case EventType::EnableDockspace:
					ImGuiManager::Get().EnableDockspace();
					eventType = EventType::None;
					break;
				case EventType::DisableDockspace:
					ImGuiManager::Get().DisableDockspace();
					eventType = EventType::None;
					break;
				default:
					break;
			}
		}		
	};
}

#endif