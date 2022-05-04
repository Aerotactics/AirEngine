#pragma once
#include "ISprite.h"
#include "Vector2.h"

#include "SFML/Graphics.hpp"

class Window;
class Texture;

class SFMLSprite
{
private:
	sf::Sprite m_sprite;
	Texture* m_pTexture;
	
	int m_width;
	int m_height;

public:
	SFMLSprite* Create(SpriteData& spriteData);

	Texture* GetTexture() { return m_pTexture; }
	void SetTexture(Texture* pTexture);

	void SetPosition(Vector2<float>& position);
	void SetScale(Vector2<float>& scale);
	void SetRotation(float& rotation);

	void SetUV(unsigned int u, unsigned int v);

	Vector2<float> GetSize();
	void Draw(Window* pWindow);
};
