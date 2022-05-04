#pragma once
#include "IComponent.h"
#include "ITickable.h"
#include "SFMLInput.h"

using Key = InputCodes::Key;

class TransformComponent;

class ControllerComponent : public IComponent, public ITickable
{
private:
	TransformComponent* m_pTransformComponent;
	struct Keys
	{
		Key up;
		Key down;
		Key left;
		Key right;
	} m_keys;

public:
	ControllerComponent();

	virtual bool Init(tinyxml2::XMLElement* pData) override final;
	virtual void Tick(double delta) override final;

	void SetKeys(int up, int down, int left, int right);
	void SetTransformComponent(TransformComponent* pTransformComponent) { m_pTransformComponent = pTransformComponent; }

	void GetKeys(Key& up, Key& down, Key& left, Key& right);
};