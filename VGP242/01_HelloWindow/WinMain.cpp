#include <AzyEngine/Inc/AzyEngine.h>

using namespace AzyEngine;
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Window";

	App myApp;
	myApp.Run(config);
}