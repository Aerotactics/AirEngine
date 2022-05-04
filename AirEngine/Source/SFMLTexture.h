#pragma once

#include "IResource.h"
#include "ITexture.h"
#include "SFML/Graphics.hpp"

class Window;

class SFMLTexture
{
private:
	sf::Texture m_texture;
	int frameWidth;
	int frameHeight;

public:
	bool Load(std::byte* pData, size_t dataSize);

	void* Get() const { return (void*)&m_texture; }

	void Draw(Window* pWindow);

	Vector2<unsigned int> GetSize();
};