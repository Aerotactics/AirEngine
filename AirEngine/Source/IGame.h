#pragma once

class IGame
{
public:
	virtual ~IGame() {}

	virtual const char* GetGameName() const { return ""; }
	virtual bool Init() = 0;
	virtual void Tick(double delta) = 0;
	virtual void Shutdown() = 0;
};