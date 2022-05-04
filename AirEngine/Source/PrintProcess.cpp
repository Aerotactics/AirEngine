#include "PrintProcess.h"
#include "Logger.h"

void PrintProcess::OnInit()
{
	PRINT(m_pText);
	Succeed();
}