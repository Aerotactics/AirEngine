#pragma once
#include "IResource.h"

template<class Type>
class ISoundBuffer : public IResource
{
private:
	Type m_bufferType;

public:
	virtual bool Load(std::byte* pData, size_t dataSize) override final
	{
		return m_bufferType.Load(pData, dataSize);
	}

	virtual void* Get() const override final { return m_bufferType.Get(); }
};
