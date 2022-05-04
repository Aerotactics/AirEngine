#include "ControllerComponent.h"

#include "AirEngine.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SFMLInput.h"
#include "TinyXML/tinyxml2.h"

//TODO: Move these to XML?
constexpr float kVerticalMoveSpeed = 350.f;
constexpr float kHorizontalMoveSpeed = 350.f;

using XMLElement = tinyxml2::XMLElement;
using Input = IInput<SFMLInput>;

ControllerComponent::ControllerComponent()
	: m_pTransformComponent(nullptr)
{
	m_keys.up = Key::Unknown;
	m_keys.down = Key::Unknown;
	m_keys.left = Key::Unknown;
	m_keys.right = Key::Unknown;
}

bool ControllerComponent::Init(tinyxml2::XMLElement* pData)
{
	int up = pData->IntAttribute("up", -1);
	int down = pData->IntAttribute("down", -1);
	int left = pData->IntAttribute("left", -1);
	int right = pData->IntAttribute("right", -1);

	SetKeys(up, down, left, right);

	IComponent* pComponent = m_pOwner->GetComponent("TransformComponent");

	if (!pComponent)
		return false;

	SetTransformComponent(static_cast<TransformComponent*>(pComponent));
	return true;
}

// TODO: Make this less bad
void ControllerComponent::Tick(double delta)
{
	Vector2<float> move;
	if (Input::KeyPressed(m_keys.up))
		move.y -= kVerticalMoveSpeed * (float)delta;
	if (Input::KeyPressed(m_keys.down))
		move.y += kVerticalMoveSpeed * (float)delta;
	if (Input::KeyPressed(m_keys.left))
		move.x -= kHorizontalMoveSpeed * (float)delta;
	if (Input::KeyPressed(m_keys.right))
		move.x += kHorizontalMoveSpeed * (float)delta;

	if (move.x != 0 || move.y != 0)
		m_pTransformComponent->Move(move);
}

void ControllerComponent::SetKeys(int up, int down, int left, int right)
{
	m_keys.up = static_cast<Key>(up);
	m_keys.down = static_cast<Key>(down);
	m_keys.left = static_cast<Key>(left);
	m_keys.right = static_cast<Key>(right);
}

void ControllerComponent::GetKeys(Key& up, Key& down, Key& left, Key& right)
{
	up = m_keys.up;
	down = m_keys.down;
	left = m_keys.left;
	right = m_keys.right;
}