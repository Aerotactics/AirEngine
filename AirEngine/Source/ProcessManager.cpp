#include "ProcessManager.h"

#include "IProcess.h"

ProcessManager::~ProcessManager()
{
	for (auto pProc : m_processes)
	{
		pProc->DestroyChild();
		BLEACH_DELETE(pProc);
	}
	m_processes.clear();
}

IProcess* ProcessManager::StartProcess(IProcess* pProcess)
{
	if(!pProcess)
		return nullptr;

	m_processes.push_back(pProcess);
	return pProcess;
}

// Note: Does nothing if the process is unlisted
void ProcessManager::StopProcess(IProcess* pProcess)
{
	if (auto it = std::find(m_processes.begin(), m_processes.end(), pProcess); it != m_processes.end())
	{
		IProcess* pProc = *it;
		pProc->Abort();
	}
}

void ProcessManager::Update(double delta)
{
	for (int i = int(m_processes.size()) - 1; i >= 0; --i)
	{
		IProcess* pProc = m_processes.at(i);

		if (!pProc->IsInitialized())
			pProc->_OnInit();

		if (pProc->IsRunning())
			pProc->OnUpdate(delta);

		if (pProc->HasSucceeded())
			pProc->OnSuccess();

		if (pProc->HasFailed())
			pProc->OnFail();

		if (pProc->HasAborted())
			pProc->OnAbort();

		if (pProc->IsDone())
		{
			pProc->_OnExit();
			BLEACH_DELETE(pProc);
			m_processes.erase(m_processes.begin() + i);
		}
	}
}

