#pragma once

#include "IGameObject.h"

class StaticObject : public IGameObject
{
public:
	StaticObject(ObjectID id)
		: IGameObject(id)
	{}

	void SetPosition(Vector2<float> position);
};