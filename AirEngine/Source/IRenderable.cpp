#include "IRenderable.h"

#include "AirEngine.h"

IRenderable::IRenderable()
{
	AirEngine::GetRenderer()->AddRenderable(this);
}

IRenderable::~IRenderable()
{
	AirEngine::GetRenderer()->RemoveRenderable(this);
}
