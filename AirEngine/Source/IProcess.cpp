#include "IProcess.h"

#include "AirEngine.h"

void IProcess::Abort()
{
	m_state = ProcessState::kAborted;
	DestroyChild();
}

void IProcess::DestroyChild()
{
	if(!m_pChildProcess)
		return;

	if (m_pChildProcess->IsDone())
		return;

	m_pChildProcess->DestroyChild();
	BLEACH_DELETE(m_pChildProcess);
	m_pChildProcess = nullptr;
}

void IProcess::_OnInit()
{
	m_state = ProcessState::kRunning;
	OnInit();
}

void IProcess::_OnExit()
{
	OnExit();
	if (m_pChildProcess)
		AirEngine::GetProcessManager()->StartProcess(m_pChildProcess);
}