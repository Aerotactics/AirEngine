#include "SFMLTexture.h"

#include "Window.h"

bool SFMLTexture::Load(std::byte* pData, size_t dataSize)
{
    if (!m_texture.loadFromMemory(pData, dataSize))
        return false;
    return true;
}

void SFMLTexture::Draw(Window* pWindow)
{
    sf::RenderWindow* pRenderWindow = static_cast<sf::RenderWindow*>(pWindow->Get());
    sf::Sprite sprite(m_texture);
    pRenderWindow->draw(sprite);
}

Vector2<unsigned int> SFMLTexture::GetSize()
{
    sf::Vector2u size = m_texture.getSize();
    Vector2<unsigned int> convertedSize(size.x, size.y);
    return convertedSize;
}

