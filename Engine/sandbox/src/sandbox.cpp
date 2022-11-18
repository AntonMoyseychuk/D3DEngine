#include <memory>

#include "engine/src/app/Application.h"
#include "engine/src/utility/parser/Parser.h"
#include "engine/src/utility/exception/Exception.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	std::unique_ptr<engine::app::Application> app = nullptr;
	int result = { 0 };
	try {
		app = std::make_unique<engine::app::Application>(L"Sandbox", 1080, 720);

		result = app->Run();
	}
	catch (const engine::except::Exception& ex) {
		MessageBoxA(nullptr, ex.what(), "Unexpected Error", MB_ICONEXCLAMATION | MB_OK);
	}

	return result;
}