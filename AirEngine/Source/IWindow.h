#pragma once

template<class Type>
class IWindow
{
private:
	Type m_window;

public:
	bool Init(const char* pTitle, int width, int height) { return m_window.Init(pTitle, width, height); }

	void Clear() { m_window.Clear(); }
	void Display() { m_window.Display(); }
	void Shutdown() { m_window.Shutdown(); }

	auto* Get() { return m_window.Get(); }
};