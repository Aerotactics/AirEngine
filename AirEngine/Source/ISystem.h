#pragma once
#include "FileData.h"

#include <memory>

template<class Type>
class ISystem
{
private:
	Type m_system;

public:
	const char* GetSystemName() const { return m_system.GetSystemName(); }

	bool LoadRaw(FileData& fileData) { return m_system.LoadRaw(fileData); }

	bool LoadFileFromZip(const char* pZipFilename, FileData& fileData) { return m_system.LoadFileFromZip(pZipFilename, fileData); }

	double GetElapsedTime() { return m_system.GetElapsedTime(); }
};