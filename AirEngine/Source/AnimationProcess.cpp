#include "AnimationProcess.h"

#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Vector2.h"

void AnimationProcess::OnInit()
{
	SpriteComponent* pSpriteComponent = m_pComponent->GetSpriteComponent();
	Texture* pTexture = m_pComponent->GetAnimationTexture();

	Vector2<float> spriteSize = pSpriteComponent->GetSize();
	m_frameWidth = (int)spriteSize.x;
	m_frameHeight = (int)spriteSize.y;
	Vector2<unsigned int> textureSize = pTexture->GetSize();
	m_frameCount = textureSize.x / (unsigned int)spriteSize.x;
	m_elapsed = m_framerate;

	Sprite* pSprite = pSpriteComponent->GetSprite();
	pSprite->SetTexture(pTexture);
	pSprite->SetUV(0, 0);
}

void AnimationProcess::OnUpdate(double delta)
{
	m_elapsed -= delta;

	if(m_elapsed > 0.f)
		return;

	++m_currentFrame;
	if (m_currentFrame >= m_frameCount)
	{
		if (m_isLooping)
		{
			m_currentFrame = 0;
		}
		else
		{
			Succeed();
			return;
		}
	}

	m_pComponent->GetSpriteComponent()->GetSprite()->SetUV(m_currentFrame * m_frameWidth, 0);

	m_elapsed = m_framerate;
}

void AnimationProcess::OnSuccess()
{
	m_pComponent->Reset();
}
