#include <windows.h>

#include "editor_app_delegate.h"

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	auto& application = engine::application::instance();
	auto app_delegate = editor_app_delegate();

	application.set_delegate(&app_delegate);
	application.on_launched();

	return 0;
}