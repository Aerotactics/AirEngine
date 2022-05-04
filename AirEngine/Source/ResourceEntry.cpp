#include "ResourceEntry.h"

ResourceEntry::ResourceEntry(Resource& resource)
	: m_resource(std::move(resource))
	, m_referenceCount(1)
{}

