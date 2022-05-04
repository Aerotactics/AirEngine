#pragma once

#include "Bleach/BleachNew.h"
#include <vector>

class IProcess;

class ProcessManager
{
private:
	std::vector<IProcess*> m_processes;

public:
	~ProcessManager();

	IProcess* StartProcess(IProcess* pProcess);
	void StopProcess(IProcess* pProcess);

	void Update(double delta);
};