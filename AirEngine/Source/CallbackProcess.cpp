#include "CallbackProcess.h"

void CallbackProcess::OnInit()
{
	m_function();
	Succeed();
}