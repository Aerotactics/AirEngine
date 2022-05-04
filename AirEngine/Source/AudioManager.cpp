#include "AudioManager.h"

#include "AirEngine.h"
#include "Sound.h"
#include "Music.h"
#include "Logger.h"

AudioManager::~AudioManager()
{
	for (auto& [_, pSound] : m_sounds)
	{
		BLEACH_DELETE(pSound);
	}
	m_sounds.clear();

	for (auto& [_, pMusic] : m_music)
	{
		BLEACH_DELETE(pMusic);
	}
	m_music.clear();
}

void AudioManager::PlaySound(const char* pFilename)
{
	Sound* pSound = LoadSound(pFilename);
	if (!pSound)
	{
		ERR("[AudioManager] Failed to play sound: " << pFilename);
		return;
	}
	pSound->Play();
}

void AudioManager::PlayMusic(const char* pFilename, bool looping)
{
	Music* pMusic = LoadMusic(pFilename);
	if (!pMusic)
	{
		ERR("[AudioManager] Failed to play music: " << pFilename);
		return;
	}
	pMusic->Play();
	pMusic->SetLooping(looping);
}

Sound* AudioManager::LoadSound(const std::string& pFilename)
{
	if(auto it = m_sounds.find(pFilename); it != m_sounds.end())
		return it->second;

	Sound* pSound = BLEACH_NEW(Sound);
	if (!pSound->Load(pFilename))
	{
		ERR("[AudioManager] Failed to load file as Sound: " << pFilename);
		BLEACH_DELETE(pSound);
		return nullptr;
	}
	m_sounds[pFilename] = pSound;
	return pSound;
}

Music* AudioManager::LoadMusic(const std::string& pFilename)
{
	if (auto it = m_music.find(pFilename); it != m_music.end())
		return it->second;

	Music* pMusic = BLEACH_NEW(Music);
	if (!pMusic->Load(pFilename))
	{
		ERR("[AudioManager] Failed to load file as Music: " << pFilename);
		BLEACH_DELETE(pMusic);
		return nullptr;
	}
	m_music[pFilename] = pMusic;
	return pMusic;
}