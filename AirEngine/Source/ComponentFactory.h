#pragma once
#include "IComponent.h"
#include "TinyXML/tinyxml2.h"
#include "Bleach/BleachNew.h"

#include <type_traits>
#include <unordered_map>

// Makes components
//	Custom components must be registered with REGISTER_COMPONENT, found in 
//	Macros.h, in order for this class to know what subtype to output.
//	Registration must be done before creating the component.
class ComponentFactory
{
private:
	std::unordered_map<std::string, IComponent*(*)()> m_instanceFunctions;

public:
	ComponentFactory() = default;
	ComponentFactory(const ComponentFactory&) = delete;
	ComponentFactory(ComponentFactory&&) noexcept = delete;
	ComponentFactory& operator=(const ComponentFactory&) = delete;
	ComponentFactory& operator=(ComponentFactory&&) noexcept = delete;
	~ComponentFactory() = default;

	bool Init();

	// Takes in an Element* and outputs a new component from the Element's name.
	//	Returns nullptr if the component doesn't have an instantiation function,
	//	or if the new component fails initilization. Otherwise, returns the new 
	//	component.
	IComponent* CreateComponent(tinyxml2::XMLElement* pElement)
	{
		IComponent* pComponent = nullptr;
		const char* pName = pElement->Name();
		auto pFunctor = m_instanceFunctions.find(pName);
		if (pFunctor == m_instanceFunctions.end())
		{
			ERR("[ComponentFactory] Unable to find component registration: " << pName);
			return nullptr;
		}

		pComponent = pFunctor->second();

		if (!pComponent->Init(pElement))
		{
			BLEACH_DELETE(pComponent);
			ERR("[ComponentFactory] Component failed Init: " << pName);
			return nullptr;
		}
		return pComponent;
	}

	// Adds an _Instantiate<type> function to m_instanceFunctions map, allowing
	//	CreateComponent to Instantiate this subtype of component. Returns
	//	false if class doesn't inherit from IComponent, or true if a new 
	//	function is created.
	template<class ComponentType>
	void RegisterType(const std::string& typeName)
	{
		m_instanceFunctions[typeName] = &_Instantiate<ComponentType>;
	}

private:
	// Creates an instance of an IComponent subtype
	//	This has to be static because function pointers cannot be taken from
	//	members of a class instance.
	template<class ComponentType>
	static IComponent* _Instantiate() { return BLEACH_NEW(ComponentType); }
};
