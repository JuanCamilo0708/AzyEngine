#pragma once

#include <AzyEngine/Inc/AzyEngine.h>

class GameState : public AzyEngine::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Terminate() override;
};