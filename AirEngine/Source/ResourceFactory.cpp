#include "ResourceFactory.h"

#include "AirEngine.h"
#include "Macros.h"
#include "System.h"
#include "Logger.h"

#include "Resource.h"
#include "RawBytes.h"
#include "XML.h"
#include "SoundBuffer.h"

#include <filesystem>

using namespace tinyxml2;

bool ResourceFactory::Init()
{
	m_pSystem = AirEngine::GetSystem();
	return (m_pSystem);
}

// Creates a new resource from file.
Resource* ResourceFactory::CreateResource(const std::string& pFilename)
{
	FileData fileData(pFilename);
	Resource* pResource = nullptr;

	// Load the file into filedata
	//	First attempts to load from a specific Asset zip,
	//	Then attempts to load from a raw file on failure,
	//	but if all else fails, return nullptr
	if (!m_pSystem->LoadFileFromZip(kAssetZip, fileData))
	{
		if (!m_pSystem->LoadRaw(fileData))
		{
			return nullptr;
		}
	}

	// We loaded it, but the file is empty
	if (fileData.pData == nullptr)
	{
		ERR("[ResourceFactory] Loaded empty file: " << fileData.filepath);
		return nullptr;
	}

	// Make a new Resource (std::byte == char)
	pResource = new Resource((std::byte*)fileData.pData, fileData.size);

	return pResource;
}
