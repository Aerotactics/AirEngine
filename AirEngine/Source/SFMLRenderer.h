#pragma once
#include "IRenderer.h"

#include <vector>
#include <thread>

#include "SFML/Graphics.hpp"

class SFMLRenderer
{
private:
	sf::RenderWindow m_window;
	std::thread m_renderThread;

public:
	bool Init(const char* pTitle, int width, int height);
	void Render();
	void Shutdown();
};