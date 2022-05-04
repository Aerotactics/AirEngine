#include "CollisionComponent.h"

#include "AirEngine.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

CollisionComponent::CollisionComponent()
	: m_pSpriteComponent(nullptr)
	, m_pTransformComponent(nullptr)
{}

bool CollisionComponent::Init([[maybe_unused]] tinyxml2::XMLElement* pData)
{
	IComponent* pComponent = m_pOwner->GetComponent("TransformComponent");
	if (!pComponent)
		return false;
	SetTransformComponent(static_cast<TransformComponent*>(pComponent));

	pComponent = m_pOwner->GetComponent("SpriteComponent");
	if (!pComponent)
		return false;
	SetSpriteComponent(static_cast<SpriteComponent*>(pComponent));

	return true;
}

void CollisionComponent::Tick([[maybe_unused]] double delta)
{
	for (int i = (int)m_recurringCollisions.size() - 1; i >= 0; --i)
	{
		if (auto it = std::find(m_collisionsThisFrame.begin(), m_collisionsThisFrame.end(), m_recurringCollisions[i]); it == m_collisionsThisFrame.end())
		{
			OnExitCollision(m_recurringCollisions[i]);
			m_recurringCollisions.erase(m_recurringCollisions.begin() + i);
		}
	}
	m_collisionsThisFrame.clear();
}

bool CollisionComponent::IsColliding(GameObject* pObject)
{
	if (!pObject)
		return false;

	Vector2<float> pos = m_pTransformComponent->GetPosition();
	Vector2<float> size = m_pSpriteComponent->GetSize();
	float left = pos.x;
	float top = pos.y;
	float right = pos.x + size.x;
	float bottom = pos.y + size.y;

	Vector2<float> pos2 = static_cast<TransformComponent*>(pObject->GetComponent("TransformComponent"))->GetPosition();
	Vector2<float> size2 = static_cast<SpriteComponent*>(pObject->GetComponent("SpriteComponent"))->GetSize();
	float otherLeft = pos2.x;
	float otherTop = pos2.y;
	float otherRight = pos2.x + size2.x;
	float otherBottom = pos2.y + size2.y;

	bool collide = false;

	bool xOverlap = left < otherRight&& right > otherLeft;
	bool yOverlap = top < otherBottom&& bottom > otherTop;

	if (xOverlap && yOverlap)
	{
		collide = true;
		OnCollide(pObject);
		static_cast<CollisionComponent*>(pObject->GetComponent("CollisionComponent"))->OnCollide(m_pOwner);
	}

	return collide;
}

void CollisionComponent::OnCollide(GameObject* pObject)
{
	m_collisionsThisFrame.push_back(pObject);
	if (auto it = std::find(m_recurringCollisions.begin(), m_recurringCollisions.end(), pObject); it == m_recurringCollisions.end())
	{
		OnEnterCollision(pObject);
	}
	m_recurringCollisions.push_back(pObject);

	m_pOwner->OnCollide(pObject);
	m_pTransformComponent->OnCollide(pObject);
}

void CollisionComponent::OnEnterCollision(GameObject* pObject)
{
	m_pOwner->OnEnterCollision(pObject);
}

void CollisionComponent::OnExitCollision(GameObject* pObject)
{
	m_pOwner->OnExitCollision(pObject);
}