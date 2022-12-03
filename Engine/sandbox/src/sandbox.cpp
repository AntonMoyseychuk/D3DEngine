#include <memory>

#include "engine/graphics_engine/application/Application.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	std::unique_ptr<graphics_engine::app::Application> app = nullptr;
	try {
		app = std::make_unique<graphics_engine::app::Application>(L"Sandbox", 1280, 900);
	
		return app->Run();
	}
	catch (const std::exception& ex) {
		MessageBoxA(nullptr, ex.what(), "Unexpected Error", MB_ICONEXCLAMATION | MB_OK);
	}

	return 0;
}