#pragma once
#include "SFML/Audio.hpp"

#include "ISoundBuffer.h"

class SFMLSoundBuffer
{
private:
	sf::SoundBuffer m_buffer;

public:
	SFMLSoundBuffer* Load(std::byte* pData, size_t dataSize);

	void* Get() const { return (void*)&m_buffer; }
};