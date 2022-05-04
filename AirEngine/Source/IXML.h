#pragma once
#include "IResource.h"

template<class Type>
class IXML : public IResource
{
private:
	Type m_instance;

public:
	virtual bool Load(std::byte* pData, size_t dataSize) override final
	{
		return m_instance.Load(pData, dataSize);
	}

	virtual void* Get() const override final { return m_instance.Get(); }
};