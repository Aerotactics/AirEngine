#include "SFMLMusic.h"

#include "AirEngine.h"
#include "RawBytes.h"

SFMLMusic* SFMLMusic::Load(const char* pFilename)
{
	ByteData* pData = AirEngine::GetResourceManager()->Load<ByteData>(pFilename);
	if(!pData)
		return nullptr;
	m_music.openFromMemory(pData->m_pBytes, pData->m_dataSize);
	return this;
}