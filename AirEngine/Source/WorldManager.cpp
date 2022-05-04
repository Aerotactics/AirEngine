#include "WorldManager.h"

#include "AirEngine.h"
#include "Window.h"
#include "XML.h"

using namespace tinyxml2;

bool WorldManager::Init()
{
	// World Init used to be here.
	m_currentWorld = 0;
	return true;
}

void WorldManager::Update()
{
	// A world is required to be added in the game's init!
	//	AirEngine::GetWorldManager().AddWorld("WorldFile.xml");
	assert(!m_worlds.empty());
	m_worlds[m_currentWorld].Update();
}

void WorldManager::Draw(Window* pWindow)
{
	m_worlds[m_currentWorld].Draw(pWindow);
}

bool WorldManager::AddWorld(const char* pFilename)
{
	World world;
	XMLDocument* pWorldDoc = AirEngine::GetResourceManager()->Load<XMLDocument>(pFilename);
	XMLElement* pElement = pWorldDoc->FirstChildElement();

	if(!world.Init(pElement))
		return false;

	m_worlds.emplace_back(std::move(world));
	return true;
}
