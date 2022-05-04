#pragma once
#include "IWindow.h"

#include "SFML/Graphics.hpp"

class SFMLWindow
{
private:
	sf::RenderWindow m_window;

public:
	bool Init(const char* pTitle, int width, int height);
	void Clear();
	void Display();
	void Shutdown();

	auto* Get() const { return &m_window; }
};