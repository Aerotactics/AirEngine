#include "ComponentManager.h"

#include "ComponentFactory.h"
#include "ITickable.h"
#include "Logger.h"

ComponentManager::ComponentManager()
	: m_pComponentFactory(nullptr)
{
}

ComponentManager::~ComponentManager()
{
	BLEACH_DELETE(m_pComponentFactory);
}

bool ComponentManager::Init()
{
	m_pComponentFactory = BLEACH_NEW(ComponentFactory);
	return m_pComponentFactory->Init();
}

void ComponentManager::Update(double delta)
{
	for(auto pTickable : m_tickables)
		pTickable->Tick(delta);
}

IComponent* ComponentManager::CreateComponent(tinyxml2::XMLElement* pElement)
{
	return m_pComponentFactory->CreateComponent(pElement);
}

void ComponentManager::DeleteComponent(IComponent* pComponent)
{
	if(auto it = std::find(m_components.begin(), m_components.end(), pComponent); it != m_components.end())
		m_components.erase(it);
}

void ComponentManager::AddTickable(ITickable* pTickable)
{
	m_tickables.emplace_back(pTickable);
}

void ComponentManager::RemoveTickable(ITickable* pTickable)
{
	if(auto it = std::find(m_tickables.begin(), m_tickables.end(), pTickable); it != m_tickables.end())
		m_tickables.erase(it);
	else
		ERR("[ComponentManager] Attempted to remove non-existent ITickable.");
}
