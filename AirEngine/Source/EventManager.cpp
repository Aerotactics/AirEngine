#include "EventManager.h"

#include "AirEngine.h"
#include "IEvent.h"

void EventManager::RegisterListener(const char* pEventName, Listener* pListener)
{
	m_listeners[pEventName].push_back(pListener);
}

void EventManager::UnregisterListener(const char* pEventName, Listener* pListener)
{
	if (auto it = std::find(m_listeners[pEventName].begin(), m_listeners[pEventName].end(), pListener); it != m_listeners[pEventName].end())
	{
		m_listeners[pEventName].erase(it);
	}
}

void EventManager::QueueEvent(IEvent* pEvent)
{
	//For now, we won't worry about duplicates.
	m_events.push_back(pEvent);
}

void EventManager::ProcessEvents()
{
	std::vector<IEvent*> events;
	std::swap(m_events, events);
	for (auto pEvent : events)
	{
		for(auto pListener : m_listeners[pEvent->GetName()])
			pListener->TriggerEvent(pEvent);
		BLEACH_DELETE(pEvent);
	}
	events.clear();
}

bool EventManager::IsEventType(IEvent* pEvent, const char* pEventName) const
{
	return (pEvent->GetName() == pEventName);
}
