#pragma once
#include "AirEngine.h"
#include "ComponentManager.h"
#include "ComponentFactory.h"
#include "ResourceFactory.h"
#include "Bleach/BleachNew.h"

#define REGISTER_COMPONENT(type) AirEngine::GetGameObjectManager()->GetComponentManager()->GetComponentFactory()->RegisterType<type>(#type);

#define REGISTER_RESOURCE(fileExt, type) AirEngine::GetResourceManager()->GetResourceFactory()->AddFileAssociation<type>(fileExt);

#define STRINGIZE(thing) #thing