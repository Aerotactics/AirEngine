#include "pch.h"
#include "Ball.h"

#include "AirEngine.h"
#include "Processes.h"
#include "Player.h"

static constexpr float kStartSpeed = 2.f;

void Ball::Reset()
{
	if (!m_pTransformComponent)
	{
		m_pTransformComponent = static_cast<TransformComponent*>(GetComponent("TransformComponent"));
	}

	m_direction = {0.f, 0.f};
	m_speed = 0.f;

	m_pTransformComponent->SetPosition({502.f, 380.f});

	AirEngine::GetProcessManager()->StartProcess(new DelayProcess(1.f))
		->SetChild(new CallbackProcess([this]() { SetRandomVelocity(); } ));
}

void Ball::Move()
{
	m_pTransformComponent->Move(m_direction);
}

void Ball::SetRandomVelocity()
{
	m_speed = kStartSpeed;

	float velocity = float(rand() % 90) - 45.f;
	if(rand() % 100 >= 50)
		velocity += 180;

	SetVelocity(velocity, m_speed);
}

void Ball::SetVelocity(float angleDegrees, float speed)
{
	float rads = angleDegrees * kPi / 180.f;

	m_direction.x = speed * cosf(rads);
	m_direction.y = speed * sinf(rads);
}

void Ball::Tick(double delta)
{
	if (!m_lazyInit)
	{
		Reset();
		m_lazyInit = true;
	}
	Move();

	UpdateComponents(delta);
}

void Ball::OnEnterCollision(IGameObject* pOther)
{
	std::string name = pOther->GetName();

	if (name == "Goal")
	{
		Reset();
		AirEngine::GetAudioManager()->PlaySound("Goal.wav");
	}
	else if (name == "Player")
	{
		m_speed += 0.1f;
		
		Player* pPlayer = static_cast<Player*>(pOther);
		
		//Grab positions
		Vector2<float> pos = static_cast<TransformComponent*>(GetComponent("TransformComponent"))->GetPosition();
		Vector2<float> otherPos = static_cast<TransformComponent*>(pPlayer->GetComponent("TransformComponent"))->GetPosition();

		//Get Ball center point
		Vector2<float> size = static_cast<SpriteComponent*>(GetComponent("SpriteComponent"))->GetSize();
		pos.x += size.x / 2;
		pos.y += size.y / 2;

		//Get Player's Center point
		Vector2<float> otherSize = static_cast<SpriteComponent*>(pPlayer->GetComponent("SpriteComponent"))->GetSize();
		otherPos.x += otherSize.x / 2.f;
		otherPos.y += otherSize.y / 2.f;

		Vector2<float> directionVector = {otherPos.x - pos.x, otherPos.y - pos.y};

		//Get angle and convert to degrees
		//	So, atan2f works here, but atanf does not.
		//	Honestly, the ball is finally working as expected. I
		//	don't 100% understand why it works but it does.
		float radians = atan2f(directionVector.y, directionVector.x);
		float degrees = radians * (180.f / kPi);

		//Adjust for reflection
		SetVelocity(degrees + 180.f, m_speed);
	}
	else if (name == "Wall")
	{
		m_direction.y *= -1;
		AirEngine::GetAudioManager()->PlaySound("Bump.wav");
	}
}