#include "GameState.h"
using namespace AzyEngine::Input;
void GameState::Initialize()
{
	LOG("GAME STATE INITIALIZED");

}

void GameState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		AzyEngine::MainApp().ChangeState("MainState");
	}
}

void GameState::Terminate()
{

	LOG("GAME STATE TERMINATED");
}
