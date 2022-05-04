#pragma once

#include "IResource.h"
#include "Vector2.h"

class Texture;
class Window;

struct SpriteData
{
	Texture* pTexture;
	Vector2<float> origin;
	int width;
	int height;
};

template<class Type>
class ISprite
{
private:
	Type m_sprite;

public:
	Type* Load(SpriteData& data)
	{
		if(!m_sprite.Create(data))
			return nullptr;
		return &m_sprite;
	}

	Texture* GetTexture() { return m_sprite.GetTexture(); }
	void SetTexture(Texture* pTexture) { m_sprite.SetTexture(pTexture); }

	void SetUV(unsigned int u, unsigned int v) { m_sprite.SetUV(u, v); }

	void SetPosition(Vector2<float> position) { m_sprite.SetPosition(position); }
	void SetScale(Vector2<float> scale) { m_sprite.SetScale(scale); }
	void SetRotation(float rotation) { m_sprite.SetRotation(rotation); }

	Vector2<float> GetSize() { return m_sprite.GetSize(); }

	void Draw(Window* pWindow) { m_sprite.Draw(pWindow); }
};