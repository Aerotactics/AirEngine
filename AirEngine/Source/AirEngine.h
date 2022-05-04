#pragma once
#include "Bleach/BleachNew.h"
#include <assert.h>

#include "System.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "AudioManager.h"
#include "ProcessManager.h"
#include "EventManager.h"
#include "ScriptingManager.h"
#include "WorldManager.h"

class IGame;

class AirEngine
{
private:
	static AirEngine* s_pInstance;
	bool m_isRunning;

	Renderer m_renderer;
	System m_system;

	ResourceManager m_resourceManager;
	GameObjectManager m_gameObjectManager;
	AudioManager m_audioManager;
	ProcessManager m_processManager;
	EventManager m_eventManager;
	ScriptingManager m_scriptingManager;
	WorldManager m_worldManager;

	IGame* m_pGame;

public:
	AirEngine(IGame* pGame);
	AirEngine(const AirEngine&) = delete;
	AirEngine(AirEngine&&) noexcept = delete;
	void operator=(const AirEngine&) = delete;
	void operator=(AirEngine&&) noexcept = delete;
	~AirEngine() = default;

	static Renderer* GetRenderer() { return AirEngine::_Get()->_GetRenderer(); }
	static System* GetSystem() { return AirEngine::_Get()->_GetSystem(); }
	static ResourceManager* GetResourceManager() { return AirEngine::_Get()->_GetResourceManager(); }
	static GameObjectManager* GetGameObjectManager() { return AirEngine::_Get()->_GetGameObjectManager(); }
	static AudioManager* GetAudioManager() { return AirEngine::_Get()->_GetAudioManager(); }
	static ProcessManager* GetProcessManager() { return AirEngine::_Get()->_GetProcessManager(); }
	static EventManager* GetEventManager() { return AirEngine::_Get()->_GetEventManager(); }
	static ScriptingManager* GetScriptingManager() { return AirEngine::_Get()->_GetScriptingManager(); }
	static WorldManager* GetWorldManager() { return AirEngine::_Get()->_GetWorldManager(); }

	static void QuitGame() { AirEngine::_Get()->_QuitGame(); }

	/* Called from Main */
	bool _Init();
	void _Run();
	void _Shutdown();
	static void _Create(IGame* pGame);
	static void _Destroy();

	/* Returns the static instance of the engine. */
	static AirEngine* _Get();

private:
	Renderer* _GetRenderer() { return &m_renderer; }
	System* _GetSystem() { return &m_system; }
	ResourceManager* _GetResourceManager() { return &m_resourceManager; }
	GameObjectManager* _GetGameObjectManager() { return &m_gameObjectManager; }
	AudioManager* _GetAudioManager() { return &m_audioManager; }
	ProcessManager* _GetProcessManager() { return &m_processManager; }
	EventManager* _GetEventManager() { return &m_eventManager; }
	ScriptingManager* _GetScriptingManager() { return &m_scriptingManager; }
	WorldManager* _GetWorldManager() { return &m_worldManager; }

	/* Flags the engine for shutdown. */
	void _QuitGame() { m_isRunning = false; }
};

