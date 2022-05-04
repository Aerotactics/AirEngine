#pragma once
#include <unordered_map>
#include <string>

namespace tinyxml2{ class XMLElement; }

using ObjectID = uint64_t;

class GameObjectManager;
class IComponent;

class GameObject
{
	friend GameObjectManager;

private:
	ObjectID m_id;
	std::unordered_map<std::string, IComponent*> m_components;
	bool m_toDelete;

public:
	GameObject();
	virtual ~GameObject();

	virtual bool Init() { return true; }
	virtual void Tick([[maybe_unused]] double delta) {}

	void AddComponent(const std::string& componentName, IComponent* pComponent);
	IComponent* GetComponent(const char* pName);

	ObjectID GetID() const { return m_id; }
	void MarkForDelete() { m_toDelete = true; }
	bool IsMarkedForDelete() const { return m_toDelete; }

	virtual void OnCollide([[maybe_unused]] GameObject* pOther) {};
	virtual void OnEnterCollision([[maybe_unused]] GameObject* pOther) {};
	virtual void OnExitCollision([[maybe_unused]] GameObject* pOther) {};

protected:
	void SetID(ObjectID id) { m_id = id; }
};

