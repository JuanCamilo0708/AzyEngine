#include "Precompiled.h"
#include "WindowMessageHandler.h"
#include "DebugUtil.h"

using namespace AzyEngine::Core;

void AzyEngine::Core::WindowMessageHandler::Hook(HWND window, Callback cb)
{
	mWindow = window;
	mPreviousCallbadck = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC);
	SetWindowLongA(window, GWLP_WNDPROC, (LONG_PTR)cb);

}

void AzyEngine::Core::WindowMessageHandler::UnHook()
{
	SetWindowLongPtrA(mWindow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallbadck);
	mWindow = nullptr; 
}

LRESULT AzyEngine::Core::WindowMessageHandler::ForwardMessage(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ASSERT(mPreviousCallbadck != nullptr, "WindowMessageHandler: no callback is hooked!");
	return CallWindowProcA((WNDPROC)mPreviousCallbadck, window, msg, wParam, lParam);
}
