#include "DelayProcess.h"

void DelayProcess::OnUpdate(double delta)
{
	m_time -= delta;
	if (m_time <= 0)
		Succeed();
}