#pragma once
#include <string>

template<class MusicType>
class IMusic
{
private:
	MusicType m_music;

public:
	MusicType* Load(const std::string& pFilename) { return m_music.Load(pFilename); }

	void Play() { m_music.Play(); }
	void Pause() { m_music.Pause(); }
	void Stop() { m_music.Stop(); }

	void SetLooping(bool shouldLoop) { m_music.SetLooping(shouldLoop); }
};