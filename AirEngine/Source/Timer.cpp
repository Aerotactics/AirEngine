#include "Timer.h"

#include "AirEngine.h"
#include "DelayProcess.h"
#include "CallbackProcess.h"


TimerID Timer::_Set(double timeInSeconds, std::function<void()> function, bool loop)
{
	//Get next ID
	TimerID id;
	if (!m_freeIDs.empty())
	{
		id = m_freeIDs.back();
		m_freeIDs.pop_back();
	}
	else
	{
		id = m_maxID;
		++m_maxID;
	}
	
	//Build the process
	//	Consists of a delay and a callback. The callback will
	//	recursively add a new timer when the callback triggers,
	//	unless is is not set to loop, then the original function
	//	becomes the callback. Returns an ObjectID which can be 
	//	passed to Timer::Stop to stop the timer. 
	IProcess* pProcess = nullptr;
	if (loop)
	{
		_AddLoopProcess(pProcess, timeInSeconds, function, id);
	}
	else
	{
		pProcess = BLEACH_NEW(DelayProcess(timeInSeconds));
		pProcess->SetChild(BLEACH_NEW(CallbackProcess([this, function, id]
		{
			function();
			_Clear(id);
		})));
		m_timers[id] = pProcess;
	}

	AirEngine::GetProcessManager()->StartProcess(pProcess);
	return id;
}

//Stops the process that is associated with a given ID,
//	then adds the ID to timer pool
void Timer::_Stop(TimerID id)
{
	if (id >= m_maxID)
	{
		ERR("[Timer] Attemped to Stop invalid TimerID: " << id);
		return;
	}
	if (auto it = m_timers.find(id); it == m_timers.end())
	{
		ERR("[TIMER] Attmpted to stop Free'd TimerID: " << id);
		return;
	}

	AirEngine::GetProcessManager()->StopProcess(m_timers[id]);
	_Clear(id);
}

// Erases a timer entry and adds the TimerID to pool
void Timer::_Clear(TimerID id)
{
	m_freeIDs.push_back(id);
	m_timers.erase(id);
}

// This function recursively adds a delay and callback to an 
//	existing process. The callback calls this function to 
//	contiue looping the two processes.
void Timer::_AddLoopProcess(IProcess* pProcess, double timeInSeconds, std::function<void()> function, TimerID id)
{
	//This had to be split up to make sure all the parts work
	//	together. First, we attach a delay process to the existing
	//	pProcess, or start a new process. We save that pointer.
	IProcess* pDelayProcess = nullptr;
	if (pProcess == nullptr)
	{
		pProcess = BLEACH_NEW(DelayProcess(timeInSeconds));
		pDelayProcess = pProcess;
	}
	else
	{
		pDelayProcess = pProcess->SetChild(BLEACH_NEW(DelayProcess(timeInSeconds)));
	}

	//Then, we attach a callback process onto that delay process.
	//	This process pointer is also saved so that we can call
	//	this function with that address as a parameter.
	//	 NOTE: We also pass the ID in as well to maintain it.
	IProcess* pCallbackProcess = pDelayProcess->SetChild(BLEACH_NEW(CallbackProcess([this, pCallbackProcess, timeInSeconds, function, id]
	{
		function();
		_AddLoopProcess(pCallbackProcess, timeInSeconds, function, id);
	})));

	//Finally, the timer pointer is updated with the new delay 
	//	process, so that if Timer::Stop is called, we can stop
	//	the currently running DelayProcess.
	m_timers[id] = pDelayProcess;
}
