#pragma once

#include <vector>

#include "World.h"

class Window;

class WorldManager
{
private:
	std::vector<World> m_worlds;
	size_t m_currentWorld;

public:
	WorldManager() = default;
	WorldManager(const WorldManager&) = delete;
	WorldManager(WorldManager&&) noexcept = delete;
	WorldManager& operator==(const WorldManager&) = delete;
	WorldManager& operator==(WorldManager&&) = delete;
	~WorldManager() = default;

	bool Init();
	void Update();
	void Draw(Window* pWindow);

	bool AddWorld(const char* pFilename);
};