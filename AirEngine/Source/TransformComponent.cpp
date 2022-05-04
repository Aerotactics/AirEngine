#include "TransformComponent.h"

#include "AirEngine.h"
#include "TinyXML/tinyxml2.h"

using XMLElement = tinyxml2::XMLElement;

TransformComponent::TransformComponent()
{}

bool TransformComponent::Init(XMLElement* pData)
{
	auto pElement = pData->FirstChildElement("Position");
	if (pElement)
		m_position = Vector2<float>(pElement->FloatAttribute("x"), pElement->FloatAttribute("y"));

	pElement = pData->FirstChildElement("Scale");
	if (pElement)
		m_scale = Vector2<float>(pElement->FloatAttribute("x"), pElement->FloatAttribute("y"));

	return true;
}

void TransformComponent::Tick([[maybe_unused]] double delta)
{
	m_position += m_deltaPosition;
	m_previousDeltaPosition = m_deltaPosition;
	m_deltaPosition = Vector2<float>(0, 0);
}

void TransformComponent::OnCollide([[maybe_unused]] GameObject* pObject)
{
	m_position -= m_previousDeltaPosition;
}