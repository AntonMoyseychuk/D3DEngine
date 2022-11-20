#include "Window.h"
#include "engine/src/graphics/Graphics.h"

#include "engine/src/utility/exception/WindowException.h"


namespace engine::window {
	Window::WindowClass Window::WindowClass::s_WindowClass;

	Window::WindowClass::WindowClass() noexcept
		: m_Instance(GetModuleHandle(nullptr))
	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.hInstance = GetInstance();
		wc.lpszClassName = GetName();
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = (HICON)LoadImage(nullptr, L"D:\\Studies\\Graphics\\D3DEngine\\Engine\\sandbox\\res\\texture\\icon.ico",
			IMAGE_ICON, DI_DEFAULTSIZE, DI_DEFAULTSIZE, LR_LOADFROMFILE);;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		RegisterClassEx(&wc);
	}

	Window::WindowClass::~WindowClass() noexcept
	{
		UnregisterClass(GetName(), GetInstance());
	}

	const wchar_t* Window::WindowClass::GetName() noexcept
	{
		return s_ClassName;
	}

	HINSTANCE Window::WindowClass::GetInstance() noexcept
	{
		return s_WindowClass.m_Instance;
	}


	Window::Window(const wchar_t* title, uint32_t width, uint32_t height)
		: m_Title(title)
	{
		RECT wr = { 0, 0, width, height };
		if (!AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false)) {
			throw ENGINE_WINDOW_LAST_ERROR_EXCEPTION();
		}
		m_Width = wr.right - wr.left;
		m_Height = wr.bottom - wr.top;

		m_HWND = CreateWindow(
			WindowClass::GetName(), title,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT,
			m_Width, m_Height,
			nullptr, nullptr,
			WindowClass::GetInstance(),
			this
		);
		if (m_HWND == nullptr) {
			throw ENGINE_WINDOW_LAST_ERROR_EXCEPTION();
		}

		ShowWindow(m_HWND, SW_SHOW);

		try {
			m_Graphics = std::make_unique<graphics::Graphics>(m_HWND);
		}
		catch (const except::Exception& ex) {
			DestroyWindow(m_HWND);
			throw;
		}
	}

	Window::~Window()
	{
		DestroyWindow(m_HWND);
	}

	Window::window_id Window::GetHandle() const noexcept
	{
		return m_HWND;
	}

	const wchar_t* Window::GetTitle() const noexcept
	{
		return m_Title.c_str();
	}

	void Window::SetTitle(const wchar_t* title)
	{
		if (!SetWindowText(m_HWND, title)) {
			throw ENGINE_WINDOW_LAST_ERROR_EXCEPTION();
		}
	}

	float Window::GetWidth() const noexcept
	{
		return m_Width;
	}

	float Window::GetHeight() const noexcept
	{
		return m_Height;
	}

	graphics::Graphics& Window::GetGraphics()
	{
		if (m_Graphics == nullptr) {
			throw ENGINE_D3D_NO_GRAPHIC_EXCEPTION();
		}
		return *m_Graphics;
	}

	LRESULT WINAPI Window::HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_NCCREATE) {
			const CREATESTRUCTW* const create = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Window* const window = reinterpret_cast<Window*>(create->lpCreateParams);

			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

			return window->HandleMsg(hwnd, msg, wParam, lParam);
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	LRESULT WINAPI Window::HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* const window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return window->HandleMsg(hwnd, msg, wParam, lParam);
	}

	LRESULT Window::HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_KILLFOCUS:
			Keyboard.ResetStateBuffer();
			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			if (!(lParam & 0x40000000 || Keyboard.IsAutorepeatEnable())) {
				Keyboard.OnKeyPressed(static_cast<uint8_t>(wParam));
			}
			break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
			Keyboard.OnKeyReleased(static_cast<uint8_t>(wParam));
			break;

		case WM_CHAR:
			Keyboard.OnChar(static_cast<char>(wParam));
			break;

		case WM_MOUSEMOVE:
		{
			const POINTS pt = MAKEPOINTS(lParam);

			if (pt.x >= 0 && pt.x < m_Width && pt.y >= 0 && pt.y < m_Height) {
				Mouse.OnMove(pt.x, pt.y);
				if (!Mouse.IsInClientState()) {
					SetCapture(m_HWND);
					Mouse.OnEnter();
				}
			}
			else {
				if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
					Mouse.OnMove(pt.x, pt.y);
				}
				else {
					ReleaseCapture();
					Mouse.OnLeave();
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Mouse.OnLeftButtonPressed(pt.x, pt.y);
			break;
		}
		case WM_LBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Mouse.OnLeftButtonReleased(pt.x, pt.y);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Mouse.OnRightButtonPressed(pt.x, pt.y);
			break;
		}
		case WM_RBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Mouse.OnRightButtonReleased(pt.x, pt.y);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			int16_t delta = GET_WHEEL_DELTA_WPARAM(wParam);

			Mouse.OnWheel(pt.x, pt.y, delta);
			break;
		}
		case WM_MOUSEHOVER:
		{
			Mouse.OnEnter();
			break;
		}
		case WM_MOUSELEAVE:
		{
			Mouse.OnLeave();
			break;
		}

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}

		return 0;
	}
}