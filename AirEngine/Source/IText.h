#pragma once

#include "Vector2.h"

#include "Window.h"

template <class Type>
class IText
{
	friend class Renderer;

private:
	Type m_type;

protected:
	void AddText(const char* pText, Vector2<float> position, const char* pFontFile, int pixelSize) { m_type.AddText(pText, position, pFontFile, pixelSize); }
	void Draw(Window* pWindow) { m_type.Draw(pWindow); }
};