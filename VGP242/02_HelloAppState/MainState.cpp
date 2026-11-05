#include "MainState.h"
using namespace AzyEngine::Input;
void MainState::Initialize()
{
	LOG("MAIN STATE INITIALIZED");
}

void MainState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		AzyEngine::MainApp().ChangeState("GameState");
	}
}

void MainState::Terminate()
{
	LOG("MAIN STATE TERMINATED");
}
