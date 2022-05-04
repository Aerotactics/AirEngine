#include "Renderer.h"

#include "AirEngine.h"
#include "Window.h"

void Renderer::Render()
{
	m_window.Clear();

	// Draw the world
	AirEngine::GetWorldManager()->Draw(&m_window);

	// Draw the objects
	for (auto pRenderable : m_renderComponents)
	{
		pRenderable->Draw(&m_window);
	}

	m_text.Draw(&m_window);

	m_window.Display();
}