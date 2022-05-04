#pragma once
#include "IProcess.h"

class DelayProcess : public IProcess
{
private:
	double m_time;

public:
	DelayProcess(double time)
		: m_time(time)
	{}

	virtual void OnUpdate(double delta) override final;
};