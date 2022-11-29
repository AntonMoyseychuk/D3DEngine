#pragma once
#include <string>
#include <memory>

#include "engine/src/utility/winapi/WinAPI.h"

#include "engine/src/input/Keyboard.h"
#include "engine/src/input/Mouse.h"

namespace engine::graphics {
	class Graphics;
}

namespace engine::window {
	class Window
	{
	private:
		class WindowClass
		{
		public:
			static const wchar_t* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;

			static WindowClass& Get() noexcept;
		private:
			WindowClass(const wchar_t* iconFilepath) noexcept;
			~WindowClass() noexcept;

			WindowClass(const WindowClass& wc) = delete;
			WindowClass& operator=(const WindowClass& wc) = delete;

		private:
			static constexpr const wchar_t* s_ClassName = L"Window";
			HINSTANCE m_Instance;
		};

	public:
		typedef HWND window_id;

		Window(const wchar_t* title, uint32_t width, uint32_t height);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		const wchar_t* GetTitle() const noexcept;
		window_id GetHandle() const noexcept;
		void SetTitle(const wchar_t* title);
		float GetHeight() const noexcept;
		float GetWidth() const noexcept;

		graphics::Graphics& GetGraphics();

	private:
		static LRESULT WINAPI HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		LRESULT HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	public:
		input::Keyboard Keyboard;
		input::Mouse Mouse;

	private:
		window_id m_HWND;
		
		std::wstring m_Title;
		uint32_t m_Width;
		uint32_t m_Height;

		WindowClass& m_WindowClass;

		std::unique_ptr<engine::graphics::Graphics> m_Graphics = nullptr;
	};
}