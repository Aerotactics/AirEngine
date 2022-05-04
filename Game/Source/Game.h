#pragma once

#include "IGame.h"

class Game : public IGame
{
public:
	virtual const char* GetGameName()  const override final { return "Demo Game"; }
	virtual bool Init() override final;
	virtual void Tick(double delta) override final;
	virtual void Shutdown() override final;
};