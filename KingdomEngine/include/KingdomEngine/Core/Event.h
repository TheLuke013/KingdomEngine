#ifndef EVENT_H
#define EVENT_H

#include <vector>

namespace KE
{
	enum class EventType
	{
		NONE,
		CLOSE_APPLICATION,
		RESTART_IMGUI,
		ACTIVE_IMGUI,
		DISABLE_IMGUI,
		ACTIVE_DOCKSPACE,
		DISABLE_DOCKSPACE,
		LOAD_OPENGL2,
		LOAD_OPENGL3
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
