#pragma once
#include <string>
#include <memory>
#include <unordered_map>

static constexpr const char* kAssetZip = "../Game/Assets/Assets.zip";

class Resource;
class System;

class ResourceFactory
{
private:
	System* m_pSystem;
	
public:
	bool Init();
	
	Resource* CreateResource(const std::string& pFilename);
};
