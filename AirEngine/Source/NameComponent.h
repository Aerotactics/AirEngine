#pragma once
#include "IComponent.h"

namespace tinyxml2
{
	class XMLElement;
}

class NameComponent : public IComponent
{
private:
	const char* m_pName;

public:
	NameComponent();

	virtual bool Init(tinyxml2::XMLElement* pData) override final;

	void SetName(const char* name) { m_pName = name; }
	const char* GetName() const { return m_pName; }
};
