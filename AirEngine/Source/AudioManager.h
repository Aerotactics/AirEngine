#pragma once
#include <unordered_map>
#include <string>

#include "Bleach/BleachNew.h"

class Sound;
class Music;

class AudioManager
{
private:
	std::unordered_map<std::string, Sound*> m_sounds;
	std::unordered_map<std::string, Music*> m_music;

public:
	~AudioManager();

	void PlaySound(const char* pFilename);
	void PlayMusic(const char* pFilename, bool looping);

	Sound* LoadSound(const std::string& pFilename);
	Music* LoadMusic(const std::string& pFilename);
};