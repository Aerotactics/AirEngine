#include "ResourceManager.h"

#include "AirEngine.h"
#include "ResourceEntry.h"
#include "Logger.h"

ResourceManager::~ResourceManager()
{
	m_resources.clear();
}

bool ResourceManager::Init()
{
	return m_resourceFactory.Init();
}

// Attempts to load a resource into memory by filename.
//	If it already exists, the raw implementation of the 
//	resource will be returned. If it doesn't exist, a new
//	instance of the resource will be loaded in memory.
Resource* ResourceManager::Load(const std::string& pFilename)
{
	// Find the resource
	// It is an iterator, which can be thought of like a pointer
	if (auto it = m_resources.find(pFilename); it != m_resources.end())
	{
		it->second.IncrementReferenceCount();
		return it->second.Get();
	}

	// Make the resource
	Resource* pResource = m_resourceFactory.CreateResource(pFilename);

	if (!pResource)
		return nullptr;

	// If valid, store it and return it
	auto [it, success] = m_resources.emplace(pFilename, pResource);
	return it->second.Get();
}

void ResourceManager::Release(const std::string& pFilename)
{
	// Try and find the resource
	auto it = m_resources.find(pFilename);
	if (it == m_resources.end())
	{
		LOG("[ResourceManager] Tried to release an uncached resource: " << pFilename << " (Make sure the path is correct)");
		return;
	}

	int references = it->second.DecrementReferenceCount();
	if (references <= 0)
	{
		LOG("[ResourceManager] Released a cached Resource: " << pFilename);
		m_resources.erase(it->first);
	}
}
