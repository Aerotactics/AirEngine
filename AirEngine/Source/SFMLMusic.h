#pragma once

#include "IMusic.h"
#include "SFML/Audio.hpp"

class SFMLMusic
{
private:
	sf::Music m_music;

public:
	SFMLMusic* Load(const char* pFilename);

	void Play() { m_music.play(); }
	void Pause() { m_music.pause(); }
	void Stop() { m_music.stop(); }

	void SetLooping(bool shouldLoop) { m_music.setLoop(shouldLoop); }
};