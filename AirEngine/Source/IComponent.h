#pragma once
#include <string>
#include "Logger.h"

class GameObject;
class GameObjectFactory;

namespace tinyxml2 { class XMLElement; }

class IComponent
{
	friend GameObjectFactory;

protected:
	GameObject* m_pOwner;

public:
	IComponent()
		: m_pOwner(nullptr)
	{
	}
	virtual ~IComponent();

	virtual bool Init(tinyxml2::XMLElement* pData) = 0;
	virtual void Shutdown() {};

private:
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
};