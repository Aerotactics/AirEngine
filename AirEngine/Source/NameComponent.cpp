#include "NameComponent.h"

#include "AirEngine.h"
#include "TinyXML/tinyxml2.h"

NameComponent::NameComponent()
	: m_pName(nullptr)
{}

bool NameComponent::Init(tinyxml2::XMLElement* pData)
{
	pData->QueryStringAttribute("name", &m_pName);
	return true;
}
