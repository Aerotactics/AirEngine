#include "ITickable.h"

#include "AirEngine.h"
#include "ComponentManager.h"

ITickable::ITickable()
{
	AirEngine::GetGameObjectManager()->GetComponentManager()->AddTickable(this);
}

ITickable::~ITickable()
{
	AirEngine::GetGameObjectManager()->GetComponentManager()->RemoveTickable(this);
}
