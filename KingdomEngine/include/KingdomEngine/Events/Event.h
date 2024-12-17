#ifndef EVENT_H
#define EVENT_H

#include <vector>

namespace KE
{
	enum class EventType
	{
		None,
		WindowClose,
		RestartImGui,
		EnableImGui,
		DisableImGui,
		EnableDockspace,
		DisableDockspace,
		LoadGL2,
		LoadGL3,
		KeyPressed,
		KeyReleased
	};

	class Event
	{
	public:
		EventType type_;

		Event(EventType type)
			: type_(type)
		{

		}
	};

	class EventListener
	{
	public:
		EventType eventType;
		
		virtual ~EventListener() = default;

		virtual void _OnEvent() = 0;
	};

	class EventManager
	{
	public:
		static EventManager& Get()
		{
			static EventManager* instance = new EventManager();
			return *instance;
		}

		void Register(EventListener* listener)
		{
			listeners.push_back(listener);
		}
		
		void Dispatch(Event e)
		{
			for (auto listener : listeners)
			{
				listener->eventType = e.type_;
			}
		}
		
		void ProcessAllEvents()
		{
			for (auto listener : listeners)
			{
				listener->_OnEvent();
			}
		}

	private:
		EventManager() {}

		std::vector<EventListener*> listeners;
	};
}

#define DISPATCH_EVENT(e) KE::EventManager::Get().Dispatch(e);
#define PROCESS_ALL_EVENTS() KE::EventManager::Get().ProcessAllEvents();
#define REGISTER_EVENT_LISTENER(listener) KE::EventManager::Get().Register(listener);

#endif
