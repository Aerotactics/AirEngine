#pragma once
#include "IComponent.h"
#include "IRenderable.h"
#include "ITickable.h"

#include "SFMLSprite.h"
#include "Bleach/BleachNew.h"

using Sprite = ISprite<SFMLSprite>;

class AnimationComponent;
class AnimationProcess;
class TransformComponent;

class SpriteComponent 
	: public IComponent
	, public IRenderable
	, public ITickable
{
	friend AnimationComponent;
	friend AnimationProcess; // Hmm...

private:
	Sprite* m_pSprite;
	TransformComponent* m_pTransform;

public:
	SpriteComponent();
	~SpriteComponent();

	virtual bool Init(tinyxml2::XMLElement* pData) override final;
	virtual void Tick([[maybe_unused]] double delta) override final;
	virtual void Draw(Window* pWindow) override final { m_pSprite->Draw(pWindow); }

	Vector2<float> GetSize() const { return m_pSprite->GetSize(); }

	void SetTransform(TransformComponent* pTransform) { m_pTransform = pTransform; }

protected:
	Sprite* GetSprite() { return m_pSprite; }
};