#include "Precompiled.h"
#include "App.h"

using namespace AzyEngine;
using namespace AzyEngine::Core;

void App::Run(const AppConfig& config)
{
	LOG("App Started");
	//initialize all singletons
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
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

	//terminate all singletons and window
	myWindow.Terminate();
}

void App::Quit()
{
	mIsRunning = false;
}