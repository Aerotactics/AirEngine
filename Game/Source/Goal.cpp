#include "pch.h"
#include "Goal.h"

#include "AirEngine.h"
#include "Events.h"
#include "TinyXML/tinyxml2.h"

bool Goal::Init(tinyxml2::XMLElement* pElement)
{
	m_player = pElement->IntAttribute("player");
	return true;
}

void Goal::OnEnterCollision(IGameObject* pOther)
{
	std::string name = pOther->GetName();

	if (name == "Ball")
	{
		AirEngine::GetEventManager()->QueueEvent(new GoalEvent(m_player));
	}
}
