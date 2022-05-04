#pragma once
#include "IComponent.h"
#include "ITickable.h"

#include <vector>

class SpriteComponent;
class TransformComponent;

class CollisionComponent : public IComponent, public ITickable
{
private:
	SpriteComponent* m_pSpriteComponent;
	TransformComponent* m_pTransformComponent;

	std::vector<GameObject*> m_collisionsThisFrame;
	std::vector<GameObject*> m_recurringCollisions;

public:
	CollisionComponent();

	virtual bool Init([[maybe_unused]] tinyxml2::XMLElement* pData) override final;
	virtual void Tick([[maybe_unused]] double delta) override final;

	bool IsColliding(GameObject* pObject);

	void SetSpriteComponent(SpriteComponent* pSpriteComponent) { m_pSpriteComponent = pSpriteComponent; }
	void SetTransformComponent(TransformComponent* pTransformComponent) { m_pTransformComponent = pTransformComponent; }

private:
	void OnCollide(GameObject* pObject);

	void OnEnterCollision(GameObject* pObject);
	void OnExitCollision(GameObject* pObject);
};