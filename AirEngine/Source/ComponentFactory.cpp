#include "ComponentFactory.h"

#include "Macros.h"
#include "DefaultComponents.h"

bool ComponentFactory::Init()
{
	//Register Default Components
		//	This is roundabout, but will work for now
	REGISTER_COMPONENT(AnimationComponent);
	REGISTER_COMPONENT(CollisionComponent);
	REGISTER_COMPONENT(ControllerComponent);
	REGISTER_COMPONENT(NameComponent);
	REGISTER_COMPONENT(SpriteComponent);
	REGISTER_COMPONENT(TransformComponent);
	return true;
}
