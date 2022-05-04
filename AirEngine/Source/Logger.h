#pragma once
#include <iostream>
#include <string>

#ifdef _DEBUG
#define LOG(stream) \
	std::cout << "[LOG] " << stream << "\n"
#else
#define LOG(stream) {}
#endif

#ifdef _DEBUG
#define ERR(stream) \
	std::cout << "[ERROR] " << stream << "\n"
#else
#define ERR(stream) {}
#endif

#define PRINT(stream) \
	std::cout << "[Console] " << stream << "\n"