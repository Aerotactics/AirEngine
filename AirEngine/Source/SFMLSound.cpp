#include "SFMLSound.h"

#include "AirEngine.h"
#include "Logger.h"

SFMLSound* SFMLSound::Load(const char* pFilename)
{
	sf::SoundBuffer* pBuffer = AirEngine::GetResourceManager()->Load<sf::SoundBuffer>(pFilename);
	
	if(!pBuffer)
		return nullptr;
	
	m_sound.setBuffer(*pBuffer);
	return this;
}