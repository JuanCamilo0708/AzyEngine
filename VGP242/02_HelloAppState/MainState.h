#pragma once

#include <AzyEngine/Inc/AzyEngine.h>

class MainState : public AzyEngine::AppState
{
	void Initialize() override;
	void Update(float deltaTime) override;
	void Terminate() override;
};
