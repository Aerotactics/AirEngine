#pragma once
#include <memory>

class Resource
{
private:
	std::byte* m_pBytes;
	size_t m_size;

public:
	Resource(std::byte* pBytes, size_t size)
		: m_pBytes(pBytes)
		, m_size(size)
	{}

	std::byte* GetBytes() { return m_pBytes; }
	size_t GetSize() { return m_size; }
};

