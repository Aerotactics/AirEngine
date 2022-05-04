#pragma once
#include "GameObjectFactory.h"

#include <vector>

class ComponentManager;
class GameObject;
class ITickable;
class World;

using ObjectID = uint64_t;

class GameObjectManager
{
private:
	std::vector<GameObject*> m_objects;
	std::vector<ObjectID> m_freeObjectIDs;
	ObjectID m_maxID;

	GameObjectFactory* m_pObjectFactory;
	ComponentManager* m_pComponentManager;

public:
	GameObjectManager();
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager(GameObjectManager&&) noexcept = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;
	GameObjectManager& operator=(GameObjectManager&&) noexcept = delete;
	~GameObjectManager();

	bool Init();
	void Update(double delta);

	template<class ObjectType>
	GameObject* CreateObject(const char* pFilename);
	
	void DestroyObject(ObjectID id);
	void DestroyAllObjects();

	size_t GetObjectCount() const { return m_objects.size(); }

	ComponentManager* GetComponentManager() { return m_pComponentManager; }

private:
	ObjectID _GetNextID();
	void _DestroyObject(ObjectID id);
};

// Calls the Factory and makes an object (therefor, 
//	must also be templated)
template<class ObjectType>
inline GameObject* GameObjectManager::CreateObject(const char* pFilename)
{
	GameObject* pObject = m_pObjectFactory->CreateObject<ObjectType>(pFilename);
	if (pObject)
	{
		m_objects.push_back(pObject);
	}
	return pObject;
}
