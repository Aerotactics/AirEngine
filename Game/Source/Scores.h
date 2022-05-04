#pragma once

#include "StaticObject.h"

class Player;

class Scores : public IGameObject, public Listener
{
private:
	std::vector<int> m_scores;

public:
	Scores(ObjectID id)
		: IGameObject(id)
		, m_scores()
	{}

	virtual bool Init(tinyxml2::XMLElement* pElement) override final;
	virtual void Tick(double delta) override final;
	virtual void TriggerEvent(IEvent* pEvent) override final;
};