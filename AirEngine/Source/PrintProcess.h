#pragma once
#include "IProcess.h"

class PrintProcess : public IProcess
{
private:
	const char* m_pText;

public:
	PrintProcess(const char* pText)
		: m_pText(pText)
	{}

	virtual void OnInit() override final;
};