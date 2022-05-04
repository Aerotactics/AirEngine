#include "SFMLRenderer.h"

#include "AirEngine.h"

#include "ResourceManager.h"
#include <assert.h>

bool SFMLRenderer::Init(const char* pTitle, int width, int height)
{
	m_window.create(sf::VideoMode(width, height), pTitle);

	if(!m_window.isOpen())
		return false;

	return true;
}

void SFMLRenderer::Render()
{
	m_window.clear();

	//Demonstration Only
	Texture* pTexture = (Texture*)AirEngine::Get()->GetResourceManager()->Load("SharedAssets/Player.png");

	assert(pTexture != nullptr);
	sf::Sprite sprite;
	sprite.setTexture(*pTexture->Get());
	sprite.setOrigin(16, 16);
	sprite.setPosition(512, 384);
	m_window.draw(sprite);

	AirEngine::Get()->GetResourceManager()->Release("SharedAssets/Player.png");

	//Temporary Close event
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			AirEngine::Get()->QuitGame();
	}

	m_window.display();

	//std::this_thread::sleep_for();
}

void SFMLRenderer::Shutdown()
{
	m_window.close();
}
