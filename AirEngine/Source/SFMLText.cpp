#include "SFMLText.h"

#include "AirEngine.h"
#include "RawBytes.h"
#include "Window.h"
#include "Logger.h"

void SFMLText::AddText(const char* pText, Vector2<float> position, const char* pFontFile, int pixelSize)
{
	if (!LoadFont(pFontFile))
	{
		ERR("Failed to load font: " << pFontFile);
		return;
	}

	sf::Text text;
	text.setString(pText);
	text.setFont(m_font);
	text.setPosition(position.x, position.y);
	text.setCharacterSize(pixelSize);

	m_texts.push_back(text);
}

void SFMLText::Draw(Window* pWindow)
{
	for (auto& text : m_texts)
	{
		sf::RenderWindow* pRenderWindow = static_cast<sf::RenderWindow*>(pWindow->Get());
		pRenderWindow->draw(text);
	}
	m_texts.clear();
}

bool SFMLText::LoadFont(const char* pFilename)
{
	ByteData* pBytes = AirEngine::GetResourceManager()->Load<ByteData>(pFilename);
	return m_font.loadFromMemory(pBytes->m_pBytes, pBytes->m_dataSize);
}
