#pragma once
#include "IProcess.h"

#include <functional>

class CallbackProcess : public IProcess
{
private:
	std::function<void()> m_function;

public:
	CallbackProcess(std::function<void()> function)
		: m_function(function)
	{}

	virtual void OnInit() override final;
};
