#include "Precompiled.h"
#include "AzyEngine.h"

App& AzyEngine::MainApp()
{
	static App sApp;
	return sApp;
}
