#include "SFMLWindow.h"

#include "AirEngine.h"

bool SFMLWindow::Init(const char* pTitle, int width, int height)
{
	m_window.create(sf::VideoMode(width, height), pTitle);

	if(!m_window.isOpen())
		return false;

	return true;
}

void SFMLWindow::Clear()
{
	m_window.setActive();

	m_window.clear();
}

void SFMLWindow::Display()
{
	m_window.display();

	//Temporary Close event
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			AirEngine::QuitGame();
	}
}

void SFMLWindow::Shutdown()
{
	m_window.close();
}
