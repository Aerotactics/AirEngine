#include "StaticObject.h"

#include "TransformComponent.h"
// This could probably be under a different class that
//  handles Transform, perhaps "Transformable"
//  Player would use is as well.
void StaticObject::SetPosition(Vector2<float> position)
{
    static_cast<TransformComponent*>(GetComponent("TransformComponent"))->SetPosition(position);
}