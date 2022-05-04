#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

class IProcess;

using TimerID = uint64_t;

// A simple timer system
class Timer
{
private:
	static Timer s_timer;
	std::unordered_map<TimerID, IProcess*> m_timers;
	std::vector<TimerID> m_freeIDs;
	TimerID m_maxID;

public:
	static TimerID Set(double timeInSeconds, std::function<void()> function, bool loop = false) { return s_timer._Set(timeInSeconds, function, loop); }
	static void Stop(TimerID id) {s_timer._Stop(id); }

private:
	TimerID _Set(double timeInSeconds, std::function<void()> function, bool loop);
	void _Stop(TimerID id);
	void _Clear(TimerID id);
	void _AddLoopProcess(IProcess* pProcess, double timeInSeconds, std::function<void()> function, TimerID id);
};