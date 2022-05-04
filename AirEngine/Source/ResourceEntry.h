#pragma once
#include "Resource.h"

class ResourceEntry
{
private:
	Resource m_resource;
	int m_referenceCount;

public:
	ResourceEntry(Resource& resource);
	ResourceEntry(ResourceEntry&& other) noexcept = delete;
	ResourceEntry& operator=(ResourceEntry&& other) noexcept = delete;
	ResourceEntry(const ResourceEntry&) = delete;
	ResourceEntry& operator=(const ResourceEntry&) = delete;
	~ResourceEntry() = default;

	Resource* Get() { return &m_resource; }
	void IncrementReferenceCount() { ++m_referenceCount; }
	int DecrementReferenceCount() { return --m_referenceCount; }
};
