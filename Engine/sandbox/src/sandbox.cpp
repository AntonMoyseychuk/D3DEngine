#include <memory>

#include "engine/src/app/Application.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	std::unique_ptr<engine::app::Application> app = nullptr;
	int result = { 0 };
	try {
		app = std::make_unique<engine::app::Application>(L"Sandbox", 1280, 900);
	
		result = app->Run();
	}
	catch (const std::exception& ex) {
		MessageBoxA(nullptr, ex.what(), "Unexpected Error", MB_ICONEXCLAMATION | MB_OK);
	}

	return 0;
}