#pragma once

#include "IWindow.h"
#include "SFMLWindow.h"
#include "SFMLText.h"
#include "IRenderable.h"
#include "Logger.h"

using Text = IText<SFMLText>;

class Window;

class Renderer
{
private:
	Window m_window;
	Text m_text;
	std::vector<IRenderable*> m_renderComponents;

public:
	bool Init(const char* pTitle, int width, int height)
	{
		return m_window.Init(pTitle, width, height);
	}

	void Render();

	void Shutdown()
	{
		m_window.Shutdown();
	}

	void AddRenderable(IRenderable* pComponent)
	{
		if(std::find(m_renderComponents.begin(), m_renderComponents.end(), pComponent) != m_renderComponents.end())
		{
			LOG("Renderer attempted to add duplicate component.");
			return;
		}
		m_renderComponents.push_back(pComponent);
	}

	void RemoveRenderable(IRenderable* pComponent)
	{
		if (auto it = std::find(m_renderComponents.begin(), m_renderComponents.end(), pComponent); it != m_renderComponents.end())
		{
			m_renderComponents.erase(it);
		}
		else
		{
			LOG("Renderer attempted to remove invalid component.");
		}
	}

	void DrawText(const char* pText, Vector2<float> position, const char* pFontFile, int pixelSize) { m_text.AddText(pText, position, pFontFile, pixelSize); }
};
