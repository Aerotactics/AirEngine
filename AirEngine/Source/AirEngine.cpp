#include "AirEngine.h"

#include "IGame.h"

#include <assert.h>

static constexpr int kWindowWidth = 1024;
static constexpr int kWindowHeight = 768;

AirEngine* AirEngine::s_pInstance = nullptr;

AirEngine::AirEngine(IGame* pGame)
	: m_isRunning(false)
	, m_pGame(pGame)
{
}

AirEngine* AirEngine::_Get()
{
	return s_pInstance;
}

bool AirEngine::_Init()
{
	unsigned int seed = (unsigned int)time(nullptr);
	srand(seed);

	if(!m_renderer.Init(m_pGame->GetGameName(), kWindowWidth, kWindowHeight))
		return false;

	if(!m_worldManager.Init())
		return false;

	if (!m_gameObjectManager.Init())
		return false;

	if (!m_pGame->Init())
		return false;

	return true;
}

void AirEngine::_Run()
{
	m_isRunning = true;
	double delta = 0;
	while (m_isRunning)
	{
		delta = m_system.GetElapsedTime();

		m_eventManager.ProcessEvents();
		m_gameObjectManager.Update(delta);
		m_worldManager.Update();
		m_processManager.Update(delta);
		m_pGame->Tick(delta);
		m_renderer.Render();
	}
}

void AirEngine::_Shutdown()
{
	if (m_isRunning)
	{
		ERR("Engine tried to shutdown while expected to be running");
		return;
	}

	if(m_pGame)
		m_pGame->Shutdown();
	BLEACH_DELETE(m_pGame);

	m_renderer.Shutdown();
}

void AirEngine::_Create(IGame* pGame)
{
	assert(s_pInstance == nullptr); // You tried to make a new instance of the Engine. :C
	static AirEngine* pEngine = BLEACH_NEW(AirEngine(pGame));
	s_pInstance = pEngine;
}

void AirEngine::_Destroy()
{
	BLEACH_DELETE(s_pInstance);
}
