#include "GameObjectFactory.h"

#include "AirEngine.h"
#include "ComponentManager.h"

GameObjectFactory::GameObjectFactory(GameObjectManager* pOwner)
	: m_pOwner(pOwner)
	, m_pComponentFactory(nullptr)
{
}

bool GameObjectFactory::Init()
{
	m_pComponentFactory = m_pOwner->GetComponentManager()->GetComponentFactory();
	m_pResourceManager = AirEngine::GetResourceManager();
	if(!m_pComponentFactory || !m_pResourceManager)
		return false;
	return true;
}
