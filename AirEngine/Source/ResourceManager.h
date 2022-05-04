#pragma once
#include "ResourceFactory.h"

#include <unordered_map>
#include <string>

class ResourceEntry;

class ResourceManager
{
private:
	std::unordered_map<std::string, ResourceEntry> m_resources;
	ResourceFactory m_resourceFactory;
	std::unordered_map<std::string, unsigned int> m_fileToIndex;

public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) noexcept = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) noexcept = delete;
	~ResourceManager();

	bool Init();

	Resource* Load(const std::string& pFilename);
	
	void Release(const std::string& pFilename);

	ResourceFactory* GetResourceFactory() { return &m_resourceFactory; }

private:
};
