#pragma once

template<class Type>
class IRenderer
{
private:
	Type m_renderer;

public:
	bool Init(const char* pTitle, int width, int height)
	{
		return m_renderer.Init(pTitle, width, height);
	}

	void Render()
	{
		m_renderer.Render();
	}

	void Shutdown()
	{
		m_renderer.Shutdown();
	}
};
