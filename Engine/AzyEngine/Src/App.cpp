#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace AzyEngine;
using namespace AzyEngine::Core;
using namespace AzyEngine::Graphics;
using namespace AzyEngine::Input;

void App::Run(const AppConfig& config)
{
	LOG("App Started");
	//initialize all singletons and windos (StaticInitializa)
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
	auto handle = myWindow.GetWindowHandle();
	GraphicsSystem::StaticInitialize(handle, false);
	InputSystem::StaticInitialize(handle);
	//initialize starting state
	ASSERT(mCurrentState != nullptr, "App: no state is set");
	mCurrentState->Initialize();

	InputSystem* input = InputSystem::Get();

	//updates
	mIsRunning = true;
	while (mIsRunning)
	{
		myWindow.ProcessMessage();
		input->Update();
		//updating all that needs updates

		if (!myWindow.IsActive() || input->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			continue;
		}
		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

		float deltaTime = TimeUtil::GetDeltaTime();

#if defined(_DEBUG)
		if (deltaTime > 0.5f)
		{
			continue;
		}
#endif
		mCurrentState->Update(deltaTime);
		
		GraphicsSystem* gs = GraphicsSystem::Get();
		gs->BeginRender();
			mCurrentState->Render();
			mCurrentState->DebugUI();
		gs->EndRender();

	}
	LOG("App Is Terminating");	
	// terminate last state
	mCurrentState->Terminate();

	//terminate all singletons and window (StaticTerminate)
	InputSystem::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	myWindow.Terminate();
}

void App::Quit()
{
	mIsRunning = false;
}

void AzyEngine::App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter!= mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}
