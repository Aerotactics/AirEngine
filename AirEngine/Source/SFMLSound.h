#pragma once

#include "ISound.h"
#include "SFML/Audio.hpp"

class SFMLSound
{
private:
	sf::Sound m_sound;

public:
	SFMLSound* Load(const char* pFilename);

	void Play() { m_sound.play(); }
	void Pause() { m_sound.pause(); }
	void Stop() { m_sound.stop(); }

	void SetLooping(bool shouldLoop) { m_sound.setLoop(shouldLoop); }
};
