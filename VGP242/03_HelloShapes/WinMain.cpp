#include <AzyEngine/Inc/AzyEngine.h>
#include "DoSomethigState.h"
#include "DoColorState.h"
#include "ThirdState.h"
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AzyEngine::AppConfig config;
	config.appName = L"Hello Shapes";

	AzyEngine::App& myApp = AzyEngine::MainApp();
	myApp.AddState<DoSomethigState>("DoSomethingState");
	myApp.AddState<DoColorState>("DoColorState");
	myApp.AddState<ThirdState>("ThirdState");
	myApp.Run(config);
	return 0;
}