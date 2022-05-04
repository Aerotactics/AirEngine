#include "AirEngine.h"

#include "Scores.h"
#include "GoalEvent.h"

bool Scores::Init([[maybe_unused]] tinyxml2::XMLElement* pElement)
{
	m_scores.push_back(0);
	m_scores.push_back(0);
	AirEngine::GetEventManager()->RegisterListener("GoalEvent", this);
	return true;
}

void Scores::Tick(double delta)
{
	for (size_t i = 0; i < m_scores.size(); ++i)
	{
		float spacing = float(832 * i + 64);
		AirEngine::GetRenderer()->DrawText(std::to_string(m_scores[i]).c_str(), {spacing, 64.f}, "Pixellari.ttf", 128);
	}
	UpdateComponents(delta);
}

void Scores::TriggerEvent(IEvent* pEvent)
{
	if(!AirEngine::GetEventManager()->IsEventType(pEvent, "GoalEvent"))
		return;

	unsigned int scorer = static_cast<GoalEvent*>(pEvent)->GetScorer() - 1;

	if (scorer < m_scores.size())
	{
		++m_scores[scorer];
	}
}
