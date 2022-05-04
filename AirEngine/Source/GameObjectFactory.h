#pragma once

//Required
#include "ResourceManager.h"
#include "ComponentFactory.h"
#include "GameObject.h"
#include "TinyXML/tinyxml2.h"

#include <unordered_map>
#include <functional>
#include <string>

using namespace tinyxml2;

class GameObjectManager;
class ResourceManager;
class IComponent;

//Creates GameObjects
class GameObjectFactory
{
	friend GameObjectManager;

private:
	GameObjectManager* m_pOwner;
	ResourceManager* m_pResourceManager;
	ComponentFactory* m_pComponentFactory;

public:
	GameObjectFactory(GameObjectManager* pOwner);
	GameObjectFactory(const GameObjectFactory&) = delete;
	GameObjectFactory(GameObjectFactory&&) noexcept = delete;
	GameObjectFactory& operator=(const GameObjectFactory*) = delete;
	GameObjectFactory& operator=(GameObjectFactory&&) noexcept = delete;
	~GameObjectFactory() = default;

	bool Init();

private:
	template<class ObjectType>
	GameObject* CreateObject(const char* pFilename);
};

//Creates a new object and returns it
//	Class is templated so GameObject::Init can call properly.
//	Takes in an XML file and builds the object's components
//	from it.
template<class ObjectType>
inline GameObject* GameObjectFactory::CreateObject(const char* pFilename)
{
	//Load the XML file
	XMLDocument* pDoc = static_cast<XMLDocument*>(m_pResourceManager->Load(pFilename));

	if (!pDoc)
		return nullptr;

	// Create the GameObject
	GameObject* pObject = BLEACH_NEW(ObjectType);
	pObject->Init();

	// Seek to Components
	XMLElement* pElement = pDoc->FirstChildElement()->FirstChildElement();

	// For each element, try to add it as a component
	//	Note: Requires component registration (see ComponentFactory)
	for (pElement = pElement->NextSiblingElement(); pElement; pElement = pElement->NextSiblingElement())
	{
		const std::string& componentName = pElement->Name();
		IComponent* pComponent = m_pComponentFactory->CreateComponent(pElement);
		if (pComponent)
		{
			pObject->AddComponent(componentName, pComponent);
			pComponent->SetOwner(pObject);
		}
	}

	return pObject;
}
