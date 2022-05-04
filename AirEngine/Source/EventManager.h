#pragma once
#include <unordered_map>
#include <vector>
#include <string>

struct IEvent;

//TODO: These should be templated. I'm not sure why I
//	chose to make all events trigger the same listener
//	class. Seems bad. I also dont know why I decided that
//	comparing strings everywhere was the right way to do
//	what I intended. Too late to fix that now, but at
//	least I know where it went wrong.
class Listener
{
public:
	virtual void TriggerEvent([[maybe_unused]] IEvent* pEvent) {}
};

class EventManager
{
private:
	std::vector<IEvent*> m_events;
	std::unordered_map<std::string, std::vector<Listener*>> m_listeners;

public:
	void RegisterListener(const char* pEventName, Listener* pListener);
	void UnregisterListener(const char* pEventName, Listener* pListener);
	void QueueEvent(IEvent* pEvent);
	void ProcessEvents();

	bool IsEventType(IEvent* pEvent, const char* pEventName) const;
};