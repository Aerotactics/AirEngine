#pragma once
#include <string>
#include <vector>

// An intermediate container used to store file information
struct FileData
{
	const std::string filepath;
	char* pData;
	size_t size;

	FileData() = default;
	FileData(const std::string& filepath)
		: filepath(filepath)
		, pData(nullptr)
		, size(0)
	{}
};
