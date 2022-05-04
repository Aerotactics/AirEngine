#pragma once
#include "IResource.h"
#include "IXML.h"

namespace tinyxml2
{
	class XMLDocument;
}

class TinyXML
{
private:
	tinyxml2::XMLDocument* m_pDocument;

public:
	TinyXML();
	~TinyXML();

	bool Load(std::byte* pData, size_t dataSize);

	void* Get() const { return (void*)m_pDocument; }
};