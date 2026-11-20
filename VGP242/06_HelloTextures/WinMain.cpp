#include <AzyEngine/Inc/AzyEngine.h>
#include "DoColorState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AzyEngine::AppConfig config;
	config.appName = L"Hello Mesh";

	AzyEngine::App& myApp = AzyEngine::MainApp();

	myApp.AddState<DoColorState>("DoColorState");

	myApp.Run(config);
	return 0;
}