#pragma once

#include "IGameObject.h"

class Player : public IGameObject
{
public:
	Player(ObjectID id)
		: IGameObject(id)
	{}

	void SetPosition(Vector2<float> position);
	void SetControls(int up, int down, int left, int right);
	void PlayAnimation(const char* filename, double framerate, bool isLooping = false);

	virtual void OnEnterCollision(IGameObject* other) override final;

	virtual void Tick(double delta) override final;
};
