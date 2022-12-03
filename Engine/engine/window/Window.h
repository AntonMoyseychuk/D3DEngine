#pragma once
#include <string>
#include <memory>

#include "engine/utility/winapi/WinAPI.h"

#include "engine/input/Keyboard.h"
#include "engine/input/Mouse.h"

namespace engine::graphics::core {
	class SwapChain;
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
		Window(const wchar_t* title, uint32_t drawContextWidth, uint32_t drawContextHeight);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

	public:
		void SwapBuffers(bool vsync) const;
		void ClearBuffers(float r, float g, float b, float a = 1.0f) const noexcept;
	
	public:
		HWND GetHandle() const noexcept;
		float GetWidth() const noexcept;
		float GetHeight() const noexcept;

		RECT GetClientWindowRect() const noexcept;
		const wchar_t* GetTitle() const noexcept;
		void SetTitle(const wchar_t* title);

	private:
		static LRESULT WINAPI HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		LRESULT HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	public:
		input::Keyboard Keyboard;
		input::Mouse Mouse;

	private:
		HWND m_HWND;
		WindowClass& m_WindowClass;
		
		uint32_t m_Width;
		uint32_t m_Height;
		std::wstring m_Title;
		
		std::unique_ptr<graphics::core::SwapChain> m_SwapChain = nullptr;
	};
}