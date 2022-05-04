#pragma once
#include <vector>
#include <memory>
#include "Vector2.h"

class Window;

template<class Type>
class ITexture 
{
private:
	Type m_texture;

public:
	virtual bool Load(std::byte* pData, size_t dataSize) override final
	{
		return m_texture.Load(pData, dataSize);
	}

	void Draw(Window* pWindow) { m_texture.Draw(pWindow); }

	Vector2<unsigned int> GetSize() { return m_texture.GetSize(); }

	virtual void* Get() const override final { return m_texture.Get(); }
};
