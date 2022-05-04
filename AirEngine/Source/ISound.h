#pragma once
#include <string>

template<class SoundType>
class ISound
{
private:
	SoundType m_sound;

public:
	SoundType* Load(const std::string& pFilename) { return m_sound.Load(pFilename); }

	void Play() { m_sound.Play(); }
	void Pause() { m_sound.Pause(); }
	void Stop() { m_sound.Stop(); }

	void SetLooping(bool shouldLoop) { m_sound.SetLooping(shouldLoop); }
};