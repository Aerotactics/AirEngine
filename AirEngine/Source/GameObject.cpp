#include "GameObject.h"

#include "IComponent.h"
#include "Logger.h"
#include "TinyXML/tinyxml2.h"
#include "Bleach/BleachNew.h"

using XMLElement = tinyxml2::XMLElement;

GameObject::GameObject()
    : m_id(0)
    , m_toDelete(false)
{
}

GameObject::~GameObject()
{
    for (auto [_,pComp] : m_components)
    {
        BLEACH_DELETE(pComp);
    }
    m_components.clear();
}

void GameObject::AddComponent(const std::string& componentName, IComponent* pComponent)
{
    if (!pComponent)
    {
        //If this happens, it's probably serious
        ERR("Object attempted to add a null component");
        return;
    }

    if (m_components.find(componentName) != m_components.end())
    {
        ERR("Object attempted to add existing component");
        return;
    }
    
    m_components[componentName] = pComponent;
}

IComponent* GameObject::GetComponent(const char* pName)
{
    if(m_components.find(pName) != m_components.end())
        return m_components[pName];
    return nullptr;
}
