#pragma once
#include "IEvent.h"

struct GoalEvent : public IEvent
{
private:
	unsigned int m_scorer;

public:
	GoalEvent(unsigned int scorer)
		: IEvent("GoalEvent")
		, m_scorer(scorer)
	{}

	unsigned int GetScorer() const { return m_scorer; }
};