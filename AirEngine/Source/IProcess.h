#pragma once

namespace ProcessState
{
	constexpr int kInit			= 1 << 0;
	constexpr int kRunning		= 1 << 1;
	constexpr int kSucceeded	= 1 << 2;
	constexpr int kFailed		= 1 << 3;
	constexpr int kAborted		= 1 << 4;

	constexpr int kDone			= kSucceeded | kFailed | kAborted;
}

class IProcess
{
	friend class ProcessManager;

private:
	int m_state;
	IProcess* m_pChildProcess; // This *could* be an array

public:
	IProcess(IProcess* pChildProcess)
		: m_state(ProcessState::kInit)
		, m_pChildProcess(pChildProcess)
	{}

	IProcess()
		: IProcess(nullptr)
	{}

	virtual ~IProcess() { }

	IProcess* SetChild(IProcess* pProcess) { m_pChildProcess = pProcess; return pProcess; }

	virtual void OnInit() {}
	virtual void OnUpdate([[maybe_unused]] double delta) { m_state = ProcessState::kSucceeded; }
	virtual void OnExit() {}

	virtual void OnSuccess() {}
	virtual void OnFail() {}
	virtual void OnAbort() {}

	bool IsInitialized() { return !(m_state & ProcessState::kInit); }
	bool IsRunning() { return m_state & ProcessState::kRunning; }
	bool HasSucceeded() { return m_state & ProcessState::kSucceeded; }
	bool HasFailed() { return m_state & ProcessState::kFailed; }
	bool HasAborted() { return m_state & ProcessState::kAborted; }
	bool IsDone() { return m_state & ProcessState::kDone; }

protected:
	void Succeed() { m_state = ProcessState::kSucceeded; }
	void Fail() { m_state = ProcessState::kFailed; }
	void Abort();
	void DestroyChild();

private:
	void _OnInit();
	void _OnExit();
};