#pragma once
#include "IComponent.h"
#include "ITickable.h"

#include "Vector2.h"

class TransformComponent : public IComponent, public ITickable
{
private:
	Vector2<float> m_position;
	Vector2<float> m_scale;
	Vector2<float> m_deltaPosition;
	Vector2<float> m_previousDeltaPosition;

public:
	TransformComponent();

	virtual bool Init(tinyxml2::XMLElement* pData) override final;
	virtual void Tick(double delta) override final;

	Vector2<float> GetPosition() const { return m_position; }
	Vector2<float> GetScale() const { return m_scale; }

	void SetPosition(Vector2<float> position) { m_position = position; }
	void SetScale(Vector2<float> scale) { m_scale = scale; }

	void Move(Vector2<float> offset) { m_deltaPosition += offset; }
	void Scale(Vector2<float> offset) { m_scale += offset; }

	void OnCollide(GameObject* pObject);
};