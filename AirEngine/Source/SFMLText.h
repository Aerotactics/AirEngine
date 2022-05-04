#pragma once
#include "IText.h"

#include "SFML/Window.hpp"

class SFMLText
{
private:
	sf::Font m_font;
	std::vector<sf::Text> m_texts;

public:
	void AddText(const char* pText, Vector2<float> position, const char* pFontFile, int pixelSize);
	void Draw(Window* pWindow);

private:
	bool LoadFont(const char* pFilename);
};