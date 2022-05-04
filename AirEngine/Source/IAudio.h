#pragma once

template<class Type>
class IAudio
{
private:
	Type m_audio;

public:
	void Play() { m_audio.Play(); }
	void Pause() { m_audio.Pause(); }
	void Stop() { m_audio.Stop(); }
};