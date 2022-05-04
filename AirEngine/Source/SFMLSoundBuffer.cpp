#include "SFMLSoundBuffer.h"

SFMLSoundBuffer* SFMLSoundBuffer::Load(std::byte* pData, size_t dataSize)
{
	if (!m_buffer.loadFromMemory(pData, dataSize))
		return nullptr;
	return this;
}
