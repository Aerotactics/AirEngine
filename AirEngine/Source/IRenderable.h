#pragma once
#include "SFMLWindow.h"

class Window;

class IRenderable
{
public:
	IRenderable();
	virtual ~IRenderable();

	virtual void Draw(Window* pWindow) = 0;
};
