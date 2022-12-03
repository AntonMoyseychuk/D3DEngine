#include <memory>

#include "engine/application/Application.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	try {
		engine::app::Application engine(L"Sandbox", 1280, 900);
	
		return engine.Run();
	}
	catch (const std::exception& ex) {
		MessageBoxA(nullptr, ex.what(), "Unexpected Error", MB_ICONEXCLAMATION | MB_OK);
	}

	return 0;
}