#pragma once
#include "Bleach/BleachNew.h"
#include "AirEngine.h"

#define MAIN(game) \
int main() \
{ \
	INIT_LEAK_DETECTOR(); \
	AirEngine::_Create(BLEACH_NEW(game)); \
	AirEngine* pEngine = AirEngine::_Get(); \
	if (pEngine->_Init()) \
	{ \
		pEngine->_Run(); \
	} \
	pEngine->_Shutdown(); \
	AirEngine::_Destroy(); \
	DESTROY_LEAK_DETECTOR();\
	return 0; \
}