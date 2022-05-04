#pragma once

#include "IGameObject.h"

class TransformComponent;

class Ball : public IGameObject
{
private:
	Vector2<float> m_direction;
	TransformComponent* m_pTransformComponent;
	bool m_lazyInit;
	float m_speed;

public:
	Ball(ObjectID id)
		: IGameObject(id)
		, m_pTransformComponent(nullptr)
		, m_lazyInit(false)
		, m_speed(0)
	{}

	virtual void Tick(double delta) override final;

	virtual void OnEnterCollision(IGameObject* pOther) override final;

private:
	void Reset();
	void Move();
	void SetRandomVelocity();

	void SetVelocity(float angleDegrees, float speed);
};