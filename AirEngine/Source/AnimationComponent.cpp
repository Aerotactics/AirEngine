#include "AnimationComponent.h"

#include "AirEngine.h"
#include "GameObject.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "AnimationProcess.h"
#include "TinyXML/tinyxml2.h"

using XMLElement = tinyxml2::XMLElement;

AnimationComponent::AnimationComponent()
	: m_pSpriteComponent(nullptr)
	, m_pOriginalTexture(nullptr)
	, m_pAnimationTexture(nullptr)
	, m_currentAnimation()
	, m_pProcess(nullptr)
{}

bool AnimationComponent::Init([[maybe_unused]] tinyxml2::XMLElement* pData)
{
	IComponent* pComponent = m_pOwner->GetComponent("SpriteComponent");
	if (!pComponent)
		return false;
	SetSpriteComponent(static_cast<SpriteComponent*>(pComponent));
	return true;
}

void AnimationComponent::PlayAnimation(const std::string& filename, double framerate, bool isLooping)
{
	if (!strcmp(filename.c_str(), m_currentAnimation.c_str()) && !m_currentAnimation.empty())
		return;

	if (!m_currentAnimation.empty())
	{
		StopAnimation(m_currentAnimation);
	}

	m_currentAnimation = filename;
	m_pOriginalTexture = m_pSpriteComponent->GetSprite()->GetTexture();
	m_pAnimationTexture = static_cast<Texture*>(AirEngine::GetResourceManager()->Load(filename.c_str()));

	if (m_pAnimationTexture)
		m_pProcess = AirEngine::GetProcessManager()->StartProcess(BLEACH_NEW(AnimationProcess(this, framerate, isLooping)));
	else
		Reset();
}

void AnimationComponent::StopAnimation(const std::string& filename)
{
	if (strcmp(filename.c_str(), m_currentAnimation.c_str()))
	{
		LOG("Animation Component attempted to stop an incorrect animation.");
		return;
	}

	AirEngine::GetProcessManager()->StopProcess(m_pProcess);

	Reset();
}

void AnimationComponent::Reset()
{
	m_currentAnimation = "";
	m_pProcess = nullptr;
	m_pSpriteComponent->GetSprite()->SetTexture(m_pOriginalTexture);
	m_pOriginalTexture = nullptr;
}
