// Your Demo Here
#include "Game.h"

#include "Macros.h"
#include "DefaultComponents.h"
#include "Sound.h"
#include "Music.h"
#include "Input.h"

constexpr const char* kExamplePlayer = "ExamplePlayer.xml";

using Key = InputCodes::Key;

bool Game::Init()
{
	PRINT("Starting Game");

	REGISTER_COMPONENT(AnimationComponent);

	AirEngine::GetWorldManager()->AddWorld("World.xml");

	AirEngine::GetAudioManager()->PlayMusic("CanonInD.ogg", true);
	
	AirEngine::GetGameObjectManager()->CreateObject<GameObject>(kExamplePlayer);
	return true;
}

void Game::Tick([[maybe_unused]] double delta)
{
	AirEngine::GetRenderer()->DrawText("Air Engine\n\tby Michael McCluskey", {350, 350}, "Pixellari.ttf", 48);

	if(Input::KeyPressed(Key::Escape))
		AirEngine::QuitGame();
}

void Game::Shutdown()
{
	PRINT("Shutting Down");
}

/*
static int CreateObject(lua_State* luaState)
{
	if (!luaState)
		return 0;

	size_t length = (size_t)lua_tointeger(luaState, 1);
	const char* pFilename = lua_tolstring(luaState, 2, &length);
	AirEngine::GetGameObjectManager()->CreateObject(pFilename);

	return 0;
}
*/
