#include "GameObjectManager.h"

#include "AirEngine.h"
#include "ComponentManager.h"
#include "GameObject.h"
#include "CallbackProcess.h"

// MaxID is set to 1 since 0 is reserved for objects
//	without an ID.
GameObjectManager::GameObjectManager()
	: m_maxID(1)
	, m_pObjectFactory(nullptr)
	, m_pComponentManager(nullptr)
{
}

GameObjectManager::~GameObjectManager()
{
	DestroyAllObjects();

	BLEACH_DELETE(m_pObjectFactory);
	BLEACH_DELETE(m_pComponentManager);
}

bool GameObjectManager::Init()
{
	m_pObjectFactory = BLEACH_NEW(GameObjectFactory(this));
	m_pComponentManager = BLEACH_NEW(ComponentManager());
	if(!m_pObjectFactory 
		|| !m_pComponentManager 
		|| !m_pComponentManager->Init()
		|| !m_pObjectFactory->Init())
		return false;

	return true;
}

void GameObjectManager::Update(double delta)
{
	for(auto pObject : m_objects)
		pObject->Tick(delta);
	m_pComponentManager->Update(delta);
}

void GameObjectManager::DestroyObject(ObjectID id)
{
	if (id == 0 || id >= m_maxID)
	{
		ERR("[GameObjectManager] Attempted destroying object without valid ID.");
		return;
	}

	AirEngine::GetProcessManager()->StartProcess(new CallbackProcess([this, id]()
	{  
		_DestroyObject(id);
	}));
}

void GameObjectManager::DestroyAllObjects()
{
	for (auto object : m_objects)
		BLEACH_DELETE(object);

	m_objects.clear();
}

ObjectID GameObjectManager::_GetNextID()
{
	ObjectID newID;
	if (!m_freeObjectIDs.empty())
	{
		newID = m_freeObjectIDs.back();
		m_freeObjectIDs.pop_back();
	}
	else
	{
		newID = m_maxID;
		++m_maxID;
	}
	return newID;
}

void GameObjectManager::_DestroyObject(ObjectID id)
{
	size_t it = 0;
	for (auto pObject : m_objects)
	{
		if (pObject->GetID() == id)
		{
			m_freeObjectIDs.push_back(id);
			m_objects.erase(m_objects.begin() + it);
		}
		++it;
	}
}
