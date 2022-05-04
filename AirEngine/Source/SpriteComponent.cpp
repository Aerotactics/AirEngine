#include "SpriteComponent.h"

#include "AirEngine.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TinyXML/tinyxml2.h"

using XMLElement = tinyxml2::XMLElement;

SpriteComponent::SpriteComponent()
	: m_pTransform(nullptr)
	, m_pSprite(nullptr)
{}

SpriteComponent::~SpriteComponent()
{
	BLEACH_DELETE(m_pSprite);
}

bool SpriteComponent::Init(XMLElement* pData)
{
	const char* filename = nullptr;
	pData->QueryStringAttribute("Texture", &filename);

	if (!filename)
		return false;

	SpriteData data;
	data.pTexture = (Texture*)AirEngine::GetResourceManager()->Load(filename);
	data.width = pData->IntAttribute("width");
	data.height = pData->IntAttribute("height");
	data.origin = Vector2<float>(pData->FloatAttribute("originX"), pData->FloatAttribute("originY"));
	m_pSprite = BLEACH_NEW(Sprite);
	m_pSprite->Load(data);

	//Requires a Transform Component
	IComponent* pComponent = m_pOwner->GetComponent("TransformComponent");
	if (pComponent)
		SetTransform(static_cast<TransformComponent*>(pComponent));
	return true;
}

void SpriteComponent::Tick([[maybe_unused]] double delta)
{
	if (m_pTransform)
	{
		m_pSprite->SetPosition(m_pTransform->GetPosition());
		m_pSprite->SetScale(m_pTransform->GetScale());
	}
}