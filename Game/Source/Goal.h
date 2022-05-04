#pragma once

#include "StaticObject.h"
#include "Player.h"

class Goal : public StaticObject
{
private:
	unsigned int m_player;

public:
	Goal(ObjectID id)
		: StaticObject(id)
		, m_player(0)
	{}

	virtual bool Init(tinyxml2::XMLElement* pElement) override final;

	virtual void OnEnterCollision(IGameObject* pOther) override final;
};
