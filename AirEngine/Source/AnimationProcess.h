#pragma once
#include "IProcess.h"

class AnimationComponent;

class AnimationProcess : public IProcess
{
private:
	AnimationComponent* m_pComponent;
	double m_framerate;
	int m_frameWidth;
	int m_frameHeight;
	double m_elapsed;
	int m_frameCount;
	int m_currentFrame;
	bool m_isLooping;

public:
	AnimationProcess(AnimationComponent* pComponent, double framerate, bool isLooping = false)
		: m_pComponent(pComponent)
		, m_framerate(framerate)
		, m_frameWidth(0)
		, m_frameHeight(0)
		, m_elapsed(0)
		, m_frameCount(0)
		, m_currentFrame(0)
		, m_isLooping(isLooping)
	{}

	virtual void OnInit() override final;
	virtual void OnUpdate(double delta) override final;

	virtual void OnSuccess() override final;
};