#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace AzyEngine;
using namespace AzyEngine::Core;
using namespace AzyEngine::Graphics;

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
	//initialize starting state

	//updated
	mIsRunning = true;
	while (mIsRunning)
	{
		myWindow.ProcessMessage();
		//updating all that needs updates

		if (!myWindow.IsActive())
		{
			Quit();
			continue;
		}

	}
	LOG("App Is Terminating");	
	// terminate last state

	//terminate all singletons and window (StaticTerminate)
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
