#include "TinyXML.h"

#include "Logger.h"
#include "TinyXML/tinyxml2.h"
#include "Bleach/BleachNew.h"

using namespace tinyxml2;

TinyXML::TinyXML()
	: m_pDocument(BLEACH_NEW(XMLDocument))
{
}

TinyXML::~TinyXML()
{
	BLEACH_DELETE(m_pDocument);
}

bool TinyXML::Load(std::byte* pData, size_t dataSize)
{
	XMLError error = m_pDocument->Parse(reinterpret_cast<const char*>(pData), dataSize);
	if (error)
	{
		ERR("[XML] Failed to parse file.");
		return false;
	}
	return true;
}