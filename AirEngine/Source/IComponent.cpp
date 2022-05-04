#include "IComponent.h"

#include "AirEngine.h"
#include "ComponentManager.h"

IComponent::~IComponent()
{
	AirEngine::GetGameObjectManager()->GetComponentManager()->DeleteComponent(this);
}
