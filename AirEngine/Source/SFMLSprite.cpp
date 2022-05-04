#include "SFMLSprite.h"

#include "Texture.h"
#include "Window.h"
#include "SFML/Graphics.hpp"

SFMLSprite* SFMLSprite::Create(SpriteData& spriteData)
{
    
    sf::Texture* pTexture = reinterpret_cast<sf::Texture*>(spriteData.pTexture->Get());
    
    if(!pTexture)
        return nullptr;
    
    m_pTexture = spriteData.pTexture;
    m_width = spriteData.width;
    m_height = spriteData.height;
    m_sprite.setTexture(*pTexture);
    m_sprite.setOrigin(spriteData.origin.x, spriteData.origin.y);
    
    SetUV(0,0);

    return this;
}

void SFMLSprite::SetTexture(Texture* pTexture)
{
    m_pTexture = pTexture;
    sf::Texture* pSFTexture = reinterpret_cast<sf::Texture*>(pTexture->Get());
    m_sprite.setTexture(*pSFTexture);
}

void SFMLSprite::SetPosition(Vector2<float>& position)
{
    m_sprite.setPosition(position.x, position.y);
}

void SFMLSprite::SetScale(Vector2<float>& scale)
{
    m_sprite.setScale(scale.x, scale.y);
}

void SFMLSprite::SetRotation(float& rotation)
{
    m_sprite.setRotation(rotation);
}

void SFMLSprite::SetUV(unsigned int u, unsigned int v)
{
    sf::Vector2f scale = m_sprite.getScale();
    m_sprite.setTextureRect( sf::IntRect(
        u, v, 
        m_width * (int)scale.x, 
        m_height * (int)scale.y ));
}

Vector2<float> SFMLSprite::GetSize()
{
    sf::Vector2f scale = m_sprite.getScale();
    return Vector2<float>(m_width * scale.x, m_height * scale.y);
}

void SFMLSprite::Draw(Window* pWindow)
{
    sf::RenderWindow* pRenderWindow = reinterpret_cast<sf::RenderWindow*>(pWindow->Get());
    pRenderWindow->draw(m_sprite);
}
