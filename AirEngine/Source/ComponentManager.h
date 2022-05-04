#pragma once
#include <vector>
#include <string>

class ComponentFactory;
class IComponent;
class ITickable;

namespace tinyxml2
{
	class XMLElement;
}

// Handles all component-related management, previously handled by
//	GameObjectManager. This class is owned by GameObjectManager,
//	but now functions within its own space.
class ComponentManager
{
private:
	std::vector<ITickable*> m_tickables;
	std::vector<IComponent*> m_components;
	ComponentFactory* m_pComponentFactory;

public:
	ComponentManager();
	ComponentManager(const ComponentManager&) = delete;
	ComponentManager(ComponentManager&&) noexcept = delete;
	ComponentManager& operator=(const ComponentManager&) = delete;
	ComponentManager& operator=(ComponentManager&&) noexcept = delete;
	~ComponentManager();

	bool Init();
	void Update(double delta);

	IComponent* CreateComponent(tinyxml2::XMLElement* pElement);
	void DeleteComponent(IComponent* pComponent);

	void AddTickable(ITickable* pTickable);
	void RemoveTickable(ITickable* pTickable);

	ComponentFactory* GetComponentFactory() { return m_pComponentFactory; }
};
