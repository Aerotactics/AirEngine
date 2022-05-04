#include "Player.h"

#include "AirEngine.h"
#include "SFMLSound.h"
#include "Input.h"

using Sound = ISound<SFMLSound>;
using Input = IInput<SFMLInput>;
using Key = InputCodes::Key;

void Player::SetPosition(Vector2<float> position)
{
    static_cast<TransformComponent*>(GetComponent("TransformComponent"))->SetPosition(position);
}

void Player::SetControls(int up, int down, int left, int right)
{
    static_cast<ControllerComponent*>(GetComponent("ControllerComponent"))->SetKeys(up, down, left, right);
}

void Player::PlayAnimation(const char* filename, double framerate, bool isLooping)
{
    std::string file(filename);
    static_cast<AnimationComponent*>(GetComponent("AnimationComponent"))->PlayAnimation(file, framerate, isLooping);
}

void Player::OnEnterCollision(IGameObject* other)
{
    std::string name = other->GetName();

    if (name == "Wall")
    {
        AirEngine::GetAudioManager()->PlaySound("Bump.wav");
    }
    else if (name == "Ball")
    {
        AirEngine::GetAudioManager()->PlaySound("Hit.wav");
        PlayAnimation("PlayerHit.png", 0.1f);
    }
}

void Player::Tick(double delta)
{
    Key up; 
    Key down;
    Key left;
    Key right;
    static_cast<ControllerComponent*>(GetComponent("ControllerComponent"))->GetKeys(up, down, left, right);
    if (Input::KeyPressed(up) || Input::KeyPressed(down))
    {
        PlayAnimation("PlayerRun.png", 0.2f);
    }

    UpdateComponents(delta);
}
