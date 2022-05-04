#pragma once
#include "IComponent.h"

class AnimationProcess;
class SpriteComponent;
class IProcess;
class Texture;

class AnimationComponent : public IComponent
{
	friend AnimationProcess;

private:
	SpriteComponent* m_pSpriteComponent;
	Texture* m_pOriginalTexture;
	Texture* m_pAnimationTexture;
	std::string m_currentAnimation;
	IProcess* m_pProcess;

public:
	AnimationComponent();

	virtual bool Init(tinyxml2::XMLElement* pData) override final;

	void PlayAnimation(const std::string& filename, double framerate, bool isLooping = false);
	void StopAnimation(const std::string& filename);

	void SetSpriteComponent(SpriteComponent* pComponent) { m_pSpriteComponent = pComponent; }

protected:
	SpriteComponent* GetSpriteComponent() { return m_pSpriteComponent; }
	Texture* GetAnimationTexture() { return m_pAnimationTexture; }

	void Reset();
};