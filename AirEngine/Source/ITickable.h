#pragma once

class ITickable
{
public:
	ITickable();
	virtual ~ITickable();

	virtual void Tick(double delta) = 0;
};