#include <AzyEngine/Inc/AzyEngine.h>
#include "MainState.h"
#include "GameState.h"
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AzyEngine::AppConfig config;
	config.appName = L"Hello App State";

	AzyEngine::App& myApp = AzyEngine::MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.AddState<MainState>("MainState");

	myApp.Run(config);


	return 0;
}