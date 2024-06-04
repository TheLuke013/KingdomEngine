#ifndef EVENT_H
#define EVENT_H

#include <vector>

namespace KE
{
	enum EventType
	{
		NONE,
		CLOSE_APPLICATION
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
		virtual ~EventListener() = default;

		virtual void _OnEvent(Event e) = 0;
	};

	class EventManager
	{
	public:
		static EventManager& Get();

		void Register(EventListener* listener);
		void Fire(Event e);

	private:
		EventManager() {}

		std::vector<EventListener*> listeners;
	};
}

#define DISPATCH_EVENT(e) KE::EventManager::Get().Fire(e);
#define REGISTER_EVENT_LISTENER(listener) KE::EventManager::Get().Register(listener);

#endif
