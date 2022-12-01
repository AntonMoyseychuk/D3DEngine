#pragma once
#include <string>
#include <memory>

#include "engine/src/utility/winapi/WinAPI.h"
#include "engine/src/graphics/SwapChain.h"

#include "engine/src/input/Keyboard.h"
#include "engine/src/input/Mouse.h"

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
		Window(const wchar_t* title, uint32_t width, uint32_t height);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

	public:
		void SwapBuffers(bool vsync);
	
	public:
		const wchar_t* GetTitle() const noexcept;
		HWND GetHandle() const noexcept;
		void SetTitle(const wchar_t* title);
		float GetHeight() const noexcept;
		float GetWidth() const noexcept;

	private:
		static LRESULT WINAPI HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		LRESULT HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	public:
		input::Keyboard Keyboard;
		input::Mouse Mouse;

	private:
		WindowClass& m_WindowClass;
		
		HWND m_HWND;
		
		std::wstring m_Title;
		uint32_t m_Width;
		uint32_t m_Height;
		
		graphics::SwapChain m_SwapChain;
	};
}